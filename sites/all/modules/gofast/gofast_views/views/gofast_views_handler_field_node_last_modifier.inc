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

    $nid = $values->nid;
    $revision_uid = db_select("node_revision", "nr")->fields("nr", array("uid"))->condition("nr.nid", $nid)->execute()->fetchCol()[0];

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
      $message_data_node = gofast_message_get_last_message($mids);

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
      $message_data_com = gofast_message_get_last_message($mids_com);

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
        $uid = $message_data['ruid']['value'];
      }
    }
    if(isset($message_data['ruid']['to']) && !isset($uid)){
      if($message_data['ruid']['to'] != 0){
        $uid = $message_data['ruid']['to'];
      }
    }
    if(isset($message_data['uid']['value']) && !isset($uid)){
      if($message_data['uid']['value'] != 0){
        $uid = $message_data['uid']['value'];
      }
    }
    if(isset($message_data['uid']['to']) && !isset($uid)){
      if($message_data['uid']['to'] != 0){
        $uid = $message_data['uid']['to'];
      }
    }
    if(!isset($uid)){
      $revision_uid = db_select("node_revision", "nr")->fields("nr", array("uid"))->condition("nr.nid", $nid)->execute()->fetchCol()[0];
      $uid = $revision_uid;
    }
    $users_infos = gofast_get_properties_user_by_uid_or_u_name($uid, NULL, ["uid", "name", "status", "picture"], TRUE);
    if ($users_infos) {
      $output .= theme('user_picture', array('account' => $users_infos, 'dimensions' => 40));
    }

    return $output;
  }

}
