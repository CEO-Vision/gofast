(function($, Gofast, Drupal) {
  $(document).ready(function(){
    Drupal.behaviors.webformAjaxification = {
      attach: function(context, settings){
        //GOFAST-7430 - handle builder element remove from JS instead of submitting the form
        $("#form-builder-field-remove button").off("mousedown");
        $("#form-builder-field-remove button").off("click");
        $("#form-builder-field-remove").ajaxForm();
        $("#webform-configure-form .form-actions button").on("click", () => Gofast.addLoading());
        $("#webform-configure-form").ajaxForm(() => {
          Gofast.removeLoading();
          Gofast.toast(Drupal.t("Webform successfully submitted", {}, {context: 'gofast:gofast_webform'}), "success");
        });

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
        $('#fillout-tab.webform-reload').click(function(e){
          e.preventDefault();
          e.stopPropagation();
          Gofast.processAjax("/node/" + Gofast.get("node").id);
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
  });

  //Call t functions here to have them translated
  Drupal.t("No changes will be saved until you click the 'Save' button.", {}, {context: 'gofast:gofast_webform'});
  Drupal.t("Unpublish", {}, {context: 'gofast:gofast_webform'});
  Drupal.t("Publish", {}, {context: 'gofast:gofast_webform'});
  Drupal.t('Submission values', {}, {context: 'gofast:gofast_webform'});

})(jQuery, Gofast, Drupal);
