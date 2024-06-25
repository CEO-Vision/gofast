<?php

/*
 * API used to format 'message' datas
 */

/**
 * Split a node into an array of params
 *
 * @param $node
 *  Node to split
 *
 * @return array()
 *  An array that contains the node's params
 */
function gofast_message_ext_split_node($node){

  //_____________________________Checking if each field exists. Assign NULL if it does not._________________________________

  if(isset($node->nid)){ $nid = $node->nid; }
  else{ $nid = NULL; }

  if(isset($node->uid)){ $uid = $node->uid; }
  else{ $uid = NULL; }

  if(isset($node->status)){ $status = $node->status; }
  else{ $status = NULL; }

  if(isset($node->body['und']['0']['summary'])){ $summary = $node->body['und']['0']['summary']; }
  else{ $summary = NULL; }

  if(isset($node->field_criticity['und']['0']['tid'])){  $criticity = $node->field_criticity['und']['0']['tid']; }
  else{  $criticity = NULL; }

  if(isset($node->field_date['und']['0']['value'])){ $deadline = $node->field_date['und']['0']['value']; }
  else{ $deadline = NULL; }

  if(isset($node->language)){ $lang = $node->language; }
  else{ $lang = NULL; }

  if(isset($node->revision_uid)){ $ruid = $node->revision_uid; }
  else{ $ruid = NULL; }

  if(isset($node->changed)){ $changed = $node->changed; }
  else{ $changed = NULL; }

  if(isset($node->title)){ $title = $node->title; }
  else{ $title = NULL; }

  if(isset($node->body['und']['0']['value'])){ $body = $node->body['und']['0']['value']; }
  else{ $body = NULL; }

  if(isset($node->created)){ $created = $node->created; }
  else{ $created = NULL; }

  if(isset($node->type)){ $type = $node->type; }
  else{ $type = NULL; }

  if(isset($node->field_category['und']['0']['tid'])){ $category = $node->field_category['und']['0']['tid']; }
  else{ $category = NULL; }

  if(isset($node->field_state['und']['0']['tid'])){ $state = $node->field_state['und']['0']['tid']; }
  else{ $state = NULL; }

  if(isset($node->field_target_link['und'])){ $target_array = $node->field_target_link['und']; }
  else{ $target_array = NULL; }

  if(isset($node->field_emplacement['und'])){ $location_array = $node->field_emplacement['und']; }
  else{ $location_array = NULL; }

  if(isset($node->field_external_page_url['und'])){ $URL_array = $node->field_external_page_url['und']; }
  else{ $URL_array = NULL; }

  if(isset($node->og_group_content_ref['und'])){ $group_array = $node->og_group_content_ref['und']; }
  else{ $group_array = NULL; }

  if(isset($node->field_tags['und'])){ $tags_array = $node->field_tags['und']; }
  else{ $tags_array = NULL; }

  if(isset($node->field_document_author['und'][0]['value'])){ $author = $node->field_document_author['und'][0]['value']; }
  else{ $author = NULL; }

  if(isset($node->field_document_reference['und'][0]['value'])){ $document_reference = $node->field_document_reference['und'][0]['value']; }
  else{ $document_reference = NULL; }

  if(isset($node->field_current_version['und'][0]['value'])){ $version = $node->field_current_version['und'][0]['value']; }
  else{ $version = NULL; }

  //_______________________________________________________________________________________________________________________


  $tags = gofast_message_ext_api_format_array($tags_array, 'tid');
  $group = gofast_message_ext_api_format_array($group_array, 'target_id');
  $location = gofast_message_ext_api_format_array($location_array, 'value');
  $URL = gofast_message_ext_api_format_array($URL_array, 'value');
  $target = gofast_message_ext_api_format_array($target_array, 'target_id');

  $document_reference_label = strtolower(t(variable_get("document_reference_label", "Document reference"), array(), array('context' => 'gofast')));

  $params = array(
      'nid'                     => $nid,      // Node ID
      'uid'                     => $uid,      // User/Author ID
      'status'                  => $status,   // (Un)Published state
      'groups'                  => $group,    // Groups IDs
      'title'                   => $title,    // Title
      'body'                    => $body,     // Body
      'created'                 => $created,  // Created timestamp
      'type'                    => $type,     // Type of the node
      'tags'                    => $tags,     // Terms
      'category'                => $category, // Category
      'state'                   => $state,    // State
      'locations'               => $location, // Locations links in alfresco
      'URLs'                    => $URL,      // Externals links
      'targets'                 => $target,   // Targets to other contents
      'criticity'               => $criticity,// Criticity
      'deadline'                => $deadline, // Deadline, formated date
      'lang'                    => $lang,     // Lang
      'summary'                 => $summary,  // Summary
      'ruid'                    => $ruid,     // Revision user ID
      'changed'                 => $changed,  // Changed timestamp
      'author'                  => $author,   // Custom field author
      $document_reference_label => $document_reference,   // Custom field author
      'version'                 => $version   // Version of the document
  );


    //Kanban specific
    if(in_array($node->type, gofast_kanban_get_node_types())){


            if(isset($node->field_person_in_charge['und']['0']['target_id'])){ $person_in_charge = $node->field_person_in_charge['und']['0']['target_id']; }
            else{ $person_in_charge = NULL; }

            if(isset($node->field_members['und']['0']['target_id'])){ $members =  gofast_message_ext_api_format_array($node->field_members['und'], 'target_id'); }
            else{ $members = NULL; }

            if(isset($node->field_labels['und']['0']['tid'])){ $labels =  gofast_message_ext_api_format_array($node->field_labels['und'], 'tid'); }
            else{ $labels = NULL; }

            if(isset($node->field_start_date['und']['0']['value'])){ $start_date = $node->field_start_date['und']['0']['value']; }
            else{ $start_date = NULL; }

            if(isset($node->field_finish_date['und']['0']['value'])){ $finish_date = $node->field_finish_date['und']['0']['value']; }
            else{ $finish_date = NULL; }

            if(isset($node->field_column_index['und']['0']['value'])){ $column_index = $node->field_column_index['und']['0']['value']; }
            else{ $column_index = NULL; }

            if(isset($node->field_task_column['und'])){ $task_column = gofast_message_ext_api_format_array($node->field_task_column['und'], 'tid'); }
            else{ $task_column = NULL; }

            if(isset($node->field_board_columns)){ $board_columns = $node->field_board_columns['und']; }
            else{ $board_columns = NULL; }

            //check checklist items
            if(isset($node->todolist[0])){ $todolist = $node->todolist[0]; }
            else{ $todolist = NULL; }


            $params['person_in_charge'] = $person_in_charge;
            $params['members'] = $members;
            $params['labels'] = $labels;
            $params['start_date'] = $start_date;
            $params['finish_date'] = $finish_date;
            $params['column_index'] = $column_index;
            $params['task_column'] = $task_column;
            $params['todolist'] = $todolist;
            $params['board_columns'] = $board_columns;

    }
  return $params;
}

/**
 * Split a comment into an array of params
 *
 * @param $comment
 *  Comment to split
 *
 * @return array()
 *  An array that contains the comment's params:
 *  0. Comment ID - 1. Author ID - 2. Node ref ID - 3. Title - 4.Body - 5. Created (timestamp
 *  6. Changed (timestamp)
 */
function gofast_message_ext_split_comment($comment){

  if(isset($comment->cid)){ $cid = $comment->cid; }
  if(isset($comment->uid)){ $uid = isset($_POST["override_audit_comment_uid"]) ? $_POST["override_audit_comment_uid"] : $comment->uid; }
  if(isset($comment->nid)){ $nid = $comment->nid; }
  if(isset($comment->subject)){ $title = $comment->subject; }
  if(isset($comment->comment_body['und']['0']['value'])){ $body = $comment->comment_body['und']['0']['value']; }
  if(isset($comment->created)){ $created = $comment->created; }
  if(isset($comment->changed)){ $changed = $comment->changed; }

  $params = array(
        'cid'     => $cid,      // Comment ID
        'uid'     => $uid,      // Author ID
        'nid'     => $nid,      // Associated node ID
        'title'   => $title,    // Title
        'body'    => $body,     // Body
        'created' => $created,  // Created timestamp
        'changed' => $changed   // Changed timestamp
  );

  return $params;
}

