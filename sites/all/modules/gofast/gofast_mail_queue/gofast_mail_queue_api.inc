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
    $subscribed_user = NULL;
    $subscribed_term = NULL;
    $subscribed_group = NULL;
    $subscribed_node = NULL;
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
      case NMEM:
      case DMEM: // Generate notification for the group administrator

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
        
      case ECOM:
          
        $type_com='message_comment';
          
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
        
       case NCOM:
          
        $type_com='message_comment';
          
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

    if($subscribed_user != NULL){
      foreach($subscribed_user as $subscribed_user_item){
        if($subscribed_user_item['0'] != ""){ //Empty target (fix some empty arrays returned issue)
           if($type == 'message_kanban' && $type_com != NULL){
               if(gofast_kanban_is_user_concerned_node($node, $subscribed_user_item[0])){
                    gofast_mail_queue_api_query($subscribed_user_item, $message_json, $type_com);
               }                    
           }elseif($type_com != NULL ){
                gofast_mail_queue_api_query($subscribed_user_item, $message_json, $type_com);
           }else{
                gofast_mail_queue_api_query($subscribed_user_item, $message_json, $type);   
                }
             }
         }
     }
    

    if($subscribed_node != NULL){
      foreach($subscribed_node as $subscribed_node_item){
          if($subscribed_node_item['0'] != ""){ //Empty target (fix some empty arrays returned issue)
          //gofast_mail_queue_api_query($subscribed_node_item, $message_json, $type);
             if($type == 'message_kanban' && $type_com != NULL){
                if(gofast_kanban_is_user_concerned_node($node, $subscribed_node_item[0])){
                    gofast_mail_queue_api_query($subscribed_node_item, $message_json, $type_com);
                }          
             }elseif($type_com != NULL ){
                gofast_mail_queue_api_query($subscribed_node_item, $message_json, $type_com);
             }else{
                gofast_mail_queue_api_query($subscribed_node_item, $message_json, $type);
                      
                }
            }
        }
    }
    

    if($subscribed_group != NULL){
      foreach($subscribed_group as $subscribed_group_array){ //iterating into all groups
        if(isset($subscribed_group_array)){
          foreach($subscribed_group_array as $subscribed_group_item){ //iterating into the group
            if($subscribed_group_item['0'] != ""){ //Empty target (fix some empty arrays returned issue)
              //gofast_mail_queue_api_query($subscribed_group_item, $message_json, $type);              
                if($type == 'message_kanban' && $type_com != NULL){
                   if(gofast_kanban_is_user_concerned_node($node, $subscribed_group_item[0])){
                         gofast_mail_queue_api_query($subscribed_group_item, $message_json, $type_com);
                   }                        
                }elseif($type_com != NULL ){     
                    gofast_mail_queue_api_query($subscribed_group_item, $message_json, $type_com);
                }else{
                    gofast_mail_queue_api_query($subscribed_group_item, $message_json, $type);
                   
                }
            }
          }
        }
      }
    }

    if($subscribed_term != NULL){
      foreach($subscribed_term as $subscribed_term_array){ //Iterating into all tags
        if(isset($subscribed_term_array)){
          foreach($subscribed_term_array as $subscribed_term_item){ //Iterating into the tag
            if($subscribed_term_item != ""){ //Empty target (fix some empty arrays returned issue)
              //gofast_mail_queue_api_query($subscribed_term_item, $message_json, $type);
              if($type == 'message_kanban' && $type_com != NULL){
                    if(gofast_kanban_is_user_concerned_node($node, $subscribed_term_item[0])){
                         gofast_mail_queue_api_query($subscribed_term_item, $message_json, $type_com);
                    }                       
              }elseif($type_com != NULL ){     
                  gofast_mail_queue_api_query($subscribed_term_item, $message_json, $type_com);
              }else{ 
                  gofast_mail_queue_api_query($subscribed_term_item, $message_json, $type);

              }
            }
          }
        }
      }
    }
  }

  $timer_stop = microtime(true);
  watchdog('gofast_mail_queue', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);

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

function gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $recpt, $urlAttachmentFile = '', $urlAttachmentTitle = '', $attachement_method = 'REQUEST', $alt_body = "", $transmitter_id = ""){
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
      if($user->status == 0){
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
      if(isset($user->uid) && $user->status == 0){
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
  }
  $mail->setFrom(variable_get('site_mail'), variable_get('site_mail_sender', 'Postmaster ' . variable_get('site_name', 'GoFast')));
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
  $format_mail = "";
  $format_mail .= theme('gofast-notifications-mailer-header', array('logo' => theme_get_setting('logo', 'bootstrap_gofast'), 'title' => $title)); //Include header
  $format_mail .= theme('gofast-notifications-mailer-body', array('content' => $body)); //Body
  $format_mail .= theme('gofast-notifications-mailer-footer', array('footer' => $footer)); //Footer
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
    if($type == NULL){

        $subject = t('Notifications report (!date)', array('!date' => format_date(time(), 'custom', 'j-m-Y H:i')), $l);
        $title = t("Your notifications from site_name", array('site_name' => variable_get('site_name')), $l);
        $body = gofast_mail_queue_format_mail($array_notification);
        if($body != NULL){
          $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
          gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
        }
    /*}else if($type == "message_kanban"){

        $subject = t('Notifications report for Tasks (!date)', array('!date' => format_date(time(), 'custom', 'j-m-Y H:i')), $l);
        $title = t("Your Tasks notifications from site_name", array('site_name' => variable_get('site_name')), $l);
        $body = gofast_mail_queue_format_kanban_mail($array_notification);
        if($body != NULL){
          $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
          gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
        }*/
    }else if($type == "message_comment"){
        
        $subject = t('Notifications report for comments (!date)', array('!date' => format_date(time(), 'custom', 'j-m-Y H:i')), $l);
        $title = t("Your Comments notifications from site_name", array('site_name' => variable_get('site_name')), $l);
        $body = gofast_mail_queue_format_mail_comment($array_notification);
        if($body != NULL){
          $uid_formated = array(array('recpt' => $uid, 'method' => 'to'));
          gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $uid_formated);
        }
        
    }else{
        //TODO make it works with other types, not just KANBAN
    }

    //Subject: 'Members Notification'
    $subject = t('Membership notifications report (!date)', array('!date' => format_date(time(), 'custom', 'j-m-Y H:i')), $l);
    $title = t("Your notifications from site_name", array('site_name' => variable_get('site_name')), $l);
    $body = gofast_mail_queue_format_membership_mail($array_notification);
    if($body != NULL){
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

function gofast_mail_queue_format_mail($notifications){
  //Clear notification (double enteries...)
  //Warning : Possible performances drop in cron
  $notifications = json_decode(json_encode($notifications), TRUE);
  foreach($notifications as $key_occur => $occur){
    unset ($notifications[$key_occur]['qid']);
  }
  $notifications = array_intersect_key($notifications, array_unique(array_map('serialize', $notifications)));
  $notifications = json_decode(json_encode($notifications));
  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Format mail');
  //foreach($notifications as $occur){
    global $base_url;
    $item_uid = json_decode(reset($notifications)->uid, TRUE)[0]['recpt'];
    $item_user = user_load($item_uid);
    $events_body = "";
    $user = user_load($item_uid);
    $myformat= system_date_format_locale($user->language, "medium");
    $l = array('langcode' => $user->language, 'context' => 'gofast');
    $digest_content = t("Your latest notifications", array(), $l) . "<span style='float:right;'>" . "<a style='color:darkgrey;text-decoration:none;' href='".$base_url."/subscriptions'>".t('Manage your subscriptions', array(), $l)."</a></span>";
    $digest_title = gofast_user_display_name($user);
    $footer = "";

    //________________________________________SUMMARY AND BODY_______________________________________
    $summary =  "";
    $items_sort = array();
    $count_node = 0;
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
    $first = TRUE;

    //Avoid sendinf empty notification
    if(count($items_sort) == 0){
      return NULL;
    }

    foreach($items_sort as $group => $items){ //Check groups
      if(!$first){$summary .= "<br />";}
      else{$first = FALSE;}
      $summary .= "<strong>".$group."</strong><br />";
      foreach($items as $nid => $item){ //Check nids
        $pass = FALSE;
        $node = node_load($nid);
        $target = "";
        if(isset($node->field_emplacement['und'])){
          foreach($node->field_emplacement['und'] as $space){
            $target .= $space['value']."<br />";
          }
        }
        $title = $node->title;
        $title = "<a style='text-decoration:none; color:#0074A6' href='".$base_url."/node/".$node->nid."'>".$title."</a>";
        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
        $node_icon = gofast_mail_queue_fa_png($node_icon);
        //Variables to increment or set TRUE according to the events:
        $isNew = FALSE;
        $updated = FALSE;
        $edited = 0;
        $commented = 0;
        $edit_commented = 0;
        $pre_updates = array();
        $updates = NULL;
        $updates_body = NULL;
        $updates_summary = NULL;
        $updates_new = NULL;
        $com_updates = NULL;
        $versionning = NULL;
        $version_loop = FALSE;
        $versionning_theme = NULL;
        $versionning_updates = NULL;
        $count_updates = 0;
        $info = null;

        foreach($item as $event){//Checking number of events and setting event field
          $message = json_decode($event->message, TRUE);
          $event_name = $message['event'];
          $timestamp = $event->timestamp;

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
          //________________________________________________

          if(strcmp($event_name['value'], "NCON") == 0){ //New content event
            $isNew  = TRUE;
            $body = NULL;
            $node_target = $base_url."/node/".$nid;
            if($message['summary']['value'] !== "" && $message['summary']['value'] !== NULL){
              $body = $message['summary']['value'];
            }
            if($message['body']['value'] !== "" && $message['body']['value'] !== NULL){
              $body = $message['body']['value'];
            }
            $updates_new .= theme('gofast-notifications-node-new', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user) ,'body' => $body, 'node_link' => $node_target, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));

          }
          else if(strcmp($event_name['value'], "ECON") == 0 || strcmp($event_name['value'], "NDEL") == 0){ //Edited content event
            $edited ++;
            $pass = FALSE; //Check if a change was detected for this event
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
                  $pre_updates[$user->uid][] = array('field' => $message_k, 'from' => $from, 'to' => $to, 'timestamp' => $timestamp);
                  $pre_updates[$user->uid]['user'] = $user;
                }
                if($message_k == 'status' && $from == 1 && $to == 0) {
                    $isDelete = TRUE;
                } else {
                    $isDelete = FALSE;
                }
                $pass = TRUE;
              }
            }
          }
         /* else if(strcmp($event_name['value'], "NCOM") == 0){ //New comment case
            $commented ++;
            $combody = $message['body']['value'];
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-comment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => $message['title']['value'], 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $combody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply' => t("Reply", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          }
          else if(strcmp($event_name['value'], "ECOM") == 0){ //Edited comment case
            $edit_commented ++;
            if(isset($message['title']['to'])){
              $ctitle = $message['title']['to'];
            }
            else{
              $ctitle = $message['title']['value'];
            }

            if(isset($message['body']['to'])){
              $cbody = $message['body']['to'];
            }
            else{
              $cbody = $message['body']['value'];
            }
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-ecomment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => $ctitle, 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $cbody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply' => t("Reply", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          }
          */
          else if(strcmp($event_name['value'], "NREV") == 0){
            $versionning_uid = $user->uid;
            $current_version = $message['version']['to'];
            if($versionning == NULL){ //1st versionning message
              $updated = TRUE;
              $versionning_user = user_load($versionning_uid);
              $versionning = $message['version']['to'];
              if(substr($current_version, -2) == '.0'){ //Major version
                $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                $version_loop = FALSE;
              }
              else{ //Minor version
                  $version_loop = array('from' => $versionning, 'to' => NULL);
              }
            }
            else{ //Others versionning messages
              if(is_array($version_loop)){ //We are in a version loop
                if(user_load($versionning_uid) == $versionning_user){ //User is the same than before
                  if(substr($current_version, -2) == '.0'){ //Major version, we end the loop
                    if($version_loop['to'] != NULL){ //Multiple minor versions pending
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $versionning = $message['version']['to'];
                      $versionning_user = user_load($versionning_uid);
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{ //One minor version pending
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $versionning = $message['version']['to'];
                      $versionning_user = user_load($versionning_uid);
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                  }
                  else{ //Minor version
                    $version_loop['to'] = $message['version']['to'];
                  }
                }
                else{ //User have changed
                  if(is_array($version_loop)){ //We are in a version loop, we end the loop
                    if(substr($current_version, -2) == '.0'){ //Major version
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = array('from' => $versionning, 'to' => $message['version']['to']);
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{//Minor version
                      if($version_loop['to'] != NULL){ //Multiple minor versions pending
                        $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                        $versionning_user = user_load($versionning_uid);
                        $versionning = $message['version']['to'];
                        $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                      }
                      else{ //One minor version pending
                        $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                        $versionning_user = user_load($versionning_uid);
                        $versionning = $message['version']['to'];
                        $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                      }
                    }
                  }
                  else{ //We are not in a version loop
                    if(substr($current_version, -2) == '.0'){ //Major version
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{ //Minor version
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = array('from' => $versionning, 'to' => $message['version']['to']);
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                    }
                  }
                }
              }
              else{ //We are not in a version loop
                if(substr($current_version, -2) == '.0'){ //Major version
                  $versionning = $message['version']['to'];
                  $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                  $version_loop = FALSE;
                }
                else{ //Minor version, we loop
                    $versionning = $message['version']['to'];
                    $versionning_uid = $user->uid;
                    $versionning_user = user_load($versionning_uid);
                    $version_loop = array('from' => $versionning, 'to' => NULL);
                }
              }
            }
            $count_updates++;
          }
          else if ( strcmp($event_name['value'], "NMEM") == 0
                  || strcmp($event_name['value'], "DMEM") == 0 ){
            continue; // Event not included in this notification

          }
          else{ //It's not a standard notification
            $mail = $event->message;
            return $mail;
          }
        }
        foreach($pre_updates as $k_updates => $v_updates){//Pass into all modifications made by a single user to sort them
          $user = user_load($k_updates);
          $modifications = "<table id='edits-metadatas' style='width:100%; border-left: 1px solid #dddddd; border-top: 1px solid #dddddd; border-radius:5px;'><tr>";
          $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Field', array(), $l)."</th>";
          $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Old/Removed', array(), $l)."</th>";
          $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('New/Added', array(), $l)."</th>";
          $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Date', array(), $l)."</th>";
          $modifications .= "</tr>";
          $body_is_edited = FALSE;
          $summary_is_edited = FALSE;
          $meta_is_edited = FALSE;
          foreach($v_updates as $item_updates){
            if(is_array($item_updates)){
              if(isset($item_updates['from']) && isset($item_updates['to'])){ //Edit found
                if($item_updates['field'] == 'body'){
                  $body_is_edited = TRUE;
                  $ebody = $item_updates['to'];
                }
                else if($item_updates['field'] == 'summary'){
                  $summary_is_edited = TRUE;
                  $esummary = $item_updates['to'];
                }
                else if($item_updates['field'] == 'status'){
                  $status = $item_updates['to'];
                  $info .= theme('gofast-notifications-node-info', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']), 'title' => $title, 'status' => $status, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($item_updates['timestamp'], 'custom', $myformat, NULL, $l["langcode"])));
                }
                else{
                  $meta_is_edited = TRUE;
                  $modifications .= "<tr style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; font-size: 0.8em;'>";
                    $modifications .= "<td style='width: 115px; font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>".t(ucfirst($item_updates['field']),array(), $l)."</center></td>";
                    $array_from = explode(',', $item_updates['from']);
                    $array_to = explode(',', $item_updates['to']);
                      if($item_updates['from'] == ""){
                        $modifications .= "<td style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'></td>";
                      }
                      else{
                        $modifications .= "<td style='background-color: rgba(255, 77, 77, 0.25); border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>";
                        foreach($array_from as $item_from){
                          $modifications .= "<span style='font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".t($item_from, array(), $l)."</span><br />";
                        }
                        $modifications .= "</center></td>";
                      }
                      if($item_updates['to'] != ""){
                        $modifications .= "<td style='background-color: rgba(91, 255, 77, 0.25); border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>";
                        foreach($array_to as $item_to){
                          $modifications .= "<span style='font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".t($item_to, array(), $l)."</span><br />";
                        }
                        $modifications .= "</center></td>";
                      }
                      else{
                        $modifications .= "<td style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'></td>";
                      }
                    $modifications .= "";
                    $modifications .= "<td style='width: 115px; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><span style='font-size:0.8em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".format_date($item_updates['timestamp'], 'custom', $myformat, NULL, $l["langcode"])."</span></td>";
                    $modifications .= "</tr>";
                }
                if($body_is_edited){
                    $updates_body = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $ebody, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date( $item_updates['timestamp'], 'custom', $myformat, NULL, $l["langcode"])));
                 
                }
                if($summary_is_edited){
                    $updates_summary = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $esummary, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($item_updates['timestamp'], 'custom', $myformat, NULL, $l["langcode"])));
                 
                }
              }
              /*else{ //Edit not found
                $modifications .= "<span>".t('This content has been edited', array(), $l)."</span>
                <br /><span style='float:right;font-size: 12px;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".format_date($item_updates['timestamp'])."</span><br /><br />";
              }*/
            }
          }
          $modifications .= "</table>";
          if($meta_is_edited){
            $updates .= theme('gofast-notifications-node-event', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']),'modifications' => $modifications, 'is_digest' => FALSE, 'tokens' => NULL, "date" => ""));
          }
        }
        $info = $info.$updates_body.$updates_summary;

        //________________________________________VERSIONNING___________________________________________________
        if($updated){
          if(is_array($version_loop)){ //We end version loop
            if(isset($version_loop['to'])){ //Multiple pendings
            $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
            }
            else{ //One pending
            $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
            }
            if(isset($message['version']['to'])){
              $versionning = $message['version']['to'];
            }
            /*else if(isset($message['version']['value'])){
              $versionning = $message['version']['value'];
            }*/
            $version_loop = FALSE;
          }
          $versionning_theme .= theme('gofast-notifications-node-version', array('l' => $l, 'is_digest' => FALSE, 'tokens' => NULL, 'version' => NULL, 'version' => $versionning, 'version_message' => $versionning_updates, 'count_version' => $count_updates));
        }
        //_______________________________________SUMMARY________________________________________________________
        $summary .= "<div id='sum-item'><span>   <a style='color:blue;text-decoration:none;' href='".$base_url."/node/".$nid."' target='_blank'>&emsp;<span style='float:left;'>".$node_icon."</span>".$title."</a> </span>";
        if($isNew){ //Seting "NEW" message
          $summary .= "<span style='color:red;font-size:8px;'>".t("NEW ", array(), $l)."</span>";
        }
        if($isDelete){ //Seting "DELETE" message
          $summary .= "<span style='color:red;font-size:8px;'>".t("DELETE ", array(), $l)."</span>";
        }
        if($updated){ //Seting "VERSION UPDATE" message
          $summary .= "<span style='color:red;font-size:8px;'>".t("VERSION UPDATE ", array(), $l)."</span>";
        }
        $summary .= "<span style='float:right;color:grey;font-size:10;'>";
        //Here we are setting strings according to the modifications
        if($edited > 0 && $isDelete == FALSE){
          $summary .= "<a style='color:grey;' href='#u-node".$count_node."'>".t("edited nb_editions times.", array('nb_editions' => $edited), $l)."</a> ";
        }
        /* if($commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_comment new comment(s).", array('nb_comment' => $commented), $l)."</a> ";
        }
        if($edit_commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_ecomments edited comment(s).", array('nb_ecomments' => $edit_commented), $l)."</a> ";
        }*/
        $summary .= "</span></div><div style='width:100%; height:1px;'></div>";
        //____________________________________________________BODY_________________________________________________
        $details = "";
        $date = "";
        $node_updates = "";

        if($info || $updates_new){
          $node_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #bce8f1; opacity: 0.9;padding: 2px; text-align: center;">'.t("Info", array(), array('context' => "gofast:mail_queue")).'</p>'.$updates_new.$info;
        }
        /*if($com_updates){
          $node_updates .= "<p style='font-size:18px; background-color: #FFEFDF; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; padding: 2px; text-align: center;'>".t('Comments', array(), $l)."</p>";
          foreach($com_updates as $com_update){
            $node_updates .= $com_update;
          }
        }*/
        if($updates || $updated){
          $node_updates .= '<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;text-align: center;'>".t('Document\'s updates', array(), $l)."</p>".$versionning_theme.$updates;
        }
        /*if($com_updates != NULL){
          $com_updates = "<p style='font-size:18px; background-color: #FFEFDF; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; padding: 2px; text-align: center;'>".t('Comments', array(), $l)."</p>".$com_updates; //Start of comments
        }
        if($updated && $updates){
          $updates = $versionning_theme.'<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd; text-align: center;'>".t('Document\'s editions', array(), $l)."</p>".$updates;
        }
        else if ($updated){
          $updates = $versionning_theme.$updates;
        }
        else if($updates){
         $updates = '<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;text-align: center;'>".t('Document\'s editions', array(), $l)."</p>".$updates;
        }
        if(isset($updates_new) || isset($info)){
          $com_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #5bc0de; opacity: 0.9;padding: 2px; text-align: center;">'.t("Info", array(), array('context' => "gofast:mail_queue")).'</p>'.$info.$updates_new.$com_updates; //Adding New contents
        }*/
        $events_body .= theme('gofast-notifications-node-update', array('l' => $l, 'count_node' => $count_node, 'isNew' => $isNew, 'isRev' => $updated, 'group' => $group, 'node_icon' => $node_icon, 'node_title' => $title, 'com_updates' => NULL, 'updates' => $node_updates, 'spaces' => $target, 'details' => $details, 'date' => $date));
        $count_node ++;
      }
    }
    $summary .= "<br />"; //End of summary

    //_____________________________________________________BUILD THE EMAIL_______________________________________________
    $body = "";//Build the body
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => $digest_title, 'content' => $digest_content)); //Top
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => "", "content" => $summary)); //Summary
    $body .= $events_body; //Events

    $mail = "";//Build the mail structure
    $mail .= theme('gofast-notifications-mailer-body', array('l' => $l, 'content' => $body)); //Include body
  //}
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Format mail. '.$end_timer.' sec was needed.');
  return $mail;
}



