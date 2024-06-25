<?php

function gofast_kanban_form_kanban_node_form_alter(&$form, &$form_state) {
  unset($form['prevent_notify']);
}

/**
 * Add a new column to the given Kanban
 * @param type $kanban_nid
 */
function gofast_kanban_board_column_add($kanban_nid) {

  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $kanban_nid), WATCHDOG_DEBUG);

  $newColumnName = filter_xss(filter_input(INPUT_POST, 'label'));
  $key = 10; // Should be higher than default column
  $newColumnId = gofast_kanban_column_create($newColumnName, $key);
  
  //add the newly created column to Kanban
  $kanban = node_load($kanban_nid);
  $kanban->field_board_columns[LANGUAGE_NONE][]= array('tid' => $newColumnId);
  node_save($kanban);

  print json_encode(['label' => $newColumnName, 'id' => $newColumnId]);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}


/**
 * Update the label of a column
 * ! WARNING ! Default columns would not be modified, new column will be created instead
 * @param type $kanban_nid
 * @param type $column_id
 */
function gofast_kanban_board_column_update($kanban_nid, $column_id) {
  

  $timer_start = microtime(true);
  //watchdog('gofast_kanban', '%name() START : nid=[%nid] $column_id=[%column_id]', array('%name' => __FUNCTION__, '%nid' => $kanban_nid, '%column_id' => $column_id), WATCHDOG_DEBUG);

  $newColumnName = filter_xss(filter_input(INPUT_POST, 'label'));

  if (gofast_kanban_is_default_column($column_id) === TRUE) {
    //Should create a brand new column to avoid overriding the default one
    //Get the position of the current column in Kanban
    $key = gofast_kanban_board_get_column_index($kanban_nid, $column_id);

    $newColumnId = gofast_kanban_column_create($newColumnName, $key);
    //add the newly created column to Kanban
    $kanban = node_load($kanban_nid);
    $kanban->field_board_columns[LANGUAGE_NONE][$key] = array('tid' => $newColumnId);
    node_save($kanban);

    //Then move all tasks to the new column
    gofast_kanban_board_column_move_all_tasks($kanban, $column_id, $newColumnId);
  } else {
    //Simply rename the taxonomy term
    $term = taxonomy_term_load($column_id);
    $term->name = $newColumnName;
    taxonomy_term_save($term);
  }
  
  $timer_stop = microtime(true);
  
  drupal_json_output(['newColumnName' => $newColumnName, 'newColumnId' => isset($newColumnId) ? strval($newColumnId) : FALSE]);

//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  
}

/**
 * Move column in kanban
 * @param type $kanban_nid
 * @param type $column_id
 * @param int $newPosition
 */
function gofast_kanban_board_column_move($kanban_nid, $column_id, $newPosition) {

  
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] ', array('%name' => __FUNCTION__, '%nid' => $kanban_nid), WATCHDOG_DEBUG);

  // $oldPosition = filter_input(INPUT_POST, 'old_index');
  
  $kanban = node_load($kanban_nid);
  $node_wrapper = entity_metadata_wrapper('node', $kanban);
  $columns = $node_wrapper->field_board_columns->value();

  $column_to_move = NULL;
  $column_to_move_index = NULL;
  
  foreach($columns as $key => $col){
    if($col->tid == $column_id){
      $column_to_move = $col;
      $column_to_move_index = $key;
    }
  }
  
  //keep column to move
  // $column_to_move= $columns[$oldPosition];
  
  //build new column array
  $new_columns = array();
  // newPosision min value is 1 from kanban plugin 
  $new_columns[$newPosition - 1 ] = $column_to_move;
  
  // unset($columns[$oldPosition]);
  unset($columns[$column_to_move_index]);
  $reordered_columns = array_values($columns);
  foreach($reordered_columns as $key => $column){
    if($key < $newPosition - 1){
      $new_columns[$key] = $column;
    }else{
       $new_columns[$key+1] = $column;
    }
  }
     
  $node_wrapper->field_board_columns->set($new_columns);
  $node_wrapper->save();

  $timer_stop = microtime(true);

