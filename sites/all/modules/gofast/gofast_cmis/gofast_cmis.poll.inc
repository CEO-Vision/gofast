<?php

/**
 * Implements hook_poll_info()
 *
 * @return array
 */
function gofast_cmis_poll_info() {
  return array(
    'document_updated' => array(
      'label' => 'Updated_document',
      'description' => 'Gathers whether the document has changed or not',
      'interval' => 2,
      'context' => 'node',
      'selector' => '#refresh-preview'
    ),
    'document_being_edited' => array(
      'label' => 'Edit_document',
      'description' => 'Gathers whether the document is being edited or not',
      'interval' => 1,
      'context' => 'node',
      'selector' => '.on-node-lock-disable'
    )
  );
}

/**
 * Implements hook_poll()
 */
function gofast_cmis_poll($poll_name, $poll_info, $context) {
  $commands = array();

  if (!isset($context['nid'])) {
    return;
  }

  $node = node_load($context['nid'], NULL, TRUE);
  $old_node = (object) $context['entity'];

  switch ($poll_name) {
    case 'document_updated':
      //$path = current_path();
      $old_version = $context['block_cmis']['node']['version'];
      $version = gofast_cmis_alfresco_get_infos($node)['last_version'];
      if ($old_version != $version && $old_version != null && $version != null) {
        gofast_cmis_set_context("node", "version", $version);
        $commands[] = ajax_command_invoke($poll_info['selector'], 'prop', array('disabled', false));
        $commands[] = gofast_command_toast_message(t("The document's version has changed from !old_version to !version. You can reload document preview.", array('!old_version' => $old_version, "!version" => $version), array('context' => 'gofast:gofast_cmis')));
        //reload contextual actions
         $node_contextual_actions = gofast_get_contextual_actions_node($node);
         $contextual_actions .= theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-actions', 'buttons' => $node_contextual_actions));
         $commands[] = ajax_command_invoke('#breadcrumb-alt-actions', 'replaceWith', array($contextual_actions));
        }
      break;
    case 'document_being_edited':

        global $user;
        if ($node->type === 'alfresco_item') {
          $lock_state = isset($node->cmis_lock_owner) ? $node->cmis_lock_owner : gofast_cmis_webservice_execute_request("getlocked", gofast_cmis_node_get_item_id($node));
        }
        else {
          $lock_state = 'nolocked';
          return;
        }

        $canEdit = node_access("update", $node) && $lock_state === "nolocked" && !gofast_get_content_state_archived($node);
        if(!$canEdit) {
          if($lock_state !== 'nolocked' && $lock_state !== $old_node->cmis_lock_owner){
            if (!gofast_mobile_is_mobile_domain()) {
               $commands[] = ajax_command_invoke('.drop-area', 'css', array('display', 'none'));
            }
          $commands[] = ajax_command_invoke($poll_info['selector'], 'addClass', array('disabled'));
          $commands[] = gofast_command_toast_message(t("Document is being edited by ", array(), array('context' => 'gofast:gofast_cmis')) . " " . $lock_state);
            }
          }else{
              //if current user editing
                  if ($lock_state !== 'nolocked' && $lock_state !== $old_node->cmis_lock_owner && $old_node->cmis_lock_owner == $user->name) {
                      $commands[] = ajax_command_invoke($poll_info['selector'], 'addClass', array('disabled'));
                      if (!gofast_mobile_is_mobile_domain()) {
                        $commands[] = ajax_command_invoke('.drop-area', 'css', array('display', 'none'));
                      }
                  } else if ($lock_state !== $old_node->cmis_lock_owner) {
                      $commands[] = ajax_command_invoke($poll_info['selector'], 'removeClass', array('disabled'));
                      if (!gofast_mobile_is_mobile_domain()) {
                        $commands[] = ajax_command_invoke('.drop-area', 'css', array('display', 'none'));
                      }
                  }
          }
      break;
  }

  return $commands;
}

/**
 * Set context for cmis polling
 * @param $element
 *  The element.
 * @param $key
 *  The key
 * @param $value
 *  The value to assign
 *
 */
function gofast_cmis_set_context($element = FALSE, $key = NULL, $value = NULL){
    $block_context = array(
      'block_cmis' => array(
        $element => array(
          $key => $value
        )
      )
    );

  gofast_set_context($block_context);
  
}