/**
 * Format an array as a string:
 * Exemple: (v1, v2, v3)
 *
 * @param $brut_array
 *  Array to format
 *
 * @param $key
 *  Potential key. If NULL, no key will be used
 *
 * @return string
 *  Formated string
 */
function gofast_message_ext_api_format_array($brut_array, $key){
  $i = 0;
  $formatted_string = "";
  if(isset($brut_array)){
    if($key != NULL){
      foreach ($brut_array as $brut_item) { //Formated as (t1, t2, t3...)
        if($i == 0){
          if(isset($brut_item[$key])){
            $formatted_string = $brut_item[$key];
          }
        }
        else{
          if(isset($brut_item[$key])){
            $formatted_string .= (", ".$brut_item[$key]);
          }
        }
        $i++;
      }
    }

    else{
      foreach ($brut_array as $brut_item) { //Formated as (t1, t2, t3...)
        if($i == 0){
          $formatted_string = $brut_item;
        }
        else{
          $formatted_string .= (", ".$brut_item);
        }
        $i++;
      }
    }
  }

  if($i == 0 || !isset($formatted_string)){ //Case: No array content found
    $formatted_string = "";
  }

  return $formatted_string;
}

function gofast_message_ext_api_share($node){
    $node_array[] = array();
    foreach($node as $k_from => $v_from){
        $node_array[$k_from]['value'] = $v_from;
    }
    return $node_array;
}

function gofast_message_ext_api_compare_todolist($k_from, $v_from, $to) {
  $compare_array = array();

  $from_items = array();
  if (!is_array($v_from)) {
    $v_from = (array) $v_from;
  }
  if(count((array) $v_from["items"]) > 0){
    foreach($v_from["items"] as $item){
      $from_items[$item->ciid] = $item;
    }
  }
  if (!empty($v_from) && isset($v_from) && !is_string($v_from)) { 
    $v_from["items"] = $from_items;
  }

  $to_items = array();
  if (!is_array($to[$k_from])) {
    $to[$k_from] = (array) $to[$k_from];
  }
  if(count((array) $to[$k_from]["items"]) > 0){
    foreach($to[$k_from]["items"] as $item){
      $to_items[$item->ciid] = $item;
    }
  }
  $to[$k_from]["items"] = $to_items;
  //check if there are count difference (to detect items add or remove)
  if(count((array)$to[$k_from]["items"]) > count((array) $v_from["items"])){
    //item add
    $items_added = array_diff_key($to[$k_from]["items"], $v_from["items"]);
    if(count($items_added) > 0){
      foreach($items_added as $item_added){
        $field_name = "todolist_".$item_added->ciid."_".$item_added->label."_";
        $field_name .= "label";
        $compare_array[$field_name]['from'] = "";
        $compare_array[$field_name]['to'] = $item_added->label;
      }
    }
  }
  
  if(count((array) $v_from["items"]) > count((array) $to[$k_from]["items"])){
    //item deleted
    $items_deleted = array_diff_key($v_from["items"], $to[$k_from]["items"]);
    if(count($items_deleted) > 0){
      foreach($items_deleted as $item_deleted){
        $field_name = "todolist_".$item_deleted->ciid."_".$item_deleted->label."_";
        $field_name .= "label";
        $compare_array[$field_name]['from'] = $item_deleted->label;
        $compare_array[$field_name]['to'] = "";
      }
    }
  }
  foreach($v_from["items"] as $key=>$item){
    //check label, deadline, uid and status
    //the fieldname must be on the following form : todolist_ciid_label_fieldname
    
    if($item->label !== $to[$k_from]["items"][$key]->label){
      $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
      $field_name .= "label";
      $compare_array[$field_name]['from'] = $item->label;
      $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->label;
      
    }
    if($item->deadline !== $to[$k_from]["items"][$key]->deadline){
      $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
      $field_name .= "deadline";
      $compare_array[$field_name]['from'] = $item->deadline;
      $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->deadline;
      
    }
    if($item->uid !== $to[$k_from]["items"][$key]->uid){
      $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
      $field_name .= "assignee";
      $compare_array[$field_name]['from'] = $item->uid;
      $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->uid;
      
    }
    if($item->status !== $to[$k_from]["items"][$key]->status){
      $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
      $field_name .= "status";
      $compare_array[$field_name]['from'] = $item->status;
      $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->status;
      
      //if a task status has changed, add a new line into the array, containing the global status
      if (isset($to[$k_from]["nb_items_completed"])) {
        $compare_array["todolist_Global Progression"]['from'] = $v_from["nb_items_completed"] ." / ".$v_from["nb_items"];
        $compare_array["todolist_Global Progression"]['to'] = $to[$k_from]["nb_items_completed"]." / ".$to[$k_from]["nb_items"];
      }
    }
  }
  return $compare_array;
}


/**
 * Compare 2 arrays with same structure and return differences in 1 array
 *
 * @param $from
 *  Source array
 *
 * @param $to
 *  New array
 *
 * @return array
 */

function gofast_message_ext_api_compare($from, $to){
  $compare_array[] = array();
  foreach($from as $k_from => $v_from){
    $isSame = $v_from == $to[$k_from]; //Same values

    //Bugfix GOFAST-2970 : Sometimes, the version 1.0 seems to be removed.
    if($k_from == 'version'){
      if($v_from == "1.0" && $to[$k_from] == NULL){
        $isSame = TRUE;
      }
    }
    if($k_from == 'todolist'){
      $compare_array = array_merge($compare_array, gofast_message_ext_api_compare_todolist($k_from, $v_from, $to));

    } elseif($k_from == "board_columns"){
      // board columns may be null when node is a task, but the key may exist anyway like when called from module in
      // entity pre-save hook, because gofast_message_ext_split_node sets the key in all cases. The value is null when
      // there is no data to set, e.g. for a task.
      $board_columns_from = array_map(
        fn ($item) => $item["tid"],
        $v_from ?? [],
      );
      $board_columns_to = array_map(
        fn ($item) => $item["tid"],
        $to[$k_from] ?? [],
      );
      if(count($board_columns_from) > count($board_columns_to)){ 
        // Column removed
        $removed_column = reset(array_diff($board_columns_from, $board_columns_to));
        $term = taxonomy_term_load($removed_column);
        $compare_array[$k_from]["from"] = $term->name;
        $compare_array[$k_from]["to"] = "";
      } else if(count($board_columns_from) < count($board_columns_to)){
        // New column added
        $added_column = reset(array_diff($board_columns_to, $board_columns_from));  
        $term = taxonomy_term_load($added_column);
        $compare_array[$k_from]["from"] = "";
        $compare_array[$k_from]["to"] = $term->name;
      } else {
        // In the case we are renaming a default column, make an update event from the previous and old term
        $old_tid = reset(array_diff($board_columns_from, $board_columns_to));
        $new_tid = reset(array_diff($board_columns_to, $board_columns_from));
        $old_term = taxonomy_term_load($old_tid);
        $new_term = taxonomy_term_load($new_tid);
        $compare_array[$k_from]["from"] = $old_term->name;
        $compare_array[$k_from]["to"] = $new_term->name;
      }
      
    } 
    else{
      if($isSame){
        $compare_array[$k_from]['value'] = $v_from;
      }
      else{
        if($k_from == 'version'){ //New version case
          if($from['version'] == NULL){
            $compare_array[$k_from]['value'] = $v_from;
          }
          else{
            $compare_array[$k_from]['from'] = $v_from;
            $compare_array[$k_from]['to'] = $to[$k_from];
          }
        }
        else{
          $compare_array[$k_from]['from'] = $v_from;
          $compare_array[$k_from]['to'] = $to[$k_from];
        }
      }
    }
  }
  return $compare_array;
}

