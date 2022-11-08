<?php

/**
 * API for gofast_subscription_ui module
 */

/**
 * Get type of a node (usually called by *_get_item_type   below)
 * 
 * @param $nid
 *  Node's ID
 * 
 * @return
 *  A string that contains the referenced type
 */
function gofast_subscription_ui_get_node_type($nid){
  $query = db_select('node', 'n')
          ->fields('n', array('type'))
          ->condition('nid', $nid)
          ->execute();
  $result = $query->fetch();
  switch($result->type){
    case 'alfresco_item':
      $return_type = "Document";
      break;
    case 'article':
      $return_type = "Wiki page";
      break;
    case 'group':
      $return_type = "Group";
      break;
    case 'forum':
      $return_type = "Forum";
      break;
    case 'webform':
      $return_type = "Web Form";
      break;
    case 'organisation':
      $return_type = "Organization";
      break;
    case 'extranet':
      $return_type = "Extranet";
      break;
    case 'public':
      $return_type = "Public space";
      break;
    case 'task':
      $return_type = "Task";
      break;
    case 'kanban':
      $return_type = "Card";
      break;
    default:
      $return_type = $result->type;
      break;
  }
  
  return $return_type;
}

/**
 * Get type of document/user/group subscription item (usually called by *_get_user_subscriptions)
 * 
 * Used to turn a generic machine name into human readable name.
 * 
 * @param $item
 *  A subscription item
 * 
 * @return
 *  A string that contains the referenced type
 */
function gofast_subscription_ui_get_item_type($item){
  $entity_type = $item->entity_type;
  
  switch($entity_type){
    case 'user':
      $item_type = "User";
      break;
    case 'taxonomy_term':
      $item_type = "Term";
      break;
    case 'node':
      $nid = $item->entity_id;
      $item_type = gofast_subscription_ui_get_node_type($nid);
      break;
    default:
      $item_type = "Error";
      break;
  }
  
  return $item_type;
}

/**
 * Get name/title of a subscription item (usually called by *_get_user_subscriptions)
 * 
 * @param $item
 *  A subscription item
 * 
 * @return
 *  A string that contains the referenced name
 */
function gofast_subscription_ui_get_item_name($item){
  $entity_type = $item->entity_type;
  $entity_id = $item->entity_id;
  
  switch($entity_type){
    case 'user':
      $query = db_select('users', 'u')
            ->fields('u', array('name'))
            ->condition('uid', $entity_id)
            ->execute();
      $result = $query->fetch();
      $item_name = $result->name;
      break;
    case 'taxonomy_term':
      $query = db_select('taxonomy_term_data', 't')
            ->fields('t', array('name'))
            ->condition('tid', $entity_id)
            ->execute();
      $result = $query->fetch();
      $item_name = $result->name;
      break;
    case 'node':
      $item_name = gofast_breadcrumb_display_breadcrumb($entity_id, ['return' => TRUE, 'title_link' => TRUE, 'remove_extension' => FALSE, 'editable' => FALSE, 'in_modal' => TRUE]);
      break;
    default:
      $item_name = "Error";
      break;
  }
  
  return $item_name;
}

function gofast_subscription_ui_get_item_path($item){
  
  $entity_type = $item->entity_type;
  $entity_id = $item->entity_id;
  
  switch($entity_type){
    case 'user':
      $query = db_select('users', 'u')
            ->fields('u', array('name'))
            ->condition('uid', $entity_id)
            ->execute();
      $result = $query->fetch();
      $item_path = $result->name;
      break;
    case 'taxonomy_term':
      $query = db_select('taxonomy_term_data', 't')
            ->fields('t', array('name'))
            ->condition('tid', $entity_id)
            ->execute();
      $result = $query->fetch();
      $item_path = $result->name;
      break;
    case 'node':

      $options = array('return' => TRUE);
      $breadcrumb = gofast_breadcrumb_get_breadcrumb($entity_id, $options);
      $raw_locations = array();
      foreach ($breadcrumb as $k => $crumbs){
        $full_path = $crumbs[count($crumbs)-2]['location'].'/'.$crumbs[count($crumbs)-1]['name'];
        $raw_locations[] = $full_path;
      }   
      //set item_path to first location;
      $item_path = $raw_locations[0];
      break;
    default:
      $item_path = "Error";
      break;
  }
  return $item_path;
  
}

