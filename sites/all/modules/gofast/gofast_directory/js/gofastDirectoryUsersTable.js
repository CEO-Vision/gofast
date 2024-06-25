(function ($, Gofast, Drupal) {

    'use strict';

    // 8 columns in main header means array length must be of 8
    const DirectoryUsersTableSubheaderElements = [
        "",
        "",
        '<input type="text" name="lastname" class="form-control GofastDirectoryUsersFilter__lastname" placeholder="' + Drupal.t("Enter lastname") + '"/>',
        '<input type="text" name="firstname" class="form-control GofastDirectoryUsersFilter__firstname" placeholder="' + Drupal.t("Enter firstname") + '"/>',
        '<input type="text" name="entity" class="form-control GofastDirectoryUsersFilter__entity" placeholder="' + Drupal.t("Enter entity") + '"/>',
        '<select name="role" class="form-control selectpicker"><option value="">' +
        Drupal.t("All") +
        '</option><option value="3">' +
        Drupal.t("Super administrator", {}, { context: "gofast:gofast_directory" }) +
        '</option>><option value="7">' +
        Drupal.t("User support", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="4">' +
        Drupal.t("Standard", {}, { context: "gofast:gofast_directory" }) +
        '</option></select>',
        '<select name="type" class="form-control selectpicker"><option value="">' +
        Drupal.t("All") +
        '</option><option value="1">' +
        Drupal.t("Internal", {}, { context: "gofast:gofast_user" }) +
        '</option>><option value="2">' +
        Drupal.t("External", {}, { context: "gofast:gofast_user" }) +
        '</option></select>',
        '<div class="input-daterange input-group GofastDateRange GofastDirectoryUsersFilter__created" data-field="created"><input type="text" class="form-control" name="startLogin" style="font-size: 12px; padding: 3px;" /><div class="input-group-append"><span class="input-group-text" style="padding: 1px;"></span></div><input type="text" class="form-control" name="endLogin" style="font-size: 12px; padding: 3px;"/></div>',
        '<div class="input-daterange input-group GofastDateRange GofastDirectoryUsersFilter__created" data-field="created"><input type="text" class="form-control" name="startCreated" style="font-size: 12px; padding: 3px;" /><div class="input-group-append"><span class="input-group-text" style="padding: 1px;"></span></div><input type="text" class="form-control" name="endCreated"style="font-size: 12px; padding: 3px;" /></div>',
        '<select name="status" class="form-control selectpicker" style="display: block !important;"><option value="">' +
        Drupal.t("All") +
        '</option><option value="0">' +
        Drupal.t("Blocked", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="1">' +
        Drupal.t("Disabled", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="2">' +
        Drupal.t("Activated", {}, { context: "gofast:gofast_directory" }) +
        '</option><option value="3">' +
        Drupal.t("Standby", {}, { context: "gofast:gofast_directory" }) +
        '</option></select>',
        '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
        '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
        '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
        '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
        '</button></div>',
    ];

    Drupal.behaviors.gofastDirectoryUsers = {
        attach: function(context, settings){
            if(document.querySelector('#gofastDirectoryUsersTable') != null){
                if(!document.querySelector('#gofastDirectoryUsersTable').classList.contains('processed')){
                    let table = document.querySelector('#gofastDirectoryUsersTable')
                    table.classList.add('processed')
                    GofastDirectoryTable.init(table)
                    // supported by most browsers since 2019, so we check in case an older browser is used
                    // this is far less expensive than a MutationObserver
                    if (typeof ResizeObserver != "undefined") {
                        const directoryResizeObserver = new ResizeObserver(function(entries) {
                            GofastRefreshKDataTableSubheader("gofastDirectoryUsersTable", "DirectoryUserFilterForm");
                        });
                        directoryResizeObserver.observe(document.querySelector("#gofastDirectoryUsersTable"));
                        $("#gofastDirectoryUsersTable").on("datatable-on-destroy", function(){
                            directoryResizeObserver.disconnect();
                        });
                    }
                    $("#gofastDirectoryUsersTable").on("datatable-on-layout-updated", function(){
                        GofastAddKDataTableSubheader("gofastDirectoryUsersTable", "DirectoryUserFilterForm", DirectoryUsersTableSubheaderElements);
                    });
                    $("#gofastDirectoryUsersTable").on("datatable-on-init", function(){
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

    var GofastDirectoryTable = function() {
        // Private functions
        let _tableEl;
        let _bodyHeight;
        let _table;
        let _columns;
        let _selection;
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
            _selection = "";
            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/directory/directory_async/user",
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
                    serverPaging: true,
                    serverFiltering: true,
                    serverSorting: true,
                    autoColumns: false,
                },
                
                // layout definition
                layout: {
                    class: 'GofastTable GofastTable--scroll h-100', // h-100 is important since it enforces the right initial sizing for the container inside which the flex flow will operate
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
                        field: 'picture',
                        title: '',
                        autoHide: false,
                        width: 40,
                        sortable: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            let picture = ''
                            if (data.picture) {
                                output = `<span class="symbol symbol-40"><img src="${data.picture}"></span>`
                            } else {

                                picture = '<span class="symbol-label"><i class="fas fa-user"></i></span>'

                                if(data.firstname && data.lastname){
                                    let symbol = data.firstname.slice(0,1).toUpperCase() + " " + data.lastname.slice(0,1).toUpperCase()
                                    picture = '<span class="symbol-label"> ' + symbol + '</span>'
                                }
                                var output = '<div class="d-flex align-items-center">'
                                                    + '<div class="symbol symbol-30 flex-shrink-0">'
                                                        + picture
                                                    + '</div>'
                                                + '</div>';
                            }

                            return output;
                        },
                    },
                    {
                        field: 'lastname',
                        title: _columns.lastname ,
                        autoHide: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            return '<a class="btn-link text-nowrap" href="/user/' + data.uid + '"> ' + data.lastname + '</a>'
                        },
                    },
                    {
                        field: 'firstname',
                        title: _columns.firstname ,
                        autoHide: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            return '<a class="btn-link text-nowrap" href="/user/' + data.uid + '"> ' + data.firstname + '</a>';
                        },
                    },
                    {
                        field: 'entity',
                        title: _columns.entity,
                        autoHide: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            return ('<span data-toggle="popover" data-trigger="hover" data-placement="top" title="' + data.entity + '" class="gofast__popover text-nowrap">'+ data.entity +'</span>');
                        }
                    },
                    {
                        field: 'role',
                        title: _columns.role,
                        autoHide: false,
                        width: 150,
                        template: function(data){
                            if (!data || data.length == 0) return "-";
                            let rolesTag = "<span>";
                            for (let role of data.roles) {
                                rolesTag += "<span class='badge badge-pill badge-light' style='width: max-content;'><span class='text-truncate'>" + role + "</span></span>";
                            }
                            rolesTag += "</span>";
                            return rolesTag;
                        },
                        sortCallback: function(data, sort, column) {
                            if (data.length == 0) return "-";
                            const mapProfileRidToImportance = {3: 0, 7: 1, 4: 2};
                            return $(data).sort(function (a, b) {
                                if (sort == 'asc'){
                                    return mapProfileRidToImportance[parseInt(a.role_id)] - mapProfileRidToImportance[parseInt(b.role_id)];
                                } else {
                                    return mapProfileRidToImportance[parseInt(b.role_id)] - mapProfileRidToImportance[parseInt(a.role_id)];
                                }
                            })
                        },
                    },
                    {
                        field: 'type',
                        title: _columns.type,
                        autoHide: false,
                        template: function(data){
                            if (!data || data.length == 0) return "-";
                            if (data.type) {
                                return "<span class='badge badge-pill badge-dark'>" + Drupal.t("External", {}, {context: "gofast:gofast_user"}) + "</span>";
                            }
                            return "<span class='badge badge-pill badge-secondary'>" + Drupal.t("Internal", {}, {context: "gofast:gofast_user"}) + "</span>";
    
                        },
                    },
                    {
                        field: 'login',
                        title: _columns.login,
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            return '<span>' + (parseInt(data.login) > 0 ? window.GofastFormatAsDrupalDate(data.login * 1000) : Drupal.t("Never logged in")) + '</span>';
                        },

                    },
                    {
                        field: 'created',
                        title: _columns.created,
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            return '<span>' + window.GofastFormatAsDrupalDate(data.created * 1000) + '</span>';
                        },

                    },
                    {
                        field: 'status',
                        title: _columns.status,
                        autoHide: false,
                        width: 80,
                        template: function(data) {
                            if (!data || data.length == 0) return "-";
                            let tem = ''
                            if(data.status.value == "2") {
                                tem = '<span class="label label-primary label-dot mr-2"></span><span class="font-weight-bold text-primary">' + data.status.label + '</span>';
                                } else if(data.status.value == "0") {
                                    if(data.standby.value == 1){
                                        tem = '<span class="label label-danger label-dot mr-2"></span><span class="font-weight-bold text-danger">' + data.standby.label + '</span>';
                                    }else{
                                        tem = '<span class="label label-danger label-dot mr-2"></span><span class="font-weight-bold text-danger">' + data.status.label + '</span>';
                                    }
                                } else {
                                    tem ='<span class="label label-warning label-dot mr-2"></span><span class="font-weight-bold text-warning">' + data.status.label + '</span>';
                                }

                            return tem
                        }
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
                ],
                rows: {
                    autoHide: false,
                    afterTemplate: function(row, data, index) {
                        if (!data || data.length == 0) return;
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
                    _table.spinnerCallback(true)
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
                    if(filter.startLogin) filter.startLogin = moment(filter.startLogin, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.endLogin) filter.endLogin = moment(filter.endLogin, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.startCreated) filter.startCreated = moment(filter.startCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
                    if(filter.endCreated) filter.endCreated = moment(filter.endCreated, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
    
                    _table.setDataSourceParam("query", filter)
                    _table.load()
                })
                $('#DirectoryUserFilterForm').on('reset', function(e){
                    $(e.currentTarget['status']).val('').selectpicker("refresh")
                    _table.setDataSourceParam("query", {})
                    _table.load()
                })
                clearInterval(formInterval);
            }, 100);

            $("#gofastDirectoryUsersTable").on("datatable-on-check", function(event,args){
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

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryUsersTable");
                if (selected_records.length) {
                    // disable delete action if one among checked user(s) never logged in
                    const selectedLoginValues = _table.getRecord(selected_records[0].dataset.row).getColumn("login").getValue();
                    if (!selectedLoginValues.includes(Drupal.t("Never logged in"))) {
                        $("#gofastDeleteUserAction").addClass("disabled");
                    }
                }
           });
                  
           $("#gofastDirectoryUsersTable").on("datatable-on-uncheck", function(event,args){
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

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryUsersTable");
           });

           const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

           for(const interferringEvent of interferringEvents) {
            $("#gofastDirectoryUsersTable").on(interferringEvent, function(event, data){
                GofastRefreshKDataTableSubheader("gofastDirectoryUsersTable", "DirectoryUserFilterForm");
                
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                   var uid = $(this).find(".uid_span").html();
                   _selection += uid+"-";  
                });
               
               
                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectoryUsersTable");
                if (interferringEvent == "datatable-on-ajax-done") {
                    $(".datatable-subheader").show();
                    Gofast.removeLoading();
                }
            });
           }
        }

        return {

            init: function(table){
                initTable(table)
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
            $("#gofastDirectoryUsersTable").KTDatatable().setActiveAll(false);
            GofastKDataTableReload("gofastDirectoryUsersTable");
        }
      });
    }
  }

})(jQuery, Gofast, Drupal);
