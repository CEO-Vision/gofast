<?php

include_once __DIR__ . '/gofast_og.bulk.inc';

/**
 * Callback to menu /space/admin/members
 * @param type $js
 * @param type $action
 * @return string
 */
function gofast_og_admin_members_page($js, $action ='add'){
  $output =  '<div id="gofast-og-admin-spaces-container">'
            .theme('gofast_og_space_admin', array('js' => $js, 'action'=>$action))
            .'</div>';
  return $output;
}

/**
 * Return the list of actif user in a specific format
 * to be used by a checkboxes widget
 * @return string
 */
function gofast_og_get_visible_users(){
  $users = array();

  $query = db_select('users', 'u');
  $query->fields('u', array('uid','name'));
  $query->join('field_data_ldap_user_givenname', 'a', 'a.entity_id = u.uid');
  $query->join('field_data_ldap_user_sn', 'b', 'b.entity_id = u.uid');
  $query->fields('a', array('ldap_user_givenname_value'));
  $query->fields('b', array('ldap_user_sn_value'));
  $query->condition('u.status', 1);
  $query->condition('u.name', 'adm', '<>');
  $query->condition('u.uid', '1', '<>');
  $query->orderBy('b.ldap_user_sn_value', 'ASC');

  $results = $query->execute();

  if ($results->rowCount() > 0) {
    while($user = $results->fetchObject()){
      $users[$user->uid] = strtoupper($user->ldap_user_sn_value).' '.$user->ldap_user_givenname_value;
    }
  }
  return $users;
}



/**
 * Gofast OG member administration page.
 */
function gofast_og_admin_account($js, $group_type, $gid) {
  gofast_og_admin_member ($js, $group_type, $gid);
}

/**
 * Edit single OG membership - modal callback.
 */
function gofast_og_edit_membership($js, $group_type, $gid, $og_membership) {
  ctools_include('og_ui/og_ui.admin', 'og', '');

  $args = func_get_args();
  array_shift($args);

  if (!$js){
    return drupal_get_form('og_ui_edit_membership', $group_type, $gid, $og_membership);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Edit membership', array(), array('context' => 'gofast:gofast_og')),
    'build_info' => array(
      'args' => $args
    )
  );

  $commands = ctools_modal_form_wrapper('og_ui_edit_membership', $form_state);

  if($form_state['last_admin']){
    form_get_errors();
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_toast_message(t("You can't remove the last administrator of a space", array(), array('context' => "gofast:gofast_og")), "error")
    );
  }else if ($form_state['submitted']) {
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_processAjax("/node/{$gid}" . "#ogmembers")
    );
  }

  print ajax_render($commands);
}

function gofast_og_form_og_ui_edit_membership_form_alter(&$form, &$form_state) {
  $form['#submit'][] = '';
}

/**
 * Delete single OG membership - modal callback.
 */
function gofast_og_delete_membership($js, $group_type, $gid, $og_membership) {
  ctools_include('og_ui/og_ui.admin', 'og', '');

  $args = func_get_args();
  array_shift($args);

  if (!$js){
    return drupal_get_form('gofast_og_ui_delete_membership', $group_type, $gid, $og_membership);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Delete membership', array(), array('context' => 'gofast:gofast_og')),
    'build_info' => array(
      'args' => $args
    )
  );

  $commands = ctools_modal_form_wrapper('gofast_og_ui_delete_membership', $form_state);

  if($form_state['last_admin']){
    form_get_errors();
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_toast_message(t("You can't remove the last administrator of a space", array(), array('context' => "gofast:gofast_og")), "error")
    );
  }else if ($form_state['submitted']) {
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_processAjax("/node/{$gid}" . "#ogmembers")
    );
  }

  print ajax_render($commands);
}

/**
 * Delete a single membership from group.
 */
function gofast_og_ui_delete_membership($form, &$form_state, $group_type, $gid, $og_membership) {
  og_set_breadcrumb($group_type, $gid, array(l(t('Group'), "$group_type/$gid/group")));
  $group = entity_load_single($group_type, $gid);
  $label = entity_label($group_type, $group);
  $account = user_load($og_membership->etid);

  // Add group membership form. We still don't have the user or state.
  $form_state['og_membership'] = $og_membership;
  $form['#validate'][] = "gofast_og_ui_delete_membership_validate";

    return confirm_form($form,
        t('Remove membership in group @group', array('@group' => $label)),
        'group/' . $group_type . '/' . $gid . '/admin/people',
        '</br>' . "<div class='alert alert-block alert-dismissible alert-warning messages warning'>" . '<i class="fa fa-exclamation-triangle" style="color:#F0AD4E;font-size:1.5em"> </i>  ' . t('Warning: If you delete a member of the space it will also be deleted from its child spaces') . "</div>" . t('Are you sure you would like to remove the membership for the user @user?', array('@user' => $account->name)) ,
        t('Remove'),
        t('Cancel')
    );
  }

/**
 * Implements validation of membership deletion form
 */
