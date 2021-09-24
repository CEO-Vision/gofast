<?php

/**
 * Implements HOOK_form_FORM_ID_alter()
 * @param type $form
 * @param type $form_state
 * @param type $form_id
 * @return boolean
 */
function gofast_userlist_form_userlist_node_form_alter(&$form, &$form_state, $form_id) {
  unset($form['actions']['delete']);
  $form['fieldset_userlist'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create UserList', array(), array('context' => 'gofast:gofast_userlist')),
//    '#access' => FALSE,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 0
  );

  $nid = isset($form['#node']->nid) ? $form['#node']->nid : '';

  $form_state['reset_html_ids'] = TRUE;

  if (!empty($nid)) { // edit
    $ulid = $form['#node']->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
    $userlist_members = gofast_userlist_get_members($ulid);

    $form_state['values']['field_userlist_members'] = empty($form_state['values']['field_userlist_members']) ? implode(',', $userlist_members) : $form_state['values']['field_userlist_members'];
    
    $userlist_administrators = gofast_userlist_get_administrators($ulid);

    $form_state['values']['field_userlist_admincomplete'] = empty($form_state['values']['field_userlist_admincomplete']) ? implode(',', $userlist_administrators) : $form_state['values']['field_userlist_admincomplete'];
  }

  $form['field_userlist_ulid']['#access'] = FALSE;

  $form['og_group_ref']['#attributes']['class'][] = 'gofast_display_none';
  $form['og_group_ref']['#required'] = FALSE;
  
  if(!empty($nid)){
    $form['fieldset_userlist']['field_userlist_admincomplete'] = array(
      '#title' => t('UserList administrators',array(),array('context'=>'gofast:gofast_userlist')),
      '#type' => 'textfield',
      '#required' => FALSE,
      '#maxlength' => '',
      '#autocomplete_path' => 'gofast_user_autocomplete',
      '#attributes' => array('class' => array('labelize-autocomplete')),
      '#value' => isset($form_state['values']['field_userlist_admincomplete']) ? $form_state['values']['field_userlist_admincomplete'] : '',
      '#default_value' => isset($form_state['values']['field_userlist_admincomplete']) ? $form_state['values']['field_userlist_admincomplete'] : '',
    );
  }
  
  $form['field_userlist_members'] = array(
    '#title' => t('UserList members',array(),array('context'=>'gofast:gofast_userlist')),
    '#type' => 'textfield',
    '#required' => FALSE,
    '#maxlength' => '',
    '#autocomplete_path' => 'gofast_user_autocomplete',
    '#attributes' => array('class' => array('labelize-autocomplete')),
    '#value' => isset($form_state['values']['field_userlist_members']) ? $form_state['values']['field_userlist_members'] : '',
    '#default_value' => isset($form_state['values']['field_userlist_members']) ? $form_state['values']['field_userlist_members'] : '',
  );

  $form['fieldset_userlist']['title'] = $form['title'];
  $form['fieldset_userlist']['field_userlist_members'] = $form['field_userlist_members'];
  $form['fieldset_userlist']['field_description'] = $form['field_description'];
  if (!empty($nid)) { // edit
    $form['actions']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#attributes' => array('class' => array('btn', 'btn-sm'), 'onClick' => 'Gofast.addLoading();', 'style' => 'margin-left:10px;'),
      '#weight' => '49',
      '#submit' => array('gofast_userlist_custom_form_cancel')
    );
  }
  unset($form['title']);
  unset($form['field_userlist_members']);
  unset($form['field_description']);

  $form['#validate'] = array('gofast_userlist_form_userlist_node_form_validate');
  $form['#submit'] = array('gofast_userlist_form_userlist_node_form_submit');
  
}

/**
 * 
 * @param type $form
 * @param type $form_state
 */
function gofast_userlist_custom_form_cancel($form, &$form_state) {
  $nid = $form['#node']->nid;

  drupal_goto('/node/' . $nid);
}

/**
 * 
 * @param type $form
 * @param array $form_state
 */
