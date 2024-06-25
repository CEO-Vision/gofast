<?php

/**
 * @file
 * gofast_features_mail.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gofast_features_mail_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
}
