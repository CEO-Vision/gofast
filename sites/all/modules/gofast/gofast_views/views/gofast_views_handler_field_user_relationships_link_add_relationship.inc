<?php

/**
 * @file
 * User Relationships Views integration.
 * Show column with link to change approval status.
 */
class gofast_views_handler_field_user_relationships_link_add_relationship extends views_handler_field_node_link {
//  function construct() {
//    parent::construct();
////    $this->additional_fields['requestee_id'] = 'requestee_id';
////    $this->additional_fields['requester_id'] = 'requester_id';
////    $this->additional_fields['rid']          = 'rid';
////    $this->additional_fields['approved']     = 'approved';
//    $this->additional_fields['requestee_id'] = array('table' => 'user_relationships', 'field' => 'requestee_id');
//    $this->additional_fields['requester_id'] = array('table' => 'user_relationships', 'field' => 'requester_id');
//    $this->additional_fields['rid'] = array('table' => 'user_relationships', 'field' => 'rid');
//    $this->additional_fields['approved'] = array('table' => 'user_relationships', 'field' => 'approved');
//  }
//
//  function query() {
//    $this->ensure_my_table();
//    $this->add_additional_fields();
//    
//    
//    
//  }

  function render($values) {

    global $user;
    $usr = $this->get_value($values);
    $relationships =  user_relationships_load(array('between' => array($user->uid, array($usr->uid) )));
   
    
//    $rid = $relationships->rid;
    if (!$user->uid) {
      return;
    }
    if (empty($relationships)){
      return theme('gofast_link_add_relationship', array('uid' => $usr->uid));
    }
    else {
//      debug($relationships);
      if (reset($relationships)->requestee_id == $user->uid) {
        if (reset($relationships)->approved == 1) {
          return theme('gofast_user_relationships_remove_link', array('uid' => reset($relationships)->requester_id, 'rid' => reset($relationships)->rid));
        }
        else {
          return theme('gofast_user_relationships_pending_request_approve_link', array('uid' => reset($relationships)->requestee_id, 'rid' => reset($relationships)->rid)) .
          ' | ' .
          theme('gofast_user_relationships_pending_request_disapprove_link', array('uid' => reset($relationships)->requestee_id, 'rid' => reset($relationships)->rid));
        }
      }
      else if (reset($relationships)->requester_id == $user->uid) {
        if (reset($relationships)->approved == 1) {
          return theme('gofast_user_relationships_remove_link', array('uid' => reset($relationships)->requester_id, 'rid' => reset($relationships)->rid));
        }
        else {
          return theme('gofast_user_relationships_pending_request_cancel_link', array('uid' => reset($relationships)->requester_id, 'rid' => reset($relationships)->rid));
        }
      }
    }
  }
}
