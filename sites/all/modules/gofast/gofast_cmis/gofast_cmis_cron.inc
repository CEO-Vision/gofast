<?php

/*
 * Instant replication
 */
define('GOFAST_CMIS_REPLICATING_MODE_INSTANT', 0);

/*
 * Cron replication
 */
define('GOFAST_CMIS_REPLICATING_MODE_CRON', 1);

/*
 * Max activity authorized to switch in cron replication mode
 */
define('GOFAST_CMIS_REPLICATING_MAX_ACTIVITY', 3);

/*
 * Max items in a replication cron
 */
define('GOFAST_CMIS_CRON_MAX_ITEM', 100);

/**
 * Wait for cron replication
 */
define ('GOFAST_CMIS_CRON_PROCESSING_WAIT', 0);

/*
 * The entry is currently being processed
 */
define ('GOFAST_CMIS_CRON_PROCESSING_PROCESS', 1);

/*
 * We will sync the Drupal and Alfresco nodes
 */
define('GOFAST_CMIS_CRON_OPERATION_SYNC', 'Sync');

/*
 * Restart soffice process
 */
define('GOFAST_CMIS_CRON_OPERATION_RESTART_SOFFICE', 'restart_soffice');


/*
 * This function send an alert mail to CEO-Vision support team
 * @param $reason
 *   The reason of the alert
 * @param fail
 *   Is this error resulting in a replication fail
 */
function gofast_cmis_send_alert_email($reason, $fail = FALSE, $nid = '', $noderef=''){
  if($fail == false){
    return;
  }
  //Prepare mail
  $criticity = $fail ? "failed" : "warn";
  $subject = "[GoFast Report] Replication " . $criticity . " (Drupal CMIS cron)";
  $title = "GoFast Report";
  $footer = "GoFast Report notification E-mail";
  
  $body = "Something went wrong in CMIS synchronization. Criticity: " . $criticity;
  $body .= "<br />Reason: " . $reason;
  $body .= "<div><table>";
  $body .= "<tr><td>Node reference</td><td>Node ID</td></tr>";
  $body .= "<tr><td>". $noderef ."</td><td>". $nid ."</td></tr>";
  $body .= "</table></div>";
  
  $recpt = array(array('recpt' => user_load('5')->mail, 'method' => 'to'));
  
  //Send mail
  gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $recpt);
}

/*
 * Process an item to be synchronized in Drupal
 */