/**
 * Get machine type of a subscription item (Usualy called to create links)
 * 
 * @param $item
 *  A subscription item
 * 
 * @return
 *  A string that contains the referenced type
 */
function gofast_subscription_ui_get_machine_type($item){
  $entity_type = $item->entity_type;
  $entity_id = $item->entity_id;
  
  switch($entity_type){
    case 'user':
      $item_machine_type = "user";
      break;
    case 'taxonomy_term':
      $item_machine_type = "term";
      break;
    case 'node':
      $nid = $item->entity_id;
      $item_type = gofast_subscription_ui_get_node_type($nid);
      if($item_type == "Group" || $item_type == "Organization" || $item_type == "Extranet" || $item_type == "Public space"){
        $item_machine_type = "og";
      }
      else{
        $item_machine_type = "node";
      }
      break;
    default:
      $item_machine_type = "Error";
      break;
  }
  
  return $item_machine_type;
}

/**
 * Retrieve subscriptions of an user (Usually called by the .module to create the UI)
 * 
 * @param $uid
 *  ID of the requested user
 * 
 * @return
 *  An array describing all user's subscriptions
 */
function gofast_subscription_ui_get_user_subscriptions($uid, $limit = FALSE, $offset = FALSE, $sortField = FALSE, $sortDir = FALSE){
  $items = NULL;

  // query every field we need at once instead of doing multiple queries in a loop, sort must be done in the query
  // in order for sorting to work with the query limit which causes the serve side pagination perf increase
  $query_string = "SELECT flagging.entity_id, flagging.entity_type, flagging_id, flagging.uid name, flagging.fid, taxonomy_term_data.name, users.name, node.type, node.title, field_revision_field_frequency_term.field_frequency_term_value, field_revision_field_frequency_user.field_frequency_user_value, field_revision_field_frequency_node.field_frequency_node_value, field_revision_field_frequency_og.field_frequency_og_value, field_frequency_comment_value,
    CASE
      WHEN flagging.entity_type = 'taxonomy_term' THEN '" . t("Tag") . "'
      WHEN flagging.entity_type = 'node' THEN (
        CASE
          WHEN node.type = 'group' THEN '" . t("Group") . "'
          WHEN node.type = 'organisation' THEN '" . t("Organization") . "'
          WHEN node.type = 'extranet' THEN '" . t("Extranet") . "'
          WHEN node.type = 'public_space' THEN '" . t("Public space") . "'
          WHEN node.type = 'alfresco_item' THEN '" . t("Document") . "'
          WHEN node.type = 'article' THEN '" . t("Wiki page") . "'
          WHEN node.type = 'forum' THEN '" . t("Forum") . "'
          WHEN node.type = 'webform' THEN '" . t("Web Form") . "'
          WHEN node.type = 'task' THEN '" . t("Task") . "'
          WHEN node.type = 'kanban' THEN '" . t("Card") . "'
          ELSE '" . t("Node") . "'
        END
      )
      WHEN flagging.entity_type = 'user' THEN '" . t("User") . "'
      ELSE '0'
    END AS sortable_type,
    CASE
      WHEN flagging.entity_type = 'taxonomy_term' THEN taxonomy_term_data.name
      WHEN flagging.entity_type = 'node' THEN node.title
      WHEN flagging.entity_type = 'user' THEN users.name
      ELSE '0'
    END AS sortable_name,
    CASE
      WHEN flagging.entity_type = 'taxonomy_term' AND field_revision_field_frequency_term.field_frequency_term_value IS NOT NULL THEN field_revision_field_frequency_term.field_frequency_term_value
      WHEN flagging.entity_type = 'node' THEN (
        CASE
          WHEN (node.type = 'group' OR node.type = 'organization' OR node.type = 'extranet' OR node.type = 'public_space') AND field_revision_field_frequency_og.field_frequency_og_value IS NOT NULL THEN field_revision_field_frequency_og.field_frequency_og_value
          WHEN field_revision_field_frequency_node.field_frequency_node_value IS NOT NULL THEN field_revision_field_frequency_node.field_frequency_node_value
          ELSE '0'
        END
      )
      WHEN flagging.entity_type = 'user' AND field_revision_field_frequency_user.field_frequency_user_value IS NOT NULL THEN field_revision_field_frequency_user.field_frequency_user_value
      ELSE '0'
    END AS sortable_frequency
  FROM flagging
    INNER JOIN flag ON flagging.fid = flag.fid
    LEFT JOIN taxonomy_term_data ON flagging.entity_id = taxonomy_term_data.tid AND flagging.entity_type = 'taxonomy_term'
    LEFT JOIN users ON flagging.entity_id = users.uid AND flagging.entity_type = 'user'
    LEFT JOIN node ON flagging.entity_id = node.nid AND flagging.entity_type = 'node'
    LEFT JOIN field_revision_field_frequency_term ON flagging.flagging_id = field_revision_field_frequency_term.entity_id AND flagging.entity_type = 'taxonomy_term'
    LEFT JOIN field_revision_field_frequency_user ON flagging.flagging_id = field_revision_field_frequency_user.entity_id AND flagging.entity_type = 'user'
    LEFT JOIN field_revision_field_frequency_node ON flagging.flagging_id = field_revision_field_frequency_node.entity_id AND flagging.entity_type = 'node'
    LEFT JOIN field_revision_field_frequency_og ON flagging.flagging_id = field_revision_field_frequency_og.entity_id AND flagging.entity_type = 'node'
    LEFT JOIN field_revision_field_frequency_comment ON flagging.flagging_id = field_revision_field_frequency_comment.entity_id
  WHERE flagging.uid = :uid AND (flag.name = 'subscribe_node' OR flag.name = 'subscribe_user' OR (flag.name = 'subscribe_term' AND taxonomy_term_data.name IS NOT NULL) OR flag.name='subscribe_og')";

  if ($sortField) {
    $query_string .= " ORDER BY sortable_" . $sortField . " " . strtoupper($sortDir);
  }

  if ($limit) {
    $query_string .= " LIMIT ". $limit . " OFFSET " . $offset;
  }

  $query = db_query($query_string, array(":uid" => $uid));
  // additional SQL queries only on displayed events
  foreach($query as $occur){
    if ($occur->entity_type == "user"){
      $item_machine_type = "user";
    }
    if ($occur->entity_type == "taxonomy_term"){
      $item_machine_type = "term";
    }
    if ($occur->entity_type == "node"){
      $item_machine_type = ($occur->sortable_type == t("Group") || $occur->sortable_type == t("Organization") || $occur->sortable_type == t("Extranet") || $occur->sortable_type == t("Public space")) ? "og" : "node";
      //$occur->sortable_name = gofast_breadcrumb_display_breadcrumb($occur->entity_id, ['return' => TRUE, 'title_link' => TRUE, 'remove_extension' => FALSE, 'editable' => FALSE, 'in_modal' => TRUE]);
      if($item_machine_type == "og"){
         $occur->sortable_name = l( gofast_cmis_space_get_drupal_path($occur->entity_id), $occur->entity_type . '/' . $occur->entity_id);
      }else{
         $occur->sortable_name = l($occur->sortable_name, $occur->entity_type . '/' . $occur->entity_id);
      }
      //$occur->sortable_name = l( gofast_cmis_space_get_drupal_path($occur->entity_id), $occur->entity_type . '/' . $occur->entity_id);
      //$item_path =  gofast_cmis_space_get_drupal_path($occur->entity_id);
      $item_path = "";
    } else {
      $item_path = $occur->sortable_name;
    }
    
    //Generate unflag link
    $flag = flag_get_flag('subscribe_'.$item_machine_type);
    $flag_link = module_invoke('flag', 'flag_link', $flag, 'unflag', $occur->entity_id);
    $flag_link = url($flag_link['href'], $flag_link);
    $item_x_link = theme("gofast_subscription_ui_unflag", ['link' => $flag_link]);
    
    $items[] = array(
      'name_id' => $occur->sortable_name,
      'type' => $occur->sortable_type,
      'x_link' => $item_x_link,
      'fid' => t($occur->flagging_id, array(), array('context' => 'gofast')),
      'machine_type' => $item_machine_type,
      'path' => $item_path,
      'frequency' => $occur->sortable_frequency,
      'frequency_comment' => $occur->field_frequency_comment_value,
    );
  }

  // default sorting
  if (!$sortField) {
    $type  = array_column($items, 'type');
    $path = array_column($items, 'path');
    
    array_multisort($type, SORT_ASC, $path, SORT_ASC, $items);
  }
  return $items;
}

