<?php

/**
 * 
 * @param type $type
 * @param type $filter
 */
function gofast_kanban_autocomplete($type, $space, $filter){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args()) ), WATCHDOG_DEBUG);
  
  //clean filter
 // $filter_cleaned = substr($filter, 0, strpos('?', $filter) );
  $space_nid = $space;

  if($type=='user'){
    $roles_filter = array('roles' => array('administrator member', 'group contributor', 'read only member'), 'space_nid' => $space_nid);
  return gofast_modal_user_by_role_autocomplete($filter, $roles_filter); 
  }else if($type=='user-userlist'){
    $roles_filter = array('roles' => array('administrator member', 'group contributor'), 'space_nid' => $space_nid);
    return gofast_modal_user_userlist_autocomplete($filter, $roles_filter);
  }else if($type=='user-not-readonly'){
    $roles_filter = array('roles' => array('administrator member', 'group contributor'), 'space_nid' => $space_nid);
    return gofast_modal_user_by_role_autocomplete($filter, $roles_filter);
  }else if($type =='node'){
    $other_filters = array('bundle' => array('alfresco_item', 'conference', 'webform', 'forum', 'article'));
   // $roles_filter = array('roles' => array('administrator member', 'group contributor', 'read only member'), 'space_nid' => $space_nid);
    return gofast_modal_node_content_autocomplete($filter, $other_filters); 
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}
/**
 * 
 * @param type $nid
 * @return type
 */
function gofast_kanban_build_json($nid){
  
  $kanban_json = json_encode(gofast_kanban_build($nid));
  return $kanban_json;
  
}

function gofast_kanban_build($nid, $filter = NULL){
  
  $kanban_data = array();
   
  $kanban = node_load($nid);
  
  if(isset($kanban)){
    $kanban_data['title'] = $kanban->title;  
    $kanban_data['nid'] = $kanban->nid;  
    $kanban_data['tasklists'] = gofast_kanban_get_columns($kanban);
    $kanban_data['tasks'] = gofast_kanban_get_tasks($kanban, NULL, TRUE, $filter);
    $kanban_data['space_nid'] = $kanban->og_group_content_ref[LANGUAGE_NONE][0]['target_id'];
    
  }
  
  return $kanban_data;
}

/**
 * Get all column of the given kanban
 * @param type $kanban
 * @return array
 */
function gofast_kanban_get_columns($kanban) {
  $kanban_columns = array();
  foreach ($kanban->field_board_columns['und'] as $key => $tid) {
    $tid = $tid['tid'];
    $kanban_columns[$tid] = array(
          'title' => t(taxonomy_term_load($tid)->name, [], ["context" => "gofast:gofast:kanban"]),
          'id' => $tid,
          'order' => $key
        );
  }

  return $kanban_columns;
}

/**
 * Get all task for the given kanban, can be filtered by columuns
 * @param type $kanban
 * @param type $columns = array() Array of wanted columns
 * @param boolean $full if TRUE => return taks fully detailed, if FALSE => rerurn only task nid (default TRUE)
 * @param string $filter 
 * @return array
 */
function gofast_kanban_get_tasks($kanban, $columns = NULL, $full = TRUE, $filter = NULL ){
  $tasks = array();
  
  if( !isset($columns) ){
    $columns = gofast_kanban_get_columns($kanban);
  }
  
  foreach($columns as $key => $column){
    $id = $column['id'];
    $tasks[$id] = array();
        
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type' , 'node')
        ->entityCondition('bundle', 'task')
        ->propertyCondition('status', 1)
        ->fieldCondition('field_task_column', 'tid', $id)
        ->fieldCondition('field_board', 'target_id', $kanban->nid);
     
    if(isset($filter)){
      $query->propertyCondition('title', '%'.$filter.'%' , 'like');        
    }
    $query->fieldOrderBy('field_column_index', 'value');
    $results = $query->execute();
    if(isset($results)){
      $tasks_nids = array_keys((array) $results['node']);
      if($full){
        $tasks_nodes = node_load_multiple($tasks_nids);
        foreach($tasks_nodes as $task){
          $tasks[$id][] = gofast_kanban_get_task_details($task);
        }
      }
      else{
         $tasks[$id]=is_array($tasks_nids) ? $tasks_nids : array();
      }
    }
  }
  return $tasks;
}

/**
 * Return display info for the task status
 * @param $task the task node
 * @return array containing state, localized state and state indicator
 */
function gofast_kanban_get_task_status_decorator($task) {
  $task_details = [];
  $task_details["state"] = "";
  $task_details["localized_state"] = "";
  $task_details["localized_state_indicator"] = "primary";
  if (!empty($task->field_state)) {
    $task_status_term = taxonomy_term_load($task->field_state[LANGUAGE_NONE][0]['tid']);
    $task_details["state"] = $task_status_term->name;
    if ($task_details["state"] == "Done") {
      $task_details["localized_state_indicator"] = "success";
    }
    if ($task_details["state"] == "To Do") {
      $task_details["localized_state_indicator"] = "danger";
    }
    $task_details["localized_state"] = i18n_taxonomy_localize_terms($task_status_term)->name;
  }
  return $task_details;
}

