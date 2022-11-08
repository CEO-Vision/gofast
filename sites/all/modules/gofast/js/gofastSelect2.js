/* https://preview.keenthemes.com/keen/demo1/features/forms/widgets/select2.html*/


(function ($, Gofast, Drupal) {
    
    'use strict';

    Drupal.behaviors.gofastSelect2Init = {
        attach: function(context, settings){
            
           $('select.gofastSelect2:not(.processed)').each(function(){
              $(this).addClass('processed');
              if(!$(this).hasClass('gofast_display_none')){
                 $(this).select2();
              }
           });
        }
    };

})(jQuery, Gofast, Drupal);