function gofast_cmis_process_item($node_ref, $name, $person, $path, $gid, $author, $cron = FALSE){
  usurp(user_load_by_name($person)->uid);
  $_POST['prevent_automatic_multifilling'] = true;
  if(!$cron){
    /*----------------------------------------------
     * We try to get the Alfresco item
     * We perform a lot of operations to do that as we cannot continue
     * without this node. We give 7 seconds to allow Alfresco
     * to perform it's operations. Keep in mind that all these actions 
     * are done asynchronously, regarding the user waiting time
     * ---------------------------------------------
     */
    sleep(10);
  }
  gofast_cmis_write_log_info("Getting item " . $node_ref, FALSE);
  
  //Clear CMIS cache for this item as we need to get the very last version
  gofast_cmis_static_cache($node_ref, TRUE);
  gofast_cmis_static_cache(str_replace('workspace', 'archive', $node_ref), FALSE);
  
  //Get the Alfresco item
  $item = gofast_cmis_item_get($node_ref, TRUE);
  
  ## Get the right path and gid (GOFAST-5589)
  $parents = gofast_cmis_item_get_parent($node_ref, TRUE); 
  foreach($parents->objectList as $parent){
    $path = $parent->properties["cmis:path"];
  }
  $gid = gofast_cmis_get_spaceid_by_webdav_folder($path, null);
  if($gid == NULL){
      //If we can't retrieve a gid, it probably means there is no such folder
      gofast_cmis_write_log_info("Unable to find " . $path);
  }
  if(!og_user_access("node", $gid, "create alfresco_item content")){
      gofast_cmis_write_log_info("Forbidden write permission to " . $path);
  }

  //Check either the item is deleted
  $item_is_deleted = FALSE;
  $url = "http://localhost:8080/alfresco/service/get/version/?reference=" . str_replace('workspace', 'archive', $node_ref);
  $username = "admin";
  $password = gofast_get_admin_pwd();

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
  curl_setopt($ch, CURLOPT_URL, $url);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = trim($buf);
  $item_delete = json_decode($result);
    
  if(isset($item_delete[0]->nodeRef)){ //Found a deleted node
    $item_is_deleted = TRUE;
  }
  
  if(!isset($item->properties) && $item_is_deleted == FALSE){ //Fail to get the item
    if(variable_get('gofast_cmis_failed_' . $node_ref, 0)){
      $reason = "Cannot retrieve the alfresco node a second time, we will stop to try to synchronize this item !";
      if (module_exists('gofast_community')){
          gofast_cmis_send_alert_email($reason, TRUE, $nid, $node_ref);
      }
      
      variable_del('gofast_cmis_failed_' . $node_ref);
      usurp(1);
      return;
    }
    else{
      $reason = "Cannot retrieve the alfresco node, we will retry in the next replication cron";
      if (module_exists('gofast_community')){
          gofast_cmis_send_alert_email($reason, FALSE, $nid, $node_ref);
      }
      //Change item processing state to 0
      db_update('alfresco_replication')
              ->fields(array('state' => 0, 'runsince' => time()))
              ->condition('noderef', $node_ref)
              ->execute();
      variable_set('gofast_cmis_failed_' . $node_ref, 1);
      usurp(1);
      return 2;
    }
  }
  /*----------------------------------------------
   * At this point, an alfresco item was found, contained in $item
   * ---------------------------------------------
   */
  gofast_cmis_write_log_info("Item is deleted: " . var_export($item_is_deleted, TRUE), FALSE);
  
  //We try to retrieve the node ID using the given reference
  gofast_cmis_write_log_info("Trying to get corresponding Drupal node", FALSE);
  $nid = gofast_cmis_node_get_by_reference($node_ref);
  
  if($nid == null && $item_is_deleted == FALSE){//The node doesn't exist or is about to be created
    gofast_cmis_write_log_info("Creating Drupal node", FALSE);
    gofast_cmis_process_item_create_node($item, $node_ref, $name, $person, $path, $gid, $author);
  }
  else if($nid == null && $item_is_deleted == TRUE){ //Node isn't created but Alfresco item is in the trash
    /*$reason = "Drupal was about to create a node programmatically but the Alfresco node is in the trash.";
    gofast_cmis_send_alert_email($reason, TRUE, "none", $node_ref);*/
  }
  else if($nid != null && is_object($item)){ //Node is created and item was found, we update/delete the node
    $node = node_load($nid);
    if( $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] !== $node_ref){ //Node found but alfresco_reference mismatch, we create a new node
      gofast_cmis_write_log_info("Creating Drupal node", FALSE);
      gofast_cmis_process_item_create_node($item, $node_ref, $name, $person, $path, $gid, $author);      
    }else{  //We update/delete the node
      gofast_cmis_write_log_info("Updating Drupal node", FALSE);
      gofast_cmis_process_item_update_node($item, $nid, $person, $item_is_deleted);
    }
  }
  else if($nid != null && $item_is_deleted == TRUE){ //Node is created and item is deleted, we delete the node
    gofast_cmis_write_log_info("Deleting Drupal node", FALSE);
    gofast_cmis_process_item_update_node($item, $nid, $person, $item_is_deleted);
  }
  else{
    $reason = "Can't find anything to do with this node.";
      if (module_exists('gofast_community')){
        gofast_cmis_send_alert_email($reason, TRUE, $gid, $node_ref);
      }
  }
  usurp(1);
}

/*
 * Create node programmatically if needed
 */
function gofast_cmis_process_item_create_node($item, $node_ref, $name, $person, $path, $gid, $author){
  $node = NULL;
  $status = 1;
  $name = $item->properties['cmis:name'];
  $size_brute = $item->properties["cmis:contentStreamLength"];
  $created = strtotime($item->properties['cmis:creationDate']);
  $size = $size_brute / 1024 / 1024;
  if ($size > 50) { //File is too large to autodetect language
      $language = LANGUAGE_NONE;
  }else{
      $language = gofast_cmis_item_detect_document_language($node_ref, user_load_by_name($person));
  }
  
  $private = 0;

  if (variable_get("cmis_creating_" . $node_ref, "false") === "true") {
    watchdog("CRON NODE CREATE", "Le noeud " . $node_ref . " est en cours de création.");
    return;
  }

    watchdog("CRON NODE UPDATE", "Creating node.");
    variable_set("cmis_creating_" . $node_ref, "true");
    
    gofast_cmis_write_log_info("Creating node programmatically", FALSE);
    $node = gofast_cmis_create_node_programmatically($node_ref, $person, $name, $status, $language, $private, $gid, $path, $author, $created);
    if($node == null || $node == false){
      $reason = "The programmatical node creation has failed";
      if (module_exists('gofast_community')){
          gofast_cmis_send_alert_email($reason, TRUE, "none", $node_ref);
      }
    }
    
  //Update immediatly the node to check if modification happened during the replication
  gofast_cmis_process_item_update_node($item, $node->nid, NULL, FALSE);
}

