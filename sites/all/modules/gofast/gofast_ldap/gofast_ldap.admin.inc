<?php
    
/**
 * @file
 * 
 * Gofast configuration callbacks.
 * Admin interface for Gofast LDAP settings
 */
     
/**
 * Helper, returns minimal LDAP form fields set to expose to adms. Values for 
 * the other fields will be derived from defaults according to the server type.
 */
function gofast_ldap_settings_form_fields() {
  // Expose the base settings, add custom.
  $mapped = gofast_ldap_migrate_mapping('new_to_old');
  return array_merge_recursive($mapped, array(
    'server' => array('sid' => NULL, 'followrefs' => NULL),
    'bind_method' => array('binding_service_acct' => NULL),
    // ... add any other fields brought by LDAP modules 
  ));
}
    
/**
 * Creates a GoFast LDAP server configuration used for user data provisioning.
 */
function gofast_ldap_server_create($sid = GOFAST_LDAP_INT_SERVER, $silent = FALSE) {
  ldap_servers_module_load_include('php', 'ldap_servers', 'LdapServerAdmin.class');
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
      
  if (!ldap_servers_ldap_extension_loaded()) {
    drupal_set_message(t('PHP LDAP Extension is not loaded.'), 'warning');
  }
      
  $server = new LdapServerAdmin($sid);
      
  if ($server->sid !== $sid) {
    $server->drupalFormSubmit('add', gofast_ldap_server_defaults($sid));
    if ($server->hasError() == FALSE) {
      if (!$silent) {
        drupal_set_message(t('LDAP Server %name added.', array('%name' => $server->name)), 'status');
      }
    }
    else {
      drupal_set_message($server->errorName() . ':' . $server->errorMsg(), 'error');
      $server->clearError();
    }
    ldap_servers_cache_clear();
  }
  else {
    /** @todo load server and set maessage according to */
    //drupal_set_message(t('Gofast LDAP : The server configuration already exists, or another uses the same machine name.'), 'warning');
  }
}
    
/**
 * LDAP server default instances management. Form builder
 */
function gofast_ldap_server_settings_form() {
  ldap_servers_module_load_include('inc', 'ldap_servers', 'ldap_servers.functions');
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
      
  if (!ldap_servers_ldap_extension_loaded()) {
    drupal_set_message(t('PHP LDAP Extension is not loaded.'), 'warning');
  }
      
  foreach (gofast_ldap_server_default_names() as $sid => $label) {
    $form[$sid] = array(
      '#type' => 'fieldset',
      '#title' => $label,
      'info' => array(
        '#type' => 'item',
        '#description' => 'Automatically create Gofast ldap server configuration.' . theme('item_list', array('items' => array(
            'If no server configuration is found, automatically create and load server configuration.',
            "If a configuration named '{$sid}' already exists, delete safely via the LDAP servers administration page, then recreate.")))),
    );
        
    $info = $description = '';
    $server = gofast_ldap_server_load($sid);
        
    if ($server_exists = $server->sid === $sid) {
      $info = t('Server %conf is already configured.', array('%conf' => $sid), array('context' => 'gofast:gofast_ldap'));
      $description = array_to_html(get_object_vars($server), TRUE);
    }
    else {
      $info = t('Server %conf is not configured or does not exist. You can create it based on predefined defaults settings.', 
                array('%conf' => $sid), array('context' => 'gofast:gofast_ldap'));
    }
        
    $form[$sid]['status'] = array(
      '#type' => 'item',
      '#markup' => $info,
      '#description' => $description
    );
        
    $form[$sid][$sid] = array(
      '#type' => 'submit',
      '#name' => 'op',
      '#value' => 'create',
      '#access' => !$server_exists
    );
  }
      
  return $form;
}
    
/**
 * Submit callback for LDAP admin (default instances management) form
 */
function gofast_ldap_server_settings_form_submit($form, &$form_state) {
  if ($form_state['submitted'] && $form_state['triggering_element']['#value'] === 'create') {
    $sid = $form_state['triggering_element']['#parents'][0];
    gofast_ldap_server_create($sid);
  }
}
    
function gofast_ldap_admin_entries_display() {
    $form = drupal_get_form('gofast_ldap_admin_entries');
    $render = drupal_render($form);
    return gofast_create_page_content($render);
}
    
function gofast_ldap_fetch_entries() {
    
    $sid = GOFAST_LDAP_EXT_SERVER;
    $server = gofast_ldap_server_load($sid);
        
    $pagination = $_GET['pagination'];
    $sort = $_GET['sort'];
    $filters = $_GET['query'];
        
    $entries = [];
                
    $defaults = array(
        'attributes' => array_keys(gofast_ldap_server_attributes($sid, FALSE, FALSE)),
        'ou' => NULL,
    );
                
    //Filters
    if (isset($filters) && !empty($filters) && $filters[key($filters)] != "") {
        $key = key($filters);
        $defaults['filters'] = array(
            array(
                'attr' => $key,
                'value' => '*' . $filters[$key] . '*',
            ),
        );
    } else {
        $defaults['filters'] = array(
            array(
                'attr' => 'sn',
                'value' => '*',
            ),
        );
    }
             
    //Pagination - Doesn't work and is made client-side
    if ($pagination) {
        $defaults['ipp'] = $pagination;
    } else {
        $defaults['ipp'] = 20;
    }
 
    //Query opt
    $query_opt = filter_input(INPUT_GET, '_ldap_opt', FILTER_DEFAULT, array(
        'flags' => FILTER_REQUIRE_ARRAY,
        'options' => array(
            'default' => array()
        )
    ));
        
    //Options merging
    $options = $query_opt + $defaults;
        
    //Fetch entries and format
    $entries = gofast_ldap_admin_query($server, $options);       
    $formatted_entries = gofast_ldap_admin_entries_format($entries, $server, $sid);
        
    print $formatted_entries;
}
    
