<?php

/**
 * 
 */
class CheckListEntity extends Entity {

  // Nothing for now

  protected function defaultUri() {
    // parent::defaultUri();
    return array('path' => 'checklist/' . $this->identifier());
  }

  const CHECKLIST_ITEM_STATUS_ALL = 'ALL';
  const CHECKLIST_ITEM_STATUS_COMPLETED = '1';
  const CHECKLIST_ITEM_STATUS_UNCOMPLETED = '0';

  /**
   * Return progress in percentage of the checklist
   * @return type
   */
  public function getProgress() {
    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

    $progress = 0;

    if (count($this->getItems()) > 0) {
      $progress = count($this->getItems($this::CHECKLIST_ITEM_STATUS_COMPLETED)) / count($this->getItems()) * 100;
    }

    $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
    
    return number_format($progress, 0);
  }

  /**
   * Return Items of the Checklist (all status by default
   * Can be filtered by status ( CHECKLIST_ITEM_STATUS_COMPLETED or CHECKLIST_ITEM_STATUS_UNCOMPLETED)
   * @param type $status
   * @return array
   */
  public function getItems($status = CheckListEntity::CHECKLIST_ITEM_STATUS_ALL) {
    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);
    global $user;
    if($user->uid == 0){
        return array();
    }

    $items = array();

    $query = db_select('gofast_kanban_checklist_item', 'ci')
        ->fields('ci', array('ciid', 'label', 'deadline', 'uid', 'status'))
        ->condition('cid', $this->identifier(), '=');

    if ($status == $this::CHECKLIST_ITEM_STATUS_COMPLETED) {
      $query->condition('status', $this::CHECKLIST_ITEM_STATUS_COMPLETED, '=');
    } else if ($status == $this::CHECKLIST_ITEM_STATUS_UNCOMPLETED) {
      $query->condition('status', $this::CHECKLIST_ITEM_STATUS_UNCOMPLETED, '=');
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

}

/**
 * Extending the EntityAPIController for the UserList entity.
 */
class CheckListEntityController extends EntityAPIController {

  /**
   * Entity Checklist save
   * @param type $entity
   * @param \DatabaseTransaction $transaction
   */
  public function save($entity, \DatabaseTransaction $transaction = NULL) {

    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

    parent::save($entity, $transaction);

    $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  }

  /**
   * Entity Userlist delete
   * @param type $ids
   * @param \DatabaseTransaction $transaction
   */
  public function delete($ids, \DatabaseTransaction $transaction = NULL) {
    $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);


    $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  }

}

function gofast_kanban_mychecklist_load($cid) {   
  return entity_load_single('checklist', $cid);
}

function gofast_kanban_checklist_load_multiple($cids = array(), $conditions = array()) {
  return entity_load('checklist', $cids, $conditions);
}

/**
 * Implements hook_entity_info().
 */
function gofast_kanban_entity_info() {

  $info = array();

  $info['checklist'] = array(
      'label' => t('CheckList'),
      'base table' => 'gofast_kanban_checklist',
      'entity keys' => array(
          'id' => 'cid',
      ),
      'module' => 'gofast_kanban',
      'entity class' => 'CheckListEntity', //'Entity',
      'controller class' => 'CheckListEntityController', //'EntityAPIController', 
      //  'access callback' => 'gofast_kanban_access_callback',
      'uri callback' => 'entity_class_uri',
//      'admin ui' => array(
//          'path' => 'admin/userlists',
//          'controller class' => 'EntityDefaultUIController',
//      ),
      'fieldable' => FALSE, //do not allow the checklist entity to have field attached
      'bundles' => array(
          'checklist' => array(
              'label' => t('CheckList'),
              'admin' => array(
                  'path' => 'admin/checklist',
              )
          )
      ),
      'views controller class' => 'EntityDefaultViewsController',
  );

  /*
    $info['checklist_item'] = array(
    'label' => t('CheckList Item'),
    'base table' => 'gofast_kanban_checklist_item',
    'entity keys' => array(
    'id' => 'ciid',
    'label' => 'name',
    ),
    'module' => 'gofast_kanban',
    'entity class' => 'CheckListItemEntity', //'Entity',
    'controller class' => 'CheckListItemEntityController', //'EntityAPIController',
    //  'access callback' => 'gofast_kanban_access_callback',
    'uri callback' => 'entity_class_uri',
    'admin ui' => array(
    'path' => 'admin/userlists',
    'controller class' => 'EntityDefaultUIController',
    ),
    'fieldable' => TRUE, //allow the userlist entity to have field attached
    'bundles' => array(
    'checklist' => array(
    'label' => t('CheckList Item'),
    'admin' => array(
    'path' => 'admin/userlists',
    )
    )
    ),
    'views controller class' => 'EntityDefaultViewsController',
    );
   */

  return $info;
}

/**
 * 
 * @param type $form
 * @param type $form_state
 * @param type $cid
 * @return type
 */
