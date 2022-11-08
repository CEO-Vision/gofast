/* https://preview.keenthemes.com/keen/demo1/features/forms/widgets/bootstrap-datetimepicker.html*/


(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.behaviors.gofastDatetimepickerInit = {
    attach: function(context, settings) {
      if(typeof $.fn.datepicker.dates == "undefined") {
        return;
      }
      const getDatepickerOrientation = (elmt) => {
        elmt = elmt.closest(":visible");
        let widgetPositioning = { horizontal: 'right', vertical: 'top' };
        if (elmt.offset().top < 400) widgetPositioning.vertical = "bottom";
        if ($(window).width() - elmt.offset().left < 400) {
          widgetPositioning.horizontal = "left";
        }
        return widgetPositioning;
      }

      // datepicker doesn't have same config neither same format as datetimepicker
      const datepicker_default_setting = {
        language: window.GofastLocale,
        locale : window.GofastLocale,
        autoclose: true,
        format: window.GofastConvertDrupalDatePattern("bootstrapDate"),
        todayHighlight: true,
        beforeShowDay: GofastWidgetsCallbacks.datePickerCallback,
      };
      // in case another datepicker erased the ln18 object
      setDatepickerL18n();
      $('.gofastDatepicker:not(.processed)').each(function(){
        $(this).addClass('processed');
        $(this).datepicker(datepicker_default_setting);
        // prevent a bug in datepicker when the datepicker is too close of the right border
        $(this).datepicker().on("show", function(e) {
          $(".datepicker:visible").css("z-index", 10000);
          e.target.style.display = "static";
          const distanceFromRight = $(window).width() - ($(e.target).offset().left + $(e.target).width());
          if (distanceFromRight < 150) {
            $(".datepicker:visible").css("left", (parseInt($(".datepicker:visible").css("left")) + 144) + "px");
          }
        });
      });

      const datetimepicker_default_setting = {
        locale: window.GofastLocale,
        showTodayButton: true,
        format: window.GofastConvertDrupalDatePattern("bootstrap", Drupal.settings.date_format_short, false)
      };
      $('.gofastDatetimepicker:not(.processed)').each(function(){
        datetimepicker_default_setting.widgetPositioning = getDatepickerOrientation($(this));
        $(this).addClass('processed');
        $(this).datetimepicker(datetimepicker_default_setting)
        $(this).on("show.datetimepicker update.datetimepicker", (e) => {
          GofastWidgetsCallbacks.dateTimePickerCallback();
        });
        // we want the user to be able to select the time right after the date, so we set the blur event manually
        $(this).on("blur", e => $(this).datetimepicker("hide"));
      });
    }
  };
  
})(jQuery, Gofast, Drupal);