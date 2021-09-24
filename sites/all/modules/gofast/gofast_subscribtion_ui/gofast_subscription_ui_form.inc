<?php
/**
 * Create the form for 'frequency' field of the .module + AJAX request
 */

/**
 * Update frequency field of a subscription
 */
function gofast_subscription_ui_frequency_update($form, $form_state){
  $machine_type = $form_state['build_info']['args']['1']; //Get machine type used to build the request
  $frequency = $form_state['values']['frequency'];
  $fid = $form_state['values']['fid']; //Get the flag/subscription ID to reference
  
  db_update("field_revision_field_frequency_".$machine_type)
          ->fields(array("field_frequency_".$machine_type."_value" => $frequency))
          ->condition('entity_id', $fid)
          ->execute();
  return $form;
}

/**
 * Get frequency params for the requested flag(subscription) entery
 * 
 * Generate select form for frequency selection
 * 
 * @param $fid
 *  ID of the requested flag
 * 
 * @param $machine_type
 *  Machine type ('node, user, og, term...) of the requested flag
 * 
 * @return
 *  An array that contains a form
 */
function gofast_subscription_ui_frequency_form($form, &$form_state, $fid, $machine_type){
  //Query to select the frequency linked to the requested flag ID.
  $query = db_query("SELECT field_frequency_".$machine_type."_value FROM field_revision_field_frequency_".$machine_type." WHERE entity_id='".$fid."'");
  $default_frequency_o = $query->fetch();
  $field_freq = ('field_frequency_'.$machine_type.'_value');
  if(isset($default_frequency_o->$field_freq)){
    $default_frequency = $default_frequency_o->$field_freq;
  }
  else{
    $default_frequency = NULL;
  }
  $dropdown_frequency = array( //Options
    0 => t('Twice a day', array(), array('context' => 'gofast:subscription')),
    1 => t('Once a day', array(), array('context' => 'gofast:subscription')),
    2 => t('Once a week', array(), array('context' => 'gofast:subscription')),
    3 => t('Once a month', array(), array('context' => 'gofast:subscription')),
    4 => t('Instantly', array(), array('context' => 'gofast:subscription')),
  );
  $form['frequency'] =  array(
                          '#type'     => 'select',
                          '#options'  => $dropdown_frequency,
                          '#key_type' => 'associative',
                          '#default_value' => $default_frequency,
                          '#ajax' => array(
                                            'callback'  => 'gofast_subscription_ui_frequency_update',
                                            'wrapper'   => 'frequency'
                                          )
                        );
  $form['fid'] =  array(
                          '#type'     => 'hidden',
                          '#value'    => $fid,
                        );

  return $form;
}