/*
 * Synchronize existing alfresco node with existing Drupal node
 */
function gofast_cmis_process_item_update_node($item, $nid, $person, $is_deleted){
  $node = node_load($nid);
  $document_update = TRUE; //Will be set to false if it's not a document update (version)

  //Save the node technically if the alfresco modification date is 12h in the past or more
  $alfresco_date = strtotime($item->properties['cmis:lastModificationDate']);
  
  $outdated_event = $alfresco_date < (time()-43200) ? true : false;
  
  //If the item is deleted, replicate it to the Drupal node
  if($is_deleted){
    gofast_cmis_write_log_info("Deleting Drupal node as Alfresco node is deleted", FALSE);
    $_GET['nid'] = $nid;
    cache_clear_all("field:node:$nid", 'cache_field');
    $node = node_load($nid, null, true);
    if($node->status != 0){
        gofast_ajax_node_unpublish(NULL, NULL, FALSE);
    }
  }
  else{
    //The item isn't deleted and needs to be updated
    $item_id = $item->properties['alfcmis:nodeRef'];

    /*
     * ________Location/Space update________
     */
    //Retrieve all spaces of the alfresco node
    $parents = gofast_cmis_item_get_parent($item_id, TRUE); 
    foreach($parents->objectList as $parent){
      $paths[] = $parent->properties["cmis:path"];
    }
    $field = GOFAST_CMIS_LOCATIONS_FIELD;

    //Format new paths as they are in node to compare them
    foreach($paths as $path){
      $paths_diff[]['value'] = $path;
    }

    if(!empty(gofast_array_diff_recursive($node->field_emplacement[LANGUAGE_NONE], $paths_diff, FALSE))){ //Need to update locations
      gofast_cmis_write_log_info("Updating: locations", FALSE);
      //Prepare and send the request to gofast_xeditable
      $_POST['pk'] = $nid;
      $_POST['name'] = $field;
      $_POST['value'] = $paths;
      $_POST['non_xeditable'] = TRUE;
      if($outdated_event || gofast_check_emplacement_is_migration_update($node->field_emplacement[LANGUAGE_NONE], $paths_diff)){
        gofast_cmis_write_log_info("emplacement correspond to migration replication ".$item->properties['cmis:name'], FALSE);
        $_POST['technically_save'] = TRUE;
      }
      gofast_cmis_write_log_info("About to update locations", FALSE);
      gofast_update_node_field();
      gofast_cmis_write_log_info("Locations updated", FALSE);
      $document_update = FALSE;
    }

    /*
     * ________Title update________
     */
    $field = "title";
    if($node->title !== $item->properties['cmis:name']){ //Need to update title
      gofast_cmis_write_log_info("Updating: title", FALSE);
      //Prepare and send the request to gofast_xeditable
      $_POST['pk'] = $nid;
      $_POST['name'] = $field;
      $_POST['value'] = $item->properties['cmis:name'];
      $_POST['non_xeditable'] = TRUE;
      if($outdated_event || gofast_check_title_is_migration_update($node->title, $item->properties['cmis:name'])){
        gofast_cmis_write_log_info("title correspond to migration replication ".$item->properties['cmis:name'], FALSE);
        $_POST['technically_save'] = TRUE;
      }
      gofast_update_node_field();
      $document_update = FALSE;
    }

    /*
     * ________Document update________
     */
     //We check if the version has changed
     if($item->properties['cmis:versionLabel'] != $node->field_current_version[LANGUAGE_NONE][0]['value']){
       gofast_cmis_write_log_info("Updating: version", FALSE);
       $node = node_load($node->nid, NULL, TRUE);
       if(gofast_check_version_is_migration_update($node->field_current_version[LANGUAGE_NONE][0]['value']) || $outdated_event){
           gofast_cmis_write_log_info("version correspond to migration replication ".$item->properties['cmis:name'], FALSE);
            $node->field_current_version[LANGUAGE_NONE][0]['value'] = $item->properties['cmis:versionLabel'];
            $node = gofast_prepare_node_save_technically($node); 
            $ruid = $node->revision_uid;
            node_save($node);
            db_update('node_revision')
              ->fields(array('uid' => $ruid))
              ->condition('nid', $node->nid)
              ->execute();
       }else{    
            $node->field_current_version[LANGUAGE_NONE][0]['value'] = $item->properties['cmis:versionLabel'];
            node_save($node);
       }
       $document_update = FALSE;
     }
     
      if($document_update){
        gofast_cmis_write_log_info("No update needed, nothing to do (so I won't do anything).", FALSE);
      }
  }
}
/*
 * Return true if it's a migration update ( so it's a technically update)
 */
