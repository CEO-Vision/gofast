<?php
/**
 * @file
 * gofast_features_taxonomy.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gofast_features_taxonomy_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer taxonomy'.
  $permissions['administer taxonomy'] = array(
    'name' => 'administer taxonomy',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in category'.
  $permissions['delete terms in category'] = array(
    'name' => 'delete terms in category',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in columns'.
  $permissions['delete terms in columns'] = array(
    'name' => 'delete terms in columns',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in format'.
  $permissions['delete terms in format'] = array(
    'name' => 'delete terms in format',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in hobbies'.
  $permissions['delete terms in hobbies'] = array(
    'name' => 'delete terms in hobbies',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in interests'.
  $permissions['delete terms in interests'] = array(
    'name' => 'delete terms in interests',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in skills'.
  $permissions['delete terms in skills'] = array(
    'name' => 'delete terms in skills',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in state'.
  $permissions['delete terms in state'] = array(
    'name' => 'delete terms in state',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in category'.
  $permissions['edit terms in category'] = array(
    'name' => 'edit terms in category',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in columns'.
  $permissions['edit terms in columns'] = array(
    'name' => 'edit terms in columns',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in format'.
  $permissions['edit terms in format'] = array(
    'name' => 'edit terms in format',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in hobbies'.
  $permissions['edit terms in hobbies'] = array(
    'name' => 'edit terms in hobbies',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in interests'.
  $permissions['edit terms in interests'] = array(
    'name' => 'edit terms in interests',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in skills'.
  $permissions['edit terms in skills'] = array(
    'name' => 'edit terms in skills',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in state'.
  $permissions['edit terms in state'] = array(
    'name' => 'edit terms in state',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  return $permissions;
}
