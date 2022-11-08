<?php


/**
 * Implements hook_menu()
 */
function gofast_user_menu()
{
  $items = array();

  $items['admin/config/gofast/user'] = array(
    'title' => t('User accounts', array(), array('context' => 'gofast')),
    'page callback' => 'drupal_get_form',
    'page arguments' => array('gofast_user_settings_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_NORMAL_ITEM,
  );

  // Profile popup ajax callback
  $items['profile/popup/%'] = array(
    'page callback' => 'gofast_user_profile_popup',
    'type' => MENU_CALLBACK,
    'page arguments' => array(2),
    'access arguments' => array('access user profiles'),
    'access callback' => 'user_access',
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['spaces/private-space'] = array(
    'page callback' => 'gofast_user_private_space_page',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  $items['profile/save-language/%'] = array(
    'page callback' => 'gofast_user_save_lang',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['gofast/user-autocomplete/%'] = array(
    'page callback' => 'gofast_user_autocomplete',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access user profiles'),
    'access callback' => 'user_access'
  );

  $items['gofast/%ctools_js/user/edit-avatar/%'] = array(
    'title' => t("Edit avatar", array(), array('context' => 'gofast')),
    'page callback' => 'gofast_user_edit_avatar',
    'page arguments' => array(1, 4),
    'type' => MENU_CALLBACK,
    'access callback' => 'user_access',
    'access arguments' => array('access user profiles'),
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['gofast/save/avatar'] = array(
    'title' => 'Gofast save avatar ajax',
    'page callback' => 'gofast_crop_save_avatar_ajax',
    'type' => MENU_CALLBACK,
    'access callback' => 'user_access',
    'access arguments' => array('access user profiles'),
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['admin/user/%user/edit-roles/%ctools_js'] = array(
    'title' => 'GoFAST User Roles',
    'page callback' => 'gofast_user_edit_roles',
    'page arguments' => array(4, 2),
    'type' => MENU_CALLBACK,
    'access callback' => 'user_access',
    'access arguments' => array('administer roles')
  );

  $items['gofast/user/%/unblock'] = array(
    'title' => 'GoFAST_User UnblockAndRefreshed',
    'page callback' => 'gofast_user_unblockAndRefresh',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access callback' => 'gofast_user_is_adm',
  );

  $items['gofast/user/%/leave'] = array(
    'title' => 'GoFAST_User UnblockAndRefreshed',
    'page callback' => 'gofast_user_unblockAndRefresh',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access callback' => 'gofast_user_is_adm',
  );

  $items['gofast/user/%/unblock_profile'] = array(
    'title' => 'GoFAST_User Unblock',
    'page callback' => 'gofast_user_unblock_profile',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access callback' => 'gofast_user_is_adm',
  );

  $items['gofast/user/%/block_profile'] = array(
    'title' => 'GoFAST_User Block',
    'page callback' => 'gofast_user_block_profile',
    'page arguments' => array(2),
    'type' => MENU_CALLBACK,
    'access callback' => 'gofast_user_is_adm',
  );

  $items['gofast/user/%/get_section'] = array(
    'title' => 'GoFAST_User Groups',
    'page callback' => 'gofast_user_get_groups_async',
    'page arguments' => array(2),
    'access callback' => 'user_access',
    'access arguments' => array('access user profiles'),
    'delivery callback' => 'gofast_ajax_delivery'
  );

  // @todo will be obsolete as of GF4
  $items['gofast/user/%/myteam'] = array(
    'title' => 'GoFAST_User Block',
    'page callback' => 'gofast_user_groups_get_block_myteam_async',
    'page arguments' => array(2),
    'access callback' => 'user_access',
    'access arguments' => array('access user profiles'),
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['gofast/user/whoami'] = array(
    'page callback' => 'gofast_user_whoami',
    'access callback' => TRUE,
    'type' => MENU_CALLBACK,
  );

  $items['gofast/user/cani/%/%'] = array(
    'page callback' => 'gofast_user_whatcanido',
    'page arguments'=> array(3, 4),
    'access callback' => TRUE,
  );

  $items['gofast/user/%/profile/get'] = array(
    'page callback' => 'gofast_user_profile_get_json',
    'page arguments' => array(2),
    // authorization is checked inside the callback
    'access callback' => TRUE
  );

  // different logic to handle templating on the front side
  $items['gofast/user/%/profile/get/%/team'] = array(
    'page callback' => 'gofast_get_managed_users',
    'page arguments' => array(2, 5),
    // authorization is checked inside the callback
    'access callback' => TRUE
  );
  
  // different logic to handle templating on the front side
  $items['gofast/user/%/profile/get/team'] = array(
    'page callback' => 'gofast_get_manager_managed_users',
    'page arguments' => array(2, 5),
    // authorization is checked inside the callback
    'access callback' => TRUE
  );

  $items['gofast/user/login/redirect/%/%'] = array(
    'page callback' => 'gofast_user_login_with_token',
    'page arguments' => array(4,5),
    'access arguments' =>  TRUE,
    'type' => MENU_CALLBACK,
    'access callback' => TRUE
  );

  $items['gofast/user/login/version/mobile'] = array(
    'page callback' => 'gofast_user_login_and_redirect_to_mobile',
    'type' => MENU_CALLBACK,
    'access callback' => TRUE
  );

  $items['gofast/user/login/version/standard'] = array(
    'page callback' => 'gofast_user_login_and_redirect_to_standard',
    'type' => MENU_CALLBACK,
    'access callback' => TRUE
  );


  return $items;
}

/**
 * Implements hook_menu_alter()
 */
function gofast_user_menu_alter(&$items)
{
  // Add an access callback to user item so that user menu links are not shown
  // to anonymous users.
  if (isset($items['user'])) {
    $items['user']['access callback'] = 'user_is_logged_in';
  }
  $items['admin/people/create']['page callback'] = 'gofast_user_node_add_user'; //GOFAST-7014
  
    $login_form_disabled = variable_get("gofast_disable_login_form", FALSE);
  if($login_form_disabled){
      $items['user/login']['access callback'] = 'false';
  }
  
  $items['admin/people']['access arguments'] = array('access administration pages');
  foreach ($items as $path => $item) {
    if (strpos($path, 'admin/config/development') !== FALSE) {
      $items[$path]['access callback'] = "gofast_user_is_drupal_admin";
    }
  }  
}

function gofast_user_is_drupal_admin($string = "", $account = NULL) {
  global $user;

  if (!isset($account)) {
    $account = $user;
  }

  if ($account->uid == 1) {
    return TRUE;
  }

  return FALSE;
}

/**
 * formulaire de config test
 */
function gofast_user_settings_form()
{
  $adm_exists = GOFAST_USER_ADMINISTRATOR_ID !== FALSE;

  $form['gofast_user_settings'] = array(
    '#type' => 'fieldset',
    '#title' => 'Manage Gofast users',
    'info' => array(
      '#type' => 'item',
      '#description' => 'Create account (test) : ' . theme('item_list', array('items' => array(GOFAST_USER_ADMINISTRATOR_USERNAME)))
    ),
  );

  $form['gofast_user_settings']['status'] = array(
    '#type' => 'item',
    '#description' => $adm_exists ? t('An administrator named %name already exists', array('%name' => GOFAST_USER_ADMINISTRATOR_USERNAME), array('context' => 'gofast:gofast_user')) : t('Create administrator profile', array(), array('context' => 'gofast:gofast_user'))
  );

  $form['gofast_user_settings']['submit'] = array(
    '#type' => 'submit',
    '#name' => 'Create',
    '#value' => 'Create',
    '#disabled' => $adm_exists
  );

  return $form;
}

function gofast_user_settings_form_submit($form, &$form_state)
{
  if ($form_state['submitted'] && drupal_strtolower($form_state['clicked_button']['#value']) == 'create') {
    $account = gofast_user_adm_create();
    if ($account->uid) {
      drupal_set_message('Administrator account created successfully.', 'status');
    }
  }
}



/**
 * Ajax callback. Return user's mini profile delivery.
 */
function gofast_user_profile_popup($uid = 0)
{
  $output = '';

  if (!user_view_access($uid)) {
    return $output;
  }

  return theme('gofast_user_profile_popup_template', array('uid' => $uid));
}


/**
 * Page callback for the current logged in user private space.
 */
function gofast_user_private_space_page()
{
  $space = gofast_og_get_user_private_space();
  // This is a workaround to add the actual node to the page vars.
  $_GET['q'] = 'node/' . $space->nid;
  return node_page_view($space);
}


/**
 * Ajax callback for user quick saving his prefered language.
 */
function gofast_user_save_lang($lang, $account = NULL)
{
  global $user;

  $account = user_load(isset($account->uid) ? $account->uid : $user->uid);
  $languages = language_list();

  if (!$lang || !in_array($lang, array_keys($languages)) || !$account->language) {
    return;
  }

  $account->language = $lang;

  if (user_save($account)) {
    drupal_set_message(t('Profile saved.'), 'status', FALSE);
  } else {
    drupal_set_message(t('An error occured.'), 'error', FALSE);
  }

  return theme('status_messages');
}


/**
 * Autocomplete callback for user lookups.
 */
function gofast_user_autocomplete($str)
{
  $matches = gofast_ac_query($str, 'user');
  drupal_json_output($matches);
}

/**
 * Autocomplete callback for user lookups.
 */
function gofast_user_space_autocomplete($str)
{
  $matches = array_merge(gofast_ac_query($str, 'user'), gofast_ac_query($str, 'node', array('bundle' => array('group', 'organisation', 'extranet', 'public'))));
  drupal_json_output($matches);
}


/**
 *
 * @param type $ajax
 * Ajax callback for editing avatar
 */
function gofast_user_edit_avatar($ajax, $uid)
{
  if ($ajax) {
    ctools_include('modal');
    ctools_include('ajax');

    $user = user_load($uid);
    if (is_numeric($user->picture)) {
      $user->picture = file_load($user->picture);
    }

    $avatar = (!is_null($user->picture) ? '/sites/default/files/pictures/' . $user->picture->filename : null);
    $output .= theme('gofast_user_avatar_crop', array(
      'avatar' => $avatar,
      'uid'    => $uid
    ));

    $commands[] = ctools_modal_command_display(t('Cropping avatar', array(), array('context' => 'gofast')), $output);

    print ajax_render($commands);
    exit;
  } else {
    return "";
  }
}


function gofast_crop_save_avatar_ajax()
{
  $output = ['status' => 0];

  if (!empty($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) == 'xmlhttprequest') {
    $data = base64_decode($_POST['data']);
    $uid = $_POST['uid'];
    $account = user_load($uid);
    $ext = !empty($_POST['ext']) ? strtolower($_POST['ext']) : '';

    if (is_numeric($user->picture)) {
      $user->picture = file_load($user->picture);
      if (file_exists($user->picture)) {
        file_delete($user->picture);
      }
    }

    $tmp_filename = 'sites/default/files/pictures/tempfile' . $uid;

    /** WebP/m support is fine but image_style_url() fails to create thumbnails
     * so we leave it as unsupported for now.
    if (in_array($ext, ['webm', 'webp'])) {
      // Function imagecreatefromstring does not support WebP.
      file_put_contents($tmp_filename, $data);
      $image = imagecreatefromwebp($tmp_filename);
    }
    else {
      $image = imagecreatefromstring($data);
    } */

    $image = imagecreatefromstring($data);
    $func = $ext === 'jpg' ? 'imagejpeg' : 'image' . $ext;

    if ($image === FALSE) {
      $msg = t('Image type is unsupported (.!ext): data is not in a recognised '
        . 'format, or the image is corrupt and cannot be loaded.', ['!ext' => $ext]);
      watchdog('gofast_user', $msg, [], WATCHDOG_ERROR);
      $http_status = '500 Internal Server Error';
      $output['errorMsg'] = $msg;
    } elseif (!function_exists($func)) {
      $msg = t('Function !func does not exist!', ['!func' => $func]);
      watchdog('gofast_user', $msg, [], WATCHDOG_ERROR);
      $http_status = '500 Internal Server Error';
      $output['errorMsg'] = $msg;
    } else {
      $func($image, $tmp_filename);
      $data = file_get_contents('sites/default/files/pictures/tempfile' . $uid);
      $account->picture = file_save_data($data, 'public://pictures/picture-' . $uid . '-' . time() . '.' . $ext, FILE_EXISTS_REPLACE);

      // This line below is the most important, we generate the thumbnail
      // _programmatically_ (in case of permission issues if generating the thumbnail from a GET request)
      $thumbnail_uri = image_style_path('thumbnail', $account->picture->uri);
      image_style_create_derivative("thumbnail", $account->picture->uri, $thumbnail_uri);

      user_save($account);
      drupal_unlink('sites/default/files/pictures/tempfile' . $uid);

      $http_status = '200 OK';
      $output = [
        'status' => 1,
        'pictureUrl' => file_create_url($account->picture->uri),
        'thumbnailUrl' => $thumbnail_uri
      ];
    }
  }

  if ($http_status) {
    header('Status: ' . $http_status);
  }

  header('Content-Type: application/json');
  $response = json_encode($output);

  return $response;
}


/**
 * "whoami" endpoint for front-end to be able to quickly check if the current
 * user is still logged-in (async).
 *
 * Sends json representation of ['uid' => $user->uid] to client.
 */
function gofast_user_whoami()
{
  global $user;
  drupal_json_output(array('uid' => $user->uid));
  exit();
}

function gofast_user_whatcanido($operation, $nid)
{
  // no type-hinting since all values coming from URL parts are initially strings, so we compensate for that
  $node = node_load(intval($nid));
  drupal_json_output(node_access($operation, $node));
  exit();
}

/* this function unblock users */
function gofast_user_unblockAndRefresh($uid)
{

  gofast_user_unblock($uid);

  $myView = views_embed_view('gofast_user_directory', 'page_3');

  print $myView;
  exit();
}


function gofast_user_unblock_profile($uid)
{

  gofast_user_unblock($uid);

  $user_profile = user_view(user_load($uid));
  $profile_view = drupal_render($user_profile);

  print $profile_view;
  exit();
}

function gofast_user_unblock($uid)
{
  // 3 steps for unblock the user
  $my_user = user_load($uid);
  $edit = array('status' => 1);

  //is the user is also disabled, re-enable it
  if (gofast_user_is_left($my_user)) {
    gofast_user_unleave_user($uid);
  } else {
    user_save($my_user, $edit);
    //audit
    global $user;
    $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'user_unblocked', 'uid_to_block' => $uid);
    $event = serialize($event);
    $last_event_serialized = rawurlencode($event);

    $last_event_unserialized["mod_timestamp"] = time();
    $last_event_unserialized["mod_author"] = $user->uid;

    //Insert inton audit
    gofast_audit_insert_line_audit(0, 'user_unblocked', $last_event_serialized, $last_event_unserialized); //The value 0 is define in order to not render node in the audit

  }
  db_truncate('flood')->execute();
  db_truncate('login_security_track')->execute();
}


function gofast_user_block_profile($uid)
{

  gofast_user_block($uid);

  $user_profile = user_view(user_load($uid));
  $profile_view = drupal_render($user_profile);

  print $profile_view;
  exit();
}


function gofast_user_block($uid)
{
  // 3 steps for unblock the user
  $my_user = user_load($uid);
  $edit = array('status' => 0);
  user_save($my_user, $edit);

  db_truncate('flood')->execute();
  db_truncate('login_security_track')->execute();
}

/**
 * Function gofast_user_get_groups_async : get user spaces (section type)
 *
 * @param string $account_uid
 * @return void
 */
function gofast_user_get_groups_async($account_uid){

  $account = user_load($account_uid);
  
  $section = $_GET['section'];
  
  $spaces = array();

  $spaces = gofast_user_get_spaces_by_user($account, $section);
  
  print $spaces;
  exit;
}

/**
 * Function gofast_user_get_spaces_by_user: get html result for section give in parameter
 *
 * @param object $account
 * @param string $section
 * @return $result
 */
function gofast_user_get_spaces_by_user($account, $section){
  
  global $user;
  
  // Is the current user theme administrator ?
  $is_adm = gofast_user_is_adm($user);

  // Is the current user visiting his own profile (note : let su manage other
  // profiles as its own).
  $self = $user->uid == 1 || $user->uid == $account->uid;
  
  $spaces = array();
  $result = '';
  
  $groups_user_gids = gofast_og_get_spaces_by_user($account);

  $groups_user = node_load_multiple($groups_user_gids);
  $nodes_groups_path = gofast_cmis_space_get_drupal_path_multiple_nodes($groups_user_gids);


  // switch section
  switch ($section) {
    case 'group':
    case 'organisation':
    case 'public':
    case 'extranet':
      foreach ($groups_user as $group) {
        if (node_access('view', $group)) {
          if($group->type == $section){
            $spaces['path'][$group->nid] = $nodes_groups_path[$group->nid];
          };
        }
      }
      asort($spaces['path']);
      foreach ($spaces['path'] as $gid => $webdav_path) {
        $result .= gofast_breadcrumb_display_breadcrumb($gid, ['return' => TRUE, "title_link" => TRUE, "editable" => FALSE, "show_role" => TRUE, "show_role_for" => $account->uid]);
      }
      if(empty($result)){
        $result = '<div class="text-muted">' . t('No spaces found') . '</div>';
      }
      break;
    case 'requests':
      
      // Requested groups
      $requested_groups_ids = gofast_og_get_user_pending_spaces($account);
      
      if (count($requested_groups_ids) > 0) {
        $query_og_info = db_select('node', 'n');
        $query_og_info->fields('n', array('nid', 'title', 'type'));
        $query_og_info->condition('n.nid', array_values($requested_groups_ids), 'IN');

        $results = $query_og_info->execute();

        if ($results->rowCount() > 0) {
          while ($og = $results->fetchObject()) {
            $gid = $og->nid;
            $og_link = l($og->title . ' (' . t("Pending", array(), array('context' => 'gofast')) . ')', "node/{$gid}", array('attributes' => array('class' => 'ajax-navigate', 'nid' => $gid, 'title' => $og->title)));
            $result .= $og_link . "</br>";
          }
        }
      }
      if(empty($result)){
        $result = '<div class="text-muted">' . t('No requests in progress') . '</div>';
      }
      break;
    case 'userlists':
      
      // get userlists
      $userlists = array();
      $userlists_ids = gofast_userlist_get_userlists_by_user($account);
      if (!empty($userlists_ids)) {
        foreach ($userlists_ids as $key => $ulid) {
          $entity_userlist = entity_load_single('userlist', $key);
          $nid = $entity_userlist->nid;
          $node = node_load($nid);
          $title = $node->title;
          if (!empty($title)) {
            $userlists[$key] = $title;
          }
        }
        asort($userlists);
        foreach ($userlists as $ulid => $title_userlists) {
          $userlists = entity_load('userlist', array($ulid));
          $userlist = $userlists[$ulid];
          
          $result .= theme('gofast_user_display_userlist', array('nid' => $userlist->nid, 'ulid' => $ulid, 'title' => $title_userlists));
        }
      }
      if(empty($result)){
        $result = '<div class="text-muted">' . t('No userlists found') . '</div>';
      }
      break;
    default:
      break;
  }

  return $result;
  
}

// @todo will be obsolete as of GF4
function gofast_user_groups_get_block_myteam_async($account_uid)
{
  $output = '';
  $block = gofast_user_block_view('my_team', $account_uid);
  $output .= '<section id="block-gofast-user-my-team" class="block block-gofast-user contextual-links-region clearfix">';
  $output .= '<h2 class="block-title">' . $block['subject'] . '</h2>';
  $output .= $block['content'];
  $output .= '</section>';

  print $output;
  exit;
}

function _format_related_user_info_for_profile($user, $user_picture = FALSE)
{
  if($user_picture == TRUE){
    $picture = theme('user_picture', array('account' => $user, 'dimensions' => '40', 'popup' => FALSE));
  }else{
    $picture = $user->picture->filename ? "/sites/default/files/pictures/" . $user->picture->filename : null;
  }
  $userLdap = gofast_ldap_user_attributes($user);
  return [
    "uid" => $user->uid,
    "firstname" => $userLdap['ldap_user_givenname']["value"],
    "lastname" => $userLdap['ldap_user_sn']["value"],
    "picture" => $picture
  ];
}

function gofast_get_managed_users($accountUid, $managerId)
{
  if(user_view_access(user_load($accountUid))) {
    $userTeam = [];
    $managerUsername = db_query("SELECT `name` FROM users WHERE `uid`='$managerId'")->fetchCol()[0];
    $groupUserIds = db_query("SELECT entity_id FROM field_data_ldap_user_manager WHERE entity_type = 'user' AND ldap_user_manager_value LIKE 'uid=$managerUsername%'")->fetchCol();
    foreach($groupUserIds as $groupUserId) {
      $managedUser = user_load($groupUserId);
      $userTeam[] = _format_related_user_info_for_profile($managedUser, TRUE);
    }
    drupal_json_output($userTeam);
    exit;
  } else {
    drupal_json_output(["error" =>
      ["message" => "Operation not authorized"]
    ]);
    exit;
  }
}

function gofast_get_manager_managed_users($accountUid)
{
  $userTeam = [];
  if(user_view_access(user_load($accountUid))) {
    $userTeam = gofast_user_team_member(user_load($accountUid));
    drupal_json_output($userTeam);
    exit;
  } else {
    drupal_json_output(["error" =>
      ["message" => "Operation not authorized"]
    ]);
    exit;
  }
}

function gofast_user_get_relationshios($account){
  $user_relationships = gofast_user_load_relationships($account->uid, TRUE, TRUE);
  $uids_relationships = array_keys($user_relationships);
  foreach($uids_relationships as $uid_relationship) {
    $user_relationship = user_load($uid_relationship);
    $relationships[] = _format_related_user_info_for_profile($user_relationship, TRUE);
  }

  return $relationships;
}

// callback to asynchronously get user profile infos in JSON format
function gofast_user_profile_get_json($accountUid)
{
  global $user;
  if(user_view_access(user_load($accountUid))) {
    $account = user_load($accountUid);
    // a simple array of ldap attributes is easier to manipulate
    $ldap = gofast_ldap_user_attributes($account);
    $managerUsername = "";
    if (!isset($ldap["ldap_user_manager"]["value"]) || empty($ldap["ldap_user_manager"]["value"])
    // in case there already are JS errors stored in DB, we don't want to generate more
    || $ldap["ldap_user_manager"]["value"] == "undefined"
    || $ldap["ldap_user_manager"]["value"] == "[object Object]"
    ){
      $manager = false;
    } else {
      // username is mistakenly labelled as uid in the database
      $managerUsername = explode(",", substr($ldap["ldap_user_manager"]["value"], 4))[0];
      $manager = user_load_by_name($managerUsername);
      $manager = _format_related_user_info_for_profile($manager, FALSE);
    }
    // @warning some ldap fields are objects, others are strings, but the front-end is able to handle that
    foreach($account->field_skills[LANGUAGE_NONE] as $key=>$skills){
      $account->field_skills[LANGUAGE_NONE][$key]['value'] = $skills['tid'];
      $account->field_skills[LANGUAGE_NONE][$key]['name'] = taxonomy_term_load($skills['tid'])->name;
    }
    // @warning some ldap fields are objects, others are strings, but the front-end is able to handle that
    foreach($account->field_interests[LANGUAGE_NONE] as $key=>$interests){
      $account->field_interests[LANGUAGE_NONE][$key]['value'] = $interests['tid'];
      $account->field_interests[LANGUAGE_NONE][$key]['name'] = taxonomy_term_load($interests['tid'])->name;
    }
    // @warning some ldap fields are objects, others are strings, but the front-end is able to handle that
    foreach($account->field_hobbies[LANGUAGE_NONE] as $key=>$hobbies){
      $account->field_hobbies[LANGUAGE_NONE][$key]['value'] = $hobbies['tid'];
      $account->field_hobbies[LANGUAGE_NONE][$key]['name'] = taxonomy_term_load($hobbies['tid'])->name;
    }

    drupal_json_output([
      "firstname" => $ldap['ldap_user_givenname'],
      "lastname" => $ldap['ldap_user_sn'],
      "job" => $ldap['ldap_user_title'],
      "phone" => $ldap['ldap_user_telephonenumber'] ?: $ldap['ldap_user_mobile'],
      "email" => $account->mail,
      "department" => $ldap['ldap_user_o'],
      "birthdate" => $account->field_birthdate[LANGUAGE_NONE][0]['value'] ?? "",
      "manager" => $manager,
      'description' => $account->ldap_user_description[LANGUAGE_NONE][0]['value'] ?? "",
      'skills' => $account->field_skills[LANGUAGE_NONE] ?? "",
      'interests' => $account->field_interests[LANGUAGE_NONE] ?? "",
      'hobbies' => $account->field_hobbies[LANGUAGE_NONE] ?? "",
      'relationships' => gofast_user_get_relationshios($account)
    ]);
    exit;
  } else {
    drupal_json_output(["error" =>
      ["message" => "Operation not authorized"]
    ]);
    exit;
  }
}
