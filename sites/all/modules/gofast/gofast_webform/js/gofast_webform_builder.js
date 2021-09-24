(function($, Gofast, Drupal) {  
  
  //Unbind click and tap events as we don't need to reload te builder anymore
  $('#webform-edit-tab').off('tap').off('mouseup');
  
  //Dismiss modal because we use ctools modal to ajaxify this call
  Drupal.CTools.Modal.dismiss();
  
  //Format the builder
  $('#form-builder > h3').hide();
  $('#form-builder-fields > div > div > h3').hide();
  $('.form-builder-fields > li').css('width', '95%');
  
  //Format the configuration tab
  $('label.option').css("font-weight", 'normal');
  
  //Ajaxify the configuration form submit
  $('#webform-configure-form > div > .form-actions > .btn-success').addClass('ctools-use-modal');
  
  //Prepend info message
  $("#form-builder-webform-save-form > div > .form-actions").prepend("<p><i class='fa fa-info' style='color: #269abc;'></i> " + Drupal.t("No changes will be saved until you click the 'Save' button.", {}, {context: 'gofast:gofast_webform'}) + "</p>");
  
  Drupal.behaviors.webform_publish_button = {
      attach: function(){
          //Clear publish/unpublish button
          $(".gofast-webform-publish-unpublish").remove();
          
          //Attach a button to publish or unpublish the form
        if($("#edit-status > div:first() > label > input").is(":checked")){
            $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-sm btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Unpublish", {}, {context: 'gofast:gofast_webform'}) + "</button>").click(function(e){
                e.preventDefault();
                //Publish the form
                $("#edit-status > div:last() > label > input").prop('checked', true);
                $("#webform-configure-form > div > .form-actions > button").click();
            });
        }else{
            $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-sm btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Publish", {}, {context: 'gofast:gofast_webform'}) + "</button>").click(function(e){
                e.preventDefault();
                //Publish the form
                $("#edit-status > div:first() > label > input").prop('checked', true);
                $("#webform-configure-form > div > .form-actions > button").click();
            });
        }
      }
  };
  
  //Attach Drupal behaviors to process the rendered builder
  Drupal.attachBehaviors();
  
})(jQuery, Gofast, Drupal);