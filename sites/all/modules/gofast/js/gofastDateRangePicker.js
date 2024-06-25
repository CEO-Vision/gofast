(function ($, Gofast, Drupal) {
    
    // Init date range picker for a given element
    function initializeDateRangePicker(element, options) {
        
        // Cleaning the input
        $(element).val("");
        
        let user = Gofast.get('user');
        let lang = user.language;
        // Configure default options
        const defaultOptions = {
            autoUpdateInput: false,
            language: lang,
            showDropdowns: true,
            locale: {
                cancelLabel: Drupal.t('Clear'),
                applyLabel: Drupal.t('Apply'),
            },
            autoclose: true,
            format: window.GofastConvertDrupalDatePattern("bootstrapDate"),
            todayHighlight: true,
            clearBtn: true,
            singleDatePicker: false,
            beforeShowDay: GofastWidgetsCallbacks.datePickerCallback,
        };

        // Merge default options with specific options
        const mergedOptions = Object.assign({}, defaultOptions, options);
        $(element).daterangepicker(mergedOptions);

        // Clear the input when the user click on the clear button
        $(element).on('cancel.daterangepicker', function (ev, picker) {
            $(this).val('')
        });
        
        // Manually update the date because if autoUpdateInput is set to true, when we click outside the datepicker, the value is updated
        $(element).on('apply.daterangepicker', function(ev, picker) {
            // Get language and format
            let format = picker.locale.format;
            if(picker.singleDatePicker){
                $(this).val(picker.startDate.format(format));
            }else{
                $(this).val(picker.startDate.format(format) + ' - ' + picker.endDate.format(format));
            }
        });
    }

    // Insert the function into the Gofast global variable
    Gofast.initializeDateRangePicker = initializeDateRangePicker;

    Drupal.behaviors.gofastDateRangePicker = {
        attach: function (context, settings) {
            // For each .form-search-date element not already processed
            $(".form-search-date:not(.processed)", context).addClass('processed').each(function () {
                let input = $('.gofastDateRangetimepicker');
                Gofast.initializeDateRangePicker(input, {
                    // Specific options here
                });
            });
        }
    };
})(jQuery, Gofast, Drupal);
