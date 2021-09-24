
/**
 * @file
 *  Handles Gofast Search front-end functionalities
 */

(function ($, Gofast, Drupal) {

  Drupal.settings.gofast = Drupal.settings.gofast || {};
  Gofast.search = Gofast.search || {};

  /**
   * Process search results snippets. Provides navigation links allowing user
   * to navigate across snippets.
   */
  Drupal.behaviors.gofastSearchSnippetsSlides = {
    attach : function (context, settings) {
      $('.snippets:not(.page-processed)').addClass('page-processed').each(function(){
        var etid = $(this).attr('etid');
        $(this).paginateTable({
          rowsPerPage: 1,
          pager: '.pager' + etid
        });
      });
    }
  };

  /**
   * Gofast Search "go" feature. Process "go" links so that solr highlighting
   * is extended on a target page.
   */
  Drupal.behaviors.gofastSearchGoHighlight = {
    attach : function (context, settings) {
      var ctxt = $(context);
      $('.search-results a.go-search-snippet:not(.snippet-processed)', ctxt).addClass('snippet-processed').each(function() {
        var word = $(this).attr('word'),
            snippet = $(this).attr('snippet');
        if (word && snippet) {
          Drupal.settings.gofast.highlight = Drupal.settings.gofast.highlight || {};
          $(this).click(function(){
            Drupal.settings.gofast.highlight.word = word;
            Drupal.settings.gofast.highlight.snippet = snippet;
          });
        }
      });
    }
  };

  /**
   * Preprocess word/snippet highlight configs from settings or url, and apply
   * on the target page if applicable.
   */
  Drupal.behaviors.gofastSearchHighlightTarget = {
    attach: function (context, settings) {
      Drupal.settings.gofast.highlight = Drupal.settings.gofast.highlight || {};
      var hl = Drupal.settings.gofast.highlight;
      if (hl.word && hl.snippet) {
        if (!hl.selector) {
          var queryVars = Gofast.getQueryVariables();
          hl.selector = queryVars.selector ? queryVars.selector : null;
        }
        Gofast.highlightElement(hl.word, hl.snippet, hl.selector);
        Drupal.settings.gofast.highlight = {};
      }
      else {
        var queryVars = Gofast.getQueryVariables();
        if (queryVars.word && queryVars.snippet) {
          var selector = queryVars.selector ? queryVars.selector : null;
          Gofast.highlightElement(queryVars.word, queryVars.snippet, selector);
        }
      }
    }
  };

//  Drupal.behaviors.solrSearchOptionsPersistence = {
//    attach: function(context) {
//      var $context = $(context).find('.search-options');
//      if (!$context.length) return;
//
//      var toogleOption = function (item, value) {
//        $(item).toggleClass('item-checked');
//        return value === '1' ? '0' : '1';
//      };
//
//      $('li:not(.item-processed)', $context).addClass('item-processed').each(function(){
//        var item = $(this),
//         itemId = item.attr('item'),
//         formItem = $('input:hidden[name=' + itemId + ']');
//
//        $(this).click(function(e){
//          e.preventDefault();
//          e.stopPropagation();
//          formItem.val(toogleOption(item, formItem.val()));
//          Gofast.setCookie('search_params', $('#search-form').serialize(), 31536000);
//        });
//      });
//    }
//  };


  Drupal.behaviors.solrSearchOptionsPersistence = {
    attach: function(context) {

      var $context = $(context).find('.container-filter');
      if (!$context.length) return;


      var toogleOption = function (item, value) {
        $(item).toggleClass('item-checked');
        return value === '1' ? '0' : '1';
      };

     /* $('#facetapi_search_filters .bootstrap-switch-wrapper:not(.item-processed)', $context).addClass('item-processed').each(function(){
        $(this).click(function(e){
            alert("click");
          var item = $(e.currentTarget);
          itemId = item.attr('item');
          formItem = $('input:hidden[name=' + itemId + ']');
          e.preventDefault();
          e.stopPropagation();
          //formItem.val(toogleOption(item, formItem.val()));
          Gofast.setCookie('search_params', $('#search-form').serialize(), 31536000);
          $('.search-form').trigger('submit');
        });
      });*/
    }
  };

  Drupal.behaviors.solrSearchResultsActions = {
    attach : function (context, settings) {
      var callback = function() {
        //$(this).find('.icone_actions').click();
      },
      config = {
        sensitivity: 1,  // number = sensitivity threshold (must be 1 or higher)
        interval: 100,   // number = milliseconds for onMouseOver polling interval
        over: callback,  // function = onMouseOver callback (REQUIRED)
        timeout: 200,    // number = milliseconds delay before onMouseOut
        out: callback    // function = onMouseOut callback (REQUIRED)
      };
      $('.search-result dt.title:not(.actions-processed)').addClass('actions-processed').each(function() {
        $(this).hoverIntent(config);
      });
    }
  };

  /**
   * Get more result snippets asynchronously
   */
  Drupal.behaviors.gofastSearchGetMoreSnippets = {
    attach: function (context, settings) {
      if (Gofast.get('more-snippets-async')) {
        // Remove flag to prevent duplicate requests.
        delete Drupal.settings.gofast_search['more-snippets-async'];
        var keywords = Drupal.settings.gofast_search['q'];
        
        if (keywords && keywords.length && keywords !== '*:*') {
          var start = Drupal.settings.gofast_search['start'];
          var rows = Drupal.settings.gofast_search['rows'];
          
          // Add loader + tooltip to be displayed on hover.
          var $loader = $('<div class="loader-more-snippets">');
          var loaderSelector = '.loader-more-snippets';
          $loader.attr({
            'data-toggle': 'tooltip',
            'data-placement': 'left',
            'data-original-title': Drupal.t('loading more snippets...')
          });

          // Wait for the current resultset to fully populate the DOM.
          setTimeout(function() {
            $('.search-result').append($loader).hover(function(e){
              $(e.currentTarget).find(loaderSelector).show();
            }, function(e){
              $(e.currentTarget).find(loaderSelector).hide();
            });
            $(loaderSelector).tooltip();

            var path = '/gofast-search/more-snippets-async';
            $.ajax({
              type: 'GET',
              url : Drupal.settings.gofast.baseUrl + path,
              data: {
                'hl.q': keywords,
                start: start,
                rows: rows
              },
              dataType: 'json',
              // Add the xhr object to the pool.
              beforeSend: function (xhr, options) {
                Gofast.xhrPool = Gofast.xhrPool || {};
                Gofast.xhrPool.searchMoreSnippets = xhr;
              },
              success: function (data) {
                if (typeof data.snippets === 'undefined') {
                  // Drupal request succeeded but the proxied request to Solr may
                  // fail.
                  var errorMsg = data.error || 'unknown error';
                  console.error(errorMsg);
                  return;
                }
                // Iterate each results and replace snippets. Since the pagination
                // is going to be reset we keep track of each snippet' currentPage
                // so we can reapply it after replacement.
                for (var prop in data.snippets) {
                  var type = prop.split(':')[0],
                      etid = prop.split(':')[1],
                      snippets = data.snippets[prop],
                      selector = 'table[entity_type='+type+'][etid='+etid+']',
                      currentPage = parseInt($(selector + ' + .snippet-pager-wrapper .currentPage').text());
                  $(selector).replaceWith(snippets);
                  Drupal.behaviors.gofastSearchSnippetsSlides.attach($(selector));
                  if($(selector + ' + .snippet-pager-wrapper .snippet-pager').css("display") == "none"){
                      $(selector + ' + .snippet-pager-wrapper .snippet-pager').css("display", "block");
                  }
                  if (currentPage > 1) {
                    // Simulate click on next page until we reach currentPage.
                    for (var i=1; i<currentPage; i++)
                      $(selector + ' + .snippet-pager-wrapper .nextPage').click();
                  }
                }
              },
              error: function(xhr, textStatus, error) {
                if (textStatus !== 'abort')
                  console.error(xhr, textStatus, error);
              },
              complete: function() {
                $(loaderSelector).remove();
                $('.search-result .tooltip').remove();
              }
            });
          }, 500);
        }
      }
    }
  }


  /**
   * Autocomplete Callback - Used for processing suggestions returned by Solr
   * Suggester & Spellchecker.
   */
  Gofast.search.processAC = function (_dta, term, rawTerm) {
    var suggestions = {}, output = {},
        response = typeof _dta === 'string' ? $.parseJSON(_dta) : _dta,
        spellcheck = response && response.spellcheck,
        suggesters = response && response.suggest,
        collations = spellcheck && spellcheck.collations;

    if (suggesters) {
      for (var name in suggesters){
        var suggest = suggesters[name][term];
        suggestions[name] = {};

        if (suggest && suggest.suggestions && suggest.suggestions.length) {
          for (var i=0; i<suggest.suggestions.length; i++) {
            var o = suggest.suggestions[i],
                stripped = Gofast.htmlDecode(o.term.replace(/<\/?b>/gi, '' ).trim());

            if (stripped in suggestions[name])
              continue;

            if (stripped.localeCompare(term, 'en', {usage:'search', sensitivity: 'accent'}) === 0)
              continue;

            // Should we remove too long suggesitons ? (having very long
            // suggestions is a symptom of the whole field being returned, for
            // example when matching a label that contains something like a
            // filename without any whitespace, but it's a good thing to get
            // an early but exact/full match when typing, the issue comes when
            // the string overflows from the input)
            // if (stripped.length > 80)
            //   continue;

            if (!o.term.match(/<\/?b>/gi)) {
              var pattern = term.replace(/\s/g, '[^A-Za-z0-9]+'),
                  regex = new RegExp(pattern, 'gi');

              o.term = o.term.replace(regex, function (match) {
                return '<b>' + match + '</b>';
              });
            }

            suggestions[name][stripped] = o.term;
          }
        }
      }
    }

    if (collations && collations.length) {
      suggestions.collations = {};
      if (Gofast.get('dev_mode')) {
        console.log('collation');
      }
      collations.filter(function(collation){
        return typeof collation === 'object';
      }).forEach(function(collation){
        //if (collation.hits > 0) {
          var stripped = Gofast.htmlDecode(collation.collationQuery.replace(/<\/?b>/g, '' ).trim()),
              parsed = stripped.replace(term, '<b>' + term + '</b>').trim();
          if (stripped === parsed) {
            parsed = '<b>' + parsed + '</b>';
          }
          suggestions.collations[stripped] = parsed;
        //}
      });
    }

    var order = {
      collations:0,     // collation queries when available are supposed to be the best fit
      infixSuggester:1, // from what I experienced yield more clever suggestions
      fuzzySuggester:2  // fuzzy yields more results, useful when other dict don't output anything
    }

    for (var source in order) {
      if (typeof suggestions[source] === 'object') {
        // Keep the 5 best matches (max) per dictionaries
        Gofast.apply(output, Gofast.sliceObj(suggestions[source], 0, 5));
      }
    }

    return Gofast.sliceObj(output, 0, 5);
  };

  /**
   * Alternative search autocomplete callback
   */
  Gofast.search.altAC = function (results) {
    return Gofast.sliceObj(results, 0, 5);
  };

  /**
   * Extend/Alter Gofast Collection object for search suggestions purpose.
   */
  Gofast.search.Collection = Gofast.clone(Gofast.Collection);

  Gofast.apply(Gofast.search.Collection.prototype, {
    getData: function () {
      if (this.size() > 1) {
        this.sort();
      }

      var arr = [],
          raw = this.getRawData();

      for (var name in raw) {
        arr.push(raw[name]);
      }

      this.data = Gofast.merge.apply(null, arr);
      this.filter();

      return this.data;
    },

    filter: function (matches) {
      var changes = false,
          matches = this.data, // matches || this.data,
          tmp;
      for (var match in matches) {
        tmp = match.match(/^(.+)\s\<[0-9]+\>$/);
        if (tmp && matches[tmp[1]]) {
          delete matches[tmp[1]];
          changes = true;
        }
      }
      if (changes) {
        this.data = matches;
      }
      return matches;
    },

    sort: function () {
      // Sort data sets by weigth.
      var req = this._req,
          raw = this.getRawData();

      Gofast.sortObjKeys(raw, function (a, b) {
        return req[a].weight || 0 - req[b].weight || 0;
      });
    }
//    sort: function (data) {
//      Gofast.sortObjKeys(data, function (a, b) {
//        var regex = /^.+\s\<[0-9]+\>$/,
//            am = a.match(regex),
//            bm = b.match(regex);
//
//        return am && bm && 0 || am && -1 || 1;
//      });
//    }

  });

  /**
   * Escape the given string for special Solr query characters.
   *  (such as ':', '(', ')', '*', '?', etc.)
   *
   * @param {type} query
   * @returns {@exp;query@call;replace}
   */
  Gofast.search.escapeQuery = function (query) {
    var pattern = new RegExp(/(\+|-|&&|\|\||!|\(|\)|\{|}|\[|]|\^|"|~|\*|\?|:|\\|\\\\)/g),
        replace = '\\\$1';

    return query.replace(pattern, replace);
  };

  /*
   * Store results for add to cart
   */
    Gofast.search.storeResultsForAddToCart = function (elmnt) {
      if (Gofast.search.nbs_nids_save == undefined){
        Gofast.search.nbs_nids_save = 0;
      }
        if ($('#addToCart').css('display') === 'none') {
            $('#addToCart').css("display", "");
        } else {
            var selected_for_basket = $("input[class='selected_for_basket']");
            var display = false;
            selected_for_basket.each(function () {
                if ($(this).is(":checked")) {
                    display = true;
                }
            });
            if (display) {
                $('#addToCart').css("display", "");
            } else {
                $('#addToCart').css("display", "none");
            }
        }
            var parent = elmnt.parentElement.parentElement;
            var children = parent.children[1];
            var element = children.children;
            var href = element[0].href;
            var nid = href.slice(href.lastIndexOf("/")+1);
        if (elmnt.checked) {
            if (Gofast.search.nbs_nids_save < 50) {
                Gofast.search.nbs_nids_save++;
                if (Gofast.search.nbs_nids_save === 1) {
                    Gofast.search.string_nids = nid + ",";
                } else {
                    Gofast.search.string_nids += nid + ",";
                }
            }
        } else {
            if (Gofast.search.string_nids.indexOf(nid) !== -1) {
                nid = nid + ",";
                Gofast.search.string_nids = Gofast.search.string_nids.replace(nid, "");
                Gofast.search.nbs_nids_save--;
            }
        }
    };

  /*
   * Toggle checked all item for add to cart
   */
    Gofast.search.toggleCheckedAllItemForAddToCart = function () {
        var all_selected = $(".all_selected_for_basket");
        if (all_selected.is(":checked")) {
            var selected_for_basket = $("input[class='selected_for_basket']");
            selected_for_basket.each(function () {
                if (!$(this).is(":checked")) {
                    $(this).prop( "checked", true );
                    var parent = $(this).parent().parent();
                    var children = parent.children();
                    var element = children[1].getElementsByClassName('gofast-title');
                    var href = element[0].href;
                    var nid = href.slice(href.lastIndexOf("/")+1);
                    if (Gofast.search.nbs_nids_save < 50) {
                    Gofast.search.nbs_nids_save++;
                        if (Gofast.search.nbs_nids_save === 1) {
                            Gofast.search.string_nids = nid + ",";
                        } else {
                            Gofast.search.string_nids += nid + ",";
                        }
                    }
                }
            });
            $('#addToCart').css("display", "");
        } else {
            var selected_for_basket = $("input[class='selected_for_basket']");
            selected_for_basket.each(function () {
                if ($(this).is(":checked")) {
                    $(this).prop( "checked", false );
                }
            });
            $('#addToCart').css("display", "none");
            Gofast.search.nbs_nids_save = 0;
            Gofast.search.string_nids = "";
        }
    };

  /**
   * When selected documents on search page, show burger menu
   */
  Gofast.search.toggleDisplayButtonForAddToCart = function (elmnt) {
      Gofast.search.storeResultsForAddToCart(elmnt);
  }

  /*
   * Get documents selected for add to cart
   */
    Gofast.search.getAlfrescoItemForAddToCart = function () {
        if (typeof Gofast.search.string_nids === "") {
            Gofast.toast("", "warning", Drupal.t("Please select at least one document", {}, {'context' : 'gofast:gofast_search'}));
        } else {
            var nids = Gofast.search.string_nids;
            jQuery.post("/modal/nojs/gofast_search/add_search_results_to_cart", {nids : nids})
            .done(function(commands){
                var jsonCommands = JSON.parse(commands);

                jsonCommands.forEach(function(k,v){
                    if(k.command == "modal_display"){
                        Gofast.removeLoading();
                        Gofast.modal(k.output, k.title);
                    }
                });
            });
        }
    };

  /*
   * submit add search results to cart
   */
    Gofast.search.submitAddSearchResultsToCart = function () {
        var nids = Gofast.search.nids;
        jQuery.post("/gofast_search/add_search_results_to_cart_submit", {nids : nids})
        .done(function(){
            modalContentClose();
            Gofast.toast("", "success", Drupal.t("Your results have been added to the cart", {}, {'context' : 'gofast:gofast_search'}));
        });
    };

  /*
   * Execute a saved search
   */
    Gofast.search.executeSavedSearch = function (url,search_params,strict_search) {
            Gofast.setCookie('search_params', search_params, 31536000);
            Gofast.setCookie('strict_search', strict_search, 31536000);
            Gofast.processAjax(decodeURIComponent(url));
    };

     Drupal.behaviors.gofast_search_switchs = {
        attach: function (context) {
             var toogleOption = function (item, value) {
                $(item).toggleClass('item-checked');
                return value === '1' ? '0' : '1';
              };

              $("#facetapi_search_filters [type='checkbox']:not(.item-processed)").addClass('item-processed').each(function( index ) {
                  if($( this ).attr("checked")){
                        $( this ).bootstrapSwitch('state', true);
                    }else{
                        $( this ).bootstrapSwitch('state', false);
                    }
                  $( this ).on("switchChange.bootstrapSwitch", function (event, state) {
                        var item = $(event.currentTarget);
                        itemId = item.attr('item');
                        formItem = $('input:hidden[name=' + itemId + ']');
                        event.preventDefault();
                        event.stopPropagation();
                        formItem.val(toogleOption(item, formItem.val()));
                        Gofast.setCookie('search_params', $('#search-form').serialize(), 31536000);
                        $('.search-form').trigger('submit');
                });
              });


             /* $("#facetapi_search_filters [type='checkbox']").on('change.bootstrapSwitch', function(e) {
                    alert(e.target.checked);
                });*/
        }
      };

  Drupal.behaviors.BlockFilterSearch = {
    attach : function (context, settings) {
       //$("#search_tab").tabs();

        $('.current-search-item-gofast-active').mCustomScrollbar({
            theme: 'dark-thin'
        });
    $('.block-facetapi',context).each(function(){
        var block_facetapi_id = document.getElementById($(this).attr('id'));
        if ($(block_facetapi_id,context).hasClass('expanded') && $(block_facetapi_id).find('i').hasClass("fa-chevron-down"))
        {
           $(block_facetapi_id,context).find('i').removeClass("fa-chevron-down").addClass("fa-chevron-right");
        }else if ($(block_facetapi_id).hasClass('expanded') && $(block_facetapi_id).find('i').hasClass("fa-chevron-right")){
           $(block_facetapi_id,context).find('i').removeClass("fa-chevron-right").addClass("fa-chevron-down");
        }
    });
    $('.block-title',context).click(function(){
        if ($(this).parent().hasClass('expanded'))
        {
          if($(this).parent().find('i').first().hasClass("fa-chevron-down")){
             $(this).parent().find('i').first().removeClass("fa-chevron-down").addClass("fa-chevron-right");
          }
        }else{
           if($(this).parent().find('i').first().hasClass("fa-chevron-right")){
            $(this).parent().find('i').first().removeClass("fa-chevron-right").addClass("fa-chevron-down");
          }
        }
    });
    }
  }

  Drupal.behaviors.DidYouMeanEncode = {
    attach : function (context, settings) {
      $('.spelling-suggestions a[href^="/search/solr/"]').once('encode', function(){
        // GOFAST-6737 - Double escape forward slashes
        var terms = $(this).attr('href').replace(/^\/search\/solr\//, '');
        var href = '/search/solr/' + terms.replaceAll('/', '%252F');
        $(this).attr('href', href);
      });
    }
  }



})(jQuery, Gofast, Drupal);
