<?php
/**
 * @file
 * gofast_features_ldap.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function gofast_features_ldap_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gofast_ldap_int_base_dn';
  $strongarm->value = 'dc=ceo-vision,dc=com';
  $export['gofast_ldap_int_base_dn'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_authentication_conf';
  $strongarm->value = array(
    'sids' => array(
      'gofastLDAP' => 'gofastLDAP',
    ),
    'authenticationMode' => 2,
    'loginUIUsernameTxt' => NULL,
    'loginUIPasswordTxt' => NULL,
    'ldapUserHelpLinkUrl' => NULL,
    'ldapUserHelpLinkText' => 'Logon Help',
    'emailOption' => 4,
    'emailUpdate' => 3,
    'passwordOption' => 4,
    'allowOnlyIfTextInDn' => array(
      0 => 'ou=people',
    ),
    'excludeIfTextInDn' => array(),
    'allowTestPhp' => '',
    'excludeIfNoAuthorizations' => NULL,
    'ssoRemoteUserStripDomainName' => NULL,
    'ssoExcludedPaths' => array(),
    'ssoExcludedHosts' => array(),
    'seamlessLogin' => NULL,
    'ssoNotifyAuthentication' => NULL,
    'ldapImplementation' => NULL,
    'cookieExpire' => NULL,
    'emailTemplate' => '@username@fake-domain.com',
    'emailTemplateHandling' => 3,
    'templateUsagePromptUser' => 0,
    'templateUsageNeverUpdate' => 0,
    'templateUsageResolveConflict' => 1,
    'templateUsagePromptRegex' => '.*@fake-domain\\.com',
    'templateUsageRedirectOnLogin' => 1,
  );
  $export['ldap_authentication_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_help_user_data_clear';
  $strongarm->value = 0;
  $export['ldap_help_user_data_clear'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_help_user_data_clear_set_date';
  $strongarm->value = 1393857729;
  $export['ldap_help_user_data_clear_set_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_help_watchdog_detail';
  $strongarm->value = 0;
  $export['ldap_help_watchdog_detail'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_encryption';
  $strongarm->value = '6';
  $export['ldap_servers_encryption'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_servers_require_ssl_for_credentails';
  $strongarm->value = 1;
  $export['ldap_servers_require_ssl_for_credentails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_user_conf';
  $strongarm->value = array(
    'drupalAcctProvisionServer' => 0,
    'ldapEntryProvisionServer' => 'gofastLDAP',
    'drupalAcctProvisionTriggers' => array(
      2 => 0,
      1 => 0,
    ),
    'ldapEntryProvisionTriggers' => array(
      6 => '6',
      7 => 0,
      8 => '8',
      3 => '3',
    ),
    'orphanedDrupalAcctBehavior' => 'ldap_user_orphan_do_not_check',
    'orphanedCheckQty' => '100',
    'userConflictResolve' => 2,
    'manualAccountConflict' => '3',
    'acctCreation' => 1,
    'ldapUserSynchMappings' => array(
      2 => array(
        '[dn]' => array(
          'ldap_attr' => '[dn]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'uid=[property.name],ou=people,dc=ceo-vision,dc=com',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[objectclass:0]' => array(
          'ldap_attr' => '[objectclass:0]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'inetOrgPerson',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[objectclass:1]' => array(
          'ldap_attr' => '[objectclass:1]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'organizationalPerson',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[objectclass:2]' => array(
          'ldap_attr' => '[objectclass:2]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'person',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[objectclass:3]' => array(
          'ldap_attr' => '[objectclass:3]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => 'top',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[mail]' => array(
          'ldap_attr' => '[mail]',
          'user_attr' => '[property.mail]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[cn]' => array(
          'ldap_attr' => '[cn]',
          'user_attr' => 'user_tokens',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '[field.ldap_user_givenname] [field.ldap_user_sn]',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[uid]' => array(
          'ldap_attr' => '[uid]',
          'user_attr' => '[property.name]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[userpassword]' => array(
          'ldap_attr' => '[userpassword]',
          'user_attr' => '[password.user-only]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[givenName]' => array(
          'ldap_attr' => '[givenName]',
          'user_attr' => '[field.ldap_user_givenname]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[sn]' => array(
          'ldap_attr' => '[sn]',
          'user_attr' => '[field.ldap_user_sn]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[displayName]' => array(
          'ldap_attr' => '[displayName]',
          'user_attr' => '[field.ldap_user_displayname]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[ou]' => array(
          'ldap_attr' => '[ou]',
          'user_attr' => '[field.ldap_user_ou]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[manager]' => array(
          'ldap_attr' => '[manager]',
          'user_attr' => '[field.ldap_user_manager]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[title]' => array(
          'ldap_attr' => '[title]',
          'user_attr' => '[field.ldap_user_title]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[o]' => array(
          'ldap_attr' => '[o]',
          'user_attr' => '[field.ldap_user_o]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[telephoneNumber]' => array(
          'ldap_attr' => '[telephoneNumber]',
          'user_attr' => '[field.ldap_user_telephonenumber]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[mobile]' => array(
          'ldap_attr' => '[mobile]',
          'user_attr' => '[field.ldap_user_mobile]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[departmentNumber]' => array(
          'ldap_attr' => '[departmentNumber]',
          'user_attr' => '[field.ldap_user_departmentnumber]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[description]' => array(
          'ldap_attr' => '[description]',
          'user_attr' => '[field.ldap_user_description]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
        '[photo]' => array(
          'ldap_attr' => '[photo]',
          'user_attr' => '[property.picture]',
          'convert' => 0,
          'direction' => '2',
          'user_tokens' => '',
          'config_module' => 'ldap_user',
          'prov_module' => 'ldap_user',
          'enabled' => 1,
          'prov_events' => array(
            0 => 4,
            1 => 3,
          ),
        ),
      ),
    ),
    'disableAdminPasswordField' => 0,
  );
  $export['ldap_user_conf'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ldap_user_cron_last_uid_checked';
  $strongarm->value = 1;
  $export['ldap_user_cron_last_uid_checked'] = $strongarm;

  return $export;
}