/**
 * @param $message_array
 *  Formated array by *_compare
 *
 * return array
 *  An array that contains edited fields (keys)
 */
function gofast_message_ext_api_get_updated_fields($message_array){
$edited_fields = array();

  foreach($message_array as $array_k => $array_v){
    if(count((array) $array_v) == 2 && $array_k != "changed" && $array_k != "ruid" && $array_k != 'created'){
        if( $array_v["from"] !== $array_v["to"]){
          $edited_fields[] = $array_k;
        }
      }
  }
  return $edited_fields;
}

function gofast_message_ext_api_field_target_id_get_mids_from_nid($nid){
    $list_field_target_id_value_final = array();
    $entity_ids = db_query('select entity_id,field_target_id_value from {field_data_field_target_id} where field_target_id_value= '.$nid.'')->fetchAllKeyed();
    $list_field_target_id_value = $entity_ids;
    if(count( $list_field_target_id_value) > 0){
         foreach($list_field_target_id_value as $mid=>$mynid){
               $list_field_target_id_value_final[] = $mid;
         }
    }
    $mids = $list_field_target_id_value_final;

    return $mids;
}

function gofast_message_ext_api_field_node_id_get_mids_from_nid($nid){
    $list_field_node_id_value_final = array();
    $entity_ids = db_query('select entity_id,field_node_id_value from {field_data_field_node_id} where field_node_id_value = '.$nid.'')->fetchAllKeyed();
    $list_field_node_id_value = $entity_ids;
    if(count( $list_field_node_id_value) > 0){
         foreach($list_field_node_id_value as $mid=>$mynid){
               $list_field_node_id_value_final[] = $mid;
         }
    }
    $mids = $list_field_node_id_value_final;

    return $mids;
}

/**
 * given en array of mids, return the last message value
 * @param $mids: an array of message entity ids
 * @return rhe message value formatted as an associative array
 */
function gofast_message_get_last_message($mids) {
  $message_data_json = db_select("field_data_field_message_log","m")
    ->fields("m", array("field_message_log_value"))
    ->condition("m.field_message_log_value", "INVALID", "<>")
    ->condition("entity_id", $mids, "IN")
    ->orderBy("m.entity_id", "DESC")
    ->execute()
    ->fetchCol()[0];
  if (isset($message_data_json)) {
    $message_data = json_decode($message_data_json, TRUE);
  } else {
    $message_data = array();
  }
  return $message_data;
}

/**
 * Get the last event on a node
 *
 * @param $nid
 *  Entity ID
 *
 * @return
 *  A formated string describing the last event of a node.
 *
 */
