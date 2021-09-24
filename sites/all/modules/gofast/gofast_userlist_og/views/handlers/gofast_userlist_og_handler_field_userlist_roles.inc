<?php

/**
 * Field handler to provide a list of OG roles of a userlist.
 */
class gofast_userlist_og_handler_field_userlist_roles extends og_handler_field_prerender_list {

  function query() {
    // Get a user table we can relate to.
    // @todo: Make the used user relationship configurable.
    foreach ($this->query->relationships as $alias => $info) {
      if ($info['table'] == 'gofast_userlists') {
        $userlist_table_alias = $alias;
      }
      elseif ($info['table'] == 'og_membership') {
        $og_membership_table_alias = $alias;
      }

      if (!empty($userlist_table_alias) && !empty($og_membership_table_alias)) {
        break;
      }
    }

    // If there is a users table present use its uid. Else, skip this field.
    if (!empty($userlist_table_alias)) {
      $this->aliases['ulid'] = $this->query->add_field($userlist_table_alias, 'ulid');
    }
    if (!empty($og_membership_table_alias)) {
      $this->aliases['group_type'] = $this->query->add_field($og_membership_table_alias, 'group_type');
    }
    parent::query();
  }

  function pre_render(&$values) {
    if (!isset($this->aliases['ulid']) || !isset($this->aliases['group_type'])) {
      return;
    }

    $list = array();
    $this->items = array();
    foreach ($values as $value) {
      if ($value->{$this->aliases['ulid']} && $value->{$this->field_alias}) {
        $list[] = array(
          'ulid' => $value->{$this->aliases['ulid']},
          'group_type' => $value->{$this->aliases['group_type']},
          'gid' => $value->{$this->field_alias},
        );
      }
    }

    // Array of all the role IDs we will need to get a role name.
    $all_rids = array();
    if ($list) {
      foreach ($list as $value) {     
        $rids = gofast_userlist_og_get_userlist_roles($value['group_type'], $value['gid'], $value['ulid'], FALSE);
        foreach ($rids as $rid => $role) {
          $this->items[$value['gid']][$value['ulid']][$rid]['rid'] = $rid;
          $this->items[$value['gid']][$value['ulid']][$rid]['role'] = $role;
        }
      }
    }
  }

  function render_item($rid, $item) {
    return check_plain($item['role']);
  }

  function advanced_render($values) {
    if (isset($this->aliases['ulid'])) {
      return parent::advanced_render($values);
    }
  }

  function document_self_tokens(&$tokens) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = t('The name of the role.');
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = t('The role ID of the role.');
  }

  function add_self_tokens(&$tokens, $item) {
    $tokens['[' . $this->options['id'] . '-role' . ']'] = $item['role'];
    $tokens['[' . $this->options['id'] . '-rid' . ']'] = $item['rid'];
  }
}
