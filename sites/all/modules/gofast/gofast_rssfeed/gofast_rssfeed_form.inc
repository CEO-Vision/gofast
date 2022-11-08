<?php
/**
 * Implement HOOk_Form()
 */
function gofast_admin_rssfeed_settings_form() {
    $form = array();
  
    $form['rssfeed']['lis_rssfeed'] = array(
        '#type' => 'fieldset',
        '#title' => t('Current list of RSS Feed', array(), array('context' => 'gofast:gofast_rssfeed')),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#tree' => TRUE, //Make the form elements keep their tree
        '#theme' => 'gofast_rssfeed_container_list_rssfeed'
    );    
    
  return $form;
}