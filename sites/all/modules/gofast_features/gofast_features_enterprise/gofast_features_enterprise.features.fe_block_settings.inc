<?php
/**
 * @file
 * gofast_features_enterprise.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gofast_features_enterprise_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['gofast_riot-gofast_riot_chat'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'gofast_riot_chat',
    'module' => 'gofast_riot',
    'node_types' => array(),
    'pages' => '<?php

$detect = new Mobile_Detect;

if ($detect->isMobile() || $detect->isTablet()){
  return false;
}else{
   return true;
}

?>',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => 0,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'header',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => 'riot',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  return $export;
}
