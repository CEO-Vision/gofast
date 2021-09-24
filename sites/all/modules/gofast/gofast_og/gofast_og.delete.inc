<?php

/**
 * @file
 * 
 * Provides options to user when deleting OG Node : 
 *  - Delete all the content associated with group.
 *  - Delete the group and make the content public.
 *  - Move all content in a specific destination group.
 */

define('OG_DELETE_NOTHING', 0);
define('OG_DELETE_ORPHANS', 1);
define('OG_DELETE_MOVE_NODES', 2);
define('OG_DELETE_MOVE_NODES_MEMBERSHIPS', 3);

/**
 * Implementation of hook_form_FORM_ID_alter() for node_delete_confirm.
 */
function gofast_og_form_node_delete_confirm_alter(&$form, &$form_state) {
  if (og_is_group_type('node', $form['#node']->type)) {
    $node = $form['#node'];

    // Get referencable spaces (for move option), considering the current user
    // permissions in each space candidates.
    $referenceables = gofast_og_get_referenceable_spaces($node, $GLOBALS['user']);
    $og_nodes = array_map(function($item){ return $item->title; }, $referenceables);
    
    // If the space being deleted contains contents, we follow either A or B:
    $contents = gofast_og_get_content($node->nid, TRUE);
    if (!empty($contents)) {
      // A. Exclude root spaces from the target spaces list because root spaces 
      // can only contain child spaces (@todo except if such content is multi 
      // filled outside the scope of the deleted space).
      //$og_nodes = array_diff_key($og_nodes, gofast_og_get_root_spaces(FALSE, TRUE));

      // B. Warn the user that these contents will be lost if not multi-filled 
      // outside the scope of the deleted space.
      $items = array_map(function($item) { return l($item->title, "node/{$item->nid}"); }, $contents);
      $root_space = gofast_og_get_root_space($node, TRUE);
      
      $msg = t('Warning: %space contents that are not shared outside of its scope '
            .'will be lost if you choose %root as the target space (a root space cannot '
            .'contain content but only spaces).', 
            array('%space' => $node->title, '%root' => $root_space->title),
             array('context' => 'gofast:gofast_og'));
      $list = '<a href="#" class="gofast-pointer collapsed" data-toggle="collapse" data-target="#del-content-list">' 
              . t('Show/Hide contents list.', array(), array('context' => 'gofast')) . '</a>';
      $expand = '<div style="padding-left:15px;">' . $list . '</div>';
      $warning = '<div class="alert error">' . $msg . $expand . theme('item_list', array('items' => $items, 'attributes' => array('id' => 'del-content-list', 'class' => array('collapse')))) . '</div>';
    }
    
    // Also exclude from the target space candidates the node being deleted and 
    // any of its descendants.
    $descendants = gofast_og_get_children($node->nid, TRUE, FALSE, TRUE);
    foreach ($descendants + array($node->nid => $node->nid) as $nid => $gid) {
      unset ($og_nodes[$gid]);
    }
    
    $options = array(); 
    $options[OG_DELETE_ORPHANS] = t('Delete all the content associated with %deleted.', array('%deleted' => $node->title), array('context' => 'gofast:gofast_og'));
    //$options[OG_DELETE_NOTHING] = t('Delete the space and make the content public');
    //$options[OG_DELETE_ORPHANS] = t("Delete all group posts which don't also belong to another group.");
    if (!empty($og_nodes)) {
      $options[OG_DELETE_MOVE_NODES_MEMBERSHIPS] = t('Move %deleted contents and subspaces to another space.', array('%deleted' => $node->title), array('context' => 'gofast:gofast_og'));
    }
    
    /**
     * @todo add warning when moving space content into a target space: 
     *  user permission in the target space will be applied for moved content 
     *  so subspace users may loose write access on these content in target space.
     */
    
    $form['verb'] = array(
      '#type' => 'radios',
      '#title' => t('Space contents', array(), array('context' => 'gofast')),
      '#options' => $options,
      '#default_value' => OG_DELETE_ORPHANS,
      '#weight' => -1,
      // HTML is added to prevent our theme from embedding text in a tooltip.      
      '#description' => '<i></i>' 
                    . t('In addition to deleting this space, choose how to disposition the contents and memberships within it.'
                     , array(), array('context' => 'gofast:gofast_og'))
    );
  
    $form['move_users'] = array(
      '#type' => 'checkbox',
      '#title' => t('Update user memberships as well.', array(), array('context' => 'gofast:gofast_og')),
      '#default_value' => 1,
      '#attributes' => array('class' => array('gofast-form-indent')),
      '#weight' => 0,
      '#description' => '<i></i>' 
                        . t('Select this option if you want %deleted members to become members of the target space.'
                        , array('%deleted' => $node->title), array('context' => 'gofast:gofast_og')),
      '#states' => array(
        // Show this field only when the corresponding option is selected.
        'visible' => array(
          ':input[name="verb"]' => array('value' => OG_DELETE_MOVE_NODES_MEMBERSHIPS),
        )
      )
    );
    
    $form['target'] = array(
      '#type' => 'select',
      '#title' => t('Target space', array(), array('context' => 'gofast')),
      '#default_value' => 0,
      '#options' => $og_nodes,
      '#weight' => 1,
      // HTML is added to prevent our theme from embedding text in a tooltip.
      '#description' => '<i></i>' . t('Specify a destination space.', array(), array('context' => 'gofast')) . ' '
              . t('Note: Some nodes are hidden because you cannot set the parent of this space to be the space itself or one of its children.'
               , array(), array('context' => 'gofast:gofast_og')),
      '#states' => array(
        // Show this field only when the corresponding option is selected.
        'visible' => array(
          ':input[name="verb"]' => array('value' => OG_DELETE_MOVE_NODES_MEMBERSHIPS),
        )
      )
    );
    
    if (isset($warning) && isset($root_space->nid)) {
      $form['warning'] = array(
        '#type' => 'container',
        '#weight' => 2,
        '#states' => array(
          'visible' => array(
            ':input[name="verb"]' => array('value' => OG_DELETE_MOVE_NODES_MEMBERSHIPS),
            ':input[name="target"]' => array('value' => $root_space->nid),
          )
        ),
        'markup' => array(
          '#markup' => $warning
        )
      );
    }
    
    $form['description']['#weight'] = 10;
    $form['description']['#markup'] .= '<br /><br />';
    array_unshift($form['#submit'], 'gofast_og_delete_content_form_submit');
  }
}

