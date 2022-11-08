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
 * Update comments frequency field of a subscription
 */
function gofast_subscription_ui_comments_frequency_update($form, $form_state){
  $machine_type = $form_state['values']['machine_type'];
  $frequency = $form_state['values']['frequency_comment'];
  $fid = $form_state['values']['fid']; //Get the flag/subscription ID to reference
  
  $result = db_update("field_revision_field_frequency_comment")
          ->fields(array("field_frequency_comment_value" => $frequency))
          ->condition('entity_id', $fid)
          ->execute();
  if (!!$result === FALSE) {
    $result = db_insert("field_revision_field_frequency_comment")
          ->fields(array(
            "entity_type" => "flagging",
            "bundle" => "subscribe_" . $machine_type,
            "deleted" => 0,
            "entity_id" => $fid,
            "revision_id" => $fid,
            "language" => LANGUAGE_NONE,
            "delta" => 0,
            "field_frequency_comment_value" => $frequency
            ))
          ->execute();
  }
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
function gofast_subscription_ui_frequency_form($form, &$form_state, $fid, $machine_type, $frequency = FALSE){
  //Query to select the frequency linked to the requested flag ID.
  if (!$frequency) {
    $query = db_query("SELECT field_frequency_".$machine_type."_value FROM field_revision_field_frequency_".$machine_type." WHERE entity_id='".$fid."'");
    $default_frequency_o = $query->fetch();
    $field_freq = ('field_frequency_'.$machine_type.'_value');
    $frequency = $default_frequency_o->$field_freq ?? NULL;
  }
  
  $dropdown_frequency = gofast_subscriptions_ui_get_frequency_dropdown();
  
  $form['frequency'] =  array(
    '#type'     => 'select',
    '#options'  => $dropdown_frequency,
    '#key_type' => 'associative',
    '#default_value' => $frequency,
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
function gofast_subscription_ui_comments_frequency_form($form, &$form_state, $fid, $machine_type, $frequency = FALSE){
  //Query to select the frequency comment linked to the requested flag ID.
  if (!$frequency) {
    $query_com = db_query("SELECT field_frequency_comment_value FROM field_revision_field_frequency_comment WHERE entity_id='".$fid."'");
    $default_frequency_com_o = $query_com->fetch();
    $frequency_com = $default_frequency_com_o->field_frequency_comment_value ?? NULL;
  }
  
  $dropdown_frequency_comment = gofast_subscriptions_ui_get_frequency_dropdown();
                        
  $form['frequency_comment'] =  array(
    '#type'     => 'select',
    '#options'  => $dropdown_frequency_comment,
    '#key_type' => 'associative',
    '#default_value' => $frequency_com,
    '#ajax' => array(
      'callback'  => 'gofast_subscription_ui_comments_frequency_update',
      'wrapper'   => 'comments_frequency'
    )
  );
                        
  $form['fid'] =  array(
    '#type'     => 'hidden',
    '#value'    => $fid,
  );
  $form['machine_type'] =  array(
    '#type'     => 'hidden',
    '#value'    => $machine_type,
  );

  return $form;
}

/**
 * Get frequency params for the requested flag(subscription) entery
 * 
 * Generate select form for frequency selection in the global actions for selected elements
 * 
 * @return
 *  An array that contains a form
 */
function gofast_subscription_ui_frequency_placeholder_form($form, &$form_state){
  
  $dropdown_frequency = gofast_subscriptions_ui_get_frequency_dropdown();
                        
  $form['frequency_mass_actions'] =  array(
    '#type'     => 'select',
    '#options'  => $dropdown_frequency + [10 => t("Please select", array(), array("context" => "gofast:gofast_subscription"))],
    '#key_type' => 'associative',
    '#default_value' => 10,
  );
  
  return $form;
}

function gofast_subscriptions_ui_get_frequency_dropdown(){
  return [
    0 => t('Twice a day', array(), array('context' => 'gofast:subscription')),
    1 => t('Once a day', array(), array('context' => 'gofast:subscription')),
    2 => t('Once a week', array(), array('context' => 'gofast:subscription')),
    3 => t('Once a month', array(), array('context' => 'gofast:subscription')),
    4 => t('Instantly', array(), array('context' => 'gofast:subscription')),
    5 => t('Never', array(), array('context' => 'gofast:subscription')),
  ];
}
