<?php
/**
 * @file
 * gofast_features_global.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gofast_features_global_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['comment-recent'] = array(
    'cache' => 1,
    'custom' => 0,
    'delta' => 'recent',
    'module' => 'comment',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -44,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -19,
      ),
      'seven' => array(
        'region' => 'dashboard_inactive',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['facetapi-p4qpTYeYVZKBxyOGtweKWKo0Oh3Zd5Sx'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'p4qpTYeYVZKBxyOGtweKWKo0Oh3Zd5Sx',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -42,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['gofast-gofast_audit_node_page'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_audit_node_page',
    'module' => 'gofast',
    'node_types' => array(),
    'pages' => '<?php return TRUE; ?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -20,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -61,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -61,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast-gofast_node_actions'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_node_actions',
    'module' => 'gofast',
    'node_types' => array(),
    'pages' => '<?php return TRUE; ?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -25,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -40,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -50,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast-gofast_node_comments_tree'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_node_comments_tree',
    'module' => 'gofast',
    'node_types' => array(),
    'pages' => '<?php
$account = $GLOBALS[\'user\'];
if( arg(0) == \'node\' and is_numeric(arg(1)) and (arg(2) == FALSE || arg(2) == "replytocomment") ){
  $node = node_load(arg(1));
  if($node->type == \'alfresco_item\' || $node->type == \'article\'  || $node->type == \'forum\' || $node->type == \'webform\'){
     if(node_access(\'view\',$node, $account) && variable_get(\'site_frontpage\', \'node\') !== "node/".$node->nid){
      return TRUE;
    }else{
      return FALSE;
    }
  }else{
  return FALSE;
  }
}else{
  return FALSE;
}
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -28,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -25,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -60,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast-gofast_node_infos'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_node_infos',
    'module' => 'gofast',
    'node_types' => array(),
    'pages' => '<?php
$account=$GLOBALS[\'user\'];
if( arg(0) == \'node\' && is_numeric(arg(1)) && (arg(2) == FALSE || arg(2) == "replytocomment") ){
  $node = node_load(arg(1));
  if($node->type == \'alfresco_item\' || $node->type == \'article\' || $node->type == \'forum\' || $node->type == \'webform\'){
    if(node_access(\'view\',$node, $account)){
      return TRUE;
    }else{
      return FALSE;
    }
  }else{
  return FALSE;
  }
}else{
  return FALSE;
}
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -43,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -39,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -40,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast-lang_switch'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'lang_switch',
    'module' => 'gofast',
    'node_types' => array(),
    'pages' => '<?php return TRUE; ?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -38,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -43,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -50,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_book-gofast_book_group'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_book_group',
    'module' => 'gofast_book',
    'node_types' => array(
      0 => 'article',
      1 => 'extranet',
      2 => 'group',
      3 => 'organisation',
      4 => 'private_space',
      5 => 'public',
    ),
    'pages' => '<?php
 if(node_load(arg(1))->type == \'article\'){
return true;
}else{
return false;
}
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -53,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -54,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -40,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_cmis-gofast_cmis_fast_upload_file'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'gofast_cmis_fast_upload_file',
    'module' => 'gofast_cmis',
    'node_types' => array(),
    'pages' => '<?php
  if (!user_is_logged_in()) {
    return FALSE;
  }
  else {
    if (arg(0) == \'node\' and is_numeric(arg(1)) and arg(2) == FALSE) {
      $node = node_load(arg(1));
      if ($node->type == \'alfresco_item\') {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
    else {
      if (current_path() != "" && ((drupal_is_front_page() || current_path() == "activity") && current_path() != "dashboard" && current_path() != "dashboard2")  && current_path() != "gofast/browser" && (current_path() != "dashboard" && current_path() != "dashboard2")) {
        return TRUE;
      }
      else {
        return FALSE;
      }
    }
  }
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -46,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -43,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_menu-gofast_menu_icons'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'gofast_menu_icons',
    'module' => 'gofast_menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'administrator' => 3,
      'authenticated user' => 2,
      'contributor' => 4,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -42,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -42,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['gofast_search-gofast_saved_searches_fastaccess'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'gofast_saved_searches_fastaccess',
    'module' => 'gofast_search',
    'node_types' => array(),
    'pages' => '<?php return false; ?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -51,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -40,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -40,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_user-about_me'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'about_me',
    'module' => 'gofast_user',
    'node_types' => array(),
    'pages' => '<?php
// Only show on true user VIEW pages. Not node/add or node/n/edit etc
return (arg(0) == \'users\' || (arg(0) == \'user\' && is_numeric(arg(1))) && (!arg(2)));
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -47,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -43,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -47,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_user-my_relationships'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'my_relationships',
    'module' => 'gofast_user',
    'node_types' => array(),
    'pages' => 'user
user/*
users/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -45,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -42,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -44,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['gofast_user-my_team'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'my_team',
    'module' => 'gofast_user',
    'node_types' => array(),
    'pages' => 'user
user/*
users/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -44,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -41,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -45,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['gofast_views-activity_listing_filters'] = array(
    'cache' => 2,
    'custom' => 0,
    'delta' => 'activity_listing_filters',
    'module' => 'gofast_views',
    'node_types' => array(),
    'pages' => 'activity',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -37,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -37,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -37,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );
  $export['gofast_views-activity_stream_filters'] = array(
    'cache' => 2,
    'custom' => 0,
    'delta' => 'activity_stream_filters',
    'module' => 'gofast_views',
    'node_types' => array(),
    'pages' => '<?php
global $user;
if($user->uid == 0){
   return FALSE;
}
if(current_path() == "activity_feed"){
   return TRUE;
}

if(current_path() == "activity"){
   return TRUE;
}

if(drupal_is_front_page() || current_path() == "node"){
   if(variable_get(\'site_frontpage\', \'node\') == "node"){
      return TRUE;
   }else{
     return FALSE;
   }
}else{
return FALSE;
}

?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -27,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -24,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -36,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_views-activity_stream_link'] = array(
    'cache' => 2,
    'custom' => 0,
    'delta' => 'activity_stream_link',
    'module' => 'gofast_views',
    'node_types' => array(),
    'pages' => '<?php
global $user;
if($user->uid == 0){
   return FALSE;
}
if(drupal_is_front_page()){
   if(variable_get(\'site_frontpage\', \'node\') !== "node"){
      return TRUE;
   }else{
     return FALSE;
   }
}else{
return FALSE;
}

?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -36,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -36,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['gofast_views-gofast_book_blocks'] = array(
    'cache' => 2,
    'custom' => 0,
    'delta' => 'gofast_book_blocks',
    'module' => 'gofast_views',
    'node_types' => array(),
    'pages' => '_test_',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -39,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -23,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -36,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['gofast_views-gofast_og_filters'] = array(
    'cache' => 2,
    'custom' => 0,
    'delta' => 'gofast_og_filters',
    'module' => 'gofast_views',
    'node_types' => array(),
    'pages' => 'og/list_grid*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -24,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -22,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => -36,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['locale-language'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'language',
    'module' => 'locale',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -10,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -31,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['menu-menu-mobile-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'menu-mobile-menu',
    'module' => 'menu',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -27,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-main'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '<?php

if(drupal_is_front_page()){
   return FALSE;
 }

?>',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -49,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 2,
  );

  $export['system-main-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'main-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -30,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -30,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-management'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'management',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -31,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -29,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 1,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-navigation'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'navigation',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -22,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -24,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['system-user-menu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'user-menu',
    'module' => 'system',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -6,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -4,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['user-login'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'login',
    'module' => 'user',
    'node_types' => array(),
    'pages' => 'public/sharing*
public/multi_sharing*
Welcome
Access_config
conference/test-config
occitanie/feedback_page
occitanie/feedback_greatings
not_supported',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -46,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -53,
      ),
      'seven' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views--exp-gofast_audit-page'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '-exp-gofast_audit-page',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'gofast_audit
gofast_audit/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -27,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -42,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-037b626fb5fa50d5aadc9f47899c890b'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '037b626fb5fa50d5aadc9f47899c890b',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<front>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 8,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 1,
  );

  $export['views-gofast_activity_feed-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_activity_feed-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<?php
if(current_path() == "activity_feed"){
   return TRUE;
}
if(drupal_is_front_page() || current_path() == "node"){
   if(variable_get(\'site_frontpage\', \'node\') == "node"){
      return TRUE;
   }else{
     return FALSE;
   }
}else{
return FALSE;
}

?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -47,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '<none>',
    'visibility' => 2,
  );

  $export['views-gofast_activity_feed-block_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_activity_feed-block_1',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 6,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 13,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-gofast_activity_feed-block_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_activity_feed-block_2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 13,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 18,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-gofast_activity_feed-block_3'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_activity_feed-block_3',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 10,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 15,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  $export['views-gofast_activity_feed-block_4'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_activity_feed-block_4',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 9,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 14,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => '',
    'visibility' => 0,
  );

  return $export;
}
