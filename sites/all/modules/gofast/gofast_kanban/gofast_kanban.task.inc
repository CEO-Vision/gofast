<?php


/**
 * Implements HOOK_form_FORMID_alter()
 * @param type $form
 * @param type $form_state
 */
function gofast_kanban_form_task_node_form_alter(&$form, &$form_state) {
  
  $kanban_nid = $form_state['build_info']['args'][0]->field_board[LANGUAGE_NONE][0]['target_id'];
  $form['field_board'][LANGUAGE_NONE]['#default_value'] = $kanban_nid;
  $form['field_board'][LANGUAGE_NONE]['#type'] = "hidden";
  
  $task_column_id = $form_state['build_info']['args'][0]->field_task_column[LANGUAGE_NONE][0]['tid'];
  $form['field_task_column'][LANGUAGE_NONE]['#default_value'] = $task_column_id;
  $form['field_task_column'][LANGUAGE_NONE]['#type'] = "hidden";

  // No need for first version (might be used with Gantt consolidation)
  unset($form['field_parent_task']);
  unset($form['field_start_date']);
  unset($form['field_finish_date']);

  unset($form['prevent_notify']);
  unset($form['content_visibility']);
  unset($form['og_group_content_ref']);  // automatically added on node_save
  unset($form['field_checklist']);

  //if it's a creation form
  if (empty($form_state['value']['nid'])) {
    unset($form['field_state']);
  }
 
  $form['field_date']['#id'] = 'task_deadline';
  $form['field_date']['#date_is_default'] = 1;
  $form['field_date']['#attributes'] = array('class' => array('d-none', 'gofast_display_none'));

  libraries_load('bootstrap-datetimepicker');
  $form['field_date_picker'] = array(
    '#title' => t('Due date', array(), array('context' => 'gofast_kanban')),
    '#prefix' => '<div class="col-md-6" >',
    '#suffix' => '</div><style>.date-form-element-content-multiline{ padding: 0px; border: none; } </style>',
    '#type' => 'textfield',
    '#weight' => $form['field_person_in_charge']['#id']['#weight']+1,
    '#id' =>  'task_deadline_picker',
    '#attached' => array(
      'js' => array(
        array(
          'data' => drupal_get_path('module', 'gofast_kanban') . '/js/gofast_kanban_datepicker.js',
          'type' => 'file',
          'scope' => 'footer'
        )
      )
    )
  );

  $og_group_content_ref = $form_state['build_info']['args'][0]->og_group_content_ref[LANGUAGE_NONE][0]['target_id'];

  $form['field_members']['#attributes'] = array('class' => array('d-none', 'gofast_display_none'));
  $form['field_members_autocomplete'] = array(
      '#type' => 'textfield',
      '#title' => t('Participant(s)', array(), array('context' => 'gofast_kanban')),
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => FALSE,
      '#autocomplete_path' =>  '/kanban/autocomplete/user/'.$og_group_content_ref,
      '#attributes' => array('class' => array('labelize-autocomplete')),
      '#weight' => $form['field_members']['#weight'],
      '#prefix' => '<div class="col-md-6" >',
      '#suffix' => '</div>'
  );


  $form['field_person_in_charge']['#attributes'] = array('class' => array('d-none', 'gofast_display_none'));
  
  $form['field_person_in_charge_autocomplete'] = array(
      '#type' => 'textfield',
      '#title' => t('Responsible', array(), array('context' => 'gofast_kanban')),
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => FALSE,
      '#autocomplete_path' =>  '/kanban/autocomplete/user-not-readonly/'.$og_group_content_ref ,
//      '#attributes' => array('class' => array('labelize-autocomplete')),
      '#weight' => $form['field_field_person_in_charge']['#weight'],
      '#prefix' => '<div class="col-md-6" >',
      '#suffix' => '</div>'
  );
  
  $form['#group_children']['field_members_autocomplete'] = 'group_row2';
  $form['#group_children']['field_person_in_charge_autocomplete'] = 'group_row1';
  $form['#group_children']['field_date_picker'] = 'group_row1';

  $form['field_labels']['#prefix'] = '<div class="col-md-6" >';
  $form['field_labels']['#suffix'] = '</div>';
  //Disabled while it's not implemented
  unset($form['field_labels']);


  //Set index to max value
  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'task')
      ->fieldCondition('field_task_column', 'tid', $task_column_id)
      ->fieldCondition('field_board', 'target_id', $kanban_nid)
      ->count();

  $result = $query->execute();

  if (empty($result)) {
    $result = 0;
  }
  $form['field_column_index'][LANGUAGE_NONE][0]['value']['#default_value'] = $result;
  $form['field_column_index'][LANGUAGE_NONE][0]['value']['#value'] = $result;
  $form['field_column_index']['#type'] = "hidden";


  $form['field_target_link']['#attributes'] =  array('class' => array('d-none', 'gofast_display_none'));
  $form['field_target_link_autocomplete'] = array(
      '#type' => 'textfield',
      '#title' => t('Attachment(s)', array(), array('context' => 'gofast_kanban')),
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => FALSE,
      '#autocomplete_path' => 'gofast/documents-autocomplete',
      '#attributes' => array('class' => array('labelize-autocomplete')),
      '#weight' => $form['field_target_link']['#weight'],
  );
  
  // Disable "Show row weigth"                                                                                         
  $javascript = &drupal_static('drupal_add_js', array());
  unset($javascript['misc/tabledrag.js']);
  // Prevent it from being enabled later.                                                                                        
  $tabledrag_added = &drupal_static('drupal_add_tabledrag');
  $tabledrag_added = TRUE;
  
  
  //Removed title validator
  if( ($key = array_search('gofast_form_validate_title',$form['#validate']) ) !== FALSE ){
    unset ($form['#validate'][$key]);
  }
  array_unshift($form['#validate'], gofast_kanban_form_validate_title);
  
  // add validate function
  $form['#validate'][] = 'gofast_kanban_task_node_form_validate';

  //Force modal overflow to auto
  $form['#suffix'] = '<style>#modal-content { overflow: auto !important; } .gf-kanban-deadline-hide-time div.form-type-textfield:nth-of-type(2){ display: none;}</style>';
}

