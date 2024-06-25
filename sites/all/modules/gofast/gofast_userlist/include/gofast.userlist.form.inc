<?php

/**
 * Implements HOOK_form_FORM_ID_alter()
 * @param type $form
 * @param type $form_state
 * @param type $form_id
 * @return boolean
 */
function gofast_userlist_form_userlist_node_form_alter(&$form, &$form_state, $form_id) {
  global $user;
  unset($form['actions']['delete']);
  $nid = isset($form['#node']->nid) ? $form['#node']->nid : '';

  $form['fieldset_userlist'] = array(
    '#type' => 'fieldset',
    '#title' => empty($nid) ? t('Create UserList', array(), array('context' => 'gofast:gofast_userlist')) : t('Edit UserList', array(), array('context' => 'gofast:gofast_userlist')),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 0
  );

  $form['field_userlist_ulid']['#access'] = FALSE;

  $form['og_group_ref']['#attributes']['class'][] = 'gofast_display_none';
  $form['og_group_ref']['#required'] = FALSE;


  $attributes = [
    'class' => ['form-control-tags js-tagify'],
    'data-user' => '', // show ac users
    // 'data-enforce' => '',
  ];

  $form_state['reset_html_ids'] = TRUE;
  
  $form['fieldset_userlist']['title'] = $form['title'];

  $form['fieldset_userlist']['field_userlist_members'] = array(
    '#title' => t('UserList members',array(),array('context'=>'gofast:gofast_userlist')),
    '#type' => 'textfield',
    '#name' => 'ac-list-tags-userlist-members',
    '#required' => FALSE,
    '#maxlength' => '',
    '#attributes' => $attributes,
  );
 
  $form['fieldset_userlist']['field_userlist_admincomplete'] = array(
    '#title' => t('UserList administrators',array(),array('context'=>'gofast:gofast_userlist')),
    '#type' => 'textfield',
    '#name' => 'ac-list-tags-userlist-admin',
    '#required' => TRUE,
    '#maxlength' => '',
    '#attributes' => $attributes,
  );

  if (empty($nid)) { // create
    $creator = $user;
    $userlist_administrators_tags[] = gofast_ac_format_value_json(
      'user',
      $creator,
    );
  }

  if (!empty($nid)) { // edit
    $ulid = $form['#node']->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
    $userlist_members = gofast_userlist_get_members($ulid);
    $userlist_members_uids = array();
    $userlist_members_tags = array();

    foreach ($userlist_members as $uid => $userlist_member) $userlist_members_uids[] = $uid;
    $userlist_members = user_load_multiple($userlist_members_uids);
    foreach ($userlist_members as $userlist_member) $userlist_members_tags[] = gofast_ac_format_value_json('user', $userlist_member);

    $form['fieldset_userlist']['field_userlist_members']["#value"] = json_encode($userlist_members_tags);

    $userlist_administrators = gofast_userlist_get_administrators($ulid);
    $userlist_administrators_uids = array();
    $userlist_administrators_tags = array();

    foreach ($userlist_administrators as $uid => $userlist_administrator) $userlist_administrators_uids[] = $uid;
    $userlist_administrators = user_load_multiple($userlist_administrators_uids);
    foreach ($userlist_administrators as $userlist_administrator) $userlist_administrators_tags[] = gofast_ac_format_value_json('user', $userlist_administrator);

    $form['actions']['cancel'] = array(
      '#type' => 'submit',
      '#value' => t('Cancel'),
      '#attributes' => array('class' => array('btn', 'btn-sm'), 'onClick' => 'Gofast.addLoading();', 'style' => 'margin-left: 10px;'),
      '#weight' => '49',
      '#submit' => array('gofast_userlist_custom_form_cancel')
    );
  }
  
  if(!isset( $form['actions']['cancel'])){
    gofast_add_cancel_button_to_form($form);
  }

  $form['fieldset_userlist']['field_userlist_admincomplete']["#value"] = json_encode($userlist_administrators_tags);

  $form['fieldset_userlist']['field_description'] = $form['field_description'];
  unset($form['field_description']);
  unset($form['title']);
  
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
  if (isset($form['#node']->nid)) { // edition mode
    $form_state['values']['status'] = 1; // in case the value has been set to 0 in an admin form_alter hook
  }
  $members = array();

  //Fill field_userlist_members with the hidden input when editing members of userlist
  $members_value =  json_decode($form_state['input']['ac-list-tags-userlist-members']);
  foreach ($members_value as $member_value) {
    array_push($members, $member_value->value);
  }
  $form_state['values']['fieldset_userlist']['field_userlist_members'] = implode(',', $members);
  
  $admins = array();
  //Fill field_userlist_admin with the hidden input when editing admin of userlist
  $admins_value =  json_decode($form_state['input']['ac-list-tags-userlist-admin']);
  if(count((array) $admins_value) == "0"){
    form_set_error('ac-list-tags-userlist-admin', t('You must select at least one administrator.'));
  }
  foreach ($admins_value as $admin_value) {
    array_push($admins , $admin_value->value);
  }
  $form_state['values']['fieldset_userlist']['field_userlist_admincomplete'] = implode(',', $admins );
  
  $errors = form_get_errors();
  if ($errors) {
    // Clear errors.
    form_clear_error();

    foreach ($errors as $name => $error_message) {
      $commands[] = gofast_command_toast_message($error_message, "error");
    }
    print ajax_render($commands);exit;
  }
}

/**
 * Send notification to concerned user (who was added to userlist)
 *
 * @param Integer $id_new_member : uid
 * @param Integer $id_userlist : nid
 * @param String|NULL $message : Null for member , not empty for administrator
 * @param String $role_member ADM : administrator users list, MEM : member users
 * list
 *
 * @throws \Exception
 */
function gofast_mail_add_user_to_userlist(int $id_new_member, int 
$id_userlist, string|null $message, string $role_member ): void {

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

  $ulid = $node->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
  $groups_userlist = gofast_userlist_og_get_groups_by_userlist( $ulid );
  

  if(isset($groups_userlist) && count($groups_userlist)){
    $grps = "";
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

  $ulid = $node->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
  $groups_userlist = gofast_userlist_og_get_groups_by_userlist( $ulid );

    $grps = "";
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
  } else {
    $members = array();
  }

  $field_members = explode(',', $form_state['values']['fieldset_userlist']['field_userlist_admincomplete']);
  $new_members = array();

  foreach ($field_members as $member) {
      $new_members[] = $member;
  }
  if ($nid) {
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
