<?php
/**
 * Field handler to present a link to the node.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_node_download_link extends views_handler_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
    $this->additional_fields['reference'] = array('table' => 'field_data_field_reference', 'field' => 'field_reference_value');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    if ($value = $this->get_value($values, 'type') == "alfresco_item"){
      $ref = $this->get_value($values, 'reference');
      return theme('gofast_download_link', array('reference' => $ref)); //$this->render_link($options, $values);
    }
  }
  
}