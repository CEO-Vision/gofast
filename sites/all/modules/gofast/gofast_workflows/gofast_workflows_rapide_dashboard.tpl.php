<!-- DIV globale du bloc -->
<?php global $user; ?>
<div class="gofast-block2 <?php if(gofast_mobile_is_mobile_domain()){?>well well-sm <?php } ?>">
    <?php if(!isset($node)): ?>
    <?php
        if(gofast_mobile_is_mobile_domain()){
            $right = "26px";
            $position = "absolute";
        }else{
            $right = "55px";
            $position = "absolute";
        }
    ?>
      <div style="float:left;  margin-bottom:5px; margin-left:5px;position:<?php echo $position; ?>;right:<?php echo $right; ?>;">
        <div class="btn-group" role="group">
          <button id="refresh-pagedashboard" type="button" class="btn btn-default gofast_display_none"><i class="fa fa-arrow-left"></i></button>
          <button id="refresh-lightdashboard" type="button" class="btn btn-default"><i class="fa fa-refresh"></i></button>
          <button id="dropdown-rapid" type="button" class="btn btn-info dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
              <?php echo t("New", array(), array("context" => "gofast")); ?> <span class="caret"></span>
          </button>
          <script>
              var dropdownInterval = setInterval(function(){
                  if(typeof jQuery === "function" && typeof jQuery().dropdown === "function"){
                    clearInterval(dropdownInterval);
                    jQuery("#dropdown-rapid").dropdown();
                    jQuery("#refresh-lightdashboard").click(function(){
                        Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                            jQuery('iframe#bonita_form_process')[0].contentWindow.location.reload(true);
                        });
                    });
                    jQuery("#refresh-pagedashboard").click(function(){
                        location.reload();
                    });
                }
              }, 500);
          </script>
     <?php endif; ?>
            <ul class="dropdown-menu" style="left: -51px;">
      <?php if(!isset($node)): ?>
              <li><a id='btn_wf_start' onclick="Drupal.gofast_workflows.ceo_vision_js_process_get_available_processes(null);"><span class="fa fa-play" style="margin: 1px 8px 0 0;"></span><?php echo t("New process", array(), array("context" => "gofast:gofast_workflows")); ?></a></li>
              <?php if(!gofast_mobile_is_mobile_domain()){?><li><a id='btn_wf_start_cart' onclick="Drupal.gofast_workflows.ceo_vision_js_process_get_available_processes('cart');"><span class="fa fa-shopping-cart" style="margin: 1px 8px 0 0;"></span><?php echo t("New process from cart documents", array(), array("context" => "gofast:gofast_workflows")); ?></a></li> <?php } ?>
                 <?php endif; ?>
            </ul>
        </div>
        </div>

  <div style="clear:both;"></div>
  <?php if(isset($node)): ?>
  <div style="padding:0px;height:100%;">
            <div style="width:100%;height:100%;min-height:550px;border:none;" id="bonita_document_dashboard_placeholder" class="loader-bonita-dashboard"><!-- Bonita dashboard will be placed here after Bonita login --></div>
            <script>
                Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                      jQuery("#bonita_document_dashboard_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboardDocument/content/?nid=<?php echo $node->nid; ?>&title=<?php echo rawurlencode($node->title); ?>&app=GoFAST&locale=<?php echo $user->language ?>" id="bonita_form_process" style="width:100%;height:100%;min-height:550px;border:none;"></iframe>');
                });
            </script>
  </div>
  <?php else: ?>
   <div style="padding:0px;height:100%;">
       <div id="bonita_light_dashboard_placeholder" class="loader-bonita-dashboard"><!-- Bonita dashboard will be placed here after Bonita login --></div>
   </div>

  <script type="text/javascript">
         jQuery(document).ready(function(){
             Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                 Gofast.setCookie("bonita_sess_timestamp",Math.floor(Date.now() / 1000));
                 jQuery("#bonita_light_dashboard_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboard/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process" style="width:100%;height:100%;min-height:550px;border:none;"></iframe>');
             });
         });
  </script>
  <?php endif; ?>
</div>
