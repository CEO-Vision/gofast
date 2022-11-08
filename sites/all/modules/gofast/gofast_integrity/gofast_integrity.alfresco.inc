<?php

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Folders that have a metadata issue
 * 
 * @param array $items array(reference,nid,path,title..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_folders_spaces_metadata($items){
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        //Check if we have mandatory empty properties
        if(empty($item['reference']) || empty($item['paths']) || empty($item['title'])){
            $item['invalid_metadata_properties'] = "This item is missing mandatory properties (ref, title, path..)";
            $invalid[] = $item;
            continue;
        }
        
        //If this is a space, check if we have an associated nid
        if(strpos($item['title'], '_') === 0 && (empty($item['nid']) || $item['is_group'] != true)){
            $item['invalid_metadata_isnt_group'] = "This space have no nid or isn't marked as a group";
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
 * Documents that have a metadata issue
 * 
 * @TODO Missing custom metadata check (category, state..)
 * 
 * @param array $items array(reference,nid,path,title..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_documents_metadata($items){
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        //Check if we have mandatory empty properties
        if(empty($item['reference']) || empty($item['paths']) || empty($item['title'])){
            $item['invalid_metadata_properties'] = "This item is missing mandatory properties (ref, title, path..)";
            $invalid[] = $item;
            continue;
        }
        
        //Check if we have an associated nid
        if(empty($item['nid'])){
            $item['invalid_metadata_isnt_replicated'] = "This document is not replicated to Drupal";
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
 * Folders that have a permission issue
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_folders_spaces_permissions($items){
    global $user;
    $valid = array();
    $invalid = array();
    
    //We have to retrieve the list of all archived spaces because they needs specials treatment
    $archived = array_keys(db_query("SELECT entity_id from field_data_field_archive WHERE field_archive_value=1")->fetchAllAssoc("entity_id"));
    
    //Fetch into items
    foreach($items as $item){
        //Retrieve all permissions of this item
        $item = array_merge($item, gofast_integrity_alfresco_get_permissions_from_reference($item['reference']));
        
        $inheritence = $item['inheritence'];
        $permissions = $item['permissions'];
        $roles = $item['roles'];
        
        //If this is a space, check if we doesn't inherit permissions
        if(strpos($item['title'], '_') === 0 && $inheritence){
            $item['invalid_shouldnt_inherit'] = "This space inherit its permissions";
            $invalid[] = $item;
            continue;
        }
        
        //If this is a folder, check if we inherit permissions
        if(strpos($item['title'], '_') !== 0 && !$inheritence){
            $item['invalid_should_inherit'] = "This folder does not inherit its permissions";
            $invalid[] = $item;
            continue;
        }
        
        //Now we will check if this space have the proper permissions taking in account the following particular cases :
        //Private spaces, Root spaces, Archived spaces
        if(strpos($item['title'], '_') === 0){
            //Check if our item is a root space
            $is_root_space = $item['paths'][0] == "/Sites/_Groups" || $item['paths'][0] == "/Sites/_Organisations" || $item['paths'][0] == "/Sites/_Extranet" || $item['paths'][0] == "/Sites/_Public";
            
            //Check if our item is a private space
            $is_private_space = $item['bundle'] == "private_space";
            
            //Check if our item has a space bundle
            $is_space = $item['bundle'] == "group" || $item['bundle'] == "organisation" || $item['bundle'] == "extranet" || $item['bundle'] == "public";
            
            //Check if our item is an archived element (based on Drupal flag)
            $is_archived = in_array(intval($item['nid']), $archived, TRUE);            
            
            //Check if our item has only the root permission (for space 4 it's _#4)
            $only_main_permission = count($permissions) === 1 && $permissions[0] === "GROUP__#" . $item["nid"];
            
            //Check if our item has all permissions
            $has_all_permissions = count($permissions) === 3 && in_array("GROUP__#" . $item["nid"], $permissions, TRUE) && in_array("GROUP__#" . $item["nid"] . "_STANDARD", $permissions, TRUE) && in_array("GROUP__#" . $item["nid"] . "_ADMIN", $permissions, TRUE);
            
            //Check if our item has only read roles (no read, no admin)
            $only_read_roles = in_array("cmis:read", $roles, true) && !in_array("cmis:write", $roles, true) && !in_array("cmis:all", $roles, true);
            
            //Check if our item has all roles (read, write, admin)
            $has_all_roles = in_array("cmis:read", $roles, true) && in_array("cmis:write", $roles, true) && in_array("cmis:all", $roles, true);
            
            if($is_root_space && (!$only_main_permission ||!$only_read_roles)){ //Root spaces
                $item['invalid_root_space_permissions'] = "Invalid count or type of permissions/roles set for this root space";
                $invalid[] = $item;
                continue;
            }else if(!$is_root_space && $is_private_space && !$has_all_roles){ //Private spaces
                $item['invalid_private_permissions'] = "Invalid count or type of permissions/roles set for this private space";
                $invalid[] = $item;
                continue;
            }else if(!$is_root_space && !$is_private_space && $is_space && (!$has_all_roles || !$has_all_permissions) && !$is_archived){ //Space
                $item['invalid_space_permissions'] = "Invalid count or type of permissions/roles set for this space";
                $invalid[] = $item;
                continue;
            }else if(!$is_root_space && !$is_private_space && $is_space && (!$only_main_permission ||!$only_read_roles) && $is_archived){ //Archived space
                $item['invalid_space_permissions'] = "Invalid count or type of permissions/roles set for this archived space";
                $invalid[] = $item;
                continue;
            }else if(!$is_root_space && !$is_private_space && !$is_space){ //Space without bundle
                $item['invalid_bundle'] = "Invalid bundle set for this space";
                $invalid[] = $item;
                continue;
            }
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
 * Mirrored folders that miss the gofast:ismirrored aspect property
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_folders_mirrors($items) {
    $valid = array();
    $invalid = array();
    
    //Fetch into items
    foreach($items as $item){
        if (isset($item["ismirrored"]) && $item["ismirrored"] == TRUE) {
            $valid[] = $item;
            continue;
        }
        $reference = $item["reference"];
        $folder_parents = gofast_cmis_webservice_get_node_parents($reference);

        $nb_parents = count($folder_parents);
        if($nb_parents > 1){
            // Check if parents are mirrors
            foreach($folder_parents as $parent){
                // Get reference by $parent path
                $parent_reference = gofast_cmis_item_get_by_path($parent)->properties['alfcmis:nodeRef'];
                $folder_parents_parents = gofast_cmis_webservice_get_node_parents($parent_reference);
                $nb_parents_parents = count($folder_parents_parents);
                if($nb_parents_parents > 1){
                    $valid[] = $item;
                }else{
                    $invalid[] = $item;
                }
            }
        }
    }

    return array(
        "valid" => $valid,
        "invalid" => $invalid
    );
}

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Documents that have an aspect issue
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_documents_aspects($items){
    global $user;
    
    $valid = array();
    $invalid = array();
    
    //This array contains mandatory aspects for a document. If they are not on the document, it's an issue
    $document_mandatory_aspects = array(
        "gofast:nodeproperties",
    );
    
    //This array contains valid aspects for a document. They can be associated but it's not mandatory
    $document_valid_aspects = array(
        "cm:titled",
        "gofast:drupalorigin",
        "sys:localized",
        "cm:author",
        "exif:exif",
        "rn:renditioned",
        "cm:thumbnailModification",
        "imap:imapContent",
        "cm:emailed",
        "imap:flaggable",
        "cm:ownable",
        "cm:taggable",
        "sys:cascadeUpdate",
        "audio:audio",
        "cm:copiedfrom",
        "webdav:object",
        "cm:copiedfrom",
        "webdav:object"
    );
    
    //Fetch into items
    foreach($items as $item){
        //Get aspects associated to the current document
        $aspects = gofast_integrity_alfresco_get_aspects_from_reference($item['reference']);
        $item['aspects'] = $aspects;
        
        //Compare them to find out if we are missing a mandatory aspect
        $mandatory_errors = array_diff($document_mandatory_aspects, $aspects);
        if(count($mandatory_errors) > 0){
            $item['invalid_missing_document_aspects'] = "There is missing aspects on this document";
            $item['missing_aspects'] = $mandatory_errors;
            $invalid[] = $item;
            continue;
        }
        
        //Compare them to find out if there is an unwanted aspect
        $unwanted_errors = array_diff($aspects, array_merge($document_mandatory_aspects, $document_valid_aspects));
        if(count($unwanted_errors) > 0){
            $item['invalid_unwanted_document_aspects'] = "There is unwanted aspects on this document";
            $item['unwanted_aspects'] = $unwanted_errors;
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
 * Retrieve aspects associated to an Alfresco item passed by reference
 * 
 * @param string $reference The Alfresco reference
 * @return array List of aspects
 */
function gofast_integrity_alfresco_get_aspects_from_reference($reference){
    global $user;
    
    $data = array();
    $output = array();
    
    //Normalize reference
    $reference = substr($reference, 24);
        
    //Retrieve item ACLs
    $url = "http://localhost:8080/alfresco/api/-default-/public/cmis/versions/1.1/atom/entry?id=" . $reference;
        
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    
    $url = $url . "&alf_ticket=" . $ticket;
        
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_PROXY, '');
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    $acls = curl_exec($ch);
        
    //Parse the XML output
    $parser = xml_parser_create();
    xml_parse_into_struct($parser, $acls, $data);
    xml_parser_free($parser);
    
    //Retrieve needed values to validate permissions
    foreach($data as $element){
        if($element['tag'] == "CMIS:VALUE" && substr($element['value'], 0, 2) == "P:"){
            $output[] = substr($element['value'], 2);
        }
    }
    
    return $output;
}

/*
 * @package gofast_integrity
 * This function identify the following issue : 
 * Documents that have a permission issue
 * 
 * @param array $items array(reference..)
 * @return array array(valid, invalid)
 */
function gofast_integrity_alfresco_identify_documents_permissions($items){
    global $user;
    
    $valid = array();
    $invalid = array();
    
    //Load taxonomy term archived from category
    $tid = array_keys(taxonomy_get_term_by_name("Pre-Archived", "state"))[0];
    //We have to retrieve the list of all read only documents because they needs specials treatment
    $archived = array_keys(db_query("SELECT entity_id from field_data_field_state WHERE field_state_tid=" . $tid)->fetchAllAssoc("entity_id"));
    $dua = array_keys(db_query("SELECT entity_id from field_revision_field_retention_end WHERE field_retention_end_value IS NOT NULL;")->fetchAllAssoc("entity_id"));
    $ro = array_merge($dua, $archived);
    //Fetch into items
    foreach($items as $item){
        //Retrieve all permissions of this item
        $item = array_merge($item, gofast_integrity_alfresco_get_permissions_from_reference($item['reference']));
        
        $inheritence = $item['inheritence'];
        
        //Check inheritence, if the document is multifiled, it should not inherit permissions
        //If it is not multifiled, it should inherit
        if(count($item['paths']) > 1 && $inheritence && !in_array(intval($item['nid']), $ro, TRUE)){
            $item['invalid_shouldnt_inherit'] = "This document is multifiled and should not inherit";
            $invalid[] = $item;
            continue;
        }
        if(count($item['paths']) == 1 && !$inheritence && !in_array(intval($item['nid']), $ro, TRUE)){
            $item['invalid_should_inherit'] = "This document is not multifiled and should inherit";
            $invalid[] = $item;
            continue;
        }
        
        if($inheritence && in_array(intval($item['nid']), $ro, TRUE)){
            $item['invalid_should_inherit_archived'] = "This document is in read only mode and should not inherit";
            $invalid[] = $item;
            continue;
        }
        
        //Check if permissions are properly set if it's a multifiled document (no heritence)
        if(count($item['paths']) > 1){
            $permissions_check = $item['permissions']; //Save the variable here
            
            //Fetch into the parents
            foreach($item['parents'] as $parent){
                //Retrieve permissions of the parent
                $parent_permissions = gofast_integrity_alfresco_get_permissions_from_reference($parent)['permissions'];
                
                //We have the permissions of this parent now, find them in our saved object and check if they are here
                if(count(array_diff($parent_permissions, $permissions_check)) !== 0 && !in_array(intval($item['nid']), $ro, TRUE)){
                    $item['invalid_permissions_missing'] = "This document is missing permissions from it's parents";
                    $item['missing_permissions'] = array_diff($parent_permissions, $permissions_check);
                    $invalid[] = $item;
                    continue 2;
                }
                if(count(array_diff($parent_permissions, $permissions_check)) !== 2 && in_array(intval($item['nid']), $ro, TRUE)){
                    $item['invalid_permissions_missing'] = "This document is missing permissions or have too much from it's parents (archived, DUA, special)";
                    $item['missing_archived_permissions'] = array_diff($parent_permissions, $permissions_check);
                    $invalid[] = $item;
                    continue 2;
                }
                
                //We have finished to check this parent, let's remove them for the check
                $permissions_check = array_diff($permissions_check, $parent_permissions);
            }
            
            if(count($permissions_check) !== 0){
                $item['invalid_permissions_overload'] = "This document has some permissions it shouldn't have";
                $item['overload_permissions'] = $permissions_check;
                $invalid[] = $item;
                continue;
            }
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
 * Retrieve permissions associated to an Alfresco item passed by reference
 * Also return inheritence and roles
 * 
 * @param string $reference The Alfresco reference
 * @return array List of roles, permissions and inheritence
 */
function gofast_integrity_alfresco_get_permissions_from_reference($reference){
    global $user;
    
    $data = array();
    $output = array();
    
    //Normalize reference
    $reference = substr($reference, 24);
        
    //Retrieve item ACLs
    $url = "http://localhost:8080/alfresco/api/-default-/public/cmis/versions/1.1/atom/acl?id=" . $reference;
        
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    
    $url = $url . "&alf_ticket=" . $ticket;
        
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_PROXY, '');
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    $acls = curl_exec($ch);
        
    //Parse the XML output
    $parser = xml_parser_create();
    xml_parse_into_struct($parser, $acls, $data);
    xml_parser_free($parser);
    
    //Retrieve needed values to validate permissions
    foreach($data as $element){
        if($element['tag'] == "CMIS:DIRECT"){
            $inheritence = $element['value'] == "true" ? false : true;
            $output['inheritence'] = $inheritence;
        }
        if($element['tag'] == "CMIS:PRINCIPALID"){
            $permissions[] = $element['value'];
            $output['permissions'] = $permissions;
        }
        if($element['tag'] == "CMIS:PERMISSION"){
            $roles[] = $element['value'];
            $output['roles'] = $roles;
        }            
    }
    
    return $output;
}

/*
 * @package gofast_integrity
 * This fonction is the entry point of Alfresco spaces integrity
 * It will retrieve all Alfresco folders starting with '_'
 * These folders are supposed to be spaces
 * 
 * @return array list of folders
 */
function gofast_integrity_alfresco_get_supposed_spaces($start, $count){
    $output = array();
    
    //Prepare query to retrieve all folders starting with '_'
    $query = "SELECT * "
            . "FROM cmis:folder AS f "
            . "JOIN gofast:nodeproperties AS gfp ON f.cmis:objectId = gfp.cmis:objectId "
            . "WHERE f.cmis:name LIKE '\_%' ";
    
    $results = gofast_integrity_alfresco_cmis_query($query, $start, $count);
    
    //Format results
    foreach($results as $result){
        //$paths = array();
        $parents_ref = array();
        
        $properties = $result->properties;
        
        $output[] = array(
            "reference" => $properties["alfcmis:nodeRef"],
            "nid" => $properties["gofast:nid"],
            "paths" => array($properties["cmis:path"]),
            "parents_ref" => array($properties["cmis:parentId"]),
            "title" => $properties["cmis:name"],
            "is_group" => $properties["gofast:isgroup"],
            "bundle" => $properties['gofast:bundle']
        );
    }
    
    return $output;
}

/*
 * @package gofast_integrity
 * This fonction is the entry point of Alfresco folders integrity
 * It will retrieve all Alfresco folders not starting with '_'
 * 
 * @return array list of folders
 */
function gofast_integrity_alfresco_get_folders($start, $count){
    $output = array();
    
    //Prepare query to retrieve all folders starting with '_'
    $query = "SELECT * "
            . "FROM cmis:folder AS f "
            . "JOIN gofast:nodeproperties AS gfp ON f.cmis:objectId = gfp.cmis:objectId "
            . "WHERE f.cmis:name NOT LIKE '\_%' ";
    
    $results = gofast_integrity_alfresco_cmis_query($query, $start, $count);
    
    //Format results
    foreach($results as $result){
        //$paths = array();
        $parents_ref = array();
        
        $properties = $result->properties;
        
        if(strpos($properties['cmis:path'], "/Sites/surf-config") === 0
          || strpos($properties['cmis:path'], "/Dictionnaire de données") === 0
          || strpos($properties['cmis:path'], "/Espaces Utilisateurs") === 0 ){
            continue;
        }
        
        $output[] = array(
            "reference" => $properties["alfcmis:nodeRef"],
            "nid" => $properties["gofast:nid"],
            "paths" => array($properties["cmis:path"]),
            "parents_ref" => array($properties["cmis:parentId"]),
            "title" => $properties["cmis:name"],
            "is_group" => $properties["gofast:isgroup"],
            "bundle" => $properties['gofast:bundle'],
            "ismirrored" => $properties['gofast:ismirrored'],
        );
    }
    
    return $output;
}

/*
 * @package gofast_integrity
 * This fonction is the entry point of Alfresco documents integrity
 * It will retrieve all Alfresco documents in a defined range
 * 
 * @param integer $start The start of the range
 * @param integer $end the end of the range
 * @return array list of documents
 */
function gofast_integrity_alfresco_get_documents($start, $count){
    $output = array();
    
    //Prepare query to retrieve documents
    $query = "SELECT * "
            . "FROM cmis:document AS f "
            . "JOIN gofast:nodeproperties AS gfp ON f.cmis:objectId = gfp.cmis:objectId "
            . "WHERE f.cmis:name <> 'pdf' ";
    
    $results = gofast_integrity_alfresco_cmis_query($query, $start, $count);
            
    //Format results
    foreach($results as $result){
        $paths = array();
        $parents_ids = array();
        
        $properties = $result->properties;
        
        //Retrieve parents of this document using CMIS
        $parents = gofast_cmis_item_get_parent($properties["alfcmis:nodeRef"])->objectList;
        
        //Extracts paths of CMIS parents
        foreach($parents as $parent){
            $parent_path = $parent->properties["cmis:path"];
            
            //Exclusion condition, we are not in a GoFAST folder
            $exclusion = substr($parent_path, 0, 6) !== "/Sites" || substr($parent_path, 0, 18) === "/Sites/surf-config";
            
            if($exclusion){
                continue 2;
            }else{
                $paths[] = $parent->properties["cmis:path"];
                $parents_ids[] = $parent->properties["alfcmis:nodeRef"];
            }
        }
        
        $output[] = array(
            "reference" => $properties["alfcmis:nodeRef"],
            "nid" => $properties["gofast:nid"],
            "paths" => $paths,
            "parents" => $parents_ids,
            "title" => $properties["cmis:name"],
        );
    }
    
    return $output;
}

/*
 * @package gofast_integrity
 * Send a query to Alfresco using CMIS protocol
 * 
 * @param string $query The CMIS query
 * @param integer $start The start of the query range
 * @param integer $end The end of the query range
 * @return object See cmisapi_query
 */
function gofast_integrity_alfresco_cmis_query($query, $start = 0, $count = 1000000){
    module_load_include('api.inc', 'cmis');
    
    $query = urlencode($query);
    $query = urldecode($query);
    
    try {
      $repository = cmisapi_getRepositoryInfo();
      $repoId = !empty($repository->repositoryId) ? $repository->repositoryId : 'default';
      $options = array(
          "skipCount" => $start,
          "maxItems" => $count,
      );
      return cmisapi_query($repoId, $query, $options)->objectList;
    }
    catch (CMISException $e) {
      cmis_error_handler('cmis_query', $e);
    }
}