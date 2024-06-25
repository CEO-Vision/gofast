
(function ($, Gofast, Drupal) {
    "use strict";

    // This array will hold the filters for this directory
    let gofastAuditTableElements = [];

    // Map special behaviors to related audit types
    const hasExport = ["site"];
    const hasInputs = ["site", "space"];
    let hasSetInputs = false;    
    // When an input has dynamic options, we have to parse them and put them in the input: these are the handlers responsible for this, sorted by input type
    const inputHandlers = {
      select: function(name, data) {
        let select = '<select name="' + name + '" class="form-control selectpicker GofastAuditFilterForm__' + name + '" >';
        select += '<option value="">' + Drupal.t("All") + '</option>';
        for (var [value, string] of Object.entries(data)) {  
          if(name === "event_type"){
            string = string.join(";");
            select += '<option value="' + string + '">' + value + '</option>';
          } else {
            select += '<option value="' + value + '">' + string + '</option>';
          }
        }
        select += '</select>';
        return select;
      }
    }

    // Schemas (return definitions of columns and filters in one single object)
    const _getAuditDefinitions = function(columns, auditType = "site") {
      return {
        date: {
          column: {
            field: "date",
            title: columns.date,
            autoHide: false,
            template: function (data) {
              return `<span style="font-family: 'Segoe UI';">${data.date}</span>`;
            },
          },
          filter: '<div class="input-daterange input-group GofastDateRange GofastAuditFilterForm__date" data-field="timestamp"><input type="text" class="form-control" name="startDate" style="font-size: 12px; padding: 3px;" /><div class="input-group-append"><span class="input-group-text" style="padding: 1px;"></span></div><input type="text" class="form-control" name="endDate" style="font-size: 12px; padding: 3px;"/></div>',
        },
        login: {
          column: {
            field: "login",
            title: columns.login,
            autoHide: false,
            textAlign: "center",
            template: function (data) {
              return data.name;
            },
          },
          filter: '<input type="text" name="login" class="form-control GofastAuditFilterForm__login" placeholder="' + Drupal.t("Enter login") + '"/>',
        },
        displayname: {
          column: {
            field: "displayname",
            title: columns.displayname,
            autoHide: false,
            textAlign: "center",
            template: function (data) {
              return data.displayname;
            }
          },
          filter: '<input type="text" name="displayname" class="form-control GofastAuditFilterForm__displayname" placeholder="' + Drupal.t("Enter first name or surname") + '"/>',
        },
        title: {
          column: {
            field: "title",
            title: columns.title,
            autoHide: false,
            textAlign: "center",
            template: function (data) {
              const href = (data.href ?? `/node/${data.nid}`)
              return data.title ? `<a class="text-truncate" title="${data.title}" href="${href}">${data.title}</a>` : "-";
            },
          },
          filter: '<input type="text" name="title" class="form-control GofastAuditFilterForm__title" placeholder="' + Drupal.t("Enter entity name") + '"/>',
        },
        details: {
          column: {
            field: "", // left empty in order not to show misleading arrow
            title: columns.details,
            autoHide: false,
            width: 60,
            textAlign: "center",
            sortable: false,
            template: function (data) {
              return data.details || "-";
            },
          },
          filter: '',
        },
        eventtype: {
          column: {
            field: "eventtype",
            title: columns.eventtype,
            autoHide: false,
            width: auditType == "node" ? 180 : 220,
            textAlign: "center",
            template: function (data) {
              return `<span class="w-100 label label-inline label-light-primary font-weight-bold h-100"><div class="text-truncate" title="${data.translated_event_type}">${data.translated_event_type}</div></span>`;
            },
          },
          filter: 'event_type',
        },
        type: {
          column: {
            field: "type",
            title: columns.type,
            autoHide: false,
            textAlign: "center",
            template: function (data) {
              return data.translated_type ? `<span class="w-100 label label-inline label-light-primary font-weight-bold h-100"><div class="text-truncate" title="${data.translated_type}">${data.translated_type}</div></span>` : "-";
            },
          },
          filter: 'type',
        },
        actions: {
          column: {
            field: "actions",
            title: "",
            sortable: false,
            autoHide: false,
            width: 40,
            textAlign: "left",
            sortable: false,
          },
          filter: '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
          '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
          '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
          '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
          '</button></div>',
        }
      };
    }

    // There are several types of audits (site, space, node): this function gets the audit definitions and keeps only the elements relevant to the target audit type
    const getAuditDefinitionByType = function(auditType, columns) {
      const auditDefinitions = _getAuditDefinitions(columns, auditType);
      const auditDefinitionsByType = {
        "site": [auditDefinitions.date, auditDefinitions.login, auditDefinitions.displayname, auditDefinitions.title, auditDefinitions.details, auditDefinitions.eventtype, auditDefinitions.type, auditDefinitions.actions],
        "node": [auditDefinitions.date, auditDefinitions.login, auditDefinitions.eventtype],
      };
      // for now these types have the same columns and filters, but it may change in the future
      auditDefinitionsByType["space"] = auditDefinitionsByType.site;
      return auditDefinitionsByType[auditType];
    }

    const gofastAuditTable = (function () {
      // Private attributes
      let _tableEl;
      let _table;
      let _columns;
      let _auditType;
      let _auditEntityId;
      const initTable = function (table) {
        _tableEl = table;
        let jsonColumns = _tableEl.dataset.columns;
        _columns = JSON.parse(jsonColumns);
        let auditType = _tableEl.dataset.type;
        _auditType = auditType;
        let auditEntityId = _tableEl.dataset.etid;
        _auditEntityId = auditEntityId;
        // Init definition of filtering inputs
        gofastAuditTableElements = getAuditDefinitionByType(_auditType, _columns).map(el => el.filter);
        // Hide filtering inputs if needed
        if (hasInputs.indexOf(_auditType) < 0) {
          _tableEl.classList.add("no-datatable-subheader");
        }
        _createTable(table);
      };

      var _createTable = function (table) {
        _table = $(table).KTDatatable({
          data: {
            type: "remote",
            source: {
              read: {
                url: window.origin + "/gofast/audit/get/" + _auditType + "/" + _auditEntityId,
                method: "GET",
                map: function (raw) {
                  if (raw == null) {
                    return [];
                  }
                  // keep track of last query for export
                  if (hasExport.indexOf(_auditType) >= 0) {
                    let queryString = "sort[field]=" + raw.meta.field + "&sort[sort]=" + raw.meta.sort;
                    for (const [filterName, filterValue] of Object.entries(raw.filters)) {
                      queryString += "&query[" + filterName + "]=" + filterValue
                    }
                    $("#audit_export_xls_button > a").attr("data-query", queryString);
                  }
                  var dataSet = raw;
                  if (typeof raw.data !== "undefined") {
                    dataSet = raw.data;
                  }
                  // inputs with dynamic options
                  if (raw.inputs?.length && !hasSetInputs) {
                    hasSetInputs = true;
                    for (const input of raw.inputs) {
                      const { name, type, data } = input;
                      const index = gofastAuditTableElements.indexOf(name);
                      gofastAuditTableElements[index] = inputHandlers[type](name, data)
                    }
                    GofastAddKDataTableSubheader("gofastAuditTable", "GofastAuditFilterForm", gofastAuditTableElements);
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
            class: "GofastTable GofastTable--scroll h-100",
            scroll: false, // enable/disable datatable scroll both horizontal and vertical when needed.
            footer: false, // display/hide footer
            icons: {
              sort: {
                asc: "fa fa-chevron-up",
                desc: "fa fa-chevron-down",
              },
            },
          },
          // column sorting
          sortable: true,

          pagination: true,

          translate: {
            records: {
              processing: Drupal.t("Please wait..."),
              noRecords: Drupal.t("No records found"),
            },
            toolbar: {
              pagination: {
                items: {
                  default: {
                    first: Drupal.t("First"),
                    prev: Drupal.t("Previous"),
                    next: Drupal.t("Next"),
                    last: Drupal.t("Last"),
                    more: Drupal.t("More pages"),
                    input: Drupal.t("Page number"),
                    select: Drupal.t("Select page size"),
                  },
                  info: Drupal.t(
                    "Displaying {{start}} - {{end}} of {{total}} records"
                  ),
                },
              },
            },
          },

          // columns definition
          columns: getAuditDefinitionByType(_auditType, _columns).map(el => el.column),
        });
      };

      // the form being rendered a bit later, we have to wait for it to be rendered before we can attach events to it
      const formInterval = setInterval(function () {
        if (!$("#GofastAuditFilterForm").length) {
          return;
        }
        $(".datatable-subheader button[type='reset']").on("click", function (e) { // reset button
          e.preventDefault();
          _table.setDataSourceParam('pagination', Object.assign({}, _table.getDataSourceParam('pagination'), { page: 1 }));
          _table.reload();
        });
        $("#GofastAuditFilterForm").on("submit", function (e) {
          e.preventDefault();
          _table.spinnerCallback(true)
          let filterArr = $(this).serializeArray();
          let filter = Object.create({});

          filterArr.forEach((fil) => {
            if (!!fil.value) {
              let att = fil.name;
              filter[att] = fil.value;
            }
          });

          // don't submit if date values are incomplete
          const dateValues = [{start: filter.startDate, end: filter.endDate}];
          for (const dateValue of dateValues) {
              if ((dateValue.start && !dateValue.end) || (!dateValue.start && dateValue.end)) {
                  Gofast.toast(Drupal.t("Please fill in both start and end dates", {}, {context: "gofast:gofast_directory"}), "error");
                  return;
              }
          }

          // We have to convert the date string value into a timestamp before submission, so the server will be able to handle the filtering request
          if(filter.startDate) filter.startDate = moment(filter.startDate, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;
          if(filter.endDate) filter.endDate = moment(filter.endDate, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).valueOf() / 1000;

          _table.setDataSourceParam("query", filter);
          if(filter){_table.setDataSourceParam("currentPage", _table.getCurrentPage());} // set currentPage in the request if filter is applied GOFAST-11592
          _table.reload();
        });
        clearInterval(formInterval);
      }, 100);

      const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

      for(const interferringEvent of interferringEvents) {
       $("#gofastAuditTable").on(interferringEvent, function(event, data){
          GofastRefreshKDataTableSubheader("gofastAuditTable", "GofastAuditFilterForm");
          if (!_table) {
            return;
          }
          if (interferringEvent == "datatable-on-ajax-done") {
            $(".datatable-subheader").show();
            Gofast.removeLoading();
          }
       });
      }

      return {
        init: function (table) {
          initTable(table);
        },
      };
    })();
  
    Gofast.initAuditDirectory = function () {
        if (document.querySelector("#gofastAuditTable") == null) {
            return
        }
        if (!document.querySelector("#gofastAuditTable").classList.contains("processed")) {
          let table = document.querySelector("#gofastAuditTable");
          table.classList.add("processed");
          gofastAuditTable.init(table);
          if (typeof ResizeObserver != "undefined") {
            const directoryResizeObserver = new ResizeObserver(function (entries) {
              GofastRefreshKDataTableSubheader("gofastAuditTable","GofastAuditFilterForm");
            });
            directoryResizeObserver.observe(document.querySelector("#gofastAuditTable"));
            $("#gofastAuditTable").on("datatable-on-destroy", function () {
              directoryResizeObserver.disconnect();
            });
          }
          $("#gofastAuditTable").on("datatable-on-layout-updated", function () {
              GofastAddKDataTableSubheader("gofastAuditTable", "GofastAuditFilterForm", gofastAuditTableElements);
              Drupal.attachBehaviors();
              $("[data-toggle='popover']").popover({
                  template: '<div class="popover" class="d-none" role="tooltip"><div class="arrow"></div><div class="popover-body overflow-auto max-h-250px"></div></div>'
              });
            }
          );
        }
    };
})(jQuery, Gofast, Drupal);
  