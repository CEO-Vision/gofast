<?php

/**
 * @file
 *  Gofast Event administration interface.
 */


/**
 * Event Log settings form.
 * @todo : add enable/disable event log option.
 */
function gofast_event_settings_form($form, &$form_state) {
    watchdog('test', 'test 0 ');
  // Enable/Disable Event Log
  $form['status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event log settings', array(), array('context' => 'gofast:gofast_event')),
    '#weight' => -10,
    '#collapsible' => TRUE,
    '#description' => t('Enable Event Log to record node events and provide users with detailed informations.', array(), array('context' => 'gofast:gofast_event')),
  );
  $form['status']['gofast_event_log_status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Event Log', array(), array('context' => 'gofast:gofast_event')),
    '#default_value' => variable_get('gofast_event_log_status', FALSE),
  );

  // Content types to be selected for event log.
  $form['type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enabled content types', array(), array('context' => 'gofast:gofast_event')),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#states' => array('disabled' => array(':input[name="gofast_event_log_status"]' => array('checked' => FALSE))),
    '#description' => t('Check the content types for which event log will be available.', array(), array('context' => 'gofast:gofast_event'))
  );
  $form['type']['gofast_event_node_types_enabled'] = array(
    '#type' => 'checkboxes',
    '#options' => node_type_get_names(),
    '#default_value' => $defaults = gofast_event_node_types_enabled(),
    '#description' => t('Note : Global node fields such as %title will be automatically processed, while attached fields (bundle specific) have to be set foreach selected content types.', array('%title' => 'title'), array('context' => 'gofast:gofast_event'))
  );
  
  $form['data'] = array(
    '#type' => 'hidden',
    '#value' => $defaults
  );

  $form = system_settings_form($form);
  $form['#validate'][] = 'gofast_event_settings_form_validate';
  $form['#submit'][] = 'gofast_event_settings_form_submit';
  watchdog('test', 'test 1 ');
  return $form;
}

function gofast_event_settings_form_validate($form, &$form_state) {
  debug($form_state, '', true);
}

/**
 * Form submit handler for Gofast Event Log settings.
 */
function gofast_event_settings_form_submit($form, &$form_state) {
  $selected = array_filter($form_state['values']['gofast_event_node_types_enabled']);
  $original = $form_state['values']['data'];
  // Check for changes and rebuild the {menu_router} table if needed.  
  if ($selected !== $original) {
    // Attach field to and/or detach from the selected bundle(s).
    gofast_event_create_field_instances(array_diff($selected, $original));
    gofast_event_delete_field_instances(array_diff($original, $selected));
    menu_rebuild();
  }
}

/**
 * Event Log fields settings form.
 */
function gofast_event_fields_form($form, &$form_state, $bundle_name = NULL) {
  if (empty($bundle_name)) return;
  
  $fields_enabled = gofast_event_fields_enabled($bundle_name);
  
  // Build options array from $bundle_name's attached fields.
  $options = field_info_instances('node', $bundle_name);
  
  // Remove the field options (prevents self processing).
  unset ($options[GOFAST_EVENT_LOG_FIELD_NAME]);
  
  foreach ($options as $fieldname => &$infos) {
    // Only keep the field label.
    $infos = $infos['label'];
  }
  
  $form[$bundle_name] = array(
    '#type' => 'fieldset',
    '#title' => $bundle_name . ' : ' . t('Enabled fields', array(), array('context' => 'gofast:gofast_event')),
    '#weight' => -5,
    '#collapsible' => TRUE,
    '#states' => array('disabled' => array(':input[name="gofast_event_log_status"]' => array('checked' => FALSE))),
    '#description' => t('Check the fields for which changes have to be recorded.', array(), array('context' => 'gofast:gofast_event'))
  );

  $form[$bundle_name]['gofast_event_fields_enabled'] = array(
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => $fields_enabled,
    '#description' => t('Each time a node is saved, changes for the selected fields will be processed and appended to the Event Log field.', array(), array('context' => 'gofast:gofast_event'))
  );
  
  $form['data'] = array(
    '#type' => 'hidden',
    '#value' => array(
      'fields' => gofast_event_fields_enabled(),
      'bundle_name' => $bundle_name
    )
  );
  
  $form['#submit'] = array('gofast_event_fields_form_submit');
  return system_settings_form($form);
}

/**
 * Form submit handler for Gofast Event Log fields settings.
 */
function gofast_event_fields_form_submit($form, &$form_state) {
  // Merge enabled fields with defaults before submitting.
  $form_state['values']['gofast_event_fields_enabled'] = array(
    $form_state['values']['data']['bundle_name'] => $form_state['values']['gofast_event_fields_enabled']
  ) + $form_state['values']['data']['fields'];
}


/**
 * Wrapper function that creates field instances of the given field foreach 
 * bundles passed in param.
 * 
 * @param $bundles 
 *  An array of node bundles.
 * @param $field_name
 *  A string holding the name of the field to attach.
 */
function gofast_event_create_field_instances($bundles = array(), $field_name = GOFAST_EVENT_LOG_FIELD_NAME) {
  // Attach field to bundles if not already.
  foreach ($bundles as $bundle_name => $label) {
    if (field_read_instance('node', $field_name, $bundle_name, array('include_inactive' => true))) {
      // An existing instance is already binded to the given bundle.
      continue;
    }
    // ...otherwise, create an instance of the field and bind it to the bundle.
    $instance = gofast_event_field_instance_prepare($field_name, $bundle_name, $label);
    field_create_instance($instance);
  }
}


/**
 * Wrapper function that delete field instances of the given field foreach 
 * bundles passed in param.
 * 
 * @param $bundles 
 *  An array of node bundles.
 * @param $field_name
 *  A string holding the name of the field to attach.
 */
function gofast_event_delete_field_instances($bundles = array(), $field_name = GOFAST_EVENT_LOG_FIELD_NAME) {
  foreach ($bundles as $bundle_name => $info) {
    // Marks the field instance and its data for deletion.
    if ($instance = field_read_instance('node', $field_name, $bundle_name, array('include_inactive' => true))) {
      // Get the fields' info array for the given content type.
      $instance = field_info_instance('node', $field_name, $bundle_name);
    }
  }
}

/**
 * Helper that returns a default field instance structure.
 * @todo : hook_field_info() ...
 */
function gofast_event_field_instance_prepare($field_name, $bundle_name, $label = '') {
  return array(
    'field_name' => $field_name,
    'entity_type' => 'node',
    'bundle' => $bundle_name,
    'label' => $label,
    'description' => '',
    'settings' => array('text_processing' => 0),
    'required' => FALSE,
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'type' => 'hidden'
      )
    )
  );
}