<?php

/**
 * Implements hook_form_FORM_ID_alter()
 *
 * @param type $form
 * @param type $form_state
 * @param type $form_id
 */
function gofast_userlist_og_form_og_ui_add_users_alter(&$form, &$form_state, $form_id) {

  $group_type = $form_state['build_info']['args'][0];
  $gid = $form_state['build_info']['args'][1];

  $group = entity_load_single($group_type, $gid);
  $label = entity_label($group_type, $group);

  $form['og_user']['#title'] = t('Add a group member or a userlist to %group', array('%group' => $label));

  $form['og_user']['member_entity_type'] = array(
    '#type' => 'hidden'
  );

  $form['og_user']['member_entity_id'] = array(
    '#type' => 'hidden'
  );

  $attributes_name = [
    'class' => [' form-control-tags js-tagify'],
    //'data-enforce' => '', //  Comment : Do not allow putting data that dose not exist | Decomment : allow putting data that dose not exist
    'data-user' => '', // show ac users
    //'data-node' => '', // show ac node
    'data-userlist' => '', // show ac userlist
    //'data-taxonomy_term' => '' // show ac taxonomy term
  ];

  $form['og_user']['name']=[
      '#title' => t('User or Userlist name ', array(), array('context' => 'gofast_og_userlist')),
      '#type' => 'textfield',
      '#attributes' => $attributes_name,
      '#name' => 'ac-list-tags-field-user-userlist'
  ];

  $form['actions']['submit']['#value'] = t('Add new member(s)', array(), array('context' => 'gofast_og_userlist'));

  $form['#attached']['js'][] = drupal_get_path('module', 'gofast_userlist_og') . '/js/gofast_userlist_og.js';
}


/**
 * Implements hook_form_FORM_ID_alter()
 */
function gofast_userlist_og_form_og_ui_edit_membership_alter(&$form, &$form_state) {
  if (!isset($form['membership_fields']['#entity'])) {
    return;
  }

  $og_membership = $form['membership_fields']['#entity'];

  if ($og_membership->entity_type === 'userlist') {

    $member = entity_load_single('userlist', $og_membership->etid);

    $form['membership_fields']['#access'] = FALSE;
    $form['og_user']['state']['#access'] = FALSE;

    $form['og_user']['name'] = array(
      '#type' => 'markup',
      '#title' => t('Userlist', array(), array('context' => 'gofast')),
      '#markup' => theme('gofast_userlist_autocomplete_view', array('userlist' => $member)),
      '#suffix' => '<br/><br/>'
    );

    // Prevent from assigning more than one role to a member (same logic as
    // gofast_user_account_form_alter().
    $form['og_user']['roles']['#attributes'] = array('class' => array('og-roles-force-single'));
    $form['og_user']['roles']['#attached']['js'] = array(array(
        'data' => drupal_get_path('module', 'gofast_og') . '/gofast_og.js',
        'type' => 'file',
        'scope' => 'footer',
        'weight' => 5
    ));

    if (count($form['og_user']['roles']["#options"]) > 0) {
      foreach ($form['og_user']['roles']["#options"] as $rid => $role_string) {
        $form['og_user']['roles']["#options"][$rid] = t($role_string, array(), array("context" => "gofast"));
      }
    }

    //Get this userlist role to assign it to default value
    $form['og_user']['roles']["#default_value"] = array_keys(gofast_userlist_og_get_userlist_roles("node", $og_membership->gid, $og_membership->etid));

    if (!isset($form['actions']['delete'])) {
      $form['actions']['delete'] = array(
        '#type' => 'markup',
        '#markup' => l(t('Remove'), 'group/node/' . $og_membership->gid . '/admin/userlist/delete-membership/' . $og_membership->id),
      );
    }

    if (isset($form['actions']['delete']['#markup'])) {
      $path = "spaces/nojs/node/{$og_membership->gid}/admin/userlist/delete-membership/{$og_membership->id}";
      $form['actions']['delete']['#markup'] = gofast_button(t('Remove'), $path, 'btn-danger', 'glyphicon-trash', array('class' => array('ctools-use-modal')));
    }
    $form['#submit'] = array(
      "gofast_userlist_og_edit_membership_submit"
    );
    $form['actions']['submit']['#attributes'] = array('class' => array('btn-success'));
  }
}

/**
 * Submit handler; Edit membership in group.
 */
