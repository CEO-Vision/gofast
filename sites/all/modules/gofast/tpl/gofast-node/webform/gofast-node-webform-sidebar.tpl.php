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

<div class="card card-custom card-stretch">
<div class="card card-custom card-stretch <?= gofast_essential_is_essential()  ? "card-simplified" : "" ?>">
  <?php if(!gofast_essential_is_essential()) : ?>
    <div class="position-absolute h-100 d-flex"><span id="collapsible-metadata-panel-toggle" class="m-auto cursor-pointer d-flex"><i class="fas fa-chevron-left m-auto"></i></span></div>
  <?php endif; ?>
  <?php if ($node->status != 0) : ?>
    <div class="card-header overflow-hidden justify-content-end h-50px min-h-50px border-0 px-2">
      <div id="node-tabsHeader" class="card-toolbar min-w-200px w-100">
        <?php echo theme('gofast_node_webform_tabsHeader', ['node' => $node,'count_notif' =>  gofast_get_notif_by_name($node, TRUE, FALSE)]) ?>
        <!-- @include('components.document.metadonnes.headerTabs') -->
      </div>
    </div>
    <div class="card-body p-0 overflow-hidden">
      <div class="tab-content overflow-auto p-3 h-100 w-100" id="myTabContent" data-nid="<?= $node->nid ?>">

        <div data-nid="<?= $node->nid ?>" class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
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
        <div class="tab-pane fade" id="document__commentstab" role="tabpanel" aria-labelledby="comments-tab">
          <div id="comments-container">
            <div>
              <div id="comments" class="comment-wrapper">
                <div id="gofast-node-comments-loader" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
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
  <?php else : ?>
    <div class="card-body p-0 overflow-hidden">
      <div class="tab-content overflow-auto p-3 h-100 w-100" id="myTabContent">
        <div class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
          <div id="node-info-content-unprocessed" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
        </div>
      </div>
    </div>
  <?php endif; ?>
  <?php
    $detect = new Mobile_Detect();
    if(gofast_essential_is_essential()) :
  ?>
  <div id="metadataSideButton"> 
    <i class="fas fa-2x fa-info-circle<?= gofast_essential_is_essential() && !$detect->isMobile()  ? "" : " invisible" ?>"></i>
    <span id="gofast-task-notifiation" style="display:block;margin-left:15px!important;margin-top:-35px!important;margin-bottom:18px!important;" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
    <i class="fa fa-2x fa-chevron-left<?= gofast_essential_is_essential() && !$detect->isMobile()  ? "" : " invisible" ?>"></i>
  </div>
  <?php endif; ?>
</div>



<script type='text/javascript'>
  jQuery(document).ready(function() {
    Gofast.gofast_main_block_breadcrumb();
    Gofast.gofast_right_block_breadcrumb();
    Drupal.behaviors.webformAjaxification.attach(document, Drupal.settings);
    jQuery("#collapsible-metadata-panel-toggle").on("click", Gofast.initCollapsibleMetadataPanel);

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
    }, 2000);
  });
</script>
