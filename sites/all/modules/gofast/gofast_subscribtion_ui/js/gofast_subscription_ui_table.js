(function ($, Gofast, Drupal) {

  'use strict';

  Drupal.behaviors.gofastSubscriptionsTable = {
      attach: function(context, settings){
          if(document.querySelector('#gofastSubscriptionsTable') != null){
              if(!document.querySelector('#gofastSubscriptionsTable').classList.contains('processed')){
                  let table = document.querySelector('#gofastSubscriptionsTable')
                  table.classList.add('processed')
                  GofastSubscriptionsTable.init(table)
                  
                  $("#gofastSubscriptionsTable").on("datatable-on-init", function(){
                    Drupal.attachBehaviors();
                    
                    $("#subscriptionSelectedElementsDelete").click(Gofast.subscriptionDeleteSelected);
                    $('select[name="frequency_mass_actions"]').on("change", Gofast.subscriptionUpdateSelected)
                  });
                  
                  $("#gofastSubscriptionsTable").on("datatable-on-layout-updated", function(){
                    Drupal.attachBehaviors();
                    $("#gofastSubscriptionsTable").trigger("datatable-on-check");
                  });
                  
                  $("#gofastSubscriptionsTable").on("datatable-on-check", function(){
                    var records = Gofast.subscriptionTable.getSelectedRecords();
                    $("#subscriptionSelectedElementsCount").text(records.length);
                    
                    if(records.length > 0){
                        $("#subscriptionSelectedElementsActions").removeClass("d-none");
                    }else{
                        $("#subscriptionSelectedElementsActions").addClass("d-none");
                    }
                  });
                  
                  $("#gofastSubscriptionsTable").on("datatable-on-uncheck", function(){
                    //Trigger checked event
                    $("#gofastSubscriptionsTable").trigger("datatable-on-check");
                  });
                  $("#gofastSubscriptionsTable").on("datatable-on-update-perpage datatable-on-goto-page", function(){
                    GofastKDataTableReload();
                  });
                  $("#gofastSubscriptionsTable").on("datatable-on-ajax-done", function(event){
                    setTimeout(function(){
                        $("#gofastSubscriptionsTable form").each(function(){
                            var is_comment = $(this).attr("id").startsWith("gofast-subscription-ui-comments-frequency-form");
                            var form_base_id = is_comment ? "gofast-subscription-ui-comments-frequency-form" : "gofast-subscription-ui-frequency-form";
                            var select_id =  is_comment ? "edit-frequency-comment" : "edit-frequency";
                            var select_name = is_comment ? "frequency_comment" : "frequency";
                            var number_form = $(this).attr("id").replace(form_base_id, "");
                            var ajax_event = {};
                            ajax_event.callback = is_comment ? "gofast_subscription_ui_comments_frequency_update" : "gofast_subscription_ui_frequency_update";
                            ajax_event.event =  "change";
                            ajax_event.selector = "#" + select_id + number_form;
                            ajax_event.submit = { _triggering_element_name: select_name };
                            ajax_event._triggering_element_name = select_name;
                            ajax_event.url =  "/system/ajax";
                            ajax_event.wrapper = select_name;

                            if(typeof Drupal.settings.ajax == "undefined"){
                                Drupal.settings.ajax = {};
                            }
                            Drupal.settings.ajax[select_id + number_form] = ajax_event;
                        });

                        Drupal.attachBehaviors();
                    }, 1000);
                  });
              }
          }

      }
  };

  var GofastSubscriptionsTable = function() {
      // Private functions
      let _tableEl;
      let _bodyHeight;
      let _columns;

      //Init table
      var initTable = function(table) {
          _tableEl = table
          _bodyHeight = table.parentElement.offsetHeight - 50;

          let jsonColumns = _tableEl.dataset.columns
          _columns = JSON.parse(jsonColumns)
          
        //   let jsonData = _tableEl.dataset.data
        //   _data = JSON.parse(jsonData)

          _crateTable(table)
      };

      var _crateTable = function(table){
          Gofast.subscriptionTable = $(table).KTDatatable({
              data: {
                  type: 'remote',
                  source: {
                    read: {
                        url: window.origin + "/subscriptions_async",
                        method: 'GET',
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
                  serverPaging: true,
                  serverFiltering: false,
                  serverSorting: true,
                  autoColumns: false,
              },

              // layout definition
              layout: {
                  class: 'GofastTable',
                  height: _bodyHeight,
                  scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
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
                      selector: {
                          class: 'kt-checkbox--solid'
                      },
                      field: 'checkbox',
                      title: '',
                      autoHide: false,
                      width: 25,
                  },
                  {
                      field: 'type',
                      title: _columns.type,
                      autoHide: false,
                      template: function(data) {
                        if (data.length == 0) return "-";
                        return data.type
                      },
                      sortCallback: function(data, sort, column) {
                        return $(data).sort(function (a, b) {
                            if (sort == 'asc'){ 
                                // ensure "Étiquettes" is sorted with the e and "ùnico" with the u
                                return a.type.localeCompare(b.type);
                            } else {
                                return b.type.localeCompare(a.type);
                            }
                        })
                      },
                      width: 100,
                  },
                  {
                    field: 'name',
                    title: _columns.name,
                    autoHide: false,
                    template: function(data) {
                        if (data.length == 0) return "-";
                        const nameElement = document.createElement("textarea");
                        nameElement.innerHTML = data.name;
                        return nameElement.value;
                    },
                    width: 340,
                  },
                  {
                    field: 'frequency',
                    title: _columns.frequency,
                    autoHide: false,
                    sortable: false,
                    template: function(data) {
                        if (data.length == 0) return "-";
                        return data.frequency
                    },
                    width: 180,
                  },
                  {
                    field: 'comments_frequency',
                    title: _columns.comments_frequency,
                    autoHide: false,
                    sortable: false,
                    template: function(data) {
                        if (data.length == 0) return "-";
                        return data.comments_frequency
                    },
                    width: 180,
                  },
                  {
                    field: 'actions',
                    title: _columns.actions,
                    autoHide: false,
                    sortable: false,
                    template: function(data) {
                        if (data.length == 0) return "-";
                        return data.actions
                    },
                    width: 60,
                  },
              ],
          });
      }

      return {
          init: function(table){
              initTable(table);
          },
      };
  }();
  
  Gofast.subscriptionDeleteSelected = function(){
    var selected = Gofast.subscriptionTable.getSelectedRecords();
    
    selected.each(function(k,elem){
        let selectedHref = $(elem).find('td[data-field="actions"]').find("a.flag-action").attr("href");
        //Delete the element
        $.get(selectedHref);
    })
  }
  
  Gofast.subscriptionUpdateSelected = function(){
    var selected = Gofast.subscriptionTable.getSelectedRecords();
    var value = $(this).val();
    var global_input = $(this);
    
    if(value == 10){
        return;
    }
    
    selected.each(function(k,elem){
        //Update the element
        $(elem).find('td[data-field="frequency"]').find("select").val(parseInt(value)).change();
        global_input.val(10).change();
    })
  }
})(jQuery, Gofast, Drupal);
