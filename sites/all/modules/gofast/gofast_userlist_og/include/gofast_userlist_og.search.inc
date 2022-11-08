<?php 

/**
 * Implements hook_apachesolr_field_mappings_alter().
 * 
 * Adds some special facets for the Audience Field as defined by OG
 */
function gofast_userlist_og_apachesolr_field_mappings_alter(&$mappings) {
  
//  $mappings['per-field'][OG_AUDIENCE_FIELD] = $mappings['entityreference'];  
  $mappings['per-field'][OG_AUDIENCE_FIELD]['alter callbacks'] = array('gofast_userlist_og_alter_callback');
  $mappings['per-field'][OG_AUDIENCE_FIELD]['map callback'] = 'gofast_userlist_og_map_gid_label';
  
}


/**
 * 
 * Alters the build array of the OG_AUDIENCE_FIELD filter.
 * Adds a filter that allows the user to filter outside of his group for the userlist
 * 
 * @param type $build
 * @param FacetapiAdapter $adapter
 * @param type $facet
 */
function gofast_userlist_og_alter_callback(&$build, FacetapiAdapter $adapter, $facet){

  $count = 0;
  global $user;
  if (is_array($build) && !empty($build)) {
    // Add a filter 'Your Groups'
    $user_groups =  array_merge_recursive(og_get_groups_by_user($user) , gofast_userlist_og_get_groups_by_user($user));
   
    foreach ($build as $filter => $value) {

      // We could do this with the objects, but it would make it a lot more
      //complex
      $filter_values = explode(':', $filter);
      $count += isset($user_groups[$filter_values[0]][$filter_values[1]]) ? $value['#count'] : 0;
    }

    $search_string = gofast_userlist_og_get_my_groups_filter();
    $build[$search_string] = array('#count' => $count);    
  }
  
}

/**
 * Creates a special filter for filtering on the content for the current
 * users groups
 * 
 * @global type $user
 * @return type
 */
function gofast_userlist_og_get_my_groups_filter() {
  global $user;
  $user_groups = array_merge_recursive(og_get_groups_by_user($user) , gofast_userlist_og_get_groups_by_user($user));

  // Build our facet filter
  foreach ($user_groups as $entity_type => $type) {
    foreach ($type as $entity_id) {
      $key = $entity_type . ':' . $entity_id;
      $search_groups[] = '"' . $key . '"';
    }
  }
  return '(' . implode(' OR ' , $search_groups)  . ')';
}


/**
 * Maps prganic group names to their human friendly label and adds a Your Groups
 * facet
 *
 * @param array $values
 *   An array of indexed values being mapped.
 * @param array $options
 *   An associative array of map options containing:
 *   - entities: An array of entities that $values are bundles for.
 *
 * @return array
 *   An array mapping the indexed values to human readable values.
 */
function gofast_userlist_og_map_gid_label(array $ids, array $options) {
  global $user;
  $my_groups_filter_string = gofast_userlist_og_get_my_groups_filter();

  // Remove the value we are looking for
  if (($key = array_search($my_groups_filter_string, $ids)) !== false) {
    unset($ids[$key]);
  }
  $map = apachesolr_entityreference_facet_map_callback($ids, $options);
  $map[$my_groups_filter_string] = t('Your groups');
  return $map;
}