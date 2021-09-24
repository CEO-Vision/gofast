<?php

/**
 * @file
 *
 * Gofast Field Handler.
 *  Last Modifier
 *
 * Renders a themed user picture corresponding to the last modifier of a given node.
 *
 * Here 'last modifier' means the author of the latest event among
 * - node creation (default fall back)
 * - node update
 * - node comment
 */
class gofast_views_handler_field_node_last_modifier extends views_handler_field_node_link {

  function render($values) {
    $output = '';


    $node = isset($values->_field_data['nid']['entity']) ?
            $values->_field_data['nid']['entity'] : node_load($values->nid);
    $nid = $node->nid;

    ## Query to get the last message event
    $query = new EntityFieldQuery();

    $query->entityCondition('entity_type', 'message')
    ->fieldCondition('field_target_id', 'value', $nid, '=');
    ## Get last message about the node
    $query_exe = $query->execute();

    $query_com = new EntityFieldQuery();

    $query_com->entityCondition('entity_type', 'message')
    ->fieldCondition('field_node_id', 'value', $nid, '=');
    ## Get last message about the comment in node
    $query_com_exe = $query_com->execute();

    ## Set timestamp of last node event if exists
    if(isset($query_exe['message'])){
      $mids = array_keys($query_exe['message']);
      $message_items = entity_load('message', $mids);
      $last_message = end($message_items);
      while($last_message->field_message_log['und']['0']['value'] === 'INVALID' && $last_message != FALSE){
        $last_message = prev($message_items);
      }
      $message_data_json = NULL;
      if(isset($last_message->field_message_log['und']['0']['value'])){
        $message_data_json = $last_message->field_message_log['und']['0']['value'];
      }
      $message_data_node = json_decode($message_data_json, TRUE);

      ## Get node last event timestamp
      if(isset($message_data_node['changed']['value'])){
        $node_timestamp = $message_data_node['changed']['value'];
      }
      else{
        $node_timestamp = $message_data_node['changed']['to'];
      }
    }
    else{
      ## No node event recorded
      $node_timestamp = 0;
    }

    ## Set timestamp of last comment in node event if exists
    if(isset($query_com_exe['message'])){
      $mids_com = array_keys($query_com_exe['message']);
      $message_items_com = entity_load('message', $mids_com);
      $last_message_com = end($message_items_com);
      while($last_message_com->field_message_log['und']['0']['value'] === 'INVALID' && $last_message_com != FALSE){
        $last_message_com = prev($message_items_com);
      }

      while(!gofast_message_ext_api_comment_is_valid($last_message_com->field_message_log['und']['0']['value']) && $last_message_com != FALSE){
        $last_message_com = prev($message_items_com);
      }

      $message_data_json_com = $last_message_com->field_message_log['und']['0']['value'];
      $message_data_com = json_decode($message_data_json_com, TRUE);

      ## Get comment last event timestamp
      if(isset($message_data_com['changed']['value'])){
        $com_timestamp = $message_data_com['changed']['value'];
      }
      else{
        $com_timestamp = $message_data_com['changed']['to'];
      }
    }
    else{
      ## No node event recorded
      $com_timestamp = 0;
    }

    ## Compare timestamp
    if($node_timestamp>$com_timestamp){
      $message_data = $message_data_node;
    }
    else{
      $message_data = $message_data_com;
    }


    ## Load the user
    if(isset($message_data['ruid']['value'])){
      if($message_data['ruid']['value'] != 0){
        $user_loaded = user_load($message_data['ruid']['value'], TRUE);
      }
    }
    if(isset($message_data['ruid']['to']) && !isset($user_loaded)){
      if($message_data['ruid']['to'] != 0){
        $user_loaded = user_load($message_data['ruid']['to'], TRUE);
      }
    }
    if(isset($message_data['uid']['value']) && !isset($user_loaded)){
      if($message_data['uid']['value'] != 0){
        $user_loaded = user_load($message_data['uid']['value'], TRUE);
      }
    }
    if(isset($message_data['uid']['to']) && !isset($user_loaded)){
      if($message_data['uid']['to'] != 0){
        $user_loaded = user_load($message_data['uid']['to'], TRUE);
      }
    }
    if(!isset($user_loaded)){
      $user_loaded = user_load($node->revision_uid, TRUE);
    }
    $uid = $user_loaded->uid;
    $account = user_load($uid);
    if ($account) {
      $output .= theme('user_picture', array('account' => $account));
    }

    return $output;
  }

}