/**
 * Validate handler. 
 * 
 *  Set a form error if a node title contains invalid title.
 */
function gofast_kanban_form_validate_title(&$form, &$form_state) {
  $node = $form_state['node'];
  $title = &$form_state['values']['title'];

  // Always strip whitespaces from the title.
  $title = trim($title);

  // All content types are subject to the same validator.
  if (!gofast_kanban_validate_title($title)) {
    form_set_error('title', t('Title contains illegals characters or an invalid name.', array(), array('context' => 'gofast')));
    drupal_set_message(t('Title contains illegals characters or an invalid name.', array(), array('context' => 'gofast')), 'error');
  }
  
}


/**
 * 
 * @param type $str
 * @return type
 */
function gofast_kanban_validate_title($str) {
  
  $invalid_chars = array('<', '>', '*', '|', '"', '\\');
  
  // Matches any string containing a single or more invalid chars.
  $chars = '(.*[' . preg_quote(implode('', $invalid_chars), '/') . ']+.*)';

  // Build the pattern, use 'i' modifier for case insensitive matches (Windows
  // name restrictions are case insensitive).
  $pattern = "/{$chars}/i";

  /**
   * @todo: catch & return matches so that validate handlers can set error details. 
   */
  return !preg_match($pattern, $str);
}


/**
 * 
 * @param type $form
 * @param type $form_state
 */
function gofast_kanban_form_comment_node_task_form_alter(&$form, &$form_state) {


  $comment = $form_state['comment'];

//themed form
  $form['#theme'] = array('kanban_comment_form');
  $form['#action'] = '/kanban/task/' . $comment->nid . '/add/comment';

  $form['#attributes']['data-taskId'] = $comment->nid;


//keep only ajax modal action
  unset($form['actions']);
}

/**
 * 
 * @global type $user
 * @param type $node
 * @param type $status
 * @return type
 */
