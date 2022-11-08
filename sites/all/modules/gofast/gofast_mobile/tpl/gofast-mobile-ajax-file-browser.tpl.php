<div id="file_browser_mobile_mobile_container" class="panel panel-default">
  <div id="file_browser_mobile_header" class="panel-body">
    <div id="file_browser_mobile_header_breadcrumb">
      <ul></ul>
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
</div>

<script>
              //Triger the mobile file browser navigation when we are ready and connected
              function triggerMobileNavigation(){
                if(typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false || typeof Gofast.ITHitMobile === "undefined"){ //Not yet ready
                  setTimeout(triggerMobileNavigation, 1000);
                }else{ //Ready !
                  Gofast.ITHitMobile.mobileVersion = true;
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
                  if(typeof params.path === "undefined"){ //No path provided, navigate to default path
                    Gofast.ITHitMobile.navigate(Gofast.ITHitMobile.currentPath, true);
                  }else{ //Path provided, navigate to path                  
                    Gofast.ITHitMobile.navigate(params.path, true);
                  }                  
                  //Attach browser events
                  Gofast.ITHitMobile.attachBrowserEvents();
                }
              }
              triggerMobileNavigation();
</script>