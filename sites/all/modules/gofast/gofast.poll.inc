<?php

/**
 * Implements hook_poll_info()
 *
 * @return array
 */
function gofast_poll_info() {
  $items =  array();
  $items['metadata'] = array(
    'label' => 'Metadata update',
    'description' => 'Gathers and change metadata information',
    'interval' => 2,
    'context' => 'node',
    'selector' => '#document__infotab'
  );
  $items['lock_action'] = array(
    'label' => 'Document lock',
    'description' => 'Gathers and set contextual actions on document',
    'interval' => 2,
    'context' => 'node',
    'selector' => '#breadcrumb-alt-actions'
  );
  $items['title'] = array(
    'label' => 'Title',
    'description' => 'Gathers and set document title',
    'interval' => 1,
    'context' => 'node',
    'selector' => '.breadcrumb-gofast'
  );
  $items['comments'] = array(
    'label' => 'Comments',
    'description' => 'Gathers and set new comments',
    'interval' => 2,
    'context' => 'node',
    'selector' => '#comments-container'
  );

  $items['workflows'] = array(
    'label' => 'Workflows',
    'description' => 'Check workflows count',
    'interval' => 2,
    'context' => TRUE,
    'selector' => "#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .unread_count"
  );

  if(module_exists("gofast_workflows")){ // for the community
    $items['workflows_document'] = array(
      'label' => 'Workflows for document',
      'description' => 'Check workflows count contextually to documents',
      'interval' => 6,
      'context' => TRUE,
      'selector' => NULL
    );
  }

  return $items;
}

/**
 * Implements hook_poll()
 */
function gofast_poll($poll_name, $poll_info, $context) {
  $commands = array();

  if ($poll_name === 'workflows') {
    $commands = gofast_poll_handle_workflows($commands, $poll_info, $context);
  }

  //Next pollings are only intended to run for nodes
  if (!isset($context['nid']) ) {
      return $commands;
  }

  $node = node_load($context['nid'], NULL, TRUE);
  $old_node = (object) $context['entity'];

  if($poll_name == "workflows_document"){
    $commands = gofast_poll_handle_workflows_document($commands, $poll_info, $context, $old_node, $node);
  }

  if ($poll_name === 'lock_action' && ($node->type === 'alfresco_item')) {
    $commands = gofast_poll_handle_lock($commands, $poll_info, $context, $old_node, $node);
  }

  //Some of next pollings are not intended to run if the node hasn't been changed
  if (!in_array($poll_name, array('comments', 'comments_mobile')) && $node->changed <= $old_node->changed) {
    return $commands;
  }

  switch ($poll_name) {
    case 'metadata':
      $commands = gofast_poll_handle_metadata($commands, $poll_info, $context, $old_node, $node);
      break;

    case 'title':
      $commands = gofast_poll_handle_title($commands, $poll_info, $context, $old_node, $node);
      break;

    case 'comments':
      $commands = gofast_poll_handle_comments($commands, $poll_info, $context, $old_node, $node);
      break;
  }

  return $commands;
}

