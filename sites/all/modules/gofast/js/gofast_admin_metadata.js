(function ($, Gofast, Drupal) {

    'use strict';

    const GofastAdminMetadataElements = [
        "",
        '',
        '<div class="d-flex""><input type="text" name="tagname" class="form-control GofastMetaTagFilter__tagname" placeholder="' + Drupal.t("Search") + '"/>',
        '<button type="submit" class="btn-icon input-group-text" style="border: 0; border-radius: 0; position: relative; left: -45px; margin: 1px;">' +
        '<i class="fas fa-search" style="font-size: 1.25rem;"></i></button></div>',
        '<div><a href="/modal/nojs/taxonomy/tags/add" class="ctools-use-modal btn btn-primary" style="position: fixed; right: 200px;">' +
            Drupal.t("Add new") + '</a></div>',
    ];

    Drupal.behaviors.gofastMetadata = {
        attach: function (context, settings) {
            if (document.querySelector('#gofastMetatagsTable') != null) {
                if (!document.querySelector('#gofastMetatagsTable').classList.contains('processed')) {
                    let table = document.querySelector('#gofastMetatagsTable')
                    table.classList.add('processed')
                    GofastMetatagTable.init(table)
                    $("#gofastMetatagsTable").on("datatable-on-layout-updated", function () {
                        GofastAddKDataTableSubheader("gofastMetatagsTable", "MetadataFilterForm", GofastAdminMetadataElements);
                    });
                }
            }

        }
    };

    var GofastMetatagTable = function () {
        // Private functions
        let _tableEl;
        let _bodyHeight;
        let _table;
        let _columns;
        let _selection;
        // metatag table
        var initTable = function (table) {
            _tableEl = table
            let jsonColumns = _tableEl.dataset.columns
            _columns = JSON.parse(jsonColumns)


            _crateTable(table)


        };

        var _crateTable = function (table) {
            _selection = "";
            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/gofast/global/get-async/tags",
                            method: 'GET',
                            map: function(raw) {
                                if (raw == null) {
                                    return [];
                                }
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
                    class: 'GofastTable GofastTable--scroll',
                    scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
                    footer: false, // display/hide footer
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
                        field: 'links',
                        title: '',
                        width: 35,
                        autoHide: false,
                        sortable: false
                    },
                    {
                        field: 'tag_nam',
                        title: _columns.name,
                        autoHide: false,
                        template: function (data) {
                            return data.name
                        },
                    },
                    {
                        field: 'used',
                        title: _columns.used,
                        autoHide: false,
                        template: function (data) {
                            return data.qty
                        },
                    },
                    {
                        field: 'actions',
                        title: '',
                        sortable: false,
                        autoHide: false,
                        width: 0,
                        template: function(data) {
                            return '<div class="w-100 d-flex justify-content-center" id="">' +
                                '<div class="btn-group btn-group-xs" role="group" aria-label="contextual actions">' +
                                '</div>' +
                                '<div class="m-auto dropdown">' +
                                '<a type="button" class="btn btn-primary btn-icon btn-sm position-relative" id="dropdown-metatag-dropdown" title="Contextual actions" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">' +
                                '<i class="fa fa-bars icon-nm"></i>' +
                                '</a>' +
                                '<div class="dropdown-menu dropdown-menu-md py-1" aria-labelledby="dropdown-metatag-dropdown">' +
                                '<ul class="navi navi-hover navi-link-rounded-lg px-1">' +
                                '<li class="navi-item">' +
                                '<a class="navi-link ctools-use-modal" id="" href="/modal/nojs/metadata/bulk_action/edit/' + data.tid + '"><span class="navi-icon"><i class="fas fa-pen"></i></span><span class="navi-text">' + Drupal.t("Edit") + '</span></a>        </li><li class="navi-separator my-1"></li>' +
                                '<li class="navi-item">' +
                                '<a class="navi-link ctools-use-modal" id="" href="/modal/nojs/metadata/bulk_action/merge/' + data.tid + '"><span class="navi-icon"><i class="fas fa-layer-group"></i></span><span class="navi-text">' + Drupal.t("Merge") + '</span></a>        </li><li class="navi-separator my-1"></li>' +
                                '<li class="navi-item">' +
                                '<a class="navi-link ctools-use-modal" id="" href="/modal/nojs/metadata/bulk_action/delete/' + data.tid + '"><span class="navi-icon"><i class="fas fa-trash"></i></span><span class="navi-text">' + Drupal.t("Delete") + '</span></a>' +
                                '</li>' +
                                '</ul>' +
                                '</div></div>' +
                                '</div>';
                        },
                    },
                    {
                        field: 'tid',
                        title: '',
                        autoHide: false,
                        width: 0,
                        sortable: false,
                        template: function(data) {
                            return '<span style="display:none;" class="tid_span" value="'+ data.tid +'">' + data.tid + '</span>'
                        },
                    },
                ],
            });

            // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
            const formInterval = setInterval(function() {
                if (!$('#MetadataFilterForm').length) {
                    return;
                }
                $('#MetadataFilterForm').on('submit', function(e){
                    $(".datatable-body").html("");
                    Gofast.addLoading();
                    e.preventDefault();
                    let filterArr = $(this).serializeArray()
                    let filter = Object.create({})

                    filterArr.forEach(fil => {
                        if(!!fil.value){
                            let att = fil.name
                            filter[att] = fil.value
                        }
                    })

                    _table.setDataSourceParam("query", filter)
                    _table.reload()
                })
                clearInterval(formInterval);
            }, 100);

            $("#gofastMetatagsTable").on("datatable-on-ajax-done", function() {
                Gofast.removeLoading();
            });

            $("#gofastMetatagsTable").on("datatable-on-check", function(event,args){
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                if(selected_records.length !== 0){
                    $("#container-selected-items .dropdown").off("click");
                    $("#container-selected-items .dropdown").on("show.bs.dropdown", Gofast.fixDropdownPosition);
                }
                selected_records.each(function (index) {
                    var tid = $(this).find(".tid_span").html();
                    _selection += tid + "-";
                });

                $("#container-selected-items .navi-item .ctools-use-modal").each(function (index) {
                    var href = $(this).attr("href");
                    var array_href = href.split("/");
                    array_href[array_href.length - 1] = _selection;
                    var new_href = array_href.join("/");
                    $(this).attr("href", new_href);
                    $(this).removeClass("ctools-use-modal-processed");
                    $(this).off("click");
                });

                GofastTriggerKDataTableMegaDropdown(selected_records, "gofastMetatagsTable");
            });

            $("#gofastMetatagsTable").on("datatable-on-uncheck", function (event, args) {
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function (index) {
                    var tid = $(this).find(".tid_span").html();
                    _selection += tid + "-";
                });

                $("#container-selected-items .navi-item .ctools-use-modal").each(function (index) {
                    var href = $(this).attr("href");
                    var array_href = href.split("/");
                    array_href[array_href.length - 1] = _selection;
                    var new_href = array_href.join("/");
                    $(this).attr("href", new_href);
                    $(this).removeClass("ctools-use-modal-processed");
                    $(this).off("click");
                });

                GofastTriggerKDataTableMegaDropdown(selected_records, "gofastMetatagsTable");
            });

            const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

            for(const interferringEvent of interferringEvents) {
                $("#gofastMetatagsTable").on(interferringEvent, function(event, data){
                    GofastRefreshKDataTableSubheader("gofastMetatagsTable", "MetadataFilterForm");
                    
                    var selected_records = _table.getSelectedRecords();
                    _selection = "";
                    selected_records.each(function (index) {
                        var tid = $(this).find(".tid_span").html();
                        _selection += tid + "-";
                    });
    
                    GofastTriggerKDataTableMegaDropdown(selected_records, "gofastMetatagsTable");
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
