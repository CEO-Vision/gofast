<?php

/**
 * @file
 * Definition of views_handler_field_node_link_delete.
 */

/**
 * Field handler to present a link to delete a node with modal validation.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_node_link_edit_mode extends views_handler_field_node_link {
  
  function render($values) {
    $node = $this->get_value($values);
    return theme('gofast_link_edit_mode', array('node' => $node)); //$this->render_link($options, $values);
  }
}