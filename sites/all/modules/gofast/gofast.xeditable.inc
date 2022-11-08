<?php

/**
 * Extends du hook_library pour inclure la librairie x-editable (et ses dépendances) nécessaires pour l'édition inline/popup
 *
 * @return string
 */
function gofast_xeditable_libraries_info(&$libraries) {

  $libraries['typeaheadjs'] = array(
    'name' => 'typeaheadjs',
    'vendor url' => 'https://vitalets.github.io/x-editable/',
    'download url' => 'https://vitalets.github.io/x-editable/assets/zip/bootstrap3-editable-1.5.1.zip',
    'version' => '3.5.4',
    'version callback' => 'short_circuit_version',
    'files' => array(
      'js' => array(
        'typeaheadjs.js'=> array(
          'group' => 104,
        ),
        'lib/typeahead.js'=> array(
          'group' => 104,
        )
      ),
      'css' => array(
        'lib/typeahead.js-bootstrap.css'
      )
    ),
    'dependencies' => array(
      'x-editable',
    ),
  );

/*   $libraries['select2'] = array(
    'name' => 'select2',
    'vendor url' => 'https://select2.github.io/',
    'download url' => 'https://github.com/select2/select2/archive/3.5.4.zip',
    'version' => '3.5.4',
    'version callback' => 'short_circuit_version',
    'files' => array(
      'js' => array(
        'select2.min.js',
      ),
      'css' => array(
        'select2.css',
        'select2-bootstrap.css',
      ),
    ),
  ); */

  $libraries['ckeditor'] = array(
    'name' => 'ckeditor',
    'vendor url' => 'http://ckeditor.com/',
    'download url' => 'http://download.cksource.com/CKEditor/CKEditor/CKEditor%204.5.6/ckeditor_4.5.6_standard.zip',
    'version' => '4.5.6',
    'version callback' => 'short_circuit_version',
    'files' => array(
      'js' => array(
        'ckeditor.js'=> array(
          'every_page' => TRUE,
        ),
        '/adapters/jquery.js',
      ),
    ),
  );

  $libraries['x-editable'] = array(
    'name' => 'x-editable for bootstrap',
    'vendor url' => 'https://vitalets.github.io/x-editable/',
    'download url' => 'https://vitalets.github.io/x-editable/assets/zip/bootstrap3-editable-1.5.1.zip',
    'version' => '1.5.1',
    'version callback' => 'short_circuit_version',
    'files' => array(
      'js' => array(
        'dist/bootstrap3-editable/js/bootstrap-editable.js' => array(
          'group' => 103,
        ),
        'dist/inputs-ext/typeaheadjs/typeaheadjs.js'=> array(
          'group' => 104,
        ),
        'dist/inputs-ext/typeaheadjs/lib/typeahead.js'=> array(
          'group' => 104,
        )
      )
    ),
    'dependencies' => array(
      'bootstrap-datetimepicker',
      'ckeditor',
    ),
  );
}

/**
 * Extends hook_menu()
 */
function gofast_xeditable_menu() {

  $items = array();

  // Editable field submission menu callback
  $items['update_field'] = array(
    'page callback' => 'gofast_update_field',
    'page arguments' => array(),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => TRUE, // form validation handle this.
    'delivery callback' => 'gofast_ajax_delivery'
  );

  // Editable field submission menu callback
  $items['update_node_field'] = array(
    'page callback' => 'gofast_update_node_field',
    'page arguments' => array(),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => TRUE, // form validation handle this.
    'delivery callback' => 'gofast_ajax_delivery'
  );

  // Editable field submission menu callback
  $items['update_alfresco_item_properties'] = array(
    'page callback' => 'gofast_update_alfresco_item_properties',
    'page arguments' => array(),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => TRUE, // form validation handle this.
    'delivery callback' => 'gofast_ajax_delivery'
  );

  // Editable field submission menu callback
  $items['update_user_groups'] = array(
    'page callback' => 'gofast_update_user_groups',
    'page arguments' => array(),
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'delivery callback' => 'gofast_ajax_delivery'
  );

  $items['popup/%'] = array(
    'title' => 'Show popup with specified block in it',
    'description' => "Render block popup",
    'page callback' => 'gofast_popup_block',
    'page arguments' => array(1),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
  );

  $items['gofast/node_autocomplete'] = array(
    'page callback' => 'gofast_xeditable_node_autocomplete',
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
  );

  $items['gofast/tag_autocomplete'] = array(
    'page callback' => 'gofast_xeditable_tag_autocomplete',
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
  );

    $items['xeditable/get/subscribe/%/%'] = array(
    'page callback' => 'gofast_xeditable_get_subscribe_term_link',
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'page arguments' => array(3,4),
    'type' => MENU_CALLBACK,
  );

  return $items;
}

/**
 * Extends hook_theme
 * @param type $themes
 * @return type
 */
function gofast_xeditable_theme(&$themes) {

  $themes['x-editable_field'] = array(
    'template' => 'tpl/x-editable_field',
    'variables' => array(
      'xeditable_vars' => gofast_xeditable_get_default_values()
    ),
  );

  $themes['popup_content'] = array(
    'template' => 'tpl/popup_content',
    'variables' => array(
      'popup_variables' => array(
        'container_class' => NULL,
        'title' => NULL,
        'link_text' => NULL,
        'link_class' => NULL,
        'type' => 'button',
        'placement' => NULL,
        'content' => NULL,
        'js_callback' => NULL,
      )
    )
  );

  $themes['book_popup_content'] = array(
    'template' => 'tpl/book_popup_content',
    'variables' => array(
      'popup_variables' => array(
        'container_class' => NULL,
        'title' => NULL,
        'link_text' => NULL,
        'link_class' => NULL,
        'type' => 'button',
        'placement' => NULL,
        'content' => NULL,
        'js_callback' => NULL,
      )
    )
  );
}

function gofast_xeditable_enrich_values($array_field_values, $empty = "") {
  return array(
    'xeditable_vars' => array_replace_recursive(gofast_xeditable_get_default_values($empty), $array_field_values));
}

function gofast_xeditable_get_default_values($empty = NULL) {
  if(!isset($empty)){
    t('None', array(), array('context' => 'gofast'));
  }
  return array(
    'pk' => NULL,
    'name' => NULL,
    'value' => NULL,
    // Additionnal data
    'title' => NULL,
    'source' => NULL,
    'params' => array(),
    'type' => 'text',
    'format' => NULL,
    'emptytext' => $empty,
    'placement' => 'bottom',
    'mode' => 'inline',
    'url' => '/update_field',
    'wrapper_class' => array(),
    'delegated' => 'false',
    'onblur' => 'ignore',
  );
}

/**
 * Editable field function callback : node bundle only
 */
