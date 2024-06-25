/* https://preview.keenthemes.com/keen/demo1/features/forms/widgets/bootstrap-datetimepicker.html*/


(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.behaviors.gofastDatetimepickerInit = {
    attach: function(context, settings) {
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
        clearBtn: true,
        beforeShowDay: GofastWidgetsCallbacks.datePickerCallback,
      };
      // in case another datepicker erased the ln18 object
      setDatepickerL18n();
      $('.gofastDatepicker:not(.processed)').each(function(){
        $(this).addClass('processed');
        $(this).datepicker(datepicker_default_setting);
        // prevent datepicker overflowing from the right of the window
        $(this).datepicker().on("show", function(e) {
          $(".datepicker:visible").css("z-index", 10000);
          e.target.style.display = "static";
          const windowWidth = $(window).width();
          const originalElementLeftOffset = $(e.target).offset().left;
          const datepickerWidth = $(".datepicker:visible").width();
          const isOverflowing = (windowWidth - originalElementLeftOffset - datepickerWidth) < 0;
          if (isOverflowing) {
            // offset().right doesn't exist in jQuery so we use getBoundingClientRect().right instead
            const originalElementRightOffset = Math.round(windowWidth - e.target.getBoundingClientRect().right);
            $(".datepicker:visible").css("left", "auto").css("right", originalElementRightOffset + "px");
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
        $(this).on("show.datetimepicker update.datetimepicker change.datetimepicker", (e) => {
          GofastWidgetsCallbacks.dateTimePickerCallback();
        });
        // we want the user to be able to select the time right after the date, so we set the blur event manually
        $(this).on("blur", e => $(this).datetimepicker("hide"));
      });
    }
  };
  
})(jQuery, Gofast, Drupal);