<?php
/**
 * Define my custom in_opeator
 */
class gofast_audit_handler_filter_custom_in_operator extends views_handler_filter_in_operator {
  // overwrite the get_value_options function.
  function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }
    
    $availables_values = gofast_audit_get_list_event_types();
    $this->value_options = $availables_values;
  }
}


?>