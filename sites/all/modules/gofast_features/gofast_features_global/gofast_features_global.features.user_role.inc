<?php
/**
 * @file
 * gofast_features_global.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function gofast_features_global_user_default_roles() {
  $roles = array();

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 2,
  );

  // Exported role: business administrator.
  $roles['business administrator'] = array(
    'name' => 'business administrator',
    'weight' => 6,
  );

  // Exported role: contributor.
  $roles['contributor'] = array(
    'name' => 'contributor',
    'weight' => 3,
  );

  // Exported role: manager.
  $roles['manager'] = array(
    'name' => 'manager',
    'weight' => 4,
  );

  // Exported role: read only.
  $roles['read only'] = array(
    'name' => 'read only',
    'weight' => 5,
  );

  return $roles;
}