function gofast_ldap_admin_entries_format($entries, $server, $sid) {
    $formatted_entries = array();
    $attributes = array_keys(gofast_ldap_server_attributes($sid, FALSE, FALSE));
    
    for($key=0;$key<$entries['count'];$key++) {
        
        foreach($attributes as $attr) {
            $formatted_entries[$key][$attr] = $entries[$key][$attr][0];
        }
                     
        if(!isset($entries[$key][$server->user_attr][0])) {
            continue;
        }
        $user_id = ($uid_attr_exists = isset($entries[$key][$server->user_attr][0])) ? $entries[$key][$server->user_attr][0] : $key;
        $imported_string = "";
        $user_exists = false;
        if(!$uid_attr_exists || $user_exists = user_load_by_name($user_id)) {
            $imported_string = '<i class="d-flex justify-content-center mr-6 fas fa-check gofastImported"></i>';
        }
        $formatted_entries[$key]['imported'] = $imported_string;
            
    }
    return json_encode($formatted_entries);
}
    
function gofast_ldap_admin_entries_import_selected() {

  $sid = GOFAST_LDAP_EXT_SERVER;
  $server = gofast_ldap_server_load($sid);
  
  $mapping = array_filter(gofast_ldap_prov_mapping($sid));
  
  $roles = gofast_user_roles();
  $role_name = GOFAST_ROLE_CONTRIBUTOR;
  $data = array(
    "ldap_user_manager" => 4,
    "ldap_user_ou" => null,
  );

  $all_users = $_POST["users"];
  $selected = $_POST["selected"];
  if (!$selected) {
    $msg = t('There is no selected user. Please select at least 1 user.', array() , array('context' => 'gofast'));
    drupal_get_messages($type = 'status', TRUE);
    drupal_set_message($msg, 'error');
    exit;
  }
  $ret = array();
  foreach ($all_users as $key => $user) {
    // skip pagination keys which may come from the front-end directory
    if (!is_numeric($key)) {
      continue;
    }
    $username = $user[$server->user_attr];
    if (in_array($username, $selected)) {

      foreach ($mapping as $entry => $remote) {
        if (empty($remote)) {
          continue;
        }
        switch ($entry) {
          case "ldap_user_manager":
          case "ldap_user_ou":
            break;
          case "ldap_user_displayname":
            $data[$entry] = (empty($user[$remote])) ? $user["cn"] : $user[$remote];
            break;
          default:
            $data[$entry] = $user[$remote];
            break;
        }
      }
      $ret[$username] = gofast_user_create($username, $role_name, $data);
    }

    // Alter drupal messages queue to make it more readable.
    $created = array_keys(array_filter($ret));
    $msg = t('Following accounts have been created successfully : !list', array('!list' => theme('item_list', array('items' => $created))), array('context' => 'gofast:gofast_ldap'));
    drupal_get_messages($type = 'status', TRUE);
    drupal_set_message($msg, 'status');
  }
}
      
      
/**
 * Page callback for LDAP administration tools.
 */
