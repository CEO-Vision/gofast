<?php



/**
 * Returns default settings for Gofast search environment.
 */
function gofast_search_settings_environment_default(){
  return array (
    'url' => 'http://localhost:8983/solr', // @todo https ?
    'make_default' => true,
    'name' => GOFAST_SEARCH_ENV_NAME,
    'env_id' => GOFAST_SEARCH_ENV_ID,
    'service_class' => '',
    'conf' => 
    array (
      'apachesolr_read_only' => '0',
      'apachesolr_direct_commit' => false,
      'apachesolr_soft_commit' => false,
      'apachesolr_access_always_add_grants' => false,
    ),
    'save' => 'Save',
    'form_id' => 'apachesolr_environment_edit_form',
    'op' => 'Save',
  );
}


/**
 * Returns default settings for the gofast search index.
 */
function gofast_search_settings_index_default() {
  return array (
    'env_id' => GOFAST_SEARCH_ENV_ID,
    'entities' => 
    array ( // @todo : comments / user / taxo entities ?
      'node' => 
      array (
        'article' => 'article',
        'alfresco_item' => 'alfresco_item',
        'forum' => 'forum',
        'group' => 'group',
        'organisation' => 'organisation',
        'page' => false,
        'book' => false,
      ),
    ),
    'submit' => 'Save',
    'form_id' => 'apachesolr_index_config_form',
    'op' => 'Save',
  );
}


/**
 * Returns default settings for the gofast search page.
 */
function gofast_search_settings_page_default() {
  return array (
    'search_page' => array (
      'page_id' => 'core_search',
      'label' => 'Core Search',
      'description' => 'Core Search',
      'search_path' => GOFAST_SEARCH_PATH,
      'page_title' => 'Search results ', // do not translate here because t() is called when outputting the value
      'env_id' => GOFAST_SEARCH_ENV_ID,
      'settings' => array (
        'fq' => array (),
        'apachesolr_search_custom_enable' => false,
        'apachesolr_search_search_type' => 'custom',
        'apachesolr_search_per_page' => 10,
        'apachesolr_search_spellcheck' => 1,
        'apachesolr_search_search_box' => 1,
        'apachesolr_search_allow_user_input' => false,
        'apachesolr_search_browse' => 'browse',
      ),
      'table' => 'apachesolr_search_page',
      'type' => 'Normal',
      'export_type' => 1,
    ),
    'label' => 'Core Search',
    'page_id' => 'core_search',
    'description_enable' => 1,
    'description' => 'Core Search',
    'make_default' => true,
    'env_id' => GOFAST_SEARCH_ENV_ID,
    'page_title' => 'Search results',
    'search_type' => 'custom',
    'search_path' => GOFAST_SEARCH_PATH,
    'custom_filter_enable' => false,
    'filters' => '',
    'advanced' => array (
      'apachesolr_search_per_page' => 10,
      'apachesolr_search_spellcheck' => 1,
      'apachesolr_search_search_box' => 1,
      'apachesolr_search_allow_user_input' => false,
      'apachesolr_search_browse' => 'browse',
    ),
    'submit' => 'Save',
    'submit_edit' => 'Save and edit',
    'form_id' => 'apachesolr_search_page_settings_form',
    'op' => 'Save',
  );
}

/**
 * Create Gofast search environment.
 */
function gofast_search_create_environment() {
  $env_settings = array('values' => gofast_search_settings_environment_default());
  drupal_form_submit($env_settings['values']['form_id'], $env_settings);
  return ($errors = form_get_errors()) ? $errors : TRUE;
}

/**
 * Setup the default index configuration for Gofast search environment
 */
function gofast_search_create_index() {
  $conf = array('values' => gofast_search_settings_index_default());
  drupal_form_submit($conf['values']['form_id'], $conf);
  return ($errors = form_get_errors()) ? $errors : TRUE;
}

/**
 * Create Gofast default search page.
 */
function gofast_search_create_page() {
  $page = array('values' => gofast_search_settings_page_default());
  drupal_form_submit($page['values']['form_id'], $page);
  return ($errors = form_get_errors()) ? $errors : TRUE;
}


