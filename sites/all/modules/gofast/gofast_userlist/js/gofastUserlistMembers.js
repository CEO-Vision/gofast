(function ($, Gofast, Drupal) {
    'use strict';

    Drupal.behaviors.gofastUserlistMembers = {
        attach: function(context, settings){
            if($('#userlist_members').hasClass('processed')){
                return;
            }
            $('#userlist_members').addClass('processed');

            $('#userlist_members').on('shown.bs.tab', function (e) {

                console.log('event:', e);
                if(!document.querySelector('#gofastUserlistMembersTable').classList.contains('processed')){
                    document.querySelector('#gofastUserlistMembersTable').classList.add('processed');
                    KTDatatableColumnRenderingDemo2.init()
                    return;
                }
              });


        }
    };

    var KTDatatableColumnRenderingDemo2 = function() {
        // Private functions

        // basic demo
        var demo = function() {
            let table = document.querySelector('#gofastUserlistMembersTable')
            let bodyHeight = table.parentElement.offsetHeight - 50;

            window.datatable = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/userlist/userlists_members_async/" + table.dataset.id,
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
                    scroll: true, // enable/disable datatable scroll both horizontal and vertical when needed.
                    height: bodyHeight,
                    footer: false, // display/hide footer
                },

                // column sorting
                sortable: true,

                pagination: true,

                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
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
                        field: 'image',
                        title: '',
                        autoHide: false,
                        width: 50,
                        template: function(data) {
                            let image = ''
                            if (data.image) {
                                image = data.image;
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
                            return "<a class=\"btn btn-link text-nowrap\" href=\"" + data.href + "\">" + data.sname + "</a>";
                        },

                    },
                    {
                        field: 'gname',
                        title: Drupal.t('First name'),
                        autoHide: false,
                        overflow: 'hidden',
                        template: function(data) {
                            return "<a class=\"btn btn-link text-nowrap\" href=\"" + data.href + "\">" + data.gname + "</a>";
                        },
                    },
                    {
                        field: 'role',
                        title: Drupal.t('Role'),
                        autoHide: false,
                        overflow: 'hidden',
                        template: function(data) {
                            if(data.role == "membre"){
                                var text = Drupal.t('Member', {}, {'context' : 'gofast:gofast_userlist'});
                            }else if(data.role == "admin"){
                                var text = Drupal.t('Administrator', {}, {'context' : 'gofast:gofast_userlist'});
                            }else if(data.role == "pending_member"){
                                var text = Drupal.t('Pending member', {}, {'context' : 'gofast:userlist:preadd:role:label'});
                            }
                            return "<span>" + text + "</span>";
                        },
                    },
                    {
                        field: 'Actions',
                        title: Drupal.t('Accept / Refuse Pending Members', {}, {'context' : 'gofast:gofast_userlist:preadd:field_label'}),
                        sortable: false,
                        width: 150,
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            var output = '';
                            if(data.role === "pending_member"){
                                output = '<a href="#" class="btn btn-sm' +
                                    ' btn-clean btn-icon btn-icon-md"' +
                                    ' title="' + Drupal.t('Accept member', {}, {'context' : 'gofast:gofast_userlist:preadd:action:accept_member:button_tooltip'}) + '"' +
                                    ' onclick="Gofast.userlist.handleAcceptRefuseButton(this, ' + data.uid + ', ' + table.dataset.id + ', \'accept\')"><i class="fas fa-user-check text-success"></i></a>';
                                output += '<a href="#" class="btn btn-sm' +
                                    ' ml-12' +
                                    ' btn-clean btn-icon btn-icon-md"' +
                                    ' title=" ' + Drupal.t('Refuse member', {}, {'context' : 'gofast:gofast_userlist:preadd_action:refuse_member:button_tooltip'}) + '"' +
                                    ' onclick="Gofast.userlist.handleAcceptRefuseButton(this, ' + data.uid + ', ' + table.dataset.id + ', \'refuse\')"><i class="fas fa-user-times text-danger text-center"></i></a>';
                            } else {
                                output = '<a href="#" class="btn btn-sm' +
                                    ' ml-12 btn-clean btn-icon btn-icon-md">-</a>';
                            }
                            return output;
                        }
                    }
                ],

            });
            $('#kt_datatable_search_role').on('change', function() {
                console.log('select value:', $(this).val().toLowerCase());
                datatable.search($(this).val().toLowerCase(), 'role');
            });

            $('#kt_datatable_search_role , #kt_datatable_search_type, #kt_datatable_search_status').selectpicker();

        };

        return {
            // public functions
            init: function() {
                demo();
            },
        };
    }();

})(jQuery, Gofast, Drupal);
