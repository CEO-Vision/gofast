<?php
/**
 * Form definition for adding/editing a userlist.
 * @param type $form
 * @param type $form_state
 * @return string
 */
function userlist_form($form, &$form_state = NULL, $userlist = NULL ){
  
  $form['name'] = array(
    '#title' => t('UserList name'),
    '#type' => 'textfield',
    '#default_value' => isset($userlist->name)? $userlist->name : '',
    '#required' => TRUE,
  );
  
  $form['from_ldap'] = array(
    '#type' => 'hidden',
    '#default_value' => isset($userlist->from_ldap)? $userlist->from_ldap : 0,
    '#required' => TRUE,
  );
  
  field_attach_form('userlist', $userlist, $form, $form_state);
  
  /*
  $userlist_members = array();
    
  $form['field_userlist_members'][LANGUAGE_NONE] = empty($form_state['values']['field_userlist_members']) ? implode(',', $userlist_members) : $form_state['values']['field_userlist_members'];
  
  //Retrieve former members
  foreach ($userlist->field_userlist_members[LANGUAGE_NONE] as $member_uid) {
    $member = user_load($member_uid['value']);
    $userlist_members[] = gofast_og_ac_format_value('user', $member, NULL, $member->name, NULL);
  }

  
  $form['field_userlist_members'] = array(
    '#title' => t('UserList members'),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#autocomplete_path' => 'gofast_user_space_autocomplete',
    '#attributes' => array('class' => array('labelize-autocomplete')),
    '#value' => empty($form_state['values']['field_userlist_members']) ? implode(',', $userlist_members ) : $form_state['values']['field_userlist_members']
  );
  */
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => isset($userlist->id)? t('Update userlist') : t('Save userlist'),
  );
  
  return $form;
  
}


/**
 * Submit handler for the userlist add/edit form
 * @param type $form
 * @param type $form_state
 */
function userlist_form_submit($form, &$form_state){
  
  //@TODO : save selected users as member in field_userlist_members
     
  $userlist = entity_ui_form_submit_build_entity($form, $form_state);
   
  $userlist->save();
    
  drupal_set_message(t('The userlist: @name has been saved.', array('@name' => $userlist->name) ));
  $form_state['redirect'] = 'admin/userlists';
}

