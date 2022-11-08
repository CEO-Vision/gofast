<?php

/**
 * @file
 * Definition of gofast_views_handler_field_user_quick_actions.
 */

/**
 * Field handler to present a quick actions to perform on a user profiles.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_user_quick_actions extends views_handler_field_node_link {
  
  function render($values) {
    $user = $this->get_value($values);
    return theme('gofast_block_user_quick_actions', array('user' => $user));
  }
}