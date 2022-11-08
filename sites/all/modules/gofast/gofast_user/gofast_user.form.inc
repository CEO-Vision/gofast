<?php

module_load_include('module', 'gofast_mobile');

/**
 * Gofast admin user roles form builder.
 */
function gofast_user_edit_roles_form($form, $form_state, $account)
{
  $form['info'] = array(
    '#markup' => '<div>' . theme('username', array('account' => $account)) . '<hr></div>'
  );

  $form['roles'] = array(
    '#title' => t('Edit user profiles', array(), array('context' => 'gofast:gofast_user')),
    '#type' => 'checkboxes',
    '#options' => $roles = gofast_user_roles(),
    '#default_value' => array_keys(array_intersect_key($roles, $account->roles)),
    '#access' => user_access('administer roles'),
    '#attached' => array('js' => array(array(
      'data' => drupal_get_path('module', 'gofast_user') . '/js/gofast_user.js',
      'type' => 'file',
      'scope' => 'footer',
      'weight' => 5
    )))
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save', array(), array('context' => 'gofast'))
  );

  return $form;
}

/**
 * Submit callback for edit user roles form.
 */
function gofast_user_edit_roles_form_submit($form, $form_state)
{
  $account = $form_state['build_info']['args'][0];
  $roles = gofast_user_roles();

  $selected = array_filter($form_state['values']['roles']);
  $rid = reset($selected);
  $role_name = $roles[$rid];

  // Only submit changes.
  if (!gofast_user_has_role($role_name, $account)) {
    // Apply single-role policy.
    foreach ($roles as $_rid => $_name) {
      unset($account->roles[$_rid]);
    }
    $account->roles[$rid] = $role_name;
  }

  user_save($account);
}

function gofast_user_node_add_user() {

    $node = new stdClass();
    $node->type = "private_space";
    $user_register_form = drupal_get_form('user_register_form', $node);
    $content = theme('page_user_register_form', ['form' => $user_register_form]);
    $pageContent = gofast_create_page_content($content);

    return $pageContent;
}

function gofast_user_set_group_roles_form_field(&$form) {
  // Ideally we would use the gofast_user_get_and_order_profile_options() helper to make this code more readable,
  // but that could possibly break some already existing validation/submission logic, so we'll just do it manually.

  // Set default value for user roles.
  $role_admin = user_role_load_by_name(GOFAST_ROLE_ADMIN);
  $role_contrib = user_role_load_by_name(GOFAST_ROLE_CONTRIBUTOR);
  $role_ro = user_role_load_by_name(GOFAST_ROLE_READ_ONLY);
  $role_ba = user_role_load_by_name(GOFAST_ROLE_BUSINESS_ADMIN);

  //Value for administrator is 'Super Administrator'
  $form['group_roles']['roles']['#options'][$role_admin->rid] = t(GOFAST_ROLE_SUPER_ADMIN_VALUE, array(), array('context' => 'gofast:user'));
  $form['group_roles']['roles'][$role_admin->rid]['#attributes']['class'][] = 'role_administrator';
  $form['group_roles']['roles'][$role_admin->rid]['#description'] = t('The Super-Administrator can manage all aspects of the site.', array(), array('context' => 'gofast:user'));
  $form['group_roles']['roles'][$role_admin->rid]['#weight'] = -1;
  $form['group_roles']['roles'][$role_admin->rid]['#suffix'] = "<hr>";

   //Add custom class to allow business-administrator selection WITH another role
  $form['group_roles']['roles']['#options'][$role_ba->rid] = t(GOFAST_ROLE_BUSINESS_ADMIN_VALUE, array(), array("context" => "gofast"));
  $form['group_roles']['roles'][$role_ba->rid]['#attributes']['class'][] = 'role_business_adm'; 
  $form['group_roles']['roles'][$role_ba->rid]['#description'] = t("The profile @role is meant to help Spaces and Platforms' Administrators . It allows access to additional features (users management, edit some plateform's configurations, contact the spaces' administrators, etc.)", array("@role" => t(GOFAST_ROLE_BUSINESS_ADMIN_VALUE, array(), array("context" => "gofast"))), array('context' => 'gofast:user'));
  $form['group_roles']['roles'][$role_ba->rid]['#weight'] = -2;

  $form['group_roles']['roles']['#options'][$role_contrib->rid] = t('Standard', array(), array('context' => 'gofast:user'));
  $form['group_roles']['roles'][$role_contrib->rid]['#attributes']['class'][] = 'role_contributor';
  $form['group_roles']['roles'][$role_contrib->rid]['#description'] = t('The Standard user can read and manage authorized contents but will not be able to manager other users.', array(), array('context' => 'gofast:user'));
  $form['group_roles']['roles'][$role_contrib->rid]['#weight'] = -3;

  $form['group_roles']['is_extranet']['#suffix'] = "<hr>";
  $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#title'] = t("External", array(), array('context' => 'gofast:user'));
  $form['group_roles']['is_extranet']['#prefix'] ='<label class="control-label" >'.t('Type', array(), array('context' => 'gofast')).'</label>';

  $form['group_roles']['is_broadcaster']['#prefix'] ='<label class="control-label" >'.t('Permissions', array(), array('context' => 'gofast')).'</label>';

  //Add custom classes on flag to trigger js
  $form['is_extranet']['#attributes']['class'][] = 'flag_extranet';
  $form['is_broadcaster']['#attributes']['class'][] = 'flag_broadcaster';
  $form['gofast_default_role']['field_default_role']['#attributes']['class'][] = 'default_roles';

  //Unset read only choice
  unset($form['account']['roles']['#options'][$role_ro->rid]);
  unset($form['group_roles']['roles']['#options'][$role_ro->rid]);

  $form['group_roles']['roles']['#multiple'] = TRUE;
  $form['group_roles']['#keen-accordion'] = TRUE;
  $form['group_roles']['#collapsed'] = TRUE;
}

/**
 * Implements hook_form_FormID_alter()
 */
