(function ($, Gofast, Drupal) {
    'use strict';

    Drupal.behaviors.gofastSearchAdvancedHistory = {
        attach: function (context, settings) {

            var searchAdvancedHistoryTable = function () {
                // Private functions
                let _table;
                let _tableEl;
                let _columns;
                // user table

                var initHistoryTable = function (table) {
                    _tableEl = table
                    let jsonColumns = _tableEl.dataset.columns
                    _columns = JSON.parse(jsonColumns)
                    _createHistoryTable(table)
                };

                var _createHistoryTable = function (table) {

                    _table = $(table).KTDatatable({
                        data: {
                            type: 'remote',
                            source: {
                                read: {
                                    url: window.origin + "/advanced/search/history",
                                    method: 'GET',
                                    contentType: 'application/json',
                                    map: function (raw) {
                                        // prevent JS error if no data after applying filter
                                        if (raw == null) {
                                            return [];
                                        }

                                        // sample data mapping
                                        var dataSet = raw;
                                        if (typeof raw.data !== 'undefined') {
                                            dataSet = raw.data;
                                        }
                                        return dataSet;
                                    },
                                },

                            },
                            serverPaging: true,
                            saveState: false,
                        },

                        // layout definition
                        layout: {
                            class: 'GofastTable GofastTable--scroll',
                            scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
                            footer: false, // display/hide footer
                        },

                        // column sorting
                        sortable: false,

                        pagination: true,

                        translate: {
                            records: {
                                processing: Drupal.t('Please wait...'),
                                noRecords: Drupal.t('No records found')
                            },
                            toolbar: {
                                pagination: {
                                    items: {
                                        default: {
                                            first: Drupal.t('First'),
                                            prev: Drupal.t('Previous'),
                                            next: Drupal.t('Next'),
                                            last: Drupal.t('Last'),
                                            more: Drupal.t('More pages'),
                                            input: Drupal.t('Page number'),
                                            select: Drupal.t('Select page size')
                                        },
                                        info: Drupal.t("Displaying {{start}} - {{end}} of {{total}} records")
                                    }
                                }
                            }
                        },

                        // columns definition
                        columns: [
                            {
                                field: 'name',
                                title: _columns.name,
                                autoHide: false,
                                width: 500,
                                sortable: false,
                                template: function (data) {
                                    //If empty name
                                    if (data.name == "") {
                                        return "<a href='#' class='search-advanced-history-link btn-link text-nowrap'>" + Drupal.t("No search name") + "</a>"
                                    }
                                    return "<a href='#' class='search-advanced-history-link btn-link text-nowrap'>" + data.name + "</a>"
                                },
                            },
                            {
                                field: 'date',
                                title: _columns.date,
                                autoHide: false,
                                width: 200,
                                sortable: false,
                                template: function (data) {
                                    return "<span class='text-nowrap'>" + data.date + "</span>"
                                },
                            },
                            {
                                field: 'filters',
                                title: "",
                                autoHide: false,
                                sortable: false,
                                width: 0,
                                template: function (data) {
                                    return "<span class='text-nowrap'>" + data.filters + "</span>"
                                },
                            },
                            {
                                field: 'query',
                                title: "",
                                autoHide: false,
                                sortable: false,
                                width: 0,
                                template: function (data) {
                                    return "<span class='text-nowrap'>" + data.query + "</span>"
                                },
                            },

                        ],
                    });

                }

                return {

                    initHistory: function (table) {
                        initHistoryTable(table)
                    },
                };
            }();

            // Execute only if gofastAdvancedSearchHistory have not processed class
            $("#gofastAdvancedSearchHistory:not(.gofastAdvancedSearchHistory-processed)").addClass("gofastAdvancedSearchHistory-processed").each(function () {
                $('#gofastAdvancedSearchHistory').KTDatatable('destroy');
                let historyTable = document.querySelector('#gofastAdvancedSearchHistory')
                searchAdvancedHistoryTable.initHistory(historyTable);
            });

            $("#gofastAdvancedSearchHistory").once().on("datatable-on-layout-updated", function () {
                Drupal.attachBehaviors();
            });

            // When clicking on td, get data-value and put it in the input , $('.search-advanced-history-link') not processed
            $('.search-advanced-history-link:not(.processed)').click(function (e) {
                $(this).addClass('processed')
                Gofast.resetAdvancedSearchForm();

                let queryColumn = $(this).parents('.datatable-row').find('td[data-field="query"]');
                let nameColumn = $(this).parents('.datatable-row').find('td[data-field="name"]');
                let fieldColumn = $(this).parents('.datatable-row').find('td[data-field="filters"]');

                // Get value of data-field="query" via aria-label
                let query = queryColumn.attr('aria-label');

                // If query is not empty, put it in the input
                if (query != "") {
                    $('#search-form-body').find('input[name="search_label"]').val(query);
                }

                // Get search name
                let searchName = nameColumn.attr('aria-label');
                if (searchName != "") {
                    $('#search-form-body').find('input#search-name-input').val(searchName);
                }
                // Get value of data-field="filters" via aria-label
                let filters = fieldColumn.attr('aria-label');

                // JSON decode filters
                filters = JSON.parse(filters);
                // Reach all filters (the key is the name of the filter)
                for (let key in filters) {
                    // Get value of the filter
                    let operator = filters[key].operator;
                    let value = filters[key].value;

                    // If value is an array, it's a select
                    if (Array.isArray(value)) {

                    } else {
                        debugger;
                        // Fill the operator
                        
                        // Check if its a select, input, date, etc
                        // If it's a select
                        let accordion;
                        if ($('#search-form-body').find('select[name="' + key + '"]').length > 0) {
                            // Get select
                            let select = $('#search-form-body').find('select[name="' + key + '"]');
                            
                            $('#search-form-body').find('select[name="' + key + '"]').parents('.GofastForm__Field').find('.form-select-field-operator').val(operator)
                            
                            // The value is an id , then find the option with this id
                            let option = select.find('option[id="' + key + "-"+ value + '"]');
                            
                            // If the option exist, get the value attributes
                            let optionValue = option.attr('value');
                            // Set value
                            select.val(optionValue);
                            
                            //Trigger change event
                            select.trigger('change');
                            accordion = select.parents('.accordion').first();
                        }
                        // If it's a date
                        else if ($('#search-form-body').find('input[name="' + key + '"]').hasClass('datepicker')) {
                            $('#search-form-body').find('input[name="' + key + '"]').parents('.grid-container').find('.form-select-field-operator').val(operator)
                            
                            // Get datepicker
                            let datepicker = $('#search-form-body').find('input[name="' + key + '"]');
                            // Set value
                            datepicker.val(value);
                            accordion = datepicker.parents('.accordion').first();
                        }
                        // If it's an input
                        else if ($('#search-form-body').find('input[name="' + key + '"]').length > 0) {
                            
                            $('#search-form-body').find('input[name="' + key + '"]').parents('.grid-container').find('.form-select-field-operator').val(operator)
                            // Get input
                            let input = $('#search-form-body').find('input[name="' + key + '"]');

                            // Set value
                            input.val(value);
                            accordion = input.parents('.accordion').first();
                        }
                        // If it's a tagify
                        else if ($('#search-form-body').find('tag[name="' + key + '"]').hasClass('tagify')) {
                            $('#search-form-body').find('tag[name="' + key + '"]').parents('.grid-container').find('.form-select-field-operator').val(operator)
                            
                            // Get tagify
                            let inputElmName = $('#search-form-body').find('[name="' + key + '"]>input');
                            // Set value
                            window.tagify[inputElmName[0].name].removeAllTags();
                            window.tagify[inputElmName[0].name].addTags(JSON.parse(value));
                            accordion = tagify.parents('.accordion').first();
                        }
                        else if (key == "im_field_category") {
                            // for each filters 
                            let values = [];
                            let select = $('#search-form-body').find('select[name="content_type"]');
                            for (let keyFilter in filters[key]) {
                                let valueFilter = filters[key][keyFilter];
                                // Add value to an array
                                values.push("im_field_category-" + valueFilter);
                            }
                            
                            // JSON encode values
                            select.val(values);
                            select.trigger('change');
                        }else if(key == "sm_og_group_content_ref"){
                            window.tagify["ac-list-tags-list-spaces"].removeAllTags();
                            // Reach all filters[key]
                            let values = [];
                            for (let keyFilter in filters[key]) {
                                let valueFilter = filters[key][keyFilter];
                                // Add value to an array
                                values.push(JSON.parse(valueFilter));
                            }
                            window.tagify["ac-list-tags-list-spaces"].settings.whitelist = values;
                            window.tagify["ac-list-tags-list-spaces"].addTags(values);
                        }

                        //Only if accordion is defined, open accordion where input is (take the first accordion)
                        if (typeof accordion !== 'undefined') {   
                            accordion.find('.collapse').addClass('show');
                            accordion.find('.card-title').removeClass('collapsed');
                        }
                    }
                }
            });
        }
    }
})(jQuery, Gofast, Drupal);
