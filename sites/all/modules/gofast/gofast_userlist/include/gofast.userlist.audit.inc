<?php

/**
 * Insert Userlist action on GF AUDIT
 * @global type $user
 * @param type $event_type
 * @param type $node
 * @return type
 */
function gofast_userlist_insert_into_audit($event_type, $node, $message = NULL) {


  //we get only modified values
  $last_event_serialized = array();

  if (isset($message)) {
    $message_data = json_decode($message, TRUE);
    foreach ($message_data as $key => $value) {
      if (isset($value["to"])) {
        $event[$key] = array("removed" => $value["from"], "current" => $value["to"]);
      }
    }
  }

  switch ($event_type) {
    case "NUSL":
      //first we check if a creation line already exists in the audit for this node
      $result = db_select('ceo_vision_audit', 'a')
          ->fields('a', array('nid')) // select on "nid" field because there is an index on it
          ->condition('nid', $node->nid)
          ->condition('event_type', 'new_userlist')
          ->execute();

      if ($result->rowCount() > 0) {
        return;
      }

      $last_event_unserialized["mod_timestamp"] = time();
      $last_event_unserialized["mod_author"] = $node->uid;

      $event['mod_author'] = $node->uid;
      $event['mod_timestamp'] = time();
      $event['title']['current'] = $node->title;
      $event['status'] = 'new';
      $event = serialize($event);
      $last_event_serialized = rawurlencode($event);
      $event_type = "new_userlist";
      gofast_audit_insert_line_audit($node->nid, $event_type, $last_event_serialized, $last_event_unserialized);


      break;
    case "EUSL" :

      //Prevent inserting "Empty modification into audit"
      $keys = (isset($message))?array_keys($event):array();
      if( count($keys) == 0 || (count($keys) == 1 && in_array("changed", $keys)) ){
        return;
      }

      //unset log changed of ruid
      unset($event['ruid']);

      global $user;
      $last_event_unserialized["mod_timestamp"] = time();
      $last_event_unserialized["mod_author"] = $user->uid;
      $event_type = "update_userlist";
      $event['mod_author'] = $user->uid;
      $event['mod_timestamp'] = time();
      $event['title']['current'] = isset($event['title']['current']) ? $event['title']['current'] : $node->title;
      $event['event'] = $event_type;
      $event = serialize($event);
      $last_event_serialized = rawurlencode($event);

      gofast_audit_insert_line_audit($node->nid, $event_type, $last_event_serialized, $last_event_unserialized);

      break;
    case "DUSL" :

      //first we check if a creation line already exists in the audit for this node
      $result = db_select('ceo_vision_audit', 'a')
          ->fields('a', array('nid')) // select on "nid" field because there is an index on it
          ->condition('nid', $node->nid)
          ->condition('event_type', 'delete_userlist')
          ->execute();

      if ($result->rowCount() > 0) {
        return;
      }
      global $user;
      $event_type = "delete_userlist";
      $last_event_unserialized["mod_timestamp"] = time();
      $last_event_unserialized["mod_author"] = $user->uid;
      $event['mod_author'] = $user->uid;
      $event['mod_timestamp'] = time();
      $event['title'] = $node->title;
      $event['event'] = $event_type;
      $event = serialize($event);
      $last_event_serialized = rawurlencode($event);

      gofast_audit_insert_line_audit($node->nid, $event_type, $last_event_serialized, $last_event_unserialized);

      break;
  }
}

/**
 * Insert into audit when user join spaces by userlist
 *
 * @param string $event_type
 * @param int $gid
 * @param array $members
 * @param int $ulid
 * @return void
 */
