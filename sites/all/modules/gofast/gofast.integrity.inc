<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


function gofast_integrity_dashboard(){
    $form = drupal_get_form("gofast_integrity_space_form");

    $output = drupal_render($form);
    
    return $output;
    
}

function gofast_integrity_get_unpublished_orphaned_alfresco_items(){
   $date = time() - 7776000;
   $results = db_query("SELECT nid as etid from node WHERE (SELECT COUNT(*) FROM og_membership WHERE og_membership.etid=node.nid AND og_membership.field_name='og_group_content_ref')=0 AND node.type = 'alfresco_item' AND node.status=0 AND node.changed > '".$date."' ")->fetchAll();
   return $results;
}


function gofast_integrity_space_form($form,&$form_state){   
    
    $actions_list = array("publish" => t("Publish again recovered documents"), "unpublish" => t("Unpublish deleted documents"), "repair_locations" => t("Repair nodes locations"));
    
     $form['action'] = array(
        '#type' => 'select',
        '#title' => t('Action'),                  
        '#options' => $actions_list,
        '#required' => TRUE,             
      );
    
   //TODO replace it by autocomplete field    
      $form['gids'] = array(
        '#type' => 'textfield',
        '#title' => t('Spaces'),                      
        '#required' => TRUE, 
        '#description' => t("type a space separated list of gid. Enter 0 to select all orphaned documents ( without any space )")
      );
    
      $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Submit"),
      '#submit' => array('gofast_integrity_space_form_submit'),
      ); 
      
      return $form;
    
}

function gofast_integrity_space_form_validate(&$form, &$form_state){
   //TODO
}


function gofast_integrity_space_form_submit(&$form, &$form_state){
   $gids = explode(" " , $form_state["values"]["gids"]);
   
   $action = $form_state["values"]["action"];
   
   if($action == "publish"){
       //we get all unpublished spaces node, and check if the corresponding alfresco documents are into trash or not. If not, publish again the node
           $batch = array(
                    'title' => 'Construction de la liste',
                    'operations' => array(
                      array('gofast_integrity_publish_batch', array($gids)),
                    ),
                    'finished' => 'gofast_integrity_publish_batch_finished', 
                    'progress_message' => "",
                  );
                batch_set($batch);
                // Only needed if not inside a form _submit handler.
                // Setting redirect in batch_process.
                batch_process("node");
                
   }elseif($action == "repair_locations"){
        //we get all node for the selected space, and call function to repair locations into Drupal DB
           $batch = array(
                    'title' => 'Construction de la liste',
                    'operations' => array(
                      array('gofast_integrity_repair_locations_batch', array($gids)),
                    ),
                    'finished' => 'gofast_integrity_repair_locations_batch_finished', 
                    'progress_message' => "",
                  );
                batch_set($batch);
                // Only needed if not inside a form _submit handler.
                // Setting redirect in batch_process.
                batch_process("node");
   }
   
  
}

function gofast_integrity_repair_locations_batch($gids,&$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    if($gids == array(0 => "0")){
        $all_nids = array();
    }else{
        $all_nids = gofast_og_get_nodes_from_gids($gids);
    }
    $context['sandbox']['max'] = count($all_nids);
  }


   if($gids == array(0 => 0)){
        $all_nids = array();
    }else{
        $all_nids = gofast_og_get_nodes_from_gids($gids);
    }

  $limit = 50;
  $cut_all_nids = array_slice($all_nids,$context['sandbox']['current_node'], $limit, true);

  global $cmis_sudo_admin;
  $cmis_sudo_admin = true;
  foreach($cut_all_nids as $key => $nid){
    $node = node_load($nid->etid);
    gofast_process_location_check_async($nid->etid,true, true);
    $context['results'][$nid->etid] = "Repairing locations for node ".$node->title." ( ".$nid->etid." )";

    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $key+1;
    $context['message'] = $node->title;
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function gofast_integrity_repair_locations_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One post processed.', '@count posts processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  
  if(count($results) > 0){
      foreach($results as $result){
         drupal_set_message($result);
      }
  }
  
  drupal_set_message($message);
}


