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

    usurp(1);
    //$html_content = theme('user_picture', array('account' => $myuser, 'dimensions' => 20));
    $html_content = "<img title='".$myuser->ldap_user_givenname['und'][0]['value']." ".$myuser->ldap_user_sn['und'][0]['value']."' style='width:24px;height:24px;' src='".gofast_get_url_picture_by_id($myuser->picture->fid)."' />";

    $html_content = "<span onclick='event.preventDefault();window.parent.parent.Gofast.processAjax(\"/user/" . $uid . "\")'>" . $html_content . "</span>";
  } else if (isset($params['actor'])) {
    usurp(1);
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
    usurp(1);
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

  //Check if we have a str param
  if (isset($params['str'])) {
    $str = $params['str'];
  } else {
    gofast_api_mandatory_parameter("str");
  }

  if (strlen($str) < 1) {
    gofast_api_success(array());
  }

  $options_ac_user = array(
    'format_key_callback' => 'gofast_user_api_autocomplete_format_key',
    'format_value_callback' => 'gofast_user_api_autocomplete_format_value'
  );

  $output = gofast_ac_query($str, 'user', $options_ac_user);

  gofast_api_success($output);
}

function gofast_user_api_autocomplete_format_key($entity_type, $entity)
{
  return $entity->uid;
}

function gofast_user_api_autocomplete_format_value($entity_type, $entity)
{
  $displayname = gofast_user_display_name($entity);
  $html_content = "<img title='".$entity->ldap_user_givenname['und'][0]['value']." ".$entity->ldap_user_sn['und'][0]['value']."' style='width:24px;height:24px;' src='".gofast_get_url_picture_by_id($entity->picture->fid)."' />";
  $user_icon = str_replace('<span>', '<span style="display:none;">', $html_content);
  $user_icon = "<img" . preg_replace('/(.*)<img(.*)\/>(.*)/sm', '\2', $user_icon) . "/>";
  return array('login' => $entity->name, 'mail' => $entity->mail, 'uid' => $entity->uid, 'displayname' => $displayname, 'icon' => $user_icon);
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

  //Generate token
  $uuid = gofast_generate_uuid();
  $token = base64_encode($uuid);

  //Generate end timestamp
  $timestamp = time() + 180;

  //Store the token
  db_insert("gofast_token")
    ->fields(array(
      'uid' => $user->uid,
      'token' => $token,
      'timestamp' => $timestamp
    ))->execute();

  $output = array('token' => $token);

  gofast_api_success($output);
}
