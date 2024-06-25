(function($, Gofast, Drupal) {
  Drupal.behaviors.webformAjaxification = {
    attach: function(context, settings){
      //GOFAST-7430 - handle builder element remove from JS instead of submitting the form
      $("#form-builder-field-remove button").off("mousedown");
      $("#form-builder-field-remove button").off("click");
      $("#form-builder-field-remove").ajaxForm();
      $("#webform-configure-form .form-actions button:not(.processed)").on("click", () => Gofast.addLoading());
      $("#webform-configure-form .form-actions button").addClass("processed");
      $("#webform-configure-form:not(.processed)").ajaxForm(() => {
        Gofast.removeLoading();
        Gofast.toast(Drupal.t("Webform successfully submitted", {}, {context: 'gofast:gofast_webform'}), "success");
      });

      // if the webform is loaded without page load, then the ajax settings mechanism relying on page load has not been triggered
      // which means we have to set it ourselves in order for the upload buttons inside the webform to work
      Drupal.settings.ajax = Drupal.settings.ajax || {};
      $("form.webform-client-form .webform-component-file button:not(.ajax-processed)").each(function() {
        const buttonId = $(this).attr("id");
        const buttonName = $(this).attr("name");
        const shortButtonName =  buttonName.replace("submitted_", "").replace("_upload_button", "");
        const buttonValue = $(this).attr("value");
        const fileInputWrapper = $(this).closest(".webform-component-file").parent();
        const fileInputWrapperId = fileInputWrapper.attr("id");
        const formBuildId = $(this).closest("form").find("input[name='form_build_id']").val();
        const ajax_event = {};
        ajax_event.event =  "mousedown";
        ajax_event.selector = "#" + buttonId;
        ajax_event.keypress = true;
        ajax_event.prevent = "click";
        ajax_event.submit = { _triggering_element_name: buttonName, "_triggering_element_value": buttonValue };
        ajax_event.url =  "/file/ajax/submitted/" + shortButtonName + "/" + formBuildId;
        ajax_event.wrapper = fileInputWrapperId;
        Drupal.settings.ajax[buttonId] = ajax_event;
        Drupal.behaviors.AJAX.attach();
      });
      $("#webform-configure-form").addClass("processed");
      //On click on edit tab, load form builder (the 1st time)
      $("#manage-tab").once("webform-ajax-processed").each(function(){
        var link = $('#manage-tab', context);
        new Drupal.ajax("#manage-tab", link, {
          url: "/gofast/webform/get_builder/" + Gofast.get('node').id,
          settings: {noLoader: true},
          event: 'mouseup tap'
        });
      });

      //On click on your submissions tab, display user's submissions
      $("#submission-tab").once("webform-ajax-processed").each(function(){
        var link = $('#submission-tab', context);
        new Drupal.ajax("#submission-tab", link,{
          url: "/gofast/webform/get_submissions/" + Gofast.get('node').id,
          settings: {noLoader: true},
          event: 'mouseup tap'
        });
      });

      //On click on results tab, display user's submissions
      $("#results-tab").once("webform-ajax-processed").each(function(){
        var link = $('#results-tab', context);
        new Drupal.ajax("#results-tab", link,{
          url: "/gofast/webform/get_results/" + Gofast.get('node').id,
          settings: {noLoader: true},
          event: 'mouseup tap'
        });
      });

      //On form save, reload view tab if we go back to it
      $("#form-builder-webform-save-form #edit-save").click(function(){
        $("#fillout-tab").addClass("webform-reload");
        // $('.content.well').html("<div class='loader-blog'></div>");
      });
      $('#fillout-tab.webform-reload').once("webform-reload", function(){
        $(this).on("click", (e) => {
          e.preventDefault();
          e.stopPropagation();
          Gofast.processAjax("/node/" + Gofast.get("node").id);
        })
      });

      //Prevent form builder block to scroll
      Drupal.behaviors.formBuilderBlockScroll = {};

      //Implements our custom scroll behavior
      $(window).scroll(function(){
          if($('#form-builder-wrapper').length > 0){
              var start = $('#form-builder-wrapper').offset().top;
              var current = $(window).scrollTop()+50;
              var max = $("#form-builder-wrapper").height()+start-$('ul.form-builder-fields').height();

              //Check if we need to trigger scroll or not
              if(current < max && current > start){
                  var margin = (current-start);
                  //Scroll
                  $('ul.form-builder-fields').css("margin-top", margin);
                  $('ul.form-builder-fields').css("position", "absolute");
              }else if(current < start){
                  $('ul.form-builder-fields').css("margin-top", 0);
              }
          }
      });
    }
  };

  //Call t functions here to have them translated
  Drupal.t("No changes will be saved until you click the 'Save' button.", {}, {context: 'gofast:gofast_webform'});
  Drupal.t("Unpublish", {}, {context: 'gofast:gofast_webform'});
  Drupal.t("Publish", {}, {context: 'gofast:gofast_webform'});
  Drupal.t('Submission values', {}, {context: 'gofast:gofast_webform'});

})(jQuery, Gofast, Drupal);
