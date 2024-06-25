<?php

/**
 * function gofast_search_advanced_get_search_advanced_filters
 * @return array
 *
 * Return the filters for the advanced search
 */
function gofast_search_advanced_get_search_advanced_filters(){

  $filters = gofast_search_advanced_declare_standard_metadatas()['metadatas'];
  $fieldset_filters['default'] = array(
    'title' => t('SEARCH AREA : Information'),
    'filters' => $filters,
    'weight' => 0,
  );

  // Special filters
  $fieldset_filters_final = array_merge($fieldset_filters, module_invoke_all('search_advanced_filters'));

  // Sort with weight DESC
  uasort($fieldset_filters_final, function($a, $b){
    return $a['weight'] - $b['weight'];
  });


  return $fieldset_filters_final;

}


function gofast_search_advanced_history_save($name, $query, $filters){
  global $user;

  $account = user_load($user->uid);

  // Get account search_history
  $search_history = $account->field_search_history[LANGUAGE_NONE][0]['value'];
  // If the search history is not empty, decode it
  if(!empty($search_history)){
    $search_history = json_decode($search_history, true);
  }else{
    $search_history = array();
  }
  // Save the history on the search history cookies array
  $history = array();
  $history['query'] = $query;
  $history['filters'] = json_encode($filters);
  $history['name'] = $name;
  $history['date'] = date('d/m/Y H:i:s');
  // If the search history is not empty, add the new search to the array
  if(!empty($search_history)){
    $search_history[] = $history;
  }
  else{
    $search_history[0] = $history;
  }

  // Saved it to the user account
  $account->field_search_history["und"][0] = array(
    'value' => json_encode($search_history),
  );
  user_save($account);
}


/**
 * Returns an array of allowed taxonomy values for a given field name.
 *
 * @param string $field_name
 *   The name of the field for which to retrieve allowed taxonomy values.
 *
 * @return array
 *   An array of allowed taxonomy values for the given field name.
 */
function gofast_advanced_search_get_taxonomy($field_name){

  $allow_taxonomy_value = taxonomy_allowed_values(field_info_field($field_name));
    // Retrieve the allowed taxonomy values for the given field name.
    // Loop through each allowed taxonomy value.
    foreach ($allow_taxonomy_value as $tid => $term) {
      // Localize the taxonomy term name.
      $localized_term = i18n_taxonomy_localize_terms(taxonomy_term_load($tid));
      // Add the localized term to the array of allowed taxonomy values.
      $allow_taxonomy_value[$localized_term->tid] = $localized_term->name;
    }
    // Return the array of allowed taxonomy values.
    return $allow_taxonomy_value;
}


/**
 * Returns an array of allowed language values.
 *
 * @return array
 *   An array of allowed language values.
 */
function gofast_advanced_search_get_language(){
    // Retrieve the allowed language values.
    $all_languages = locale_language_list('name', TRUE);
    // Don't keep technical languages in languages list.
    $languages = array_filter($all_languages, fn($el) => $el != "gfen", ARRAY_FILTER_USE_KEY);
    return $languages;
}

function gofast_search_advanced_history_clear(){

  global $user;

  $account = user_load($user->uid);

  // Get account search_history
  $search_history = $account->field_search_history[LANGUAGE_NONE][0]['value'];

  // Remove the search history
  $account->field_search_history["und"][0] = array(
    'value' => '',
  );
  user_save($account);
}

/**
 * Returns an array of category options for the advanced search form.
 *
 * @return array
 *   An array of category options, keyed by category ID and with category name as value.
 */
function gofast_search_advanced_get_categories(){
  $categories_standard = array();
  $categories_custom = array();

  $terms = taxonomy_term_load_multiple(FALSE, array('vid' => GOFAST_VID_CATEGORY));

  //sort form table
  usort($terms, function ($a, $b) {
    return (i18n_taxonomy_localize_terms($a)->name < i18n_taxonomy_localize_terms($b)->name) ? -1 : 1;
  });

  foreach ($terms as $term) {

    $localized_term = i18n_taxonomy_localize_terms($term);
    if ($term->field_standard_gf[LANGUAGE_NONE][0]['value'] == 1) {
      $categories_standard['im_field_category-' . $localized_term->tid] = $localized_term->name;
    } else {
      $categories_custom['im_field_category-' . $localized_term->tid] = $localized_term->name;
    }
  }

  $categories[t('Standard', array(), array('context' => 'gofast'))] = $categories_standard;
  $categories[t("@site_name's categories", array('@site_name' => variable_get('site_name')), array('context' => 'gofast'))] = $categories_custom;

  return $categories;
}
