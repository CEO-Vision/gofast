<?php
/**
 * @file
 * gofast_features_init.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gofast_features_init_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
