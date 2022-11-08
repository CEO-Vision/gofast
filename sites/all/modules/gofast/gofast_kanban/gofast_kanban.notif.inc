<?php

function gofast_kanban_get_node_types() {
  return array("kanban", "task", "checklist");
}

function gofast_kanban_get_node_specific_fields($type) {
  $fields = array();
  if ($type == 'task') {
    $fields = array("field_person_in_charge", "field_members", "field_labels", "field_start_date", "field_finish_date", "field_column_index", "field_task_column");
  }
  return $fields;
}

function gofast_kanban_get_readable_name_specific_fields($field_name, $include_tdl_item_name = false) {
  watchdog("debug kanban readable name", $field_name);
  $field_association = array("person_in_charge" => "Responsible",
      "members" => "assignees",
      "labels" => "labels",
      "start_date" => "Start date",
      "finish_date" => "Finish date",
      "column_index" => "Column index",
      "task_column" => "Column");
  if (isset($field_association[$field_name])) {
    return $field_association[$field_name];
  } else {
    //looking for fields starting by todolist_
    if (strpos($field_name, "todolist_") == 0) {
      $tdl_label = explode("_", $field_name)[3];
      if ($include_tdl_item_name == true) {
        $tdl_label = explode("_", $field_name)[2] . " " . $tdl_label;
      }
      return $tdl_label;
      //return str_replace("todolist_", "", $field_name);
    } else {
      return $field_name;
    }
  }
}

/**
 * 
 * @param type $field_name
 * @return boolean
 */
function gofast_kanban_is_todolist_field($field_name) {
  if (strpos($field_name, "todolist_") === 0) {
    return true;
  } else {
    return false;
  }
}

