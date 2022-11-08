<?php

/**
 * @file
 *  Ldap Server default settings. 
 */

/**
 * Provides default settings for Gofast LDAP internal/external servers.
 * 
 * @param string $sid
 *  LDAP server ID or server type.
 */
function gofast_ldap_server_defaults($sid = NULL, $param = NULL) {
  if (empty($sid) || !is_scalar($sid)) {
    return false;
  }

  $settings = array();
  
  switch ($sid) {
    case GOFAST_LDAP_INT_SERVER :
      // OpenLDAP Gofast internal server base configuration.
      $settings = array(
        'sid' => GOFAST_LDAP_INT_SERVER,
        'name' => GOFAST_LDAP_INT_SERVER,
        'status' => 1,
        'ldap_type' => 'openldap',
        'address' => 'localhost',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => GOFAST_LDAP_INT_BIND_DN,
        'bindpw' => GOFAST_LDAP_INT_BIND_PW,
        'clear_bindpw' => 0,
        'basedn' => GOFAST_LDAP_INT_BASE_DN,
        'user_attr' => 'uid',
        'account_name_attr' => 'uid',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'jpegPhoto',
        'unique_persistent_attr' => 'entryuuid',
        'unique_persistent_attr_binary' => 1,
        'user_dn_expression' => 'uid=%username,ou=people,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => 'groupofnames',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 1,
        'grp_user_memb_attr' => 'memberof',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => 'o',
        'title_attr' => 'title',
        'department_attr' => 'departmentnumber'
      );
      break;
      
    case 'openldap' :
      // OpenLDAP ext server base configuration.
      $settings = array(
        'sid' => GOFAST_LDAP_EXT_SERVER,
        'name' => '',
        'status' => 1,
        'ldap_type' => 'openldap',
        'address' => '',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => '',
        'bindpw' => '',
        'clear_bindpw' => 0,
        'basedn' => '',
        'user_attr' => 'uid',
        'account_name_attr' => 'uid',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'jpegPhoto',
        'unique_persistent_attr' => 'entryuuid',
        'unique_persistent_attr_binary' => 1,
        'user_dn_expression' => 'uid=%username,ou=people,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => 'groupofnames',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 0,
        'grp_user_memb_attr' => '',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => 'o',
        'title_attr' => 'title',
        'department_attr' => 'departmentnumber'        
      );
      break;
      
    case GOFAST_LDAP_EXT_SERVER:
    case 'default':
    default:
      $settings = array(
        'sid' => $sid,
        'name' => '', 
        'status' => 1,
        'ldap_type' => 'default',
        'address' => '',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => '',
        'bindpw' => '',
        'clear_bindpw' => 0,
        'basedn' => '',
        'user_attr' => '',
        'account_name_attr' => '',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'jpegPhoto',
        'unique_persistent_attr' => '',
        'unique_persistent_attr_binary' => 0,
        'user_dn_expression' => 'cn=%username,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => '',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 0,
        'grp_user_memb_attr' => '',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => '',
        'title_attr' => 'title',
        'department_attr' => ''
      );
      break;
      
    case 'ad':
      // Active Directory base configuration, settings are derived from Botanic
      // AD settings and are intended to be used as the defaults for any AD config.
      $settings = array(
        'sid' => GOFAST_LDAP_EXT_SERVER,
        'name' => '', 
        'status' => 1,
        'ldap_type' => 'ad',
        'address' => '',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => '',
        'bindpw' => '',
        'clear_bindpw' => 0,
        'basedn' => '',
        'user_attr' => 'sAMAccountName',
        'account_name_attr' => 'sAMAccountName',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'jpegPhoto', // thumbnailPhoto', -> old 
        'unique_persistent_attr' => '',
        'unique_persistent_attr_binary' => 0,
        'user_dn_expression' => 'cn=%username,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => 'group',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 1,
        'grp_user_memb_attr' => 'memberOf',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => 'company',
        'title_attr' => 'title',
        'department_attr' => 'department'
      );
      break;
      
    case 'botanic_test':
      $settings = array(
        'sid' => GOFAST_LDAP_EXT_SERVER,
        'name' => '', 
        'status' => 1,
        'ldap_type' => 'ad',
        'address' => '192.168.101.142',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => 'sysrobot@botanic.com',
        'bindpw' => '6R0b0t$',
        'clear_bindpw' => 0,
        'basedn' => 'dc=botanic,dc=com',
        'user_attr' => 'sAMAccountName',
        'account_name_attr' => 'sAMAccountName',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'thumbnailPhoto',
        'unique_persistent_attr' => '',
        'unique_persistent_attr_binary' => 0,
        'user_dn_expression' => 'cn=%username,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => 'group',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 1,
        'grp_user_memb_attr' => 'memberOf',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => 'company',
        'title_attr' => 'description', // intended (Botanic's AD misconfigured)
        'department_attr' => 'department'          
      );
      break;
    
    case GOFAST_LDAP_TEST_SERVER:
      $settings = array(
        'sid' => GOFAST_LDAP_INT_SERVER,
        'name' => GOFAST_LDAP_INT_SERVER,
        'status' => 1,
        'ldap_type' => 'openldap',
        'address' => '192.168.8.86',
        'port' => '389',
        'tls' => 0,
        'followrefs' => 0,
        'bind_method' => '1',
        'binddn' => GOFAST_LDAP_INT_BIND_DN,
        'bindpw' => GOFAST_LDAP_INT_BIND_PW,
        'clear_bindpw' => 0,
        'basedn' => GOFAST_LDAP_INT_BASE_DN,
        'user_attr' => 'uid',
        'account_name_attr' => 'uid',
        'mail_attr' => 'mail',
        'mail_template' => '',
        'picture_attr' => 'jpegPhoto',
        'unique_persistent_attr' => 'entryuuid',
        'unique_persistent_attr_binary' => 1,
        'user_dn_expression' => 'uid=%username,ou=people,%basedn',
        'ldap_to_drupal_user' => '',
        'testing_drupal_username' => '',
        'testing_drupal_user_dn' => '',
        'grp_unused' => 0,
        'grp_object_cat' => 'groupofnames',
        'grp_nested' => 1,
        'grp_user_memb_attr_exists' => 1,
        'grp_user_memb_attr' => 'memberof',
        'grp_memb_attr' => 'member',
        'grp_memb_attr_match_user_attr' => 'dn',
        'grp_derive_from_dn' => 0,
        'grp_derive_from_dn_attr' => '',
        'grp_test_grp_dn' => '',
        'grp_test_grp_dn_writeable' => '',
        'search_pagination' => 1,
        'search_page_size' => '1000',
        'company_attr' => 'o',
        'title_attr' => 'title',
        'department_attr' => 'departmentnumber'
      );      
  }
  
  if (!empty($param)) {
    if (isset($settings[$param])) {
      return $settings[$param];
    }
    else {
      watchdog('Gofast LDAP', 'Undefined setting :param in server defaults - server ID: :sid).', array(':param' => $param, ':sid' => $sid));
      return NULL;
    }
  }
  
  return $settings;
}

