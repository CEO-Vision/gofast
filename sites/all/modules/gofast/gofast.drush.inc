<?php

/**
 * Implements hook_drush_help().
 */
function gofast_drush_help($command) {
  switch ($command) {
    case 'drush:post-install':
      return dt('Runs Drupal post-installation script from GoFast modules.') . "\n" .
        dt('Note: Gofast administrator (adm) MUST EXISTS prior to run this command.');
      
    case 'drush:create-adm':
      return dt('Creates Gofast administrator (adm).');
      
    case 'drush:fix-tasks':
      return dt('Fix content of Kanban Tasks field "description".');
      
    case 'drush:riot-fix-memberships':
      return dt('Resync user memberships in all rooms according to the corresponding space (OG) memberships.');

    case 'drush:riot-sync-avatars':
      return dt('Uploads Gofast user avatar images to matrix media store.') .  "\n" .
             dt('Outputs the mx_content_id of the file that contains user<->img associations.');
  }
}

/**
 * Implements hook_drush_command().
 */
function gofast_drush_command() {
  $items = array();

  $items['post-install'] = array(
    'description' => dt('Runs Drupal post-installation script from GoFast modules.'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  $items['create-adm'] = array(
    'description' => dt('Creates Gofast administrator (adm).'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_create_adm',
    'arguments' => array (
      'name' => 'the value of the name',
      'password' => 'the value of the password',
    ),
  );

  $items['flush-advagg'] = array(
    'description' => dt('Flush and recreate all advagg files (js and css)'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

   $items['import-translations'] = array(
    'description' => dt('Import translations from .po stored into the source code'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL
  );

  $items['full-reindex'] = array(
    'description' => dt('Smart full reindex all contents.'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_full_reindex',
    'arguments' => array (
      'action' => 'The action to do ( start , cancel - default to start ) ',
    ),
    'options' => [
      'delete' => 'Delete the whole index and indexing table, and optionally '
      . 'the variables storing the index exclusion-list. Ignored if argument is'
      . 'different than "start". Values can be "index" or "all". Defaults to '
      . 'FALSE meaning no deletion, or to "index" if the option is passed with '
      . 'no value.'
    ]
  );
    
  $items['fix-tasks'] = array(
    'description' => dt('Fix Kanban Tasks field "description".'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_fix_tasks'
  );

  $items['riot-fix-memberships'] = array(
    'description' => dt('Resync user memberships in all riot rooms according to the corresponding space (OG) memberships.'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_riot_fix_memberships'
  );
  
  $items['riot-sync-avatars'] = array(
    'description' => dt('Uploads Gofast user avatar images to matrix media store.'),
    'bootsrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'callback' => 'drush_gofast_riot_sync_avatars'
  );  
  

  return $items;
}

function drush_gofast_full_reindex($action = 'start') {
  module_load_include('inc', 'gofast_search', 'gofast_search.admin');
  usurp(1);
  
  if (!in_array($action, ['start', 'cancel'], TRUE)) {
    $e = "Invalid argument : `{$action}` Valid arguments are : [ start, cancel ], default to `start`.";
    throw new InvalidArgumentException($e);
  }
  
  if ($delete = drush_get_option('delete', FALSE)) {
    $delete = $delete === TRUE ? 'index' : $delete;
    if ($action !== 'start') {
      drush_log('Ignoring option --delete.', 'success');
    }
    else {
      switch ($delete) {
        case 'all':
          drush_log($delete, 'success');
          // Clear the list of excluded node from index/tika.
          variable_del('gofast_mail_report_scheduled');
          variable_del('gofast_search_tika_is_working');
          variable_del('gofast_search_tika_node_exclude');
          variable_del('gofast_search_index_node_exclude');

          drush_log('Index exclusion list variables were deleted.', 'success');

          // no break intended
        case 'index':
          module_load_include('inc', 'apachesolr', 'apachesolr.index');
          if (apachesolr_index_delete_index(GOFAST_SEARCH_ENV_ID)) {
            drush_log('The index has been deleted.', 'success');
          }
          else {
            drush_log('An error occured while trying to delete the index.', 'error');
            return;
          }
          break;

        default:
          $e = "Invalid option : `{$delete}` Valid --delete options : [ index, all ], default to `index`.";
          throw new InvalidArgumentException($e);
      }
    }
  }
    
  switch ($action) {
    case 'cancel':
      $msg = gofast_search_cancel_full_reindex();
      break;
      
    case 'start':
      if ($delete) {
        // Module apachesolr has already marked entities for reindexing. 
        // We just need to enable full reindexing mode.
        variable_set('gofast_full_reindex', REQUEST_TIME);
        watchdog('Gofast Search', 'Starting Full Reindex');
        $msg = 'Full reindexing has started.';
      }
      elseif (variable_get('gofast_full_reindex', FALSE) === FALSE) {
        $msg = gofast_search_start_full_reindex();
      }
      else {
        $msg = 'Full reindexing already running.';
      }
  }
  
  if ($msg) {
    drush_log($msg, 'success');
  }
}


function drush_gofast_import_translations(){
set_time_limit(0);

//FR
//default po
$file = new stdClass();
$file->filename = "fr_default.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_default.po";

$langcode = "fr";
$mode = 0;
$group = "default";

_locale_import_po($file, $langcode, $mode, $group);

//taxonomy po
$file = new stdClass();
$file->filename = "fr_taxonomy.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_taxonomy.po";

$langcode = "fr";
$mode = 0;
$group = "taxonomy";

_locale_import_po($file, $langcode, $mode, $group);

//menu po
$file = new stdClass();
$file->filename = "fr_menu.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_menu.po";

$langcode = "fr";
$mode = 0;
$group = "menu";

_locale_import_po($file, $langcode, $mode, $group);


//current search po
$file = new stdClass();
$file->filename = "fr_cs.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_cs.po";

$langcode = "fr";
$mode = 0;
$group = "current_search";

_locale_import_po($file, $langcode, $mode, $group);

//facetapi po
$file = new stdClass();
$file->filename = "fr_facetapi.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_facetapi.po";

$langcode = "fr";
$mode = 0;
$group = "facetapi";

_locale_import_po($file, $langcode, $mode, $group);

//nodetype po
$file = new stdClass();
$file->filename = "fr_nt.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/fr_nt.po";

$langcode = "fr";
$mode = 0;
$group = "node";

_locale_import_po($file, $langcode, $mode, $group);


//NL
//default po
$file = new stdClass();
$file->filename = "nl_default.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_default.po";

$langcode = "nl";
$mode = 0;
$group = "default";

_locale_import_po($file, $langcode, $mode, $group);

//taxonomy po
$file = new stdClass();
$file->filename = "nl_taxonomy.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_taxonomy.po";

$langcode = "nl";
$mode = 0;
$group = "taxonomy";

_locale_import_po($file, $langcode, $mode, $group);

//menu po
$file = new stdClass();
$file->filename = "nl_menu.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_menu.po";

$langcode = "nl";
$mode = 0;
$group = "menu";

_locale_import_po($file, $langcode, $mode, $group);


//current search po
$file = new stdClass();
$file->filename = "nl_cs.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_cs.po";

$langcode = "nl";
$mode = 0;
$group = "current_search";

_locale_import_po($file, $langcode, $mode, $group);

//facetapi po
$file = new stdClass();
$file->filename = "nl_facetapi.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_facetapi.po";

$langcode = "nl";
$mode = 0;
$group = "facetapi";

_locale_import_po($file, $langcode, $mode, $group);


//nodetype po
$file = new stdClass();
$file->filename = "nl_nt.po";
$file->uri = "/var/www/d7/sites/all/modules/gofast/po/nl_nt.po";

$langcode = "nl";
$mode = 0;
$group = "node";

_locale_import_po($file, $langcode, $mode, $group);
}

function drush_gofast_flush_advagg(){
    module_load_include('inc', 'advagg', 'advagg.admin');

    /**
    * Clear out all advagg cache bins and clear out all advagg aggregated files.
    */
    advagg_admin_clear_all_files_button();


    advagg_admin_increment_global_counter();
    advagg_admin_reset_mtime();
}

function drush_gofast_post_install() {
  global $user;

  // Override session for admin op.
  drupal_save_session(FALSE);
  $user = user_load(1);
  $modules = module_implements('post_install');
  if(!empty(module_implements('post_install_alter'))){
    $modules = module_invoke_all("post_install_alter", $modules);
  }

  foreach ($modules as $module) {
    if (strpos($module, 'gofast') === 0) {
      $function = $module . '_post_install';
      $ret = $function();
      foreach ((array) $ret as $log) {
        if (isset($log['message'])) {
          drush_log($log['message'], isset($log['status']) ? $log['status'] : 'notice');
        }
      }
    }
  }
}

function drush_gofast_create_adm($name, $password) {
  global $user;

  // Override session for admin op.
  drupal_save_session(FALSE);
  $user = user_load(1);

  $account = gofast_user_adm_create($name, $password);
  if ($account === FALSE) {
    drush_log('Gofast user creation failed.', 'error');
  }
  else {
    drush_log("Gofast user '{$account->name}' has been created successfully.", 'ok');
  }
}

/**
 * drush:fix-task callback
 * 
 * Fix the content of Kanban Tasks' field "description".
 */
function drush_gofast_fix_tasks() {
  usurp(1);
  
  $EFQuery = new EntityFieldQuery();
  $EFQuery->entityCondition('entity_type', 'node')
          ->entityCondition('bundle', 'task');
  
  $result = $EFQuery->execute();

  if (empty($result['node'])) {
    drush_log('There is no Task.', 'notice');
  }
  
  $nids = array_keys($result['node']);
  $nodes = entity_load('node', $nids);

  foreach ($nodes as $nid => $node) {
    if ($node->created == $node->changed)
      // The fix neeeds to be applied on nodes that have been updated. Newly 
      // created ones are fine.
      continue;
    
    if (!isset($node->body[LANGUAGE_NONE][0]['value']))
      continue;
       
    $node->body[LANGUAGE_NONE][0]['value'] = urldecode($node->body[LANGUAGE_NONE][0]['value']);
    node_save($node);
    
    drush_log(dt('Node !nid fixed', ['!nid' => $nid]), 'ok');
  } 
}

/**
 * drush:riot-fix-memberships callback
 * 
 * Sync user memberships in all rooms according to OG memberships.
 */
function drush_gofast_riot_fix_memberships() {
  if (!module_exists('gofast_riot')) {
    drush_log(dt('Gofast Riot module not enabled'), 'notice');
    return;
  }
  
  // Operate as admin, won't work otherwise.
  usurp(1);

  $log = gofast_riot_fix_rooms_memberships(TRUE);
  
  foreach ($log as $nid => $info) {
    $added = implode(', ', $info['added']);
    $removed = implode(', ', $info['removed']);
    $msg = "{$nid} | {$info['space']}\n - invited: {$added}\n -  kicked: {$removed}\n";
    drush_log(dt($msg), 'ok');
  }
  
  drush_log(dt('User memberships in Riot rooms are now synced with user memberships in Gofast space.'), 'ok');
}

function drush_gofast_riot_sync_avatars () {
  if (!module_exists('gofast_riot')) {
    drush_log(dt('Gofast Riot module not enabled'), 'notice');
    return;
  }

  usurp(1);
  
  // Ensure we have a valid token (drush does not invoke hook_login).
  $edit = []; // passed by reference
  gofast_riot_user_login($edit, []);
  
  list ($mx_content_id, $log) = _gofast_riot_sync_user_avatar();
  
  foreach ($log as $key => $info) {
    $level = isset($info['errcode']) ? 'error' : 'ok';
    $msg = $key . "\n";
    foreach ($info as $prop => $value) {
      $msg .= " -> {$prop}: {$value}\n";
    }
    drush_log($msg, $level);
  }
  
  if (empty($mx_content_id)) {
    $status = 'error';
    $output = 'NULL';
  }
  else {
    $status = 'success';
    $output = $mx_content_id;
  }

  drush_log('mx_content_id: ' . $output . "\n", $status);
}