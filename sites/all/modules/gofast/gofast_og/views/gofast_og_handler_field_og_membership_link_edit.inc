<?php

/**
 * @file
 * 
 *  Defines Gofast OG handler for edit membership operation.
 */


/**
 * @override og_handler_field_og_membership_link_edit 
 */


/**
 * Field handler to present a link to edit membership.
 *
 * @ingroup views_field_handlers
 */
class gofast_og_handler_field_og_membership_link_edit extends views_handler_field_entity {

  function construct() {
    parent::construct();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    $options['destination'] = array('default' => FALSE, 'bool' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display', array(), array('context' => 'gofast:gofast_og')),
      '#default_value' => $this->options['text'],
    );
    $form['destination'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use destination', array(), array('context' => 'gofast:gofast_og')),
      '#description' => t('Add destination to the link', array(), array('context' => 'gofast:gofast_og')),
      '#default_value' => $this->options['destination'],
      '#fieldset' => 'more',
    );
    parent::options_form($form, $form_state);
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $value = $this->get_value($values, 'id');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  function render_link($data, $values) {
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['html'] = TRUE;

    // Ensure user has access to edit this membership.
    $og_membership = $this->get_value($values);
    $group_type = $og_membership->group_type;
    $gid = $og_membership->gid;
    $group = entity_load_single($group_type, $gid);

    if (!og_user_access($group_type, $gid, 'manage members') || $group->uid == $og_membership->etid) {
      return;
    }
    
    // Prevent Administrator membership to be edited.
    if ($og_membership->etid == GOFAST_USER_ADMINISTRATOR_ID) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit', array(), array('context' => 'gofast'));
    unset($this->options['alter']['fragment']);

    if (!empty($this->options['destination'])) {
      $this->options['alter']['query'] = drupal_get_destination();
    }

    // Modal link
    $this->options['alter']['path'] = "spaces/nojs/{$group_type}/{$gid}/admin/people/edit-membership/{$og_membership->id}";
    $this->options['alter']['link_class'] = 'ctools-use-modal btn btn-sm btn-primary glyphicon glyphicon-edit';
    $this->options['alter']['alt'] = ucfirst($text);

    return ' ';
  }
}
