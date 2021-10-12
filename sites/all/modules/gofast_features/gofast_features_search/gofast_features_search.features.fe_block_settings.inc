<?php
/**
 * @file
 * gofast_features_search.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function gofast_features_search_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['apachesolr_search-mlt-001'] = array(
    'cache' => 4,
    'custom' => 0,
    'delta' => 'mlt-001',
    'module' => 'apachesolr_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -15,
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

  $export['apachesolr_search-sort'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'sort',
    'module' => 'apachesolr_search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'bootstrap_gofast',
        'weight' => -48,
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

  $export['current_search-gofast_current_search_block'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'gofast_current_search_block',
    'module' => 'current_search',
    'node_types' => array(),
    'pages' => 'search/solr
search/solr/*',
    'roles' => array(),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -47,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -38,
      ),
      'seven' => array(
        'region' => '',
        'status' => 0,
        'theme' => 'seven',
        'weight' => 0,
      ),
    ),
    'title' => 'Current search',
    'visibility' => 1,
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
        'weight' => -43,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'sidebar_second',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -36,
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

  $export['search-form'] = array(
    'cache' => -1,
    'custom' => 0,
    'delta' => 'form',
    'module' => 'search',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(
      'authenticated user' => 2,
    ),
    'themes' => array(
      'bootstrap_gofast' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast',
        'weight' => -50,
      ),
      'bootstrap_gofast_mobile' => array(
        'region' => 'navigation',
        'status' => 1,
        'theme' => 'bootstrap_gofast_mobile',
        'weight' => -41,
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

  return $export;
}