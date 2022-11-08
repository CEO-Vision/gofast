<?php

/**
 * Implements hook_poll_info()
 *
 * @return array
 */
function gofast_kanban_poll_info() {

  $detect = new Mobile_Detect;
  //detect if the user_agent correspond to an old IE
  $IE_version = $detect->version('IE');
  if ($IE_version == "7.0" || $IE_version == "8.0" || $IE_version == "9.0" || $IE_version == "10.0" || $IE_version == "11.0") {
    return array();

  } else {
      $items['kanban_columns'] = array(
        'label' => 'Updated_kanban',
        'description' => 'Gathers whether the kanban is changed',
        'interval' => 2,
        // 'context' => TRUE,
        'selector' => '#ogkanban:visible, #gofastKanbanContainer:visible'
      );
      $items['kanban_tasks_updated'] = array(
        'label' => 'Updated_tasks',
        'description' => 'Gathers wether the kanban task is changed',
        'interval' => 5,
        'selector' => '#ogkanban:visible, #gofastKanbanContainer:visible'
      );

     return $items;
  }
}

/**
 * Set context for gofast kanban polling
 * @param $element
 *  The element in the polling.
 * @param $key
 *  The key for the polling's element
 * @param $value
 *  The value to assign
 *
 */
function gofast_kanban_set_context($element = FALSE, $key = NULL, $value = NULL) {
  
  $context = array('gofast_kanban' => array(
      $element => array(
          $key => $value
      )
  ));
  gofast_set_context($context);
}


/**
 * Set context for gofast kanban polling
 * @param $element
 *  The element in the polling.
 * @param $key
 *  The key for the polling's element
 * @param $value
 *  The value to assign
 *
 */
function gofast_kanban_set_tasks_context($element = FALSE, $key = NULL, $value = NULL) {

  $context = array('gofast_kanban_task' => array(
      $element => array(
          $key => $value
      )
  ));
 gofast_set_context($context);
}

/**
 * Implements hook_poll()
 */
function gofast_kanban_poll($poll_name, $poll_info, $context) {

  $timer_start = microtime(true);
// watchdog('gofast_kanban', '%name() START', array('%name' => __FUNCTION__), WATCHDOG_DEBUG);

  $commands = array();
  

  if (isset($context['mobile_nid']) && gofast_mobile_is_mobile_domain()) {
    $space_nid = $context['mobile_nid'];
    $node = node_load($space_nid, NULL, TRUE); 
  }else if(isset($context['nid']) &&  !gofast_mobile_is_mobile_domain()){
    $space_nid = $context['nid'];
    $node = node_load(gofast_kanban_get_space_kanban($space_nid)[0], NULL, TRUE);
  }else{
    return;
  }
  
  // l'id est la bonne, reste a verifier que le poll se passe bien -----------


  switch ($poll_name) {
    case 'kanban_columns':
      if ($node->type === 'kanban') {
      
        
        if( ! isset($context['gofast_kanban']['node']['kanban_columns']) || empty($context['gofast_kanban']['node']['kanban_columns'])){
          $old_kanban_columns = array_keys(gofast_kanban_get_columns($node));
        }else{
          $old_kanban_columns = $context['gofast_kanban']['node']['kanban_columns'];
        }
        
        $new_columns = array_keys(gofast_kanban_get_columns($node));
        $columns_moved = array_diff_assoc($new_columns, $old_kanban_columns);
        
        //columns were added or deleted
        if (count($new_columns) !== count($old_kanban_columns) /*&& count($old_kanban_columns) > 0*/) {
          
            gofast_kanban_set_context("node", "kanban_columns", $new_columns );
            $commands[] = gofast_command_toast_message(t('Columns were reloaded (due to column update)', array(), array('context' => 'gofast_kanban')), 'info');

            //reload board
            $commands[] = gofast_command_callback("Gofast.reloadKanbanFromPolling", array($node->nid));

          return $commands;

        // Columns were moved
        } else if ( count($columns_moved) > 0) {
          
          gofast_kanban_set_context("node", "kanban_columns", $new_columns );
          $commands[] = gofast_command_toast_message(t('Columns were reloaded (due to column moving)', array(), array('context' => 'gofast_kanban')), 'info');

          //reload board
          $commands[] = gofast_command_callback("Gofast.reloadKanbanFromPolling", array($node->nid));

          return $commands;

        } else {
          return;
        }
      } else {
        return;
      }
      break;

    case 'kanban_tasks_updated':  
       if ($node->type === 'kanban') {
                 
        $board_tasks = $context['gofast_kanban_task']['node']['kanban_tasks_updated'];
        $tasks_was_updated = FALSE;


        if (!isset($context['gofast_kanban_task']['node']['kanban_tasks_updated']) || empty($context['gofast_kanban_task']['node']['kanban_tasks_updated'])) {
          $board_tasks = gofast_kanban_count_tasks_per_column($node->nid);          
          gofast_kanban_set_tasks_context("node", "kanban_tasks_updated", $board_tasks);
          
          $commands[] = gofast_command_callback("Gofast.kanban_update_tasks", array($board_tasks));
          return $commands;
          
        } else {
  
          foreach ($board_tasks as $column_tid => $nb_tasks) {
            $new_tasks = gofast_kanban_count_tasks_per_column($node->nid);
            
            // Do not take into account old/deleted columns still presents in context
            if(! array_key_exists($column_tid, $new_tasks)){
              $tasks_was_updated = FALSE;
              break;
            }
            
            if ( $new_tasks[$column_tid] != $nb_tasks) {
              $tasks_was_updated = TRUE;
              break;
            }
             
          }

          if ($tasks_was_updated == TRUE) {
            $reloaded_task = gofast_kanban_count_tasks_per_column($node->nid);
            gofast_kanban_set_tasks_context("node", "kanban_tasks_updated", $reloaded_task);
            $commands[] = gofast_command_callback("Gofast.kanban_update_tasks", array($reloaded_task));
            $commands[] = gofast_command_toast_message(t('Cards were reloaded (due to card moved)', array(), array('context' => 'gofast_kanban')), 'info');
            //reload board
            $commands[] = gofast_command_callback("Gofast.reloadKanbanFromPolling", array($node->nid));

            return $commands;
          } else {
            return;
          }
        }
      } else {
        return;
      }
      break;
  }
  $timer_stop = microtime(true);
//watchdog('gofast_kanban', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_DEBUG);
}
