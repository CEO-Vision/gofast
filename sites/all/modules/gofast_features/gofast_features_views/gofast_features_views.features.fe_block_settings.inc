<?php
/**
 * @file
 * gofast_features_views.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gofast_features_views_default_fe_block_settings() {
  $export = array();
  $export['version'] = '2.0';
  return $export;
}