/**
 * Return a class decorator for the deadline
 * @param type $deadline_date
 * @return string
 */
function gofast_kanban_get_task_deadline_decorator($deadline_date, $card_status){
  $decorator = '';
  
  $interval = $deadline_date->diff(new DateTime('NOW'));
  
  if ($interval->d >= 0 && $interval->d <= 1 && $interval->invert == 1) {
    $decorator = 'deadline-nearly-reached';
    if($card_status === 'Done'){
      $decorator .= '-off';
    }
  } else if ($interval->d >= 0 && $interval->invert == 0) {
    $decorator = 'deadline-reached';
    if($card_status === 'Done'){
      $decorator .= '-off';
    }
  }

  return $decorator;
}


function gofast_kanban_get_task_details($task) {
  global $user;
  $task_details = array();

  $task_details['title'] = $task->title;
  $task_details['nid'] = $task->nid;
  $task_details['comments_count'] = $task->comment_count;
  $task_details['uid'] = $task->uid;
  $task_details['kanban_nid'] = $task->field_board[LANGUAGE_NONE][0]['target_id'];
  
  $task_details['created_date'] = format_date($task->created, 'short_without_hours');
  
  $task_details['deadline'] = '';
  $task_details['deadline_color_indicator'] = '';
  $task_details['checklist_deadline'] = (gofast_kanban_get_user_checklist_item_with_nearest_deadline($task->nid, $user->uid))->deadline;

  $deadline_date_cklist = null;
  if ($task_details['checklist_deadline'] && is_numeric($task_details['checklist_deadline'])) {
    $deadline_date_cklist = new DateTime();
    $deadline_date_cklist->setTimestamp($task_details['checklist_deadline']);
    $task_status = taxonomy_term_load($task->field_state[LANGUAGE_NONE][0]['tid'])->name;
    $task_details['checklist_deadline'] = format_date($task_details['checklist_deadline'],  'short_without_hours');
    $task_details['checklist_deadline_color_indicator'] = gofast_kanban_get_task_deadline_decorator($deadline_date_cklist, $task_status );
  }

  //Display badge depending on state
  $task_details = array_merge($task_details, gofast_kanban_get_task_status_decorator($task));

  if (!empty($task->field_date[LANGUAGE_NONE][0]['value'])) {
    $deadline_date = new DateTime($task->field_date[LANGUAGE_NONE][0]['value']);
    $task_details['deadline'] = format_date($deadline_date->getTimestamp(),  'short_without_hours');
    $task_details['deadline_color_indicator']= gofast_kanban_get_task_deadline_decorator($deadline_date, $task_details["state"]);
  }

  //Get the closest deadline
  $task_details['closest_deadline'] = "";
  if ($deadline_date_cklist != null){
    $task_details['closest_deadline_timestamp'] = $deadline_date_cklist->getTimestamp();
    $task_details['closest_deadline'] = $task_details['checklist_deadline'];
    $task_details['closest_deadline_color_indicator'] = $task_details['checklist_deadline_color_indicator'];
  }else{
    $task_details['closest_deadline_timestamp'] = ($deadline_date!= null) ? $deadline_date->getTimestamp(): "";
    $task_details['closest_deadline'] = $task_details['deadline'];
    $task_details['closest_deadline_color_indicator'] = $task_details['deadline_color_indicator'];
  }

  if($task_details['closest_deadline'] != ""){
     $task_details['dueDate'] = format_date($task_details['closest_deadline_timestamp'], 'custom', "Y-m-d") . " 00:00:00.000";
  }

  $checklist_details = gofast_kanban_get_task_checklists($task->nid);
  
  $task_details['progress'] = $checklist_details[0]['progress'];
  $task_details['nb_items'] = $checklist_details[0]['nb_items'];
  $task_details['nb_items_completed'] = $checklist_details[0]['nb_items_completed'];
  
  //get first items of checklist
  $task_details['first_item_label'] = gofast_kanban_get_user_checklist_first_item($task->nid);
  $task_details['count_assigned_items'] = gofast_kanban_get_user_checklist_count_item($task->nid);
  
  $task_details['attachments']= array();
  foreach ($task->field_target_link[LANGUAGE_NONE] as $key => $elt){
    $task_details['attachments'][] = $elt['target_id'];
  }
  
  $task_details['person_in_charge'] = $task->field_person_in_charge[LANGUAGE_NONE][0]['target_id'];
  $task_details['members'] = array();
  foreach( $task->field_members['und'] as $key => $member){
    $task_details['members'][] = $member['target_id'];
  }

  return $task_details;
}

/**
 * 
 * @global type $user
 * @param type $task_nid
 * @param type $user_uid
 * @return type
 */
function gofast_kanban_get_user_checklist_first_item($task_nid, $user_uid = NULL){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args()) ), WATCHDOG_DEBUG);
  
  $first_item = array();
  
  global $user;
  if(!isset($user_uid)){
    $user_uid = $user->uid;
  }
  
  $first_item_obj = gofast_kanban_get_user_checklist_item_with_nearest_deadline($task_nid, $user_uid);
  if(is_array($first_item_obj) && count($first_item_obj) == 0){
     $first_item = t("You are the card's responsible", array(), array('gofast_kanban'));
  }else{
     $first_item = $first_item_obj->label;
  }
 
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $first_item;
  
}

