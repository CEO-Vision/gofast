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
  if(isset($brut_array)){
    if($key != NULL){
      foreach ($brut_array as $brut_item) { //Formated as (t1, t2, t3...)
        if($i == 0){
          if(isset($brut_item[$key])){
            $formated_string = $brut_item[$key];
          }
        }
        else{
          if(isset($brut_item[$key])){
            $formated_string .= (", ".$brut_item[$key]);
          }
        }
        $i++;
      }
    }

    else{
      foreach ($brut_array as $brut_item) { //Formated as (t1, t2, t3...)
        if($i == 0){
          $formated_string = $brut_item;
        }
        else{
          $formated_string .= (", ".$brut_item);
        }
        $i++;
      }
    }
  }

  if($i == 0 || !isset($formated_string)){ //Case: No array content found
    $formated_string = "";
  }

  return $formated_string;
}

function gofast_message_ext_api_share($node){
    $node_array[] = array();
    foreach($node as $k_from => $v_from){
        $node_array[$k_from]['value'] = $v_from;
    }
    return $node_array;
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
      $isSame = (strcmp($v_from, $to[$k_from]) == 0); //Same values

      //Bugfix GOFAST-2970 : Sometimes, the version 1.0 seems to be removed.
      if($k_from == 'version'){
        if($v_from == "1.0" && $to[$k_from] == NULL){
          $isSame = TRUE;
        }
      }

       if($k_from == 'todolist'){
             $from_items = array();
            if(count($v_from->items) > 0){
                foreach($v_from->items as $item){
                    $from_items[$item->ciid] = $item;
                }
            }
            $v_from->items = $from_items;
              $to_items = array();
            if(count($to[$k_from]["items"]) > 0){
                foreach($to[$k_from]["items"] as $item){
                    $to_items[$item->ciid] = $item;
                }
            }
            $to[$k_from]["items"] = $to_items;
            //check if there are count difference (to detect items add or remove)
            if(count($to[$k_from]["items"]) > count($v_from->items)){
                //item add
                $items_added = array_diff_key($to[$k_from]["items"], $v_from->items);
                if(count($items_added) > 0){
                    foreach($items_added as $item_added){
                        $isSame = false;
                        $field_name = "todolist_".$item_added->ciid."_".$item_added->label."_";
                        $field_name .= "label";
                        $compare_array[$field_name]['from'] = "";
                        $compare_array[$field_name]['to'] = $item_added->label;
                    }
                }
            }

             if(count($v_from->items) > count($to[$k_from]["items"])){
                //item deleted
                $items_deleted = array_diff_key($v_from->items, $to[$k_from]["items"]);
                if(count($items_deleted) > 0){
                    foreach($items_deleted as $item_deleted){
                        $isSame = false;
                        $field_name = "todolist_".$item_deleted->ciid."_".$item_deleted->label."_";
                        $field_name .= "label";
                        $compare_array[$field_name]['from'] = $item_deleted->label;
                        $compare_array[$field_name]['to'] = "";
                    }
                }
            }
          foreach($v_from->items as $key=>$item){
            //check label, deadline, uid and status
            //the fieldname must be on the following form : todolist_ciid_label_fieldname

            if($item->label !== $to[$k_from]["items"][$key]->label){
                     $isSame = false;
                     $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
                     $field_name .= "label";
                     $compare_array[$field_name]['from'] = $item->label;
                     $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->label;

            }
            if($item->deadline !== $to[$k_from]["items"][$key]->deadline){
                     $isSame = false;
                     $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
                     $field_name .= "deadline";
                     $compare_array[$field_name]['from'] = $item->deadline;
                     $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->deadline;

            }
            if($item->uid !== $to[$k_from]["items"][$key]->uid){
                     $isSame = false;
                     $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
                     $field_name .= "assignee";
                     $compare_array[$field_name]['from'] = $item->uid;
                     $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->uid;

            }
            if($item->status !== $to[$k_from]["items"][$key]->status){
                     $isSame = false;
                     $field_name = "todolist_".$item->ciid."_".$to[$k_from]["items"][$key]->label."_";
                     $field_name .= "status";
                     $compare_array[$field_name]['from'] = $item->status;
                     $compare_array[$field_name]['to'] = $to[$k_from]["items"][$key]->status;

                     //if a task status has changed, add a new line into the array, containing the global status
                     $compare_array["todolist_Global Progression"]['from'] = $v_from->nb_items_completed." / ".$v_from->nb_items;
                     $compare_array["todolist_Global Progression"]['to'] = $to[$k_from]["nb_items_completed"]." / ".$to[$k_from]["nb_items"];
            }
          }
      }else{

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
    if(count($array_v) == 2 && $array_k != "changed" && $array_k != "ruid" && $array_k != 'created'){
        $edited_fields[] = $array_k;
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

  $query_exe['message'] = gofast_message_ext_api_field_target_id_get_mids_from_nid($nid);
  $query_com_exe['message'] = gofast_message_ext_api_field_node_id_get_mids_from_nid($nid);


  if(isset($query_exe['message']) || isset($query_com_exe['message'])){

    if(isset($query_exe['message'])){ //Set timestamp of last node event if exists
      $mids = array_values($query_exe['message']);
      $last_mid = end($mids);
      //load only the last entity
      $message_items = entity_load('message', array($last_mid));

      $last_message = array_shift(array_values($message_items));

      while($last_message->field_message_log['und']['0']['value'] === 'INVALID' && $last_message != FALSE){
        $last_message = array_shift(array_values(entity_load('message',array(prev($mids)))));
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
      $mids_com = array_values($query_com_exe['message']);
      $last_mid = end($mids_com);
      //load only the last entity
      $message_items_com = entity_load('message', array($last_mid));
      $last_message_com = array_shift(array_values($message_items_com));

      while($last_message_com->field_message_log['und']['0']['value'] === 'INVALID' && $last_message_com != FALSE){
        $last_message_com = array_shift(array_values(entity_load('message',array(prev($mids_com)))));
      }

      while(!gofast_message_ext_api_comment_is_valid($last_message_com->field_message_log['und']['0']['value']) && $last_message_com != FALSE){
        $last_message_com = array_shift(array_values(entity_load('message',array(prev($mids_com)))));
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
        $user_loaded = user_load($message_data['ruid']['value']);
        if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
         //$user_loaded_displayname = gofast_user_get_display_name_sql($message_data['ruid']['value']);
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
         //$user_loaded_displayname = gofast_user_get_display_name_sql($message_data['ruid']['to']);
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
          //$user_loaded_displayname = gofast_user_get_display_name_sql($message_data['uid']['value']);
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
          //$user_loaded_displayname = gofast_user_get_display_name_sql($message_data['uid']['to']);
      }
    }
    if(empty($user_loaded_displayname)){
      $user_loaded = user_load(1);
       if(gofast_user_view_access($user_loaded) === FALSE){
            $user_loaded_displayname = "";
        }else{
            $user_loaded_displayname = gofast_user_display_name($user_loaded);
        }
        //$user_loaded_displayname = gofast_user_get_display_name_sql(1);
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
    $message_data_com = json_decode($message, TRUE);

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
    $users_to_implode[] = gofast_user_display_name($uid);
  }
  $return = implode(",", $users_to_implode);
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
function gofast_message_ext_api_get_username($users_id){
  $array_uids = explode(",", $users_id);
  $users_to_implode = array();
  foreach($array_uids as $uid){
    $account = user_load($uid);
    $users_to_implode[] = $account->name;
  }
  $return = implode(",", $users_to_implode);
  return $return;
}


function gofast_message_ext_api_render_event($event){
        $edit = NULL;
        global $user;
        $myformat= system_date_format_locale($user->language, "medium");
        $l = array('langcode' => $user->language, 'context' => 'gofast');

        if(isset($event['0'])|| $event['message'] != 'ECON'){ //If precise edits was caught out
          foreach($event as $edit_key => $edition){
            if(is_array($edition) || ($edit_key == "title" && $edit === NULL )){
              switch($event['event']){
                case 'ECON':
                case 'NREV':
                case 'ETDL':
                  $isTaxoTerm = $edition['field'] == "criticity" || $edition['field'] == "state" || $edition['field'] == "criticity" || $edition['field'] == "category" || $edition['field'] == "tags"  || $edition['field'] == "task_column";
                  $isNodeRef = $edition['field'] == "targets" || $edition['field'] == "groups";
                  $isUserTerm = $edition['field'] == "members" || $edition['field'] == "person_in_charge" || strpos($edition['field'], "assignee") !== false;
                  $isDateTerm = strpos($edition['field'], "deadline") !== false;
                  $isTDLStatusTerm = strpos($edition['field'], "status") !== false;

                if($isTaxoTerm){ //Translating ids in name
                    $from = gofast_message_ext_api_get_term($edition['from']);
                    $to = gofast_message_ext_api_get_term($edition['to']);
                  }
                else if($isNodeRef){
                    $from = gofast_message_ext_api_get_node_name($edition['from']);
                    $to = gofast_message_ext_api_get_node_name($edition['to']);
                  }
                else if($isUserTerm){
                  $from = gofast_message_ext_api_get_user_name($edition['from']);
                  $to = gofast_message_ext_api_get_user_name($edition['to']);
                }else if($isDateTerm){
                  $from = format_date($edition['from'], 'custom', $myformat, NULL, $l["langcode"]);
                  $to = format_date($edition['to'], 'custom', $myformat, NULL, $l["langcode"]);
                }else if($isTDLStatusTerm){
                  if($edition['from'] == 0){
                     $from_themed_status = t("Todo", array(), $l);
                  }else{
                     $from_themed_status = t("Done", array(), $l);
                  }
                  if($edition['to'] == 0){
                     $to_themed_status = t("Todo", array(), $l);
                  }else{
                     $to_themed_status = t("Done", array(), $l);
                  }
                  $from =  $from_themed_status;
                  $to = $to_themed_status;
                }else{
                    $from = $edition['from'];
                    $to = $edition['to'];
                  }

                  if($from == NULL && $to != NULL){ //Case: New

                    $edit_card = "<span>".t(ucfirst($edition['field']), array(), array('context' => 'gofast'))."</span>";

                    if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                      $content_card = $to;
                    }
                    else{
                      $content_card = t($to, array(), array('context' => 'gofast'));
                    }
                    $edit_content = theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('New'), 'content' => $content_card, 'child_content' => true]);
                    $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $edit_card, 'content' => $edit_content]);

                  }
                  if($from != NULL && $to == NULL){ //Case: Removed

                   $edit_card .= "<span>" . t(ucfirst($edition['field']), array(), array('context' => 'gofast')) . "</span>";
                        if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                          $content_card = $from;
                        }
                        else{
                         $content_card = t($from, array(), array('context' => 'gofast'));
                        }
                  $edit_content = theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Removed'), 'content' => $content_card, 'child_content' => true]);
                  $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $edit_card, 'content' => $edit_content]);
                  }
                  if($from != NULL && $to != NULL){ //Case: Edition
                   $is_todolist_field = gofast_kanban_is_todolist_field($edition['field']);
                   if($is_todolist_field){
                        $edition['field'] = gofast_kanban_get_readable_name_specific_fields($edition['field'], true);
                   }
                    $edit_card = "<span>" . t(ucfirst($edition['field']), array(), array('context' => 'gofast')) . "</span>";

                    if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                     $content_card .= $from;
                    }
                    else{
                      $content_card .= t($from, array(), array('context' => 'gofast'));
                    }
                    $edit_content .= theme('gofast_card_template', ['class' => 'bg-danger mb-2', 'title' => t('Old'), 'content' => $content_card, 'child_content' => true]);
                     $content_card = "";
                    if($edition['field'] == 'body' || $edition['field'] == 'summary'){
                      $content_card .= $to;
                    }
                    else{
                     $content_card .= t($to, array(), array('context' => 'gofast'));
                    }
                     $edit_content .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('New'), 'content' => $content_card, 'child_content' => true]);
                     $edit .= theme('gofast_card_template', ['class' => 'gofastPopoverHeader', 'title' => $edit_card, 'content' => $edit_content]);
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
                  if (!empty($event['dest_uid'])) {
                    $dest_array_uids = json_decode($event['dest_uid'], 1);
                    $array_id_sharing = [];
                    foreach ($dest_array_uids as $dest_arrays) {
                      foreach ($dest_arrays as $key => $dest_item) {
                        if ($key === 'type' && $dest_item === 'user') {
                          $array_id_sharing[] = $dest_arrays['value'];
                        }
                      }
                    }
                    foreach ($array_id_sharing as $id_sharing) {
                      $content_card .= '<div class="d-inline-flex align-items-center"';
                      if ($id_sharing != '') {
                        if (is_numeric($id_sharing)) {
                          $content_card .= theme('user_picture', [
                                'account' => user_load($id_sharing),
                                'popup' => FALSE,
                                'dimensions' => [
                                  'width' => '25px',
                                  'height' => '25px',
                                ],
                              ]
                            ) . '<div class="pl-3"> ' . l(gofast_message_ext_api_get_user_name($id_sharing), '/user/' . $id_sharing) . '</div>';
                        }
                        else {
                          $content_card .= theme('user_picture', [
                                'account' => user_load(0),
                                'popup' => FALSE,
                                'dimensions' => [
                                  'width' => '25px',
                                  'height' => '25px',
                                ],
                              ]
                            ) . '<div class="pl-3"> ' . $id_sharing;
                        }
                      }
                      $content_card .= '</div></br>';
                    }
                    $edit .= theme('gofast_card_template', [
                      'class' => 'gofastPopoverHeader m-0',
                      'title' => t('Sent to: ', [], ['context' => 'gofast']),
                      'content' => $content_card,
                    ]);
                    $content_card = '';
                    foreach ($event as $key => $event3) {
                      if ($key == "version" && $key != '0') {
                        $content_card .= '<code><strong>' . $event3 . '</strong></code>';
                      }
                    }
                    $edit .= theme('gofast_card_template', [
                      'class' => 'gofastPopoverHeader m-0',
                      'title' => t('Shared document version: '),
                      'content' => $content_card,
                    ]);
                  }
                  break;
                case 'sharing_dl':

                 $edit .= "<div class='text-dark-65'>" . t("Detail of the shared document download", array(), array('context' => 'gofast')) . "</div>";
                 $content_card = '';
                  foreach($edition as $key=>$event4){
                    if($key == "addr_ip"){
                        if(empty(user_load($event4))){
                           $content_card .= '<code><strong>' .$event4 . '</strong></code>' ;
                        }else{
                           $content_card .=  theme('user_picture', array( 'account' => user_load($event4), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))) . ':   ' .  gofast_message_ext_api_get_user_name($id_sharing) . '</br>';
                        }
                    }
                  }
                  $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('IP of the downloader : '), 'content' => $content_card]);
                 $content_card = '';
                  foreach($event as $key=>$event5){
                      if($key == "version" && $key != '0'){
                         $content_card .= '<code><strong>' .$event5 . '</strong></code>' ;
                            }
                  }
                   $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Version : '), 'content' => $content_card]);
                  break;
                case 'user_blocked':
                case 'user_leave':
                    $uid_to_block = $edition['uid_to_block'];
                    $content_card =  theme('user_picture', array( 'account' => user_load($uid_to_block), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . ':   ' .  gofast_message_ext_api_get_user_name($uid_to_block) . '</br>';
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('User blocked : '), 'content' => $content_card]);
                    break;
                case 'user_unblocked':
                case 'user_unleave':
                    $uid_to_block = $edition['uid_to_block'];
                    $content_card =  theme('user_picture', array( 'account' => user_load($uid_to_block), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . ':   ' .  gofast_message_ext_api_get_user_name($uid_to_block) . '</br>';
                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('User unblocked : '), 'content' => $content_card]);
                    break;
                case 'delete_folder':
                    $path = $edition['path'];
                    $content_card = str_replace("/alfresco/webdav/","", rawurldecode($path));
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Delete folder : '), 'content' => $content_card]);
                    break;
                case 'delete_node':
                  $nodesPath = $edition['node_path'];
                  if (!empty($nodesPath) && $nodesPath != [""]) {
                      foreach ($nodesPath as $Path) {
                   $content_card  = $Path ." </br>";
                      }
                  }else{
                    $content_card = "Pas de path definie";
                  }
                  $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' =>t('Delete node location : '), 'content' => $content_card]);
                  break;
                case 'create_user':
                    $user_uid = $edition['user_create'];
                     $content_card =  theme('user_picture', array( 'account' => user_load($user_uid), 'popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . ':   ' .  gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                     $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('Created user : '), 'content' => $content_card]);
                    break;
                case 'delete_user':
                    $user_delete_name = $edition['user_delete_name'];
                   $content_card  =  theme('user_picture', array('popup' => TRUE, 'dimensions' => array('width' => '25px', 'height' => '25px'))) . ':   ' .  $user_delete_name . '</br>';
                   $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => t('Deleted user : '), 'content' => $content_card]);
                  break;
                case 'add_member':
                    if (isset($edition['user_name'])){
                        $user_name = $edition['user_name'];
                    }else if(isset($edition['array_members'])){
                        $user_name = $edition['array_members'];
                    }else{
                        $user_name = $edition['userlist_members'];
                    }

                    if (isset($edition['user_role'])){
                        $user_role = $edition['user_role'];
                    }else{
                        $user_role = $edition['userlist_role'];
                    }

                   $edit .= "<div class='text-dark-65'>" . t("Detail of the added member", array(), array('context' => 'gofast')) . "</div>";

                    if (isset($edition['user_name'])){
                        $titre_card = t('Added member : ');
                        $content_card =  theme('user_picture', array( 'account' => user_load($user_name), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                            ) . ':   ' .  gofast_message_ext_api_get_user_name($user_name) . '</br>';
                    }else if(isset($edition['array_members'])){
                        $userlist_name = 'test';
                        $titre_card = t('Added member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                        foreach ($user_name as $user_uid) {
                          $content_card =  theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))) . ':   ' .  gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                        }
                    }else{
                        $userlist_name = $edition['userlist_name'];
                        $titre_card = t('Added member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                        foreach($user_name as $user_uid){
                           $content_card =  theme('user_picture', array( 'account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                                ) . ':   ' .  gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                        }
                        if(count($user_name) == 0){
                            $content_card = t('Empty userlist', array(), array('context' => 'gofast_audit'));
                        }
                    }

                    $edit .= theme('gofast_card_template', ['class' => 'bg-success', 'title' => $titre_card, 'content' => $content_card]);

                    $role_name = og_get_user_roles_name($user_role);
                    $content_card = t(reset($role_name) , array() , array('context' => 'gofast_audit'));
                    $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Role : '), 'content' => $content_card]);
                    break;
                case 'workflow_add':
                  $content_card = $edition['worklow_name'] . " </br>";
                  $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Creating workflow name : '), 'content' => $content_card]);
                  break;
                case 'workflow_delete':
                  $content_card = $edition['worklow_name'] . " </br>";
                  $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Delete workflow name : '), 'content' => $content_card]);
                  break;
                case 'card_add':
                    $content_card = $edition['card_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' => t('Creating card name : '), 'content' => $content_card]);
                  break;
                case 'card_delete':
                    $content_card = $edition['card_name'] . " </br>";
                    $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' =>t('Delete card name : '), 'content' => $content_card]);
                  break;
                case 'delete_member':

                  if (isset($edition['user_name'])) {
                    $user_name = $edition['user_name'];
                  } else if (isset($edition['array_members'])) {
                    $user_name = $edition['array_members'];
                  }else {
                    $user_name = $edition['userlist_members'];
                  }


                  $edit .= "<div class='text-dark-65'>" .  t("Detail of the deleted member", array(), array('context' => 'gofast')) . "</div>";

                  if (isset($edition['user_name'])) {
                    $title_card = t('Deleted member : ');
                    $content_card = theme('user_picture', array('account' => user_load($user_name), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                        ) . ':   ' . gofast_message_ext_api_get_user_name($user_name) . '</br>';
                  } else if (isset($edition['array_members'])) {
                    $userlist_name = 'test';
                    $title_card = t('Deleted member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                    foreach ($user_name as $user_uid) {
                      $content_card=  theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))) . ':   ' .  gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                    }
                  } else {
                     $userlist_name = $edition['userlist_name'];
                     $title_card = t('Deleted member (from userlist %userlist): ', array('%userlist' => $userlist_name));
                    foreach ($user_name as $user_uid) {
                      $content_card = theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                          ) . ':   ' . gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                    }
                    if(count($user_name) == 0){
                      $content_card .= t('Empty userlist', array(), array('context' => 'gofast_audit'));
                    }
                  }
                     $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => $title_card, 'content' => $content_card]);

                  break;
                  case 'create_room':
                       $content_card = $edition['room_name'] . " </br>";
                       $edit .= theme('gofast_card_template', ['class' => 'bg-info', 'title' =>t('Creating room name : '), 'content' => $content_card]);
                      break;
                  case 'delete_room':
                       $content_card = $edition['room_name'] . " </br>";
                       $edit .= theme('gofast_card_template', ['class' => 'bg-danger', 'title' => t('Delete room name : '), 'content' => $content_card]);
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
