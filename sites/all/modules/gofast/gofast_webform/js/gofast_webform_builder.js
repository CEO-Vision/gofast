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
  $("#form-builder-webform-save-form").ajaxForm((response, status) => {
    if (status != "success") {
      return;
    }
    response = JSON.parse(response);
    // ajax base is not automatically initialized with ajaxForm, so we take responsibility for running the ajax commands
    Drupal.ajax.prototype.handleAjaxCommands(response);
  });
  
  //Prepend info message
  if (!$("#form-builder-webform-save-form .fa-info").length) {
    $("<p><i class='fa fa-info' style='color: #269abc;'></i> " + Drupal.t("No changes will be saved until you click the 'Save' button.", {}, {context: 'gofast:gofast_webform'}) + "</p>").insertBefore($("#form-builder-webform-save-form > div > .form-actions"));
  }
  Drupal.behaviors.webform_publish_button = {
      attach: function(){
        //Clear publish/unpublish button
        $(".gofast-webform-publish-unpublish").remove();
        $("#form-builder-webform-save-form > div > .form-actions").css({display: "flex", gap: "1rem"});
        //Attach a button to publish or unpublish the form
        if($("#edit-status > div:first() > label > input").is(":checked")){
          $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Unpublish", {}, {context: 'gofast:gofast_webform'}) + "</button>");
          $(".gofast-webform-publish-unpublish").click(function(e){
            e.preventDefault();
            //Publish the form
              $('.gofast-webform-publish-unpublish').remove();
              $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Unpublish", {}, {context: 'gofast:gofast_webform'}) + "</button>");
              $("#edit-status > div:last() > label > input").prop('checked', true);
              $("#webform-configure-form > div > .form-actions > button").click();
            });
        }else{
            $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Publish", {}, {context: 'gofast:gofast_webform'}) + "</button>");
            $(".gofast-webform-publish-unpublish").click(function(e){
              e.preventDefault();
              //Publish the form
                $('.gofast-webform-publish-unpublish').remove();
                $("#form-builder-webform-save-form > div > .form-actions").append("<button class='btn btn-info icon-before gofast-webform-publish-unpublish'><span class='fa fa-share' aria-hidden='true'></span> " + Drupal.t("Publish", {}, {context: 'gofast:gofast_webform'}) + "</button>");
                $("#edit-status > div:first() > label > input").prop('checked', true);
                $("#webform-configure-form > div > .form-actions > button").click();
            });
        }
        if ($(".gofast-webform-delete").length == 0) {
            $("#form-builder-webform-save-form > div > .form-actions").append("<a class='ctools-use-modal' href='/modal/nojs/node/" + Gofast.get("node").id + "/manage'><button class='btn btn-danger icon-before gofast-webform-delete'><span class='fa fa-trash' aria-hidden='true'></span>&nbsp;" + Drupal.t("Delete", {}, {context: 'gofast'}) + "</button></a>");
        }
      }
  };
  //Attach Drupal behaviors to process the rendered builder
  Drupal.attachBehaviors();
  
})(jQuery, Gofast, Drupal);