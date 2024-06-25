 <?php
  $node_path = gofast_cmis_space_get_webdav_path_node_page($node->nid);
  if(gofast_essential_is_essential() && !gofast_mobile_is_phone()){
    print theme('essential_ajax_file_browser', ['node' => $node]);
  } else {

    print theme('ajax_file_browser', ["node" => $node]);
  }
  ?>

 <script>
   //Tells the page template that we will handle navigation
   Gofast.mobileNavigationHandled = true;

   //Triger the file browser navigation when we are ready and connected
   function triggerNavigation() {
    if (typeof Gofast.ITHit === "undefined" || typeof Gofast.ITHit.Uploader === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
       setTimeout(triggerNavigation, 1000);
     } else { //Ready !
       //Get params from URL
       var params = {};
       if (location.search) {
         var parts = location.search.substring(1).split('&');

         for (var i = 0; i < parts.length; i++) {
           var nv = parts[i].split('=');
           if (!nv[0]) continue;
           params[nv[0]] = nv[1] || true;
         }
       }
       Gofast.ITHit.loadTree();
       if (typeof params.path !== "undefined") { //Path provided, navigate to path
        if(Gofast._settings.isMobileDevice){
          Gofast.ITHitMobile.navigate(params.path);
        } else {
          Gofast.ITHit.navigate(params.path, false, false, null, null, null, "backgroundNavigation");
        }
      } else if(!isNaN(location.pathname.split("/")[2]) && Gofast._settings.isEssential){
        let targetHash = location.hash || "#ogdocuments";
        Gofast.Essential.navigateFileBrowser(location.pathname.split("/")[2], targetHash, "load")
      } else { 
        if(Gofast._settings.isEssential){
          if(window.location.pathname == "/activity"){ // Navigate to /Sites to have no selected space on activity page load
            Gofast.ITHit.navigate("/Sites", false, false, null, null, null, "backgroundNavigation");
          }
        } else {
          if(Gofast._settings.isMobileDevice){
            Gofast.ITHitMobile.navigate("<?php print $node_path; ?>");
          } else {
            Gofast.ITHit.navigate("<?php print $node_path; ?>", false, false, null, null, null, "backgroundNavigation"); //No path provided, navigate to default path
          }
        }
      }
       //Attach events to the browser
       Gofast.ITHit.attachBrowserEvents();
       //Init queue mechanism if needed
       if (Gofast.ITHit.activeQueue === false) {
         Gofast.ITHit.refreshQueue();
       }
       //Set drag and drop zone for upload
       Gofast.ITHit.Uploader.DropZones.RemoveById('file_browser_full_files');
       Gofast.ITHit.Uploader.DropZones.RemoveById('file_browser_full_upload_table');

       Gofast.ITHit.Uploader.DropZones.AddById('file_browser_full_files');
       Gofast.ITHit.Uploader.DropZones.AddById('file_browser_full_upload_table');
       //Add events handlers for upload queue
       Gofast.ITHit.attachUploadEvents();
     }
   }
   triggerNavigation();

   <?php
    $is_new = abs($node->created - time()) < 10;
    if ($_POST['gofast_og_wrong_path'] && !$is_new) {
      $_POST['gofast_og_wrong_path'] = FALSE;
    ?>
     Gofast.toast(Drupal.t("Unable to find this space's folder", {}, {
       context: 'gofast:ajax_file_browser'
     }), "warning");
        setTimeout(function () {
                jQuery("#dropdown-node-dropdown").prop("disabled",true).css("background-color","grey");
                jQuery(".breadcrumb-item .EditableInput__value").replaceWith("<div></div>");
          }, 2000);
    
     
   <?php } ?>
 </script>