function gofast_user_form_user_register_form_alter(&$form, &$form_state)
{
  global $user;
  gofast_user_account_form_alter($form, $form_state, 'user_register_form');
  gofast_user_set_group_roles_form_field($form);
  // default value is "Standard"
  $form['group_roles']['roles']['#default_value'] = array(user_role_load_by_name(GOFAST_ROLE_CONTRIBUTOR)->rid);

  $form['#validate'][] = 'gofast_user_username_field_validate';
  $form['wrapper_account']['name']['#description'] = 'Username has to be between 5-15 characters long and can only contain letters and numbers';

  if (!empty($_GET['gids']) && empty($form_state[GOFAST_OG_USER_MEMBERSHIP_FIELD])) {
    $form[GOFAST_OG_USER_MEMBERSHIP_FIELD][LANGUAGE_NONE][0]['default']['#default_value'] = $_GET['gids'];
  }

  //We check if the user that is creating the new account has admin privileges to
  //some organisations and build the form according to that
  foreach ($form['ldap_user_ou'][LANGUAGE_NONE]['#options'] as $gid => $name) {
    if (is_numeric($gid) && !in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $gid, $user->uid), true)) {
      unset($form['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid]);
      unset($form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid]);
    }
  }

  if ($user->uid == 1) {
    $spaces = array_merge(gofast_og_get_children("4", TRUE, FALSE, TRUE), gofast_og_get_children("5", TRUE, FALSE, TRUE), gofast_og_get_children("6", TRUE, FALSE, TRUE), gofast_og_get_children("7", TRUE, FALSE, TRUE));
    foreach ($spaces as $gid) {
      $form['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid] = gofast_get_node_title($gid);
      $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid] = gofast_get_node_title($gid);
    }
  }

  //Move notify to message panel
  $form["message"]["notify"] = $form['group_complement']['notify'];
  unset($form['group_complement']['notify']);

  //Retrieve saved user form configuration
  $default_user_form_configuration = array(
    'sasl_auth' => variable_get('gofast_sasl_auth', 0),
    'extranet' => FALSE,
    'broadcaster' => FALSE,
    'comment_restricted' => FALSE,
    'default_role' => "1",
    'notify' => TRUE
  );
  $user_form_defaults = variable_get("user_form_defaults", $default_user_form_configuration);

  $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#default_value'] = $user_form_defaults['sasl_auth'];
  $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#default_value'] = $user_form_defaults['extranet'];
  $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#title'] = t("External", array(), array('context' => 'gofast:user'));
  $form['group_roles']['is_extranet']['#suffix'] = "<hr>";
  $form['group_roles']['is_extranet']['#prefix'] ='<label class="control-label" >'.t('Type', array(), array('context' => 'gofast')).'</label>';

  $form['group_roles']['is_broadcaster']['#prefix'] ='<label class="control-label" >'.t('Permissions', array(), array('context' => 'gofast')).'</label>';
  $form['group_roles']['is_broadcaster'][LANGUAGE_NONE]['#default_value'] = $user_form_defaults['broadcaster'];
  $form['group_roles']['field_is_comment_restricted'][LANGUAGE_NONE]['#default_value'] = $user_form_defaults['comment_restricted'];

  $form['gofast_default_role']['field_default_role']['und']["#default_value"] = $user_form_defaults['default_role'];

  $form['group_complement_notify']['notify']["#default_value"] = $user_form_defaults['notify'];

  //add hidden field to manage creator's response if account with same mail already exists
  $form['email_already_exists_confirmed']["#type"] = "hidden";
  $form['email_already_exists_confirmed']["#default_value"] = 0;

  $form['#validate'][] = 'gofast_user_form_user_register_form_validate';

  //add custom validate to manage create user with mail already taken
  $form['#validate'][] = 'gofast_user_account_validate';

  $form['#attributes']['class'][] = 'GofastForm GofastForm__UserRegister';
  $form['group_account']['#keen-accordion'] = TRUE;
  $form['group_account']['#collapsible'] = TRUE;
  $form['group_account']['#collapsed'] = FALSE;
  $form['gofast_default_role']['#keen-accordion'] = TRUE;
  $form['gofast_default_role']['#collapsed'] = TRUE;
  //Need to add Keen Flag after field build
  $form['#after_build'][] = 'gofast_user_accordion_userlist';
  $form['group_profile_data']['#keen-accordion'] = TRUE;
  $form['group_profile_data']['#collapsed'] = TRUE;
  $form['og_user_node']['#keen-accordion'] = TRUE;
  $form['og_user_node']['#collapsed'] = TRUE;
  $form['wrapper_language_settings_info']['locale']['#keen-accordion'] = TRUE;
  $form['message']['#keen-accordion'] = TRUE;

}
function gofast_user_accordion_userlist(&$form, &$form_state){
    if(isset($form['og_userlist_node']['userlists']) && count($form['og_userlist_node']['userlists']['#options'])){
        $form['og_userlist_node']['#keen-accordion'] = TRUE;
         $form['og_userlist_node']['#collapsed'] = TRUE;
    }
    else{
         $form['og_userlist_node']['#access'] = FALSE;
    }
    return $form;
}

function gofast_user_form_user_register_form_validate(&$form, &$form_state) {
    $errors = form_get_errors();
    if ($errors) {

      foreach ($errors as $name => $error_message) {
          if ($name == 'mail') {
              break;
          }
        $commands[] = gofast_command_toast_message($error_message, "error");
      }
      if (isset($commands)) {
        print ajax_render($commands);exit;
      }
    }
}

function gofast_user_account_validate($form, &$form_state)
{
  global $user;
  $errors = form_get_errors();
  if ($errors) {
    // Clear errors.
    form_clear_error();
    // Clear error messages.
    $error_messages = drupal_get_messages('error');
    // Initialize an array where removed error messages are stored.
    $removed_messages = array();

    // Remove all errors originated by the 'foo][bar' element.
    foreach ($errors as $name => $error_message) {

      if ($name == 'mail') {
        // error is about mail. Check if a user alreasy exists with same mail. If yes, check if this user is blocked. If yes, discard the error
        $mail = $form_state["values"]["mail"];
        $existing_user = user_load_by_mail($mail);
        //be sure we don't load user we are currently edit
        $editing_user = $form['#user'];
        if (isset($editing_user->uid)) {
          if ($existing_user->uid == $editing_user->uid) {
            $existing_users = user_load_multiple(array(), array('mail' => $mail));
            foreach ($existing_users as $uid => $my_user) {
              if ($uid !== $editing_user->uid) {
                $existing_user = $my_user;
              }
            }
          }
        }
      }
    }

    // Reinstate remaining errors, except if it concern the og_group_content_ref field and if the broadcast field is fill
    foreach ($errors as $name => $error) {
      form_set_error($name, $error);
      // form_set_error() calls drupal_set_message(), so we have to filter out
      // these from the error messages as well.
      $removed_messages[] = $error;
    }

    // Reinstate remaining error messages (which, at this point, are messages that
    // were originated outside of the validation process).
    foreach (array_diff($error_messages['error'], $removed_messages) as $message) {
      drupal_set_message($message, 'error');
    }
  }
}

