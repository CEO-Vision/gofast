<?php

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource user
 * @action autocomplete
 * @methods GET
 */
function gofast_api_user_picture($params)
{
  switch ($params['method']) {
    case 'GET':
      gofast_api_get_user_picture($params);
      break;
    default:
      gofast_api_not_implemented("This method");
      break;
  }
}

function gofast_api_get_user_picture($params)
{
  //Check authentication
  global $user;
  if ($user->uid == 0) {
    //gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }

  //Check if we have a str param
  if (isset($params['username'])) {
    $username = $params['username'];
  } else if (isset($params['uid'])) {
    $uid = $params['uid'];
  } else {
    gofast_api_mandatory_parameter("username/uid");
  }

  //Check if we have to return the name of the user
  if (isset($params['with_name'])) {
    $with_name = $params['with_name'];
  }

  if (isset($params['uid'])) {
    $myuser = user_load($uid);

    //$html_content = theme('user_picture', array('account' => $myuser, 'dimensions' => 20));
    $html_content = "<img title='".$myuser->ldap_user_givenname['und'][0]['value']." ".$myuser->ldap_user_sn['und'][0]['value']."' style='width:24px;height:24px;' src='".gofast_get_url_picture_by_id($myuser->picture->fid)."' />";

    $html_content = "<span onclick='event.preventDefault();window.parent.parent.Gofast.processAjax(\"/user/" . $uid . "\")'>" . $html_content . "</span>";
  } else if (isset($params['actor'])) {
    $html_content =  gofast_workflows_get_actor_members_list($username);
    $html_content = str_replace("width='16px'", 'width="40px"', $html_content);
    $html_content = str_replace("height='16px'", 'height="40px"', $html_content);
  } else {
    $myuser = user_load_by_name($username);
    if (!isset($myuser->uid)) {
      //maybe we received a bonita_id
      $uid = gofast_workflows_get_drupalid_from_bonitaid($username);
      $myuser = user_load($uid);
      if (!isset($myuser->uid)) {
        gofast_api_internal_server_error("Unable to load user with username : " . $username);
      }
    } else {
      $uid = $myuser->uid;
    }
    $html_content = "<img title='".$myuser->ldap_user_givenname['und'][0]['value']." ".$myuser->ldap_user_sn['und'][0]['value']."' style='width:24px;height:24px;' src='".gofast_get_url_picture_by_id($myuser->picture->fid)."' />";

    if ($with_name) {
      $html_content .= "<span style='padding-right: 10px;'>" . gofast_user_get_display_name_sql($uid) . "</span>";
    }

    $html_content = "<span onclick='event.preventDefault();window.parent.parent.Gofast.processAjax(\"/user/" . $uid . "\")'>" . $html_content . "</span>";
  }
  $output = array(
    'content' => $html_content
  );

  gofast_api_success($output);
}


/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource user
 * @action autocomplete
 * @methods GET
 */
function gofast_api_user_autocomplete($params)
{
  switch ($params['method']) {
    case 'GET':
      gofast_api_get_user_autocomplete($params);
      break;
    default:
      gofast_api_not_implemented("This method");
      break;
  }
}

function gofast_api_get_user_autocomplete($params)
{
  //Check authentication
  global $user;
  if ($user->uid == 0) {
    gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }

  $from_jitsi = array_pop(explode("/", $params["q"])) == "jitsi";
  $mandatory_param = "str";
  if ($from_jitsi) {
    $mandatory_param = "query";
  }
  //Check if we have a str param
  if (isset($params[$mandatory_param])) {
    $str = $params[$mandatory_param];
  } else {
    gofast_api_mandatory_parameter($mandatory_param);
  }

  $bundles = ["user"];
  if ($from_jitsi) {
    $bundles[] = "contact";
  }
  /** @warning here "bundles" are entity types */
  if (isset($params['bundles']) && $params['bundles'] != "null") {
    $bundles = explode(",", gofast_xss_clean($params['bundles']));
  }
  if (strlen($str) < 1) {
    gofast_api_success(array());
  }

  $output = [];

  foreach ($bundles as $bundle) {
    $format_key_callback = "gofast_{$bundle}_api_autocomplete_format_key";
    $format_value_callback = "gofast_{$bundle}_api_autocomplete_format_value";
    if ($from_jitsi) {
      $format_value_callback = "gofast_{$bundle}_api_autocomplete_format_jitsi_value";
    }
    $ac_options = array(
      'format_key_callback' => $format_key_callback,
      'format_value_callback' => $format_value_callback,
    );
    if ($bundle == "contact") {
      $bundle = "node";
      $ac_options["bundle"] = ["contact"];
    }
    $ac_query = gofast_ac_query($str, $bundle, $ac_options);
    $output = $output + $ac_query;
  }
  if ($from_jitsi) {
    $output = array_values($output);
  }

  gofast_api_success($output);
}

function gofast_userlist_api_autocomplete_format_key($entity_type, $entity) {
  return $entity->ulid;
}

function gofast_userlist_api_autocomplete_format_value($entity_type, $entity) {
  $members = gofast_userlist_get_members($entity->ulid, FALSE);
  if (empty($members)) {
    $members_string = t("None");
  } else {
    $members_names = array_map(fn ($el) => $el["display_name"], $members);
    $members_string = implode(", ", $members_names);
    $members_string = strlen ($members_string) > 50 ? substr($members_string, 0, 50) . "..." : $members_string;
  }
  // these are the values which are meant to be parsed as the final value and displayed content in the autocomplete widget (data-type attribute is used to facilitate the parsing)
  $input_value = "<span style=\"display: none;\" data-type=\"userlist\">" . $entity->ulid . "</span>";
  $input_title = "<span style=\"display: none;\" data-type=\"userlist-title\">" . $entity->name . " / " . $members_string . "</span>";
  // use the styles toggled by the classes used in the userlist directory
  $icon = "<span style=\"display: inline-block; overflow: visible; position: relative; width: 24px;\"><div style=\"display: flex; align-items: center;\"><div style=\"display: inline-block; position: relative; border-radius: .42rem; flex-shrink: 0;\"> <span style=\"width: 24px; height: 24px; display: flex; align-items: center; justify-content: center; font-weight: 500; color: #3f4254; background-color: #f3f6f9; background-repeat: no-repeat; background-position: center center; background-size: cover; border-radius: .42rem;\">";
  $icon .= strtoupper(substr($entity->name, 0, 2));
  $icon .= "</span></div></div></span>";
  $icon = $input_value . $input_title . $icon;
  return array('login' => $entity->name, 'mail' => $members_string, 'uid' => $entity->ulid, 'displayname' => $entity->name, 'icon' => $icon, 'type' => $entity_type);
}

function gofast_user_api_autocomplete_format_key($entity_type, $entity)
{
  return $entity->uid;
}

function gofast_user_api_autocomplete_format_value($entity_type, $entity)
{
  $displayname = gofast_user_display_name($entity);
  $safe_givenname = str_replace(['"', '\''], ['', ''], $entity->ldap_user_givenname['und'][0]['value']);
  $safe_surname = str_replace(['"', '\''], ['', ''], $entity->ldap_user_sn['und'][0]['value']);

  $html_content = "<img title='".$safe_givenname." ".$safe_surname."' style='width:24px;height:24px;' src='".gofast_get_url_picture_by_id($entity->picture->fid)."' />";
  $user_icon = str_replace('<span>', '<span style="display:none;">', $html_content);
  $user_icon = "<img" . preg_replace('/(.*)<img(.*)\/>(.*)/sm', '\2', $user_icon) . "/>";
  return array('login' => $entity->name, 'mail' => $entity->mail, 'uid' => $entity->uid, 'displayname' => $displayname, 'icon' => $user_icon, 'type' => $entity_type);
}

function gofast_user_api_autocomplete_format_jitsi_value($entity_type, $entity)
{
  $displayname = gofast_user_display_name($entity);
  $avatar = gofast_get_url_picture_by_id($entity->picture->fid);
  return array('id' => "user_" . $entity->uid, 'name' => $displayname, 'avatar' => $avatar, 'type' => "user");
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource login
 * @action token
 * @methods GET
 */
function gofast_api_login_token($params)
{
  if ($params['method'] != "GET") {
    gofast_api_not_implemented("This method");
  }

  if(gofast_workflows_is_external_api()){
       gofast_api_forbidden("External access to this action is forbidden.");
  }

  //Retrieve name param
  $name = $params['name'];
  if (!isset($name) && empty($name)) {
    gofast_api_mandatory_parameter('name');
  }

  //Retrieve corresponding user
  $user = user_load_by_name($name);
  if ($user === false) {
    gofast_api_not_found("User " . $name . " not found");
  }

  //Generate end timestamp
  $timestamp = time() + 180;

  //Is there already a valid token for this user?
  $query = db_select('gofast_token', 'gt')
    ->fields('gt', array('token'))
    ->condition('gt.uid', $user->uid)
    ->condition('gt.timestamp', time(), '>');
  $token = $query->execute()->fetchField();

  if (!$token) {
    //Remove previous token(s)
    db_delete("gofast_token")
      ->condition('uid', $user->uid)
      ->execute();

    //Generate the token
    $uuid = gofast_generate_uuid();
    $token = base64_encode($uuid);

    //Store the token
    db_insert("gofast_token")
      ->fields(array(
        'uid' => $user->uid,
        'token' => $token,
        'timestamp' => $timestamp
      ))->execute();
  }

  $output = array('token' => $token);

  gofast_api_success($output);
}

/**
 * Send invites to Jitsi rooms, even if they were not created from GoFAST.
 * If the user is a not a GoFAST user, he/she will receive a notification.
 * Otherwise the user will by notified by the chat.
 */
function gofast_api_user_invite($params) {
  if ($params['method'] != "POST") {
    gofast_api_not_implemented("This method");
  }
  global $user;
  $inviter = user_load($user);
  $inviter_name = gofast_user_display_name($inviter);
  
  $invited_list = gofast_xss_clean($params["invited"]);
  foreach ($invited_list as $invited) {
    $type_and_id = explode("_", $invited["id"]);
    $type = $type_and_id[0];
    $id = $type_and_id[1];
    if ($type == "user") {
      $invitee = user_load($id);
      $l = ['langcode' => $invitee->language, 'context' => 'gofast:gofast_conference'];
      $conference_link = '<a href="' . $params["url"] . '">&nbsp;' . t("this meeting", [], $l) . "</a>";
      $message = t('@user invited you on @link which is about to begin or is happening right now', ['@user' => $inviter_name], $l);
      $message = str_replace("@link", $conference_link, $message);
      gofast_riot_api_send_message($inviter, $id, $message);
      continue;
    }
    if ($type == "contact") {
      $contact = node_load($id);
      $name = $contact->field_contact_name[LANGUAGE_NONE][0]['value'];
      $first_name = $contact->field_contact_firstname[LANGUAGE_NONE][0]['value'];
      $recip_name = $first_name." ".$name;
      $recipient_mail = $contact->field_contact_email[LANGUAGE_NONE][0]['value'];
      $l = ['langcode' => $inviter->language, 'context' => 'gofast:gofast_conference'];
      $conference_link = '<a href="' . $params["url"] . '">&nbsp;' . t("this meeting", [], $l) . "</a>";
      $message = t('@user invited you on @link which is about to begin or is happening right now', ['@user' => $inviter_name], $l);
      $message = str_replace("@link", $conference_link, $message);
      $mail_body = theme('gofast_conference_minimal_invite_body', array(
        'recip_name' => $recip_name,
        'inviter_name' => $inviter_name,
        'message' => $message,
        'conference_link' => $params["url"],
        'l' => array('langcode' => $inviter->language, 'context' => 'gofast:gofast_conference'),
      ));
      $recipients = [['recpt' => $recipient_mail, 'method' => 'to']];
      $subject = t("You are invited to a new @sitename conference", array("@sitename" => variable_get("site_name", "GoFAST")), $l);
      $title = t("You are invited to a meeting", [], $l);
      $footer = t('Message sent from @site_name', ["@site_name", variable_get('site_name')], $l);
      $mail = ['body' => $mail_body, 'subject' => $subject, 'title' => $title, 'footer' => $footer];
      gofast_mail_queue_api_queue_ext($mail, $recipients, time());

    }
  }
  gofast_api_success("OK");
}