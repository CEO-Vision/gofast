<?php

/**
 * Field handler to provide a list of title groups.
 */
class gofast_views_handler_filter_group_title extends views_handler_filter_many_to_one {

  function get_value_options() {
    $this->value_options = array();
    $bundles = array_keys(gofast_og_node_types());
    // Get all title of nodes.
    $results = db_select('node', 'n')
      ->fields('n')
      ->condition('n.type', $bundles)
      ->orderBy('n.title')
      ->execute();
    foreach ($results as $result) {
      $this->value_options[$result->nid] = $result->nid;
    }
  }
}
