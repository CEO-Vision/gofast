<?php
/**
 * @file
 * gofast_features_global.facetapi_defaults.inc
 */

/**
 * Implements hook_facetapi_default_facet_settings().
 */
function gofast_features_global_facetapi_default_facet_settings() {
  $export = array();

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:document_reference_unrestricted';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'document_reference_unrestricted';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'display' => 'display',
    ),
    'sort_weight' => array(
      'display' => -50,
    ),
    'sort_order' => array(
      'display' => 4,
    ),
    'empty_behavior' => 'none',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => 0,
    'nofollow' => 1,
    'show_expanded' => 0,
    'keep_open' => 1,
    'expand' => 0,
    'collapsible_children' => 1,
  );
  $export['apachesolr@gofast_solr:block:document_reference_unrestricted'] = $facet;
  
  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:field_title';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'field_title';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'display' => 'display',
    ),
    'sort_weight' => array(
      'display' => -50,
    ),
    'sort_order' => array(
      'display' => 4,
    ),
    'empty_behavior' => 'none',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => 0,
    'nofollow' => 1,
    'show_expanded' => 0,
    'keep_open' => 1,
    'expand' => 0,
    'collapsible_children' => 1,
  );
  $export['apachesolr@gofast_solr:block:field_title'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:field_custom_date';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'field_custom_date';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'date' => 'date',
    ),
    'sort_weight' => array(
      'date' => -50,
    ),
    'sort_order' => array(
      'date' => 4,
    ),
    'empty_behavior' => 'none',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => 0,
    'nofollow' => 1,
    'show_expanded' => 0,
    'keep_open' => 1,
    'expand' => 0,
    'collapsible_children' => 1,
  );
  $export['apachesolr@gofast_solr:block:field_custom_date'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:field_retention_end';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'field_retention_end';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'date' => 'date',
    ),
    'sort_weight' => array(
      'date' => -50,
    ),
    'sort_order' => array(
      'date' => 4,
    ),
    'empty_behavior' => 'none',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => 0,
    'nofollow' => 1,
    'show_expanded' => 0,
    'keep_open' => 1,
    'expand' => 0,
    'collapsible_children' => 1,
  );
  $export['apachesolr@gofast_solr:block:field_retention_end'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr::classification';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = '';
  $facet->facet = 'classification';
  $facet->enabled = FALSE;
  $facet->settings = array(
    'operator' => 'and',
    'hard_limit' => '50',
    'dependencies' => array(
      'roles' => array(),
      'bundle' => 'none',
      'bundle_selected' => array(),
    ),
    'facet_mincount' => '1',
    'facet_missing' => 0,
    'flatten' => 0,
    'individual_parent' => 0,
    'query_type' => 'term',
    'limit_active_items' => 0,
  );
  $export['apachesolr@gofast_solr::classification'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:classification';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'classification';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'display' => 'display',
      'active' => 'active',
      'count' => 0,
      'indexed' => 0,
      'date' => 0,
    ),
    'sort_weight' => array(
      'display' => '-50',
      'active' => '0',
      'count' => '0',
      'indexed' => '0',
      'date' => '0',
    ),
    'sort_order' => array(
      'display' => '4',
      'active' => '4',
      'count' => '4',
      'indexed' => '4',
      'date' => '4',
    ),
    'empty_behavior' => 'none',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => '0',
    'nofollow' => 1,
    'show_expanded' => 0,
    'keep_open' => 1,
    'expand' => 0,
    'collapsible_children' => 1,
    'empty_text' => array(
      'value' => '',
      'format' => 'filtered_html',
    ),
  );
  $export['apachesolr@gofast_solr:block:classification'] = $facet;

  return $export;
}
