(function ($, Gofast, Drupal) {
    'use strict';

    Drupal.behaviors.gofastDirectorySearchAdvanced = {
        attach: function (context, settings) {


            // When clicking on #gofastAdvancedSearchResults, launch api/search/search
            $('#submit-advanced-search').once().click(function(e) {


                // TABLE //
                // Remove old datatable if exist
                if($('#gofastAdvancedSearchResults').length > 0){
                    $('#gofastAdvancedSearchResults').KTDatatable('destroy');
                }

                let table = document.querySelector('#gofastAdvancedSearchResults')
                // Generate table
                searchAdvancedTable.init(table);

            });


            // When clicking on #submit-advanced-reset, reset all input form
            $('#submit-advanced-reset').once().click(function(e) {
                Gofast.resetAdvancedSearchForm();
            });

            // When choose a date option in the select, show the date input
            $('.form-select-date').once().change(function() {
                let value = $(this).val();
                let input = $(this).parents('.form-search-date').find('.form-control-date');
                // If the user select an interval , then the input is a datepicker range
                if(value == "between"){ // The interval option
                    // Convert input into datePicker range
                    Gofast.initializeDateRangePicker(input)
                }else if(value == "lower" || value == "higher"){
                    Gofast.initializeDateRangePicker(input, {
                        singleDatePicker: true,
                    });
                }
            });
            
            // Reset function
            Gofast.resetAdvancedSearchForm = function(){
                // Reset all inputs except all operator select and global operator
                $('#search-form-body').find('.form-group input:not(.form-select-field-operator)').val(null);
                
                $('#search-form-body').find('.form-group select:not(.form-select-field-operator)').val(null);
                $('#search-form-body').find('.form-group select:not(.form-select-field-operator)').trigger('change');
                
                // Reset spaces tagify
                window.tagify["ac-list-tags-list-spaces"].removeAllTags();
                
                // Reset all tagify input , we remove all tags inside window.tagify
                $('#search-form-body').find('.form-tagify').each(function() {
                    // Get children input of tagify
                    let input = $(this).find('input.js-tagify');
                    // if the input is not tagify, return
                    if(input.length == 0){
                        return;
                    }
                    // Get name attr
                    let name = input.attr('name');
                    // Remove all tags
                    window.tagify[name].removeAllTags();
                });
                
                // Reset all operator with equal value
                $('#search-form-body').find('.form-select-field-operator').each(function() {
                    $(this).val("equal");
                });
                
                // Reset all datepicker to between
                $('#search-form-body').find('.form-select-date').each(function() {
                    $(this).val("between");
                });
            }


            // When category was changed, check if fieldset exist
            $('#edit-content-type').once().change(function() {
                let categories = $(this).val();
                console.log(categories);

                for (let i = 0; i < categories.length; i++) {
                    if(categories[i].name == "Guide Pratique"){
                        $('#accordion-search-sdma-fiche-gp').removeClass('d-none');
                    }
                }


                // Make a request to check if fieldset exist
                $.ajax({
                    url: window.origin + "/advanced/search/fieldset",
                    type: 'GET',
                    data: {
                        categories: categories
                    },
                    success: function (data) {
                        // If fieldset exist, add it to the DOM
                        if(data.fieldset != null){
                            // Remove old fieldset
                            $('.accordion-advanced-search-standard .fieldset').remove();
                            // Add new fieldset
                            $('.accordion-advanced-search-standard').append(data.fieldset);
                            // Add new fieldset to the form
                            $('#edit-search-advanced').append(data.fieldset);
                        }
                    }
                });
            });

            // Foreach gofast-select2 class init select2
            $('.gofast-select2').once().each(function() {
                $(this).select2({
                    allowClear: true,
                    width: '100%'
                });
            });

            // Foreach gofast-select2 class init select2
            $('.gofast-select2-ajax').once().each(function() {
                var URL = Drupal.settings.gofast.baseUrl + '/gofast/gofast_ac_config';
                var newOption = new Option(Drupal.t('None'), "", false, false);
                $(this).select2({
                    placeholderOption: function () { return undefined; },
                    width: '100%',
                    ajax: {
                    url: URL,
                    params: {
                            data: newOption
                        },
                        dataType: "json",
                        type: "POST",
                        data: function (params) {
                            var queryParameters = {
                                str: params.term,
                                get_user: true
                            }
                            return queryParameters;
                        },
                        processResults: function (data, params) {
                            var resultArray = {
                                results: $.map(data, function (item) {
                                    return {
                                        text: item.display_name,
                                        id: item.display_name
                                    }
                                })
                            };

                            resultArray.results.push({
                                text: params.term,
                                id: params.term
                            }, {
                                text: Drupal.t('None'),
                                id: 'null'
                            }
                            );

                            return resultArray;
                        }
                    }
                });
            });


            var searchAdvancedTable = function () {
                // Private functions
                let _tableEl;
                let _table;
                let _selection;
                let columns = [];
                // user table
                var initTable = function (table) {
                    _crateTable(table)
                };



                var _crateTable = function (table) {
                    _selection = "";
                    // Get all name attr and his value for $('.accordion-advanced-search-standard .form-group .form-control')
                    var nameAttr = {};
                    $('.accordion-advanced-search-standard .form-group .form-control').each(function() {
                        let name = $(this).attr('name');
                        let value = "";
                        // If the value is select2, get the value of the select2
                        if($(this).hasClass('select2-hidden-accessible')){
                            if($(this).hasClass('gofast-select2-ajax')){
                                value = $(this).find('option:selected').val();
                            }else{
                                value = $(this).find('option:selected').attr('id');
                            }
                        }else if($(this).hasClass('form-tagify')){
                            // If the value is tagify, get the value of the tagify
                            value = $(this).find('input.js-tagify').val();
                        }else{
                            value = $(this).val();
                        }
                        if(value == ""){
                            value = null;
                        }
                        
                        // If it's a date, get the specific operator
                        let operator = "";
                        if($(this).hasClass('form-control-date')){
                            operator = $(this).parents('.form-search-date').find('.form-select-date').val();
                        }else{
                            // Get the form-select-field-operator
                            operator = $(this).parents('.form-field-operator').find('.form-select-field-operator').val();
                        }
                        
                        if(value != null){
                            // initialize the object if it doesn't exist
                            if (!nameAttr[name]) {
                                nameAttr[name] = {};
                            }
                            
                            // add the operator 
                            nameAttr[name].operator = operator;
                            
                            // Add it to the object like this nameAttr.name = value
                            nameAttr[name].value = value;
                        }
                        
                    });

                    // Console log columns
                    _table = $(table).KTDatatable({
                        data: {
                            type: 'remote',
                            source: {
                                read: {
                                    url: window.origin + "/advanced/search",
                                    params : {
                                        name: $('input[id="search-name-input"]').val(),
                                        query: $('input[id="edit-search-label"]').val(),
                                        spaces: $('input[id="edit-space"]').val(),
                                        categories :$('select[id="edit-content-type"]').val(),
                                        options: JSON.stringify(nameAttr),
                                        globalOperator: $('input[name="global-operator"]:checked').val().toUpperCase(),
                                    },
                                    method: 'GET',
                                    contentType: 'application/json',
                                    map: function(raw) {
                                        // prevent JS error if no data after applying filter
                                        if (raw == null) {
                                            return [];
                                        }

                                        // sample data mapping
                                        var dataSet = raw;
                                        if (typeof raw.data !== 'undefined') {
                                            dataSet = raw.data;
                                        }

                                        // REFRESH HISTORY Table  //
                                        $('#gofastAdvancedSearchHistory').KTDatatable('reload');
                                        return dataSet;
                                    },
                                },

                            },
                            sortable: true, 
                            serverPaging: true,
                            serverSorting: true,
                            saveState : false,
                        },

                        // layout definition
                        layout: {
                            class: 'GofastTable GofastTable--scroll h-100',
                            scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
                            footer: false, // display/hide footer
                            icons: {
                                sort: {
                                    asc: 'fa fa-chevron-up',
                                    desc: 'fa fa-chevron-down',
                                }
                            }
                        },

                        // column sorting

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
                        columns: _createColumns(),
                    });
                }

                var _createColumns = function () {
                    let finalColumn = [];
                    // Call hooks to declare new columns
                    if(typeof Gofast.hooks.gofast_advanced_search.hook_declare_columns == "object"){
                        Gofast.hooks.gofast_advanced_search.templates = {};
                        for(var i in Gofast.hooks.gofast_advanced_search.hook_declare_columns){
                            if(typeof Gofast.hooks.gofast_advanced_search.hook_declare_columns[i] == "function"){
                                let specColumn = Gofast.hooks.gofast_advanced_search.hook_declare_columns[i]();
                                // Check if the column name is in the cookie
                                let filtersColumns = window.getFiltersColumnsFromCookies();
                                if(filtersColumns.length > 0){
                                    specColumn = specColumn.filter(function (el) {
                                        return filtersColumns.includes(el.field);
                                    });
                                }
                                finalColumn.unshift(...specColumn);
                            }
                        }
                    }
                    //finalColumn.unshift({ selector: { class: 'kt-checkbox--solid' }, field: 'checkbox', title: '', autoHide: false, width: 25, });
                    return finalColumn;
                };

                return {

                    init: function (table) {
                        initTable(table)
                    },
                };
            }();
        }
    }

    if(typeof Gofast.hooks.gofast_advanced_search == "undefined"){
        Gofast.hooks.gofast_advanced_search = [];
        Gofast.hooks.gofast_advanced_search.hook_declare_columns = [];
    }


    Gofast.hooks.gofast_advanced_search.hook_declare_columns.push(function(){
        return [
            {
                field: 'entity_id',
                title: Drupal.t('ID'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    return "<span>"  +row.entity_id + "</span>";
                },
            },
            {
                field: 'im_field_format',
                title: Drupal.t('Type'),
                width: 50,
                textAlign: 'center',
                autoHide: false,
                template: function (row) {
                    if (row.im_field_format == undefined || row.im_field_format == null) {
                        return "-";
                    }
                    return "<span>" + row.im_field_format + "</span>";
                }
            },
            {
                field: 'label',
                title: Drupal.t('Title'),
                width: 400,
                textAlign: 'left',
                autoHide: false,
                template : function(row) {
                    if(row.label == undefined || row.label == null){
                        return "-";
                    }
                    return "<span>"  +row.label + "</span>";
                }
            },
            {
                field: 'formatedGroupes',
                title: Drupal.t('Spaces'),
                width: 200,
                textAlign: 'center',
                sortable: false,
                autoHide: false,
                template: function(row) {
                    let result = "";
                    Object.entries(row.formatedGroupes).forEach(([key, value]) => {
                        result += "<a class='d-flex w-100 mb-2' href='/node/" + value.nid + "' data-nid=" + value.nid + "' data-toggle='search-tooltip' class=''><span class='badge badge-secondary bg-hover-primary text-hover-white text-truncate'>"  + value.title + "</span></a>";
                    });
                    return result;
                },        
            },
            {
                field: 'im_field_state',
                title: Drupal.t('State'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    let result = "";
                    if(row.im_field_state == undefined || row.im_field_state == null){
                        return "-";
                    }
                    result = "<span class='badge badge-secondary h-100 text-wrap font-weight-normal'>" + row.im_field_state + "</span>";
                    return result;
                }
            },
            {
                field: 'im_field_criticity',
                title: Drupal.t('Criticity'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    let result = "";
                    if(row.im_field_criticity == undefined || row.im_field_criticity == null){
                        return "-";
                    }
                    result = "<span class='badge badge-secondary h-100 text-wrap font-weight-normal'>" + row.im_field_criticity + "</span>";
                    return result;
                }
            },
            {
                field: 'im_field_tags',
                title: Drupal.t('Tags'),
                width: 100,
                textAlign: 'center',
                sortable: false,
                autoHide: false,
                template: function(row) {
                    let result = "";
                    if(row.im_field_tags == undefined || row.im_field_tags == null){
                        return "-";
                    }
                    Object.entries(row.im_field_tags).forEach(([key, value]) => { 
                        result += "<div class='d-flex w-100 mb-2'><span class='badge badge-secondary h-100 text-wrap font-weight-normal'>" + Drupal.t(value) + "</span></div>"; 
                    }); 
                    return result; 
                return result;
                }
            },
            {
                field: 'sm_vid_Category',
                title: Drupal.t('Category'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    let result = "";
                    if(row.sm_vid_Category == undefined || row.sm_vid_Category == null){
                        return "-";
                    }
                    Object.entries(row.sm_vid_Category).forEach(([key, value]) => { 
                        result += "<span class='badge badge-secondary h-100 text-wrap font-weight-normal'>" + Drupal.t(value) + "</span>"; 
                    }); 
                    return result;
                }
            },
            {
                field: 'sm_unr_author',
                title: Drupal.t('Author'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.sm_unr_author == undefined || row.sm_unr_author == null){
                        return "-";
                    }
                    return "<span>"  +row.sm_unr_author + "</span>";
                },
            },
            {
                field: 'tos_unr_document_reference',
                title: Drupal.t('Document reference'),
                width: 200,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.tos_unr_document_reference == undefined || row.tos_unr_document_reference == null){
                        return "-";
                    }
                    return "<span>"  +row.tos_unr_document_reference + "</span>";
                },
            },
            {
                field: 'ps_popularity',
                title: Drupal.t('Popularity'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.ps_popularity == undefined || row.ps_popularity == null){
                        return "-";
                    }
                    return "<span>"  +row.ps_popularity + "</span>";
                },
            },
            {
                field: 'ds_field_date',
                title: Drupal.t('Deadline'),
                width: 200,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.ds_field_date == undefined || row.ds_field_date == null){
                        return "-";
                    }
                    return "<span>"  +row.ds_field_date + "</span>";
                },
            },
            {
                field: 'ds_created',
                title: Drupal.t('Creation date'),
                width: 200,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.ds_created == undefined || row.ds_created == null){
                        return "-";
                    }
                    return "<span>"  +row.ds_created + "</span>";
                },
            },
            {
                field: 'ds_changed',
                title: Drupal.t('Last updated'),
                width: 200,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.ds_changed == undefined || row.ds_changed == null){
                        return "-";
                    }
                    return "<span>"  +row.ds_changed + "</span>";
                },
            },
            {
                field: 'ss_language',
                title: Drupal.t('Language'),
                width: 100,
                textAlign: 'center',
                autoHide: false,
                template: function(row) {
                    if(row.ss_language == undefined || row.ss_language == null){
                        return "-";
                    }
                    return '<div class="symbol symbol-20 document__editable--label position-relative py-2">'
                    + '<img class="metadata-language-flag" alt="Pic" src="' + row.ss_language  + '" />'
                    + '</div>';
                },
            },
        ];  
    })
})(jQuery, Gofast, Drupal);
