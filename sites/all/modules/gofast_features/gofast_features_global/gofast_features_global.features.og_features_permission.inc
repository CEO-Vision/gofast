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

  // Exported og permission: 'node:group:add user'
  $permissions['node:group:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:administer group'
  $permissions['node:group:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:administer spaces'
  $permissions['node:group:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:approve and deny subscription'
  $permissions['node:group:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:archive space'
  $permissions['node:group:archive space'] = array(
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

  // Exported og permission: 'node:group:delete any forum content'
  $permissions['node:group:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
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

  // Exported og permission: 'node:group:delete own forum content'
  $permissions['node:group:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
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

  // Exported og permission: 'node:group:manage members'
  $permissions['node:group:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:group:manage permissions'
  $permissions['node:group:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:manage roles'
  $permissions['node:group:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:subscribe'
  $permissions['node:group:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:group:subscribe without approval'
  $permissions['node:group:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:group:unsubscribe'
  $permissions['node:group:unsubscribe'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
      'member' => 'member',
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

  // Exported og permission: 'node:group:update any forum content'
  $permissions['node:group:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
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

  // Exported og permission: 'node:organisation:add user'
  $permissions['node:organisation:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:administer group'
  $permissions['node:organisation:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:administer spaces'
  $permissions['node:organisation:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:approve and deny subscription'
  $permissions['node:organisation:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:archive space'
  $permissions['node:organisation:archive space'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create alfresco_item content'
  $permissions['node:organisation:create alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:create article content'
  $permissions['node:organisation:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:create book content'
  $permissions['node:organisation:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:create extranet content'
  $permissions['node:organisation:create extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create forum content'
  $permissions['node:organisation:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:create group content'
  $permissions['node:organisation:create group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create kanban content'
  $permissions['node:organisation:create kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create organisation content'
  $permissions['node:organisation:create organisation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:create page content'
  $permissions['node:organisation:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create public content'
  $permissions['node:organisation:create public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:create task content'
  $permissions['node:organisation:create task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:create webform content'
  $permissions['node:organisation:create webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete any alfresco_item content'
  $permissions['node:organisation:delete any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any article content'
  $permissions['node:organisation:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any book content'
  $permissions['node:organisation:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any extranet content'
  $permissions['node:organisation:delete any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete any forum content'
  $permissions['node:organisation:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any group content'
  $permissions['node:organisation:delete any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete any kanban content'
  $permissions['node:organisation:delete any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete any organisation content'
  $permissions['node:organisation:delete any organisation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any page content'
  $permissions['node:organisation:delete any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete any public content'
  $permissions['node:organisation:delete any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete any task content'
  $permissions['node:organisation:delete any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete any webform content'
  $permissions['node:organisation:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete own alfresco_item content'
  $permissions['node:organisation:delete own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete own article content'
  $permissions['node:organisation:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete own book content'
  $permissions['node:organisation:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete own extranet content'
  $permissions['node:organisation:delete own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete own forum content'
  $permissions['node:organisation:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete own group content'
  $permissions['node:organisation:delete own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete own kanban content'
  $permissions['node:organisation:delete own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete own organisation content'
  $permissions['node:organisation:delete own organisation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:delete own page content'
  $permissions['node:organisation:delete own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete own public content'
  $permissions['node:organisation:delete own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:delete own task content'
  $permissions['node:organisation:delete own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:delete own webform content'
  $permissions['node:organisation:delete own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:manage members'
  $permissions['node:organisation:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:manage permissions'
  $permissions['node:organisation:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:manage roles'
  $permissions['node:organisation:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:subscribe'
  $permissions['node:organisation:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:organisation:subscribe without approval'
  $permissions['node:organisation:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:unsubscribe'
  $permissions['node:organisation:unsubscribe'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:organisation:update any alfresco_item content'
  $permissions['node:organisation:update any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update any article content'
  $permissions['node:organisation:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update any book content'
  $permissions['node:organisation:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update any extranet content'
  $permissions['node:organisation:update any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update any forum content'
  $permissions['node:organisation:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update any group content'
  $permissions['node:organisation:update any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update any kanban content'
  $permissions['node:organisation:update any kanban content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update any organisation content'
  $permissions['node:organisation:update any organisation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update any page content'
  $permissions['node:organisation:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update any public content'
  $permissions['node:organisation:update any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update any task content'
  $permissions['node:organisation:update any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update any webform content'
  $permissions['node:organisation:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update group'
  $permissions['node:organisation:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update own alfresco_item content'
  $permissions['node:organisation:update own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update own article content'
  $permissions['node:organisation:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update own book content'
  $permissions['node:organisation:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update own extranet content'
  $permissions['node:organisation:update own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update own forum content'
  $permissions['node:organisation:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update own group content'
  $permissions['node:organisation:update own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update own kanban content'
  $permissions['node:organisation:update own kanban content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update own organisation content'
  $permissions['node:organisation:update own organisation content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:organisation:update own page content'
  $permissions['node:organisation:update own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update own public content'
  $permissions['node:organisation:update own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:organisation:update own task content'
  $permissions['node:organisation:update own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:organisation:update own webform content'
  $permissions['node:organisation:update own webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:add user'
  $permissions['node:private_space:add user'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:administer group'
  $permissions['node:private_space:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:administer spaces'
  $permissions['node:private_space:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:approve and deny subscription'
  $permissions['node:private_space:approve and deny subscription'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:archive space'
  $permissions['node:private_space:archive space'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create alfresco_item content'
  $permissions['node:private_space:create alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:create article content'
  $permissions['node:private_space:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:create book content'
  $permissions['node:private_space:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:create extranet content'
  $permissions['node:private_space:create extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create forum content'
  $permissions['node:private_space:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:create group content'
  $permissions['node:private_space:create group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create kanban content'
  $permissions['node:private_space:create kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create organisation content'
  $permissions['node:private_space:create organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create page content'
  $permissions['node:private_space:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create public content'
  $permissions['node:private_space:create public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create task content'
  $permissions['node:private_space:create task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:create webform content'
  $permissions['node:private_space:create webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:private_space:delete any alfresco_item content'
  $permissions['node:private_space:delete any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:delete any article content'
  $permissions['node:private_space:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:delete any book content'
  $permissions['node:private_space:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:delete any extranet content'
  $permissions['node:private_space:delete any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any forum content'
  $permissions['node:private_space:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:delete any group content'
  $permissions['node:private_space:delete any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any kanban content'
  $permissions['node:private_space:delete any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any organisation content'
  $permissions['node:private_space:delete any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any page content'
  $permissions['node:private_space:delete any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any public content'
  $permissions['node:private_space:delete any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any task content'
  $permissions['node:private_space:delete any task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete any webform content'
  $permissions['node:private_space:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:delete own alfresco_item content'
  $permissions['node:private_space:delete own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:delete own article content'
  $permissions['node:private_space:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:delete own book content'
  $permissions['node:private_space:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:delete own extranet content'
  $permissions['node:private_space:delete own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own forum content'
  $permissions['node:private_space:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:delete own group content'
  $permissions['node:private_space:delete own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own kanban content'
  $permissions['node:private_space:delete own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own organisation content'
  $permissions['node:private_space:delete own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own page content'
  $permissions['node:private_space:delete own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own public content'
  $permissions['node:private_space:delete own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own task content'
  $permissions['node:private_space:delete own task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:delete own webform content'
  $permissions['node:private_space:delete own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:private_space:manage members'
  $permissions['node:private_space:manage members'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:manage permissions'
  $permissions['node:private_space:manage permissions'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:manage roles'
  $permissions['node:private_space:manage roles'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:subscribe'
  $permissions['node:private_space:subscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:subscribe without approval'
  $permissions['node:private_space:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:unsubscribe'
  $permissions['node:private_space:unsubscribe'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any alfresco_item content'
  $permissions['node:private_space:update any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update any article content'
  $permissions['node:private_space:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update any book content'
  $permissions['node:private_space:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:update any extranet content'
  $permissions['node:private_space:update any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any forum content'
  $permissions['node:private_space:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update any group content'
  $permissions['node:private_space:update any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any kanban content'
  $permissions['node:private_space:update any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any organisation content'
  $permissions['node:private_space:update any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any page content'
  $permissions['node:private_space:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any public content'
  $permissions['node:private_space:update any public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any task content'
  $permissions['node:private_space:update any task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update any webform content'
  $permissions['node:private_space:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:private_space:update group'
  $permissions['node:private_space:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group administrator' => 'group administrator',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update own alfresco_item content'
  $permissions['node:private_space:update own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update own article content'
  $permissions['node:private_space:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update own book content'
  $permissions['node:private_space:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update own extranet content'
  $permissions['node:private_space:update own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own forum content'
  $permissions['node:private_space:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:private_space:update own group content'
  $permissions['node:private_space:update own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own kanban content'
  $permissions['node:private_space:update own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own organisation content'
  $permissions['node:private_space:update own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own page content'
  $permissions['node:private_space:update own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own public content'
  $permissions['node:private_space:update own public content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own task content'
  $permissions['node:private_space:update own task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:private_space:update own webform content'
  $permissions['node:private_space:update own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:public:add user'
  $permissions['node:public:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:administer group'
  $permissions['node:public:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:administer spaces'
  $permissions['node:public:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:approve and deny subscription'
  $permissions['node:public:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:archive space'
  $permissions['node:public:archive space'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create alfresco_item content'
  $permissions['node:public:create alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:create article content'
  $permissions['node:public:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:create book content'
  $permissions['node:public:create book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:create extranet content'
  $permissions['node:public:create extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create forum content'
  $permissions['node:public:create forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:create group content'
  $permissions['node:public:create group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create kanban content'
  $permissions['node:public:create kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create organisation content'
  $permissions['node:public:create organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create page content'
  $permissions['node:public:create page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create public content'
  $permissions['node:public:create public content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:create task content'
  $permissions['node:public:create task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:create webform content'
  $permissions['node:public:create webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:public:delete any alfresco_item content'
  $permissions['node:public:delete any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete any article content'
  $permissions['node:public:delete any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete any book content'
  $permissions['node:public:delete any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete any extranet content'
  $permissions['node:public:delete any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any forum content'
  $permissions['node:public:delete any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete any group content'
  $permissions['node:public:delete any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any kanban content'
  $permissions['node:public:delete any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any organisation content'
  $permissions['node:public:delete any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any page content'
  $permissions['node:public:delete any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any public content'
  $permissions['node:public:delete any public content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete any task content'
  $permissions['node:public:delete any task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete any webform content'
  $permissions['node:public:delete any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete own alfresco_item content'
  $permissions['node:public:delete own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:delete own article content'
  $permissions['node:public:delete own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:delete own book content'
  $permissions['node:public:delete own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:delete own extranet content'
  $permissions['node:public:delete own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own forum content'
  $permissions['node:public:delete own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:delete own group content'
  $permissions['node:public:delete own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own kanban content'
  $permissions['node:public:delete own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own organisation content'
  $permissions['node:public:delete own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own page content'
  $permissions['node:public:delete own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own public content'
  $permissions['node:public:delete own public content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:delete own task content'
  $permissions['node:public:delete own task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:delete own webform content'
  $permissions['node:public:delete own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:public:manage members'
  $permissions['node:public:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:manage permissions'
  $permissions['node:public:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:manage roles'
  $permissions['node:public:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:subscribe'
  $permissions['node:public:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:public:subscribe without approval'
  $permissions['node:public:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:unsubscribe'
  $permissions['node:public:unsubscribe'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:public:update any alfresco_item content'
  $permissions['node:public:update any alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:update any article content'
  $permissions['node:public:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update any book content'
  $permissions['node:public:update any book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update any extranet content'
  $permissions['node:public:update any extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any forum content'
  $permissions['node:public:update any forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update any group content'
  $permissions['node:public:update any group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any kanban content'
  $permissions['node:public:update any kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any organisation content'
  $permissions['node:public:update any organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any page content'
  $permissions['node:public:update any page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any public content'
  $permissions['node:public:update any public content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update any task content'
  $permissions['node:public:update any task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update any webform content'
  $permissions['node:public:update any webform content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update group'
  $permissions['node:public:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update own alfresco_item content'
  $permissions['node:public:update own alfresco_item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:update own article content'
  $permissions['node:public:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:update own book content'
  $permissions['node:public:update own book content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:update own extranet content'
  $permissions['node:public:update own extranet content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own forum content'
  $permissions['node:public:update own forum content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'group contributor' => 'group contributor',
    ),
  );

  // Exported og permission: 'node:public:update own group content'
  $permissions['node:public:update own group content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own kanban content'
  $permissions['node:public:update own kanban content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own organisation content'
  $permissions['node:public:update own organisation content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own page content'
  $permissions['node:public:update own page content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own public content'
  $permissions['node:public:update own public content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:public:update own task content'
  $permissions['node:public:update own task content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:public:update own webform content'
  $permissions['node:public:update own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:add user'
  $permissions['node:userlist:add user'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:administer group'
  $permissions['node:userlist:administer group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:administer spaces'
  $permissions['node:userlist:administer spaces'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:userlist:approve and deny subscription'
  $permissions['node:userlist:approve and deny subscription'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:archive space'
  $permissions['node:userlist:archive space'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:create alfresco_item content'
  $permissions['node:userlist:create alfresco_item content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create article content'
  $permissions['node:userlist:create article content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create book content'
  $permissions['node:userlist:create book content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create conference content'
  $permissions['node:userlist:create conference content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create extranet content'
  $permissions['node:userlist:create extranet content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create forum content'
  $permissions['node:userlist:create forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create group content'
  $permissions['node:userlist:create group content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create organisation content'
  $permissions['node:userlist:create organisation content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create page content'
  $permissions['node:userlist:create page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create public content'
  $permissions['node:userlist:create public content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:create userlist content'
  $permissions['node:userlist:create userlist content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:create webform content'
  $permissions['node:userlist:create webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any alfresco_item content'
  $permissions['node:userlist:delete any alfresco_item content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any article content'
  $permissions['node:userlist:delete any article content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any book content'
  $permissions['node:userlist:delete any book content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any conference content'
  $permissions['node:userlist:delete any conference content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any extranet content'
  $permissions['node:userlist:delete any extranet content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any forum content'
  $permissions['node:userlist:delete any forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any group content'
  $permissions['node:userlist:delete any group content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any organisation content'
  $permissions['node:userlist:delete any organisation content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any page content'
  $permissions['node:userlist:delete any page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any public content'
  $permissions['node:userlist:delete any public content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete any userlist content'
  $permissions['node:userlist:delete any userlist content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:userlist:delete any webform content'
  $permissions['node:userlist:delete any webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own alfresco_item content'
  $permissions['node:userlist:delete own alfresco_item content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own article content'
  $permissions['node:userlist:delete own article content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own book content'
  $permissions['node:userlist:delete own book content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own conference content'
  $permissions['node:userlist:delete own conference content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own extranet content'
  $permissions['node:userlist:delete own extranet content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own forum content'
  $permissions['node:userlist:delete own forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own group content'
  $permissions['node:userlist:delete own group content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own organisation content'
  $permissions['node:userlist:delete own organisation content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own page content'
  $permissions['node:userlist:delete own page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own public content'
  $permissions['node:userlist:delete own public content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own userlist content'
  $permissions['node:userlist:delete own userlist content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:delete own webform content'
  $permissions['node:userlist:delete own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:manage members'
  $permissions['node:userlist:manage members'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:manage permissions'
  $permissions['node:userlist:manage permissions'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:manage roles'
  $permissions['node:userlist:manage roles'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:subscribe'
  $permissions['node:userlist:subscribe'] = array(
    'roles' => array(
      'non-member' => 'non-member',
    ),
  );

  // Exported og permission: 'node:userlist:subscribe without approval'
  $permissions['node:userlist:subscribe without approval'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:userlist:unsubscribe'
  $permissions['node:userlist:unsubscribe'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any alfresco_item content'
  $permissions['node:userlist:update any alfresco_item content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any article content'
  $permissions['node:userlist:update any article content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any book content'
  $permissions['node:userlist:update any book content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any conference content'
  $permissions['node:userlist:update any conference content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any extranet content'
  $permissions['node:userlist:update any extranet content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any forum content'
  $permissions['node:userlist:update any forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any group content'
  $permissions['node:userlist:update any group content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any organisation content'
  $permissions['node:userlist:update any organisation content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any page content'
  $permissions['node:userlist:update any page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any public content'
  $permissions['node:userlist:update any public content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update any userlist content'
  $permissions['node:userlist:update any userlist content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:userlist:update any webform content'
  $permissions['node:userlist:update any webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update group'
  $permissions['node:userlist:update group'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:update own alfresco_item content'
  $permissions['node:userlist:update own alfresco_item content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own article content'
  $permissions['node:userlist:update own article content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own book content'
  $permissions['node:userlist:update own book content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own conference content'
  $permissions['node:userlist:update own conference content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own extranet content'
  $permissions['node:userlist:update own extranet content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own forum content'
  $permissions['node:userlist:update own forum content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own group content'
  $permissions['node:userlist:update own group content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own organisation content'
  $permissions['node:userlist:update own organisation content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own page content'
  $permissions['node:userlist:update own page content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own public content'
  $permissions['node:userlist:update own public content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:userlist:update own userlist content'
  $permissions['node:userlist:update own userlist content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:userlist:update own webform content'
  $permissions['node:userlist:update own webform content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  return $permissions;
}
