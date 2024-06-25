<?php

/**
 * Implements hook_menu
 */
function gofast_search_advanced_menu() {
  $items = array();

  $items['search/advanced'] = array(
    'page callback' => 'gofast_search_advanced_search',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  $items['advanced/search'] = array(
    'page callback' => 'gofast_search_advanced_search_query',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  $items['advanced/search/history'] = array(
    'page callback' => 'gofast_search_advanced_search_history',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  $items['advanced/search/fieldset'] = array(
    'page callback' => 'gofast_search_advanced_search_fieldset',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  $items['modal/%ctools_js/search/advanced/history/clear/confirm'] = array(
    'page callback' => 'gofast_search_advanced_history_clear_confirm',
    'type' => MENU_CALLBACK,
    'page arguments' => array(1),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );
  
  $items['search/advanced/filter/column'] = array(
    'page callback' => 'gofast_search_advanced_filter_column',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
  );

  return $items;
}

/**
 * Callback for advanced search page.
 *
 * @return $pageContent
 */
function gofast_search_advanced_search() {
  $content = theme('page_gofast_search_advanced_search');
  $pageContent = gofast_create_page_content($content);

  return $pageContent;
}

/**
 * Callback for advanced search page.
 */
function gofast_search_advanced_search_query(){

  $pagination = $_GET['pagination'];
  $query = $_GET['query'];
  $spaces = $_GET['spaces'];
  $categories = $_GET['categories'];
  $search_name = $_GET['name'];
  $options = json_decode($_GET['options'],TRUE);

  if(empty($pagination["page"])) $pagination["page"] = GOFAST_PAGINATION_PAGE_DEFAULT;
  if(empty($pagination["perpage"])) $pagination["perpage"] = GOFAST_PAGINATION_PERPAGE_DEFAULT;

  $filters_authorized = gofast_search_advanced_get_search_advanced_filters();
  // Get all filters authorized
  $all_filters = array();

  foreach($filters_authorized as $name => $filter){
    $all_filters = array_merge($all_filters, $filter['filters']);
  }

  // Rewrite key with solr field
  $index = 0;
  $tagify_filters = array();
  foreach($all_filters as $key => $filter){
    if($filter['search_column_hidden']){
      unset($all_filters[$key]);
      $index++;
      continue;
    }
    // If it's a tagify filter add it to a specific array
    if($filter['type'] == 'tagify'){
      $tagify_filters[] = $filter['solr_field'];
    }
    if(isset($filter['solr_field']) && $filter['solr_field'] != $key){
      // Insert the filter at the same place in the array
      $all_filters = array_merge(array_slice($all_filters, 0, $index), array($filter['solr_field'] => $filter), array_slice($all_filters, $index));
      unset($all_filters[$key]);
    }
    $index++;
  }

  $filters = array();

  //Get nid from spaces
  $spaces = json_decode($spaces);
  foreach($spaces as $space){
    $filters['sm_og_group_content_ref'][] = "node:" . $space->value;
    $json = gofast_ac_format_value_json('node', node_load($space->value));
    $history_filters['sm_og_group_content_ref'][] = json_encode($json);
  }

  // Get categories
  foreach($categories as $category){
    $category = str_replace("im_field_category-", "", $category);
    $filters['im_field_category'][] = $category;
    $history_filters['im_field_category'][] = $category;
  }
  // Match all options with filters authorized
  foreach($options as $name => $option_value){
    $curr_operator = $option_value['operator'];
    $curr_value = str_replace($name . '-', '',$option_value['value']);
    
    // Store the history filters
    $history_filters[$name]['operator'] = $curr_operator;
    $history_filters[$name]['value'] = $curr_value;
    if(isset($all_filters[$name]) && !empty($curr_value)){
      // If it'a date operator we need to format the date
      switch ($curr_operator) {
        case 'between':
          // Convert the value to an array
          $array_date = explode(" - ", $curr_value);
          // Format the date
          $array_date[0] = DateTime::createFromFormat('d/m/Y', $array_date[0]);
          $array_date[1] = DateTime::createFromFormat('d/m/Y', $array_date[1]);
          
          // Define the solr array filter
          $curr_value = ' [' . $array_date[0]->format('Y-m-d\TH:i:s\Z') . ' TO ' . $array_date[1]->format('Y-m-d\TH:i:s\Z') . ']';
          break;
        case 'lower':
          // Get the value and format it
          $curr_value = DateTime::createFromFormat('d/m/Y', $curr_value);
          // Define the solr array filter
          $curr_value = ' [' . $curr_value->format('Y-m-d\TH:i:s\Z') . ' TO *]';
          break;
        case 'higher':
          // Get the value and format it
          $curr_value = DateTime::createFromFormat('d/m/Y', $curr_value);
          // Define the solr array filter
          $curr_value = ' [* TO ' . $curr_value->format('Y-m-d\TH:i:s\Z') . ']';
          break;
        default:
          # code...
          break;
      }
      $filters[$name]['operator'] = $curr_operator;
      $filters[$name]['value'] = $curr_value;
    }
  }
  gofast_search_advanced_history_save($search_name, $query, $history_filters);
  
  // Check for tagify filters
  foreach($tagify_filters as $tagify_filter){
    if(isset($filters[$tagify_filter])){
      $tagify_values = json_decode($filters[$tagify_filter]['value'], TRUE);
      $filters[$tagify_filter]['value'] = array();
      foreach($tagify_values as $key => $tagify_value){

        // Convert $filters[$tagify_filter] to an array if it's not
        if(!is_array($filters[$tagify_filter])){
          $filters[$tagify_filter] = array($filters[$tagify_filter]);
        }
        // Replace $filters[$tagify_filter] by an array with all values
        $filters[$tagify_filter]['value'][$key] = $tagify_value['value'];
      }
    }
  }
  // Search function from gofast_search module
  $results = gofast_search_query($query, $filters);
  // Store some values in variables to reaffect later
  $nb_results = $results['results'];

  // Keep only data we want
  $results = array_map(function($result) use ($all_filters) {
    $filtered_result = array();

    // Check facet filters authorized and add them to the result
    foreach($all_filters as $key=>$filter) {
      if(isset($filter['solr_field']) && !empty($filter['solr_field'])){
        $key = $filter['solr_field'];
      }
      if(isset($result['fields'][$key])) {
          $filtered_result[$key] = $result['fields'][$key];
        } else if (isset($result[$key])){
          $filtered_result[$key] = $result[$key];
        }
        else {
          $filtered_result[$filter['']] = '';
        }
      }
      
      // add the path to the result to prevent path display in table
      $filtered_result['path'] = $result['fields']['path'];
      
      return $filtered_result;
    }, $results);

  // Unset some values we don't want to display
  unset($results['results']);
  unset($results['total']);
  unset($results['popularity']);
  unset($results['facets']);
  // Create an array of all metadata (corresponding to Type, Titre, Popularité...) inside an array to be compatible with datatable, be care to dont have the same name for metadata
  foreach($all_filters as $key => $facet){

    //If it's a separator, we don't add it to the metadata
    if($facet['type'] == 'separator' || $facet['search_column_hidden'] == TRUE) continue;

    if(isset($facet['solr_field']) && !empty($facet['solr_field'])){
      $key = $facet['solr_field'];
    }
  }

  // Reach all results to reformate them
  foreach($results as $key => $result){

    // Create drupal hook to modify the result
    foreach(module_implements('advanced_search_result_alter') as $module){
      $result = call_user_func($module . "_advanced_search_result_alter", $result);
    }
    $results[$key] = $result;
  }
  // Send data to keen datatable
  $kt_results['data'] = $results;
  $kt_results['meta']['total'] = $nb_results;
  $kt_results['meta']["sort"]="desc";
  $kt_results['meta']["page"] = $pagination["page"];
  $kt_results['meta']["pages"]= $kt_results['meta']['total'] / $pagination["perpage"];
  $kt_results['meta']["perpage"]= $pagination["perpage"];
  print json_encode($kt_results); exit;
}

/**
 * Callback for advanced search history block.
 */
function gofast_search_advanced_search_history(){
  $pagination = $_GET['pagination'];

  global $user;

  $account = user_load($user->uid);

  $json_history = $account->field_search_history[LANGUAGE_NONE][0]['value'];
  $search_history = json_decode($json_history, true);

  if(empty($search_history)){
    $search_history = array();
  }

  // Reverse array to get the last search first
  $search_history = array_reverse($search_history);


  // Send data to keen datatable
  $kt_results['data'] = $search_history;
  $kt_results['meta']['total'] = count($search_history);
  $kt_results['meta']["sort"]="desc";
  $kt_results['meta']["page"] = $pagination["page"];
  $kt_results['meta']["pages"]= $kt_results['meta']['total'] / $pagination["perpage"];
  $kt_results['meta']["perpage"]= $pagination["perpage"];
  print json_encode($kt_results); exit;
}


function gofast_search_advanced_search_fieldset(){
  $categories = $_GET['categories'];
  
  // Init the fieldset array
  // $fieldset = array();
  // foreach ($categories as $key => $category) {
  //   if($category['taxonomy_type'] == "category"){
  //     $fieldset[] = module_invoke_all('advanced_search_fieldset', $category['value']);
  //   }
  // }
}

/**
 * Callback for advanced search history clear form
 */
function gofast_search_advanced_history_clear_confirm($js){
  $form_id = 'gofast_search_advanced_history_clear_confirm_form';

  if (!$js) {
    $form = drupal_get_form($form_id);
    return $form;
  }

  ctools_include('modal');
  ctools_include('ajax');

  $form_state = array(
    'title' => t("Confirm deletion of advanced search history"),
    'ajax' => TRUE,
    're_render' => FALSE,
    'no_redirect' => TRUE,
  );

  $commands = ctools_modal_form_wrapper($form_id, $form_state);

  // Handle if submit with errors
  if (isset($commands[0])) {
    $commands[0]['output'] = gofast_normalize_string_from_ajaxifying($commands[0]['output']);
  }

  if ($form_state['executed']) {
    $commands[] = ajax_command_html('#ctools-add-js', "<script type='text/javascript'>$('#gofastAdvancedSearchHistory').KTDatatable('reload');</script>");
    $commands[] = ctools_modal_command_dismiss();
  }
  print ajax_render($commands);
  exit;
}

/**
 * Callback for get search column filter template
 */
function gofast_search_advanced_filter_column(){
  
  // Get column filters
  $columns_displayed = $_GET['columns_displayed'];
  // Get all metadatas
  $columns_filters = gofast_search_advanced_declare_all_metadatas(false);
  // Reach all filters and remove all useless filters
  $columns_result = array();
  foreach ($columns_filters as $key => $filter) {
    foreach ($filter as $key2 => $filter2) {
      if ($filter2['search_column_hidden'] || $filter2['type'] == "separator") {
        unset($columns_filters[$key][$key2]);
        continue;
      }
      $data = array();
      $data['title'] = $filter2['title'];
      $data['id'] =  $filter2['solr_field'];
      // If $data['solr_filed] is in $columns_displayed, we set $data['checked'] to true
      if (in_array($data['id'], $columns_displayed)) {
        $data['checked'] = true;
      }
      $columns_result[$key][] = $data;
    }
  }
  // Send data to template
  $content = theme('gofast_search_advanced_filters_columns', array('columns' => $columns_result));
  // Send data to keen datatable
  print json_encode($content); exit;
}
