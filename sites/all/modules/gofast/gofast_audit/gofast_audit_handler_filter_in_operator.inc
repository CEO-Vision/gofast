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
class gofast_views_handler_filter_date extends views_handler_filter_date {
  public function op_between($field) {
    global $user;
    if($user->language == "en"){
      $format = "m/d/Y";
    }else{
      $format = "d/m/Y";
    }
    $a = (DateTime::createFromFormat($format, $this->value['min']))->getTimestamp();
    $b = (DateTime::createFromFormat($format, $this->value['max']))->getTimestamp();
    // if user inputed two times the same date, we assume he was looking for a 24h timespan
    if ($a == $b) {
      $b += 86400;
    }

    // This is safe because we are manually scrubbing the values. It is
    // necessary to do it this way because $a and $b are formulas when using an
    // offset.
    $operator = strtoupper($this->operator);
    $this->query->add_where_expression($this->options['group'], "$field $operator $a AND $b");
  }
}

?>
