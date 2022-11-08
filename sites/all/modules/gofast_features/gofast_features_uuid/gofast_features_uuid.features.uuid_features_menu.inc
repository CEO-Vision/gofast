<?php
/**
 * @file
 * gofast_features_uuid.features.uuid_features_menu.inc
 */

/**
 * Implements hook_menu_default_uuid_features_menu().
 */
function gofast_features_uuid_menu_default_uuid_features_menu() {
  $menu_uuid_links = array();

  // Exported menu link: 069e0615-6e8c-4a1b-b611-98bf92d96256
  $menu_uuid_links['069e0615-6e8c-4a1b-b611-98bf92d96256'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/conference',
    'router_path' => 'node/add/conference',
    'link_title' => 'Conference',
    'options' => array(
      'attributes' => array(
        'title' => 'Jitsi-meet conference',
      ),
      'alter' => TRUE,
      'identifier' => 'main-menu_conference:node/add/conference',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'uuid' => '069e0615-6e8c-4a1b-b611-98bf92d96256',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
  );
  // Exported menu link: 078721e5-e465-44eb-8a0c-388f23f186f8
  $menu_uuid_links['078721e5-e465-44eb-8a0c-388f23f186f8'] = array(
    'menu_name' => 'menu-mobile-menu',
    'link_path' => 'browser',
    'router_path' => 'browser',
    'link_title' => 'File Browser',
    'options' => array(
      'attributes' => array(
        'title' => 'File browser',
      ),
      'identifier' => 'menu-mobile-menu_file-browser:browser',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'uuid' => '078721e5-e465-44eb-8a0c-388f23f186f8',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 08de8db9-5f36-4e4e-9368-75ebcebe6b30
  $menu_uuid_links['08de8db9-5f36-4e4e-9368-75ebcebe6b30'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'relationships',
    'router_path' => 'relationships',
    'link_title' => 'My relationships',
    'options' => array(
      'identifier' => 'user-menu_my-relationships:relationships',
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'uuid' => '08de8db9-5f36-4e4e-9368-75ebcebe6b30',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 0b3514b6-7665-48ba-9a25-00bda78d3f16
  $menu_uuid_links['0b3514b6-7665-48ba-9a25-00bda78d3f16'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My profile dropdown',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -10,
    'customized' => 1,
    'uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 0b8034e4-eba8-4af0-9a23-67bca9189f09
  $menu_uuid_links['0b8034e4-eba8-4af0-9a23-67bca9189f09'] = array(
    'menu_name' => 'menu-mobile-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(
        'title' => 'Log out',
      ),
      'identifier' => 'menu-mobile-menu_logout:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'uuid' => '0b8034e4-eba8-4af0-9a23-67bca9189f09',
    'language' => 'und',
    'menu_links_customized' => 0,
  );
  // Exported menu link: 0d7456e5-a0e6-4d61-91b8-f992c5424ca8
  $menu_uuid_links['0d7456e5-a0e6-4d61-91b8-f992c5424ca8'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_user:user',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -46,
    'customized' => 1,
    'uuid' => '0d7456e5-a0e6-4d61-91b8-f992c5424ca8',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 0ed359be-3a4f-4923-bab5-1251a66e3ee0
  $menu_uuid_links['0ed359be-3a4f-4923-bab5-1251a66e3ee0'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'og/list_grid/group',
    'router_path' => 'og/list_grid',
    'link_title' => 'Groups',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_groups:og/list_grid/group',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'uuid' => '0ed359be-3a4f-4923-bab5-1251a66e3ee0',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: 15e84a41-7a6a-4285-a081-82a2ce3436ed
  $menu_uuid_links['15e84a41-7a6a-4285-a081-82a2ce3436ed'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin/config/gofast/ldap/manage',
    'router_path' => 'admin/config/gofast/ldap/manage',
    'link_title' => 'Import Users From LDAP',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_import-users-from-ldap:admin/config/gofast/ldap/manage',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -44,
    'customized' => 1,
    'uuid' => '15e84a41-7a6a-4285-a081-82a2ce3436ed',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 1e18c103-8520-4a0f-b01f-0757ec65951d
  $menu_uuid_links['1e18c103-8520-4a0f-b01f-0757ec65951d'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'admin/people/create',
    'router_path' => 'admin/people/create',
    'link_title' => 'User',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_user:admin/people/create',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'uuid' => '1e18c103-8520-4a0f-b01f-0757ec65951d',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
  );
  // Exported menu link: 204927a7-da87-4226-8e0a-2ca89377eb3a
  $menu_uuid_links['204927a7-da87-4226-8e0a-2ca89377eb3a'] = array(
    'menu_name' => 'menu-mobile-menu',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Workflows',
    'options' => array(
      'attributes' => array(
        'title' => 'Workflows',
      ),
      'identifier' => 'menu-mobile-menu_workflows:<front>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'uuid' => '204927a7-da87-4226-8e0a-2ca89377eb3a',
    'language' => 'und',
    'menu_links_customized' => 0,
  );
  // Exported menu link: 2abf1b6b-35f7-4e9d-a5a3-2164885a5329
  $menu_uuid_links['2abf1b6b-35f7-4e9d-a5a3-2164885a5329'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/group',
    'router_path' => 'node/add/group',
    'link_title' => 'Space',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_space:node/add/group',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -48,
    'customized' => 1,
    'uuid' => '2abf1b6b-35f7-4e9d-a5a3-2164885a5329',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
  );
  // Exported menu link: 3c5e768a-edf2-463e-be9c-d5ae84d2d495
  $menu_uuid_links['3c5e768a-edf2-463e-be9c-d5ae84d2d495'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -10,
    'customized' => 1,
    'uuid' => '3c5e768a-edf2-463e-be9c-d5ae84d2d495',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 47cef16d-5656-4676-b1e5-9b2163c1c6b8
  $menu_uuid_links['47cef16d-5656-4676-b1e5-9b2163c1c6b8'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contacts-listing',
    'router_path' => 'contacts-listing',
    'link_title' => 'Address Book',
    'options' => array(
      'attributes' => array(
        'title' => 'The way to get contact listing view',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'uuid' => '47cef16d-5656-4676-b1e5-9b2163c1c6b8',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: 4a6fb361-50ba-4ad7-930c-7f8a6f45a79b
  $menu_uuid_links['4a6fb361-50ba-4ad7-930c-7f8a6f45a79b'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'og/list_grid/extranet',
    'router_path' => 'og/list_grid',
    'link_title' => 'Extranet',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_extranet:og/list_grid/extranet',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 0,
    'uuid' => '4a6fb361-50ba-4ad7-930c-7f8a6f45a79b',
    'language' => 'und',
    'menu_links_customized' => 0,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: 4ae3d0b6-a9f0-4912-9562-ec6a2c5e42d4
  $menu_uuid_links['4ae3d0b6-a9f0-4912-9562-ec6a2c5e42d4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'og/list_grid/public',
    'router_path' => 'og/list_grid/%',
    'link_title' => 'Public',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_public:og/list_grid/public',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'uuid' => '4ae3d0b6-a9f0-4912-9562-ec6a2c5e42d4',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: 577c082a-c12c-40eb-8c4b-82cbb4f8d850
  $menu_uuid_links['577c082a-c12c-40eb-8c4b-82cbb4f8d850'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/alfresco-item',
    'router_path' => 'node/add/alfresco-item',
    'link_title' => 'File, Document',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_file-document:node/add/alfresco-item',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'uuid' => '577c082a-c12c-40eb-8c4b-82cbb4f8d850',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: 5af2180e-ccd8-4953-8d32-8e2ecd7bb78b
  $menu_uuid_links['5af2180e-ccd8-4953-8d32-8e2ecd7bb78b'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'gofast/browser',
    'router_path' => 'gofast/browser',
    'link_title' => 'Spaces',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_spaces:gofast/browser',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'uuid' => '5af2180e-ccd8-4953-8d32-8e2ecd7bb78b',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 6455f77e-434f-4fc1-a4ab-28bbe2d20b2e
  $menu_uuid_links['6455f77e-434f-4fc1-a4ab-28bbe2d20b2e'] = array(
    'menu_name' => 'user-menu',
    'router_path' => 'modal/%/subscriptions',
    'link_path' => 'modal/%/subscriptions',
    'link_title' => 'Subscriptions',
    'options' => array(
      'attributes' => array(
        'class' => 'ctools-use-modal',
      ),
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -41,
    'customized' => 1,
    'uuid' => '6455f77e-434f-4fc1-a4ab-28bbe2d20b2e',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 656a20c1-4ee8-444a-9825-d7940303b315
  $menu_uuid_links['656a20c1-4ee8-444a-9825-d7940303b315'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'myuserpoints',
    'router_path' => 'myuserpoints',
    'link_title' => 'My !points',
    'options' => array(
      'identifier' => 'user-menu_my-points:myuserpoints',
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'uuid' => '656a20c1-4ee8-444a-9825-d7940303b315',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 698b581a-37a7-40b1-ad80-ddfe5eabd612
  $menu_uuid_links['698b581a-37a7-40b1-ad80-ddfe5eabd612'] = array(
    'menu_name' => 'user-menu',
    'router_path' => 'modal/%/cart',
    'link_path' => 'modal/%/cart',
    'link_title' => 'Cart',
    'options' => array(
      'attributes' => array(
        'class' => 'ctools-use-modal',
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'uuid' => '698b581a-37a7-40b1-ad80-ddfe5eabd612',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 6b65c5da-9d17-485f-8905-3b48f2f234b7
  $menu_uuid_links['6b65c5da-9d17-485f-8905-3b48f2f234b7'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/group',
    'router_path' => 'node/add/group',
    'link_title' => 'Group',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_group:node/add/group',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'uuid' => '6b65c5da-9d17-485f-8905-3b48f2f234b7',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '2abf1b6b-35f7-4e9d-a5a3-2164885a5329',
  );
  // Exported menu link: 772a2887-5478-4285-9f35-de316a2aea69
  $menu_uuid_links['772a2887-5478-4285-9f35-de316a2aea69'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'gofast/browser',
    'router_path' => 'gofast/browser',
    'link_title' => 'Browser',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_browser:gofast/browser',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'uuid' => '772a2887-5478-4285-9f35-de316a2aea69',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '5af2180e-ccd8-4953-8d32-8e2ecd7bb78b',
  );
  // Exported menu link: 7fcaf186-c2a1-45e0-afe7-31cababd7bbd
  $menu_uuid_links['7fcaf186-c2a1-45e0-afe7-31cababd7bbd'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/organisation',
    'router_path' => 'node/add/organisation',
    'link_title' => 'Organisation',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_organisation:node/add/organisation',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'uuid' => '7fcaf186-c2a1-45e0-afe7-31cababd7bbd',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '2abf1b6b-35f7-4e9d-a5a3-2164885a5329',
  );
  // Exported menu link: 823a0221-9ff3-4536-a329-8e9e9958b625
  $menu_uuid_links['823a0221-9ff3-4536-a329-8e9e9958b625'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/alfresco-item',
    'router_path' => 'node/add/alfresco-item',
    'link_title' => 'Create',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_create:node/add/alfresco-item',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: 8bf11178-1cbd-43e2-9787-598fb9d805f3
  $menu_uuid_links['8bf11178-1cbd-43e2-9787-598fb9d805f3'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/webform',
    'router_path' => 'node/add/webform',
    'link_title' => 'Webform',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_webform:node/add/webform',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 0,
    'uuid' => '8bf11178-1cbd-43e2-9787-598fb9d805f3',
    'language' => 'und',
    'menu_links_customized' => 0,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: 8ca80d16-149d-4573-a34f-e434edcc25fc
  $menu_uuid_links['8ca80d16-149d-4573-a34f-e434edcc25fc'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/contact',
    'router_path' => 'node/add/contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
    'uuid' => '8ca80d16-149d-4573-a34f-e434edcc25fc',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: 8ec899da-6aae-4072-a66c-f66f4d3c23a4
  $menu_uuid_links['8ec899da-6aae-4072-a66c-f66f4d3c23a4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'space/admin/members',
    'router_path' => 'space/admin/members',
    'link_title' => 'Members management',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'identifier' => 'main-menu_space-members-management:space/admin/members',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 15,
    'customized' => 1,
    'uuid' => '8ec899da-6aae-4072-a66c-f66f4d3c23a4',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '5af2180e-ccd8-4953-8d32-8e2ecd7bb78b',
  );
  // Exported menu link: 8ff5c811-dcc7-4bae-896b-fb4a637b06c4
  $menu_uuid_links['8ff5c811-dcc7-4bae-896b-fb4a637b06c4'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/extranet',
    'router_path' => 'node/add/extranet',
    'link_title' => 'Extranet',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_extranet:node/add/extranet',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 0,
    'uuid' => '8ff5c811-dcc7-4bae-896b-fb4a637b06c4',
    'language' => 'und',
    'menu_links_customized' => 0,
    'parent_uuid' => '2abf1b6b-35f7-4e9d-a5a3-2164885a5329',
  );
  // Exported menu link: 95a6f74f-1d19-41bc-8368-4cf2dcc062b2
  $menu_uuid_links['95a6f74f-1d19-41bc-8368-4cf2dcc062b2'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'gofast_audit',
    'router_path' => 'gofast_audit',
    'link_title' => 'Audit',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -43,
    'customized' => 1,
    'uuid' => '95a6f74f-1d19-41bc-8368-4cf2dcc062b2',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 969d0099-d9c1-4097-9018-4bc470a144b9
  $menu_uuid_links['969d0099-d9c1-4097-9018-4bc470a144b9'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -40,
    'customized' => 1,
    'uuid' => '969d0099-d9c1-4097-9018-4bc470a144b9',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: 9be62586-dc02-45f4-b295-5554f0bca598
  $menu_uuid_links['9be62586-dc02-45f4-b295-5554f0bca598'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/article',
    'router_path' => 'node/add/article',
    'link_title' => 'Wiki article',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_article-page:node/add/article',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'uuid' => '9be62586-dc02-45f4-b295-5554f0bca598',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: a1450a30-ea8a-4c9f-a2b0-54037c3242e8
  $menu_uuid_links['a1450a30-ea8a-4c9f-a2b0-54037c3242e8'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/alfresco-item',
    'router_path' => 'node/add/alfresco-item',
    'link_title' => 'External page',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_external-page:node/add/alfresco-item',
      'alter' => TRUE,
      'query' => array(
        'external' => 'true',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'uuid' => 'a1450a30-ea8a-4c9f-a2b0-54037c3242e8',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: a90c6814-2cf6-4966-a2a8-3d285c93e176
  $menu_uuid_links['a90c6814-2cf6-4966-a2a8-3d285c93e176'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'messages',
    'router_path' => 'messages',
    'link_title' => 'Messages',
    'options' => array(
      'identifier' => 'user-menu_messages:messages',
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'uuid' => 'a90c6814-2cf6-4966-a2a8-3d285c93e176',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: b4a3f752-fd5a-438b-8757-21fec2b7a6d8
  $menu_uuid_links['b4a3f752-fd5a-438b-8757-21fec2b7a6d8'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'userlists',
    'router_path' => 'userlists',
    'link_title' => 'Userlists',
    'options' => array(
      'attributes' => array(
        'title' => 'The way to get userlists view',
      ),
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -33,
    'customized' => 1,
    'uuid' => 'b4a3f752-fd5a-438b-8757-21fec2b7a6d8',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: b583d48c-956b-4183-8c02-6c96a65e4fcb
  $menu_uuid_links['b583d48c-956b-4183-8c02-6c96a65e4fcb'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'My profile',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'user-menu_my-profile:user',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
    'uuid' => 'b583d48c-956b-4183-8c02-6c96a65e4fcb',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: b643f711-39fe-48ba-b23f-4471742e4350
  $menu_uuid_links['b643f711-39fe-48ba-b23f-4471742e4350'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/forum',
    'router_path' => 'node/add/forum',
    'link_title' => 'Forum',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_forum:node/add/forum',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 0,
    'uuid' => 'b643f711-39fe-48ba-b23f-4471742e4350',
    'language' => 'und',
    'menu_links_customized' => 0,
    'parent_uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
  );
  // Exported menu link: ca9f0e8a-a355-48c8-bcf6-6c235a171aa2
  $menu_uuid_links['ca9f0e8a-a355-48c8-bcf6-6c235a171aa2'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'gofast_stats/dashboard',
    'router_path' => 'gofast_stats/dashboard',
    'link_title' => 'Statistics',
    'options' => array(
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'uuid' => 'ca9f0e8a-a355-48c8-bcf6-6c235a171aa2',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: d5b1a21e-c54a-42fc-a429-cee4419d29d2
  $menu_uuid_links['d5b1a21e-c54a-42fc-a429-cee4419d29d2'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/userlist',
    'router_path' => 'node/add/userlist',
    'link_title' => 'UserList',
    'options' => array(
      'attributes' => array(
        'title' => 'Used to group users and facilitate permission definition.',
      ),
      'alter' => TRUE,
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -32,
    'customized' => 1,
    'uuid' => 'd5b1a21e-c54a-42fc-a429-cee4419d29d2',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
  );
  // Exported menu link: e2935a52-5fb0-4ef8-a60b-d3f62abb4f81
  $menu_uuid_links['e2935a52-5fb0-4ef8-a60b-d3f62abb4f81'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/alfresco-item',
    'router_path' => 'node/add/alfresco-item',
    'link_title' => 'Content',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_content:node/add/alfresco-item',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'uuid' => 'e2935a52-5fb0-4ef8-a60b-d3f62abb4f81',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '823a0221-9ff3-4536-a329-8e9e9958b625',
  );
  // Exported menu link: ef5c659c-d339-469f-9adb-97b5a5abc463
  $menu_uuid_links['ef5c659c-d339-469f-9adb-97b5a5abc463'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'admin/config/gofast/global',
    'router_path' => 'admin/config/gofast/global',
    'link_title' => 'GoFAST configuration',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_configuration:admin/config/gofast/global',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'uuid' => 'ef5c659c-d339-469f-9adb-97b5a5abc463',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '0b3514b6-7665-48ba-9a25-00bda78d3f16',
  );
  // Exported menu link: ef7ff62e-3844-4268-bdba-53b4b3e214d0
  $menu_uuid_links['ef7ff62e-3844-4268-bdba-53b4b3e214d0'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user_listing_tab',
    'router_path' => 'user_listing_tab',
    'link_title' => 'Users',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_users:user_listing_grid',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'uuid' => 'ef7ff62e-3844-4268-bdba-53b4b3e214d0',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );
  // Exported menu link: f20e36c5-4b8a-4c4c-a133-b7cde7b074ff
  $menu_uuid_links['f20e36c5-4b8a-4c4c-a133-b7cde7b074ff'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/add/public',
    'router_path' => 'node/add/public',
    'link_title' => 'Public',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_public:node/add/public',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'uuid' => 'f20e36c5-4b8a-4c4c-a133-b7cde7b074ff',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => '2abf1b6b-35f7-4e9d-a5a3-2164885a5329',
  );
  // Exported menu link: f736bf81-ca21-4cc4-8fa9-5ffd704f16fd
  $menu_uuid_links['f736bf81-ca21-4cc4-8fa9-5ffd704f16fd'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'user_listing_tab',
    'router_path' => 'user_listing_tab',
    'link_title' => 'Directories',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_directories:og/list_grid/directories',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -47,
    'customized' => 1,
    'uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
    'language' => 'und',
    'menu_links_customized' => 1,
  );
  // Exported menu link: f7618410-be8f-49ab-9187-c5e4205caae2
  $menu_uuid_links['f7618410-be8f-49ab-9187-c5e4205caae2'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'og/list_grid/organisation',
    'router_path' => 'og/list_grid/%',
    'link_title' => 'Organisation',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_organisation:og/list_grid/organisation',
      'alter' => TRUE,
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'uuid' => 'f7618410-be8f-49ab-9187-c5e4205caae2',
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_uuid' => 'f736bf81-ca21-4cc4-8fa9-5ffd704f16fd',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Audit');
  t('Browser');
  t('Cart');
  t('Conference');
  t('Contact');
  t('Address Book');
  t('Content');
  t('Create');
  t('Directories');
  t('External page');
  t('Extranet');
  t('File Browser');
  t('File, Document');
  t('Forum');
  t('GoFAST configuration');
  t('Group');
  t('Groups');
  t('Import Users From LDAP');
  t('Log out');
  t('Logout');
  t('Members management');
  t('Messages');
  t('My !points');
  t('My profile');
  t('My profile dropdown');
  t('My relationships');
  t('Organisation');
  t('Public');
  t('Space');
  t('Spaces');
  t('Statistics');
  t('Subscriptions');
  t('User');
  t('User account');
  t('UserList');
  t('Userlists');
  t('Users');
  t('Wiki article');
  t('Workflows');

  return $menu_uuid_links;
}