/**
 * Clear subscriptions, called by the mail queue module before acting
 */
function gofast_subscription_ui_api_clear_subscriptions(){
  $query = db_query("SELECT entity_id, flagging.entity_type, flagging_id, flagging.uid, name, flagging.fid FROM flagging INNER JOIN flag ON flagging.fid = flag.fid WHERE name='subscribe_node' OR name='subscribe_user' OR name='subscribe_term' OR name='subscribe_og'");
  
  while($item = $query->fetch()){
    $uid = $item->uid;
    $fid = $item->flagging_id;
    $type = $item->name;
    $eid = $item->entity_id;
    //TODO: Check if user exists.. Is disabled etc...
    switch($type){ //Differents checks for any types of subscriptions (group, user etc..)
      case 'subscribe_og': //Subscription to a group
        if(!is_object(og_get_membership('node', $eid, 'user', $uid))){ //The user isn't in the group
          gofast_subscription_ui_api_delete_subscription($fid);
          break;
        }
        break;
      case 'subscribe_node'://Subscription to a node
        $node = node_load($eid, NULL, TRUE);
        if($node == NULL){ //Case of a non existing node
          gofast_subscription_ui_api_delete_subscription($fid);
          break;
        }
        else{
          $group_array = $node->og_group_content_ref['und'];
          $access = FALSE;
          
          foreach ($group_array as $group_item) { //For each groups referenced in the node
            if(is_object(og_get_membership('node', $group_item['target_id'], 'user', $uid)) || $uid = 1){ //The user is in one of the node's group
              $access = TRUE;
            }
          }
          
          if($access == FALSE){
            gofast_subscription_ui_api_delete_subscription($fid);
          }
        }
        break;
    }
  }
}

