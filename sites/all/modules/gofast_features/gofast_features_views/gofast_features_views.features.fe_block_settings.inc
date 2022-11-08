<?php
/**
 * @file
 * gofast_features_views.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gofast_features_views_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['views-f2962364d8e304f01f149b532354e3ab'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'f2962364d8e304f01f149b532354e3ab',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -13,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -15,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -14,
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

  $export['views-gofast_audit_node-block_audit'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_audit_node-block_audit',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<?php
if ($node = menu_get_object()) {
  if($node->type == \'alfresco_item\'){
       return true;
  }else{
       return false;
  }
}
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -21,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 1,
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

  $export['views-gofast_group_article-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_group_article-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 3,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 7,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 2,
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

  $export['views-gofast_group_content-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_group_content-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 4,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 8,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 3,
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

  $export['views-gofast_group_content-block_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_group_content-block_1',
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
        'weight' => 17,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
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

  $export['views-gofast_group_content-block_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_group_content-block_2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 12,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 16,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
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

  $export['views-gofast_og_members_admin-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_og_members_admin-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -2,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 2,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -3,
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

  $export['views-gofast_og_members_admin-block_2'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_og_members_admin-block_2',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -1,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 3,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -2,
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

  $export['views-gofast_recently_read-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_recently_read-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '<?php
if(strpos(current_path() , "search/solr")  !== false || strpos(current_path() , "dashboard")  !== false || strpos(current_path() , "gofast/browser")  !== false
|| strpos(current_path() , "pdf_compare/")  !== false || strpos(current_path() , "admin/config/gofast/ldap/manage")  !== false || strpos(current_path() , "user_listing_tab")  !== false  || strpos(current_path() , "inactive_users")  !== false || strpos(current_path() , "user_listing_grid_contrib")  !== false || strpos(current_path() , "occitanie")  !== false  || strpos(current_path(), "contacts-listing") !==false){
    return false;
}elseif( (arg(0) == "node") && (is_numeric(arg(1))) && (arg(2) == FALSE) ){
  $node = node_load(arg(1));
  if(gofast_og_is_space($node)){
      return false;
  }else{
  return true;
  }
}else{
   return true;
}
?>',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -23,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -23,
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

  $export['views-gofast_views-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_views-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 5,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 4,
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

  $export['views-og_members-block_1'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'og_members-block_1',
    'module' => 'views',
    'node_types' => array(
      0 => 'group_node',
      1 => 'orga',
    ),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 0,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => 4,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -1,
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

  $export['views-recently_read-block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'recently_read-block',
    'module' => 'views',
    'node_types' => array(),
    'pages' => 'search/solr/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => 1,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -19,
      ),
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
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

  return $export;
}