function gofast_ldap_admin_entries($form, &$form_state) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
  $sid = GOFAST_LDAP_EXT_SERVER;
  $server = gofast_ldap_server_load($sid);
      
  $opt_key = __FUNCTION__ . '_search_options';
  $options = isset($form_state[$opt_key]) ? $form_state[$opt_key] : gofast_ldap_admin_options_default($sid);
  gofast_ldap_admin_entries_import_options($form_state, $options);
  $attributes = gofast_ldap_server_attributes($sid, TRUE, TRUE);
      
  $form['sid'] = array(
    '#type' => 'hidden',
    '#value' => $sid
  );
      
  $form['options'] = array(
    '#title' => t('Search Options', array(), array('context' => 'gofast:gofast_ldap')),
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#prefix' => '<div class="card"><div class="card-header">',
    '#suffix' => '</div>',
  );
      
  foreach ($options['filters'] as $key => $filter) {
    $form['options']['filter_' . $key] = array(
      '#title' => t('Filter', array(), array('context' => 'gofast')) . ' ' . ($key + 1),
      '#type' => 'select',
      '#options' => $attributes,
      '#default_value' => $filter['attr'],
      '#prefix' => $key ? '<td>' : '<table><tr><td>'
    );
        
    $form['options']['filter_value_' . $key] = array(
      '#type' => 'textfield',
      '#default_value' => $filter['value'],
      '#suffix' => '</td>',
      '#size' => 11
    );
  }
      
  $form['options']['sort_by'] = array(
    '#title' => t('Sort by', array(), array('context' => 'gofast')),
    '#type' => 'select',
    '#options' => $attributes,
    '#default_value' => $options['sort_by'],
    '#prefix' => '<td>'
  );
  $form['options']['sort_dir'] = array(
    '#type' => 'select',
    '#options' => array('asc' => t('ascending', array(), array('context' => 'gofast')), 'desc' => t('descending', array(), array('context' => 'gofast'))),
    '#default_value' => $options['sort_dir'],
    '#suffix' => '</td>'
  );
      
  $col_num = count($options['filters']) + 2; // filters, sorting & pagination/submit.
  $ltd_width = (100 / $col_num) . '%';
  $form['options']['ipp'] = array(
    '#title' => t('items/page', array(), array('context' => 'gofast')),
    '#type' => 'select',
    '#options' => (array(10 => 10, 20 => 20, 50 => 50, 100 => 100, 250 => 250)),
    '#default_value' => $options['ipp'],
    '#prefix' => "<td style='width:{$ltd_width};text-align:right;'>"
  );
      
  $form['options']['submit-search'] = array(
    '#name' => 'op',
    '#type' => 'submit',
    '#value' => t('Search', array(), array('context' => 'gofast')),
    '#prefix' => '<div class="form-item form-group" style="padding:2px;">',
    '#suffix' => '</div></td></tr></table><script>jQuery("[id^=gofast-ldap-admin-entries]").attr("action", "/admin/config/gofast/ldap/manage")</script><style>.breadcrumb-gofast{display:none;}</style>',
    '#submit' => array('gofast_ldap_admin_entries_search')
  );
      
  // Prepare several options to be selected in a second step when importing user
  // entries : organisation unit, manager, and roles. 
  $root_spaces = gofast_og_get_root_spaces(FALSE, TRUE);
  $org = gofast_og_get_spaces_by_bundle(array('organisation'));
  $organisations = array_diff_key($org, $root_spaces)/* +  array('_none' => t('- None -'))*/;
      
  foreach ($organisations as $gid => &$org) {
    $org = $org->title;
  }
  $form['import_opt']['ou'] = array(
    '#title' => t('Organisation', array(), array('context' => 'gofast')),
    '#type' => 'select',
    '#options' => NULL,
    '#prefix' => '<div class="gofast-ldap-admin-import-options">'
  );
      
  $managed_gids = gofast_og_get_managed_spaces();
  gofast_og_form_field_filter_by_id($form, array('import_opt', 'ou'), $managed_gids, FALSE, FALSE);  
      
  $managers = gofast_user_load_multiple_by_roles(array('administrator', 'manager'));
  foreach ($managers as $uid => &$account) {
    $account = gofast_user_display_name($account);
  }
  $form['import_opt']['manager'] = array(
    '#title' => t('Manager', array(), array('context' => 'gofast')),
    '#type' => 'select',
    '#options' => $managers,
  );
      
  $roles = gofast_user_roles();
  $form['import_opt']['roles'] = array(
    '#title' => t('Profiles', array(), array('context' => 'gofast')),
    '#type' => 'checkboxes',
    '#options' => $roles,
    '#default_value' => array_keys($roles, GOFAST_ROLE_CONTRIBUTOR),
  );
      
  $btn = array(
    gofast_button(t('Save'), NULL, 'btn-success', NULL, array('op' => 'save')),
    gofast_button(t('Cancel'), NULL, 'btn-danger', NULL, array('op' => 'cancel'))
  );
  $form['import_opt']['submit-opt'] = array(
    '#markup' => implode('&nbsp;', $btn),
    '#suffix' => '</div>'
  );
      
  // Execute LDAP search query.
  $results = gofast_ldap_admin_query($server, $options);
      
  // Gather some informations to display.
  $count = isset($results['count']) ? $results['count'] : 0;
  $count_msg = format_plural($count, '1 ' . t('result', array(), array('context' => 'gofast')), '@count ' . t('results', array(), array('context' => 'gofast')));
      
  if ($count >= $server->searchPageSize) {
    $msg = t('Warning : Your LDAP directory is set to return at most :size entries, some results could not be displayed.', 
            array(':size' => $server->searchPageSize), array('context' => 'gofast:gofast_ldap'));
    drupal_set_message($msg, 'warning');
  }
      
  if (isset($results['error'])) {
    drupal_set_message($results['error'], 'error');
  }
      
  $form['results'] = array(
    '#title' => t('Search Results', array(), array('context' => 'gofast')) . '<span style="float:right;"> ' . $count_msg . '</span>',
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#prefix' => '<div class="card-body">',
  );
      
  $selected = 0; 
  $form['results']['submit-import'] = array(
    '#name' => 'op',
    '#type' => 'submit',
    '#value' => t('Import Selection', array(), array('context' => 'gofast')),
    '#submit' => array('gofast_ldap_admin_entries_import'),
    '#validate' => array('gofast_ldap_admin_entries_validate'),
    '#attributes' => array('style' => 'float:right'),
    '#prefix' => '<span class="ldap-selected">' . format_plural($selected, '@count entry selected.', '@count entries selected.') . '</span>',
    '#attached' => array(
      'js' => array(array(
        'data' => drupal_get_path('module', 'gofast_ldap') . '/gofast_ldap.js',
        'type' => 'file',
        'scope' => 'footer',
        'weight' => 5
      ))
    ),
    '#states' => array(
      'enabled' => array(
        '#edit-results input[type="checkbox"]' => array('checked' => TRUE)
      )
    )
  );
      
  // Build the header.
  $colNames = array_keys(gofast_ldap_server_attributes($sid, FALSE, TRUE));
  $header = array_diff_key(array_combine($colNames, $colNames) + array('_imported' => t('Imported', array(), array('context' => 'gofast'))), array('_none' => NULL));
      
  // Remove _none option from attribute array so we can iterate over attributes.
  unset ($attributes['_none']);
      
  // Process results before rendering.
  $processed_results = $rows = $disabled = array();
  for ($i = 0; $i < $count; $i++) {
    if(!isset($results[$i][$server->user_attr][0])){
        continue;
    }
    // Set a row id using user identifier if set, fallback with the current 
    // index otherwise (some entries might be non-user entries).
    $user_id = ($uid_attr_exists = isset($results[$i][$server->user_attr][0])) ? $results[$i][$server->user_attr][0] : $i;
    // Populate the row.
    $rows[$user_id] = array();
    foreach ($attributes as $attr => $label) {
      $value = '';
      if (isset($results[$i][$attr])) {
        // Handle both single/multi valued attributes.
        unset($results[$i][$attr]['count']);
        $value = implode('/', $results[$i][$attr]);
      }
      $rows[$user_id][$attr] = $value;
    }
    // Add the "Imported" flag column and init checkboxes states array.
    $rows[$user_id]['_imported'] = '-';
    $user_exists = FALSE;
    if (!$uid_attr_exists || $user_exists = user_load_by_name($user_id)) {
      // If no uid attribute is found within this entry, or if a corresponding 
      // account already exists in database, disable the checkbox to prevent
      // duplicates, and flag the user as "imported". However it is possible 
      // we have conflicts between drupal and ldap identifiers, hence having
      // false duplicates.
      $user_exists && $rows[$user_id]['_imported'] = '<span class="glyphicon glyphicon-ok"></span>';
      $disabled[$user_id]['#disabled'] = TRUE;
    }
    else {
      $processed_results[$user_id] = $results[$i];
    }
  }
      
  // Pagination settings.
  $limit = $options['ipp'];
  $page = pager_default_initialize(count($rows), $limit);
  $offset = $limit * $page;
  // Split results into page sized chunks.
  $p_rows = array_slice($rows, $offset, $limit, TRUE);
      
  // Transport form state options through the pager's parameters.
  $params = array_diff_key($options, array('attributes' => 0));
      
  $form['results']['selection'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $p_rows,
    '#multiple' => TRUE,
    '#validated' => TRUE,
  );
      
  foreach($disabled as $d_key => $d_value){
      if(isset($form['results']['selection']['#options'][$d_key])){
          $form['results']['selection'][$d_key]['#disabled'] = TRUE;
      }
  }
      
  $form['results']['pager'] = array(
    '#theme' => 'pager',
    '#parameters' => array('_ldap_opt' => $params),
    '#prefix' => '<div class="align-items-center card-footer d-flex justify-content-center">',
    '#suffix' => '</div>',
  );
      
  // Make processed results available in submit callback.
  $form_state[__FUNCTION__ . '_search_results'] = $processed_results;
      
  return $form;
}
    
