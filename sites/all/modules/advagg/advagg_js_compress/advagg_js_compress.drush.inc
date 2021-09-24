<?php

/**
 * @file
 * Drush commands for AdvAgg JS minification.
 */

/**
 * @addtogroup 3rd_party_hooks
 * @{
 */

/**
 * Implements hook_drush_help().
 */
function advagg_js_compress_drush_help($command) {
  switch ($command) {
    case 'drush:advagg-jsmin':
      return dt('Run js minification for all js files.');

  }
}

/**
 * Implements hook_drush_command().
 */
function advagg_js_compress_drush_command() {
  $items = array();
  $items['advagg-js-compress'] = array(
    'description' => dt('Run the advagg cron hook.'),
    'examples' => array(
      'Standard example' => 'drush advagg-js-compress',
    ),
    'aliases' => array('advagg-jsmin'),
  );

  return $items;
}

/**
 * @} End of "addtogroup 3rd_party_hooks".
 */

/**
 * Callback function for drush advagg-jsmin.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 */
function drush_advagg_js_compress() {
  // Get the redo list.
  list($list, $redo_list) = advagg_js_compress_all_js_files_list();

  // Return if nothing to do.
  if (empty($redo_list)) {
    drush_log(dt('All of %total js files are already minified.', array(
      '%total' => count($list),
    )), 'ok');
    return;
  }

  drush_log(dt('A total of %redo out of %total js files will be minified.', array(
    '%redo' => count($redo_list),
    '%total' => count($list),
  )), 'ok');

  // Compress js files and cache.
  advagg_js_compress_redo_files($redo_list, 0, TRUE);
}
