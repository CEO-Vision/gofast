<?php
/**
 * @file
 * og_example.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function og_example_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