/**
 * Permforms an LDAP search query given the set of parameters.
 * 
 * @param \LdapServer $LdapServer 
 *  An LDAP server instance.
 * 
 * @param array $options
 *  An array of filters, attrbutes and additional options used to build the 
 * search query 
 * 
 * @return array|boolean
 *  An array of matching entries->attributes (will have 0 elements if search 
 *  returns no results), or FALSE on error.
 */
function gofast_ldap_admin_query(LdapServer $LdapServer, $options) {
  $filters = array_filter($options['filters'], function ($item) {
    return $item['attr'] !== '_none'; 
  });
      
  if (empty($filters)) {
    $filters[] = array(
      'attr' => 'objectClass',
      'value' => '*'
    );
  }
      
  $_filters = array();
  $__filter = "";
  $filter = "";
      
  foreach ($filters as $key => $_filter) {
    // Escape meta characters except wildcard char, this allows user to take 
    // advantage of the corresponding operator. User is still able to escape 
    // it by prepending a backslash.
    list ($attribute, $value) = gofast_ldap_escape_filter($_filter);
    if (empty($value) && $value !== "0") {
      $value = '*';
    }
        
    $__filter = $attribute . '=' . $value;
    array_push($_filters, $__filter); // array("filter1", "filter2", "filter3" ...)
  }
      
  foreach ($_filters as $key => $__filter) {
    if (empty($value) && $value !== "0") {
      $value = '*';
    }
    if (strpos($__filter, "|") !== false) { // if "|" in $__filter
        $filter_explode = array();
        $filters_explode = explode("|", $__filter);
        foreach ($filters_explode as $explode_filter) {
            array_push($filter_explode, explode("=", $explode_filter));
        }
        $filter .= '(|';
        for ($i = 0; $i != count($filters_explode); $i++) {
            if (!empty($filters_explode[$i]) && strpos($filters_explode[$i], "=") && !empty($filter_explode[$i][1])) {
                if (strpos($filters_explode[$i], "!") !== false) { // if "!" in $__filter
                    $filters_explode[$i] = str_replace("!", "", $filters_explode[$i]);
                    $filters_explode[$i] = '!(' . $filters_explode[$i] . ')';
            }
                $filter .= '(' . $filters_explode[$i] . ')';
            }
        }
        $filter .= ')';
        $prev_filter = $filters[$key-1];
        $next_filter =$filters[$key+1];
        if ((!empty($prev_filter)) && ($next_filter === null)) { // if isset(prev_filter) and !isset(next_filter)
            $filter = '(&' . $filter . ')';
        }
    } else {
        $current_filter = $__filter;
        if (strpos($current_filter, "!") !== false) { // if "!" in $__filter
            $current_filter = str_replace("!", "", $__filter);
            $current_filter = '!(' . $current_filter . ')';
        }
        $next_filter =$filters[$key+1];
        if ($next_filter === null) {
            $filter = '(&' . $filter . '(' . $current_filter . '))';
        } else {
            $filter = $filter . '(' . $current_filter . ')';
        }
    }
}
    
  $attributes = $options['attributes'];
      
  return $LdapServer->searchAllBaseDns($filter, $attributes);
}
    
/**
 * Form submit handler for LDAP managed entries.
 * 
 * Update LDAP query options before performs search.
 */
function gofast_ldap_admin_entries_search($form, &$form_state) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
  if ($form_state['values']['op'] !== t('Search', array(), array('context' => 'gofast'))) {
    return;
  }
      
  $values = $form_state['values'];
  $filter_attr = $filter_val = array();
  $options = gofast_ldap_admin_options_default($values['sid']);
      
  foreach ($values as $name => $value) {
    if (strpos($name, 'filter_value_') === 0) {
      $filter_val[] = $value;
      continue;
    }
    if (strpos($name, 'filter_') === 0) {
      $filter_attr[] = $value;
      continue;
    }
    $options[$name] = $value;
  }
      
  foreach ($filter_attr as $key => $filter) {
    $options['filters'][$key] = array(
      'attr' => $filter,
      'value' => $filter_val[$key]
    );
  }
      
  $form_state[__FUNCTION__ . '_options'] = $options;
  $form_state['rebuild'] = TRUE;
}
    
function gofast_ldap_admin_entries_import_options($form_state, &$options) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
      
  $values = $_POST;
  $filter_attr = $filter_val = array();
      
  foreach ($values as $name => $value) {
    if (strpos($name, 'filter_value_') === 0) {
      $filter_val[] = $value;
      continue;
    }
    if (strpos($name, 'filter_') === 0) {
      $filter_attr[] = $value;
      continue;
    }
  }
      
  foreach ($filter_attr as $key => $filter) {
    $options['filters'][$key] = array(
      'attr' => $filter,
      'value' => $filter_val[$key]
    );
  }  
}
    
/**
 * Form validate handler for LDAP managed entries.
 */
function gofast_ldap_admin_entries_validate($form, &$form_state) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
  if ($form_state['values']['op'] !== t('Import Selection', array(), array('context' => 'gofast'))) {
    return;
  }
      
  $rid = reset((array_filter($form_state['values']['roles'])));
  if (!array_key_exists($rid, $form['import_opt']['roles']['#options'])) {
    form_set_error('roles', t('The selected profile is not part of the authorized options.', array(), array('context' => 'gofast:gofast_ldap')));
  }
}
    
