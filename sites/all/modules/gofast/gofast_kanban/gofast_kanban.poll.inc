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
function gofast_kanban_set_context($key = NULL, $value = NULL, $context_key = "gofast_kanban") {
  // we have to encode the value if it's an array, otherwise JS-side when the $.extend function will try to merge the settings it will extend the array values inside of replacing them
  if (is_array($value)) {
    $value = json_encode($value);
  }
  $context = array($context_key => array(
    $key => $value
  ));
  gofast_set_context($context);
}

// refreshes the entire kanban context for given node and returns a dummy command to force-trigger pollEnd and refresh the context client side as well
function gofast_kanban_reset_context($node) {
  $kanban_columns = array_keys(gofast_kanban_get_columns($node));
  $new_tasks = gofast_kanban_get_tasks($node);
  $new_checklists_progress = gofast_kanban_get_checklists_progress_by_board_tasks($new_tasks);
  gofast_kanban_set_context("kanban_columns", [$node->nid => $kanban_columns]);
  gofast_kanban_set_context("kanban_tasks_updated", [$node->nid => $new_tasks], "gofast_kanban_task");
  gofast_kanban_set_context("kanban_checklists_progress", [$node->nid => $new_checklists_progress], "gofast_kanban_checklist");
  $commands[] = ajax_command_replace(NULL, "");
  return $commands;
}

/**
 * Implements hook_poll()
 */
function gofast_kanban_poll($poll_name, $poll_info, $context) {
  $commands = array();

  if (isset($context['nid'])){
    $space_nid = $context['nid'];
    $node = node_load(gofast_kanban_get_space_kanban($space_nid)[0], NULL, TRUE);
  }else{
    return;
  }

  switch ($poll_name) {
    case 'kanban_columns':
      if ($node->type === 'kanban') {
      
        if(!isset($context['gofast_kanban']['kanban_columns']) || empty($context['gofast_kanban']['kanban_columns'])){
          // if the context is not set, set it for the first time
          return gofast_kanban_reset_context($node);
        }else{
          $old_kanban_columns = json_decode($context['gofast_kanban']['kanban_columns'], TRUE);
          $old_kanban_columns_nid = reset(array_keys($old_kanban_columns));
          $old_kanban_columns = reset(array_values($old_kanban_columns));
          // context is wrong: reset it
          if ($old_kanban_columns_nid != $node->nid) {
            return gofast_kanban_reset_context($node);

          }
        }
        $new_columns = array_keys(gofast_kanban_get_columns($node));
        $columns_moved = array_diff_assoc($new_columns, $old_kanban_columns);
        
        //columns were added or deleted
        if (count($new_columns) !== count($old_kanban_columns)) {
            gofast_kanban_set_context("kanban_columns", [$node->nid => $new_columns]);
            $commands[] = gofast_command_toast_message(t('Columns were reloaded (due to column update)', array(), array('context' => 'gofast_kanban')), 'info');

            //reload board
            $commands[] = gofast_command_callback("Gofast.reloadKanbanFromPolling", array($node->nid));

          return $commands;

        // Columns were moved
        } else if ( count($columns_moved) > 0) {
          gofast_kanban_set_context("kanban_columns", [$node->nid => $new_columns]);
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

        // set context if not set
        if (!isset($context['gofast_kanban_task']['kanban_tasks_updated']) || !isset($context['gofast_kanban_checklist']['kanban_checklists_progress'])) {
          return gofast_kanban_reset_context($node);
        }
        $board_tasks = json_decode($context['gofast_kanban_task']['kanban_tasks_updated'], TRUE);
        $board_tasks_nid = reset(array_keys($board_tasks));
        $board_tasks = reset(array_values($board_tasks));
        // context is wrong: reset it
        if ($board_tasks_nid != $node->nid) {
          return gofast_kanban_reset_context($node);
        }
        $old_checklists_progress = json_decode($context['gofast_kanban_checklist']['kanban_checklists_progress'], TRUE);
        $old_checklists_progress = reset(array_values($old_checklists_progress));
        $new_tasks = gofast_kanban_get_tasks($node);
        $new_checklists_progress = gofast_kanban_get_checklists_progress_by_board_tasks($new_tasks);
        $tasks_were_updated = FALSE;
        $checklists_were_updated = FALSE;

        // board-aware tasks update check
        foreach ($board_tasks as $column_tid => $tasks) {
          $nb_tasks = count($tasks);
          // Do not take into account old/deleted columns still presents in context
          if(!array_key_exists($column_tid, $new_tasks)){
            $tasks_were_updated = FALSE;
            break;
          }
          if (count($new_tasks[$column_tid]) != $nb_tasks) {
            $tasks_were_updated = TRUE;
            break;
          }
        }

        // checklist progress check
        foreach($new_checklists_progress as $key => $progress){
          if($old_checklists_progress[$key] != $progress) {
            $checklists_were_updated = TRUE;
            break;
          }
        }

        // update if needed
        if ($tasks_were_updated == TRUE) {
          $reloaded_task =  gofast_kanban_get_tasks($node);
          gofast_kanban_set_context("kanban_tasks_updated", [$node->nid => $reloaded_task], "gofast_kanban_task");
          $commands[] = gofast_command_toast_message(t('Cards were reloaded (due to card moved)', array(), array('context' => 'gofast_kanban')), 'info');
          //reload board
          $commands[] = gofast_command_callback("Gofast.reloadKanbanFromPolling", array($node->nid));

          return $commands;
        } else if ($checklists_were_updated == TRUE) {
          $reloaded_task =  gofast_kanban_get_tasks($node);
          $reloaded_checklist = gofast_kanban_get_checklists_progress_by_board_tasks($reloaded_task);
          gofast_kanban_set_context("kanban_tasks_updated", [$node->nid => $reloaded_task], "gofast_kanban_task");
          gofast_kanban_set_context("kanban_checklists_progress", [$node->nid => $reloaded_checklist], "gofast_kanban_checklist");
          $commands[] = gofast_command_toast_message(t('Cards were reloaded (due to progress update)', array(), array('context' => 'gofast_kanban')), 'info');
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
  }
}
