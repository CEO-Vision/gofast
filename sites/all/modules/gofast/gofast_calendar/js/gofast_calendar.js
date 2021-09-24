/* global Gofast, Drupal */

(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.behaviors.gofastCalendar = {
    attach: function(context, settings){ 
      $('.date-views-pager').find('.icon-after').on('click', function () {
        //remove tooltip
        $('.tooltip').each(function(key, elt){
          $(elt).remove();
        });
      });

      $('.date-views-pager').find('.icon-before').on('click', function () {
        //remove tooltip
        $('.tooltip').each(function(key, elt){
          $(elt).remove();
        });
      });
    }
  };
    
    Drupal.behaviors.gofastCalendar_popover = {
        attach: function(context, settings){           
            if (typeof $('.popup_calendar:not(.calendar_popover-processed)',context).popover == "undefined" || Gofast._settings.isMobile) {
                return;
            } 
          
            $('.popup_calendar:not(.calendar_popover-processed)',context).addClass('calendar_popover-processed').popover({               
                content:function() {
                    var my_id = $(this).attr("id");
                    if (my_id !== ""){
                        return $('#window_popup_calendar_'+my_id).html();
                    } 
                },
                html:true,
                placement:'bottom',
                trigger:'hover'
            });
        }
    };
  
  
    
})(jQuery, Gofast, Drupal);     
