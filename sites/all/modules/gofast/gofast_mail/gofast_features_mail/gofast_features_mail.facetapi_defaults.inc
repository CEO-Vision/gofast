<?php

/**
 * @file
 * gofast_features_mail.facetapi_defaults.inc
 */

/**
 * Implements hook_facetapi_default_facet_settings().
 */
function gofast_features_mail_facetapi_default_facet_settings() {
  $export = array();

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:acknowledge_number';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'acknowledge_number';
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
  $export['apachesolr@gofast_solr:block:acknowledge_number'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:arrival_departure_date';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'arrival_departure_date';
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
  $export['apachesolr@gofast_solr:block:arrival_departure_date'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:arrival_departure_link';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'arrival_departure_link';
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
  $export['apachesolr@gofast_solr:block:arrival_departure_link'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:impute_to';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'impute_to';
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
  $export['apachesolr@gofast_solr:block:impute_to'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:mail_instruction';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'mail_instruction';
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
  $export['apachesolr@gofast_solr:block:mail_instruction'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:mail_object';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'mail_object';
  $facet->enabled = TRUE;
  $facet->settings = array(
    'weight' => 0,
    'widget' => 'gofast_facetapi_links',
    'filters' => array(),
    'active_sorts' => array(
      'display' => 'display',
      'active' => 0,
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
  $export['apachesolr@gofast_solr:block:mail_object'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:mail_rid';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'mail_rid';
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
  $export['apachesolr@gofast_solr:block:mail_rid'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:mail_sender';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'mail_sender';
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
  $export['apachesolr@gofast_solr:block:mail_sender'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:mandatory_anwser';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'mandatory_anwser';
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
  $export['apachesolr@gofast_solr:block:mandatory_anwser'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:service_recipient';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'service_recipient';
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
  $export['apachesolr@gofast_solr:block:service_recipient'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@gofast_solr:block:user_recipient';
  $facet->searcher = 'apachesolr@gofast_solr';
  $facet->realm = 'block';
  $facet->facet = 'user_recipient';
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
  $export['apachesolr@gofast_solr:block:user_recipient'] = $facet;

  return $export;
}