function gofast_kanban_get_user_checklist_count_item($task_nid, $user_uid = NULL){
  $items = array();
  
  global $user;
  if(!isset($user_uid)){
    $user_uid = $user->uid;
  }
  
  //Get item with nearest deadline
  $filters = array(
      0 => array(
          'name' => 'c.task_nid',
          'value' => $task_nid,
          'operator' => '='
      ),
      1 => array(
          'name' => 'ci.status',
          'value' => '0', //uncompleted
          'operator' => '='
      ),
  );
  
  $count = gofast_kanban_get_user_checklistItems($user_uid, TRUE, $filters, TRUE);
  
  return $count;
}

/**
 * Return the checklist item uncompleted with the nearest deadline for the given user
 * If no item with deadline found, return the first item for the user sorted by label
 * @param type $task_nid
 * @param type $user_uid
 */
function gofast_kanban_get_user_checklist_item_with_nearest_deadline($task_nid, $user_uid){
 
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args()) ), WATCHDOG_DEBUG);
  
  $first_item = array();
  $items = array();
  
  //Get item with nearest deadline
  $filters = array(
      0 => array(
          'name' => 'c.task_nid',
          'value' => $task_nid,
          'operator' => '='
      ),
      1 => array(
          'name' => 'ci.status',
          'value' => '0', //uncompleted
          'operator' => '='
      ),
      2 => array(
          'name' => 'deadline',
          'value' => 'NULL',
          'operator' => '<>'
      )
  );
  
  $items = gofast_kanban_get_user_checklistItems($user_uid, TRUE, $filters);
  
  if(count($items) == 0){ 
    unset($filters[2]); // removed deadline <> NULL condition
    $items = gofast_kanban_get_user_checklistItems($user_uid, TRUE, $filters);
  }
  $first_item = $items[0];
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $first_item;
}


function gofast_kanban_get_task_activities($nid, $activity_types = array('ALL'),  $JSONFormat = FALSE){

  // ACTIVITY TYPE : COMMENT, 
  $activities = array();
  global $base_url;
  
  if(in_array('COMMENT', $activity_types) || in_array('ALL', $activity_types)){
    $comments = gofast_kanban_get_task_comments($nid, TRUE);

    foreach($comments as $comment){  
      
      $who = user_load($comment->uid);     
      $comment_wrapper = entity_metadata_wrapper('comment', $comment);    
      $activities[] = array(
          'event_type' => 'COMMENT',
          'event_timestamp' => isset($comment->changed)? $comment->changed : $comment->created,
          'event_details' => array(
              'who' => array(
                'uid' => $comment->uid, 
                'name' => gofast_user_get_display_name_sql($comment->uid), 
                'picture' => ($dataReturn['creator_picture'] = $who->picture->uri == null ? $base_url . '/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png' : file_create_url($who->picture->uri))
              ),
              'what' => array(
                  'comment_body' => $comment_wrapper->comment_body->value()['value'],
                  'comment_id' =>  $comment->cid
              )
          ),
          'event_task_nid' => $nid
      );
    }
  }
  
  if(in_array('EVENT', $activity_types) || in_array('ALL', $activity_types)){
     
    $events = gofast_kanban_get_task_events($nid);
     
    foreach($events as $event){  
      $activity = gofast_kanban_format_activity_event($event, $nid);
      if(! empty($activity)){ // removed unrelevant events
         $activities[] = $activity;
      }
    } 
  }
   
  //Sort by date DESC
  usort($activities, '_gofast_kanban_sort_activities');
  
  if($JSONFormat){
     print_r(json_encode($activities));
  }else{
    return $activities;
  }  
}

/**
 * Return activities on given task 
 * @param type $nid
 * @return String HTML
 */
function gofast_kanban_render_task_activities($nid, $async = FALSE){
  
  $task_activities = gofast_kanban_get_task_activities($nid, array("EVENT"));
  
  $container = theme('kanban_activities', array('activities' => $task_activities));
  if($async){
    return  $container;
  }else{
    print $container;
  }
}

function _gofast_kanban_sort_activities($a, $b){
    if($a['event_timestamp'] == $b['event_timestamp']){
      return 0;
    } 
    return $a['event_timestamp'] > $b['event_timestamp'] ? -1 : +1;
}


/**
 * 
 * @param type $event_details
 * @return array
 */
