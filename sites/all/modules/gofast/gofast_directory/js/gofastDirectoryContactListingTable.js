(function ($, Gofast, Drupal) {

    'use strict';
      // 8 columns in main header means array length must be of 8
    const DirectoryContactListingTableSubheaderElements = [
        "",
        "",
        '<input type="text" name="lastname" class="form-control GofastDirectoryUsersFilter__lastname" placeholder="' + Drupal.t("Enter lastname") + '"/>',
        '<input type="text" name="firstname" class="form-control GofastDirectoryUsersFilter__firstname" placeholder="' + Drupal.t("Enter firstname") + '"/>',
        '<input type="text" name="entity" class="form-control GofastDirectoryUsersFilter__entity" placeholder="' + Drupal.t("Enter entity") + '"/>',
        '<input type="text" name="email" class="form-control GofastDirectoryUsersFilter__email" placeholder="' + Drupal.t("Enter email address") + '"/>',
        '<input type="text" name="mobile" class="form-control GofastDirectoryUsersFilter__mobile" placeholder="' + Drupal.t("Enter mobile") + '"/>', 
        '',
        '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" id="btnSubmit" class="btn btn-xs btn-primary btn-icon m-0">' +
        '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
        '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
        '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
        '</button></div>',
    ];

    Drupal.behaviors.gofastDirectoryContactListing = {
        attach: function () {
            if(document.querySelector('#gofastDirectoryContactListingTable') != null) {
                if(!document.querySelector('#gofastDirectoryContactListingTable').classList.contains('processed')){
                    let table = document.querySelector('#gofastDirectoryContactListingTable')
                    table.classList.add('processed')
                        GofastDirectoryTable.init(table)
                        if (typeof ResizeObserver != "undefined") {
                            const directoryResizeObserver = new ResizeObserver(function(entries) {
                                GofastRefreshKDataTableSubheader("gofastDirectoryContactListingTable", "DirectoryContactListingFilterForm");
                            });
                            directoryResizeObserver.observe(document.querySelector("#gofastDirectoryContactListingTable"));
                            $("#gofastDirectoryContactListingTable").on("datatable-on-destroy", function(){
                                directoryResizeObserver.disconnect();
                            });
                        }
                        $("#gofastDirectoryContactListingTable").on("datatable-on-layout-updated", function(){
                            GofastAddKDataTableSubheader("gofastDirectoryContactListingTable", "DirectoryContactListingFilterForm", DirectoryContactListingTableSubheaderElements);
                        });
                        $("#gofastDirectoryContactListingTable").on("datatable-on-init", function(){
                            const pagerTitleInterval = setInterval(function(){
                                if (!$(".datatable-pager-info button").length) {
                                    return;
                                }
                                $(".datatable-pager-info button").attr("title", Drupal.t('Select page size'));
                                clearInterval(pagerTitleInterval);
                        }, 500);
                    });
               }   
            }
        }
    };

    var GofastDirectoryTable = function () {
        // Private functions
        let _tableEl;
        let _table;
        let _columns;
        let _selection;
        // space table

        var initTable = function (table) {

            _tableEl = table

            let jsonColumns = _tableEl.dataset.columns
            _columns = JSON.parse(jsonColumns)// prevent KTDatatable setting title for all select inputs, including select filters
            $.fn.KTDatatable.defaults.translate.toolbar.pagination.items.default.select = "";
            _crateTable(table)

        };

        var _crateTable = function (table) {

            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/directory/directory_async/contact_listing",
                            method: 'GET',
                            map: function (raw) {
                                // sample data mapping
                                var dataSet = raw;
                                if (typeof raw.data !== 'undefined') {
                                    dataSet = raw.data;
                                }                 
                                return dataSet;
                            },
                        },
                    },
                    pageSize: 20,
                    serverPaging: false,
                    serverFiltering: true,
                    serverSorting: true,
                    autoColumns: false,
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
                
                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
                },

                // column sorting
                sortable: true,
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
                
                rows: {
                    afterTemplate: function (row, data, index) {
                        Drupal.attachBehaviors(row);
                    }
                },
                
                // columns definition
                columns: [
                    {
                        selector: {
                            class: 'kt-checkbox--solid'
                        },
                        field: 'checkbox',
                        title: '',
                        autoHide: false,
                        width: 25,
                    },  
                    {
                        field: "",
                        title: '',
                        autoHide: false,
                        overflow: 'visible',
                        width: 0,
                        sortable: false,
                        template: function(data) {
                            return '<span class="nid_span" style="display:none;">' + data.nid + '</span>';
                        },
                    },
                    {
                        field: "lastname",
                        title: _columns.lastname,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<span>' + data.lastname + '</span>';
                        },
                    },
                    {
                        field: "firstname",
                        title: _columns.firstname,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<span>' + data.firstname + '</span>';
                        },
                    },
                    {
                        field: "entity",
                        title: _columns.entity,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<span>' + data.entity + '</span>';
                        },
                    },
                    {
                        field: "email",
                        title: _columns.email,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<span>' + data.email + '</span>';
                        },
                    },
                    {
                        field: "phone",
                        title: _columns.phone,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<span>' + data.phone + '</span>';
                        },
                    },
                    {
                        field: 'actions--delete',
                        title: '',
                        sortable: false,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            if (data.can_update) {
                                return '<a href="/modal/nojs/node/' + data.nid + '/manage" class="btn btn-link-primary btn-icon btn-lg mx-2 ctools-use-modal"><i class="fa fa-trash-o"></i></a>';
                            }
                            return "";
                        },
                    },
                    {
                        field: 'actions--edit',
                        title: '',
                        sortable: false,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            if (data.can_update) {
                                return '<a href="/modal/nojs/contact/' + data.nid + '/edit" class="btn btn-link-primary btn-icon btn-lg mx-2 ctools-use-modal"><i class="fa fa-edit"></i></a>';
                            }
                            return "";
                        },
                    },
                ],
            });
            
            const formInterval = setInterval(function() {
                if (!$('#DirectoryContactListingFilterForm').length) {
                    return;
                }
                $('#DirectoryContactListingFilterForm').on('submit', function(e){
                    e.preventDefault()
                    _table.spinnerCallback(true)
                    let filterArr = $(this).serializeArray()
                    let filter = Object.create({})
                    filterArr.forEach(fil => {
                        if(!!fil.value){
                            let att = fil.name
                            filter[att] = fil.value
                        }
                    })          
                    _table.setDataSourceParam("query", filter)
                    _table.load()
                  
                  GofastKDataTableReload("gofastDirectoryContactListingTable");
                  $('#gofastDirectoryContactListingTable .datatable-subheader > th:nth-child(1) > span:nth-child(1)').css('margin', 0)
                })
                
                $('#DirectoryContactListingFilterForm').on('reset', function(e){
                    $(e.currentTarget['status']).val('').selectpicker("refresh")
                    _table.setDataSourceParam("query", {})
                    _table.load()
                })
                $('#gofastDirectoryContactListingTable .datatable-subheader > th:nth-child(1) > span:nth-child(1)').css('margin', 0)
                clearInterval(formInterval);
            }, 100);
            
            
            $("#gofastDirectoryContactListingTable").on("datatable-on-check", function(event,args){
                $(".kt-checkbox--solid input[disabled]").prop("checked", false);
                var selected_records = _table.getSelectedRecords().filter(function(record){
                    return $(this).find(".kt-checkbox--solid input[disabled]").length == 0;
                });
                _selection = "";
                selected_records.each(function( index ) {
                   var nid = $(this).find(".nid_span").html();  
                   _selection += nid+"-";  
                });
                _selection = _selection.slice(0, -1); // remove trailing "-";
            
                if(selected_records.length === _table.getDataSet().length){
                    $('#gofastDirectoryContactListingTable .datatable-head [type=checkbox]').prop( "checked", true);
                }
               
                $("#container-selected-items .navi-item .ctools-use-modal").each(function(index){
                      var href = $(this).attr("href");
                      var array_href = href.split("/");
                      array_href[array_href.length - 1] = _selection;
                      var new_href = array_href.join("/");
                      $(this).attr("href", new_href);
                      $(this).removeClass("ctools-use-modal-processed");
                      $(this).off( "click");
                });                           
                
                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryContactListingTable");
                
                //disable the search button 
                if(selected_records.length > 0){
                    $("#btnSubmit").css("pointer-events", "none")
                    //remove the contextual actions container
                }
           });
                  
           $("#gofastDirectoryContactListingTable").on("datatable-on-uncheck", function(event,args){
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                                
                if($('#gofastDirectoryContactListingTable .datatable-head [type=checkbox]').is(':checked')){
                    $('#gofastDirectoryContactListingTable .datatable-head [type=checkbox]').prop( "checked", false);
                }

                selected_records.each(function( index ) {
                   var nid = $(this).find(".nid_span").html();                
                   _selection += nid +"-";  
                });
               
                $("#container-selected-items .navi-item .ctools-use-modal").each(function(index){
                      var href = $(this).attr("href");
                      var array_href = href.split("/");
                      array_href[array_href.length - 1] = _selection;
                      var new_href = array_href.join("/");
                      $(this).attr("href", new_href);
                      $(this).removeClass("ctools-use-modal-processed"); 
                      $(this).off( "click");
                });

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryContactListingTable");
                
                //enable the search button
                if(selected_records.length == 0){
                    $("#btnSubmit").css("pointer-events", "auto")
                }
           });
           const interferringEvents = ["datatable-on-sort", "datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

           for(const interferringEvent of interferringEvents) {
            $("#gofastDirectoryContactListingTable").on(interferringEvent, function(event, data){
                GofastRefreshKDataTableSubheader("gofastDirectoryContactListingTable", "DirectoryContactListingFilterForm");
                var selected_records = _table.getSelectedRecords();
                if(interferringEvent == "datatable-on-sort") {
                    $('.contextual-actions-container').css('display', 'none');
                    window.GofastKDataTableReload('gofastDirectoryContactListingTable');
                }
                _selection = "";
                selected_records.each(function( index ) {
                   var nid = $(this).find(".nid_span").html();
                   _selection += nid+"-";  
                });
            
                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryContactListingTable");
                if (interferringEvent == "datatable-on-ajax-done") {
                    $(".datatable-subheader").show();
                    Gofast.removeLoading();
                }
            });
           }
           
        }
        return {
            init: function (table) {
                initTable(table)
            },
        };
    }();

})(jQuery, Gofast, Drupal);