function gofast_user_username_field_validate($form, &$form_state)
{

  $output['error'] = FALSE;
  $username = $form_state['input']['name'];

  if (strlen($username) < 2 || strlen($username) > 50) {
    $output['error'] = TRUE;
    $output['msg'] = t('The username has to be between 2 and 50 characters long. ', array(), array('context' => 'gofast:gofast_user'));
  }
  if (strpos($username, ' ') > 0 || strpos($username, "'") !== FALSE) {
    $output['error'] = TRUE;
    $output['msg'] = t('Username cannot contain spaces or ' . chr(39), array(), array('context' => 'gofast:gofast_user'));
  }

  //display username errors
  if ($output['error']) {
    //drupal_set_message( $output['msg'], 'error');
    form_set_error('name', $output['msg']);
  }
}

/**
 * Implements hook_form_FormID_alter()
 */
function gofast_user_form_user_profile_form_alter(&$form, &$form_state)
{
  global $user;
  if ($user->uid == 1) {
    return;
  }

  // Only use for edit profile
  $form_state['is_admin'] = FALSE;

  $editing_user = $form['#user'];
  gofast_user_account_form_alter($form, $form_state, 'user_profile_form');
  gofast_ldap_profile_forms_alter($form, $form_state);

  // This reorganize method changed the element tree, wrapper...
  gofast_ldap_reorganize_user_register_form_elements($form, $form_state);
  gofast_user_set_group_roles_form_field($form);

  //translate
  gofast_user_account_form_translate_field($form);

  // The username is readonly
  $form['group_account']['wrapper_account']['name']['#attributes']['readonly'] = 'readonly';
  $form['picture']['#access'] = FALSE;

  $self = FALSE;
  if ($editing_user->uid == $user->uid) {
    //only for current user
    $form['group_account']['account']['mail']['#access'] = TRUE;
    $form['group_account']['account']['pass']['#access'] = TRUE;
    $form['actions']['cancel']['#access'] = FALSE;
    $self = TRUE;
  } else {
    $form['group_account']['account']['mail']['#access'] = FALSE;
    $form['group_account']['account']['pass']['#access'] = FALSE;
    $form['actions']['cancel']['#access'] = FALSE;
  }

  $can_be_edited = FALSE;
  if (gofast_user_is_adm() || gofast_user_is_adm($editing_user) || user_access('gofast administer user')) {
    $can_be_edited = TRUE;
  }


  $form['#attributes']['class'][] = 'GofastForm GofastForm__UserRegister';
  $form['group_account']['#keen-accordion'] = TRUE;
  $form['group_account']['#collapsible'] = TRUE;
  $form['group_account']['#collapsed'] = FALSE;
  $form['gofast_default_role']['#keen-accordion'] = TRUE;
  $form['gofast_default_role']['#collapsed'] = FALSE;

  $form['field_birthdate']['#access'] = $self;
  //Can only be editable via xeditable;
  $form['field_hobbies']['#access'] = FALSE;
  $form['field_interests']['#access'] = FALSE;
  $form['field_skills']['#access'] = FALSE;

  $form[GOFAST_OG_USER_MEMBERSHIP_FIELD]['#access'] = $can_be_edited;
  $form['user_relationships_ui_settings']['#access'] = $can_be_edited;

  $form['group_profile_data']['ldap_user_title']['#access'] = $self;
  $form['group_profile_data']['ldap_user_o']['#access'] = $can_be_edited;
  $form['group_profile_data']['ldap_user_telephonenumber']['#access'] = $self;
  $form['group_profile_data']['ldap_user_mobile']['#access'] = $self;
  $form['group_profile_data']['ldap_user_title']['#access'] = $self;
  $form['group_profile_data']['#keen-accordion'] = TRUE;
  $form['group_profile_data']['#collapsible'] = TRUE;
  $form['group_profile_data']['#collapsed'] = FALSE;
  $form['wrapper_language_settings_info']['locale']['#keen-accordion'] = TRUE;
  $form['wrapper_language_settings_info']['locale']['#collapsible'] = TRUE;
  $form['wrapper_language_settings_info']['locale']['#collapsed'] = FALSE;
  $form['account']['status']['#access'] = $can_be_edited;

  if (!gofast_user_is_adm() || gofast_user_is_adm($editing_user)) {
    $form['group_profile_data']['#access'] = $can_be_edited;
    $form['group_profile_data']['ldap_user_ou']['#access'] = $can_be_edited;
    $form['group_complement']['#access'] = $can_be_edited;
  }

  if ($self) {
    $form['group_profile_data']['#access'] = $self;
  }

  $form['group_roles']['#access'] = $can_be_edited;
  $form['gofast_default_role']['#access'] = $can_be_edited;

  // Adding field to fieldset should be done in the after_build for conserving the add-on in manager textbox
  $form['#after_build'][] = 'gofast_ldap_add_to_fieldset';

  //Hide useless group complements
  $form['group_complement']["#type"] = "hidden";

  //add custom validate to manage edit user with mail already taken
  $form['#validate'][] = 'gofast_user_account_validate';

  if (!$editing_user->uid) {
  } else {
    ctools_include('modal');
    ctools_include('ajax');
    $dest = "modal/nojs/{$editing_user->uid}/manage_main_orga";
    $alt = t('Manage main organization', array(), array('context' => 'gofast_manage_main_organization'));
    $contentButton = ctools_modal_text_button($alt, $dest, $alt, 'blue-hover manage_main_organization');
    $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]["#suffix"] = $contentButton;
    if ($form_state['modal_orga'] == TRUE) {
      //We check if the user that is creating the new account has admin privileges to
      //some organisations and build the form according to that
      foreach ($form['ldap_user_ou'][LANGUAGE_NONE]['#options'] as $gid => $name) {
        if ($gid == $form['ldap_user_ou'][LANGUAGE_NONE]['#default_value']) { //Bypass for current organization
          continue;
        }
        if (is_numeric($gid) && !in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $gid, $user->uid), true)) {
          unset($form['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid]);
          unset($form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#options'][$gid]);
        }
      }
      unset($form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]["#suffix"]); //delete button Manage main organization in modal 'Manage main organization'
    } else {
      $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]["#disabled"] = TRUE;
    }
  }

  // override ldap features label settings
  $form['group_profile_data']['ldap_user_title'][LANGUAGE_NONE][0]['value']['#title'] = t('Function', array(), array('context' => 'gofast:gofast_ldap'));
  $form['group_profile_data']['ldap_user_o'][LANGUAGE_NONE][0]['value']['#title'] = t('Entity', array(), array('context' => 'gofast'));
  
  if(isset($_SESSION['pass_reset_' . $user->uid])){
    //We are reseting our password, hide all other fields and format form
    $form['group_profile_data']["#type"] = "hidden";
    $form['wrapper_language_settings_info']["#type"] = "hidden";
    $form['wrapper_language_settings_info']['locale']["#type"] = "hidden";
    
    $form['group_account']['wrapper_account']["#type"] = "hidden";
    $form['group_account']['account']['mail']["#type"] = "hidden";
    
    $form['group_account']['#title'] = t("Reset your password", array(), array('context' => "gofast"));
    
    $form["#prefix"] = '<div class="card ml-5 mr-5 mt-2">';
    $form["#suffix"] = '</div>';
    
    $form['actions']['submit']['#ajax'] = [
      'wrapper' => 'ajax_content',
      'callback' => 'gofast_user_ajax_submit_edit_user'
    ];
  }

   $form['wrapper_timezone'] = array('#type' => 'container',
                                      '#attributes' => array(
                                            'class' => array('row', 'wrapper_language_settings_info')
                                     ));
   
   $form['wrapper_timezone']["#type"] = "fieldset";
   $form['wrapper_timezone']["timezone"] = $form['timezone'];
   $form['wrapper_timezone']["timezone"]['#collapsible'] = TRUE;
   $form['wrapper_timezone']["timezone"]['#collapsed'] = FALSE;
   $form['wrapper_timezone']["timezone"]["#theme_wrappers"][] = "bootstrap_panel";
   $form['wrapper_timezone']["timezone"]["#keen-accordion"] = true;
   unset($form['timezone']);
}

