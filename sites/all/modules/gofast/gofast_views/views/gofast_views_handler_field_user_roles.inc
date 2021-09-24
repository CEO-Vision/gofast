<?php

/**
 * @file
 * 
 *  Defines gofast_views_handler_field_user_roles.
 */

/**
 * Field handler to provide a list of roles a user belongs to.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_user_roles extends views_handler_field_prerender_list {
  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'users', 'field' => 'uid');
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['uid'];
  }

  function pre_render(&$values) {
    $uids = array();
    $this->items = array();    

    foreach ($values as $result) {
      $uids[] = $this->get_value($result, NULL, TRUE);
    }

    if ($uids) {
      $technicals = _gofast_user_technical_roles();
      $result = db_query(
        'SELECT u.uid, u.rid, r.name FROM {role} r INNER JOIN {users_roles} u ON u.rid = r.rid ' .
        'WHERE u.uid IN (:uids) AND r.name NOT IN (:tech) ORDER BY r.name',
        array(':uids' => $uids, ':tech' => $technicals)
      );
      foreach ($result as $role) {
        $this->items[$role->uid][$role->rid]['role'] = check_plain($role->name);
        $this->items[$role->uid][$role->rid]['rid'] = $role->rid;
        $this->items[$role->uid][$role->rid]['uid'] = $role->uid;
      }
    }
  }

  function render_item($count, $item) {
    $output = $item['role'];
    
    $perm = user_access('administer roles');
    $admin = $GLOBALS['user']->uid == GOFAST_USER_ADMINISTRATOR_ID && $item['uid'] != GOFAST_USER_ADMINISTRATOR_ID;
    
    if ($admin || $perm && $item['role'] != GOFAST_ROLE_ADMIN) {
      $attributes = array('attributes' => array('title' => $item['role'], 'class' => 'ctools-use-modal'));
      $output = l(t('Edit user roles'), "admin/user/{$item['uid']}/edit-roles/nojs", $attributes);
    }
    
    return $output;
  }

  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = t('The name of the role.', array(), array('context' => 'gofast'));
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = t('The role ID of the role.', array(), array('context' => 'gofast'));
  }

  function add_self_tokens(&$tokens, $item) {
    if (!empty($item['role'])) {
      $tokens['[' . $this->options['id'] . '-role' . ']'] = $item['role'];
      $tokens['[' . $this->options['id'] . '-rid' . ']'] = $item['rid'];
    }
  }
}