/**
 * Delete a subscription
 * 
 * @param $fid
 *  Flagging ID of the subscription
 */
function gofast_subscription_ui_api_delete_subscription($fid){
  db_delete('flagging')
          ->condition('flagging_id', $fid)
          ->execute();
}

/**
 * Return an array of subscribed users
 * 
 * @param $type
 *  Type of subscription (node, group, user, term...)
 * 
 * @param $eid
 *  Entity ID
 * 
 * @param $nid
 *  The node ID where the event come from (permission check)
 * 
 * @param $is_comment
 *  TRUE if the event is a comment and we want to get the frequency set specifically for the subscription comments
 * 
 * @return
 *  An array of 0=>user;1=>frequency or NULL if there is no subscribed user
 */
function gofast_subscription_ui_api_subscribed_list($type, $eid, $nid = NULL, $is_comment = FALSE){
  if(!isset($nid)){
    $nid = $eid;
  }
  $users_subscribed = NULL;
  if($type=='group'){
    $type = 'og';
  }
  $query = db_query("SELECT entity_id, flagging.entity_type, flagging_id, uid, name, flagging.fid FROM flagging INNER JOIN flag ON flagging.fid = flag.fid WHERE name='subscribe_".$type."' AND entity_id='".$eid."'");
  $i=0;
  
  while($subscription_item = $query->fetch()){
    $query_frequency = db_query("SELECT flagging_id, flagging.entity_id, field_revision_field_frequency_".$type.".entity_id, field_frequency_".$type."_value, field_frequency_comment_value FROM flagging LEFT JOIN field_revision_field_frequency_".$type." ON flagging_id=field_revision_field_frequency_".$type.".entity_id LEFT JOIN field_revision_field_frequency_comment ON flagging_id=field_revision_field_frequency_comment.entity_id WHERE flagging.flagging_id='".$subscription_item->flagging_id."'");
    //check permissions if subscription type is "user"
    if($type == "user" && !node_access('view', node_load($nid), user_load($subscription_item->uid))){
      continue;
    }
    $users_subscribed[$i][0] = $subscription_item->uid;
    $frequency = $query_frequency->fetchAll();
    if($is_comment){
      $users_subscribed[$i][1] = $frequency[0]->field_frequency_comment_value ?? variable_get("comments_notification_frequency_configuration", 0);
      $i++;
      continue;
    }
    $frequency_obj = ('field_frequency_'.$type.'_value');
    $users_subscribed[$i][1] = $frequency[0]->$frequency_obj ?? variable_get("notification_frequency_configuration", 0);
    $i++;
  }
  return $users_subscribed;
}

