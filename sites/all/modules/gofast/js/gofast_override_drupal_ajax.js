(function ($, Gofast, Drupal) {
  $(document).ready(function () {
    var user = Gofast.get('user');

    /**
     * Modify form values prior to form submission.
     */
    Drupal.ajax.prototype.beforeSubmit = function (form_values, element, options) {
      if (element.attr('id') === 'conference-node-form') {
        for (var i = 0; i < form_values.length; i++) {
          if (form_values[i].name.indexOf('edit-list-participants-hidden-values') >= 0) {
            var values = [];
            var labelizeMetaData = [];
            $('span.labelize-metadata').each(function (key, value) {
              var data = {};
              var element = $(value);
              if (element.attr('data-type')) {
                data.id = element.attr('data-id');
                data.type = element.attr('data-type');
                data.name = element.attr('data-name');
                data.address = element.attr('data-address');
                labelizeMetaData.push(data);
              } else {
                labelizeMetaData.push(element.attr('data-value'));
              }

            });
            for (var property in labelizeMetaData) {
              if (labelizeMetaData.hasOwnProperty(property)) {
                values.push(labelizeMetaData[property]);
              }
            }
            form_values[i].value = JSON.stringify(values);
          }

          if (form_values[i].name.indexOf('edit-list-participants-hidden-values') >= 0) {

          }
        }
      }
    };
    /**
     * Override Drupal's AJAX prototype beforeSend function so it can append the
     * throbber inside the pager links.
     */
    Drupal.ajax.prototype.beforeSend = function (xmlhttprequest, options) {

      // For forms without file inputs, the jQuery Form plugin serializes the form
      // values, and then calls jQuery's $.ajax() function, which invokes this
      // handler. In this circumstance, options.extraData is never used. For forms
      // with file inputs, the jQuery Form plugin uses the browser's normal form
      // submission mechanism, but captures the response in a hidden IFRAME. In this
      // circumstance, it calls this handler first, and then appends hidden fields
      // to the form to submit the values in options.extraData. There is no simple
      // way to know which submission mechanism will be used, so we add to extraData
      // regardless, and allow it to be ignored in the former case.

      // /!\ IMPORTANT : Fix the bug "convert null to object" in the admin/structuree/view
      Gofast.xhrPool = Gofast.xhrPool || {};
      Gofast.xhrPool['drupal_ajax_' + Object.keys(Gofast.xhrPool).length] = xmlhttprequest;
      var disableAjaxLoadingBackground = (typeof options.data === 'string' && (options.data.indexOf('view_name') >= 0 || options.data.indexOf('autorefresh=true') >= 0)) || options.url.indexOf('gofast/poll') >= 0 || decodeURIComponent(options.url).indexOf('gofast/node-info/') >= 0  || options.url.indexOf('vote') >= 0 || options.url.indexOf('gofast/poll') >= 0 ;
      if (!disableAjaxLoadingBackground) {
        Gofast.addLoading();
      }

      if (this.form) {
        options.extraData = options.extraData || {};

        // Let the server know when the IFRAME submission mechanism is used. The
        // server can use this information to wrap the JSON response in a TEXTAREA,
        // as per http://jquery.malsup.com/form/#file-upload.
        options.extraData.ajax_iframe_upload = '1';

        // The triggering element is about to be disabled (see below), but if it
        // contains a value (e.g., a checkbox, textfield, select, etc.), ensure that
        // value is included in the submission. As per above, submissions that use
        // $.ajax() are already serialized prior to the element being disabled, so
        // this is only needed for IFRAME submissions.
        var v = $.fieldValue(this.element);
        if (v !== null) {
          options.extraData[this.element.name] = v;
        }
      }

      var $element = $(this.element);

      // Disable the element that received the change to prevent user interface
      // interaction while the Ajax request is in progress. ajax.ajaxing prevents
      // the element from triggering a new request, but does not prevent the user
      // from changing its value.
      $element.addClass('progress-disabled').attr('disabled', true);

      // Insert progressbar or throbber.
      if (this.progress.type == 'bar') {
        var progressBar = new Drupal.progressBar('ajax-progress-' + this.element.id, eval(this.progress.update_callback), this.progress.method, eval(this.progress.error_callback));
        if (this.progress.message) {
          progressBar.setProgress(-1, this.progress.message);
        }
        if (this.progress.url) {
          progressBar.startMonitoring(this.progress.url, this.progress.interval || 500);
        }
        this.progress.element = $(progressBar.element).addClass('ajax-progress ajax-progress-bar');
        this.progress.object = progressBar;
        $element.closest('.file-widget,.form-item').after(this.progress.element);
      } else if (this.progress.type == 'throbber') {
        this.progress.element = $('<div class="ajax-progress ajax-progress-throbber"><i class="glyphicon glyphicon-refresh glyphicon-spin"></i></div>');
        if (this.progress.message) {
          $('.throbber', this.progress.element).after('<div class="message">' + this.progress.message + '</div>');
        }

        // If element is an input type, append after.
        if ($element.is('input')) {
          $element.after(this.progress.element);
        } else if ($element.is('select')) {
          var $inputGroup = $element.closest('.form-item').find('.input-group-addon, .input-group-btn');
          if (!$inputGroup.length) {
            $element.wrap('<div class="input-group">');
            $inputGroup = $('<span class="input-group-addon">');
            $element.after($inputGroup);
          }
          $inputGroup.append(this.progress.element);
        }
        // Otherwise append the throbber inside the element.
        else {
          $element.append(this.progress.element);
        }
      }

    };

    /**
     * Handler for the form redirection completion.
     */
    Drupal.ajax.prototype.success = function (response, status) { 
      // some versions of FF seem to append "=" to the hash, breaking the navigation
      if (location.hash.length && location.hash.slice(-1) == "=") {
        location.hash = location.hash.slice(0, -1);
      }

      var disableAjaxLoadingBackground = true;
      $.each(response, function(key, command_js){
        if( typeof(command_js) == "Object" && command_js.command === "triggerEvent" && command_js.eventType === "pollEnd"){ // do not remove Loading throbber after a poll request
          disableAjaxLoadingBackground = false;
        }
      }); 
      if (disableAjaxLoadingBackground === true) {
        Gofast.removeLoading();
     }
      
      // Remove the progress element.
      if (this.progress.element) {
        $(this.progress.element).remove();
      }
      if (this.progress.object) {
        this.progress.object.stopMonitoring();
      }
      $(this.element).removeClass('progress-disabled').removeAttr('disabled');

      Drupal.freezeHeight();

      // Fixed the constructor of undefined error in admin config interface
      if (user.uid != 1) {
        // /!\ IMPORTANT : Reset ajaxViews (There were 2 view_dom_id gofast_activity_feed which caused the bug) fof fixing filter bug on the activity feed 
        if (typeof Drupal.settings.views !== 'undefined') {
          Drupal.settings.views.ajaxViews = {};
        }
      }

      for (var i in response) {        
        if (response.hasOwnProperty(i) && response[i] != null && response[i]['command'] && this.commands[response[i]['command']]) {
          this.commands[response[i]['command']](this, response[i], status);
        }
      }
      
      // Reattach behaviors, if they were detached in beforeSerialize(). The
      // attachBehaviors() called on the new content from processing the response
      // commands is not sufficient, because behaviors from the entire form need
      // to be reattached.
      if (this.form) {
        var settings = this.settings || Drupal.settings;
        Drupal.attachBehaviors(this.form, settings);
      }

      Drupal.unfreezeHeight();

      // Remove any response-specific settings so they don't get used on the next
      // call by mistake.
      this.settings = null;


    };

    /**
     * Handler for the form redirection error.
     */
    Drupal.ajax.prototype.error = function (xmlhttprequest, uri, customMessage) {
      if(xmlhttprequest.error === "aborted"){ //Aborted is not an error but a cancel of the AJAX request
        return;
      }
      
      if(xmlhttprequest.status === 403){ //403 is not an error but a deconnexion. we go to baseurl.
        location.href = location.origin;
        return;
      }
      
      //Add error button at top right
      var user = Gofast.get("user");     
      //$.post(location.origin + "/gofast/js-error", {useragent : navigator.userAgent, request : location.href, url : uri, message : JSON.stringify(xmlhttprequest), line : customMessage});
      Gofast.removeLoading();
     // alert(Drupal.ajaxError(xmlhttprequest, uri, customMessage));
      Gofast.toast(Drupal.ajaxError(xmlhttprequest, uri, customMessage), 'error');
      // Remove the progress element.
      if (this.progress.element) {
        $(this.progress.element).remove();
      }
      if (this.progress.object) {
        this.progress.object.stopMonitoring();
      }
      // Undo hide.
      $(this.wrapper).show();
      // Re-enable the element.
      $(this.element).removeClass('progress-disabled').removeAttr('disabled');
      // Reattach behaviors, if they were detached in beforeSerialize().
      if (this.form) {
        var settings = this.settings || Drupal.settings;
        Drupal.attachBehaviors(this.form, settings);
      }
    };
  });
})(jQuery, Gofast, Drupal);