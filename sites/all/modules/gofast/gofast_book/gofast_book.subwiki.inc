<?php

/*
 * Handle moving a wiki
 * wiki_nid: The wiki node id to move
 * parent_nid : The target
 *  COULD BE : A space
 *  COULD BE : Another article, so the wiki will be a subwiki of the parent
 * ALSO : Handle creating and deleting folders for subwikis
*/
function gofast_book_subwiki_handle_move($wiki_nid, $new_parent_nid){
  //Load nodes
  $wiki_node = node_load($wiki_nid);
  $new_parent_node = node_load($new_parent_nid);
  
  if(!$wiki_node || !$new_parent_node){
    return;
  }
  
  $new_parent_type = $new_parent_node->type;
  
  $wiki_ref = gofast_cmis_node_get_reference_by_nid_without_cmis($wiki_nid);
  $old_parent_path = gofast_cmis_webservice_get_node_parents($wiki_ref)[0];
  $old_parent_item = gofast_cmis_item_get_by_path($old_parent_path);
  $old_parent_name = $old_parent_item->properties["cmis:name"];

  if ($new_parent_type == "article") {
    //CASE : Put under subwiki
    gofast_book_subwiki_make_subwiki($new_parent_node);
    $new_parent_ref = gofast_cmis_node_get_reference_by_nid_without_cmis($new_parent_nid);
    $new_parent_path = gofast_cmis_webservice_get_node_parents($new_parent_ref)[0];
    
    $new_parent_item = gofast_cmis_item_get_by_path($new_parent_path);
  } else {
    //CASE : Put under space
    $new_parent_space_ref = gofast_cmis_node_get_reference_by_nid_without_cmis($new_parent_nid, TRUE);
    $new_parent_space_item = gofast_cmis_item_get($new_parent_space_ref);
    $new_parent_space_path = $new_parent_space_item->properties['cmis:path'];
    $new_parent_item = gofast_cmis_item_get_by_path($new_parent_space_path . '/Wikis');
  }
  
  // move nested_book_inside
  gofast_cmis_alfresco_api_move_item($wiki_ref, $new_parent_item->id);

  //If the old parent was a subwiki container, check if we have to unmake it a subwiki container
  if($old_parent_name != "Wikis"){ //So old_parent_type was an article
    $old_parent_wiki_item = gofast_cmis_item_get_by_path($old_parent_path . '/' . $old_parent_name . '.html');
    $old_parent_wiki_nid = $old_parent_wiki_item->properties['gofast:nid'];
    $old_parent_wiki_node = node_load($old_parent_wiki_nid);
    gofast_book_subwiki_unmake_subwiki($old_parent_wiki_node, FALSE);
  }
}

/*
 * Make an article to become a wiki handler
*/
function gofast_book_subwiki_make_subwiki($wiki_node){
  // Get target folder
  $ref = gofast_cmis_node_get_reference_by_nid_without_cmis($wiki_node->nid);
  $item = gofast_cmis_item_get($ref);
  $name = str_replace(".html", "", $item->properties["cmis:name"]);
  $path = gofast_cmis_webservice_get_node_parents($ref)[0];
  $folder = end(explode('/', $path));
  
  if($folder != $name){
    //This isn't yet a subwiki
    $folder_item = gofast_cmis_item_get_by_path($path);
    gofast_cmis_item_folder_insert($name, $folder_item->id, TRUE);
    $new_folder = gofast_cmis_item_get_by_path($path . '/' . $name, TRUE);
    
    gofast_cmis_item_move($ref, $new_folder->id, $folder_item->id, TRUE);
  }
}

/*
 * Unmake an article to be a wiki handler
 * Will only process if there is no more subwikis (You can use force param if needed)
*/
function gofast_book_subwiki_unmake_subwiki($wiki_node, $force = FALSE){
  $wiki_ref = gofast_cmis_node_get_reference_by_nid_without_cmis($wiki_node->nid);
  $parent_path = gofast_cmis_webservice_get_node_parents($wiki_ref)[0];
  $parent_item = gofast_cmis_item_get_by_path($parent_path);
  
  if(!$force){
    //Checking if we need to unwikify
    $parent_childs = gofast_cmis_item_get_children($parent_item->id, TRUE);
    $parent_childs_count = count((array) $parent_childs);
    if($parent_childs_count > 1){
      return;
    }
  }
  
  $new_parent_path = explode('/',$parent_path);
  array_pop($new_parent_path);
  $new_parent_path = implode('/',$new_parent_path);
  $new_parent_item = gofast_cmis_item_get_by_path($new_parent_path);
  
  //Move wiki outside of it's folder
  gofast_cmis_item_move($wiki_ref, $new_parent_item->id, $parent_item->id, TRUE);
  gofast_cmis_item_remove_folder($parent_item->id, TRUE);
}