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
class gofast_views_handler_field_node_block_file_management extends views_handler_field_node_link {
  
  function render($values) {
    $node = $this->get_value($values);
    if($node == false){
      $node = node_load($values->nid);
    }
    return theme('gofast_block_file_management', array('node' => $node)); //$this->render_link($options, $values);
  }
}