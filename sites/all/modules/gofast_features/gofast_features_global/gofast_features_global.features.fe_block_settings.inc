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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -5,
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

  $export['facetapi-92UUVWTLTPj6BCT01cxok6z1M059jUaB'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => '92UUVWTLTPj6BCT01cxok6z1M059jUaB',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '<?php
$options = array_map(function ($item) { return $item["value"]; }, gofast_search_options());
return isset($options["include-deleted"]) && $options["include-deleted"];
?>',
    'roles' => array(
      'administrator' => 3,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -25,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -24,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -25,
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
  
  $export['facetapi-stCK3p1pqOoldH3aHCNHQeLwUKhxjp0X'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'stCK3p1pqOoldH3aHCNHQeLwUKhxjp0X',
    'module' => 'facetapi',
    'node_types' => array(),
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
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
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

  $export['facetapi-B5gBLZB40UdSjPP0LNE1Ulp7aeUE3YcP'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'B5gBLZB40UdSjPP0LNE1Ulp7aeUE3YcP',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -38,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -33,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -38,
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

  $export['facetapi-BHiFEIqUWHxvFsag27pIUX0buKyEvnTu'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'BHiFEIqUWHxvFsag27pIUX0buKyEvnTu',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -44,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -36,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -44,
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

  $export['facetapi-BzPECiCdVnXcCj2XLhTMisuxAuWM1mYr'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'BzPECiCdVnXcCj2XLhTMisuxAuWM1mYr',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -32,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -28,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -32,
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

  $export['facetapi-KCgvQpfl4sa74ytQpJabF1aCIiUNnvax'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'KCgvQpfl4sa74ytQpJabF1aCIiUNnvax',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -31,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -27,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
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

  $export['facetapi-Nfm5rJukhKAVAfhml8Kh3sgt1rqRrJ1j'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'Nfm5rJukhKAVAfhml8Kh3sgt1rqRrJ1j',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -35,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -31,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -35,
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

  $export['facetapi-NlPTURTL0kNVgQw1QFKKPDcOQ8c1glSX'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'NlPTURTL0kNVgQw1QFKKPDcOQ8c1glSX',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -40,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -35,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -40,
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

  $export['facetapi-Tyz3B6agozQa7WmvxpF3nPi6zVqI74BA'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'Tyz3B6agozQa7WmvxpF3nPi6zVqI74BA',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -33,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -29,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -33,
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

  $export['facetapi-WIh38uN0LqAB3yTCuruCH64TWqbXV02j'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'WIh38uN0LqAB3yTCuruCH64TWqbXV02j',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -34,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -30,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -34,
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

  $export['facetapi-bLd1qxpEqn41AaDkLKGukDy4Pa58j2yf'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'bLd1qxpEqn41AaDkLKGukDy4Pa58j2yf',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -36,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -32,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -36,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Spaces',
    'visibility' => 0,
  );

  $export['facetapi-fHWtNs2CwIRHzlG1amHG1tK9nWouVnuW'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'fHWtNs2CwIRHzlG1amHG1tK9nWouVnuW',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -30,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -26,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
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

  $export['facetapi-qbinparXldWoyR0fadV8cRwIY4reG9zO'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'qbinparXldWoyR0fadV8cRwIY4reG9zO',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -29,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -25,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -29,
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

  $export['facetapi-yAEUE2ISArAx3t6LoeCmdng5qrLkp7tN'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'yAEUE2ISArAx3t6LoeCmdng5qrLkp7tN',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -39,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -34,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -39,
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

  $export['facetapi-zajk0pGWEW0UJuM5hoXYKDVXEMpYRQv8'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'zajk0pGWEW0UJuM5hoXYKDVXEMpYRQv8',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -45,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -37,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -45,
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

  $export['facetapi-JTciEtFqvh2wjddOcK9OrfYZS6SgNLje'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'JTciEtFqvh2wjddOcK9OrfYZS6SgNLje',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -27,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -37,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -27,
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

  $export['facetapi-RWMfMjRxjuc2sj0ccNMGuzd56dUkP71O'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'RWMfMjRxjuc2sj0ccNMGuzd56dUkP71O',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -43,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -35,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
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
    'visibility' => 0,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -9,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -28,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -43,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -26,
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

  $export['gofast_ajax_file_browser-main_ajax_file_browser'] = array(
    'cache' => 8,
    'custom' => 0,
    'delta' => 'main_ajax_file_browser',
    'module' => 'gofast_ajax_file_browser',
    'node_types' => array(),
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
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => 'explorer',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -56,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -53,
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
      if (current_path() != "" && (drupal_is_front_page() && current_path() != "dashboard" && current_path() != "dashboard2")  && current_path() != "gofast/browser" && (current_path() != "dashboard" && current_path() != "dashboard2")) {
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -46,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
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
      'bootstrap_keen' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -51,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -47,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -45,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -13,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -27,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -54,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -27,
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
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -19,
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
      'bootstrap_keen' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -49,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -21,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -20,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => -12,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 6,
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
      'bootstrap_keen' => array(
        'region' => 'content',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => -46,
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
      'bootstrap_keen' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_keen',
        'weight' => 26,
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

  $export['facetapi-RPgGWR1sojqXFjYqa5qRtodUEUa0B2c5'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'RPgGWR1sojqXFjYqa5qRtodUEUa0B2c5',
    'module' => 'facetapi',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => 0,
      ),
      'bootstrap_keen' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_keen',
        'weight' => 0,
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


  return $export;
}