/*function gofast_mail_queue_format_kanban_mail($notifications){
  //Clear notification (double enteries...)
  //Warning : Possible performances drop in cron
  $notifications = json_decode(json_encode($notifications), TRUE);
  foreach($notifications as $key_occur => $occur){
    unset ($notifications[$key_occur]['qid']);
  }
  $notifications = array_intersect_key($notifications, array_unique(array_map('serialize', $notifications)));
  $notifications = json_decode(json_encode($notifications));
  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Format mail Kanban');
  //foreach($notifications as $occur){
    global $base_url;
    $item_uid = json_decode(reset($notifications)->uid, TRUE)[0]['recpt'];
    $item_user = user_load($item_uid);
    $events_body = "";
    $user = user_load($item_uid);
    $myformat= system_date_format_locale($user->language, "medium");
    $l = array('langcode' => $user->language, 'context' => 'gofast');
    $digest_content = t("Your latest notifications", array(), $l) . "<span style='float:right;'>" . "<a style='color:darkgrey;text-decoration:none;' href='".$base_url."/subscriptions'>".t('Manage your subscriptions', array(), $l)."</a></span>";
    $digest_title = gofast_user_display_name($user);
    $footer = "";

    //________________________________________SUMMARY AND BODY_______________________________________
    $summary =  "";
    $items_sort = array();
    $count_node = 0;
    foreach($notifications as $item){ //Sort notifications for a user by node id
      $message = json_decode($item->message, TRUE);
      $nid = $message['nid']['value'];
      $node = node_load($nid);//Load node item at it's actual state
      if(isset($node->og_group_content_ref['und'])){
        $match = FALSE;
        foreach($node->og_group_content_ref['und'] as $k_group => $v_group){
          $group_node = node_load($v_group['target_id']);
          if(node_access('view', $group_node, $item_user) && $match == FALSE){
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
    $first = TRUE;

    //Avoid sendinf empty notification
    if(count($items_sort) == 0){
      return NULL;
    }

    foreach($items_sort as $group => $items){ //Check groups
      if(!$first){$summary .= "<br />";}
      else{$first = FALSE;}
      $summary .= "<strong>".$group."</strong><br />";
      foreach($items as $nid => $item){ //Check nids
        $pass = FALSE;
        $node = node_load($nid);
        $target = "";
        if(isset($node->field_emplacement['und'])){
          foreach($node->field_emplacement['und'] as $space){
            $target .= $space['value']."<br />";
          }
        }
        $title = $node->title;
        $title = "<a style='text-decoration:none; color:#0074A6' href='".$base_url."/node/".$node->nid."'>".$title."</a>";
        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
        $node_icon = gofast_mail_queue_fa_png($node_icon);
        //Variables to increment or set TRUE according to the events:
        $isNew = FALSE;
        $updated = FALSE;
        $edited = 0;
        $commented = 0;
        $edit_commented = 0;
        $pre_updates = array();
        $updates = NULL;
        $updates_body = NULL;
        $updates_summary = NULL;
        $updates_new = NULL;
        $com_updates = NULL;
        $versionning = NULL;
        $version_loop = FALSE;
        $versionning_theme = NULL;
        $versionning_updates = NULL;
        $count_updates = 0;
        $info = null;

        foreach($item as $event){//Checking number of events and setting event field
          $message = json_decode($event->message, TRUE);
          $event_name = $message['event'];
          $timestamp = $event->timestamp;

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
          //________________________________________________

          if(strcmp($event_name['value'], "NCON") == 0){ //New content event
            $isNew  = TRUE;
            $body = NULL;
            $node_target = $base_url."/node/".$nid;
            if($message['summary']['value'] !== "" && $message['summary']['value'] !== NULL){
              $body = $message['summary']['value'];
            }
            if($message['body']['value'] !== "" && $message['body']['value'] !== NULL){
              $body = $message['body']['value'];
            }
            $updates_new .= theme('gofast-notifications-node-new', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user) ,'body' => $body, 'node_link' => $node_target, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));

          }
          else if(strcmp($event_name['value'], "ECON") == 0 || strcmp($event_name['value'], "NDEL") == 0 || strcmp($event_name['value'], "ETDL") == 0){ //Edited content event
            $edited ++;
            $pass = FALSE; //Check if a change was detected for this event
            foreach($message as $message_k => $message_item){
              if(count($message_item) == 2 && $message_k != "changed" && $message_k != "ruid"){ //Format for each event
                $isTaxoTerm = $message_k == "criticity" || $message_k == "state" || $message_k == "criticity" || $message_k == "category" || $message_k == "tags" || $message_k == "task_column";
                $isNodeRef = $message_k == "targets" || $message_k == "groups";
                $isUserTerm = $message_k == "members" || $message_k == "person_in_charge" || strpos($message_k, "assignee") !== false;
                $isDateTerm = strpos($message_k, "deadline") !== false;
                $isTDLStatusTerm = strpos($message_k, "status") !== false;
                if($isTaxoTerm){ //Translating ids in name
                  $from = gofast_message_ext_api_get_term($message_item['from']);
                  $to = gofast_message_ext_api_get_term($message_item['to']);
                }
                else if($isNodeRef){
                  $from = gofast_message_ext_api_get_node_name($message_item['from']);
                  $to = gofast_message_ext_api_get_node_name($message_item['to']);
                }else if($isUserTerm){
                  if(isset($message_item['from']) && $message_item['from']!== null){
                    $from = gofast_message_ext_api_get_user_name($message_item['from']);
                  }else{
                    $from ="";
                  }
                  if(isset($message_item['to']) && $message_item['to']!== null){
                    $to = gofast_message_ext_api_get_user_name($message_item['to']);
                  }else{
                    $to = "";
                  }
                }else if($isDateTerm){
                  $from = format_date($message_item['from'], 'custom', $myformat, NULL, $l["langcode"]);
                  $to = format_date($message_item['to'], 'custom', $myformat, NULL, $l["langcode"]);
                }else if($isTDLStatusTerm){
                  if($message_item['from'] == 0){
                     $from_themed_status = t("Todo", array(), $l);
                  }else{
                     $from_themed_status = t("Done", array(), $l);
                  }
                  if($message_item['to'] == 0){
                     $to_themed_status = t("Todo", array(), $l);
                  }else{
                     $to_themed_status = t("Done", array(), $l);
                  }
                  $from =  $from_themed_status;
                  $to = $to_themed_status;
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
                  $pre_updates[$user->uid][] = array('field' => $message_k, 'from' => $from, 'to' => $to, 'timestamp' => $timestamp);
                  $pre_updates[$user->uid]['user'] = $user;
                }
                $pass = TRUE;
              }else if($message_k == "ruid"){
                $pre_updates[$user->uid]['user_ruid'] = user_load($message_item['value']);
              }
            }
          }
          else if(strcmp($event_name['value'], "NCOM") == 0){ //New comment case
            $commented ++;
            $combody = '<pre class="gf-kanban-comment">'.$message['body']['value'].'</pre>';
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-comment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => '', 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $combody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply_size' => "100",'comment_reply' => t("View task", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          }
          else if(strcmp($event_name['value'], "ECOM") == 0){ //Edited comment case
            $edit_commented ++;
            if(isset($message['title']['to'])){
              $ctitle = $message['title']['to'];
            }
            else{
              $ctitle = $message['title']['value'];
            }

            if(isset($message['body']['to'])){
              $cbody =  '<pre class="gf-kanban-comment">'.$message['body']['to'].'</pre>';
            }
            else{
              $cbody = '<pre class="gf-kanban-comment">'.$message['body']['value'].'</pre>';
            }
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-ecomment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => $ctitle, 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $cbody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply_size' => "100", 'comment_reply' => t("View task", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          } 
          
          else if(strcmp($event_name['value'], "NREV") == 0){
            $versionning_uid = $user->uid;
            $current_version = $message['version']['to'];
            if($versionning == NULL){ //1st versionning message
              $updated = TRUE;
              $versionning_user = user_load($versionning_uid);
              $versionning = $message['version']['to'];
              if(substr($current_version, -2) == '.0'){ //Major version
                $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                $version_loop = FALSE;
              }
              else{ //Minor version
                  $version_loop = array('from' => $versionning, 'to' => NULL);
              }
            }
            else{ //Others versionning messages
              if(is_array($version_loop)){ //We are in a version loop
                if(user_load($versionning_uid) == $versionning_user){ //User is the same than before
                  if(substr($current_version, -2) == '.0'){ //Major version, we end the loop
                    if($version_loop['to'] != NULL){ //Multiple minor versions pending
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $versionning = $message['version']['to'];
                      $versionning_user = user_load($versionning_uid);
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{ //One minor version pending
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $versionning = $message['version']['to'];
                      $versionning_user = user_load($versionning_uid);
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                  }
                  else{ //Minor version
                    $version_loop['to'] = $message['version']['to'];
                  }
                }
                else{ //User have changed
                  if(is_array($version_loop)){ //We are in a version loop, we end the loop
                    if(substr($current_version, -2) == '.0'){ //Major version
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = array('from' => $versionning, 'to' => $message['version']['to']);
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{//Minor version
                      if($version_loop['to'] != NULL){ //Multiple minor versions pending
                        $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                        $versionning_user = user_load($versionning_uid);
                        $versionning = $message['version']['to'];
                        $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                      }
                      else{ //One minor version pending
                        $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $versionning_user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                        $versionning_user = user_load($versionning_uid);
                        $versionning = $message['version']['to'];
                        $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                      }
                    }
                  }
                  else{ //We are not in a version loop
                    if(substr($current_version, -2) == '.0'){ //Major version
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = FALSE;
                    }
                    else{ //Minor version
                      $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($versionning_user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                      $version_loop = array('from' => $versionning, 'to' => $message['version']['to']);
                      $versionning_user = user_load($versionning_uid);
                      $versionning = $message['version']['to'];
                      $version_loop = array('from' => $message['version']['to'], 'to' => NULL);
                    }
                  }
                }
              }
              else{ //We are not in a version loop
                if(substr($current_version, -2) == '.0'){ //Major version
                  $versionning = $message['version']['to'];
                  $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;<span style='color:red;'>".t('Major version', array(), $l)."</span> ".$versionning."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
                  $version_loop = FALSE;
                }
                else{ //Minor version, we loop
                    $versionning = $message['version']['to'];
                    $versionning_uid = $user->uid;
                    $versionning_user = user_load($versionning_uid);
                    $version_loop = array('from' => $versionning, 'to' => NULL);
                }
              }
            }
            $count_updates++;
          }
          else if ( strcmp($event_name['value'], "NMEM") == 0
                  || strcmp($event_name['value'], "DMEM") == 0 ){
            continue; // Event not included in this notification

          }
          else{ //It's not a standard notification
            $mail = $event->message;
            return $mail;
          }
        }
        variable_set("debugentitynotif", $pre_updates);
        foreach($pre_updates as $k_updates => $v_updates){//Pass into all modifications made by a single user to sort them
          $user = user_load($k_updates);
          $l["context"] = "gofast:gofast_kanban";
          $modifications = "";
          $array_modifications_tdl = array();

          $l["context"] = "gofast";
          $body_is_edited = FALSE;
          $summary_is_edited = FALSE;
          $meta_is_edited = FALSE;
          $todolist_is_edited = FALSE;
          foreach($v_updates as $item_updates){
            if(is_array($item_updates)){
              if(isset($item_updates['from']) && isset($item_updates['to'])){ //Edit found
                if($item_updates['field'] == 'body'){
                  $body_is_edited = TRUE;
                  $ebody = $item_updates['to'];
                }
                else if($item_updates['field'] == 'summary'){
                  $summary_is_edited = TRUE;
                  $esummary = $item_updates['to'];
                }
                else if($item_updates['field'] == 'status'){
                  $status = $item_updates['to'];
                  $info .= theme('gofast-notifications-node-info', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']), 'title' => $title, 'status' => $status, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
                }elseif($item_updates['field'] == 'task_columntodo?'){
                    $todolist_is_edited = TRUE;
                }
                else{
                  //get more readable fields names
                  $is_todolist_field = gofast_kanban_is_todolist_field($item_updates['field']);
                  $readable_name = gofast_kanban_get_readable_name_specific_fields($item_updates['field']);

                    $temp_modification = "<tr style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; font-size: 0.8em;'>";
                    $temp_modification .= "<td style='width: 115px; font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>".t(ucfirst($readable_name),array(), $l)."</center></td>";
                    $array_from = explode(',', $item_updates['from']);
                    $array_to = explode(',', $item_updates['to']);
                      if($item_updates['from'] == ""){
                        $temp_modification .= "<td style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'></td>";
                      }
                      else{
                        $temp_modification .= "<td style='background-color: rgba(255, 77, 77, 0.25); border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>";
                        foreach($array_from as $item_from){
                          $temp_modification .= "<span style='font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".t($item_from, array(), $l)."</span><br />";
                        }
                        $temp_modification .= "</center></td>";
                      }
                      if($item_updates['to'] != ""){
                        $temp_modification .= "<td style='background-color: rgba(91, 255, 77, 0.25); border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><center>";
                        foreach($array_to as $item_to){
                          $temp_modification .= "<span style='font-size:1em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".t($item_to, array(), $l)."</span><br />";
                        }
                        $temp_modification .= "</center></td>";
                      }
                      else{
                        $temp_modification .= "<td style='border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'></td>";
                      }
                    $temp_modification .= "";
                    $temp_modification .= "<td style='width: 115px; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd;'><span style='font-size:0.8em;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></td>";
                    $temp_modification .= "</tr>";

                    //we are in a todolist item, so store the theme into another variable
                  if($is_todolist_field){
                      //build an array containing themed modifications foreach todolist item (ciid)
                      $ciid = explode("_", $item_updates['field'])[1];
                      $tdl_label = explode("_", $item_updates['field'])[2];
                      //specific case for global progression
                      if($ciid == "Global Progression"){
                        $array_modifications_tdl[$ciid."_".$tdl_label][0] = $item_updates['to'];
                      }else{
                        $array_modifications_tdl[$ciid."_".$tdl_label][] = $temp_modification;
                      }
                      $meta_is_edited = TRUE;
                  }else{
                      if($modifications == ""){
                            $l["context"] = "gofast:gofast_kanban";
                            $modifications = "<table id='edits-metadatas' style='width:100%; border-left: 1px solid #dddddd; border-top: 1px solid #dddddd; border-radius:5px;'><tr>";
                            $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Field', array(), $l)."</th>";
                            $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Remove', array(), $l)."</th>";
                            $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Added', array(), $l)."</th>";
                            $modifications .= "<th style='border-right: 1px solid #dddddd; border-bottom: 1px solid #bbbbbb; border-bottom: 1px solid #dddddd; color: #444444;'>".t('Date', array(), $l)."</th>";
                            $modifications .= "</tr>";
                            $l["context"] = "gofast";
                      }
                       $modifications .= $temp_modification;
                       $meta_is_edited = TRUE;
                  }

                }
                if($body_is_edited){
                  if(isset($updates_body_timestamp) && $updates_body_timestamp < $item_updates['timestamp']){
                    $updates_body_timestamp = $item_updates['timestamp'];
                    $updates_body = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $ebody, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
                  }
                  else{
                    $updates_body_timestamp = $item_updates['timestamp'];
                    $updates_body = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $ebody, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
                  }
                }
                if($summary_is_edited){
                  if(isset($updates_summary_timestamp) && $updates_summary_timestamp < $item_updates['timestamp']){
                    $updates_summary_timestamp = $item_updates['timestamp'];
                    $updates_summary = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $esummary, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
                  }
                  else{
                    $updates_summary_timestamp = $item_updates['timestamp'];
                    $updates_summary = theme('gofast-notifications-node-edited', array('l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user']) ,'body' => $esummary, 'title' => $title, 'is_digest' => FALSE, 'tokens' => NULL, "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
                  }
                }
              }
              /*else{ //Edit not found
                $modifications .= "<span>".t('This content has been edited', array(), $l)."</span>
                <br /><span style='float:right;font-size: 12px;font-family:Helvetica Neue,Helvetica,Arial,sans-serif;color:#666666;'>".format_date($item_updates['timestamp'])."</span><br /><br />";
              }*/
        /*    }
          }
          $modifications .= "</table>";

          if($meta_is_edited){
            $updates .= theme('gofast-notifications-node-kanban-event', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $v_updates['user'])), 'author_name' => gofast_user_display_name($v_updates['user_ruid']),'modifications' => $modifications, 'modifications_todolist' => $array_modifications_tdl , 'is_digest' => FALSE, 'tokens' => NULL, "date" => ""));
          }

        }
        $info = $info.$updates_body.$updates_summary;

        //________________________________________VERSIONNING___________________________________________________
        if($updated){
          if(is_array($version_loop)){ //We end version loop
            if(isset($version_loop['to'])){ //Multiple pendings
            $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".t('from', array(), $l)." ".$version_loop['from']." ".t('to', array(), $l)." ".$version_loop['to']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
            }
            else{ //One pending
            $versionning_updates .= "<div style='float:left; margin-top: 5px;'>".theme('user_picture', array('account' => $user, 'dimensions' => array('width' => '30px', 'height' => '30px')))."</div>&emsp;".t('Minor version', array(), $l)." ".$version_loop['from']."<br /><span style='color: grey; font-size:11px;'>&emsp;&emsp;".t("Updated by", array(), $l)." ".gofast_user_display_name($user)." . ".  format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])."</span></span><br /><br />";
            }
            if(isset($message['version']['to'])){
              $versionning = $message['version']['to'];
            }
            /*else if(isset($message['version']['value'])){
              $versionning = $message['version']['value'];
            }*/
          /*  $version_loop = FALSE;
          }
          $versionning_theme .= theme('gofast-notifications-node-version', array('l' => $l, 'is_digest' => FALSE, 'tokens' => NULL, 'version' => NULL, 'version' => $versionning, 'version_message' => $versionning_updates, 'count_version' => $count_updates));
        }
        //_______________________________________SUMMARY________________________________________________________
        $summary .= "<div id='sum-item'><span>   <a style='color:blue;text-decoration:none;' href='".$base_url."/node/".$nid."' target='_blank'>&emsp;<span style='float:left;'>".$node_icon."</span>".$title."</a> </span>";
        if($isNew){ //Seting "NEW" message
          $summary .= "<span style='color:red;font-size:8px;'>".t("NEW ", array(), $l)."</span>";
        }
        if($updated){ //Seting "VERSION UPDATE" message
          $summary .= "<span style='color:red;font-size:8px;'>".t("VERSION UPDATE ", array(), $l)."</span>";
        }
        $summary .= "<span style='float:right;color:grey;font-size:10;'>";
        //Here we are setting strings according to the modifications
        if($edited > 0){
          $summary .= "<a style='color:grey;' href='#u-node".$count_node."'>".t("edited nb_editions times.", array('nb_editions' => $edited), $l)."</a> ";
        }
         if($commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_comment new comment(s).", array('nb_comment' => $commented), $l)."</a> ";
        }
        if($edit_commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_ecomments edited comment(s).", array('nb_ecomments' => $edit_commented), $l)."</a> ";
        } 
        $summary .= "</span></div><div style='width:100%; height:1px;'></div>";
        //____________________________________________________BODY_________________________________________________
        $details = "";
        $date = "";
        $node_updates = "";

        if($info || $updates_new){
          $node_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #bce8f1; opacity: 0.9;padding: 2px; text-align: center;">'.t("Info", array(), array('context' => "gofast:mail_queue")).'</p>'.$updates_new.$info;
        }
        if($com_updates){
          $node_updates .= "<p style='font-size:18px; background-color: #FFEFDF; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; padding: 2px; text-align: center;'>".t('Comments', array(), $l)."</p>";
          foreach($com_updates as $com_update){
            $node_updates .= $com_update;
          }
        } 
        if($updates || $updated){
          $node_updates .= '<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;text-align: center;'>".t('Kanban\'s updates', array(), $l)."</p>".$versionning_theme.$updates;
        }
        if($updates_kanban){
          $node_updates .= '<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;text-align: center;'>".t('Todolist\'s updates', array(), $l)."</p>".$versionning_theme.$updates_kanban;
        }
        if($com_updates != NULL){
          $com_updates = "<p style='font-size:18px; background-color: #FFEFDF; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; padding: 2px; text-align: center;'>".t('Comments', array(), $l)."</p>".$com_updates; //Start of comments
        }
        if($updated && $updates){
          $updates = $versionning_theme.'<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd; text-align: center;'>".t('Document\'s editions', array(), $l)."</p>".$updates;
        }
        else if ($updated){
          $updates = $versionning_theme.$updates;
        }
        else if($updates){
         $updates = '<a href="#top" style="font-size: 10px; font-weight: bold; text-decoration: none;color:blue; float: right;">TOP</a><div style="width: 100%; height:15px;"></div>'."<p style='font-size:18px; background-color: #DEFFCF; padding: 2px;border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;text-align: center;'>".t('Document\'s editions', array(), $l)."</p>".$updates;
        }
        if(isset($updates_new) || isset($info)){
          $com_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #5bc0de; opacity: 0.9;padding: 2px; text-align: center;">'.t("Info", array(), array('context' => "gofast:mail_queue")).'</p>'.$info.$updates_new.$com_updates; //Adding New contents
        }
        $events_body .= theme('gofast-notifications-node-update', array('l' => $l, 'count_node' => $count_node, 'isNew' => $isNew, 'isRev' => $updated, 'group' => $group, 'node_icon' => $node_icon, 'node_title' => $title, 'com_updates' => NULL, 'updates' => $node_updates, 'spaces' => $target, 'details' => $details, 'date' => $date));
        $count_node ++;
      }
    }
    $summary .= "<br />"; //End of summary

    //_____________________________________________________BUILD THE EMAIL_______________________________________________
    $body = "";//Build the body
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => $digest_title, 'content' => $digest_content)); //Top
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => "", "content" => $summary)); //Summary
    $body .= $events_body; //Events

    $mail = "";//Build the mail structure
    $mail .= theme('gofast-notifications-mailer-body', array('l' => $l, 'content' => $body)); //Include body
  //}
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Format mail KANBAN. '.$end_timer.' sec was needed.');
  return $mail;
}*/

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
 * @return type
 */
