<?php

/*
 * Merge options sent to the breadcrumb
 */
function gofast_breadcrumb_options($options){
  //Parse GET options
  $get_options = [];
  if($_GET['options']){
    $get_options = json_decode($_GET['options'], TRUE);
  }

  $options = $options + $get_options + [
    "show_title" => TRUE, //Should we show the node title at the end or not
    "show_tooltip" => FALSE, //Should we show the tooltip or not
    "from_tooltip" => FALSE, //Is the breadcrumb displayed inside a tooltip or not
    "return" => FALSE, //Return programmatically or display (ajax)
    "editable" => TRUE, //Is the node title editable, note that a permission check will be done even if this is enabled
    "remove_extension" => TRUE, //Mainly for the documents, should we remove the file extension at the end or not
    "title_link" => FALSE, //Do the node title should be a link, note that this option can't be enabled with "editable" option
    "show_role" => FALSE, //Should we display the role of the current user, the user passed in "show_role_for" option or the userlist passed in "show_role_for_ul" option at the end
    "show_role_for" => NULL, //If "show role" option is enabled, select the user to target (should be a uid)
    "show_role_for_ul" => NULL, //If "show role" option is enabled, select the userlist to target (should be a ulid)
    "show_all_items" => FALSE, //If "show_all_items" option is enabled, all the items will be displayed without the "more" boutton
    "only_title" => FALSE, //If this option is enabled, all breadcrumb parts are ignored except the title. "show_title" option MUST be enabled,
    "only_first" => FALSE, //If this option is enabled, only the first breadcrumb will be displayed
    'in_modal' => FALSE, //If this option is enabled, the breadcrumb will be able to work inside a modal
    'no_padding' => FALSE, //If this option is enabled, the breadcrumb will not have padding
    "manage_locations" => FALSE, //If this option is enabled, the breadcrumb will be wrapped in an xeditable to manage locations
  ];

  return $options;
}

/*
 * Generate crumbs from locations with given options
 *
 * @params
 * locations => An array of locations
 * options => An array of options
 */
function gofast_breadcrumb_generate_crumbs_from_locations($locations, $options = []){
  //For each location, we generate a breadcrumb
  foreach ($locations as $location) {
    $parts = explode('/', $location);
    $current_parts = [];
    $crumbs = [];

    //Fetch into parts to generate crumbs for each of them
    foreach($parts as $part){
      //Ignore some useless parts
      $ignore_parts = [
        "",
        "Sites"
      ];

      if(in_array($part, $ignore_parts)){
        continue;
      }
      
      //Generate crumb for the current location
      $current_parts[] = $part;
      $crumbs[] = gofast_breadcrumb_generate_crumbs_from_location($current_parts, $options);
    }
    
    //If there is only a single crumb, duplicate the element to show the icon
    if(count($crumbs) == 1){
      $crumbs[] = $crumbs[0];
    }

    //Insert the crumbs into all crumbs
    $all_crumbs[] = $crumbs;
  }
  return $all_crumbs;
}

/*
 * Generate crumbs from parts with given options
 *
 * @params
 * location => An array of parts
 * options => An array of options
 */
