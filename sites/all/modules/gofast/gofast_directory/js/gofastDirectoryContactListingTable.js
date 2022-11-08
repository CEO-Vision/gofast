(function ($, Gofast, Drupal) {

    'use strict';

    Drupal.behaviors.gofastDirectorySpaces = {
        attach: function () {
            if (document.querySelector('#gofastDirectoryContactListingTable') != null) {
                if (!document.querySelector('#gofastDirectoryContactListingTable').classList.contains('processed')) {
                    let table = document.querySelector('#gofastDirectoryContactListingTable')
                    table.classList.add('processed')
                    GofastDirectoryTable.init(table)
                    Drupal.attachBehaviors();
                }
            }
        }
    };

    var GofastDirectoryTable = function () {
        // Private functions
        let _tableEl;
        let _table;
        let _columns;
        // space table

        var initTable = function (table) {

            _tableEl = table

            let jsonColumns = _tableEl.dataset.columns
            _columns = JSON.parse(jsonColumns)
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
                            return '<a href="/modal/nojs/node/' + data.nid + '/manage" class="btn btn-link-primary btn-icon btn-lg mx-2 ctools-use-modal"><i class="fa fa-trash-o"></i></a>';
                        },
                    },
                    {
                        field: 'actions--edit',
                        title: '',
                        sortable: false,
                        overflow: 'visible',
                        autoHide: false,
                        template: function (data) {
                            return '<a href="/modal/nojs/contact/' + data.nid + '/edit" class="btn btn-link-primary btn-icon btn-lg mx-2 ctools-use-modal"><i class="fa fa-edit"></i></a>';
                        },
                    }
                ],
            });
        }

        return {
            init: function (table) {
                initTable(table)
            },
        };
    }();

})(jQuery, Gofast, Drupal);
