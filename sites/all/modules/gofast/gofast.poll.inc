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
    'selector' => '#block-gofast-gofast-node-infos div'
  );
  $items['lock_action'] = array(
    'label' => 'Document lock',
    'description' => 'Gathers and set contextual actions on document',
    'interval' => 1,
    'context' => 'node',
    'selector' => '#breadcrumb-alt-lock'
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
    'selector' => '#breadcrumb-alt-comments'
  );
  if (gofast_mobile_is_mobile_domain()) {
    $items['comments_mobile'] = array(
      'label' => 'Comments Mobile',
      'description' => 'Gathers and set new comments for mobile version',
      'interval' => 2,
      'context' => 'node',
      'selector' => '#comments-container'
    );
    $items['metadata_mobile'] = array(
      'label' => 'Metadata update for mobile',
      'description' => 'Gathers and change metadata information for mobile',
      'interval' => 2,
      'context' => 'node',
      'selector' => '#gofast_mobile_node_info'
    );
  }
  $items['locations_paths_rebuild'] = array(
    'label' => 'locations paths rebuild',
    'description' => 'Rebuilds locations paths cache if needed',
    'interval' => 10,
    'context' => TRUE,
    'selector' => NULL
  );

    $items['workflows'] = array(
      'label' => 'Workflows',
      'description' => 'Check workflows count',
      'interval' => 2,
      'context' => TRUE,
      'selector' => ".updated-workflow"
    );
  if(module_exists("gofast_workflows")){ // for the community
    $items['workflows_document'] = array(
      'label' => 'Workflows for document',
      'description' => 'Check workflows count contextually to documents',
      'interval' => 2,
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

  if ($poll_name === 'locations_paths_rebuild') {
    //gofast_ztree_get_paths();
    /* global $user;
     watchdog("debug POLL cmis check emplacement", $user->uid);
     gofast_cmis_get_emplacements_cache($user->uid);*/
  }
  if ($poll_name === 'workflows') {
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
        $wf_badge = '<span class="updated-workflow unread_count badge badge-notify-menu badge-notify" style="visibility: visible;">' . $count . '</span>';
       }else{
        $wf_badge = '<span class="updated-workflow unread_count badge badge-notify-menu badge-notify">0</span>';
       }
       $commands[] = ajax_command_replace($poll_info['selector'], $wf_badge);
       if($_SESSION['bonita_init_load']){
           unset($_SESSION['bonita_init_load']);
       }else{
           $commands[] = gofast_command_toast_message(t("Your assigned tasks has been changed."));
           $commands[] = gofast_command_callback("Gofast.refreshDashboardTasksBlock");

           if(module_exists("gofast_workflows")){ // for the community
            //refresh rapiddashboard
            $commands[] = ajax_command_html("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer", gofast_workflows_dashboard_rapide());
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
         }
      }
      gofast_poll_set_context('workflows', 'tasks_progress', $old_tasks);


    }
  }

  if (!isset($context['nid']) ) {
      return $commands;
  }

  $node = node_load($context['nid'], NULL, TRUE);
  $old_node = (object) $context['entity'];

  if ($poll_name === 'lock_action' && ($node->type === 'alfresco_item')) {
    $current_lock = gofast_cmis_node_get_lock($node);
    if ($current_lock !== $old_node->cmis_lock_owner) {
      $new_node = node_load($node->nid);
      $node_lock_action = gofast_get_lock_action_node($node);

      if (gofast_mobile_is_mobile_domain()) { // poll du mobile pour les alfresco_item
        $commands[] = ajax_command_html('#gofast_mobile_node_info', gofast_mobile_get_node_info($new_node));
      } else {
      $commands[] = ajax_command_html('#block-gofast-gofast-node-infos', gofast_get_node_infos($new_node));
      }

      // We update the lock icon
      $commands[] = ajax_command_invoke($poll_info['selector'], 'replaceWith', array(theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-lock', 'buttons' => $node_lock_action))));
      // Also need to update title & node_info if lock has changed.
      $commands[] = ajax_command_replace('.breadcrumb-gofast', gofast_get_breadcrumb_ajax($new_node));

      $commands[] = gofast_command_toast_message(t("Node lock updated", array(), array('context' => 'gofast')));
      $new_node->cmis_lock_owner = $current_lock;
      $context['entity'] = $new_node;
      gofast_set_context($context);
    }
  }

  if($poll_name == "workflows_document"){
      if(isset($context['workflows_document'])){
          $node_workflow_action = gofast_get_workflow_action_node($node);
          $count = $node_workflow_action[0]['button-text'];
          if($count != $context['workflows_document']){
              $context['workflows_document'] = $node_workflow_action[0]['button-text'];
              gofast_set_context($context);
              $commands[] = gofast_command_callback("Gofast.refreshWorkflowIcon");
          }
      }
  }


  if (!in_array($poll_name, array('lock_action', 'comments', 'comments_mobile')) && $node->changed <= $old_node->changed) {
    return $commands;
  }

  switch ($poll_name) {
    case 'metadata':
      $new_node = node_load($node->nid);
      $commands[] = ajax_command_replace($poll_info['selector'], gofast_get_node_infos($new_node));
      $commands[] = ajax_command_replace("div.breadcrumb.gofast.breadcrumb-gofast", gofast_get_breadcrumb_ajax($new_node));
      //$commands[] = gofast_command_toast_message(t("Node metadata updated", array(), array('context' => 'gofast')));
      break;

    case 'metadata_mobile':
      $new_node = node_load($node->nid);
      $commands[] = ajax_command_replace('#gofast_mobile_node_info', "<div id='gofast_mobile_node_info'>".gofast_mobile_get_node_info($new_node).'</div>');
      $commands[] = ajax_command_replace("div.breadcrumb.gofast.breadcrumb-gofast", gofast_get_breadcrumb_ajax($new_node));
      $commands[]  = ajax_command_html('#gofast_mobile_node_actions', theme('gofast_mobile_node_actions', array('node' => $new_node)));
      //$commands[] = gofast_command_toast_message(t("Node metadata updated", array(), array('context' => 'gofast')));
      break;

    case 'title':
      $new_node = node_load($node->nid);
      if ($node->title !== $old_node->title) {
        $commands[] = ajax_command_replace($poll_info['selector'], array(gofast_get_breadcrumb_ajax($new_node)));
      }
      break;

    case 'comments':
      $new_node = node_load($node->nid);
      //$new_comments = gofast_get_node_new_comments($node);
      if ($old_node->comment_count !== $new_node->comment_count) {
        // Updating the comments counter (over node)
        $node_comments_actions = gofast_get_comments_actions_node($new_node);
        $commands[] = ajax_command_invoke($poll_info['selector'], 'replaceWith', array(theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-comments', 'buttons' => $node_comments_actions))));
        //$commands[] = gofast_command_toast_message(t("Node Comment Actions updated", array(), array('context' => 'gofast')));

        // Refreshing the comments content (under node)
        $comment_default_per_page = variable_get('comment_default_per_page_' . $new_node->type, 50);
        variable_set('comment_default_per_page_' . $new_node->type, 9999999);
        $comments = comment_node_page_additions($new_node);
        $comment_render = drupal_render($comments);
        variable_set('comment_default_per_page_' . $new_node->type, 1);
        $commands[] = ajax_command_html('#comments-container', $comment_render);

        // Refreshing the comments tree (right side)
        $commands[] = ajax_command_html('#block-gofast-gofast-node-comments-tree', gofast_comments_tab($new_node));

        //$commands[] = gofast_command_toast_message(t("Node Comments DOM updated", array(), array('context' => 'gofast')));
        $context['entity'] = $new_node;
        gofast_set_context($context);
        //$commands[] = gofast_command_toast_message(t("Node Comment Actions updated", array(), array('context' => 'gofast')));
      }
      break;

    case 'comments_mobile':
      $new_node = node_load($node->nid);
      if ($old_node->comment_count !== $new_node->comment_count) {
        //$commands[] = gofast_command_toast_message(t("Node Comment Actions updated", array(), array('context' => 'gofast')));

        // Refreshing the comments content (under node)
        $comment_default_per_page = variable_get('comment_default_per_page_' . $new_node->type, 50);
        variable_set('comment_default_per_page_' . $new_node->type, 9999999);
        $comments = comment_node_page_additions($new_node);
        $comment_render = drupal_render($comments);
        variable_set('comment_default_per_page_' . $new_node->type, 1);
        $commands[] = ajax_command_html('#comments-container', $comment_render);

        //$commands[] = gofast_command_toast_message(t("Node Comments DOM updated", array(), array('context' => 'gofast')));
        $context['entity'] = $new_node;
        gofast_set_context($context);
      }

      break;
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