/**
 * Form submit handler for LDAP managed entries.
 * 
 * Imports LDAP user entries from an external server, creating/provisioning 
 * drupal user accounts appropriately.
 */
function gofast_ldap_admin_entries_import($form, &$form_state) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
  if ($form_state['values']['op'] !== t('Import Selection', array(), array('context' => 'gofast'))) {
    return;
  }
      
  $val = $form_state['values'];
      
  $sid = $val['sid'];
  $form_id = $form_state['build_info']['form_id'];
  $results = $form_state[$form_id . '_search_results'];
      
  $mapping = array_filter(gofast_ldap_prov_mapping($sid));
      
  $selected = array_filter($val['selection']);
  $defaults = array('ldap_user_manager' => $val['manager'], 'ldap_user_ou' => $val['ou']);
      
      
  $rid = reset((array_filter($val['roles'])));
  $role_name = $form['import_opt']['roles']['#options'][$rid];
      
  $ret = $errors = array();
  foreach ($selected as $username) {
    $entry = $results[$username] + array('__name' => $username);
        
    $prov = array_map(function($attr) use ($entry, $sid) {
      return isset($entry[$attr][0]) ? $entry[$attr][0] : _ldap_prov_fallback($attr, $entry, $sid); 
    }, $mapping);
        
    $data = $defaults + array_filter($prov);
    $ret[$username] = gofast_user_create($username, $role_name, $data);
    $errors[$username] = $ret[$username] ? FALSE : form_get_errors();
  }
      
  // Alter drupal messages queue to make it more readable.
  $created = array_keys(array_filter($ret));  
  $msg = t('Following accounts have been created successfully : !list', array('!list' => theme('item_list', array('items' => $created))), array('context' => 'gofast:gofast_ldap'));  
  drupal_get_messages($type = 'status', TRUE);
  drupal_set_message($msg, 'status');
      
//  _dump(array($sid, 'ret' => $ret, '$errors' => $errors), 'fs');
}
    
/**
 * Ajax callback for testing LDAP server connection, given the submitted POST
 * parameters.
 */
function gofast_ldap_admin_test_connection($options = NULL, $ajax = TRUE) {
  ldap_servers_module_load_include('php', 'ldap_servers', 'LdapServerAdmin.class');
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
      
  $status = FALSE;
  $settings = $options ? $options : filter_input(INPUT_POST, 'ldapConnectionTest', FILTER_DEFAULT , FILTER_REQUIRE_ARRAY);
      
  if (empty($settings)) {
    watchdog('Gofast LDAP', 'Error while testing connection, no server settings received.', array(), WATCHDOG_ERROR);
  }
  else {
    // Load current config.
    $sid = $settings['sid'];
    $server = new LdapServerAdmin($sid);
    if ($server->sid !== $sid) {
      watchdog('Gofast LDAP', 'Error while testing connection, cannot load server configuration. Server ID: :sid', array(':sid' => $sid), WATCHDOG_ERROR);
    }
    else {
      // Get field mapping (bindpw is protected).
      $map = $server::field_to_properties_map() + array('bindpw' => 'bindpw');
          
      // Override saved configuration with submitted settings.
      foreach ($settings as $setting => $value) {
        if (array_key_exists($setting, $map)) {
          $property = $map[$setting];
          $server->$property = $value;
        }
      }
          
      // Test server connection.
      $server->disconnect();
      $server->connect();
      $binding = $server->bind();
          
      $status = $binding === LDAP_SUCCESS;
      watchdog('Gofast LDAP', 'LDAP Server binding attempt - Server ID: :sid - status: :status.', array(':sid' => $sid, ':status' => $status ? 'success' : 'fail'), WATCHDOG_ERROR);
    } 
  }
      
  if ($ajax) {
    drupal_json_output(array('connectionStatus' => $status));
    exit;
  }
      
  return $status;
}
    
/**
 * Helper that switches SASL Authentication flags, either global or for a 
 * specific account if $account is set.
 * 
 * @see gofast_ldap_sasl_auth_on() for more details.
 */
function gofast_ldap_sasl_auth_switch($toggle = NULL, $account = NULL) {
  if (!isset($toggle)) {
    // Check status and revert it.
    $toggle = isset($account->sasl_auth[LANGUAGE_NONE][0]['value']) ? 
            $account->sasl_auth[LANGUAGE_NONE][0]['value'] : ! variable_get('gofast_sasl_auth', FALSE);
  }
  return $toggle ? gofast_ldap_sasl_auth_on($account) : gofast_ldap_sasl_auth_off($account);
}
    
/**
 * Helper that switches SASL Authentication flags, either global or for a 
 * specific account if $account is set.
 * 
 * @see gofast_ldap_sasl_auth_on() for more details.
 */
function gofast_ldap_sasl_auth_switch_async($toggle = NULL, $account = NULL) {
    set_time_limit(0);
    fastcgi_finish_request();
        
    variable_set("gofast_sasl_switching", TRUE);
    gofast_ldap_sasl_auth_switch($toggle, $account);
}
    
/**
 * Helper that returns a list of all users that COULD be affected by delegated
 * authentication. Drupal admin, Gofast primary adm, and extranet users are 
 * excluded from this list.
 * 
 * @return array
 *  An array of uid keyed by user name.
 */
function gofast_ldap_sasl_get_users() {
  $query = db_select('users', 'u');
  $query->join('field_data_is_extranet', 'f', 'f.entity_id = u.uid');
  $res = $query
          ->fields('u', array('uid', 'name'))
          ->condition('u.uid', array(0, 1, GOFAST_USER_ADMINISTRATOR_ID), 'NOT IN')
          ->condition('f.is_extranet_value', 0)
          ->condition('u.status', 1)
          ->execute()
          ->fetchAllAssoc('name');
              
  return array_map(function($item){ return $item->uid; }, $res);
}
    
