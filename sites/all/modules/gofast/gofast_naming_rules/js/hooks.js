
/**
 * @file
 *
 * Implements JS hooks related to naming rules.
 *
 */
(function ($, Gofast, Drupal) {
    Gofast = Gofast || {};
    Gofast.hooks = Gofast.hooks || {};


    // this hook will prevent metadata update if it returns false
    Gofast.hooks.beforePostMetadata =  Gofast.hooks.beforePostMetadata || [];
    // trigger warning modal just before field_category update if the category has a naming rule
    Gofast.hooks.beforePostMetadata.push(async function(elem, value) {
        const field_name = elem.attr("name");
        // we're interested only in field_category update
        if (field_name != "field_category") {
            return true;
        }
        const nid = elem.attr("data-id");
        try {
            // next block will not be executed until this promise has either been resolved or rejected (e. g. field update will not occur before resolve or reject is executed)
            await new Promise(async (resolve, reject) => {
                let data = "";
                // this endpoint returns an empty string if the category has no naming rule, otherwise it will return the warning modal template
                await $.post("/taxonomy/naming_rules/apply_category_confirm", {value, nid}).done(response => data = response);
                // no naming rule: go on with the field update
                if (!data) {
                    resolve();
                    return true;
                }
                data = JSON.parse(data);
                // has naming rule: open modal and prevent close on blur (because the user MUST trigger one of the events below to end this block)
                Gofast.modal(data.theme, data.message);
                Drupal.CTools.Modal.closeOnBlur(false);
                // end the promise on modal buttons click
                const closeEvent = $(".modal button.close").on("click", () => {
                    reject();
                    $(".modal button.close").off("click", closeEvent);
                });
                $("#modal-footer #apply_category_confirm").on("click", () => {
                    // grey out title until it is reloaded with the right name and tooltip by the polling
                    const titleElement = $("#title-reference");
                    const crumbTitle = titleElement.find(".breadcrumb-item");
                    const editableCrumb = crumbTitle.find(".EditableInput__value");
                    document.querySelector(".breadcrumb-item .EditableInput__value")
                    editableCrumb.css("pointer-events", "none");
                    crumbTitle.css("cursor", "not-allowed");
                    crumbTitle.addClass("text-muted");
                    titleElement.prepend($("<div class='spinner spinner-sm mr-6'>"));
                    // forward submitting of category save
                    resolve();
                    Drupal.CTools.Modal.dismiss();
                });
                $("#modal-footer #apply_category_cancel").on("click", () => {
                    reject();
                    Drupal.CTools.Modal.dismiss();
                });
            });
        } catch (e) {
            // return false if the promise has been rejected so the field update is aborted
            return false;
        }
        // otherwise return true
        return true;

    });
})(jQuery, Gofast, Drupal);