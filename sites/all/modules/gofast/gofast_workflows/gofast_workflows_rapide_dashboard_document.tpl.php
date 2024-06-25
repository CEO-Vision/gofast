<?php
    if(gofast_essential_is_essential()){
        $right = "26px";
        $position = "absolute";
    }else{
        $right = "55px";
        $position = "absolute";
    }   
    $reference = $node->nid . "`" . $node->title ."|";
    $_GET["document"] = $reference;
?>
<!-- DIV globale du bloc -->
<?php global $user; ?>


<div class="GofastWorkflows <?php if(gofast_essential_is_essential()){?>well well-sm <?php } ?>">
    <button id="refresh-lightdashboard-document" type="button" class="btn btn-sm btn-default d-none" ><i class="fa fa-refresh"></i></button>
    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column">           
            <div class="w-100 px-2" style="display:none;">
                <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap" id="gofastWorkflowNavTabs" role="tablist">
                    <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardDocumentMyTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab" href="#lightDashboardDocumentMy">
                            <span class="nav-icon">
                                <i class="fas fa-flag"></i>
                            </span>
                            <span class="nav-text"><?php echo t("My current tasks", array(), array("context"=> "gofast:gofast_workflows")) ?></span>
                        </a>
                    </li>
                    <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardDocumentOtherTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab" href="#lightDashboardDocumentOther">
                            <span class="nav-icon">
                                <i class="fas fa-flag"></i>
                            </span>
                            <span class="nav-text"><?php echo t("Others current tasks", array(), array("context"=> "gofast:gofast_workflows")) ?></span>
                        </a>
                    </li>
                    <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardDocumentHistoryTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab" href="#lightDashboardDocumentHistory">
                            <span class="nav-icon">
                                <i class="fas fa-cogs"></i>
                            </span>
                            <span class="nav-text"><?php echo t("History", array(), array("context"=> "gofast:gofast_workflows")) ?></span>
                        </a>
                    </li>
                     <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardDocumentNewTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab" href="#lightDashboardDocumentNew">
                            <span class="nav-icon">
                                <i class="fa fa-play mr-1"></i>
                            </span>
                            <span class="nav-text"><?php echo t("New", array(), array("context"=> "gofast")) ?></span>
                        </a>
                    </li>
                </ul>
            </div>
            <div class="h-100 w-100 overflow-hidden" >
                <div class="tab-content h-100 w-100" id="gofastWorkflowContentPanel">             
                    <div style="padding:0!important;" class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardDocumentMy" role="tabpanel" aria-labelledby="document__tasktab">
                       <div id="lightDashboardDocumentMy_placeholder" class="loader-bonita-dashboard">
                            <div class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
                       </div>
                    </div>
                    <div style="padding:0!important;" class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardDocumentOther" role="tabpanel" aria-labelledby="lightDashboardDocumentOtherTab">
                        <div id="lightDashboardDocumentOther_placeholder" class="loader-bonita-dashboard">
                            <div class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
                        </div>
                    </div>
                    
                     <div style="padding:0!important;" class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardDocumentHistory" role="tabpanel" aria-labelledby="lightDashboardDocumentHistoryTab">
                        <div id="lightDashboardDocumentHistory_placeholder" class="loader-bonita-dashboard">
                            <div class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
                        </div>
                     </div>
                    <div style="padding:0!important;" class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardDocumentNew" role="tabpanel" aria-labelledby="lightDashboardDocumentNewTab">
                      <div ><?php echo gofast_workflows_get_available_processes(false); ?></div>
                    </div>
                </div>
            </div>   
        </div>
    <!--<div id="bonita_light_dashboard_placeholder" class="loader-bonita-dashboard"></div>-->
    <script type="text/javascript">
            jQuery(document).ready(() => setTimeout(function(){       
                Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                    Gofast.setCookie("bonita_sess_timestamp",Math.floor(Date.now() / 1000));
                    //check if the user has an assigned task and focus on "my task" tab if he has at least one
                    <?php if (is_numeric($nb_my_assigned_tasks) && $nb_my_assigned_tasks > 0) : ?>
                        $('#lightDashboardDocumentMyParentTab').click();
                        $('.header_tasks_tab > #gofast-task-notifiation').parent().addClass('active');
                    <?php endif; ?>
                });
                
                jQuery("#refresh-lightdashboard-document").click(function(){
                    Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                        if(jQuery("#lightDashboardDocumentMy #bonita_form_process").length) {
                            jQuery("#lightDashboardDocumentMy #bonita_form_process")[0].contentWindow.location.reload(true);
                        }
                        if(jQuery("#lightDashboardDocumentOther #bonita_form_process").length) {
                            jQuery("#lightDashboardDocumentOther #bonita_form_process")[0].contentWindow.location.reload(true);
                        }
                        if(jQuery("#lightDashboardDocumentMy #bonita_form").length) {
                            jQuery("#lightDashboardDocumentMy #bonita_form")[0].contentWindow.location.reload(true);
                        }
                        if (jQuery("#lightDashboardDocumentHistory #bonita_form_process_history").length) {
                            jQuery("#lightDashboardDocumentHistory #bonita_form_process_history")[0].contentWindow.location.reload(true);
                        }
                    });
                });
            }, 1500));
    </script>
</div>
