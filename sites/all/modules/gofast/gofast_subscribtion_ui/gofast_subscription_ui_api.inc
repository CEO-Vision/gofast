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
      $return_type = "Article";
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
      $query = db_select('node', 'n')
            ->fields('n', array('title', 'nid'))
            ->condition('nid', $entity_id)
            ->execute();
      $result = $query->fetch();
      
      // GET NODE BY NODE ID 
      $node = node_load($result->nid);
      $node_reference = $node->field_folder_reference;
      $node_reference_value = '';
      // GET REFERENCE OF CURRENT NODE
      foreach($node_reference as $ref){
        $node_reference_value = $ref[0]['value']; 
      }
      // GET PAHT OF CURRENT NODE
      $node_item = gofast_cmis_item_get($node_reference_value);
      $node_path = $node_item->properties['cmis:path'];

      $item_name = $node_path;
      break;
    default:
      $item_name = "Error";
      break;
  }
  
  return $item_name;
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
function gofast_subscription_ui_get_user_subscriptions($uid){
  
  $items = NULL;
  //The query will get datas restricted by a user ID.
  $query = db_query("SELECT entity_id, flagging.entity_type, flagging_id, flagging.uid name, flagging.fid FROM flagging INNER JOIN flag ON flagging.fid = flag.fid WHERE flagging.uid=".$uid." AND (name='subscribe_node' OR name='subscribe_user' OR name='subscribe_term' OR name='subscribe_og')");
  
  foreach($query as $occur){
    $item_type = gofast_subscription_ui_get_item_type($occur);
    $item_name = gofast_subscription_ui_get_item_name($occur);
    $item_fid = $occur->flagging_id;
    $item_machine_type = gofast_subscription_ui_get_machine_type($occur);
    $item_x_link = flag_create_link('subscribe_'.$item_machine_type, $occur->entity_id);
    
    if($item_type == "Term"){ //A term has no node to display.
      $item_link = "user/subscriptions";
    }
    
    else{ //Drupal link type/ID
      $item_link = $occur->entity_type.'/'.$occur->entity_id;
    }
    
    $items[] = array(
      'name_id' => l($item_name, $item_link),
      'type' => t($item_type, array(), array('context' => 'gofast')),
      'x_link' => $item_x_link,
      'fid' => t($item_fid, array(), array('context' => 'gofast')),
      'machine_type' => $item_machine_type,
    );
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
 * @return
 *  An array of 0=>user;1=>frequency or NULL if there is no subscribed user
 */
function gofast_subscription_ui_api_subscribed_list($type, $eid, $nid = NULL){
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
        $query_frequency = db_query("SELECT flagging_id, flagging.entity_id, field_revision_field_frequency_".$type.".entity_id, field_frequency_".$type."_value FROM flagging INNER JOIN field_revision_field_frequency_".$type." ON flagging_id=field_revision_field_frequency_".$type.".entity_id WHERE flagging.flagging_id='".$subscription_item->flagging_id."'");
        //check permissions if subscription type is "user"
        if($type == "user"){
            if(node_access('view', node_load($nid), user_load($subscription_item->uid))){ //Disabled because we clear subscriptions before and it blocks some notifications
              $frequency = $query_frequency->fetchAll();
              $frequency_obj = ('field_frequency_'.$type.'_value');
              $users_subscribed[$i][0] = $subscription_item->uid;
              $users_subscribed[$i][1] = $frequency['0']->$frequency_obj;
              $i++;
            }
        }else{
             $frequency = $query_frequency->fetchAll();
              $frequency_obj = ('field_frequency_'.$type.'_value');
              $users_subscribed[$i][0] = $subscription_item->uid;
              $users_subscribed[$i][1] = $frequency['0']->$frequency_obj;
              $i++;
        }
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