function gofast_kanban_checklistItem_form($form, &$form_state) {

  $checklistItem = $form_state['build_info']['args'][0];
  
  $form['#theme'] = array('kanban_checklist_item_form');
  
  //checklist item ciid
  $form['ciid'] =array(
      '#type' => 'hidden',
      '#value' => $checklistItem->ciid
  );
  
  $form['label'] = array(
      '#type' => 'textfield',
      '#title' => t('Label', array(), array('context' => 'gofast_kanban')),
      '#size' => 60,
      '#maxlength' => 128,
      '#required' => TRUE,
  );

  $form['cid'] = array(
      '#type' => 'hidden',
      '#value' => $checklistItem->cid
  );

  $form['deadline'] = array(
      '#type' => 'textfield',
      '#title' => t('Deadline', array(), array('context' => 'gofast_kanban')),
      '#default_value' => new DateTime('TOMORROW'),
      '#required' => FALSE
  );

  $form['assignee'] = array(
      '#type' => 'textfield',
      '#title' => t('Assignee', array(), array('context' => 'gofast_kanban')),
      '#autocomplete_path' => 'gofast_user_autocomplete',
      '#attributes' => array('class' => array('labelize-autocomplete')),
  );
  
  $checklist = gofast_kanban_mychecklist_load($checklistItem->cid); 
  $form['#attributes']['data-taskId'] = $checklist->task_nid;
  
  $form['#action'] = '/kanban/task/'.$checklist->task_nid.'/add/todo';
  
  
  return $form;
}

/**
 * Create a new checklist
 * @param type $nid
 * @param type $label
 * @param type $attrs
 */
function gofast_kanban_checklist_create($nid, $label, $attrs = array()) {
  
}

function gofast_kanban_checklist_update($cid, $attrs = array()) {
  
}

function gofast_kanban_checklist_delete($cid) {
  
}

function gofast_kanban_checklistItem_create($cid, $label, $attrs = array()) {
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $checklist = gofast_kanban_mychecklist_load($cid);

  $node = node_load($checklist->task_nid);
  $values = gofast_kanban_get_task_checklists($node->nid);

  $query = db_insert('gofast_kanban_checklist_item')
      ->fields( array(
        'cid'=> $cid,
        'label' => $label,
        'deadline' => (isset($attrs['deadline'])? $attrs['deadline']: NULL ),
        'uid' => (isset($attrs['uid'])? $attrs['uid']: NULL ),         
      ));
  
  $id = $query->execute();
  
  //Save entities ( audit and notificiation)
  gofast_kanban_ext_create_checklistsave_entity($node,$values);
  
  $timer_stop = microtime(true);
  return $id;
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * @param type $ciid
 * @param type $attrs arrays, each key should match a table column 
 */
function gofast_kanban_checklistItem_udpate($ciid, $attrs = array()) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);
  
  //save values before save ( for audit and notification)
  $node = gofast_kanban_get_task_from_checklistItem($ciid,true);
  $values = gofast_kanban_get_task_checklists($node->nid);
  $old_values_items = array();
  if(count($values[0]["items"]) > 0){
      foreach($values[0]["items"] as $item){
          $old_values_items[$item->ciid] = $item;
      }
  }
  
  //format timestamp for deadline
  if(isset($attrs['deadline'])){
    $attrs['deadline'] = intdiv($attrs['deadline'], 1000);
  }
  
  if (count($attrs) > 0) {     
    $query = db_update('gofast_kanban_checklist_item');
    $query->fields($attrs);
    $query->condition('ciid', $ciid);
    $query->execute();
  }
  
  //Save entities ( audit and notificiation)
  gofast_kanban_ext_create_checklistsave_entity($node,$values);
  
  //compare if there is a new assignee
  $new_values = gofast_kanban_get_task_checklists($node->nid);
  //first, reformate the list
  
  $new_values_items = array();
  if(count($new_values[0]["items"]) > 0){
      foreach($new_values[0]["items"] as $item){
          $new_values_items[$item->ciid] = $item;
      }
  }
 
  global $user;

  if (count($new_values_items) > 0) {
        $n = variable_get('kanban_notifications',array());
         if(!isset($n[$node->nid]))$n[$node->nid] = array(); 
        if(!isset($n[$node->nid]['items'])){
            $n[$node->nid]['items']= $old_values_items;
            if(!isset($n[$node->nid]['participants']))$n[$node->nid]['participants'] = array(); 
        }
        if(!in_array($user->uid,$n[$node->nid]['participants'])){
            $n[$node->nid]['participants'][]=$user->uid;
        }
        $n[$node->nid]['last_update']=time();
        variable_set('kanban_notifications', $n);
  }
      
  /*    
    foreach ($new_values_items as $ciid => $item) {
      //do not send notification if the assignee is the current user
      if ($item->uid !== $user->uid) {
        
        if ($item->uid != $old_values_items[$ciid]->uid) {
           
            
            $account = $RecipUser = user_load($item->uid);
            $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));

            $userName = gofast_user_display_name($account);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);

           
            $subject = t('Task: You are assigned on "!title_todo" of the "!title" task', array('!title_todo'=>$item->label,'!title'=>$node->title), $l);

            $title = t('New assignation on a checklist item', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
           
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('You have been assigned to a checklist element of the card : ', array(), $l);
            $responsible = user_load($node->field_person_in_charge[LANGUAGE_NONE][0]["target_id"]);
            $username = theme('username', array('account' => $responsible, 'popup' => FALSE, 'link' => $options['link']));
            $description_detail = "<h3>".t('Responsible', array(), $l)."</h3>".$username;          
            $description_detail .= "<h3>".t('Card description', array(), $l)."</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>".$node->body[LANGUAGE_NONE][0]["value"]."</pre>";
            $description_detail .= "<h3>".t('Task description', array(), $l)."</h3> - ".$item->label;
            $description_detail .= "<h3>".t('Deadline', array(), $l)."</h3>".format_date($item->deadline,  'short_without_hours');
            $body = theme('gofast-notifications-node-task-assignee', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail

            ));

            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail, $recpt, time());
          }
          else if($item->deadline !=  $old_values_items[$ciid]->deadline){ //Send notification when deadline change
             
            $account = $RecipUser = user_load($item->uid);
            $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));

            $userName = gofast_user_display_name($account);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);
            
           
            $deadline_formated= $item->deadline ? format_date($item->deadline,  'short_without_hours') : t('undefined',array(),$l);
            
            $subject = t('Task: New deadline on "!deadline" for "!title_todo" of the "!title" task', array('!deadline'=>$deadline_formated,'!title_todo'=>$item->label,'!title'=>$node->title), $l);

            $title = t('New deadline', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
            
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('Deadline has change on a checklist element of the card : ', array(), $l);
            $responsible = user_load($node->field_person_in_charge[LANGUAGE_NONE][0]["target_id"]);
            $username = theme('username', array('account' => $responsible, 'popup' => FALSE, 'link' => $options['link']));
            $description_detail = "<h3>".t('Responsible', array(), $l)."</h3>".$username;          
            $description_detail .= "<h3>".t('Card description', array(), $l)."</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>".$node->body[LANGUAGE_NONE][0]["value"]."</pre>";
            $description_detail .= "<h3>".t('Task description', array(), $l)."</h3> - ".$item->label;
            $description_detail .= "<h3>".t('Deadline', array(), $l)."</h3>".$deadline_formated;
            $body = theme('gofast-notifications-node-task-deadline-change', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail

            ));

            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail, $recpt, time()); 

          }
      }
    }
   
  }
   * */
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * Delete a checklistItem
 * @param type $ciid
 */
