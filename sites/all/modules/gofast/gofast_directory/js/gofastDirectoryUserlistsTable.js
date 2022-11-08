(function ($, Gofast, Drupal) {

    'use strict';

    // 8 columns in main header means array length must be of 8
    const DirectoryUserlistsTableSubheaderElements = [
        "",
        "",
        '<input type="text" name="userlist" class="form-control GofastDirectoryUserslistFilter__userlist"  placeholder="' + Drupal.t("Enter userlist name") + '"/>',
        '<div class="d-flex"><input type="text" name="firstname" class="w-50 form-control GofastDirectoryUserslistFilter__firstname" placeholder="' + Drupal.t("Enter creator firstname") + '"/><input type="text" name="lastname" class="w-50 form-control GofastDirectoryUserslistFilter__lastname" placeholder="' + Drupal.t("Enter creator lastname") + '"/></div>',
        '',
        '',
        '<div class="input-daterange input-group GofastDateRange GofastDirectoryUserslistFilter__created" data-field="created">' +
        '<input type="text" class="form-control" name="startCreated" style="font-size: 12px; padding: 3px;" />' +
        '<div class="input-group-append">' +
        '<span class="input-group-text" style="padding: 1px;"></span>' +
        '</div>' +
        '<input type="text" class="form-control" name="endCreated" style="font-size: 12px; padding: 3px;" />' +
        '</div>',
        '<div class="input-daterange input-group GofastDateRange GofastDirectoryUserslistFilter__modified" data-field="modified">' +
        '<input type="text" class="form-control" name="startModified" style="font-size: 12px; padding: 3px;" />' +
        '<div class="input-group-append">' +
        '<span class="input-group-text" style="padding: 1px;"></span>' +
        '</div>' +
        '<input type="text" class="form-control" name="endModified" style="font-size: 12px; padding: 3px;" />' +
        '</div>',
        '<div class="GofastDirectoryFilterButtons d-flex ml-auto flex-column align-items-center" style="gap: .5rem; transform: translateY(-1rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
        '<i class="fas fa-search"></i>' +
        '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
        '<i class="fas fa-undo"></i>' +
        '</button></div>',
    ];

    Drupal.behaviors.gofastDirectoryUserlists = {
        attach: function(context, settings){
            if(document.querySelector('#gofastDirectoryUserlistsTable') != null){
                if(!document.querySelector('#gofastDirectoryUserlistsTable').classList.contains('processed')){
                    let table = document.querySelector('#gofastDirectoryUserlistsTable')
                    table.classList.add('processed')
                    GofastDirectoryTable.init(table)
                    if (typeof ResizeObserver != "undefined") {
                        const directoryResizeObserver = new ResizeObserver(function(entries) {
                            GofastRefreshKDataTableSubheader("gofastDirectoryUserlistsTable", "DirectoryUserlistFilterForm");
                        });
                        directoryResizeObserver.observe(document.querySelector("#gofastDirectoryUserlistsTable"));
                        $("#gofastDirectoryUserlistsTable").on("datatable-on-destroy", function(){
                            directoryResizeObserver.disconnect();
                        });
                    }
                    $("#gofastDirectoryUserlistsTable").on("datatable-on-layout-updated", function(){
                        GofastAddKDataTableSubheader("gofastDirectoryUserlistsTable", "DirectoryUserlistFilterForm", DirectoryUserlistsTableSubheaderElements);
                        $(".datatable-pager-info button").attr("title", Drupal.t('Select page size'));
                    });
                    $("#gofastDirectoryUserlistsTable").on("datatable-on-init", function(){
                        const pagerTitleInterval = setInterval(function(){
                            if (!$(".datatable-pager-info button").length) {
                                return;
                            }
                            $(".datatable-pager-info button").attr("title", Drupal.t('Select page size'));
                            clearInterval(pagerTitleInterval);
                        }, 500);
                    });
                }
                $('.admin_popover[data-toggle="popover"]').on('shown.bs.popover', function(){$('.popover').addClass('adminPopover');});
            }
        }
    };

    var GofastDirectoryTable = function() {
        // Private functions
        let _tableEl;
        let _table;
        let _columns;

        // user table
        var initTable = function(table) {

            _tableEl = table
            let jsonColumns = _tableEl.dataset.columns
            _columns = JSON.parse(jsonColumns)
            // prevent KTDatatable setting title for all select inputs, including select filters
            $.fn.KTDatatable.defaults.translate.toolbar.pagination.items.default.select = "";
            _crateTable(table)
        };

        var _crateTable = function(table){

            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/directory/directory_async/userlist",
                            method: 'GET',
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

                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
                },

                toolbar: {
                    items: {
                        pagination: {
                            pages: {
                                desktop: {
                                    layout: 'default',
                                    pagesNumber: 3
                                },
                                tablet: {
                                    layout: 'default',
                                    pagesNumber : 3
                                },
                                mobile: {
                                    layout: 'compact'
                                }
                            }
                        }
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
                                },
                                info: Drupal.t("Displaying {{start}} - {{end}} of {{total}} records")
                            }
                        }
                    }
                },

                rows: {
                    afterTemplate: function (row, data, index) {
                        Drupal.attachBehaviors(row);
                        var adminPopover = $('.admin_popover');
                        initPopover(adminPopover);
                    }
                },

                // columns definition
                columns: [
                    {
                        field: 'actions',
                        title: '',
                        overflow: 'visible',
                        width: 35,
                        autoHide: false,
                        sortable: false,
                        template: function(data) {
                            return '<div id="contextual-actions-loading-' + data.nid + '" class="loader-breadcrumb not-processed"></div><div id="userlist-node-actions-' + data.nid + '">';
                        },
                    },
                    {
                        field: "",
                        title: '',
                        autoHide: false,
                        overflow: 'visible',
                        width: 35,
                        sortable: false,
                        template: function(data) {
                            let name = data.name
                            let symbol = 'UL'
                            if(name.length >= 2){
                                symbol = name.slice(0,2).toUpperCase()
                            }

                            var output = "<div class=\"d-flex align-items-center\"><div class=\"symbol symbol-35 flex-shrink-0\"> <span class=\"symbol-label\">" + symbol + "</span></div></div>";

                            return output;
                        },
                    },
                    {
                        field: 'name',
                        title: _columns.name ,
                        autoHide: false,
                        width: 250,
                        template: function (data){
                            const namePopover = '<div class="py-2 px-4">' + data.name + '</div>';
                            return ('<a data-toggle="popover" data-trigger="hover" data-html="true" data-content="' + namePopover.replaceAll("\"", "'") + '" class="gofast__popover btn-link text-nowrap" href="/node/' + data.nid + '#userlistlocations"> ' + data.name + '</a>');
                        }
                    },
                    {
                        field: 'creator',
                        title: _columns.creator,
                        autoHide: false,
                        width: 250,
                        template: function(data){
                            const {creator} = data

                            const firstname = creator.firstname ? creator.firstname : null
                            const lastname = creator.lastname ? creator.lastname : null
                            const picture = creator.picture ? creator.picture : null

                            if(firstname || lastname){
                                return "<div class=\"d-flex align-items-center\"> <div class=\"symbol symbol-25 symbol-circle mr-4\"> <img alt=\"Pic\" src=\"" + picture + "\"> </div> <div class=\"font-size-lg\">" + firstname + " " + lastname + "</div></div>";
                            }
                            return "<div class=\"font-size-lg\">" + Drupal.t("You don't have permission to view this profile", {}, {context: "gofast"}) + "</div>";
                        }
                    },
                    {
                        field: "nb_admins",
                        title: _columns.nb_admins,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center',
                        width: 75,
                        template: function(data){
                            var popoverContent = '';
                            data.nb_admins.admins.forEach(function(value,index){
                                const picture = value.picture;
                                const firstName = value.gname;
                                const lastName = value.sname;
                                const uid = value.uid;
                                popoverContent += "<div class=\"d-flex align-items-center p-5\"> <div class=\"symbol symbol-35 flex-shrink-0 mr-4\"> <img alt=\"Pic\" src=\"" + picture + "\"> </div> <a href=\"/user/" + uid + "\" class=\"font-size-lg\">" + firstName + " " + lastName + "</a> </div> ";
                            });
                            const nb_admins = data.nb_admins.nb_admins;

                            return "<a tabindex='" + data.nid + "' class=\"admin_popover\" type=\"button\" data-toggle=\"popover\" data-trigger=\"focus\" data-placement=\"left\" data-html=\"true\" data-content='" + popoverContent + "'>" + nb_admins + "  <i class=\"fa fa-caret-down ml-2\" style=\"color: #3699FF\"></i></a>";
                        }
                    },
                    {
                        field: "nb_members",
                        title: _columns.nb_members,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center',
                        width: 75,
                    },
                    {
                        field: 'created',
                        title: _columns.created,
                        overflow: 'visible',
                        autoHide: false,
                        width: 100,
                        template: function(data) {
                            return "<span>" + window.GofastFormatAsDrupalDate(data.created * 1000) +"</span>";
                        },

                    },
                    {
                        field: 'modified',
                        title: _columns.modified,
                        overflow: 'visible',
                        autoHide: false,
                        width: 100,
                        template: function(data) {
                            return "<span>" + window.GofastFormatAsDrupalDate(data.modified * 1000) +"</span>";
                        },

                    },
                    {
                        field: 'buttons',
                        title: "",
                        overflow: 'visible',
                        autoHide: false,
                        width: 100,
                        textAlign: 'left',
                        sortable: false,
                    },
                ],
            });

            
            // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
            const formInterval = setInterval(function() {
                if (!$('#DirectoryUserlistFilterForm').length) {
                    return;
                }
                $('#DirectoryUserlistFilterForm').on('submit', function(e){
                    e.preventDefault()
                    let filterArr = $(this).serializeArray()
                    let filter = Object.create({})

                    filterArr.forEach(fil => {
                        if(!!fil.value){
                            let att = fil.name
                            filter[att] = fil.value
                        }
                    })
                    // don't submit if date values are incomplete
                    const dateValues = [{start: filter.startModified, end: filter.endModified}, {start: filter.startCreated, end: filter.endCreated}];
                    for (const dateValue of dateValues) {
                        if ((dateValue.start && !dateValue.end) || (!dateValue.start && dateValue.end)) {
                            Gofast.toast(Drupal.t("Please fill in both start and end dates", {}, {context: "gofast:gofast_directory"}), "error");
                            return;
                        }
                    }

                    if(filter.startCreated) filter.startCreated = moment(filter.startCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.endCreated) filter.endCreated = moment(filter.endCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.startModified) filter.startModified = moment(filter.startModified, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.endModified) filter.endModified = moment(filter.endModified, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;

                    _table.setDataSourceParam("query", filter)
                    _table.load()
                })

                $('#DirectoryUserlistFilterForm').on('reset', function(e){
                    $(e.currentTarget['status']).val('').selectpicker("refresh")
                    _table.setDataSourceParam("query", {})
                    _table.load()
                })
                clearInterval(formInterval);
            }, 100);

            const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

            for(const interferringEvent of interferringEvents) {
             $("#gofastDirectoryUserlistsTable").on(interferringEvent, function(event, data){
                GofastRefreshKDataTableSubheader("gofastDirectoryUserlistsTable", "DirectoryUserlistFilterForm");
                if (interferringEvent == "datatable-on-ajax-done") {
                    $(".datatable-subheader").show();
                    Gofast.removeLoading();
                }
             });
            }

        }

        var initPopover = function(el) {
            var skin = el.data('skin') ? 'popover-' + el.data('skin') : '';
            var triggerValue = el.data('trigger') ? el.data('trigger') : 'hover';

            el.popover({
                trigger: triggerValue,
                template: '\
                <div class="popover ' + skin + '" role="tooltip">\
                    <div class="arrow"></div>\
                    <h3 class="popover-header"></h3>\
                    <div class="popover-body"></div>\
                </div>'
            });
        }

        return {

            init: function(table){
                initTable(table)
            },
        };
    }();

})(jQuery, Gofast, Drupal);