/**
 * According to form values, move or delete OG content. Deletion occurs only if 
 * it is not associated with another group.
 */
function gofast_og_delete_content_form_submit($form, &$form_state) {
  $deleted_group_nid = $form_state['values']['nid'];
  
  if (array_key_exists('target', $form_state['values'])) {
    $target_group_nid = $form_state['values']['target'];
  }
  
  $move_children = $form_state['values']['verb'] >= OG_DELETE_MOVE_NODES;
//  gofast_og_delete_node_membership(gofast_og_get_memberships($deleted_group_nid), $form_state, $context); // ?
  
  $batch = array(
    'title' => t('OG Delete', array(), array('context' => 'gofast:gofast_og')),
    'operations' => array(
      array('gofast_og_delete_node_membership', array(gofast_og_get_memberships($deleted_group_nid), $form_state)),
      array('gofast_og_delete_user_membership', array(gofast_og_get_memberships($deleted_group_nid, 'user'), $form_state)),
    ),
    'finished' => 'gofast_og_delete_membership_finish',
  );
  
  batch_set($batch);
  
  if ($move_children && isset($target_group_nid)) {
    $form_state['redirect'] = 'node/' . $target_group_nid;
  }
  else {
    $form_state['redirect'] = variable_get('site_frontpage', 'node');
  }
}

/**
 * Delete node memberships or move node memberships to the selected OG.
 */
