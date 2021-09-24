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

  return $export;
}