function gofast_userlist_insert_into_spaces_audit($event_type, $members_by_spaces, $ulid){
  global $user;

  switch ($event_type) {
    case 'add_member':
      foreach ($members_by_spaces as $gid => $space_member_array) {
        $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'add_member', 'array_members' => $space_member_array);
        $event = serialize($event);
        $last_event_serialized = rawurlencode($event);
        $last_event_unserialized["mod_timestamp"] = time();
        $last_event_unserialized["mod_author"] = $user->uid;
        $last_event_unserialized["mod_members"] = implode(';', $space_member_array);
        gofast_audit_insert_line_audit($gid, $event_type, $last_event_serialized, $last_event_unserialized);
      }
      break;
    case 'delete_member':
      foreach ($members_by_spaces as $gid => $space_member_array) {
        $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'delete_member', 'array_members' => $space_member_array);
        $event = serialize($event);
        $last_event_serialized = rawurlencode($event);
        $last_event_unserialized["mod_timestamp"] = time();
        $last_event_unserialized["mod_author"] = $user->uid;
        $last_event_unserialized["mod_members"] = implode(';', $space_member_array);
        gofast_audit_insert_line_audit($gid, $event_type, $last_event_serialized, $last_event_unserialized);
      }
      break;
    default:
      # code...
      break;
  }

}

/*
 * Alter title field for deleted spaces
 */

function gofast_userlist_views_pre_render(&$view) {
  if ($view->name == "gofast_audit") {
    foreach ($view->result as &$result) {
      if ($result->ceo_vision_audit_event_type == "delete_userlist") {
        $details = unserialize(rawurldecode($result->ceo_vision_audit_details));
        $result->node_ceo_vision_audit_title = $details['title'];
      } else if ($result->ceo_vision_audit_event_type == "new_userlist" || $result->ceo_vision_audit_event_type == "update_userlist") {
        $details = unserialize(rawurldecode($result->ceo_vision_audit_details));
        $result->node_ceo_vision_audit_title = $details['title']['current'];
      }
    }
  }
}

/**
 * Format detail popup for audit log
 * @global type $user
 * @param type $event
 * @return type
 */
function gofast_userlist_api_render_event($event) {

  $edit = NULL;
  global $user;
  $myformat = system_date_format_locale($user->language, "medium");
  $l = array('langcode' => $user->language, 'context' => 'gofast');

  if (isset($event['0'])) {
    foreach ($event as $edit_key => $edition) {
      if (is_array($edition) /* || ($edit_key == "title" && $edit === NULL ) */) {
        switch ($event['event']) {
          case 'EUSL':
          case 'update_userlist' :

            $from = $edition['from'];
            $to = $edition['to'];

            if (($from == NULL && $to != NULL) && $edition['field'] != 'title') { //Case: New
              $edit .= '<div class="panel panel-primary"><div class="panel-heading">' . t(ucfirst($edition['field']), array(), array('context' => 'gofast')) . '</div><div class="panel-body">';
              $edit .= '<div class="panel panel-success"><div class="panel-heading">' . t('New') . '</div><div class="panel-body">';
              if ($edition['field'] == 'body' || $edition['field'] == 'summary') {
                $edit .= $to;
              }else  if ($edition['field'] == 'userlist members' || $edition['field'] == 'userlist adm') {
                $members = $to;
                foreach ($members as $user_uid) {
                  $edit .= theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                      ) . ':   ' . gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                }
              } else {
                $edit .= t($to, array(), array('context' => 'gofast'));
              }
              $edit .= '</div></div></div></div>';
            }
            if ($from != NULL && $to == NULL) { //Case: Removed
              $edit .= '<div class="panel panel-primary"><div class="panel-heading">' . t(ucfirst($edition['field']), array(), array('context' => 'gofast')) . '</div><div class="panel-body">';
              $edit .= '<div class="panel panel-danger"><div class="panel-heading">' . t('Removed') . '</div><div class="panel-body">';
              if ($edition['field'] == 'body' || $edition['field'] == 'summary') {
                $edit .= $from;
              }else  if ($edition['field'] == 'userlist members' || $edition['field'] == 'userlist adm') {
                $members =$from;
                foreach ($members as $user_uid) {
                  $edit .= theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                      ) . ':   ' . gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                }
              } else {
                $edit .= t($from, array(), array('context' => 'gofast'));
              }
              $edit .= '</div></div></div></div>';
            }
            if ($from != NULL && $to != NULL) { //Case: Edition
              $edit .= '<div class="panel panel-primary"><div class="panel-heading">' . t(ucfirst($edition['field']), array(), array('context' => 'gofast')) . '</div><div class="panel-body">';
              $edit .= '<div class="panel panel-danger"><div class="panel-heading">' . t('Old') . '</div><div class="panel-body">';
              if ($edition['field'] == 'body' || $edition['field'] == 'summary') {
                $edit .= $from;
              }else  if ($edition['field'] == 'userlist members' || $edition['field'] == 'userlist adm') {
                $members = $from;
                foreach ($members as $user_uid) {
                  $edit .= theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                      ) . ':   ' . gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                }
              } else {
                $edit .= t($from, array(), array('context' => 'gofast'));
              }
              $edit .= '</div></div>';
              $edit .= '<div class="panel panel-success"><div class="panel-heading">' . t('New') . '</div><div class="panel-body">';
              if ($edition['field'] == 'body' || $edition['field'] == 'summary') {
                $edit .= $to;
              }else  if ($edition['field'] == 'userlist members' || $edition['field'] == 'userlist adm') {
                $members = $to;
                foreach ($members as $user_uid) {
                  $edit .= theme('user_picture', array('account' => user_load($user_uid), 'popup' => FALSE, 'dimensions' => array('width' => '25px', 'height' => '25px'))
                      ) . ':   ' . gofast_message_ext_api_get_user_name($user_uid) . '</br>';
                }
              } else {
                $edit .= t($to, array(), array('context' => 'gofast'));
              }
              $edit .= '</div></div></div></div>';
            }
            break;
        }
      }
    }
  }

  $output .= theme('gofast-message-ext-last-event', array('output_prepare' => $event['message'], 'edit' => $edit));
  return $output;
}

