<?php

/**
 * @package gofast_cmis
 * This method get the alfresco ticket stored.
 */
function gofast_cmis_get_user_ticket() {
  if (gofast_cmis_check_alfresco_status() && !empty($_SESSION['gofast_user_alf_ticket'])) {
    return $_SESSION['gofast_user_alf_ticket'];
  }
  return FALSE;
}

/**
 * @package gofast_cmis
 * This method store the alfresco ticket for the current user.
 */
function gofast_cmis_set_user_ticket($ticket) {
  $_SESSION['gofast_user_alf_ticket'] = $ticket;
}


/**
 * @package gofast_cmis
 * This method revoke the ticket for the current user.
 */
function gofast_cmis_unset_user_ticket() {
  $_SESSION['gofast_user_alf_ticket'] = NULL;
}

/**
 * @package gofast_cmis
 * This function returns wether alfresco service is up or not.
 * @return boolean TRUE if alfresco is up, FALSE otherwise
 */
function gofast_cmis_check_alfresco_status() {
  // This is alfresco service status verification, if != 200, alfresco is down
  if (200 !== gofast_get_http_code('http://localhost:8080' . '/alfresco/')) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/**
 * @package gofast_cmis
 * This method validates the ticket using alfresco API.
 * If the ticket cannot be retrieved with itself, the user has lost its authentification ticket.
 * In this case, we generate the ticket again and store it for the user.
 *
 * @global type $user the user we validate
 * @return string the user ticket string
 */
function gofast_cmis_ticket_validate() {
  global $user;

  $user_ticket = gofast_cmis_get_user_ticket();
  $url = "http://localhost/alfresco/service/api/login/ticket/" . $user_ticket . "?alf_ticket=" . $user_ticket;
  if ($user_ticket === NULL || 200 !== gofast_get_http_code($url)) {
    $user_ticket = gofast_cmis_retrieve_and_store_ticket($user);
    return $user_ticket;
  }
  else {
    return $user_ticket;
  }
}

/**
 * @package gofast_cmis
 * This method retrieves alfresco ticket and stores it to user variable.
 * @param $user the user on which we generate and store the ticket.
 * @return string the ticket generated
 */
function gofast_cmis_retrieve_and_store_ticket($user) {
  $ticket = gofast_cmis_webservice_generate_alfresco_ticket($user->name);
  gofast_cmis_set_user_ticket($ticket);
  return $ticket;
}

/**
 * @package gofast_cmis
 * fonction qui renvoit l'id du repository courant (Alfresco)
 * necessaire pour utiliser l'api cmis.
 * S'il est impossible de récupérer le repository, c'est qu'il y a un problème
 * d'authentification, on délogue le user pour qu'il se reconnecte.
 *
 * @return type
 */
function gofast_cmis_get_repository() {
  global $repository_id;

  if (!gofast_cmis_check_alfresco_status()) {
    return FALSE;
  }

  if (!isset($repository_id)) {
    try {
      $repository = cmisapi_getRepositoryInfo();
      if ($repository !== NULL) {
        $repositoryInfo = $repository->repositoryInfo;
        $repository_id = $repositoryInfo['cmis:repositoryId'];
      }
      else {
        return $repository;
      }
    }
    catch (CMISException $e) {
      module_load_include('pages.inc', 'user');
      user_logout();
    }
  }
  return $repository_id;
}

/**
 * @package gofast_cmis
 * Returns a list of all the children of a specified folder (based on path).
 * Can return all the folders of a path or user accessible folder if the user is
 * set in the parameters.
 *
 * @global type $repository_id
 * @param string $base_path the path we want to lookup
 * @return array a collection of folders.
 */
function gofast_cmis_get_children($base_path, $filter_documents = "folders", $asAdmin = FALSE) {
  $item = gofast_cmis_item_get_by_path($base_path, $asAdmin);
  return isset($item->id) ? gofast_cmis_item_get_children($item->id, $asAdmin, $filter_documents) : array();
}

/**
 * @package gofast_cmis
 * This method return base path for remove store regarding node.
 *
 * @param type $node the node we want to retrieve base path
 * @return string the base path to return, depending on the node type.
 */
function gofast_cmis_node_get_base_path($node) {
  switch ($node->type) {
    case 'group':
    case 'organisation':
    case 'public':
    case 'extranet':
    case 'private_space':
      $path = "/Sites";
      break;
    default:
      $path = "/Sites";
      break;
  }
  return $path;
}

/**
 * @package gofast_cmis
 * This method returns the item id associated to a specified node.
 *
 * @param type $node the node on which we want its remote store id
 * @return string the node item id, null otherwise
 */
function gofast_cmis_node_get_item_id($node) {
  $wrapper = entity_metadata_wrapper('node', $node);
  if ($node->type === 'alfresco_item' || $node->type == 'article') {
    return $wrapper->{GOFAST_CMIS_REFERENCE_FIELD}->value();
  }
  else {
    if (gofast_og_is_space($node)) {
      return $wrapper->{GOFAST_CMIS_FOLDER_REFERENCE_FIELD}->value();
    }
    else {
      return null;
    }
  }
}

/**
 * @package gofast_cmis
 * Returns the main location path of a given repository id.
 * @param string $item_id the remote store item reference
 * @return string the path of the node reference.
 */
function gofast_cmis_item_get_main_location($item_id) {
  $node_id = gofast_cmis_node_get_by_reference($item_id);
  if ($node_id !== null) {
    $wrapper = entity_metadata_wrapper('node', node_load($node_id));

    return $wrapper->{GOFAST_CMIS_MAIN_LOCATION_FIELD}->value();
  }
  else {
    return null;
  }
}

/**
 * @package gofast_cmis
 * This function returns the node items ids for a given item id.
 * @param string $item_id the remote store item identifier
 * @return type
 */
function gofast_cmis_item_get_parents_item_ids($item_id) {
  return array_keys(gofast_cmis_item_get_parent($item_id)->objectsById);
}

/**
 * @package gofast_cmis
 * This method returns the (remote store) item id regarding the current node.
 * If the node has no parents, returns the (remote store) base path id corresponding to its type.
 *
 * @param type $node the node on which we want to remote store parent id
 * @return string the remote store id
 */
function gofast_cmis_node_get_parent_item_id($node) {
  $parent_node_id = _gofast_og_space_get_parent($node, FALSE, TRUE);
  $parent_node = !$parent_node_id ? FALSE : node_load($parent_node_id);
  return !$parent_node ? gofast_cmis_node_item_get_base_path($node)->properties['cmis:objectId'] : gofast_cmis_node_get_item_id($parent_node);
}

/**
 * @package gofast_cmis
 * This method moves an existing item to another folder in remote store.
 * It is trigger during the node update of an og node.
 *
 * @param type $node the node to move
 * @param boolean $asAdmin execute as admin?
 * @return string the moved item id
 */
function gofast_cmis_node_edit_item_move($space_node, $old_parent_node, $new_parent_node, $asAdmin = TRUE) {
  $item_id = gofast_cmis_node_get_item_id($space_node);
  $new_parent_item_id = gofast_cmis_node_get_item_id($new_parent_node);
  $old_parent_item_id = gofast_cmis_node_get_item_id($old_parent_node);

  return gofast_cmis_item_move(gofast_cmis_get_raw_item_id($item_id), gofast_cmis_get_raw_item_id($new_parent_item_id), gofast_cmis_get_raw_item_id($old_parent_item_id), $asAdmin);
}

/**
 * @package gofast_cmis
 * This method renames an existing item to another name in remote store.
 * It is trigger during the node update of an og node.
 *
 * @param type $node the node to rename
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return string the renamed item id
 */
function gofast_cmis_node_edit_item_rename($node, $asAdmin = TRUE) {
  $title = gofast_cmis_node_get_normalized_node_title($node);
  return gofast_cmis_item_rename(gofast_cmis_node_get_item_id($node), $title, $asAdmin);
}

/**
 * @package gofast_cmis
 * This method insert a new item in remote store.
 * It is trigger during the node presave of an og node.
 *
 * @param type $node the node to insert
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return string the created item id
 */
function gofast_cmis_node_edit_item_folder_insert($node, $asAdmin = TRUE) {
  $title = gofast_cmis_node_get_normalized_node_title($node);
  $parent_item_id = gofast_cmis_node_get_parent_item_id($node);

  return gofast_cmis_item_folder_insert($title, $parent_item_id, $asAdmin);
}

/**
 * @package gofast_cmis
 * This method get an item from remote store using its node.
 *
 * @param type $node the node we want to retrieve
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type
 */
function gofast_cmis_node_edit_item_get($node, $asAdmin = TRUE) {
  return gofast_cmis_item_get(gofast_cmis_node_get_item_id($node), $asAdmin);
}

/**
 * @package gofast_cmis
 * This method get node's parent of a given node from remote store.
 *
 * @param type $node the node on which we get its parent
 * @param type $asAdmin execute as admin? Defaults to TRUE.
 * @return string the parent item id
 */
function gofast_cmis_node_edit_item_get_parent($node, $asAdmin = TRUE) {
  return gofast_cmis_item_get_parent(gofast_cmis_node_get_item_id($node), $asAdmin);
}

/**
 * @package gofast_cmis
 * This method returns all the children of a node.
 *
 * @param type $node the node on which we get its children
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return array the children item ids
 */
function gofast_cmis_node_edit_item_get_children($node, $asAdmin = TRUE) {
  return gofast_cmis_item_get_children(gofast_cmis_node_get_item_id($node), $asAdmin);
}

/**
 * @package gofast_cmis
 * This method returns the base path item for a given node.
 * The base path is the root path of each kind of object types.
 *
 * @param type $node the node used to get it's base path
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type the remote store item
 */
function gofast_cmis_node_item_get_base_path($node, $asAdmin = TRUE) {
  return gofast_cmis_item_get_base_path(gofast_cmis_node_get_base_path($node), $asAdmin);
}

//-------------------------------------------------------------------------------------------------------

/**
 * @package gofast_cmis
 * This method moves an existing item to another folder in remote store.
 *
 * @param string $item_id the actual item id that will move
 * @param string $destination_item_id the destination item id
 * @param string $source_item_id the source item id. NULL for copy
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $moved_item the item that has moved
 */
function gofast_cmis_item_move($item_id, $destination_item_id, $source_item_id = NULL, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $moved_item = cmisapi_moveObject($repository_id, gofast_cmis_get_raw_item_id($item_id), gofast_cmis_get_raw_item_id($destination_item_id), gofast_cmis_get_raw_item_id($source_item_id), gofast_cmis_aspect_get_drupal_origin_property());


  $cached_item = &gofast_cmis_static_cache($item_id);
  $cached_item = $moved_item;

  $cmis_sudo_admin = FALSE;

  return $moved_item;
}

/**
 * @package gofast_cmis
 * This method removes an existing item to another folder in remote store.
 *
 * @param string $item_id the actual item id that will move
 * @param string $parent_folder_item_id the container item id from which we remove the item
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $removed_item whether the item was removed or not
 */
function gofast_cmis_item_remove_multifile_document($item_id, $parent_folder_item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $removed_item = cmisapi_removeObjectFromFolder($repository_id, gofast_cmis_get_raw_item_id($item_id), gofast_cmis_get_raw_item_id($parent_folder_item_id), gofast_cmis_aspect_get_drupal_origin_property());

  gofast_cmis_static_cache($item_id, TRUE);
  $cmis_sudo_admin = FALSE;

  return $removed_item;
}

/**
 * @package gofast_cmis
 * This method removes an existing folder item.
 *
 * @param string $item_id the actual item id that will move
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $removed_item whether the item was removed or not
 */
function gofast_cmis_item_remove_item($item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $removed_item = cmisapi_deleteObject($repository_id, gofast_cmis_get_raw_item_id($item_id));

  gofast_cmis_static_cache($item_id, TRUE);
  $cmis_sudo_admin = FALSE;

  return $removed_item;
}

function gofast_cmis_item_remove_folder($item_id ,$asAdmin = true){
 $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;
  $removed_item = cmisapi_deleteTree($repository_id , $item_id, array());

  gofast_cmis_static_cache($item_id, TRUE);
  $cmis_sudo_admin = FALSE;

  return $removed_item;
}
/**
 * @package gofast_cmis
 * This method gets the properties of an existing item in remote store.
 *
 * @param string $item_id the actual item id we would like to get
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $item_properties the item properties we retrieve
 */
function gofast_cmis_item_get_properties($item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  $cached_item = &gofast_cmis_static_cache($item_id . '_properties');
  if (isset($cached_item)) {
    return $cached_item;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $item_properties = cmisapi_getProperties($repository_id, gofast_cmis_get_raw_item_id($item_id));

  if ($item_properties !== FALSE) {
    $cached_item = $item_properties;
  }
  $cmis_sudo_admin = FALSE;
  return $item_properties;
}

/**
 * @package gofast_cmis
 * This method updates the properties of an existing item in remote store.
 *
 * @param string $item_id the actual item id that will be updated
 * @param array $properties array of item properties to update.
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $updated_item the item that has been updated
 */
function gofast_cmis_item_update_properties($item_id, $properties, $asAdmin = TRUE, $force_js = FALSE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  //if nid is false, it means we are in a space case
  $nid = gofast_ajax_file_browser_get_nid_from_reference($item_id);
  if($force_js == FALSE && $nid != false){
    $updated_item = cmisapi_updateProperties($repository_id, gofast_cmis_get_raw_item_id($item_id), array_merge($properties, gofast_cmis_aspect_get_drupal_origin_property()));
  }

  if(!isset($updated_item->id) || $force_js == TRUE || $nid == false){ //CMIS was not able to edit the item's properties
    $properties_js = array();
    foreach($properties as $cmis_key => $cmis_value){
      if(substr($cmis_key, 0, 4) === 'cmis'){ //cmis:xxx in a CMIS request must be xxx in JS call.
        $js_key = substr($cmis_key, 5);
        $js_value = $cmis_value;
      }
      else{
        $js_key = $cmis_key;
        $js_value = $cmis_value;
      }
      $properties_js[$js_key] = $js_value;
    }
    unset ($properties);
    $properties = $properties_js;

    gofast_cmis_webservice_item_update_properties($item_id, $properties, $asAdmin);
    $updated_item = gofast_cmis_item_get($item_id, $asAdmin);
  }
  $cached_item = &gofast_cmis_static_cache($item_id . '_properties');
  $cached_item = $updated_item;

  $cmis_sudo_admin = FALSE;

  return $updated_item;
}

/**
 * @package gofast_cmis
 * This function set the drupal origin property to true (to prevent alfresco rules to be done).
 * @param string $item_id the item that has been updated
 */
function gofast_cmis_item_update_drupalOrigin($item_id) {
  gofast_cmis_item_update_properties($item_id, array());
}

/**
 * @package gofast_cmis
 * This function reset the drupal origin to false.
 *
 * @param string $item_id the actual item id that will be updated
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $updated_item the item that has been updated
 */
function gofast_cmis_release_drupal_origin($item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;
  $updated_item = cmisapi_updateProperties($repository_id, gofast_cmis_get_raw_item_id($item_id), gofast_cmis_aspect_get_drupal_origin_reset_property());

  $cached_item = &gofast_cmis_static_cache($item_id . '_properties');
  $cached_item = $updated_item;

  $cmis_sudo_admin = FALSE;

  return $updated_item;
}

/**
 * @package gofast_cmis
 * This method renames an existing item to another name in remote store.
 *
 * @param string $item_id the actual item id that will be renamed
 * @param string $new_name the new name we want to set
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type the renamed item id
 */
function gofast_cmis_item_rename($item_id, $new_name, $asAdmin = TRUE) {
  return gofast_cmis_item_update_properties($item_id, array('cmis:name' => $new_name), $asAdmin);
}

/**
 * @package gofast_cmis
 * This method insert a new item in remote store to parent item based on its name.
 *
 * @param string $title the title of the folder item to insert
 * @param string $parent_item_id parent of the new item folder to insert
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $created_item the item created
 */
function gofast_cmis_item_folder_insert($title, $parent_item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $created_item = cmisapi_createFolder($repository_id, gofast_cmis_get_raw_item_id($parent_item_id), $title, gofast_cmis_aspect_get_drupal_origin_property());

  if (isset($created_item->properties['alfcmis:nodeRef'])) {
    $item_id = $created_item->properties['alfcmis:nodeRef'];

    $cached_item = &gofast_cmis_static_cache($item_id);
    $cached_item = $created_item;
  }

  $cmis_sudo_admin = FALSE;

  return $created_item;
}

/**
 * @package gofast_cmis
 * This method insert a new item in remote store to parent item based on its name.
 *
 * @param string $parent_item_id parent of the new item folder to insert
 * @param string $title the title of the folder item to insert
 * @param string $content the content of the file to insert
 * @param string $mimetype the mimetype of the file to insert
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return $created_item the item created
 */
function gofast_cmis_item_content_insert($parent_item_id, $title, $content, $mimetype, $options = array(), $asAdmin = FALSE) {
  $repository_id = gofast_cmis_get_repository();
  $options += gofast_cmis_aspect_get_drupal_origin_property();
  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $created_item = cmisapi_createDocument($repository_id, gofast_cmis_get_raw_item_id($parent_item_id), $title, $options, $content, $mimetype);

  if (isset($created_item->properties['alfcmis:nodeRef'])) {
    $item_id = $created_item->properties['alfcmis:nodeRef'];

    $cached_item = &gofast_cmis_static_cache($item_id);
    $cached_item = $created_item;
  }

  $cmis_sudo_admin = FALSE;

  return $created_item;
}

/**
 * @package gofast_cmis
 * This method get an item from remote store using its node.
 *
 * @param string $item_id the item id to get
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type
 */
function gofast_cmis_item_get($item_id, $asAdmin = FALSE) {
  $repository_id = gofast_cmis_get_repository();
//var_dump($repository_id);exit;
  if (!$repository_id) {
    return FALSE;
  }

  $cached_item = &gofast_cmis_static_cache($item_id);
  if (isset($cached_item)) {
    return $cached_item;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $item = cmisapi_getObject($repository_id, gofast_cmis_get_raw_item_id($item_id));

  if ($item !== FALSE) {
    $cached_item = $item;
  }
  $cmis_sudo_admin = FALSE;

  return $item;
}

/**
 * @package gofast_cmis
 * This method get an item from remote store using its path.
 *
 * @param type $path the path to use
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return Object the item object from alfresco
 */
function gofast_cmis_item_get_by_path($path, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  $cache = gofast_cmis_static_cache(null);
  $cached_item = array_filter($cache, function($item) use ($path) {
    return isset($item->properties['cmis:path']) && $item->properties['cmis:path'] === $path;
  });
  if (!empty($cached_item)) {
    return array_shift($cached_item);
  }

  // if we find a way to safely reset the folder cache each time it is modified, we will be able to use the caching below instead of the static caching above
  // $cache_id = "gofast_item_get_by_path_" . $path;
  // $cache_object = cache_get($cache_id);
  // if ($cache_object) {
  //   return $cache_object->data;
  // }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;
  $item = cmisapi_getObjectByPath($repository_id, rawurlencode($path));

  if (isset($item->properties['alfcmis:nodeRef'])) {
    $cached_item = &gofast_cmis_static_cache($item->properties['alfcmis:nodeRef']);
    $cached_item = $item;
    // cache_set($cache_id, $item, "cache", time() + 86400);
  }
  $cmis_sudo_admin = FALSE;

  return $item;
}

/**
 * @package gofast_cmis
 * This method get node's parent of a given node from remote store.
 *
 * @param string $item_id the remote store item identifier
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @param boolean $cache use cached items? Defaults to TRUE.
 * @return type
 */
function gofast_cmis_item_get_parent($item_id, $asAdmin = TRUE, $cache = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  $cached_item = &gofast_cmis_static_cache($item_id . '_parents');
  if (isset($cached_item) && $cache) {
    return $cached_item;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $parent_item = cmisapi_getFolderParent($repository_id, gofast_cmis_get_raw_item_id($item_id));

  $cached_item = $parent_item;
  $cmis_sudo_admin = FALSE;

  return $parent_item;
}

function gofast_cmis_activate_alfresco_connection() {
  $drupal_db_info = Database::getConnectionInfo()["default"];
  $alfresco_database = array_merge($drupal_db_info, array("database" => "alfresco", "username" => "alfresco"));
  unset($alfresco_database["port"]);
  unset($alfresco_database["prefix"]);
  // will add only if it has not been added yet
  Database::addConnectionInfo('default', 'alfresco', $alfresco_database);
}

/**
 * @package gofast_cmis
 * This method get node's parent of a given node from remote store.
 *
 * @param string $item_id the remote store item identifier
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type
 */
function gofast_cmis_item_get_object_parent($item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  $cached_item = &gofast_cmis_static_cache($item_id . '_parents');
  if (isset($cached_item)) {
    return $cached_item;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $parent_item =  cmisapi_getObjectParents($repository_id, gofast_cmis_get_raw_item_id($item_id));

  $cached_item = $parent_item;
  $cmis_sudo_admin = FALSE;

  return $parent_item;
}

/**
 * @package gofast_cmis
 * This method return the cmis url for getting parents. We use this methode instead of the classic CMIS way because
 * for documents with a lot of versions, the CMIS request to getting object is long
 *
 * @param string $item_id the remote store item identifier
 * @return type
 */
function gofast_cmis_item_get_parent_url($item_id) {
    //we have to get the current version label
  if (strpos($item_id, "workspace") === false) {
    $item_id = "workspace://SpacesStore/" . $item_id;
  }
    $list = gofast_cmis_webservice_item_get_versions($item_id, true);
    if(!is_array($list)){ //We usually get here when the content is deleted
      return;
    }
    if(!isset($list[0]->label)){
        $list[0]->label = "1.0";
    }
    $url = "http://localhost:8080/alfresco/api/-default-/public/cmis/versions/1.1/atom/parents?id=".$item_id.";".$list[0]->label;
    return $url;
}

/**
 * @package gofast_cmis
 * This method returns all the children of an item id
 *
 * @param string $item_id the remote store item identifier
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @param string $filter_documents "documents" to get only documents, "folders" to get only folders and "groups" to get only groups. leave empty for all or set "all"
 * @return type
 */
function gofast_cmis_item_get_children($item_id, $asAdmin = TRUE, $filter_documents = "all") {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  if ($filter_documents) {

    $children = gofast_cmis_webservice_item_get_descendants($item_id, $filter_documents,false, $cmis_sudo_admin);
  }
  else {
    $children = cmisapi_getDescendants($repository_id, gofast_cmis_get_raw_item_id($item_id));
  }
  $cmis_sudo_admin = FALSE;

  return $children;
}

/**
 * @package gofast_cmis
 * This method returns content of an item id
 *
 * @param string $item_id the remote store item identifier
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type
 */
function gofast_cmis_item_get_content($item_id, $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  if (!$repository_id) {
    return FALSE;
  }

  $cached_item = &gofast_cmis_static_cache($item_id . '_content');
  if (isset($cached_item)) {
    return $cached_item;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  $content = cmisapi_getContentStream($repository_id, gofast_cmis_get_raw_item_id($item_id));

  if ($content !== null) {
    $cached_item = $content;
  }
  $cmis_sudo_admin = FALSE;

  return $content;
}

/**
 * @package gofast_cmis
 * This method set content on an existing item id
 *
 * @param string $item_id the actual item id to update
 * @param mixed $content the content to set
 * @param type $contentType the mitype of the content
 * @param type $options an array of options
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type $updated_item the update item
 */
function gofast_cmis_item_set_content($item_id, $content = NULL, $contentType = NULL, $options = array(), $asAdmin = TRUE) {
  $repository_id = gofast_cmis_get_repository();

  $options += gofast_cmis_aspect_get_drupal_origin_property();

  if (!$repository_id) {
    return FALSE;
  }

  global $cmis_sudo_admin;
  $cmis_sudo_admin = $asAdmin;

  //Use REST API here, because there is a bug on CMIS setcontentstream function. If we don't have permission on the main location, ALfresco
  //refuse to update the doc, even if we have permission on the document
  //SEE https://srv01.ceo-vision.com/jira_new/browse/GOFAST-4752
  //
  //$updated_item = cmisapi_setContentStream($repository_id, gofast_cmis_get_raw_item_id($item_id), $content, $contentType, $options);
    $postfields = $content;
    global $user;
     $ticket = gofast_cmis_get_user_ticket();
        if($ticket == FALSE){
           $ticket = gofast_cmis_retrieve_and_store_ticket($user);
        }

    $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/".gofast_cmis_get_raw_item_id($item_id)."/content?alf_ticket=".$ticket."";
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_POST, 1);
    curl_setopt($curl, CURLOPT_HTTPHEADER, Array("Content-Type: application/octet-stream;"));
    curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "PUT"); // note the PUT here
    curl_setopt($curl, CURLOPT_URL, $url );
    curl_setopt($curl, CURLOPT_POSTFIELDS, $postfields);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    $return = curl_exec($curl);
    $decoded_return = json_decode($return);

   //check if the file has correctly been uploaded ( there are bugs sometimes...)
    gofast_cmis_static_cache($item_id, TRUE);
    $item = gofast_cmis_item_get($item_id);
    $version = $item->properties['cmis:versionLabel'];

    if($version != $decoded_return->entry->properties->{'cm:versionLabel'}){
        //upload has not be done, use another way to upload content
         watchdog("DEBUG CEO-Vision" , "problem uploading file using REST API, use CMIS instead");
         $decoded_return = cmisapi_setContentStream($repository_id, gofast_cmis_get_raw_item_id($item_id), $content, $contentType, $options);
    }

  $cached_item = &gofast_cmis_static_cache($item_id . '_content');
  $cached_item = $decoded_return;

  $cmis_sudo_admin = FALSE;

  return $decoded_return;
}

/**
 * @package gofast_cmis
 * This method returns the base path item for a given item path.
 * The base path is the root path of each kind of object types.
 * eg. for groups is /Sites/Groups/
 * eg. for private_space is /Sites/Espaces privés/
 * @param string $path the path used to get it's base path
 * @param boolean $asAdmin execute as admin? Defaults to TRUE.
 * @return type the remote store item
 */
function gofast_cmis_item_get_base_path($path, $asAdmin = TRUE) {
  return gofast_cmis_item_get_by_path($path, $asAdmin);
}

/**
 * @package gofast_cmis
 * This methode returns the normalized title for node.
 * Normalization is trailing "_" in front of each space.
 * Otherwise, keep the same name.
 * @param type $node the node to normalize
 * @return string the normalized title, wirh "_" at the beginning of a group, without otherwise
 */
function gofast_cmis_node_get_normalized_node_title($node) {
  if (gofast_og_is_space($node)) {
    if (gofast_og_is_user_private_space($node)) {
      $title = $node->name;
    }
    else {
      $title = $node->title;
    }
    if (substr($title, 0, 1) === "_") {
      return $title;
    }
    else {
      return "_" . $title;
    }
  }
  else {
    return $node->title;
  }
}

/**
 * @package gofast_cmis
 * This method returns the item reference in raw format (only the item id) without the string workspace://SpacesStore/
 * @param string $item_id the remote store item identifier
 * @return type
 */
function gofast_cmis_get_raw_item_id($item_id) {
  if ($item_id !== NULL) {
    return str_replace("workspace://SpacesStore/", "", $item_id);
  }
  return $item_id;
}

/**
 * @package gofast_cmis
 * Provides static variable storage for Gofast CMIS requests/data.
 *
 * @param string $name
 *  The request $name for which to set or retrieve data. If NULL, whole cache is
 *  returned. Note that an url si not necessarily unique for different requests
 *  since parameters might be sent via header options. In this case you will
 *  have to catenate parameters to prevent erasing another request cache
 *  variable.
 *
 * @param boolean $reset
 *  If TRUE, reset the cache for a specific $name (if set), or reset the whole
 *  cache if $name is NULL. This function's return value should not be used when
 *  TRUE is passed in.
 *
 * @return mixed
 *  If $name is set, the requested data for this specific $name, or an array of
 *  CMIS objects keyed by $name otherwise.
 */
function &gofast_cmis_static_cache($name, $reset = FALSE) {
  static $cache = array();
  // Check if dealing with a previously defined variable.
  //echo'<pre>';print_r($cache);echo '</pre>';
  if (!is_object($cache) && (isset($cache[$name]) || array_key_exists($name, $cache))) {
    if ($reset) {
      $cache[$name] = NULL;
    }
    return $cache[$name];
  }
  // No static variables exist.
  if (isset($name)) {
    // if ($reset) { Reset was called before a default is set. }
    // First call with new non-NULL $name. Initialize a new static variable.
    if (!is_object($cache)) {
      $cache[$name] = NULL;
      return $cache[$name];
    }

  }
  // $name == NULL
  if ($reset && !is_object($cache)) {
    // Reset all. This needs to be done one variable at a time so that
    // references returned by earlier invocations also get reset.
    foreach ($cache as $name => $data) {
      $cache[$name] = NULL;
    }
  }
  // As the function returns a reference, the return should always be a
  // variable.
  return $cache;
}

/**
 * @package gofast_cmis
 * This function returns the webdav path of a given node.
 * Node should be alfresco_item.
 * @param type $nid the node id to retrieve.
 * @return array a list of strings that points to webdav item(s).
 */
function gofast_cmis_node_get_webdav_path($nid) {
  $node = node_load($nid);
  if ($node->type !== "alfresco_item" && $node->type !== "article") {
    return FALSE;
  }
  $parents_webdav_paths = array();
  $filename = isset($node->{GOFAST_CMIS_FILENAME_FIELD}[LANGUAGE_NONE][0]["value"]) ? $node->{GOFAST_CMIS_FILENAME_FIELD}[LANGUAGE_NONE][0]["value"] : gofast_cmis_item_get(gofast_cmis_node_get_item_id($node))->properties["cmis:contentStreamFileName"];
  $parents = gofast_og_get_parent($node);
  if ($parents !== FALSE) {
    foreach ($parents as $parent_nid) {
      $parents_webdav_paths[$parent_nid] = gofast_cmis_space_get_webdav_path($parent_nid) . '/' . $filename;
    }
  }
  return $parents_webdav_paths;
}

function gofast_cmis_node_get_reference_by_path($node) {
  if ($node->type !== "alfresco_item" && $node->type !== "article") {
    return FALSE;
  }
  $item_path = $node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value'] . '/' . $node->{GOFAST_CMIS_FILENAME_FIELD}[LANGUAGE_NONE][0]['value'];
  $item = gofast_cmis_item_get_by_path($item_path);
  return !isset($item->id) ? $item->properties['alfcmis:nodeRef'] : FALSE;
}

/**
 * Retreive an alfresco_reference based on node nid
 * @param int $nid
 * @return alf_reference if found, FALSE if no or too much maching item found
 */
function gofast_cmis_node_get_reference_by_nid($nid){

   usurp(1);

  $start = 0;
  $count = 1000000;
  $alf_ref = FALSE;

  $query = "SELECT * "
    . "FROM cmis:document AS f "
    . "JOIN gofast:nodeproperties AS gfp ON f.cmis:objectId = gfp.cmis:objectId "
    . "WHERE gfp.gofast:nid = '$nid' ";

  $results = gofast_integrity_alfresco_cmis_query($query, $start, $count);
  if (count($results) == 1) {
   $alf_ref = $results[0]->properties['alfcmis:nodeRef'];
  }else{
    foreach($results as $key => $result){ 
      if( strpos($result->properties['cmis:name'], ".html.html" ) > -1 ) {
        // uwanted wiki duplicate => to be deleted
        gofast_cmis_item_remove_item($result->properties['alfcmis:nodeRef'], TRUE );
      }else{
        $alf_ref = $result->properties['alfcmis:nodeRef'];
        
      }
    }
  }

   usurp(FALSE);

  return $alf_ref;
}

/**
 * @package gofast_cmis
 * This function returns the webdav path of a space.
 * Node should be space only.
 * @param type $space_nid the space node id to retrieve.
 * @return string the webdav path of the space.
 */
function gofast_cmis_space_get_drupal_path($space_nid) {
  if (!gofast_og_is_space(node_load($space_nid))) {
    return;
  }
  $group = node_load($space_nid);
  if($group->type == "private_space"){
      $author = user_load($group->uid);
      $private_space_path = "/".$author->name;
      return $private_space_path;
  }

  while(gofast_og_get_parent(node_load($space_nid)) != null){
     $path = '/' . (node_load($space_nid)->title) . $path;
     $space_nid = gofast_og_get_parent(node_load($space_nid));
  }
   $path = '/' . (node_load($space_nid)->title) . $path;
   return $path;
}

/**
 * @package gofast_cmis
 * This function returns the webdav path of given spaces
 * Node should be space only.
 * @param type $space_nids Array of spaces node id to retrieve.
 * @return string the webdav path of the space.
 */
function gofast_cmis_space_get_drupal_path_multiple_nodes($space_nids = array()) {

  $paths = array();

  $groups = node_load_multiple($space_nids);

  foreach ($groups as $group) {

    $path = '';
    if (!gofast_og_is_space) {
      $path = null;
    } else {

      if ($group->type == "private_space") {
        $author = user_load($group->uid);
        $private_space_path = "/" . $author->name;
        $paths[$group->nid] = $private_space_path;
      } else {

        $curr_group = $group;
        $path = '';

        while (gofast_og_get_parent($curr_group) != null) {
          $path = '/' . ($curr_group->title) . $path;
          $curr_group = gofast_og_get_parent($curr_group, TRUE);
        }
        $path = '/' . ($curr_group->title) . $path;
      }
    }
    $paths[$group->nid] = $path;
  }
  return $paths;
}

/**
 * @package gofast_cmis
 * This function returns the webdav path of a space.
 * Node should be space only.
 * @param type $space_nid the space node id to retrieve.
 * @return string the webdav path of the space.
 */
function gofast_cmis_space_get_drupal_path_on_browser($space_nid) {
  if (!gofast_og_is_space(node_load($space_nid))) {
    return;
  }
  $item_id = gofast_cmis_node_get_item_id(node_load($space_nid));
  $cmis_object = gofast_cmis_item_get($item_id);
  if ($cmis_object->properties["cmis:path"] == null){
      $_POST['gofast_og_wrong_path'] = TRUE;
      return gofast_cmis_space_get_drupal_path_on_browser(gofast_og_get_parent(node_load($space_nid)));
  }
  $path = $cmis_object->properties["cmis:path"];
  return $path;
}

/**
 * @package gofast_cmis
 * This function returns the webdav path of a space.
 * Node should be space only.
 * @param type $space_nid the space node id to retrieve.
 * @return string the webdav path of the space.
 */
function gofast_cmis_space_get_webdav_path($space_nid) {
  $ret = '/Sites';
  if (!empty($space_nid)) {
    $parts = explode('/', gofast_cmis_space_get_drupal_path($space_nid));
    $ret .= implode('/_', $parts);
  }
  $ret = str_replace("\\", ",", $ret);
  return $ret;
}


/**
 * @package gofast_cmis
 * This function returns the webdav path of a space that does not rely on LDAP fields.
 * Node should be space only.
 * @param type $space_nid the space node id to retrieve.
 * @return string the webdav path of the space.
 */
function gofast_cmis_space_get_webdav_path_node_page($space_nid) {
  $ret = '';
  if (!empty($space_nid)) {
    $parts = explode('/', gofast_cmis_space_get_drupal_path_on_browser($space_nid));
    $ret .= implode('/', $parts);
  }
  $ret = str_replace("\\", ",", $ret);
  return $ret;
}

/**
 * @package gofast_cmis
 * This function generates a drupal path from webdav path.
 * @param type $array_paths
 * @return type
 */
function gofast_ztree_get_drupal_path_from_webdav_path($array_paths = array()) {
  $drupal_paths = array();
  foreach ($array_paths as $key => $webdav_path) {
    $path_without_base = str_replace("/Sites", "", $webdav_path);
    $drupal_path = preg_replace("/\/_/", "/", $path_without_base);
    $drupal_paths[$key] = $drupal_path;
  }
  return $drupal_paths;
}

/**
 * @package gofast_cmis
 * This function returns a property to indicate the following CMIS action with come from drupal.
 * @return type
 */
function gofast_cmis_aspect_get_drupal_origin_property() {
    return array();
  return array("gofast:origin" => 'true');
}

/**
 * @package gofast_cmis
 * This function returns a property to indicate futurs CMIS action won't come anymore from drupal.
 * @return type
 */
function gofast_cmis_aspect_get_drupal_origin_reset_property() {
  return array("gofast:origin" => 'false');
}

/**
 * This function allows to detect item language by extraction of the content.
 * @global type $user the current user
 * @global type $tika_runs a flag that indactes tika is running
 * @param string $node_ref the node reference to analyse
 * @return string the lang code, und if none found
 */
 function gofast_cmis_item_detect_document_language($node_ref, $account = NULL , $detect_language_by_file = NULL) {
  // This is the option set in the CMIS Settings panel
  $language_auto_detect_default_value = variable_get('language_auto_detection', 1);

  if ($account === NULL) {
    global $user;
    $account = $user;
  }

  // Auto detect language option is not set or set to OFF
  if ($language_auto_detect_default_value === 0) {
    return $account->language;
  }

  if ($node_ref !== NULL) {
    // Get the remote file content so we can extract language
    $content = gofast_cmis_item_get_content($node_ref);
    $file_id = gofast_cmis_get_raw_item_id($node_ref);

    $public_path = DRUPAL_ROOT . '/' . variable_get('file_public_path', conf_path() . '/files');
    $file_path = "{$public_path}/{$file_id}";
    $written_file = fopen($file_path, 'w+');
    fwrite($written_file, $content);
    fclose($written_file);
  }
  else {
    if (!isset($detect_language_by_file)){
        // We want to detect language from dropped file (d&d)
        $dropped_file = variable_get($user->name . "_file_form_populate", "default");
        $file_id = $dropped_file["file_name"];

        $read_file = fopen($dropped_file["file_path"], "r");
        $content = fread($read_file, filesize($dropped_file["file_path"]));

        $file_path = $dropped_file["file_path"];
    }else{


        $file_id = $detect_language_by_file->filename;
        $read_file = fopen($detect_language_by_file->uri, "r");
        $content = fread($read_file, $detect_language_by_file->filesize);

        $file_path = DRUPAL_ROOT . '/' . variable_get('file_public_path', conf_path() . '/files') . '/file_tmp_detect_language.txt' ;
        $written_file = fopen($file_path, 'x+');
        fwrite($written_file, $content);
        fclose($written_file);

    }
  }

  $command = sprintf('java -jar %s --language %s', GOFAST_TIKA_PATH, $file_path);

  // Activate "tika_runs" flags.
  global $tika_runs;
  $tika_runs = $file_id;
  //variable_set('gofast_cmis_tika_is_working', $file_id);

  ini_set('memory_limit', '128M');
  $result = array();

  exec($command, $result);

  // Release memory and flags.
  ini_set('memory_limit', '512M');
  //variable_del('gofast_cmis_tika_is_working');
  $tika_runs = FALSE;
  if ($node_ref !== NULL) {
    gofast_cmis_purge_published_temp_file($file_path);
  }
  if (!isset($detect_language_by_file)){
    //gofast_cmis_purge_published_temp_file($file_path);
  }

  $language_list = language_list();
  if (isset($result[0]) && isset($language_list[$result[0]])) {
    $language = $result[0];
  }
  else {
    $language = LANGUAGE_NONE;
  }

  return $language;
}

/**
 * Returns whether a node is locked or not.
 * @param type $node
 * @return mixed FALSE if not alfresco_item or not locked, the user if locked.
 */
function gofast_cmis_node_is_locked($node) {
  $node_locked = FALSE;
  if($node->type === 'alfresco_item' || $node->type === 'article') {
    $node_reference = gofast_cmis_node_get_item_id($node);
    $lock_state = gofast_cmis_webservice_execute_request("getlocked", $node_reference);
    if($lock_state !== 'nolocked') {
      $node_locked = user_load_by_name(array('name' => trim($lock_state)));
    }
  }
  return $node_locked;
}

function gofast_cmis_node_get_lock($node) {
  return isset($node->cmis_node_lock) ? $node->cmis_node_lock : gofast_cmis_webservice_execute_request("getlocked", gofast_cmis_node_get_item_id($node));
}

/*
 * fonction qui archive un noeud passé en parametre
 */
function gofast_cmis_node_archive($node, $manually = false) {
  if (node_access('update', $node) && user_access('administer revisions')) {

    //on change l'état du noeud en "Archivé"
    $archived_taxonomy_term = taxonomy_get_term_by_name("Pre-Archived", 'state');
    $archived_taxonomy_term_id = reset($archived_taxonomy_term)->tid;
    $node->{'field_state'}[LANGUAGE_NONE][0]['tid'] = $archived_taxonomy_term_id;

    //Si c'est un noeud de type document, on appel le script Alfresco qui mettra tout le monde en lecture seul (sauf adm);
    //je change les droits du document
    // puis je supprime ses versions intermédiaires
    if ($node->type == "alfresco_item" || $node->type == "article") {
      $node_ref = gofast_cmis_node_get_item_id($node);
      //je change le owner du document pour ne pas que l'auteur puisse continuer de la modifier
      gofast_cmis_webservice_item_set_owner($node_ref);

      //je supprime les version intermédiaires
      gofast_cmis_delete_minor_versions($node, true);

      gofast_cmis_webservice_item_archive($node_ref);
    }
    if ($manually == false) {
      node_save($node);
    }
    return $node;
  }
}

function gofast_cmis_node_unarchive($node, $manually = false) {
  $node->field_state[LANGUAGE_NONE] = array();
  if ($node->type == "alfresco_item" || $node->type == "article") {
    $node_ref = gofast_cmis_node_get_item_id($node);
    gofast_cmis_webservice_item_archive($node_ref, TRUE);
  }
  if ($manually == false) {
     node_save($node);
  }
}

/*
 * fonction qui archive le groupe recu en parametre
 * @TODO : Update function to match GF3 code
 */
function ceo_vision_archive_group($group) {
  //tout d'abord on verifie si le user a le droit d'archiver ce groupe
  if (ceo_vision_archive_has_right($group)) {
    //on archive tous les documents de ce groupe
    $children = og_group_child_nids($group->nid);
    if (count($children) > 0) {
      foreach ($children as $key => $mynode_nid) {
        $mynode = node_load($mynode_nid);
        if (isset($mynode->nid)) {
          watchdog("gofast archive node", $mynode->nid);
          ceo_vision_archive_node($mynode);
        }
      }
    }

    //on passe tous les membres de ce groupe en lecture seule (sauf adm). d'abord on change le user courant car je ne sais pas trop pourquoi, un user ne peut pas
    //ce mettre lui même read only dans un groupe
    $members = get_members_id_group($group->nid);

    global $user;
//        $original_user = $user;
//        session_save_session(FALSE);
//        $user = user_load(array('uid' => ceo_vision_ui_get_id_subadmin())); // D7: use user_load(1);
    if (count($members) > 0) {
      foreach ($members as $member) {
        if ($member != ceo_vision_ui_get_id_subadmin()) {
          watchdog("gofast archive add user read only", $member);
          //si le user est l'auteur du groupe, il faut d'abord changer l'auteur de ce groupe pour pouvoir passer ce user en lecture seul
          if ($member == $group->uid) {
            watchdog("gofast archive change author", $member);
            $group->uid = ceo_vision_ui_get_id_subadmin();
            $group = ceo_vision_save_node_technicly($group);
          }
          og_save_subscription($group->nid, $member, array('is_admin' => 0));

          $member_object = user_load($member);
          if (!ceo_vision_is_read_only_group($group->nid, $member_object)) {

            $return_ro = ceo_vision_add_user_read_only($group, $member, true);
            watchdog("debug return RO " . $member, $return_ro);
          }
        }
      }
    }

    //on remplit le champs CCK field_archive a la valeur 1
    $group->field_archive[0]["value"] = 1;
    node_save($group);

    //on restore le user courant
//        $user = $original_user;
//        session_save_session(TRUE);
  }
  else {
    return false;
  }
}

/**
 * This function extracts the subject of an eml stored on alfresco.
 * Beware not to try to detect name of another type of file, it will return empty string.
 * @global type $tika_runs
 * @param type $node_ref
 * @return type
 */
function gofast_cmis_item_eml_extract_name($node_ref) {
  if ($node_ref !== NULL) {
    // Get the remote file content so we can extract the subject
    $content = gofast_cmis_item_get_content($node_ref);
    $file_id = gofast_cmis_get_raw_item_id($node_ref);

    $public_path = DRUPAL_ROOT . '/' . variable_get('file_public_path', conf_path() . '/files');
    $file_path = "{$public_path}/{$file_id}";
    $written_file = fopen($file_path, 'w+');
    fwrite($written_file, $content);
    fclose($written_file);
  }

  $command = sprintf('java -jar %s -x %s', GOFAST_TIKA_PATH, $file_path);

  // Activate "tika_runs" flags.
  global $tika_runs;
  $tika_runs = $file_id;

  ini_set('memory_limit', '128M');
  $result = array();

  exec($command, $result);

  // Release memory and flags.
  ini_set('memory_limit', '512M');
  $tika_runs = FALSE;
  if ($node_ref !== NULL) {
    gofast_cmis_purge_published_temp_file($file_path);
  }

  $output = '';
  foreach ($result as $res) {
    if (strpos($res, "<title>") === 0) {
      $output = strip_tags($res);
      break;
    }
  }
  watchdog("Extract subject EML", $output);
  return $output;
}

function gofast_cmis_invalidate_cache_user($uid){
    watchdog("debug invalid cache user", $uid);
    unlink(GOFAST_CMIS_PATH_CACHE.'/alf_emplacements_'.$uid);
}

/**
 * Return all space on which the user is administrator
 * (exept Public => membership managed by GoFAST plateform itself)
 * @param type $uid
 * @param type $type
 * @return type
 */
function gofast_cmis_get_emplacements_managed($uid, $type = "groupsfolders"){

   $temps_debut = microtime(true);

   if(is_object($uid)){
      $my_user =  $uid;
   }else{
    $my_user = user_load($uid);
   }
   $spaces = gofast_og_get_managed_spaces($my_user);
   if(count($spaces) > 0 ){
       foreach($spaces as $gid){
           $path = "/Sites".gofast_cmis_space_get_drupal_path($gid);
           if(strpos($path, "/Sites/Public") === false){
                $liste[$gid] = $path;
           }
       }
   }

   $temps_fin = microtime(true);
   watchdog("debug temps exec get emplacement by role", round($temps_fin - $temps_debut, 4));
   return $liste;
}

function gofast_cmis_get_emplacements_cache($uid, $type = "groupsfolders"){
    $temps_debut = microtime(true);
   return array();
   $filename = GOFAST_CMIS_PATH_CACHE."/alf_emplacements_".$uid;

   //on verifie si le fichier est trop ancien, pour le régénérer si besoin
    $date_cache = @filemtime($filename);

    //60minutes
    if(time() - $date_cache > 60*60){
        $handle = false;
        @unlink(GOFAST_CMIS_PATH_CACHE.'/alf_emplacements_'.$uid);
    }else{
        $handle = @fopen($filename, "r");
    }


   if($handle == false){
       watchdog("debug recreate file emplacement", $uid);

       $all_path = array();
       $my_user = user_load($uid);
        $spaces = gofast_og_get_spaces_by_user($my_user);
        $all_path += $spaces;
             $paths = gofast_cmis_get_children("/Sites/", $type);
        foreach(array_flip($paths) as $key => $path) {
          $all_path[$key] = $path;
        }
       gofast_cmis_set_emplacements_cache($uid, $all_path);
       $handle = @fopen($filename, "r");
   }
   $liste = @fread($handle, filesize($filename));
   @fclose($handle);

   $liste = explode("\n", $liste);
   $formatted_liste = array();
   foreach($liste as $element_liste){
       $array_element_liste = explode("::*::", $element_liste);
       if($array_element_liste[0] !== 0 && $array_element_liste[0] != ""){
        $formatted_liste[$array_element_liste[0]] = $array_element_liste[1];
       }
   }

   $liste = $formatted_liste;
   $temps_fin = microtime(true);
   watchdog("debug temps exec get emplacement cache", round($temps_fin - $temps_debut, 4));
   return $liste;
}

function gofast_cmis_set_emplacements_cache($uid, $liste){
    $string_liste = "";
    foreach($liste as $gid=>$path){
        $string_liste .= $gid."::*::".$path."\n";
    }

    $file = fopen(GOFAST_CMIS_PATH_CACHE."/alf_emplacements_".$uid, "w+");
    fwrite($file,$string_liste);
    fclose($file);
}


function gofast_cmis_get_templates_option() {
   //$tids_template = gofast_xeditable_terms_get_from_array(GOFAST_VID_TAGS, array('Template', 'template'));
    $tids_template =  taxonomy_get_term_by_name("Template", "tags");
    $nids = array();
    if(count( $tids_template) > 0){
       foreach($tids_template as $tid=>$term){
         $nids = array_merge($nids, taxonomy_select_nodes($tid, FALSE));
      }
    }


  $template_array = array();
  if (count($nids) > 0) {
    $query = db_select('field_revision_' . GOFAST_CMIS_LOCATIONS_FIELD, 'f');
    $query->distinct();
    $query->join('node', 'n', 'n.nid = f.entity_id');
    $query->join('field_revision_' . GOFAST_CMIS_REFERENCE_FIELD, 'r', 'r.entity_id = f.entity_id');
    $query->join('field_revision_field_filename', 'fn', 'fn.entity_id = f.entity_id');
    $field_values = $query->fields('f', array('entity_id', GOFAST_CMIS_LOCATIONS_FIELD . '_value'))
        ->fields('r', array(GOFAST_CMIS_REFERENCE_FIELD . '_value'))
        ->fields('n', array('title', 'language'))
        ->fields('fn', array('field_filename_value'))
        ->condition('f.entity_type', "node")
        ->condition('f.entity_id', array_keys(array_flip($nids)), 'IN')
        ->execute()
        ->fetchAll();
    global $user;
    if (count($field_values) > 0) {
      $already_get_gid = array();
      foreach ($field_values as $node_values) {

        // WARNING !! Should find another way to retreive node (the following takes too much times) !!
        //$gid = gofast_og_get_group_id_from_title_without_cmis($node_values->field_emplacement_value, true);

       if(!isset($already_get_gid[$node_values->field_emplacement_value])){
         $gid = gofast_og_get_group_id_from_title_without_cmis($node_values->field_emplacement_value, true);
         $already_get_gid[$node_values->field_emplacement_value]=$gid;
       }else{
         $gid = $already_get_gid[$node_values->field_emplacement_value];
      }

       $group = node_load($gid);
       $can_access = gofast_og_node_access($group, 'view', $user);

        $is_other_private_space = false;
        if($group->type == 'private_space' && $group->uid !== $user->uid){
            $is_other_private_space = true;
        }

        if ($can_access != NODE_ACCESS_DENY && $can_access != NULL && !$is_other_private_space) {

          // Check if current user have access to this space (otherwise dont show it)
          if (strpos(gofast_access_spaces(gofast_og_get_group_id_from_title_2($node_values->field_emplacement_value, TRUE, TRUE)), 'unlocked') !== FALSE){
            // Show all spaces user have access to if TEMPLATE is multifile
            if (isset($template_array[$node_values->field_reference_value])){
                $template_array[$node_values->field_reference_value]->path[] = $node_values->field_emplacement_value . "/" . $node_values->field_filename_value;
            }else{
                $node_object = new stdClass();
                $node_object->name = $node_values->field_filename_value;
                $node_object->nid = $node_values->entity_id;
                $node_object->path[] = $node_values->field_emplacement_value . "/" . $node_values->field_filename_value;
                $node_object->id = $node_values->field_reference_value;
                $node_object->language = $node_values->language;
                $template_array[$node_values->field_reference_value] = $node_object;
              }
          }

        }
      }
    }
  }
  else {
    $template_array = array();
  }
  return $template_array;
}

/**
 * Function to get all Folders Templates locate in Sites/TEMPLATES/FOLDER
 *
 * @return $template_array the array of folders templates
 */
function gofast_cmis_get_folder_templates_option() {

    $template_array = array();
    $repository_id = gofast_cmis_get_repository();
    $path = '/Sites/FOLDERS TEMPLATES';
    $alfresco_path = str_replace("/alfresco/webdav", "", $path);
    $folder_item = gofast_cmis_item_get_by_path($alfresco_path);
    $descendants = gofast_cmis_webservice_item_get_descendants($folder_item->id, "folders",true,true);
    foreach ($descendants as $descendant){
        $descendant = gofast_cmis_item_get_by_path($descendant);
        $folder_reference = $descendant->properties['alfcmis:nodeRef'];
        $descendant_folder = gofast_cmis_webservice_item_get_descendants($folder_reference,'all',false,true);
        $folder_path = $descendant->properties['cmis:path'];
        $folder_name = $descendant->properties['cmis:name'];
        $template_array[$folder_reference]['name'] = $folder_name;
        $template_array[$folder_reference]['path'] = $folder_path;
        $template_array[$folder_reference]['id'] = $folder_reference;
        $template_array[$folder_reference]['descendants'] = $descendant_folder;
    }
    return $template_array;
}

function gofast_cmis_detect_pdf_image($node){

    //if the node is not a pdf doc, return false
    if(strtolower(extract_file_extension($node->title)) != "pdf"){
        return false;
    }
    global $cmis_sudo_admin;
    $cmis_sudo_admin = true;
    $repository_id = gofast_cmis_get_repository();
    $content = cmisapi_getContentStream($repository_id, $node->field_reference[LANGUAGE_NONE][0]["value"]);
    $file_path = "/var/www/d7/sites/default/files/swf/test_pdf_ocr";
    $file = fopen($file_path, "w+");
    fwrite($file, $content);
    fclose($file);
    $command = sprintf('java -jar %s -T %s', GOFAST_TIKA_PATH, $file_path);
    $result = array();
    try{
       ini_set('memory_limit', '-1');
       exec($command , $result );
     }catch (Exception $e) {

     }
     $result = implode('',$result);
     if($result == ""){
        return true;
     }else{
        return false;
     }
}

/*
 * function to convert ( on the alfresco side, on the mimetype metadata and on the extension ) a document on an old office format (IE doc) into new format (docx)
 * This function is mainly used to convert a doc after it was edited with onlyoffice
 */
function gofast_cmis_convert_old_office_format_to_new($node){
    watchdog("debug convert document", $node->nid);
    //get the cmis object
    $cmis_object = gofast_cmis_node_edit_item_get($node);
    $current_mimetype = $cmis_object->properties["cmis:contentStreamMimeType"];
    if($current_mimetype == "application/vnd.ms-excel"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        $new_extension = "xlsx";
        $old_extension = "xls";
    }elseif($current_mimetype == "application/msword"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        $new_extension = "docx";
        $old_extension = "doc";
    }elseif($current_mimetype == "application/vnd.ms-powerpoint"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
        $new_extension = "pptx";
        $old_extension = "ppt";
    }elseif($current_mimetype == "application/vnd.oasis.opendocument.text"){
         $new_mimetype = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        $new_extension = "docx";
        $old_extension = "odt";
    }elseif($current_mimetype == "application/vnd.oasis.opendocument.presentation"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
        $new_extension = "pptx";
        $old_extension = "odp";
    }elseif($current_mimetype == "application/vnd.oasis.opendocument.spreadsheet"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
        $new_extension = "xlsx";
        $old_extension = "ods";
    }elseif($current_mimetype == "application/rtf"){
        $new_mimetype = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
        $new_extension = "docx";
        $old_extension = "rtf";
    }

    if($new_mimetype){
        //change node title (drupal) and filename (alfresco)
        $new_title = str_replace(".".$old_extension, ".".$new_extension, $node->title);
        $node->title = $new_title;
        $new_filename = str_replace(".".$old_extension, ".".$new_extension, $node->field_filename[LANGUAGE_NONE][0]["value"]);
        $node->field_filename[LANGUAGE_NONE][0]["value"] = $new_filename;

        $node = gofast_prepare_node_save_technically($node);
        $_POST['prevent_automatic_multifilling'] = true;
        node_save($node);

        //change mimetype (alfresco)
        $old_file_name = $cmis_object->properties["cmis:name"];
        $new_file_name = str_replace(".".$old_extension, ".".$new_extension, $old_file_name);
        $properties = array("cmis:mimetype" => $new_mimetype);
        $item_id = $cmis_object->properties["alfcmis:nodeRef"];
        $updated = gofast_cmis_item_update_properties($item_id, $properties, FALSE, TRUE);

    }
    return $updated;
}

function gofast_cmis_get_all_multifilled_documents_from_gid($gid){

  $res = db_query("select node.nid,node.title,og_membership.gid from {node} INNER JOIN {og_membership} ON node.nid=og_membership.etid WHERE (SELECT COUNT(*) FROM og_membership where og_membership.etid=node.nid AND og_membership.field_name='og_group_content_ref')>1 AND node.status=1 AND og_membership.gid=:gid", array(":gid" => $gid));
  $return = array();
  foreach ($res as $node_infos) {

      $return[$node_infos->nid] = $node_infos->title;
  }

  return $return;
}

//this function is called when the document cannot be restored into the original location ( probably because it doesn't exists anymore)
//try to move it (using cmis) into the current user private space
function gofast_cmis_restore_document_alfresco_into_private_space($node){
    global $user;
    module_load_include('inc', 'gofast_cmis', 'gofast_cmis_cron');
    $private_space_gid = gofast_og_get_user_private_space($user, FALSE);
    $destination_item_id = gofast_cmis_node_get_item_id(node_load($private_space_gid));

    $ref = gofast_cmis_get_raw_item_id(gofast_cmis_node_get_item_id($node));
    $url = 'http://localhost:8080/alfresco/service/api/node/content/archive/SpacesStore/' . $ref . '/'.rawurlencode($node->title)."?a=true";
    $username = "admin";
    $password = gofast_get_admin_pwd();

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
    curl_setopt($ch, CURLOPT_URL, $url);
    $buffer = curl_exec($ch);


 // Si le document n'est pas "exclu" on créé un fichier dans lequel on met
  // le contenu brut du document afin que Tika puisse en extraire le texte.
  $file_path = DRUPAL_ROOT . '/' . variable_get('file_public_path', conf_path() . '/files');
  $file = fopen("{$file_path}/_gofast_restore_deleted_tmp", 'w+');
  fwrite($file, $buffer);
  fclose($file);

    $inserted_item = gofast_cmis_item_content_insert($destination_item_id, $node->title, $buffer, file_get_mimetype($node->title), array(), false);
    if(isset($inserted_item->properties["alfcmis:nodeRef"])){
        $node->field_reference[LANGUAGE_NONE][0]["value"] = $inserted_item->properties["alfcmis:nodeRef"];
        $node->status = 1;
        $node = gofast_prepare_node_save_technically($node);
        $ruid = $node->revision_uid;
        node_save($node);
        db_update('node_revision')
          ->fields(array('uid' => $ruid))
          ->condition('nid', $node->nid)
          ->execute();
        cache_clear_all("field:node:$node->nid", 'cache_field');
        gofast_cmis_process_item_update_node($inserted_item, $node->nid, $user->name, false);
        return true;
    }else{
        return false;
    }


}

  function gofast_cmis_synchronize_version_publication($source_node, $existing_publication_node, $comment = ""){

    //we get the source version number
    $repositoryId = gofast_cmis_get_repository();
    $source_object=cmisapi_getObject($repositoryId, $source_node->reference);
    $version_source = $source_object->properties["cmis:versionLabel"];
    //we get the publication version number
    $publication_object=cmisapi_getObject($repositoryId, $existing_publication_node->reference);
    $version_publication = $publication_object->properties["cmis:versionLabel"];

    $before_point_source = explode('.', $version_source);
    $before_point_source = $before_point_source[0];

    $before_point_publication = explode('.', $version_publication);
    $before_point_publication = $before_point_publication[0];

    global $user;
    $username = $user->name;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }

    if($before_point_source == $before_point_publication){
        //we tag the publication in major version
       // exec("curl --user $username:".$password." 'http://localhost:8080/alfresco/service/set/version/major/?comment=".rawurlencode($comment)."&reference=".$existing_publication_node->reference."'");

        //we tag the origin document as many time as needed for having the same than source node
       // exec("curl --user $username:".$password." 'http://localhost:8080/alfresco/service/set/version/major/?comment=".rawurlencode($comment)."&reference=".$source_node->reference."'");

    }else{

        //we tag the origin document as many time as needed for having the same than source node
        //exec("curl --user $username:".$password." 'http://localhost:8080/alfresco/service/set/version/major/?comment=".rawurlencode($comment)."&reference=".$source_node->reference."'");
        //$before_point_source++;

        //then we tag the publication as many time is needed
        $number_iteration =  $before_point_source - $before_point_publication;
        for($i=0; $i < $number_iteration;$i++){
                //we tag the publication in major version
                 //print_r("tag une fois, i devient ".$new_i."<br />");
                exec("curl 'http://localhost:8080/alfresco/service/set/version/major/?comment=".rawurlencode($comment)."&reference=".$existing_publication_node->reference."&alf_ticket=" . $ticket . "'");

        }
    }
  }

// check if a path is mirrored without checking if it's inside a mirrored location
function gofast_cmis_check_mirroring($path) {
  $item = gofast_cmis_item_get_by_path($path);
  $reference = $item->properties['alfcmis:nodeRef'];
  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);
  $nb_parents = count($folder_parents);
  if($nb_parents > 1){
    return TRUE;
  } else {
    return $folder_parents;
  }
}

// check if a path is mirrored _or_ inside a mirrored location
function gofast_cmis_is_path_mirrored() {
  global $user;
  // Get item
  if (!isset($_GET["path"])) {
    echo "0";
    exit;
  }

  $is_mirror = FALSE;
  $is_root = FALSE;
  $paths = [gofast_xss_clean($_GET["path"])];
  // we added a standalone "/Sites" entry as a failsafe just in case
  $root_spaces_paths = ["/Sites/_Groups" , "/Sites/_Extranet", "/Sites/_Public", "/Sites/_" . $user->name, "/Sites"];

  while(!$is_mirror && !$is_root) {
    foreach ($paths as $path) {
      // we may have some semi-colons appended to paths, in this case the subsequent cmis request would just timeout after 60 seconds of wait
      if (substr($path, -1) == ";") {
        $path = substr($path, 0, -1);
      }
      if (in_array($path, $root_spaces_paths)) {
        $is_root = TRUE;
        break;
      }
      $result = gofast_cmis_check_mirroring($path);
      if ($result === TRUE) {
        $is_mirror = TRUE;
        break;
      }
      $paths = $result;
    }
  }

  echo $is_mirror ? "1" : "0";
  exit;
}

/** this is a temporary logic, we should add a "path" column to gofast_bookmark_folder to avoid such heavy treatment and get the actual location which was selected instead of a location with the same content */
function gofast_cmis_get_mirrored_path_by_alf_ref($folder_reference, $folder_name) {
  $path = "";
  $parents = gofast_cmis_webservice_get_node_parents($folder_reference);
  foreach ($parents as $parent_path) {
    // using Alfresco native API instead of the webservice would avoid this additional call
    $parent_item = gofast_cmis_item_get_by_path($parent_path);
    $permissions = gofast_cmis_webservice_item_get_permissions($parent_item->properties['alfcmis:nodeRef']);
    $has_consumer_permission = FALSE;
    foreach($permissions as $permission) {
      if (strpos($permission, "Consumer") !== FALSE) {
        $has_consumer_permission = TRUE;
        break;
      }
    }
    if ($has_consumer_permission === TRUE) {
      $path = $parent_path . "/" . $folder_name;
      break;
    }
  }
  return $path;
}

function gofast_cmis_get_replication_count(){
  $query = db_select("alfresco_replication", "r");
  $count = $query->countQuery()->execute()->fetchField();
  return $count;
}