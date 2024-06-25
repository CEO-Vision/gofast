
/**
 * @file
 *  Drupal Autocomplete Extension.
 *  Relies on Bootstrap and Gofast subtheme.
 *  
 *  xAC = eXtended AutoComplete object
 *  
 *  To enable xAC features, use the special form element `#xAC` in the backend.
 *  An #xAC element is just an autocomplete textfield with extended parameters. 
 *  eg. 
 *      $form['some-text-field']['#xac'] = [
 *        'autocomplete_path' => '/path/to/xac-callback, // required
 *        // ... 
 *      ];
 *      
 *  @see parameters used in gofast_search_autocomplete_settings()
 */

(function($, Drupal, Gofast) {
  /**
   * GOFAST-4758 Force autocomplete popup to hide when clicking elsewhere
   */
  window.addEventListener('click', function(e) {
    const xacBox = document.querySelector('#search-block-form ul#xac-dropdown');
    if(!xacBox) {
      return;
    }
    if (!xacBox.contains(e.target)) {
      xacBox.style.display = "none";
    }
  });

  /**
   * Store original autocomplete objects prototypes.
   */
  var _xAC = Drupal.jsAC && Drupal.jsAC.prototype || undefined,
      _xACDB = Drupal.ACDB && Drupal.ACDB.prototype  || undefined;

  if (!(_xAC && _xACDB)) {
    console.log('Drupal autocomplete.js is missing.');
    return;
  }

  Gofast.xAC = Gofast.xAC || {};
  
  /**
   * Submit handler used for xAC inputs. 
   */
  Gofast.apply(Gofast.xAC, {
    submit: function() {
      var xACLab = $(this).find('.xAC-label'),
          link = xACLab.length && xACLab.find('a[href!="#"]'),
          href = link.length && link.attr('href');

      if (href) {
        Gofast.processAjax(href, false);
        return false;
      }

      Drupal.autocompleteSubmit.apply(this, arguments);
    }
  });  

  /**
   * @override
   *  Attaches and extends the autocomplete behavior to all required fields.
   */
  Drupal.behaviors.autocomplete = {
    attach: function (context, settings) {
      var acdb = [], $context = $(context);
      $context.find('input.autocomplete').once('autocomplete', function () {
        var uri = this.value,
            id = this.id.substr(0, this.id.length - 13),
            xACData = Drupal.settings.xac && Drupal.settings.xac[id],
            $input = $context.find('#' + id).attr('autocomplete', 'OFF')
                                            .attr('aria-autocomplete', 'list');
        if (!acdb[uri]) {
          acdb[uri] = new Drupal.ACDB(uri, xACData);
        }
        $context.find($input[0].form).submit(xACData && Gofast.xAC.submit || Drupal.autocompleteSubmit);
        $input.parents('.form-item')
          .attr('role', 'application')
          .append($('<span class="element-invisible" aria-live="assertive"></span>')
          .attr('id', $input.attr('id') + '-autocomplete-aria-live')
        );
        $input.parent().parent().attr('role', 'application');
        var instance = new Drupal.jsAC($input, acdb[uri], $context, xACData);
        
        // Autocomplete on paste 
        instance.autocompleteOnPaste($input);
      });
    }
  };

  /**
   * @override
   *  An AutoComplete DataBase object.
   */
  Drupal.ACDB = function (uri, xACData) {
    this.uri = uri;
    this.delay = xACData && xACData.delay || 300;
    this.cache = {};

    var collector = xACData && xACData.collector || Gofast;
    if (typeof collector === 'string') {
      collector = Gofast.access(collector);
    }

    this._setCollector(collector);
  };

  /**
   * Apply ACDB prototype back and extends it
   */
  Gofast.apply(Drupal.ACDB.prototype, {
    _setCollector: function (Collector) {
      // Destruct any previous collection..
      delete this.collection;
      this.collection = new Collector.Collection('xACDBCollection', this);
      this.collection._collector = Collector;
    },

    _getCollector: function () {
      return this.collection._collector;
    },

    getCollection: function () {
      return this.collection;
    },

    xACInit: function () {
      var xAC = this.owner.xAC;

      xAC.param = xAC.param || {};
      xAC.param.data = xAC.param.data || {};

      if (xAC.queryKey) {
        typeof xAC.queryKey === 'string' && (xAC.queryKey = xAC.queryKey.split(','));
        typeof xAC.queryKey !== 'object' && (xAC.queryKey = ['q']);
      }
    },

    /**
     * Performs a cached and delayed search.
     */
    search: function (searchString) {

      var db = this,
          xAC = db.owner.xAC,
          minLen = xAC && xAC.minLength || 3,
          parallel = xAC && xAC.parallel;

      this.searchString = searchString.trim();

      // See if this string needs to be searched for anyway. The pattern ../ is
      // stripped since it may be misinterpreted by the browser.
      searchString = searchString.replace(/^\s+|\.{2,}\/|\s+$/g, '');
      // Skip empty search strings
      if (searchString.length < minLen) {
        return null;
      }
      
      // Skip search strings ending with a comma, since that is the separator
      // between search terms.
      if (searchString.charAt(searchString.length - 1) === ',' && (!xAC || xAC.multiple === true)) {
        return null;
      }
       
      if (xAC && xAC.multiple) {
        var last = searchString.split(',').last();
        if (last && last.length < minLen) {
          return null;
        }
      }

      // See if this key has been searched for before.
      if (this.cache[searchString]) {
        return this.owner.found(this.cache[searchString]);
      }

      // Initiate delayed search.
      if (this.timer) {
        clearTimeout(this.timer);
      }
      
      db.collection.clean();
      
      this.timer = setTimeout(function () {
        db.collection.clean();
        db.owner.setStatus('begin');

        var escapedString;
        if (xAC) {
          db.xACInit();
          // Execute escape callback if any.
          escapedString = xAC.escFunc && Gofast.exec(xAC.escFunc, [searchString]) || searchString;
          xAC.queryKey && xAC.queryKey.forEach(function(key){
            xAC.param.data[key] = escapedString;
          });
        }
        else {
          escapedString = searchString;
        }

        // Ajax GET requests for autocompletion. Use Drupal.encodePath instead
        // of encodeURIComponent to allow autocomplete search terms to contain
        // slashes. If xAC data are given we pass the params in a query string.
        var main = Gofast.apply({
          name: xAC && xAC.name || 'main',
          type: 'GET',
          url: xAC && xAC.queryKey && db.uri || db.uri + '/' + Drupal.encodePath(escapedString),
          dataType: 'json',
          beforeSend: function(xhr) {
            Gofast.xhrPool = Gofast.xhrPool || {};
            Gofast.xhrPool.xhrAutoComplete = xhr;
          },
          'complete': function() {
            delete Gofast.xhrPool.xhrAutoComplete;
          },
          success: function (results) {
            if (Array.isArray(results) && !results.lentgh) {
              return;
            }
            
            if (typeof results.status === 'undefined' || results.status !== 0) {              
              var Collection = db.getCollection(),
                  callback = xAC && (this.callback || xAC.callback),
                  matches;

              if (callback) {
                results = Gofast.exec(callback, [results, escapedString, searchString]) || results;
              }
              
              // Collect data source results and fetch the current collection.
              Collection.collect(results, this.name);
              matches = Collection.getData();

              if (matches.size() && xAC || $(db.owner.input).hasClass('labelize-insert')) {
                // Add the term itself to comply with kind of google-like
                // behavior (i.e: highlights and selects the 1st item that is
                // the entry currently being typed).
                // Use the raw term entry to match with the user input.
                var entry = {};
                entry[searchString] = searchString;
                matches = Gofast.apply(entry, matches);
              }

              // Cache the current collection and fill the suggestion popup.
              db.cache[searchString] = matches;
              
              // If these aren't the matches the user wants to see anymore, 
              // don't show them.
              if (db.searchString !== searchString) {
                return;
              }

              if (Collection.size() > 1) {
                db.owner.refresh(matches);
              }
              else {
                db.owner.found(matches);
              }

              db.owner.setStatus('found');
            }
          },
          error: function (jqXHR, textStatus, errorThrown) {
            if (textStatus !== 'abort')
              Drupal.ajaxError(jqXHR, db.uri);
          }
        }, xAC && xAC.param || {});

        var collection = db.getCollection(),
            requests = collection.getRequests();

        Gofast.exec(collection.register, [main, xAC && xAC.name || 'main'], collection);

        if (parallel && parallel.requests) {
          db.parallelize(parallel.requests, main);
        }

        for (var name in requests) {
          $.ajax(requests[name]);
        }

      }, this.delay);
    },

    parallelize: function (requests, main) {
      var collection = this.getCollection(),
          opts, url;

      for (var name in requests) {
        // Use main request options as defaults.
        opts = Gofast.apply({}, requests[name], {
          name: name,
          type: main.type,
          dataType: main.dataType,
          success: main.success,
          error: main.error
        });

        url = Gofast.get('baseUrl') + '/' + opts.url;
        opts.url = url + '/' + Drupal.encodePath(this.searchString);

        Gofast.exec(collection.register, [opts, name], collection);
      }
    },
    
    cancel : function () {
      if (this.owner) 
        this.owner.setStatus('cancel');
      
      if (this.timer) 
        clearTimeout(this.timer);
      
      // Preserve this.searchString anyway for search callback to run properly.
      // this.searchString = 'Do not reset me !';
    }
    
  }, _xACDB);

  /**
   * @override
   *  An AutoComplete object.
   */
  Drupal.jsAC = function ($input, db, $context, xACData) {
    var ac = this;

    this.$context = $context || $(document);
    this.input = $input[0];
    this.ariaLive = this.$context.find('#' + this.input.id + '-autocomplete-aria-live');
    this.db = db;

    // Flag this if ac jsAC input is embedded in a vertical tab to fix display.
    this.vt = $input.closest('.vertical-tabs-pane').length > 0;

    if (xACData) {
      Gofast.apply(this, {xAC: xACData});
    }

    $input
      .keydown(function (event) { return ac.onkeydown(this, event); })
      .keyup(function (event) { ac.onkeyup(this, event); })
      .blur(function () {
        ac.selected = false;
        ac.hidePopup(); 
        ac.db.cancel();
      });
  };

  /**
   * Apply AC prototype overrides + merge in defaults.
   */
  Gofast.apply(Drupal.jsAC.prototype, {
//    hidePopup: function () {
//      // debug;
//    },

    /**
     * Handler for the "keydown" event.
     */
    onkeydown: function (input, e) {
      if (!e) {
        e = window.event;
      }
      switch (e.keyCode) {
        case 9:  // Tab.
          if (e.shiftKey === true) {
            this.selectUp();
            return false;
          }
        case 40: // down arrow.
          this.selectDown();
          return false;
        case 38: // up arrow.
          this.selectUp();
          return false;
        case 27: // Esc.
          // Reset selection if any selected or hide popup.
          if (this.selected && this.selected.previousSibling) {
            this.autoselect(true);
          }
          else {
            this.hidePopup(e.keyCode);
          }
          this.input.value = "";
          return false;
        case 13:
          return true;
        default: // All other keys.
          // Ensure no labelized item clutters the input.
          var $label = $(this.input).next('.xAC-label');
          if ($label.length) {
            var text = $label.text();
            $label.remove();
            if (this.xAC && this.xAC.editableLabel) {
              this.input.value = text;
              this.xAC.editingLabel = true;
            }
          }
          return true;
      }
    },

    /**
     * Handler for the "keyup" event.
     */
    onkeyup: function (input, e) {
      var editingLabel;
      if (this.xAC) {
        editingLabel = this.xAC.editingLabel;
        this.xAC.editingLabel = false;
      }
      if (!e) {
        e = window.event;
      }
      if (e.ctrlKey || e.altKey || e.metaKey || e.key === 'Meta') {
        // ignore if already holding a control key
        return true;
      }
      switch (e.keyCode) {
        case 9:  // tab
        case 16: // shift
        case 17: // ctrl
        case 18: // alt | opt
        case 20: // caps lock
        case 33: // page up
        case 34: // page down
        case 38: // up arrow
        case 40: // down arrow
        case 91: // left [ window | command ]
        case 92: // right window
        case 93: // select | right command
          return true;
          
        case 35: // end
        case 36: // home          
        case 37: // left arrow
        case 39: // right arrow
          if (editingLabel) {
            this.populatePopup();
          }
          return true;
        
        case 13: // Enter.
          this.hidePopup(e.keyCode);
          return true; // then submit

        default: // All other keys.
          if (input.value.length > 0 && !input.readOnly) {
            this.populatePopup();
          }
          else {
            this.hidePopup(e.keyCode);
            if (this._popup) {
              $(this._popup).remove();
            }
          }
          return true;
      }
    },

    /**
     * Highlights the currently typed entry.
     */
    autoselect: function (forceSelect) {
      $(this.input).next('.xAC-label').remove();
      var lis = $('li', this.popup);
      if (lis.length > 0) {
        this.highlight(lis.get(0)); // update this.selected
        // Call select() only when required to prevent unwanted trimming of the 
        // input string.
        if (this.selected && this.selected.previousSibling || forceSelect) {
          this.select(this.selected);
        }
      }
    },

    select: function (node) {
      this.input.value = $(node).data('autocompleteValue');

      var $node = $(node),
          $input = $(this.input);

      $input.next('.xAC-label').remove();
      if ($node.find('a[href!="#"]').length) {
        var $label = $node.clone().addClass('xAC-label');
        $label.insertAfter($input);
      }

      $(this.input).trigger('autocompleteSelect', [node]);
    },

    /**
     * Highlights and inputs the next suggestion.
     */
    selectDown: function () {
      if (this.selected && this.selected.nextSibling) {
        this.highlight(this.selected.nextSibling);
        this.select(this.selected);
      }
      else if (this.popup) {
        var lis = $('li', this.popup);
        if (lis.length > 0) {
          this.highlight(lis.get(0));
          this.select(this.selected);
        }
      }
    },

    /**
     * Highlights and inputs the previous suggestion.
     */
    selectUp: function () {
      if (this.selected && this.selected.previousSibling) {
        this.highlight(this.selected.previousSibling);
        this.select(this.selected);
      }
      else if (this.popup) {
        var lis = $('li', this.popup);
        if (lis.length > 0) {
          // jQuery won't set node siblings if we use .last() method.
          this.highlight(lis.get(lis.length-1));
          this.select(this.selected);
        }
      }
    },

    /**
     * Positions the suggestions popup and starts a search.
     */
    populatePopup: function () {
      var $input = $(this.input);

      // Remove previous state suggestions popup from DOM.
      if (this._popup) {
        $(this._popup).remove();
      }

      // Remember the current state of the popup.
      if (this.popup) {
        this._popup = this.popup;
      }

      this.selected = false;
      this.popup = $('<div class="dropdown"></div>')[0];
      this.popup.owner = this;

      $input.parent().after(this.popup);

      // Fix display if dropdown is in a vertical tab.
      if (this.vt) {
        $(this.popup).css({position:'absolute', width:$input.closest('.input-group').width()+'px'});
      }

      // Do search.
      this.db.owner = this;
      this.db.search(this.input.value);
    },

    /**
     * Fills the suggestion popup with any matches received.
     */
    found: function (matches) {
      // Ensures no previous state suggestions covers the actual popup.
      if (this._popup) {
        $(this._popup).remove();
      }

      // If no value in the textfield, do not show the popup.
      if (!this.input.value.length || !Object.keys(matches).length) {
        return false;
      }

      // Prepare matches.
      var ul = $('<ul class="dropdown-menu" id="xac-dropdown"></ul>');
      var ac = this;
      ul.css({
        display: 'block',
        right: 0,
        'min-width': 300,
      });
            
      for (var key in matches) {
        //Remove uncessessary <a> tag - already present in result(matches)
        if (matches[key].indexOf('<a') === 0 ){
          
          let element_match = $.parseHTML(matches[key]);
          let element_data = $(element_match).attr("href").split("/")
          let element_type = element_data[1];
          $(element_match).click(function (e) { 
            e.preventDefault(); 
            if(Gofast._settings.isEssential){
              e.stopPropagation();
            }
          });
          
          if(Gofast._settings.isEssential){

            $('<li class="dropdown-item"></li>').html($(element_match)).mousedown(function(){
              let nid = element_data[element_data.length-1];
              Gofast.Essential.goToNode(nid, element_type)
            })
            .appendTo(ul);
          } else {

            $('<li class="dropdown-item"></li>')
            .html($(element_match))
            .mousedown(function () {
              ac.highlight(this);
              ac.select(this);
              ac.hidePopup(this);
              if (ac.xAC && ac.xAC.submitOnClick) {
                $(ac.input.form).submit();
              }
            })
            .data('autocompleteValue', key)
            .appendTo(ul);
          }
        }
        else{
          $('<li class="dropdown-item"></li>')
          .html($('<a href="#"></a>').html(matches[key])
            .click(function (e) { e.preventDefault(); })
          )
          .mousedown(function () {
            if(!Gofast._settings.isEssential){
              ac.highlight(this);
              ac.select(this);
              ac.hidePopup(this);
              if (ac.xAC && ac.xAC.submitOnClick) {
                $(ac.input.form).submit();
              }
            }
          })
          .data('autocompleteValue', key)
          .appendTo(ul);
        }
      }

      // Show popup with matches, if any.
      if (this.popup) {
        if (ul.children().length) {
          $(this.popup).empty().append(ul).show();
          var inputAC = this.$context.find('input.autocomplete');
          window.setTimeout(function () {
            inputAC.triggerHandler('autocomplete');
          }, 150);
          $(this.ariaLive).html(Drupal.t('Autocomplete popup', {}, {'context' : 'gofast'}));
          this.autoselect();
        }
        else {
          $(this.popup).css({ visibility: 'hidden' });
          this.hidePopup();
        }
      }
    },
    
    refresh: function (matches) {
      var ul = $('ul#xac-dropdown');
      var ac = this;
      ul.empty();

      for (var key in matches) {
        //Remove uncessessary <a> tag - already present in result(matches)
        if (matches[key].indexOf('<a') === 0 ){
          var element_match = $.parseHTML(matches[key]);
          $(element_match).click(function (e) { e.preventDefault(); });
          $('<li class="dropdown-item"></li>')
          .html($(element_match))
          .mousedown(function () {
            ac.highlight(this);
            ac.select(this);
            ac.hidePopup(this);
            if (ac.xAC && ac.xAC.submitOnClick) {
              $(ac.input.form).submit();
            }
          })
          .data('autocompleteValue', key)
          .appendTo(ul);
        }
        else{
          $('<li class="dropdown-item"></li>')
          .html($('<a href="#"></a>').html(matches[key])
            .click(function (e) { e.preventDefault(); })
          )
          .mousedown(function () {
            ac.highlight(this);
            ac.select(this);
            ac.hidePopup(this);
            if (ac.xAC && ac.xAC.submitOnClick) {
              $(ac.input.form).submit();
            }
          })
          .data('autocompleteValue', key)
          .appendTo(ul);
        }
      }

      // Show popup with matches, if any.
      if (this.popup) {
        if (ul.children().length) {
          //$(this.popup).empty().append(ul).show();
          var inputAC = this.$context.find('input.autocomplete');
          window.setTimeout(function () {
            inputAC.triggerHandler('autocomplete');
          }, 150);
          $(this.ariaLive).html(Drupal.t('Autocomplete popup', {}, {'context' : 'gofast'}));
          this.autoselect();
        }
        else {
          $(this.popup).css({ visibility: 'hidden' });
          this.hidePopup();
        }
      }      
    },
    
    autocompleteOnPaste: function ($input){
      $input.on('paste', function() {
        try {
          setTimeout(() => {
            $(this).trigger('keyup');
          }, 0);
        } catch (error) {
          console.error('An error occurred while handling the paste event:', error);
        }
      });
    }
  }, _xAC);
  
  /**
   * @override
   */
  Drupal.autocompleteSubmit = function () {
    $('.form-autocomplete > .dropdown').each(function () {
      this.owner.hidePopup();
    });
    return true;
  };  

})(jQuery, Drupal, Gofast);
