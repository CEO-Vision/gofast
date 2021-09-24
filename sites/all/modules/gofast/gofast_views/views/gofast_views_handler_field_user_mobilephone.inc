<?php

/**
 * @file
 * User Relationships Views integration.
 * Show column with link to change approval status.
 */
class gofast_views_handler_field_user_mobilephone extends views_handler_field_node_link {

  function render($values) {
    $node = $this->get_value($values);
    return theme('gofast_user_mobilephone', array('user' => $node)); //$this->render_link($options, $values);
  }
}
