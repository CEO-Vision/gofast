<?php
/**
 * @file
 * Implemented features export/import hooks.
 */

/**
 * Implements hook_features_export().
 */
function og_roles_permissions_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['features_og_roles_permissions'] = 'features_og_roles_permissions';
  $export['dependencies']['og'] = 'og';

  $map = features_get_default_map('og_roles_permissions', 'name');
  foreach ($data as $role) {
    // Check first if the role exists.
    if (!features_og_roles_permissions_role_by_name($role)) {
      continue;
    }

    // Role is provided by another module: add dependency.
    if (isset($map[$role]) && $map[$role] != $module_name) {
      $export['dependencies'][$map[$role]] = $map[$role];
    }

    // Export the role.
    $export['features']['og_roles_permissions'][$role] = $role;
  }

  return array();
}

/**
 * Implements hook_features_export_options().
 */
function og_roles_permissions_features_export_options() {
  $options = array();

  $groups = og_get_all_group_bundle();
  foreach ($groups as $group_type => $bundles) {
    foreach ($bundles as $bundle => $name) {
      $roles = og_roles($group_type, $bundle, 0);
      foreach ($roles as $rid => $role) {
        $key = $group_type . ':' . $bundle . ':' . $role;
        $options[$key] = $key;
      }
    }
  }

  return $options;
}

/**
 * Implements hook_features_export_render().
 */
function og_roles_permissions_features_export_render($module, $data) {
  $code = array();
  $code[] = '  $roles = array();';
  $code[] = '';

  // Export all roles & their permissions.
  foreach ($data as $name) {
    $role = features_og_roles_permissions_role_by_name($name);
    if (!$role) {
      continue;
    }

    // Get all permissions for the role.
    $role_lookup = array($role->rid => $role->name);
    $permissions = og_role_permissions($role_lookup);
    $role->permissions = array_shift($permissions);

    // Create the export code.
    unset($role->rid);
    $role_identifier = features_var_export($name);
    $role_export = features_var_export($role, '  ');
    $code[] = "  // Exported role: {$name}.";
    $code[] = "  \$roles[{$role_identifier}] = {$role_export};";
    $code[] = '';
  }

  $code[] = '  return $roles;';
  $code = implode(PHP_EOL, $code);

  return array('default_og_roles_permissions' => $code);
}

/**
 * Implements hook_features_revert().
 */
function og_roles_permissions_features_revert($module) {
  og_roles_permissions_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function og_roles_permissions_features_rebuild($module) {
  if ($defaults = features_get_default('og_roles_permissions', $module)) {
    $modules = og_get_permissions();

    // Create/Update the roles and their permissions.
    foreach ($defaults as $name => $role) {
      // Make sure the role exists.
      $role = (object) $role;
      if ($existing = features_og_roles_permissions_role_by_name($name)) {
        $role->rid = $existing->rid;
      }
      og_role_save($role);

      // Merge with existing permissions.
      $role_lookup = array($role->rid => $role->name);
      $existing_permissions = og_role_permissions($role_lookup);
      $existing = array_shift($existing_permissions);
      $permissions = array_merge($existing, $role->permissions);

      // Cleanup permissions.
      foreach ($permissions as $permission => $value) {
        if (!array_key_exists($permission, $modules)) {
          unset($permissions[$permission]);
          continue;
        }

        $permissions[$permission] = array_key_exists($permission, $role->permissions);
      }

      // Update the role permissions.
      og_role_change_permissions($role->rid, $permissions);
    }
  }
}

/**
 * Load a OG role by its name.
 *
 * @param string $name
 *   The role name in format group_type:group_bundle:role_name.
 *
 * @return object|FALSE
 *   The role object.
 */
function features_og_roles_permissions_role_by_name($name) {
  list($group_type, $group_bundle, $role_name) = explode(':', $name);
  return db_select('og_role', 'ogr')
    ->fields('ogr')
    ->condition('ogr.gid', 0)
    ->condition('ogr.group_type', $group_type)
    ->condition('ogr.group_bundle', $group_bundle)
    ->condition('ogr.name', $role_name)
    ->execute()
    ->fetch();
}