function gofast_update_node_field() {
  global $user;

  // Retrieve submitted POST values and auto-assign variables.
  extract($_POST, EXTR_PREFIX_SAME, '_');

  $nid = $pk;
  $field_name = $name;

  //Wait for the lock to be available
  lock_wait("update_node_field_" . $nid, 15);
  //Acquire the lock
  lock_acquire("update_node_field_" . $nid, 15.0);

  //check cookie value to prevent notification or not
  if($_COOKIE["prevent_notify"] == "true"){
    $_POST['prevent_notify'] = true;
  }else{
    $_POST['prevent_notify'] = false;
  }

  // Validator for field changes. If values is different from node saved value, continue, else return
  if(!isset($value)) {
    $value = '';
  }

  // Load the account being edited.
  $node = node_load($nid, NULL, TRUE);

  if(!isset($node->nid)) {
    cache_clear_all("field:node:$node->nid", 'cache_field');
    //Release the lock
    lock_release("update_node_field_" . $nid);
    return gofast_update_field_error($field_name, 'load_entity');
  }
  //Get OG node type to make specific cleaning
  $og_node_types = array_keys (gofast_og_node_types($prevent_translation = TRUE));


  if (is_array($value)) {
    $new_values = [];
    foreach($value as $vkey => $val){ // We need to clear technical values
      if($field_name == "field_target_link"){
        array_push($new_values, gofast_xss_clean($val['value']));
      }else if($field_name == "field_tags"){
        array_push($new_values, gofast_xss_clean(is_array($val) ? $val['name'] : $val));
      }else if(strpos($val, '[GOFAST_TAG_SEPARATOR]') !== FALSE){
        unset ($value[$vkey]);
      }else{
        // XSS control if this node is not whitelisted
        $default_documents_form_configuration = array(
          'xss_whitelist' => [],
        );
        $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
        $xss_whitelist = is_array($documents_form_defaults['xss_whitelist']) ? $documents_form_defaults['xss_whitelist'] : [];
        if(in_array($nid, $xss_whitelist, TRUE) || $node->field_is_homepage[LANGUAGE_NONE][0]['value'] == 1){
          array_push($new_values, $val);
        }else{
          array_push($new_values, gofast_xss_clean($val));
        }
      }
     }
    $value = $new_values;
  }else{
    // XSS control if this node is not whitelisted
    $default_documents_form_configuration = array(
      'xss_whitelist' => [],
    );
    $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
    $xss_whitelist = is_array($documents_form_defaults['xss_whitelist']) ? $documents_form_defaults['xss_whitelist'] : [];
    if(!in_array($nid, $xss_whitelist, TRUE) && $node->field_is_homepage[LANGUAGE_NONE][0]['value'] != 1){      
      $value = gofast_xss_clean($value);
    }
  }

  $user_update_access = node_access("update", $node);
   if($_POST['technically_save'] === TRUE){
       $user_update_access = true;
   }
  if($node->type === 'alfresco_item') {
    $locked_owner = gofast_cmis_webservice_execute_request('getlocked', $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
    $node_unlocked = $locked_owner === 'nolocked';
  } else {
    $node_unlocked = TRUE;
  }
  $user_allowed = ($node->uid === $user->uid || gofast_user_is_adm($user) || $user->uid === 1);

  if(!$user_allowed && !$user_update_access) {
    cache_clear_all("field:node:$node->nid", 'cache_field');
    lock_release("update_node_field_" . $nid);
    return gofast_update_field_error($field_name, 'permissions');
  }
  if(!$node_unlocked) {
    cache_clear_all("field:node:$node->nid", 'cache_field');
    lock_release("update_node_field_" . $nid);
    return gofast_update_field_error($field_name, 'lock');
  }

  // Load entity wrapper.
  $wrapper = entity_metadata_wrapper('node', $node);

  //url_alias field
  if($field_name == "field_alias"){
        //first, check if this alias already exists
        $conditions_already_exists = array('alias' => $value);
        $existing_path_already_exists = path_load($conditions_already_exists);
        if(isset($existing_path_already_exists['pid'])){
             return gofast_update_field_error($field_name, 'already_exists');
             exit;
        }

        // Ensure fields for programmatic executions.
        $conditions = array('source' => 'node/' . $node->nid);
        $existing_path = path_load($conditions);
        if($existing_path["alias"]){
           //already exists
             if ($value != "") {
                    $path['pid'] = $existing_path['pid'];
                    $path['alias'] = trim(str_replace(" ", "_", $value));
                    path_save($path);
             }else{
                  //value is empty, delete path
                  path_delete($existing_path);
             }
        }else{
           //no existing alias for this document
            $path = array();
            $path['alias'] = trim(str_replace(" ", "_", $value));
            $path['source'] = 'node/' . $node->nid;
            $path['language'] = LANGUAGE_NONE;
            path_save($path);
        }

       return json_encode(array("status" => "OK", "newValue" => $value));
  }

  if ($value === $wrapper->{$field_name}->value() && !isset($broadcast)) {
    cache_clear_all("field:node:$node->nid", 'cache_field');
    lock_release("update_node_field_" . $nid);
    return $value;
  }

  // Load profile form so we can rely on '#validate' and '#element_validate'
  // handlers. Here we eschew drupal_get_form() to prevent some "alter" errors,
  // instead we manually build the info and call drupal_build_form().
  $form_id = $node->type . '_node_form';
  $form_state = array('build_info' => array('args' => array($node)));
  // Ensure include files are loaded so the form can be processed.
  form_load_include($form_state, 'inc', 'node', 'node.pages');

  // Build $form.
  //Temporary, while understanding why it cause https://srv01.ceo-vision.com/jira_new/browse/GOFAST-2849
  //Used to by-passed og_field_access() in form_alter that prevent editing a space under some condition cf. GOFAST-5822
   if(in_array($node->type , $og_node_types) && ($name=='body' || $field_name == 'title')){
       $form = array();
   }else{
        $form = drupal_build_form($form_id, $form_state);
   }

  // Custom process for date fields
  if ($date_field = in_array($wrapper->{$field_name}->info()['type'], array('date', 'time', 'datetime'))) {
    $_fdate = new DateTime();
    if ($value === "") {
      $value = null;
    }
    else {
      $_fdate = DateTime::createFromFormat(variable_get('date_format_short', 'm/d/Y - H:i'), $value);
      if (!$_fdate) $_fdate = DateTime::createFromFormat(variable_get('date_format_short_without_hours', 'm/d/Y'), $value);
      $timestamp_date = $_fdate->getTimestamp();
      $property_date = $_fdate->date;
      $value = $timestamp_date;
    }
  }

  if($field_name === 'title') {
    $form_state['values'][$field_name] = $value;
  }elseif($field_name === 'field_category' || $field_name === 'field_state'){
    //specific case for pre-archived node
     if(gofast_retention_get_retention_date($node) !== NULL && gofast_get_content_state_archived($node)){
         //doc is un DUA and have pre-archived state, so we can check if the user has permission to update category
         if(($field_name === 'field_state' && !node_access("delete", $node)) || $field_name === 'field_category'){
             watchdog("GOFAST debug", $node->title);
              cache_clear_all("field:node:$node->nid", 'cache_field');
              //Release the lock
              lock_release("update_node_field_" . $node->nid);
              return gofast_update_field_error($field_name, 'field_category');
         }
     }
  }else if (isset($form_state['values'][$field_name][LANGUAGE_NONE][0]['default'])) {
    $form_state['values'][$field_name][LANGUAGE_NONE][0]['default'] = $value;
  }
  else if (isset($form_state['values'][$field_name][LANGUAGE_NONE][0]['value'])) {
    if(is_array($value)){ //Check if $value contains an array or a string
      foreach ($value as $key => $val) {
        $form_state['values'][$field_name][LANGUAGE_NONE][$key]['value'] = $val;
      }
    }
    else{
      $form_state['values'][$field_name][LANGUAGE_NONE][0]['value'] = $value;
    }
  }



  // Validate form and check for error.
  drupal_validate_form($form_id, $form, $form_state);
  //$errors = form_get_errors();

  //We unset target links related errors as a user may not have access to all target links but may be
  //Allowed to edit the node. This is a workaround for GOFAST-2982
  if(isset($errors)){
    $errors = array_filter( $errors, function($key){
      return strpos($key, 'field_target_link') !== 0;
    }, ARRAY_FILTER_USE_KEY );
  }
  drupal_get_messages(); //Prevent drupal messages. To improve.

  if(!empty($errors) && !isset($errors["og_group_content_ref][und][0"])) {
    cache_clear_all("field:node:$node->nid", 'cache_field');
    lock_release("update_node_field_" . $nid);
    return gofast_update_field_error($field_name, NULL, $errors);
  }

  // Prevent having 2 nodes with the same title within a single space
  // Or containing special characters in the title.
  if(gofast_og_is_space($node, TRUE) && $field_name == 'title'){
    // All content types are subject to the same validator.
    if (!gofast_validate_filename($value)) {
      $errors = t('Title contains illegals characters or an invalid name.', array(), array('context' => 'gofast'));
      return gofast_update_field_error($field_name, NULL, $errors);
    }

    // Specific rules for Gofast Spaces.
      if (strpos($value, '_') === 0 || strpos($value, '#') === 0){
        $errors = t('A space title cannot begin with an [_] or [#].', array(), array('context' => 'gofast'));
        return gofast_update_field_error($field_name, NULL, $errors);
      }

      if (strpos($value, '#') !== FALSE){
        $errors =   t('A space title cannot contain the following char [#].', array(), array('context' => 'gofast'));
        return gofast_update_field_error($field_name, NULL, $errors);
      }

      $parent_gid = $node->og_group_ref[LANGUAGE_NONE][0]["target_id"] ? $node->og_group_ref[LANGUAGE_NONE][0]["target_id"] : array();
      $nids = array();
      $nids += gofast_og_get_content($parent_gid) + gofast_og_get_children($parent_gid);
      // remove the node from the list to check.
      unset($nids[$node->nid]);

      if (!empty($nids)) {
        // Check if any matches occurs.
        $duplicates = db_select('node', 'n')
          ->fields('n', array('nid'))
          ->condition('type', 'alfresco_item', '<>')
          ->condition('nid', $nids, 'IN')
          ->condition('title', $value, '=')
          ->execute()
          ->fetchAllAssoc('nid');

        if (!empty($duplicates)) {
          $errors = t('A node having the same title and the same parent space already exists. Please set another title.', array(), array('context' => 'gofast'));
          return gofast_update_field_error($field_name, NULL, $errors);
        }
      }
  }



  // At this point $value is validated so we can save it safely.
  try {
    // If vid param is present, we process taxonomy terms.
    if (isset($vid) && $vid !="") {
      $terms = array();
      if(is_array($value)) {
        if ($field_name === 'field_tags'){
          // if value come from tags filed we gard the same values
          foreach ($value as $term) {
            if (isset($term['name']))
              $terms[] = $term['name'];
            else
              $terms[] = $term;
          }
        } else {
          foreach($value as $term) {
            if(intval($term) === 0) {
                $terms[] = $term;
            }
          }
        }
      } else if(!empty($value)) {
            $terms[] = $value;
      }

      if (!empty($terms) && $field_name === 'field_tags') {
        $normalized_values = gofast_metadata_terms_get_from_array($vid, $terms);
      }else if(!empty($terms)) {
        $normalized_values = gofast_xeditable_terms_get_from_array($vid, $terms);
      }else{
        $normalized_values = null;
      }

      // If dealing with other than tags, field is single valued
      if($vid !== GOFAST_VID_TAGS && $normalized_values !== null) {
        $normalized_values = reset($normalized_values);
      }
    }  else {
      // If value is "", then the value we want to store DB wise is null
      $normalized_values = !empty($value) ? $value : null;
    }

    // Then set and save the wrapped element
    if ($field_name === 'body') {
      // XSS control if this node is not whitelisted
      $default_documents_form_configuration = array(
        'xss_whitelist' => [],
      );
      
      if($node->type == 'article'){
        gofast_cmis_article_node_update($form, $form_state);      
      }
      $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
      $xss_whitelist = is_array($documents_form_defaults['xss_whitelist']) ? $documents_form_defaults['xss_whitelist'] : [];

      if(!in_array($nid, $xss_whitelist, TRUE)){
        $normalized_values = gofast_xss_clean($normalized_values);
      }

      // In the case we would like to update the body, we set the summary field instead.
      $wrapper->{$field_name}->value->set($normalized_values);
    }else if ($field_name === GOFAST_OG_CONTENT_MEMBERSHIP_FIELD) {
      // In cas we update an article/forum, we update og_group_content_ref
      $groups = array();
      foreach ($normalized_values as $normalized_value) {
        $groups[] = $normalized_value;
      }
      $node_og_field = $node->og_group_content_ref[LANGUAGE_NONE];

      $node_current_og = array();
      foreach($node_og_field as $grid){
        $node_current_og[] = $grid['target_id'];
      }

      $node_new_og = array();
      foreach($groups as $grid){
        $node_new_og[] = $grid;
      }

      $deleted_groups = array_diff($node_current_og, $node_new_og);
      $added_groups = array_diff($node_new_og, $node_current_og);

      // Then we update the membership
      foreach($added_groups as $grid){
        gofast_og_subscribe_node($grid, $nid);
      }
      foreach($deleted_groups as $grid){
        gofast_og_unsubscribe_node($grid, $nid);
      }
      $node = node_load($nid, NULL, TRUE);

      //I don't know why, but the node_load doesn't take care of the unsubscribing made juste before, so I have to manuallt remove these
      // groups on the field og_group_content_ref, because if I don't do this, these groups will we added again during the node_save
      if(count($deleted_groups) > 0){
          foreach($deleted_groups as $grid){
            foreach($node->og_group_content_ref[LANGUAGE_NONE] as $key=>$group){
              if($group["target_id"] == $grid){
                  unset($node->og_group_content_ref[LANGUAGE_NONE][$key]);
              }
            }
          }
      }
    }else if ($field_name === GOFAST_CMIS_LOCATIONS_FIELD) {
        if(isset($broadcast)){
            $broadcast_string = trim($_POST["broadcast_og-hidden-values"]);
            $broadcast_array = explode(" ", $broadcast_string);
            if(count($broadcast_array) > 0){
                foreach($broadcast_array as $gid){
                    if(is_numeric($gid)){
                        $broadcast[] = $gid;
                    }
                }
            }
        }
        if($broadcast[0] == ""){
            unset($broadcast[0]);
        }
        if($broadcast && count($broadcast) != 0){
            global $cmis_as_publisher;
            global $cmis_sudo_admin;
            $cmis_as_publisher = true;
            $cmis_sudo_admin = true;
            //we are in case the user choosed at least one "broadcast" location, in other word a location in which he's not member of
            //we add this location to the $normalized_values array
            foreach($broadcast as $mynid){
                if(is_numeric($mynid)){
                    $normalized_values[] = $mynid;
                }
            }
        }
      // In the case we update locations, we need to update this field but also og_group_content_ref with groups if there are some.
      $groups = array();
      $emplacements_url = array();

      foreach ($normalized_values as $key => $normalized_value) {
        if (intval($normalized_value) !== 0) {
          $group_id = $normalized_value;
          $group_path = gofast_cmis_space_get_webdav_path($group_id);
          $normalized_values[$key] = $group_path;

          $emplacements_url[] = l($group_path, "/node/" . $group_id);
        }
        else {
          $group_id = FALSE;
          $path = htmlspecialchars_decode($normalized_value);
          $folders = '';
          $group_id = gofast_og_get_group_id_from_title_2($path, TRUE);

          $emplacements_url[] = l($normalized_value, "/node/" . $group_id, array('attributes' => array("class" => "ajax-navigate", "nid" => $group_id)));
        }

      //check if user has permission to add/move document into this group
        $group = node_load($group_id);
        //if its a new location compare to existing one on the node
        $existing_locations = $wrapper->{$field_name}->value();
        if(array_search($normalized_value, $existing_locations) === NULL){
            if(!og_user_access("node", $group_id, "create alfresco_item content") ){
                $errors = t("You don't have write permission into space", array(), array('context' => 'gofast'))." ".$group->title;
                cache_clear_all("field:node:$node->nid", 'cache_field');
                lock_release("update_node_field_" . $nid);
                 return gofast_update_field_error($field_name, NULL, $errors);
            }
        }

        $groups[] = $group_id;
      }
      $groups = array_unique($groups);
      if(count($groups) == 0){
          $errors = t("Error", array(), array('context' => 'gofast'));
          cache_clear_all("field:node:$node->nid", 'cache_field');
          lock_release("update_node_field_" . $nid);
          return gofast_update_field_error($field_name, NULL, $errors);
      }
      //We need to know which groups has been added and which ones has been removed
      $node_og_field = $node->og_group_content_ref[LANGUAGE_NONE];

      $node_current_og = array();
      foreach($node_og_field as $key=>$gid){
          //unset($node_og_field[$key]);
          $node_current_og[] = $gid['target_id'];
      }
      $node_new_og = array();
      foreach($groups as $grid){
        $node_new_og[] = $grid;
      }
      //$deleted_groups = gofast_array_diff_recursive($node_og_field, $node_new_og);
      //$added_groups = gofast_array_diff_recursive($node_new_og, $node_og_field);

      $deleted_groups = array_diff($node_current_og, $node_new_og);
      $added_groups = array_diff($node_new_og, $node_current_og);

      // print_r($deleted_groups);print_r($added_groups);print_r($node_new_og);print_r($node_og_field);exit;
      // Then we update the membership
       if(count($added_groups) > 0){
            foreach($added_groups as $grid){
              gofast_og_subscribe_node($grid, $nid);
            }
       }

       if(count($deleted_groups) > 0){
            foreach($deleted_groups as $grid){
              gofast_og_unsubscribe_node($grid, $nid);
              foreach($node->og_group_content_ref[LANGUAGE_NONE] as $key=>$group){
                  if($group["target_id"] == $grid){
                      unset($node->og_group_content_ref[LANGUAGE_NONE][$key]);
                  }
              }
            }
       }
      //Then we reload the node, reseting the cache and we update the location field
      cache_clear_all("field:node:$node->nid", 'cache_field');
      $node = node_load($nid, NULL, TRUE);

      //I don't know why, but the node_load doesn't take care of the unsubscribing made juste before, so I have to manuallt remove these
      // groups on the field og_group_content_ref, because if I don't do this, these groups will we added again during the node_save
      if(count($deleted_groups) > 0){
            foreach($deleted_groups as $grid){
              foreach($node->og_group_content_ref[LANGUAGE_NONE] as $key=>$group){
                  if($group["target_id"] == $grid){
                      unset($node->og_group_content_ref[LANGUAGE_NONE][$key]);
                  }
              }
            }
       }

      $node->field_emplacement[LANGUAGE_NONE] = array();
      foreach($normalized_values as $location){
        $node->field_emplacement[LANGUAGE_NONE][] = array('value' => $location);
      }
      $node->field_main_emplacement[LANGUAGE_NONE][0]['value'] = reset($normalized_values);
      //$wrapper->{$field_name}->set($normalized_values);
      $value = implode('<br />', $emplacements_url);
    }else if ($field_name === 'language') {
      $translatable_languages = gofast_get_translation_languages(FALSE);
      $value = gofast_get_flag_icon_by_langcode($value) . '&nbsp;' . $translatable_languages[$value];
      $wrapper->{$field_name}->set($normalized_values);
    }else if ($field_name === 'field_target_link') {
      if(is_array($value)) {
        if (is_array($normalized_values)) {
          foreach ($normalized_values as $link) {
            $values_links[] = $link;
          }
          $normalized_values = $values_links;
        }
      }
      $wrapper->{$field_name}->set($normalized_values);
    }else if ($field_name === 'field_external_page_url') {
      if(is_array($value)){
        $external_links = array_map(function($element) {
          $url = !isset(parse_url($element)["scheme"]) ? 'http://' . $element : $element;
          return l($element, $url);
        }, $value);
        $value = implode("<br />", $external_links);
      }
      if(count($normalized_values) == 1){
        if(is_numeric($node->field_format[LANGUAGE_NONE][0]['tid']) && taxonomy_term_load($node->field_format[LANGUAGE_NONE][0]['tid'])->name == "External Web Page"){
            //This is an external page and we juste updated it's external url field, change the content
            $url = reset($normalized_values);
            $reference = $node->field_reference[LANGUAGE_NONE]['0']['value'];
            $updated_item = gofast_cmis_item_set_content($reference, gofast_cmis_extract_external_page_from_url($url));
        }
      }
      $wrapper->{$field_name}->set($normalized_values);
    }else if ($field_name === 'title') {
      $old_title = $wrapper->{$field_name}->value();
      $pathinfo = pathinfo($old_title);
      $new_title = isset($pathinfo['extension']) && $pathinfo['extension'] !== NULL ? '.' . $pathinfo['extension'] : '';
      if(gofast_og_is_space($node)) {
          $homepage = gofast_og_get_article_homepage($node);
          if(isset($homepage->nid)){
            $homepage->title = $value . ".html";
            node_save($homepage);
          }
      }
      if($node->type  === 'alfresco_item'){
        if(isset($_POST['non_xeditable'])){ //Request from external module
          $wrapper->{GOFAST_CMIS_FILENAME_FIELD}->set($value);
          $wrapper->{$field_name}->set($value);
        }
        else{
          $wrapper->{GOFAST_CMIS_FILENAME_FIELD}->set($value . $new_title);
          $wrapper->{$field_name}->set($value . $new_title);
        }
      }else{
          $wrapper->{$field_name}->set($value);
      }
    }else {
        if($normalized_values == false){
            $wrapper->{$field_name}->set(NULL);
        }else{
            $wrapper->{$field_name}->set($normalized_values);
        }
    }

    //Only if module gofast_retention (DUA) enable
    if (module_exists('gofast_retention')) {
      if ($field_name === 'field_category' && $node->type  === 'alfresco_item') {
        gofast_retention_set_node_retention_end_date($value, $node, true);
      } elseif ($field_name === 'field_state' && $node->type  === 'alfresco_item') {
        gofast_retention_set_node_retention_end_date($value, $node, false);
      }
    }

    ## GOFAST-5572 Update drupal node version ( corresponding to aflresco version) before save
    $node_ref = gofast_cmis_node_get_item_id($node);
    $item_version = gofast_cmis_webservice_item_get_versions($node_ref);
    $node->{GOFAST_CMIS_CURRENT_VERSION}[LANGUAGE_NONE][0]['value'] = $item_version[0]->label;
    if ($field_name === GOFAST_CMIS_LOCATIONS_FIELD || $field_name === GOFAST_OG_CONTENT_MEMBERSHIP_FIELD) {
        if($_POST['technically_save'] === TRUE){
            $node = gofast_prepare_node_save_technically($node);
            $ruid = $node->revision_uid;
            node_save($node);
            db_update('node_revision')
              ->fields(array('uid' => $ruid))
              ->condition('nid', $node->nid)
              ->execute();
        }else{
            $_POST["is_location_update"] = TRUE;
            node_save($node);
        }
    } else{
       // $wrapper->save();/** @todo : (missing) hooks implementations */
       if($_POST['technically_save'] === TRUE){
             //because function gofast_prepare_node_save_technically doesn't work for wrapper, I have to do differently
           global $technically_changed;
           $technically_changed = $wrapper->changed->value();
            $_POST['prevent_notify'] = TRUE;
            $wrapper->save();
            unset($technically_changed);
        }else{
            $wrapper->save();/** @todo : (missing) hooks implementations */
        }
    }
  }
  catch (EntityMetadataWrapperException $e) {
    $error = array($e->getMessage());
    watchdog("debug groups xeditable error", json_encode($error));
    cache_clear_all("field:node:$node->nid", 'cache_field');
    lock_release("update_node_field_" . $nid);
    return gofast_update_field_error($field_name, NULL, $error);
  }

  $return_value = "";
  if ($date_field) {
    if (isset($date_str)) {
      $return_value = $date_str;
    }
  }
  else {
    if (isset($vid) && $vid === GOFAST_VID_TAGS) {
      $return_value = '<ul class="select2-tags"><li>' . implode('</li><li>', $terms) . '</li></ul>';
    } else {
      if (is_array($value)) {
        $return_value = implode(', ', $value);
      }
      else {
        if ($field_name === GOFAST_CMIS_LOCATIONS_FIELD) {
          cache_clear_all("field:node:$node->nid", 'cache_field');
          lock_release("update_node_field_" . $nid);
          return json_encode($value);
        } else {
          $return_value = $value;
        }
      }
    }
  }
  cache_clear_all("field:node:$node->nid", 'cache_field');
  lock_release("update_node_field_" . $nid);

  return json_encode(array("status" => "OK", "newValue" => $return_value));
}

/**
 * @deprecated
 * @global type $user
 * @return type
 */
function gofast_update_alfresco_item_properties() {
  global $user;

  // Retrieve submitted POST values and auto-assign variables.
  extract($_POST, EXTR_PREFIX_SAME, '_');

  $nid = $pk;
  $field_name = $name;

  // Load the account being edited.
  $node = node_load($nid) or gofast_update_field_error($field_name, 'load_entity');

  $user_access = gofast_xeditable_content_editable($node);
  $node->uid == $user->uid || $user->uid == GOFAST_USER_ADMINISTRATOR_ID || $user->uid == 1 || $user_access or gofast_update_field_error($field_name, 'permissions');

  // Load entity wrapper.
  $wrapper = entity_metadata_wrapper('node', $node);
  $item_id = $wrapper->{GOFAST_CMIS_REFERENCE_FIELD}->value();

  $properties = array($field_name => $value);

  if ($field_name === 'cm:author') {
    $updated = gofast_cmis_webservice_item_update_properties($item_id, $properties);
  }
  else {
    $updated = gofast_cmis_item_update_properties($item_id, $properties, FALSE);
  }

  if ($updated) {
    return $value;
  }
  else {
    gofast_update_field_error($field_name, 'update');
  }
}

/**
 * Editable field function callback : user bundle only
 */
function gofast_update_field() {
  global $user;

  // Retrieve submitted POST values and auto-assign variables.
  extract($_POST, EXTR_PREFIX_SAME, '_');

  $uid = $pk;
  $field_name = $name;

  // Validator for field changes. If values is different from node saved value, continue, else return
  if(!isset($value)) {
    $value = '';
  }

  if (is_array($value)) {
    array_walk($value, function(&$val, $key) {
      $val = filter_xss($val);
    });
  } else {
    $value = filter_xss($value);
  }

  // Load the account being edited.
  $account = user_load($uid);

  if(!$account) {
    return gofast_update_field_error($field_name, 'load_entity');
  }

  // Check for the current user being able to edit $account's profile.
  $user_allowed = $account->uid === $user->uid || gofast_user_is_adm($user) || $user->uid === 1;
  if(!$user_allowed) {
    return gofast_update_field_error($field_name, 'permissions');
  }

  // Load entity wrapper.
  $wrapper = entity_metadata_wrapper('user', $account);

  // Values received is an array, multiple values, otherwise, single
  if (is_array($value)) {
    $values_filter_name = array_map(function($element) {
      return $element->name;
    }, $wrapper->{$field_name}->value());
    // If at least one value is different
    if (count(array_diff($values_filter_name, $value)) === 0 && count(array_diff($value, $values_filter_name)) === 0) {
      return json_encode($value);
    }

  }
  else { // A string
    if ($value === $wrapper->{$field_name}->value()) {
      return $value;
    }
  }

  // Load profile form so we can rely on '#validate' and '#element_validate'
  // handlers. Here we eschew drupal_get_form() to prevent some "alter" errors,
  // instead we manually build the info and call drupal_build_form().
  $form_id = 'user_profile_form';
  $form_state = array('build_info' => array('args' => array($account)));
  // Ensure include files are loaded so the form can be processed.
  form_load_include($form_state, 'inc', 'user', 'user.pages');

  // Build $form.
  $form = drupal_build_form($form_id, $form_state);

  if ($field_name !== 'mail') {
    $field_info = $form_state['field'][$field_name][LANGUAGE_NONE]['field'];
  } else {
    $field_info = array();
  }

  // Custom process for date fields
  if (!empty($field_info)) {
    $date_field = in_array($field_info['type'], array('date', 'time', 'datetime'));
    if ($date_field) {
      $_fdate = new DateTime();
      if ($value === "") {
        $value = null;
      }
      else {
        $format = $user->language === 'fr' ? 'd/m/Y' : 'm/d/Y';
        if(isValidTimeStamp($value)){
          $value = substr($value,0,-3);
          $value = date($format,$value);
        }
        $_fdate = DateTime::createFromFormat($format, $value);
        $timestamp_date = $_fdate->getTimestamp();
        $property_date = $_fdate->date;
        $value = $timestamp_date;
      }
      $form_state['values'][$field_name][LANGUAGE_NONE][0]['value'] = $date_str;
    } else {
      if (is_array($form_state['values'][$field_name])) {
        if (is_array($form_state['values'][$field_name][LANGUAGE_NONE])) {
          $form_state['values'][$field_name][LANGUAGE_NONE]['value'] = $value;
        }
        else {
          $form_state['values'][$field_name][LANGUAGE_NONE] = $value;
        }
      }
      else {
        $form_state['values'][$field_name] = $value;
      }
    }

  }
  // Validate form and check for error.
  drupal_validate_form($form_id, $form, $form_state);
  $errors = form_get_errors();

  if(!empty($errors)) {
    return gofast_update_field_error($field_name, NULL, $errors);
  } else {
      if ($field_name === 'mail') {
        $account->mail = $value;
        //user_save($account);
    }
  }

  // At this point $value is validated so we can save it safely.
  try {
    // If vis param is present, we process taxonomy terms.
    if (isset($vid)) {
      $normalized_values = gofast_xeditable_terms_get_from_array($vid, $value);
    }
    else {
      $normalized_values = $value;
    }
    $wrapper->{$field_name}->set($normalized_values);
    $wrapper->save();/** @todo : (missing) hooks implementations */

  }
  catch (EntityMetadataWrapperException $e) {

    $error = array($e->getMessage());
    return gofast_update_field_error($field_name, NULL, $error);
  }

  $return_value = "";
  if (isset($date_field)) {
    if (isset($date_str)) {
      $return_value = $date_str;
    }
  }
  else {
    if (is_array($value)) {
      if ($field_name === GOFAST_CMIS_LOCATIONS_FIELD) {
        $return_value = json_encode($value);
      } else {
        $return_value = implode(', ', $value);
      }
    }
    else {
      $return_value = $value;
    }
  }

  return json_encode(array("status" => "OK", "value" => $return_value));
}

function gofast_update_user_groups() {
  //global $user;

  // Retrieve submitted POST values and auto-assign variables.
  extract($_POST, EXTR_PREFIX_SAME, '_');

  $gid = $pk;
  $user = user_load($gid);
  $groups = $value;

  $user_groups = gofast_og_get_spaces_by_user($user, TRUE);
  $requested_groups_ids = gofast_og_get_user_pending_spaces($user);

  $user_mixed_groups = $requested_groups_ids !== null ? array_merge($user_groups, $requested_groups_ids) : $user_groups;

  // This diff represent new groups from current user groups
  $new_groups = array_unique(array_diff($groups, $user_mixed_groups));
  gofast_user_request_groups($new_groups, $user->uid);
  $new_groups_loaded = node_load_multiple($new_groups);

  return json_encode($new_groups_loaded);

  // This diff represent removed groups from current user groups
  /* $unselected_groups = array_unique(array_diff($user_mixed_groups, $group_ids));
    gofast_user_unregister_groups($unselected_groups, $user->uid); */
}

function gofast_update_field_error($field_name, $code = NULL, $errors = NULL) {
  if (is_array($errors)) {
    // Clean drupal messages stack to prevent late print on the next page load.
    drupal_get_messages('error');
    // If form validation failed on '$fieldname' field, print the error message
    // to the user. Otherwise we don't because it's not his concern.
    foreach ($errors as $field_key => $error) {
      $_field_name = reset(explode('][', $field_key));
      if ($field_name === $_field_name) {
        return json_encode(array('status' => 'error', 'msg' => $error));
      }
    }
    // At this point user is not concerned by any error.
    // The submitted field data can be saved by the caller.
    return;
  }
  elseif (is_string($errors)) {
    // An exception is being thrown.
    return json_encode(array('status' => 'error', 'msg' => $errors));
  }

  // Mapping $code with readable error messages.
  $error = gofast_update_field_error_default();

  $message = isset($error[$code]) ? $error[$code] : t('Unknown error.', array(), array('context' => 'gofast'));
  return json_encode(array('status' => 'error', 'msg' => $message));
}

function gofast_update_field_error_default() {
  return array(
    'no_value' => t('No value was received by the server.', array(), array('context' => 'gofast')),
    'load_entity' => t('Failed to load profile data.', array(), array('context' => 'gofast')),
    'permissions' => t('You are not granted permission to edit this profile.', array(), array('context' => 'gofast')),
    'lock' => t('The document is currently locked, no operation is allowed until the document is unlocked.', array(), array('context' => 'gofast')),
    'cardinality' => t('Cannot handle a multivalued field.', array(), array('context' => 'gofast')),
    'update' => t('Failed to update.', array(), array('context' => 'gofast')),
    'already_exists' => t('This value already exists', array(), array('context' => 'gofast')),
  );
}

function gofast_user_request_groups($group_ids, $uid) {
  foreach ($group_ids as $gid) {
    if ($gid !== null) {
      gofast_og_subscribe_user($gid, $uid, OG_STATE_PENDING);
      watchdog("Gofast User Group Request", "User " . $uid . " requested group id " . $gid);
    }
  }
  if (!empty($group_ids)) {
    $loaded_nodes = array_map(function($group) {
      return $group->title;
    }, node_load_multiple($group_ids));
    drupal_set_message(t("You successfully request for being part of following group(s) : ") . implode(', ', $loaded_nodes));
    drupal_set_message(t("Your groups memberships are in pending state while the manager(s) (or adm) hasn't validated your request."));
  }
}

function gofast_user_unregister_groups($group_ids, $uid) {
  foreach ($group_ids as $gid) {
    if ($gid !== null) {
      //TODO if wanted : gofast_og_unsubscribe_user($gid, $uid);
      watchdog("Gofast User Group Cancel", "User " . $uid . " cancelled from group id " . $gid);
    }
  }
}

function gofast_xeditable_content_editable($node) {
  global $user;

  $user_access = false;

  // Edit access
  if ($user->uid === GOFAST_USER_ADMINISTRATOR_ID || $user->uid === $node->uid) {
    $user_access = true;
  }
  else {
    $node_parents = _gofast_og_content_get_parents($node, TRUE);
    $parents_memberships = array();
    if ($node_parents) {
      foreach ($node_parents as $node_parent) {
        $parents_memberships = array_merge($parents_memberships, gofast_og_get_members_userlist_included($node_parent, 'active'));
      }
      $user_access = in_array($user->uid, $parents_memberships);
    }
  }
  return $user_access;
}

/**
 * This function returns whether a taxonomy term is allowed for a given node.
 * The terms are allowed when the current node belongs to a group allowed for
 * the taxonomy (see filtered categories administration panel)
 * @param entity $term the entity term to check
 * @return boolean TRUE if allowed, FALSE otherwise.
 */
function gofast_taxonomy_category_allowed($term, $node = null) {
    $allowed_term = TRUE;
    $filtered_categories = variable_get('gofast_map_category_spaces', array());
    if(array_key_exists($term->tid, $filtered_categories) && !empty($filtered_categories[$term->tid]) && $node != null) {
       if(!is_array($node)){
           $node = array($node->nid => $node);
       }
       $count_disallowed_node = 0;
       foreach($node as $nid=>$mynode){
           $count_disallowed_node = $count_disallowed_node + 1;
           foreach($filtered_categories[$term->tid] as $gid){
             if(gofast_is_node_inside_space($mynode,$gid)){
                $count_disallowed_node = $count_disallowed_node - 1;
            }
           }
       }
       if($count_disallowed_node == 0){
           $allowed_term = TRUE;
       }else{
           $allowed_term = FALSE;
       }
    }

    return $allowed_term;
}

/**
 * This function returns all the terms of a vocabulary for html select item.
 * @param int $vid the vid to get the term of
 * @return array a list of terms with 'id' and 'text' keys
 */
function gofast_xeditable_vocabulary_to_select_items($vid, $node = null) {
  $options = array();
  $options_standard = array();
  $allowed_term = TRUE;
  foreach (taxonomy_term_load_multiple(FALSE, array('vid' => $vid)) as $term) {
    if($vid === GOFAST_VID_CATEGORY) {
      $allowed_term = gofast_taxonomy_category_allowed($term, $node);
    }

    if($allowed_term) {
      $localized_term = i18n_taxonomy_localize_terms($term);

      if($vid === GOFAST_VID_CATEGORY && $localized_term->field_standard_gf[LANGUAGE_NONE][0]['value'] == 1){
        $options_standard[] = array("id" => $localized_term->name, "text" => $localized_term->name, 'database_name' => $term->name);
      }else{
        $options[] = array("id" => $localized_term->name, "text" => $localized_term->name, 'database_name' => $term->name);
      }
    }
  }
   //Sort terms alphabetically
  foreach($options_standard as $option_unsorted_value){
    $options_standard_sorted[$option_unsorted_value['text'] . rand()] = $option_unsorted_value;
  }
  ksort($options_standard_sorted);

  //Sort terms alphabetically
  foreach($options as $option_unsorted_value){
    $options_sorted[$option_unsorted_value['text'] . rand()] = $option_unsorted_value;
  }
  ksort($options_sorted);

  if($vid === GOFAST_VID_CATEGORY) {
    unset($options);
    $options[] = array('text' => t('Standard', array(), array('context' => 'gofast')) , 'children' => array_values($options_standard_sorted));
    $options[] = array('text' => htmlspecialchars_decode(t("@site_name's categories", array('@site_name' => variable_get('site_name') ), array('context' => 'gofast'))) , 'children' => array_values($options_sorted));

  }else{
    $options = array_values($options_sorted);
  }
  //If fields of user profile are emtpy, tags will be an array.
  if (empty($options)) {
      $options = array();
  }

  return $options;
}


/*
 * Sort criticity for xeditable display and attach icons
 */
function gofast_xeditable_sort_criticity($elements, $node = null)
{

  $nids = is_null($node) ? array() : _gofast_og_content_get_parents($node);

  $is_public = FALSE;
  $is_extranet = FALSE;

  foreach ($nids as $nid) {
    $space = node_load($nid);
    if ($space->type == "public") {
      $is_public = TRUE;
    } elseif ($space->type == "extranet") {
      $is_extranet = TRUE;
    }
  }


  $output = array();
  //Sort known elements
  foreach ($elements as $k => $element) {
    switch ($element['database_name']) {
      case 'Confidential Data':
        $output[0] = $element;
        if ($is_public) {
          $output[0]['disabled'] = true;
        }
        unset($elements[$k]);
        break;
      case 'Internal Distribution':
        $output[1] = $element;
        if ($is_extranet) {
          $output[1]['disabled'] = true;
        }
        unset($elements[$k]);
        break;
      case 'Personal Data':
        $output[2] = $element;
        unset($elements[$k]);
        break;
      case 'Critical':
        $output[3] = $element;
        unset($elements[$k]);
        break;
      case 'High':
        $output[4] = $element;
        unset($elements[$k]);
        break;
      case 'Normal':
        $output[5] = $element;
        unset($elements[$k]);
        break;
      case 'Low':
        $output[6] = $element;
        unset($elements[$k]);
        break;
    }
  }

  //Add unknown elements
  foreach ($elements as $k => $element) {
    $output[] = $element;
  }

    ksort($output);
    return $output;
}

/*
 * Create param means that we create the term if it not exists
 */
function gofast_xeditable_terms_get_from_array($vid, $list_terms, $create = TRUE) {
  $existing_terms = taxonomy_get_tree($vid, 0, NULL, TRUE);

  $existing_terms_name = array_map(function($element) {
    return trim($element->name);
  }, $existing_terms);

  $new_terms = array();
  foreach ($list_terms as $term) {
     if($vid === GOFAST_VID_TAGS) {
       $und_language_term = trim($term);
     }else{
       $und_language_term = trim(gofast_xeditable_translate_back($term, array(), 'en', 'taxonomy', $vid));
     }
    if (!in_array($und_language_term, $existing_terms_name, TRUE)) {
      if($term !== '' && $create) {
        $new_terms[] = gofast_taxonomy_vocabulary_add_term($vid, $term);
      }
    }
    else {
      $taxonomy_term = array_filter($existing_terms, function($element) use ($und_language_term) {
        return $und_language_term === $element->name;
      });
      $new_terms[] = reset($taxonomy_term);
    }
  }
  return $new_terms;
}

function gofast_xeditable_translate_back($string = "", $context = NULL, $langcode = '', $textgroup ='default',$vid = null) {
  $t = $string;
  if($vid != null){
      $query = db_query("select machine_name from {taxonomy_vocabulary} where vid = :vid", array(":vid" => $vid));
      $result = $query->fetch();
      $vocab_name = $result->machine_name;
  }
  if ($string !== "") {
    if ($langcode == "en") {

      $sql = 'SELECT s.source
        FROM {locales_source} s
        JOIN {locales_target} t
          ON s.lid = t.lid
        WHERE t.translation = :string
        AND s.textgroup = :textgroup';

      $results = db_query($sql, array(':string' => $string, ':textgroup' => $textgroup));

      foreach ($results as $row) {
        $myterm =  taxonomy_get_term_by_name($row->source, $vocab_name );
        if(is_array($myterm)){
             $t = array_shift(array_values(  $myterm))->name;
             return $t ;
        }else{
            $t = $row->source;
       }
      }

    }
    else {
      $t = t($string, $context, array('langcode' => $langcode));
    }
  }
  return $t;
}


/**
 * This fonction returns a set of (max 20) results with a given string given in 'query' parameter.
 * This function is called by x-editable, that's why the search value is not set as url param but request param.
 * The return string is formatted for x-editable.
 * @return type the results of the searched string, 20 first results if string is empty.
 */
function gofast_xeditable_node_autocomplete() {
  $str = isset($_GET['query']) ? trim($_GET['query']) : '';
  $exact_match = isset($_GET['exact_match']) ? trim($_GET['exact_match']) : '';
  $nids = isset($_GET['nids']) ? $_GET['nids'] : '';

  $query = db_select('node', 'n')
          ->fields('n')
          ->condition('status', '1')
          ->condition('type', gofast_og_content_bundles(), 'IN')
          ->range(0, 20);

  if (!empty($nids)) {
    $query->condition('nid', explode(',', $nids), 'IN');
  }
  else {
    if (!empty($str)) {
      if ($exact_match) {
        $query->condition('title', $str);
      }
      else {
        $query->condition('title', '%' . db_like($str) . '%', 'LIKE');
      }
    }
  }

  $result = $query->execute();

  $results = array();

  foreach ($result as $row) {
    $node = node_load($row->nid);
    if(!node_access("view", $node)){
        continue;
    }
    $wrapper = entity_metadata_wrapper('node', $node);
    $update_date = format_date($wrapper->changed->value());
    $format = $wrapper->{'field_format'}->value();
    $format_icon = $wrapper->{'field_format'}->{'field_icone'}->value();
    $icon = $format_icon !== null ? $format_icon : 'fa-file';
    $result = array('id' => $row->nid, 'text' => $row->title, 'format' => $format->name, 'formatImageUrl' => $icon, 'updateDate' => $row->nid);
    $results[] = $result;
  }

  return drupal_json_output($results);
}

/**
 * This fonction returns a set of (max 20) results with a given string given in 'query' parameter.
 * This function is called by x-editable, that's why the search value is not set as url param but request param.
 * The return string is formatted for x-editable.
 * @return type the results of the searched string, 20 first results if string is empty.
 */
function gofast_xeditable_tag_autocomplete($print = true) {
  $str = isset($_GET['query']) ? trim($_GET['query']) : '';
  $exact_match = isset($_GET['exact_match']) ? trim($_GET['exact_match']) : '';
  $tags = isset($_GET['tags']) ? $_GET['tags'] : '';
  $vid = isset($_GET['vid']) ? $_GET['vid'] : GOFAST_VID_TAGS;

  $query = db_select('taxonomy_term_data', 't')
          ->fields('t')
          ->condition('vid', $vid)
          ->range(0, 20);

  if (!empty($tags)) {
    $query->condition('name', explode(',', $tags), 'IN');
  }
  else {
    if (!empty($str)) {
      if ($exact_match) {
        $query->condition('name', $str);
      }
      else {
        $query->condition('name', '%' . $str . '%', 'LIKE');
      }
    }
  }

  $result = $query->execute()->fetchAll();

  $results = array();

  foreach ($result as $row) {
    $result = array('id' => $row->tid, 'text' => $row->name);
    $results[] = $result;
  }

  if($print){
    return drupal_json_output($results);
  }else{
    return $results;
  }
}

/*
 * Returns the subscribe button for the given term in the given node
 * If no node reference is provided, link will redirect to /node
 * @param $term
 *  The term formatted ad TERM[...]term_id
 * @param $nid
 *  The node id to redirect
 */
function gofast_xeditable_get_subscribe_term_link($term, $nid= '/node'){
  $term =  str_replace("**", "/", $term);
  $term = gofast_xss_clean($term);
  $term_split = explode('[GOFAST_TAG_SEPARATOR]', $term);
  $term_name = '<p style="margin-top:5px; float: left;">'.$term_split[0].'</p>';
  $term_id = $term_split[1];

  $link = flag_create_link('subscribe_term', $term_id);
  //Remove text
  $link = str_replace(t("Subscribe"), "", $link);
  $link = str_replace(t("Unsubscribe"), "", $link);
  $link = str_replace($term, str_replace("/", "**", $term), $link);
  //Remove padding
  $link = str_replace('<a', '<a style="padding:0px; padding-left: 3px;"', $link);
  //Show red icon for unflag button
  if(strpos($link, 'unflag') !== FALSE){
    $link = str_replace('<i class="fa fa-rss">', '<i style="color:red;" class="fa fa-rss">', $link);
  }

  print $link.$term_name;
  exit;
}