function gofast_kanban_task_add($js, $node, $status = NULL){
    
  ctools_include('ajax');
  ctools_include('modal');
  ctools_modal_add_js();
  
  $type = 'task';
  
  if(!$js){
    drupal_goto('node/add/'.$type, array('query' => array($node, $status)));
  }
  
    
  global $user;
  
  //Set OG group for the task (used to bind task to calendar)
  $kanban_og_group_ref = node_load($node)->og_group_content_ref;
  $og_group_ref_nid = $kanban_og_group_ref;
  
  $field_board = array('und' => array('0' => array('target_id' => $node)));
  $field_status = array('und' => array('0' => array('tid' => $status)));
  
  $task_node = (object) array('uid' => $user->uid, 'type' => $type, 'field_board' => $field_board, 'field_task_column' => $field_status, 'og_group_content_ref' => $og_group_ref_nid);
  
  $form_state = array(
    'reset_html_ids' => TRUE,
    'build_info' => array(
      'args' => array(
         (object) $task_node 
      )
    ),
    'ajax' => TRUE,
    'no_redirect' => TRUE,
    're_render' => FALSE,
    'title' => null
  );
  
  $commands = ctools_modal_form_wrapper($type.'_node_form', $form_state);
  
  if(!empty($form_state['executed'])) {
    $commands[] = ctools_modal_command_dismiss();
  }
 
  print ajax_render($commands);
  return;  
}


/**
 * 
 * @param type $node
 */
function gofast_kanban_task_view($js, $node){

//  ctools_include('ajax');
//  ctools_include('modal');
//  ctools_modal_add_js();
  
  global $user;
  
  $comment_task = array('nid' => $node, 'pid' => 0, 'uid' => $user->uid);
    
  $form_state = array(
    'reset_html_ids' => TRUE,
    'build_info' => array(
      'args' => array(
         (object) $comment_task 
      )
    ),
    'ajax' => TRUE,
    'title' => NULL
  );
  
  $comment_form = drupal_build_form('comment_node_task_form', $form_state);
  
  $todo = array('cid' => gofast_kanban_get_task_checklists_raw($node, FALSE)[0], 'ciid' => NULL);
  $form_state_todo = array(
    'reset_html_ids' => TRUE,
    'build_info' => array(
      'args' => array(
         (object) $todo 
      )
    ),
    'ajax' => TRUE,
    'title' => NULL
  );
  
  $todo_form = drupal_build_form('gofast_kanban_checklistItem_form', $form_state_todo );
  
  $task_activities = gofast_kanban_get_task_activities($node);
  
  $task_todolists = gofast_kanban_get_task_checklists($node);
  
  $task_node = node_load($node);
  
  $output=theme('kanban_task_details', array(
        'task' => $task_node, 
        'comment_form' => $comment_form,
        'todo_form' => $todo_form,
        'task_todolists' => $task_todolists,
        'task_activities' => $task_activities));
  
  print $output;
  return;
}



