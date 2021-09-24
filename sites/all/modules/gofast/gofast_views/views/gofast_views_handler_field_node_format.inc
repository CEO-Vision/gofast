<?php
/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_node_format extends views_handler_field_node_link {
//  function construct() {
//    parent::construct();
//    $this->additional_fields['type'] = 'type';
//    $this->additional_fields['reference'] = array('table' => 'field_data_field_reference', 'field' => 'field_reference_value');
//    $this->additional_fields['format_tid'] = array('table' => 'field_data_field_format', 'field' => 'field_format_tid');
//  }
//
//  function query() {
//    $this->ensure_my_table();
//    $this->add_additional_fields();
//  }

  function render($values) {
    $node = $this->get_value($values);
    if($node == false){
      $node = node_load($values->nid);
    }
    return theme('gofast_node_icon_format', array('node' => $node)); //$this->render_link($options, $values);
  }

}