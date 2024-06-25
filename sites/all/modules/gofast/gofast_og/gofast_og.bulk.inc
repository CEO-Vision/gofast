<?php

/**
 *  
 *  Admin settings & UI for Gofast Bulk admin action of OG module.
 */



/**
 * 
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @param type $ajax
 * @return string
 */
function gofast_og_space_admin_add_members_form($form, &$form_state, $ajax){
    
  $timer_start = microtime(true);
  watchdog('gofast_og', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);
  
  global $user;
  $users = gofast_og_get_visible_users();
  $form['users'] = array(
    '#type' => 'checkboxes',
    '#title' => '',
    '#options'  =>  $users,
    '#required' => TRUE,
  );

  $form['users_filter'] = array(
    '#type' => 'textfield',
    '#attributes' => array('class' => array('edit-users-filter')),
  );
  
  $ogs = gofast_cmis_get_emplacements_managed($user, "groups");
  $form['spaces'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $ogs,
    '#required' => TRUE,
    '#attributes' => array('class' => array('edit-spaces')),

  );

  $og_default_roles = og_get_default_roles(FALSE);
  $og_default_role_trad = array();
  foreach($og_default_roles as $key=>$role_string){
      $og_default_role_trad[$role_string] = t($role_string);
  }  
  $form['role'] = array(
    '#type' => 'radios',
    '#options' => $og_default_role_trad ,
    '#required' => TRUE,
    '#description' => t('Role to be assigned for the users on selected spaces',
                      array(), array('context' => 'gofast:gofast_og')),
  );
  
  $auto_sb_options= array('0' => t('No', array(), array('context' => 'gofast')), '1' => t('Yes', array(), array('context' => 'gofast')));
  $form['auto_subscribe'] = array(
    '#type' => 'hidden',
    '#options' => $auto_sb_options,
    '#default_value' => 1,
    '#title' => t('Subscription',array(), array('context' => 'gofast:gofast_og')),
    '#description' => t('Auto-subscribe to the selected spaces for all users', 
                        array(), array('context' => 'gofast:gofast_og')),
  );
    
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply', array(), array('context' => 'gofast')),
    '#validate' => array('gofast_og_space_admin_add_members_form_validate'),
    '#attributes' => array('class' => array('btn', 'btn-success', 'btn-sm')),
  );
  
   if($ajax !== FALSE){
     $form['submit']['#ajax'] = array( 
        'callback' => 'gofast_og_space_admin_add_members_callback',
        'wrapper' => 'gofast-og-admin-add-member-form',
      );
   }
  
  $form['#theme'] = 'gofast_og_space_admin_add_members'; 
  
  $timer_stop = microtime(true);
  watchdog('gofast_og', '%name() END - [execution time = %time s]',array('%name' => __FUNCTION__,  '%time' => ($timer_stop - $timer_start) ), WATCHDOG_INFO);
  
  return  $form;
}


/**
 * 
 * 
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @param type $ajax
 * @return boolean
 */
function gofast_og_space_admin_edit_members_form($form, &$form_state, $ajax){  
  global $user;
  
  $timer_start = microtime(true);
  watchdog('gofast_og', '%name() START ',array('%name' => __FUNCTION__), WATCHDOG_INFO);
  
  $ogs_users = array(); //gofast_og_space_admin_get_spacesid_and_usersid($user);
  $form['spaces_members'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $ogs_users,
    '#required' => TRUE,
    '#attributes' => array('class' => array('gofast_display_none', 'edit-spaces-members')),
  );
  
  $ogs = gofast_cmis_get_emplacements_managed($user, "groups");
  $form['spaces'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $ogs,
  );

  $og_default_roles = og_get_default_roles(FALSE);
  $og_default_role_trad = array();
  foreach($og_default_roles as $key=>$role_string){
      $og_default_role_trad [$role_string] = t($role_string);
  } 
  $form['role'] = array(
    '#type' => 'radios',
    '#options' => $og_default_role_trad ,
    '#description' => t('Role to be assigned for all selected users',
                      array(), array('context' => 'gofast:gofast_og')),
  );
  
   $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply', array(), array('context' => 'gofast')),
    '#validate' => array('gofast_og_space_admin_edit_members_form_validate'),
    '#attributes' => array('class' => array('btn', 'btn-success', 'btn-sm')),
   );
      
   $form['remove'] = array(
    '#type' => 'submit',
    '#value' => t('Remove', array(), array('context' => 'gofast')),
    '#validate' => array('gofast_og_space_admin_edit_members_form_validate'),
    '#attributes' => array('class' => array('btn', 'btn-danger', 'btn-sm')),
   );
   
   
   if($ajax != FALSE){
     $form['submit']['#ajax'] = array( 
        'callback' => 'gofast_og_space_admin_edit_members_callback',
        'wrapper' => 'gofast-og-admin-edit-member-form',
      );
     
     $form['remove']['#ajax'] = array( 
        'callback' => 'gofast_og_space_admin_edit_members_callback',
        'wrapper' => 'gofast-og-admin-edit-member-form',
      );
   }

  $form['#theme'] = 'gofast_og_space_admin_edit_members'; 
  $form['#redirect'] = FALSE;
  
  $timer_stop = microtime(true);
  watchdog('gofast_og', '%name() END - [execution time = %time s]',array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start) ), WATCHDOG_INFO);
     
  return  $form;
}