function gofast_kanban_task_deadline_notify(){
   global $base_url;
   $tomorrow = new DateTime('tomorrow');
   $tomorrow_str = $tomorrow->format('Y-m-d');
   
   
   //First, get all task with global deadline set to tomorrow
   $query = new EntityFieldQuery();
   $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', array('task'), 'IN')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_date', 'value', $tomorrow_str.'%', 'like'); 
   $result = $query->execute();
   
   if (isset($result['node'])) {
      $nids = array_keys($result['node']);
      $nodes = node_load_multiple($nids);

      foreach ($nodes as $node) {   
        //Send mail to responsible
        $responsible = $node->field_person_in_charge[LANGUAGE_NONE][0]["target_id"];
        $userName = gofast_user_display_name(user_load($responsible));
         
        $RecipUser = user_load($responsible);
        $l = array('langcode' =>  $RecipUser->language, 'context' => 'gofast_kanban');

        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node , 'link' => FALSE)));
        $document_pic = gofast_mail_queue_fa_png($node_icon);
        $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
        $subject = t('Task: Deadline reached for "!title"', array('!title'=>$node->title), $l); 
        $title = t('Deadline task notification' ,array(), $l);
        $footer = t('Message sent from ', array(), $l)." ".variable_get('site_name');
        $node_link = $base_url . '/node/' . $node->nid;
        $description = t('A card on wich you are responsible reaches deadline tomorrow :', array(), $l);
        $description_detail = "<h3>".t('Description', array(), $l)."</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>".urldecode(trim($node->body[LANGUAGE_NONE][0]["value"]))."</pre>";

        $body = theme('gofast-notifications-node-task-deadline', array(
              'user_name' => $userName,
              'l' => $l,
              'node_title' => $node->title,
              'node_link' => $node_link,
              'node_icon' => $document_pic,
              'description' => $description,
              'description_detail' => $description_detail
          ));
        
        $mail = array(
          'body' => $body,
          'title' => $title,
          'subject' => $subject,
          'footer' => $footer
        );
        gofast_mail_queue_api_queue_ext($mail,  $recpt, time());   
          
      //Send mail to members
      foreach ($node->field_members[LANGUAGE_NONE] as $member) {
        $member_uid = $member["target_id"];
        //do send to member if already receive as responsible
        if($member_uid ==  $responsible) continue; 
        $userName = gofast_user_display_name(user_load($member_uid));

        $RecipUser = user_load($member_uid);
        $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');

        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
        $document_pic = gofast_mail_queue_fa_png($node_icon);
        $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
        $subject = t('Task: Deadline reached for "!title"', array('!title'=>$node->title), $l); 
        $title = t('Deadline task notification', array(), $l);
        $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
        $node_link = $base_url . '/node/' . $node->nid;
        $description = t('A card on wich you are participant reaches deadline tomorrow :', array(), $l);
        $description_detail = "<h3>" . t('Description', array(), $l) . "</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>" . urldecode(trim($node->body[LANGUAGE_NONE][0]["value"])) . "</pre>";

        $body = theme('gofast-notifications-node-task-deadline', array(
            'user_name' => $userName,
            'l' => $l,
            'node_title' => $node->title,
            'node_link' => $node_link,
            'node_icon' => $document_pic,
            'description' => $description,
            'description_detail' => $description_detail
        ));
        $mail = array(
          'body' => $body,
          'title' => $title,
          'subject' => $subject,
          'footer' => $footer
        );
        gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
      }

      //Get all todolist assignees
      $values = gofast_kanban_get_task_checklists($node->nid);
      $assignees_without_task = array();
      $assignees_with_task = array();
      if (isset($values[0])) {
        if (count($values[0]["items"]) > 0) {
          foreach ($values[0]["items"] as $todoitem) {
            if ($todoitem->status == 1) {
              $assignees_without_task[$todoitem->uid] = $todoitem->uid;
              unset($assignees_with_task[$todoitem->uid]);
            } else {
              $assignees_with_task[$todoitem->uid] = $todoitem->uid;
              unset($assignees_without_task[$todoitem->uid]);
            }
          }
        }

        //Send mail to assignees without active task
        if (count($assignees_without_task) > 0) {
          foreach ($assignees_without_task as $uid) {
            $userName = gofast_user_display_name(user_load($uid));
            
            $RecipUser = user_load($uid);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);
            $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
            $subject = t('Task: Deadline reached for "!title"', array('!title'=>$node->title), $l); 
            $title = t('Deadline task notification', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('A card on wich you had a task reaches deadline tomorrow :', array(), $l);
            $description_detail = "<h3>" . t('Description', array(), $l) . "</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>" . urldecode(trim($node->body[LANGUAGE_NONE][0]["value"])) . "</pre>";

            $body = theme('gofast-notifications-node-task-deadline', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail
            ));
            $mail = array(
              'body' => $body,
              'title' => $title,
              'subject' => $subject,
              'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
          }
        }
        //Send mail to assignees with active task
        if (count($assignees_with_task) > 0) {
          foreach ($assignees_with_task as $uid) {
            $userName = gofast_user_display_name(user_load($uid));

            $RecipUser = user_load($uid);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);
            $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
            $subject = t('Task: Deadline reached for "!title"', array('!title'=>$node->title), $l); 
            $title = t('Deadline task notification', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('A card on wich you have a pending task reaches deadline tomorrow :', array(), $l);
            $description_detail = "<h3>" . t('Description', array(), $l) . "</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>" . urldecode(trim($node->body[LANGUAGE_NONE][0]["value"])) . "</pre>";

            $body = theme('gofast-notifications-node-task-deadline', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail
            ));
            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
          }
        }
      }
    }
  }

  // Get all open todolist items with deadline set to tomorrow
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
    
    if(count($items) > 0){
        foreach($items as $item){
            //notify card responsible
            $node = node_load($item->task_nid);
            //not send email when task is disable
            if($node->status==0)continue;
            $responsible = $node->field_person_in_charge[LANGUAGE_NONE][0]["target_id"];
            $userName = gofast_user_display_name(user_load($responsible));

            $RecipUser = user_load($responsible);
            $l = array('langcode' =>  $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node , 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);
            $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
            $subject = t('Task: Deadline reached for "!title_todo" of the "!title" task', array('!title_todo'=>$item->label,'!title'=>$node->title), $l); 
            $title = t('Deadline task notification' ,array(), $l);
            $footer = t('Message sent from ', array(), $l)." ".variable_get('site_name');
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('A checklist element on a card on wich you are responsible reaches deadline tomorrow :', array(), $l);
            $description_detail = "<h3>".t('Card description', array(), $l)."</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>".urldecode(trim($node->body[LANGUAGE_NONE][0]["value"]))."</pre>";
            $description_detail .= "<h3>".t('Task description', array(), $l)."</h3> - ".$item->label;
            
            $body = theme('gofast-notifications-node-task-deadline', array(
                  'user_name' => $userName,
                  'l' => $l,
                  'node_title' => $node->title,
                  'node_link' => $node_link,
                  'node_icon' => $document_pic,
                  'description' => $description,
                  'description_detail' => $description_detail
              ));
            
            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
         
            //do not send to member if already receive as responsible
            if($item->uid  ==  $responsible) continue; 
            //notify todolist item assignee
            $assignee = $item->uid;
            $userName = gofast_user_display_name(user_load($assignee));

            $RecipUser = user_load($assignee);
            $l = array('langcode' =>  $RecipUser->language, 'context' => 'gofast_kanban');

            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node , 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);
            $recpt = array(array('recpt' => $RecipUser->mail, 'method' => 'to'));
            $subject = t('Task: Deadline reached for "!title_todo" of the "!title task"', array('!title_todo'=>$item->label,'!title'=>$node->title), $l); 
            $title = t('Deadline task notification' ,array(), $l);
            $footer = t('Message sent from ', array(), $l)." ".variable_get('site_name');
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('A checklist element on wich you are assigned reaches deadline tomorrow :', array(), $l);
            $description_detail = "<h3>".t('Card description', array(), $l)."</h3><pre style='font-family: inherit;font-size: inherit;border: none;background-color: transparent;padding: 8px;'>".urldecode(trim($node->body[LANGUAGE_NONE][0]["value"]))."</pre>";
            $description_detail .= "<h3>".t('Task description', array(), $l)."</h3> - ".$item->label;
            
            $body = theme('gofast-notifications-node-task-deadline', array(
                  'user_name' => $userName,
                  'l' => $l,
                  'node_title' => $node->title,
                  'node_link' => $node_link,
                  'node_icon' => $document_pic,
                  'description' => $description,
                  'description_detail' => $description_detail
              ));
            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail,  $recpt, time());   
        }
    }
  
  
}

