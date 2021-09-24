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
class gofast_views_handler_field_node_link_delete_modal extends views_handler_field_node_link {

  function render($values) {
    $nid = $this->get_value($values, 'nid');
    return theme('gofast_link_delete_modal', array('nid' => $nid)); //$this->render_link($options, $values);
  }

}