function gofast_userlist_form_userlist_node_form_validate($form, &$form_state) {

  $members = array();

  //Fill field_userlist_members with the hidden input when editing members of userlist
  $members_value = json_decode($form_state['input']['edit-field-userlist-members-hidden-values']);
  foreach ($members_value as $member_value) {
    array_push($members, $member_value->id);
  }

//Fill field_userlist_members with the hidden input when editing members of userlist
//  $members = explode(' ', trim($form_state['input']['edit-' . str_replace("_", "-", $form['fieldset_userlist']['field_userlist_members']['#name']) . '-hidden-values']));
  $form_state['values']['fieldset_userlist']['field_userlist_members'] = implode(',', $members);
}

/**
 * Send notification to concerned user (who was added to userlist)
 * @param type $id_new_member : uid
 * @param type $id_userlist : nid
 * @param type $message : Null for member , not empty for administrator
 * @param type $role_member ADM : administrator users list, MEM : member users list 
 */
function gofast_mail_add_user_to_userlist( $id_new_member, $id_userlist, $message, $role_member ){

  $node = node_load( $id_userlist );
  $new_member = user_load( $id_new_member );  
  $site_name = variable_get('site_name', 'GoFast');
  $l = array('langcode' => $new_member->language, 'context' => 'gofast_userlist');

  if( $role_member == 'ADM'){
      
      $subject = t("You have been added administrator to this users list : ", array(), $l).$node->title; // subject of the message (that is seen before openning the message)
      $title = t("You're administrator of ", array(), $l).$node->title;  
  }
 
  if ($role_member == 'MEM'){
      $subject = t("You have been added to this users list : " , array(), $l).$node->title; // subject of the message (that is seen before openning the message)
      $title = t(" You're member of " , array(), $l).$node->title;    
  }
  
  $footer = t('Message sent from ', array(), $l).$site_name;
  
  $mess = NULL;
  if($message !== NULL ){
    $mess = $message;
  }

  $ulid = $node->field_userlist_ulid[LANGUAGE_NONE][0][value];
  $groups_userlist = gofast_userlist_og_get_groups_by_userlist( $ulid );
  

  if(count($groups_userlist)){
    $grps .= "<ul>";
    foreach ($groups_userlist['node'] as $group_id) {
      $group = node_load($group_id);
      $item = gofast_cmis_item_get($group->field_folder_reference[LANGUAGE_NONE][0]['value'], TRUE);  
      $path = str_replace('/Sites/', '', $item->properties['cmis:path']);
      $grps .= t("<li> !space (!path) </li>", array('!space' => $group->title, '!path' => $path), array('context' => 'gofast_og'));
    }
    $grps .= "</ul>";
  }
  else{
      $grps=t('No space yet',array(),$l);
  }

  $body = theme('gofast_userlist_add_user_notif', array(
    'grps' => $grps,
    'mess' => $mess,
    'l' => $l,
    'role_member' => $role_member,
    ));

   gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, array(array('recpt' => $new_member->mail, 'method' => 'to')));
 
  }

/**
 * Send notification to concerned user (who was removed from userlist)
 * @param type $id_removed_member  : uid
 * @param type $id_userlist : nid
 * @param type $message : Null for member , not empty for administrator
 * @param type $role_member ADM : administrator users list, MEM : member users list 
 */
function gofast_mail_remove_user_from_userlist( $id_removed_member, $id_userlist, $message, $role_member ){
  
  $node = node_load( $id_userlist );
  
  $removed_member = user_load( $id_removed_member );  
  $site_name = variable_get('site_name', 'GoFast');
  $l = array('langcode' => $removed_member->language, 'context' => 'gofast_userlist');
  
  if ($role_member == 'ADM'){
  $subject = t("You are no longer administrator of this users list : ", array(), $l).$node->title; // subject of the message (that is seen before openning the message)
  $title = t("You're no longer administrator of ", array(), $l).$node->title;   
  }
  
  if($role_member == 'MEM'){
  $subject = t("You have been removed from this users list : " , array(), $l).$node->title; 
  $title = t("You're no longer member of ", array(), $l).$node->title;     
  }
  $footer = t('Message sent from ', array(), $l).$site_name;

  $mess = NULL;
  if($message !== NULL ){
    $mess = $message;
  }
  
  $ulid = $node->field_userlist_ulid[LANGUAGE_NONE][0][value];
  $groups_userlist = gofast_userlist_og_get_groups_by_userlist( $ulid );
  
    $grps .= "<ul>";
       foreach ($groups_userlist['node'] as $group_id) {
        $group = node_load($group_id);
        $item = gofast_cmis_item_get($group->field_folder_reference[LANGUAGE_NONE][0]['value'], TRUE);  
        $path = str_replace('/Sites/', '', $item->properties['cmis:path']);
        $grps .= t("<li> !space (!path) </li>", array('!space' => $group->title, '!path' => $path), array('context' => 'gofast_og'));
       }
    $grps .= "</ul>";
    
    $body = theme('gofast_userlist_remove_user_notif', array(
    'grps' => $grps,
    'mess' => $mess,
    'l' => $l,
    'role_member' => $role_member,    
  ));
    
   gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, array(array('recpt' => $removed_member->mail, 'method' => 'to')));

}