/**
 * Callback for gofast_og_space_admin_edit_members_form_submit()
 * 
 * @param type $form
 * @param type $form_state
 * @return type
 */
function gofast_og_space_admin_edit_members_callback($form, $form_state){
  
  $timer_start = microtime(true);
  watchdog('gofast_og', '%name() START ',array('%name' => __FUNCTION__), WATCHDOG_INFO);
  
  if(!form_get_errors()){
    $form_state['rebuild'] = TRUE;
    $form_state['input'] = array();
  }
  gofast_ztree_after_build($form, $form_state);
  
  $timer_stop = microtime(true);
  watchdog('gofast_og', '%name() END - [execution time = %time s]',array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start) ), WATCHDOG_INFO);
  
  return '<div id="gofast-og-admin-edit-member-form" class="row">'.drupal_render($form).'</div>';
}


/**
 * Callback for gofast_og_space_admin_add_members_form_submit()
 * 
 * @param type $form
 * @param type $form_state
 * @return type
 */
function gofast_og_space_admin_add_members_callback($form, $form_state){
  
  $timer_start = microtime(true);
  watchdog('gofast_og', '%name() START ',array( '%name' => __FUNCTION__), WATCHDOG_INFO);
  
  if(!form_get_errors()){
    $form_state['rebuild'] = TRUE;
    $form_state['input'] = array();
  }
  gofast_ztree_after_build($form, $form_state);
  
  $timer_stop = microtime(true);
  watchdog('gofast_og', '%name() END - [execution time = %time s]',array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start) ), WATCHDOG_INFO);
  
  return '<div id="gofast-og-admin-add-member-form" class="row">'.drupal_render($form).'</div>';
}


/**
 * Form validation handler for gofast_og_space_admin_add_members_form()
 * 
 * @see gofast_og_space_admin_add_members_form_submit()
 */
function gofast_og_space_admin_add_members_form_validate(&$form, &$form_state){
  if(count($form_state['values']['users']) < 1 ){
    form_set_error('users', t('There is no selected users. Please select at least 1 user.', array(), array('context' => 'gofast:gofast_og')));
    drupal_set_message(t('There is no selected users. Please select at least 1 user.', array() , array('context' => 'gofast:gofast_og') ), 'error');
  }
  if(count($form_state['values']['spaces']) < 1 ){
    form_set_error('spaces', t('There is no selected spaces. Please select a spaces.', array(), array('context' => 'gofast:gofast_og')));
    drupal_set_message(t('There is no selected spaces. Please select a spaces.', array() , array('context' => 'gofast:gofast_og') ), 'error');
  }
   if(count($form_state['values']['role']) < 1 ){
    form_set_error('role', t('There is no selected role. Please select a role to apply.', array() , array('context' => 'gofast:gofast_og')));
    drupal_set_message(t('There is no selected role. Please select a role to apply.', array() , array('context' => 'gofast:gofast_og') ), 'error'); 
  }
}

/**
 * Form validation handler for gofast_og_space_admin_edit_members_form()
 * 
 * @see gofast_og_space_admin_edit_members_form_submit()
 */