function gofast_integrity_publish_batch($gids,&$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    if($gids == array(0 => "0")){
        $all_nids = gofast_integrity_get_unpublished_orphaned_alfresco_items();
    }else{
        $all_nids = gofast_og_get_nodes_unpublished($gids);
    }
    $context['sandbox']['max'] = count($all_nids);
  }


   if($gids == array(0 => 0)){
        $all_nids = gofast_integrity_get_unpublished_orphaned_alfresco_items();
    }else{
        $all_nids = gofast_og_get_nodes_unpublished($gids);
    }

  $limit = 50;
  $cut_all_nids = array_slice($all_nids,$context['sandbox']['current_node'], $limit, true);

  global $cmis_sudo_admin;
  $cmis_sudo_admin = true;
  foreach($cut_all_nids as $key => $nid){

    $document_node = node_load($nid->etid);

    $doc = gofast_cmis_item_get($document_node->reference);

    if(isset($doc->id)) {
        //the alfresco document is not deleted, so, publish again the drupal node
        $document_node->status = 1;

        //if the node doesn't have any space ( in case of space deletion for exemple)
  if(count($document_node->og_group_content_ref) == 0){
                $parent = gofast_cmis_item_get_parent($document_node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
                $parents_formatted = array();
                if(count($parent->objectList) > 0){
                   foreach($parent->objectList as $myparent){
                       $parents_formatted[] = array("value" => htmlspecialchars($myparent->properties["cmis:path"]));
                   }
                }
                foreach($parents_formatted as $key=>$parent_path){
                   $group_id = gofast_og_get_group_id_from_title_2(htmlspecialchars_decode($parent_path["value"]), TRUE);
                   if($group_id !== false){
                    $groups_array[$group_id] = array("target_id" => $group_id);
                   }
                }
                sort($groups_array);
               $document_node->og_group_content_ref["und"] =  $groups_array;
          }

        //var_dump($document_node->og_group_content_ref["und"]);exit;
        $document_node = gofast_prepare_node_save_technically($document_node);
        $ruid = $document_node->revision_uid;
        node_save($document_node);
        db_update('node_revision')
          ->fields(array('uid' => $ruid))
          ->condition('nid', $document_node->nid)
          ->execute();
        cache_clear_all("field:node:$document_node->nid", 'cache_field');
        $context['results'][$document_node->nid] = "published again document '".$document_node->title." ( ".$document_node->nid." )";
    }

    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $key+1;
    $context['message'] = $document_node->title;
  }

  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

function gofast_integrity_publish_batch_finished($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One post processed.', '@count posts processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  
  if(count($results) > 0){
      foreach($results as $result){
         drupal_set_message($result);
      }
  }
  
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  
 
 
}


function gofast_integrity_repair_all_orphaned_doc($limit = null){
    
    $all_nids = gofast_integrity_get_orphaned_alfresco_items($limit);
    if(count($all_nids) > 0){
        foreach($all_nids as $key=>$object_node){
                $document_node = node_load($object_node->etid);
                    if(count($document_node->og_group_content_ref) == 0){
                       $parent = gofast_cmis_item_get_parent($document_node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
                       $parents_formatted = array();
                       if(count($parent->objectList) > 0){
                          foreach($parent->objectList as $myparent){
                              $parents_formatted[] = array("value" => htmlspecialchars($myparent->properties["cmis:path"]));
                          }
                       }
                       foreach($parents_formatted as $key=>$parent_path){
                          $group_id = gofast_og_get_group_id_from_title_2(htmlspecialchars_decode($parent_path["value"]), TRUE);
                          if($group_id !== false){
                           $groups_array[$group_id] = array("target_id" => $group_id);
                          }
                       }
                       sort($groups_array);
                      $document_node->og_group_content_ref["und"] =  $groups_array;
                 }

               //var_dump($document_node->og_group_content_ref["und"]);exit;
               $document_node = gofast_prepare_node_save_technically($document_node);
               $ruid = $document_node->revision_uid;
               //node_save($document_node);
               //db_update('node_revision')
               //  ->fields(array('uid' => $ruid))
               //  ->condition('nid', $document_node->nid)
               //  ->execute();
               //cache_clear_all("field:node:$document_node->nid", 'cache_field');
        }
    }
     
}

function gofast_integrity_get_orphaned_alfresco_items($limit = null){
   $date = time() - 7776000;
   if($limit !== null){
       $sql_limit = " LIMIT 0,".$limit;
   }else{
       $sql_limit = " ";
   }
   $results = db_query("SELECT nid as etid from node WHERE (SELECT COUNT(*) FROM og_membership WHERE og_membership.etid=node.nid AND og_membership.field_name='og_group_content_ref')=0 AND node.type = 'alfresco_item' AND node.status=1 AND node.changed > '".$date."' ".$sql_limit)->fetchAll();
   return $results;
}