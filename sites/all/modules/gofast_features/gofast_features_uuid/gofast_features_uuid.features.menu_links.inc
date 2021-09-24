<?php
/**
 * @file
 * gofast_features_uuid.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function gofast_features_uuid_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_extranet:og/list_grid/extranet.
  $menu_links['main-menu_extranet:og/list_grid/extranet'] = array(
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
    'language' => 'und',
    'menu_links_customized' => 0,
    'parent_identifier' => 'main-menu_:user_listing_grid',
  );
  // Exported menu link: main-menu_organisation:og/list_grid/organisation.
  $menu_links['main-menu_organisation:og/list_grid/organisation'] = array(
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
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'main-menu_:user_listing_grid',
  );
  // Exported menu link: main-menu_public:og/list_grid/public.
  $menu_links['main-menu_public:og/list_grid/public'] = array(
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
    'language' => 'und',
    'menu_links_customized' => 1,
    'parent_identifier' => 'main-menu_:user_listing_grid',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Extranet');
  t('Organisation');
  t('Public');

  return $menu_links;
}