function gofast_kanban_format_checklist_event($event_details){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $checklist_updates = array();

  foreach (array_keys((array) $event_details) as $key) {
    if (strpos($key, 'todolist') === 0) {
      $temp = explode('_', $key);

      if (count($temp) == 4) { // Needed to avoid taking "Global Progression into account
        $checklist_updates['ciid'] = $temp[1];
        $checklist_updates['label'] = $temp[2];
        $checklist_updates['field_updated'][$temp[3]] = array(
            'value' => array(
                'old' => $event_details[$key]['removed'],
                'new' => $event_details[$key]['current']
            )
        );
      }
    }
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  return $checklist_updates;
}

/**
 * Format EVENT for Task activity
 * @param type $event
 * @param type $nid
 * @return type
 */
function gofast_kanban_format_activity_event($event, $nid){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : task_nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);
  
  $activity = array();
  global $base_url;
  
  $who = user_load($event->uid);
  
  $activity['event_timestamp'] = $event->timestamp;
  $activity['event_details']['who'] = array(
      'uid' => $event->uid, 
      'name' => gofast_user_get_display_name_sql($event->uid),
      'picture' => ( $who->picture->uri == null ? $base_url . '/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png' : file_create_url($who->picture->uri))
    );
  $activity['event_task_nid'] = $nid;

  // Format event
  $event_details_serialized = rawurldecode($event->details);
  $event_details = unserialize($event_details_serialized);
  
  //Manage creation event
  if($event->event_type == 'new_node'){
    $event_details['event'] = 'NCON';
  }

  switch ($event_details['event']) {
    case 'ETDL' : //checklist
      $activity['event_type'] = 'CHECKLIST';
      $activity['event_details']['what'] = array(
          'event' => $event_details['event']
      );
      $old= "";
      $new ="";
      $field_updated = "";
      $action= "";
      
      $checklist_updates = gofast_kanban_format_checklist_event($event_details);

      if(isset($checklist_updates['field_updated']['status']) ){
        $field_updated = 'status';
        if($checklist_updates['field_updated']['status']['value']['new'] == 1){
          $action = 'marked checklist item <b>%label</b> as <b>Completed</b>';
        }else{
           $action = 'marked checklist item <b>%label</b> as <b>Uncompleted</b>';
        }
      }else if ( isset($checklist_updates['field_updated']['label']) && $checklist_updates['field_updated']['label']['value']['new'] == '' ){ //delete checklist item
        $action = 'deleted the checklist item : <b>%label</b>';
        
      }else if ( isset($checklist_updates['field_updated']['label']) && $checklist_updates['field_updated']['label']['value']['old'] == '' ){ //create checklist item
        $action = 'added a checklist item : <b>%label</b>';
      }else if( isset($checklist_updates['field_updated'])){

        $field_updated = array_keys($checklist_updates['field_updated']);
        $action = 'updated <b>%fields</b> on checklist item <b>%label</b>';
      }
      
      $activity['event_details']['what'] = array(
          'event' => $event_details['event'],
          'field_updated' => $field_updated,
          'action' =>  $action,
          'label' => $checklist_updates['label'],
          'value' => array(
            'old' => $old,
            'new' => $new
          )
      );
      
      break;
      
    case 'NCON' : // Task creation
      
      $activity['event_type'] = 'TASK';
      $field_updated = "";
      $action = "created the card ";
      $old = "";
      $new= "";
      
       $activity['event_details']['what'] = array(
          'event' => $event_details['event'],
          'field_updated' => $field_updated,
          'action' =>  $action,
          'value' => array(
            'old' => $old,
            'new' => $new
          )
      );
      break;
      
    case 'ECON' : // task attribute
      
      $activity['event_type'] = 'TASK';
      $field_updated = "";
      $action = "";
      $old = "";
      $new= "";
      
      if(array_key_exists('task_column', $event_details)){
        
        $field_updated = 'task_column';
        $action = 'moved card from <b>%old_column</b> to <b>%new_column</b>'; 
        $old = taxonomy_term_load($event_details[$field_updated]['removed'])->name;
        $new = taxonomy_term_load($event_details[$field_updated]['current'])->name;
        
      }else if(array_key_exists('deadline', $event_details)){
        
        $field_updated = 'deadline';
        if ($event_details[$field_updated]['removed'] == '') {
          $action = 'added a due date for the card : <b>%new_column</b>';
        } else if ($event_details[$field_updated]['current'] == '') {
          $action = 'removed the card due date';
        } else {
          $action = 'changed the card due date to <b>%new_column</b>';
        }
        
        if($event_details[$field_updated]['removed'] != ''){
          $old_date = new DateTime($event_details[$field_updated]['removed']);
          $old = format_date($old_date->getTimestamp(), 'short');
        }
        if($event_details[$field_updated]['current'] != ''){
          $new_date =  new DateTime($event_details[$field_updated]['current']);
          $new = format_date($new_date->getTimestamp(), 'short');
        }
          
      }else if(array_key_exists('person_in_charge', $event_details)){
        
        $field_updated = 'person_in_charge'; 
        if ($event_details[$field_updated]['removed'] == '') {
          $action = 'added <b>%new_column</b> as task responsible';
        } else if ($event_details[$field_updated]['current'] == '') {
          $action = 'removed the card responsible';
        } else {
          $action = 'changed the card responsible from <b>%old_column</b> to <b>%new_column</b>';
        }
        $old = gofast_user_get_display_name_sql($event_details[$field_updated]['removed']);
        $new = gofast_user_get_display_name_sql($event_details[$field_updated]['current']);
        
      }else if(array_key_exists('members', $event_details)){
        $field_updated = 'members';
        
        if (trim($event_details[$field_updated]['removed']) == '') {
          $action = 'added assignee(s) to the card : <b>%new_column</b> ';
        } else if (trim($event_details[$field_updated]['current']) == '') {
          $action = 'removed the card assignee(s)';
        } else {
          $action =  'changed the card assignee(s) to <b> %new_column</b>'; 
        }
        
        $old_arr = explode(',', $event_details[$field_updated]['removed']);
        foreach($old_arr as $uid){
           $old .= (strlen($old) > 0)? ' ,': '';
           $old .= gofast_user_get_display_name_sql($uid);
        }
        $new_arr = explode(',', $event_details[$field_updated]['current']);
        foreach($new_arr as $uid){
           $new .= (strlen($new) > 0)? ' ,': '';
           $new .= gofast_user_get_display_name_sql($uid);
        }
        
      }else if(array_key_exists('targets', $event_details)){
        $field_updated = 'targets';
        
        if (trim($event_details[$field_updated]['removed']) == '') {
          $action = 'added attachment(s) to the card : <br><b>%new_column</b> ';
        } else if (trim($event_details[$field_updated]['current']) == '') {
          $action = 'removed the card attachment(s)';
        } else {
          $action =  'changed the card attachment(s) to <br><b> %new_column</b>'; 
        }
        
        /*
        $old_arr = explode(',', $event_details[$field_updated]['removed']);
        $old= (count($old_arr) > 0)? '<ul>' : '';
        foreach($old_arr as $nid){
           $old .= '<li>'.gofast_user_get_display_name_sql($uid).'</li>';
        }
        $old .= (strlen($old) > 0)? '</ul>': '';
        */

        $new_arr = explode(',', $event_details[$field_updated]['current']);
        $new_nodes = node_load_multiple($new_arr);
        foreach($new_nodes as $node){
          $new .= (strlen($new) > 0)? ', ': '';
           $new .= ''.$node->title;
        }
        
      }else if(array_key_exists('title', $event_details)){
        $field_updated = 'title';
        $action = 'changed the card title from <b>%old_column</b> to <b>%new_column</b>';
        $old = $event_details[$field_updated]['removed'];
        $new = $event_details[$field_updated]['current'];
        
      }else if(array_key_exists('body', $event_details)){
        $field_updated = 'body';
        if (trim($event_details[$field_updated]['removed']) == '') {
          $action = 'added a description : <br><div class="action-details"> !new_column </div>';
        } else if (trim($event_details[$field_updated]['current']) == '') {
          $action = 'removed the card description';
        } else {
          $action =  'changed the card description to <br><div class="action-details"> !new_column </div>'; 
        }
        $old =  urldecode(trim($event_details[$field_updated]['removed']));
        $new =  urldecode(trim($event_details[$field_updated]['current']));
        
      }else if(array_key_exists('state', $event_details)){
        $field_updated = 'state';
        $action =  'changed the card status from <b>%old_column</b> to <b>%new_column</b>'; 
        $old = i18n_taxonomy_localize_terms(taxonomy_term_load($event_details[$field_updated]['removed']))->name;
        $new = i18n_taxonomy_localize_terms(taxonomy_term_load($event_details[$field_updated]['current']))->name;
        
      }else{
        return;
      }
      
      $activity['event_details']['what'] = array(
          'event' => $event_details['event'],
          'field_updated' => $field_updated,
          'action' =>  $action,
          'value' => array(
            'old' => $old,
            'new' => $new
          )
      );
      break;
  }
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  

  return $activity;
}