function gofast_kanban_checklistItem_delete($ciid) {
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);
  
  $node = gofast_kanban_get_task_from_checklistItem($ciid,true);
  $values = gofast_kanban_get_task_checklists($node->nid);
  
  $query = db_delete('gofast_kanban_checklist_item')
          ->condition('ciid', $ciid);
  
  $query->execute();
  
  //Save entities ( audit and notificiation)
  gofast_kanban_ext_create_checklistsave_entity($node,$values);
  
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
}

/**
 * 
 * @param type $ciid
 * @return type
 */
function gofast_kanban_checklistItem_get($ciid){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);
 
  $checklistItem = array();
  
  $query = db_select('gofast_kanban_checklist_item', 'ci')
        ->fields('ci', array('ciid', 'cid', 'label', 'deadline', 'uid', 'status'))
        ->condition('ciid', $ciid, '=');

  $results = $query->execute()->fetchAll();
  if (count($results) > 0) {
   $checklistItem = $results[0];
  }
 
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
 return $checklistItem; 
}



/**
 * 
 * @param type $ciid
 * @param type $user
 * @return boolean
 */
function gofast_kanban_checklistItem_canDo($ciid, $user = NULL) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $canDo = FALSE;

  if ($user == NULL) {
    $user = $GLOBALS['user'];
  }

  $checklistItem = gofast_kanban_checklistItem_get($ciid);

  //retreive task
  $checklist = gofast_kanban_mychecklist_load($checklistItem->cid);
  $task = node_load($checklist->task_nid);

  if ($user->uid == $checklistItem->uid) {
    $canDo = TRUE;
  }

  $members = $task->field_members[LANGUAGE_NONE];
  foreach ($members as $key => $member) {
    if ($user->uid == $member['target_id']) {
      $canDo = TRUE;
    }
  }

  return $canDo;
}

/**
 * Implements function for create linksharing entity
 */
function gofast_kanban_ext_create_checklistsave_entity($node,$values){
  
  global $user;  
  
  //update node (card) ruid.
  $node->revision_uid = $user->uid;
  node_save($node);

  $message = "ETDL|" . json_encode($values);
  $myentity = 'message';
  $entity = entity_create($myentity, array('type' => 'message_log'));
  $wrapper = entity_metadata_wrapper($myentity, $entity);
  $wrapper->value()->uid = $user->uid;
  $wrapper->field_target_id = $node->nid;
  $wrapper->field_message_log = $message;
  $wrapper->save();
}