function gofast_user_ajax_submit_edit_user(&$form, &$form_state) {
  global $user;
  $commands = array();
  if ($errors = form_get_errors()) {
    $form_state['rebuild'] = TRUE;
    $error_msg = theme('status_messages');
    $output = drupal_rebuild_form($form['#form_id'], $form_state, $form);
    // $commands[] = ajax_command_html('#messages-placeholder', $error_msg);
    $output = $error_msg . render($output);
    $output = gofast_normalize_string_from_ajaxifying($output);
        
    $commands[] = array(
      'command' => 'error_creating_node',
      'form' => $output,
      'custom_fields' => array(GOFAST_OG_CONTENT_MEMBERSHIP_FIELD),
      'errors' => $errors,
      'wrapper' => '#ajax_content'
    );
  } else {
    gofast_user_form_submit($form, $form_state);
    $commands[] = gofast_command_processAjax("/");
  }
      
  return array('#type' => 'ajax', '#commands' => $commands);
}


/**
 * This is the form that block a user
 * @param type $form
 * @param array $form_state
 * @return array the form
 */
function gofast_blocked_user_form($form, &$form_state)
{
  $uid = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : FALSE;
  $user = user_load($uid);

  // These two submit handlers unpublish then remove link between node and publication
  $form['#submit'] = array(
    'gofast_blocked_user_form_submit',
  );
  $uid_to_block = $uid;
  $form['#uid_to_block'] = $uid_to_block;

  $confirm_form = confirm_form(
    $form,
    t('Block this user', array(), array('context' => 'gofast')) . ' ' . $user->name,
    isset($_GET['destination']) ? $_GET['destination'] : 'user/' . $user->uid,
    t('Are you sure you want to block this user?', array(), array('context' => 'gofast:gofast_user')),
    t('Block', array(), array('context' => 'gofast')),
    t('Cancel', array(), array('context' => 'gofast'))
  );

  $confirm_form['actions']['cancel']['#type'] = "submit";
  $confirm_form['actions']['cancel']['#value'] = t('Cancel');
  $confirm_form['actions']['cancel']['#attributes'] = array(
      'id' => 'edit-cancel',
      'class' => array('btn', 'btn-secondary')
  );
  return $confirm_form;
}

function gofast_blocked_user_form_submit($form, &$form_state)
{
  global $user;

  //Get the uid to insert in the audit
  $uid_to_block = $form['#uid_to_block'];

  $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'user_blocked', 'uid_to_block' => $uid_to_block);
  $event = serialize($event);
  $last_event_serialized = rawurlencode($event);

  $last_event_unserialized["mod_timestamp"] = time();
  $last_event_unserialized["mod_author"] = $user->uid;

  //Insert inton audit
  gofast_audit_insert_line_audit(0, 'user_blocked', $last_event_serialized, $last_event_unserialized); //The value 0 is define in order to not render node in the audit
  gofast_user_block($uid_to_block);
}

/**
 * This is the form that unblock a user
 * @param type $form
 * @param array $form_state
 * @return array the form
 */
function gofast_unblocked_user_form($form, &$form_state)
{
  $uid = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : FALSE;
  $user = user_load($uid);

  // These two submit handlers unpublish then remove link between node and publication
  $form['#submit'] = array(
    'gofast_unblocked_user_form_submit',
  );

  $uid_to_block = $uid;
  $form['#uid_to_block'] = $uid_to_block;
  $confirm_form = confirm_form(
    $form,
    t('Block this user', array(), array('context' => 'gofast')) . ' ' . $user->name,
    isset($_GET['destination']) ? $_GET['destination'] : 'user/' . $user->uid,
    t('Are you sure you want to unblock this user?', array(), array('context' => 'gofast:gofast_user')),
    t('Unblock', array(), array('context' => 'gofast')),
    t('Cancel', array(), array('context' => 'gofast'))
  );
  $confirm_form['actions']['cancel']['#type'] = "submit";
  $confirm_form['actions']['cancel']['#value'] = t('Cancel');
  $confirm_form['actions']['cancel']['#attributes'] = array(
      'id' => 'edit-cancel',
      'class' => array('btn', 'btn-secondary')
  );
  return $confirm_form;
}

