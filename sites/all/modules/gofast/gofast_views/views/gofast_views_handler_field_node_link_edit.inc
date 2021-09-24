<?php

/**
 * @file
 * Definition of views_handler_field_node_link_edit.
 */

/**
 * Field handler to present a link node edit.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_node_link_edit extends views_handler_field_node_link {
  
  function render($values) {
    $nid = $this->get_value($values, 'nid');
    return theme('gofast_link_edit', array('nid' => $nid)); //$this->render_link($options, $values);
  }
}