function gofast_og_space_admin_edit_members_form_validate(&$form, &$form_state){
  
  //unset error on space_member field due to all value not present at the form loading.
  gofast_form_unset_error('spaces_members');  
  
  $action = $form_state['values']['op'];
  if($action != $form_state['values']["remove"] && count($form_state['values']['role']) < 1 ){
    form_set_error('role', t('There is no selected role. Please select a role to apply.', array() , array('context' => 'gofast')) );
    drupal_set_message(t('There is no selected role. Please select a role to apply.', array() , array('context' => 'gofast') ), 'error'); 
  }
  if($action == $form_state['values']["remove"] && count($form_state['values']['spaces_members']) < 1 ){
    form_set_error('spaces_members', t('There is no selected user. Please select at least 1 user.', array() , array('context' => 'gofast:gofast_og')) );
    drupal_set_message(t('There is no selected user. Please select at least 1 user.', array() , array('context' => 'gofast') ), 'error'); 
  }
}

/**
 * Form submission handler for gofast_og_space_admin_add_members_form()
 * 
 * @see gofast_og_space_admin_add_members_form_validate()
 */
function gofast_og_space_admin_add_members_form_submit(&$form, &$form_state){
  
  $users = $form_state['values']['users'];
  $spaces = $form_state['values']['spaces'];
  $role_to_apply = $form_state['values']['role'];
  $auto_subscribe = $form_state['values']['auto_subscribe'];
  
  //clean users array - FOR PERFORMANCE GAIN
  foreach($users as $key => $user_uid){
     if($user_uid == 0){
       unset($users[$key]);
     }
   }
  
   $og_memberships_list = array();
   
  foreach($spaces as $space_id){
    
    //retrieve right role for the group
    $og_role = gofast_og_space_admin_get_node_role('node', $space_id, $role_to_apply);
    $og_role_id = key($og_role);
    foreach($users as $key => $user_uid){
      if($user_uid > 0){
        $membership = og_get_membership('node', $space_id, 'user', $user_uid);      
        if( ! $membership ){
          gofast_og_space_admin_add_membership($space_id, $user_uid, $og_role_id);
          $membership = og_get_membership('node', $space_id, 'user', $user_uid);
          $og_memberships_list[] = $membership;
        }
      }
    }     
  }
    
  drupal_set_message(t('The user have been added to the selected space(s)', array() , array('context' => 'gofast') )); 
  
  
  $timer_start = microtime(true);
  //Disabled until performance fixed cf. GOFAST-3935 + GOFAST-3976
  //gofast_og_sendmail_members_groups($og_memberships_list);
  
  $timer_stop = microtime(true);
  watchdog('gofast_og', '%name() - gofast_og_sendmail_members_groups() END - [execution time = %time s]',array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start) ), WATCHDOG_INFO);
  
  
  //empty form values
  $form_state['input'] = array();
  $form_state['rebuild'] = TRUE; 
}

/**
 * Form submission handler for gofast_og_space_admin_edit_members_form()
 * 
 * @see gofast_og_space_admin_edit_members_form_validate()
 */
function gofast_og_space_admin_edit_members_form_submit(&$form, &$form_state){
  $spaces_members = $form_state['values']['spaces_members'];
  $role_to_apply = $form_state['values']['role'];
  $action = $form_state['values']['op'];
  
  if($action == $form_state['values']["remove"]){ // Remove users form their spaces
    foreach($spaces_members as $spaces_member){
      if( strpos($spaces_member, '_' ) > -1){ //member
        $temp = explode('_', $spaces_member);
        $space_id =  $temp[0];
        $member_id = $temp[1];
        gofast_og_space_admin_delete_membership($space_id, $member_id);
      }
    }
    drupal_set_message(t('The user(s) have been succefully removed from spaces', array() , array('context' => 'gofast')));
  }else{ // Update users role
    foreach($spaces_members as $spaces_member){
      if( strpos($spaces_member, '_' ) > -1){ //member
        $temp = explode('_', $spaces_member);
        $space_id =  $temp[0];
        $member_id = $temp[1];     
        gofast_og_space_admin_update_membership($space_id, $member_id, $role_to_apply);   
      }
    }
    drupal_set_message(t('The user(s) have been succefully updated', array() , array('context' => 'gofast'))); 
  }
  
  //empty form values
  $form_state['input'] = array();
  $form_state['rebuild'] = TRUE; 
}


/**
 * Delete membership and revoke_role
 * @param type $gid
 * @param type $uid
 */
