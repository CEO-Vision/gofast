<?php

//The highest number of notifications that can be send in one cron
define('MAX_NOTIFICATIONS_BY_PUSH', 30);

//The highest number of event that can be queued in one mail
define('MAX_EVENT_BY_NOTIFICATION', 250);

//The highest number of event that can be processed in a mail queue query
define('MAX_EVENT_PROCESSED_IN_QUERY', 10000);

/*
 * API for gofast_mail_queue used for notifications system
 *
 */

/**
 * Erase a queue item
 *
 * @param $qid
 *  ID of the item to delete
 */
function gofast_mail_queue_delete_queue_item($qid){
  db_delete("gofast_mail_queue")
        ->condition('qid', $qid)
        ->execute();
}

/**
 * Call subscription module to be clear
 */
function gofast_mail_queue_api_clear_queue(){
  //Removed in GOFAST-3669
  //gofast_subscription_ui_api_clear_subscriptions();
}

/**
 * Queue a message, asking the subscription module about interested users
 *
 * @param $message
 *  Message ID to queue
 */
function gofast_mail_queue_api_queue($message, $type){

  $timer_start = microtime(true);
  watchdog('gofast_mail_queue', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

  if($type == 'message' || $type == 'message_kanban'){
    //Improve performances to reimplement
    //gofast_subscription_ui_api_clear_subscriptions();
    $message_json = $message['0'];
    $message_data = json_decode($message_json, TRUE);
    $message_json = json_encode($message_data);
    $req = $message_data['event']['value'];

    //---------------To stock users to notify------------------
    $subscribed_user = array();
    $subscribed_term = array();
    $subscribed_group = array();
    $subscribed_node = array();
   //---------------------------------------------------------
    //We retrieve the node ID in the message
    $nid = NULL;
    if(isset($message_data['nid']['value'])){
      $nid = $message_data['nid']['value'];
    }

    $type_com = NULL; // Var to stock type message comment

    switch($req){
      case 'NCON':
        $groups = explode(",", $message_data['groups']['value']);
        if($groups['0'] == ""){ // If no registered groups
          $groups = NULL;
        }

        $terms = explode(",", $message_data['tags']['value']);
        if($terms['0'] == ""){ // If no registered terms
          $terms = NULL;
        }

        if(isset($groups)){
          foreach($groups as $group_item){ //Getting subscribed users for each referenced group
            $subscribed_group[] = gofast_subscription_ui_api_subscribed_list('group', $group_item, $nid);
          }
        }

        if(isset($terms)){
          foreach($terms as $term_item){ //Getting subscribed users for each referenced term
            $subscribed_term[] = gofast_subscription_ui_api_subscribed_list('term', $term_item, $nid);
          }
        }

        if(isset($message_data['ruid']['to'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['ruid']['to'], $nid);
        }
        else if(isset($message_data['uid']['to'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['to'], $nid);
        }
        else if(isset($message_data['ruid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['ruid']['value'], $nid);
        }
        else if(isset($message_data['uid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['value'], $nid);
        }
        break;
      case 'ECON':
        $groups_array = $message_data['groups']; //Split old and new datas
        if(count($groups_array) == 2){
          $groups = explode(",", $groups_array['to']);
        }
        else{
          $groups = explode(",", $groups_array['value']);
        }
        if($groups['0'] == ""){ // If no registered groups
          $groups = NULL;
        }

        $terms_array = $message_data['tags'];
        if(count($terms_array) == 2){
          $terms = explode(",", $terms_array['to']);
        }
        else{
          $terms = explode(",", $terms_array['value']);
        }
        if($terms['0'] == ""){ // If no registered terms
          $terms = NULL;
        }
        if(isset($groups)){
          foreach($groups as $group_item){ //Getting subscribed users for each referenced group
            $subscribed_group[] = gofast_subscription_ui_api_subscribed_list('group', $group_item, $nid);
          }
        }
        if(isset($terms)){
          foreach($terms as $term_item){ //Getting subscribed users for each referenced term
            $subscribed_term[] = gofast_subscription_ui_api_subscribed_list('term', $term_item, $nid);
          }
        }
        if(isset($message_data['ruid']['to'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['ruid']['to'], $nid);
        }
        else if(isset($message_data['uid']['to'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['to'], $nid);
        }
        else if(isset($message_data['ruid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['ruid']['value'], $nid);
        }
        else if(isset($message_data['uid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['value'], $nid);
        }
        if(isset($message_data['nid']['value'])){
          $subscribed_node = gofast_subscription_ui_api_subscribed_list('node', $message_data['nid']['value'], $nid);
        }
        break;
        case 'NMEM':
        case 'DMEM': // Generate notification for the group administrator

        watchdog('gofast_mail_queue', 'from gofast_message for membership add/delete', array(), WATCHDOG_INFO);
        $subscriptions = gofast_subscription_ui_api_subscribed_list('group', $nid, $nid);

        // notify only administrator of this spaces
        $adms = get_all_admin_group($nid);
        foreach($subscriptions as $key => $sub_user){
          if(! in_array($sub_user[0], $adms)){
            unset($subscriptions[$key]);
          }
        }

        $subscribed_group[] = $subscriptions;

        break;

      case 'ECOM':

        $type_com='message_comment';

        if(isset($message_data['uid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['value'], $nid, TRUE);
        }

        if(isset($message_data['nid']['value'])){
          $subscribed_node = gofast_subscription_ui_api_subscribed_list('node', $message_data['nid']['value'], $nid, TRUE);
          $node = node_load($message_data['nid']['value']);
          $node_split = gofast_message_ext_split_node($node);
          $groups_array = $node_split['groups'];
          $groups = explode(",", $groups_array);

          if($groups['0'] == ""){ // If no registered groups
            $groups = NULL;
          }

          if(isset($groups)){
            foreach($groups as $group_item){ //Getting subscribed users for each referenced group

              $subscribed_group[] = gofast_subscription_ui_api_subscribed_list('group', $group_item, $nid, TRUE);
            }
          }
        }

        break;

       case 'NCOM':

        $type_com='message_comment';

        if(isset($message_data['uid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['value'], $nid, TRUE);
        }

        if(isset($message_data['nid']['value'])){
          $subscribed_node = gofast_subscription_ui_api_subscribed_list('node', $message_data['nid']['value'], $nid, TRUE);
          $node = node_load($message_data['nid']['value']);
          $node_split = gofast_message_ext_split_node($node);
          $groups_array = $node_split['groups'];
          $groups = explode(",", $groups_array);

          if($groups['0'] == ""){ // If no registered groups
            $groups = NULL;
          }

          if(isset($groups)){
            foreach($groups as $group_item){ //Getting subscribed users for each referenced group

              $subscribed_group[] = gofast_subscription_ui_api_subscribed_list('group', $group_item, $nid, TRUE);
            }
          }
        }

        break;

       default: //TODO: Generate notification for groups
        if(isset($message_data['uid']['value'])){
          $subscribed_user = gofast_subscription_ui_api_subscribed_list('user', $message_data['uid']['value'], $nid);
        }
        if(isset($message_data['nid']['value'])){
          $subscribed_node = gofast_subscription_ui_api_subscribed_list('node', $message_data['nid']['value'], $nid);
          $node = node_load($message_data['nid']['value']);
          $node_split = gofast_message_ext_split_node($node);
          $groups_array = $node_split['groups'];
          $groups = explode(",", $groups_array);
          if($groups['0'] == ""){ // If no registered groups
            $groups = NULL;
          }

          if(isset($groups)){
            foreach($groups as $group_item){ //Getting subscribed users for each referenced group
              $subscribed_group[] = gofast_subscription_ui_api_subscribed_list('group', $group_item, $nid);
            }
          }
        }
        break;
    }


    if($type == 'message_kanban'){
        $node = node_load($message_data['nid']['value']);
    }
    // remove empty targets
    $subscribed_group = array_filter($subscribed_group, fn($group) => is_array($group));
    $subscribed_term = array_filter($subscribed_term, fn($term) => is_array($term));
    // destructure n-2 arrays as n-1 arrays
    $subscribed_group = array_merge(...array_values($subscribed_group));
    $subscribed_term = array_merge(...array_values($subscribed_term));
    // merge all subscription arrays
    $all_subscription_items = array_merge($subscribed_user ?: [], $subscribed_node ?: [], $subscribed_group ?: [], $subscribed_term ?: []);
    if ($all_subscription_items != NULL) {
      // accumulators intended to check for duplicates
      $filtered_subscription_items = [];
      $met_uids = [];
      $highest_met_frequency = [];
      // store unique uid values with highest frequencies
      foreach($all_subscription_items as $subscription_item) {
        if(in_array($subscription_item[0], $met_uids))  {
          if($subscription_item[1] == 4) {
            $highest_met_frequency[$subscription_item[0]] = $subscription_item[1];
          } elseif ($subscription_item[1] < $highest_met_frequency[$subscription_item[0]]) {
            $highest_met_frequency[$subscription_item[0]] = $subscription_item[1];
          }
          continue;
        }
        $met_uids[] = $subscription_item[0];
        $highest_met_frequency[$subscription_item[0]] = $subscription_item[1];
      }
      // recreate same-structured subscription array with unique stored values
      foreach($highest_met_frequency as $uid => $frequency) {
        $filtered_subscription_items[] = [$uid, $frequency];
      }
      // single loop for db insertion
      foreach($filtered_subscription_items as $subscription_item){
        if($subscription_item[0] != ""){ //Empty target (fix some empty arrays returned issue)
          if($type == 'message_kanban' && $type_com != NULL){
              if(gofast_kanban_is_user_concerned_node($node, $subscription_item[0])){
                    gofast_mail_queue_api_query($subscription_item, $message_json, $type_com);
              }
          }elseif($type_com != NULL ){
                gofast_mail_queue_api_query($subscription_item, $message_json, $type_com);
          }else{
                gofast_mail_queue_api_query($subscription_item, $message_json, $type);
          }
        }
      }
    }

    $timer_stop = microtime(true);
    watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
  }
}

/**
 *  Queue a message from external modules
 * @param type $mail
 *  Array that have to contains:
 *    'body'    =>  The body of the mail
 *    'title'   =>  The title in the mail
 *    'footer'  =>  The text in the footer of the mail
 *    'subject' =>  The subject of the mail
 * @param type $recpts
 *  An array of user's uids or mail addresses to send the mail
 *  Formated as:
 *  array =>
 *        array
 *            =>
 *            'recpt' => uid/mail
 *            'method' => 'to'/'cc'/'bcc'
 * @param type $cron_timestamp
 *  Timestamp indicates when the message have to be send
 *
 * @param type $transmitter_id
 * Transmitter id for the 'Reply to' mail option
 */
function gofast_mail_queue_api_queue_ext($mail, $recpts, $cron_timestamp, $transmitter_id = ''){
  $message = json_encode($mail);
  $recpts_encode = json_encode($recpts);
    db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $message,
          'uid' =>  $recpts_encode,
          'cron_timestamp'=> $cron_timestamp,
          'timestamp' => time(),
          'type' => 'ext',
          'transmitter_id' => $transmitter_id
        ))
        ->execute();
}

/**
 * Calcul sending timestamp and query to database
 *
 * @param $subscription
 *  An array 0=>user; 1=>frequency
 *
 * @param $log
 *  Message to log
 *
 */
function gofast_mail_queue_api_query($subscription, $log, $type = "message"){

  $timer_start = microtime(true);
  watchdog('gofast_mail_queue', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

  $uid = $subscription['0'];

  $message_data = json_decode($log, TRUE);
  if (isset($message_data["ignore_mail_queue"]["value"]) && $message_data["ignore_mail_queue"]["value"] == TRUE) {
    return;
  }
  //Looking for modifier to avoid sending him a notification
  if(isset($message_data['ruid']['to'])){
    $modifier = $message_data['ruid']['to'];
  }
  else if(isset($message_data['ruid']['from'])){
    $modifier = $message_data['ruid']['from'];
  }
  else if(isset($message_data['ruid']['value'])){
    $modifier = $message_data['ruid']['value'];
  }
  else if(isset($message_data['uid']['to'])){
    $modifier = $message_data['uid']['to'];
  }
  else if(isset($message_data['uid']['from'])){
    $modifier = $message_data['uid']['from'];
  }
  else if(isset($message_data['uid']['value'])){
    $modifier = $message_data['uid']['value'];
  }

  //To reimplement/improve if needed to clear the queue
  /*$compare = db_query("SELECT COUNT(*) FROM gofast_mail_queue WHERE uid='".$uid."' AND message='".$log."'")->fetch();
  $count_var = 'COUNT(*)';
  if($compare->$count_var != 0){ //We don't queue an existing notification with this message
    watchdog('lemangaj', 'duplicate event');
    return;
  }*/
  //watchdog('lemangaj', 'queuing event');
  if($uid != $modifier){ //Avoid notifications for the modifier's events

    $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
    $uid_json = json_encode($uid_formated);
    $frequency = $subscription['1'];
    switch($frequency){
      case '0':
        $timestamp_send = strtotime("12:00 pm");
        if($timestamp_send < time()){
          $timestamp_send = strtotime("+12 hours", $timestamp_send);
        }
        if($timestamp_send < time()){
          $timestamp_send = strtotime("+12 hours", $timestamp_send);
        }
        db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $log,
          'uid' =>  $uid_json,
          'cron_timestamp'=> $timestamp_send,
          'timestamp' => time(),
          'type' => $type
        ))
        ->execute();
        break;
        break;
      case '1':
        $timestamp_send = strtotime("tomorrow 12:00 pm");
        db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $log,
          'uid' =>  $uid_json,
          'cron_timestamp'=> $timestamp_send,
          'timestamp' => time(),
          'type' => $type
        ))
        ->execute();
        break;
      case '2':
        $timestamp_send = strtotime("Monday 12:00 pm");
        db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $log,
          'uid' =>  $uid_json,
          'cron_timestamp'=> $timestamp_send,
          'timestamp' => time(),
          'type' => $type
        ))
        ->execute();
        break;
      case '3':
        $timestamp_send = strtotime("first day of next month 12:00 pm");
        $query = db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $log,
          'uid' =>  $uid_json,
          'cron_timestamp'=> $timestamp_send,
          'timestamp' => time(),
          'type' => $type
        ))
        ->execute();
        break;
      case '4':
        $timestamp_send = time();
        db_insert('gofast_mail_queue')
        ->fields(array(
          'message' => $log,
          'uid' =>  $uid_json,
          'cron_timestamp'=> $timestamp_send,
          'timestamp' => time(),
          'type' => $type
        ))
        ->execute();
        break;
      case '5':
      default:
        break;
    }
  }

   $timer_stop = microtime(true);
   watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);


}

//
/**
 * Retrieve notifications for an uid
 *
 * @param $uid
 *  ID of the user to retrieve notifications
 * @return
 *  An array of pending notifications
 */


function gofast_mail_queue_api_get_user_notifications($uid){
  $items = NULL;
  //The query will get all the notifications.
  $query = db_query("SELECT qid, message, cron_timestamp, uid FROM gofast_mail_queue"); // WHERE uid='".$uid."'

  foreach($query as $occur){
    $item_qid = $occur->qid;
    $item_cron_timestamp = $occur->cron_timestamp;

    $item_message_json = $occur->message;
    $item_message_array = json_decode($item_message_json, TRUE);

    $item_message = "";
    $item_uid = $occur->uid;

    foreach($item_message_array as $item_k => $item_v){
      if(isset($item_v['from']) && isset($item_v['to'])){
        $item_message .= ($item_k." : ".$item_v['from']." => ".$item_v['to']."<br />");
      }
      if(isset($item_v['value'])){
        $item_message .= ($item_k." : ".$item_v['value']."<br />");
      }
    }

    $items[] = array(
      'qid'             => $item_qid,
      'message'         => $item_message,
      'json_message'    => $item_message_json,
      'cron_timestamp'  => $item_cron_timestamp,
      'uid'             => $item_uid
    );
  }
  return $items;
}

/**
 *
 * @param type $subject
 *  The subject of the email
 * @param type $title
 *  The title at the top of the mail
 * @param type $footer
 *  The footer content at the end of the mail
 * @param type $body
 *  The body of the email
 * @param type $recpt
 *  An array of user's uids or mail addresses to send the mail
 *  Formated as:
 *  array =>
 *        array
 *            =>
 *            'recpt' => uid/mail
 *            'method' => 'to'/'cc'/'bcc'
 *  * @param type $urlAttachmentFile
 *  URL of the file you may want to attach
 * @return boolean
 *  Return TRUE the mails was successfully sent
 *  If an error was caught, return a formated string with an error message
 */

function gofast_mail_queue_api_send_mail(string $subject, string $title, string $footer, string $body, array $recpt, $urlAttachmentFile = '', $urlAttachmentTitle = '', $attachement_method = 'REQUEST', $alt_body = "", $transmitter_id = ""){
  if($_POST['inhibit_send_mail']){
      watchdog('gofast_mail_queue', "Send mail currently inhibited");
      return TRUE;
  }

  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Send mail');

  $mail = new PHPMailer; //The mail object from PHPMailer
  foreach((array)$recpt as $recept_item){

    if(is_numeric($recept_item['recpt'])){ //If it's a uid
      $user = user_load($recept_item['recpt']); //Load the user
      if($user->status == 0 && gofast_user_is_left($user)){
          watchdog('gofast_mail_queue', 'prevent sending email to blocked user : '.$user->uid);
          continue;
      }
      if( ! empty(gofast_user_display_name($user) )){ //Get the user's name
        $user_name = gofast_user_display_name($user);
      }
        $user_mail = $user->mail; //Get the user's mail
    }
    else{ //If it's a mail address
      $user = user_load_by_mail($recept_item['recpt']); //Load the user
      if(isset($user->uid) && gofast_user_is_left($user)){
          watchdog('gofast_mail_queue', 'prevent sending email to blocked user : '.$user->uid);
          continue;
      }
      $user_name = "";
      $user_mail = $recept_item['recpt'];
    }
    switch($recept_item['method']){
      case 'to':
        $mail->addAddress($user_mail, $user_name);
        break;
      case 'cc':
        $mail->addCC($user_mail, $user_name);
        break;
      case 'bcc':
        $mail->addBCC($user_mail, $user_name);
        break;
    }
  }

  
  // Generate "Reply to" (the transmitter)
  if(is_numeric($transmitter_id)){
    $_transmitter = user_load($transmitter_id);
    $_mail_transmitter = $_transmitter->mail;
    $_username_transmitter = gofast_user_display_name($_transmitter);

    $mail->AddReplyTo($_mail_transmitter, $_username_transmitter);
    // Generate "FROM" username
    $mail->SetFrom(variable_get('site_mail'), $_username_transmitter);
  }else{
    $mail->setFrom(variable_get('site_mail'), variable_get('site_mail_sender', 'Postmaster ' . variable_get('site_name', 'GoFast')));
  }
  $mail->isHTML(true);
  $mail->CharSet = "utf-8";
  $mail->isSMTP();
  $mail->SMTPAutoTLS = false; // Disabled TLS (enabled by default) for now
  $mail->SMTPSecure = variable_get('smtp_protocol');
  $mail->Port = variable_get('smtp_port');
  $mail->Host = variable_get('smtp_host');
  $mail->Username = variable_get('smtp_username');
  $mail->Password = variable_get('smtp_password');
  if($mail->Username == "" && $mail->Password == ""){
    $mail->SMTPAuth = false;
  }else{
    $mail->SMTPAuth = true;
  }

  $mail->Subject = $subject;
  //Formating the final form of the mail:
  global $base_url;
  
  $l = array('langcode' => $user->language, 'context' => 'gofast:gofast_mail_queue');
  $format_mail = "";
  $format_mail .= theme('gofast-notifications-mailer-header', array('logo' => theme_get_setting('logo', 'bootstrap_gofast'), 'title' => $title)); //Include header

  // if the template has been generated by MJML and thus contains Outlook-specific tags, we don't want to use the legacy body wrapper
  if (strpos((string) $body, "[if mso | IE]") !== false) {
    $format_mail .= $body;
  } else {
    $format_mail .= theme('gofast-notifications-mailer-body', array('content' => $body)); //Body
  }
  $format_mail .= theme('gofast-notifications-mailer-footer', array('footer' => $footer, 'l' => $l)); //Footer
  //$mail->Body = $format_mail;
  $mail->msgHTML($format_mail);

  if($alt_body){
    $mail->AltBody = $alt_body;
  }

  if (!empty($urlAttachmentFile)) {
    $mail->addStringAttachment(file_get_contents($urlAttachmentFile), $urlAttachmentTitle, '8bit', 'text/calendar; method='.$attachement_method.'; charset=UTF-8', '');
    $mail->addStringAttachment(file_get_contents($urlAttachmentFile), $urlAttachmentTitle, 'base64', 'application/ics', 'attachment');
  }

  //Allow modules to alter mail before sending it
  foreach(module_implements('gofast_mail_alter') as $module){
    call_user_func_array($module . "_gofast_mail_alter", array(
      &$mail,
      array(
        'subject' => $subject,
        'title' => $title,
        'footer' => $footer,
        'body' => $body,
        'rectp' => $recpt,
        'urlAttachmentFile' => $urlAttachmentFile,
        'urlAttachmentTitle' => $urlAttachmentTitle,
        'atachement_method' => $attachement_method,
        'alt_body' => $alt_body,
      )
    ));
  }
  if(!$mail->send()){
    watchdog('gofast_mail_queue', 'ERROR Sending mail: '.$mail->ErrorInfo);
    $return = "Mail: Error, cannot send one or multiple email(s), reason: ".$mail->ErrorInfo;
  }
  else{
    $return = TRUE;
  }
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Send mail. '.$end_timer.' sec was needed.');
  return $return;
}

/**
 * Implements hook_cron
 * Send mails in queue
 */
function gofast_mail_queue_cron(){
  //Clear notification queue to avoid errors or multiple occurences
  $start_timer = time();

  watchdog('gofast_mail_queue', 'START: Clear subscriptions');
  gofast_mail_queue_api_clear_queue();
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Clear subscriptions. '.$end_timer.' sec was needed.');

  //Push mails to mail queue mailing system
  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Push notifications');
  gofast_mail_queue_api_push();
  $end_timer = time()-$start_timer;

  //watchdog('gofast_mail_queue', 'START: Push notifications KANBAN');
  //gofast_mail_queue_api_push("message_kanban");
  // $end_timer = time()-$start_timer;
  //watchdog('gofast_mail_queue', 'END: Push notifications. '.$end_timer.' sec was needed.');

  watchdog('gofast_mail_queue', 'START: Push notifications Comment');
  gofast_mail_queue_api_push("message_comment");
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Push notifications. '.$end_timer.' sec was needed.');
}

/**
 * When called, push 20 mails from the queue to the users
 */
function gofast_mail_queue_api_push($type = NULL){

  watchdog('gofast_mail_queue', 'START: Sort matching notifications to push');
  $start_timer = time();
  $sorted_notifications = gofast_mail_queue_api_sort_match(TRUE, NULL, $type); //Sort notifications to send

  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Sort match. '.$end_timer.' sec was needed.');
  $i=0;

  foreach($sorted_notifications as $uid => $array_notifications){
    $array_notification = array();
    $array_attachments_to_delete = array();


    foreach($array_notifications as $array_notification_item){

      if($array_notification_item->type != 'ext'){
        $array_notification[] = $array_notification_item;
      }
      else{ //External notification
        if($array_notification_item->cron_timestamp <= time()){
          if(isset($array_notification_item->transmitter_id)){
            $transmitter_id = $array_notification_item->transmitter_id;
          }
          $array_notification_ext = json_decode($array_notification_item->message, TRUE);
          $body_ext = $array_notification_ext['body'];
          $footer_ext = $array_notification_ext['footer'];
          $title_ext = $array_notification_ext['title'];
          $subject_ext = $array_notification_ext['subject'];

          //Attachment
          $attachmentFile = isset($array_notification_ext['urlAttachmentFile']) ? $array_notification_ext['urlAttachmentFile'] : '';
          $attachmentTitle = isset($array_notification_ext['urlAttachmentTitle']) ? $array_notification_ext['urlAttachmentTitle'] : '';
          $attachmentMethod= isset($array_notification_ext['attachmentMethod']) ? $array_notification_ext['attachmentMethod'] : "REQUEST";
          $altBody = isset($array_notification_ext['altBody']) ? $array_notification_ext['altBody'] : "";
          $mustDeleteAttachementFile  = isset($array_notification_ext['deleteAttachment']) ? $array_notification_ext['deleteAttachment'] : FALSE;

          $recpt_ext = json_decode($array_notification_item->uid, TRUE);

          gofast_mail_queue_api_send_mail($subject_ext, $title_ext, $footer_ext, $body_ext, $recpt_ext, $attachmentFile, $attachmentTitle, $attachmentMethod, $altBody, $transmitter_id);
          gofast_mail_queue_delete_queue_item($array_notification_item->qid);

          //delete attachment if present and deletion required
          if($mustDeleteAttachementFile && isset($array_notification_ext['urlAttachmentFile']) && file_exists($array_notification_ext['urlAttachmentFile'])){
            $array_attachments_to_delete[] = $array_notification_ext['urlAttachmentFile'];
          }
        }
      }
    }

    $user = user_load($uid);
    $l = array('langcode' => $user->language, 'context' => 'gofast:gofast_mail_queue');
    //__________________________________________________________FOOTER___________________________________________________
    global $base_url;
    $footer = "";
    $link_sui = "<a href='".$base_url."/subscriptions'>".t('follow this link', array(), $l).".</a>";
    $footer .= t('This is an automatic mail sent by !site_name.', array('!site_name' => variable_get('site_name')), $l);
    $footer .= "<br />";
    $footer .= t('To manage your subscriptions, you can', array(), $l)." ".$link_sui;
    //Subject: 'Notification report date'
    $short_format = system_date_format_locale($user->language, "short");
    if($type == NULL){

      $subject = t('Notifications report (!date)', array('!date' => format_date(time(), 'custom', $short_format, NULL, $l["langcode"])), $l);
      $title = t("Your notifications from site_name", array('site_name' => variable_get('site_name')), $l);
      $body = (string) gofast_mail_queue_format_mail($array_notification);
      if($body != NULL){
        $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
        gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
      }
    /*}else if($type == "message_kanban"){

        $subject = t('Notifications report for Tasks (!date)', array('!date' => format_date(time(), 'short')), $l);
        $title = t("Your Tasks notifications from site_name", array('site_name' => variable_get('site_name')), $l);
        $body = gofast_mail_queue_format_kanban_mail($array_notification);
        if($body != NULL){
          $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
          gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
        }*/
    }else if($type == "message_comment"){
        $subject = t('Notifications report for comments (!date)', array('!date' => format_date(time(), 'custom', $short_format, NULL, $l["langcode"])), $l);
        $title = t("Your Comments notifications from site_name", array('site_name' => variable_get('site_name')), $l);
        $body = (string) gofast_mail_queue_format_mail($array_notification, "comment");
        if($body != NULL){
          $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
          gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
        }

    }else{
        //TODO make it works with other types, not just KANBAN
    }

    //Subject: 'Members Notification'
    $subject = t('Membership notifications report (!date)', array('!date' => format_date(time(), 'custom', $short_format, NULL, $l["langcode"])), $l);
    $title = t("Your notifications from site_name", array('site_name' => variable_get('site_name')), $l);
    // $body = (string) gofast_mail_queue_format_membership_mail($array_notification);
    
    $item_uid = json_decode(reset($array_notification)->uid, TRUE)[0]['recpt'];
    $item_user = user_load($item_uid);
    
    $myformat = system_date_format_locale($item_user->language, "medium");
    
    $event_filters = array('NMEM', 'DMEM');
    $items_sort = (array) gofast_mail_queue_sort_notifications($array_notification, $item_user, $event_filters);
    
    $modification_type = [];
    $spaces = [];
    $authors = [];
    $user_names = [];
    $user_picts = [];
    $user_added = [];
    $new_members = [];
    $removed_members = [];
    $date = [];
    
    foreach($items_sort as $group => $items){
      
      foreach($items as $nid => $item){
        $new_members[$nid] = 0;
        $removed_members[$nid] = 0;
        
        foreach($item as $key => $event){
          
          
          $message = json_decode($event->message,true);
          $timestamp = $event->timestamp;
          
          
          $date[$nid][$key] = format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"]);
          $modification_type[$nid][$key] = $message['event']['value'];
          if($modification_type[$nid][$key] == "NMEM"){
            $new_members[$nid]++;
          } elseif ($modification_type[$nid][$key] == "DMEM"){
            $removed_members[$nid]++;
          }
          
          if (!$spaces[$nid]) {
            $spaces[$nid] = new stdClass();
          }
          $spaces[$nid]->path = str_replace("/_","/",str_replace("/Sites/_","",$message['path']['value']));
          $spaces[$nid]->icon = gofast_node_get_icon(node_load($nid));
          $authors[$nid][$key] = gofast_user_get_display_name_sql($message['ruid']['value']);

          if (!$user_picts[$nid]) {
            $user_picts[$nid] = [];
          }
          if (!$user_names[$nid]) {
            $user_names[$nid] = [];
          }
          
          if ('user' == $message['new_member_type']['value']) {
            $user_added = user_load($message['new_member_id']['value']);
            $user_added_display_name = gofast_user_display_name($user_added);
            $user_picts[$nid][$key] = '<img width="40" style="border-radius: 5px; vertical-align: middle;" typeof="foaf:Image" src="' . gofast_get_url_picture_by_id($user_added->picture->fid) . '" alt="' . t("@user's picture", array('@user' => $user_added_display_name), array('context' => 'gofast:gofast_user')) . '" title="' . t("@user's picture", array('@user' => $user_added_display_name), array('context' => 'gofast:gofast_user')) . '" />';
            $user_names[$nid][$key] = $user_added_display_name;
          }else{
            $userlist_added = entity_load_single('userlist', $message['new_member_id']['value']);
            $user_picts[$nid] = theme('gofast_userlist_picture', array('member' => $userlist_added, 'dimensions' => 40, 'attributes' => ['style' => "border-radius: 5px; width:40px;"]));
            $user_names[$nid] = $userlist_added->name;
          }
        }
      }
    }
    
    if (count($items_sort) > 0){
      $body = theme('gofast-notifications-mail-notifications-report',array(
        'modification_type' => $modification_type,
        'spaces' => $spaces,
        'authors' => $authors,
        'user_picts' => $user_picts,
        'user_names' => $user_names,
        'item_user' => $item_user,
        'new_members' => $new_members,
        'removed_members' => $removed_members,
        'date' => $date,
        'l' => array('langcode' => $user->language, 'context' => 'gofast'),
      ));
    
      $footer = variable_get('site_name', 'GoFAST');
      
      $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
      gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
    }

    foreach($array_notification as $notification){
      gofast_mail_queue_delete_queue_item($notification->qid);
    }
    if($i>MAX_NOTIFICATIONS_BY_PUSH){
      break;
    }
    $i++;
  }

  //Delete attachment
  foreach($array_attachments_to_delete as $attachment){
      unlink($attachment);
  }

}

function gofast_mail_build_comments_events(&$body, &$commented, &$edit_commented, $message, $event_name, $group_index, $item_index, $event_index) {
  if(strcmp($event_name['value'], "NCOM") == 0){ //New comment case
    $commented++;

    $body[$group_index]['items'][$item_index]['events'][$event_index]['type'] = "NCOM";
    $body[$group_index]['items'][$item_index]['events'][$event_index]['comment_title'] = $message['title']['value'];
    $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['body']['value'];
  }
  else if(strcmp($event_name['value'], "ECOM") == 0){ //Edited comment case
    $edit_commented ++;

    $body[$group_index]['items'][$item_index]['events'][$event_index]['type'] = "ECOM";

    if(isset($message['title']['to'])){
      $body[$group_index]['items'][$item_index]['events'][$event_index]['comment_title'] = $message['title']['to'];
    }
    else{
      $body[$group_index]['items'][$item_index]['events'][$event_index]['comment_title'] = $message['title']['value'];
    }

    if(isset($message['body']['to'])){
      $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['body']['to'];
    }
    else{
      $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['body']['value'];
    }
  }
}

function gofast_mail_build_regular_events(&$body, &$edited, &$count_updates, $message, $event_name, $group_index, $item_index, $event_index) {
  if(strcmp($event_name['value'], "NCON") == 0){ //New content event
    $body[$group_index]['items'][$item_index]['flag'] = "New";
    $body[$group_index]['items'][$item_index]['events'][$event_index]['type'] = "NCON";
    $body[$group_index]['items'][$item_index]['events'][$event_index]['operation'] = "isNew";
    $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['body']['value'];

    if($message['summary']['value'] !== "" && $message['summary']['value'] !== NULL){
      $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['summary']['value'];;
    }
    if($message['body']['value'] !== "" && $message['body']['value'] !== NULL){
      $body[$group_index]['items'][$item_index]['events'][$event_index]['body'] = $message['body']['value'];
    }
  }
  else if(strcmp($event_name['value'], "ECON") == 0 || strcmp($event_name['value'], "NDEL") == 0){ //Edited content event
    $edited++;
    $body[$group_index]['items'][$item_index]['events'][$event_index]['type'] = $event_name['value'];

    foreach($message as $message_k => $message_item){
      if(count($message_item) == 2 && $message_k != "changed" && $message_k != "ruid"){ //Format for each event
        $isTaxoTerm = $message_k == "criticity" || $message_k == "state" || $message_k == "criticity" || $message_k == "category" || $message_k == "tags";
        $isNodeRef = $message_k == "targets" || $message_k == "groups";
        if($isTaxoTerm){ //Translating ids in name
          $from = gofast_message_ext_api_get_term($message_item['from']);
          $to = gofast_message_ext_api_get_term($message_item['to']);
        }
        else if($isNodeRef){
          $from = gofast_message_ext_api_get_node_name($message_item['from']);
          $to = gofast_message_ext_api_get_node_name($message_item['to']);
        }
        else{
          $from = $message_item['from'];
          $to = $message_item['to'];
        }
        //Display only differences for non fulltext fields
        if($message_k != 'body' && $message_k != 'summary'){
          $array_from = explode(",", $from);
          $array_to = explode(",", $to);
          $array_from_diff = array_diff($array_from, $array_to);
          $array_to_diff = array_diff($array_to, $array_from);
          $from = implode(",", $array_from_diff);
          $to = implode(",", $array_to_diff);
        }
        if($from != "" || $to != ""){
          $body[$group_index]['items'][$item_index]['events'][$event_index]['update'] = [
            'field' => $message_k,
            'from' => $from,
            'to' => $to,
          ];
        }
      }
    }
  }
  else if(strcmp($event_name['value'], "NREV") == 0){
    $count_updates++;
    $body[$group_index]['items'][$item_index]['events'][$event_index]['type'] = "NREV";
    $body[$group_index]['items'][$item_index]['events'][$event_index]['revision'] = $message['version']['to'];
  }
}

/**
 * Build mail body for notifications
 * @global type $base_url
 * @param type $notifications
 * @param type $notification_type : "regular" or "comment"
 * @return type $mail body
 *
 */
function gofast_mail_queue_format_mail($notifications, $notification_type = "regular"){
  //Clear notification (double entries...)
  //Warning : Possible performances drop in cron
  $notifications = json_decode(json_encode($notifications), TRUE);
  foreach($notifications as $key_occur => $occur){
    unset ($notifications[$key_occur]['qid']);
  }
  $notifications = array_intersect_key($notifications, array_unique(array_map('serialize', $notifications)));
  $notifications = json_decode(json_encode($notifications));
  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Format mail');

  $item_uid = json_decode(reset($notifications)->uid, TRUE)[0]['recpt'];
  $item_user = user_load($item_uid);
  $user = user_load($item_uid);
  $extra_short_format = system_date_format_locale($user->language, "extra_short");
  $short_without_hours_format = system_date_format_locale($user->language, "short_without_hours");
  $short_format = system_date_format_locale($user->language, "short");
  $l = array('langcode' => $user->language, 'context' => 'gofast');
  if ($notification_type == "comment") {
    $digest_content = t("Your latest notifications of comments for the !date", array("!date" => format_date(time(), 'custom', $short_without_hours_format, NULL, $l["langcode"])), $l);
  } else {
    $digest_content = t("Your latest notifications for the !date", array("!date" => format_date(time(), 'custom', $short_without_hours_format, NULL, $l["langcode"])), $l);
  }
  $digest_title = $user->ldap_user_givenname[LANGUAGE_NONE][0]['value'];

  //________________________________________BUILD THE BODY_______________________________________
  $body = [];
  $items_sort = [];
  foreach($notifications as $item){ //Sort notifications for a user by node id
    $message = json_decode($item->message, TRUE);
    $nid = $message['nid']['value'];
    $node = node_load($nid);//Load node item at it's actual state
    if(isset($node->og_group_content_ref['und'])){
      $match = FALSE;
      foreach($node->og_group_content_ref['und'] as $k_group => $v_group){
        $group_node = node_load($v_group['target_id']);
        $user_gids = gofast_og_get_spaces_by_user($item_user, TRUE, FALSE);
        if(in_array($group_node->nid, $user_gids, TRUE) && $match == FALSE){
          $group = $group_node->title;
          $match  = TRUE;
        }
      }
      if(!$match){
        $group = NULL;
        continue;
      }
    }
    else{
      $group = NULL;
      continue;
    }
    if(!isset($group)){
      continue;
    }
    $items_sort[$group][$nid][] = $item; //Sorting... (By group + By nid)
  }

  //Avoid sendinf empty notification
  if(count($items_sort) == 0){
    return NULL;
  }

  $group_index = 0;
  foreach($items_sort as $group => $items){ //Check groups
    $body[$group_index]['group'] = $group;

    $item_index = 0;
    foreach($items as $nid => $item){ //Check nids
      $node = node_load($nid);

      $body[$group_index]['items'][$item_index]['node'] = $node;

      $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
      $node_icon = gofast_mail_queue_fa_png($node_icon, "14");
      // may be changed
      $node_icon_primary = gofast_mail_queue_fa_png($node_icon, "14");
      $node_icon_white = gofast_mail_queue_fa_png($node_icon, "18", "white");

      $body[$group_index]['items'][$item_index]['icon'] = $node_icon;
      $body[$group_index]['items'][$item_index]['icon_primary'] = $node_icon_primary;
      $body[$group_index]['items'][$item_index]['icon_white'] = $node_icon_white;

      if ($notification_type == "comment") {
        $commented = 0;
        $edit_commented = 0;
      } else {
        $edited = 0;
        $count_updates = 0;
      }

      $event_index = 0;
      foreach($item as $event){//Checking number of events and setting event field
        $message = json_decode($event->message, TRUE);
        $event_name = $message['event'];

        //Loading the most recent modifier
        if(isset($message['ruid']['to'])){
          $user = user_load($message['ruid']['to']);
        }
        else if(isset($message['ruid']['from'])){
          $user = user_load($message['ruid']['from']);
        }
        else if(isset($message['ruid']['value'])){
          $user = user_load($message['ruid']['value']);
        }
        else if(isset($message['uid']['to'])){
          $user = user_load($message['uid']['to']);
        }
        else if(isset($message['uid']['from'])){
          $user = user_load($message['uid']['from']);
        }
        else if(isset($message['uid']['value'])){
          $user = user_load($message['uid']['value']);
        }

        $body[$group_index]['items'][$item_index]['events'][$event_index]['timestamp'] = $event->timestamp;

        if ($notification_type == "comment") {
          $body[$group_index]['items'][$item_index]['events'][$event_index]['user'] = $user;
          $body[$group_index]['items'][$item_index]['events'][$event_index]['author_name'] = gofast_user_display_name($user);
          $body[$group_index]['items'][$item_index]['events'][$event_index]['author_pic'] = '<img width="40" style="border-radius: 5px; vertical-align: middle;" typeof="foaf:Image" src="' . gofast_get_url_picture_by_id($user->picture->fid) . '" alt="' . t("@user's picture", array('@user' => format_username($user)), array('context' => 'gofast:gofast_user')) . '" title="' . t("@user's picture", array('@user' => format_username($user)), array('context' => 'gofast:gofast_user')) . '" />';
          $body[$group_index]['items'][$item_index]['events'][$event_index]['vid'] = $message['cid']['value'];
          $body[$group_index]['items'][$item_index]['events'][$event_index]['nid'] = $message['nid']['value'];
          gofast_mail_build_comments_events($body, $commented, $edit_commented, $message, $event_name, $group_index, $item_index, $event_index);
        } else {
          gofast_mail_build_regular_events($body, $edited, $count_updates, $message, $event_name, $group_index, $item_index, $event_index);
          // if it's a regular notif, we want to group events by user so we build a temporary user-grouped events array
          $current_uid = $body[$group_index]['items'][$item_index]['events'][$event_index]['user']->uid;
          if (!isset($body[$group_index]['items'][$item_index]['users'][$current_uid]['user'])) {
            $body[$group_index]['items'][$item_index]['users'][$current_uid]['author_name'] = gofast_user_display_name($user);
            $body[$group_index]['items'][$item_index]['users'][$current_uid]["author_pic"] = '<img width="40" style="border-radius: 5px; vertical-align: middle;" typeof="foaf:Image" src="' . gofast_get_url_picture_by_id($user->picture->fid) . '" alt="' . t("@user's picture", array('@user' => format_username($user)), array('context' => 'gofast:gofast_user')) . '" title="' . t("@user's picture", array('@user' => format_username($user)), array('context' => 'gofast:gofast_user')) . '" />';
            $body[$group_index]['items'][$item_index]['users'][$current_uid]['user'] = $user;
          }
          $body[$group_index]['items'][$item_index]['users'][$current_uid]['actions'][] = $body[$group_index]['items'][$item_index]['events'][$event_index];
          // sort actions in user event by timestamp
          usort($body[$group_index]['items'][$item_index]['users'][$current_uid]["actions"], function($a, $b) {
            return (int) $b['timestamp'] <=> (int) $a['timestamp'];
          });
        }

        $event_index++;
      }

      if ($notification_type == "comment") {
        $body[$group_index]['items'][$item_index]['comment_add_count'] = $commented;
        $body[$group_index]['items'][$item_index]['comment_edit_count'] = $edit_commented;

        $met_cids = array();
        // sort item events by desc timestamp
        usort($body[$group_index]['items'][$item_index]['events'], function($a, $b) {
          return (int) $b['timestamp'] <=> (int) $a['timestamp'];
        });
        foreach($body[$group_index]['items'][$item_index]['events'] as $index => $event) {
          // item events being sorted by desc timestamp, we can keep only the first one by cid and be confident that it's the latest operation the user did on that item
          if (!in_array($event['vid'], $met_cids)) {
            $met_cids[] = $event['vid'];
          } else {
            unset($body[$group_index]['items'][$item_index]['events'][$index]);
          }
        }
      } else {
        $body[$group_index]['items'][$item_index]['edit_count'] = $edited;
        $body[$group_index]['items'][$item_index]['update_count'] = $count_updates;

        // if it's a regular notif, we erase the events array with the new user-grouped one
        $body[$group_index]['items'][$item_index]['events'] = $body[$group_index]['items'][$item_index]['users'];
        unset($body[$group_index]['items'][$item_index]['users']);
      }


      $item_index++;
    }

    $group_index++;
  }

  //_____________________________________________________BUILD THE EMAIL_______________________________________________
  $mail = theme('gofast-notifications-node-subheader', array('l' => $l, 'digest_title' => $digest_title, 'digest_content' => $digest_content, 'content' => $body)); //Summary
  $mail .= theme('gofast-notifications-node-body', array('l' => $l, 'short_format' => $short_format, 'short_without_hours_format' => $short_without_hours_format, 'extra_short_format' => $extra_short_format, "content" => $body)); //Events

  $end_timer = time() - $start_timer;
  watchdog('gofast_mail_queue', 'END: Format mail. ' . $end_timer . ' sec was needed.');
  return $mail;
}

function gofast_mail_breadcrumb(stdClass $node): string {
  /*global $base_url;
  $main_path = "";
  if(in_array($node->type, ['alfresco_item', 'article'])) {
      $main_location = array($node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value']);
      $other_locations = isset($node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE]) ? array_map(function ($element) {
        return ($element['value']);
      }, $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE]) : array();
      $locations = array_unique(array_merge($main_location, $other_locations));
      foreach ($locations as $location ){
        if (og_user_access('node', $node->nid, 'view', $user)) {
          $document_folders = explode("/", str_replace("/Sites/", "", $node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value']));
          foreach($document_folders as $folder) {
              if($folder[0] == "_") $folder = t(substr($folder, 1));
              // get translated root spaces
              if(in_array($folder, ["_Groups", "_Public", "_Organisations", "_Extranet"])) $folder = t($folder, array(), array("context" => "gofast"));
              $main_path .= "<span style='color: #0074A6;'>" . $folder . "</span>&nbsp;/&nbsp;";
          }
          break;
        }
      }
  }
  $title = $node->title;
  $title = $main_path . "<a style='text-decoration:none; color:#0074A6' href='".$base_url."/node/".$node->nid."'>".$title."</a>";*/
  
  //GOFAST-7489 For now, remove full breadcrumb in notifications
  global $base_url;
  $title = $node->title;
  $title = "<a style='text-decoration:none; color:#0074A6' href='".$base_url."/node/".$node->nid."'>".$title."</a>";
  
  return $title;
}

/**
 * Private helper used by gofast_node_deadline_notify() to accumulate notification recipients
 * and associated data while avoiding duplicating recipients
 */
function gofast_node_deadline_notify_accumulate_recipients(&$recpt, $subscribers, $node, $node_sub_type = NULL) {
  
  foreach ($subscribers as $subscriber) {    
    $user = user_load($subscriber[0]);
    // nodes are sorted by types relevant to the deadline notification, most relevant types having the lowest indexes
    $node_index = 2;
    if ($node->type == "kanban" || $node->type == "task"){
      $node_index = 1;
    }
    if ($node->type == "conference")  {
      $node_index = 0;
    }
    // we create a new recipient if it doesn't already exist
    if (!isset($recpt[$user->mail])) {
      $recpt[$user->mail] = array(
        'recpt' => $user->mail,
        'method' => 'to',
        'firstname' => $user->ldap_user_givenname[LANGUAGE_NONE][0]['value'],
        'user_language' => $user->language,
      );
      $recpt[$user->mail]['nodes'][$node_index][$node->nid] = clone $node;
    } else if (isset($recpt[$user->mail]['nodes'][$node_index][$node->nid]) && $node_sub_type == "todolist"){
      // if the node is already accumulated for the target recipient, merge todolist items
      $previous_items = $recpt[$user->mail]['nodes'][$node_index][$node->nid]->items ?? [];
      $all_items = $previous_items + $node->items;
      $recpt[$user->mail]['nodes'][$node_index][$node->nid] = clone($node);
      $recpt[$user->mail]['nodes'][$node_index][$node->nid]->items = $all_items;
    } else {
      // if new recipient already exists, we just add the new node to its registry
      $recpt[$user->mail]['nodes'][$node_index][$node->nid] = clone $node;
    }
  }
}

/**
 *
 * Once per day, retrieve all node with deadline = tomorrow, then send a email
 * to related users.
 */
function gofast_node_deadline_notify(){
  $tomorrow = new DateTime('tomorrow');
  $tomorrow_str = $tomorrow->format('Y-m-d');

  $query = new EntityFieldQuery();
  // we also take the conferences and tasks node types
  $query->entityCondition('entity_type', 'node')
     ->entityCondition('bundle', array('webform'), 'NOT IN')
     ->propertyCondition('status', 1)
     ->fieldCondition('field_date', 'value', $tomorrow_str.'%', 'like');
  $result = $query->execute();
  
  $recpt = array();
  $nids = array();

  if (isset($result['node'])) {
    $nids = array_unique(array_keys($result['node']));
    $nodes = node_load_multiple($nids);

    foreach ($nodes as $node) {
      $subscribers = array();
      
      if($node->type == "kanban" || $node->type == "task"){ // do not notify all space members
        $i = 0;
        if(isset($node->field_person_in_charge[LANGUAGE_NONE][0]['target_id']) && $node->field_person_in_charge[LANGUAGE_NONE][0]['target_id'] !== 0){
           $subscribers[$i][0] = $node->field_person_in_charge[LANGUAGE_NONE][0]['target_id'];
           $i++;
        } 
        foreach($node->field_members[LANGUAGE_NONE] as $member){
          if ($subscribers[$i - 1][0] == $member['target_id']) {
            continue; 
          }
          $subscribers[$i][0] =  $member['target_id'];
          $i++;
        }
        if (isset($subscribers)) {
          $node->responsible = $node->field_person_in_charge[LANGUAGE_NONE][0]['target_id'] ? user_load($node->field_person_in_charge[LANGUAGE_NONE][0]['target_id']) : NULL;
          gofast_node_deadline_notify_accumulate_recipients($recpt, $subscribers, $node);
        }
      }
      //if node is conference, get conference participants
      elseif ($node->type == "conference") {
        $participants = $node->field_existing_participants[LANGUAGE_NONE];
        $i = 0;
        foreach($participants as $participant){
          $subscribers[$i][0] = $participant['target_id']; 
          $i++;
        }
        
        if (isset($subscribers)) {
          gofast_node_deadline_notify_accumulate_recipients($recpt, $subscribers, $node);
        }  
      }
      else{
        $og_groups = $node->og_group_content_ref['und'];

        //get group subscriber
        if (isset($og_groups)) {
          $met_subscribers = [];
          foreach ($og_groups as $og_group) {
            //retrieve subscribers
            $subscribers = gofast_subscription_ui_api_subscribed_list('og', $og_group['target_id']);
            if (isset($subscribers)) {
              // don't sent multiple times the same multifiled documents to the same user
              $subscribers = array_diff($subscribers, $met_subscribers);
              gofast_node_deadline_notify_accumulate_recipients($recpt, $subscribers, $node);
              $met_subscribers = [...$met_subscribers, ...$subscribers];
            }
          }
        }
      }
    }
  }

  //look for kanban todolist item deadline
  $filters = array(
    0 => array(
      'name' => 'status',
      'value' => '0', //uncompleted
      'operator' => '='
    ),
    1 => array(
      'name' => 'deadline',
      'value' => strtotime("tomorrow noon"),
      'operator' => '<'
    ),
    2 => array(
      'name' => 'deadline',
      'value' => time(),
      'operator' => '>'
    )
  );

  $items = gofast_kanban_get_user_checklistItems(false, TRUE, $filters);
  if (count($items) > 0) {
    foreach ($items as $item) {
      $node = node_load($item->task_nid);
      //don't add item if task is disabled
      if ($node->status == 0) continue;
      //get item data :
      $node->items = [];
      $node->items[$item->ciid] = [];
      $node->items[$item->ciid]["item_label"] = $item->label;
      $node->items[$item->ciid]["item_responsible"] = $item->uid ? user_load($item->uid) : NULL;

      $responsible = $node->field_person_in_charge[LANGUAGE_NONE][0]["target_id"];
      $node->responsible = $responsible ? user_load($responsible) : NULL;
      $parent_space = $node->og_group_content_ref[LANGUAGE_NONE][0]['target_id'];
      $node->parent_space = $parent_space ? gofast_get_node_title($parent_space) : NULL;
      $subscribers = array();
      $subscribers[] = array(0 => $responsible);
      if($item->uid != $responsible){
        $subscribers[] = array(0 => $item->uid);
      }
      gofast_node_deadline_notify_accumulate_recipients($recpt, $subscribers, $node, 'todolist');
    }
  }

  if($recpt){
    //Send notification mail
    foreach ($recpt as $to) {
      // at this stage, the indexes are in the order of their creations, but we want them in asc order
      ksort($to['nodes']);
      $mail_recpt = array();
      $mail_recpt[] = $to;

      $userName = user_load_by_mail($mail_recpt[0]['recpt'])->ldap_user_givenname[LANGUAGE_NONE][0]['value'];

      $RecipUser = user_load_by_mail($mail_recpt[0]['recpt']);
      $l = array('langcode' =>  $RecipUser->language, 'context' => 'gofast');

      $short_without_hours_format = system_date_format_locale($RecipUser->language, "short_without_hours");
      $subject = '['.variable_get('site_name').'] '.t('Your deadline on @date', array('@date' => format_date($tomorrow->getTimestamp() , 'custom', $short_without_hours_format, NULL, $l["langcode"])), $l);
      $title = t('Deadline notification', array(), $l);
      $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');

      $body = theme('gofast-notifications-node-deadline', array(
        'user' => $RecipUser,
        'user_name' => $userName,
        'nodes' => $mail_recpt[0]['nodes'],
        'deadline' => format_date($tomorrow->getTimestamp() , 'custom', $short_without_hours_format, NULL, $l["langcode"]),
        'l' => $l,
      ));

      // we don't need the nodes reference anymore and we really don't want to insert them into db
      unset($mail_recpt[0]['nodes']);

      $mail = array(
        'body' => $body,
        'title' => $title,
        'subject' => $subject,
        'footer' => $footer
      );
      $ret = gofast_mail_queue_api_queue_ext($mail, $mail_recpt, time());
      if ($ret == TRUE) {
        flood_register_event('print_mail');
        $ok = TRUE;
      }
    }
  }
}

/**
 * Return all kind of available event
 * @return string
 */
function gofast_mail_queue_get_all_event_types(){

  $types = array(
      'NCON',
      'ECON',
      'NDEL',
      'NCOM',
      'ECOM',
      'NREV',
      'NMEM',
      'DMEM'
  );
  return $types;
}

/**
 * Sort notifications for a user by node id and can filter event by type if argument is given
 * @param type $notifications
 * @param type $item_user
 * @param type $event_filters
 * @return array
 */
function gofast_mail_queue_sort_notifications($notifications, $item_user, $event_filters = array() ) {

  $timer_start = microtime(true);
  watchdog('gofast_mail_queue', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

  if(empty($event_filters)){
    $event_filters = gofast_mail_queue_get_all_event_types();
  }

  $items_sorted = array();
  foreach ($notifications as $item) {
    $message = json_decode($item->message, TRUE);

    if( ! in_array($message['event']['value'] , $event_filters) ){
      continue;
    }

    $nid = $message['nid']['value'];
    $node = node_load($nid); //Load node item at it's actual state
    if (isset($node->og_group_content_ref['und'])) { // node type
      $match = FALSE;
      foreach ($node->og_group_content_ref['und'] as $k_group => $v_group) {
        $group_node = node_load($v_group['target_id']);
        if (node_access('view', $group_node, $item_user) && $match == FALSE) {
          $group = $group_node->title;
          $match = TRUE;
        }
      }
      if (!$match) {
        $group = NULL;
        continue;
      }
    }else if (isset($node->og_group_ref['und'])){ // group type
      $match = TRUE;
      $group = $node->title;
    } else {
      $group = NULL;
      continue;
    }
    if (!isset($group)) {
      continue;
    }
    $items_sorted[$group][$nid][] = $item; //Sorting... (By group + By nid)
  }

  $timer_stop = microtime(true);
  watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);

  return $items_sorted;
}

/**
 * Clear notification (double enteries...)
 * Warning : Possible performances drop in cron
 * @param array() $notifications
 */
function gofast_mail_queue_clean_notifications(&$notifications) {

  $timer_start = microtime(true);
  watchdog('gofast_mail_queue', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

  $notifications = json_decode(json_encode($notifications), TRUE);
  foreach ($notifications as $key_occur => $occur) {
    unset($notifications[$key_occur]['qid']);
  }
  $notifications = array_intersect_key($notifications, array_unique(array_map('serialize', $notifications)));
  $notifications = json_decode(json_encode($notifications));

  $timer_stop = microtime(true);
  watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
}

/**
 * @deprecated
 * Build notification mail for space administrator (membership activity)
 */
function gofast_mail_queue_format_membership_mail($notifications){

  $timer_start = time(true);
  watchdog('gofast_mail_queue', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

  gofast_mail_queue_clean_notifications($notifications);

  global $base_url;
  $item_uid = json_decode(reset($notifications)->uid, TRUE)[0]['recpt'];
  $item_user = $user = user_load($item_uid);

  $events_body = "";
  $myformat = system_date_format_locale($user->language, "medium");
  $l = array('langcode' => $user->language, 'context' => 'gofast');
  $digest_content = t("Your latest space administrator notifications (membership)", array(), $l) . "<span style='float:right;'>" . "<a style='color:#3F4254;text-decoration:none;' href='" . $base_url . "/subscriptions'>" . t('Manage your subscriptions', array(), $l) . "</a></span>";
  $digest_title = gofast_user_display_name($user);
  $footer = "";

  $event_filters = array('NMEM', 'DMEM');
  $items_sort = gofast_mail_queue_sort_notifications($notifications, $item_user, $event_filters);

  if(count($items_sort) == 0){ // no notifications to be sent
    return NULL;
  }

  //________________________________________SUMMARY AND BODY_______________________________________
  $summary = "";
  $count_node = 0;
  $first = TRUE;


  foreach ($items_sort as $group => $items) { //Check groups
    if (!$first) {
      $summary .= "<br />";
    } else {
      $first = FALSE;
    }

    $count_new_membership = 0;
    $count_removed_membership = 0;

    //$summary .= "<strong>" . $group . "</strong><br />";
    foreach ($items as $nid => $item) { //Check nids
      $pass = FALSE;
      $node = node_load($nid);
      $target = "";
      if (isset($node->field_emplacement['und'])) {
        foreach ($node->field_emplacement['und'] as $space) {
          $target .= $space['value'] . "<br />";
        }
      }
      $path = isset($item[0]) ? json_decode($item[0]->message, TRUE)['path']['value'] : $node->title;
      $title = "<a style='text-decoration:none; color:#0074A6' href='" . $base_url . "/node/" . $node->nid . "'>" . $path . "</a>";
      $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
      $node_icon = gofast_mail_queue_fa_png($node_icon);

      //Variables to increment or set TRUE according to the events:
      $isNew = FALSE;
      $isDeleted = FALSE;
      $updated = FALSE;

      // $pre_updates = array();
      $updates = NULL;
      $updates_summary = NULL;

      $info = null;

      foreach ($item as $event) {//Checking number of events and setting event field
        $message = json_decode($event->message, TRUE);
        $event_name = $message['event'];
        $timestamp = $event->timestamp;

        $user = user_load($message['ruid']['value']);

        $body = NULL;
        $node_target = $base_url . "/node/" . $nid;
        $author = gofast_user_get_display_name_sql($message['ruid']['value']);
        $path = rawurlencode($message['path']['value']);
        $link_path = "<a href='" . $node_target . "?&path=" . $path . "#ogmembers'>" . $message['path']['value'] . "</a>";

        if (strcmp($event_name['value'], "NMEM") == 0) { // New Member in space
          $isNew = TRUE;
          $count_new_membership++;
          $template_name = 'gofast-notifications-node-new-member';
        }else  if (strcmp($event_name['value'], "DMEM") == 0) { // Remove Member in space{
          $isDeleted = TRUE;
          $count_removed_membership++;
          $template_name = 'gofast-notifications-node-remove-member';
        }

        if ('user' == $message['new_member_type']['value']) {
          $user_added = user_load($message['new_member_id']['value']);
          $user_pict = theme('user_picture', array('account' => $user_added, 'dimensions' => 40, 'attributes' => ['style' => "border-radius: 5px; width:40px;"]));
          $user_name = gofast_user_display_name($user_added);
        }else{
          $userlist_added = entity_load_single('userlist', $message['new_member_id']['value']);
          $user_pict = theme('gofast_userlist_picture', array('member' => $userlist_added, 'dimensions' => 40, 'attributes' => ['style' => "border-radius: 5px; width:40px;"]));
          $user_name = $userlist_added->name;
        }

        $updates .= theme($template_name, array(
                      'l' => $l,
                      'user_pic' => $user_pict,
                      'user_name' => $user_name,
                      'body' => $body,
                      'node_link' => $node_target,
                      'title' => $title,
                      'is_digest' => FALSE,
                      'tokens' => NULL,
                      'author' =>$author,
                      "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"]),
                      "path" => $link_path
                    ));

      }
      $info = $info . $updates . $updates_summary;

      //_______________________________________SUMMARY________________________________________________________
      $summary .= "<div id='sum-item'><span>   <a style='color:#007bff;text-decoration:none;' href='" . $base_url . "/node/" . $nid . "' target='_blank'>&emsp;<span>" . $node_icon . "</span>" . $title . "</a> </span>";
      if ($isNew) { //Seting "NEW" message
        $summary .= "<span style='color:green;font-size:8px;'>" . t("NEW MEMBERS (%nb) ", array('%nb' => $count_new_membership), $l) . "</span>";
      }
      if ($isDeleted) { //Seting "VERSION UPDATE" message
        $summary .= "<span style='color:red;font-size:8px;'>" . t("REMOVED MEMBERS (%nb)", array('%nb' => $count_removed_membership), $l) . "</span>";
      }
      $summary .= "</span></div><div style='width:100%; height:1px;'></div>";

      $node_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #bce8f1; opacity: 0.9;padding: 2px; text-align: center;">' . t("Info", array(), array('context' => "gofast:mail_queue")) . '</p>' . $info;

      $events_body .= theme('gofast-notifications-node-update', array('l' => $l, 'count_node' => $count_node, 'isNew' => $isNew, 'isRev' => $updated, 'group' => $group, 'node_icon' => $node_icon, 'node_title' => $title, 'com_updates' => NULL, 'updates' => $node_updates, 'spaces' => $target));
      $count_node ++;
    }
  }
  //_____________________________________________________BUILD THE EMAIL_______________________________________________
  $body = ""; //Build the body
  $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => $digest_title, 'content' => $digest_content)); //Top
  $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => "", "content" => $summary)); //Summary
  $body .= $events_body; //Events

  $mail = ""; //Build the mail structure
  $mail .= theme('gofast-notifications-mailer-body', array('l' => $l, 'content' => $body)); //Include body
  $timer_stop = microtime(true);
  watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
  return $mail;
}

/*
 * Turn font awsome icons into png icons (stored in the img folder of the module)
 */
function gofast_mail_queue_fa_png($input, $width = "", $color = ""){
  $matcher = array(
    'fa-file-word' => 'word',
    'fa-file file-other' => 'other',
    'fa-file-powerpoint' => 'powerpoint',
    'fa-home' => 'home',
    'fa-globe' => 'globe',
    'fa-file-alt' => 'text',
    'fa-comments forums' => 'comments',
    'fa-file-code' => 'code',
    'fa-file-image' => 'image',
    'fa-sitemap' => 'sitemap',
    'fa-newspaper' => 'ballot',
    'fa-file-pdf pdf-image' => 'pdf-image',
    'fa-file-pdf' => 'pdf',
    'fa-share-alt' => 'share',
    'fa-file-excel' => 'excel',
    'fa-users' => 'users',
    'fa-user-single' => 'user',
    'fa-video' => 'conference',
    'fa-file-audio' => 'audio',
    'fa-list-alt file-webform' => 'webform',
    'fa-file file-visio' => 'visio',
    'fa-file-video' => 'video',
    'fa-file-image image-svg' => 'svg',
    'fa-id-card' => 'profile',
    'fa-file-text file-odg' => 'odg',
    'fa-envelope' => 'mail',
    'fa-file file-cao' => 'cao',
    'fa-file-archive' => 'archive',
    'fa-trello' => "trello",
    'fa-flag file-task' => "flag",
    'fa-folder' => "folder",
  );
  foreach($matcher as $fa => $png){
    if(strpos($input, $fa)){
      $output = theme('gofast-notifications-node-icon', array(
        'icon' => $png . (strlen($color) > 0 ? '-' . $color : '') . '.png',
        'width' => $width,
      ));
      return $output;
    }
  }
  $output = theme('gofast-notifications-node-icon', array(
    'icon' => 'other' . (strlen($color) > 0 ? '-' . $color : '') . '.png',
    'width' => $width,
  ));
  return $output;
}
/**
 * Sort pending notification, matching them by uid (used to prepare mails)
 *
 * @param $timestamp_filter
 *  If set to true, this will return notifications only for current or outdated cron timestamp
 * @param $time
 *  Optional: Set the time for timestamp filter
 * @return
 *  An array of matched notifications formatted as:
 *
 *  [uid1] => array
 *        ['0'] => array
 *              ['qid']     => value
 *              ['message'] => value
 *              ...
 *        ['1'] => array
 *              ...
 *  [uid2] => array
 *         ...
 *         ...
 *
 * The params in the array are:
 *  -qid: Queue ID
 *  -message: json encoded message
 *  -uid: user ID to deliver the message
 *  -crom_timestamp: Timestamp the notification have to be sent
 */
function gofast_mail_queue_api_sort_match($timestamp_filter = FALSE, $time = NULL, $type = NULL){
  if(!$time){
    $time = time();
  }
  $start_timer = time();
  //if $type is not null, add a condition
  if($type == NULL){
    $query = db_query("SELECT cron_timestamp,timestamp,qid,uid,type,transmitter_id FROM gofast_mail_queue WHERE cron_timestamp<=".$time." AND (type = 'message' OR type = 'ext') ORDER BY uid LIMIT " . MAX_EVENT_PROCESSED_IN_QUERY)->fetchAll();
  }else{
    $query = db_query("SELECT cron_timestamp,timestamp,qid,uid,type,transmitter_id FROM gofast_mail_queue WHERE cron_timestamp<=".$time." AND type = '".$type."' ORDER BY uid LIMIT " . MAX_EVENT_PROCESSED_IN_QUERY)->fetchAll();
  }
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'EVENT: Mail queue retrieve. '.$end_timer.' sec was needed.');

  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'EVENT: Mail queue retrieve. '.$end_timer.' sec was needed.');

  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'EVENT: Sorted by timestamp. '.$end_timer.' sec was needed.');
  $uid_checked = array(); //Used to do not check the same ID twice
  $return = array();
  $limiter = 0;
  foreach($query as $occur){ //1st loop in datas

    $uid = json_decode($occur->uid, TRUE)[0]['recpt'];

    if(!in_array($uid, $uid_checked, TRUE)){
      $uid_checked[] = $uid;
      $return[$uid]['0'] = $occur;
      $return[$uid]['0']->message = db_query("SELECT message FROM gofast_mail_queue WHERE qid=" . $occur->qid)->fetch()->message;
      $i = 1;
      $event_limit = 0;
      foreach($query as $occur_compare){
      //Compare and match same destination notification for the current timastamp
        $isMatch = ($occur->qid != $occur_compare->qid && $occur->uid == $occur_compare->uid);
        if($isMatch){
          $return[$uid][$i] = $occur_compare;
          $return[$uid][$i]->message = db_query("SELECT message FROM gofast_mail_queue WHERE qid=" . $occur_compare->qid)->fetch()->message;
          $i++;
          $event_limit++;
        }
        if($event_limit >= MAX_EVENT_BY_NOTIFICATION){
          break;
        }
      }
      $limiter++;
      $end_timer = time()-$start_timer;
      watchdog('gofast_mail_queue', 'EVENT: End looping in datas. '.$end_timer.' sec was needed. '.$limiter.' people queued');
    }
    if($limiter >= MAX_NOTIFICATIONS_BY_PUSH){
      break;
    }
  }
  return $return;

}
/**
 * Implements hook_theme
 */

