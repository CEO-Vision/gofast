(function ($, Gofast, Drupal) {
  "use strict";

  const GofastTagsTableElements = [
    "",
    "",
    '<input type="text" name="tagname" class="form-control GofastTagsFilter__tagname" placeholder="' +
      Drupal.t("Search") +
      '"/>',
    '<input type="text" class="form-control form-control-tags GofastTagsFilter__docname js-tagify" id="edit-list-documents" name="ac-list-tags-documents" data-node placeholder="' +
      Drupal.t("Filter by document(s)") +
      '"/>',
    '<div class="GofastDirectoryFilterButtons d-flex ml-auto mt-auto align-items-center" style="gap: .5rem; transform: translate(.5rem, -.5rem);"><button type="submit" class="btn btn-xs btn-primary btn-icon m-0">' +
      '<i class="fas fa-search" style="font-size: 12px !important;"></i>' +
      '</button><button type="reset" class="btn btn-xs btn-light btn-icon m-0">' +
      '<i class="fas fa-undo" style="font-size: 12px !important;"></i>' +
      "</button></div>",
  ];

  let GofastTagsDefaultAction = "";

  var GofastTagsTable = (function () {
    // Private functions
    let _tableEl;
    let _table;
    let _columns;
    let _selection;
    // tags table
    var initTable = function (table) {
      _tableEl = table;
      let jsonColumns = _tableEl.dataset.columns;
      _columns = JSON.parse(jsonColumns);
      // prevent KTDatatable setting title for all select inputs, including select filters
      $.fn.KTDatatable.defaults.translate.toolbar.pagination.items.default.select =
        "";
      _crateTable(table);
    };

    var _crateTable = function (table) {
      _selection = "";
      _table = $(table).KTDatatable({
        data: {
          type: "remote",
          source: {
            read: {
              url: window.origin + "/gofast/admin/directory/tags",
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
                  GofastTagsDefaultAction = raw.default_action_button;
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
        columns: [
          {
            selector: {
              class: "kt-checkbox--solid",
            },
            field: "checkbox",
            title: "",
            autoHide: false,
            width: 10,
          },
          {
            field: "",
            title: "",
            autoHide: false,
            width: 30,
            overflow: "visible",
            sortable: false,
          },
          {
            field: "tag_nam",
            title: _columns.name,
            autoHide: false,
            template: function (data) {
              return data.name;
            },
          },
          {
            field: "docs",
            title: _columns.docs,
            autoHide: false,
            textAlign: "center",
            template: function (data) {
              // let popoverContent = "";
              // data.documents.forEach(function(document) {
              //     const href = "/node/" + document.nid;
              //     const title = document.title.replace(/['"]/g, " ");
              //     popoverContent += "<div class=\"d-flex align-items-center p-2\"> <i class=\"" + document.icon + "\"></i>&nbsp;<a href=\"" + href + "\" class=\"font-size-lg\">" + title + "</a> </div> ";
              // });
              // return "<a tabindex='" + data.tid + "' data-toggle=\"popover\" data-trigger=\"focus\" data-placement=\"left\" data-html=\"true\" data-content='" + popoverContent + "'>" + data.qty + "  <i class=\"cursor-pointer fa fa-caret-down ml-2\" style=\"color: #3699FF\"></i></a>";
              return data.qty;
            },
            width: 150,
          },
          {
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
          {
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
              );
            },
          },
        ],
        rows: {
          autoHide: false,
          beforeTemplate: function (row, data, index) {
            row.attr("data-tid", data.tid);
          },
        },
      });

      // the form being rendered ad hoc, we have to wait for it to be rendered before we can attach events to it
      const formInterval = setInterval(function () {
        if (!$("#GofastTagsFilterForm").length) {
          return;
        }
        $("#GofastTagsFilterForm").on("submit", function (e) {
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

      $("#gofastTagsTable").on(
        "datatable-on-check",
        function (event, args) {
          $(".kt-checkbox--solid input[disabled]").prop("checked", false);
          var selected_records = _table
            .getSelectedRecords()
            .filter(function (record) {
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
              var array_href = href.split("/");
              array_href[array_href.length - 1] = _selection;
              var new_href = array_href.join("/");
              $(this).attr("href", new_href);
              $(this).removeClass("ctools-use-modal-processed");
              $(this).off("click");
            }
          );

          GofastTriggerKDataTableMegaDropdown(
            selected_records,
            "gofastTagsTable",
            GofastTagsDefaultAction
          );
        }
      );

      $("#gofastTagsTable").on(
        "datatable-on-uncheck",
        function (event, args) {
          var selected_records = _table.getSelectedRecords();
          _selection = "";
          selected_records.each(function (index) {
            var tid = $(this).find(".tid_span").html();
            _selection += tid + "-";
          });

          $("#container-selected-items .navi-item .ctools-use-modal").each(
            function (index) {
              var href = $(this).attr("href");
              var array_href = href.split("/");
              array_href[array_href.length - 1] = _selection;
              var new_href = array_href.join("/");
              $(this).attr("href", new_href);
              $(this).removeClass("ctools-use-modal-processed");
              $(this).off("click");
            }
          );

          GofastTriggerKDataTableMegaDropdown(
            selected_records,
            "gofastTagsTable",
            GofastTagsDefaultAction
          );
        }
      );

      const interferringEvents = [
        "datatable-on-ajax-done",
        "datatable-on-goto-page",
        "datatable-on-update-perpage",
      ];

      for (const interferringEvent of interferringEvents) {
        $("#gofastTagsTable").on(interferringEvent, function (event, data) {
          GofastRefreshKDataTableSubheader(
            "gofastTagsTable",
            "GofastTagsFilterForm"
          );

          var selected_records = _table.getSelectedRecords();
          _selection = "";
          selected_records.each(function (index) {
            var tid = $(this).find(".tid_span").html();
            _selection += tid + "-";
          });

          GofastTriggerKDataTableMegaDropdown(
            selected_records,
            "gofastTagsTable",
            GofastTagsDefaultAction
          );
        });
      }
    };

    return {
      init: function (table) {
        initTable(table);
      },
    };
  })();

  Gofast.initTagsDirectory = function () {
    if (document.querySelector("#gofastTagsTable") != null) {
      if (
        !document
          .querySelector("#gofastTagsTable")
          .classList.contains("processed")
      ) {
        let table = document.querySelector("#gofastTagsTable");
        table.classList.add("processed");
        GofastTagsTable.init(table);
        if (typeof ResizeObserver != "undefined") {
          const directoryResizeObserver = new ResizeObserver(function (
            entries
          ) {
            GofastRefreshKDataTableSubheader(
              "gofastTagsTable",
              "GofastTagsFilterForm"
            );
          });
          directoryResizeObserver.observe(
            document.querySelector("#gofastTagsTable")
          );
          $("#gofastTagsTable").on("datatable-on-destroy", function () {
            directoryResizeObserver.disconnect();
          });
        }
        $("#gofastTagsTable").on("datatable-on-layout-updated", function () {
            GofastAddKDataTableSubheader("gofastTagsTable", "GofastTagsFilterForm", GofastTagsTableElements);
            // full reload = everything will be unchecked = we must update the total display accordingly
            if (typeof _table == "undefined") {
              _GofastKDataTableSelectCounter(0, "gofastTagsTable");
            }
            Drupal.attachBehaviors();
            // $("[data-toggle='popover']").popover({
            //     template: '<div class="popover" role="tooltip"><div class="arrow"></div><div class="popover-body overflow-auto max-h-250px"></div></div>'
            // });
          }
        );

        $("#gofastTagsTable").on("datatable-on-init", function () {
          const pagerTitleInterval = setInterval(function () {
            if (!$(".datatable-pager-info button").length) {
              return;
            }
            $(".datatable-pager-info button").attr(
              "title",
              Drupal.t("Select page size")
            );
            clearInterval(pagerTitleInterval);
          }, 500);
        });
      }
    }
  };
  Gofast.renameTag = async function (tid) {
    let canEdit = false;
    await $.get(
      "/gofast/user/has/administer site configuration/permission",
      function (data) {
        canEdit = data;
      }
    );
    if (!canEdit) {
      Gofast.toast(
        Drupal.t(
          "You don't have the permission to rename tags",
          {},
          { context: "gofast:gofast_admin" }
        ),
        "warning"
      );
      return;
    }
    const element = $(
      "tr[data-tid='" + tid + "'] > [data-field='tag_nam'] > span"
    );
    const content = element.text();
    element.html("");
    GofastEditableInput(element[0], content, "text", {
      save: async (newName) => {
        await $.post("/taxonomy/1/tag/" + tid + "/edit", {
          name: newName,
        }).done(function (data) {
          Gofast.toast(
            Drupal.t(
              "Tag renamed successfully",
              {},
              { context: "gofast:gofast_admin" }
            ),
            "success"
          );
        });
      },
      programmaticTrigger: true,
      showConfirmationButtons:
        "tr[data-tid='" +
        tid +
        "'] > [data-field='tag_nam'] .EditableInput__input",
    });
    element
      .find(".EditableInput__value")
      .trigger("click", { programmaticTriggered: true });
  };
})(jQuery, Gofast, Drupal);
