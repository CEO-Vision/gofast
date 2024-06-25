<?php

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Documents that have an OG issue (from alfresco CMIS query)
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_drupal_identify_documents_ogs($items){
    global $user;
    
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        $gids = array();
        
        //Fetch all document's paths to find the space folders corresponding to these paths
        foreach($item['paths'] as $path){
            //Split the path by '/' and prepare to find gid from path
            $path_components = explode("/", $path);
            $gid = null;
            $it = 0;
            
            //Recursivly search for space (we assume all spaces start with _)
            //Then try to find out the gid associated to the path
            while (true){
                if(count($path_components) < 2){ //We are in /Sites, we were not able to find a space looking folder
                    $item['invalid_space_not_found'] = "Space not found from path for this document";
                    $item['space_not_found'] = $path;
                    $invalid[] = $item;
                    continue 3;
                }
                
                //Check if we are in a space looking folder
                if(substr(end($path_components), 0, 1) === "_"){
                    //Try to find the gid associated to this space.
                    //Because we want to use Alfresco as our base reference, we will have to make another CMIS request
                    //here.
                    $space_path = implode("/", $path_components);
                    $alfresco_item = gofast_cmis_item_get_by_path($space_path);
                    $gid = $alfresco_item->properties['gofast:nid'];
                    break;
                }
                
                //We are in a folder, remove the last element and iterrate again
                array_pop($path_components);
                
                //Prevent infinite loop. It shouldn't happens but it's a necessary security
                //in a while true loop
                if($it > 50){
                    $item['invalid_loop'] = "Infinite loop detected in space finding";
                    $item['space_loop'] = $path;
                    $invalid[] = $item;
                    continue 3;
                }
                $it++;
            }
            
            //Validate found gid and insert it in our final array
            if(is_numeric($gid)){
                $gids[] = $gid;
            }else{
                $item['invalid_space_gid'] = "Unable to validate found gid";
                $item['space_path'] = $path;
                $item['space_gid'] = $gid;
                $invalid[] = $item;
                continue 2;
            }
        }
        
        //Check if we have retrieved gids to compare with current drupal's OGs
        if(count($gids) < 1){
            $item['invalid_space_gid'] = "Unable to find any gid";
            $invalid[] = $item;
            continue;
        }
        
        //Retrieve Drupal OGs to compare them with found gids
        $ogs = (array) og_get_entity_groups("node", $item['nid'], array(OG_STATE_ACTIVE), GOFAST_OG_CONTENT_MEMBERSHIP_FIELD)['node'];
        
        //Find missing OG
        $missing_ogs = array_diff($gids, $ogs);
        if(count($missing_ogs) > 0){
            $item['invalid_missing_ogs'] = "Missing ogs for this document";
            $item['missing_ogs'] = $missing_ogs;
            $invalid[] = $item;
            continue;
        }
        
        //Find OG that shouldn't be here
        $supp_ogs = array_diff($ogs, $gids);
        if(count($supp_ogs) > 0){
            $item['invalid_unwanted_ogs'] = "Unwanted ogs for this document";
            $item['unwanted_ogs'] = $supp_ogs;
            $invalid[] = $item;
            continue;
        }
        
        //This item is valid
        $valid[] = $item;
    }
    
    return array(
        "valid" => $valid,
        "invalid" => $invalid
    );
}

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Documents that have a metadata issue (title, locations..)
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_drupal_identify_documents_metadata($items){
    global $user;
    
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        //Load Drupal node
        $node = node_load($item['nid']);
        
        if(!is_object($node)){ //Make sure we got a node
            $item['invalid_node_load'] = "Unable to load node for this document";
            $invalid[] = $item;
            continue;
        }
        
        $title = $node->title;
        $locations_array = array_merge((array) $node->field_main_emplacement['und'], $node->field_emplacement['und']);
        $locations = array();
        foreach($locations_array as $location){
            $locations[] = $location['value'];
        }
        
        //Check : Title
        if($title != $item['title']){
            $item['invalid_node_title'] = "Invalid node title for this document";
            $item['node_title'] = $title;
            $invalid[] = $item;
            continue;
        }
        
        //Check : Locations
        if(count(array_diff($locations, $item['paths'])) != 0 || count(array_diff($item['paths'], $locations)) != 0){
            $item['invalid_node_locations'] = "Invalid node locations for this document";
            $item['node_locations'] = $locations;
            $invalid[] = $item;
            continue;
        }
        
        //This item is valid
        $valid[] = $item;
    }
    
    return array(
        "valid" => $valid,
        "invalid" => $invalid
    );
}

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Spaces that are not properly replicated in drupal, considering title, reference, parent og (from alfresco CMIS query)
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_drupal_identify_spaces($items){
    global $user;
    
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        //Load Drupal node
        $node = node_load($item['nid']);
        
        if(!is_object($node)){ //Make sure we got a node
            $item['invalid_node_load'] = "Unable to load node for this space";
            $invalid[] = $item;
            continue;
        }
        
        //Extract data
        $reference = $node->field_folder_reference['und'][0]['value'];
        $item['node_reference'] = $reference;
        
        $og_parent = $node->og_group_ref['und'][0]['target_id'];
        $item['og_parent'] = $og_parent;
        
        $alfresco_parent_nid = gofast_cmis_item_get($item['parents_ref']['0'])->properties['gofast:nid'];
        $item['alfresco_parent_nid'] = $alfresco_parent_nid;
        
        //Check : Reference
        if($reference != $item['reference']){
            $item['invalid_node_reference'] = "Invalid node reference for this space";
            $invalid[] = $item;
            continue;
        }
        
        //Check : Parent
        if($og_parent != $alfresco_parent_nid){
            $item['invalid_parent_nid'] = "Invalid parent nid for this space";
            $invalid[] = $item;
            continue;
        }
        
        //This item is valid
        $valid[] = $item;
    }
    
    return array(
        "valid" => $valid,
        "invalid" => $invalid
    );
}

