<?php

/**
 * @file
 * Definition of gofast_views_handler_field_user_directories_user_gofast_role.
 */

/**
 * Field handler to provide simple renderer that allows using a themed user link.
 *
 * @ingroup views_field_handlers
 */
class gofast_userlist_og_handler_field_userlist_directories_userlist_number_admins extends views_handler_field_node_link
{
  function render($values)
  {
    $userlist = $this->get_value($values);
    $members_number = count(gofast_userlist_get_administrators($userlist->field_userlist_ulid[LANGUAGE_NONE][0]['value'])) + 1;
    return theme('gofast_userlist_display_number_members', array('text' => $members_number));
  }
}