function gofast_message_ext_api_get_last_event2($nid, $enforced_timestamp = FALSE){
  $result = NULL;

  // Get last message about the node
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'message')->fieldCondition('field_target_id', 'value', $nid, '=');
  $query_exe = $query->execute();
  // Get last message about the comment in node
  $query_com = new EntityFieldQuery();
  $query_com->entityCondition('entity_type', 'message')->fieldCondition('field_node_id', 'value', $nid, '=');
  $query_com_exe = $query_com->execute();

  if(isset($query_exe['message']) || isset($query_com_exe['message'])){
    if(isset($query_exe['message'])){ //Set timestamp of last node event if exists
      $mids = array_keys($query_exe['message']);
      $message_data_node = gofast_message_get_last_message($mids);

      if(isset($message_data_node['changed']['value'])){ //Get node last event timestamp
        $node_timestamp = $message_data_node['changed']['value'];
      }
      else{
        $node_timestamp = $message_data_node['changed']['to'];
      }
    }
    else{ //No node event recorded
      $node_timestamp = 0;
    }

    if(isset($query_com_exe['message'])){ //Set timestamp of last comment in node event if exists
      $mids_com = array_keys($query_com_exe['message']);
      $message_data_com = gofast_message_get_last_message($mids_com);

      if(isset($message_data_com['changed']['value'])){ //Get comment last event timestamp
        $com_timestamp = $message_data_com['changed']['value'];
      }
      else{
        $com_timestamp = $message_data_com['changed']['to'];
      }
    }
    else{ //No node event recorded
      $com_timestamp = 0;
    }

    if($node_timestamp>$com_timestamp){ //Compare timestamps
      $message_data = $message_data_node;
    }
    else{
      $message_data = $message_data_com;
    }

    $event = $message_data['event']['value'];
    if(count((array) $message_data['changed']) == 2){
        $timestamp = $message_data['changed']['to'];
      }
      else{
        $timestamp = $message_data['changed']['value'];
    }

    //Get all the field modifications recorded by the most recent message
    $edited_fields_array = gofast_message_ext_api_get_updated_fields($message_data);
    foreach($edited_fields_array as $k=>$v){ //Translate
      $edited_fields_array[$k] = t($v, array(), array('context' => 'gofast:last_event'));
    }
    $edited_fields = implode(", ", $edited_fields_array);
    //Get all edited values
    $i = 0;
    foreach($edited_fields_array as $edited_item){
      $result[$i]['from'] = $message_data[$edited_item]['from'];
      $result[$i]['to'] = $message_data[$edited_item]['to'];
      $result[$i]['field'] = $edited_item;
      $i++;
    }

    if(isset($message_data_com['version']['to'])){ //Try to catch a new version
      $version = $message_data_com['version']['to'];
    }

    //*********Trying to load the user that relates the most to the event***********
    $user_loaded = FALSE;
    if(isset($message_data['ruid']['value'])){
      if($message_data['ruid']['value'] != 0){
        $user_loaded = user_load($message_data['ruid']['value']);
        if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
      }
    }
    if(isset($message_data['ruid']['to']) && empty($user_loaded_displayname)){
      if($message_data['ruid']['to'] != 0){
        $user_loaded = user_load($message_data['ruid']['to']);
        if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
      }
    }
    if(isset($message_data['uid']['value']) && empty($user_loaded_displayname)){
      if($message_data['uid']['value'] != 0){
        $user_loaded = user_load($message_data['uid']['value']);
        if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
      }
    }
    if(isset($message_data['uid']['to']) && empty($user_loaded_displayname)){
      if($message_data['uid']['to'] != 0){
        $user_loaded = user_load($message_data['uid']['to']);
         if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
      }
    }
    if(empty($user_loaded_displayname)){
       if(gofast_user_view_access(user_load(1)) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
    }
    $user_name = $user_loaded_displayname;
    //********************************************************************************

    $enforced = FALSE;
    if ($enforced_timestamp && (abs($enforced_timestamp - $timestamp) > 300)) {
      $enforced = TRUE;
      $timestamp = $enforced_timestamp;
    }

    if($timestamp < (time()-86400)){
      $date = format_date($timestamp, 'long');
    }
    else{
      $relative_timestamp = (time()-$timestamp);
      $hours = floor($relative_timestamp / 3600);
      $minutes = floor(($relative_timestamp / 60) % 60);
      if($hours == 0){
        $date = t("@min min ago", array('@min' => $minutes));
      }
      else{
        $date = t("@hour hour(s) and @min min ago", array('@hour' => $hours, '@min' => $minutes));
      }
    }

    if ($enforced) {
      $result['message'] = t("updated @date.", array('@date' => $date));
      $result['event_last_modifier'] = $user_loaded;
      return $result;
    }

    switch($event){
      case 'NCON':
        $result['message'] = "<span class='font-weight-bolder text-primary'>".t("New content. ", array(), array('context' => 'gofast'))."</span>".t("Created by @user on @date.", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        $result['event'] = $event;
        break;
      case 'ECON':
        $result['event'] = $event;
        $result['message'] = t("@user updated @edited_fields @date.", array('@user' => $user_name, '@edited_fields' => $edited_fields, '@date' => $date));
        if(strcmp($edited_fields, "") == 0){
          $result['message'] = t("@user updated this content @date.", array('@user' => $user_name, '@date' => $date));
        }
        break;
      case 'NCOM':
        $result['event'] = $event;
        $result['title'] = $message_data['title']['value'];
        $result['body'] = $message_data['body']['value'];
        $result['message'] = "<span class='font-weight-bolder text-primary'>".t("New comment. ", array(), array('contexy' => 'gofast'))."</span>".t(" added by @user on @date.", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        break;
      case 'ECOM':
        $result['event'] = $event;
        if(isset($message_data['title']['to'])){
          $result['title'] = $message_data['title']['to'];
        }
        else{
          $result['title'] = $message_data['title']['value'] ?? "";
        }
        if(isset($message_data['body']['to'])){
          $result['body'] = $message_data['body']['to'];
        }
        else{
          $result['body'] = $message_data['body']['value'] ?? "";
        }
        $result['message'] = t("@user updated a comment @date.", array('@user' => $user_name, '@date' => $date));
        break;
      case 'NREV':
        $result['event'] = $event;
        if(!isset($version)){
            $result['message'] = t("@user updated the document's version @date.", array('@user' => $user_name, '@date' => $date));
        }
        else{
            $result['message'] = t("@user updated the document's version to @version @date.", array('@user' => $user_name, '@version' => $version, '@date' => $date));
        }
        break;
      case 'linksharing':
        $array_dest = explode(";", $message_data['desti_uid']['value']);
        unset($array_dest[count($array_dest)-1]);
        $result['version'] = $message_data['version']['value'];
        $result['dest_uid'] = $message_data['desti_uid']['value'];
        $result['message'] = t("@user shared a document @date", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        $result['event'] = $event;
        $result['title'] = $message_data['title']['value'];
        $result['user_uid'] = $message_data['ruid']['value'];
        break;
    }
    $result['event_last_modifier'] = $user_loaded;
  }
  else{
    $result = NULL;
  }
  return $result;
}

/**
 * Get the last event on a node
 *
 * @param $nid
 *  Entity ID
 *
 * @return
 *  A formated string describing the last event of a node.
 *
 */
function gofast_message_ext_api_get_last_event($nid){
  $result = NULL;
  $query = new EntityFieldQuery();

  $query->entityCondition('entity_type', 'message')
          ->fieldCondition('field_target_id', 'value', $nid, '=');
  $query_exe = $query->execute(); //Get last message about the node

  $query_com = new EntityFieldQuery();

  $query_com->entityCondition('entity_type', 'message')
          ->fieldCondition('field_node_id', 'value', $nid, '=');
  $query_com_exe = $query_com->execute(); //Get last message about the comment in node

  if(isset($query_exe['message']) || isset($query_com_exe['message'])){

    if(isset($query_exe['message'])){ //Set timestamp of last node event if exists
      $mids = array_keys($query_exe['message']);
      $message_items = entity_load('message', $mids);
      $last_message = end($message_items);
      while($last_message->field_message_log['und']['0']['value'] === 'INVALID' && $last_message != FALSE){
        $last_message = prev($message_items);
      }
      $message_data_json = NULL;
      if(isset($last_message->field_message_log['und']['0']['value'])){
        $message_data_json = $last_message->field_message_log['und']['0']['value'];
      }
      $message_data_node = json_decode($message_data_json, TRUE);

      if(isset($message_data_node['changed']['value'])){ //Get node last event timestamp
        $node_timestamp = $message_data_node['changed']['value'];
      }
      else{
        $node_timestamp = $message_data_node['changed']['to'];
      }
    }
    else{ //No node event recorded
      $node_timestamp = 0;
    }

    if(isset($query_com_exe['message'])){ //Set timestamp of last comment in node event if exists
      $mids_com = array_keys($query_com_exe['message']);
      $message_items_com = entity_load('message', $mids_com);
      $last_message_com = end($message_items_com);
      while($last_message_com->field_message_log['und']['0']['value'] === 'INVALID' && $last_message_com != FALSE){
        $last_message_com = prev($message_items_com);
      }

      while(!gofast_message_ext_api_comment_is_valid($last_message_com->field_message_log['und']['0']['value']) && $last_message_com != FALSE){
        $last_message_com = prev($message_items_com);
      }

      $message_data_json_com = $last_message_com->field_message_log['und']['0']['value'];
      $message_data_com = json_decode($message_data_json_com, TRUE);

      if(isset($message_data_com['changed']['value'])){ //Get comment last event timestamp
        $com_timestamp = $message_data_com['changed']['value'];
      }
      else{
        $com_timestamp = $message_data_com['changed']['to'];
      }
    }
    else{ //No node event recorded
      $com_timestamp = 0;
    }

    if($node_timestamp>$com_timestamp){ //Compare timestamps
      $message_data = $message_data_node;
    }
    else{
      $message_data = $message_data_com;
        }

    $event = $message_data['event']['value'];
    if(count($message_data['changed']) == 2){
        $timestamp = $message_data['changed']['to'];
      }
      else{
        $timestamp = $message_data['changed']['value'];
    }

    //Get all the field modifications recorded by the most recent message
    $edited_fields_array = gofast_message_ext_api_get_updated_fields($message_data);
    foreach($edited_fields_array as $k=>$v){ //Translate
      $edited_fields_array[$k] = t($v, array(), array('context' => 'gofast:last_event'));
    }
    $edited_fields = implode(", ", $edited_fields_array);
    //Get all edited values
    $i = 0;
    foreach($edited_fields_array as $edited_item){
      $result[$i]['from'] = $message_data[$edited_item]['from'];
      $result[$i]['to'] = $message_data[$edited_item]['to'];
      $result[$i]['field'] = $edited_item;
      $i++;
    }

    if(isset($message_data_com['version']['to'])){ //Try to catch a new version
      $version = $message_data_com['version']['to'];
    }

    //*********Trying to load the user that relates the most to the event***********
    if(isset($message_data['ruid']['value'])){
      if($message_data['ruid']['value'] != 0){
        $user_loaded = user_load($message_data['ruid']['value'], TRUE);
      }
    }
    if(isset($message_data['ruid']['to']) && !isset($user_loaded)){
      if($message_data['ruid']['to'] != 0){
        $user_loaded = user_load($message_data['ruid']['to'], TRUE);
      }
    }
    if(isset($message_data['uid']['value']) && !isset($user_loaded)){
      if($message_data['uid']['value'] != 0){
        $user_loaded = user_load($message_data['uid']['value'], TRUE);
      }
    }
    if(isset($message_data['uid']['to']) && !isset($user_loaded)){
      if($message_data['uid']['to'] != 0){
        $user_loaded = user_load($message_data['uid']['to'], TRUE);
      }
    }
    if(!isset($user_loaded)){
      $user_loaded = user_load(1, TRUE);
    }
    $user_name = $user_loaded->ldap_user_givenname['und']['0']['value']." ".$user_loaded->ldap_user_sn['und']['0']['value'];
    //********************************************************************************

    if($timestamp < (time()-86400)){
      $date = format_date($timestamp, 'long');
    }
    else{
      $relative_timestamp = (time()-$timestamp);
      $hours = floor($relative_timestamp / 3600);
      $minutes = floor(($relative_timestamp / 60) % 60);
      if($hours == 0){
        $date = t("@min min ago", array('@min' => $minutes));
      }
      else{
        $date = t("@hour hour(s) and @min min ago", array('@hour' => $hours, '@min' => $minutes));
      }
    }
    switch($event){
      case 'NCON':
        $result['message'] = "<span style='color:red'>".t("New content. ", array(), array('context' => 'gofast'))."</span>".t("Created by @user on @date.", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        $result['event'] = $event;
        break;
      case 'ECON':
        $result['event'] = $event;
        $result['message'] = t("@user updated @edited_fields @date.", array('@user' => $user_name, '@edited_fields' => $edited_fields, '@date' => $date));
        if(strcmp($edited_fields, "") == 0){
          $result['message'] = t("@user updated this content @date.", array('@user' => $user_name, '@date' => $date));
        }
        break;
      case 'NCOM':
        $result['event'] = $event;
        $result['title'] = $message_data['title']['value'];
        $result['body'] = $message_data['body']['value'];
        $result['message'] = "<span style='color:red'>".t("New comment. ", array(), array('contexy' => 'gofast'))."</span>".t(" added by @user on @date.", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        break;
      case 'ECOM':
        $result['event'] = $event;
        if(isset($message_data['title']['to'])){
          $result['title'] = $message_data['title']['to'];
        }
        else{
          $result['title'] = $message_data['title']['value'];
        }
        if(isset($message_data['body']['to'])){
          $result['body'] = $message_data['body']['to'];
        }
        else{
          $result['body'] = $message_data['body']['value'];
        }
        $result['message'] = t("@user updated a comment @date.", array('@user' => $user_name, '@date' => $date));
        break;
      case 'NREV':
        $result['event'] = $event;
        if(!isset($version)){
            $result['message'] = t("@user updated the document's version @date.", array('@user' => $user_name, '@date' => $date));
        }
        else{
            $result['message'] = t("@user updated the document's version to @version @date.", array('@user' => $user_name, '@version' => $version, '@date' => $date));
        }
        break;
      case 'linksharing':
        $array_dest = explode(";", $message_data['dest']['value']);
        unset($array_dest[count($array_dest)-1]);
        $result['version'] = $message_data['version']['value'];
        $result['dest_uid'] = $message_data['desti_uid']['value'];
        $result['message'] = t("@user shared a document @date", array('@user' => $user_name, '@date' => $date), array('context' => 'gofast'));
        $result['event'] = $event;
        $result['title'] = $message_data['title']['value'];
        $result['user_uid'] = $message_data['ruid']['value'];
        break;
    }
  }
  else{
    $result = NULL;
  }
  return $result;
}

/*
 * Check if a comment is valid or not
 * Comment is invalid if it has been deleted or if it's private
 */
function gofast_message_ext_api_comment_is_valid($message){
  $message_data_com = is_array($message) ? $message : json_decode($message, TRUE);

    $cid = $message_data_com['cid']['value'];

    if(empty($cid)){
        return FALSE;
    }

    $comment_exists = count(db_query("select cid from comment where cid=:cid", array(":cid" => $cid))->fetchAll()) > 0;

    $comment_is_public = count(db_query("select field_comment_is_private_value from field_data_field_comment_is_private where entity_id=:cid AND field_comment_is_private_value=1", array(":cid" => $cid))->fetchAll()) == 0;

    if(!$comment_exists || !$comment_is_public){
        return FALSE;
    }

    return TRUE;
}

/**
 * Turn a string formated as IDterm1, IDterm2, IDterm3..
 * as term1, term2, term3...
 *
 * @param $term_ids
 *  Formated string as IDterm1, IDterm2, IDterm3..
 *
 * @return string
 *  Formated string as term1, term2, term3...
 */
function gofast_message_ext_api_get_term($term_ids){
  $array_terms = explode(",", $term_ids);
  $array_taxo = taxonomy_term_load_multiple($array_terms);
  $taxo_to_implode = array();
  foreach($array_taxo as $taxo_item){
    $taxo_to_implode[] = $taxo_item->name;
  }
  $return = implode(",", $taxo_to_implode);
  return $return;
}

/**
 * Turn a string formated as IDnode1, IDnode2, IDnode3..
 * as node1, node2, node3...
 *
 * @param $node_ids
 *  Formated string as IDnode1, IDnode2, IDnode3..
 *
 * @return string
 *  Formated string as node1, node2, node3...
 */
function gofast_message_ext_api_get_node_name($node_ids){
  $array_nids = explode(",", $node_ids);
  $nodes_to_implode = array();
  foreach($array_nids as $nid){
    $nodes_to_implode[] = gofast_get_node_title($nid);
  }
  $return = implode(",", $nodes_to_implode);
  return $return;
}

/**
 * Turn a string formated as IDuser1, IDuser2, IDuser3..
 * as user1, user2, user3...
 *
 * @param $users_id
 *  Formated string as IDuser1, IDuser2, IDuser3..
 *
 * @return string
 *  Formated string as user1, user2, user3...
 */
function gofast_message_ext_api_get_user_name($users_id){
  $array_uids = explode(",", $users_id);
  $users_to_implode = array();
  foreach($array_uids as $uid){
    if($uid != null){
      $users_to_implode[] = gofast_user_display_name($uid);
    }
  }
  $return = implode(",", $users_to_implode);
  return $return;
}

/**
 * @deprecated
 */
function gofast_message_ext_api_get_username($users_id){
  return gofast_message_ext_api_get_user_name($users_id);
}


function gofast_message_ext_api_render_event($event){
        $edit = NULL;
        global $user;
        $myformat = system_date_format_locale($user->language, "medium");
        $l = array('langcode' => $user->language, 'context' => 'gofast');
        $output = "";

        if(isset($event['0'])|| $event['message'] != 'ECON'){ //If precise edits was caught out
          foreach($event as $edit_key => $edition){
            if(is_array($edition) || ($edit_key == "title" && $edit === NULL )){
              switch($event['event']){
                case 'ECON':
                case 'NREV':
                case 'ETDL':
                  $info = gofast_message_ext_api_get_info_field($edition,$myformat,$l);
                  $from = $info['from'];
                  $to = $info['to'];
                  if(empty($from) && !empty($to)){ //Case: New
                    $is_todolist_field = gofast_kanban_is_todolist_field($edition['field']);
                    if($is_todolist_field){
                      $edition['field'] = gofast_kanban_get_readable_name_specific_fields($edition['field'], false);
                    }
                    // Title configuration for New Card
                    if ($edition['field']=='URLs'){
                      $edit_card .= '<span>'.t('External links', array(), array('context' => 'gofast')).'</span>';
                    }else{
                      $edit_card .= '<span>'.t(ucfirst(str_replace('_', ' ', $edition['field'])), array(), array('context' => 'gofast')).'</span>';
                    }
                    
                    if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                      $content_card = $to;
                    }
                    else{
                      $content_card .= '<p class="ml-1 m-0 " >' . t($to, array(), array('context' => 'gofast')) . '</p>';
                    }

                    $edit_content = theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('New'), 'content' => $content_card, 'child_content' => true]);
                    $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $edit_card, 'content' => $edit_content]);

                  } 
                  if (!empty($from) && empty($to) && $from != $to){ //Case: Removed
                    $is_todolist_field = gofast_kanban_is_todolist_field($edition['field']);
                    if($is_todolist_field){
                      $edition['field'] = gofast_kanban_get_readable_name_specific_fields($edition['field'], false);
                    }
                    // Title configuration for Remove Card
                    if ($edition['field']=='URLs'){
                      $title_card .= '<span>'.t('External links', array(), array('context' => 'gofast')).'</span>';
                    }else{
                      $title_card = '<span>' . t(ucfirst(str_replace('_', ' ', $edition['field'])), array(), array('context' => 'gofast')) . "</span>";
                    } 
                    if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                      $content_card = $from;
                    }else{
                      $content_card = '<p class="ml-1 m-0 " >' . t($from, array(), array('context' => 'gofast')) . '</p>';
                    }

                    $edit_content = theme('gofast_card_template', ['class' => 'bg-danger mb-2', 'title' => t('Removed'), 'content' => $content_card,'child_content' => true]);
                    if($edition["child"]){
                      $is_todolist_field_child = gofast_kanban_is_todolist_field($edition['child'][0]['field']);
                      if($is_todolist_field_child){
                        $edition['child'][0]['field'] = gofast_kanban_get_readable_name_specific_fields($edition['child'][0]['field'], true);
                      }
                      $edit_card_child = '<span>' . t("Progress indicator", array(), array('context' => 'gofast')) . "</span>";
                      $fraction = $edition["child"][0]["to"];
                      $attribut = gofast_message_ext_api_get_progress_percentage($fraction);
                      $edit_content .= '<div>'.$edit_card_child.' <div class="progress position-relative"><div class="progress-bar" style="width:'.$attribut.'%!important" role="progressbar" aria-valuenow="100" aria-valuemin="0" aria-valuemax="100">'.$attribut.'%</div></div></div>';
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $title_card, 'content' => $edit_content]);
                  }
                  if(!empty($from)  && !empty($to)){ //Case: Edition
                    $is_todolist_field = gofast_kanban_is_todolist_field($edition['field']);
                    if($is_todolist_field){
                      $edition['field'] = gofast_kanban_get_readable_name_specific_fields($edition['field'], false);
                    }
                    if(strpos($edition["field"], "Global") !== false){
                      $title_card = '<span>' . t(ucfirst(str_replace('_', ' ', $edition['field'])), array(), array('context' => 'gofast')) . "</span>";
                      $fraction = $to;
                      $attribut = gofast_message_ext_api_get_progress_percentage($fraction);
                      $edit_content .= '<div class="progress position-relative"><div class="progress-bar" style="width:'.$attribut.'%!important" role="progressbar" aria-valuenow="100" aria-valuemin="0" aria-valuemax="100">'.$attribut.'%</div></div>';
                    }else{
                    // Title configuration for Edition Card
                      $title_card = '<span>' . t(ucfirst(str_replace('_', ' ', $edition['field'])), array(), array('context' => 'gofast')) . "</span>";
                      if($edition['field'] =='ruid'){
                        $title_card = '<span>' . t("Revision identifier") . "</span>";
                      }else if ($edition['field']=='URLs'){
                        $title_card = '<span>' . t('External links', array(), array('context' => 'gofast')) . "</span>";
                      }
                      if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                        $content_card = $from;
                      }
                      else{
                        $content_card = '<p class="ml-1 m-0 " >' . t($from, array(), array('context' => 'gofast')) . '</p>';
                      }
                      $edit_content = theme('gofast_card_template', ['class' => 'bg-danger mb-2', 'title' => t('Old'), 'content' => $content_card, 'child_content' => true]);
                      $content_card = "";
                      if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                        $content_card .= $to;
                      }
                      else{
                        $content_card .= '<p class="ml-1 m-0 " >' . t($to, array(), array('context' => 'gofast')) . '</p>';
                      }
                      $edit_content .= theme('gofast_card_template', ['class' => 'bg-success mb-2', 'title' => t('New'), 'content' => $content_card, 'child_content' => true]);
                    }
                    if($edition["child"]){
                      $is_todolist_field_child = gofast_kanban_is_todolist_field($edition['child'][0]['field']);
                      if($is_todolist_field_child){
                        $edition['child'][0]['field'] = gofast_kanban_get_readable_name_specific_fields($edition['child'][0]['field'], true);
                      }
                      $edit_card_child = '<span>' . t("Progress indicator", array(), array('context' => 'gofast')) . "</span>";
                      $fraction = $edition["child"][0]["to"];
                      $attribut = gofast_message_ext_api_get_progress_percentage($fraction);
                      $edit_content .= '<div>'.$edit_card_child.' <div class="progress position-relative"><div class="progress-bar" style="width:'.$attribut.'%!important" role="progressbar" aria-valuenow="100" aria-valuemin="0" aria-valuemax="100">'.$attribut.'%</div></div></div>';
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $title_card, 'content' => $edit_content]);
                  }
                  break;
                case 'NCOM':
                  $title_card = t("New comment", array(), array('context' => 'gofast')) . ' - ' . $event['title'];
                  $content_card =strip_tags($event['body'], '<br><a><p><center><span><strong><s><em><h1><h2><h3><h4><u>');
                  $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader m-0', 'title' =>  $title_card, 'content' => $content_card]);
                  break;
                case 'ECOM':
                  $title_card = t("Edited comment", array(), array('context' => 'gofast')) . ' - ' . $event['title'];
                  $content_card = strip_tags($event['body'], '<br><a><p><center><span><strong><s><em><h1><h2><h3><h4><u>');
                  $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader m-0', 'title' =>  $title_card, 'content' => $content_card]);
                  break;
                case 'linksharing':
                  $content_card .= '<div class="d-flex flex-column justify-content-center align-items-center">';
                  $toValue = $edition["to"];
                  $recipients_infos = json_decode($toValue);
                  if ($recipients_infos !== null ) {
                    $content_card .= '<p>' . t('Sent to: ', array(), array('context' => 'gofast')) . '</p>';
                    foreach($recipients_infos[0] as $recipients_info) {
                        switch ($recipients_info->type) {
                          case "user":
                              $content_card .= gofast_message_ext_api_generate_content_card_user($recipients_info->value, "");
                              break;
                          case "userlist":
                              $userlist_name = node_load($recipients_info->value)->title;
                              $content_card .=  gofast_message_ext_api_generate_content_card($userlist_name, "");
                              break;
                          case "email":
                            $content_card .='<div class="d-flex flex-row align-items-center">'. '<i class="fa fa-envelope text-info mr-2"></i> <p class="m-0">' . $recipients_info->value. '</p></div>';
                              break;
                          default:
                        }
                    }
                  } else {
                     $content_card .= '<p>' . t("No recipient found", array(), array("context" => "gofast:gofast_audit")) . '</p>';
                  }
                  if($edition['version'] && $edition['version'] != '0' ){
                    $content_card .='<div class="d-flex flex-row align-items-center"> '.t('Shared document version: '). ' <code><strong>' .$edition['version'] . '</strong></code></div>' ;
                  }
                  $content_card .= '</div>';
                  $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' =>  t("Linksharing",array(),array('context' => 'gofast:gofast_audit_node')), 'content' => $content_card]);
                  break;
                case 'sharing_dl':
                  $content_card = '<div class="d-flex flex-column justify-content-center align-items-center">';
                  $userInfo = $edition["addr_ip"];
                  if ($userInfo) {
                      if (empty(user_load($userInfo))) {
                          $content_card .= '<div class="d-flex flex-row align-items-center justify-content-center"> <p class="m-0">' . t("IP of the downloader: ") . '</p> <code><strong>' . $userInfo . '</strong></code></div>';
                      } else {
                          $content_card .= theme('user_picture', ['account' => user_load($userInfo), 'popup' => TRUE, 'dimensions' => ['width' => '25px', 'height' => '25px']]) . gofast_message_ext_api_get_user_name($id_sharing);
                      }

                      if ($edition["version"]) {
                          $content_card .= '<div class="d-flex flex-row align-items-center"> <p class="m-0">' . t("Version:") . '</p> <code><strong>' . $edition["version"] . '</strong></code></div>';
                      }
                  }
                  $content_card .= '</div>';
                  $edit = theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Shared content download'), 'content' => $content_card]);
                  break;
                
                case 'user_blocked':
                    $uid_to_block = $edition['uid_to_block'];
                    $content_card = gofast_message_ext_api_generate_content_card_user($uid_to_block, "");
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('User blocked : '), 'content' => $content_card]);
                    break;
                case 'user_leave':
                    $uid_to_block = $edition['uid_to_block'];
                    $content_card =  theme('user_picture', array( 'account' => user_load($uid_to_block), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . gofast_message_ext_api_get_user_name($uid_to_block) . '</br>';
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('User leave : '), 'content' => $content_card]);
                    break;
                case 'user_unblocked':
                    $uid_to_block = $edition['uid_to_block'];
                    $content_card = gofast_message_ext_api_generate_content_card_user($uid_to_block, "");
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('User unblocked : '), 'content' => $content_card]);
                    break;
                case 'user_unstandby' :
                    $uid_to_unstandby = $edition['uid_to_unstandby'];
                    $content_card =  theme('user_picture', array( 'account' => user_load($uid_to_unstandby), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . gofast_message_ext_api_get_user_name($uid_to_unstandby) . '</br>';
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('User activated : '), 'content' => $content_card]);
                    break;       
                case 'delete_folder':
                    $path = $edition['path'];
                    $content_card = str_replace("/alfresco/webdav/","", rawurldecode($path));
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Deleted folder : '), 'content' => $content_card]);
                    break;
                case 'delete_node':
                    $nodesPath = $edition['node_path'];
                    if (!empty($nodesPath) && $nodesPath != [""]) {
                        foreach ($nodesPath as $Path) {
                    $content_card  = $Path ." </br>";
                        }
                    }else{
                      $content_card = t("No defined path");
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Deleted node location : '), 'content' => $content_card]);
                    break;
                case 'create_user':
                    $user_name = $edition['user_create'];
                    $content_card = gofast_message_ext_api_generate_content_card_user($user_name, $role);
                     $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('Created user : '), 'content' => $content_card]);
                    break;
                case 'delete_user':
                    $user_delete_name = $edition['user_delete_name'];
                    $content_card  =  theme('user_picture', array('popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))) . $user_delete_name . '</br>';
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Deleted user : '), 'content' => $content_card]);
                    break;
                case 'add_member':
                    if (isset($edition['user_name'])) {
                      $user_name = $edition['user_name'];
                      $role_name = gofast_og_get_user_roles($edition["nid"], $user_name);
                      $role = gofast_message_ext_api_get_role($role_name);
                      $titre_card = t('Added member : ');
                      $content_card = gofast_message_ext_api_generate_content_card_user($user_name, $role);
                    } else if (isset($edition['array_members'])) {
                      $user_name = $edition['array_members'];
                      $role_name = gofast_og_get_user_roles($edition["nid"], $user_name[0]);
                      $role = gofast_message_ext_api_get_role($role_name);
                      $titre_card = t('Added member : ');
                      $content_card =  gofast_message_ext_api_generate_content_card_group($user_name, $role);
                    } else {
                      $user_name = $edition['userlist_members'];
                      $role_name = gofast_userlist_og_get_userlist_roles("node", $edition["nid"], $edition["userlist_id"], FALSE, FALSE);
                      $role = gofast_message_ext_api_get_role($role_name);
                      $userlist_name = $edition['userlist_name'];
                      $titre_card = t('Added member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                      $content_card = (count($user_name) == 0) ? t('Empty userlist', array(), array('context' => 'gofast_audit')) : gofast_message_ext_api_generate_content_card($userlist_name, $role);
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => $titre_card, 'content' => $content_card]);
                    break;
                case 'workflow_add':
                    $content_card = $edition['worklow_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Created workflow name : '), 'content' => $content_card]);
                    break;
                case 'workflow_delete':
                    $content_card = $edition['worklow_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Deleted workflow name : '), 'content' => $content_card]);
                    break;
                case 'card_add':
                    $content_card = $edition['card_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Created card name : '), 'content' => $content_card]);
                    break;
                case 'card_delete':
                    $content_card = $edition['card_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' =>t('Deleted card name : '), 'content' => $content_card]);
                    break;
                case 'delete_member':
                    if (isset($edition['user_name'])) {
                      $user_name = $edition['user_name'];
                      $title_card = t('Deleted member : ');
                      $content_card = gofast_message_ext_api_generate_content_card_user($user_name, "");
                    } else if (isset($edition['array_members'])) {
                      $user_name = $edition['array_members'];
                      $title_card = t('Deleted member : ');
                      $content_card =  gofast_message_ext_api_generate_content_card_group($user_name, $role);
                    }else {
                      $user_name = $edition['userlist_members'];
                      $userlist_name = $edition['userlist_name'];
                      $title_card = t('Deleted member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                      $content_card = (count($user_name) == 0) ? t('Empty userlist', array(), array('context' => 'gofast_audit')) : gofast_message_ext_api_generate_content_card($userlist_name, "");
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => $title_card, 'content' => $content_card]);
                    break;
                case 'update_userlist':
                  $userlist_name = $edition['userlist_name'];
                  $title_card = t('Updated member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                  $content_card = "";
                    if(isset($edition['userlist_members'])){
                      if (isset($edition['userlist_members']['removed'])) {
                        $user_name = $edition['userlist_members']["removed"];
                        $content_card .= '<p class="ml-1 m-0 text-danger" >' . t("Removed", array(), array('context' => 'gofast:gofast_userlist')) . '</p>';
                        $content_card .= (count($user_name) == 0) ? t('Empty userlist', array(), array('context' => 'gofast_audit')) : gofast_message_ext_api_generate_content_card_group($user_name, "");
                      } 
                      if (isset($edition['userlist_members']['current'])) {
                        $user_name = $edition['userlist_members']['current'];
                        $content_card .= '<p class="ml-1 m-0 text-success" >' . t("New", array(), array('context' => 'gofast:gofast_userlist')) . '</p>';
                        $content_card .= gofast_message_ext_api_generate_content_card_group($user_name, "");
                      }
                    }else{
                      $content_card = t('No info available.');
                    }
                    $edit .= theme('gofast_card_template', ['class' => 'bg-warning', 'title' => $title_card, 'content' => $content_card]);
                    break;
                case 'create_room':
                    $content_card = $edition['room_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' =>t('Created room name : '), 'content' => $content_card]);
                    break;
                case 'delete_room':
                    $content_card = $edition['room_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Deleted room name : '), 'content' => $content_card]);
                    break;
                case 'preadd_user':
                    $titre_card = t('Pre-added member : ');
                    $user_id = $edition["user_id"];
                    $content_card = gofast_message_ext_api_generate_content_card_user($user_id);
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => $titre_card, 'content' => $content_card]);
                    break;   
                case 'deny_membership':
                    $titre_card = t('Member denied : ');
                    $user_id = $edition["user_id"];
                    $role_name = gofast_og_get_user_roles($edition["nid"], $user_id);
                    $role = gofast_message_ext_api_get_role($role_name);
                    $content_card = gofast_message_ext_api_generate_content_card_user($user_id,$role);
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => $titre_card, 'content' => $content_card]);
                    break;
                case 'update_role':
                  $title_card = t("Role modification", array(), array("context" => "gofast:gofast_audit"))." : ";
                  $entity_id = $edition["entity_id"];
                  $entity_type = $edition["entity_type"];
                  $entity = entity_load_single($entity_type, $entity_id);

                  $formatted_old_role = gofast_message_ext_api_get_role($edition["old_role"]);
                  $formatted_new_role = gofast_message_ext_api_get_role($edition["new_role"]);
                  $content_card = "";
                  if($entity_type == "userlist"){
                    $content_card = '<div class="d-flex flex-column justify-content-center align-items-center"><div class="mb-2 symbol symbol-50 flex-shrink-0">
                    <span class="symbol-label"><i class="fas fa-2x fa-user-friends userlist"></i></span></div><p class="text-truncate">' . $entity->name . '</p>';
                  } else if($entity_type == "user"){
                    $content_card = '<div class="d-flex flex-column justify-content-center align-items-center">' .
                    theme('user_picture', ['account' => user_load($entity_id), 'popup' => FALSE, 'dimensions' => ['width' => '25px', 'height' => '25px']]) .
                    "<p class='text-truncate'>" . gofast_message_ext_api_get_user_name($entity_id) ."</p>";
                  }
                  $content_card .= "<div class='card card-custom p-3 mb-1 w-100 d-flex flex-row justify-content-center align-items-center bg-danger'>
                  <span class='text-white font-size-h5 text-center card-label mr-3'>".t("Old")." :</span>$formatted_old_role</div>";
                  $content_card .= "<div class='card card-custom p-3 mb-1 w-100 d-flex flex-row justify-content-center align-items-center bg-success'>
                  <span class='text-white font-size-h5 text-center card-label mr-3'>".t("New")." :</span>$formatted_new_role</div>";
                  $content_card .= "</div>";
                  $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => $title_card, 'content' => $content_card]);
                  
                  break;
              }
            }
          }
          $output .= theme('gofast-message-ext-last-event', array('output_prepare' => $event['message'], 'edit' => $edit));
        }
        else{
          $output .= theme('gofast-message-ext-last-event', array('output_prepare' => $event['message'], 'edit' => NULL));
        }

        return $output;
}

