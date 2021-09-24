<?php
/**
 * @file
 * gofast_features_og_roles_permissions.features.og_roles_permissions.inc
 */

/**
 * Implements hook_default_og_roles_permissions().
 */
function gofast_features_og_roles_permissions_default_og_roles_permissions() {
  $roles = array();

  // Exported role: node:extranet:administrator member.
  $roles['node:extranet:administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'extranet',
    'name' => 'administrator member',
    'permissions' => array(
      'access all webform results' => TRUE,
      'add user' => TRUE,
      'administer group' => TRUE,
      'approve and deny subscription' => TRUE,
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create extranet content' => TRUE,
      'create forum content' => TRUE,
      'delete all webform submissions' => TRUE,
      'delete any alfresco_item content' => TRUE,
      'delete any article content' => TRUE,
      'delete any book content' => TRUE,
      'delete any extranet content' => TRUE,
      'delete any forum content' => TRUE,
      'delete any webform content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own extranet content' => TRUE,
      'delete own forum content' => TRUE,
      'edit all webform submissions' => TRUE,
      'manage members' => TRUE,
      'manage permissions' => TRUE,
      'manage roles' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any book content' => TRUE,
      'update any extranet content' => TRUE,
      'update any forum content' => TRUE,
      'update any webform content' => TRUE,
      'update group' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own extranet content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:extranet:group contributor.
  $roles['node:extranet:group contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'extranet',
    'name' => 'group contributor',
    'permissions' => array(
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any forum content' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:extranet:member.
  $roles['node:extranet:member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'extranet',
    'name' => 'member',
    'permissions' => array(
      'access own webform submissions' => TRUE,
      'create group_node content' => TRUE,
      'create orga content' => TRUE,
      'create webform content' => TRUE,
      'delete any group_node content' => TRUE,
      'delete any orga content' => TRUE,
      'delete any page content' => TRUE,
      'delete own group_node content' => TRUE,
      'delete own orga content' => TRUE,
      'delete own page content' => TRUE,
      'delete own webform content' => TRUE,
      'delete own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'unsubscribe' => TRUE,
      'update any group_node content' => TRUE,
      'update any orga content' => TRUE,
      'update own group_node content' => TRUE,
      'update own orga content' => TRUE,
      'update own webform content' => TRUE,
    ),
  );

  // Exported role: node:extranet:non-member.
  $roles['node:extranet:non-member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'extranet',
    'name' => 'non-member',
    'permissions' => array(
      'subscribe' => TRUE,
    ),
  );

  // Exported role: node:extranet:read only member.
  $roles['node:extranet:read only member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'extranet',
    'name' => 'read only member',
    'permissions' => array(),
  );

  // Exported role: node:group:administrator member.
  $roles['node:group:administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'group',
    'name' => 'administrator member',
    'permissions' => array(
      'access all webform results' => TRUE,
      'add user' => TRUE,
      'administer group' => TRUE,
      'approve and deny subscription' => TRUE,
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'create group content' => TRUE,
      'delete all webform submissions' => TRUE,
      'delete any alfresco_item content' => TRUE,
      'delete any article content' => TRUE,
      'delete any book content' => TRUE,
      'delete any forum content' => TRUE,
      'delete any group content' => TRUE,
      'delete any webform content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'delete own group content' => TRUE,
      'edit all webform submissions' => TRUE,
      'manage members' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any book content' => TRUE,
      'update any forum content' => TRUE,
      'update any group content' => TRUE,
      'update any webform content' => TRUE,
      'update group' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
      'update own group content' => TRUE,
    ),
  );

  // Exported role: node:group:group contributor.
  $roles['node:group:group contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'group',
    'name' => 'group contributor',
    'permissions' => array(
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any forum content' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:group:member.
  $roles['node:group:member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'group',
    'name' => 'member',
    'permissions' => array(
      'access own webform submissions' => TRUE,
      'create group_node content' => TRUE,
      'create orga content' => TRUE,
      'create webform content' => TRUE,
      'delete any group_node content' => TRUE,
      'delete any orga content' => TRUE,
      'delete own group_node content' => TRUE,
      'delete own orga content' => TRUE,
      'delete own webform content' => TRUE,
      'delete own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'unsubscribe' => TRUE,
      'update any group_node content' => TRUE,
      'update any orga content' => TRUE,
      'update own group_node content' => TRUE,
      'update own orga content' => TRUE,
      'update own webform content' => TRUE,
    ),
  );

  // Exported role: node:group:non-member.
  $roles['node:group:non-member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'group',
    'name' => 'non-member',
    'permissions' => array(
      'subscribe' => TRUE,
    ),
  );

  // Exported role: node:group:read only member.
  $roles['node:group:read only member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'group',
    'name' => 'read only member',
    'permissions' => array(),
  );

  // Exported role: node:organisation:administrator member.
  $roles['node:organisation:administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'organisation',
    'name' => 'administrator member',
    'permissions' => array(
      'access all webform results' => TRUE,
      'add user' => TRUE,
      'administer group' => TRUE,
      'approve and deny subscription' => TRUE,
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'create organisation content' => TRUE,
      'delete all webform submissions' => TRUE,
      'delete any alfresco_item content' => TRUE,
      'delete any article content' => TRUE,
      'delete any book content' => TRUE,
      'delete any forum content' => TRUE,
      'delete any organisation content' => TRUE,
      'delete any webform content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'delete own organisation content' => TRUE,
      'edit all webform submissions' => TRUE,
      'manage members' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any book content' => TRUE,
      'update any forum content' => TRUE,
      'update any organisation content' => TRUE,
      'update any webform content' => TRUE,
      'update group' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
      'update own organisation content' => TRUE,
    ),
  );

  // Exported role: node:organisation:group contributor.
  $roles['node:organisation:group contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'organisation',
    'name' => 'group contributor',
    'permissions' => array(
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any forum content' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:organisation:member.
  $roles['node:organisation:member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'organisation',
    'name' => 'member',
    'permissions' => array(
      'access own webform submissions' => TRUE,
      'create group_node content' => TRUE,
      'create orga content' => TRUE,
      'create webform content' => TRUE,
      'delete any group_node content' => TRUE,
      'delete any orga content' => TRUE,
      'delete own group_node content' => TRUE,
      'delete own orga content' => TRUE,
      'delete own webform content' => TRUE,
      'delete own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'unsubscribe' => TRUE,
      'update any group_node content' => TRUE,
      'update any orga content' => TRUE,
      'update own group_node content' => TRUE,
      'update own orga content' => TRUE,
      'update own webform content' => TRUE,
    ),
  );

  // Exported role: node:organisation:non-member.
  $roles['node:organisation:non-member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'organisation',
    'name' => 'non-member',
    'permissions' => array(
      'subscribe' => TRUE,
    ),
  );

  // Exported role: node:organisation:read only member.
  $roles['node:organisation:read only member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'organisation',
    'name' => 'read only member',
    'permissions' => array(),
  );

  // Exported role: node:private_space:administrator member.
  $roles['node:private_space:administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'administrator member',
    'permissions' => array(
      'access all webform results' => TRUE,
      'administer group' => TRUE,
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete all webform submissions' => TRUE,
      'delete any alfresco_item content' => TRUE,
      'delete any article content' => TRUE,
      'delete any book content' => TRUE,
      'delete any forum content' => TRUE,
      'delete any webform content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'edit all webform submissions' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any book content' => TRUE,
      'update any forum content' => TRUE,
      'update any webform content' => TRUE,
      'update group' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:private_space:group administrator.
  $roles['node:private_space:group administrator'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'group administrator',
    'permissions' => array(),
  );

  // Exported role: node:private_space:group contributor.
  $roles['node:private_space:group contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'group contributor',
    'permissions' => array(
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any forum content' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:private_space:member.
  $roles['node:private_space:member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'member',
    'permissions' => array(
      'access own webform submissions' => TRUE,
      'create group_node content' => TRUE,
      'create orga content' => TRUE,
      'create webform content' => TRUE,
      'delete any group_node content' => TRUE,
      'delete any orga content' => TRUE,
      'delete own group_node content' => TRUE,
      'delete own orga content' => TRUE,
      'delete own webform content' => TRUE,
      'delete own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'update any group_node content' => TRUE,
      'update any orga content' => TRUE,
      'update own group_node content' => TRUE,
      'update own orga content' => TRUE,
      'update own webform content' => TRUE,
    ),
  );

  // Exported role: node:private_space:non-member.
  $roles['node:private_space:non-member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'non-member',
    'permissions' => array(),
  );

  // Exported role: node:private_space:read only member.
  $roles['node:private_space:read only member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'private_space',
    'name' => 'read only member',
    'permissions' => array(),
  );

  // Exported role: node:public:administrator member.
  $roles['node:public:administrator member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'public',
    'name' => 'administrator member',
    'permissions' => array(
      'access all webform results' => TRUE,
      'add user' => TRUE,
      'administer group' => TRUE,
      'approve and deny subscription' => TRUE,
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'create public content' => TRUE,
      'delete all webform submissions' => TRUE,
      'delete any alfresco_item content' => TRUE,
      'delete any article content' => TRUE,
      'delete any book content' => TRUE,
      'delete any forum content' => TRUE,
      'delete any public content' => TRUE,
      'delete any webform content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'delete own public content' => TRUE,
      'edit all webform submissions' => TRUE,
      'manage members' => TRUE,
      'manage permissions' => TRUE,
      'manage roles' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any book content' => TRUE,
      'update any forum content' => TRUE,
      'update any public content' => TRUE,
      'update any webform content' => TRUE,
      'update group' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
      'update own public content' => TRUE,
    ),
  );

  // Exported role: node:public:group contributor.
  $roles['node:public:group contributor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'public',
    'name' => 'group contributor',
    'permissions' => array(
      'create alfresco_item content' => TRUE,
      'create article content' => TRUE,
      'create book content' => TRUE,
      'create forum content' => TRUE,
      'delete own alfresco_item content' => TRUE,
      'delete own article content' => TRUE,
      'delete own book content' => TRUE,
      'delete own forum content' => TRUE,
      'unsubscribe' => TRUE,
      'update any alfresco_item content' => TRUE,
      'update any article content' => TRUE,
      'update any forum content' => TRUE,
      'update own alfresco_item content' => TRUE,
      'update own article content' => TRUE,
      'update own book content' => TRUE,
      'update own forum content' => TRUE,
    ),
  );

  // Exported role: node:public:member.
  $roles['node:public:member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'public',
    'name' => 'member',
    'permissions' => array(
      'access own webform submissions' => TRUE,
      'create group_node content' => TRUE,
      'create orga content' => TRUE,
      'create webform content' => TRUE,
      'delete any group_node content' => TRUE,
      'delete any orga content' => TRUE,
      'delete own group_node content' => TRUE,
      'delete own orga content' => TRUE,
      'delete own webform content' => TRUE,
      'delete own webform submissions' => TRUE,
      'edit own webform submissions' => TRUE,
      'unsubscribe' => TRUE,
      'update any group_node content' => TRUE,
      'update any orga content' => TRUE,
      'update own group_node content' => TRUE,
      'update own orga content' => TRUE,
      'update own webform content' => TRUE,
    ),
  );

  // Exported role: node:public:non-member.
  $roles['node:public:non-member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'public',
    'name' => 'non-member',
    'permissions' => array(
      'subscribe' => TRUE,
    ),
  );

  // Exported role: node:public:read only member.
  $roles['node:public:read only member'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'public',
    'name' => 'read only member',
    'permissions' => array(),
  );

  return $roles;
}