// return $new_columns;

//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
}




function gofast_kanban_board_column_delete($kanban_nid, $column_id) {
   
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] column_id=[%column_id]', array('%name' => __FUNCTION__, '%nid' => $kanban_nid, '%column_id' => $column_id), WATCHDOG_DEBUG);
  
  $kanban = node_load($kanban_nid);
  $node_wrapper = entity_metadata_wrapper('node', $kanban);
  $columns = $node_wrapper->field_board_columns->value();
    
  //Delete all task in the column to remove
  gofast_kanban_board_column_delete_all_tasks($kanban_nid, $column_id);
  
  //Delete column
  foreach($columns as $key => $column){
    if($column->tid == $column_id){
      unset($columns[$key]); // removed column
    }
  }
  $reaodered_columns = array_values($columns);
     
  $node_wrapper->field_board_columns->set($reaodered_columns);
  $node_wrapper->save();
 
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}


/**
 * Delete all task in the given column
 * @param type $kanban_nid
 * @param type $column_id
 */
function gofast_kanban_board_column_delete_all_tasks($kanban_nid, $column_id){
  
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : nid=[%nid] column_id=[%column_id]', array('%name' => __FUNCTION__, '%nid' => $kanban_nid, '%column_id' => $column_id), WATCHDOG_DEBUG);

  $tasks = gofast_kanban_get_tasks(node_load($kanban_nid), array( 0 => array('id' => $column_id) ) );
  
  foreach($tasks[$column_id] as $task ){
    gofast_kanban_task_delete($task['nid']);
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}

/**
 * Move all task of ta given kanban from a column to another
 * @param type $kanban
 * @param type $column_id
 * @param type $new_column_id
 */
function gofast_kanban_board_column_move_all_tasks($kanban, $column_id, $new_column_id) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : kanban_nid=[%nid] column_id=[%column_id] new_column_id=[%new_column_id] ', array('%name' => __FUNCTION__, '%nid' => $kanban->nid, '%column_id' => $column_id,'%new_column_id' => $new_column_id), WATCHDOG_DEBUG);

  //get all task
  $tasks_nids = gofast_kanban_get_tasks($kanban, array(0 => array('id' => $column_id)), FALSE);

  if(! empty($tasks_nids[$column_id])){
    $update_query = db_update('field_data_field_task_column');
    $update_query->expression('field_task_column_tid', $new_column_id);
    $update_query->condition('entity_type', 'node')
        ->condition('bundle', 'task')
        ->condition('entity_id', array_values($tasks_nids), 'IN');

    $update_query->execute();
  }

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}


/**
 * 
 * @param type $name
 * @param type $key
 * @return type
 */
function gofast_kanban_column_create($name, $key){
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START : name=[%arg_name] key=%key ', array('%name' => __FUNCTION__, '%arg_name' => $name, '%key' => $key), WATCHDOG_DEBUG);

  $tid = NULL;
  
  $vocab = taxonomy_vocabulary_machine_name_load('columns');
  $term = (object) array(
          'name' => $name,
            'description' => $name,
            'vid' => $vocab->vid,
            'weight' => $key,
            'field_default_column' => 0
  );
  taxonomy_term_save($term);

  $tid = $term->tid;

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);

  return $tid;
}

/**
 * Return the last column index for the given kanban
 * @param type $kanban_nid
 * @return type $max_index
 */
function gofast_kanban_board_get_max_column_index($kanban_nid) {
  $timer_start = microtime(true);
//watchdog('gofast_kanban', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $max_index = 0;
  $kanban = node_load($kanban_nid); 
  $max_index = array_key_last($kanban->field_board_columns[LANGUAGE_NONE]);

  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
  
  return $max_index;
}