function gofast_kanban_task_update($nid){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);
    
  $args = array(
      'label' => array('filter' => FILTER_UNSAFE_RAW),
      'person-in-charge' => array('filter' => FILTER_VALIDATE_INT),
      'deadline' =>  array('filter' => FILTER_VALIDATE_INT),
      'members' =>  array('filter' => FILTER_SANITIZE_ENCODED, 'flags' => FILTER_FORCE_ARRAY),
      'attachements' =>  array('filter' => FILTER_SANITIZE_ENCODED, 'flags' => FILTER_FORCE_ARRAY),
   //   'labels' =>  array('filter' => FILTER_SANITIZE_ENCODED, 'flags' => FILTER_FORCE_ARRAY),
      'description' =>  array('filter' => FILTER_UNSAFE_RAW),
      'content-visibility' =>  array('filter' => FILTER_UNSAFE_RAW),
      'status' =>  array('filter' => FILTER_VALIDATE_INT)
  );
  $post_variable = filter_input_array(INPUT_POST, $args, FALSE);
  
  $task = node_load($nid);
  $node_wrapper = entity_metadata_wrapper('node', $task);

  if (isset($post_variable['label']) && !empty($post_variable['label'])) {
    $task->title =  filter_xss($post_variable['label']);
    $node_wrapper->save();
    
  } elseif (isset($post_variable['person-in-charge']) ) {
    
    if(strlen($post_variable['person-in-charge']) < 1){
      $node_wrapper->field_person_in_charge->set(NULL);
    }else{
      $node_wrapper->field_person_in_charge->set($post_variable['person-in-charge']);
    }
    
    $node_wrapper->save();
    
  } elseif (isset($post_variable['deadline']) ) {

    $node_wrapper->field_date->set(!empty($post_variable['deadline'])? $post_variable['deadline'] : NULL);    
    $node_wrapper->save();
    
  } elseif (isset($post_variable['members']) ) {
    
//    $new_members = array(); 
//    foreach($post_variable['members'] as $member){
//      $temp = explode('_', $member);
//      if(count($temp) > 1){
//        $new_members[] = $temp[0];
//      }
//    }
//    $node_wrapper->field_members->set($new_members);
    if( count($post_variable['members']) > 0 && $post_variable['members'][0] != ''){
      $node_wrapper->field_members->set($post_variable['members']);
    }else{
      $node_wrapper->field_members->set(array());
    }

    $node_wrapper->save();
    
  } elseif (isset($post_variable['attachements']) ) {
    
    if( count($post_variable['attachements']) > 0 && $post_variable['attachements'][0] != ''){
      $node_wrapper->field_target_link->set($post_variable['attachements']);
    }else{
      $node_wrapper->field_target_link->set(array());
    }
    $node_wrapper->save();
    
//  } elseif (isset($post_variable['labels']) && !empty($post_variable['labels'])) {
//    $$node_wrapper->field_labels->set($post_variable['labels']);
//    $node_wrapper->save();
//    
  } elseif (isset($post_variable['description']) ) {
    
//watchdog('gofast_kanban','description = '.$post_variable['description'], array(), WATCHDOG_DEBUG);

    //Filters HTML content that is not in the following array. Removes HTML attributes like style - (GOFAST-6551 activating ACF (see commit on features) to keep a protection against XSS)
    //$desc_allowed_tags = array('a', 'em', 'strong', 'u', 'blockquote', 'img', 'ul', 'ol', 'span', 'p', 's');
    //$node_wrapper->body->set(array('value' =>  filter_xss($post_variable['description'], $desc_allowed_tags)));

      $node_wrapper->body->set(array('value' =>  str_replace(array("\r\n", "\n", "\t"), "", $post_variable['description'])));
      $node_wrapper->save();

  } elseif (isset($post_variable['content-visibility']) && !empty($post_variable['content-visibility'])) {

    if ($post_variable['content-visibility'] == "on") {
      $node_wrapper->content_visibility->set(0);
    } else {
      $node_wrapper->content_visibility->set(1);
    }
    $node_wrapper->save();
    
  } elseif (isset($post_variable['status']) ) {

    $node_wrapper->field_state->set(!empty($post_variable['status'])? $post_variable['status'] : NULL);    
    $node_wrapper->save();

  }


//  node_save($task); 
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}


/**
 * Delete (unpublish) a task
 * @param type $nid
 */
function gofast_kanban_task_delete($nid){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $nid), WATCHDOG_DEBUG);

  $task = node_load($nid);
  $task->status = 0;
  node_save($task);
  
  gofast_kanban_set_tasks_context("node", "kanban_tasks_updated", "TRUE");
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}



/**
 * 
 * @param type $nid
 * @param type $column
 * @param type $index
 */
