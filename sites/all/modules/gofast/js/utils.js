
/**
 * @file Gofast Utils
 *  Provides development tools by extending prototype/JQuery objects.
 *
 *  This file is part of the Gofast main library and is loaded on every page.
 *  Do not insert code that has to be run on specific page.
 */

/**
 * define Gofast namespace
 */
var Gofast = (function($) {
  var
    charKeys = [],
    entityKeys = [],
    charToEntity = {},
    entityToChar = {},
    htmlEncodeReplaceFn = function(match, capture) {
      return charToEntity[capture];
    },
    htmlDecodeReplaceFn = function(match, capture) {
      return (capture in entityToChar) ? entityToChar[capture] : String.fromCharCode(parseInt(capture.substr(2), 10));
    },
    entitiesMap = {
      '&amp;'     :   '&',
      '&gt;'      :   '>',
      '&lt;'      :   '<',
      '&quot;'    :   '"',
      '&#39;'     :   "'"
    };

  for (var key in entitiesMap) {
    entityToChar[key] = entitiesMap[key];
    charToEntity[entitiesMap[key]] = key;
    charKeys.push(entitiesMap[key]);
    entityKeys.push(key);
  }

  var charToEntityRegex = new RegExp('(' + charKeys.join('|') + ')', 'g'),
      entityToCharRegex = new RegExp('(' + entityKeys.join('|') + '|&#[0-9]{1,5};' + ')', 'g');

  // Sort an array using the comparator, but if the comparator returns zero, use
  // the objects' original indices to tiebreak. This results in a stable sort.
  var stableSort = function (array, userComparator) {
      var len = array.length,
          indices = new Array(len),
          result = new Array(len),
          i;

      // Generate 0-n index map from original array
      for (i = 0; i < len; i++) {
          indices[i] = i;
      }

      // Sort indices array using a comparator which compares original values at
      // the two indices, and uses those indices as a tiebreaker.
      indices.sort(function(index1, index2) {
          return userComparator(array[index1], array[index2]) || (index1 - index2);
      });

      // Reconsitute a sorted array using the array that the indices have been
      // sorted into.
      for (i = 0; i < len; i++) {
          result[i] = array[indices[i]];
      }

      // Rebuild the original array.
      for (i = 0; i < len; i++) {
          array[i] = result[i];
      }

      return array;
  },

  // Default comparatyor to use when no comparator is specified for the sort
  // method. Javascript sort does LEXICAL comparison.
  lexicalCompare = function (lhs, rhs) {
      lhs = String(lhs);
      rhs = String(rhs);

      return (lhs < rhs) ? -1 : ((lhs > rhs) ? 1 : 0);
  };

  /**
   * Toaster interface, ease options mapping & fallback behavior.
   */
  var toaster = function (type) {
    return function (msg, title, options) {
      var message = $('<div/>')
              .append(msg)
              .addClass(options.messageClass),

          title = $('<div/>')
              .append(title)
              .addClass(options.titleClass),

          toaster = $('<div/>')
              .addClass(options.toastClass)
              .addClass(this.toasterConfig.defaults.iconClasses[type] || options.iconClass)
              .append(title)
              .append(message);
      var container;
      if ($('#'+options.containerId).length <= 0) {
        container = $('<div/>')
            .attr('id', options.containerId)
            .addClass(options.positionClass)
            .html(toaster)
            .click(function(){ $(this).remove(); delete container; })
            .css({display:'none'});
        container.appendTo($(options.target));
      } else {
        container = $('#'+options.containerId);
      }
      toaster.appendTo(container);

      if (options.timeOut > 0) {
        setTimeout(function () {
          container[options.hideMethod]({
            duration: options.hideDuration,
            easing: options.hideEasing,
            complete: function(){ container.remove(); delete container; }
          });
        }, options.timeOut);
      }




      return container[options.showMethod]({
        duration: options.showDuration,
        easing: options.showEasing
      });
    };
  };

  return {
    global: {
      protectedAttr: [{
        selector: '.protected',
        attrList: [
          'value' // default
        ]
      }]
    },
    enumerables : null,/*[
      'hasOwnProperty',
      'isPrototypeOf',
      'propertyIsEnumerable',
      'valueOf',
      'toLocaleString',
      'toString',
      'constructor'
    ]*/

    toasterConfig: {
      _get: function () {
        return {
          info: toaster('info'),
          success: toaster('success'),
          warning: toaster('warning'),
          error: toaster('error')
        };
      },
      defaults: {
        tapToDismiss: true,
        toastClass: 'toast',
        containerId: 'toast-container',
        debug: false,
        showMethod: 'fadeIn', // fadeIn, slideDown, and show are built into jQuery
        showDuration: 500,
        showEasing: 'swing', // swing and linear are built into jQuery
        onShown: undefined,
        hideMethod: 'fadeOut',
        hideDuration: 1000,
        hideEasing: 'swing',
        onHidden: undefined,
        extendedTimeOut: 1000,
        iconClasses: {
          error: 'toast-error',
          info: 'toast-info',
          success: 'toast-success',
          warning: 'toast-warning'
        },
        iconClass: 'toast-info',
        positionClass: 'toast-top-right',
        timeOut: 8000, // Set timeOut and extendedTimeOut to 0 to make it sticky
        titleClass: 'toast-title',
        messageClass: 'toast-message',
        target: 'body',
        closeHtml: '<button type="button">&times;</button>',
        newestOnTop: true,
        preventDuplicates: true,
        progressBar: false
      }
    },

    /**
     * AJAX responder commands.
     */
    Commands: {

      /**
       * Toasts a message using Gofast Toaster.
       */
      toast: function (ajax, response, status) {
        Gofast.toast(response.message, response.type, response.title);
      },

      /**
       * Triggers an event. Set document as context if undefined or null.
       */
      triggerEvent: function (ajax, response, status) {
        $(response.context || document).trigger(response.eventType, response.data);
      },

      /**
       * Executes a function callback.
       */
      callback: function (ajax, response, status) {
        Gofast.exec(response.callback, response.data);
      },

      /**
       * Executes a function callback.
       */
      openWindow: function (ajax, response, status) {
        if(response.newtab == true){
            window.open(response.url, '_blank');
        }else{
            window.open(response.url);
        }
      },

      /**
       * Process AjaxProcess function
       */
      processAjax: function (ajax, response, status) {
        Gofast.processAjax(response.href, false);
      },

      scrollToComment: function(ajax, response, status) {
        Gofast.scrollToComment(response.hrefComment);
      }
    },

    display_modal_form: function(form_url, title){
        $("body").append($("<a class='ctools-use-modal' href='" + form_url + "?title=" + title + "' id='modal_form_fake_link'></a>"));
        Drupal.attachBehaviors();
        $("#modal_form_fake_link").click();
        $("#modal_form_fake_link").remove();
    },

    scrollToComment: function(comment) {
      if ($(comment).length >= 1) {
        $('html, body').animate({
          scrollTop: $(comment).offset().top - 70
        }, 1000, 'swing', function () {
          window.location.hash = comment;
        });
        setTimeout(function(){
          $(comment).next().find(".panel-heading").addClass("comment-new");
          $(comment).next().find(".panel-footer").addClass("comment-new");
          setTimeout(function(){
            $(comment).next().find(".panel-heading").removeClass("comment-new");
            $(comment).next().find(".panel-footer").removeClass("comment-new");
          }, 2000);
        }, 900);
      }else{ //Waiting for comments to be fully loaded
        setTimeout(function(){Gofast.scrollToComment(comment);}, 200);
      }
    },

    getToaster: function () {
      return this.toasterConfig._get();
    },

    /**
     * Convert certain characters (&, <, >, ', and ") to their HTML character equivalents for literal display in web pages.
     * @param {String} value The string to encode.
     * @return {String} The encoded text.
     * @method
     */
    htmlEncode: function(value) {
      return (!value) ? value : String(value).replace(charToEntityRegex, htmlEncodeReplaceFn);
    },

    swapTag: function (str, tag) {
      // Remove tag from both ends of the string, then swap all remaining tags.
      var tagName = tag.replace(/<|>/g, ''),
          op = '<' + tagName + '>',
          cl = '<\/' + tagName + '>',
          pattern = '^' + op + '|' + cl + '$',
          regex = new RegExp(pattern, 'gi'),
          swapped = str.replace(regex, '');

      if (str === op + swapped + cl)
        return swapped;

      if (str === swapped || str === swapped + cl)
        swapped = cl + swapped;

      regex = new RegExp('<\/?' + tagName + '.*?>', 'g');
      return swapped.replace(/<\/?b.*?>/g, function (match) {
        return match === op ? cl : op;
      }).concat(cl);
    },

    /**
     * Convert certain characters (&, <, >, ', and ") from their HTML character equivalents.
     * @param {String} value The string to decode.
     * @return {String} The decoded text.
     * @method
     */
    htmlDecode: function(value) {
      return (!value) ? value : String(value).replace(entityToCharRegex, htmlDecodeReplaceFn);
    },

    /**
     * Helper to interrupt script run.
     */
    stopJS: function () {
      throw new Error('This is not an error. This is just to abort javascript for debugging.');
    },

    get: function (name) {
      var me = this,
          setting,
          accessor = me._accessors[name];
      if (typeof accessor === 'undefined')
        return undefined;
      for (var i = 0; i < accessor.length; i++) {
        if (setting && typeof setting[accessor[i]] !== 'undefined')
          setting = setting[accessor[i]];
        else
          setting = me._settings[accessor[i]];
      }
      return setting;
    },

    initSettings: function () {
      var me = this, modules;

      me._accessors = {};
      me._settings = Drupal.settings || {};
      modules = me._settings.gofast && me._settings.gofast.modules || {};

      for (var module in modules) {
        if (!me._settings[module]) continue;
        for (var setting in me._settings[module])
          me._accessors[setting] = me._accessors[setting] || [module, setting];
      }
    },

    access: function(name, scope) {
      var scope = scope || window,
          accessor = name.split('.'),
          obj = scope;
      for (var i=0; i<accessor.length; i++) {
        obj = obj[accessor[i]];
      }
      return obj;
    },

    /**
     * Copies all the properties of config to the specified object. There are 2
     * levels of defaulting supported (Ext like).
     *   Ext.apply(obj, { a: 1 }, { a: 2 });   //obj.a === 1
     *   Ext.apply(obj, {  }, { a: 2 });       //obj.a === 2
     *
     * Note that if recursive merging and cloning without referencing the
     * original objects or arrays is needed, use Gofast.merge instead.
     *
     * @param {Object} object The receiver of the properties.
     * @param {Object} config The primary source of the properties.
     * @param {Object} [defaults] An object that will also be applied for default values.
     * @return {Object} returns `object`.
     */
    apply: function(object, config, defaults) {
      var enumerables = Gofast.enumerables;

      if (defaults) {
        Gofast.apply(object, defaults);
      }

      if (object && config && typeof config === 'object') {
        var i, j, k;

        for (i in config) {
          object[i] = config[i];
        }

        if (enumerables) {
          for (j = enumerables.length; j--; ) {
            k = enumerables[j];
            if (config.hasOwnProperty(k)) {
              object[k] = config[k];
            }
          }
        }
      }

      return object;
    },

    /**
    * Clone simple variables including array, {}-like objects, DOM nodes and Date
    * without keeping the old reference. A reference for the object itself is
    * returned if it's not a direct decendant of Object.
    *
    * @param {Object} item The variable to clone
    * @return {Object} clone
    */
    clone: function (item) {
      if (item === null || item === undefined) {
          return item;
      }

      // DOM nodes
      if (item.nodeType && item.cloneNode) {
          return item.cloneNode(true);
      }

      var type = Object.prototype.toString.call(item),
          i, j, k, clone, key, enumerables;

      // Date
      if (type === '[object Date]') {
          return new Date(item.getTime());
      }

      // Array
      if (type === '[object Array]') {
          i = item.length;

          clone = [];

          while (i--) {
              clone[i] = Gofast.clone(item[i]);
          }
      }
      // Object
      else if (type === '[object Object]' && item.constructor === Object) {
          clone = {};
          enumerables = Gofast.enumerables;

          for (key in item) {
              clone[key] = Gofast.clone(item[key]);
          }

          if (enumerables) {
              for (j = enumerables.length; j--;) {
                  k = enumerables[j];
                  if (item.hasOwnProperty(k)) {
                      clone[k] = item[k];
                  }
              }
          }
      }

      return clone || item;
    },

    /**
     * Merges any number of objects recursively without referencing them or their
     * children (Ext like).
     *
     * @param {Object} destination The object into which all subsequent objects are merged.
     * @param {Object...} object Any number of objects to merge into the destination.
     * @return {Object} merged The destination object with all passed objects merged in.
     */
    merge: function (destination) {
      var i = 1,
        ln = arguments.length,
        mergeFn = Gofast.merge,
        cloneFn = Gofast.clone,
        object, key, value, sourceKey;

      for (; i < ln; i++) {
        object = arguments[i];

        for (key in object) {
          value = object[key];
          if (value && value.constructor === Object) {
              sourceKey = destination[key];
              if (sourceKey && sourceKey.constructor === Object) {
                  mergeFn(sourceKey, value);
              }
              else {
                  destination[key] = cloneFn(value);
              }
          }
          else {
              destination[key] = value;
          }
        }
      }

      return destination;
    },

    /**
     * Returns a shallow copy of a portion of an object into a new object.
     * Useful for extracting a slice of object properties. Referenced properties
     * (i.e. properties of the original object that references some) are not
     * preserved.
     *
     * @see Array.prototype.slice()
     */
    sliceObj: function (obj/*, begin, end*/) {
      var sliced = {},
          args = [].slice.call(arguments, 1),
          arrLike = [].slice.apply(Object.keys(obj), args);

      arrLike.forEach(function(item, i){
        sliced[item] = obj[item];
      });

      return sliced;
    },

    /**
    * Sorts the elements of an Array in a stable manner (equivalently keyed
    * values do not move relative to each other). By default, this method sorts
    * the elements alphabetically and ascending.
    * **Note:** This method modifies the passed array, in the same manner as the
    * native javascript Array.sort.
    *
    * @param {Array} array The array to sort.
    * @param {Function} [sortFn] The comparison function.
    * @param {Mixed} sortFn.a The first item to compare.
    * @param {Mixed} sortFn.b The second item to compare.
    * @param {Number} sortFn.return `-1` if a < b, `1` if a > b, otherwise `0`.
    * @return {Array} The sorted array.
    */
    sort: function(array, sortFn) {
      return stableSort(array, sortFn || lexicalCompare);
    },

    sortObjKeys: function (obj, sortFn) {
      var arrLike = [].slice.apply(Object.keys(obj)),
          clone = Gofast.clone(obj), i;
      for (var prop in obj) {
        if (obj.hasOwnProperty(prop))
          delete obj[prop];
      }
      Gofast.sort(arrLike, sortFn);
      for (i=0; i<arrLike.length; i++) {
        obj[arrLike[i]] = clone[arrLike[i]];
      }
      return obj;
    },

    getWindowWidth: function() {
      var w = window,
          e = document.documentElement,
          g = document.getElementsByTagName('body')[0];
      return w.innerWidth || e.clientWidth || g.clientWidth;
    },

    getWindowHeight: function() {
      var w = window,
          e = document.documentElement,
          g = document.getElementsByTagName('body')[0];
      return w.innerHeight || e.clientHeight || g.clientHeight;
    },

    setCookie: function(name, value, expiration) {
       /**@todo encodeURIComponent() ? */
      if (typeof expiration === undefined) {
        expiration = 0;
      }
      var date = new Date();
      date.setTime(date.getTime() + (expiration * 1000));
      var expires = '; expires=' + date.toGMTString();
      document.cookie = name + '=' + value + expires + '; path=/; secure=true;';
    },

    getCookie: function getCookie(c_name) {
      var i, x, y, ARRcookies = document.cookie.split(";");
      for (i = 0; i < ARRcookies.length; i++) {
        x = ARRcookies[i].substr(0, ARRcookies[i].indexOf("="));
        y = ARRcookies[i].substr(ARRcookies[i].indexOf("=") + 1);
        x = x.replace(/^\s+|\s+$/g, "");
        if (x == c_name) {
          return unescape(y); /**@todo use decodeURIComponent() */
        }
      }
      return false;
    },

    preventNotifyToggle: function preventNotifyToggle(){
       var current_state_prevent_notify = Gofast.getCookie('prevent_notify');
       var new_state_prevent_notify;
       if(current_state_prevent_notify == "true"){
           new_state_prevent_notify = "false";
       }else{
           new_state_prevent_notify = "true";
       }
       Gofast.setCookie('prevent_notify', new_state_prevent_notify, 31536000);
       if(new_state_prevent_notify == "true"){
           Gofast.toast(Drupal.t('Notifications temporarily desactivated', {}, {'context' : 'gofast'}) );
       }else{
           Gofast.toast(Drupal.t('Notifications temporarily activated', {}, {'context' : 'gofast'}) );
       }
   },

   preventNotifySetDefaultValue: function preventNotifySetDefaultValue(default_value){
        Gofast.setCookie('prevent_notify', default_value, 31536000);
   },
    StrictSearchSetDefaultValue: function StrictSearchSetDefaultValue(default_value){
        Gofast.setCookie('strict_search', default_value, 31536000);
   },

    StrictSearchToggle: function StrictSearchToggle(){
       var current_state_strict_search = Gofast.getCookie('strict_search');
       var new_state_strict_search;
       if(current_state_strict_search === "true" || current_state_strict_search === false){
           new_state_strict_search = "false";
       }else{
           new_state_strict_search = "true";
       }
       Gofast.setCookie('strict_search', new_state_strict_search, 31536000);
       if(new_state_strict_search == "true"){
           Gofast.toast(Drupal.t('Strict search mode activated', {}, {'context' : 'gofast'}) );
       }else{
           Gofast.toast(Drupal.t('Strict search mode desactivated', {}, {'context' : 'gofast'}) );
       }
        $('.search-form').trigger('submit');
   },

    deleteCookie: function(name, expire, path) {
      var ck_expire = 'Thu, 01 Jan 1970 00:00:01 GMT';
      var ck_path= '/';
      if(undefined != expire && expire.length > 0){
        ck_expire = expire;
      }
      if(undefined != path && path.length > 0){
        ck_path = path;
      }
      document.cookie = name + '=; expires='+ck_expire+'; path='+ck_path;
    },

    resize: function(el) {
      // Resize element according to its width/height ratio
      var width = el.width(), height = el.height();

      while (height / width > 1) {
        height -= 1;
        width += 1;
      }
      while (width / height > 3) {
        width -= 1;
        height += 1;
      }

      width = Math.round(width);
      height = Math.round(height);
      // CTools Modal fix
      var content = el.find('.ctools-modal-content'); // contient header (height = 20px)
      if (content.length) {
        var contentInner = content.find('#modal-content'), wH = getWindowHeight();
        // Set the modal shape
        contentInner.css({width: width, height: height, 'max-height': wH - 100, 'max-width': 950});
        content.css({width: contentInner.outerWidth(), height: contentInner.outerHeight() + 20});
        el.css({width: content.outerWidth() + 25, height: content.outerHeight() + 25, 'max-height': wH - 50});
        // Reset some to remove outer scroll
        contentInner.css({height: ''});
        content.css({height: '', 'max-height': wH - 40});
        el.css({height: '', 'max-height': wH - 20});

        var avatarForm = el.find('#gofast-image-form');
        if (avatarForm.length) {
          // Recenter after a while (let the browser load and resize img before)
          setTimeout(function() {
            el.center();
          }, 1000);
        }
      }
      el.css('overflow', 'auto');

      // Since busy browser migth have been wrong about the content dimensions on
      // the first run : wait a moment, refresh element, test its dimensions and
      // redo if it looks weird.
      setTimeout(function() {
        el = $(el);
        if (el.width() < el.height()) {
          Gofast.resize(el);
          el.center();
        }
      }, 200);
    },

    /**
     * Determines if the passed element is overflowing its bounds, either
     * vertically or horizontally. Will temporarily modify the "overflow"
     * style to detect this if necessary.
     *
     * @param {Object} el
     *  The DOM element to check.
     *
     * @returns {Boolean|Object}
     *  An object describing overflow if the passed-in element, boolean false otherwise.
     */
    checkOverflow: function (el) {
      el = el instanceof Element && el || el instanceof jQuery && el.get(0);
      if (!el) return;

      var curOverflow = el.style.overflow,
          overflowX,
          overflowY;

      if (!curOverflow || curOverflow === 'visible')
        el.style.overflow = 'hidden';

      overflowX = el.scrollWidth - el.clientWidth,
      overflowY = el.scrollHeight - el.clientHeight;

      el.style.overflow = curOverflow;

      return (overflowX > 0 || overflowY > 0) && {x:overflowX,y:overflowY};
    },

    addLoading: function () {
      var backdrop = $('#backdrop');
      backdrop.stop();

      // Get the docHeight and (ugly hack) add 50 pixels to make sure we don't
      // have a *visible* border below our div. (modal.js)
      var docHeight = $(document).height() + 50,
          docWidth = $(document).width(),
          css = {
            height: docHeight + 'px',
            width: docWidth + 'px'
          };

      $('#backdrop').css(css).fadeIn();
    },

    /**
     * Validates a jQuery selector
     *
     * @returns {Boolean}
     */
    selectorValidate: function (selector) {
      try {
        var $element = $(selector);
      }
      catch(error) {
        return false;
      }
      return true;
    },

    //Used to simulate slow processes for dev purpose (NOT ASYNC !!)
    sleep: function (milliseconds) {
      var start = new Date().getTime();
      for (var i = 0; i < 1e14; i++) {
        if ((new Date().getTime() - start) > milliseconds){
          break;
        }
      }
    },

    /**
     * Matches a given context.
     *
     * @returns {Boolean}
     */
    contextMatch: function () {
      var context = Gofast.apply({}, Gofast.get('context')),
          ctxt = arguments;

      if (!ctxt.length) {
        return false;
      }

      // This to prevent boolean fallback in the loop below.
      context[true] = 1;
      context[false] = 1;

      for (var match=1, o=0, i=0, ctx; i<ctxt.length; i++) {
        Gofast.is_scalar(ctxt[i]) && (ctx = {}) && (ctx[ctxt[i]] = 1) || (ctx = ctxt[i]);
        for (var key in ctx)
          o = o || context[key] == ctx[key]; // not strict intended.
        match = match && o;
      }
      if(Gofast.get('dev_mode')) {
        //console.log(ctxt, match);
      }
      return match;
    },

    /**
     * Checks if the given variable is a js scalar (atomic) object or not.
     */
    is_scalar: function (obj){
      return (/string|number|boolean/).test(typeof obj);
    },

    removeLoading: function() {
      $('#backdrop, #gofast-throbber').stop();
      $('#backdrop, #gofast-throbber').fadeOut();
    },

    modal: function (html, title, options) {
      if (typeof html === 'undefined')
        return console.error('No HTML to display in Gofast Modal');

      options = options || {};
      title = title || 'GoFast';

      Drupal.CTools.Modal.show(options);
      Drupal.CTools.Modal.modal_display.apply(undefined, [options, {title: title, output: html}]);
    },

    closeModal: function () {
      Drupal.CTools.Modal.dismiss();
    },

    hideContextualMessageNextTime: function(mykey,value){
        if(value == true){
             var show = "false"
        }else{
             var show = "true"
        }
        var user_id = Gofast.get("user").uid;
        $.get("/gofast/contextual_messages/set/"+user_id, {key: mykey, value: show});

    },

    modalMsg: function (message, title, options) {
      if (typeof message === 'undefined')
        return;

      if (typeof title === 'undefined')
        title = 'GoFast';

      message = '<div class="gofast-modal-message"><p>' + message + '</p></div>';

      options = Gofast.apply(options || {}, {
        modalSize: {
          width: 500
        }
      });

      Gofast.modal.apply(undefined, [message, title, options]);
    },

    sendXHR: function (method, path, params, async, headers, callback) {
      var xhr = new XMLHttpRequest();
      xhr.open(method, path, async);

      Object.prototype.toString.call(callback) === '[object Function]' ?
              xhr.onreadystatechange = callback(xhr) : xhr.onreadystatechange = handleStateChange;

      if (method === 'POST')
        xhr.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');

      if (Object.prototype.toString.call(headers) === '[object Array]') {
        for (var i = 0, len = headers.length; i < len; i++) {
          xhr.setRequestHeader(headers[i].name, headers[i].value);
        }
      }
      xhr.withCredentials = true;

      xhr.send(params);

      function handleStateChange() {
        if (xhr.readyState === 4) {
          // The request is complete
          if (xhr.status >= 200 && xhr.status < 300) {
            // Succeeded, we can check response with xhr.responseText or (for
            // requests with XML replies) xhr.responseXML.
          }
        }
      }
    },

    exec: function (funcName, args, context) {
      var context = context || Gofast;
      if (typeof funcName === 'function')
        return funcName.apply(context, args);
      else if (typeof funcName === 'string')
        return Gofast.execByName.apply(this, [funcName.replace(/^Gofast\./, ''), context].concat(args));
    },

    execByName: function (funcName, context) {
      var args = [].slice.call(arguments, 2),
          namespaces = funcName.split('.'),
          func = namespaces.pop();
      for (var i = 0; i < namespaces.length; i++) {
        context = context[namespaces[i]];
      }
      return context[func].apply(context, args);
    },

    goto: function (href, redirect, ajax) {
      href = Gofast.get('basePath') + href.replace(/^\//, '');
      redirect = redirect || false;
      window.YAHOO = window.YAHOO || false;
      ajax = ajax && YAHOO;

      if (redirect) {
        // HTTP redirect behavior.
        window.location.replace(href);
      }
      else {
        // Simulate click on a link, keep the originating page in session history.
        if (ajax) {
          /** @todo: ajax **/
          YAHOO.util.History.navigate('q', href);
        }
        else {
          window.location.href = href;
        }
      }
    },

    copyToClipboard: function (text) {
      var $temp = $("<input>");
      $("body").append($temp);
      $temp.val(text).select();
      document.execCommand("copy");
      $temp.remove();
      Gofast.toast(Drupal.t('Link copied to clipboard !', {}, {'context':'gofast:conference'}));
    },

    getAllUrlParams: function(url) {

      // get query string from url (optional) or window
      var queryString = url ? url.split('?')[1] : window.location.search.slice(1);

      // we'll store the parameters here
      var obj = {};

      // if query string exists
      if (queryString) {

        // stuff after # is not part of query string, so get rid of it
        queryString = queryString.split('#')[0];

        // split our query string into its component parts
        var arr = queryString.split('&');

        for (var i = 0; i < arr.length; i++) {
          // separate the keys and the values
          var a = arr[i].split('=');

          // set parameter name and value (use 'true' if empty)
          var paramName = a[0];
          var paramValue = typeof (a[1]) === 'undefined' ? true : a[1];

          // (optional) keep case consistent
          paramName = paramName.toLowerCase();
          if (typeof paramValue === 'string') paramValue = paramValue;

          // if the paramName ends with square brackets, e.g. colors[] or colors[2]
          if (paramName.match(/\[(\d+)?\]$/)) {

            // create key if it doesn't exist
            var key = paramName.replace(/\[(\d+)?\]/, '');
            if (!obj[key]) obj[key] = [];

            // if it's an indexed array e.g. colors[2]
            if (paramName.match(/\[\d+\]$/)) {
              // get the index value and add the entry at the appropriate position
              var index = /\[(\d+)\]/.exec(paramName)[1];
              obj[key][index] = paramValue;
            } else {
              // otherwise add the value to the end of the array
              obj[key].push(paramValue);
            }
          } else {
            // we're dealing with a string
            if (!obj[paramName]) {
              // if it doesn't exist, create property
              obj[paramName] = paramValue;
            } else if (obj[paramName] && typeof obj[paramName] === 'string'){
              // if property does exist and it's a string, convert it to an array
              obj[paramName] = [obj[paramName]];
              obj[paramName].push(paramValue);
            } else {
              // otherwise add the property
              obj[paramName].push(paramValue);
            }
          }
        }
      }

      return obj;
    },


    /**
     * Toaster wrapper function
     *
     * @param {String} msg
     *  The text to show.
     *
     * @param {String} type
     *  Any of the following : info, success, warning, error.
     *
     * @param {String} title [optional]
     *  A title for the toast notification.
     *
     * @param {Object} options [optional]
     *  Override default properties.
     */
    toast: function (msg, type, title, options) {
      type = type || 'info';
      options = Gofast.apply({}, options || {}, Gofast.toasterConfig.defaults);
      Gofast.getToaster()[type].apply(this, [msg, title, options]);
    },

    removeBookmarkDromDashboard : function(nid){
        jQuery('.gofast_flag_title > a[href="/node/' + nid + '"]').parent().parent().parent().remove();
    },

    selectPartOfInput : function(input, startPos, endPos) {
        input.focus();
        if (typeof input.selectionStart != "undefined") {
            input.selectionStart = startPos;
            input.selectionEnd = endPos;
        } else if (document.selection && document.selection.createRange) {
            // IE branch
            input.select();
            var range = document.selection.createRange();
            range.collapse(true);
            range.moveEnd("character", endPos);
            range.moveStart("character", startPos);
            range.select();
        }
    },

    //If we are on the dashboard and there is a tasks block, reload it
    refreshDashboardTasksBlock : function(){
        if($(".panel-dashboard-workflows").length === 1){
            var iframe = $(".panel-dashboard-workflows").find("iframe")[0];
            Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
               iframe.src = iframe.src;
            });
        }
    },

    processDashboardDropdowns: function(){
        $(".dropdown-placeholder").not(".dropdown-processed").addClass("dropdown-processed").click(function(){
          if(! $(this).hasClass("dropdown-processing")){
            var nid = this.id.substring(21);
	    if($(this).parents('#gofast-node-actions-microblogging').length > 0){
		var microblogging = true;
	    }
            var div = $(this).parent();
            var container = div.parent();

            //Animation
            $(this).addClass("dropdown-processing");
            $("#dropdownactive-placeholder-" + nid).show();
	    if(microblogging === true){
		jQuery.post(location.origin+"/activity/ajax/microblogging/menu/"+nid, function(data){
		    var newdiv = div.replaceWith(data);
		    Drupal.attachBehaviors();
		    container.find(".gofast-node-actions").addClass("open");

		    //Align menu
		    console.log(Gofast.last_menu_align);
		    if(Gofast.last_menu_align === "up"){
			$(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
			$(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }else{
			$(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
			$(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		    }
		});
	    }else{
		//Load menu
		jQuery.post(location.origin+"/activity/ajax/menu/"+nid, function(data){
		  var newdiv = div.replaceWith(data);
		  Drupal.attachBehaviors();
		  container.find(".gofast-node-actions").addClass("open");

		  //Align menu
		  console.log(Gofast.last_menu_align);
		  if(Gofast.last_menu_align === "up"){
		    $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("top", "100%").css("bottom", "inherit");
		    $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }else{
		    $(".gofast-dropdown-menu:not(.dropdown-menu-right)").css("bottom", "100%").css("top", "inherit");
		    $(".gofast-dropdown-menu.dropdown-menu-right").css("top", "inherit").css("bottom", "0px");
		  }
		});
	    }
          }
        });
    },
    isTablet: function () {
      var userAgent = navigator.userAgent.toLowerCase();
      var isTablet = /(ipad|tablet|(android(?!.*mobile))|(windows(?!.*phone)(.*touch))|kindle|playbook|silk|(puffin(?!.*(IP|AP|WP))))/.test(userAgent);
      return isTablet;
    },
    isMobile: function () {
      let check = false;
      (function (a) { if (/(android|bb\d+|meego).+mobile|avantgo|bada\/|blackberry|blazer|compal|elaine|fennec|hiptop|iemobile|ip(hone|od)|iris|kindle|lge |maemo|midp|mmp|mobile.+firefox|netfront|opera m(ob|in)i|palm( os)?|phone|p(ixi|re)\/|plucker|pocket|psp|series(4|6)0|symbian|treo|up\.(browser|link)|vodafone|wap|windows ce|xda|xiino/i.test(a) || /1207|6310|6590|3gso|4thp|50[1-6]i|770s|802s|a wa|abac|ac(er|oo|s\-)|ai(ko|rn)|al(av|ca|co)|amoi|an(ex|ny|yw)|aptu|ar(ch|go)|as(te|us)|attw|au(di|\-m|r |s )|avan|be(ck|ll|nq)|bi(lb|rd)|bl(ac|az)|br(e|v)w|bumb|bw\-(n|u)|c55\/|capi|ccwa|cdm\-|cell|chtm|cldc|cmd\-|co(mp|nd)|craw|da(it|ll|ng)|dbte|dc\-s|devi|dica|dmob|do(c|p)o|ds(12|\-d)|el(49|ai)|em(l2|ul)|er(ic|k0)|esl8|ez([4-7]0|os|wa|ze)|fetc|fly(\-|_)|g1 u|g560|gene|gf\-5|g\-mo|go(\.w|od)|gr(ad|un)|haie|hcit|hd\-(m|p|t)|hei\-|hi(pt|ta)|hp( i|ip)|hs\-c|ht(c(\-| |_|a|g|p|s|t)|tp)|hu(aw|tc)|i\-(20|go|ma)|i230|iac( |\-|\/)|ibro|idea|ig01|ikom|im1k|inno|ipaq|iris|ja(t|v)a|jbro|jemu|jigs|kddi|keji|kgt( |\/)|klon|kpt |kwc\-|kyo(c|k)|le(no|xi)|lg( g|\/(k|l|u)|50|54|\-[a-w])|libw|lynx|m1\-w|m3ga|m50\/|ma(te|ui|xo)|mc(01|21|ca)|m\-cr|me(rc|ri)|mi(o8|oa|ts)|mmef|mo(01|02|bi|de|do|t(\-| |o|v)|zz)|mt(50|p1|v )|mwbp|mywa|n10[0-2]|n20[2-3]|n30(0|2)|n50(0|2|5)|n7(0(0|1)|10)|ne((c|m)\-|on|tf|wf|wg|wt)|nok(6|i)|nzph|o2im|op(ti|wv)|oran|owg1|p800|pan(a|d|t)|pdxg|pg(13|\-([1-8]|c))|phil|pire|pl(ay|uc)|pn\-2|po(ck|rt|se)|prox|psio|pt\-g|qa\-a|qc(07|12|21|32|60|\-[2-7]|i\-)|qtek|r380|r600|raks|rim9|ro(ve|zo)|s55\/|sa(ge|ma|mm|ms|ny|va)|sc(01|h\-|oo|p\-)|sdk\/|se(c(\-|0|1)|47|mc|nd|ri)|sgh\-|shar|sie(\-|m)|sk\-0|sl(45|id)|sm(al|ar|b3|it|t5)|so(ft|ny)|sp(01|h\-|v\-|v )|sy(01|mb)|t2(18|50)|t6(00|10|18)|ta(gt|lk)|tcl\-|tdg\-|tel(i|m)|tim\-|t\-mo|to(pl|sh)|ts(70|m\-|m3|m5)|tx\-9|up(\.b|g1|si)|utst|v400|v750|veri|vi(rg|te)|vk(40|5[0-3]|\-v)|vm40|voda|vulc|vx(52|53|60|61|70|80|81|83|85|98)|w3c(\-| )|webc|whit|wi(g |nc|nw)|wmlb|wonu|x700|yas\-|your|zeto|zte\-/i.test(a.substr(0, 4))) check = true; })(navigator.userAgent || navigator.vendor || window.opera);
      return check;
    },
    isInternal: function () {
      var nodeData = Gofast.get('node');
      //Check if the document is internal
      if (typeof nodeData !== "undefined" && nodeData.type == "alfresco_item") {
        //Gofast.isInternal(nodeData.id);
        var response = $.ajax({
          url: location.origin + "/gofast/is_internal",
          type: 'POST',
          data: { nid: nodeData.id },
          dataType: 'json',
          async: false
        });
        return response.responseJSON.value;
      }else{
        return false;
      }
    },
    isConfidential: function () {
      var nodeData = Gofast.get('node');
      //Check if the document is confidential
      if (typeof nodeData !== "undefined" && nodeData.type == "alfresco_item") {
        //Gofast.isInternal(nodeData.id);
        var response = $.ajax({
          url: location.origin + "/gofast/is_confidential",
          type: 'POST',
          data: { nid: nodeData.id },
          dataType: 'json',
          async: false
        });
        return response.responseJSON.value;
      } else {
        return false;
      }
    },
    gofast_saml_sp_drupal: function (event, cookie_domain) {
      $.cookie('gofast_version_login_selected', // cookie name
       jQuery('#edit-simplified-login').val(), // version button value
        {
        expires: 90,           // Expires in 90 days
        path: '/',          // The value of the path
        domain: cookie_domain, // The value of the domain
        secure: true          // If set to true the secure attribute of the cookie
        // will be set and the cookie transmission will
        // require a secure protocol (defaults to false).
      });

      if (event.target.tagName != "A") { location.href = jQuery("#edit-saml-sp-drupal-login-links > a").attr("href"); event.preventDefault()};
    },
    HidePrintButton: function () {
      if($("#pdf_frame").contents().find("#print.toolbarButton").hasClass("hideprint_processed") || $("#pdf_frame").contents().find("#print.toolbarButton").length == 0){
          return;
      }
      $("#pdf_frame").contents().find("#print.toolbarButton").addClass("hideprint_processed");
      var is_internal = Gofast.isInternal();
      var is_confidential = Gofast.isConfidential();
      if ($('#pdf_frame').length > 0 && $("#pdf_frame").contents().find("#print.toolbarButton").length > 0 && ( is_internal == true ||  is_confidential == true)) {
        $("#pdf_frame").contents().find("#print.toolbarButton").addClass('gofastHideButton');
      } else if ($('#pdf_frame').length > 0 && $("#pdf_frame").contents().find("#print.gofastHideButton").length > 0 && is_internal == false && is_confidential == false) {
        $("#pdf_frame").contents().find("#print.toolbarButton").removeClass('gofastHideButton');
      };
    }
  }; // Gofast._
})(jQuery);

Gofast.Collection = function (name, db) {
  this.name = name;
  this.data;

  if (typeof db !== 'undefined') {
    this._db = db;
  }

  this._req = {};
  this._data = {};
  this._collector = Gofast;
};

Gofast.apply(Gofast.Collection.prototype, {
  size: function() {
    return Object.keys(this._data).length;
  },

  isComplete : function () {
    return this.size() === Object.keys(this._req).length;
  },

  getRawData: function () {
    return this._data;
  },

  getData: function () {
    var arr = [],
        raw = this.getRawData();
    for (var name in raw) {
      arr.push(raw[name]);
    }
    this.data = Gofast.merge.apply(null, arr);
    return this.data;
  },

  clean: function (name) {
//    console.log('clean collection');
    if (typeof name !== 'undefined') {
      delete this._data[name];
      delete this._req[name];
    }
    else {
      this._data = {};
      this._req = {};
    }
    delete this.data;
  },

  register: function (req, name) {
    name = name || Object.keys(this.req).length;
    this._req[name] = req;
  },

  getRequests: function () {
    return this._req;
  },

  collect: function (data, name) {
    this._data[name] = data;
  },

  process: function () {
    // Use to process all matches once collected.
  },

  getDb: function () {
    return this._db;
  }

});

/**
 * Init operations
 */
Drupal.behaviors._gofastInit = {
  attach: function (context, settings) {
    // Settings takes a while before being set so we trigger init from here.
    Gofast.initSettings();

    // Registers our Drupal ajax commands.
    for (var command in Gofast.Commands)
      Drupal.ajax.prototype.commands[command] = Gofast.Commands[command];
  }
};

(function($, Gofast) {
//  'use strict';

  /* Add ECMA262-5 method binding if not supported natively */
  if (!('bind' in Function.prototype)) {
    Function.prototype.bind = function(owner) {
      var that = this;
      if (arguments.length <= 1) {
        return function() {
          return that.apply(owner, arguments);
        };
      } else {
        var args = Array.prototype.slice.call(arguments, 1);
        return function() {
          return that.apply(owner, arguments.length === 0 ? args : args.concat(Array.prototype.slice.call(arguments)));
        };
      }
    };
  }

  /* Add ECMA262-5 Array methods if not supported natively */

  if (!('indexOf' in Array.prototype)) {
    Array.prototype.indexOf = function(find, i /*opt*/) {
      if (i === undefined)
        i = 0;
      if (i < 0)
        i += this.length;
      if (i < 0)
        i = 0;
      for (var n = this.length; i < n; i++)
        if (i in this && this[i] === find)
          return i;
      return -1;
    };
    Object.defineProperty(Array.prototype, 'indexOf', { enumerable: false });
  }

  if (!('lastIndexOf' in Array.prototype)) {
    Array.prototype.lastIndexOf = function(find, i /*opt*/) {
      if (i === undefined)
        i = this.length - 1;
      if (i < 0)
        i += this.length;
      if (i > this.length - 1)
        i = this.length - 1;
      for (i++; i-- > 0; ) /* i++ because from-argument is sadly inclusive */
        if (i in this && this[i] === find)
          return i;
      return -1;
    };
    Object.defineProperty(Array.prototype, 'lastIndexOf', { enumerable: false });
  }

  if (!('forEach' in Array.prototype)) {
    Array.prototype.forEach = function(action, that /*opt*/) {
      for (var i = 0, n = this.length; i < n; i++)
        if (i in this)
          action.call(that, this[i], i, this);
    };
    Object.defineProperty(Array.prototype, 'forEach', { enumerable: false });
  }

  if (!('map' in Array.prototype)) {
    Array.prototype.map = function(mapper, that /*opt*/) {
      var other = new Array(this.length);
      for (var i = 0, n = this.length; i < n; i++)
        if (i in this)
          other[i] = mapper.call(that, this[i], i, this);
      return other;
    };
    Object.defineProperty(Array.prototype, 'map', { enumerable: false });
  }

  if (!('filter' in Array.prototype)) {
    Array.prototype.filter = function(filter, that /*opt*/) {
      var other = [], v;
      for (var i = 0, n = this.length; i < n; i++)
        if (i in this && filter.call(that, v = this[i], i, this))
          other.push(v);
      return other;
    };
    Object.defineProperty(Array.prototype, 'filter', { enumerable: false });
  }

  if (!('every' in Array.prototype)) {
    Array.prototype.every = function(tester, that /*opt*/) {
      for (var i = 0, n = this.length; i < n; i++)
        if (i in this && !tester.call(that, this[i], i, this))
          return false;
      return true;
    };
    Object.defineProperty(Array.prototype, 'every', { enumerable: false });
  }

  if (!('some' in Array.prototype)) {
    Array.prototype.some = function(tester, that /*opt*/) {
      for (var i = 0, n = this.length; i < n; i++)
        if (i in this && tester.call(that, this[i], i, this))
          return true;
      return false;
    };
    Object.defineProperty(Array.prototype, 'some', { enumerable: false });
  }

  if (!('last' in Array.prototype)) {
    Array.prototype.last = function() {
      return this && this.length && this[this.length - 1] || undefined;
    };
    Object.defineProperty(Array.prototype, 'last', { enumerable: false });
  }

  /* Extends String.prototype */

  /* Add ECMA262-5 string trim if not supported natively */
  if (!('trim' in String.prototype)) {
    String.prototype.trim = function() {
      return this.replace(/^\s+/, '').replace(/\s+$/, '');
    };
    Object.defineProperty(String.prototype, 'trim', { enumerable: false });
  }

  // Create 'capitalize' method
  if (!('capitalize' in String.prototype)) {
    String.prototype.capitalize = function() {
      return this.charAt && this.charAt(0).toUpperCase() + this.slice(1);
    };
    Object.defineProperty(String.prototype, 'capitalize', { enumerable: false });
  }

  // Create 'trimChars' method
  if (!('trimChars' in String.prototype)) {
    /**
     * Removes a particular set of characters from the start and end of a string
     * @param {String} chars the charactersto remove form the start and end of the string
     * @returns {String}
     */
    String.prototype.trimChars = function (chars) {
      let reg = new RegExp('^['+chars+']+|['+chars+']+$', "g")
      return this.replace(reg, '');
    }
    Object.defineProperty(String.prototype, 'trimChars', { enumerable: false });
  }

  // Create a string ruler (in px)...
  String.prototype.visualLength = function() {
    var ruler = document.getElementById("str-ruler");
    if (!ruler) {
      console.log('Cannot find any ruler in DOM.');
      return;
    }
    ruler.innerHTML = this;
    return ruler.offsetWidth;
  };
  Object.defineProperty(String.prototype, 'visualLength', { enumerable: false });

  // ... so we can properly trim string
  String.prototype.trimToPx = function(length) {
    var tmp = this;
    var trimmed = this;
    if (tmp.visualLength() > length) {
      trimmed += "...";
      while (trimmed.visualLength() > length) {
        tmp = tmp.substring(0, tmp.length - 1);
        trimmed = tmp + "...";
      }
    }
    return trimmed;
  };
  Object.defineProperty(String.prototype, 'trimToPx', { enumerable: false });


  /* Extends Object prototype */

  if (!('size' in Object.prototype)) {
    /** @todo support IE8 ? */
    Object.defineProperty(Object.prototype, 'size', {
      writable: true,
      configurable: true,
      enumerable: false,
      value: function(){
        var size = 0, key;
        for (key in this)
          if (this.hasOwnProperty(key))
            size++;
        return size;
      }
    });
  }

  /**
   * Center matched element on the screen (relative to the viewport : position
   * fixed) - or in another element (relative to that element : position
   * absolute).
   * @param relativeElement If set, matched element is centered inside this
   * element.
   */
  $.fn.center = function() {
    var winW = Gofast.getWindowWidth(), winH = Gofast.getWindowHeight();
    // @TODO : centrer relativement à un élément passé en paramètre.
    // - position absolute / fixed en fonction de la présence d'argument
    // - ignorer arg si = $(window) ou $(document)
    // - prendre en compte yScroll = w.pageYOffset || e.scrollTop || g.scrollTop
    // top : yScroll + (winH - $(this).outerHeight()) / 2
    return this.css({
      position: 'fixed',
      top: Math.max(0, (Math.round(winH - $(this).outerHeight()) / 2.3)) + 'px',
      left: Math.max(0, (Math.round(winW - $(this).outerWidth()) / 2)) + 'px'
    });
  };

  /**
   * Returns the text of an element, ignoring all child elements
   * @returns string
   */
  $.fn.getText = function() {
    return this
            .clone()        // clone the element
            .children()     // select all the children
            .remove()       // remove all the children
            .end()          // again go back to selected element
            .text();        // and get text
  };

  $.fn.filterByText = function(text) {
    // Need to escape selector metacharacters (cf. https://api.jquery.com/category/selectors/ )
    text = text.replace(/([!"#$%&'()*+,.\/:;<=>?@\[\]\^`{|}~])/g, '\\$1');
    return this.filter(':contains(' + text + ')').find('*').filter(function() {
      return $(this).getText().indexOf(text) !== -1;
    });
  };

  $.fn.exists = function() {
    return this.length > 0;
  };

  // [name] is the name of the event "click", "mouseover", ..
  // same as you'd pass it to bind()
  // [fn] is the handler function
  $.fn.bindFirst = function(obj, name, fn) {
      // bind as you normally would
      // don't want to miss out on any jQuery magic
      $(obj).bind(name, fn);

      // Thanks to a comment by @Martin, adding support for
      // namespaced events too.
      var handlers = $._data(obj, 'events')[name.split('.')[0]];
      // take out the handler we just inserted from the end
      var handler = handlers.pop();
      // move it at the beginning
      handlers.splice(0, 0, handler);
  };

//  var ev = new $.Event('remove');
//  $.each(['remove', 'empty', 'detach'], function(i, name){
//    var orig = $.fn[name];
//    $.fn[name] = function() {
//      $(this).trigger(ev);
//      return orig.apply(this, arguments);
//    };
//  });

})(jQuery, Gofast);


//Polyfill Object for IE
(function(){function r(e,n,t){function o(i,f){if(!n[i]){if(!e[i]){var c="function"==typeof require&&require;if(!f&&c)return c(i,!0);if(u)return u(i,!0);var a=new Error("Cannot find module '"+i+"'");throw a.code="MODULE_NOT_FOUND",a}var p=n[i]={exports:{}};e[i][0].call(p.exports,function(r){var n=e[i][1][r];return o(n||r)},p,p.exports,r,e,n,t)}return n[i].exports}for(var u="function"==typeof require&&require,i=0;i<t.length;i++)o(t[i]);return o}return r})()({1:[function(require,module,exports){
module.exports = (function () {
	"use strict";

	var ownKeys      = require ('reflect.ownkeys')
	var reduce       = Function.bind.call(Function.call, Array.prototype.reduce);
	var isEnumerable = Function.bind.call(Function.call, Object.prototype.propertyIsEnumerable);
	var concat       = Function.bind.call(Function.call, Array.prototype.concat);

	if (!Object.values) {
		 Object.values = function values(O) {
			return reduce(ownKeys(O), function (v, k) { return concat(v, typeof k === 'string' && isEnumerable(O, k) ? [O[k]] : []) }, []) } }

	if (!Object.entries) {
		 Object.entries = function entries(O) {
			return reduce(ownKeys(O), function (e, k) { return concat(e, typeof k === 'string' && isEnumerable(O, k) ? [[k, O[k]]] : []) }, []) } }

	return Object

}) ();

},{"reflect.ownkeys":2}],2:[function(require,module,exports){
if (typeof Reflect === 'object' && typeof Reflect.ownKeys === 'function') {
  module.exports = Reflect.ownKeys;
} else if (typeof Object.getOwnPropertySymbols === 'function') {
  module.exports = function Reflect_ownKeys(o) {
    return (
      Object.getOwnPropertyNames(o).concat(Object.getOwnPropertySymbols(o))
    );
  }
} else {
  module.exports = Object.getOwnPropertyNames;
}

},{}]},{},[1])
