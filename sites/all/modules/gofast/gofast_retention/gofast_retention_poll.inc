<?php 

/**
 * Implements hook_poll_info()
 * 
 * @return array
 */
function gofast_retention_poll_info() {
  return array(
    'document_retention' => array(
      'label' => 'Updated_document_retention',
      'description' => 'Gathers whether the document retention date has changed or not',
      'interval' => 2,
      'context' => 'node',
      'selector' => '#refresh-preview'
    )
  );
}


/**
 * Implements hook_poll()
 */
function gofast_retention_poll($poll_name, $poll_info, $context) {
  $commands = array();

  if (!isset($context['nid'])) {
    return;
  }

  $node = node_load($context['nid'], NULL, TRUE);
  $old_retention_date = $context['gofast_retention']['node']['retention_date'];
  
  switch ($poll_name) {
    case 'document_retention':

      if ($node->type === 'alfresco_item') {

        if($node->field_retention_end[LANGUAGE_NONE][0]['value'] != $old_retention_date ){

          if (!gofast_mobile_is_mobile_domain()) {
            $node_contextual_actions = gofast_get_contextual_actions_node($node);
            $contextual_actions = '';
            $contextual_actions .= theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-actions', 'buttons' => $node_contextual_actions));
          }

          if( $node->field_retention_end[LANGUAGE_NONE][0]['value'] === NULL){
            //$commands[] = gofast_command_toast_message(t("Node document has changed.", array(), array('context' => 'gofast:gofast_retention')));
            if (!gofast_mobile_is_mobile_domain()) {
              $commands[] = ajax_command_invoke('#breadcrumb-alt-actions', 'replaceWith', array($contextual_actions));
              $commands[] = ajax_command_invoke('.drop-area', 'css', array('display', ''));
            }
          }else{
            //$commands[] = gofast_command_toast_message(t("Node document has changed.", array(), array('context' => 'gofast:gofast_retention')));
            if (!gofast_mobile_is_mobile_domain()) {
              $commands[] = ajax_command_invoke('#breadcrumb-alt-actions', 'replaceWith', array($contextual_actions) );
              $commands[] = ajax_command_invoke('.drop-area', 'css', array('display', 'none'));
            }
          }
          //gofast_set_context($context);
          gofast_retention_set_context("node", "retention_date", $node->field_retention_end[LANGUAGE_NONE][0]['value'] );
          
          return $commands;
        }else{
          return;
        }
        
      }else{
        return;
      }
      
      break;
  }
}


/**
 * Set context for retention polling
 * @param $element
 *  The element in the polling.
 * @param $key
 *  The key for the polling's element
 * @param $value
 *  The value to assign
 * 
 */
function gofast_retention_set_context($element = FALSE, $key = NULL, $value = NULL){
    $context = array(
      'gofast_retention' => array(
        $element => array(
          $key => $value
        )
      )
    );
  
  gofast_set_context($context);
  
}