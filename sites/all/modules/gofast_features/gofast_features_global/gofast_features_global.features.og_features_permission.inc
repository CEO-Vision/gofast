<?php
/**
 * @file
 * gofast_features_global.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function gofast_features_global_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:extranet:add user'
  $permissions['node:extranet:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:administer group'
  $permissions['node:extranet:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:administer spaces'
  $permissions['node:extranet:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:approve and deny subscription'
  $permissions['node:extranet:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:archive space'
  $permissions['node:extranet:archive space'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:create alfresco_item content'
  $permissions['node:extranet:create alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:create article content'
  $permissions['node:extranet:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:create book content'
  $permissions['node:extranet:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:create extranet content'
  $permissions['node:extranet:create extranet content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:create forum content'
  $permissions['node:extranet:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:create group content'
  $permissions['node:extranet:create group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:create kanban content'
  $permissions['node:extranet:create kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:create organisation content'
  $permissions['node:extranet:create organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:create page content'
  $permissions['node:extranet:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:create public content'
  $permissions['node:extranet:create public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:create task content'
  $permissions['node:extranet:create task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:create webform content'
  $permissions['node:extranet:create webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete any alfresco_item content'
  $permissions['node:extranet:delete any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any article content'
  $permissions['node:extranet:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any book content'
  $permissions['node:extranet:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any extranet content'
  $permissions['node:extranet:delete any extranet content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any forum content'
  $permissions['node:extranet:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any group content'
  $permissions['node:extranet:delete any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete any kanban content'
  $permissions['node:extranet:delete any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete any organisation content'
  $permissions['node:extranet:delete any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete any page content'
  $permissions['node:extranet:delete any page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any public content'
  $permissions['node:extranet:delete any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete any task content'
  $permissions['node:extranet:delete any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete any webform content'
  $permissions['node:extranet:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete own alfresco_item content'
  $permissions['node:extranet:delete own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete own article content'
  $permissions['node:extranet:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete own book content'
  $permissions['node:extranet:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete own extranet content'
  $permissions['node:extranet:delete own extranet content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:delete own forum content'
  $permissions['node:extranet:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete own group content'
  $permissions['node:extranet:delete own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete own kanban content'
  $permissions['node:extranet:delete own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete own organisation content'
  $permissions['node:extranet:delete own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete own page content'
  $permissions['node:extranet:delete own page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:extranet:delete own public content'
  $permissions['node:extranet:delete own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:delete own task content'
  $permissions['node:extranet:delete own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:delete own webform content'
  $permissions['node:extranet:delete own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:manage members'
  $permissions['node:extranet:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:manage permissions'
  $permissions['node:extranet:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:manage roles'
  $permissions['node:extranet:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:subscribe'
  $permissions['node:extranet:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:extranet:subscribe without approval'
  $permissions['node:extranet:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:unsubscribe'
  $permissions['node:extranet:unsubscribe'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:extranet:update any alfresco_item content'
  $permissions['node:extranet:update any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update any article content'
  $permissions['node:extranet:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update any book content'
  $permissions['node:extranet:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update any extranet content'
  $permissions['node:extranet:update any extranet content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update any forum content'
  $permissions['node:extranet:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update any group content'
  $permissions['node:extranet:update any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update any kanban content'
  $permissions['node:extranet:update any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update any organisation content'
  $permissions['node:extranet:update any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update any page content'
  $permissions['node:extranet:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update any public content'
  $permissions['node:extranet:update any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update any task content'
  $permissions['node:extranet:update any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update any webform content'
  $permissions['node:extranet:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update group'
  $permissions['node:extranet:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update own alfresco_item content'
  $permissions['node:extranet:update own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update own article content'
  $permissions['node:extranet:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update own book content'
  $permissions['node:extranet:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update own extranet content'
  $permissions['node:extranet:update own extranet content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:extranet:update own forum content'
  $permissions['node:extranet:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update own group content'
  $permissions['node:extranet:update own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update own kanban content'
  $permissions['node:extranet:update own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update own organisation content'
  $permissions['node:extranet:update own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update own page content'
  $permissions['node:extranet:update own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update own public content'
  $permissions['node:extranet:update own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:extranet:update own task content'
  $permissions['node:extranet:update own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:extranet:update own webform content'
  $permissions['node:extranet:update own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:administer group'
  $permissions['node:group:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:create alfresco_item content'
  $permissions['node:group:create alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:create article content'
  $permissions['node:group:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:create book content'
  $permissions['node:group:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:create extranet content'
  $permissions['node:group:create extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create forum content'
  $permissions['node:group:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:create group content'
  $permissions['node:group:create group content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:create kanban content'
  $permissions['node:group:create kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create organisation content'
  $permissions['node:group:create organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create page content'
  $permissions['node:group:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create public content'
  $permissions['node:group:create public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:create task content'
  $permissions['node:group:create task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:create webform content'
  $permissions['node:group:create webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:delete any alfresco_item content'
  $permissions['node:group:delete any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any article content'
  $permissions['node:group:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any book content'
  $permissions['node:group:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any extranet content'
  $permissions['node:group:delete any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any group content'
  $permissions['node:group:delete any group content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any kanban content'
  $permissions['node:group:delete any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any organisation content'
  $permissions['node:group:delete any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any page content'
  $permissions['node:group:delete any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any public content'
  $permissions['node:group:delete any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete any task content'
  $permissions['node:group:delete any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete any webform content'
  $permissions['node:group:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own alfresco_item content'
  $permissions['node:group:delete own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:delete own article content'
  $permissions['node:group:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:delete own book content'
  $permissions['node:group:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:delete own extranet content'
  $permissions['node:group:delete own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own group content'
  $permissions['node:group:delete own group content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:delete own kanban content'
  $permissions['node:group:delete own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own organisation content'
  $permissions['node:group:delete own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own page content'
  $permissions['node:group:delete own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own public content'
  $permissions['node:group:delete own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:delete own task content'
  $permissions['node:group:delete own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:delete own webform content'
  $permissions['node:group:delete own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update any alfresco_item content'
  $permissions['node:group:update any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update any article content'
  $permissions['node:group:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update any book content'
  $permissions['node:group:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any extranet content'
  $permissions['node:group:update any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any group content'
  $permissions['node:group:update any group content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any kanban content'
  $permissions['node:group:update any kanban content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update any organisation content'
  $permissions['node:group:update any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any page content'
  $permissions['node:group:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any public content'
  $permissions['node:group:update any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update any task content'
  $permissions['node:group:update any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update any webform content'
  $permissions['node:group:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update group'
  $permissions['node:group:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own alfresco_item content'
  $permissions['node:group:update own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update own article content'
  $permissions['node:group:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update own book content'
  $permissions['node:group:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update own extranet content'
  $permissions['node:group:update own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own forum content'
  $permissions['node:group:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update own group content'
  $permissions['node:group:update own group content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own kanban content'
  $permissions['node:group:update own kanban content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:update own organisation content'
  $permissions['node:group:update own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own page content'
  $permissions['node:group:update own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own public content'
  $permissions['node:group:update own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:update own task content'
  $permissions['node:group:update own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:group:update own webform content'
  $permissions['node:group:update own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  return $permissions;
}
