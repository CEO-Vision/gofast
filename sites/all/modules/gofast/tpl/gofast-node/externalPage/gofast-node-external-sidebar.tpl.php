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

<div class=" card card-custom card-stretch <?= gofast_essential_is_essential()  ? "card-simplified" : "" ?>">
  <?php if($node->status != 0 ): ?>
    <div class="card-header justify-content-end h-50px min-h-50px border-0 px-2">
      <div id="node-tabsHeader" class="card-toolbar min-w-200px w-100">
        <?php echo theme('gofast_node_external_tabsHeader', ['node' => $node, 'count_notif' =>  gofast_get_notif_by_name($node, TRUE, FALSE)]) ?>
        <!-- @include('components.document.metadonnes.headerTabs') -->
      </div>
    </div>
    <div class="card-body p-0">
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
        <?php
          $block = module_invoke('gofast', 'block_view', 'gofast_node_comments_tree');
          print render($block['content']);
        ?>
        </div>
      </div>
    </div>
  <?php else: ?>
    <div class="card-body p-0">
      <div class="tab-content overflow-auto p-3 h-100 w-100" id="myTabContent">

        <div class="tab-pane fade show active " id="document__infotab" role="tabpanel" aria-labelledby="info-tab">
          <div id="node-info-content-unprocessed" class="spinner spinner-center spinner-primary spinner-lg m-5 not-processed position-absolute h-100 w-100"></div>
        </div>
      </div>
    </div>
  <?php endif; ?>
</div>


<script type='text/javascript'>
  jQuery(document).ready(function() {
    Gofast.gofast_right_block_breadcrumb();

    if(location.hash.startsWith("#comment-")){
      Gofast.loadcomments("<?= $node->nid ?>");
    }
    setTimeout(function() {
      Gofast.loadextrametadata("<?= $node->nid ?>");
      if(!$(".myTabContent[data-nid='<?= $node->nid ?>'] #comments-container").hasClass("processed")){
        Gofast.loadcomments("<?= $node->nid ?>");
      }
      jQuery('#comment-jstree').jstree();
    }, 2000);

  });
</script>
