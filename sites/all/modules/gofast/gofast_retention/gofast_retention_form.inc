<?php
/**
 * Implement HOOk_Form()
 * @param type $form
 * @param type $form_state
 */
//function gofast_retention_form_gofast_admin_retention(&$form, &$form_state){
function gofast_admin_retention_settings_form(){
   $form = array();
   $form['retention']['recipients'] = array(
    '#type' => 'fieldset',
    '#title' => t('Current list of mail recipient', array(), array('context' => 'gofast:gofast_retention')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
//    'markup' => array(
//      '#markup' => t('You can edit an existing retention periode', array(), array('context' => 'gofast:gofast_retention'))
//    ),
    '#tree' => TRUE, //Make the form elements keep their tree
  );
   
  $list_recipient = array();
  $recipients = array();
  if ( NULL != variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR) ) {
    $list_recipient = variable_get(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR);
    foreach($list_recipient as $recipient){
      $recipient_user =  user_load($recipient->id);
      $recipients[] = gofast_modal_ac_format_send_email_value('user', $recipient_user , NULL, $recipient_user->name, NULL);   
    } 
  }
  
  $form_state['values']['recipients']['list_reciptient'] = empty($form_state['values']['recipients']['list_recipient']) ? implode(',', $recipients) : $form_state['values']['list_recipient'];
  $form['retention']['recipients']['list_recipient'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient(s)', array(), array('context' => 'gofast:gofast_retention')). ' *',
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t('Users who will be notified once retention period is over', array(), array('context' => 'gofast:gofast_retention')),
    '#required' => FALSE,
    '#autocomplete_path' => 'gofast_user_autocomplete',
    '#attributes' => array('class' => array('labelize-autocomplete labelize-insert')),
    '#value' =>  implode(',', $recipients)
  );

    
  $form['retention']['list_retention'] = array(
    '#type' => 'fieldset',
    '#title' => t('Current list of retention period', array(), array('context' => 'gofast:gofast_retention')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
//    'markup' => array(
//      '#markup' => t('You can edit an existing retention periode', array(), array('context' => 'gofast:gofast_retention'))
//    ),
    '#tree' => TRUE, //Make the form elements keep their tree
    '#theme' =>  'gofast_retention_container_list_retention'
  );
  
  $form['retention']['list_retention']['category'] = array(
     '#type' => 'hidden',
     '#value' => ''
  );
    
  $form['retention']['add_edit_retention'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add/Edit a retention period', array(), array('context' => 'gofast:gofast_retention')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    'markup' => array(
      '#markup' => t('You can add or edit an existing retention period', array(), array('context' => 'gofast:gofast_retention'))
    ),
    '#tree' => TRUE, //Make the form elements keep their tree
  );
  
  $form['retention']['add_edit_retention']['new_retention_widget']= array(
    '#title' => t('New Retention period', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'radios',
    '#options' => array(0=> t('Yes'), 1 => t('No')),
    '#default_value' => 0
  );
  
  $form['retention']['add_edit_retention']['new_retention']= array(
    '#type' => 'hidden',
    '#default_value' => 0,
    '#attributes' => array(
      'id' =>  'edit-add-edit-retention-new-retention'   
    )
  );
  
  $existing_terms = taxonomy_get_tree(GOFAST_VID_CATEGORY, 0, NULL, TRUE);
  $edit_category_actions = array();
  $edit_category_actions[0] = t('Select a category', array(), array('context' => 'gofast:gofast_retention')) ;
  foreach ($existing_terms as $existing_term) {
   // if($existing_term->field_standard_gf[LANGUAGE_NONE][0]['value'] != 1){
      $edit_category_actions[$existing_term->tid] = i18n_taxonomy_localize_terms($existing_term)->name;
   // }
  }
  
  $form['retention']['add_edit_retention']['category']= array(
    '#title' => t('Category', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'select',
    '#options' => $edit_category_actions
  );
  
  $form['retention']['add_edit_retention']['tid']= array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' =>  'edit-add-edit-retention-tid'   
    )
  );
  
  $form['retention']['add_edit_retention']['uuid']= array(
    '#type' => 'hidden',
    '#attributes' => array(
      'id' =>  'edit-add-edit-retention-uuid'   
    )
  );
  
  $form['retention']['add_edit_retention']['duration']= array(
    '#title' => t('Retention duration', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'textfield',
  );
  
  $units = array('d' =>'Day', 'm' =>'Month', 'y' => 'Year');
  $units_trad =array();
  foreach($units as $key => $unit){
    $units_trad[$key] = t($unit, array(), array('context' => 'gofast:gofast_retention'));
  }
  $form['retention']['add_edit_retention']['duration_unit']= array(
    '#title' => t('Unit', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'select',
    '#options' => $units_trad
  );
  
  $actions = array('-None-', 'Archive', 'Sort', 'Destruction');
  $actions_trad =array();
  foreach($actions as $action){
    $actions_trad[$action] = t($action, array(), array('context' => 'gofast:gofast_retention'));
  }
  $form['retention']['add_edit_retention']['retention_action']= array(
    '#title' => t('Action', array(), array('context' => 'gofast:gofast_retention')),
    '#type' => 'select',
    '#options' => $actions_trad
  );
  
  $form['#validate'][] = 'gofast_retention_form_gofast_admin_retention_validate';
  $form['#submit'][] = 'gofast_retention_form_gofast_admin_retention_submit';
  
  $form['retention']['#theme'] = 'gofast_retention_add_retention_period_form'; 
  
  foreach(module_implements('alter_admin_retention_settings_form') as $module){
      $function = $module . '_alter_admin_retention_settings_form';
      $form = call_user_func( $function, $form, $units_trad );
  } 
  
   $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast')),
  );
  
  return $form;
} 

/**
 * Validation of form_gofast_admin_retention
 * @param type $form
 * @param type $form_state
 */
function gofast_retention_form_gofast_admin_retention_validate($form, &$form_state){
  
}

/**
 * Submission of form_gofast_admin_retention
 * @param type $form
 * @param type $form_state
 */
function gofast_retention_form_gofast_admin_retention_submit($form, &$form_state){
  $current_matrice = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR);
    
  $term_uuid = '';
  $term_tid = '';
    
  //create
  if ( isset($form_state['values']['add_edit_retention']['new_retention']) && $form_state['values']['add_edit_retention']['new_retention'] == 0 ){
    
    //get category uuid
    $term = taxonomy_term_load($form_state['values']['add_edit_retention']['category']);
    $term_uuid = $term->uuid;
    $term_tid = $term->tid;

  //update
  }else{    
    $term_uuid = $form_state['values']['add_edit_retention']['uuid'];
    $term_tid = $form_state['values']['add_edit_retention']['tid'];
    
    
  }
  
  if( $form_state['values']['add_edit_retention']['duration'] !== ''){
    
    $current_matrice[$term_uuid] = array(
        'uuid' => $term_uuid,
        'tid' => $term_tid,
        'period' => $form_state['values']['add_edit_retention']['duration'] ,
        'period_unit' => $form_state['values']['add_edit_retention']['duration_unit'],
        'action' => $form_state['values']['add_edit_retention']['retention_action']
    );
  }else{
    unset($current_matrice[$term_uuid]);
  }
  variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $current_matrice );
  //$id = ($form['retention']['recipients']['list_recipient']['#id']) . '-hidden-values'; 
  
  $id = ($form['retention']['recipients']['list_recipient']['#id']) . '-hidden-values';
  if(substr($form_state['input'][$id], 0, 2) === "[{"){
    $json_list_recipients = json_decode($form_state['input'][$id]);
    variable_set(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR, $json_list_recipients);
  }else{
      //workaround for https://ceo-vision.com/jira/browse/GOFAST-5745
      $array_dest = explode(" ", trim($form_state['input'][$id]));
      if(count($array_dest) > 0){
          $json_list_recipients = array();
          foreach($array_dest as $uid){
              $account = user_load($uid);
              $account_obj = new stdClass();
              $account_obj->id = $uid;
              $account_obj->address = $account->mail;
              $account_obj->name = $account->name;
              $account_obj->type = "user";
              $json_list_recipients[] = $account_obj;
          }
          variable_set(GOFAST_RETENTION_PERIOD_RECIPIENTS_VAR, $json_list_recipients);
      }       
   }
   
   if( isset($form_state['values']['frequence_sorting']['duration'])){
       gofast_archive_sorting_room_settings_frequence_notification( $form, $form_state);
    }   
}

/**
 * Implements HOOK_FORM_alter()
 * @global type $user
 * @param type $form
 * @param type $form_state
 */
function gofast_retention_form_gofast_admin_settings_alter(&$form, &$form_state) {
  //DUA
  /*  if (!module_exists('gofast_community')){
        $form['retention'] = array(
        '#title' => t('Document Retention', array(), array('context' => 'gofast:gofast_retention')),
        '#type' => 'fieldset',
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#group' => 'vt'
      );
             
     // gofast_retention_form_gofast_admin_retention($form, $form_state);
    }*/
}
