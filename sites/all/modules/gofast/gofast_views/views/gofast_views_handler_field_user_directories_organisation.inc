<?php

/**
 * @file
 * Definition of gofast_views_handler_field_user_directories_organisation.
 */

/**
 * Field handler to provide simple renderer that allows using a themed user link.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_user_directories_organisation extends views_handler_field_node_link
{
  function render($values)
  {
    $account = $this->get_value($values);
    return theme('gofast_user_display_user_organisation', array('user' => $account));
  }
}