/**
 * Retreive all element
 * @param type $nid
 */
function gofast_kanban_get_task_events($nid){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : task_nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);
  
  $events = array();
  
  $query = db_select('ceo_vision_audit', 'au')
     ->fields('au', array('nid', 'timestamp', 'uid', 'event_type', 'details'));
  
  $query->condition('nid', $nid, '=');
  $query->condition('event_type', "view_node", '<>');
    
  $query->orderBy('timestamp', 'DESC');
  
  $results = $query->execute()->fetchAll();
  if (count($results) > 0) {
     $events = $results;
  } 
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $events;
}

/**
 * Return all comment for the given task
 * @param type $nid id of the linked Task node
 * @param type $full (if TRUE load return full nodes, else only return cids
 * @return type
 */
function gofast_kanban_get_task_comments($nid, $full = FALSE ){
  
  $comments = array();

  $query =  new EntityFieldQuery();
  $query-> entityCondition('entity_type', 'comment')
        ->propertyCondition('nid', $nid)
        ->propertyOrderBy('created', 'DESC');

  $results = $query->execute();
  
   if(isset($results)){
      $cids = array_keys($results['comment']);
      
      if($full === TRUE){
        $comments = entity_load('comment', $cids);
      }else{
        $comments = $cids;
      }
   }

  return $comments;
}


function gofast_kanban_get_task_checklists_raw($nid, $full = FALSE) {

  $checklist = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'checklist')
      ->propertyCondition('task_nid', $nid)
      ->propertyOrderBy('label', 'ASC');

  $results = $query->execute();

  if (isset($results)) {
    $cids = array_keys($results['checklist']);

    if ($full === TRUE) {
      $checklist = gofast_kanban_checklist_load_multiple($cids);
    } else {
      $checklist = $cids;
    }
  }

  return $checklist;
}

