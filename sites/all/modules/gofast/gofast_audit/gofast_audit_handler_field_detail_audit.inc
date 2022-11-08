<?php
/**
 * @file
 *
 */

/**
 * Field handler to display details on modifications from audit table
 *
 * @ingroup views_field_handlers
 */
class gofast_audit_handler_field_detail_audit extends views_handler_field {
  function construct() {
    parent::construct();
    //$this->additional_fields['nid'] = array('table' => 'node', 'field' => 'nid');
  }

  function option_definition() {
    $options = parent::option_definition();

//    $options['use_title'] = array('default' => FALSE);
//    $options['display_as_link'] = array('default' => TRUE);

    return $options;
  }

  /**
   * Provide link to the page being visited.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
//    $form['use_title'] = array(
//      '#title' => t('Use node title as filename'),
//      '#type' => 'checkbox',
//      '#default_value' => !empty($this->options['use_title']),
//    );
//
//    $form['display_as_link'] = array(
//      '#title' => t('Display as download link'),
//      '#type' => 'checkbox',
//      '#default_value' => !empty($this->options['display_as_link']),
//    );
  }

 function render($values) {
     //on formate joliment les modifications, en se basant sur la fonction utilisée lors des notifications
    $data['events_log'][0] = unserialize(rawurldecode($values->ceo_vision_audit_details));
    $data['update-index'] = 0;
     drupal_add_js(drupal_get_path('module', 'gofast_message_ext') . '/gofast_message_ext.js');
    $string_return = gofast_audit_view_node_update_events_log($data);
    //$string_return['details'] = "TODO";
    return $string_return['details'];
  }
}