/**
 * 
 * @param type $node
 * @param type $uid
 * @return boolean
 */
function gofast_kanban_is_user_concerned_node($node, $uid) {
  $is_concerned = false;

  //To know if a user is concerned by a node, we check if he is into on of the following field => responsible, members, checklist)
  if (count($node->field_members[LANGUAGE_NONE]) > 0) {
    foreach ($node->field_members[LANGUAGE_NONE] as $member) {
      if ($member["target_id"] == $uid) {
        $is_concerned = true;
      }
    }
  }

  if (count($node->field_person_in_charge[LANGUAGE_NONE]) > 0) {
    foreach ($node->field_person_in_charge[LANGUAGE_NONE] as $member) {
      if ($member["target_id"] == $uid) {
        $is_concerned = true;
      }
    }
  }

  //Checklist
  $values = gofast_kanban_get_task_checklists($node->nid);
  if (isset($values[0])) {
    if (count($values[0]["items"]) > 0) {
      foreach ($values[0]["items"] as $todoitem) {
        if ($todoitem->uid == $uid) {
          $is_concerned = true;
        }
      }
    }
  }

  return $is_concerned;
}

/**
 * Check if a notification must be keep to send later in Cron Job
 * @global type $user
 * @param type $node
 */
function gofast_kanban_send_delayed_notification($node) {
  global $user;
  
  //If the task modification is about the assignee, the responsible or a members, keep change to be proccessed in Cron Job later
  $original_node = $node->original;
  $node_data = gofast_message_ext_split_node($node);

  if(!isset($node->original)){
      $original_node = new stdClass();
      $original_node->type = "task";
      $original_node->field_person_in_charge['und']['0']['target_id'] = "";
      $original_node->field_members['und']['0']['target_id'] = "";
      $term = array_shift(taxonomy_get_term_by_name('To Do', 'state'));
      $original_node->field_state['und']['0']['tid'] = $term->tid;
  }
  $original_node_data = gofast_message_ext_split_node($original_node);
  $node_compare = gofast_kanban_notif_compare_taks($original_node_data, $node_data);
  
  if(isset($node_compare['person_in_charge']) || isset($node_compare['members']) || isset($node_compare['state'])){
      $n = variable_get('kanban_notifications',array());
      if(!isset($n[$node->nid]))$n[$node->nid] = array(); 
      if(!isset($n[$node->nid]['task'])){
          $n[$node->nid]['task']= $original_node_data;
          if(!isset($n[$node->nid]['participants']))$n[$node->nid]['participants'] = array(); 
      }
      if(!in_array($user->uid,$n[$node->nid]['participants'])){
          $n[$node->nid]['participants'][]=$user->uid;
      }
      $n[$node->nid]['last_update']=time();
      variable_set('kanban_notifications', $n);
  }
}