function gofast_kanban_task_update_column($nid, $column) {

  $index = $_GET['index'];

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid], column=[%column], index=[%index], ', array('%name' => __FUNCTION__, '%nid' => $nid, '%column' => $column, '%index' => $index), WATCHDOG_DEBUG);

  $task = node_load($nid);
  $node_wrapper = entity_metadata_wrapper('node', $task);

  $old_column = $node_wrapper->field_task_column->value()->tid;

  if ($column !== $node_wrapper->field_task_column->value()->tid) {
    $node_wrapper->field_task_column->set($column);
    $node_wrapper->save();
  }

  $_POST['technically_save'] = TRUE;
 
  gofast_kanban_task_update_position($nid, $index, $old_column->tid);


  
}

/**
 * 
 * @param type $nid
 * @param type $column
 * @param type $from_task
 * @param type $from_index
 * @param type $increment
 */
function gofast_kanban_task_reorder_column($nid, $column, $from_task, $from_index, $to_index = NULL, $increment = TRUE) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $tasks_nids = gofast_kanban_task_get_task_to_reorder($nid, $column, $from_task, $from_index, $to_index);

  if (!empty($tasks_nids)) {
    $update_query = db_update('field_data_field_column_index');

    if ($increment == TRUE) {
      $update_query->expression('field_column_index_value', 'field_column_index_value + :increment', array(':increment' => 1));
    } else {
      $update_query->expression('field_column_index_value', 'field_column_index_value - :increment', array(':increment' => 1));
    }

    $update_query->condition('entity_type', 'node')
        ->condition('bundle', 'task')
        ->condition('entity_id', $tasks_nids, 'IN');

    $update_query->execute();
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * 
 * @param type $board_nid
 * @param type $column_id
 * @param type $from_task
 * @param type $from_index
 * @param type $to_index
 * @return type
 */
function gofast_kanban_task_get_task_to_reorder($board_nid, $column_id, $from_task, $from_index, $to_index) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START  args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  $tasks_nids = array();

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'task')
      ->entityCondition('entity_id', $from_task, '<>')
      ->fieldCondition('field_task_column', 'tid', $column_id)
      ->fieldCondition('field_board', 'target_id', $board_nid)
      ->fieldCondition('field_column_index', 'value', $from_index, '>=');

  if ($to_index !== NULL) {
    $query->fieldCondition('field_column_index', 'value', $to_index, '<=');
  }

  $results = $query->execute();

  if (isset($results)) {
    $tasks_nids = array_keys($results['node']);
  }

//watchdog('gofast_kanban', 'nb task to reorder => %nb_task]', array('%nb_task' => count($tasks_nids)), WATCHDOG_DEBUG);


  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  return $tasks_nids;
}

/**
 * 
 * @param type $nid
 * @param type $index
 * @param type $old_column
 */