function gofast_og_ui_delete_membership_validate($form, &$form_state) {
    $membership = $form_state['og_membership'];

    $member_uid = $membership->etid;
    $node = node_load($membership->gid);

    //Check if we are impacting an administrator membership
    if($membership->entity_type == "user"){
        $roles = og_get_user_roles("node", $node->nid, $member_uid);
    }else if($membership->entity_type == "userlist"){
        $roles = gofast_userlist_og_get_userlist_roles("node", $node->nid, $member_uid);
    }

    if(in_array("administrator member", $roles, TRUE)){
        //Check cound of administrators in this space
        $users_admins = gofast_userlist_og_get_node_members_by_role($node->nid, array(OG_STATE_ACTIVE), "administrator member");
        if(count($users_admins) < 2){
            $form_state['last_admin'] = TRUE;
            form_set_error("last_admin", t("You can't remove the last administrator of a space", array(), array('context' => "gofast:gofast_og")));
        }
    }

}


function gofast_og_check_remove_last_admin_children($member_uid, $node, $membership){
    //load all node children
    $descendants = gofast_og_get_children($node->nid, TRUE, FALSE, TRUE);
    if(count($descendants) > 0){
        $last_admin = false;
        foreach($descendants as $gid){
             //Check if we are impacting an administrator membership
            watchdog("debug admin 1", $membership->entity_type);
            if($membership->entity_type == "user"){
                $roles = og_get_user_roles("node", $gid, $member_uid);
            }else if($membership->entity_type == "userlist"){
                $roles = gofast_userlist_og_get_userlist_roles("node", $gid, $member_uid);
            }
             watchdog("debug admin", json_encode($roles));
           if(in_array("administrator member", $roles, TRUE)){
                //Check cound of administrators in this space
                 watchdog("debug admin 2", json_encode($roles));
                $users_admins = gofast_userlist_og_get_node_members_by_role($gid, array(OG_STATE_ACTIVE), "administrator member");
                 watchdog("debug admin 3", json_encode($users_admins));
                if(count($users_admins) < 2){
                    $last_admin = true;
                    return false;
                }
           }
        }
    }else{
        //no children
        return true;
    }
   if($last_admin == true){
        return false;
   }else{
       return true;
   }

}

/**
 * Submit handler;Delete the membership.
 */
function gofast_og_ui_delete_membership_submit($form, &$form_state) {

  $membership = $form_state['og_membership'];

  $member_uid = $membership->etid;
  $node = node_load($membership->gid);
  $account = user_load( $member_uid );

  $membership->delete();

  //Check if this User is member by userlist in current space
  $check = gofast_og_check_spaces_user($membership->entity_type, $account, $membership->gid);
  if( $check == FALSE ){
      gofast_og_sendmail_delete_membership_user(user_load($member_uid), array($node), NULL);
  }

  if($membership->entity_type == 'user'){
    $membership_data = array(
        'membership_action' => 'DMEM', // Remove Member
        'membership_type' => 'user',
        'membership_id' => $member_uid,
        'membership_name' => gofast_user_get_display_name_sql($member_uid)
    );
    gofast_message_ext_create_og_membership_entity($node, $membership_data);
  }

  //Log into audit
  gofast_audit_delete_members($node, $membership_data);

  $form_state['redirect'] = 'group/' . $membership->group_type . '/' . $membership->gid . '/admin/people';

  drupal_set_message(t('The membership was removed.'));
}

/**
 * Grant access to OG group - modal callback.
 */
function gofast_og_grant_membership($js, $group_type, $gid, $og_membership) {
  ctools_include('og_ui/og_ui.admin', 'og', '');

  $args = func_get_args();
  array_shift($args);

  if (!$js){
    return drupal_get_form('gofast_og_ui_grant_membership', $group_type, $gid, $og_membership);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Accept membership request', array(), array('context' => 'gofast:gofast_og')),
    'build_info' => array(
      'args' => $args
    )
  );

  $commands = ctools_modal_form_wrapper('gofast_og_ui_grant_membership', $form_state);

  if ($form_state['submitted']) {
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_processAjax("/node/{$gid}" . "#ogmembers")
    );
  }

  print ajax_render($commands);
}

/**
 * Deny access to OG group - modal callback.
 */
function gofast_og_deny_membership($js, $group_type, $gid, $og_membership) {
  ctools_include('og_ui/og_ui.admin', 'og', '');

  $args = func_get_args();
  array_shift($args);

  if (!$js){
    return drupal_get_form('gofast_og_ui_deny_membership', $group_type, $gid, $og_membership);
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Deny membership request', array(), array('context' => 'gofast:gofast_og')),
    'build_info' => array(
      'args' => $args
    )
  );

  $commands = ctools_modal_form_wrapper('gofast_og_ui_deny_membership', $form_state);

  if ($form_state['submitted']) {
    $commands = array(
      ctools_modal_command_dismiss(),
      gofast_command_processAjax("/node/{$gid}" . "#ogmembers")
    );
  }

  print ajax_render($commands);
}

/**
 * Grant membership to a space.
 */