/**
 * Enables SASL delegated authentication.
 * 
 * Update userPassword attributes (from the internal server) for each users 
 * except those not supposed to be registered in the external server (extranet 
 * users, Gofast primary administrator & drupal admin), so that LDAP delegates
 * the authentication process to the external server.
 * 
 * It is possible to process a single account, for exemple if the account was 
 * previously reverted and you want to reactive delegation fot this account, 
 * or if the mechanism is disabled globally and the need is to enable it for 
 * a limited set of users, (not for all users that would be normally affected).
 * 
 * @see gofast_ldap_sasl_auth_off()
 * 
 * @param object $account [optional] 
 *  A drupal user account. If set, auth delegation will be enabled globally if 
 *  not already, but only this account will be processed.
 * 
 * @return array
 *  An array of log information, or FALSE if an error occured. The log array 
 *  contains the following keys :
 * - 'sasl_auth_on' => Array of users (ids) for which SASL auth is enabled.
 * - 'sasl_auth_off' => Array of uids for which SASL auth failed & is disabled.
 * - 'all_users' => $uids => Array of all users impacted by SASL auth switch.
 */
function gofast_ldap_sasl_auth_on($account = NULL) {
   watchdog('Gofast LDAP', 'Activating SASL authentication');
       
  // Load GoFast internal & external server.
  $server = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
  $ext_server = gofast_ldap_server_load(GOFAST_LDAP_EXT_SERVER);
      
  // Try binding to servers.
  $bindings = TRUE;
  foreach (array($server, $ext_server) as $_server) {
    $bindings = $bindings & gofast_ldap_bind_or_warn($_server);
  }
      
  if (!$bindings) {
    variable_set("gofast_sasl_switching", FALSE);
    return FALSE;
  }
      
  $single = isset($account->uid) && isset($account->name);
      
  // List all 'SASL users' so we can match accounts with LDAP entries.
  if ($single) {
    $uids = array($account->name => $account->uid);
    $users = array($account->uid => $account);
  }
  else {
    $uids = gofast_ldap_sasl_get_users();
    $users = entity_load('user', $uids);
  }
      
  // External server domain components.
  $basedn = is_array($ext_server->basedn) ? reset($ext_server->basedn) : $ext_server->basedn;
  $dc_string = substr($basedn, strpos($basedn, 'dc='));
  $domain = str_replace(array('dc=', ',', 'DC='), array('', '.',''), $dc_string);
      
  global $base_url;
  $success = $fail = array();
      
  foreach ($users as $uid => $_account) {
    watchdog('jle', "Setting SASL on for " . $uid);
    // Check if the account is registered in the targeted server.
    $filter = "{$ext_server->user_attr}={$_account->name}";
    $result = $ext_server->searchAllBaseDns($filter);
    if (!isset($result['count']) || $result['count'] === 0) {
      $msg = t('Could not find !user in directory using filter "!filter".', array('!user' => $_account->name, '!filter' => $filter), array('context' => 'gofast:gofast_ldap'));
      $fail[$_account->uid] = $msg;
      watchdog('Gofast LDAP', $msg, array(), WATCHDOG_ERROR);
      // Save status and abort.
      gofast_ldap_sasl_update_field($_account, 0);
      continue;
    }
        
    // Process userPassword attribute (internal).
    $dn = gofast_ldap_user_dn($uid);
    $userPassword = "{SASL}{$_account->name}@{$domain}";
    if (!$server->modifyLdapEntry($dn, array('userPassword' => $userPassword))) {
      $msg = t('Could not modify !user entry in directory.', array('!user' => $_account->name), array('context' => 'gofast:gofast_ldap'));
      watchdog('Gofast LDAP', $msg, array(), WATCHDOG_ERROR);
      $fail[$_account->uid] = $msg;
      // Save status and abort.
      gofast_ldap_sasl_update_field($_account, 0);
      continue;
    }
        
    $success[$_account->uid] = t('SASL authentication activated successfully : !pw', array('!pw' => $userPassword), array('context' => 'gofast:gofast_ldap'));
    watchdog('Gofast LDAP', $success[$_account->uid]);
        
    // Save status.
    gofast_ldap_sasl_update_field($_account, 1);
        
    // Notify user that his password is now managed by its company's directory.
    $subject = t('GoFast - SASL Authentication ON', array(), array('langcode' => $_account->language, 'context' => 'gofast:gofast_ldap'));
    $content = t('Your !site account credentials are now managed by your company\'s directory.',
            array('!site' => l(GOFAST_NAME, $base_url)), array('langcode' => $_account->language, 'context' => 'gofast:gofast_ldap'))
        .' <br /><br /> '
      .t('If you encounter any problem accessing your account, you can still get a 
      temporary access via the login page. However, you will have to contact 
      your enterprise system manager to change your password.',
      array(), array('langcode' => $_account->language ,'context' => 'gofast:gofast_ldap'));
//    gofast_send_immediate_notifications($_account, $subject, $content, array(), 'phpmailer');
  }
      
  if (!$single) {
    watchdog('Gofast LDAP', t('SASL authentication - success: !count', array('!count' => count($success)), array('context' => 'gofast:gofast_ldap')));
    watchdog('Gofast LDAP', t('SASL authentication - error: !count', array('!count' => count($fail)), array('context' => 'gofast:gofast_ldap')));    
  }
      
  $log = array(
    'sasl_auth_on' => $success,
    'sasl_auth_off' => $fail,
    'all_users' => $uids
  );
      
  // Save SASL auth state.
  variable_set('gofast_sasl_auth', TRUE);
      
  // Reset cache.
  entity_get_controller('user')->resetCache($uids);
      
  variable_set("gofast_sasl_switching", FALSE);
  return $log;
}
    
/**
 * Disables SASL delegated authentication.
 * 
 * Revert userPassword attributes in each LDAP user entry that is affected by 
 * SASL authentication. It is possible to revert a single account while keeping 
 * the global mechanism enabled by passing in a user account.
 * 
 * @see gofast_sasl_delegation_on() for more details.
 * 
 * @param object $account [optional] 
 *  A fully loaded drupal user account. If set, then only this account will be 
 *  reverted and SASL authentication mechanism remains active globally.
 * 
 * @return array
 *  An array of log information, or FALSE if an error occured.
 */