function get_last_event($nid){
    //print_r(node_load($nid)); exit;
}
/**
 * Define an html rendering based on an array of information about the role of a user or a userlist 
 *
 * @param Array $roleObject
 *   The user ID for whom the content card is generated.
 *
 * @return html
 *   HTML content with role.
 */
function gofast_message_ext_api_get_role($roleObject) {
  $existing_role = array('read only member', 'group contributor', 'administrator member');
  foreach ($roleObject as $key => $value) {
      if (in_array($value, $existing_role)) {
          switch ($value) {
              case 'read only member':                  
                $titleTranslation = t("Read Only", array(), array('context' => 'gofast:gofast_user'));
                return '<span class="label font-weight-bold label-lg label-inline w-50 ' . "label-light-primary" . '" style="height:30px;">' . $titleTranslation . '</span>';
              case 'group contributor':
                $titleTranslation = t("Contributor", array(), array('context' => 'gofast:gofast_user'));
                return '<span class="label font-weight-bold label-lg label-inline w-50 ' . "label-primary" . '" style="height:30px;">' . $titleTranslation . '</span>';
              case 'administrator member':
                $titleTranslation = t("Administrator", array(), array('context' => 'gofast:gofast_user'));
                return '<span class="label font-weight-bold label-lg label-inline w-50 ' . "label-danger" . '" style="height:30px;">' . $titleTranslation . '</span>';

          }
      }
  }
  return "";
}
/**
 * Generate content card for a user
 *
 * Retrieves information and generates a content card for a user based on the user ID.
 *
 * @param int $user_id
 *   The user ID for whom the content card is generated.
 * @param string $role
 *   Optional user role to be displayed on the card.
 *
 * @return html
 *   HTML content representing the user card.
 */