function gofast_mail_queue_sort_notifications($notifications, $item_user, $event_filters = array() ) {

  $timer_start = time(true);
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

  $timer_start = time(true);
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
 * Build notification mail for space administrator (membership activity)
 * @param array() $notifications
 * @return type
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
  $digest_content = t("Your latest space administrator notifications (membership)", array(), $l) . "<span style='float:right;'>" . "<a style='color:darkgrey;text-decoration:none;' href='" . $base_url . "/subscriptions'>" . t('Manage your subscriptions', array(), $l) . "</a></span>";
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
      $title = $node->title;
      $title = "<a style='text-decoration:none; color:#0074A6' href='" . $base_url . "/node/" . $node->nid . "'>" . $title . "</a>";
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
          $user_pict = theme('user_picture', array('account' => $user_added));
          $user_name = gofast_user_display_name($user_added);
        }else{
          $userlist_added = entity_load_single('userlist', $message['new_member_id']['value']);
          $user_pict = theme('gofast_userlist_picture', array('member' => $userlist_added));
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
                      "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])
                    ));

      }
      $info = $info . $updates . $updates_summary;

      //_______________________________________SUMMARY________________________________________________________
      $summary .= "<div id='sum-item'><span>   <a style='color:blue;text-decoration:none;' href='" . $base_url . "/node/" . $nid . "' target='_blank'>&emsp;<span style='float:left;'>" . $node_icon . "</span>" . $title . "</a> </span>";
      if ($isNew) { //Seting "NEW" message
        $summary .= "<span style='color:green;font-size:8px;'>" . t("NEW MEMBERS (%nb) ", array('%nb' => $count_new_membership), $l) . "</span>";
      }
      if ($isDeleted) { //Seting "VERSION UPDATE" message
        $summary .= "<span style='color:red;font-size:8px;'>" . t("REMOVED MEMBERS (%nb)", array('%nb' => $count_removed_membership), $l) . "</span>";
      }
      $summary .= "</span></div><div style='width:100%; height:1px;'></div>";

      $node_updates = '<p style="font-size:18px; border-right: 1px solid #dddddd;border-bottom: 1px solid #dddddd;background-color: #bce8f1; opacity: 0.9;padding: 2px; text-align: center;">' . t("Info", array(), array('context' => "gofast:mail_queue")) . '</p>' . $info;

      $events_body .= theme('gofast-notifications-node-update', array('l' => $l, 'count_node' => $count_node, 'isNew' => $isNew, 'isRev' => $updated, 'group' => $group, 'node_icon' => $node_icon, 'node_title' => $title, 'com_updates' => NULL, 'updates' => $node_updates, 'spaces' => $target, 'details' => $details, 'date' => $date));
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

