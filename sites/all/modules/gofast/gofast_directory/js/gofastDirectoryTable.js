(function ($, Gofast, Drupal) {
    'use strict';

    Gofast = Gofast || {};

    Gofast.initPermissionsForm = function() {
        $('div.form-item-permissions-3administrator-bs-switch').after('<hr>');
        $('div.form-item-permissions-internal-bs-switch').after('<hr>');
        $('input#edit-permissions-4contributor-bs-switch').on('change', function() {
            if ($(this).prop('checked')) {
                $('input#edit-permissions-7business-administrator-bs-switch').prop('checked', false);
                $('input#edit-permissions-3administrator-bs-switch').prop('checked', false);
            }
        });
        $('input#edit-permissions-3administrator-bs-switch, input#edit-permissions-7business-administrator-bs-switch').on('change', function() {
            if ($(this).prop('checked')) {
                $('input#edit-permissions-4contributor-bs-switch').prop('checked', false);
            }
        });
        $('input#edit-permissions-internal-bs-switch').on('change', function() {
            if ($(this).prop('checked')) {
                $('input#edit-permissions-extranet-bs-switch').prop('checked', false);
            } else {
                $('input#edit-permissions-extranet-bs-switch').prop('checked', true);
            }
        });
        $('input#edit-permissions-extranet-bs-switch').on('change', function() {
            if ($(this).prop('checked')) {
                $('input#edit-permissions-internal-bs-switch').prop('checked', false);
            } else {
                $('input#edit-permissions-internal-bs-switch').prop('checked', true);
            }
        });
        // we have to select at least one permission between extranet and internal, which are strictly commutative
        $('input#edit-permissions-extranet-bs-switch').prop('checked', true);
    }

    window.GofastKDataTableReload = function(tableId) {
        $("#" + tableId + " thead tr:first-of-type th:nth-of-type(2)").html(""); // remove megacheckbox
        $(".datatable-subheader spacer:first-of-type").text(""); // remove megacheckbox counter
        $(".GofastTable.datatable").KTDatatable().reload();
    };

    window._GofastKDataTableSelectCounter = function(rowsCount, tableId) {
        const targetContainer = $("#" + tableId + " thead tr:nth-of-type(2) spacer:first-of-type");
        if (rowsCount === 0) {
            targetContainer.text("");
            return;
        }
        targetContainer.css({
            whiteSpace: "nowrap",
            display: "flex",
            margin: "auto",
        });
        targetContainer.text(rowsCount + " " + (rowsCount > 1 ? Drupal.t('elements') : Drupal.t('element')));
    };

    /**
     * pseudo-facade triggering the GofastRefreshKDataTableMegaDropdown global function accordingly to the given rows array state
     * @warning in order to be triggered correctly, this pseudo-facade must be called on both "datatable-check" and "dataTable-uncheck" events
     * @param {HTMLTableRowElement[]} rows 
     * @param {string} tableId 
     */
    window.GofastTriggerKDataTableMegaDropdown = function(rows, tableId) {
        _GofastKDataTableSelectCounter(rows.length, tableId);
        if (!rows.length) {
            _GofastRefreshKDataTableMegaDropdown(tableId, -2);
            return;
        }
        if (rows.length == 1) {
            _GofastRefreshKDataTableMegaDropdown(tableId, rows[0].dataset.row);
            return;
        }
        _GofastRefreshKDataTableMegaDropdown(tableId);
    }
    
    /**
     * directory dropdowns are hidden by default: regardless of their original location, this function shows them in the same spot to give the user the impression there is only one "mega" dropdown
     * @param {string} tableId | DOM ID of the Keen Datable
     * @param {number} rowId | if -1, looks for the bulk actions dropdown, if even less, clears the dropdown, otherwide looks for the dropdown in the row with the given rowId
     */
     window._GofastRefreshKDataTableMegaDropdown = function (tableId, rowId = -1) {
        const $targetContainer =  $("#" + tableId + " thead tr:first-of-type th:nth-of-type(2)");
        const targetWidth =  $("#" + tableId + " thead tr:nth-of-type(2) form > *:nth-of-type(2)").width();
        $targetContainer.html("");
        $targetContainer.width(targetWidth);
        if (rowId < -1) {
            return;
        }
        let $dropdownContainer = $("#container-selected-items");
        $dropdownContainer.hide()
        if (rowId > -1) {
            $dropdownContainer = $("#" + tableId + " tr[data-row='" + rowId + "'] [data-field='actions'] .dropdown");
            if (!$dropdownContainer.length) {
                $dropdownContainer = $("#" + tableId + " tr[data-row='" + rowId + "'] [data-field='actions'] .contextual-actions");
            }
            if (!$dropdownContainer.children().length) {
                return;
            }
            $dropdownContainer.hide();
        }
        const $dropdownContainerClone = $dropdownContainer.clone(true).width(targetWidth);
        $dropdownContainerClone.appendTo($targetContainer);
        $dropdownContainerClone.parent().find(".dropdown").css("cssText", "margin-left: 0 !important;");
        $targetContainer.css("font-weight", "400");
        $targetContainer.children().show();
        $targetContainer.find(".dropdown-menu").css("display", "");
        Drupal.attachBehaviors();
    }

    /**
     * refreshes layout of the Keen Datatable subheader, is called on subheader add but
     * @warning must also be called on the KDataTable "datatable-ajax-done" event
     * @param {string} tableId | DOM ID of the Keen Datable 
     * @param {string} formId | DOM ID of the form wrapping the subheader
     */
    window.GofastRefreshKDataTableSubheader = function (tableId, formId) {
        setTimeout(function() {
            const firstRow = $("#" + tableId + " tbody tr:first-of-type > td");
            // Keen may render thead with wider cells than tbody, that's why we make sure everythign is aligned
            const headerCellsWidth = $("#" + tableId + " thead tr:first-of-type th").map(function (i, el) {
                if (firstRow.length) {
                    el.style.width = getComputedStyle(firstRow[i]).width;
                    return parseInt(getComputedStyle(firstRow[i]).width);
                }
                return parseInt(getComputedStyle(el).width);
            });
            const formElements = $("#" + formId + " > *");
            for (let i = 0; i < formElements.length; i++) {
                if (formElements[i].classList.contains("GofastDirectoryFilterButtons")) {
                    continue;
                }
                // even if the form element collapses for some reason, we make sure the inputs will not collapse
                formElements[i].style.minWidth = (headerCellsWidth[i] - 10) + "px";
                formElements[i].style.maxWidth = (headerCellsWidth[i] - 10) + "px";
                formElements[i].style.marginRight = "10px";
                if (formElements[i].tagName == "INPUT") {
                    formElements[i].addEventListener("keydown", function(e) {
                        if (e.code == "Enter") {
                            $(".datatable-subheader form").submit();
                        }
                    });
                }
                if (formElements[i].querySelector(".input-group-text")) {
                    formElements[i].querySelector(".input-group-text").style.width = "auto";
                }
            }
            // remove classes KTDatatable add on sort which unexpectedly translate the subheader layout
            $(".datatable-subheader > th").attr("class", "");
            $(".datatable-subheader").css("visibility", "visible");
            $(".datatable-subheader .fa-search").attr("title", Drupal.t("Apply current filters")).tooltip();
            $(".datatable-subheader .fa-undo").attr("title", Drupal.t("Reset current filters")).tooltip();
            // this doesn't trigger the on-sort event, so we have to add a loader for this
            $(".datatable-subheader button[type='reset']").on("click", () => {
                $("#" + tableId + " thead tr:first-of-type th:nth-of-type(2)").html(""); // remove megacheckbox
                $(".datatable-subheader spacer:first-of-type").text(""); // remove megacheckbox counter
                $("[data-toggle='date-tooltip']").tooltip("dispose");
                $("[data-toggle='date-tooltip']").datepicker("clearDates");
                $(".datatable-subheader").hide();
                // reset values and submit again (more reliable to submit again than counting on some input listeners)
                $(".datatable-subheader select").val(null);
                $(".datatable-subheader input").val(null);
                $("#" + formId).submit();  
            });
        }, 250);
    }

    /**
     * this adds a subheader to a Keen Datatable, but may work for other purposes
     * @warning to be triggered correctly, this function must be called on the KDataTable "datatable-on-layout-updated" event
     * @param {string} tableId | DOM ID of the Keen Datable 
     * @param {string} formId | DOM ID of the form wrapping the subheader
     * @param {string[]} templateElements | array of template elements: number of template elements _must_ be the same as the number of columns, submit button(s) may be included, template elements values must be raw HTML strings and if a column is skipped just put an empty string instead
     */
    window.GofastAddKDataTableSubheader = function (tableId, formId, templateElements) {
        if ($("#" + tableId + " thead #" + formId).length) {
            return;
        }
        let subheaderTemplate = '<tr class="datatable-subheader" style="border-bottom: 1px solid #EBEDF3; visibility: hidden;"><th><form id="' + formId + '" class="pb-2 d-flex align-items-center" style="max-height: 50px;">';
        for (const element of templateElements) {
            if (element === "") {
                subheaderTemplate += "<spacer></spacer>";
                continue;
            }
            subheaderTemplate += element;
        }
        subheaderTemplate += '</form></th></tr>';
        $("#" + tableId + " thead").append(subheaderTemplate);
        $("#" + tableId + " thead tr:first-of-type").css("border-bottom", "none");
        $("#" + tableId + " thead tr:nth-of-type(2)").css({display: "flex", justifyContent: "start", width: "100%"});
        $("#" + tableId + " tbody").css("height", "calc(100% - 110px)");

        var arrows;
        if (KTUtil.isRTL()) {
            arrows = {
                leftArrow: '<i class="la la-angle-right"></i>',
                rightArrow: '<i class="la la-angle-left"></i>'
            }
        } else {
            arrows = {
                leftArrow: '<i class="la la-angle-left"></i>',
                rightArrow: '<i class="la la-angle-right"></i>'
            }
        }

        setDatepickerL18n();
        $('.GofastDateRange').datepicker({
            language: window.GofastLocale,
            locale : window.GofastLocale,
            format: window.GofastConvertDrupalDatePattern("bootstrapDate"),
            rtl: KTUtil.isRTL(),
            todayHighlight: true,
            templates: arrows,
            clearBtn: true,
            autoclose: true,
        }).on("changeDate", function(e) {
            if (typeof e.date === "undefined") {
                $(e.target).tooltip("dispose");
                return;
            }
            const $dateInput = $(e.target)
            const inputName = $dateInput.attr("name");
            const $siblingInput = $("[name='" + inputName.replace("start", "end") + "']");
            // if we set a startDate and there is an associated endDate input, we want the endDate to be set one day later rather than the same day
            if (inputName.startsWith("start") && $siblingInput.length && typeof e.date != "undefined") {
                const oneDayLater = new Date(e.date.getTime() + 86400000);
                $siblingInput.datepicker("setDate", oneDayLater);
            }
            $dateInput.tooltip("dispose");
            $dateInput.attr("title", $dateInput.val());
            $dateInput.attr("data-toggle", "date-tooltip");
            $dateInput.tooltip();
        }).on("show", function(e) {
            // prevent datepicker from overflowing on smaller screens
            $(".datepicker:visible").css("z-index", 10000);
            e.target.style.display = "static";
            const distanceFromRight = $(window).width() - ($(e.target).offset().left + $(e.target).width());
            if (distanceFromRight < 150) {
              $(".datepicker:visible").css("left", (parseInt($(".datepicker:visible").css("left")) + 144) + "px");
            }
        });

        // When clicking on the dropdown menu, remove display: none from filters
        $("#" + tableId ).on('click', function() {
            const $subHeaderContainer =  $("#" + tableId + " thead");
            $subHeaderContainer.find(".dropdown-menu").css("display", "");
        });

        GofastRefreshKDataTableSubheader(tableId, formId);
    }
})(jQuery, Gofast, Drupal);