function gofast_message_ext_api_generate_content_card_user($user_id, $role = '') {
  $content = '<div class="d-flex flex-column justify-content-center align-items-center">' .
      theme('user_picture', ['account' => user_load($user_id), 'popup' => FALSE, 'dimensions' => ['width' => '25px', 'height' => '25px']]) .
      "<p class='text-truncate'>" . gofast_message_ext_api_get_user_name($user_id) . "</p>";
  if (!empty($role)) {
      $content .= $role;
  }
  $content .= '</div>';
  return $content;
}
/**
 * Generate content generic card 
 *
 * Retrieves information and generates a content card 
 *
 * @param int $name
 *   The name for whom the content card is generated.
 * @param string $role
 *   Optional user role/userlist to be displayed on the card.
 *
 * @return html
 *   HTML content representing the user card.
 */
function gofast_message_ext_api_generate_content_card($name, $role = '') {
  $symbol = (strlen($name) >= 2) ? strtoupper(substr($name, 0, 2)) : 'UL';
  $content = '<div class="d-flex flex-column justify-content-center align-items-center">' .
      '<div class="symbol symbol-35 flex-shrink-0"> <span class="symbol-label">' . $symbol . ' </span></div>' .
      '<p>' . $name . '</p>';

  if (!empty($role)) {
      $content .= $role;
  }
  $content .= '</div></div>';
  return $content;
}
/**
 * Generate content card for a group of users
 *
 * Retrieves information and generates a content card for a group of user based on the user ID.
 *
 * @param int $user_ids
 *   The user ID for whom the content card is generated.
 * @param string $role
 *   Optional user role to be displayed on the card.
 *
 * @return html
 *   HTML content representing the card.
 */
