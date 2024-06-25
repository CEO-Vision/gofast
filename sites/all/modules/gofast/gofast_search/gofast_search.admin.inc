<?php

/**
 * @file
 * 
 * Gofast Search configuration callbacks.
 */

function gofast_search_get_stats($env_id = GOFAST_SEARCH_ENV_ID, $exploitable = FALSE) {
  ctools_include('apachesolr.admin', 'apachesolr', '');
  $environment = apachesolr_environment_load($env_id);
  $return = array();

  // Check for availability
  $service_class_info = isset($environment['conf']['service_class_info']) ? $environment['conf']['service_class_info'] : NULL;
  $service_class = isset($environment['service_class']) ? $environment['service_class'] : NULL;
  if (!apachesolr_server_status($environment['url'], $service_class, $service_class_info)) {
    drupal_set_message(t('The server seems to be unavailable. Please verify the server settings at the <a href="!settings_page">settings page</a>', array('!settings_page' => url("admin/settings/apachesolr/settings/{$environment['env_id']}/edit", array('query' => drupal_get_destination())))), 'warning');
    return '';
  }

  try {
    $solr = apachesolr_get_solr($env_id);
    $solr->clearCache();
    $data = $solr->getLuke();
  }
  catch (Exception $e) {
    watchdog('Apache Solr', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
    drupal_set_message(nl2br(check_plain($e->getMessage())), "warning");
    $data = new stdClass;
    $data->fields = array();
  }

  $messages = array();
  if (isset($data->index->numDocs)) {
    try {
      // Collect the stats
      $stats_summary = $solr->getStatsSummary();
      module_load_include('inc', 'apachesolr', 'apachesolr.index');
      $status = apachesolr_index_status($environment["env_id"]);

      $pending_msg = $stats_summary['@pending_docs'] ? t('(@pending_docs sent but not yet processed)', $stats_summary, array('context' => 'gofast:gofast_search')) : '';
      $index_msg = $stats_summary['@index_size'] ? t('(@index_size on disk)', $stats_summary, array('context' => 'gofast:gofast_search')) : '';
      $indexed_message = t('@num Items !pending !index_msg', array(
        '@num' => $data->index->numDocs,
        '!pending' => $pending_msg,
        '!index_msg' => $index_msg,
      ), array('context' => 'gofast:gofast_search'));
      $messages[] = array(t('Indexed'), $indexed_message);
      $return['pending'] = $stats_summary['@pending_docs'];
      $return['indexed'] = $data->index->numDocs;

      $queued = t('@items (@percentage%)', array(
        '@items' => format_plural( $status['remaining'], t('1 item', array(), array('context' => 'gofast')), t('@count items', array(), array('context' => 'gofast'))),
        '@percentage' => 100 - ((int) min(100, 100 * ($status['total'] - $status['remaining']) / max(1, $status['total']))),
        ), array('context' => 'gofast:gofast_search')
      );
      $return['queued'] = $status['remaining'];
      $messages[] = array(t('Queued', array(), array('context' => 'gofast:gofast_search')), $queued);
    }
    catch (Exception $e) {
      watchdog('Apache Solr', nl2br(check_plain($e->getMessage())), NULL, WATCHDOG_ERROR);
    }
  }
  if (empty($messages)) {
    $messages[] = array(t('Error', array(), array('context' => 'gofast')), t('No data was returned from the server. Check your log messages.', array(), array('context' => 'gofast:gofast_search')));
  }
  else {
    // Add info about documents excluded from extration/index.
    $extract_logs = variable_get('gofast_search_tika_node_exclude', array());
    $items = format_plural(count($extract_logs), t('1 item', [], ['context' => 'gofast']), t('@count items', [], ['context' => 'gofast']));
    $excluded = t('@items', ['@items' => $items], ['context' => 'gofast']);
    $messages[] = [t('Excluded from extraction', [], ['context' => 'gofast:gofast_search']), $excluded];

    $index_logs = variable_get('gofast_search_index_node_exclude', array());
    $items = format_plural(count($index_logs), t('1 item', [], ['context' => 'gofast']), t('@count items', [], ['context' => 'gofast']));
    $excluded = t('@items', ['@items' => $items], ['context' => 'gofast']);
    $messages[] = [t('Excluded from index', [], ['context' => 'gofast:gofast_search']), $excluded];
  }

  foreach ($messages as $k => &$msg) {
    $msg = array('data' => $msg/*, 'style' => 'height:30px'*/);
    foreach ($msg['data'] as &$td) {
      $td = array('data' => $td/*, 'style' => 'padding:3px 15px'*/);
    }
  }
  
  if ($exploitable){
    return $return;
  }
  else {
   return theme('table', array('header' => array(), 'rows' => $messages));
  }
}

/**
 * Exclusion lists management callback.
 */
function gofast_search_manage_excluded_docs($exclusion_type, $nid, $queue = 0) {
  switch ($exclusion_type) {
    case 'extraction':
      $log_name = 'gofast_search_tika_node_exclude';
      break;
    case 'index':
      $log_name = 'gofast_search_index_node_exclude';
      break;
    default:
      watchdog('Gofast Solr', 'Cannot handle exclusion type "@type"', array('@type' => $exclusion_type));
      return drupal_goto('admin/config/gofast/global', array('fragment' => 'search-index'));
  }
  
  $excluded = variable_get($log_name, array());
  $ids = array_keys($excluded);
  
  if ($nid && isset($excluded[$nid])) {
    unset ($excluded[$nid]);
  }
  elseif ($nid == 0) {
    $excluded = array();
  }
  
  variable_set($log_name, $excluded);
  
  if ($queue) {
    if ($nid == 0) {
      $nodes = node_load_multiple($ids);
      ctools_include('apachesolr.index', 'apachesolr', '');
      apachesolr_index_nodeapi_mass_update($nodes);
    }
    else {
      apachesolr_mark_entity('node', $nid);
    }
  }
  
  return drupal_goto('admin/config/gofast/global', array('fragment' => 'search-index'));
}

/**
 * Start full reindexing. 
 */
function gofast_search_start_full_reindex() {
  watchdog('Gofast Search', 'Starting Full Reindex');
  module_load_include('inc', 'apachesolr', 'apachesolr.index');
  apachesolr_index_mark_for_reindex(GOFAST_SEARCH_ENV_ID);

  variable_set('gofast_full_reindex', REQUEST_TIME);
  $message = t('Full reindexing has started.', [], ['context' => 'gofast:gofast_search']);

  if (drupal_is_cli()) {
    // return message for drush. 
    return $message;
  }
  
  drupal_set_message($message);
  ctools_include('ajax');
  $commands = gofast_ajaxification_get_toast_messages();
  $commands[] = ajax_command_html('#ctools-add-js', "<script type='text/javascript'>
    Gofast.loadSettingsTab('edit-indexing');
    history.pushState({},'','/admin/config/gofast/global#search-index');
  </script>");
  print ajax_render($commands);
  exit;
}

/**
 * Cancel full reindexing. 
 */
function gofast_search_cancel_full_reindex() {
  $full_reindex_timestamp = variable_get('gofast_full_reindex', FALSE);
    
  if ($full_reindex_timestamp) {
    foreach (['node', 'user'] as $entity_type) {
      $table = apachesolr_get_indexer_table($entity_type);
      
      // Mark queued entities as processed by setting lower timestamp, other 
      // entities marked recently for indexing will still be indexed. 
      db_update($table)
        ->fields(array('changed' => $full_reindex_timestamp -1))
        ->condition('changed', $full_reindex_timestamp)
        ->execute();
      
      // Reset last position so that indexing keeps going normally. 
      $entity_id = db_query('SELECT MAX(entity_id) FROM {'.$table.'}')->fetchField();
      apachesolr_set_last_index_position(GOFAST_SEARCH_ENV_ID, $entity_type, $full_reindex_timestamp, $entity_id);
    }
  }
  
  variable_set('gofast_full_reindex', FALSE);
  watchdog('Gofast Search', 'Full Reindex cancelled.');  
  
  $message = t('Full Reindexing has been cancelled.', [], ['context' => 'gofast:gofast_search']);
  
  if (drupal_is_cli()) {
    // return message for drush. 
    return $message;
  }
  drupal_set_message($message);
  ctools_include('ajax');
  $commands = gofast_ajaxification_get_toast_messages();
  $commands[] = ajax_command_html('#ctools-add-js', "<script type='text/javascript'>
    Gofast.loadSettingsTab('edit-indexing');
    history.pushState({},'','/admin/config/gofast/global#search-index');
  </script>");
  print ajax_render($commands);
  exit;
}

/**
 * Mark full reindexing as finished. Record indexing time info and disable it. 
 */
function gofast_search_finish_full_reindex() {
  $start = variable_get('gofast_full_reindex', 'n/a');
  
  $info = [
    'start' => $start,
    'end' => REQUEST_TIME
  ];
  
  variable_set('gofast_full_reindex_last', $info);
  variable_set('gofast_full_reindex', FALSE);
  
  $duration = is_int($start) ? REQUEST_TIME - $start : 'n/a';
  $message = t('Full Reindex is finished (duration: !d).', ['!d' => $duration], ['context' => 'gofast:gofast_search']);
  drupal_set_message($message);

  watchdog('Gofast Search', 'Full Reindex is finished (duration: !d).', ['!d' => $duration]);
}