function gofast_integrity_check_create_space_drupal($nid, $node, &$failure) {
    $messages = "";
    if (!$node) {
        $message = "Space with gid @gid has not been inserted in Drupal database.";
        $messages .= $message;
        watchdog("gofast_integrity_check_on_action", $message, array("@gid" => $nid), WATCHDOG_WARNING);
        $failure = TRUE;
    }
    $reference = $node->{GOFAST_CMIS_FOLDER_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'];
    if (!$reference) {
        $message = "Alfresco reference is missing Drupal-side for space n°@gid.";
        $messages .=  (!empty($messages) ? " " : "")  . $message; 
        watchdog("gofast_integrity_check_on_action", $message, array("@gid" => $nid), WATCHDOG_WARNING);
        $failure = TRUE;
    }
    $og_parent = $node->{GOFAST_OG_PARENT_GROUP_FIELD}[LANGUAGE_NONE][0]['target_id'];
    if (!$og_parent) {
        $message = "Parent reference is missing Drupal-side for space n°@gid.";
        $messages .=  (!empty($messages) ? " " : "") . $message;
        watchdog("gofast_integrity_check_on_action", $message, array("@gid" => $nid), WATCHDOG_WARNING);
        $failure = TRUE;
    }
    // write to a zabbix item as well
    if ($failure) {
        return str_replace("@gid", $nid, $messages);
    }
}


function gofast_integrity_check_rename_drupal($node, $old_title, $new_title, $is_space, $extension, $repair = FALSE) {
  //First check : Node title should be set properly in the Drupal node object
  if($node->title != $new_title && '_' . $node->title != $new_title && $node->title . $extension != $new_title){
    watchdog("gofast_integrity_check_on_action", "Node : " . $node->nid . ", Old name : $old_title, New name : $new_title -- Drupal item title is wrong. Title reported is : " . $node->title, [], WATCHDOG_WARNING);
    
    // REPAIR if enabled
    if ($repair) {
        $node->title = $new_title;
        $ruid = $node->revision_uid;
        gofast_prepare_node_save_technically($node);
        node_save($node);
        db_update('node_revision')
            ->fields(array('uid' => $ruid))
            ->condition('nid', $node->nid)
            ->execute();
        cache_clear_all("field:node:$node->nid", 'cache_field');
    }
    
    return 'ko';
  }
  
  //All check passed
  return "ok";
}

