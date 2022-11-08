<?php
global $user;

if (gofast_user_is_adm($user)) {
  $is_admin = TRUE;
} else {
  $is_admin = FALSE;
}

if (count(module_implements("extra_metadata")) >= 1) {
  //Check if node have metadata
  $extra_data = '';
  foreach (module_implements("extra_metadata") as $module) {
    $metadata = call_user_func($module . "_extra_metadata", $node);
    $extra_data .= $metadata;
  }

  if(!empty($extra_data)){
    $extra_metadata = TRUE;
  } else {
    $extra_metadata = FALSE;
  }
}
?>
<div class="card card-custom card-stretch">
  <div class="position-absolute h-100 d-flex"><span id="collapsible-metadata-panel-toggle" class="m-auto cursor-pointer d-flex"><i class="fas fa-chevron-left m-auto"></i></span></div>
  <?php if($node->status != 0 ): ?>
    <div class="card-body p-0">
      <div class="tab-content p-3 h-100 w-100" id="myTabContent">
        <div class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
          <div id="node-info-content-unprocessed" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
        </div>
        <?php if (count(module_implements("extra_metadata")) >= 1) { ?>
          <div class="tab-pane fade" id="document__extra_metadata_tab" role="tabpanel" aria-labelledby="extra-metadata-tab">
            <div id="extra-metadata-container">
              <div>
                <div id="extra-metadata-tab" class="comment-wrapper">
                  <div id="gofast-node-extra-metadata-loader" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
                </div>
              </div>
            </div>
          </div>
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
    Gofast.gofast_right_block_breadcrumb(true);

    jQuery("#collapsible-metadata-panel-toggle").on("click", Gofast.initCollapsibleMetadataPanel);

    jQuery("[href='#document__audittab'").on("click", function() {
      Gofast.loadAuditBlock();
    });

    setTimeout(function() {
      Gofast.loadextrametadata(Gofast.get('node').id);
      Gofast.loadcomments(Gofast.get('node').id);
    }, 2000);

  });
</script>
