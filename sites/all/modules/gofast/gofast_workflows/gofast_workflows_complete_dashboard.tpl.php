<div id="workflows-dashboard-search">
    <div class="panel panel-info">
        <div class="panel-heading" data-toggle="collapse" data-target="#workflows-dashboard-search-content" style="cursor: pointer;">
            <h3 class="panel-title"><?php echo t("Search workflows", array(), array('context' => "gofast:gofast_workflows")); ?> <i class="fa fa-caret-down"></i></h3>
        </div>
        <div id="workflows-dashboard-search-content" class="panel-body collapse">
            <?php echo $search_form; ?>
        </div>
    </div>

    <div class="panel panel-info">
        <div class="panel-heading">
            <h3 class="panel-title"><?php echo t("Search results", array(), array('context' => "gofast:gofast_workflows")); ?></h3>
        </div>
        <div class="panel-body">
            <iframe id="bonita_full_dashboard_search" style="width:100%;height:100%;min-height:800px;border:none;"></iframe>
        </div>
    </div>
</div>

<div id="workflows-dashboard-details">
    <div class="panel panel-info">
        <div class="panel-heading">
            <h3 class="panel-title"><?php echo t("Workflow tasks", array(), array('context' => "gofast:gofast_workflows")); ?></h3>
        </div>
        <div class="panel-body">
            <iframe id="workflows-dashboard-tasks" style="width:100%;height:100%;border:none;" onload="resizeIframe(this)"></iframe>
        </div>
    </div>
    
    <div class="panel panel-info">
        <div class="panel-heading">
            <h3 class="panel-title"><?php echo t("Documents in this workflow", array(), array('context' => "gofast:gofast_workflows")); ?></h3>
        </div>
        <div class="panel-body" id="workflows-dashboard-documents">
        </div>
    </div>
    
    <div class="panel panel-info">
        <div class="panel-heading">
            <h3 class="panel-title"><?php echo t("Workflow history", array(), array('context' => "gofast:gofast_workflows")); ?></h3>
        </div>
        <div class="panel-body">
            <iframe id="workflows-dashboard-history" style="width:100%;height:100%;border:none;" onload="resizeIframe(this)"></iframe>
        </div>
    </div>
</div>

<script>
    var waitSearchAvailable = setInterval(function(){
        if(typeof Gofast.gofast_workflow_search_execute === "function" && typeof Gofast._settings === "object" && typeof Gofast._settings.gofast === "object"){
            Gofast.gofast_workflow_search();
            clearInterval(waitSearchAvailable);
        }
    }, 200);

    //Not really proud of it but it works
    function resizeIframe(obj) {
        Gofast.intervalidentifier = 0;
        var iframeResizeInterval = setInterval(function(){
          Gofast.intervalidentifier++;

          if(Gofast.intervalidentifier > 10){
              clearInterval(iframeResizeInterval);
          }

          obj.style.height = obj.contentWindow.document.body.scrollHeight + 'px';  
        }, 500);
    }

    if(jQuery(".breadcrumb-gofast").length == 0){
        jQuery("#ajax_content").prepend('<div class="breadcrumb gofast breadcrumb-gofast">' + Drupal.t("Workflows dashboard", {}, {context: "gofast:gofast_workflows"}) + '</div>');
    }
        
    jQuery("document").ready(function(){
        <?php if(isset($_GET['details'])){ ?>
                Gofast.gofast_workflow_show_details(<?php echo $_GET['pid'] ?>, "<?php echo $_GET['type'] ?>", "<?php echo $_GET['title'] ?>", <?php echo $_GET['hid'] ?>, <?php echo $_GET['documents'] ?>);
        <?php } ?>
    });
</script>