/**
 * 
 * @param type $nid
 * @return type
 */
function gofast_kanban_get_task_checklists($nid){
  
  $checklists = array();
    
  $checklists_entities = gofast_kanban_get_task_checklists_raw($nid, TRUE);
  foreach ($checklists_entities as $checklist) {
    $checklists[] = array(
        'cid' => $checklist->cid,
        'label' => $checklist->label,
        'items' => gofast_kanban_get_task_checklist_item($checklist->cid),
        'nb_items_completed' => count($checklist->getItems(CheckListEntity::CHECKLIST_ITEM_STATUS_COMPLETED)),
        'nb_items' => count($checklist->getItems()),
        'progress' => $checklist->getProgress(),
        'task_nid' => $nid
    );
  }
  return $checklists;
}


function gofast_kanban_get_task_checklist_item($cid){
  
  $items = array();
  
  $checklist = gofast_kanban_mychecklist_load($cid);
  $items_entities = $checklist->getItems();
  
  foreach($items_entities as $key => $item){
    $items[] = $item;
  }
  
  return $items;
}

/**
 * Return all the kanban for the given space.
 * @param type $nid
 */
function gofast_kanban_get_space_kanban($nid, $full = FALSE){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : space_nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);
  
  $kanbans = array();
  
  //Search for the kanban of this space
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'kanban')
      ->fieldCondition('og_group_content_ref', 'target_id', $nid, '=');
  $results = $query->execute();

  if (isset($results) && count($results) > 0 ) {
    $kanban_nids = array_keys($results['node']);
    $kanbans = $kanban_nids;
  }else{
    $kanbans[] = gofast_kanban_create_space_kanban($nid);
  }
  

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  if ($full === TRUE) {
    return node_load_multiple($kanbans);
  }else{
    return $kanbans;
  }
}

/**
 * 
 * @return type
 */
function gofast_kanban_get_default_board_columns(){
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);
  $default_columns = array();
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'taxonomy_term')
    ->entityCondition('bundle', array('columns'))
    ->fieldCondition('field_default_column', 'value',  1)  
    ->propertyOrderBy('weight');
  $result = $query->execute();
  $tids = array_keys($result['taxonomy_term']);
  
  foreach($tids as $tid){
    $default_columns[] = array('tid' => $tid);
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $default_columns;
}

/**
 * @param boolean $JSONFormat if TRUE, return a list of status JSON formatted (default FALSE)
 * @return type
 */
function gofast_kanban_get_available_status( $JSONFormat = FALSE){
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);
  $available_status = array();
  
  $status = array('To Do', 'In Progress', 'Done'); //and Archived in futur version
  foreach($status as $status_label){
    $term = array_shift(taxonomy_get_term_by_name($status_label, 'state'));
    $available_status[] = array('tid' => $term->tid, 'label' => t($term->name));
  }
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  if($JSONFormat){
    print_r(json_encode($available_status));
  }else{
    return $available_status;
  }
  
  
}


/**
 * 
 * @param type $nid
 * @return type
 */
function gofast_kanban_create_space_kanban($nid){
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : space_nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);
  
  $kanban = new stdClass();
  $kanban->title = "Kanban";
  $kanban->type = "kanban";
  node_object_prepare($kanban);
  $kanban->language = LANGUAGE_NONE;
  $kanban->uid = 1;
  $kanban->status = 1;
  $kanban->promote = 0;
  $kanban->og_group_content_ref[LANGUAGE_NONE][0]['target_id'] = $nid;
  
  
  //get default column
  $kanban->field_board_columns[LANGUAGE_NONE] = gofast_kanban_get_default_board_columns();
  
  
  $kanban = node_submit($kanban);
  node_save($kanban);
  
  return $kanban->nid;
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * Return TRUE if the given column is part of the defaults, else return FALSE
 * @param type $column_id
 * @return boolean
 */
