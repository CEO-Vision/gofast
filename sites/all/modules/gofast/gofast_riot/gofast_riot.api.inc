<?php

function gofast_riot_api_create_room($room_name, $invite_users = array()){

  global $conf;
  $users = array();
  foreach ($invite_users as $invite_user) {
    $name = gofast_user_get_login($invite_user);
    $tmp_user ="@".strtolower($name).":".$conf['gofast-comm_domain'];
    $users[] = $tmp_user;
  }

  $param = array("name" => $room_name, 'invite' => $users, 'preset' => "private_chat");
  $url = "https://" . 'internal-' . $conf['gofast-comm_domain'] . "/_matrix/client/api/v1/createRoom?access_token=" . variable_get('riot_token_admin');
  $data_string = json_encode($param);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json',
    'Content-Length:' . strlen($data_string))
  );
  $result = curl_exec($ch);
  return json_decode($result,TRUE);
}

function gofast_riot_api_send_message($user = NULL, $target_id = NULL, $message = NULL){

  global $conf;

  if(empty($user)){
    $user = "@chatroom.active:" . $conf['gofast-comm_domain'];
  }

  $target = user_load($target_id, TRUE);

  if(empty($message)){
    $display_name = $target->ldap_user_displayname[LANGUAGE_NONE][0]['value'];
    $message = t('@user send test', array('@user' => $display_name));
  }

  // Get room id beetween chatroom active and the user mentionned
  $room_id = str_replace(":" . $conf['gofast-comm_domain'], '', gofast_riot_get_chatroom_id($target_id));

  // Genrate unique id for the message
  $message_id = uniqid('m.', true);

  // Call matrix api so send message : use org.matrix.custom.xml for send html message (here with a link)
  $param = array('msgtype' => "m.text", "format" => "org.matrix.custom.html", "body" => $message, "formatted_body" => $message);
  $path = '/_matrix/client/r0/rooms/' . urlencode($room_id . ":" . $conf['gofast-comm_domain']) . '/send/m.room.message/' . $message_id ;
  $query = '?access_token=' . variable_get('riot_token_admin');
  $url = 'https://' . 'internal-' . $conf['gofast-comm_domain'] . $path . $query;

  $data_string = json_encode($param);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json',
    'Content-Length:' . strlen($data_string))
  );
  $res = curl_exec($ch);
  return json_encode($res);
}

function gofast_riot_api_check_members($room_id){
  global $conf;
  $room_id = urlencode($room_id);
  $path = "/_matrix/client/r0/rooms/{$room_id}/members";


  $query = http_build_query([
    'access_token' => variable_get('riot_token_admin'),
//    'membership' => 'join,invite'
  ]);

  $url = 'https://' . 'internal-' . $conf['gofast-comm_domain'] . $path . '?' . $query;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'GET');
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
      'Content-Type: application/json'
  ));

  $result = curl_exec($ch);
  $result = json_decode($result, TRUE);

  return $result;
}


function gofast_riot_api_change_room_avatar($room_id, $img_url){

  global $conf;

  $param = array('url' => $img_url);
  $path = '/_matrix/client/r0/rooms/' . urlencode($room_id) . '/state/m.room.avatar';
  $query = '?access_token=' . variable_get('riot_token_admin');
  $url = 'https://' . 'internal-' . $conf['gofast-comm_domain'] . $path . $query;

  $data_string = json_encode($param);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-Type: application/json',
    'Content-Length:' . strlen($data_string))
  );
  $res = curl_exec($ch);

  return json_encode($res);
}

function gofast_riot_api_upload_file($img_url){
  global $conf;
  $filename = end(explode('/',$img_url));
  $content_type = gofast_get_mime_content_type($filename);
  
  $url = "https://" . 'internal-' . $conf['gofast-comm_domain'] . "/_matrix/media/v1/upload?filename=". urlencode($filename) . "&access_token=" . variable_get('riot_token_admin');
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($ch, CURLOPT_POSTFIELDS, file_get_contents($img_url));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
    'Content-Type: ' . $content_type,
    'Content-Length:' . strlen(file_get_contents($img_url))
  ));
  $result = curl_exec($ch);
  return json_decode($result,TRUE);
}