function gofast_unblocked_user_form_submit($form, &$form_state)
{
  $uid_to_block = $form['#uid_to_block'];
  gofast_user_unblock($uid_to_block);
}

function gofast_delete_user_form($form, &$form_state) //Delete user - task
{
  $uid = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : FALSE;
  $user = user_load($uid);

  $form['#submit'] = array(
    'gofast_delete_user_form_submit',
  );
  $form['#uid_to_delete'] = $uid;
  $confirm_form = confirm_form(
    $form,
    t('Delete this user', array(), array('context' => 'gofast')) . ' ' . $user->name,
    isset($_GET['destination']) ? $_GET['destination'] : 'user_listing_tab',
    t('Are you sure you want to delete this user ?', array(), array('context' => 'gofast:gofast_user'))
  );
  $confirm_form['actions']['cancel']['#type'] = "submit";
  $confirm_form['actions']['cancel']['#value'] = t('Cancel');
  $confirm_form['actions']['cancel']['#attributes'] = array(
      'id' => 'edit-cancel',
      'class' => array('btn', 'btn-secondary')
  );
  return $confirm_form;
}

// Function delete user
function gofast_delete_user_form_submit($form, &$form_state)
{

  global $user;

  $user_to_delete_datas = user_load($form['#uid_to_delete']); // load user Datas
  $isAdmin = !empty($user->roles['3']);


  if ($user_to_delete_datas->access == 0 && $isAdmin) {

    // 1- function that delete user data in ldap
    gofast_ldap_user_delete($user_to_delete_datas);

    // 2- Function that delete user data in Bonita
    // we create the cookie as admin bonita
    $cookie_name = "cookie_bonita" . BONITA_TECHNICAL_LOGIN . ".txt";
    $workflows_user_id = gofast_workflows_get_user_id($user_to_delete_datas);

    if ($workflows_user_id != null && isset($variable_association[$user_to_delete_datas->uid])) {
      gofast_workflows_curl_delete_user($workflows_user_id, $cookie_name);
      $variable_association = variable_get(VARIABLE_NAME_ID_BONITA, array());
      unset($variable_association[$user_to_delete_datas->uid]);
      variable_set(VARIABLE_NAME_ID_BONITA, $variable_association);
    }

    //Insert into audit
    $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'delete_user', "user_delete_name" => gofast_message_ext_api_get_user_name($user_to_delete_datas->uid));
    $event = serialize($event);
    $last_event_serialized = rawurlencode($event);
    $last_event_unserialized["mod_timestamp"] = time();
    $last_event_unserialized["mod_author"] = $user->uid;
    gofast_audit_insert_line_audit(0, 'delete_user', $last_event_serialized, $last_event_unserialized);

    // 3- delete user data from drupal BDD
    user_delete($user_to_delete_datas->uid);
  }
}

function gofast_leave_user_form($form, &$form_state)
{
  $uid = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : FALSE;
  $user = user_load($uid);

  $form['#submit'] = array(
    'gofast_leave_user_form_submit',
  );
  $form['#uid_to_block'] = $uid;
  $confirm_form = confirm_form(
    $form,
    t('Disable this user', array(), array('context' => 'gofast')) . ' ' . $user->name,
    isset($_GET['destination']) ? $_GET['destination'] : 'user/' . $uid,
    t('Are you sure you want to disable this user?', array(), array('context' => 'gofast:gofast_user'))
  );
  $confirm_form['actions']['cancel']['#attributes'] = array('class' => array('btn', 'btn-secondary'));
  return $confirm_form;
}

function gofast_leave_user_form_submit($form, &$form_state)
{
  $uid_to_block = $form['#uid_to_block'];
  gofast_user_leave_user($uid_to_block);
}

function gofast_unleave_user_form($form, &$form_state)
{
  $uid = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : FALSE;
  $user = user_load($uid);

  $form['#submit'] = array(
    'gofast_unleave_user_form_submit',
  );
  $last_url = $_SERVER['HTTP_REFERER'];
  $uid_to_block = $uid;
  $form['#uid_to_block'] = $uid_to_block;
  $confirm_form = confirm_form(
    $form,
    t('Re-enable this user', array(), array('context' => 'gofast')) . ' ' . $user->title,
    isset($_GET['destination']) ? $_GET['destination'] : 'user/' . $uid,
    t('Are you sure you want to re-enable this user?', array(), array('context' => 'gofast:gofast_user'))
  );
  $confirm_form['actions']['cancel']['#type'] = "submit";
  $confirm_form['actions']['cancel']['#value'] = t('Cancel');
  $confirm_form['actions']['cancel']['#attributes'] = array(
      'id' => 'edit-cancel',
      'class' => array('btn', 'btn-secondary')
  );
  return $confirm_form;
}

function gofast_unleave_user_form_submit($form, &$form_state)
{
  $uid_to_block = $form['#uid_to_block'];
  gofast_user_unleave_user($uid_to_block);
}


/**
 * Translate label & descritpion for form
 * @param type $form
 */
