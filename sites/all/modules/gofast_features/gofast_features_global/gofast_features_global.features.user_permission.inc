<?php
/**
 * @file
 * gofast_features_global.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gofast_features_global_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access audit'.
  $permissions['access audit'] = array(
    'name' => 'access audit',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_audit',
  );

  // Exported permission: 'access all views'.
  $permissions['access all views'] = array(
    'name' => 'access all views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'access all webform results'.
  $permissions['access all webform results'] = array(
    'name' => 'access all webform results',
    'roles' => array(),
    'module' => 'webform',
  );

  // Exported permission: 'access backup and migrate'.
  $permissions['access backup and migrate'] = array(
    'name' => 'access backup and migrate',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access backup files'.
  $permissions['access backup files'] = array(
    'name' => 'access backup files',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access cmis'.
  $permissions['access cmis'] = array(
    'name' => 'access cmis',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'cmis',
  );

  // Exported permission: 'access comments'.
  $permissions['access comments'] = array(
    'name' => 'access comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'access content overview'.
  $permissions['access content overview'] = array(
    'name' => 'access content overview',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'access contextual links'.
  $permissions['access contextual links'] = array(
    'name' => 'access contextual links',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'contextual',
  );

  // Exported permission: 'access dashboard'.
  $permissions['access dashboard'] = array(
    'name' => 'access dashboard',
    'roles' => array(),
    'module' => 'dashboard',
  );

  // Exported permission: 'access news feeds'.
  $permissions['access news feeds'] = array(
    'name' => 'access news feeds',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'aggregator',
  );

  // Exported permission: 'access own webform results'.
  $permissions['access own webform results'] = array(
    'name' => 'access own webform results',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access own webform submissions'.
  $permissions['access own webform submissions'] = array(
    'name' => 'access own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'access printer-friendly version'.
  $permissions['access printer-friendly version'] = array(
    'name' => 'access printer-friendly version',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'book',
  );

  // Exported permission: 'access space info not member'.
  $permissions['access space info not member'] = array(
    'name' => 'access space info not member',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_og',
  );

  // Exported permission: 'access statistics'.
  $permissions['access statistics'] = array(
    'name' => 'access statistics',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'access toolbar'.
  $permissions['access toolbar'] = array(
    'name' => 'access toolbar',
    'roles' => array(),
    'module' => 'toolbar',
  );

  // Exported permission: 'access user profiles'.
  $permissions['access user profiles'] = array(
    'name' => 'access user profiles',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user',
  );

  // Exported permission: 'access vote up/down statistics'.
  $permissions['access vote up/down statistics'] = array(
    'name' => 'access vote up/down statistics',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vud',
  );

  // Exported permission: 'add content to books'.
  $permissions['add content to books'] = array(
    'name' => 'add content to books',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'book',
  );

  // Exported permission: 'add userpoints'.
  $permissions['add userpoints'] = array(
    'name' => 'add userpoints',
    'roles' => array(),
    'module' => 'userpoints',
  );

  // Exported permission: 'administer actions'.
  $permissions['administer actions'] = array(
    'name' => 'administer actions',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer advanced forum'.
  $permissions['administer advanced forum'] = array(
    'name' => 'administer advanced forum',
    'roles' => array(),
    'module' => 'advanced_forum',
  );

  // Exported permission: 'administer backup and migrate'.
  $permissions['administer backup and migrate'] = array(
    'name' => 'administer backup and migrate',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'administer blocks'.
  $permissions['administer blocks'] = array(
    'name' => 'administer blocks',
    'roles' => array(),
    'module' => 'block',
  );

  // Exported permission: 'administer book outlines'.
  $permissions['administer book outlines'] = array(
    'name' => 'administer book outlines',
    'roles' => array(),
    'module' => 'book',
  );

  // Exported permission: 'administer categories configuration'.
  $permissions['administer categories configuration'] = array(
    'name' => 'administer categories configuration',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer ckeditor'.
  $permissions['administer ckeditor'] = array(
    'name' => 'administer ckeditor',
    'roles' => array(),
    'module' => 'ckeditor',
  );

  // Exported permission: 'administer ckeditor link'.
  $permissions['administer ckeditor link'] = array(
    'name' => 'administer ckeditor link',
    'roles' => array(),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'administer cmis'.
  $permissions['administer cmis'] = array(
    'name' => 'administer cmis',
    'roles' => array(),
    'module' => 'cmis',
  );

  // Exported permission: 'administer comments'.
  $permissions['administer comments'] = array(
    'name' => 'administer comments',
    'roles' => array(),
    'module' => 'comment',
  );

  // Exported permission: 'administer content translations'.
  $permissions['administer content translations'] = array(
    'name' => 'administer content translations',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'i18n_node',
  );

  // Exported permission: 'administer content types'.
  $permissions['administer content types'] = array(
    'name' => 'administer content types',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer custom link configuration'.
  $permissions['administer custom link configuration'] = array(
    'name' => 'administer custom link configuration',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer documents configuration'.
  $permissions['administer documents configuration'] = array(
    'name' => 'administer documents configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer elysia_cron'.
  $permissions['administer elysia_cron'] = array(
    'name' => 'administer elysia_cron',
    'roles' => array(),
    'module' => 'elysia_cron',
  );

  // Exported permission: 'administer facets'.
  $permissions['administer facets'] = array(
    'name' => 'administer facets',
    'roles' => array(),
    'module' => 'facetapi',
  );

  // Exported permission: 'administer features'.
  $permissions['administer features'] = array(
    'name' => 'administer features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'administer fieldgroups'.
  $permissions['administer fieldgroups'] = array(
    'name' => 'administer fieldgroups',
    'roles' => array(),
    'module' => 'field_group',
  );

  // Exported permission: 'administer filters'.
  $permissions['administer filters'] = array(
    'name' => 'administer filters',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'administer flags'.
  $permissions['administer flags'] = array(
    'name' => 'administer flags',
    'roles' => array(),
    'module' => 'flag',
  );

  // Exported permission: 'administer forums'.
  $permissions['administer forums'] = array(
    'name' => 'administer forums',
    'roles' => array(),
    'module' => 'forum',
  );

  // Exported permission: 'administer general configuration'.
  $permissions['administer general configuration'] = array(
    'name' => 'administer general configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(),
    'module' => 'og',
  );

  // Exported permission: 'administer history_js'.
  $permissions['administer history_js'] = array(
    'name' => 'administer history_js',
    'roles' => array(),
    'module' => 'history_js',
  );

  // Exported permission: 'administer image styles'.
  $permissions['administer image styles'] = array(
    'name' => 'administer image styles',
    'roles' => array(),
    'module' => 'image',
  );

  // Exported permission: 'administer import ldap'.
  $permissions['administer import ldap'] = array(
    'name' => 'administer import ldap',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer index configuration'.
  $permissions['administer index configuration'] = array(
    'name' => 'administer index configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer integrity configuration'.
  $permissions['administer integrity configuration'] = array(
    'name' => 'administer integrity configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer languages'.
  $permissions['administer languages'] = array(
    'name' => 'administer languages',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: 'administer ldap configuration'.
  $permissions['administer ldap configuration'] = array(
    'name' => 'administer ldap configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer mailsystem'.
  $permissions['administer mailsystem'] = array(
    'name' => 'administer mailsystem',
    'roles' => array(),
    'module' => 'mailsystem',
  );

  // Exported permission: 'administer menu'.
  $permissions['administer menu'] = array(
    'name' => 'administer menu',
    'roles' => array(),
    'module' => 'menu',
  );

  // Exported permission: 'administer modules'.
  $permissions['administer modules'] = array(
    'name' => 'administer modules',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer news feeds'.
  $permissions['administer news feeds'] = array(
    'name' => 'administer news feeds',
    'roles' => array(),
    'module' => 'aggregator',
  );

  // Exported permission: 'administer nodes'.
  $permissions['administer nodes'] = array(
    'name' => 'administer nodes',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'administer pastell configuration'.
  $permissions['administer pastell configuration'] = array(
    'name' => 'administer pastell configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer permissions'.
  $permissions['administer permissions'] = array(
    'name' => 'administer permissions',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'administer phpmailer settings'.
  $permissions['administer phpmailer settings'] = array(
    'name' => 'administer phpmailer settings',
    'roles' => array(),
    'module' => 'phpmailer',
  );

  // Exported permission: 'administer privatemsg settings'.
  $permissions['administer privatemsg settings'] = array(
    'name' => 'administer privatemsg settings',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'administer radioactivity'.
  $permissions['administer radioactivity'] = array(
    'name' => 'administer radioactivity',
    'roles' => array(),
    'module' => 'radioactivity',
  );

  // Exported permission: 'administer retention configuration'.
  $permissions['administer retention configuration'] = array(
    'name' => 'administer retention configuration',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer revisions'.
  $permissions['administer revisions'] = array(
    'name' => 'administer revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'gofast_cmis',
  );

  // Exported permission: 'administer roles'.
  $permissions['administer roles'] = array(
    'name' => 'administer roles',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_user',
  );

  // Exported permission: 'administer rss configuration'.
  $permissions['administer rss configuration'] = array(
    'name' => 'administer rss configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer search'.
  $permissions['administer search'] = array(
    'name' => 'administer search',
    'roles' => array(),
    'module' => 'search',
  );

  // Exported permission: 'administer shortcuts'.
  $permissions['administer shortcuts'] = array(
    'name' => 'administer shortcuts',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'administer signature configuration'.
  $permissions['administer signature configuration'] = array(
    'name' => 'administer signature configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer smtp configuration'.
  $permissions['administer smtp configuration'] = array(
    'name' => 'administer smtp configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer software updates'.
  $permissions['administer software updates'] = array(
    'name' => 'administer software updates',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'administer spaces'.
  $permissions['administer spaces'] = array(
    'name' => 'administer spaces',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'gofast_og',
  );

  // Exported permission: 'administer spaces configuration'.
  $permissions['administer spaces configuration'] = array(
    'name' => 'administer spaces configuration',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer sso configuration'.
  $permissions['administer sso configuration'] = array(
    'name' => 'administer sso configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer tags configuration'.
  $permissions['administer tags configuration'] = array(
    'name' => 'administer tags configuration',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer themes'.
  $permissions['administer themes'] = array(
    'name' => 'administer themes',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'administer user relationships'.
  $permissions['administer user relationships'] = array(
    'name' => 'administer user relationships',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'user_relationships',
  );

  // Exported permission: 'administer userpoints'.
  $permissions['administer userpoints'] = array(
    'name' => 'administer userpoints',
    'roles' => array(),
    'module' => 'userpoints',
  );

  // Exported permission: 'administer users'.
  $permissions['administer users'] = array(
    'name' => 'administer users',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'user',
  );

  // Exported permission: 'administer users configuration'.
  $permissions['administer users configuration'] = array(
    'name' => 'administer users configuration',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer views'.
  $permissions['administer views'] = array(
    'name' => 'administer views',
    'roles' => array(),
    'module' => 'views',
  );

  // Exported permission: 'administer visibility configuration'.
  $permissions['administer visibility configuration'] = array(
    'name' => 'administer visibility configuration',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast',
  );

  // Exported permission: 'administer vote up/down'.
  $permissions['administer vote up/down'] = array(
    'name' => 'administer vote up/down',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vud',
  );

  // Exported permission: 'administer vote up/down on comments'.
  $permissions['administer vote up/down on comments'] = array(
    'name' => 'administer vote up/down on comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud_comment',
  );

  // Exported permission: 'administer vote up/down on nodes'.
  $permissions['administer vote up/down on nodes'] = array(
    'name' => 'administer vote up/down on nodes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vud_node',
  );

  // Exported permission: 'administer voting api'.
  $permissions['administer voting api'] = array(
    'name' => 'administer voting api',
    'roles' => array(),
    'module' => 'votingapi',
  );

  // Exported permission: 'allow disabling privatemsg'.
  $permissions['allow disabling privatemsg'] = array(
    'name' => 'allow disabling privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'archive space'.
  $permissions['archive space'] = array(
    'name' => 'archive space',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'gofast_og',
  );

  // Exported permission: 'block IP addresses'.
  $permissions['block IP addresses'] = array(
    'name' => 'block IP addresses',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'bypass advanced aggregation'.
  $permissions['bypass advanced aggregation'] = array(
    'name' => 'bypass advanced aggregation',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'advagg',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'contact administrators'.
  $permissions['contact administrators'] = array(
    'name' => 'contact administrators',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_og',
  );

  // Exported permission: 'create alfresco_item content'.
  $permissions['create alfresco_item content'] = array(
    'name' => 'create alfresco_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create article content'.
  $permissions['create article content'] = array(
    'name' => 'create article content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create book content'.
  $permissions['create book content'] = array(
    'name' => 'create book content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create conference content'.
  $permissions['create conference content'] = array(
    'name' => 'create conference content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create contact content'.
  $permissions['create contact content'] = array(
    'name' => 'create contact content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create extranet content'.
  $permissions['create extranet content'] = array(
    'name' => 'create extranet content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create forum content'.
  $permissions['create forum content'] = array(
    'name' => 'create forum content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create group content'.
  $permissions['create group content'] = array(
    'name' => 'create group content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create kanban content'.
  $permissions['create kanban content'] = array(
    'name' => 'create kanban content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create new books'.
  $permissions['create new books'] = array(
    'name' => 'create new books',
    'roles' => array(
      'administrator' => 'administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'book',
  );

  // Exported permission: 'create organisation content'.
  $permissions['create organisation content'] = array(
    'name' => 'create organisation content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create page content'.
  $permissions['create page content'] = array(
    'name' => 'create page content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create private_space content'.
  $permissions['create private_space content'] = array(
    'name' => 'create private_space content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'create public content'.
  $permissions['create public content'] = array(
    'name' => 'create public content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create task content'.
  $permissions['create task content'] = array(
    'name' => 'create task content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create userlist content'.
  $permissions['create userlist content'] = array(
    'name' => 'create userlist content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create webform content'.
  $permissions['create webform content'] = array(
    'name' => 'create webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'customize ckeditor'.
  $permissions['customize ckeditor'] = array(
    'name' => 'customize ckeditor',
    'roles' => array(),
    'module' => 'ckeditor',
  );

  // Exported permission: 'customize shortcut links'.
  $permissions['customize shortcut links'] = array(
    'name' => 'customize shortcut links',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'delete all webform submissions'.
  $permissions['delete all webform submissions'] = array(
    'name' => 'delete all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete any alfresco_item content'.
  $permissions['delete any alfresco_item content'] = array(
    'name' => 'delete any alfresco_item content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any article content'.
  $permissions['delete any article content'] = array(
    'name' => 'delete any article content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any book content'.
  $permissions['delete any book content'] = array(
    'name' => 'delete any book content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any conference content'.
  $permissions['delete any conference content'] = array(
    'name' => 'delete any conference content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any contact content'.
  $permissions['delete any contact content'] = array(
    'name' => 'delete any contact content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any extranet content'.
  $permissions['delete any extranet content'] = array(
    'name' => 'delete any extranet content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any forum content'.
  $permissions['delete any forum content'] = array(
    'name' => 'delete any forum content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any group content'.
  $permissions['delete any group content'] = array(
    'name' => 'delete any group content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any kanban content'.
  $permissions['delete any kanban content'] = array(
    'name' => 'delete any kanban content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any organisation content'.
  $permissions['delete any organisation content'] = array(
    'name' => 'delete any organisation content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any page content'.
  $permissions['delete any page content'] = array(
    'name' => 'delete any page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any private_space content'.
  $permissions['delete any private_space content'] = array(
    'name' => 'delete any private_space content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any public content'.
  $permissions['delete any public content'] = array(
    'name' => 'delete any public content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any task content'.
  $permissions['delete any task content'] = array(
    'name' => 'delete any task content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any userlist content'.
  $permissions['delete any userlist content'] = array(
    'name' => 'delete any userlist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete any webform content'.
  $permissions['delete any webform content'] = array(
    'name' => 'delete any webform content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete backup files'.
  $permissions['delete backup files'] = array(
    'name' => 'delete backup files',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'delete own alfresco_item content'.
  $permissions['delete own alfresco_item content'] = array(
    'name' => 'delete own alfresco_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own article content'.
  $permissions['delete own article content'] = array(
    'name' => 'delete own article content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own book content'.
  $permissions['delete own book content'] = array(
    'name' => 'delete own book content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own conference content'.
  $permissions['delete own conference content'] = array(
    'name' => 'delete own conference content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own contact content'.
  $permissions['delete own contact content'] = array(
    'name' => 'delete own contact content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own extranet content'.
  $permissions['delete own extranet content'] = array(
    'name' => 'delete own extranet content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own forum content'.
  $permissions['delete own forum content'] = array(
    'name' => 'delete own forum content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own group content'.
  $permissions['delete own group content'] = array(
    'name' => 'delete own group content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own kanban content'.
  $permissions['delete own kanban content'] = array(
    'name' => 'delete own kanban content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own organisation content'.
  $permissions['delete own organisation content'] = array(
    'name' => 'delete own organisation content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own page content'.
  $permissions['delete own page content'] = array(
    'name' => 'delete own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own private_space content'.
  $permissions['delete own private_space content'] = array(
    'name' => 'delete own private_space content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own public content'.
  $permissions['delete own public content'] = array(
    'name' => 'delete own public content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own task content'.
  $permissions['delete own task content'] = array(
    'name' => 'delete own task content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own userlist content'.
  $permissions['delete own userlist content'] = array(
    'name' => 'delete own userlist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform content'.
  $permissions['delete own webform content'] = array(
    'name' => 'delete own webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own webform submissions'.
  $permissions['delete own webform submissions'] = array(
    'name' => 'delete own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'delete privatemsg'.
  $permissions['delete privatemsg'] = array(
    'name' => 'delete privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'delete relation relationships'.
  $permissions['delete relation relationships'] = array(
    'name' => 'delete relation relationships',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user_relationships',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'delete terms in criticity'.
  $permissions['delete terms in criticity'] = array(
    'name' => 'delete terms in criticity',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in forums'.
  $permissions['delete terms in forums'] = array(
    'name' => 'delete terms in forums',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in tags'.
  $permissions['delete terms in tags'] = array(
    'name' => 'delete terms in tags',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'delete terms in userpoints'.
  $permissions['delete terms in userpoints'] = array(
    'name' => 'delete terms in userpoints',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit all webform submissions'.
  $permissions['edit all webform submissions'] = array(
    'name' => 'edit all webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit any alfresco_item content'.
  $permissions['edit any alfresco_item content'] = array(
    'name' => 'edit any alfresco_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any article content'.
  $permissions['edit any article content'] = array(
    'name' => 'edit any article content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any book content'.
  $permissions['edit any book content'] = array(
    'name' => 'edit any book content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any conference content'.
  $permissions['edit any conference content'] = array(
    'name' => 'edit any conference content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any contact content'.
  $permissions['edit any contact content'] = array(
    'name' => 'edit any contact content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any extranet content'.
  $permissions['edit any extranet content'] = array(
    'name' => 'edit any extranet content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any forum content'.
  $permissions['edit any forum content'] = array(
    'name' => 'edit any forum content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any group content'.
  $permissions['edit any group content'] = array(
    'name' => 'edit any group content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any kanban content'.
  $permissions['edit any kanban content'] = array(
    'name' => 'edit any kanban content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any organisation content'.
  $permissions['edit any organisation content'] = array(
    'name' => 'edit any organisation content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any page content'.
  $permissions['edit any page content'] = array(
    'name' => 'edit any page content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any private_space content'.
  $permissions['edit any private_space content'] = array(
    'name' => 'edit any private_space content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any public content'.
  $permissions['edit any public content'] = array(
    'name' => 'edit any public content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any task content'.
  $permissions['edit any task content'] = array(
    'name' => 'edit any task content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any userlist content'.
  $permissions['edit any userlist content'] = array(
    'name' => 'edit any userlist content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'edit any webform content'.
  $permissions['edit any webform content'] = array(
    'name' => 'edit any webform content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit mimemail user settings'.
  $permissions['edit mimemail user settings'] = array(
    'name' => 'edit mimemail user settings',
    'roles' => array(),
    'module' => 'mimemail',
  );

  // Exported permission: 'edit own alfresco_item content'.
  $permissions['edit own alfresco_item content'] = array(
    'name' => 'edit own alfresco_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own article content'.
  $permissions['edit own article content'] = array(
    'name' => 'edit own article content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own book content'.
  $permissions['edit own book content'] = array(
    'name' => 'edit own book content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own comments'.
  $permissions['edit own comments'] = array(
    'name' => 'edit own comments',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'edit own conference content'.
  $permissions['edit own conference content'] = array(
    'name' => 'edit own conference content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own contact content'.
  $permissions['edit own contact content'] = array(
    'name' => 'edit own contact content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own extranet content'.
  $permissions['edit own extranet content'] = array(
    'name' => 'edit own extranet content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own forum content'.
  $permissions['edit own forum content'] = array(
    'name' => 'edit own forum content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own group content'.
  $permissions['edit own group content'] = array(
    'name' => 'edit own group content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own kanban content'.
  $permissions['edit own kanban content'] = array(
    'name' => 'edit own kanban content',
    'roles' => array(
      'administrator' => 'administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own organisation content'.
  $permissions['edit own organisation content'] = array(
    'name' => 'edit own organisation content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own page content'.
  $permissions['edit own page content'] = array(
    'name' => 'edit own page content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own private_space content'.
  $permissions['edit own private_space content'] = array(
    'name' => 'edit own private_space content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own public content'.
  $permissions['edit own public content'] = array(
    'name' => 'edit own public content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own task content'.
  $permissions['edit own task content'] = array(
    'name' => 'edit own task content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own userlist content'.
  $permissions['edit own userlist content'] = array(
    'name' => 'edit own userlist content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'manager' => 'manager',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform content'.
  $permissions['edit own webform content'] = array(
    'name' => 'edit own webform content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own webform submissions'.
  $permissions['edit own webform submissions'] = array(
    'name' => 'edit own webform submissions',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'edit radioactivity'.
  $permissions['edit radioactivity'] = array(
    'name' => 'edit radioactivity',
    'roles' => array(),
    'module' => 'radioactivity',
  );

  // Exported permission: 'edit terms in criticity'.
  $permissions['edit terms in criticity'] = array(
    'name' => 'edit terms in criticity',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in forums'.
  $permissions['edit terms in forums'] = array(
    'name' => 'edit terms in forums',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in tags'.
  $permissions['edit terms in tags'] = array(
    'name' => 'edit terms in tags',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit terms in userpoints'.
  $permissions['edit terms in userpoints'] = array(
    'name' => 'edit terms in userpoints',
    'roles' => array(),
    'module' => 'taxonomy',
  );

  // Exported permission: 'edit userpoints'.
  $permissions['edit userpoints'] = array(
    'name' => 'edit userpoints',
    'roles' => array(),
    'module' => 'userpoints',
  );

  // Exported permission: 'edit webform components'.
  $permissions['edit webform components'] = array(
    'name' => 'edit webform components',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'webform',
  );

  // Exported permission: 'flag bookmarks'.
  $permissions['flag bookmarks'] = array(
    'name' => 'flag bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag cart'.
  $permissions['flag cart'] = array(
    'name' => 'flag cart',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag flag_public'.
  $permissions['flag flag_public'] = array(
    'name' => 'flag flag_public',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_node'.
  $permissions['flag subscribe_node'] = array(
    'name' => 'flag subscribe_node',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_og'.
  $permissions['flag subscribe_og'] = array(
    'name' => 'flag subscribe_og',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_term'.
  $permissions['flag subscribe_term'] = array(
    'name' => 'flag subscribe_term',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'flag subscribe_user'.
  $permissions['flag subscribe_user'] = array(
    'name' => 'flag subscribe_user',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'generate features'.
  $permissions['generate features'] = array(
    'name' => 'generate features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'gofast administer users'.
  $permissions['gofast administer users'] = array(
    'name' => 'gofast administer users',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_user',
  );

  // Exported permission: 'maintain relation relationships'.
  $permissions['maintain relation relationships'] = array(
    'name' => 'maintain relation relationships',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user_relationships',
  );

  // Exported permission: 'manage features'.
  $permissions['manage features'] = array(
    'name' => 'manage features',
    'roles' => array(),
    'module' => 'features',
  );

  // Exported permission: 'moderate userpoints'.
  $permissions['moderate userpoints'] = array(
    'name' => 'moderate userpoints',
    'roles' => array(),
    'module' => 'userpoints',
  );

  // Exported permission: 'perform backup'.
  $permissions['perform backup'] = array(
    'name' => 'perform backup',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'post comments'.
  $permissions['post comments'] = array(
    'name' => 'post comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'pre add members'.
  $permissions['pre add members'] = array(
    'name' => 'pre add members',
    'roles' => array(
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_og',
  );

  // Exported permission: 'rate content'.
  $permissions['rate content'] = array(
    'name' => 'rate content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'fivestar',
  );

  // Exported permission: 'read all private messages'.
  $permissions['read all private messages'] = array(
    'name' => 'read all private messages',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'read privatemsg'.
  $permissions['read privatemsg'] = array(
    'name' => 'read privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'reply only privatemsg'.
  $permissions['reply only privatemsg'] = array(
    'name' => 'reply only privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'report private messages to mollom'.
  $permissions['report private messages to mollom'] = array(
    'name' => 'report private messages to mollom',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'reset vote up/down votes'.
  $permissions['reset vote up/down votes'] = array(
    'name' => 'reset vote up/down votes',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vud',
  );

  // Exported permission: 'restore from backup'.
  $permissions['restore from backup'] = array(
    'name' => 'restore from backup',
    'roles' => array(),
    'module' => 'backup_migrate',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'search content'.
  $permissions['search content'] = array(
    'name' => 'search content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'search',
  );

  // Exported permission: 'see vote up/down node stats'.
  $permissions['see vote up/down node stats'] = array(
    'name' => 'see vote up/down node stats',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'vud_node',
  );

  // Exported permission: 'select account cancellation method'.
  $permissions['select account cancellation method'] = array(
    'name' => 'select account cancellation method',
    'roles' => array(),
    'module' => 'user',
  );

  // Exported permission: 'select text format for privatemsg'.
  $permissions['select text format for privatemsg'] = array(
    'name' => 'select text format for privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'send arbitrary files'.
  $permissions['send arbitrary files'] = array(
    'name' => 'send arbitrary files',
    'roles' => array(),
    'module' => 'mimemail',
  );

  // Exported permission: 'skip comment approval'.
  $permissions['skip comment approval'] = array(
    'name' => 'skip comment approval',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'comment',
  );

  // Exported permission: 'switch shortcut sets'.
  $permissions['switch shortcut sets'] = array(
    'name' => 'switch shortcut sets',
    'roles' => array(),
    'module' => 'shortcut',
  );

  // Exported permission: 'translate admin strings'.
  $permissions['translate admin strings'] = array(
    'name' => 'translate admin strings',
    'roles' => array(),
    'module' => 'i18n_string',
  );

  // Exported permission: 'translate content'.
  $permissions['translate content'] = array(
    'name' => 'translate content',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
      'contributor' => 'contributor',
    ),
    'module' => 'translation',
  );

  // Exported permission: 'translate interface'.
  $permissions['translate interface'] = array(
    'name' => 'translate interface',
    'roles' => array(),
    'module' => 'locale',
  );

  // Exported permission: 'translate user-defined strings'.
  $permissions['translate user-defined strings'] = array(
    'name' => 'translate user-defined strings',
    'roles' => array(),
    'module' => 'i18n_string',
  );

  // Exported permission: 'unflag bookmarks'.
  $permissions['unflag bookmarks'] = array(
    'name' => 'unflag bookmarks',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag cart'.
  $permissions['unflag cart'] = array(
    'name' => 'unflag cart',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag flag_public'.
  $permissions['unflag flag_public'] = array(
    'name' => 'unflag flag_public',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_node'.
  $permissions['unflag subscribe_node'] = array(
    'name' => 'unflag subscribe_node',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_og'.
  $permissions['unflag subscribe_og'] = array(
    'name' => 'unflag subscribe_og',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_term'.
  $permissions['unflag subscribe_term'] = array(
    'name' => 'unflag subscribe_term',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'unflag subscribe_user'.
  $permissions['unflag subscribe_user'] = array(
    'name' => 'unflag subscribe_user',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use PHP for settings'.
  $permissions['use PHP for settings'] = array(
    'name' => 'use PHP for settings',
    'roles' => array(),
    'module' => 'php',
  );

  // Exported permission: 'use advanced search'.
  $permissions['use advanced search'] = array(
    'name' => 'use advanced search',
    'roles' => array(),
    'module' => 'search',
  );

  // Exported permission: 'use ctools import'.
  $permissions['use ctools import'] = array(
    'name' => 'use ctools import',
    'roles' => array(),
    'module' => 'ctools',
  );

  // Exported permission: 'use flag import'.
  $permissions['use flag import'] = array(
    'name' => 'use flag import',
    'roles' => array(),
    'module' => 'flag',
  );

  // Exported permission: 'use text format filtered_html'.
  $permissions['use text format filtered_html'] = array(
    'name' => 'use text format filtered_html',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format full_html'.
  $permissions['use text format full_html'] = array(
    'name' => 'use text format full_html',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'contributor' => 'contributor',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'use text format php_code'.
  $permissions['use text format php_code'] = array(
    'name' => 'use text format php_code',
    'roles' => array(),
    'module' => 'filter',
  );

  // Exported permission: 'use tokens in privatemsg'.
  $permissions['use tokens in privatemsg'] = array(
    'name' => 'use tokens in privatemsg',
    'roles' => array(),
    'module' => 'privatemsg',
  );

  // Exported permission: 'use vote up/down'.
  $permissions['use vote up/down'] = array(
    'name' => 'use vote up/down',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud',
  );

  // Exported permission: 'use vote up/down on comments'.
  $permissions['use vote up/down on comments'] = array(
    'name' => 'use vote up/down on comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud_comment',
  );

  // Exported permission: 'use vote up/down on nodes'.
  $permissions['use vote up/down on nodes'] = array(
    'name' => 'use vote up/down on nodes',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud_node',
  );

  // Exported permission: 'view all relation relationships'.
  $permissions['view all relation relationships'] = array(
    'name' => 'view all relation relationships',
    'roles' => array(),
    'module' => 'user_relationships_ui',
  );

  // Exported permission: 'view forum statistics'.
  $permissions['view forum statistics'] = array(
    'name' => 'view forum statistics',
    'roles' => array(),
    'module' => 'advanced_forum',
  );

  // Exported permission: 'view last edited notice'.
  $permissions['view last edited notice'] = array(
    'name' => 'view last edited notice',
    'roles' => array(),
    'module' => 'advanced_forum',
  );

  // Exported permission: 'view own relation relationships'.
  $permissions['view own relation relationships'] = array(
    'name' => 'view own relation relationships',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'user_relationships_ui',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view own userpoints'.
  $permissions['view own userpoints'] = array(
    'name' => 'view own userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(),
    'module' => 'system',
  );

  // Exported permission: 'view userpoints'.
  $permissions['view userpoints'] = array(
    'name' => 'view userpoints',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'userpoints',
  );

  // Exported permission: 'view vote up/down count on comments'.
  $permissions['view vote up/down count on comments'] = array(
    'name' => 'view vote up/down count on comments',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud_comment',
  );

  // Exported permission: 'view vote up/down count on nodes'.
  $permissions['view vote up/down count on nodes'] = array(
    'name' => 'view vote up/down count on nodes',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'vud_node',
  );

  // Exported permission: 'write privatemsg'.
  $permissions['write privatemsg'] = array(
    'name' => 'write privatemsg',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'privatemsg',
  );

  // Exported permission: 'administer gofast webhook'.
  $permissions['administer gofast webhook'] = array(
    'name' => 'administer gofast webhook',
    'roles' => array(
      'administrator' => 'administrator',
      'business administrator' => 'business administrator',
    ),
    'module' => 'gofast_webhook',
  );

  return $permissions;
}
