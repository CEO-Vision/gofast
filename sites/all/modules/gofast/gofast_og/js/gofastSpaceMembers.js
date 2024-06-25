(function ($, Gofast, Drupal) {

    'use strict';
    // 8 columns in main header means array length must be of 8
    const $tableElement = $('#gofastSpaceMembersTable');
    const DirectoryUsersTableSubheaderElements = [
        "",
        "",
        '<input type="text" name="sname" class="form-control GofastDirectoryUsersFilter__lastname" placeholder="' + Drupal.t("Enter lastname") + '"/>',
        '<input type="text" name="gname" class="form-control GofastDirectoryUsersFilter__firstname" placeholder="' + Drupal.t("Enter firstname") + '"/>',
        '<input type="text" name="entity" class="form-control GofastDirectoryUsersFilter__entity" placeholder="' + Drupal.t("Enter entity") + '"/>',
        '<select name="profile" class="form-control selectpicker">' +
        '<option value="">' + Drupal.t("All") + '</option>' +
        '<option value="3">' + Drupal.t("Super administrator", {}, { context: "gofast:gofast_user" }) + '</option>' +
        '<option value="7">' + Drupal.t("User support", {}, { context: "gofast:gofast_directory" }) + '</option>' +
        '<option value="4">' + Drupal.t("Standard", {}, { context: "gofast:gofast_directory" }) + '</option>' +
        '</select>',
        '<select name="type" class="form-control selectpicker"><option value="">' +
        Drupal.t("All") +
        '</option>><option value="external">' +
        Drupal.t("External", {}, { context: "gofast:gofast_user" }) +
        '</option>><option value="userlist">' +
        Drupal.t("Userlist", {}, { context: "gofast:gofast_user" }) +
        '</option>><option value="user">' +
        Drupal.t("User") +
        '</option></select>',
        '<select name="rid" class="form-control selectpicker"><option value="">' +
        Drupal.t("All") +
        '</option><option value="' +  $tableElement.attr("data-admin-rid") + '">' +
        Drupal.t("Administrator", {}, { context: "gofast:gofast_user" }) +
        '</option><option value="' +  $tableElement.attr("data-contributor-rid") + '">' +
        Drupal.t("Contributor", {}, { context: "gofast:gofast_user" }) +
        '</option><option value="' +  $tableElement.attr("data-readonly-rid") + '">' +
        Drupal.t("Read Only", {}, { context: "gofast:gofast_user" }) +
        '</option><option value="0">' +
        Drupal.t('Pending members', {}, {context: 'gofast:gofast_user'}) +
        '</option></select>',
        '<div class="input-daterange input-group GofastDateRange GofastDirectoryUsersFilter__created" data-field="created"><input type="text" class="form-control" name="startCreated" style="font-size: 12px; padding: 3px;" /><div class="input-group-append"><span class="input-group-text" style="padding: 1px;"></span></div><input type="text" class="form-control" name="endCreated"style="font-size: 12px; padding: 3px;" /></div>',
        '<select name="status" class="form-control selectpicker" style="display: block !important;"><option value="">' +
        Drupal.t("All") +
        '</option><option value="0">' +
        Drupal.t("Blocked", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="1">' +
        Drupal.t("Activated", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="2">' +
        Drupal.t("Disabled", {}, { context: "gofast:gofast_directory" }) +
        '</option></select>',
        '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
        '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
        '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
        '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
        '</button></div>',
    ];
    // columns definition
    const DirectoryUsersTableColumns = [
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
            field: 'picture',
            title: '',
            autoHide: false,
            width: 40,
            sortable: false,
            template: function(data) {
                let image = ''
                if (data.image) {
                    return data.image;
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
            template: function(data) {
                let snamePopover = `<div class='py-2 px-4'>${data.sname}</div>`;
                return (`<a class="btn-link d-flex" href="${data.href}"><span class="text-truncate" data-toggle="popover" data-placement="right" data-trigger="hover" data-html="true" data-content="${snamePopover}">${data.sname}</span></a>`);
            },

        },
        {
            field: 'gname',
            title: Drupal.t('First name'),
            autoHide: false,
            template: function(data) {
                let gnamePopover = `<div class='py-2 px-4'>${data.gname}</div>`;
                return (`<a class="btn-link d-flex" href="${data.href}"><span class="text-truncate" data-toggle="popover" data-placement="right" data-trigger="hover" data-html="true" data-content="${gnamePopover}">${data.gname}</span></a>`);
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
                return `<span class="text-truncate" title="${text}">${text}</span>`;
            }
        },
        {
            field: 'profile',
            title: Drupal.t('Profile'),
            autoHide: false,
            width: 150,
            textAlign: 'center',
            template: function(data) {
                let text = "-"
                if (typeof data.profile != "undefined") {
                    text = data.profile;
                }
                return "<span class='badge badge-pill badge-light' style='width: max-content;'><span class='text-truncate'>" + text + "</span></span>";
            }
        },
        {
            field: 'type',
            title: 'Type',
            overflow: 'visible',
            autoHide: false,
            template: function(data) {
                if(data.type == "userlist"){
                    var text = Drupal.t('Userlist');
                    return "<span class='badge badge-pill badge-light'>" + text + "</span>";
                }else if(data.type == "user"){
                    var text = Drupal.t('User');
                    return "<span class='badge badge-pill badge-light'>" + text + "</span>";
                }else if(data.type == "external"){
                    var text = Drupal.t('External');
                    return "<span class='badge badge-pill badge-light'>" + text + "</span>";
                }
                    return "<span class='badge badge-pill badge-dark'>" + data.type + "</span>";
                },

        },
        {
            field: 'rid',
            title: Drupal.t('Role'),
            autoHide: false,
            width: 150,
            sortCallback: function(data, sort, column) {
                return $(data).sort(function (a, b) {
                    if (sort == 'asc'){
                        return mapOGRidToImportance(parseInt(a.role)) - mapOGRidToImportance(parseInt(b.role));
                    } else {
                        return mapOGRidToImportance(parseInt(b.role)) - mapOGRidToImportance(parseInt(a.role));
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
                        status.class = 'label-secondary';
                        break;
                }
                if(row.membership_state == "2"){
                    return '<span class="label font-weight-bold label-lg label-light label-inline w-100 " style="height:30px;">'+Drupal.t('Pending members', {}, {'context': 'gofast:gofast_user'})+'</span>';
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
            width: 80,
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
                    case '2':
                        status.title = Drupal.t('Disabled');
                        status.class = 'warning';
                        break;

                    default:
                        status.title = Drupal.t('No Status');
                        status.class = 'warning';
                        break;
                }

                return "<span class='label label-" + status.class + " label-dot mr-2'></span><span class='font-weight-bold text-" + status.class + "'>" + status.title + "</span>";
            },
        },
        {
            field: 'buttons',
            title: "",
            overflow: 'visible',
            autoHide: false,
            width: 0,
            textAlign: 'left',
            sortable: false,
        },
        {
            field: 'actions',
            title: '',
            width: 40,
            autoHide: false,
            sortable: false,
            textAlign: "left",
            template: function(data) {
                if (!data || data.length == 0) return "-";
                return "<div class=\"d-none\">" + data.actions + "</div>";
            },
        },
        {           
            field: 'uid',
            title: '',
            autoHide: false,
            width: 0,
            sortable: false,
            template: function(data) {
                if (!data || data.length == 0) return "-";
                return '<span style="display:none;" class="uid_span" value="'+ data.uid +'">' + data.uid + '</span>'
            },
        },
    ];

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
    function processGofastSpaceMembersTable() {
        let table = document.querySelector('#gofastSpaceMembersTable');
        if (table) {
            table.classList.add('processed');
            GofastSpaceMembersTable.init();
            if (typeof ResizeObserver !== "undefined") {
                const directoryResizeObserver = new ResizeObserver(function(entries) {
                    GofastRefreshKDataTableSubheader("gofastSpaceMembersTable", "DirectoryUserFilterForm");
                });
                directoryResizeObserver.observe(document.querySelector("#gofastSpaceMembersTable"));
                $("#gofastSpaceMembersTable").on("datatable-on-destroy", function(){
                    directoryResizeObserver.disconnect();
                });
            }
            $("#gofastSpaceMembersTable").on("datatable-on-layout-updated", function(){
                GofastAddKDataTableSubheader("gofastSpaceMembersTable", "DirectoryUserFilterForm", DirectoryUsersTableSubheaderElements);
            });
            $("#gofastSpaceMembersTable").on("datatable-on-init", function(){
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

    Drupal.behaviors.gofastSpaceMembers = {
        attach: function (context, settings) {
            if ($('#gofastSpaceMembersLink').length == 0 || $('#gofastSpaceMembersLink').hasClass('processed')) {
                return;
            }
            $('#gofastSpaceMembersLink').addClass('processed');
            if ($('#gofastSpaceMembersTable').length) {
                if ($('#gofastSpaceMembersLink').hasClass('active') && !document.querySelector('#gofastSpaceMembersTable').classList.contains('processed')) {
                    processGofastSpaceMembersTable();
                }
            }
            $('#gofastSpaceMembersLink').on('shown.bs.tab', function (e) {
                if ($('#gofastSpaceMembersTable').length) {
                    if (!document.querySelector('#gofastSpaceMembersTable').classList.contains('processed')) {
                        processGofastSpaceMembersTable();
                        return;
                    }
                }
            });
        }
    }; 

    var GofastSpaceMembersTable = function() {
        // Private attributes
        let _table;
        let _tableEl;
        let _selection;
        let _props = {};
        let _has_actions = true;

        var initTable = function() {
            if($('#gofastSpaceMembersTable').length) {
                _tableEl = document.querySelector('#gofastSpaceMembersTable')
            }
            // remove checkboxes if current user is not a space administrator
            if(_tableEl.dataset["checkboxes"] == "0") {
                DirectoryUsersTableColumns.shift();
                DirectoryUsersTableSubheaderElements.shift();
                _has_actions = false;
            }
            _selection = "";
            _table = $(_tableEl).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/gofast_og/space_members_async/" + _tableEl.dataset.id,
                            method: 'GET',
                            // sample custom headers
                            // headers: {'x-my-custom-header': 'some value', 'x-test-header': 'the value'},
                            map: function(raw) {
                                // sample data mapping
                                var dataSet = raw;
                                if (typeof raw.data !== 'undefined') {
                                    dataSet = raw.data;
                                }
                                if (typeof raw.props !== 'undefined') {
                                    _props = raw.props;
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

                // columns definition
                columns: DirectoryUsersTableColumns,
                rows: {
                    autoHide: false,
                    afterTemplate: function(row, data, index) {
                        if (!data || data.length == 0 || !_has_actions) return;
                        if (data.uid == Gofast.get("user").uid) {
                            const checkboxInterval = setInterval(function() {
                                const targetCheckbox = row.find(".kt-checkbox--solid input[type='checkbox']");
                                const targetCheckboxCell = row.find(".datatable-cell-check");
                                if (!targetCheckbox.length) {
                                    return;
                                }
                                targetCheckboxCell.attr("title", Drupal.t("You are not authorized to select yourself since you are not authorized to perform actions such as deleting your own account.", {}, {context: "gofast:gofast_user"}));
                                targetCheckbox.attr("disabled", "");
                                targetCheckbox.closest("label").css("cursor", "not-allowed");
                                clearInterval(checkboxInterval);
                            }, 100);
                        }
                    },
                },
            });
            // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
            const formInterval = setInterval(function() {
                if (!$('#DirectoryUserFilterForm').length) {
                    return;
                }
                $('#DirectoryUserFilterForm').on('submit', function(e){
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
                    const dateValues = [{start: filter.startLogin, end: filter.endLogin}, {start: filter.startCreated, end: filter.endCreated}];
                    for (const dateValue of dateValues) {
                        if ((dateValue.start && !dateValue.end) || (!dateValue.start && dateValue.end)) {
                            Gofast.toast(Drupal.t("Please fill in both start and end dates", {}, {context: "gofast:gofast_directory"}), "error");
                            return;
                        }
                    }
                    
                    // if date is localized, we need to "unformat" it in order to get the correct timestamp
                    if(filter.startCreated) filter.startCreated = moment(filter.startCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.endCreated) filter.endCreated = moment(filter.endCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
    
                    _table.setDataSourceParam("query", filter)
                    _table.load()
                })
                $('#DirectoryUserFilterForm').on('reset', function(e) {
                    e.preventDefault();
                
                    $(this).find('input, select').val('').selectpicker('refresh');
                    _table.setDataSourceParam('query', {});
                    _table.load();
                });
                
                clearInterval(formInterval);
            }, 100);

            $("#gofastSpaceMembersTable").on("datatable-on-check", function(event,args){
                $(".kt-checkbox--solid input[disabled]").prop("checked", false);
                var selected_records = _table.getSelectedRecords().filter(function(record){
                    return $(this).find(".kt-checkbox--solid input[disabled]").length == 0;
                });
                _selection = "";
                selected_records.each(function( index ) {
                   var uid = $(this).find(".uid_span").html();                
                   _selection += uid+"-";  
                });
                _selection = _selection.slice(0, -1); // remove trailing "-";
               
                $("#container-selected-items .navi-item .ctools-use-modal").each(function(index){
                      var href = $(this).attr("href");
                      var array_href = href.split("/");
                      array_href[array_href.length - 1] = _selection;
                      var new_href = array_href.join("/");
                      $(this).attr("href", new_href);
                      $(this).removeClass("ctools-use-modal-processed");
                      $(this).off( "click");
                });

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastSpaceMembersTable");
                if (selected_records.length) {
                    // disable delete action if one among checked user(s) never logged in
                    const selectedLoginValues = _table.getRecord(selected_records[0].dataset.row).getColumn("login").getValue();
                    if (!selectedLoginValues.includes(Drupal.t("Never logged in"))) {
                        $("#gofastDeleteUserAction").addClass("disabled");
                    }
                }
           });
                  
           $("#gofastSpaceMembersTable").on("datatable-on-uncheck", function(event,args){
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                   var uid = $(this).find(".uid_span").html();               
                   _selection += uid+"-";  
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

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastSpaceMembersTable");
           });

           const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

           for(const interferringEvent of interferringEvents) {
            $("#gofastSpaceMembersTable").on(interferringEvent, function(event, data){
                GofastRefreshKDataTableSubheader("gofastSpaceMembersTable", "DirectoryUserFilterForm");
                
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                   var uid = $(this).find(".uid_span").html();
                   _selection += uid+"-";  
                });

                if (_has_actions) {
                    GofastTriggerKDataTableMegaDropdown(selected_records,"gofastSpaceMembersTable");
                }
                if (interferringEvent == "datatable-on-ajax-done") {
                    $(".datatable-subheader").show();
                    Gofast.removeLoading();
                }
            });
           }    
        };
        return {
            // public functions
            init: function() {
                initTable();
                Drupal.attachBehaviors();
            },
        };
    }();

    Gofast.manage_bulkactions_users_process = async function() {
        var panels = $(".manage-bulkactions-users-panel");
        var panelsProgressBar = $("#bulkactions-users-panels-progress .progress-bar");
        var numberOfPanels = panels.length;
        var processedPanels = 0;
        
        //For each panel, process the request and check the result
        for (const panel of panels) {
          var uid = $(panel).find('#uid').text();
          var action = $(panel).find('#action').text();
          var options = $(panel).find('#options').text();
          await $.post(location.origin + "/directory/manage_bulkactions/users/process", { uid : uid , action : action, options: options}).done(function(data) {
            let success = false;
            if(data == "succesfully_managed") {
                $(panel).find('.panel-body').find('ul').find('li').append("<i class='fa fa-check' style='color:green' aria-hidden='true'></i>");
                $(panel).find('.panel-body').find(".manage-bulkactions-users-info").html("<i class='fa fa-check' style='color:green' aria-hidden='true'></i> " + Drupal.t("Success", {}, {context: 'gofast'}));
                success = true;
            }else{   
                $(panel).find('.panel-body').find('ul').find('li').append("<i class='fa fa-times' style='color:red' aria-hidden='true'></i>");
                $(panel).find('.panel-body').find(".manage-bulkactions-users-info").html("<i class='fa fa-times' style='color:red' aria-hidden='true'></i> " + data);
                success = true;
            }
            if (success) {
                // update progress bar
                processedPanels++;
                const progressWidth = Math.round((100 / numberOfPanels) * processedPanels);
                panelsProgressBar.css({width: progressWidth + "%"});
                panelsProgressBar.attr("aria-valuenow", progressWidth);
                // panelsProgressBar.html(processedPanels + " / " + numberOfPanels);
                panelsProgressBar.html(progressWidth + "%");
            }
            if (success && processedPanels == numberOfPanels) {
                $("#gofastSpaceMembersTable").KTDatatable().setActiveAll(false);
                GofastKDataTableReload("gofastSpaceMembersTable");
            }
          });
        }
      }
})(jQuery, Gofast, Drupal);