/**
 * Send notifications / compare with original data
 * @param type INT $nid: Task ID
 * @param type Array $participants: Array of UID who did change
 * @param type Array $original_node_data: Original task data before change
 * @return type Array $sent_to: Array of UID who receive notifications
 */

function gofast_kanban_send_notification($nid,$participants,$original_node_data){
 global $base_url;
  
 $node=node_load($nid);
 $node_data = gofast_message_ext_split_node($node);
 $node_compare = gofast_kanban_notif_compare_taks($original_node_data, $node_data);
 $sent_to=array();
 
 if(isset($node_compare["person_in_charge"])){

    $from = gofast_message_ext_api_get_username($node_compare["person_in_charge"]['from']);
    $to = gofast_message_ext_api_get_username($node_compare["person_in_charge"]['to']);
    $array_from = explode(",", $from);
    $array_to = explode(",", $to);
    $array_from_diff = array_diff($array_from, $array_to);
    $array_to_diff = array_diff($array_to, $array_from);
    $from = implode(",", $array_from_diff);
    $to = $array_to_diff;
    //at this point, $to contains all usersnames added into members, so we can send them immediate notification
    if (count($to) > 0) {
      foreach ($to as $username) {
        $account = $RecipUser = user_load_by_name($username);
        $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));
       
        //Do not send notification if the user has update the task
        if (!in_array($account->uid, $participants)) {
          $userName = gofast_user_display_name($account);
          $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');
          $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
          $document_pic = gofast_mail_queue_fa_png($node_icon);      
          $subject = t('Task: You are responsible of "!title"', array('!title'=>$node->title), $l);        
          $title = t('New assignation as responsible on a card', array(), $l);
          $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
          $node_link = $base_url . '/node/' . $node->nid;        
          $description = t('You have been assigned as responsible on the card :', array(), $l);
          $short_without_hours_format = system_date_format_locale($account->language, "short_without_hours");
          
          $description_detail = theme('gofast-notifications-node-card-detail', array(
              'node' => $node,
              'node_compare' => $node_compare,
              'l' => $l,
              'short_without_hours_format' => $short_without_hours_format
            ));      
          
          
          $body = theme('gofast-notifications-node-task-status', array(
              'user_name' => $userName,
              'l' => $l,
              'node_title' => $node->title,
              'node_link' => $node_link,
              'node_icon' => $document_pic,
              'description' => $description,
              'description_detail' => $description_detail
          ));
          $mail = array(
              'body' => $body,
              'title' => $title,
              'subject' => $subject,
              'footer' => $footer
          );
          gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
          $sent_to[]=$account->uid;
        }
      }
    }
 }  
 if (isset($node_compare["members"])) {
    $from = gofast_message_ext_api_get_username($node_compare["members"]['from']);
    $to = gofast_message_ext_api_get_username($node_compare["members"]['to']);
    $array_from = explode(",", $from);
    $array_to = explode(",", $to);
    $array_from_diff = array_diff($array_from, $array_to);
    $array_to_diff = array_diff($array_to, $array_from);

    $from = implode(",", $array_from_diff);
    $to = $array_to_diff;
    if (count($to) > 0) {
      foreach ($to as $username) {
        $account = $RecipUser = user_load_by_name($username);
        $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));
        //Do not send notification if the user has update the task
        if (!in_array($account->uid, $participants)) {
          $userName = gofast_user_display_name($account);
          $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');
          $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
          $document_pic = gofast_mail_queue_fa_png($node_icon);    
          $subject = t('Task: You are a member of "!title"', array('!title'=>$node->title), $l);        
          $title = t('New assignation on a card', array(), $l);
          $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
          $node_link = $base_url . '/node/' . $node->nid;
          $description = t('You have been assigned as participant on the card :', array(), $l);
          $short_without_hours_format = system_date_format_locale($account->language, "short_without_hours");
          
          $description_detail = theme('gofast-notifications-node-card-detail', array(
              'node' => $node,
              'node_compare' => $node_compare,
              'l' => $l,
              'short_without_hours_format' => $short_without_hours_format
            )); 

          $body = theme('gofast-notifications-node-task-status', array(
              'user_name' => $userName,
              'l' => $l,
              'node_title' => $node->title,
              'node_link' => $node_link,
              'node_icon' => $document_pic,
              'description' => $description,
              'description_detail' => $description_detail
          ));
          $mail = array(
              'body' => $body,
              'title' => $title,
              'subject' => $subject,
              'footer' => $footer
          );
          gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
          
          $sent_to[]=$account->uid;
        }
      }
    }
  }
  if (isset($node_compare["state"])) {
    
    $user_responsible = explode(",", gofast_message_ext_api_get_username($node_data['person_in_charge']));
    $array_members = explode(",", gofast_message_ext_api_get_username($node_data['members']));
    $to = array_unique(array_merge($user_responsible, $array_members ));
    if (count($to) > 0) {
      foreach ($to as $username) {
        $account = $RecipUser = user_load_by_name($username);
        $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));
       
        //Do not send notification if the user has update the task
        if (!in_array($account->uid, $participants) && !in_array($account->uid,$sent_to)) {
          $userName = $account->ldap_user_givenname[LANGUAGE_NONE][0]['value'];
          $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');
          $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
          $document_pic = gofast_mail_queue_fa_png($node_icon);          
          $task_status = $node_compare["state"]['to'];
          $status =  i18n_taxonomy_localize_terms(taxonomy_term_load($task_status))->name;      
          $subject = t('Task: Status "!status" for "!title"', array('!status'=> $status,'!title'=>$node->title), $l);         
          $title = t('Status changed on a card', array(), $l);
          $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');      
          $node_link = $base_url . '/node/' . $node->nid;
          $description = t('The status of the card changed to : <b>@status</b>', array('@status' => $status), $l);
          $short_without_hours_format = system_date_format_locale($account->language, "short_without_hours");
          
          $description_detail = theme('gofast-notifications-node-card-detail', array(
              'node' => $node,
              'node_compare' => $node_compare,
              'l' => $l,
              'short_without_hours_format' => $short_without_hours_format
            )); 
 
          $body = theme('gofast-notifications-node-task-status', array(
              'user_name' => $userName,
              'l' => $l,
              'node_title' => $node->title,
              'node_link' => $node_link,
              'node_icon' => $document_pic,
              'description' => $description,
              'description_detail' => $description_detail
          ));
          $mail = array(
              'body' => $body,
              'title' => $title,
              'subject' => $subject,
              'footer' => $footer
          );
          gofast_mail_queue_api_queue_ext($mail,  $recpt, time()); 
          $sent_to[]=$account->uid;
        }
      }
    }
  }
}

