  <div id="gofast-node-info-basic">
    <?php if ($node_infos['delete_message']) : ?>      
      <div class="alert alert-custom alert-notice alert-light-danger fade show" role="alert">
          <div class="alert-icon"><i class="flaticon-warning"></i></div>
          <div class="alert-text"><?php print $node_infos['delete_message']; ?></div>
      </div>
    <?php else: ?>
      <?php print theme('gofast_node_metadata_info', ['node_infos' => $node_infos]) ?>
      <div class="separator separator-solid my-4"></div>
      <?php print theme('gofast_node_metadata_location', ['node_infos' => $node_infos]) ?>
      <div class="separator separator-solid my-4"></div>
      <?php print theme('gofast_node_metadata_tags', ['node_infos' => $node_infos]) ?>
      <div class="separator separator-solid"></div>
      <?php print theme('gofast_node_metadata_links', ['node_infos' => $node_infos]) ?>
    <?php endif; ?>
  </div>
