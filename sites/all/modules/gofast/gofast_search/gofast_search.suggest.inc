<?php

/**
 * @file
 *  Handles suggestions & spellchecking settings/processing.
 */

/**
 * Returns settings for client side autocomplete data processing.
 */
function gofast_search_autocomplete_settings() {
  $env = apachesolr_environment_load(GOFAST_SEARCH_ENV_ID);
  $core_path = parse_url($env['url'], PHP_URL_PATH);
  
  $suggester_handler = '/suggest';
  $headers_param = array();
  
  // Need proxy authentication and/or solr auth plugin/backend. 
  
  // Use solr restricted user credentials if any, allowing clients to make 
  // requests straight to /suggest handler by setting authorization header.
  $authorized = GOFAST_SEARCH_RESTRICTED_USER_AUTHORIZE;
  $defined = GOFAST_SEARCH_RESTRICTED_USER !== FALSE && GOFAST_SEARCH_RESTRICTED_USER_PASS !== FALSE;
  if ($authorized && $defined) {
    $autocomplete_path = ltrim($core_path . $suggester_handler, '/');
    $auth_str = base64_encode(GOFAST_SEARCH_RESTRICTED_USER . ':' . GOFAST_SEARCH_RESTRICTED_USER_PASS);
    $headers_param = ['headers' => ['Authorization' => 'Basic ' . $auth_str]];
  }
  else {
    // Request suggestions via drupal callback gofast_search_solr_autocomplete()
    // using admin credentials for proxy authorization. 
    $autocomplete_path = 'gofast-search/solr-autocomplete';    
  }
 
  return array(
    'autocomplete_path' => $autocomplete_path, 
    'collector' => 'Gofast.search',
    'queryKey' => array('suggest_q'),
    'escFunc' => 'Gofast.search.escapeQuery',
    'callback' => NULL, 
    'minLength' => 2,
    'delay' => 200,
    'submitOnClick' => TRUE,
    'editableLabel' => TRUE,
    'multiple' => FALSE,
    'param' => array(
      'type' => 'GET',
      'dataType' => 'json',
      'weight' => 2,
      'data' => array(
        'wt' => 'json',
      )
    ) + $headers_param,
  );
}

/**
 * Retrieve all of the suggestions that were given after a certain search
 */
function _gofast_search_get_search_suggestions($env_id) {
//  1. If spellcheck.alternativeTermCount is > 0, the default behavior for 
//  each term should be to iterate over all suggestions to take the best one :  
//  frequency (for extendedResults) of the suggested term, or the number of char 
//  edit that occured might allow us to manage such a behavior. 
//  
//  2. If spellcheck.extendedResults is true then $value->suggestion[0] is not 
//  an array but an object.
//  
//  3. If spellcheck.collate is true, then 'collation' is returned as $word (if
//  collateExtendedResults is true 'correctlySpelled' is returned as well), thus
//  making it impossible to expect one of these keywords as a suggestion without
//  checking its $value/typeof.
//  -> This has been fixed (cf. SOLR-3029, SOLR-9972, SOLR-10522), but still 
//  the issue below (4) persists. 
//  
//  4. If spellcheck.collate is true, spellCheckComponent json response is not 
//  formatted correctly : "collation" should be a unique key for one array of 
//  collations, instead each of these is returned with the same 'collation' key
//  thus resulting in the last collation overriding the other ones, regardless
//  of spellcheck.maxCollations parameter. This is the consequence of a bug in 
//  the spellCheckComponent (now fixed, @see SOLR-3029, SOLR-9972, SOLR-10522) 
//  BUT ALSO the consequence of using lossy output format for NamedLists, which 
//  is the case (cf. DrupalApacheSolrService::NAMED_LIST_FORMAT = 'map'). 
//  We can't override this since the whole results structure will be impacted 
//  and this would require a huge refactoring, so we have to rebuild collations 
//  by hand.
  
  $suggestions_output = array();
  if (!apachesolr_has_searched($env_id)) {
    return $suggestions_output;
  }
  
  $query = apachesolr_current_query($env_id);
  $keyword = $query->getParam('q');
  
  $searcher = $query->getSearcher();
  $response = apachesolr_static_response_cache($searcher);
  $params = $response->responseHeader->params;

  if (empty($response->spellcheck->suggestions)) {
    // no suggestion, no collation. Don't go further.
    return $suggestions_output;
  }
  
  // Get spellchecker suggestions into an array.
  $suggestions = get_object_vars($response->spellcheck->suggestions);

  if ($params->{'spellcheck.collate'} === 'true') {
    // Rebuild  missing spellcheck collations from the solr output. @ceovision (4)
    gofast_search_rebuild_collations($response);
    
    if ($params->{'spellcheck.collateExtendedResults'} === 'true') {
      $collations = gofast_search_collation_queries($response->spellcheck->collations);
    }
    else {
      $collations = $response->spellcheck->collations;
    }
  }
  
  // Prefer collations over simple suggestions. 
  if (!empty($collations)) {
    $suggestions_output = array_values((array)$collations);
  }
  elseif ($suggestions) {
    $replacements = array();
    foreach ($suggestions as $word => $value) {
      $suggestion = $value->suggestion;
      // Setting spellcheck.extendedResults query parameter to true makes words
      // objects instead of strings.
      $replacements[$word] = is_object($suggestion[0]) ? $suggestion[0]->word : $suggestion[0];
    }
    $suggested_keyword = strtr($keyword, $replacements);
    if ($keyword != $suggested_keyword) {
      $suggestions_output[] = $suggested_keyword;
    }
  }

  return $suggestions_output;  
}

