<div id="workflows-dashboard-search">
    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column">
        <div class="accordion accordion-solid accordion-toggle-plus mt-2 mb-2 gofastBoostrapPanel" id="accordion_gofast_612e319b85b58">
            <div class="card">
                <div class="card-header">
                    <div class="card-title" data-toggle="collapse" data-target="#collapse_gofast_612e319b85b58" aria-expanded="true">
                        <?php echo t("Process and tasks list", array(), array('context' => "gofast:gofast_workflows")); ?> </div>
                </div>
                <div id="collapse_gofast_612e319b85b58" class="collapse show" data-parent="#accordion_gofast_612e319b85b58" style="">
                    <div class="card-body">
                        <?php echo $search_form; ?>
                    </div>
                </div>
            </div>
        </div>

        <div class="card card-custom mt-4">
            <div class="card-body p-0">
                <ul class="nav nav-tabs nav-fill justify-content-center" id="myTab1" role="tablist">
                    <li class="nav-item">
                        <a class="nav-link px-2 d-flex justify-content-center active" id="wfdash_search_header" aria-controls="wfdash_search" data-toggle="tab" href="#wfdash_search">
                            <span class="nav-icon">
                                <i class="fal fa-clipboard-list-check"></i>
                            </span>
                            <span class="nav-text"><?php echo t("Process and tasks list", array(), array('context' => "gofast:gofast_workflows")); ?></span>
                        </a>
                    </li>

                    <li class="nav-item">
                        <a class="nav-link px-2 d-flex justify-content-center" id="wfdash_stats_header" aria-controls="wfdash_stats" data-toggle="tab" href="#wfdash_stats">
                            <span class="nav-icon">
                                <i class="far fa-chart-pie"></i>
                            </span>
                            <span class="nav-text"><?php echo t("Reports and statistics", array(), array('context' => "gofast:gofast_workflows")); ?></span>
                        </a>
                    </li>
                </ul>

                <div class="tab-content" id="myTabContent">
                    <div class="tab-pane fade show active" id="wfdash_search" role="tabpanel" aria-labelledby="wfdash_search_header">
                        <div class="card card-custom p-1">
                            <div class="card-body">
                                <iframe id="bonita_full_dashboard_search" style="width:100%;height:100%;min-height:800px;border:none;"></iframe>
                            </div>
                        </div>
                    </div>
                    <div class="tab-pane fade" id="wfdash_stats" role="tabpanel" aria-labelledby="wfdash_stats_header">
                        <div class="card card-custom p-1">
                            <div id="workflowsStatsHeader" class="mt-4 mb-4 h-100px d-none">
                                <h3><?= t("Type de processus selectionné : ", array(), array("context" => "gofast:gofast_workflows_stats")) ?><b id="workflowsStatsType"></b></h3>
                                <div style="margin-left: auto; order:2;">
                                    <button id="gofast-workflow-excel-export" onclick="Gofast.download_workflow_fields(event)" class="btn btn-outline-success mr-2"><i class="flaticon2-poll-symbol"></i> <?php echo t('Download data (.xlsx)', array(), array('context' => 'gofast:gofast_workflows')); ?></a>
                                        <button onclick="Gofast.gofast_workflow_stats.downloadDatas()" class="btn btn-outline-success mr-2"><i class="flaticon2-pie-chart"></i> <?php echo t('Download statistics (.xlsx)', array(), array('context' => 'gofast:gofast_workflows')); ?></a>
                                </div>
                            </div>
                            <div class="card-body" id="workflowsStatsContainer">
                                <div class="text-center pt-15 mt-15 pb-15 mb-15">
                                    <p><?php echo t('Select a "Process Type" from the filters and click "Search"') ?></p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
<div class="card-body pb-2 pt-0 px-1 d-flex flex-column">
    <div id="workflows-dashboard-details">

        <div class="accordion accordion-solid accordion-toggle-plus mt-2 mb-2 gofastBoostrapPanel" id="accordion_gofast_612e319b85b56">
            <div class="card">
                <div class="card-header">
                    <div class="card-title" data-toggle="collapse" data-target="#collapse_gofast_612e319b85b56" aria-expanded="true">
                        <?php echo t("Workflow tasks", array(), array('context' => "gofast:gofast_workflows")); ?> </div>
                </div>
                <div id="collapse_gofast_612e319b85b56" class="collapse show" data-parent="#accordion_gofast_612e319b85b56" style="">
                    <div class="card-body">
                        <iframe id="workflows-dashboard-tasks" style="width:100%;height:100%;border:none;" onload="resizeIframe(this)"></iframe>
                    </div>
                </div>
            </div>
        </div>

        <div class="accordion accordion-solid accordion-toggle-plus mt-2 mb-2 gofastBoostrapPanel" id="accordion_gofast_612e319b85b55">
            <div class="card">
                <div class="card-header">
                    <div class="card-title" data-toggle="collapse" data-target="#collapse_gofast_612e319b85b55" aria-expanded="true">
                        <?php echo t("Documents in this workflow", array(), array('context' => "gofast:gofast_workflows")); ?> </div>
                </div>
                <div id="collapse_gofast_612e319b85b55" class="collapse show" data-parent="#accordion_gofast_612e319b85b55" style="">
                    <div class="card-body">
                        <div class="panel-body" id="workflows-dashboard-documents"></div>
                    </div>
                </div>
            </div>
        </div>

        <div class="accordion accordion-solid accordion-toggle-plus mt-2 mb-2 gofastBoostrapPanel" id="accordion_gofast_612e319b85b54">
            <div class="card">
                <div class="card-header">
                    <div class="card-title" data-toggle="collapse" data-target="#collapse_gofast_612e319b85b54" aria-expanded="true">
                        <?php echo t("Workflow history", array(), array('context' => "gofast:gofast_workflows")); ?> </div>
                </div>
                <div id="collapse_gofast_612e319b85b54" class="collapse show" data-parent="#accordion_gofast_612e319b85b54" style="">
                    <div class="card-body">
                        <iframe id="workflows-dashboard-history" style="width:100%;height:100%;border:none;" onload="resizeIframe(this)"></iframe>
                    </div>
                </div>
            </div>
        </div>

 </div>
 </div> 
<script>
    var waitSearchAvailable = setInterval(function(){
        if(typeof Gofast.gofast_workflow_search_execute === "function" && typeof Gofast._settings === "object" && typeof Gofast._settings.gofast === "object"){
            Gofast.gofast_workflow_apply_filters();
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

          if(obj.contentWindow !== null){
            obj.style.height = (obj.contentWindow.document.body.scrollHeight + 15) + 'px';
          }
        }, 500);
    }

    if(jQuery(".breadcrumb-gofast").length == 0){
        jQuery("#ajax_content").prepend('<div class="breadcrumb gofast breadcrumb-gofast" style="margin-bottom:2px;">' + Drupal.t("Workflows dashboard", {}, {context: "gofast:gofast_workflows"}) + '</div>');
    }

    jQuery("document").ready(function(){
        <?php if(isset($_GET['details'])){ ?>
                Gofast.gofast_workflow_show_details(<?php echo $_GET['pid'] ?>, "<?php echo $_GET['type'] ?>", "<?php echo $_GET['title'] ?>", <?php echo $_GET['hid'] ?>, <?php echo $_GET['documents'] ?>);
        <?php } ?>
    });
</script>

<style>
    .breadcrumb-gofast {
        display: none;
    }

    .apexcharts-menu-icon {
        display: none;
    }
</style>
