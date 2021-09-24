(function($, Gofast, Drupal) {  
  
  //Hide cancel link as it's not ajaxified
  $('#webform-submission-delete-form > div > .form-actions > a').hide();
  
  //Attach Drupal behaviors
  Drupal.attachBehaviors();
  
})(jQuery, Gofast, Drupal);