function gofast_og_delete_node_membership($og_memberships, $form_state, &$context) {
  if (array_key_exists('target', $form_state['values'])) {
    $target_group_nid = $form_state['values']['target'];
  }
  
  $delete_orphans = $form_state['values']['verb'] == OG_DELETE_ORPHANS;
  $move_children = $form_state['values']['verb'] >= OG_DELETE_MOVE_NODES;
  
  foreach ($og_memberships as $og_membership) {
    $entity = entity_load_single('node', $og_membership->etid);
    if ($move_children) {
      // There is an array_unique() in og_save_ancestry which guards against 
      // duplicates so don't worry here.
      $membership = og_get_membership($og_membership->group_type, $target_group_nid, $og_membership->entity_type, $og_membership->etid);
      if (!isset($membership->id)) {
        $og_membership = og_membership_load($og_membership->id);
        $og_membership->gid = $target_group_nid;
        og_membership_save($og_membership);
      }
    }
    if ($delete_orphans) {
      //if the entity is a space, get all the children of this space and also delete them      
        $_GET['nid'] = $entity->nid;
        gofast_ajax_node_unpublish(NULL, NULL, FALSE);
    }
    $context['results']['node'][] = $entity->nid . ' : ' . check_plain($entity->title);
  }
}

/**
 * Delete user memberships or move user memberships to the selected OG node.
 */
function gofast_og_delete_user_membership($og_memberships, $form_state, &$context) {
  $deleted_group_nid = $form_state['values']['nid'];
  $verb = $form_state['values']['verb'];
  $move_users = $form_state['values']['move_users'];
  
  if ($verb == OG_DELETE_MOVE_NODES_MEMBERSHIPS && $move_users) {
    $node = $form_state['#node'];
    $target_group_nid = $form_state['values']['target'];
    
    foreach ($og_memberships as $og_membership) {
      $membership = og_get_membership($og_membership->group_type, $target_group_nid, $og_membership->entity_type, $og_membership->etid);
      if (!isset($membership->id) && $node->uid != $og_membership->etid) {
        $og_membership = og_membership_load($og_membership->id);
        $og_membership->gid = $target_group_nid;
        og_membership_save($og_membership);
        $context['results']['user'][] = $og_membership->etid;
      }
      else {
        // We might want to update user roles in the target space since he could
        // loose 'edit' permission on the moved contents (all contents from the 
        // deleted space).
      }
    }
  }
  entity_delete('node', $deleted_group_nid);
}

function gofast_og_delete_membership_finish($success, $results, $operations) {
  // The 'success' parameter means no fatal PHP errors were detected. All
  // other error management should be handled using 'results'.
  $items = array();
  $message = '';
  if ($success) {
    if (array_key_exists('user', $results)) {
      if (count($results['user'])) {
        $message = format_plural(count($results['user']), 'Moved 1 membership.', 'Moved @count memberships.');
      }
    }
    if (array_key_exists('node', $results)) {
      if (count($results['node'])) {
        $message = format_plural(count($results['node']), 'One post processed.', '@count posts processed.');
      }
    }
  } 
  else {
    $message = t('Finished with an error.', array(), array('context' => 'gofast'));
  }
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  foreach ($results as $result) {
    $items[] = t('Loaded node %title.', array('%title' => $result), array('context' => 'gofast'));
  }
  if (count($items)) {
    $_SESSION['my_batch_results'] = $items;
  }
}

/**
 * Returns all OG memberships referencing the given OG node id (as a parent 
 * node). No access control. If you are retrieving for displaying, you may want 
 * to use an embedded View instead of this function.
 */
function gofast_og_get_memberships($gid, $entity_type = 'node') {
  $ids = array();
  $query = db_select('og_membership', 'ogm')
    ->fields('ogm')
    ->condition('ogm.gid', $gid, '=')
    ->condition('ogm.entity_type', $entity_type, '=');
  $result = $query->execute()->fetchAll();
  foreach ($result as $key => $value) {
    $ids[] = $value;
  }
  return $ids;
}