/**
 * Build mail body for comments notfication
 * @global type $base_url
 * @param type $notifications
 * @return type $mail body
 * 
 */
function gofast_mail_queue_format_mail_comment($notifications){
  //Clear notification (double enteries...)
  //Warning : Possible performances drop in cron
  $notifications = json_decode(json_encode($notifications), TRUE);
  foreach($notifications as $key_occur => $occur){
    unset ($notifications[$key_occur]['qid']);
  }
  $notifications = array_intersect_key($notifications, array_unique(array_map('serialize', $notifications)));
  $notifications = json_decode(json_encode($notifications));
  $start_timer = time();
  watchdog('gofast_mail_queue', 'START: Format mail');
  //foreach($notifications as $occur){
    global $base_url;
    $item_uid = json_decode(reset($notifications)->uid, TRUE)[0]['recpt'];
    $item_user = user_load($item_uid);
    $events_body = "";
    $user = user_load($item_uid);
    $myformat= system_date_format_locale($user->language, "medium");
    $l = array('langcode' => $user->language, 'context' => 'gofast');
    $digest_content = t("Your latest notifications of comments", array(), $l) . "<span style='float:right;'>" . "<a style='color:darkgrey;text-decoration:none;' href='".$base_url."/subscriptions'>".t('Manage your subscriptions', array(), $l)."</a></span>";
    $digest_title = gofast_user_display_name($user);
    $footer = "";

    //________________________________________SUMMARY AND BODY_______________________________________
    $summary =  "";
    $items_sort = array();
    $count_node = 0;
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
    $first = TRUE;

    //Avoid sendinf empty notification
    if(count($items_sort) == 0){
      return NULL;
    }

    foreach($items_sort as $group => $items){ //Check groups
      if(!$first){$summary .= "<br />";}
      else{$first = FALSE;}
      $summary .= "<strong>".$group."</strong><br />";
      foreach($items as $nid => $item){ //Check nids
        $pass = FALSE;
        $node = node_load($nid);
        $target = "";
        if(isset($node->field_emplacement['und'])){
          foreach($node->field_emplacement['und'] as $space){
            $target .= $space['value']."<br />";
          }
        }
        $title = $node->title;
        $title = "<a style='text-decoration:none; color:#0074A6' href='".$base_url."/node/".$node->nid."'>".$title."</a>";
        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
        $node_icon = gofast_mail_queue_fa_png($node_icon);
       
        //Variables to increment or set TRUE according to the events:
        $isNew = FALSE;
        $updated = FALSE;
        $commented = 0;
        $edit_commented = 0;
        $com_updates = NULL;      

        foreach($item as $event){//Checking number of events and setting event field
          $message = json_decode($event->message, TRUE);
          $event_name = $message['event'];
          $timestamp = $event->timestamp;

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
          //________________________________________________

          if(strcmp($event_name['value'], "NCOM") == 0){ //New comment case
            $commented ++;
            $combody = $message['body']['value'];
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-comment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => $message['title']['value'], 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $combody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply' => t("Reply", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          }
          else if(strcmp($event_name['value'], "ECOM") == 0){ //Edited comment case
            $edit_commented ++;
            if(isset($message['title']['to'])){
              $ctitle = $message['title']['to'];
            }
            else{
              $ctitle = $message['title']['value'];
            }

            if(isset($message['body']['to'])){
              $cbody = $message['body']['to'];
            }
            else{
              $cbody = $message['body']['value'];
            }
            $com_updates[$message['cid']['value']] = theme('gofast-notifications-node-ecomment', array('node_title' => $title, 'l' => $l, 'author_pic' => theme('user_picture', array('account' => $user)), 'author_name' => gofast_user_display_name($user),'comment_title' => $ctitle, 'cid' => $message['cid']['value'], 'nid' => $message['nid']['value'], 'comment_body' => $cbody, 'is_digest' => FALSE, 'tokens' => NULL, 'comment_reply' => t("Reply", array(), $l), "date" => format_date($timestamp, 'custom', $myformat, NULL, $l["langcode"])));
          }
        /* else{ //It's not a standard notification
            $mail = $event->message;
            return $mail;
          }*/
        }
        
        //_______________________________________SUMMARY________________________________________________________
        $summary .= "<div id='sum-item'><span>   <a style='color:blue;text-decoration:none;' href='".$base_url."/node/".$nid."' target='_blank'>&emsp;<span style='float:left;'>".$node_icon."</span>".$title."</a> </span>";
        
        if($commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_comment new comment(s).", array('nb_comment' => $commented), $l)."</a> ";
        }
        if($edit_commented > 0){
          $summary .= "<a style='color:grey;' href='#c-node".$count_node."'>".t("nb_ecomments edited comment(s).", array('nb_ecomments' => $edit_commented), $l)."</a> ";
        }
        $summary .= "</span></div><div style='width:100%; height:1px;'></div>";
        //____________________________________________________BODY_________________________________________________
        $details = "";
        $date = "";
        $node_updates = "";
        $node_updates .= "<p style='font-size:18px; background-color: #FFEFDF; border-right: 1px solid #dddddd; border-bottom: 1px solid #dddddd; padding: 2px; text-align: center;'>".t('Comments detail', array(), $l)."</p>";

        if($com_updates){
          foreach($com_updates as $com_update){
            $node_updates .= $com_update;
          }
        }
       
        $events_body .= theme('gofast-notifications-node-update', array('l' => $l, 'count_node' => $count_node, 'isNew' => $isNew, 'isRev' => $updated, 'group' => $group, 'node_icon' => $node_icon, 'node_title' => $title, 'com_updates' => NULL, 'updates' => $node_updates, 'spaces' => $target, 'details' => $details, 'date' => $date));
        $count_node ++;
      }
    }
    $summary .= "<br />"; //End of summary

    //_____________________________________________________BUILD THE EMAIL_______________________________________________
    $body = "";//Build the body
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => $digest_title, 'content' => $digest_content)); //Top
    $body .= theme('gofast-notifications-mailer-digest', array('l' => $l, 'title' => "", "content" => $summary)); //Summary
    $body .= $events_body; //Events

    $mail = "";//Build the mail structure
    $mail .= theme('gofast-notifications-mailer-body', array('l' => $l, 'content' => $body)); //Include body
  //}
  $end_timer = time()-$start_timer;
  watchdog('gofast_mail_queue', 'END: Format mail. '.$end_timer.' sec was needed.');
  return $mail;

}
/*
 * Turn font awsome icons into png icons (stored in the img folder of the module)
 */
