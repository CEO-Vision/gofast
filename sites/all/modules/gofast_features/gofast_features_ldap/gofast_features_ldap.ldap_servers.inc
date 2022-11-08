<?php
/**
 * @file
 * gofast_features_ldap.ldap_servers.inc
 */

/**
 * Implements hook_default_ldap_servers().
 */
function gofast_features_ldap_default_ldap_servers() {
  $export = array();

  $ldap_servers_conf = new stdClass();
  $ldap_servers_conf->disabled = FALSE; /* Edit this to true to make a default ldap_servers_conf disabled initially */
  $ldap_servers_conf->api_version = 1;
  $ldap_servers_conf->sid = 'gofastLDAP';
  $ldap_servers_conf->name = 'gofastLDAP';
  $ldap_servers_conf->status = TRUE;
  $ldap_servers_conf->ldap_type = 'openldap';
  $ldap_servers_conf->address = 'localhost';
  $ldap_servers_conf->port = 389;
  $ldap_servers_conf->tls = FALSE;
  $ldap_servers_conf->followrefs = FALSE;
  $ldap_servers_conf->bind_method = 1;
  $ldap_servers_conf->binddn = 'cn=manager,dc=ceo-vision,dc=com';
  $ldap_servers_conf->bindpw = 'mandriva';
  $ldap_servers_conf->basedn = array(
    0 => 'dc=ceo-vision,dc=com',
  );
  $ldap_servers_conf->user_attr = 'uid';
  $ldap_servers_conf->account_name_attr = 'uid';
  $ldap_servers_conf->mail_attr = 'mail';
  $ldap_servers_conf->mail_template = '';
  $ldap_servers_conf->picture_attr = 'photo';
  $ldap_servers_conf->unique_persistent_attr = 'entryuuid';
  $ldap_servers_conf->unique_persistent_attr_binary = TRUE;
  $ldap_servers_conf->user_dn_expression = 'uid=%username,ou=people,%basedn';
  $ldap_servers_conf->ldap_to_drupal_user = '';
  $ldap_servers_conf->testing_drupal_username = '';
  $ldap_servers_conf->testing_drupal_user_dn = '';
  $ldap_servers_conf->grp_unused = FALSE;
  $ldap_servers_conf->grp_object_cat = 'groupofnames';
  $ldap_servers_conf->grp_nested = TRUE;
  $ldap_servers_conf->grp_user_memb_attr_exists = TRUE;
  $ldap_servers_conf->grp_user_memb_attr = 'memberof';
  $ldap_servers_conf->grp_memb_attr = 'member';
  $ldap_servers_conf->grp_memb_attr_match_user_attr = 'dn';
  $ldap_servers_conf->grp_derive_from_dn = FALSE;
  $ldap_servers_conf->grp_derive_from_dn_attr = '';
  $ldap_servers_conf->grp_test_grp_dn = '';
  $ldap_servers_conf->grp_test_grp_dn_writeable = '';
  $ldap_servers_conf->search_pagination = FALSE;
  $ldap_servers_conf->search_page_size = 1000;
  $ldap_servers_conf->weight = 0;
  $export['gofastLDAP'] = $ldap_servers_conf;

  return $export;
}