/**
 * Form submit
 * @param type $form
 * @param array $form_state
 */
function gofast_userlist_form_userlist_node_form_submit($form, &$form_state) {

  $form_state['values']['field_userlist_members'] = $form_state['values']['fieldset_userlist']['field_userlist_members'];

  //Retrieve old administrators
  $nid = isset($form['#node']->nid) ? $form['#node']->nid : '';
  if ($nid) {
    $members = gofast_og_get_members(node_load($nid));

    foreach ($members as $id => $member) {
      if ($member == $form['#node']->uid) {
        unset($members[$id]);
      }
    }
  } else {
    $members = array();
  }

  $field_members = json_decode($form_state['input']["edit-field-userlist-admincomplete-hidden-values"]);
  $new_members = array();

  foreach ($field_members as $member) {
    if (!$nid || $member->id != $form['#node']->uid) {
      $new_members[] = $member->id;
    }
  }

  //Sort out members to add and members to remove
  $to_add = array_diff($new_members, $members);
  $to_remove = array_diff($members, $new_members);

  if (count($to_add) > 0 || count($to_remove) > 0) {
    $roles_query = og_roles('node', "userlist", $nid, FALSE, FALSE);
    foreach ($roles_query as $rkey => $roles) {
      if ($roles == GOFAST_OG_ROLE_ADMIN) {
        $admin_rid = $rkey;
      }
      if ($roles == GOFAST_OG_ROLE_READ_ONLY) {
        $readonly_rid = $rkey;
      }
      if ($roles == GOFAST_OG_ROLE_STANDARD) {
        $contributor_rid = $rkey;
      }
    }

    foreach ($to_add as $uid) {
      gofast_og_subscribe_user($nid, $uid);
      og_role_revoke('node', $nid, $uid, $readonly_rid);
      og_role_revoke('node', $nid, $uid, $contributor_rid);
      og_role_revoke('node', $nid, $uid, $admin_rid);
      og_role_grant('node', $nid, $uid, $admin_rid);
    }

    foreach ($to_remove as $uid) {
      og_role_revoke('node', $nid, $uid, $readonly_rid);
      og_role_revoke('node', $nid, $uid, $contributor_rid);
      og_role_revoke('node', $nid, $uid, $admin_rid);
      gofast_og_unsubscribe_user($nid, $uid);
    }


    if ($nid && !isset($form_state['#submitted'])) { //Avoid submit form twice) { // Only for Edition
       
       $role_member = 'ADM';
       $message_add = t("From now, you can manage this users list and modify his members.");
       foreach ($to_add as $uid) {
            gofast_mail_add_user_to_userlist( $uid, $nid, $message_add, $role_member);
       }
       
       $message_remove = t("From now, you can no longer manage this users list and modify his members.");
       foreach ($to_remove as $uid) {
            gofast_mail_remove_user_from_userlist( $uid, $nid, $message_remove, $role_member );
       }
     
      $node = node_load($nid, NULL, FALSE); //Node before edition
      $node_refresh = node_load($nid, NULL, TRUE); //Node after edition
      $node_data = gofast_userlist_split_node_extend($node, gofast_message_ext_split_node($node));
      $node_refresh_data = gofast_userlist_split_node_extend($node_refresh, gofast_message_ext_split_node($node_refresh));
      $node_compare = gofast_userlist_compare($node_data, $node_refresh_data);

      $event_type = 'EUSL';

      $node_compare['userlist adm']['from'] = $members;
      $node_compare['userlist adm']['to'] = $new_members;

      $node_compare['event']['value'] = $event_type;
      $message = json_encode($node_compare);

      gofast_userlist_insert_into_audit($event_type, $node, $message);
    }

    $form_state['#submitted'] = TRUE;
  }
}