function gofast_breadcrumb_generate_crumbs_from_location($parts, $options = []){
  $crumb = [];
  $gid = FALSE;
  $folder = false;
  $is_mirror = false;

  //Copy the parts to preserve the original array
  $copy_parts = $parts;
  
  $path = $full_path =  "/Sites/" . implode('/', $copy_parts);
  
  while(!empty($copy_parts) && !$gid){
    //Get the space corresponding to our locations
    $path = "/Sites/" . implode('/', $copy_parts);
    $gid = gofast_ajax_file_browser_get_nid_from_href($path, TRUE);

    if(!$gid){
      $folder = true;
      array_pop($copy_parts);
    }  
  }

  if($folder){
    // Check mirroring
      $reference = gofast_cmis_item_get_by_path("/Sites/" . implode('/', $parts))->properties['alfcmis:nodeRef'];
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
            $is_mirror = false;
            break;
          }else{
            $is_mirror = true;
          }
        }
      }
    }

  $href = "/node/".$gid;
  if(gofast_mobile_is_mobile_domain()) {
    $href = "/home_page_navigation?&path=" . rawurlencode($full_path)."#navBrowser";
  }

  $space = node_load($gid);

  //Check our permissions in this space
  global $user;
  $membership = og_get_membership('node', $gid, 'user', $user->uid);
  $isMember = ($membership != FALSE && $membership->state != OG_STATE_PENDING);

  if(!$isMember){
    $isMember = gofast_userlist_og_is_user_member_of_space($gid, user_load($user->uid));
  }

  $crumb['icon'] = gofast_node_get_icon($space);
  $crumb['gid'] = $gid;
  $crumb['href'] = $href;
  $crumb['location'] = implode('/', $parts);
  $crumb['folder'] = $folder;
  $crumb['is_mirror'] = $is_mirror;
  $crumb['name'] = end($parts);
  $crumb['text'] = $isMember ? FALSE : TRUE;

  //Remove '_' from space name
  if(!$folder){
    $crumb['name'] = substr($crumb['name'], 1);
  }

  return $crumb;
}

/*
 * Insert title into crumbs
 * The title can be editable or not, depending on the options
*/
function gofast_breadcrumb_insert_title($crumbs, $node, $options = []){
  foreach($crumbs as &$crumb){ //Parse all crumbs
    if($options['editable']){ //Need ability to edit the title
      $crumb[] = [
        'name' => "<b>$node->title</b>",
        'text' => TRUE,
      ];
    }else{ //Put the title at the end
      if($options['title_link']){
        $crumb[] = [
          'icon' => gofast_node_get_icon($node),
          'name' => $node->title,
          'gid' => $node->nid,
        ];
      }else{
        $crumb[] = [
          'name' => $node->title,
          'text' => TRUE,
        ];
      }
    }
  }

  return $crumbs;
}

/*
 * Remove all parts, except the title
*/
function gofast_breadcrumb_only_title($crumbs, $node, $options = []){
  $only_title_crumb[][] = end($crumbs[0]);
  return $only_title_crumb;
}

/*
 * Insert role into crumbs
 * The user can be the current user or a selected user, depending on the options
 */
function gofast_breadcrumb_insert_role($crumbs, $node, $options = []){
  global $user;

  //Check "show_role_for" param
  if($options['show_role_for']){
    $uid = $options['show_role_for'];
  }else{
    $uid = $user->uid;
  }

  //Check "show_role_for_ul" param
  if($options['show_role_for_ul']){
    $ulid = $options['show_role_for_ul'];
  }

  //Retrieve the role
  if($ulid){
    if (!empty(gofast_userlist_og_get_userlist_roles('node', $node->nid, $ulid, FALSE, TRUE))) {
      $role = t(array_shift(gofast_userlist_og_get_userlist_roles('node', $node->nid, $ulid, FALSE, TRUE)), array(), array('context' => 'gofast:gofast_userlist'));
    }
  }else{
    if (!empty(gofast_og_get_user_final_roles_for_space('node', $node->nid, $uid))) {
      $role = t(array_shift(gofast_og_get_user_final_roles_for_space('node', $node->nid, $uid)), array(), array('context' => 'gofast:gofast_userlist'));
    }
  }

  foreach($crumbs as &$crumb){ //Parse all crumbs
    $crumb[count($crumb)-1]['role'] = " (" . $role . ")";
  }

  return $crumbs;
}

/*
 * Sort crumbs by permissions
 * Put crumbs with full permissions on top of the crumbs
 */
function gofast_breadcrumb_sort_by_permissions($crumbs, $options = []){
  $crumbs_full_permissions = [];
  $other_crumbs = [];

  foreach($crumbs as $crumb){
    $full_permissions = TRUE;

    foreach($crumb as $part){
      if($part['gid'] && $part['text']){
        $full_permissions = FALSE;
      }
    }

    if($full_permissions){
      $crumbs_full_permissions[] = $crumb;
    }else{
      $other_crumbs[] = $crumb;
    }
  }

  return array_merge($crumbs_full_permissions, $other_crumbs);
}
