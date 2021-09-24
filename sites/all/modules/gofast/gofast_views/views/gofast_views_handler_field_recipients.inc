<?php

/**
 * @file
 * User Relationships Views integration.
 * Show column with link to change approval status.
 */
class gofast_views_handler_field_recipients extends views_handler_field_node_link {

  function render($values) {
    global $user;

    $thread = privatemsg_thread_load($values->thread_id);
    $output = '';

    $ids = array();
    if ($thread['participants']) {
      
      $participants = array_values($thread['participants']);
      
      if (($n = count($participants) - 1) > 2) {
        $output = '<span class="participant-count">' . $n . ' ' . t('participants', array(), array('context' => 'gofast')) . '</span><div class="gofast-participants">' . $output . '</div>';
        return $output;
      }
      else{
        foreach ($participants as $key => $account) {
          if (in_array($account->uid, $ids)) continue;
          $output .= theme('user_picture', array('account' => $account, 'popup' => FALSE, 'dimensions' => array(
                  'width' => '20px',
                  'height' => '20px',
              )));
          $ids[] = $account->uid;
        }
      }
      
      $output = '<div style="display:inline-flex;">' . $output . '</div>';
      
    }
    return $output;
    
  }
  
}