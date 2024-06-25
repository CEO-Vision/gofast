<?php

/**
 * Implements hook_drush_command().
 */
function gofast_search_drush_command() {
  $commands['bundle-reindex'] = array(
    'description' => 'Reindex Apachesolr content for Specific Bundle',
    'arguments' => array(
      'bundle' => 'The type of the bundle (article,page etc.)',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_search_reindex_bundle',
  );
  return $commands;
}

/**
 * This is a callback for the reindex of node entity with specific bundle.
 */
function drush_gofast_search_reindex_bundle($bundle = NULL) {
  if (!empty($bundle)) {
    module_load_include('inc', 'apachesolr', 'apachesolr.index');
    $env_id = GOFAST_SEARCH_ENV_ID;
    apachesolr_index_node_solr_reindex($env_id, $bundle);
    drush_print("Reindex the node of {$bundle}");
  }
  else {
    drush_print("Without bundle no operation is possible");
  }
}