function gofast_mail_queue_fa_png($input, $little = false){
  if($little){
    $size = "class='little'";
  }
  $matcher = array(
    'fa-file-word-o' => 'word.png',
    'fa-file-o file-other' => 'other.png',
    'fa-file-powerpoint-o' => 'powerpoint.png',
    'fa-home' => 'home.png',
    'fa-globe' => 'globe.png',
    'fa-file-text-o' => 'text.png',
    'fa-comments-o' => 'comments.png',
    'fa-file-code-o' => 'code.png',
    'fa-file-image-o' => 'image.png',
    'fa-sitemap' => 'sitemap.png',
    'fa-newspaper' => 'newspaper.png',
    'fa-file-pdf-o pdf-image' => 'pdf-image.png',
    'fa-file-pdf-o' => 'pdf.png',
    'fa-share-alt' => 'share.png',
    'fa-file-excel-o' => 'excel.png',
    'fa-users' => 'users.png',
    'fa-video-camera' => 'conference.png',
    'fa-file-sound-o' => 'audio.png',
    'fa-list-alt file-webform' => 'webform.png',
    'fa-file-o file-visio' => 'visio.png',
    'fa-file-video-o' => 'video.png',
    'fa-file-image-o image-svg' => 'svg.png',
    'fa-id-card-o' => 'profile.png',
    'fa-file-text-o file-odg' => 'odg.png',
    'fa-envelope-o' => 'mail.png',
    'fa-file-o file-cao' => 'cao.png',
    'fa-file-archive-o' => 'archive.png',
    'fa-trello' => "trello.png"
  );
  foreach($matcher as $fa => $png){
    if(strpos($input, $fa)){
      $output = str_replace('<img', '<img ' . $size . " ",theme('gofast-notifications-node-icon', array('icon' => $png)));
      return $output;
    }
  }
  $output = str_replace('<img', '<img ' . $size . " ", theme('gofast-notifications-node-icon', array('icon' => 'other.png')));
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
 *  An array of matched notifications formated as:
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
    'template' => '/tpl/gofast-notifications-mailer-header'
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
  $theme['gofast-notifications-node-comment'] = array(
    'template' => 'tpl/gofast-notifications-node-comment'
  );
  $theme['gofast-notifications-node-update'] = array(
    'template' => 'tpl/gofast-notifications-node-update'
  );
  $theme['gofast-notifications-node-event'] = array(
    'template' => 'tpl/gofast-notifications-node-event'
  );
  $theme['gofast-notifications-node-version'] = array(
    'template' => 'tpl/gofast-notifications-node-version'
  );
  $theme['gofast-notifications-node-ecomment'] = array(
    'template' => 'tpl/gofast-notifications-node-ecomment'
  );
  $theme['gofast-notifications-node-new'] = array(
    'template' => 'tpl/gofast-notifications-node-new'
  );
  $theme['gofast-notifications-node-edited'] = array(
    'template' => 'tpl/gofast-notifications-node-edited'
  );
  $theme['gofast-notifications-node-footer'] = array(
    'template' => 'tpl/gofast-notifications-node-footer'
  );
  $theme['gofast-notifications-node-deadline'] = array(
     'template' => 'tpl/gofast-notifications-node-deadline'
   );
  $theme['gofast-notifications-node-icon'] = array(
     'template' => 'tpl/gofast-notifications-node-icon'
   );
  $theme['gofast-notifications-node-info'] = array(
     'template' => 'tpl/gofast-notifications-node-info'
   );
  $theme['gofast-notifications-node-new-member'] = array(
     'template' => 'tpl/gofast-notifications-node-new-member'
   );
  $theme['gofast-notifications-node-remove-member'] = array(
     'template' => 'tpl/gofast-notifications-node-remove-member'
   );


  return $theme;
}
