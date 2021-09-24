(function($, Gofast, Drupal) {  
  $(document).ready(function(){
    Drupal.behaviors.webformAjaxification = {
      attach: function(context, settings){
        //On click on a tab, select it and unselect others. Also display the corresponding divs
        $(".webform-tab").off('click').on('click', function(e){
          $(".webform-tab").removeClass("active");
          $(e.currentTarget).addClass("active");
          $(".webform-content").hide();
          $("#" + e.currentTarget.id.replace('tab', 'content')).show();
        }).addClass('bound');
        
        //On click on edit tab, load form builder (the 1st time)
        $("#webform-edit-tab").once("webform-ajax-processed").each(function(){
          var link = $('#webform-edit-tab', context);
          new Drupal.ajax("#webform-edit-tab", link,{
            url: "/gofast/webform/get_builder/" + Gofast.get('node').id,
            settings: {noLoader: true},
            event: 'mouseup tap',
          });
        });
        
        //On click on your submissions tab, display user's submissions
        $("#webform-submissions-tab").once("webform-ajax-processed").each(function(){
          var link = $('#webform-submissions-tab', context);
          new Drupal.ajax("#webform-submissions-tab", link,{
            url: "/gofast/webform/get_submissions/" + Gofast.get('node').id,
            settings: {noLoader: true},
            event: 'mouseup tap',
          });
        });
        
        //On click on results tab, display user's submissions
        $("#webform-results-tab").once("webform-ajax-processed").each(function(){
          var link = $('#webform-results-tab', context);
          new Drupal.ajax("#webform-results-tab", link,{
            url: "/gofast/webform/get_results/" + Gofast.get('node').id,
            settings: {noLoader: true},
            event: 'mouseup tap',
          });
        });
        
        //On form save, reload view tab if we go back to it
        $("#form-builder-webform-save-form > div > div > #edit-save").click(function(){
          $("#webform-view-tab").addClass("webform-reload");
          $('.content.well').html("<div class='loader-blog'></div>");
        });
        $('#webform-view-tab.webform-reload').click(function(e){
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
                var max = $("#form-builder-wrapper").height()+start-$('ul.form-builder-fields').height();;
                
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