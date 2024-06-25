<?php

function gofast_create_menu_spaces() {

  $private_space_node = gofast_og_get_user_private_space($user);

  $link = [
    'icon' => '',
    'svg' => '/sites/all/themes/bootstrap-keen/img/collaborative_navigate.svg',
    'label' => 'Spaces',
    'id' => 'gf-spaces-menu',
    'class' => 'menu-item-rel menu-item-open-dropdown',
    'subclass' => 'menu-submenu-left menu-submenu-fixed gf-space-menus gf-megamenu',
    'href' => '/node/'.$private_space_node->nid.'#ogdocuments',
    'menu' => [],
    'isSpace' => TRUE,
    'desktop_only' => TRUE
  ];

  $menu = array();
  $has_submenu = FALSE;
  
  global $user;

  //First Level Spaces
  $root_spaces = gofast_og_get_root_spaces(TRUE, TRUE);

  foreach ($root_spaces as $nid => $space) {

    $icon = gofast_node_get_icon($space);

    $subspaces = gofast_og_get_space_children_by_user($nid, $user);

    $has_submenu = (count($subspaces) > 0) ? TRUE : FALSE;

    $root_space = array(
      'id' => 'gf_og_'.$nid,
      'icon' => 'fas n-color ' . $icon,
      'label' => t($space->title),
      'href' => '/node/' . $nid,
      'class' => 'gf-dropdown-submenu gf-megamenu-static-submenu gf-megamenu-submenu',
      'subclass' => 'menu-submenu-right',
      'attrs' => array("gid" => $nid ),
      'has_submenu' => $has_submenu,
      'menu' => array() //gofast_create_menu_subspaces($nid)
    );
    $menu[] = $root_space;
    
    //watchdog('DEBUG_SMA', 'There IS subspaces: <pre>' . print_r($root_space, true) . '</pre>', array(), WATCHDOG_DEBUG);
    
  }


  $icon = gofast_node_get_icon($private_space_node);
  //Add user private'space
  $private_space = array(
    'id' => 'gf_og_'.$nid,
    'icon' => 'fas n-color ' . $icon,
    'label' => t("Personal Space"),
    'href' => '/node/' . $private_space_node->nid,
    'class' => 'gf-dropdown-submenu gf-megamenu-static-submenu gf-megamenu-submenu',
    'subclass' => 'menu-submenu-right',
    'attrs' => array("gid" => $private_space_node->nid ),
    'menu' => array()
  );
  $menu[] = $private_space;

  //Sort by label
  usort($menu, function($a, $b) {
    return strcasecmp($a['label'], $b['label']);
  });

  $link['menu'] = $menu;
  $link['title'] = t('My spaces', array(), array('context' => 'gofast'));
  
  return $link;
}

/**
 * /gofast/menu/get/[nid]
 */
function gofast_create_menu_subspaces($parent_gid = NULL, $fullDepth = FALSE) {

  
  global $user;
  $submenus = array();

  if (!gofast_og_is_space(node_load($parent_gid))) {
    return $submenus;
  }

  $subspaces = gofast_og_get_space_children_by_user($parent_gid, $user);

  if (count($subspaces) > 0) {

    foreach ($subspaces as $nid) {
      $space = new stdClass();
      $space->title = gofast_get_node_title($nid);
      $space->type = gofast_get_node_type($nid, TRUE);
      $space->field_format['und'][0]['tid'] = reset(gofast_mobile_get_node_format((int) $nid));
      $icon = gofast_node_get_icon($space);

      $sub_subspaces = gofast_og_get_space_children_by_user($nid, $user);
      $has_submenu = (count($sub_subspaces) > 0) ? TRUE : FALSE;

      $menu = array(
        'id' => 'gf_og_'.$nid,
        'icon' => 'fas n-color ' . $icon,
        'label' => t($space->title),
        'href' => '/node/' . $nid,
        'class' => 'gf-dropdown-submenu gf-megamenu-submenu',
        'subclass' => 'menu-submenu-right',
        'has_submenu' => $has_submenu,
        'attrs' => array("gid" => $nid ),
        'menu' => array()
      );
      
      
      
      if($fullDepth === TRUE){
        $menu['menu'] = gofast_create_menu_subspaces($nid);
      }
      $submenus[] = $menu;

      //Sort by label
      usort($submenus, function($a, $b) {
        return strcasecmp($a['label'], $b['label']);
      });
    }

    return $submenus;
  }
}

;
