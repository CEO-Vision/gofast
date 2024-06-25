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
  <div class="position-absolute h-100 d-flex"><span id="collapsible-metadata-panel-toggle" class="m-auto cursor-pointer d-flex"><i class="fas fa-chevron-left m-auto"></i></span></div>
  <?php if($node->status != 0 ): ?>
    <div class="card-body p-0">
      <div class="tab-content p-3 h-100 w-100" id="myTabContent">
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
        </div>
      </div>
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
    Gofast.gofast_main_block_breadcrumb();
    Gofast.gofast_right_block_breadcrumb();

    jQuery("#collapsible-metadata-panel-toggle").on("click", Gofast.initCollapsibleMetadataPanel);

    jQuery("[href='#document__audittab'").on("click", function() {
      Gofast.loadAuditBlock();
    });

    if(location.hash.startsWith("#comment-")){
      Gofast.loadcomments("<?= $node->nid ?>");
    }
    setTimeout(function() {
      Gofast.loadextrametadata("<?= $node->nid ?>");
      if(!$("#comments-container").hasClass("processed")){
        Gofast.loadcomments("<?= $node->nid ?>");
      }
    }, 2000);

  });
</script>
