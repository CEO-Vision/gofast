<?php
/**
 * @file
 * gofast_features_community.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gofast_features_community_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
