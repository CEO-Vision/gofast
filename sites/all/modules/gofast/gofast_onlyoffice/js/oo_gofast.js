/**
 * This file is not loaded Drupal-side but embedded in OO index.html
 */
window.addEventListener("message", ({data}) => {
    // Hide everything but the document content
    if (data.op == "hideToolbar") {
        const partsToHide = ["#app-title", "#toolbar", "#left-menu", "#right-menu", "#statusbar", "#id_panel_top", "#id_panel_left"];
        for (const partToHide of partsToHide) {
            document.querySelector(partToHide).style.display = "none";
        }
        document.querySelector(".layout-item.middle").style.top = 0;
        document.querySelector(".layout-item.middle").style.height = "100%";
    }
    // Click on a dialog button
    if (data.op == "confirm") {
        const waitForConfirmButtonInterval = setInterval(() => {
            const confirmButton = document.querySelector(".modal [result='" + data.button + "']");
            if (!confirmButton) {
                return;
            }
            clearInterval(waitForConfirmButtonInterval);
            confirmButton.click();
        }, 100);
    }
})