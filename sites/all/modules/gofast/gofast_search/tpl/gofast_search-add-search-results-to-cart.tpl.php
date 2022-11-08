<?php
  $nids_string = $nids;
  $nids = explode(",", $nids);
  $paths = array();
  foreach ($nids as $nid) {
    $node = node_load($nid);
    $path = "";
    if ($node->type == "alfresco_item" || $node->type == "article") {
        $path = $node->field_emplacement['und'][0]['value'] . "/" . $node->title;
        array_push($paths, $path);
    }
  }
  if (count($paths) > 0) $rendered_items = '<ul><li>' . implode('</li><li>', $paths) . '</li></ul>';
?>
<div id="add_search_results_to_cart_modal_container">
  <?php
    drupal_add_js("Gofast.search.nids = " . json_encode($nids_string), "inline");
  ?>
  <h2><?php print t('Add documents to your cart:', array(), array('context' => 'gofast'));?></h2>
  <?php echo strlen($rendered_items) > 0 ? $rendered_items : "<p class='mt-2 h5 text-muted'>" . t("Selected documents are not documents neither articles", array(), array("context" => "gofast:gofast_search")) . "</p>"; ?><br />
  <button type="button" class="btn btn-success" onclick="Gofast.search.submitAddSearchResultsToCart()">
    <?php print t('Add to cart', array(), array('context' => 'gofast:gofast_search'));?>
  </button>
</div>
