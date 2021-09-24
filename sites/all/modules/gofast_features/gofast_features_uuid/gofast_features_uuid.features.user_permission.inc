<?php
/**
 * @file
 * gofast_features_uuid.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gofast_features_uuid_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer uuid'.
  $permissions['administer uuid'] = array(
    'name' => 'administer uuid',
    'roles' => array(),
    'module' => 'uuid',
  );

  return $permissions;
}
