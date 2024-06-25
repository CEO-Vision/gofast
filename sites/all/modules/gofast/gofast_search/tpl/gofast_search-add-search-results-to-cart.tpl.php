<?php
  $paths = array();
  $has_wrong_data = false;
  foreach ($entities as $entity_type => &$entity_ids) {
    foreach($entity_ids as $index => $entity_id){
      $entity = entity_load_single($entity_type, $entity_id);
      $path = "";
      if ($entity->type == "alfresco_item" || $entity->type == "article") {
          $path = $entity->field_emplacement['und'][0]['value'] . "/" . $entity->title;
          array_push($paths, $path);
      } else {
        $has_wrong_data = true;
        unset($entity_ids[$index]);
      }
    }
  }
  if (count($paths) > 0) $rendered_items = '<ul><li>' . implode('</li><li>', $paths) . '</li></ul>';
?>
<?php if($has_wrong_data): ?>
  <div class='alert alert-custom alert-notice alert-light-warning fade show' role='alert'>
    <div class='alert-icon'><i class='flaticon-warning'></i></div>
    <div class='alert-text m-0'>
      <span class='font-weight-bold'><?= t("Checked items that are not content will not be added to the shopping cart.", array(), array("context" => "gofast:gofast_search")) ?></span>
    </div>
  </div>
<?php endif; ?>
<div id="add_search_results_to_cart_modal_container">
  <h2><?= t('Add documents to your cart:', array(), array('context' => 'gofast'));?></h2>
  <?php if(count($paths) > 0): ?>
    <?= $rendered_items ?>
    <button type="button" class="btn btn-success" onclick="Gofast.search.submitAddSearchResultsToCart()">
      <?= t('Add to cart', array(), array('context' => 'gofast:gofast_search'));?>
    </button>
    <?php else: ?>
      <?= "<p class='mt-2 h5 text-muted'>" . t("Selected documents are not documents neither wiki articles", array(), array("context" => "gofast:gofast_search")) . "</p>"; ?><br />
    <?php endif; ?>
    <button type="button" class="btn btn-secondary" onclick="Drupal.CTools.Modal.dismiss()">
      <?php print t('Cancel');?>
    </button>
</div>
<script>
  Gofast.search.itemsToAdd = <?= json_encode($entities) ?>
</script>
