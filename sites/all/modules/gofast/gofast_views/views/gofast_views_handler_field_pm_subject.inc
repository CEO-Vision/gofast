<?php

/**
 * Defines a field handler that renders private message subject.
 *
 * @ingroup views_field_handlers
 */
class gofast_views_handler_field_pm_subject extends views_handler_field_markup {

  /**
   * Constructor; calls to base object constructor.
   */
  function construct() {
    parent::construct();
    // Add fields to run token replacement when needed.
    $this->additional_fields['has_tokens'] = 'has_tokens';
    $this->additional_fields['mid'] = 'mid';
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    $value = $this->get_value($values);
    if ($value) {
      $value = decode_entities(check_plain($value));        
      if ($this->get_value($values, 'has_tokens') && ($mid = $this->get_value($values, 'mid'))) {
        // Apply internal token replacement.
        if ($privatemsg = privatemsg_message_load($mid, NULL, NULL, TRUE)) {
          $value = privatemsg_token_replace($value, array('privatemsg_message' => $privatemsg), array('privatemsg-show-span' => FALSE));
        }
      }
     // return l(t($value),  'gofast/nojs/messages/view/'.$this->get_value($values, 'pm_index_thread_id'), array('attributes' => array('class' => array('ctools-use-modal'))));
     return l(t($value),  'gofast/nojs/messages/view/'.$values->thread_id, array('attributes' => array('class' => array('ctools-use-modal ctools-modal-custom-style'))));    
      }
  }

}