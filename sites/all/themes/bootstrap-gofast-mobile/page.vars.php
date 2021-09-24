<?php

include_once 'MobileDetect.php';
/**
 * @file
 * Stub file for "page" theme hook [pre]process functions.
 */

/**
 * Pre-processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_preprocess
 */
function bootstrap_gofast_mobile_preprocess_page(&$variables) {
  global $user;

  $detect = new Mobile_Detect;
  if($detect->isMobile() || $detect->isTablet()){
    // Add information about the number of sidebars.
    if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
      $variables['content_column_class'] = ' class="col-sm-6"';
    } elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
      //in mobile theme, always use all the screen width ( the sidebar_second will we rendered as a dynamical block)
      $variables['content_column_class'] = ' class="col-sm-12"';
    } else {
      $variables['content_column_class'] = ' class="col-sm-12"';
    }

    if (bootstrap_setting('fluid_container') == 1) {
      $variables['container_class'] = 'container-fluid';
    } else {
      $variables['container_class'] = 'container';
    }

    // Primary nav.
    $variables['primary_nav'] = FALSE;
    if ($variables['main_menu']) {

      // Build links.
      $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
      // Provide default theme wrapper function.
      $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
    }

    // Secondary nav.
    $variables['secondary_nav'] = FALSE;
    if ($variables['secondary_menu']) {
      // Build links.
      $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
      // Provide default theme rwrapper function.
      $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
    }

    $variables['navbar_classes_array'] = array('navbar');

    if (bootstrap_setting('navbar_position') !== '') {
      $variables['navbar_classes_array'][] = 'navbar-' . bootstrap_setting('navbar_position');
    } elseif (bootstrap_setting('fluid_container') == 1) {
      $variables['navbar_classes_array'][] = 'container-fluid';
    } else {
      $variables['navbar_classes_array'][] = 'container';
    }
    if (bootstrap_setting('navbar_inverse')) {
      $variables['navbar_classes_array'][] = 'navbar-inverse';
    } else {
      $variables['navbar_classes_array'][] = 'navbar-default';
    }

    unset($variables['page']['navigation']['gofast_menu_gofast_menu_icons']);
    $variables['theme_name'] = 'gofast_mobile_mobile_navbar_page_tpl';
  }else{
    // Add information about the number of sidebars.
    if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
      $variables['content_column_class'] = ' class="col-sm-6"';
    } elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
      $variables['content_column_class'] = ' class="col-sm-12"';
    } else {
      $variables['content_column_class'] = ' class="col-sm-12"';
    }

    if (bootstrap_setting('fluid_container') == 1) {
      $variables['container_class'] = 'container-fluid';
    } else {
      $variables['container_class'] = 'container';
    }

    // Primary nav.
    $variables['primary_nav'] = FALSE;
    if ($variables['main_menu']) {
      // Build links.
      $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
      // Provide default theme wrapper function.
      $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
    }

    $create_mlid = db_query("SELECT mlid from {menu_links} WHERE link_title='Create' and module = 'menu'")->fetchField();
    $spaces_mlid = db_query("SELECT mlid from {menu_links} WHERE link_title='Spaces' and module = 'menu'")->fetchField();
    $directories_mlid = db_query("SELECT mlid from {menu_links} WHERE link_title='Directories' and module = 'menu'")->fetchField();

    unset($variables['primary_nav'][$create_mlid]);
    unset($variables['primary_nav'][$spaces_mlid]);
    unset($variables['primary_nav'][$directories_mlid]);;


      // Build links.
      $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
      // Provide default theme wrapper function.
      $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');


    $variables['navbar_classes_array'] = array('navbar');

    if (bootstrap_setting('navbar_position') !== '') {
      $variables['navbar_classes_array'][] = 'navbar-' . bootstrap_setting('navbar_position');
    } elseif (bootstrap_setting('fluid_container') == 1) {
      $variables['navbar_classes_array'][] = 'container-fluid';
    } else {
      $variables['navbar_classes_array'][] = 'container';
    }
    if (bootstrap_setting('navbar_inverse')) {
      $variables['navbar_classes_array'][] = 'navbar-inverse';
    } else {
      $variables['navbar_classes_array'][] = 'navbar-default';
    }

    $variables['theme_name'] = 'gofast_mobile_simplified_navbar_page_tpl';

    if (isset($variables['logo'])) {
      $variables['search_form_class'] = 'col-xs-6 col-sm-7';
    } else {
      $variables['search_form_class'] = 'col-xs-10 col-sm-9';
    }

    if (isset($variables['logo'])) {
      $variables['icon_form_class'] = 'col-xs-4 col-sm-4';
    } else {
      $variables['icon_form_class'] = 'col-xs-5 col-sm-5';
    }
  }

  $variables['breadcrumb_navigation_items_class'] = 'breadcrumb navigation_simplified';
  $variables['breadcrumb_navigation_item_class'] = 'item_navigation';
  $pages_name = $variables['theme_hook_suggestions'];
}

/**
 * Processes variables for the "page" theme hook.
 *
 * See template for list of available variables.
 *
 * @see page.tpl.php
 *
 * @ingroup theme_process
 */
function bootstrap_gofast_process_page(&$variables) {
  $variables['navbar_classes'] = implode(' ', $variables['navbar_classes_array']);
}
