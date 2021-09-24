<?php

/**
 * @file
 * 
 *  Defines gofast_views_handler_field_user_og_roles.
 */

/**
 * Field handler to provide a list of OG roles a user belongs to.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_user_og_roles extends views_handler_field_prerender_list {

  function construct() {
    parent::construct();
    $this->additional_fields['uid'] = array('table' => 'users', 'field' => 'uid');
  }

  function option_definition() {
    $options = parent::option_definition();

    $i = 0;
    foreach (array(GOFAST_OG_ROLE_ADMIN, GOFAST_OG_ROLE_STANDARD, GOFAST_OG_ROLE_READ_ONLY) as $role) {
      if ($i === 0) {
        $opts = array('default' => TRUE, 'bool' => TRUE);
      }
      else {
        $opts = array('default' => FALSE, 'bool' => TRUE);
      }
      $options[$role] = $opts;
      $i++;
    }

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $i = 0;
    foreach (array(GOFAST_OG_ROLE_ADMIN, GOFAST_OG_ROLE_STANDARD, GOFAST_OG_ROLE_READ_ONLY) as $role) {
      $default_val = FALSE;
      if ($i === 0) {
        $default_val = TRUE;
      }
      $form[$role] = array(
        '#title' => $role,
        '#type' => 'checkbox',
        '#default_value' => $default_val,
        '#description' => t('If checked, it will set this role as selected role for render', array(), array('context' => 'gofast')),
        '#fieldset' => 'more',
      );
      $i++;
    }

    parent::options_form($form, $form_state);
  }

  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['uid'];
  }

  function pre_render(&$values) {
    $uids = array();
    $this->items = array();

    if ($this->options[GOFAST_OG_ROLE_ADMIN]) {
      $role_names = array(GOFAST_OG_ROLE_ADMIN);
    }
    else if ($this->options[GOFAST_OG_ROLE_STANDARD]) {
      $role_names = array(GOFAST_OG_ROLE_STANDARD);
    }
    else if ($this->options[GOFAST_OG_ROLE_READ_ONLY]){
      $role_names = array(GOFAST_OG_ROLE_READ_ONLY);
    }
    else{
      $role_names = array(GOFAST_OG_ROLE_ADMIN, GOFAST_OG_ROLE_STANDARD, GOFAST_OG_ROLE_READ_ONLY);
    }
    
    foreach ($values as $result) {
      $uids[] = $this->get_value($result, NULL, TRUE);
    }

    if ($uids && count($this->view->args) > 0) {
      $gid = $this->view->args[0];
      if ($gid) {
        $group_type = 'node'; // it's bad but we don't use any other OG-entity).
        $space = entity_load_single($group_type, $gid);

        // Check if we should use defaults or overriden roles.
        $og_role_gid = og_is_group_default_access($group_type, $gid) ? 0 : $gid;

        // As soon as an OG membership argument is present we know the current
        // values are the corresponding uids (OG members), so we don't have to 
        // test user membership at this point, just collect roles. However we 
        // need to join og membership table to grab ogm ids.
        $og_infos = array();
        foreach($role_names as $role_name){
          $query = db_select('og_role', 'ogr');
          $query->innerJoin('og_users_roles', 'ogur', 'ogr.rid = ogur.rid');
          $query->innerJoin('og_membership', 'ogm', 'ogm.etid = ogur.uid');

          $og_infos = array_merge($og_infos, $query
                  ->fields('ogr', array('rid', 'name'))
                  ->fields('ogur', array('uid'))
                  ->fields('ogm', array('id'))
                  ->condition('ogr.group_type', $group_type, '=')
                  ->condition('ogr.group_bundle', $space->type, '=')
                  ->condition('ogr.name', $role_name, '=')
                  ->condition('ogur.uid', $uids, 'IN')
                  ->condition('ogur.gid', $gid, '=')
                  ->condition('ogm.entity_type', 'user', '=')
                  ->condition('ogm.gid', $gid, '=')
                  ->orderBy('rid')
                  ->execute()
                  ->fetchAll()
          );}

          foreach ($og_infos as $info) {
            $this->items[$info->uid][$info->rid]['role'] = $info->name;
            $this->items[$info->uid][$info->rid]['rid'] = $info->rid;
            $this->items[$info->uid][$info->rid]['uid'] = $info->uid;
            $this->items[$info->uid][$info->rid]['og_title'] = $space->title;
            $this->items[$info->uid][$info->rid]['ogm_id'] = $info->id;
          }
          
          //GOFAST-5111 We need to check if all users has been affected to a role. If it's not the case we need to
          //override the result of the queries and affect them a read only role
         foreach($uids as $uid){
              if(!empty($uid) && !isset($this->items[$uid])){
                  $rid = $this->options[GOFAST_OG_ROLE_READ_ONLY];
                  $this->items[$uid][$rid]['role'] = "read only member";
                  $this->items[$uid][$rid]['rid'] = $rid;
                  $this->items[$uid][$rid]['uid'] = $uid;
                  $this->items[$uid][$rid]['og_title'] = $space->title;
                  $ogmid = db_query("select * from og_membership where gid=" . $gid . " AND etid=" . $uid . " AND entity_type='user'")->fetchAll()[0];
                  $this->items[$uid][$rid]['ogm_id'] = $ogmid->id;
                  $this->items[$uid][$rid]['not_pending'] = TRUE;
              }
          }
          
      }
    }
  }

  function render_item($count, $item) {
    global $user;    
    if (!isset($this->view->args[0])) {
      return;
    }
    
    //$output = $item['og_title'] . ' : ';
    $output = '';
    
    $gid = $this->view->args[0];
    $perm = in_array(GOFAST_OG_ROLE_ADMIN, gofast_og_get_user_final_roles_for_space('node', $gid, $user->uid), true);
    $target_role = gofast_og_get_user_roles($gid, $item['uid']); //gofast_og_get_user_final_roles_for_space('node', $gid, $item['uid']);
    $isPending = ((!isset($target_role) || empty($target_role)) && !$item['not_pending']);
    $admin = $GLOBALS['user']->uid == GOFAST_USER_ADMINISTRATOR_ID && $item['uid'] != GOFAST_USER_ADMINISTRATOR_ID;

   // if ($admin || $perm && $item['role'] != GOFAST_OG_ROLE_ADMIN) {
    if ($perm || $GLOBALS['user']->uid == 1){
      if($isPending){
        $output .= theme('gofast_link_generic', array(
          'text' => t('Accept', array(), array('context' => 'gofast')),
          'href' => "/spaces/nojs/node/{$gid}/admin/people/grant-membership/{$item['ogm_id']}",
          'link_class' => 'btn btn-sm ctools-use-modal',
          'icon_class' => "fa fa-check"
        ));
        $output .= theme('gofast_link_generic', array(
          'text' => t('Deny', array(), array('context' => 'gofast')),
          'href' => "/spaces/nojs/node/{$gid}/admin/people/deny-membership/{$item['ogm_id']}",
          'link_class' => 'btn btn-sm ctools-use-modal',
          'icon_class' => "fa fa-times"
        ));
      }
      else {
        $output .= theme('gofast_link_generic', array(
          'text' => t('Edit role', array(), array('context' => 'gofast')),
          'link_id' => "edit-role-" . $item['ogm_id'],
          'link_class' => 'btn btn-sm ctools-use-modal',
          'href' => "/spaces/nojs/node/{$gid}/admin/people/edit-membership/{$item['ogm_id']}",
          'icon_class' => "fa fa-cog"
        ));
        //$output .= l(t('Edit role'), "spaces/nojs/node/{$gid}/admin/people/edit-membership/{$item['ogm_id']}", $attributes);
      }
    }
    else {
      $output .= '<a class="btn btn-sm" style="visibility: hidden;">' . t('Cannot edit', array(), array('context' => 'gofast')) . '</a>'; //$item['role'];
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
