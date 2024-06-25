(function ($, Gofast, Drupal) {
    "use strict";
  
    let GofastCategoriesTableElements = [];
    let GofastCategoriesDefaultAction = "";
    let GofastCategoriesTexts = {};
    let GofastCategoriesSetFilters = {};

    // Schemas
    const _getCategoriesDefinitions = function (columns) {
      return [
        {
          column: {
            selector: {
              class: "kt-checkbox--solid",
            },
            field: "checkbox",
            title: "",
            autoHide: false,
            width: 10,
            sortable: false,
          },
          filter: "",
        },
        {
          column: {
            field: "",
            title: "",
            autoHide: false,
            width: 30,
            overflow: "visible",
            sortable: false,
          },
          filter: "",
        },
        {
          column: {
            field: "name",
            title: columns.name,
            autoHide: false,
            width: 120,
            template: function (data) {
              return data.is_translated == 1
                ? data.name
                :  "<i data-toggle=\"popover\" data-trigger=\"hover\" data-html=\"true\" data-content=\"<div class='p-2'>"
                + GofastCategoriesTexts.not_translated
                + "</div>\" class=\"fa fa-exclamation-triangle text-danger\"></i>&nbsp;"
                + data.name
            },
          },
          filter: '<input type="text" name="catname" class="form-control GofastCategoriesFilter__catname" placeholder="' + Drupal.t("Search") + '"/>',
        },
        {
          column: {
            field: "is-standard",
            title: columns.standard,
            autoHide: false,
            textAlign: "center",
            width: 60,
            attr: {
              "data-nowrap": "nowrap"
            },
            template: function (data) {
              return data.is_standard == 1
                ? "<i data-toggle=\"popover\" data-trigger=\"hover\" data-html=\"true\" data-content=\"<div class='p-2'>"
                  + GofastCategoriesTexts.standard_category
                  + "</div>\" class=\"fas fa-check-circle text-success\"></i>"
                : "<i class=\"fas fa-times-circle text-danger\"></i>";
            },
          },
          filter: '<label class="checkbox gofast-switch-icon mr-3 switch switch-icon switch-sm" for="filter-standard-cat"><input class="form-checkbox" type="checkbox" id="filter-standard-cat" name="standard" data-default="on"><span data-toggle="tooltip" title="' + Drupal.t("If disabled, only non-standard categories will be shown", {}, {context: "gofast:gofast_taxonomy"}) + '" class="has-width m-auto"></span></label>',
        },
        ...(columns.dua ? [{
          column: {
            field: "dua",
            title: columns.dua,
            autoHide: false,
            width: 280,
            textAlign: "center",
            template: function (data) {
              return data.retention;
            }
          },
          filter: '<label class="checkbox gofast-switch-icon mr-3 switch switch-icon switch-sm" for="filter-dua-cat"><input class="form-checkbox" type="checkbox" id="filter-dua-cat" name="dua"><span data-toggle="tooltip" title="' + Drupal.t("If enabled, only categories with defined retention rules will be shown", {}, {context: "gofast:gofast_taxonomy"}) + '" class="has-width m-auto"></span></label>',
        }] : []),
        ...(columns.rules ? [
          {
            column: {
              field: "naming-rules",
              title: columns.rules,
              autoHide: false,
              width: 280,
              textAlign: "center",
              template: function (data) {
                return data.rules;
              },
            },
            filter: "",
          }
        ] : []),
        // {
        //   column: {
        //       field: "criticity",
        //       title: columns.criticity,
        //       autoHide: false,
        //       textAlign: "center",
        //       template: function (data) {
        //         return data.criticity;
        //       },
        //   },
        //   filter: "",
        // },
        {
          column: {
            field: "docs",
            title: columns.docs,
            autoHide: false,
            textAlign: "center",
            width: 60,
            template: function (data) {
              return data.docs_count;
            },
          },
          filter: "",
        },
        {
          column: {
            field: "spaces",
            title: columns.in,
            autoHide: false,
            textAlign: "center",
            width: 60,
            attr: {
              "data-nowrap": "nowrap"
            },
            template: function (data) {
              return data.spaces;
            },
          },
          filter: '<input type="text" class="form-control form-control-tags GofastCategoriesFilter__spacename js-tagify" id="edit-list-spaces" name="ac-list-tags-spaces" data-get-spaces placeholder="' + Drupal.t("Filter by space(s)") + '"/>',
        },
        {
          column: {
            field: "actions",
            title: "",
            sortable: false,
            autoHide: false,
            width: 40,
            textAlign: "left",
            sortable: false,
            template: function (data) {
              return "<div class=\"d-none\">" + data.actions + "</div>";
            },
          },
          filter: '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
          '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
          '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
          '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
          "</button></div>",
        },
        {
          column: {
            field: "tid",
            title: "",
            autoHide: false,
            width: 0,
            sortable: false,
            template: function (data) {
              return (
                '<span style="display:none;" class="tid_span" value="' +
                  data.tid +
                '">' +
                  data.tid +
                "</span>"
              )
            },
          },
          filter: "",
        },
      ]
    }

    var GofastCategoriesTable = (function () {
      // Private functions
      let _tableEl;
      let _table;
      let _columns;
      let _selection;
      var initTable = function (table) {
        _tableEl = table;
        let jsonColumns = _tableEl.dataset.columns;
        _columns = JSON.parse(jsonColumns);
        GofastCategoriesTableElements = _getCategoriesDefinitions(_columns).filter(Object).map((el) => el.filter);
        _createTable(table);
      };
  
      var _createTable = function (table) {
        _table = $(table).KTDatatable({
          data: {
            type: "remote",
            source: {
              read: {
                url: window.origin + "/gofast/admin/directory/categories",
                params: {
                  query: {
                    standard: "on"
                  }
                },
                method: "GET",
                map: function (raw) {
                  if (raw == null) {
                    return [];
                  }
                  var dataSet = raw;
                  if (typeof raw.data !== "undefined") {
                    dataSet = raw.data;
                  }
                  if (typeof raw.default_action_button !== "undefined") {
                    GofastCategoriesDefaultAction = raw.default_action_button;
                  }
                  if (typeof raw.texts !== "undefined") {
                    GofastCategoriesTexts = raw.texts;
                  }
                  if (typeof raw.filters !== "undefined") {
                    GofastCategoriesSetFilters = raw.filters;
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
          columns: _getCategoriesDefinitions(_columns).filter(Object).map((el) => el.column),
          rows: {
            autoHide: false,
            beforeTemplate: function (row, data, index) {
              row.attr("data-tid", data.tid);
            },
          },
        });
      };

      // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
      let formAttempts = 0;
      const formInterval = setInterval(function() {
        formAttempts ++;
        if (formAttempts > 100) {
          clearInterval(formInterval);
          return;
        }
        if (!$("#GofastCategoriesFilterForm").length) {
          return;
        }
        $("#GofastCategoriesFilterForm").on("submit", function (e) {
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

          _table.setDataSourceParam("query", filter);
          _table.reload();
        });
        clearInterval(formInterval);
      }, 100);

      // tagify being rendered by a behaviour, we have to wait for it to be rendered as well
      let tagifyAttempts = 0;
      const tagifyInterval = setInterval(function() {
        tagifyAttempts ++;
        if (tagifyAttempts > 100) {
          clearInterval(tagifyInterval);
          return;
        }
        if (!window.tagify || !window.tagify["ac-list-tags-spaces"]) {
          return;
        }
        clearInterval(tagifyInterval);
        window.tagify["ac-list-tags-spaces"].on("add remove focus blur", (e) => {
          // when tagify sizing is altered, autoscroll to always have the input visible
          window.tagify["ac-list-tags-spaces"].DOM.scope.nextSibling.nextSibling.scrollIntoView({behavior: "smooth", block: "end"});
          // we want the filters to remain at the same position when resizing the tbody
          $("#gofastCategoriesTable").attr("data-prevent-refresh", "true");
          // adjust length of tbody so we don't have a vertical scrollbar in the middle of the page after having scrolled horizontally
          if (e.type == "blur") {
            $("#gofastCategoriesTable tbody").width($("#gofastCategoriesTable table").width());
            GofastRefreshKDataTableSubheader("gofastCategoriesTable", "GofastCategoriesFilterForm");
          } else {
            $("#gofastCategoriesTable tbody").width($("#gofastCategoriesTable thead form").width());
          }
        });
      }, 100);

      $("#gofastCategoriesTable").on("datatable-on-check", function (event, args) {
        $(".kt-checkbox--solid input[disabled]").prop("checked", false);
        var selected_records = _table.getSelectedRecords().filter(function (record) {
            return (
              $(this).find(".kt-checkbox--solid input[disabled]").length == 0
            );
          });
        _selection = "";
        selected_records.each(function (index) {
          var tid = $(this).find(".tid_span").html();
          _selection += tid + "-";
        });
        _selection = _selection.slice(0, -1);

        $("#container-selected-items .navi-item .ctools-use-modal").each(
          function (index) {
            if ($(this).hasClass("default-action")) {
              return;
            }
            var href = $(this).attr("href");
            if (!href) {
              return;
            }
            var array_href = href.split("/");
            array_href[array_href.length - 1] = _selection;
            var new_href = array_href.join("/");
            $(this).attr("href", new_href);
            $(this).removeClass("ctools-use-modal-processed");
            $(this).off("click");
          }
        );

        GofastTriggerKDataTableMegaDropdown(selected_records, "gofastCategoriesTable", GofastCategoriesDefaultAction);
      });

      $("#gofastCategoriesTable").on("datatable-on-uncheck", function (event, args) {
        var selected_records = _table.getSelectedRecords();
        _selection = "";
        selected_records.each(function (index) {
          var tid = $(this).find(".tid_span").html();
          _selection += tid + "-";
        });

        $("#container-selected-items .navi-item .ctools-use-modal").each(
          function (index) {
            var href = $(this).attr("href");
            if (!href) {
              return;
            }
            var array_href = href.split("/");
            array_href[array_href.length - 1] = _selection;
            var new_href = array_href.join("/");
            $(this).attr("href", new_href);
            $(this).removeClass("ctools-use-modal-processed");
            $(this).off("click");
          }
        );

        GofastTriggerKDataTableMegaDropdown(selected_records,"gofastCategoriesTable", GofastCategoriesDefaultAction);
      });

      const interferringEvents = ["datatable-on-ajax-done", "datatable-on-goto-page", "datatable-on-update-perpage"];

      for(const interferringEvent of interferringEvents) {
       $("#gofastCategoriesTable").on(interferringEvent, function(event, data){
          GofastRefreshKDataTableSubheader("gofastCategoriesTable", "GofastCategoriesFilterForm");
          if (GofastCategoriesSetFilters) {
            for (const filter of Object.keys(GofastCategoriesSetFilters)) {
              $("#filter-" + filter + "-cat").prop("checked", true);
            }
          }

          if (!_table) {
            return;
          }

          var selected_records = _table.getSelectedRecords();
          GofastTriggerKDataTableMegaDropdown(selected_records,"gofastCategoriesTable", GofastCategoriesDefaultAction);

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
  
    Gofast.initCategoriesDirectory = function () {
        if (document.querySelector("#gofastCategoriesTable") == null) {
            return
        }
        if (
          !document
            .querySelector("#gofastCategoriesTable")
            .classList.contains("processed")
        ) {
          let table = document.querySelector("#gofastCategoriesTable");
          table.classList.add("processed");
          GofastCategoriesTable.init(table);
          if (typeof ResizeObserver != "undefined") {
            const directoryResizeObserver = new ResizeObserver(function (
              entries
            ) {
              GofastRefreshKDataTableSubheader(
                "gofastCategoriesTable",
                "GofastCategoriesFilterForm"
              );
            });
            directoryResizeObserver.observe(
              document.querySelector("#gofastCategoriesTable")
            );
            $("#gofastCategoriesTable").on("datatable-on-destroy", function () {
              directoryResizeObserver.disconnect();
            });
          }
          $("#gofastCategoriesTable").on("datatable-on-layout-updated", function () {
              GofastAddKDataTableSubheader("gofastCategoriesTable", "GofastCategoriesFilterForm", GofastCategoriesTableElements);
              // full reload = everything will be unchecked = we must update the total display accordingly
              if (typeof _table == "undefined") {
                _GofastKDataTableSelectCounter(0, "gofastCategoriesTable");
              }
              if (GofastCategoriesSetFilters) {
                for (const filter of Object.keys(GofastCategoriesSetFilters)) {
                  $("#filter-" + filter + "-cat").prop("checked", true);
                }
              }
              Drupal.attachBehaviors();
              Gofast.tour.attachFragment("triggerNamingRuleInput");
              $("[data-toggle='popover']").popover({
                  template: '<div class="popover" class="d-none" role="tooltip"><div class="arrow"></div><div class="popover-body overflow-auto max-h-250px"></div></div>'
              });
              $(".gofast-directory-spaces-popover[data-toggle='popover']").on("show.bs.popover", async function(e) {
                if ($(this).hasClass("processed")) {
                  return;
                }
                $(this).addClass("processed");
                const gids = $(this).attr("data-gids") ? $(this).attr("data-gids").split("-") : [];
                let breadcrumbs = "";
                const options = {'from_tooltip': true};
                for (const gid of gids) {
                  await $.get(location.origin + "/gofast/node-breadcrumb/" + gid + "?options=" + JSON.stringify(options), function(data) {
                    breadcrumbs += data;
                  });
                }
                $(this).attr("data-content", breadcrumbs);
                $(".gofast-directory-spaces-popover-content").parent().html(breadcrumbs);
              });
            }
          );
        }
    };
})(jQuery, Gofast, Drupal);
  