(function ($, Gofast, Drupal) {
    
    'use strict';
    
    Drupal.behaviors.gofastAdminLDAP = {
        attach: function(context, settings){
            if(document.querySelector('#gofastAdminLDAPTable') != null){
                if(!document.querySelector('#gofastAdminLDAPTable').classList.contains('processed')){
                    let table = document.querySelector('#gofastAdminLDAPTable');
                    table.classList.add('processed');
                    GofastAdminLDAPTable.init(table);
                }
            }
            
        }
    };
    
    var GofastAdminLDAPTable = function() {
        // Private functions
        let _tableEl;
        let _bodyHeight;
        let _table;
        let _columns;
        
        // user table
        var initTable = function(table) {
            
            _tableEl = table;
            _bodyHeight = table.parentElement.offsetHeight - 50;
            
            let jsonColumns = _tableEl.dataset.columns;
            _columns = JSON.parse(jsonColumns);
            
            let isSelect = 'disabled';
            //Define columns to fill them with content depending on the server
            let selector = {
                field: 'selector',
                title: '#',
                sortable: false,
                type: 'number',
                width: 30,
                selector: true,
                textAlign: 'center',
                autoHide: false,
                template: function(data) {
                    //If we return an empty tpl, it is considered as invalid by the plugin and we'll get the default checkbox that we can select
                    //Thus we return a valid template for unselectable users so they won't be checked if we press checkall, plus the fact that they're hidden and disabled
                    let chkbox = '';
                    let no_chkbox = '<label hidden class="checkbox checkbox-single checkbox-disabled"><input type="checkbox" value="">&nbsp;<span></span></label>';
                    return (data.imported == "") ? chkbox : no_chkbox;
                }
                
            };
            let imported = {
                field: 'imported',
                title: 'imported',
                autoHide: false,
                template: function(data) {
                    return data.imported;
                }
            };
            
            let cols = [];
            cols.push(selector);
            for(const [key, value] of Object.entries(_columns)) {
                const f = {
                    field: key,
                    title: key,
                    autoHide: false,
                    width: (key=="cn" || key=="telephoneNumber") ? 200 : (key=="mail") ? 300 : (key=="title") ? 200 : 130
                };
                cols.push(f);
            }
            cols.push(imported);
            _crateTable(table, cols);
        };
        
        var _crateTable = function(table, cols){
            
            _table = $(table).KTDatatable({
                data: {
                    type: 'remote',
                    source: {
                        read: {
                            url: window.origin + "/admin/config/gofast/ldap/entries",
                            method: 'GET',
                            map: function(raw) {
                                // sample data mapping
                                var dataSet = raw;
                                if (typeof raw.data !== 'undefined') {
                                    dataSet = raw.data;
                                }
                                return dataSet;
                            }
                        }
                        
                    },
                    pageSize: 20,
                    serverPaging: false,
                    serverFiltering: true,
                    serverSorting: false,
                    autoColumns: false
                },
                
                // layout definition
                layout: {
                    class: 'GofastTable GofastTable--scroll',
                    height: _bodyHeight,
                    scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
                    footer: false // display/hide footer
                },
                
                // column sorting
                sortable: true,
                search: {
                    input: $('#LDAPAdminEntriesText'),
                },
                pagination: true,
                
                search: {
                    input: $('#kt_datatable_search_query'),
                    delay: 400,
                    key: 'generalSearch'
                },
                // columns definition
                columns: cols,
                
            });
            
            function countSelectedEntries() {
                let size = _table.getSelectedRecords().length;    
                $("#gofast_adminLdap_importRowsLength").html(size + " " + Drupal.t(' items selected', {}, {context: 'gofast:ldap'}));
                // disable import button if no item is select
                if (size == 0) {
                    $("#gofast_adminLdap_importRows").addClass("disabled").css('cursor', 'not-allowed');
                } else {
                    $("#gofast_adminLdap_importRows").removeClass("disabled").css('cursor', 'auto');
                }
            }
            countSelectedEntries();
            
            $('#LDAPAdminEntriesFilterForm').on('submit', function(e){
               e.preventDefault();
               let filter_select = $('#LDAPAdminEntriesSelect').val();
               let filter_value = $('#LDAPAdminEntriesText').val();
               let filter = Object.create({});
               filter[filter_select] = filter_value;
                _table.setDataSourceParam("query", filter);
                _table.load();
            });
            
            $('#LDAPAdminEntriesFilterForm').on('reset', function(e){
                _table.setDataSourceParam("query", {});
                _table.load();
            });
            
            $('#gofastAdminLDAPTable').on('datatable-on-check datatable-on-uncheck datatable-on-layout-updated', function(e) {
                countSelectedEntries()
            });
            
            $('#gofast_adminLdap_importRows').on('click', function(e) {
                var returnArray = [];
                returnArray["dataSet"] = _table.dataSet;
                returnArray["selectedUsers"] = [];
                
                let selected = _table.getSelectedRecords();
                $(selected).each(function(index) {
                    let selected_username = $(this).find('[data-field=uid]').children().text();
                    returnArray["selectedUsers"].push(selected_username);  
                    
                    /*let importedDom = $(this).find('.gofastImported');
                    if(!importedDom.length) {
                        let selected_username = $(this).find('[data-field=uid]').children().text();
                        returnArray["selectedUsers"].push(selected_username);  
                    }*/
                });
                $.ajax({
                    type: 'POST',
                    url: "/admin/config/gofast/ldap/import",
                    data: {
                        "users" : JSON.parse(JSON.stringify(returnArray['dataSet'])),
                        "selected" : JSON.parse(JSON.stringify(returnArray['selectedUsers']))
                    }
                })
                        .done(function (data) {
                            _table.setDataSourceParam("query", {});
                            Gofast.processAjax("/admin/config/gofast/ldap/manage");
                            $("#gofast_adminLdap_importRowsLength").html('');
                });
            });
            
        };
        
        return {
            
            init: function(table){
                initTable(table);
            }
        };
    }();
    
    
    
})(jQuery, Gofast, Drupal);
