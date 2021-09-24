<?php
/**
 * @file
 * gofast_features_taxonomy.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function gofast_features_taxonomy_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:private_space:administer taxonomy'
  $permissions['node:private_space:administer taxonomy'] = array(
    'roles' => array(),
  );

  return $permissions;
}