/**
 * Retrieves missing spellcheck collations from the solr output. If successful, 
 * replaces the wrong 'collation' object keys by a unique identifier collation-n.
 * 
 * Params spellcheck.collate must be set to TRUE.
 */
function gofast_search_rebuild_collations (&$response) {
  if (!$response->spellcheck->collations) {
    return;
  }

  // Solr returned at least 1 collation object. 

  $c_pattern = '"collations":{';
  if (($pos = strpos($response->data, $c_pattern)) === FALSE) {
    watchdog('Gofast Solr', 'Unable to retrieve missing collations from raw data.');
    return;
  }
  
  $extended = $response->responseHeader->params->{'spellcheck.collateExtendedResults'} === 'true';

  // -1 to keep the opening brace.
  $_data = substr($response->data, $pos + strlen($c_pattern) - 1);
  
  for ($i = $_c = 0, $len = strlen($_data); $i < $len; $i++) {
    ($_data[$i] === '{' && $_c++) || ($_data[$i] === '}' && $_c-- && $_end = $_c === 0);
    if ($_end)
      break;
  }

  // Attempt to retrieve any overriden collations from the raw response.
  $raw_collations = substr($_data, 0, $i + 1);

  // Reformat data so that the collations object is indexed by a unique identifier
  // such as 'collation-<n>' instead of 'collation'.
  $iterator = 0;
  $pattern = $extended ? '/"collation":{/' : '/"collation":/';
  $str = $extended ? '":{' : '":';
  $raw_collations = preg_replace_callback($pattern, function($_matches) use (&$iterator, $str) {
    return '"collation-' . $iterator++ . $str; 
  }, $raw_collations);
  
  // Rebuild the collations array.
  $collations = json_decode($raw_collations);
  if (gofast_json_get_error() === JSON_ERROR_NONE) {
    // Replace the malformed collations object. 
    $response->spellcheck->collations = $collations;
  }
}


function gofast_search_extended_suggestions($suggestions, $keyword) {
  $replacements = array();
  
  foreach ($suggestions as $word => $value) {
    // Ignore collations.
    if (!isset($value->suggestion) && $word === 'collation') {
      continue;
    }
    // Handle individual keyword replacements.
    $proposals = (array) $value->suggestion;
    foreach ($proposals as $k => $proposal) {
      $suggestion = strtr($keyword, array($word => $proposal->word));
      if ($keyword === $suggestion) {
        continue;
      }
      $replacements[] = $suggestion;
    }
  }
  return $replacements;
}


function gofast_search_collation_queries($collations) {
  $collation_queries = [];
  
  foreach ($collations as $key => $collation) {
    if ($collation->hits < 1) {
      // Ignore if no match
      continue;
    }
    $collation_queries[] = $collation->collationQuery;
  }
  
  return $collation_queries;
}

/**
 * Node search autocomplete callback.
 */