function gofast_og_space_admin_delete_membership($gid, $uid){
  $role = og_get_user_roles('node', $gid, $uid, FALSE, TRUE);
  $rid = key($role);
  if(isset($rid)){
    og_role_revoke('node', $gid, $uid, $rid);
  }
  $membership = og_get_membership('node', $gid, 'user', $uid);  
  if($membership) $membership->delete();
  
  
  $node = node_load($gid);
  $membership_data = array(
      'membership_action' => 'DMEM', // New Member
      'membership_type' => 'user',
      'membership_id' => $uid,
      'membership_name' => gofast_user_get_display_name_sql($uid)
  );
  gofast_message_ext_create_og_membership_entity($node, $membership_data);
  
  //force reset of drupal variable
  drupal_static_reset('og_get_group_members_properties');
}


/**
 * Update role on membership
 * @param type $gid
 * @param type $uid
 * @param type $role
 */
function gofast_og_space_admin_update_membership($gid, $uid, $role){
    $new_og_role = gofast_og_space_admin_get_node_role('node', $gid, $role);
    $new_rid = key($new_og_role);
  $old_og_role = og_get_user_roles('node', $gid, $uid, FALSE, TRUE);
  $old_rid = key($old_og_role);
  if(isset($old_rid)){
    og_role_revoke('node', $gid, $uid, $old_rid);
  }
  og_role_grant('node', $gid, $uid, $new_rid);
}

/**
 * Add new membership and role
 * @param type $gid
 * @param type $uid
 * @param type $rid
 */
function gofast_og_space_admin_add_membership($gid, $uid, $rid){
  global $must_propagate;
  $must_propagate = true;
  
  $og_membership = og_membership_create('node', $gid, 'user', $uid, 'og_user_node', array());
  $og_membership->state = 1; 
  $og_membership->save();
  
  $old_og_role = og_get_user_roles('node', $gid, $uid, FALSE, TRUE);
  $old_rid = key($old_og_role);
  if(isset($old_rid)){
    og_role_revoke('node', $gid, $uid, $old_rid);
  }
  og_role_grant('node', $gid, $uid, $rid);
}


/**
 * Return list of space and members in a specific format
 * To be used with ztree.
 * @param type $user
 * @return type
 */
function gofast_og_space_admin_get_spacesid_and_usersid($user){
  
  $ogs_users = array(); 
  $ogs = gofast_og_get_user_visible_spaces($user, FALSE, array('group', 'organisation', 'extranet', 'public'));
  
  foreach($ogs as $gid => $og){
    $group_entity = node_load($gid);
    $ogs_users[$gid] = $og;
    if(! gofast_og_is_root_space($group_entity )){
      $members = gofast_og_get_members($group_entity, 'active' );
      foreach($members as $key=>$memberid){   
        $ogs_users[$gid.'_'.$memberid] = $memberid;
      }
    }
 }
 return $ogs_users;
}


/**
 * Return bundle roles
 * @param type $node_type
 * @param type $group_id
 * @param type $default_role
 * @return array
 */
function gofast_og_space_admin_get_node_role($node_type, $group_id, $default_role){
  $role = array();
  $og_group_roles = og_roles($node_type, null, $group_id , FALSE, FALSE);
  foreach($og_group_roles as $key => $og_group_role){
    if($og_group_role == $default_role){
     $role = array( $key => $og_group_role);
    }
  }
  return $role;
}


/**
 * Make sure all spaces home pages are visible to the users
 */
function gofast_og_publish_all_home_pages() {
  $query = new EntityFieldQuery();
  $query->entityCondition("entity_type", "node")
  ->entityCondition('bundle', 'article')
  ->entityCondition('deleted', 0)
  ->propertyCondition('status', NODE_NOT_PUBLISHED)
  ->fieldCondition('field_is_homepage', 'value', 1);
  $result = $query->execute();
  foreach ($result['node'] as $node) {
    $node = node_load($node->nid);
    $node = gofast_prepare_node_save_technically($node);
    $ruid = $node->revision_uid;
    $node->status = NODE_PUBLISHED;
    node_save($node);
    db_update('node_revision')
          ->fields(array('uid' => $ruid))
          ->condition('nid', $node->nid)
          ->execute();
        cache_clear_all("field:node:$node->nid", 'cache_field');
  }
}