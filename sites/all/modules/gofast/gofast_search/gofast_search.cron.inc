<?php

/**
 * @file
 * 
 * Gofast Search cronjobs definition.
 */


/**
 * Gofast Search cronapi callback
 * 
 * Handle a possible script crash that could have occurred during the last 
 * indexing job.
 */
function gofast_search_cron_postcrash() {
  if ($nid = variable_get('gofast_search_tika_is_working', FALSE)) {
    // Assuming the last apachesolr_cron job crashed due to PHP OOM (Tika),
    // register the referenced node as "excluded from Tika".
    gofast_search_prevents_extraction($nid, array('type' => 1, 'message' => 'Last apachesolr_cron job crashed due to PHP OOM (cron channel default run started while the Tika flag was still "on").'));
    variable_del('gofast_search_tika_is_working');
  }
  if ($reports = variable_get('gofast_mail_report_scheduled', false)) {
    // Reports have to be sent to admins.
    foreach ($reports as $report) {
      call_user_func_array('gofast_mail_report', $report);
    }
    variable_del('gofast_mail_report_scheduled');
  }
}

/**
 * Gofast Search cronapi callback
 * 
 * Reindex nodes which have popularity modified.
 */
function gofast_search_cron_reindex_pop() {
  ctools_include('apachesolr.index', 'apachesolr', '');
  
  // No-op if full reindexing is ongoing
  if (variable_get('gofast_full_reindex', FALSE) === FALSE) {
    // Which nodes need reindexing.
    $nids = gofast_search_popularity_check_nodes();
    
    if (!empty($nids)){
      // Get queued content to be indexed for comparison ().
      $query = _apachesolr_index_get_next_set_query(GOFAST_SEARCH_ENV_ID, 'node');
      $queued = $query->execute()->fetchAllAssoc('entity_id');
      $q_nids = array_keys($queued);
      
      // Reindex only nodes that are not already in queue. 
      $to_index = array_diff($nids, $q_nids);
      gofast_search_reindex_entities($to_index, 'node');
    }
  }
  
  variable_set('gofast_last_popularity_reindex', time());
}


/**
 * Checks for nodes having their popularity changed since last check.
 * 
 * @return array >
 *  An array of nids corresponding to the updated nodes.
 */
function gofast_search_popularity_check_nodes(){
  $nids = [];
  
  // Get the timestamp corresponding to the last popularity reindex
  $t = variable_get('gofast_last_popularity_reindex', FALSE);
  
  // Prevent reindexing all nodes if we have no point of comparison. 
  if ($t) {
    // Grab nodes having popularity timestamp greater than last reindex timestamp.
    $query = 'SELECT entity_id FROM {field_data_field_popularity} WHERE field_popularity_radioactivity_timestamp > '. $t;
    $nids = db_query($query)->fetchCol();
    
    // Energy cut-off is set to 1 to prevent performance issue. That means nodes
    // having a popularity < 1 are not tracked by radioactivy module, so we need 
    // to retrieve nodes which have their popularity changed from a value > 1 to
    // a value < 1 since they are missing from $nids if any. 
    // First, grab popular nodes from Solr. 
    $popular = gofast_search_get_popular_nodes_from_index();
    if ($popular === FALSE) {
      $popular = [];
    }
    
    // Check which one of them is not tracked anymore, then merge with $nids.
    $tracked = db_query('SELECT entity_id FROM {field_data_field_popularity}')->fetchCol();  
    $untracked = array_diff($popular, $tracked);
    $nids = array_merge($nids, $untracked);
  }
  else {
    // Ensure we have a ref. for next check. 
    variable_set('gofast_last_popularity_reindex', time());
  }

  return $nids;
}

/**
 * Retrieves nids of nodes considered popular from solr index.
 * 
 * @return mixed array|boolean
 *  An array of nids or FALSE if request failed. 
 */
