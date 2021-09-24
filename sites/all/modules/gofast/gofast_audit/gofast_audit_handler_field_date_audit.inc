<?php
/**
 * @file
 *
 */

/**
 * Field handler to display date on modifications from audit table
 *
 * @ingroup views_field_handlers
 */
class gofast_audit_handler_field_date_audit extends views_handler_field {
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
  //Language settings
  global $user;
  if($user->language == "en"){
    $format = "m/d/Y - H:i:s";
  }else{
    $format = "d/m/Y - H:i:s";
  }

    if($values->ceo_vision_audit_event_type == "new_node"){
	if(!empty($values->node_ceo_vision_audit_nid)){
	    $created = format_date(strtotime(gofast_cmis_item_get(gofast_cmis_node_get_item_id(node_load($values->node_ceo_vision_audit_nid)), TRUE)->properties['cmis:creationDate']), 'custom', $format);
	}
        if(!empty($created)){
            return $created;
        }else{
            return format_date($values->ceo_vision_audit_timestamp, 'custom', $format);
        }
    }else{
        return format_date($values->ceo_vision_audit_timestamp, 'custom', $format);
    }
  }
}
