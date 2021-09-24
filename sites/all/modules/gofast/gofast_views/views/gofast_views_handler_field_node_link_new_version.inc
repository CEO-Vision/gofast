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
class gofast_views_handler_field_node_link_new_version extends views_handler_field_node_link {

  function render($values) {
    if ($value = $this->get_value($values, 'type') == "alfresco_item"){
      $nid = $this->get_value($values, 'nid');
      $type = $this->get_value($values, 'type');
      return theme('gofast_link_new_version', array('nid' => $nid, 'type' => $type)); //$this->render_link($options, $values);
    }
  }
}