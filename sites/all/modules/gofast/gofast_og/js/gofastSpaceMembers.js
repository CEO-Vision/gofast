(function ($, Gofast, Drupal) {

    'use strict';

    const mapOGRidToImportance = function (rid) {
        if ([13, 16, 17, 20, 23, 26, 28].includes(rid)) {
            return 0;
        }
        if ([1, 3, 5, 7, 9, 12, 14, 18, 22, 25, 27, 29].includes(rid)) {
            return 1;
        }
        if ([2, 4, 6, 8, 10, 11, 15, 19, 21, 24, 30].includes(rid)) {
            return 2;
        }
        return 2;
    }

    Drupal.behaviors.gofastSpaceMembers = {
        attach: function(context, settings){

            if($('#gofastSpaceMembersLink').hasClass('processed')){
                return;
            }
            $('#gofastSpaceMembersLink').addClass('processed');
            if($('#gofastSpaceMembersLink').hasClass('active') && !document.querySelector('#gofastSpaceMembersTable').classList.contains('processed')){
                document.querySelector('#gofastSpaceMembersTable').classList.add('processed');
                KTDatatableColumnRenderingDemo.init();
            }
            $('#gofastSpaceMembersLink').on('shown.bs.tab', function (e) {

                console.log('event:', e);


                if(!document.querySelector('#gofastSpaceMembersTable').classList.contains('processed')){
                    document.querySelector('#gofastSpaceMembersTable').classList.add('processed');
                    KTDatatableColumnRenderingDemo.init()
                    return;
                }
              });


        }
    };

    var KTDatatableColumnRenderingDemo = function() {
        // Private functions

        // basic demo
        var demo = function() {
            const timeElapsed = Date.now();
            const today = new Date(timeElapsed).toUTCString();
            let table = document.querySelector('#gofastSpaceMembersTable')

            let users = [];

            let dataJson = []


            for (let index = 0; index < 1000; index++) {

                let data = {
                    'id' : index,
                    'name': users[KTUtil.getRandomInt(0,11)],
                    'entity': 'CEO-Vision',
                    'role': KTUtil.getRandomInt(1, 5),
                }
                dataJson.push(data);
            }

            window.datatable = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/gofast_og/space_members_async/" + table.dataset.id,
                            method: 'GET',
                            // sample custom headers
                            // headers: {'x-my-custom-header': 'some value', 'x-test-header': 'the value'},
                            map: function(raw) {
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
                    serverSorting: false,
                },

                // layout definition
                layout: {
                    scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
                    class: 'GofastTable GofastTable--scroll h-100',
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

                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
                },

                rows: {
                    afterTemplate: function (row, data, index) {
                        Drupal.attachBehaviors(row);
                    }
                },
                
                translate: {
                    records : {
                        processing : Drupal.t('Please wait...'),
                        noRecords: Drupal.t('No records found')
                    },
                    toolbar: {
                        pagination: {
                            items:{
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
                        field: 'actions',
                        title: '',
                        sortable: false,
                        overflow: 'visible',
                        width: 65,
                        textAlign: 'center',
                        autoHide: false,
                        template: function(data) {
                            return data.actions;
                        },
                    },
                    {
                        field: '',
                        title: '',
                        autoHide: false,
                        width: 50,
                        sortable: false,
                        template: function(data) {
                            let image = ''
                            if (data.image) {
                                image = "<img alt=\"Pic\" src=\"" + window.origin + "/sites/default/files/styles/thumbnail/public/pictures/" + data.image + "\"/>";
                            } else if(data.type == 'user') {
                                image = "<span class=\"symbol-label\"><i class=\"fas fa-user\"></i></span>";
                            } else {
                                image = "<span class=\"symbol-label\"><i class=\"fas fa-users\"></i></span>";
                            }
                            var output = "<div class=\"d-flex align-items-center\">\n<div class=\"symbol symbol-40 flex-shrink-0\"> " + image + "\n</div>\n</div>";
                            return output;
                        },
                    },
                    {
                        field: 'sname',
                        title: Drupal.t('Last name'),
                        autoHide: false,
                        overflow: 'hidden',
                        template: function(data) {
                            if (data.type == "userlist") {
                                var namePopover = '<div class="py-2 px-4">' + data.sname + '</div>';
                            }
                            else{
                                var namePopover = '';
                            }
                            return ('<a data-toggle="popover" data-trigger="hover" data-html="true" data-content="' + namePopover.replaceAll("\"", "'") + '" class=\"gofast__popover btn-link text-nowrap\" href=\"' + data.href + '\">' + data.sname + '</a>');
                        },

                    },
                    {
                        field: 'gname',
                        title: Drupal.t('First name'),
                        autoHide: false,
                        overflow: 'hidden',
                        template: function(data) {
                            return "<a class=\"btn-link text-nowrap\" href=\"" + data.href + "\">" + data.gname + "</a>";
                        },

                    },
                    {
                        field: 'type',
                        title: 'Type',
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            if(data.type == "userlist"){
                                var text = Drupal.t('Userlist');
                            }else if(data.type == "user"){
                                var text = Drupal.t('User');
                            }
                            return "<span>" + text + "</span>";
                        },

                    },
                    {
                        field: 'entity',
                        title: Drupal.t('Entity'),
                        autoHide: false,
                        template: function(data) {
                            let text = "-"
                            if (typeof data.entity != "undefined") {
                                text = data.entity;
                            }
                            return "<span>" + text + "</span>";
                        }
                    },
                    {
                        field: 'profile',
                        title: Drupal.t('Profile'),
                        autoHide: false,
                        template: function(data) {
                            let text = "-"
                            if (typeof data.profile != "undefined") {
                                text = data.profile;
                            }
                            return "<span>" + text + "</span>";
                        }
                    },
                    {
                        field: 'rid',
                        title: Drupal.t('Role'),
                        autoHide: false,
                        sortCallback: function(data, sort, column) {
                            return $(data).sort(function (a, b) {
                                if (sort == 'asc'){
                                    return mapOGRidToImportance(parseInt(a.rid)) - mapOGRidToImportance(parseInt(b.rid));
                                } else {
                                    return mapOGRidToImportance(parseInt(b.rid)) - mapOGRidToImportance(parseInt(a.rid));
                                }
                            })
                        },
                        template: function(row) {

                            let status = {
                                title: 'Read Only',
                                class: 'label-light-info'
                            }

                            switch (row.rname) {
                                case 'read only member':
                                    status.title = Drupal.t('Read only');
                                    status.class = 'label-light-primary';
                                    break;

                                case 'administrator member':
                                    status.title = Drupal.t('Administrator', {}, {'context' : 'gofast:gofast_user'});
                                    status.class = 'label-danger';
                                    break;

                                case 'group contributor':
                                    status.title = Drupal.t('Contributor', {}, {'context' : 'gofast:gofast_user'});
                                    status.class = 'label-primary';
                                    break;
                                default:
                                    status.title = Drupal.t('No Role');
                                    status.class = 'label-warning';
                                    break;
                            }
                            if(row.membership_state == "2"){
                                return '<span class="label font-weight-bold label-lg label-warning label-inline w-100 '+status.class+'" style="height:30px;">'+status.title+'('+Drupal.t('Pending', {}, {'context' : 'gofast'})+')</span>';
                            }else{
                                return '<span class="label font-weight-bold label-lg label-inline w-100 '+status.class+'" style="height:30px;">'+status.title+'</span>';
                            }
                        },
                    },
                    {
                        field: 'created',
                        title: Drupal.t('Subscribed'),
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            return "<span>" + window.GofastFormatAsDrupalDate(data.created * 1000) +"</span>";
                        },

                    },
                    {
                        field: 'status',
                        title: Drupal.t('Status'),
                        autoHide: false,
                        template: function(data) {

                            let status = {
                                title: 'Active',
                                class: 'label-light-info'
                            }

                            if(data.type == 'userlist'){
                                return "<span>-</span>";
                            }

                            switch (data.status) {
                                case '0':
                                    status.title = Drupal.t('Blocked');
                                    status.class = 'danger';
                                    break;

                                case '1':
                                    status.title = Drupal.t('Active');
                                    status.class = 'primary';
                                    break;

                                default:
                                    status.title = Drupal.t('No Status');
                                    status.class = 'warning';
                                    break;
                            }

                            return "<span class='label label-" + status.class + " label-dot mr-2'></span><span class='font-weight-bold text-" + status.class + "'>" + status.title + "</span>";
                        },
                    },
                ],

            });
            $('#kt_datatable_search_role').on('change', function() {
                datatable.search($(this).val().toLowerCase(), 'rid');
            });
            $('#kt_datatable_search_type').on('change', function() {
                datatable.search($(this).val().toLowerCase(), 'type');
            });
            $('#kt_datatable_search_status').on('change', function() {
                datatable.search($(this).val().toLowerCase(), 'status');
            });

            $('#kt_datatable_search_role , #kt_datatable_search_type, #kt_datatable_search_status').selectpicker();

        };

        return {
            // public functions
            init: function() {
                demo();
                Drupal.attachBehaviors();
            },
        };
    }();

})(jQuery, Gofast, Drupal);
