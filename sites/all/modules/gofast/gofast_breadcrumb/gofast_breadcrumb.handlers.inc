<?php

/*
 * Breadcrumb handler : alfresco_item
 * Main handler for document's breadcrumb
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_alfresco_item($node, &$options = []){
  
  //Check if $node is locked
  $node_reference = gofast_cmis_node_get_item_id($node);

  //Retrieve locations of the document
  if($node->status != 0){
    $locations = gofast_cmis_webservice_get_node_parents($node_reference);
  } else {
    $main_location = array($node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value']);
    $all_locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
    $other_locations = [];
    foreach($all_locations as $other_location){
      $other_locations[] = $other_location['value'];
    }
    $locations = array_unique(array_merge($main_location, $other_locations));
  }
  $options["editable"] = gofast_contextual_menu_get_action_access("rename", $node);
  if($options['remove_extension']){
    $node->title = pathinfo($node->title)['filename'];
  }

  $crumbs = gofast_breadcrumb_generate_crumbs_from_locations($locations, $options);
  
  //Sort crumbs by permissions
  $crumbs = gofast_breadcrumb_sort_by_permissions($crumbs, $options);
  
  if($options['show_title']){
    $crumbs = gofast_breadcrumb_insert_title($crumbs, $node, $options);
    
    if($options['only_title']){
      $crumbs = gofast_breadcrumb_only_title($crumbs, $node, $options);
    }
  }
  
  return $crumbs;
}

/*
 * Sub handler : article
 * Sub handler for article's breadcrumb, redirecting to alfresco_item handler
 * 
 * @params
 * node => The article's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_article($node, &$options = []){
  return gofast_breadcrumb_handle_alfresco_item($node, $options);
}

/*
 * Breadcrumb handler : forum
 * Main handler for forum's breadcrumb, using space handler
 * 
 * @params
 * node => The forum's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_forum($node, &$options = []){
  $spaces = $node->og_group_content_ref[LANGUAGE_NONE];
  $crumbs = [];
  
  //Save and set some options
  $save_editable = $options['editable'];
  $save_show = $options['show_title'];
  
  $options['show_title'] = TRUE;
  $options['title_link'] = TRUE;
  $options['editable'] = FALSE;
  
  foreach($spaces as $space){
    $gid = $space['target_id'];
    $node_space = node_load($gid, NULL, TRUE);
    
    //Retrieve the crumb of this space and insert it into the crumbs
    $crumbs = array_merge($crumbs, gofast_breadcrumb_handle_spaces($node_space, $options));
  }
  
  //Sort crumbs by permissions
  $crumbs = gofast_breadcrumb_sort_by_permissions($crumbs, $options);
  
  //Reload pased options
  $options['show_title'] = $save_show;
  $options['editable'] = $save_editable;
  
  if($options['show_title']){
    $crumbs = gofast_breadcrumb_insert_title($crumbs, $node, $options);
    
    if($options['only_title']){
      $crumbs = gofast_breadcrumb_only_title($crumbs, $node, $options);
    }
  }
  
  return $crumbs;
}

/*
 * Breadcrumb handler : webform
 * Sub handler for webform's breadcrumb, replicate forum handler
 * 
 * @params
 * node => The forum's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_webform($node, &$options = []){
  return gofast_breadcrumb_handle_forum($node, $options);
}

/*
 * Breadcrumb handler : spaces
 * Main handler for spaces breadcrumb
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_spaces($node, &$options = []){
  //Retrieve locations of the space
  $locations = [gofast_cmis_space_get_webdav_path($node->nid)];
  
  $crumbs = gofast_breadcrumb_generate_crumbs_from_locations($locations, $options);
  
  //Remove last crumb as it's the current space and it will be displayed as text
  if (!$options["title_link"]) {
    foreach($crumbs as &$crumb){
      array_pop($crumb);
    }
  }
  
  if($options['show_title'] && !$options["title_link"]){
    $crumbs = gofast_breadcrumb_insert_title($crumbs, $node, $options);
  }
  
  if($options['show_role']){
    $crumbs = gofast_breadcrumb_insert_role($crumbs, $node, $options);
  }
  
  return $crumbs;
}

/*
 * Breadcrumb handler : group
 * Sub handler
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_group($node, &$options = []){
  $crumbs = gofast_breadcrumb_handle_spaces($node, $options);
  
  return $crumbs;
}

/*
 * Breadcrumb handler : organisation
 * Sub handler
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_organisation($node, &$options = []){
  $crumbs = gofast_breadcrumb_handle_spaces($node, $options);
  
  return $crumbs;
}

/*
 * Breadcrumb handler : extranet
 * Sub handler
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_extranet($node, &$options = []){
  $crumbs = gofast_breadcrumb_handle_spaces($node, $options);
  
  return $crumbs;
}

/*
 * Breadcrumb handler : public
 * Sub handler
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_public($node, &$options = []){
  $crumbs = gofast_breadcrumb_handle_spaces($node, $options);
  
  return $crumbs;
}

/*
 * Breadcrumb handler : private_space
 * Sub handler
 * 
 * @params
 * node => The document's node
 * options => Array of options
 * 
 */
function gofast_breadcrumb_handle_private_space($node, &$options = []){
  $crumbs = gofast_breadcrumb_handle_spaces($node, $options);
  
  return $crumbs;
}