function gofast_search_get_popular_nodes_from_index() {
  ctools_include('gofast_search.admin', 'gofast_search', '');
  
  $stats = gofast_search_get_stats(GOFAST_SEARCH_ENV_ID, TRUE);
  $environment = apachesolr_environment_load(GOFAST_SEARCH_ENV_ID);
  $l = parse_url($environment['url']);

  $handler = '/select';

  $l['path'] .= $handler;
  $l['user'] = 'admin';
  $l['pass'] = gofast_get_admin_pwd();

  $query = [
    'qt' => 'select',
    'q' => 'entity_type:node',
    'fl' => 'entity_id',
    'rows' => $stats['indexed'],
    'fq' => 'ps_popularity:[0.9 TO *]'
  ];

  $l['query'] = drupal_http_build_query($query);

  $url = "{$l['scheme']}://{$l['user']}:{$l['pass']}@{$l['host']}:{$l['port']}{$l['path']}?{$l['query']}";
  $response = drupal_http_request($url);

  _gofast_search_check_solr_cmd_response($response, 'solr/radioactivity', 'grab popular nodes');
  
  if (empty($response->data)) {
    watchdog('Gofast Search', 'Could not retrieve popular nodes from index.', $variables, WATCHDOG_ERROR);
    return FALSE;
  }
  
  $data = json_decode($response->data);
  
  if (empty($data->response->docs)) {
    return [];
  }
  
  $nids = [];
  foreach ($data->response->docs as $key => $doc) {
    $nids[] = $doc->entity_id;
  }
  
  return $nids;
}

/**
 * Gofast Search cronapi callback
 * 
 * Rebuild the suggester indexes.
 */
function gofast_search_cron_rebuild_suggester() {
  $environment = apachesolr_environment_load(GOFAST_SEARCH_ENV_ID);
  $l = parse_url($environment['url']);
  
  $suggester_handler = '/suggest';
  
  $l['path'] .= $suggester_handler;
  $l['user'] = 'admin';
  $l['pass'] = gofast_get_admin_pwd();

  $query = [
    'suggest' => 'true', // should always be true when dealing with this handler
    'suggest.count' => '0', // we actually don't want suggestions
    'suggest.buildAll' => 'true', // rebuild all indexes (dictionaries)
    'suggest.reloadAll' => 'true', // reload all indexes
  ];

  $l['query'] = drupal_http_build_query($query);

  $url = "{$l['scheme']}://{$l['user']}:{$l['pass']}@{$l['host']}:{$l['port']}{$l['path']}?{$l['query']}";
  $result = drupal_http_request($url);

  _gofast_search_check_solr_cmd_response($result, 'solr/suggester', 'rebuild index command');
}

/**
 * Gofast Search cronapi callback
 * 
 * Rebuild the spellchecker indexes.
 */
function gofast_search_cron_rebuild_spellchecker() {
  $environment = apachesolr_environment_load(GOFAST_SEARCH_ENV_ID);
  $l = parse_url($environment['url']);
  
  $handler = '/select';
  
  // There is no buildAll command for spellcheck dictionaries.
  $dictionaries = [
    // Add here the dictionaries used in gofast request handler. 
    //'default', uses DirectSolrSpellChecker (relies on the main index)
    'wordbreak'
  ];  
  
  $l['path'] .= $handler;
  $l['user'] = 'admin';
  $l['pass'] = gofast_get_admin_pwd();

  foreach ($dictionaries as $dict) {
    $query = [
      'q' => '*:*',
      'fl' => '',
      'rows' => 0,
      'spellcheck' => 'true',
      'spellcheck.dictionary' => $dict,
      'spellcheck.build' => 'true', 
      'spellcheck.reload' => 'true'
    ];
  
    $l['query'] = drupal_http_build_query($query);

    $url = "{$l['scheme']}://{$l['user']}:{$l['pass']}@{$l['host']}:{$l['port']}{$l['path']}?{$l['query']}";
    $result = drupal_http_request($url);

    _gofast_search_check_solr_cmd_response($result, 'solr/spellchecker', 'rebuild index command');
  }
}

/**
 * Helper that checks Solr rebuild command response and log accordingly. 
 */
function _gofast_search_check_solr_cmd_response($response, $component, $description) {
  $var = [
    '!comp' => $component,
    '!desc' => $description
  ];
  if ($response->code == 200) {
    // HTTP status is OK but we still need to check the command response. 
    if (!empty($response->data)) {
      $data = json_decode($response->data);
      if (!empty($data->error)) {
        $var += [ '!msg' => $data->error->msg, '!code' => $data->error->code ];
        watchdog('Gofast Search', '!comp error : !msg - code: !code', $var, WATCHDOG_ERROR);
      }
      else {
        // Command was successful, log QTime.
        $var += [ '!t' => $data->responseHeader->QTime ];
        watchdog('Gofast Search', '!comp - !desc - QTime=!tms', $var);
      }
    }
    else {
      watchdog('Gofast Search', '!comp - !desc : no data returned.', $var, WATCHDOG_ERROR);
    }
  }
  else {
    $var += ['!code' => $response->code];
    watchdog('Gofast Search', 'Error encountered - !comp - !desc. HTTP Status=!code', $var, WATCHDOG_ERROR);
  }
}