function gofast_check_title_is_migration_update($old_title, $new_title){
    $file_info_old = pathinfo($old_title);
    $old_extension = isset($file_info_old['extension']) ? $file_info_old['extension'] : '';
    $file_info_new = pathinfo($new_title);
    $new_extension = isset($file_info_new['extension']) ? $file_info_new['extension'] : '';
    
    if(($old_extension == "" || strlen($old_extension) > 4 || is_numeric($old_extension)) && $new_extension !== ""){
        return true;
    }else{
        return false;
    }
}

/*
 * Return true if it's a migration update ( so it's a technically update)
 */
function gofast_check_emplacement_is_migration_update($old_emplacement, $new_emplacement){
    //we check only the first location.
    $first_old_location = $old_emplacement[0]["value"];  
    $first_old_location_array = explode("/", $first_old_location);

    if($first_old_location_array[3][0] == "_"){
        return false;
    }else{
        return true;
    }
}

function gofast_check_version_is_migration_update($old_version){
    if($old_version === NULL){
        return true;
    }else{
        return false;
    }
}

/*
 * Process cron replication
 */
function gofast_cmis_process_cron(){
  
  //We check if items seems to be blocked. In this case, we queue again these items
  $query = db_select('alfresco_replication', 'ar')
          ->fields('ar')
          ->condition('state', 1)
          ->condition('runsince', time()-120, '<')
          ->execute()
          ->fetchAll();
  foreach($query as $blockedItem){
    $reason = "This item was blocked in the replication cron. We queue it to the next cron.";
    //gofast_cmis_send_alert_email($reason, FALSE, NULL, $blockedItem->noderef);
    
    db_update('alfresco_replication')
              ->fields(array('state' => 0, 'runsince' => time()))
              ->condition('aid', $blockedItem->aid)
              ->execute();
  }
  
  gofast_cmis_write_log_info("CRON: Querying in the base");
  $query = db_select('alfresco_replication', 'ar')
          ->fields('ar')
          ->condition('state', 0)
          ->range(0, GOFAST_CMIS_CRON_MAX_ITEM)
          ->execute()
          ->fetchAll();
  if(count($query) !== 0){
    gofast_cmis_write_log_info("CRON: Will now process " . count($query) . "items");
  
    /*----------------------------------------------
       * We try to get the Alfresco item
       * We perform a lot of operations to do that as we cannot continue
       * without this node. We give 7 seconds to allow Alfresco
       * to perform it's operations. Keep in mind that all these actions 
       * are done asynchronously, regarding the user waiting time
    * ---------------------------------------------
    */
    gofast_cmis_write_log_info("CRON: Waiting 7 seconds to start");
    sleep(7);
  }
  
  foreach($query as $item){
    //Change item processing state to 1
    db_update('alfresco_replication')
              ->fields(array('state' => 1, 'runsince' => time()))
              ->condition('aid', $item->aid)
              ->execute();
    
    gofast_cmis_write_log_info("CRON: Processing " . $item->noderef);
    gofast_cmis_process_item($item->noderef, $item->name, $item->person, $item->path, $item->gid, $item->author, TRUE);
    
    //Delete item in database
    gofast_cmis_write_log_info("CRON: End of replication for " . $item->noderef);
    db_delete('alfresco_replication')
              ->condition('aid', $item->aid)
              ->execute();
  }
}