function gofast_search_node_autocomplete($str) {
  $str = trim($str);

  if (empty($str) || strlen($str) < 3) {
    // This prevents returning irrelevant results, though it should be handled 
    // clientside in order to avoid useless requests.
    drupal_json_output(array());
    exit;
  }

  $matches = gofast_ac_query($str, 'node', array('link' => TRUE));
  
  // Highlighting string matches.
  foreach ($matches as $key => &$value) {
    $value = preg_replace('/(<[^<>]*>)([^<>]*?)(' . preg_quote($str, '/') . ')/i', '$1$2<b>$3</b>', $value);
  }
  
  drupal_json_output($matches);
  exit;
}

/**
 * User search autocomplete callback.
 */
function gofast_search_user_autocomplete($str) {
  $str = trim($str);

  if (empty($str) || strlen($str) < 3) {
    // This prevents returning irrelevant results, though it should be handled 
    // clientside in order to avoid useless requests.
    drupal_json_output(array());
    exit;
  }

  $matches = gofast_ac_query($str, 'user', array('link' => TRUE));
  
  // Highlighting string matches.
  foreach ($matches as $key => &$value) {
    $value = preg_replace(array('/[\n\r]+/', '/(<[^<>]*>)([^<>]*?)(' . preg_quote($str, '/') . ')/i'), array('', '$1$2<b>$3</b>'), $value);
  }
  
  drupal_json_output($matches);
  exit;
}

/**
 * Special apachesolr_query_alter_hook used for autocomplete suggestions. 
 * 
 * @global type $user
 * @param DrupalSolrQueryInterface $query
 */
function gofast_search_autocomplete_query_alter(DrupalSolrQueryInterface $query) {
  global $user;
  $account = user_load($user->uid);

  //Boost when it's exact match
  $query->replaceParam('qf', ['suggest_label^1.0','tws_label^10.0']);
  
  $query->replaceParam('fl', [
    'id',
    'bundle',     
    'entity_id',
    'entity_type',
    'tws_label',
    'suggest_label',
    'im_field_format'
  ]);
  
  $query->replaceParam('hl', 'on');
  $query->replaceParam('hl.fl', ['suggest_label']);
  
  // Access control 
  if ($account->uid != 1){
    // Exclude orphan nodes. 
    $query->addFilter('access_node_nn0szh_all', 0, TRUE);  

    // Add grants for the user performing search.
    try {
      // $query passed by reference
      gofast_search_query_alter_access($account, $query);
    }
    catch (Exception $e) {
      watchdog("Gofast Solr", 'User %name (UID:!uid) cannot search: @message', array('%name' => $account->name, '!uid' => $account->uid, '@message' => $e->getMessage()));
      $query->abort_search = TRUE;
    }
  }
  
  // Search options 
  gofast_search_query_alter_from_options($query);
  
  // Boost functions: since there are no other boost functions to balance these we can't push them too far
  $query->replaceParam('bf', [
    'sqrt(ps_popularity)^20.0',
    'recip(ms(NOW,ds_changed),3.16e-11,1,1)^100.0'
  ]);

  $query->replaceParam('rows', 10);
  $query->replaceParam('echoParams', 'none');
}


/**
 * Autocomplete callback bound to /autocomplete request handler (edge ngram) 
 * on which we can use regular queries (ie. fq for access filter).
 */