function gofast_poll_handle_metadata($commands, $poll_info, $context, $old_node, $node){
  $new_node = node_load($node->nid);
  $commands[] = ajax_command_html($poll_info['selector'], gofast_metadata_get_node_infos($new_node));
  if(gofast_og_is_space($new_node, TRUE)){
    $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($new_node->nid, ['return' => TRUE, 'only_title' => FALSE, 'manage_locations' => TRUE]));
  }else{
    $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($new_node->nid, ['return' => TRUE, 'only_title' => FALSE, 'show_title' => FALSE, 'manage_locations' => TRUE]));
  }
  $commands[] = ajax_command_replace('.breadcrumb-gofast-show-title', gofast_breadcrumb_display_breadcrumb($new_node->nid, ['return' => TRUE, 'only_title' => FALSE, 'show_title' => TRUE]));
  $commands[] = gofast_command_toast_message(t("Node metadata updated", array(), array('context' => 'gofast')));

  $node_contextual_actions = gofast_get_contextual_actions_node($node);
  $commands[] = ajax_command_invoke("#breadcrumb-alt-actions", 'replaceWith', array(theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-actions', 'buttons' => $node_contextual_actions))));

  $history_tab = gofast_render_historyByNode_async($new_node, FALSE);
  $commands[] = ajax_command_invoke("#document__historytab", 'html', array($history_tab));
  $commands[] = ajax_command_html('#ctools-add-js', "<script type='text/javascript'>jQuery('.tooltip').remove();</script>");
  return $commands;
}

function gofast_poll_handle_title($commands, $poll_info, $context, $old_node, $node){
  $new_node = node_load($node->nid);
  if ($node->title !== $old_node->title) {
    if(gofast_og_is_space($new_node, TRUE)){
      $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($new_node->nid, ['return' => TRUE, 'only_title' => FALSE, 'manage_locations' => TRUE]));
    }else{
      $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($new_node->nid, ['return' => TRUE, 'only_title' => FALSE, 'show_title' => FALSE, 'manage_locations' => TRUE]));
    }
    if($node->type == "forum") {
      $commands[] = ajax_command_html('#forum-header-forum-title', $node->title);
      $commands[] = ajax_command_html('.forum-explorer-single .forum-explorer-element-name a', $node->title);
    }
    if($node->type == "article") {
      $commands[] = ajax_command_html('.gofastHighlightedWikiArticle', $node->title);
    }

    $node_contextual_actions = gofast_get_contextual_actions_node($node);
    $commands[] = ajax_command_invoke("#breadcrumb-alt-actions", 'replaceWith', array(theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-actions', 'buttons' => $node_contextual_actions))));

  }
  return $commands;
}

function gofast_poll_handle_comments($commands, $poll_info, $context, $old_node, $node){
  $new_node = node_load($node->nid);
  //$new_comments = gofast_get_node_new_comments($node);
  if ($old_node->comment_count !== $new_node->comment_count) {
    // Refreshing the comments content (under node)
    $comment_render = gofast_render_allCommentsByNode_async($new_node, TRUE);
    $commands[] = ajax_command_html('#comments-container', $comment_render);
    $context['entity'] = $new_node;
    gofast_set_context($context);
  }
  return $commands;
}

function gofast_poll_handle_workflows_document($commands, $poll_info, $context, $old_node, $node){

  $node_workflow_action = gofast_get_workflow_action_node($node);
  $count = $node_workflow_action[0]['button-text'];
  if($count != $context['workflows_document']){
    if($context['workflows_document'] !== null){
      $initial_loading = FALSE; //context already loaded once
    }else{
      $initial_loading = TRUE;
    }
    
    $old_count = $context['workflows_document'] ;
    $context['workflows_document'] = $count;
    gofast_set_context($context);
    $commands[] = ajax_command_replace(".gofast-task-notifiation",  '<span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation">'.$count.'</span>');
    if( $initial_loading == FALSE && $old_count != $context['workflows_document'] ){  
        $commands[] = gofast_command_callback("Gofast.loadtasks", array($node->nid));
    }
  }
  return $commands;
}

function gofast_poll_handle_lock($commands, $poll_info, $context, $old_node, $node){
  $current_lock = gofast_cmis_node_get_lock($node);
  //sometime, $old_node->cmis_lock_owner is equal to ["nolocked","nolocked"], I don't know why
  if(count($old_node->cmis_lock_owner) > 1){
     $old_cmis_lock_owner = array_shift($old_node->cmis_lock_owner);
  }else{
    $old_cmis_lock_owner = $old_node->cmis_lock_owner;
  }
  if ($current_lock !== $old_cmis_lock_owner ) {
    $node_contextual_actions = gofast_get_contextual_actions_node($node);
    if (gofast_mobile_is_mobile_domain()) { // poll du mobile pour les alfresco_item
      $commands[] = ajax_command_html('#gofast_mobile_node_info', gofast_mobile_get_node_info($node));
    } else {
      $commands[] = ajax_command_html('#document__infotab', gofast_metadata_get_node_infos($node));
      if (count(module_implements("extra_metadata")) >= 1) {
        $commands[] = ajax_command_html('#document__extra_metadata_tab', gofast_render_extraMetadataByNode_async($node,TRUE));
        $commands[] = ajax_command_replace('#node-tabsHeader', gofast_render_extraMetadataTabsByNode_async($node, TRUE));
      }
    }

    // We update the lock icon
    $commands[] = ajax_command_invoke($poll_info['selector'], 'replaceWith', array(theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-actions', 'buttons' => $node_contextual_actions))));
    // Also need to update title & node_info if lock has changed.
    if(gofast_og_is_space($node, TRUE)){
      $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($node->nid, ['return' => TRUE, 'only_title' => FALSE, 'manage_locations' => TRUE]));
    }else{
      $commands[] = ajax_command_replace('.breadcrumb-gofast-full', gofast_breadcrumb_display_breadcrumb($node->nid, ['return' => TRUE, 'only_title' => FALSE, 'show_title' => FALSE, 'manage_locations' => TRUE]));
    }
    $commands[] = ajax_command_replace('.breadcrumb-gofast-show-title', gofast_breadcrumb_display_breadcrumb($node->nid, ['return' => TRUE, 'only_title' => FALSE, 'show_title' => TRUE]));

    $commands[] = gofast_command_toast_message(t("Node lock updated", array(), array('context' => 'gofast')));
    $node->cmis_lock_owner = $current_lock;
    $context['entity'] = $node;
    gofast_set_context($context);
  }
  return $commands;
}

function gofast_poll_handle_workflows($commands, $poll_info, $context){
  $old_count = $context['block_poll']['workflows']['count'];
  $old_tasks = $context['block_poll']['workflows']['tasks_progress'];

 $count = 0;
 if(module_exists("gofast_workflows")){ // for the community
    $count = gofast_workflows_get_number_pending_tasks();
  }else{
    global $user;
    $count = count(gofast_kanban_get_user_tasks($user->uid, FALSE));
  }

  if($count != $old_count){ //Count has changed, push this change
    if($count > 0){
     $wf_badge = '<span class="label label-sm font-weight-bold label-danger position-absolute unread_notifications unread_count " style="top: 7px; right: 7px;">'.$count.'</span>';
    }else{
     $wf_badge = '<span class="label label-sm font-weight-bold label-danger position-absolute unread_notifications unread_count " style="top: 7px; right: 7px;">0</span>';
    }
    $commands[] = ajax_command_replace($poll_info['selector'], $wf_badge);
    if($_SESSION['bonita_init_load']){
        unset($_SESSION['bonita_init_load']);
    }else{
        if($old_count != ""){
            $commands[] = gofast_command_toast_message(t("Your assigned tasks has been changed."));
            $commands[] = gofast_command_callback("Gofast.refreshDashboardTasksBlock");
        }

        if(module_exists("gofast_workflows")){ // for the community
         //refresh rapiddashboard
         $commands[] = ajax_command_html("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer", gofast_workflows_dashboard_rapide());
         $commands[] = ajax_command_html('#ctools-add-js',"<script type='text/javascript'>
       jQuery('#refresh-lightdashboard-document').click();
       </script>"
        );
        }
    }
    gofast_poll_set_context('workflows', 'count', $count);
  }else{
    global $user;
    $progress_changed = FALSE;
    $tasks = gofast_kanban_get_user_tasks($user->uid, TRUE);
    foreach($tasks as $task){
       if($old_tasks["kanban-" . $task['nid']] != $task['progress']){
         $progress_changed = TRUE;
       }
       $old_tasks["kanban-" . $task['nid']] = $task['progress'];
   }

   if($progress_changed){
      $commands[] = ajax_command_html($poll_info['selector'], array($count));
      $commands[] = gofast_command_toast_message(t("Your assigned tasks has been changed."));

      if(module_exists("gofast_workflows")){ // for the community
       //refresh rapiddashboard
       $commands[] = ajax_command_html("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer", gofast_workflows_dashboard_rapide());
       $commands[] = ajax_command_html('#ctools-add-js',"<script type='text/javascript'>
       jQuery('#refresh-lightdashboard-document').click();
       </script>"
        );
       
      }
   }
   gofast_poll_set_context('workflows', 'tasks_progress', $old_tasks);
 }

 return $commands;
}

/**
 * Set context for generic polling
 * @param $element
 *  The element in the polling.
 * @param $key
 *  The key for the polling's element
 * @param $value
 *  The value to assign
 *
 */
function gofast_poll_set_context($element = FALSE, $key = NULL, $value = NULL){
    $block_context = array(
      'block_poll' => array(
        $element => array(
          $key => $value
        )
      )
    );

  gofast_set_context($block_context);

}
