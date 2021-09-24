(function ($, Gofast, Drupal) {
  $(document).ready(function(target){
    Gofast.conference = Gofast.conference || {};
    Gofast.conference.autocomplete_process = function(t){
      $('.form-item-stop-validation-propagation').find('input').prop('checked', true);
      Drupal.conference_date_save = $("#conference_date").clone();
      Drupal.conference_end_date_save = $("#conference_end_date").clone();
      $("#submit_conference").mousedown();
    }
    
    Drupal.behaviors.gofastConferenceValidation = {
      attach: function(context, settings){
        if($('.form-item-stop-validation-propagation').find('input').prop('checked') == true){
          $("#conference_date").replaceWith(Drupal.conference_date_save);
          $("#conference_end_date").replaceWith(Drupal.conference_end_date_save);
          $('.form-item-stop-validation-propagation').find('input').prop('checked', false);
          $('html,body').stop();
          Drupal.attachBehaviors();
        }
      }
    }    
  });
})(jQuery, Gofast, Drupal);     
