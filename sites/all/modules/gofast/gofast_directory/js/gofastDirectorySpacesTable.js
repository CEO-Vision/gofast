(function ($, Gofast, Drupal) {

    'use strict';

    // 8 columns in main header means array length must be of 8
    const DirectorySpacesTableSubheaderElements = [
        "",
        "",
        '<input type="text" name="name" class="form-control GofastDirectorySpacesFilter__name"  placeholder="' + Drupal.t("Enter space name") + '" />',
        '<select name="type" class="form-control selectpicker" style="display: block !important;"><option value="">' +
        Drupal.t("All") +
        '</option><option value="group">' +
        Drupal.t("Group") +
        '</option><option value="organisation">' +
        Drupal.t("Organisation") +
        '</option><option value="extranet">' +
        Drupal.t("Extranet") +
        '</option><option value="public">' +
        Drupal.t("Public") +
        '</option></select>',
        '',
        '',
        '',
        '',
        '<div class="GofastDirectoryFilterButtons d-flex ml-auto flex-column align-items-center" style="gap: .5rem; transform: translateY(-1rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
        '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
        '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
        '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
        '</button></div>',
    ];

    Drupal.behaviors.gofastDirectorySpaces = {
        attach: function(context, settings){
            if(document.querySelector('#gofastDirectorySpacesTable') != null){
                if(!document.querySelector('#gofastDirectorySpacesTable').classList.contains('processed')){
                    let table = document.querySelector('#gofastDirectorySpacesTable')
                    table.classList.add('processed')
                    GofastDirectoryTable.init(table)
                    if (typeof ResizeObserver != "undefined") {
                        const directoryResizeObserver = new ResizeObserver(function(entries) {
                            GofastRefreshKDataTableSubheader("gofastDirectorySpacesTable", "DirectorySpacesFilterForm");
                        });
                        directoryResizeObserver.observe(document.querySelector("#gofastDirectorySpacesTable"));
                        $("#gofastDirectorySpacesTable").on("datatable-on-destroy", function(){
                            directoryResizeObserver.disconnect();
                        });
                    }
                    $("#gofastDirectorySpacesTable").on("datatable-on-layout-updated", function(){
                        GofastAddKDataTableSubheader("gofastDirectorySpacesTable", "DirectorySpacesFilterForm", DirectorySpacesTableSubheaderElements);
                    });
                    $("#gofastDirectorySpacesTable").on("datatable-on-init", function(){
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
        let _selection;
        // space table

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
                            url: window.origin + "/directory/directory_async/space",
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
                    saveState : false,
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
                                },
                                tablet: {
                                    layout: 'compact',
                                },
                                mobile: {
                                    layout: 'compact'
                                }
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
                        width: 200,
                        template: function(data) {
                            return ('<a data-toggle="popover" data-trigger="hover" data-html="true" data-content="<div class=\'py-2 px-4\'>' + data.breadcrumb.replaceAll("\n", "").replaceAll("\"", "'") + '</div>" class="gofast__popover btn-link text-nowrap" href="/node/'+data.nid+'">'+data.name+'</a>')
                        },
                    },
                    {
                        field: "type",
                        title: _columns.type,
                        overflow: 'visible',
                        autoHide: false,
                        template: function(data) {
                            if(data.type == "group"){
                                var text = Drupal.t('Group');
                            }else if(data.type == "organisation"){
                                var text = Drupal.t('Organisation');
                            }else if(data.type == "extranet"){
                                var text = Drupal.t('Extranet');
                            }else if(data.type == "public"){
                                var text = Drupal.t('Public');
                            }
                            return "<span>" + text + "</span>";
                        },
                    },
                    {
                        field: "nb_contents",
                        title: _columns.contents,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center'
                    },
                    {
                        field: "nb_members",
                        title: _columns.members,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center'
                    },
                    {
                        field: "nb_admins",
                        title: _columns.admins,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center',
                        template: function(data){
                            var popoverContent = '';
                            data.nb_admins.admins.forEach(function(value,index){
                                const picture = value.picture;
                                const firstName = value.firstname + " ";
                                const lastName = value.lastname;
                                const uid = value.uid;
                                popoverContent += "<div class=\"d-flex align-items-center p-5\"> <div class=\"symbol symbol-35 flex-shrink-0 mr-4\"> <img alt=\"Pic\" src=\"" + picture + "\"> </div> <a href=\"/user/" + uid + "\" class=\"font-size-lg\">" + firstName.replace(/[\'\"]/g, '') + " " + lastName.replace(/[\'\"]/g, '') + "</a> </div> ";
                            });
                            const nb_admins = data.nb_admins.nb_admins;
                            
                            return "<a tabindex='" + data.nid + "' class=\"admin_popover\" type=\"button\" data-toggle=\"popover\" data-trigger=\"focus\" data-placement=\"left\" data-html=\"true\" data-content='" + popoverContent + "'>" + nb_admins + "  <i class=\"fa fa-caret-down ml-2\" style=\"color: #3699FF\"></i></a>";
                        }
                    },
                    {
                        field: "nb_pendings_members",
                        title: _columns.pendings,
                        overflow: 'visible',
                        autoHide: false,
                        textAlign: 'center'
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
                    {
                        field: 'actions',
                        title: "",
                        width: 0,
                        autoHide: false,
                        sortable: false,
                        template: function(data) {
                            return data.actions;
                        },
                    },
                    {           
                        field: 'gid',
                        title: '',
                        autoHide: false,
                        width: 0,
                        sortable: false,
                        template: function(data) {
                            return '<span style="display:none;" class="gid_span" value="'+ data.nid +'">' + data.nid + '</span>'
                        },
                    },
                ],
            });
            
            
            
            $("#gofastDirectorySpacesTable").on("datatable-on-check", function(event,args){
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                   var gid = $(this).find(".gid_span").html();                
                   _selection += gid+"-";  
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

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectorySpacesTable");
            });
                  
            $("#gofastDirectorySpacesTable").on("datatable-on-uncheck", function(event,args){
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                    var gid = $(this).find(".gid_span").html();
                    _selection += gid+"-";
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

                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectorySpacesTable");
            });

            const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

            for(const interferringEvent of interferringEvents) {
             $("#gofastDirectorySpacesTable").on(interferringEvent, function(event, data){
                GofastRefreshKDataTableSubheader("gofastDirectorySpacesTable", "DirectorySpacesFilterForm");
                
                var selected_records = _table.getSelectedRecords();
                _selection = "";
                selected_records.each(function( index ) {
                    var gid = $(this).find(".gid_span").html();
                    _selection += gid+"-";
                });
               
                GofastTriggerKDataTableMegaDropdown(selected_records,"gofastDirectorySpacesTable");
                if (interferringEvent == "datatable-on-ajax-done") {
                    $(".datatable-subheader").show();
                    Gofast.removeLoading();
                }
             });
            }

            // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
            const formInterval = setInterval(function() {
                if (!$('#DirectorySpacesFilterForm').length) {
                    return;
                }
                $('#DirectorySpacesFilterForm').on('submit', function(e){
                    e.preventDefault()
                    let filterArr = $(this).serializeArray()
                    let filter = Object.create({})

                    filterArr.forEach(fil => {
                        if(!!fil.value){
                            let att = fil.name
                            filter[att] = fil.value
                        }
                    })

                    $(".datatable-pager-link[data-page='1']:not('.database-pager-link-inactive')")[0].click();

                    _table.setDataSourceParam("query", filter)
                    _table.load()
                })

                $('#DirectorySpacesFilterForm').on('reset', function(e){
                    $(e.currentTarget['status']).val('').selectpicker("refresh")
                    _table.setDataSourceParam("query", {})
                    _table.load()
                })
                clearInterval(formInterval);
            }, 100);

            Drupal.attachBehaviors();
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
                initTable(table);
            },

        };
    }();

})(jQuery, Gofast, Drupal);