function gofast_ldap_sasl_auth_off($account = NULL) {
  watchdog('Gofast LDAP', 'Deactivating SASL Authentication');
  // We need to update password attribute for each affected users. To list them
  // we could rely on user entity's field sasl_auth, but it is safer to read 
  // directly from LDAP (operation reset passwords). Then we can safely update
  // sasl_auth field for every users returned by gofast_ldap_sasl_get_users().
      
  // Init GoFast Internal LDAP directory.
  $server = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
  if (!gofast_ldap_bind_or_warn($server)) {
    variable_set("gofast_sasl_switching", FALSE);
    return FALSE;
  }
      
  $single = isset($account->uid) && isset($account->name);
      
  // We have to check the encoding scheme for each user entries (we have to list 
  // attribute values because substr rules (like applying "userPassword={SASL}*" 
  // are not allowed with this attribute (however, we can still read from it!).
  $filter = $single ? ($server->user_attr . '=' . $account->name) : 'objectClass=person';
  $entries = $server->search(GOFAST_LDAP_INT_REALM_USERS, $filter, array('uid','userPassword'));  
      
  if (!isset($entries['count']) || !$entries['count']) {
    variable_set("gofast_sasl_switching", FALSE);
    return FALSE;
  }
      
  // List all 'SASL users' so we can match accounts with LDAP entries.
  if ($single) {
    $uids = array($account->name => $account->uid);
    $users = array($account->uid => $account);
  }
  else {
    $uids = gofast_ldap_sasl_get_users();
    $users = entity_load('user', $uids);
  }
      
  unset ($entries['count']);
  global $base_url;
  $success = $fail = array();
      
  foreach($entries as $key => $entry) {
    // Check userPassword presence, abort if fails or if user is drupal admin.
    if (!isset($entry['userpassword'][0]) || $entry['uid'][0] === 'admin') continue;
    if (strpos($entry['userpassword'][0], '{SASL}') !== 0) continue;
    $name = $entry['uid'][0];
    $_account = $users[$uids[$name]];
    /**
     * LDAP modules does not handle encryption types they provide, only blowfish 
     * encryption is implemented, default is clear text.
     * $enc_type = variable_get('ldap_servers_encryption' , LDAP_SERVERS_ENC_TYPE_CLEARTEXT);
     * Here a custom md5 encryption to be tested : '{md5}'. base64_encode(pack('H*', md5($pw)));
     */
    $pw = substr(gofast_encrypt(time(), $name), 0, 8);
        
    // Update userPassword attribute.
    if (!$server->modifyLdapEntry($entry['dn'], array('userPassword' => $pw))) {
      $msg = 'Could not modify !user entry in directory.';
      watchdog('Gofast LDAP', $msg, array('!user' => $name), WATCHDOG_ERROR);
      $fail[$_account->uid] = $msg;
      continue;
    }
        
    $success[$_account->uid] = t('SASL authentication deactivated successfully for !user', array('!user' => $name), array('context' => 'gofast:gofast_ldap'));
    watchdog('Gofast LDAP', $success[$_account->uid]);
        
    // Notify user that his password is now managed by Gofast.
    $subject = t('GoFast - SASL Authentication OFF', array(), array('langcode' => $_account->language, 'context'=> 'gofast:gofast_ldap'));
    $profile_page = l(t('profile page', array(), array('langcode' => $_account->language, 'context' => 'gofast:gofast_ldap')), $base_url . '/user');
    $content = t('Your !site account settings have been reset. From now you can log in using these credentials :'
                , array('!site' => l(GOFAST_NAME, $base_url)), array('langode' => $_account->language, 'context' => 'gofast:gofast_ldap' )) 
      .'<br /><br />'
      .t('username: %username', array('%username' => $_account->name), array('langcode' => $_account->language, 'context' => 'gofast')).' <br /> '
      .t('password: %password', array('%password' => $pw), array('langcode' => $_account->language, 'context' => 'gofast')).' <br /><br />'
      .t('You may change your password via your !profile_page.', array('!profile_page' => $profile_page), array('langcode' => $_account->language, 'context' => 'gofast:gofast_ldap')
    );
//    gofast_send_immediate_notifications($_account, $subject, $content, array(), 'phpmailer');
  }
      
  // Now we can safely update sasl_auth field for every 'SASL users'.
  foreach ($users as $uid => $_account) {
    gofast_ldap_sasl_update_field($_account, 0);
  }
      
  // Save SASL auth state only if the operation doesn't focus on a single account.
  if (!$single) {
    variable_set('gofast_sasl_auth', FALSE);
    watchdog('Gofast LDAP', t('SASL authentication - success: !count', array('!count' => count($success), array('context' => 'gofast:gofast_ldap'))));
    watchdog('Gofast LDAP', t('SASL authentication - error: !count', array('!count' => count($fail)), array('context' => 'gofast:gofast_ldap')));    
  }
      
  // Reset cache.
  entity_get_controller('user')->resetCache($uids);  
      
  $log = array(
    'sasl_auth_on' => $fail,
    'sasl_auth_off' => $success,
    'all_users' => $uids
  );
      
  variable_set("gofast_sasl_switching", FALSE);
      
  return $log;
}
    
/**
 * Helper that updates SASL field on the given entity.
 * 
 * @param object $account
 *  A fully loaded drupal user account.
 */
function gofast_ldap_sasl_update_field($account, $value) {
  $account->sasl_auth[LANGUAGE_NONE][0]['value'] = $value;
  field_attach_presave('user', $account);
  field_attach_update('user', $account);
}
    
/**
 * Account Sync form builder - Search a user entry in LDAP and provision
 * data into a drupal account. 
 */
