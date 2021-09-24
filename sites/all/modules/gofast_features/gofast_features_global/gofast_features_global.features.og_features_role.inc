<?php
/**
 * @file
 * gofast_features_global.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function gofast_features_global_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:private_space:group administrator'.
  $roles['node:private_space:group administrator'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'group administrator',
  );

  return $roles;
}