/**
 *
 * @global type $user
 * @param type $node
 * @param type $membership_data
 */
function gofast_userlist_audit_membership($node, $membership_data) {

  global $user;
  if ($membership_data['membership_action'] == 'DMEM') {

    $event_type = 'delete_member';
    $group_node = array();
    $group_node['event']['value'] = $membership_data['membership_action']; //NMEM or DMEM
//    $group_node['changed']['value'] = time();
    $group_node['title']['value'] = $node->title;
    $group_node['type']['value'] = $node->type;
    $group_node['ruid']['value'] = $user->uid;
    $group_node['nid']['value'] = $node->nid;
    $group_node['new_member_type']['value'] = $membership_data['membership_type']; // user or userlist
    $group_node['new_member_id']['value'] = $membership_data['membership_id']; // uid or ulid
    $group_node['new_member_name']['value'] = $membership_data['membership_name']; // name or title
    // $message = $group_node['event']['value'].'|'.json_encode($group_node);

    if ('user' == $group_node['new_member_type']['value']) {
      $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => $event_type, 'user_name' => $group_node['new_member_name']['value'], 'dest_id' => $group_node['new_member_id']['value'], 'user_role' => $user_role);
    } elseif ('userlist' == $group_node['new_member_type']['value']) {
      $entity_ulid = $group_node['new_member_id']['value'];
      $members_added = array_keys(gofast_userlist_get_members($entity_ulid));
      $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => $event_type, 'userlist_name' => $group_node['new_member_name']['value'], 'userlist_id' => $entity_ulid, 'dest_list' => $members_added, 'userlist_role' => $user_role);
    }
    $event = serialize($event);
    $last_event_serialized = rawurlencode($event);
    $last_event_unserialized["mod_timestamp"] = time();
    $last_event_unserialized["mod_author"] = $user->uid;
    $last_event_unserialized["mod_members"] = implode(';', $members_added);
  }
  gofast_audit_insert_line_audit($node->nid, $event_type, $last_event_serialized, $last_event_unserialized);
}