/**
 * Helper, maps server ID to server labels.
 */
function gofast_ldap_server_default_names($sid = NULL) {
  $map = array(
    GOFAST_LDAP_INT_SERVER => t('Gofast internal server', array(), array('context' => 'gofast:gofast_ldap')),
    GOFAST_LDAP_EXT_SERVER => ('Gofast external server'),
    GOFAST_LDAP_TEST_SERVER => ('Gofast testing server (external)'),
  );
  if (isset($sid)) {
    return isset($map[$sid]) ? $map[$sid] : FALSE;
  }
  return $map;
}

/**
 * Maps form fields from previous Gofast to 3.x versions.
 */
function gofast_ldap_migrate_mapping($mapping = NULL) {
  $map = array(
    'new_to_old' => array(
      'server' => array(
        'ldap_type' => 'ldap_server_type',
        'name' => 'ldap_server_name',
        'address' => 'ldap_server_adress',
        'port' => 'ldap_port',
        'tls' => 'ldap_tls'
      ), 
      'bind_method' => array(
        'binddn' => 'ldap_binddn',
        'bindpw' => 'ldap_bindpw'
      ),
      'users' => array(
        'basedn' => 'ldap_basedn'
      )
    ),
    'old_to_new' => array(
      'ldap_server_type' => 'server::ldap_type',
      'ldap_server_name' => 'server::name',
      'ldap_server_adress' => 'server::address',
      'ldap_port' => 'server::port',
      'ldap_tls' => 'server::tls',
      'ldap_binddn' => 'bind_method::binddn',
      'ldap_bindpw' => 'bind_method::bindpw',
      'ldap_basedn' => 'users::basedn'
    )
  );
  
  if (isset($mapping)) {
    return isset($map[$mapping]) ? $map[$mapping] : array();
  }
  
  return $map;
}


/**
 * Returns LDAP admin form options used to perform a search query. If the form 
 * page is loaded using a pager link and query parameters are set, then query 
 * parameters takes precedence over defaults. 
 */
function gofast_ldap_admin_options_default($sid = GOFAST_LDAP_INT_SERVER) {
  $defaults = array(
    'filters' => array(
      array(
        'attr' => 'sn',
        'value' => '*'
      ),
      array(
        'attr' => '_none',
        'value' => ''
      )
    ),
    'attributes' => array_keys(gofast_ldap_server_attributes($sid, FALSE, FALSE)),
    'sort_by' => 'sn',
    'sort_dir' => 'asc',
    'ipp' => 50, // pager's items per page
    'ou' => NULL,
  );

  $query_opt = filter_input(INPUT_GET, '_ldap_opt', FILTER_DEFAULT, array(
    'flags' => FILTER_REQUIRE_ARRAY,
    'options' => array(
      'default' => array()
    )
  ));

  return $query_opt + $defaults;
}

