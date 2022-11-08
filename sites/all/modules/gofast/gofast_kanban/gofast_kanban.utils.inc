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
 * @return type
 */
function gofast_kanban_get_columns($kanban) {
  $kanban_columns = array();
  foreach ($kanban->field_board_columns['und'] as $key => $tid) {
    $tid = $tid['tid'];
    $kanban_columns[$tid] = array(
          'title' => i18n_taxonomy_localize_terms(taxonomy_term_load($tid))->name,
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
 * @return type
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
      $tasks_nids = array_keys($results['node']);
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

  $deadline_date = null;
  if (!empty($task->field_date[LANGUAGE_NONE][0]['value'])) {
    $deadline_date = new DateTime($task->field_date[LANGUAGE_NONE][0]['value']);
    $task_status = taxonomy_term_load($task->field_state[LANGUAGE_NONE][0]['tid'])->name;
    $task_details['deadline'] = format_date($deadline_date->getTimestamp(),  'short_without_hours');
    $task_details['deadline_color_indicator']= gofast_kanban_get_task_deadline_decorator($deadline_date, $task_status );
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
  
  $task_details['attachments']= array();
  foreach ($task->field_target_link[LANGUAGE_NONE] as $key => $elt){
    $task_details['attachments'][] = $elt['target_id'];
  }


//  $task_details['content-visibility'] = '';
//  if($task->field_content_visibility[LANGUAGE_NONE][0]['value'] == 0){
//    $task_details['content-visibility'] = "checked='checked'";
//  }
//  
  
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
  if(count ($first_item_obj) == 0){
     $first_item = t("You are the card's responsible", array(), array('gofast_kanban'));
  }else{
     $first_item = $first_item_obj->label;
  }
 
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $first_item;
  
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

  foreach (array_keys($event_details) as $key) {
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
 * @return array() $items
 */
function gofast_kanban_get_user_checklistItems($uid = false, $full = FALSE, $filters = array()){
    global $user;
    if($user->uid == 0){
        return array();
    }

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : uid=[%uid] ', array('%name' => __FUNCTION__, '%uid' => $uid), WATCHDOG_DEBUG);
  
  $items = array();
  
  $query = db_select('gofast_kanban_checklist_item', 'ci')
     ->fields('ci', array('ciid', 'cid', 'label', 'deadline', 'uid', 'status'));

  //Do not include tasks from Card  wiwth "Done" status
  if($full){
    $query->leftJoin('gofast_kanban_checklist', 'c', 'ci.cid = c.cid');
//    $query->leftJoin('field_data_field_state', 's', "s.entity_id = c.task_nid AND s.entity_type = 'node' ");
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

  $results = $query->execute()->fetchAll();
  if (count($results) > 0) {
     $items = $results;
  } 
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
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
 * Return all tasks assigne to the given user
 * @param type $uid
 * @param type $full
 * @return type
 */
function gofast_kanban_get_user_tasks($uid, $full = FALSE){
    
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : uid=[%uid] ', array('%name' => __FUNCTION__, '%uid' => $uid), WATCHDOG_DEBUG);
  
  $tasks = array();
  $tasks_nids = array();
  
  $done_status = array_shift(taxonomy_get_term_by_name('Done', 'state'));
  
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'task')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_person_in_charge', 'target_id', $uid)
      ->fieldCondition('field_state', 'tid', $done_status->tid, '<>');
    //  ->fieldCondition('field_members', 'target_id', array($uid) , 'IN');
  $query->fieldOrderBy('field_date', 'value', 'ASC');
  $results = $query->execute();
  
  if (isset($results)) {
    $tasks_nids = array_keys($results['node']);
  }
  
  // Retreive tasks for which the user is assigned to checklist item
  $filters = array(
    0 => array('name' => 'ci.status', 'value' => 0, 'operator' => '=')
  );


  $checklist_for_user = gofast_kanban_get_user_checklistItems($uid, TRUE, $filters );
  if (!empty($checklist_for_user)) {
    
    foreach ($checklist_for_user as $item) {
      $tasks_nids[] = $item->task_nid;
    }

    $query2 = new EntityFieldQuery();
    $query2->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'task')
      ->propertyCondition('status', 1)
      ->propertyCondition('nid', $tasks_nids, 'IN');
    
  // Removed due to EntityFieldQuery::fieldOrderby() limitation => https://www.drupal.org/project/drupal/issues/1662942
  // $query2->fieldOrderBy('field_date', 'value', 'ASC');
    
    $final_results = $query2->execute();
  }else{
    $final_results = $results;
  }

  if (!empty($tasks_nids)) {

    $nids = array_keys($final_results['node']);
    
    if($full == FALSE){
      return $nids;
    }
    
    $tasks_nodes = node_load_multiple($nids);

    foreach ($tasks_nodes as $task) {
      $tasks[] = gofast_kanban_get_task_details($task);
    }
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $tasks;
}


/**
 * Return nbtask per columns
 * @param type $kanban_nid
 * @return type
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

/*
function gofast_kanban_get_looper_css(){
    
  $css = array();
  $css[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_CSS . 'theme.css';
  $css[] = drupal_get_path('module', 'gofast') . '/css/font-awesome.css';
  $css[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'open-iconic/css/open-iconic-bootstrap.min.css';
  $css[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'tributejs/tribute.css';
  $css[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'simplemde/simplemde.min.css';
  $css[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'flatpickr/flatpickr.min.css';
  
  return $css;
}


function gofast_kanban_get_looper_js(){
  
  $js = array();
  
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'jquery/jquery.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'bootstrap/js/popper.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'bootstrap/js/bootstrap.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'stacked-menu/stacked-menu.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'pace/pace.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'perfect-scrollbar/perfect-scrollbar.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'sortablejs/Sortable.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'tributejs/tribute.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'simplemde/simplemde.min.js';
  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_VENDOR . 'flatpickr/flatpickr.min.js';

  $js[] = drupal_get_path('module', 'gofast_kanban') . LOOPER_THEME_DIR_JS . 'theme.min.js';
  
  return $js;
}
*/
