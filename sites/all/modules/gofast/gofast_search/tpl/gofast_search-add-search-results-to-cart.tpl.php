<?php
  $nids_string = $nids;
  $nids = explode(",", $nids);
  $paths = array();
  foreach ($nids as $nid) {
    $node = node_load($nid);
    $path = "";
    if ($node->type == "alfresco_item") {
        $path = $node->field_emplacement['und'][0]['value'] . "/" . $node->title;
        array_push($paths, $path);
    }
  }
  $rendered_items .= '<ul><li>' . implode('</li><li>', $paths) . '</li></ul>';
?>
<div id="add_search_results_to_cart_modal_container">
  <script>
      Gofast.search.nids = <?php echo json_encode($nids_string); ?>;
  </script>
  <h2><?php print t('Add documents to your cart:', array(), array('context' => 'gofast'));?></h2>
  <?php echo $rendered_items; ?><br />
  <button type="button" class="btn btn-success" onclick="Gofast.search.submitAddSearchResultsToCart()">
    <?php print t('Add to cart', array(), array('context' => 'gofast:gofast_search'));?>
  </button>
</div>