/**
 * Returns a list of regular user attributes along with their respective labels
 * to be shown in the administration page. The attributes list may differ 
 * according to the server type given by $sid.
 */
function gofast_ldap_server_attributes($sid = GOFAST_LDAP_INT_SERVER, $append_label = TRUE, $display = TRUE) {
  $server = gofast_ldap_server_load($sid);

  // Cas spécifique Botanic (jusqu'à ce qu'ils corrigent leurs entrées)
  global $base_url;
  $botanic = strpos($base_url, 'botanic') !== false;

  $company_attr = gofast_ldap_server_defaults($server->ldap_type, 'company_attr');
  $title_attr = $botanic ? 'description' : 'title';
  
  // Attributes to request when searching. 
  $attributes = array(
    $server->user_attr => t('User ID', array(), array('context' => 'gofast:gofast_ldap')),
    'sn' => t('Last Name', array(), array('context' => 'gofast')),
    'givenname' => t('First Name', array(), array('context' => 'gofast')),
    'cn' => t('Name', array(), array('context' => 'gofast:gofast_ldap')),
    'displayName' => t('Display Name', array(), array('context' => 'gofast')),
    $title_attr => t('Function', array(), array('context' => 'gofast:gofast_ldap')),
    'ou' => t('Organizational Unit', array(), array('context' => 'gofast:gofast_ldap')),
    'department' => t('Department', array(), array('context' => 'gofast:gofast_ldap')),
    $company_attr => t('Entity', array(), array('context' => 'gofast')),
    $server->mail_attr => t('Mail', array(), array('context' => 'gofast')),
    'telephoneNumber' => t('Phone', array(), array('context' => 'gofast')), 
    'mobile' => t('Mobile', array(), array('context' => 'gofast')),
    'description' => "Description"
  );
  
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  foreach($sync_settings['mapping'] as $key => $field){
    if(!empty($field) && empty($attributes[$field])){
      $attributes[$field] = t('Custom field', array(), array('context' => 'gofast:gofast_ldap'));
    }
  }
  
  foreach($sync_settings['filters'] as $association_fields){
    $field = $association_fields[0];
    if(!empty($field) && empty($attributes[$field])){
      $attributes[$field] = t('Custom field', array(), array('context' => 'gofast:gofast_ldap'));
    }
  }
  
  if ($append_label) {
    foreach ($attributes as $attr => &$label) {
      $label .= ' (' . $attr . ')';
    }
  }

  return $display ? (array('_none' => t('None', array(), array('context' => 'gofast'))) + $attributes) : $attributes;
}

/**
 * Maps drupal user account properties to the corresponding LDAP attribute names
 * according to the server id/type given by $sid.
 * 
 * @param string $sid
 *  LDAP Server ID or server type.
 */
function gofast_ldap_prov_mapping($sid = GOFAST_LDAP_EXT_SERVER) {
  $server = gofast_ldap_server_load($sid);
  $key = $sid === GOFAST_LDAP_INT_SERVER ? $sid : $server->ldap_type;
  $defaults = gofast_ldap_server_defaults($key);
  
  return array(
    'name' => _ldap_prov_server_key('user_attr', $server, $defaults),
    'mail' => _ldap_prov_server_key('mail_attr', $server, $defaults),
    'ldap_user_sn' => 'sn',
    'ldap_user_givenname' => 'givenname',
    'ldap_user_displayname' => 'displayname',
    'ldap_user_title' => _ldap_prov_server_key('title_attr', $server, $defaults),
    'ldap_user_o' => _ldap_prov_server_key('company_attr', $server, $defaults),
    'ldap_user_ou' => 'ou',
    'ldap_user_telephonenumber' => 'telephonenumber',
    'ldap_user_mobile' => 'mobile',
    'ldap_user_departmentnumber' => _ldap_prov_server_key('department_attr', $server, $defaults),
    'ldap_user_description' => 'description',
    'ldap_user_manager' => 'manager',
    'ldap_user_mobile' => 'mobile'
  );
}

/**
 * User account provisioning - Values fallback logic for mandatory fields.
 */
function _ldap_prov_fallback($attr, $entry, $sid = NULL) {
  switch ($attr) {
    case 'givenname':
    case 'sn':
      if (empty($entry['cn'][0])) {
        return $entry['__name'];
      }
      list ($givenname, $sn) = explode(' ', $entry['cn'][0], 2) + array(1 => $entry['cn'][0]);
      return $$attr;
    default:
      return NULL;
  }
}

/**
 * Helper. Logic to retrieve an attribute held by a server key given a server 
 * config and its defaults.
 */
function _ldap_prov_server_key($key, $server, $defaults) {
  return isset($server->{$key}) ? $server->{$key} : (isset($defaults[$key]) ? $defaults[$key] : '');
}