function gofast_kanban_task_update_position($nid, $index, $old_column = NULL) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  $task = node_load($nid);
  $node_wrapper = entity_metadata_wrapper('node', $task);

  $old_index = $node_wrapper->field_column_index->value();

  $node_wrapper->field_column_index->set($index);
  $node_wrapper->save();


  if (NULL !== $old_column) {
    //update all other node in the same column
    gofast_kanban_task_reorder_column($node_wrapper->field_board->value()->nid, $node_wrapper->field_task_column->value()->tid, $nid, $index);

    //Update all node in old task column
    gofast_kanban_task_reorder_column($node_wrapper->field_board->value()->nid, $old_column, $nid, $index, NULL, FALSE);
  } else {

    // decrease task priority
    $from_index = $index;
    $to_index = $old_index;
    $increment = TRUE;


    if ($index > $old_index) { // increase task priority
      $from_index = $old_index;
      $to_index = $index;
      $increment = FALSE;
    }
    //update all other node in the same column
    gofast_kanban_task_reorder_column($node_wrapper->field_board->value()->nid, $node_wrapper->field_task_column->value()->tid, $nid, $from_index, $to_index, $increment);
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * Implements HOOK_form_validate
 * @param type $form
 * @param type $form_state
 */
function gofast_kanban_task_node_form_validate($form, &$form_state) {

  $person_in_charge = trim($form_state['input']['field_person_in_charge_autocomplete']);
  $raw_uid = NULL;
  preg_match('(<\d+>)', $person_in_charge, $raw_uid);
  if( !empty($raw_uid) && FALSE !== $raw_uid){
     preg_match('(\d+)', $raw_uid[0], $person_in_charge_uid);    
     $form_state['values']['field_person_in_charge'][LANGUAGE_NONE][0] = array('target_id' => $person_in_charge_uid[0]);   
  }
   
  $json_list_assignees = explode(' ', trim($form_state['input']['edit-' . str_replace("_", "-", $form['field_members_autocomplete']['#name']) . '-hidden-values']));
  foreach ($json_list_assignees as $assignee) {
    $form_state['values']['field_members'][LANGUAGE_NONE][] = array('target_id' => $assignee);
  }
  
  $link_values = explode(' ', trim($form_state['input']['edit-' . str_replace("_", "-", $form['field_target_link_autocomplete']['#name']) . '-hidden-values']));
  foreach ($link_values as $link) {
    $form_state['values']['field_target_link'][LANGUAGE_NONE][] = array('target_id' =>  $link);
  }

  //Formatting body field for WYSIWYG - GOFAST-6789
  $form_state['values']['body'][LANGUAGE_NONE][0]['value'] = str_replace(array("\r\n", "\n", "\t"), "", $form_state['values']['body'][LANGUAGE_NONE][0]['value']);

  $errors = form_get_errors($form);
  if(!empty($errors)){
      //This form hasn't pass the validation, print the errors in toasts and exit
      drupal_get_messages();
      $commands = [];
      
      foreach($errors as $error){
          $commands[] = gofast_command_toast_message($error, "warning");
      }
      
      print ajax_render($commands);
      exit;
  }
}

function gofast_kanban_task_add_comment($nid) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);


  global $user;
  
  $post_variable = filter_input_array(INPUT_POST);

  //Create the comment
  $comment = new stdClass();

  $comment->nid = $nid;
// $comment->cid = 0; // leave it as is
  $comment->pid = 0;
  $comment->uid = $user->uid;
  $comment->name = $user->name;
  $comment->created = time();
  $comment->status = COMMENT_PUBLISHED;
  $comment->language = LANGUAGE_NONE;
  $comment->subject = '';
  $comment->comment_body[$comment->language][0]['value'] = filter_xss($post_variable['comment_body'][LANGUAGE_NONE][0]['value']);
  $comment->comment_body[$comment->language][0]['format'] = 'full_html';

  comment_submit($comment); // saving a comment
  comment_save($comment);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * 
 * @param type $cid
 */
function gofast_kanban_task_update_comment($cid) {
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  $post_variable = filter_input_array(INPUT_POST);
  
  $comment = comment_load($cid);
  
  $comment->changed = time();
  
  $comment->comment_body[$comment->language][0]['value'] = filter_xss($post_variable['comment_body']);
  $comment->comment_body[$comment->language][0]['format'] = 'full_html';

  comment_save($comment);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

}


/**
 * Delete a comment
 * @param type $cid
 */
function gofast_kanban_task_delete_comment($cid) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  $comment = comment_load($cid);
  $task_id = $comment->nid;

  comment_delete($cid);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  print $task_id;
  exit();
}


/**
 * Implement HOOK_node_presave()
 * @global type $user
 * @param type $node
 */
function gofast_kanban_node_presave($node){
  if ($node->type === 'task') {

    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => 'node => '.$node->nid), WATCHDOG_DEBUG);

    if(! isset($node->nid)){
      //Reset uid due to Iframe constrainte
      global $user;
      $node->uid = $user->uid;
      $todo_status = $term = array_shift(taxonomy_get_term_by_name('To Do', 'state'));
      $node->field_state[LANGUAGE_NONE][0]['tid'] = $todo_status->tid; // put defautl state to "ToDo"
    }
    
    // Only if node already exists, else let it be done by  HOOK_node_insert
    if(isset($node->nid)){
      //check if we must send an immediate notification for some users 
      gofast_kanban_send_immediate_notification($node);
    }   
    $timer_stop = microtime(true);
       
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  }
}
/**
 * Implement HOOK_node_insert()
 * @param Node $node
 */