function gofast_message_ext_api_generate_content_card_group($user_ids, $role) {
  $content = '<div class="d-flex flex-column justify-content-center align-items-center">';

  if (count($user_ids) > 2) {
      foreach ($user_ids as $user_name) {
          $content .= gofast_message_ext_api_get_user_name($user_name) . "<br>";
      }
  } else {
      foreach ($user_ids as $user_name) {
          $content .= theme('user_picture', ['account' => user_load($user_name), 'popup' => FALSE, 'dimensions' => ['width' => '25px', 'height' => '25px']]) .
              "<p>" . gofast_message_ext_api_get_user_name($user_name) . "</p>";
      }
  }
  $content .= $role . '</div>';
  return $content;
}
/**
 * Calculates the progress percentage based on a given fraction.
 *
 * @param string $fraction The fraction in the format "numerator/denominator".
 *
 * @return float The calculated progress percentage.
 */
function gofast_message_ext_api_get_progress_percentage($fraction) {
  // Split the fraction into numerator and denominator
  list($numerator, $denominator) = explode('/', $fraction);
  $numerator = floatval($numerator);
  $denominator = floatval($denominator);

  // Check if values are numeric and denominator is not zero
  if (is_numeric($numerator) && is_numeric($denominator) && $denominator != 0) {
    // Calculate percentage if everything is correct
    $percentage = ($numerator / $denominator) * 100;
    return $percentage; // Return the actual calculated percentage
  } else {
    return 0; // Invalid fraction or denominator is zero
  }
}