/**
 * 
 * @param type $from
 * @param type $to
 * @return type
 */
function gofast_kanban_notif_compare_taks($from, $to) {
  $compare_array[] = array();
  foreach ($from as $k_from => $v_from) {
    $isSame = (strcmp($v_from, $to[$k_from]) == 0); //Same values   
    if ($isSame) {
      
    } else {
      $compare_array[$k_from]['from'] = $v_from;
      $compare_array[$k_from]['to'] = $to[$k_from];
    }
  }
  return $compare_array;
}

/**
 * Send notifications of checks list Items change / compare with original data
 * @param type INT $nid: Task ID
 * @param type Array $participants: Array of UID who did change
 * @param type Array $$old_values_items: original items checklists data before change
 */

function gofast_kanban_checklistItem_notification($nid,$participants,$old_values_items) {
    global $base_url;
   
    $new_values = gofast_kanban_get_task_checklists($nid);
    
    $node = node_load($nid);  
    foreach ($new_values[0]['items'] as $key => $item) {     
      $ciid = $item->ciid;
      
      if (!in_array($item->uid, $participants)) {
        $assignation_sent=false;
        
        if ($item->uid != $old_values_items[$ciid]->uid) {        
            $account = $RecipUser = user_load($item->uid);
            $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));

            $userName = gofast_user_display_name($account);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');
            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);      
            $subject = t('Task: You are assigned on "!title_todo" of the "!title" task', array('!title_todo'=>$item->label,'!title'=>$node->title), $l);
            $title = t('New assignation on a checklist item', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');     
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('You have been assigned to a checklist element of the card : ', array(), $l);       
            $short_without_hours_format = system_date_format_locale($account->language, "short_without_hours");    
            
            $description_detail = theme('gofast-notifications-node-card-detail', array(
              'node' => $node,
              'task' => $item,
              'l' => $l,
              'short_without_hours_format' => $short_without_hours_format
            ));          
            
            $body = theme('gofast-notifications-node-task-status', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail

            ));

            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail, $recpt, time());
            $assignation_sent=true;
          }
          if($item->deadline !=  $old_values_items[$ciid]->deadline && !$assignation_sent && isset($item->uid)){   
            $account = $RecipUser = user_load($item->uid);
            $recpt = array(array('recpt' => $account->mail, 'method' => 'to'));
            $userName = gofast_user_display_name($account);
            $l = array('langcode' => $RecipUser->language, 'context' => 'gofast_kanban');
            $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
            $document_pic = gofast_mail_queue_fa_png($node_icon);  
            $deadline_formated = format_date($item->deadline, 'short_without_hours', '', NULL, $l); 
            $subject = t('Task: New deadline on "!deadline" for "!title_todo" of the "!title" task', array('!deadline'=>$deadline_formated,'!title_todo'=>$item->label,'!title'=>$node->title), $l);
            $title = t('New deadline', array(), $l);
            $footer = t('Message sent from ', array(), $l) . " " . variable_get('site_name');
            
            $node_link = $base_url . '/node/' . $node->nid;
            $description = t('Deadline has change on a checklist element of the card : ', array(), $l);
            $short_without_hours_format = system_date_format_locale($account->language, "short_without_hours");
            
            $description_detail = theme('gofast-notifications-node-card-detail', array(
              'node' => $node,
              'task' => $item,
              'l' => $l,
              'short_without_hours_format' => $short_without_hours_format
            ));  
            
            $body = theme('gofast-notifications-node-task-deadline-change', array(
                'user_name' => $userName,
                'l' => $l,
                'node_title' => $node->title,
                'node_link' => $node_link,
                'node_icon' => $document_pic,
                'description' => $description,
                'description_detail' => $description_detail

            ));

            $mail = array(
                'body' => $body,
                'title' => $title,
                'subject' => $subject,
                'footer' => $footer
            );
            gofast_mail_queue_api_queue_ext($mail, $recpt, time()); 

          }
      }
    }
}