/*
 * Reset subscription for a given user
 *  @param $uid
 *    User ID to reset. Will reset all users if the param is not given.
 */
function gofast_subscription_ui_api_reset_subscriptions($uid = -1){
  if($uid == -1){ //Retrieve all plateform users uids
    $uids = db_select('users', 'u')
            ->fields('u', array('uid'))
            ->execute()
            ->fetchAll();
  }
  else{
    $uid_obj = new stdClass();
    $new_obj->uid = $uid;
    $uids = array($new_obj);
  }
  return _gofast_subscription_ui_api_reset_subscriptions_multiple($uids);
}

/*
 * Reset subscription for a given array of user
 *  @param $uids
 *    Array of stdClass containing the uids to reset keyed as:
 * 
  Array
    (
      [0] => stdClass Object
      (
        [uid] => 1
      )
 *  
      [1] => stdClass Object
      (
        [uid] => 2
      )
    )
 */
function _gofast_subscription_ui_api_reset_subscriptions_multiple($uids){
  $escaped_spaces = gofast_og_get_root_spaces();
  foreach($uids as $uid_obj){
    $uid = $uid_obj->uid;
    gofast_subscription_ui_api_delete_subscriptions_by_uid($uid);
    $user_spaces = gofast_og_get_spaces_by_user(user_load($uid), TRUE, FALSE);
    foreach($user_spaces as $gid){
      if(!in_array($gid, $escaped_spaces)){
        $og_flag = flag_get_flag('subscribe_og');
        $og_flag->flag('flag', $gid, user_load($uid));
      }
    }
  }
}

function gofast_subscription_ui_api_delete_subscriptions_by_uid($uid){
  foreach(array('subscribe_node', 'subscribe_og', 'subscribe_user', 'subscribe_term') as $flag_name){
    $flag_id = db_select('flag', 'f')
            ->fields('f', array('fid'))
            ->condition('name', $flag_name)
            ->execute()
            ->fetch()
            ->fid;
    
    $flagging_id = db_select('flagging' , 'f')
        ->fields('f', array('flagging_id'))
        ->condition('fid', $flag_id)
        ->condition('uid', $uid)
        ->execute()
        ->fetch()
        ->flagging_id;
    
    db_delete('flagging')
            ->condition('fid', $flag_id)
            ->condition('uid', $uid)
            ->execute();
    
    db_delete('field_data_field_frequency_og')
            ->condition('entity_id', $flagging_id)
            ->condition('entity_type', 'flagging')
            ->execute();
  }
}

function gofast_subscription_ui_api_delete_subscriptions_by_uid_gid($uid, $gid){
  foreach(array('subscribe_node', 'subscribe_og', 'subscribe_user', 'subscribe_term') as $flag_name){
    $flag_id = db_select('flag', 'f')
            ->fields('f', array('fid'))
            ->condition('name', $flag_name)
            ->execute()
            ->fetch()
            ->fid;
    
  $flagging_id = db_select('flagging' , 'f')
        ->fields('f', array('flagging_id'))
        ->condition('fid', $flag_id)
        ->condition('uid', $uid)
        ->execute()
        ->fetch()
        ->flagging_id;
    
    db_delete('flagging')
            ->condition('fid', $flag_id)
            ->condition('uid', $uid)
            ->condition('entity_id', $gid)
            ->execute();
    
    db_delete('field_data_field_frequency_og')
            ->condition('entity_id', $flagging_id)
            ->condition('entity_type', 'flagging')
            ->execute();
  }
}
