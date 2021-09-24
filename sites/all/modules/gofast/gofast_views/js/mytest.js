// jQuery for Drupal 7 [BEGIN]
(function ($, Gofast, Drupal) {
  
  Drupal.behaviors.mytest = {
    attach: function (context, settings) {
      context = $(context);
      
      $('textarea.no-ckeditor:not(".nocked-processed")').addClass('nocked-processed').each(function() {
         if (typeof(Drupal.settings.ckeditor.autostart) != 'undefined') Drupal.settings.ckeditor.autostart=false;
      });
      
    }
  }
 
}(jQuery, Gofast, Drupal));