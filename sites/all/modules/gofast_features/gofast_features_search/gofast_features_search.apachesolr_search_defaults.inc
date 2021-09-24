<?php
/**
 * @file
 * gofast_features_search.apachesolr_search_defaults.inc
 */

/**
 * Implements hook_apachesolr_search_default_searchers().
 */
function gofast_features_search_apachesolr_search_default_searchers() {
  $export = array();

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'core_search';
  $searcher->label = 'Core Search';
  $searcher->description = 'Core Search';
  $searcher->search_path = 'search/solr';
  $searcher->page_title = 'Search results';
  $searcher->env_id = 'gofast_solr';
  $searcher->settings = array(
    'fq' => array(),
    'apachesolr_search_custom_enable' => 0,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_per_page' => 10,
    'apachesolr_search_spellcheck' => 1,
    'apachesolr_search_search_box' => 1,
    'apachesolr_search_allow_user_input' => 0,
    'apachesolr_search_browse' => 'results',
  );
  $export['core_search'] = $searcher;

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'taxonomy_search';
  $searcher->label = 'Taxonomy Search';
  $searcher->description = 'Search all items with given term';
  $searcher->search_path = 'taxonomy/term/%';
  $searcher->page_title = '%value';
  $searcher->env_id = '';
  $searcher->settings = array(
    'apachesolr_search_search_type' => 'tid',
    'apachesolr_search_per_page' => 10,
    'apachesolr_search_browse' => 'results',
    'apachesolr_search_spellcheck' => FALSE,
    'apachesolr_search_search_box' => FALSE,
  );
  $export['taxonomy_search'] = $searcher;

  $searcher = new stdClass();
  $searcher->disabled = FALSE; /* Edit this to true to make a default searcher disabled initially */
  $searcher->api_version = 3;
  $searcher->page_id = 'user_search';
  $searcher->label = 'User Search';
  $searcher->description = 'User Search';
  $searcher->search_path = 'search/user_entity';
  $searcher->page_title = 'User';
  $searcher->env_id = 'solr';
  $searcher->settings = array(
    'fq' => array(
      0 => 'entity_type:user',
    ),
    'apachesolr_search_custom_enable' => TRUE,
    'apachesolr_search_search_type' => 'custom',
    'apachesolr_search_per_page' => 10,
    'apachesolr_search_browse' => 'browse',
    'apachesolr_search_spellcheck' => TRUE,
    'apachesolr_search_search_box' => TRUE,
  );
  $export['user_search'] = $searcher;

  return $export;
}