function gofast_userlist_og_edit_membership_submit($form, &$form_state) {

  //temporary disactivate membership propagation to prevent random bugs
  global $must_propagate;
  $must_propagate = false;

  $space_id = $form_state['values']['gid'];
  $node = node_load($space_id);
  $current_membership = og_membership_load($form_state['values']['id']);

  //retrieve right role for the group
  foreach ($form_state['values']['roles'] as $key => $role) {
    if (is_string($role)) {
      $role_id = $role;
      $role_name = og_role_load($role_id)->name;
    }
  }

  if (isset($role_name)) {
    gofast_userlist_og_update_membership($space_id, $current_membership->etid, $role_name);
    $must_propagate = true;
  }
  else {
    gofast_userlist_og_delete_membership($space_id, $current_membership->etid);
  }
}

/**
 * Implements hook_form_FORM_ID_alter()
 * Delete a single membership from group.
 */
function gofast_userlist_og_form_og_ui_delete_membership($form, &$form_state, $group_type, $gid, $og_membership) {
  og_set_breadcrumb($group_type, $gid, array(l(t('Group'), "$group_type/$gid/group")));
  $group = entity_load_single($group_type, $gid);
  $label = entity_label($group_type, $group);

  // Add group membership form. We still don't have the user or state.
  $form_state['og_membership'] = $og_membership;
  $form['#validate'][] = "gofast_userlist_og_form_og_ui_delete_membership_validate";

  if ($og_membership->entity_type == 'userlist') {

    $form['#submit'] = array(
      "gofast_userlist_og_delete_membership_submit"
    );

    $member = entity_load_single('userlist', $og_membership->etid);

    $confirm_form = confirm_form($form,
        t('Remove membership in group @group', array('@group' => $label)),
        'group/' . $og_membership->group_type . '/' . $og_membership->gid . '/admin/people',
        '</br>' . "<div class='alert alert-block alert-dismissible alert-warning messages warning'>" . '<i class="fa fa-exclamation-triangle" style="color:#F0AD4E;font-size:1.5em"> </i>  ' . t('Warning: If you delete a userlist from the space, users in this list will also be removed from their child spaces') . "</div>" . t('Are you sure you would like to remove the membership for the userlist @userlist?', array('@userlist' => $member->name)),
        t('Remove'),
        t('Cancel')
    );
    $confirm_form['actions']['cancel']['#attributes'] = array('class' => array('btn', 'btn-secondary'));
    return $confirm_form;
  }
}

/**
 * Implements validation of membership deletion form
 */
function gofast_userlist_og_form_og_ui_delete_membership_validate($form, &$form_state) {
    $membership = $form_state['og_membership'];

    $userlist_id = $membership->etid;
    $node = node_load($membership->gid);

    //Check if we are impacting an administrator membership
    $roles = gofast_userlist_og_get_userlist_roles("node", $node->nid, $userlist_id);

    if(in_array("administrator member", $roles, TRUE)){
        //Check cound of administrators in this space
        $users_admins = gofast_userlist_og_get_node_members_by_role($node->nid, array(OG_STATE_ACTIVE), "administrator member");
        if(count($users_admins) < 2){
            $form_state['last_admin'] = TRUE;
            form_set_error("last_admin", t("You can't remove the last administrator of a space", array(), array('context' => "gofast:gofast_og")));
        }
    }
}

/**
 * Submit handler;Delete the membership.
 */
function gofast_userlist_og_delete_membership_submit($form, &$form_state) {
  $membership = $form_state['og_membership'];
  $membership->delete();

  $userlist = entity_load_single('userlist', $membership->etid);
  $node = node_load($membership->gid);

  // Get all members of the remove userlist
  $userlist_members = gofast_userlist_get_members($userlist->ulid);
  foreach($userlist_members as $uid => $theme_user){
    $user_removed = user_load($uid);
    $check = gofast_og_check_spaces_user($membership->entity_type, $user_removed, $membership->gid);
    if ($check == FALSE) {
      gofast_og_sendmail_delete_membership_user($user_removed, array($node), NULL);
    }
  }

  $membership_data = array(
          'membership_action' => 'DMEM', // Delete Member
          'membership_type' => 'userlist',
          'membership_id' => $membership->etid,
          'membership_name' => $userlist->name
        );
  gofast_message_ext_create_og_membership_entity($node, $membership_data);

  //Log into audit
  gofast_userlist_audit_membership($node, $membership_data);

  $form_state['redirect'] = 'group/' . $membership->group_type . '/' . $membership->gid . '/admin/people';


  drupal_set_message(t('The membership was removed.'));
}