function gofast_mail_queue_theme(){
  $theme['gofast-notifications-mailer-header'] = array(
    'template' => 'tpl/gofast-notifications-mailer-header'
  );
  $theme['gofast-notifications-mailer-digest'] = array(
    'template' => 'tpl/gofast-notifications-mailer-digest'
  );
  $theme['gofast-notifications-mailer-footer'] = array(
    'template' => 'tpl/gofast-notifications-mailer-footer'
  );
  $theme['gofast-notifications-mailer-body'] = array(
    'template' => 'tpl/gofast-notifications-mailer-body'
  );
  $theme['gofast-notifications-node-subheader'] = array(
    'template' => 'tpl/gofast-notifications-node-subheader'
  );
  $theme['gofast-notifications-node-body'] = array(
    'template' => 'tpl/gofast-notifications-node-body'
  );
  $theme['gofast-notifications-node-update'] = array(
    'template' => 'tpl/gofast-notifications-node-update'
  );
  $theme['gofast-notifications-node-event'] = array(
    'template' => 'tpl/gofast-notifications-node-event'
  );
  $theme['gofast-notifications-node-footer'] = array(
    'template' => 'tpl/gofast-notifications-node-footer'
  );
  $theme['gofast-notifications-node-deadline'] = array(
     'template' => 'tpl/gofast-notifications-node-deadline'
   );
   $theme['gofast-notifications-node-deadline-element'] = array(
    'template' => 'tpl/gofast-notifications-node-deadline-element'
  );
  $theme['gofast-notifications-node-icon'] = array(
     'template' => 'tpl/gofast-notifications-node-icon'
   );
  $theme['gofast-notifications-node-new-member'] = array(
     'template' => 'tpl/gofast-notifications-node-new-member'
   );
  $theme['gofast-notifications-node-remove-member'] = array(
     'template' => 'tpl/gofast-notifications-node-remove-member'
   );
   $theme['gofast-notifications-mail-add-remove-member'] = array(
    'template' => 'tpl/gofast-notifications-mail-add-remove-member'
   );
   $theme['gofast-notifications-mail-notifications-report'] = array(
    'template' => 'tpl/gofast-notifications-mail-notifications-report'
   );
   $theme['gofast-notifications-user-standby'] = array(
    'template' => 'tpl/gofast-notifications-user-standby'
  );


  return $theme;
}