function gofast_og_ui_grant_membership($form, &$form_state, $group_type, $gid, $og_membership) {
  og_set_breadcrumb($group_type, $gid, array(l(t('Group'), "$group_type/$gid/group")));
  $group = entity_load_single($group_type, $gid);
  $label = entity_label($group_type, $group);
  $account = user_load($og_membership->etid);

  // Add group membership form. We still don't have the user or state.
  $form_state['og_membership'] = $og_membership;

  return confirm_form($form,
    t('Accept membership request in group @group', array('@group' => $label)),
    'group/' . $group_type . '/' . $gid . '/admin/people',
    t('Are you sure you would like to accept the membership request for the user @user?', array('@user' => $account->name)),
    t('Accept'),
    t('Cancel')
  );
}

/**
 * Submit handler;grant the membership.
 */
function gofast_og_ui_grant_membership_submit($form, &$form_state) {
  $membership = $form_state['og_membership'];
  $membership->state = '1';
  $membership->save();
  //We propagate the membership to the parents
  gofast_og_membership_propagate($membership);
  //We add user in LDAP
  gofast_ldap_og_membership_insert($membership);
  $role = key(gofast_og_get_user_roles($membership->gid, $membership->etid));
  $role = array($role);
  gofast_ldap_og_role_grant('node', $membership->gid, $membership->etid, $role);
  $form_state['redirect'] = 'group/' . $membership->group_type . '/' . $membership->gid . '/admin/people';

  // send mail in this case
  $message = t("Your request is accepted !");
  gofast_og_sendmail_members_groups($membership, $message);

  drupal_set_message(t('The membership request was accepted.'));
}

/**
 * Deny membership to a space.
 */
function gofast_og_ui_deny_membership($form, &$form_state, $group_type, $gid, $og_membership) {
  og_set_breadcrumb($group_type, $gid, array(l(t('Group'), "$group_type/$gid/group")));
  $group = entity_load_single($group_type, $gid);
  $label = entity_label($group_type, $group);
  $account = user_load($og_membership->etid);

  // Add group membership form. We still don't have the user or state.
  $form_state['og_membership'] = $og_membership;

  return confirm_form($form,
    t('Deny membership in group @group', array('@group' => $label)),
    'group/' . $group_type . '/' . $gid . '/admin/people',
    t('Are you sure you would like to deny the membership request for the user @user?', array('@user' => $account->name)),
    t('Deny'),
    t('Cancel')
  );
}

/**
 * Submit handler;Deny the membership.
 */
function gofast_og_ui_deny_membership_submit($form, &$form_state) {
  $membership = $form_state['og_membership'];

  $user_requester = user_load($membership->etid);
  $groups = node_load_multiple(array($membership->gid));
  $membership->delete();
  $form_state['redirect'] = 'group/' . $membership->group_type . '/' . $membership->gid . '/admin/people';

  // send mail in this case
  $message = t("Your request is rejected !");
  gofast_og_sendmail_rejected_membership_user($user_requester, $groups, $message);

  drupal_set_message(t('The membership request was denied.'));
}

/**
 * Alter og_user_roles_action form (VBO).
 */
function gofast_og_vbo_action_user_roles_alter(&$form, &$form_state, $context) {
  list($group_type, $gid, $space) = $context;

  $form['add_roles']['#type'] = '#hidden';
  $form['remove_roles']['#type'] = '#hidden';

  // Check if we should use defaults or overriden roles.
  if (og_is_group_default_access($group_type, $gid)) {
    // Get global OG roles.
    $roles = og_roles($group_type, $space->type, 0, FALSE, FALSE);
  }
  else {
    // Get this specific roles, as the permission set may have been overriden.
    $roles = og_roles($group_type, $space->type, $gid, TRUE, FALSE);
  }

  $defaults = og_get_default_roles(FALSE);
  $default_rid = array_search($defaults['gofast_og'], $roles);

  $form['og_roles'] = array(
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#title' => t('Roles', array(), array('context' => 'gofast')),
    '#default_value' => array($default_rid),
    '#attributes' => array('class' => array('og-roles-force-single')),
    '#attached' => array(
      'js' => array(
        array(
          'data' => drupal_get_path('module', 'gofast_og') . '/gofast_og.js',
          'type' => 'file',
          'scope' => 'footer',
          'weight' => 5
        )
      )
    )
  );

  // Our validator must be executed first to map roles add/remove for other
  // validate & submit handlers.
  array_unshift($form['actions']['submit']['#validate'], 'gofast_og_vbo_action_user_roles_validate');
}

/**
 * Validate handler - OG user roles (VBO)
 */
function gofast_og_vbo_action_user_roles_validate(&$form, &$form_state) {
  $og_roles = $form_state['values']['og_roles'];

  $granted = array_filter($og_roles);
  $revoked = array_combine($revoked = array_keys(array_diff_key($og_roles, $granted)), $revoked);

  $form_state['values']['add_roles'] = $granted;
  $form_state['values']['remove_roles'] = $revoked;
}

/**
 * Alter og_membership_delete_action form (VBO).
 */
function gofast_og_vbo_action_membership_delete_confirm_alter(&$form, &$form_state, $context) {
  list($group_type, $gid, $space) = $context;
  $form['description']['#markup'] = str_replace(array('&lt;strong&gt;', '&lt;/strong&gt;'), '', $form['description']['#markup']);
}