<?php
    $detect = new Mobile_Detect();
    $is_mobile_device = ($detect->isMobile() || $detect->isTablet() || $detect->is('iPad'));
    if(gofast_mobile_is_mobile_domain()){
        $right = "26px";
        $position = "absolute";
    }else{
        $right = "55px";
        $position = "absolute";
    }
    
   if($full_page){
       $suffix_id = "-full";
   }else{
       $suffix_id = "";
   }
?>
<!-- DIV globale du bloc -->
<?php global $user; ?>


<div <?php if(!gofast_mobile_is_mobile_domain()){?>style='min-width:600px;'<?php } ?> class="GofastWorkflows mainContent <?php if(gofast_mobile_is_mobile_domain()){?>well well-sm<?php } ?>">
  <button id="refresh-lightdashboard" type="button" class="btn btn-sm btn-default d-none" ><i class="fa fa-refresh"></i></button>
  <button id="refresh-pagedashboard" type="button" class="btn btn-default d-none"><i class="fa fa-arrow-left"></i></button>
           
    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column">
            <div class="w-100 px-2">
                <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap align-items-baseline" id="gofastWorkflowNavTabs" role="tablist">
                    <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardMyTab" aria-controls="lightDashboardMy<?php echo $suffix_id; ?>" data-toggle="tab" href="#lightDashboardMy<?php echo $suffix_id; ?>">
                            <span class="nav-icon">
                                <i class="fas fa-flag"></i>
                            </span>
                            <span class="nav-text"><?php echo t("My current tasks", array(), array("context"=> "gofast:gofast_workflows")) ?></span>
                        </a>
                    </li>
                    <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardOtherTab" aria-controls="lightDashboardOther<?php echo $suffix_id; ?>" data-toggle="tab" href="#lightDashboardOther<?php echo $suffix_id; ?>">
                            <span class="nav-icon">
                                <i class="fas fa-flag"></i>
                            </span>
                            <span class="nav-text"><?php echo t("Others current tasks", array(), array("context"=> "gofast:gofast_workflows")) ?></span>
                        </a>
                    </li>
                    <?php if (!$is_mobile_device) : ?>
                     <li class="nav-item" >
                        <a class="nav-link px-2 d-flex justify-content-center" id="lightDashboardNewTab" aria-controls="lightDashboardNew<?php echo $suffix_id; ?>" data-toggle="tab" href="#lightDashboardNew<?php echo $suffix_id; ?>">
                            <span class="nav-icon">
                                <i class="fa fa-play mr-1"></i>
                            </span>
                            <span class="nav-text"><?php echo t("New", array(), array("context"=> "gofast")) ?></span>
                        </a>
                    </li>
                    <?php endif; ?>
                </ul>
            </div>
            <div class="h-100 w-100 overflow-hidden" >
                <div class="tab-content h-100 w-100" id="gofastWorkflowContentPanel">             
                    <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardMy<?php echo $suffix_id; ?>" role="tabpanel" aria-labelledby="lightDashboardMyTab<?php echo $suffix_id; ?>">
                       <div id="bonita_light_dashboardMy_placeholder" class="loader-bonita-dashboard"></div>
                    </div>

                    <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardOther<?php echo $suffix_id; ?>" role="tabpanel" aria-labelledby="lightDashboardOtherTab<?php echo $suffix_id; ?>">
                        <div id="bonita_light_dashboardOther_placeholder" class="loader-bonita-dashboard"></div>
                    </div>
                    
                    <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="lightDashboardNew<?php echo $suffix_id; ?>" role="tabpanel" aria-labelledby="lightDashboardNewTab<?php echo $suffix_id; ?>">
                      <div><?php echo gofast_workflows_get_available_processes(false); ?></div>
                    </div>
                </div>
            </div>   
        </div>
    <!--<div id="bonita_light_dashboard_placeholder" class="loader-bonita-dashboard"></div>-->
    <script type="text/javascript">
        jQuery(document).ready(setTimeout(function(){
            var is_full_page = "<?php if($full_page == true){echo 'true';}else{echo 'false';} ?>";
            if(is_full_page == "true"){
                jQuery("#navWorkflow #lightDashboardMyTab").click();
                Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                    Gofast.setCookie("bonita_sess_timestamp",Math.floor(Date.now() / 1000));
                    jQuery("#navWorkflow #bonita_light_dashboardMy_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboardMy/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
                    jQuery("#navWorkflow #bonita_light_dashboardOther_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboardOther/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process_other" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
                }); 
            }else{
                jQuery("#lightDashboardMyTab").click();
                Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                    Gofast.setCookie("bonita_sess_timestamp",Math.floor(Date.now() / 1000));
                    jQuery("#bonita_light_dashboardMy_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboardMy/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
                    jQuery("#bonita_light_dashboardOther_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboardOther/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process_other" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
                    jQuery("[id^=bonita_form_process]").each(function() {
                        jQuery(this).on("load", function() {
                            this.contentDocument.documentElement.style.overflowX = "hidden";
                        });
                    });
                });
            }
        }, 4000));

        var dropdownInterval = setInterval(function(){
            if(typeof jQuery === "function" && typeof jQuery().dropdown === "function"){
                clearInterval(dropdownInterval);
                jQuery("#refresh-lightdashboard").click(function(){
                    Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                        jQuery('iframe#bonita_form_process')[0].contentWindow.location.reload(true);
                        jQuery('iframe#bonita_form_process_other')[0].contentWindow.location.reload(true);
                    });
                });
                jQuery("#refresh-pagedashboard").click(function(){
                    location.reload();
                });
            }
        }, 500);
 
    </script>
</div>


