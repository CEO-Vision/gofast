<?php

/**
 * @file
 * Definition of gofast_views_handler_filter_user_relationships.
 */

/**
 * Filter handler for the user's approved relationships with current user.
 *
 * @ingroup views_filter_handlers
 */
class gofast_views_handler_filter_user_relationships extends views_handler_filter_boolean_operator {
  function construct() {
    parent::construct();
    $this->value_value = t('Relationship with current user', array(), array('context' => 'gofast'));
  }

  function query() {
    $this->ensure_my_table();

    $field = $this->table_alias . '.' . $this->real_field . ' ';
    $or = db_or();
    if (!empty($this->value)) {
      $relationships = array_keys(gofast_user_load_relationships());
      $or->condition($field, $relationships, 'IN');

      $this->query->add_where($this->options['group'], $or);
    }
  }

// @todo:
// Declaration of views_handler_filter_user_relationships_type::value_submit()
// should be compatible with views_handler_filter::value_submit($form, &$form_state)
//  function value_submit($form, &$form_state) {
//    parent::construct();
//  }  
}
