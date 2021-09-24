<?php

/**
 * @file
 * User Subscription Views integration.
 */
class gofast_views_handler_field_subscribe_user extends views_handler_field_node_link {

  function render($values) {
    $user = $this->get_value($values);
    return theme('gofast_subscribe_user', array('user' => $user));
  }
}
