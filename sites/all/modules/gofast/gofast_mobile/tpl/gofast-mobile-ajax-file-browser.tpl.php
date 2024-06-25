<div id="file_browser_mobile_mobile_container" class="panel panel-default">
  <div id="file_browser_mobile_header" class="panel-body">
    <div id="file_browser_mobile_header_breadcrumb" class="d-flex justify-content-between align-items-center">
      <ul></ul>
      <button id="file_browser_mobile_upload_button" class="d-none btn btn-icon btn-primary btn-circle btn-sm" onclick="$('#mobile_ajax_file_browser_upload_input').trigger('click');">
          <i class="fas fa-plus"></i>
      </button>
    </div>
    <div id="file_browser_mobile_mobile_toolbar_search" class="input-group input-group-sm">
      <span class="input-group-addon" id="sizing-addon3"><span class="icon glyphicon glyphicon-search" aria-hidden="true"></span></span>
      <input id="file_browser_mobile_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
      <div id="file_browser_mobile_toolbar_refresh_group" class="btn-group">
        <button title="<?php echo t('Refresh'); ?>" id="file_browser_mobile_tooolbar_refresh" type="button" class="btn btn-default btn-sm dropdown-toggle" ><i class="fa fa-refresh" aria-hidden="true"></i></button>
      </div>
    </div>
  </div>
  <div id="file_browser_mobile_files" class="panel-body">
    <table id="file_browser_mobile_files_table" class="table mobile-table" style="width:100%;">
    </table>
  </div>
  <div id="file_browser_mobile_queue" class="panel-body" style="width:100%;">
  </div>
  <input class="d-none" type="file" id="mobile_ajax_file_browser_upload_input">
</div>

<script>
  //Trigger the mobile file browser navigation when we are ready and connected
  function triggerMobileNavigation(){
    if(typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false || typeof Gofast.ITHitMobile === "undefined"){ //Not yet ready
      setTimeout(triggerMobileNavigation, 1000);
    }else{ //Ready !
      Gofast.ITHitMobile.mobileVersion = true;
      //Get params from URL
      let searchParams = new URLSearchParams(location.search);
      if(searchParams.has("path")){
        Gofast.ITHitMobile.navigate(searchParams.get("path"));
      } else {
        if (typeof Gofast.get("space") == "string") {
          Gofast.ITHitMobile.navigate(Gofast.get("space"));
        } else { 
          Gofast.ITHitMobile.navigate("/Sites"); //No path provided, navigate to default path
        }                
      }
      //Attach browser events
      Gofast.ITHitMobile.attachBrowserEvents();
      Gofast.ITHit.UploaderMobile.Inputs.AddById('mobile_ajax_file_browser_upload_input');
    }
  }
  triggerMobileNavigation();
</script>