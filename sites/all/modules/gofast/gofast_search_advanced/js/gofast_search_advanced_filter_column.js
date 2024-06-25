(function ($, Gofast, Drupal) {
    'use strict';

    Drupal.behaviors.gofastSearchAdvancedFilterColumn = {
        attach: function (context, settings) {
            // Click event on the advanced search filter column
            $('#advanced-search-filter-column').once().click(function () {
                
                Gofast.addLoading();
                let columns = getFiltersColumnsFromCookies();
                // Get the template with a ajax call and giving the columns filters
                $.ajax({
                    type: "GET",
                    data: { columns_displayed: columns },
                    url: "/search/advanced/filter/column",
                    success: function (response) {
                        // JSON decode the response
                        var data = JSON.parse(response);

                        Gofast.removeLoading();
                        // Create the modal
                        Gofast.modal(data, Drupal.t('Columns filters'));
                    },
                    error : function (response) {
                        Gofast.removeLoading();
                        Gofast.toast(Drupal.t('An error occured : ') + response , 'error');
                    }
                });
            });

            // Click event on the advanced search filter column submit
            $('#submit-columns-filters').once().click(function () {
                // Get all the checked filters
                var filters = [];
                $('#list-columns-filters input:checked').each(function (index, element) {
                    filters.push($(element).val());
                });

                // Save it to the cookies
                setFiltersColumnsToCookies(filters);

                // Close the modal
                Gofast.closeModal();

                // Relaunch the search
                $('#submit-advanced-search').trigger('click');
            });

                // Check all columns checkbox
            $('.check-all-columns').on('click', function () {
                var parent = $(this).data('parent');
                $(parent).find('input[type="checkbox"]').prop('checked', $(this).prop('checked'));
                $(this).parent().find('.checkbox-label').text($(this).prop('checked') ? Drupal.t('Uncheck all') : Drupal.t('Check all'));
            });

            // When we click on a checkbox, we check if all the checkboxes are checked, then we check the check-all-columns checkbox
            $('input[name="columns[]"]').on('click', function () {
                var parent = $(this).closest('.accordion');
                var allChecked = parent.find('input[name="columns[]"]').length === parent.find('input[name="columns[]"]:checked').length;
                parent.find('.check-all-columns').prop('checked', allChecked);
                parent.find('.checkbox-label').text(allChecked ? Drupal.t('Uncheck all') : Drupal.t('Check all'));
            });
        }
    };


    // Init the filters columns cookies with the default values (if not already set)
    window.setInitFiltersColumnsCookies = function (refresh = true) {
        //Get all column id
        var filtersColumns = [];
        var $columns = $('#gofastAdvancedSearchResults thead th');
        $columns.each(function (index, element) {
            // If the colmun is displayed, we add it to the filters columns
            if ($(element).css('display') != 'none') {
                filtersColumns.push($(element).attr('data-field'));
            }
        });
        setFiltersColumnsToCookies(filtersColumns);

        return filtersColumns;
    }

    // Get the filters columns from the cookies
    window.getFiltersColumnsFromCookies = function () {
        var cookies = $.cookie('search_advanced_filters_columns');
        // If cookie exist and he is not empty
        if (cookies && cookies != "[]") {
            var filters = JSON.parse(cookies);
            return filters;
        }

        return setInitFiltersColumnsCookies();
    }

    // Set the filters columns to the cookies
    window.setFiltersColumnsToCookies = function (filters) {
        // we can't set cookie as httpOnly via JS and there is no point doing it on filters, but we at least require HTTPS
        $.cookie('search_advanced_filters_columns', JSON.stringify(filters), { secure: true });
    }



})(jQuery, Gofast, Drupal);
