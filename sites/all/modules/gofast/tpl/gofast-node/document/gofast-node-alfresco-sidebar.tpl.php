<?php
if (count(module_implements("extra_metadata")) >= 1) {
  //Check if node have metadata
  $extra_datas = array();
  foreach (module_implements("extra_metadata") as $module) {
    $metadata = call_user_func($module . "_extra_metadata", $node);
    if(!empty($metadata)){
      $extra_datas[] = $metadata;
    }
  }

}

?>

<div class="card card-custom card-stretch <?= gofast_essential_is_essential()  ? "card-simplified" : "" ?>">
  <?php if($node->status != 0 ): ?>
    <div class=" card-header justify-content-end h-50px min-h-50px border-0 px-2" style='<?php gofast_essential_is_essential() && !gofast_mobile_is_phone() ?  print "overflow: hidden" : "" ?>'>
      <div id="node-tabsHeader" class="card-toolbar min-w-200px w-100">
        <?php echo theme('gofast_node_alfresco_tabsHeader', ['node' => $node, 'count_notif' =>  gofast_get_notif_by_name($node, TRUE, TRUE)]) ?>
      </div>
    </div>
    <div class="card-body p-0">
      <div class="tab-content p-3 h-100 w-100" id="myTabContent" data-nid="<?= $node->nid ?>">

        <div data-nid="<?= $node->nid ?>" data-language="<?= $node->language ?>" class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
          <div id="node-info-content-unprocessed" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
        </div>
        <?php if (count(module_implements("extra_metadata")) >= 1) { ?>
          <?php foreach($extra_datas as $extra_data) : ?>
            <div class="tab-pane fade" id="<?php print $extra_data['id']; ?>" role="tabpanel" aria-labelledby="extra-metadata-tab">
              <div id="extra-metadata-container">
                <div>
                  <div id="extra-metadata-tab" class="comment-wrapper">
                    <div id="gofast-node-extra-metadata-loader" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
                  </div>
                </div>
              </div>
            </div>
          <?php endforeach;?>
        <?php } ?>

        <div class="tab-pane fade" id="document__tasktab" role="tabpanel" aria-labelledby="task-tab">
          <div id="tasktab-container">
            <div>
              <div id="tasktab" class="comment-wrapper">
                <?= theme("workflow_rapide_dashboard_document", array("node" => $node)) ?>
              </div>
            </div>
          </div>
        </div>

        <div class="tab-pane fade" id="document__commentstab" role="tabpanel" aria-labelledby="comments-tab">
          <div id="comments-container">
            <div>
              <div id="comments" class="comment-wrapper">
                <div id="gofast-node-comments-loader" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
              </div>
            </div>
          </div>
        </div>

        <div class="tab-pane fade" id="document__historytab" role="tabpanel" aria-labelledby="history-tab">
          <div id="historytab-container">
            <div>
              <div id="historytab" class="comment-wrapper">
                <div class="loader-blog"></div>
              </div>
            </div>
          </div>
        </div>

        <?php if (gofast_audit_access("node", $node->nid)) { ?>
          <div class="tab-pane fade" id="document__audittab" role="tabpanel" aria-labelledby="audit-tab">
            <section id="gofast-audit-container">
            </section>
          </div>
        <?php } ?>

      </div>
    </div>
    <?php $count_notif = gofast_get_notif_by_name($node, TRUE, TRUE);?>
    <?php if ((isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) || (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0)) { ?>
      <?php $has_notif = TRUE; ?>
    <?php } ?>
    <?php $detect = new Mobile_Detect(); ?>
    <div id="metadataSideButton" class="<?= gofast_essential_is_essential() && (!$detect->isMobile() || $detect->isTablet())  ? "" : "invisible" ?>"> 
      <i class="fas fa-2x fa-info-circle"></i>
      <span id="gofast-task-notifiation" style="display:block;margin-left:15px!important;margin-top:-35px!important;margin-bottom:18px!important;" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
      <i class="fa fa-2x fa-chevron-left"></i>
      <?php if($has_notif) : ?>
        <div class="red-dot"></div>
      <?php endif; ?>
    </div>    
     <?php else: ?>
      <div class="card-body p-0">
        <div class="tab-content p-3 h-100 w-100" id="myTabContent">
          <div class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
            <div id="node-info-content-unprocessed" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
          </div>
        </div>
      </div>
  <?php endif; ?>
</div>


<script type='text/javascript'>
  jQuery(document).ready(function() {
    Gofast.gofast_right_block_breadcrumb("true");

    jQuery("[href='#document__historytab']").on("click", function() {
      Gofast.historyTab("<?= $node->nid ?>");
    });

    jQuery("[href='#document__audittab'").on("click", function() {
      Gofast.loadAuditBlock();
    });

    jQuery("[href='#document__historytab']").on("click", function() {
      Gofast.historyTab("<?= $node->nid ?>");
    });

    jQuery("[href='#document__audittab'").on("click", function() {
      Gofast.loadAuditBlock();
    });
    if(location.hash.startsWith("#comment-")){
      Gofast.loadcomments("<?= $node->nid ?>");
    }
    setTimeout(function() {
      if(!$(".myTabContent[data-nid='<?= $node->nid ?>'] #comments-container").hasClass("processed")){
        Gofast.loadcomments("<?= $node->nid ?>");
      }
      Gofast.loadextrametadata("<?= $node->nid ?>");
      Gofast.handleActiveOnOGDropdownTabs();
    }, 2000);

    // switch back to active tab after polling
    jQuery("#node-tabsHeader a").each(function() {
        if (jQuery(this).hasClass("active") && jQuery(this)[0].hasAttribute("id") && jQuery(this).attr("id").includes("ParentTab")) {
            const contentId = jQuery(this).attr("id").replace("ParentTab", "");
            jQuery("#" + contentId + "_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/' + contentId + '/content/?app=GoFAST&locale='+ Gofast.get("user").language +'&nid=<?php echo $node->nid; ?> " id="bonita_form_process" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
        }
    })
    
    jQuery("[href='#document__tasktab'").on("click", function({ currentTarget: element }) {
        jQuery("#node-tabsHeader a").removeClass("active");
        const { id } = element;
        const contentId = id.replace("ParentTab", "");
        
        // get iframe matching clicked tab
        jQuery("#" + contentId + "_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/' + contentId + '/content/?app=GoFAST&locale='+ Gofast.get("user").language +'&nid=<?php echo $node->nid; ?> " id="bonita_form_process" style="width:100%;height:auto;min-height:430px;border:none;"></iframe>');
        // some specific CSS adjustements
        if (id == "lightDashboardDocumentMyParentTab") {
            setTimeout(function(){  
                jQuery("#lightDashboardDocumentMy #bonita_form").contents().find("form").parent().next().css("display", "none");
                jQuery("#lightDashboardDocumentMy #bonita_form").contents().find("form").css("width", "99%");
                jQuery("#lightDashboardDocumentMy #bonita_form").contents().find(".col-xs-12.ng-scope.thumbnail").css("display", "none");
                jQuery("#bonita_form_container").css("display", "block");
                Drupal.gofast_workflows.check_documents_tasks_after_async();
            }, 100);
        }
    });
  });
</script>
