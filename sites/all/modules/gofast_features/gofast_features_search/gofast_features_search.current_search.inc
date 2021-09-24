<?php
/**
 * @file
 * gofast_features_search.current_search.inc
 */

/**
 * Implements hook_current_search_default_items().
 */
function gofast_features_search_current_search_default_items() {
  $export = array();

  $item = new stdClass();
  $item->disabled = FALSE; /* Edit this to true to make a default item disabled initially */
  $item->api_version = 1;
  $item->name = 'gofast_current_search_block';
  $item->label = 'Gofast Current Search';
  $item->settings = array(
    'items' => array(
      'results_count_label' => array(
        'id' => 'text',
        'label' => 'Results count label',
        'text' => 'Search found [facetapi_results:result-count] item',
        'plural' => 1,
        'text_plural' => 'Search found [facetapi_results:result-count] items',
        'plural_condition' => 'facetapi_results:result-count',
        'wrapper' => 1,
        'element' => 'h5',
        'css' => 1,
        'classes' => 'gofast-search-results-count',
        'weight' => '-50',
      ),
      'gofast_active_facets' => array(
        'id' => 'gofast_active',
        'label' => 'Gofast Active Facets',
        'pattern' => '[facetapi_active:active-value]',
        'keys' => 1,
        'css' => 1,
        'classes' => 'gofast-search-facet-active',
        'nofollow' => 1,
        'weight' => '0',
      ),
    ),
    'advanced' => array(
      'empty_searches' => '1',
    ),
  );
  $export['gofast_current_search_block'] = $item;

  return $export;
}
