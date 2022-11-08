<?php

/**
 * 
 */
function gofast_retention_init_retention_matrice() {
  //create retention table as DRUPAL variable
  if (!variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR)) {

    $matrice = array();
    $matrice['89efaf7b-baed-4477-807e-991e1b9ecd2b'] = array(
      'uuid' => '89efaf7b-baed-4477-807e-991e1b9ecd2b',
      'tid' => 112,
      'period' => '60',
      'period_unit' => 'd',
      'action' => 'archive'
    );
    
    variable_set(GOFAST_RETENTION_PERIOD_MATRICE_VAR, $matrice);
  }
}

/**
 * Put node into ReadOnly Mode
 * @param type $node
 */
function gofast_retention_set_node_readonly($node){
  if(node_access('update', $node) && ($node->type == "alfresco_item") ){
     $node_ref = gofast_cmis_node_get_item_id($node);
     
    $url = 'http://localhost:8080/alfresco/service/set/node/archive/permission/?reference=' . rawurlencode($node_ref);
    exec("curl --user admin:" . gofast_get_admin_pwd() . " '" . $url . "'");  
  }
}

/**
 * 
 * @param type $node
 */
function gofast_retention_unset_node_readonly($node){
  if(node_access('update', $node) && ($node->type == "alfresco_item") ){
     $node_ref = gofast_cmis_node_get_item_id($node);
     
     $url = 'http://localhost:8080/alfresco/service/set/node/workflow/permission/?reference=' . rawurlencode($node_ref) . '&validators=&inverse=true';
     $output = exec("curl --user admin:" . gofast_get_admin_pwd() . " '" . $url . "'");
     
     $properties['gofast:preventDelete'] = 'false'; 
     gofast_cmis_item_update_properties($node_ref, $properties, false, true);
  }
}

function gofast_retention_apply_prearchived_status_retroactivly(){
  set_time_limit(0);
  //get node which have retention date
  $query = db_select('field_data_field_retention_end', 'f');
  $query->fields('f', array('entity_id', 'field_retention_end_value'));
  $query->condition('f.field_retention_end_value', 'NULL', '<>');
  $results = $query->execute();

  $result_nids = $results->fetchAllKeyed();

  if (count($result_nids) > 0) {
       $archived_taxonomy_term = taxonomy_get_term_by_name("Pre-Archived", 'state');
       $archived_taxonomy_term_id = reset($archived_taxonomy_term)->tid;
      foreach($result_nids as $nid=>$date){
        $node = node_load($nid);      
        if($node->{'field_state'}[LANGUAGE_NONE][0]['tid'] !== $archived_taxonomy_term_id){
            //node with DUA but not with pre-archived status
            $_POST['prevent_automatic_multifilling'] = true;
            $node = gofast_cmis_node_archive($node, true);
            $node = gofast_prepare_node_save_technically($node);
            $ruid = $node->revision_uid;
            node_save($node);
            db_update('node_revision')
              ->fields(array('uid' => $ruid))
              ->condition('nid', $node->nid)
              ->execute();
            watchdog("GOFAST 3.8 Update Pre-archived" , $node->nid);
        }
      }
  }
}

function gofast_retention_apply_prearchived_permissions_already_archived(){
  set_time_limit(0);
  //get node which already have pre-archived status
  $archived_taxonomy_term = taxonomy_get_term_by_name("Pre-Archived", 'state');
  $archived_taxonomy_term_id = reset($archived_taxonomy_term)->tid;
  $result_nids = taxonomy_select_nodes($archived_taxonomy_term_id, FALSE);
  usurp(1);
  if (count($result_nids) > 0) {
      
      foreach($result_nids as $nid){
        $node = node_load($nid);  
        //only archived node without DUA
        if( gofast_retention_get_retention_date($node) == NULL){
            //node with DUA but not with pre-archived status
            $_POST['prevent_automatic_multifilling'] = true;
            $node = gofast_cmis_node_archive($node, true);
            $node = gofast_prepare_node_save_technically($node);
            $ruid = $node->revision_uid;
            node_save($node);
            db_update('node_revision')
              ->fields(array('uid' => $ruid))
              ->condition('nid', $node->nid)
              ->execute();
            watchdog("GOFAST 3.8 Update already Pre-archived" , $node->nid);
        }
      }
  }
}