function gofast_kanban_is_default_column($column_id){
  
  //check if it's a default column
  $default_columns = gofast_kanban_get_default_board_columns();
  foreach($default_columns as $key => $column){
    if($column['tid'] == $column_id){
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Return the position of the given column into the kanban
 * @param type $kanban_nid
 * @param type $column_id
 * @return type
 */
function gofast_kanban_board_get_column_index($kanban_nid, $column_id){
  
  $kanban = node_load($kanban_nid);
  $kanban_columns = $kanban->field_board_columns[LANGUAGE_NONE];
  
  foreach($kanban_columns as $key => $column){
    if($column['tid'] == $column_id){
      return $key;
    }
  }
  
  return NULL;
    
}

/**
 * Retreive all checklistItem the given user is assigned to.
 * @param type $uid
 * @param boolean $full if TRUE return also Checklist data
 * @param array() $filters e.g array( 0 => array('name' => <name> , 'value' => <value>,'operator' => <operator> ))
 * @param boolean $count if TRUE make a faster query and just return the number of items
 * @return array() $items
 */
function gofast_kanban_get_user_checklistItems($uid = false, $full = FALSE, $filters = array(), $count = FALSE){
  global $user;
  if($user->uid == 0){
    return array();
  }

  $items = array();
  
  $query = db_select('gofast_kanban_checklist_item', 'ci')
    ->fields('ci', array('ciid', 'cid', 'label', 'deadline', 'uid', 'status'));

  //Do not include tasks from Card  with "Done" status
  if($full){
    $query->leftJoin('gofast_kanban_checklist', 'c', 'ci.cid = c.cid');
    $query->fields('c', array('task_nid', 'label'));
  }
     
  if($uid){
    $query->condition('ci.uid', $uid, '=');
  }
  
  //Add filters if not empty
  if(count($filters) > 0){
    foreach($filters as $filter){
      $query->condition($filter['name'], $filter['value'], $filter['operator']);
    }   
  }
  
  $query->orderBy('deadline', 'ASC');

  if ($count) {
    $results = $query->countQuery()->execute()->fetchField();
    return $results;
  }

  $results = $query->execute()->fetchAll();
  if (count($results) > 0) {
    $items = $results;
  }

  return $items;
}

/**
 * Retreive task node form a checklist item
 * @param type $ciid
 * @param type $full (default = FALSE)
 * @return type
 */
function gofast_kanban_get_task_from_checklistItem($ciid, $full= FALSE){
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : ciid=[%ciid] ', array('%name' => __FUNCTION__, '%ciid' => $ciid), WATCHDOG_DEBUG);
  
  $task = array();

  $query = db_select('gofast_kanban_checklist_item', 'ci');
  $query->leftJoin('gofast_kanban_checklist', 'c', 'ci.cid = c.cid');
  $query->fields('ci', array('ciid', 'cid'));
  $query->fields('c', array('task_nid', 'label'));
  $query->condition('ciid', $ciid, '=');

  $results = $query->execute()->fetchAll();
  if (count($results) > 0) {
    
     $task = $results[0]->task_nid;
     
     if($full){
       $task = node_load($results[0]->task_nid);
     }
  } 
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $task;
}

/**
 * Given a tasks object splitted by boards, get the formatted checklists progress matching those tasks
 */
function gofast_kanban_get_checklists_progress_by_board_tasks($board_tasks) {
  $formatted_counts = [];
  foreach ($board_tasks as $tasks) {
    foreach ($tasks as $task) {
      if (!$task["nb_items"]) {
        continue;
      }
      $progress = $task["nb_items_completed"] / $task["nb_items"];
      $formatted_counts["kanban-" . $task["nid"]] = $progress;;
    }
  }
  return $formatted_counts;
}

/**
 * Separate function to get the number of tasks (checklist items) assigned to the given user
 * With a single query and without fetching the actual tasks for better performances
 * @param int $uid
 * @param boolean $with_progress If TRUE returns fields to track checklist progress
 * @param array $tasks_nid If not empty will count only checklist items inside the tasks referenced by the given tasks ids
 * @return int|array
 */
function gofast_kanban_get_user_tasks_count($uid, $with_progress = FALSE, $tasks_nid = []) {
  $done_status = array_shift(taxonomy_get_term_by_name('Done', 'state'));

  $query = db_select('gofast_kanban_checklist_item', 'ci');
  $query->leftJoin('gofast_kanban_checklist', 'c', 'ci.cid = c.cid');
  $query->fields('c', array('task_nid'));
  $query->leftJoin('node', 'n', 'c.task_nid = n.nid');
  $query->leftJoin('field_data_field_state', 'st', 'st.entity_id = n.nid');
  if ($uid) {
    $query->condition('ci.uid', $uid, '=');
  }
  if (!empty($tasks_nid)) {
    $query->condition('c.task_nid', $tasks_nid, 'IN');
  }
  $query->condition('ci.status', 0, '='); // only get open checklist items
  $query->condition('n.status', 1, '=');
  $or = db_or();
  $or->condition('st.field_state_tid', $done_status->tid, '<>');
  $or->isNull('st.field_state_tid');
  $query->condition($or);
  $query->groupBy("c.task_nid");

  if ($with_progress) {
    $query->leftJoin('gofast_kanban_checklist_item', 'ci_total', 'c.cid = ci_total.cid'); // get the total amount of checklist items to compute the total checklist progress
    $query->addExpression("COUNT (DISTINCT ci_total.ciid)", "checklist_items_count");
    $query->addExpression("COUNT(DISTINCT CASE WHEN ci_total.status = 1 THEN ci_total.ciid END)", "checklist_done_items_count");
    $results = $query->execute()->fetchAll();
    return $results;
  }
  $count = $query->countQuery()->execute()->fetchField();
  return $count;
}

/**
 * Return all tasks assigned to the given user
 * @param type $uid
 * @param type $full
 * @return array
 */
function gofast_kanban_get_user_tasks($uid, $full = FALSE){
  $tasks = array();
  $tasks_nids = array();
  
  $done_status = array_shift(taxonomy_get_term_by_name('Done', 'state'));
  
  // Retreive tasks for which the user is assigned to checklist item
  $filters = array(
    0 => array('name' => 'ci.status', 'value' => 0, 'operator' => '=')
  );

  $checklist_for_user = gofast_kanban_get_user_checklistItems($uid, TRUE, $filters);

  if (!empty($checklist_for_user)) {
    
    foreach ($checklist_for_user as $item) {
      $tasks_nids[] = $item->task_nid;
    }
    
    $query2 = new EntityFieldQuery();
    $query2->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'task')
      ->propertyCondition('status', 1)
      ->propertyCondition('nid', $tasks_nids, 'IN');
    
    $final_results = $query2->execute();
  }

  if (!empty($tasks_nids)) {

    $nids = array_keys((array)$final_results['node']);
    $tasks_nodes = node_load_multiple($nids);
    
    //remove task from cards with "Done" status
    foreach($nids as $key=> $nid){
      if($tasks_nodes[$nid]->field_state[LANGUAGE_NONE][0]['tid'] == $done_status->tid){
        unset($tasks_nodes[$nid]);
        unset($nids[$key]);
      }
    }
    
    if($full == FALSE){
      return $nids;
    }

    foreach ($tasks_nodes as $task) {
      $task_details = gofast_kanban_get_task_details($task);
      
      if($task_details['count_assigned_items'] > 1){ //If we have multiple tasks to do, change label to count tasks
        $task_details['first_item_label'] = $task_details['count_assigned_items'] . " " . t('ToDo tasks assigned', [], ['context' => "gofast:gofast_kanban"]);
      }
      
      $tasks[] = $task_details;
    }
  }
  
  return $tasks;
}

/**
 * Return all tasks assigne to the given user
 * @param type $uid
 * @param type $full
 * @return type
 */
function gofast_kanban_get_other_tasks($uid, $full = FALSE){
  $tasks = array();
  $tasks_nids = array();
  
  $tasks_nids_in_charge = [];
  $tasks_nids_members = [];
  
  $done_status = array_shift(taxonomy_get_term_by_name('Done', 'state'));
  
  //Retrieve tasks I'm in charge
  $query_in_charge = db_select('node', 'n');
  $query_in_charge->fields('n', ['nid', 'type'])
      ->condition('fpic.field_person_in_charge_target_id', $uid)
      ->condition('fs.field_state_tid', $done_status->tid, '<>')
      ->condition('n.status', 1);
  $query_in_charge->addJoin('INNER', 'field_data_field_person_in_charge', 'fpic', 'n.nid=fpic.entity_id');
  $query_in_charge->addJoin('INNER', 'field_data_field_state', 'fs', 'n.nid=fs.entity_id');
  $results_in_charge = $query_in_charge->execute()->fetchAllAssoc('nid');
  
  if (isset($results_in_charge)) {
    $tasks_nids_in_charge = array_keys($results_in_charge);
  }
  
  //Retrieve tasks I'm member of
  $query_members = db_select('node', 'n');
  $query_members->fields('n', ['nid', 'type'])
      ->condition('fpic.field_members_target_id', $uid)
      ->condition('fs.field_state_tid', $done_status->tid, '<>')
      ->condition('n.status', 1);
  $query_members->addJoin('INNER', 'field_data_field_members', 'fpic', 'n.nid=fpic.entity_id');
  $query_members->addJoin('INNER', 'field_data_field_state', 'fs', 'n.nid=fs.entity_id');
  $results_members = $query_members->execute()->fetchAllAssoc('nid');
  
  if (isset($results_members)) {
    $tasks_nids_members = array_keys($results_members);
  }
  
  $tasks_nids = array_merge($tasks_nids_in_charge, $tasks_nids_members);

  if (!empty($tasks_nids)) {

    $nids = $tasks_nids;
    $tasks_nodes = node_load_multiple($nids);
    
    //remove task from cards with "Done" status
    foreach($nids as $key=> $nid){
      if($tasks_nodes[$nid]->field_state[LANGUAGE_NONE][0]['tid'] == $done_status->tid){
        unset($tasks_nodes[$nid]);
        unset($nids[$key]);
      }
    }
    
    if($full == FALSE){
      return $nids;
    }

    foreach ($tasks_nodes as $task) {
      $task_details = gofast_kanban_get_task_details($task);
      
      if(in_array($task_details['nid'], $tasks_nids_in_charge)){
        $task_details['first_item_label'] = t("You are the card's responsible", array(), array('gofast:gofast_kanban'));
      }else{
        $task_details['first_item_label'] = t("You are a member of this card", array(), array('gofast:gofast_kanban'));
      }
      
      $tasks[] = $task_details;
    }
  }

  return $tasks;
}


/**
 * Return nbtask per columns
 * @param type $kanban_nid
 * @return array
 */
function gofast_kanban_count_tasks_per_column($kanban_nid) {

  $kanban = node_load($kanban_nid, NULL, TRUE);
  $board_tasks = gofast_kanban_get_tasks($kanban);

  $tasks = array();
  foreach ($board_tasks as $column_tid => $column_tasks) {
    $tasks[$column_tid] = count($column_tasks);
  }
  return $tasks;
}