/**
 * Retrieves formatted information from the edition field based on the field type.
 *
 * @param array $edition The edition data.
 * @param string $myformat The format to use for dates.
 * @param array $l Localization parameters.
 *
 * @return array An associative array with formatted information from the field.
 */
function gofast_message_ext_api_get_info_field($edition, $myformat, $l) {
  $isTaxoTerm = $edition['field'] == "criticity" || $edition['field'] == "state" || $edition['field'] == "criticity" || $edition['field'] == "category" || $edition['field'] == "tags"  || $edition['field'] == "task_column";
  $isNodeRef = $edition['field'] == "targets" || $edition['field'] == "groups";
  $isUserTerm = $edition['field'] == "members" || $edition['field'] == "person_in_charge" || strpos($edition['field'], "assignee") !== false;
  $isDateTerm = strpos($edition['field'], "deadline") !== false;
  $isTDLStatusTerm = strpos($edition['field'], "status") !== false;

  if ($isTaxoTerm) { //Translating ids in name
    $from = gofast_message_ext_api_get_term($edition['from']);
    $to = gofast_message_ext_api_get_term($edition['to']);
  } else if ($isNodeRef) {
    $from = gofast_message_ext_api_get_node_name($edition['from']);
    $to = gofast_message_ext_api_get_node_name($edition['to']);
  } else if ($isUserTerm) {
    $from = gofast_message_ext_api_get_user_name($edition['from']);
    $to = gofast_message_ext_api_get_user_name($edition['to']);
  } else if ($isDateTerm) {
    $from = format_date($edition['from'], 'custom', $myformat, NULL, $l["langcode"]);
    $to = format_date($edition['to'], 'custom', $myformat, NULL, $l["langcode"]);
  } else if ($isTDLStatusTerm) {
    $from_themed_status = $edition['from'] == 0 ? t("Todo", array(), $l) : t("Done", array(), $l);
    $to_themed_status = $edition['to'] == 0 ? t("Todo", array(), $l) : t("Done", array(), $l);
    $from = $from_themed_status;
    $to = $to_themed_status;
  } else {
    $from = $edition['from'];
    $to = $edition['to'];
  }
  return array('from' => $from, 'to' => $to);
}