function gofast_ldap_sync_form() {
  $form = array();
      
  unset($_SESSION['gofast_ldap_user_synched_data']);
      
  // Hidden field to store data in (can't use 'storage')
  $form['ldap_data'] = array(
    '#type' => 'textarea',
    '#resizable' => FALSE,
    '#attributes' => array('style' => array('display:none'))
  );
      
  $form['ldap_search'] = array(
    '#title' => t('Search', array(), array('context' => 'gofast')),
    '#type' => 'textfield',
    '#default_value' => '',
    '#autocomplete_path'  => 'admin/config/gofast/ldap/search-autocomplete',
    '#description' => t('Search by first-name, last-name or id, select a suggestion then hit "Grab data"', array(), array('context' => 'gofast:gofast_ldap'))
  );
      
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Grab data', array(), array('context' => 'gofast'))
  );
      
  return $form;
}
    
/**
 * Modal page callback - Account Sync
 */
function gofast_ldap_sync_form_modal($js) {
  $isSASL = variable_get('gofast_sasl_auth', 0);
  if (!$js) {
    return drupal_get_form('gofast_ldap_sync_form');
  }
  ctools_include('modal');
  ctools_include('ajax');
      
  $form_state = array(
    'ajax' => TRUE,
    'title' => t('Search', array(), array('context' => 'gofast'))
  );
  //if($isSASL){
    $commands = ctools_modal_form_wrapper('gofast_ldap_sync_form', $form_state);
        
    if ($form_state['submitted']) {
      $html_form = gofast_normalize_string_from_ajaxifying(drupal_render(drupal_get_form('user_register_form')));      
      $commands = array(
        ctools_modal_command_dismiss(),         
        ajax_command_replace('#user-register-form', $html_form),
            
      ); 
      if(isset($_SESSION['gofast_ldap_user_synched_data_messages'])){
          $commands[] = gofast_command_toast_message($_SESSION['gofast_ldap_user_synched_data_messages'], 'error') ; 
          unset($_SESSION['gofast_ldap_user_synched_data_messages']);
      }
    }
  //}
 /* else{
    $commands = array(
      gofast_command_toast_message(t("This plateform is not associated with an external LDAP. Please contact your administrator.", array(), array('context' => 'gofast:ldap')), 'error')
    );
  }*/
      
  print ajax_render($commands);
}
    
/**
 * Account Sync - Validate callback 
 */
function gofast_ldap_sync_form_validate(&$form, &$form_state) {
  module_load_include('inc', 'gofast_ldap', 'gofast_ldap.settings');
  $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_EXT_SERVER);
      
  if (!gofast_ldap_bind_or_warn($LdapServer)) {
    form_set_error('ldap_search', t('Unable to prefill form, LDAP Directory seems to be unavailable.', array(), array('context' => 'gofast:gofast_ldap')));
    return; // unable togo further.
  }
      
  // Get matched user identifier.
  if (!preg_match('/.*\((.*)\)$/', $form_state['values']['ldap_search'], $match)) {
    form_set_error('ldap_search', t('Selection does not match a .', array(), array('context' => 'gofast:gofast_ldap')));
    return; // unable togo further.
  }
      
  // Check if a user with the same identifier already exists.
  $username = $match[1];
  if (user_load_by_name($username)) {
    $_SESSION['gofast_ldap_user_synched_data_messages'] = t('A user account with the same identifier "%user" already exists.', array('%user' => $username)); 
    form_set_error('ldap_search', t('A user account with the same identifier "%user" already exists.', array('%user' => $username), array('context' => 'gofast:gofast_ldap')));
  }
      
  $_f = array('attr' => $LdapServer->user_attr, 'value' => $username);
  list ($attribute, $value) = gofast_ldap_escape_filter($_f);
  $filter = $attribute . '=' . $value;
  $attributes = array_keys(gofast_ldap_server_attributes($LdapServer->sid, FALSE, FALSE));
  $base_dn = reset($LdapServer->basedn);
      
  $result = $LdapServer->search($base_dn, $filter, $attributes);
  if (!isset($result['count']) || !$result['count']) {
    form_set_error('ldap_search', t('No data found for user %user', array('%user' => $username), array('context' => 'gofast:gofast_ldap')));
  } 
  else {
    $form_state['values']['ldap_data'] = $result[0];
    unset($form_state['storage']);
  }
}
    
/**
 * Account Sync - Submit callback 
 */
function gofast_ldap_sync_form_submit(&$form, &$form_state) {
  // Save user data in session.   
  $_SESSION['gofast_ldap_user_synched_data'] = $form_state['values']['ldap_data'];
  $form_state['redirect'] = 'admin/people/create';
}
    
/**
 * Autocomplete callback : LDAP Search external directory for user entries.
 */
function gofast_ldap_search_autocomplete($str) {
  $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_EXT_SERVER);
  if (!gofast_ldap_bind_or_warn($LdapServer)) {
    return;
  }
      
  $matches = array();
      
  // Left trim input string and right trim for wildcard/escape char, then append
  // wildcard character.
  $str = ltrim($str);
  $str = rtrim($str, '*\\') . '*';
      
  if ($str === '') {
    drupal_json_output(array());
    exit;
  }
      
  // Person objectclass requires cn to be set, we can safely require it too.
  $attributes = array($LdapServer->user_attr, 'cn', 'givenname', 'sn'); 
      
  // Filter based on input.
  $filters = array(
    array('attr' => $LdapServer->user_attr, 'value' => $str),
    array('attr' => 'sn', 'value' => $str),
    array('attr' => 'cn', 'value' => $str)
  );
      
  // Default filter string. 
  $default = '(objectClass=organizationalPerson)';
  $filter = '';
  foreach ($filters as $_filter) {
    list ($attribute, $value) = gofast_ldap_escape_filter($_filter);
    $filter .= '(' . $attribute . '=' . $value . ')';
  }
      
  $filter = "(&{$default}(|$filter))";
  $base_dn = reset($LdapServer->basedn);
  $entries = $LdapServer->search($base_dn, $filter, $attributes);
      
  for ($i=0, $j=min(array($entries['count'],10)); $i<$j; $i++) {
    $matches[$m = "{$entries[$i]['cn'][0]} ({$entries[$i][$LdapServer->user_attr][0]})"] = $m;
  }
      
  drupal_json_output($matches);
  exit;
}