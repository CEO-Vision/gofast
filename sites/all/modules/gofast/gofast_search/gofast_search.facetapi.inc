<?php

/**
 * Implements hook_facetapi_facet_info()
 *
 *  Define facets provided by the module.
 */
function gofast_search_facetapi_facet_info($searcher_info) {
  $facets = array();

  $facets['author'] = array(
    'field' => 'is_uid',
    'label' => t('Creator', array(), array('context' => 'gofast')),
    'description' => t('Filter by Creator', array(), array('context' => 'gofast:gofast_search')),
    'map callback' => 'gofast_facet_author_name_field_mapping',
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );

  $facets['mod_author'] = array(
    'field' => 'is_mod_uid',
    'label' => t('Last Contributor', array(), array('context' => 'gofast')),
    'description' => t('Filter by Last contributor', array(), array('context' => 'gofast:gofast_search')),
    'map callback' => 'gofast_facet_author_name_field_mapping',
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );

  $facets['author_unrestricted'] = array(
    'field' => 'sm_unr_author',
    'label' => t('Author'),
    'description' => t('Filter by Author', array(), array('context' => 'gofast:gofast_search')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );

  $facets['document_reference_unrestricted'] = array(
    'field' => 'sm_unr_document_reference',
    'label' => t(variable_get("document_reference_label", "Document reference"), array(), array('context' => 'gofast')),
    'description' => t('Filter by', array(), array('context' => 'gofast:gofast_search')) . " " . t('Document reference', array(), array('context' => 'gofast')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );

  $facets['field_custom_date'] = array(
    'field' => 'ds_custom_date', // ends up in a single-valued index field.
    'field api name' => 'field_custom_date',
    'label' => GOFAST_METADATA_CUSTOM_DATE_LABEL,
    'description' => t('Filter by %label', array("%label" => GOFAST_METADATA_CUSTOM_DATE_LABEL), array('context' => 'gofast:gofast_search')),
    'query types' => array('date_queries'),
    'map callback' => 'gofast_facet_date_map',
    'map options' => array('format callback' => 'facetapi_format_timestamp'),
    'range types' => array('future'),
    'min callback' => 'gofast_facet_get_min_date',
    'max callback' => 'gofast_facet_get_max_date',
    'facet mincount allowed' => TRUE,
    'hierarchy callback' => 'gofast_facet_date_hierarchy',
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(
      array('date', SORT_ASC)
    )
  );

  $facets['classification'] = array(
    'field' => 'im_field_classification',
    'label' => t('Classification', array(), array('context' => 'gofast')),
    'description' => t('Filter by Classification', array(), array('context' => 'gofast:gofast_search')),
    'facet mincount allowed' => TRUE,
    'map callback' => 'facetapi_map_taxonomy_terms',
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );

  $facets['field_date'] = array(
    'field' => 'ds_field_date', // ends up in a single-valued index field.
    'field api name' => 'field_date',
    'label' => t('Deadline', array(), array('context' => 'gofast')),
    'description' => t('Filter by Deadline', array(), array('context' => 'gofast:gofast_search')),
    'query types' => array('date_queries'),
    'map callback' => 'gofast_facet_date_map',
    'map options' => array('format callback' => 'facetapi_format_timestamp'),
    'range types' => array('future'),
    'min callback' => 'gofast_facet_get_min_date',
    'max callback' => 'gofast_facet_get_max_date',
    'facet mincount allowed' => TRUE,
    'hierarchy callback' => 'gofast_facet_date_hierarchy',
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(
      array('date', SORT_ASC)
    )
  );

  // Override OG content membership facet.
  $og_facet = 'sm_' . GOFAST_OG_CONTENT_MEMBERSHIP_FIELD;
  $facets[$og_facet] = array(
    'map callback' => 'gofast_facet_og_label_map',
    'alter callbacks' => array('gofast_facet_og_alter'),
    'hierarchy callback' => 'gofast_facet_og_hierarchy',
    'default sorts' => array(array('display', SORT_ASC))
  );
  $facets['field_title'] = array(
    'field' => 'sm_unr_field_title', 
    'label' => t('Title', array(), array('context' => 'gofast')),
    'description' => t('Filter by Title', array(), array('context' => 'gofast:gofast_search')),
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(
      array('display', SORT_ASC)
    )
  );
  $facets['field_retention_end'] = array(
    'field' => 'ds_retention_end',
    'field api name' => 'field_retention_end',
    'label' => t('Retention date', array(), array('context' => 'gofast:gofast_search')),
    'description' => t('Filter by Retention Date', array(), array('context' => 'gofast:gofast_search')),
    'query types' => array('date_queries'),
    'map callback' => 'gofast_facet_date_map',
    'map options' => array('format callback' => 'facetapi_format_timestamp'),
    'range types' => array('future'),
    'min callback' => 'gofast_facet_get_min_date',
    'max callback' => 'gofast_facet_get_max_date',
    'hierarchy callback' => 'gofast_facet_date_hierarchy',
    'facet mincount allowed' => TRUE,
    'dependency plugins' => array('bundle', 'role'),
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'default sorts' => array(
      array('date', SORT_ASC)
    )
  );
  return $facets;
}

/**
 * Implements hook_facetapi_facet_info_alter()
 *
 *  Allows for alterations to the facet definitions.
 */
function gofast_search_facetapi_facet_info_alter(array &$facet_info, array $searcher_info) {
  // Redefine date facets.
  $facet_info['created'] = array(
    'field' => 'ds_created',
    'label' => t('Creation date', array(), array('context' => 'gofast')),
    'description' => t('Filter by creation date.', array(), array('context' => 'gofast:gofast_search')),
    'query types' => array('date_queries'),
    'map callback' => 'gofast_facet_date_map',
    'map options' => array('format callback' => 'facetapi_format_timestamp') + $facet_info['created']['map options'],
    'range types' => array('past'),
    'min callback' => 'gofast_facet_get_min_date',
    'max callback' => 'gofast_facet_get_max_date',
    'facet mincount allowed' => TRUE,
    'hierarchy callback' => 'gofast_facet_date_hierarchy',
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(array('date', SORT_DESC))
  ) + $facet_info['created'];

  $facet_info['changed'] = array(
    'field' => 'ds_changed',
    'label' => t('Modification date', array(), array('context' => 'gofast')),
    'description' => t('Filter by date of last modification.', array(), array('context' => 'gofast:gofast_search')),
    'query types' => array('date_queries'),
    'map callback' => 'gofast_facet_date_map',
    'map options' => array('format callback' => 'facetapi_format_timestamp') + $facet_info['changed']['map options'],
    'range types' => array('past'),
    'min callback' => 'gofast_facet_get_min_date',
    'max callback' => 'gofast_facet_get_max_date',
    'facet mincount allowed' => TRUE,
    'hierarchy callback' => 'gofast_facet_date_hierarchy',
    'allowed operators' => array(FACETAPI_OPERATOR_AND => TRUE),
    'dependency plugins' => array('bundle', 'role'),
    'default sorts' => array(array('date', SORT_DESC))
  ) + $facet_info['changed'];
}

/**
 * Implements hook_facetapi_query_types().
 *
 *  Define query type plugin.
 */
function gofast_search_facetapi_query_types() {
  return array(
    'gofast_date_queries' => array(
      'handler' => array(
        'class' => 'GofastFacetapiDate',
        'parent' => 'query_type',
        'file' => 'query_type.inc',
        'path' => drupal_get_path('module', 'gofast_search') . '/plugins/facetapi',
        'adapter' => 'apachesolr'
      )
    )
  );
}

/**
 * Implement hook_facetapi_realm_info_alter()
 *  Allows for alterations to the realm definitions.
 *
 * @param array $realm_info
 *  The return values of hook_facetapi_realm_info() implementations.
 */
function gofast_search_facetapi_realm_info_alter(array &$realm_info) {
  // Override the default widget used to build links in the 'block' realm.
  $realm_info['block']['default widget'] = 'gofast_facetapi_links';
}

/**
 * Implement hook_facetapi_widgets()
 *
 *  Define our own widget plugins to make overrides easier.
 */
function gofast_search_facetapi_widgets() {
  return array(
    'gofast_facetapi_links' => array(
      'handler' => array(
        'label' => t('GoFAST facet links', array(), array('context' => 'gofast')),
        'class' => 'GofastFacetapiWidgetLinks',
        'query types' => array('term', 'date', 'date_queries'),
        'requirements' => array(
          'facetapi_requirement_realm_property' => array('element type' => 'links')
        )
      )
    )
  );
}

/**
 * Implements hook_facetapi_sort_info()
 *
 *  Define facets sorting algorithm.
 */
function gofast_search_facetapi_sort_info() {
  $sorts = array();

  $sorts['date'] = array(
    'label' => t('Date sort', array(), array('context' => 'gofast')),
    'callback' => 'gofast_facet_sort_date',
    'description' => t('Sort by date or date range.', array(), array('context' => 'gofast:gofast_search')),
    'weight' => 0
  );

  return $sorts;
}

/**
 * FacetApi date sort callback.
 *
 *  Sorts by date range value (based on raw indexed date).
 */
function gofast_facet_sort_date(array $a, array $b) {
  $a_value = isset($a['#indexed_value']) ? $a['#indexed_value'] : '';
  $b_value = isset($b['#indexed_value']) ? $b['#indexed_value'] : ''; // [2013-01-01T00:00:00Z TO 2014-01-01T00:00:00Z]

  $date_queries = array_flip(array_keys(gofast_facet_date_range_query_map()));

  if (isset($date_queries[$a_value])) {
    $a_value = $date_queries[$a_value] + 99999999000000; // 20140501000000
  }
  else {
    list ($a_value,) = explode(' TO ', trim($a_value, '{[]}'));
    $a_value = preg_replace('/\D/', '', $a_value);
  }

  if (isset($date_queries[$b_value])) {
    $b_value = $date_queries[$b_value] + 99999999000000;
  }
  else {
    list ($b_value,) = explode(' TO ', trim($b_value, '{[]}'));
    $b_value = preg_replace('/\D/', '', $b_value);
  }

  if ($a_value == $b_value) {
    return 0;
  }
  return ($a_value < $b_value) ? -1 : 1;
}

/**
 * FacetApi map callback.
 *
 *  Map author username (id) to readable name (i.e firstname, lastname if set)
 *  Returns mapping for author firstname and lastname.
 */
function gofast_facet_author_name_field_mapping(array $values) {
  $map = array();
  if (!empty($values)) {
     foreach($values as $uid){
      $infos_user = gofast_get_properties_user_by_uid_or_u_name($uid, NULL, ["firstname","lastname","picture"]);
      $name = $infos_user->firstname." ".$infos_user->lastname;
      $map[$uid] = $name;
    }
  }
  return $map;
}

/**
 * FacetApi callback that returns the minimum date value from entity/field table.
 *
 * @param $facet
 *   An array containing the facet definition.
 *
 * @return
 *   The minimum timestamp extracted from the appropiated table.
 */
function gofast_facet_get_min_date(array $facet) {
  return _gofast_facet_get_date($facet, 'min');
}

/**
 * FacetApi callback that returns the maximum date value from entity/field table.
 *
 * @param $facet
 *   An array containing the facet definition.
 *
 * @return
 *   The maximum timestamp extracted from the appropiated table.
 */
function gofast_facet_get_max_date(array $facet) {
return _gofast_facet_get_date($facet, 'max');
}

/**
 *  Returns a min/max date value from the backend depending on $facet and $type.
 */
function _gofast_facet_get_date(array $facet, $type) {
  static $results = array();

  if (!isset($results[$type][$facet['name']])) {
    if (in_array($facet['name'], array('created', 'changed'))) {      
      if($type == "min"){
       $time =  variable_get("gofast_facet_get_date_min_".$facet['name'], 1325372400);
      }elseif($type == "max"){
        $time = time();
      }
    }
    else {
      $query = db_select('field_data_' . $facet['name'], 'f');
      $query->addExpression($type . '(' . $facet['name'] . '_value)', $type);
      $query->addJoin('INNER', 'node', 'n', 'n.nid = f.entity_id');
      $query->condition('n.status', 1);
      $time = $query->execute()->fetch()->{$type};
      if (!is_numeric($time)) {
        $time = "" . strtotime($time);
      }
    }
    $results[$type][$facet['name']] = $time;
  }

  return $results[$type][$facet['name']];
}

/**
 * Facet map callback.
 *
 *  Maps date ranges to human readable dates.
 */
function gofast_facet_date_map(array $values, $options = array()) {
  if (empty($options['format callback'])) {
    $options['format callback'] = 'facetapi_format_timestamp';
  }

  // Retrieve custom (fixed) range mapping.
  $_map = gofast_facet_date_range_query_map();
  $map = array();

  foreach ($values as $value) {
    if (isset($_map[$value])) {
      $map[$value] = $_map[$value];
      continue;
    }

    $range = explode(' TO ', trim($value, '{[]}'));
    if (isset($range[1])) {
      $gap = facetapi_get_date_gap($range[0], $range[1]);
      $local = date('Y-m-d\TH:i:s\Z', strtotime($range[0])); // UTC -> local
      $map[$value] = facetapi_format_date($local, $gap, $options['format callback']);
    }
  }

  return !empty($map) ? $map : $values;
}

/**
 * Helper function, maps facet query date ranges to the corresponding
 * human-readable labels.
 */
function gofast_facet_date_range_query_map() {
  return array(
    GofastFacetapiDate::GOFAST_FACET_QUERY_PAST_MONTH => t('Past month', array(), array('context' => 'gofast:gofast_search')),
    GofastFacetapiDate::GOFAST_FACET_QUERY_PAST_WEEK => t('Past week', array(), array('context' => 'gofast:gofast_search')),
    GofastFacetapiDate::GOFAST_FACET_QUERY_PAST_DAY => t('Past 24 hours', array(), array('context' => 'gofast:gofast_search')),
    GofastFacetapiDate::GOFAST_FACET_QUERY_FUTURE_MONTH => t('Within a month', array(), array('context' => 'gofast:gofast_search')),
    GofastFacetapiDate::GOFAST_FACET_QUERY_FUTURE_WEEK => t('Within a week', array(), array('context' => 'gofast:gofast_search')),
    GofastFacetapiDate::GOFAST_FACET_QUERY_FUTURE_DAY => t('Within 24 hours', array(), array('context' => 'gofast:gofast_search'))
  );
}

/**
 * Facet map callback.
 *
 *  Map group id's to readable group labels.
 */
function gofast_facet_og_label_map(array $values, array $options) {
   $map = $values = array_combine($values, $values);

   // Process default callback first.
  if (isset($options['default callback'])) {// apachesolr_og
    $map = call_user_func($options['default callback'], $values, $options);
  }

  // Mapping for 'public spaces' facet name.
  if (isset($values[GOFAST_SEARCH_PUBLIC_REF])) {
    $map[GOFAST_SEARCH_PUBLIC_REF] = '- ' . t('All Public Spaces', array(), array('context' => 'gofast')) . ' -';
  }

  foreach($map as $key => $value){ //Set spaces name
    $map[$key] = gofast_get_node_title(explode(':', $value)[1], array(), TRUE);
    }

// Keep private space name as it is submited by its owner ?
//  // Map current user's private space name.
//  $nid = gofast_og_get_user_private_space(NULL, FALSE);
//  if ($nid !== FALSE) {
//    $key = 'node:' . $nid;
//    unset ($map[$key]);
//    $map[$key] = '- ' . t('Private') . ' -';
//  }

  return $map;
}

/**
 * Facet hierarchy callback
 * Maps the parent / child relationships of date facet data.
 *
 * @param array $values
 *   An array containing raw dates.
 *
 * @return
 *   An associative array keyed by raw dates to parent dates.
 *
 * @see facetapi_get_taxonomy_hierarchy()
 */
function gofast_facet_date_hierarchy(array $values) {
  // Actually our query date types plugin handles hierarchy itself, however a
  // "hierarchy callback" must be set because adapter and widget classes rely on
  // that condition to handle facet tree correctly (i.e through theme).
  return array($values);
}

/**
 * Facet hierarchy callback
 * Maps the parent / child relationships of OG facets.
 *
 * @param array $values
 *   An array containing apachesolr OG entity reference.
 *
 * @return
 *   An associative array keyed by OG reference to parent OG reference.
 */
function gofast_facet_og_hierarchy(array $values) {
  $parents = array();

  if ($key = array_search(GOFAST_SEARCH_PUBLIC_REF, $values)) {
    // Do we want to process public group tree separately (meaning twice since
    // we already have the normal per-group tree)?
    unset ($values[$key]);
  }

  $og_ids = array_map(function($item){
    list(, $id) = explode(':', $item);
    return $id;
  }, $values);

  foreach (entity_load('node', $og_ids) as $id => $entity) {
        $pid = db_query("select gid from og_membership where etid=".$id." AND field_name='og_group_ref'")->fetch()->gid;
        if(empty($pid)){
          continue;
        }

        $key = 'node:' . $id;
        $value = 'node:' . $pid;
        $parents[$key][] = $value;
    }

  return $parents;
}
/**
 * Facet hierarchy callback
 * Alter OG entity reference to get only user have access to.
 *
 * @param array $values
 *   An array containing apachesolr OG entity reference.
 *
 * @return
 *   An array containing apachesolr OG entity reference
 */
function gofast_facet_og_alter(array &$values){
  global $user;

  $all_spaces = gofast_og_get_spaces_by_user($user, TRUE,false,false,TRUE);
  foreach($values as $key => $value){
    $id = explode(':', $key)[1];
    if(array_search($id, $all_spaces) === false){
        $node_access = false;
    }else{
        $node_access = true; 
    }
    if(!$node_access){
        unset($values[$key]);
    }
  } 
}


function gofast_search_form_facetapi_facet_display_form_alter(&$form, &$form_state){
//  _debug($form);
  /**
   * @todo: check what is happening with 'show_expanded' checkbox.
   * @see widget links plugin.
   */
}

/**
 * Returns an array of facet filtered by a specific query type.
 *
 * @param string $query_type
 * @return array with the matching facets.
 */
function gofast_facet_by_query_type($query_type = NULL) {
  $facets = facetapi_get_facet_info(GOFAST_SEARCH_SOLR_SEARCHER);
  if ($query_type) {
    $facets = array_filter($facets, function($facet) use ($query_type) {
      return in_array($query_type, $facet['query types']);
    });
  }
  return $facets;
}

/**
 * Checks the query type of a given facet.
 */
function gofast_facet_check_query_type($facet_name, $query_type = '') {
  $facets = array_map(function($_facet) {
    return $_facet['name'];
  }, gofast_facet_by_query_type($query_type));

  return in_array($facet_name, $facets);
}

/**
 * Implements hook_block_view_alter().
 */
function gofast_search_block_view_alter(&$data, $block) {
  if (isset($data['content']['#facet'])) {
    // $data['content']['#attributes']['class'][] = 'navi';
    $settings = $data['content']['#settings'];
    if (is_object($settings) && isset($settings->settings) && $settings->settings['widget'] === 'gofast_facetapi_links') {
      gofast_facetapi_static_block($block->delta);
    }
  }
}

/**
 * Ugly workaround to get the array of facetapi block deltas working in an ajaxified navigation context
 */
function gofast_facetapi_get_deltas_from_db() {
  return db_query('SELECT delta FROM {block} WHERE module = \'facetapi\' AND theme = \'bootstrap_keen\' AND status = 1 ORDER BY weight')->fetchCol();
}

/**
 * Function that manages a static array of the block deltas that contain
 * collapsible facets.
 * @warning as of GoFAST 4, this doesn't seem to work anymore
 */
function gofast_facetapi_static_block($delta = NULL) {
  $facetapi_collapsible = &drupal_static(__FUNCTION__, array());
  if ($delta) {
    // Add the given delta to our array of collapsible facets.
    $facetapi_collapsible[] = $delta;
  }
  return $facetapi_collapsible;
}

/**
 * Implements hook_preprocess_block().
 */
function gofast_search_preprocess_block(&$variables) {
  $collapsible_facets = gofast_facetapi_get_deltas_from_db();
  if (in_array($variables['block']->delta, $collapsible_facets)) {
    $variables['classes_array'][] = 'facetapi-collapsible';
    $variables['collapsible_id'] = $variables["elements"]["#attributes"]["id"];
  }
  // fixes an issue with the "card" class displayed on basic blocks messing around with the Apache SORL "Sort by" fields
  // if ($variables['block']->module == "apachesolr_search" && $variables['block']->delta == "sort") {
  //   $variables['classes_array'][] = 'border-0';
  //   drupal_add_css("." . implode(".", $variables['classes_array']) . " > ul {
  //     margin-top: 1rem;
  //     transform: translateX(-3rem);
  //   }", "inline");
  // }
}

/**
 * Implements hook_block_info_alter().
 */
function gofast_search_block_info_alter(&$blocks, $theme, $code_blocks) {
  $current_search = &$blocks['current_search']['gofast_current_search_block'];

  if(isset($current_search)){
      $current_search['title'] = t('Current search', array(), array('context' => 'gofast:gofast_search'));
      $current_search['cache'] = DRUPAL_NO_CACHE;
      $current_search['pages'] = implode(PHP_EOL, array(GOFAST_SEARCH_PATH, GOFAST_SEARCH_PATH . '/*'));
  }

  // Display status facet (deleted/available) only if search option is enabled.
  // Administer permission is also a required for both the option to be enabled,
  // and for the block visibility.
  $delta = facetapi_build_delta(GOFAST_SEARCH_SOLR_SEARCHER, 'block', 'status');
  $hash = facetapi_hash_delta($delta);
  $status_block = &$blocks['facetapi'][$hash];
  if(isset($status_block)){
      $status_block['cache'] = DRUPAL_NO_CACHE;
      $status_block['visibility'] = BLOCK_VISIBILITY_PHP;
      $status_block['pages'] = implode(PHP_EOL, array(
        '<?php',
        '$options = array_map(function ($item) { return $item["value"]; }, gofast_search_options());',
        'return isset($options["include-deleted"]) && $options["include-deleted"];',
        '?>'
      ));
  }else{
      unset($blocks['facetapi'][$hash]);
  }
}

/**
 * Implements hook_block_view_MODULE_DELTA_alter()
 *
 *  Perform alterations to the current_search block.
 */
function gofast_search_block_view_current_search_gofast_current_search_block_alter(&$data, $block) {
  // Show activated search options into the current search block.
  $search_options = array_filter(gofast_search_options(), function($option) {
    return !empty($option['value']);
  });

  $options_markup = array_map(function($item) {
    return $item['title'];
  },$search_options);
}

/**
 * Implements hook_block_view_MODULE_DELTA_alter()
 *
 *  Perform alterations to the apachesolr_search block.
 */
function gofast_search_block_view_apachesolr_search_sort_alter(&$data,$block){
  
    if(gofast_essential_is_essential()){
      $content = "<script type='text/javascript'>"
      . "jQuery('section[id^=block-apachesolr-search-sort]').find('div.btn-group').addClass('d-inline-block');"
      . "jQuery('section[id^=\"block-apachesolr-search-sort\"]').find('li').addClass('btn btn-sm btn-default text-truncate').find('a').css('color', 'inherit');"
      . "jQuery('.breadcrumb-gofast').hide();"
      . "jQuery('section[id^=\"block-apachesolr-search-sort\"]').find('li').each(function(k, elem){"
          . "var filter = jQuery(elem).find('a');"
          . "jQuery(this).click(function(){jQuery(filter).click()});"
          . "jQuery(elem).find('a').removeProp('href');"
      . "})"
      . "</script>";
    }else{
      $content = "<script type='text/javascript'>"
      . "jQuery('section[id^=block-apachesolr-search-sort]').find('div.btn-group').addClass('d-inline-block');"
      . "jQuery('section[id^=\"block-apachesolr-search-sort\"]').find('li').addClass('btn btn-sm btn-default text-truncate').find('a').css('color', 'inherit');"
      . "jQuery('.breadcrumb-gofast').hide();"
      . "jQuery('section[id^=\"block-apachesolr-search-sort\"]').find('li').each(function(k, elem){"
                . "var href = jQuery(elem).find('a').prop('href');"
                . "jQuery(elem).click(function(){Gofast.processAjax(href)});"
          . "jQuery(elem).find('a').removeProp('href');"
      . "})"
      . "</script>";
    }
    $data['content'] .= $content;

    $data['content'] = str_replace('<span class="icon-after icon glyphicon glyphicon-chevron-down"', '<span class="order_indicator fa fa-caret-down"'  ,  $data['content']); 
    $data['content'] = str_replace('<span class="icon-after icon glyphicon glyphicon-chevron-up"', '<span class="order_indicator fa fa-caret-up"'  ,  $data['content']); 
    $data['content'] = str_replace('<ul>', '<ul class="p-0 m-0"><div class="btn-group" role="group">', $data['content']);
    $data['content'] = str_replace('</ul>', '</div></ul>', $data['content']);
}

/**
 * Implements hook_current_search_items().
 *
 *  Provide GofastCurrentSearchItemActive for the current search block.
 */
function gofast_search_current_search_items() {
  return array(
    'gofast_active' => array(
      'handler' => array(
        'label' => t('GoFAST Active items', array(), array('context' => 'gofast:gofast_search')),
        'class' => 'GofastCurrentSearchItemActive'
      )
    )
  );
}

/**
 * Returns a themed facet icon as an HTML string.
 *
 * @see gofast_facetapi_icon_map()
 */
function gofast_facetapi_get_facet_icon($field, $value) {
  $icon = '';
  $icon_map = gofast_facetapi_icon_map();
  if (isset($icon_map[$field])) {
    if (is_callable($icon_map[$field])) {
      $icon = call_user_func($icon_map[$field], $value);
    }
  }
  return $icon;
}

/**
 * Returns an array that maps facet field aliases to icon loader/theme callback.
 */
function gofast_facetapi_icon_map() {
  return array(
     /** @todo: use gofast theme format when usable */
    'im_field_format' => function ($tid) {   
      return '<span class="navi-icon">'.theme('gofast_type_icon_format', array('tid' => $tid)).'</span>';
    }
  );
}

/**
 * Implements hook_theme_registry_alter().
 */
function gofast_search_theme_registry_alter(&$theme_registry) {
  // Collapsible facets only needs to inject or wrap these theming functions
  // with additional markup. When replacing the theme function, we need to save
  // the original array and invoke the original theming function in ours. This
  // allows compatibility with other modules and themes that have existing
  // overrides.
  $overriden = array(
    'facetapi_title',
    'facetapi_count',
    'facetapi_link_inactive',
    'facetapi_link_active',
    'current_search_link_active'
  );
  foreach ($overriden as $theme_function) {
    $theme_registry['gofast_' . $theme_function . '_original'] = $theme_registry[$theme_function];
    $theme_registry[$theme_function]['function'] = 'gofast_' . $theme_function;
  }
  // This overrides the default implementation of apachesolr_search_noresults
  // in order to make sure the filters sidebar still shows when the search yields no results
  $theme_registry['apachesolr_search_noresults'] = $theme_registry['search_results'];
}

/**
 * Implements theme_facetapi_title().
 */
function gofast_facetapi_title($variables) {
  return theme('gofast_facetapi_title_original', $variables) . '<span class="toggle"></span>';
}

/**
 * Implements theme_facetapi_count().
 */
function gofast_facetapi_count($variables) {
  return '<span class="facet-count">' . theme('gofast_facetapi_count_original', $variables) . '</span>';
}

/**
 * Overrides theme_facetapi_link_inactive().
 */
function gofast_facetapi_link_inactive($variables) {
  // Builds accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => FALSE,
  );
  $accessible_markup = theme('facetapi_accessible_markup', $accessible_vars);

  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $variables['text'] = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  $field = isset($variables['options']['field alias']) ? $variables['options']['field alias'] : '';
  $value = isset($variables['options']['value']) ? $variables['options']['value'] : '';

  if ($field && $value) {
    // Try to map the facet with an icon.
    $icon = gofast_facetapi_get_facet_icon($field, $value);
    // Adds bullet and keen styling to link
    if (empty($icon)) {
      $variables['text'] = '<span class="navi-bullet">
        <i class="bullet"></i>
      </span>
      <span class="navi-text">' .  $variables['text'] . '</span>';
    } else {
      $variables['text'] = $icon . '&nbsp;<span class="navi-text">' . $variables['text'] . '</span>';
    }
  }

  // Adds count to link if one was passed.
  if (isset($variables['count'])) {
    $variables['text'] .= ' ' . theme('facetapi_count', $variables);
  }

  // Resets link text, sets to options to HTML since we already sanitized the
  // link text and are providing additional markup for accessibility.
  $variables['text'] .= $accessible_markup;
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['class'][] = 'navi-link';

  return '<div class="facetapi-facet facetapi-inactive">'. theme_link($variables) .'</div>';
}

/**
 * Overrides theme_facetapi_link_active().
 */
function gofast_facetapi_link_active($variables) {
  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );

  $field = isset($variables['options']['field alias']) ? $variables['options']['field alias'] : '';
  $value = isset($variables['options']['value']) ? $variables['options']['value'] : '';

  if ($field && $value) {
    // Try to map the facet with an icon.
    $icon = gofast_facetapi_get_facet_icon($field, $value);
    // Adds bullet and keen styling to link
    if (empty($icon)) {
      $link_text = '<span class="navi-bullet">
        <i class="bullet"></i>
      </span>
      <span class="navi-text">' .  $link_text . '</span>';
    } else {
      $link_text = $icon . '&nbsp;<span class="navi-text">' . $link_text . '</span>';
    }
  }

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
  );
  $variables['text'] = t('!facetapi_deactivate_widget !facetapi_accessible_markup', $replacements, array('context' => 'gofast:gofast_search'));
  $variables['options']['html'] = TRUE;
  $variables['options']['attributes']['class'][] = 'navi-link';

  return '<div class="facetapi-facet facetapi-active">'  . $link_text . theme_link($variables). '</div>';
}

/**
 * Overrides theme_current_search_link_active().
 */
function gofast_current_search_link_active($variables) {
  return gofast_facetapi_link_active($variables);
}