function gofast_kanban_node_insert($node) {
  if ($node->type === 'task') {

    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => 'node => '.$node->nid ), WATCHDOG_DEBUG);

    $checklist = entity_create('checklist', array('label' => 'Todolist'));
    $checklist->task_nid = $node->nid;
    $checklist->save();
    
    //check if we must send an immediate notification for some users
    gofast_kanban_send_immediate_notification($node);
    
    $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  }
}

/**
 * Implements HOOK_override_og_permissions_node_access()
 * @param type $node
 * @param type $op
 * @param type $account
 */
function gofast_kanban_override_og_permissions_node_access($node, $op, $account) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[node => %nid , op => %op, account => %account]', array('%name' => __FUNCTION__, '%nid' => is_string($node) ? $node : $node->nid, '%op' => $op, '%account' => $account->uid ), WATCHDOG_DEBUG);

  $access = NODE_ACCESS_IGNORE;
  
  $type = is_string($node) ? $node : (is_array($node) ? $node['type'] : $node->type);
  if ($type == 'task' && $op == 'update') {
    $members = $node->field_members[LANGUAGE_NONE];
    foreach ($members as $key => $member) {
      if ($account->uid == $member['target_id']) {
        $access = NODE_ACCESS_ALLOW;
      }
    }
  }
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $access;
}

function gofast_kanban_task_add_todo($nid) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);


  $cids = gofast_kanban_get_task_checklists_raw($nid, FALSE);
  //while there is only 1 checklist by task : get first 
  $cid = $cids[0];

  $post_variable = filter_input_array(INPUT_POST);
  $label = filter_xss($post_variable['label']);
  $attrs = array();

  gofast_kanban_checklistItem_create($cid, $label, $attrs);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}


function gofast_kanban_task_update_todo($ciid) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);
  
  $post_variable = filter_input_array(INPUT_POST);
  $attrs = array();
  
  if(isset($post_variable['label']) && ! empty($post_variable['label'])){
    $attrs['label'] = filter_xss($post_variable['label']);
  }
  
  if (isset($post_variable['person-in-charge']) && !empty($post_variable['person-in-charge'])) {
    $attrs['uid'] = $post_variable['person-in-charge'];
  } else {
    $attrs['uid'] = NULL;
  }

  if( isset($post_variable['deadline'] ) ){
    //convert date into timestamp
    if( !empty($post_variable['deadline']) ){
       $attrs['deadline'] = $post_variable['deadline'];
    }else{
      $attrs['deadline'] = NULL;
    }
       
   
  }
  
  gofast_kanban_checklistItem_udpate($ciid, $attrs);
 
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * 
 * @param type $ciid
 * @param type $status_id
 */
function gofast_kanban_task_update_todo_status($ciid, $status) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  $attrs = array('status' => $status);
  gofast_kanban_checklistItem_udpate($ciid, $attrs);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  exit();
}

/**
 * 
 * @param type $ciid
 */
function gofast_kanban_task_delete_todo($ciid) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  gofast_kanban_checklistItem_delete($ciid);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  exit();
}

function gofast_kanban_task_node_form_submit($form, &$form_state) {
  gofast_kanban_set_tasks_context("node", "kanban_tasks_updated", "TRUE");
}


/**
 * 
 * @global type $user
 * @param type $nid
 * @param type $account
 */
function gofast_kanban_task_can_comment($nid, $account = NULL){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START args=[%args]', array('%name' => __FUNCTION__, '%args' => implode(', ', func_get_args())), WATCHDOG_DEBUG);

  if (!isset($account)) {
    global $user;
    $account = $user;
  }
  
  $canComment = FALSE;
  
  //check if user is assigne on task's checklistItem
  $checklists = gofast_kanban_get_task_checklists($nid);
  foreach ($checklists as $key=> $checklist){
    $checklistItems = gofast_kanban_get_task_checklist_item($checklist['cid']);
    foreach($checklistItems as $key => $item){
      if($account->uid == $item->uid){
        $canComment = TRUE;
      }
    }
  }  
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $canComment;
}