jQuery("document").ready(function () {
  var waitSearchAvailable = setInterval(function () {
    if (
      typeof Gofast.gofast_workflow_search_execute === "function" &&
      typeof Gofast._settings === "object" &&
      typeof Gofast._settings.gofast === "object"
    ) {
      Gofast.gofast_workflow_search();
      clearInterval(waitSearchAvailable);
    }
  }, 200);

  //Not really proud of it but it works
  function resizeIframe(obj) {
    Gofast.intervalidentifier = 0;
    var iframeResizeInterval = setInterval(function () {
      Gofast.intervalidentifier++;

      if (Gofast.intervalidentifier > 10) {
        clearInterval(iframeResizeInterval);
      }

      if(obj.contentWindow !== null){
        obj.style.height = obj.contentWindow.document.body.scrollHeight + "px";
      }
    }, 500);
  }

  if (jQuery(".breadcrumb-gofast").length == 0) {
    jQuery("#ajax_content").prepend(
      '<div class="breadcrumb gofast breadcrumb-gofast">' +
        Drupal.t(
          "Workflows dashboard",
          {},
          { context: "gofast:gofast_workflows" }
        ) +
        "</div>"
    );
  }
});