function gofast_search_solr_autocomplete($arg = NULL){
  $params = [
    'q' => $_REQUEST['suggest_q']
  ];
  
  if ($arg) {
    // Allow override from argument for testing 
    $params = $arg;
  }
  
  // Don't allow local params to pass through to EDismax from the url.
  // We also remove any remaining leading {! since that causes a parse
  // error in Solr.
  $params['q'] = preg_replace('/^(?:{![^}]*}\s*)*(?:{!\s*)*/',' ', $params['q']);

  $name = 'apachesolr';
  $solrsort = '';
  $base_path = '';
  $page = 0;
  $solr = apachesolr_get_solr(GOFAST_SEARCH_ENV_ID);
  $context = [];
  
  // This is the object that knows about the query coming from the user.
  $query = apachesolr_drupal_query($name, $params, $solrsort, $base_path, $solr, $context);  
  $searcher = $query->getSearcher();
  
  // Set static cache
  $query = apachesolr_current_query(GOFAST_SEARCH_ENV_ID, $query);
  
  // Verify if this query was already executed in the same page load
  if (!$response = apachesolr_static_response_cache($searcher)) {
    $query->addParam('qt', '/autocomplete');

    // Let modules modify the query object for access filtering. 
    drupal_alter('apachesolr_query', $query);

    $keys = $query->getParam('q');

    // We must run htmlspecialchars() here since converted entities are in the index.
    // and thus bare entities &, > or < won't match. Single quotes are converted
    // too, but not double quotes since the dismax parser looks at them for
    // phrase queries.
    $keys = htmlspecialchars($keys, ENT_NOQUOTES, 'UTF-8');
    $keys = str_replace("'", '&#039;', $keys);
    
    try {
      $response = $query->search($keys);
    } 
    catch (Exception $e) {
      // status code != 200
      $exception = $e->getMessage();
      watchdog('Gofast Search', 'Solr /autocomplete error : "' . $exception . '"', [], WATCHDOG_ERROR);
      return [];
    }
    
    // The response is cached so that it is accessible to the blocks and anything
    // else that needs it beyond the initial search.
    apachesolr_static_response_cache($searcher, $response);   
  }
    
  $docs = $response->response->docs;
  $output = [];

  foreach ($docs as $doc) {
    $hl = $doc->tus_label;
    $q = $_REQUEST['suggest_q'];
    $hl = htmlspecialchars_decode($hl, ENT_NOQUOTES); // 1st pass &amp;  => &
    $hl = htmlspecialchars_decode($hl, ENT_QUOTES);   // 2nd pass &#039; => '
    // Create a character map for accent-insensitive matching
    $character_map = [
      'a' => '[aáàâä]',
      'e' => '[eéèêë]',
      'i' => '[iíìîï]',
      'o' => '[oóòôö]',
      'u' => '[uúùûü]',
      'c' => '[cç]',
    ];
    // Create a regex pattern for the search query
    $q_pattern = '';
    for ($i = 0; $i < strlen($q); $i++) {
      $char = strtolower($q[$i]);
      $q_pattern .= isset($character_map[$char]) ? $character_map[$char] : preg_quote($q[$i], '/');
    }
    // Highlighting (case-insensitive match)
    $hl = preg_replace_callback('/' . $q_pattern. '/iu', function($match) {
      return "<strong>{$match[0]}</strong>";
    }, $hl);
    switch ($doc->entity_type) {
      case 'node':
      case 'user':
        // For both entities we use theme node_title. We add the bundle property
        // to let it recognize user entity and theme it like a node would be. 
        // Use dummy node object to avoid entity load. 
        $dummy = (object) [
            'nid' => $doc->entity_id,
            'title' => $hl,
            'type' => $doc->bundle,
            'field_format' => [
              LANGUAGE_NONE => [
                ['tid' => $doc->im_field_format[0]]
              ]
            ]
        ];
        $label = theme('node_title', ['node' => $dummy, 'link' => TRUE]);
        break;
      
      default:
        $label = '<span>' . $hl . '</span>';
    }

    $key = "<{$doc->entity_type}:{$doc->entity_id}>";
    $output[$key] = $label;
  }
  
  return $output;
}


/**
 * Fixes /autcomplete highlighter imprecision. 
 */
function gofast_search_autocomplete_fix_highlight($hl, $keys) {
  $keys = preg_quote($keys, '/');
  // Hopefully "<" is not allowed in the title.
  return preg_replace("/({$keys})([^<]*)?(<\/b>)/i", '$1$3$2', $hl);
}


/**
 * Autocomplete callback used to query our Solr Suggester component. 
 * We cannot use it for now as it is not possible to filter queries (no access 
 * control). 
 */
function gofast_search_solr_autocomplete_from_suggester(){
  $params = $_REQUEST;
  $params["q"] = $params["sq"];
  unset($params["sq"]);
  
  // This should match 'true'|'false' as a string (case sensitive). 
  $params['suggest.cfq'] = 'true';
  $param_string = '';
  
  foreach($params as $param_name => $param_value){
    if ($param_string !== ""){
      $param_string .= "&";
    }
    $param_string .= $param_name."=".rawurlencode($param_value);
  }

  $param_string = str_replace(" ", "+", $param_string);

  $username = 'admin';
  $pass = gofast_get_admin_pwd();
  $url = "http://".$username.":".$pass."@localhost:8983/solr/gofast/suggest?".$param_string;
  
  $options = array(
    'headers' => array(),
    'method' => 'GET',
    'data' => NULL,
  );

  $result = drupal_http_request($url, $options);
  
  return $result->data;
}