function gofast_user_account_form_translate_field(&$form)
{

  $label = $form['group_account']['account']['ldap_user_givenname'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_account']['account']['ldap_user_givenname'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_account']['account']['ldap_user_sn'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_account']['account']['ldap_user_sn'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#description'] =  t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['group_roles']['is_extranet'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['group_roles']['is_broadcaster'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_roles']['is_broadcaster'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['group_roles']['is_broadcaster'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['group_roles']['is_broadcaster'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['group_roles']['field_is_comment_restricted'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_roles']['field_is_comment_restricted'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['group_roles']['field_is_comment_restricted'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['group_roles']['field_is_comment_restricted'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_title'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_title'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_o'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_o'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_telephonenumber'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_telephonenumber'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_mobile'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_mobile'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['ldap_user_manager'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['ldap_user_manager'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }
}

/**
 * Translate label & descritpion for form
 * @param type $form
 */
function gofast_user_account_form_translate_field_register(&$form)
{
  $label = $form['group_account']['wrapper_account']['ldap_user_givenname'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_account']['wrapper_account']['ldap_user_givenname'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_account']['wrapper_account']['ldap_user_sn'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_account']['wrapper_account']['ldap_user_sn'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['group_account']['account']['sasl_auth'][LANGUAGE_NONE]['#description'] =  t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['is_extranet'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['is_extranet'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['is_extranet'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['is_extranet'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['is_broadcaster'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['is_broadcaster'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['is_broadcaster'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['is_broadcaster'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['field_is_comment_restricted'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['field_is_comment_restricted'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $desc = $form['field_is_comment_restricted'][LANGUAGE_NONE]['#description'];
  if ($label !== NULL) {
    $form['field_is_comment_restricted'][LANGUAGE_NONE]['#description'] = t($desc, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_ou'][LANGUAGE_NONE]['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_title'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_title'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_o'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_o'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_telephonenumber'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_telephonenumber'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_mobile'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_mobile'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }

  $label = $form['group_profile_data']['ldap_user_manager'][LANGUAGE_NONE][0]['value']['#title'];
  if ($label !== NULL) {
    $form['group_profile_data']['ldap_user_manager'][LANGUAGE_NONE][0]['value']['#title'] = t($label, array(), array('context' => 'gofast'));
  }
}

/**
 *  Performs alterations on user account forms (registration & edition).
 */
function gofast_user_account_form_alter(&$form, &$form_state, $form_id)
{


  gofast_userlist_og_user_form_alter($form, $form_state);

  //Labels translation
  gofast_user_account_form_translate_field_register($form);
  $account = $form['#user'];
  $self = $account->uid === $GLOBALS['user']->uid;

  //for the moment, prevent everybody (except admin) to edit form profil except self
  //need to be more complex (for exemple allow editing non sensible data like firstname, lastname, picture, etc, but not password or email)
  /*
   if($self == false && $GLOBALS['user']->uid != 1 && $form_id !== "user_register_form"){
       drupal_goto("/error/403");exit;
   }
 */

  // Override access policy so that gofast adm are able to edit user roles
  // without requiring 'administer permissions'.
  $access_options = $form['account']['roles']['#options'];
  $form['account']['roles']['#access'] = $access_options && user_access('administer roles');

  // Apply the same policy for the user "extranet" and "broadcaster" flags.
  $form['is_extranet']['#access'] = $form['account']['roles']['#access'];
  $form['is_broadcaster']['#access'] = $form['account']['roles']['#access'];

  $form['account']['roles']['#attributes']['class'][] = 'user-roles-force-single';
  $form['account']['roles']['#attached']['js'] = array(array(
    'data' => drupal_get_path('module', 'gofast_user') . '/js/gofast_user.js',
    'type' => 'file',
    'scope' => 'footer',
    'weight' => 5
  ));

  // Always disable & Hide 'technical' roles.
  foreach (_gofast_user_technical_roles() as $role_name) {
    $role = user_role_load_by_name($role_name);
    $form['account']['roles'][$role->rid]['#disabled'] = TRUE;
    // $form['account']['roles'][$role->rid]['#attributes']['class'] = array('aaa');
    //drupal_add_css(".form-item-roles-{$role->rid} {visibility:hidden;height:0px;}", 'inline');
  }

  // Prevent edition of user private space field reference.
  $form[GOFAST_OG_USER_PRIVATE_SPACE]['#access'] = FALSE;

  // OG membership field requires 'administer group' permission for users to
  // be able to subscribe other users into spaces, but we can't grant any user
  // this permission because it is too broad. Instead, we override the access
  // using our own permission check. Self profile is editable.
  $og_field = &$form[GOFAST_OG_USER_MEMBERSHIP_FIELD];
  $access = $self || user_access('administer spaces') && user_access('administer users');
  $og_field['#access'] = $access;
  if ($form_id === 'user_profile_form') {
    unset($form[GOFAST_OG_USER_MEMBERSHIP_FIELD]); //Disabled feature in GOFAST-3006
  }

  if ($access) {
    $og_options = &$og_field[LANGUAGE_NONE][0]['default']['#options'];

    // Override display properties.
    $og_field['#type'] = 'fieldset';
    $og_field['#title'] = t('Space membership', array(), array('context' => 'gofast'));
    unset($og_field[LANGUAGE_NONE]['#title'], $og_field[LANGUAGE_NONE][0]['default']['#title']);

    // Exclude OG bundles user should not be able to edit (private spaces).
    $space_types = gofast_og_node_types();
    unset($og_options[$space_types['private_space']]);

    // If not a self profile edition, filter options according to permission
    // check in each space.
    $managed_gids = $self ? gofast_og_get_spaces_by_user() : gofast_og_get_managed_spaces();
    gofast_og_form_field_filter_by_id($form, GOFAST_OG_USER_MEMBERSHIP_FIELD, $managed_gids);
  }

  // Autocomplete for manager textfield.

  $attributes_manager = [
    'class' => [' form-control-tags js-tagify'],
    //'data-enforce' => '', //  Comment : Do not allow putting data that dose not exist | Decomment : allow putting data that dose not exist
    'data-user' => '', // show ac users
    'data-oc-select-one' => '' // one select not multiple
    //'data-node' => '', // show ac node
    //'data-userlist' => '', // show ac userlist
    //'data-taxonomy_term' => '' // show ac taxonomy term
  ];
  $form['ldap_user_manager']['#attributes']['class'][]='gofast_display_none';

  $form['group_profile_data']['ldap_user_manager_input'] = array(
    '#title' => t('Manager', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => '',
    '#maxlength' => '', // no maxlength
    '#attributes' => $attributes_manager,
    '#name' => 'ac-list-tags-field-user-manager'
  );

  // Timezone: if configurable and default is not set, use site default.
  $config_timezone = variable_get('configurable_timezones', 1) && isset($form['timezone']['timezone']);
  if ($config_timezone && empty($form['timezone']['timezone']['#default_value'])) {
    $form['timezone']['timezone']['#default_value'] = variable_get('date_default_timezone', @date_default_timezone_get());
  }

  //Hide useless group complements
  $form['group_complement']["#type"] = "hidden";

  //Remove block/unblock field
  $form['group_complement_status']['#access'] = FALSE;
  $form['account']['status']['#access'] = FALSE;

  //Remove field left
  $form['field_left']['#attributes']['class'][] = "gofast_display_none";

  array_unshift($form['#validate'], 'gofast_user_form_validate');
  array_unshift($form['#submit'], 'gofast_user_form_submit');
}

function gofast_user_form_validate(&$form, &$form_state)
{
  // Validate 'username' as a file name since it will be used as a dir name for
  // the user's private space directory (basically directories must respect the
  // same restrictions as filenames).
  if (!gofast_validate_filename($form_state['values']['name'])) {
    form_set_error('name', t('Username identifier contains illegals characters.', array(), array('context' => 'gofast:gofast_user')));
  }
  $_SESSION["default_role_creation_user"] = $form_state['values']["field_default_role"][LANGUAGE_NONE][0]["value"];

  $role_contrib = user_role_load_by_name(GOFAST_ROLE_CONTRIBUTOR);

  if (!gofast_user_is_adm()) {
    $form_state['values']['roles'][$role_contrib->rid] = $role_contrib->rid;
  }

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
 * Submit callback for user account forms (registration & edition).
 */

function gofast_user_form_submit(&$form, &$form_state) {
  if($form['#form_id'] === 'user_profile_form'){
    //Disabled feature in GOFAST-3006
    unset($form['og_user_node']);
    unset($form_state['field']['og_user_node']);
  }

  if ($form['group_complement']['status']['#value'] == 1 && $form['#user']->status == 0 && $form['#user']->uid !== 0){
    $user = $form['#user'];
    gofast_user_unblock($user->uid);
  }

  $account = $form['#user'];
  if (isset($form_state['values']['pass'])) {
    // Keep track of password updates.
    _gofast_set_user_key($account->uid, $form_state['values']['pass']);
  }


  // Clear XSS
  $form_state['values']['ldap_user_givenname']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_givenname']['und'][0]['value'])); // firstname
  $form_state['values']['ldap_user_sn']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_sn']['und'][0]['value'])); // lastname
  $form_state['values']['ldap_user_title']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_title']['und'][0]['value'])); // title
  $form_state['values']['ldap_user_o']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_o']['und'][0]['value'])); // company
  $form_state['values']['ldap_user_telephonenumber']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_telephonenumber']['und'][0]['value'])); // phone
  $form_state['values']['ldap_user_mobile']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['ldap_user_mobile']['und'][0]['value'])); // mobile
  $form_state['values']['field_substitute']['und'][0]['value'] = trim(gofast_xss_clean($form_state['values']['field_substitute']['und'][0]['value'])); // substitute
  // END Clear XSS



 /* $self = $account->uid === $GLOBALS['user']->uid;
  $og_edit = isset($form_state['values'][GOFAST_OG_USER_MEMBERSHIP_FIELD][LANGUAGE_NONE]);

  // If the current user is editing OG field of another user, prevent any loss
  // of memberships. Administrators are not concerned because they cannot
  // unsubscribe users from a space inadvertently.
  if ($og_edit && !$self && !gofast_user_has_role(GOFAST_ROLE_ADMIN)) {
    // A manager (or a group administrator) is editing memberships, in this case
    // access policy narrow down OG memberships options according to the manager
    // spaces [i.e. its managed spaces @see gofast_og_get_managed_spaces()], so
    // the actual memberships values needs to be completed with the actual user
    // memberships.
    $og_values = &$form_state['values'][GOFAST_OG_USER_MEMBERSHIP_FIELD][LANGUAGE_NONE];

    // Computes the difference between the actual user's spaces and the managed
    // spaces (of the manager), then add it to the manager submitted values.
    // User's private space is ignored because it doesn't rely on the same
    // membership type.
    $private = array(gofast_og_get_user_private_space($account, FALSE));
    $spaces = gofast_og_get_spaces_by_user($account);
    $managed = gofast_og_get_managed_spaces();

    $missing = array_diff($spaces, $private, $managed);
    if (!empty($missing)) {
      foreach ($missing as $gid) {
        $og_values[] = array(
          'target_id' => $gid,
          'field_mode' => 'default' // . .
        );
      }
    }
  }*/
}

/**
 * Implements hook_form_FORM_ID_alter()
 *  Alter views' exposed filters' forms.
 */
function gofast_user_form_views_exposed_form_alter(&$form, &$form_state)
{
  switch ($form['#id']) {
    case 'views-exposed-form-gofast-user-directory-page':
      // Prevent useless loading of views filters. This can happen when a user
      // hover on a user picture, triggering an ajax request that will always
      // output a single result, regardless of the views filters.
      if (preg_match('/^profile\/popup\/([0-9]+)$/', current_path())) {
        // Run through each filter element to make it unaccessible. This will
        // bypass form processing and rendering.
        foreach ($form['#info'] as $filter => $info) {
          $fieldname = substr($filter, 7); // 7 as output of strlen('filter-').
          $form[$fieldname]['#access'] = FALSE;
        }
      }
      break;
  }
}


/**
 * Implements hook_form_formID_alter()
 *
 *  Adds user related configs to the form.
 */
function gofast_user_form_gofast_admin_settings_alter(&$form, &$form_state)
{
  // Adds user partitioning setting.
  $form['visibility']['user_partitioning'] = array(
    '#type' => 'select',
    '#title' => t('User Visibility', array(), array('context' => 'gofast')),
    '#options' => gofast_user_partitioning_options(),
    '#default_value' => variable_get('gofast_user_partitioning', GOFAST_USER_PARTITIONING_DEFAULT),
    '#description' => t('Choose whether or not to let users view each others if they don\'t share at least one space in common.', array(), array('context' => 'gofast:gofast_user'))
  );
  // Adds a specific access policy setting for extranet users.
  $form['visibility']['user_extranet_restriction'] = array(
    '#type' => 'radios',
    '#title' => t('Access policy for external users', array(), array('context' => 'gofast:gofast_user')),
    '#options' => gofast_user_extranet_restriction_options(),
    '#default_value' => variable_get('gofast_user_extranet_restriction', GOFAST_USER_EXTRANET_RESTRICTION_DEFAULT),
    '#description' => t('Choose whether or not to let external users access non-external spaces.', array(), array('context' => 'gofast:gofast_user'))
  );

  $form['#submit'][] = 'gofast_user_form_gofast_admin_settings_submit';
}


function gofast_user_reset_password_validate($form, &$form_state)
{
  $name = trim($form_state['values']['name']);
  // Try to load by email.
  $users = user_load_multiple(array(), array('mail' => $name, 'status' => '1'));
  $account = reset($users);
  if (!$account) {
    // No success, try to load by name.
    $users = user_load_multiple(array(), array('name' => $name, 'status' => '1'));
    $account = reset($users);
  }

  drupal_set_message(t('A password recovery email has just been sent to you in the event that your information is valid or authentication delegation is not activated on your account.'));

  if (isset($account->uid)) {
    form_set_value(array('#parents' => array('account')), $account, $form_state);
  } else {
    form_set_error("", "");
    drupal_goto("node");
  }
}

function gofast_user_alter_comments(&$form, &$form_alter)
{
  if (gofast_user_is_comment_restricted()) {
    $form['field_comment_is_private'][LANGUAGE_NONE]['#default_value'] = 1;
    $form['field_comment_is_private'][LANGUAGE_NONE]['#disabled'] = TRUE;
  }
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function gofast_user_form_user_login_block_alter(&$form, &$form_state)
{
  $count = 'COUNT(*)';
  $idp_configured = db_query("select COUNT(*) from saml_sp_idps")->fetchAll()[0]->${count};

  if ($idp_configured) {
    //Change redirect URL of SSO authentication link and format it as a button
    if (isset($form['saml_sp_drupal_login_links'])) {
      $form['saml_sp_drupal_login_links']['#value'] = "<i class='fa fa-user-circle-o'></i> " . str_replace("error/403", $_SERVER['REQUEST_URI'], $form['saml_sp_drupal_login_links']['#items'][0]['data']);
      unset($form['saml_sp_drupal_login_links']['#theme']);
      unset($form['saml_sp_drupal_login_links']['#items'][0]['data']);
      $form['saml_sp_drupal_login_links']['#type'] = "button";
      $form['saml_sp_drupal_login_links']['#attributes'] = array('onclick' => 'if(event.target.tagName != "A"){location.href = jQuery("#edit-saml-sp-drupal-login-links > a").attr("href");event.preventDefault()}', 'class' => array("font-weight-bolder", "font-size-h6", "px-8", "py-4", "my-3", "mr-3"));
      $form['saml_sp_drupal_login_links']['#executes_submit_callback'] = FALSE;
      $form['saml_sp_drupal_login_links']['#weight'] = -1;
      if((bool)variable_get("gofast_disable_login_form", false) === false){
        $form['saml_sp_drupal_login_links']['#prefix'] = "<center><div class='login-spacer'></div>";
        $form['saml_sp_drupal_login_links']['#suffix'] = "<div class='login-spacer'></div><div><hr /><h3 class='login-or'>" . t("OR", array(), array('context' => 'gofast:gofast_user')) . "</h3></div></center>";
      }        
       $form['saml_sp_drupal_login_links']['#suffix'] .= "<script>jQuery('#edit-saml-sp-drupal-login-links').attr('type', 'button');</script>";
    }
  } else {
    //The IDP is not configured, remove reference to SAML authentication
    unset($form['saml_sp_drupal_login_links']['#theme']);
    unset($form['saml_sp_drupal_login_links']['#items'][0]['data']);
  }

  $form['actions']["simplified_login"] = array(
    '#type' => 'select',
    "#weight" => "-5",
    '#attributes' => array(
      'data-minimum-results-for-search' => 'Infinity'
    ),
    '#default_value' => isset($_COOKIE["gofast_version_login_selected"]) ? $_COOKIE["gofast_version_login_selected"] : variable_get('gofast_admin_interface', GOFAST_COMPLETE_VERSION),
    '#theme_wrappers' => array(),
    '#options' => [1 => t("GoFAST Plus", array(), array('gofast')),2 => t("GoFAST Essential", array(), array('gofast'))],
);

  // If we have mobile or tablet, but not iPad, we have only one option.
  $detect = new Mobile_Detect();
  $is_mobile = ($detect->isMobile() || $detect->isTablet() || $detect->is('iPad') || gofast_mobile_is_mobile_domain());
  $is_mobile_device = ($detect->isMobile() || $detect->isTablet() || $detect->is('iPad'));
  if ($is_mobile) {
    $form['actions']['simplified_login']['#default_value'] = 2;
    $form['actions']['simplified_login']['#options'] = [2 => t('GoFAST Essential', [], ['gofast'])];
  }

  if ($is_mobile_device) {
    // GOFAST-7657 - we don't have the select to be visible on mobile devices
    unset($form['actions']['simplified_login']);
  }

  unset($form['links']['#markup']);

  $form['#submit'][] = 'gofast_ajax_login_version_submit_callback';
  $form['#validate'][] = 'gofast_user_login_form_validation';

  $form['actions']["submit"]['#attributes']['class'][] = 'col-xs-4';
  $form['actions']["submit"]['#attributes']['style'][] = 'margin-right: 10px;width: 48%;margin-bottom: 10px;';
  $form['actions']["simplified_login"]['#attributes']['style'][] = 'width: 48%;margin-bottom: 10px;';
  $form['actions']["forgot_password"]['#attributes']['style'][] = 'width: 100%;';
}


function gofast_user_form_alter(&$form, &$form_state)
{
  if ($form['#action'] === '/user/password' && $form['#form_id'] === 'user_login_block') {
    $form['#action'] = '/';
  }
  if ($form['#form_id'] === 'user_pass') {   
    $form['actions']['submit']['#attributes']['class'][] = "btn-primary";
    $form["#validate"] = array('gofast_user_reset_password_validate');
  }
  if ($form['#form_id'] === 'gofast_blocked_user_form') {
    $form['actions']['submit']['#attributes']['class'][] = 'btn-danger btn-sm';
    $form['actions']['submit']['#value'] = '<i class="fa fa-lock"></i>   ' . t('Block', array(), array('context' => 'gofast'));
  }
  if ($form['#form_id'] === 'gofast_unblocked_user_form') {
    $form['actions']['submit']['#attributes']['class'][] = 'btn-success btn-sm';
    $form['actions']['submit']['#value'] = '<i class="fa fa-unlock"></i>   ' . t('Unblock', array(), array('context' => 'gofast'));
  }
}