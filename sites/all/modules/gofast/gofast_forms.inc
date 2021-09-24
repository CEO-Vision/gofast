<?php
/*
 * Forms used in global context
 */

/**
 * Generate select form my.cnf configuration
 * 
 * @return
 *  An array that contains a form
 */
function gofast_configure_mycnf_form($form, &$form_state){
  $form = array();
  
  //First, we get and parse the my.cnf file
  $my_cnf = file("/etc/my.cnf");
  
  //Make sure that we properly retrieved the file
  //TODO
  
  //Parse the file
  foreach($my_cnf as $line){
    //Check if line is a comment
    if(substr($line, 0, 1) === "#"){
      continue;
    }
    //Check if line is a section delcaration
    if(substr($line, 0, 1) === "["){
      continue;
    }
    //Check if line is empty
    if(trim($line) == ""){
      continue;
    }
    
    //Now, we know we have to take the line in consideration
    //Trim the file and set an array keyed with the param and valued with the param value
    $line = str_replace(" ", "", $line);
    $line = explode("=", $line);
    $key = $line[0];
    $value = $line[1];
    //Finally, set these value in the form
    $form[$key] = array(
      '#title'  => $key,
      '#type'     => 'textfield',
      '#default_value' => $value,
    );
  }
  
  //Submit button
  $form['submit'] = array(
    '#suffix' => t('Please be aware this action involves a mySQL restart.'),
    '#type' => 'submit',
    '#value' => t('Apply'),
  );
  
  return $form;
}

/**
 * Submit the my.cnf configuration
 * 
 * @return
 *  An array that contains a form
 */
function gofast_configure_mycnf_form_submit($form, &$form_state){
  $output_file = "";
  $output_file = "[mysqld]" . "\n";
  
  //Clean the values
  form_state_values_clean($form_state);
  
  //Retrieve all the fields and values
  $input_parsed = $form_state['values'];
  
  //Restitute the file
  foreach($input_parsed as $input_k => $input_v){
    $output_file .= $input_k . '=' . $input_v . "\n";
  }
  
  //Write the file
  file_put_contents("/var/www/d7/sites/default/files/my.cnf", $output_file);
}