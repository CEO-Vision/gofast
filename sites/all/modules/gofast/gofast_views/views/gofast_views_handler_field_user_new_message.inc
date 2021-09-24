<?php

/**
 * @file
 * User Relationships Views integration.
 * Show column with link to change approval status.
 */
class gofast_views_handler_field_user_new_message extends views_handler_field_node_link {

  function render($values) {
    $user = $this->get_value($values);
    return theme('gofast_user_new_message', array('user' => $user)); //$this->render_link($options, $values);
  }
}
