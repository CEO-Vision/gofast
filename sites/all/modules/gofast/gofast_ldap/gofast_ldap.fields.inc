<?php

/**
 * @file
 *  fields definition to extend user bundle.
 *
 */


function gofast_ldap_fields_definition() {
  return array(
    'bundles' => array(
      'user' => NULL,
    ),
    'fields' => array(
      'field_birthdate' => array(
        'entity_types' => array(),
        'foreign keys' => array(),
        'indexes' => array(),
        'settings' => array(
          'cache_count' => 4,
          'cache_enabled' => 0,
          'granularity' => array(
            'day' => 'day',
            'hour' => 0,
            'minute' => 0,
            'month' => 'month',
            'second' => 0,
            'year' => 'year',
          ),
          'timezone_db' => '',
          'todate' => '',
          'tz_handling' => 'none',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_field_birthdate' => array(
                  'value' => 'field_birthdate_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_field_birthdate' => array(
                  'value' => 'field_birthdate_value',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'field_birthdate',
        'type' => 'datetime',
        'module' => 'date',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'datetime',
            'mysql_type' => 'datetime',
            'pgsql_type' => 'timestamp without time zone',
            'sqlite_type' => 'varchar',
            'sqlsrv_type' => 'smalldatetime',
            'not null' => FALSE,
            'sortable' => TRUE,
            'views' => TRUE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'field_format' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'tid' => array(
            'table' => 'taxonomy_term_data',
            'columns' => array(
              'tid' => 'tid',
            ),
          ),
        ),
        'indexes' => array(
          'tid' => array(
            0 => 'tid',
          ),
        ),
        'settings' => array(
          'allowed_values' => array(
            0 => array(
              'vocabulary' => 'format',
              'parent' => 0,
            ),
          ),
          'options_list_callback' => 'i18n_taxonomy_allowed_values',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_field_format' => array(
                  'tid' => 'field_format_tid',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_field_format' => array(
                  'tid' => 'field_format_tid',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'field_format',
        'type' => 'taxonomy_term_reference',
        'module' => 'taxonomy',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'tid' => array(
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'node' => array(
            0 => 'alfresco_item',
            1 => 'article',
            2 => 'forum',
            3 => 'private_space',
            4 => 'webform',
            5 => 'extranet',
            6 => 'public',
            7 => 'group',
            8 => 'organisation',
          ),
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'field_hobbies' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'tid' => array(
            'table' => 'taxonomy_term_data',
            'columns' => array(
              'tid' => 'tid',
            ),
          ),
        ),
        'indexes' => array(
          'tid' => array(
            0 => 'tid',
          ),
        ),
        'settings' => array(
          'allowed_values' => array(
            0 => array(
              'vocabulary' => 'hobbies',
              'parent' => 0,
            ),
          ),
          'options_list_callback' => 'i18n_taxonomy_allowed_values',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_field_hobbies' => array(
                  'tid' => 'field_hobbies_tid',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_field_hobbies' => array(
                  'tid' => 'field_hobbies_tid',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'field_hobbies',
        'type' => 'taxonomy_term_reference',
        'module' => 'taxonomy',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '-1',
        'deleted' => '0',
        'columns' => array(
          'tid' => array(
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'field_interests' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'tid' => array(
            'table' => 'taxonomy_term_data',
            'columns' => array(
              'tid' => 'tid',
            ),
          ),
        ),
        'indexes' => array(
          'tid' => array(
            0 => 'tid',
          ),
        ),
        'settings' => array(
          'allowed_values' => array(
            0 => array(
              'vocabulary' => 'interests',
              'parent' => 0,
            ),
          ),
          'options_list_callback' => 'i18n_taxonomy_allowed_values',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_field_interests' => array(
                  'tid' => 'field_interests_tid',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_field_interests' => array(
                  'tid' => 'field_interests_tid',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'field_interests',
        'type' => 'taxonomy_term_reference',
        'module' => 'taxonomy',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '-1',
        'deleted' => '0',
        'columns' => array(
          'tid' => array(
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'field_skills' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'tid' => array(
            'table' => 'taxonomy_term_data',
            'columns' => array(
              'tid' => 'tid',
            ),
          ),
        ),
        'indexes' => array(
          'tid' => array(
            0 => 'tid',
          ),
        ),
        'settings' => array(
          'allowed_values' => array(
            0 => array(
              'vocabulary' => 'skills',
              'parent' => 0,
            ),
          ),
          'options_list_callback' => 'i18n_taxonomy_allowed_values',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_field_skills' => array(
                  'tid' => 'field_skills_tid',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_field_skills' => array(
                  'tid' => 'field_skills_tid',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'field_skills',
        'type' => 'taxonomy_term_reference',
        'module' => 'taxonomy',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '-1',
        'deleted' => '0',
        'columns' => array(
          'tid' => array(
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'is_broadcaster' => array(
        'entity_types' => array(),
        'translatable' => '0',
        'settings' => array(
          'allowed_values' => array(
            0 => '',
            1 => '',
          ),
          'allowed_values_function' => '',
        ),
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_is_broadcaster' => array(
                  'value' => 'is_broadcaster_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_is_broadcaster' => array(
                  'value' => 'is_broadcaster_value',
                ),
              ),
            ),
          ),
        ),
        'foreign keys' => array(),
        'indexes' => array(
          'value' => array(
            0 => 'value',
          ),
        ),
        'field_name' => 'is_broadcaster',
        'type' => 'list_boolean',
        'module' => 'list',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'int',
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'is_extranet' => array(
        'entity_types' => array(),
        'translatable' => '0',
        'settings' => array(
          'allowed_values' => array(
            0 => '',
            1 => '',
          ),
          'allowed_values_function' => '',
        ),
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_is_extranet' => array(
                  'value' => 'is_extranet_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_is_extranet' => array(
                  'value' => 'is_extranet_value',
                ),
              ),
            ),
          ),
        ),
        'foreign keys' => array(),
        'indexes' => array(
          'value' => array(
            0 => 'value',
          ),
        ),
        'field_name' => 'is_extranet',
        'type' => 'list_boolean',
        'module' => 'list',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'int',
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_current_dn' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'no_ui' => 1,
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_current_dn' => array(
                  'value' => 'ldap_user_current_dn_value',
                  'format' => 'ldap_user_current_dn_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_current_dn' => array(
                  'value' => 'ldap_user_current_dn_value',
                  'format' => 'ldap_user_current_dn_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_current_dn',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_departmentnumber' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_departmentnumber' => array(
                  'value' => 'ldap_user_departmentnumber_value',
                  'format' => 'ldap_user_departmentnumber_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_departmentnumber' => array(
                  'value' => 'ldap_user_departmentnumber_value',
                  'format' => 'ldap_user_departmentnumber_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_departmentnumber',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_description' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_description' => array(
                  'value' => 'ldap_user_description_value',
                  'format' => 'ldap_user_description_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_description' => array(
                  'value' => 'ldap_user_description_value',
                  'format' => 'ldap_user_description_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_description',
        'type' => 'text_long',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'text',
            'size' => 'big',
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_displayname' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_displayname' => array(
                  'value' => 'ldap_user_displayname_value',
                  'format' => 'ldap_user_displayname_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_displayname' => array(
                  'value' => 'ldap_user_displayname_value',
                  'format' => 'ldap_user_displayname_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_displayname',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_givenname' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_givenname' => array(
                  'value' => 'ldap_user_givenname_value',
                  'format' => 'ldap_user_givenname_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_givenname' => array(
                  'value' => 'ldap_user_givenname_value',
                  'format' => 'ldap_user_givenname_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_givenname',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_last_checked' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(),
        'indexes' => array(),
        'no_ui' => 1,
        'settings' => array(),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_last_checked' => array(
                  'value' => 'ldap_user_last_checked_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_last_checked' => array(
                  'value' => 'ldap_user_last_checked_value',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_last_checked',
        'type' => 'number_integer',
        'module' => 'number',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'int',
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_ldap_exclude' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(),
        'indexes' => array(),
        'no_ui' => 1,
        'settings' => array(),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_ldap_exclude' => array(
                  'value' => 'ldap_user_ldap_exclude_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_ldap_exclude' => array(
                  'value' => 'ldap_user_ldap_exclude_value',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_ldap_exclude',
        'type' => 'number_integer',
        'module' => 'number',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'int',
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_manager' => array(
        'entity_types' => array(),
        'translatable' => '0',
        'settings' => array(
          'max_length' => '255',
        ),
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_manager' => array(
                  'value' => 'ldap_user_manager_value',
                  'format' => 'ldap_user_manager_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_manager' => array(
                  'value' => 'ldap_user_manager_value',
                  'format' => 'ldap_user_manager_format',
                ),
              ),
            ),
          ),
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'field_name' => 'ldap_user_manager',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => '255',
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_mobile' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_mobile' => array(
                  'value' => 'ldap_user_mobile_value',
                  'format' => 'ldap_user_mobile_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_mobile' => array(
                  'value' => 'ldap_user_mobile_value',
                  'format' => 'ldap_user_mobile_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_mobile',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_o' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_o' => array(
                  'value' => 'ldap_user_o_value',
                  'format' => 'ldap_user_o_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_o' => array(
                  'value' => 'ldap_user_o_value',
                  'format' => 'ldap_user_o_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_o',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_ou' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(),
        'indexes' => array(
          'value' => array(
            0 => 'value',
          ),
        ),
        'settings' => array(
          'allowed_values' => array(),
          'allowed_values_function' => '',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_ou' => array(
                  'value' => 'ldap_user_ou_value',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_ou' => array(
                  'value' => 'ldap_user_ou_value',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_ou',
        'type' => 'list_text',
        'module' => 'list',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_prov_entries' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'no_ui' => 1,
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_prov_entries' => array(
                  'value' => 'ldap_user_prov_entries_value',
                  'format' => 'ldap_user_prov_entries_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_prov_entries' => array(
                  'value' => 'ldap_user_prov_entries_value',
                  'format' => 'ldap_user_prov_entries_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_prov_entries',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '-1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_puid' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'no_ui' => 1,
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_puid' => array(
                  'value' => 'ldap_user_puid_value',
                  'format' => 'ldap_user_puid_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_puid' => array(
                  'value' => 'ldap_user_puid_value',
                  'format' => 'ldap_user_puid_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_puid',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_puid_property' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'no_ui' => 1,
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_puid_property' => array(
                  'value' => 'ldap_user_puid_property_value',
                  'format' => 'ldap_user_puid_property_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_puid_property' => array(
                  'value' => 'ldap_user_puid_property_value',
                  'format' => 'ldap_user_puid_property_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_puid_property',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_puid_sid' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'no_ui' => 1,
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_puid_sid' => array(
                  'value' => 'ldap_user_puid_sid_value',
                  'format' => 'ldap_user_puid_sid_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_puid_sid' => array(
                  'value' => 'ldap_user_puid_sid_value',
                  'format' => 'ldap_user_puid_sid_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_puid_sid',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '1',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_sn' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_sn' => array(
                  'value' => 'ldap_user_sn_value',
                  'format' => 'ldap_user_sn_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_sn' => array(
                  'value' => 'ldap_user_sn_value',
                  'format' => 'ldap_user_sn_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_sn',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_telephonenumber' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_telephonenumber' => array(
                  'value' => 'ldap_user_telephonenumber_value',
                  'format' => 'ldap_user_telephonenumber_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_telephonenumber' => array(
                  'value' => 'ldap_user_telephonenumber_value',
                  'format' => 'ldap_user_telephonenumber_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_telephonenumber',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'ldap_user_title' => array(
        'entity_types' => array(
          0 => 'user',
        ),
        'foreign keys' => array(
          'format' => array(
            'table' => 'filter_format',
            'columns' => array(
              'format' => 'format',
            ),
          ),
        ),
        'indexes' => array(
          'format' => array(
            0 => 'format',
          ),
        ),
        'settings' => array(
          'max_length' => 255,
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_ldap_user_title' => array(
                  'value' => 'ldap_user_title_value',
                  'format' => 'ldap_user_title_format',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_ldap_user_title' => array(
                  'value' => 'ldap_user_title_value',
                  'format' => 'ldap_user_title_format',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'ldap_user_title',
        'type' => 'text',
        'module' => 'text',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'value' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
          'format' => array(
            'type' => 'varchar',
            'length' => 255,
            'not null' => FALSE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'og_private' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'node' => array(
            'table' => 'node',
            'columns' => array(
              'target_id' => 'nid',
            ),
          ),
        ),
        'indexes' => array(
          'target_id' => array(
            0 => 'target_id',
          ),
        ),
        'settings' => array(
          'handler' => 'og',
          'handler_settings' => array(
            'behaviors' => array(
              'og_behavior' => array(
                'status' => TRUE,
              ),
              'views-select-list' => array(
                'status' => 0,
              ),
            ),
            'membership_type' => 'og_membership_type_default',
            'sort' => array(
              'type' => 'none',
            ),
            'target_bundles' => array(
              'private_space' => 'private_space',
            ),
          ),
          'handler_submit' => 'Change handler',
          'target_type' => 'node',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_og_private' => array(
                  'target_id' => 'og_private_target_id',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_og_private' => array(
                  'target_id' => 'og_private_target_id',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'og_private',
        'type' => 'entityreference',
        'module' => 'entityreference',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '1',
        'deleted' => '0',
        'columns' => array(
          'target_id' => array(
            'description' => 'The id of the target entity.',
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => TRUE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
      'og_user_node' => array(
        'entity_types' => array(),
        'foreign keys' => array(
          'node' => array(
            'table' => 'node',
            'columns' => array(
              'target_id' => 'nid',
            ),
          ),
        ),
        'indexes' => array(
          'target_id' => array(
            0 => 'target_id',
          ),
        ),
        'settings' => array(
          'target_type' => 'node',
          'handler' => 'og',
          'handler_settings' => array(
            'target_bundles' => array(
              'extranet' => 'extranet',
              'group' => 'group',
              'organisation' => 'organisation',
              'public' => 'public',
            ),
            'sort' => array(
              'type' => 'none',
            ),
            'membership_type' => 'og_membership_type_default',
            'behaviors' => array(
              'og_behavior' => array(
                'status' => TRUE,
              ),
              'views-select-list' => array(
                'status' => 0,
              ),
            ),
          ),
          'handler_submit' => 'Change handler',
        ),
        'translatable' => '0',
        'storage' => array(
          'type' => 'field_sql_storage',
          'settings' => array(),
          'module' => 'field_sql_storage',
          'active' => '1',
          'details' => array(
            'sql' => array(
              'FIELD_LOAD_CURRENT' => array(
                'field_data_og_user_node' => array(
                  'target_id' => 'og_user_node_target_id',
                ),
              ),
              'FIELD_LOAD_REVISION' => array(
                'field_revision_og_user_node' => array(
                  'target_id' => 'og_user_node_target_id',
                ),
              ),
            ),
          ),
        ),
        'field_name' => 'og_user_node',
        'type' => 'entityreference',
        'module' => 'entityreference',
        'active' => '1',
        'locked' => '0',
        'cardinality' => '-1',
        'deleted' => '0',
        'columns' => array(
          'target_id' => array(
            'description' => 'The id of the target entity.',
            'type' => 'int',
            'unsigned' => TRUE,
            'not null' => TRUE,
          ),
        ),
        'bundles' => array(
          'user' => array(
            0 => 'user',
          ),
        ),
      ),
    ),
    'instances' => array(
      'field_birthdate' => array(
        0 => array(
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '29',
              'settings' => array(),
            ),
            'search_index' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '29',
              'settings' => array(),
            ),
          ),
          'label' => 'Birthdate',
          'required' => 0,
          'settings' => array(
            'default_value' => 'blank',
            'default_value2' => 'same',
            'default_value_code' => '',
            'default_value_code2' => '',
            'user_register_form' => 1,
          ),
          'widget' => array(
            'active' => 1,
            'module' => 'date',
            'settings' => array(
              'display_all_day' => 0,
              'increment' => 30,
              'input_format' => 'm/d/Y - H:i:s',
              'input_format_custom' => '',
              'label_position' => 'none',
              'text_parts' => array(),
              'year_range' => '1900:+0',
            ),
            'type' => 'date_popup',
            'weight' => '33',
          ),
          'field_name' => 'field_birthdate',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'field_format' => array(
        0 => array(
          'label' => 'Format/Type',
          'widget' => array(
            'weight' => '34',
            'type' => 'options_select',
            'module' => 'options',
            'active' => 1,
            'settings' => array(
              'apply_chosen' => '',
            ),
          ),
          'settings' => array(
            'user_register_form' => 0,
          ),
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '30',
              'settings' => array(),
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'taxonomy_term_reference_link',
              'weight' => '0',
              'settings' => array(),
              'module' => 'taxonomy',
            ),
          ),
          'required' => 0,
          'description' => '',
          'default_value' => array(
            0 => array(
              'tid' => '19',
            ),
          ),
          'field_name' => 'field_format',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'field_hobbies' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '4',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'module' => 'i18n_taxonomy',
              'settings' => array(
                'edit' => array(
                  'editor' => 'form',
                ),
                'quickedit' => array(
                  'editor' => 'form',
                ),
              ),
              'type' => 'i18n_taxonomy_term_reference_link',
              'weight' => 10,
            ),
            'search_index' => array(
              'label' => 'above',
              'type' => 'taxonomy_term_reference_link',
              'weight' => '3',
              'settings' => array(),
              'module' => 'taxonomy',
            ),
          ),
          'label' => 'Hobbies',
          'required' => 0,
          'settings' => array(
            'user_register_form' => 0,
          ),
          'widget' => array(
            'active' => 1,
            'module' => 'options',
            'settings' => array(
              'apply_chosen' => '',
            ),
            'type' => 'options_select',
            'weight' => '29',
          ),
          'field_name' => 'field_hobbies',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'field_interests' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '3',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'module' => 'i18n_taxonomy',
              'settings' => array(
                'edit' => array(
                  'editor' => 'form',
                ),
                'quickedit' => array(
                  'editor' => 'form',
                ),
              ),
              'type' => 'i18n_taxonomy_term_reference_link',
              'weight' => 11,
            ),
            'search_index' => array(
              'label' => 'above',
              'type' => 'taxonomy_term_reference_link',
              'weight' => '2',
              'settings' => array(),
              'module' => 'taxonomy',
            ),
          ),
          'label' => 'Interests',
          'required' => 0,
          'settings' => array(
            'user_register_form' => 0,
          ),
          'widget' => array(
            'active' => 0,
            'module' => 'taxonomy',
            'settings' => array(
              'autocomplete_path' => 'taxonomy/autocomplete',
              'size' => 60,
            ),
            'type' => 'taxonomy_autocomplete',
            'weight' => '30',
          ),
          'field_name' => 'field_interests',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'field_skills' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '1',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'module' => 'i18n_taxonomy',
              'settings' => array(
                'edit' => array(
                  'editor' => 'form',
                ),
                'quickedit' => array(
                  'editor' => 'form',
                ),
              ),
              'type' => 'i18n_taxonomy_term_reference_link',
              'weight' => 12,
            ),
            'search_index' => array(
              'label' => 'above',
              'type' => 'taxonomy_term_reference_link',
              'weight' => '1',
              'settings' => array(),
              'module' => 'taxonomy',
            ),
          ),
          'label' => 'Skills',
          'required' => 0,
          'settings' => array(
            'user_register_form' => 0,
          ),
          'widget' => array(
            'active' => 0,
            'module' => 'taxonomy',
            'settings' => array(
              'autocomplete_path' => 'taxonomy/autocomplete',
              'size' => 60,
            ),
            'type' => 'taxonomy_autocomplete',
            'weight' => '31',
          ),
          'field_name' => 'field_skills',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'is_broadcaster' => array(
        0 => array(
          'widget' => array(
            'weight' => '3',
            'type' => 'options_onoff',
            'module' => 'options',
            'active' => 1,
            'settings' => array(
              'display_label' => 1,
            ),
          ),
          'settings' => array(
            'user_register_form' => 1,
          ),
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'list_default',
              'settings' => array(),
              'module' => 'list',
              'weight' => 31,
            ),
            'search_index' => array(
              'type' => 'hidden',
              'label' => 'above',
              'settings' => array(),
              'weight' => 0,
            ),
          ),
          'required' => 0,
          'label' => 'Broadcaster',
          'description' => 'Flags the user as a "broadcaster". Broadcaster are allowed to broadcast any content they can access in <em>any</em> spaces including spaces in which they are not a member, regardless of their roles and permissions.',
          'default_value' => array(
            0 => array(
              'value' => 0,
            ),
          ),
          'field_name' => 'is_broadcaster',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'is_extranet' => array(
        0 => array(
          'widget' => array(
            'weight' => '2',
            'type' => 'options_onoff',
            'module' => 'options',
            'active' => 1,
            'settings' => array(
              'display_label' => 1,
            ),
          ),
          'settings' => array(
            'user_register_form' => 1,
          ),
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '0',
              'settings' => array(),
            ),
            'search_index' => array(
              'type' => 'hidden',
              'label' => 'above',
              'settings' => array(),
              'weight' => 0,
            ),
          ),
          'required' => 0,
          'label' => 'Extranet user',
          'description' => 'Flags the user as an "extranet" (or external) user. Depending on global settings, administrators can revoke permissions to extranet users so they can\'t access non-extranet spaces regardless of their roles.',
          'default_value' => array(
            0 => array(
              'value' => 0,
            ),
          ),
          'field_name' => 'is_extranet',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_current_dn' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => 'ldap_user_dn_default',
          'description' => 'May change when user\'s DN changes. This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '19',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 3,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 3,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '19',
              'settings' => array(),
            ),
          ),
          'label' => 'User LDAP DN',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '14',
          ),
          'field_name' => 'ldap_user_current_dn',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_departmentnumber' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '6',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '6',
              'settings' => array(),
            ),
          ),
          'label' => 'Department',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '26',
          ),
          'field_name' => 'ldap_user_departmentnumber',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_description' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '2',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 9,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '4',
              'settings' => array(),
            ),
          ),
          'label' => 'About Me',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'active' => 1,
            'module' => 'text',
            'settings' => array(
              'rows' => 5,
            ),
            'type' => 'text_textarea',
            'weight' => '28',
          ),
          'field_name' => 'ldap_user_description',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_displayname' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '28',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '27',
              'settings' => array(),
            ),
          ),
          'label' => 'Display name',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '20',
          ),
          'field_name' => 'ldap_user_displayname',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_givenname' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '23',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '23',
              'settings' => array(),
            ),
          ),
          'label' => 'Firstname',
          'required' => TRUE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '18',
          ),
          'field_name' => 'ldap_user_givenname',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_last_checked' => array(
        0 => array(
          'default_value' => NULL,
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '16',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 5,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 5,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '16',
              'settings' => array(),
            ),
          ),
          'label' => 'Unix timestamp of when Drupal user was compard to ldap entry.  This could be for purposes of synching, deleteing drupal account, etc.',
          'required' => 0,
          'settings' => array(
            'max' => '',
            'min' => '',
            'prefix' => '',
            'suffix' => '',
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '16',
          ),
          'field_name' => 'ldap_user_last_checked',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_ldap_exclude' => array(
        0 => array(
          'default_value' => 0,
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '17',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 6,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 6,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '17',
              'settings' => array(),
            ),
          ),
          'label' => 'Whether to exclude the user from LDAP functionality',
          'required' => 0,
          'settings' => array(
            'max' => '',
            'min' => '',
            'prefix' => '',
            'suffix' => '',
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '17',
          ),
          'field_name' => 'ldap_user_ldap_exclude',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_manager' => array(
        0 => array(
          'widget' => array(
            'weight' => '27',
            'type' => 'text_textfield',
            'module' => 'text',
            'active' => 1,
            'settings' => array(
              'size' => '60',
            ),
          ),
          'settings' => array(
            'text_processing' => '0',
            'user_register_form' => 1,
          ),
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'text_default',
              'settings' => array(),
              'module' => 'text',
              'weight' => 32,
            ),
            'search_index' => array(
              'type' => 'hidden',
              'label' => 'above',
              'settings' => array(),
              'weight' => 0,
            ),
          ),
          'required' => 0,
          'label' => 'Manager',
          'description' => '',
          'default_value' => NULL,
          'field_name' => 'ldap_user_manager',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_mobile' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '5',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '15',
              'settings' => array(),
            ),
          ),
          'label' => 'Mobile phone number',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '25',
          ),
          'field_name' => 'ldap_user_mobile',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_o' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '22',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '22',
              'settings' => array(),
            ),
          ),
          'label' => 'Company',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '23',
          ),
          'field_name' => 'ldap_user_o',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_ou' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '27',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'list',
              'settings' => array(
                'edit' => array(
                  'editor' => 'form',
                ),
                'quickedit' => array(
                  'editor' => 'form',
                ),
              ),
              'type' => 'list_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '26',
              'settings' => array(),
            ),
          ),
          'label' => 'Main space',
          'required' => 0,
          'settings' => array(
            'user_register_form' => 1,
          ),
          'widget' => array(
            'weight' => '21',
            'type' => 'options_select',
            'module' => 'options',
            'active' => 1,
            'settings' => array(),
          ),
          'field_name' => 'ldap_user_ou',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_prov_entries' => array(
        0 => array(
          'default_value' => NULL,
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '18',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 4,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 4,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '18',
              'settings' => array(),
            ),
          ),
          'label' => 'LDAP Entries that have been provisioned from this Drupal user.',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '15',
          ),
          'field_name' => 'ldap_user_prov_entries',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_puid' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => 'ldap_user_puid_default',
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '20',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 1,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 1,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '20',
              'settings' => array(),
            ),
          ),
          'label' => 'Value of user\'s permanent unique id.  This should never change for a given ldap identified user.',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '12',
          ),
          'field_name' => 'ldap_user_puid',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_puid_property' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => 'ldap_user_puid_property_default',
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '21',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 2,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 2,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '21',
              'settings' => array(),
            ),
          ),
          'label' => 'Property specified as user\'s puid.',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '13',
          ),
          'field_name' => 'ldap_user_puid_property',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_puid_sid' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => 'ldap_user_provisioned_sid_default',
          'description' => 'This field should not be edited.',
          'display' => array(
            'default' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '14',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'teaser' => array(
              'label' => 'hidden',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'hidden',
              'type' => 'hidden',
              'weight' => '5',
              'settings' => array(),
            ),
          ),
          'label' => 'LDAP Server ID that puid was derived from.  NULL if puid is independent of server configuration instance.',
          'required' => 0,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => FALSE,
          ),
          'widget' => array(
            'module' => 'ldap_user',
            'settings' => array(),
            'type' => 'ldap_user_hidden',
            'weight' => '11',
          ),
          'field_name' => 'ldap_user_puid_sid',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_sn' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '26',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '28',
              'settings' => array(),
            ),
          ),
          'label' => 'Lastname',
          'required' => TRUE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '19',
          ),
          'field_name' => 'ldap_user_sn',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_telephonenumber' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '15',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '14',
              'settings' => array(),
            ),
          ),
          'label' => 'Phone number',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '24',
          ),
          'field_name' => 'ldap_user_telephonenumber',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'ldap_user_title' => array(
        0 => array(
          'default_value' => NULL,
          'default_value_function' => '',
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '25',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'inline',
              'module' => 'text',
              'settings' => array(
                'edit' => array(
                  'editor' => 'plain_text',
                ),
                'quickedit' => array(
                  'editor' => 'plain_text',
                ),
              ),
              'type' => 'text_default',
              'weight' => 0,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '25',
              'settings' => array(),
            ),
          ),
          'label' => 'Title',
          'required' => FALSE,
          'settings' => array(
            'text_processing' => 0,
            'user_register_form' => 1,
          ),
          'widget' => array(
            'module' => 'text',
            'settings' => array(
              'size' => 60,
            ),
            'type' => 'text_textfield',
            'weight' => '22',
          ),
          'field_name' => 'ldap_user_title',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'og_private' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '7',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'settings' => array(),
              'type' => 'hidden',
              'weight' => 13,
            ),
            'search_index' => array(
              'label' => 'inline',
              'type' => 'hidden',
              'weight' => '7',
              'settings' => array(),
            ),
          ),
          'label' => 'Private Space',
          'required' => 0,
          'settings' => array(
            'behaviors' => array(
              'og_widget' => array(
                'access_override' => 0,
                'admin' => array(
                  'widget_type' => 'entityreference_autocomplete',
                ),
                'default' => array(
                  'widget_type' => 'options_select',
                ),
                'status' => TRUE,
              ),
            ),
            'user_register_form' => 0,
          ),
          'view modes' => array(
            'full' => array(
              'custom settings' => FALSE,
              'label' => 'Full',
              'type' => 'og_list_default',
            ),
            'teaser' => array(
              'custom settings' => FALSE,
              'label' => 'Teaser',
              'type' => 'og_list_default',
            ),
          ),
          'widget' => array(
            'active' => 0,
            'module' => 'og',
            'settings' => array(),
            'type' => 'og_complex',
            'weight' => '32',
          ),
          'field_name' => 'og_private',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
      'og_user_node' => array(
        0 => array(
          'default_value' => NULL,
          'description' => '',
          'display' => array(
            'default' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '8',
              'settings' => array(),
            ),
            'full' => array(
              'label' => 'above',
              'module' => 'og_ui',
              'settings' => array(
                'edit' => array(
                  'editor' => 'form',
                ),
                'quickedit' => array(
                  'editor' => 'form',
                ),
              ),
              'type' => 'og_list_default',
              'weight' => 7,
            ),
            'search_index' => array(
              'label' => 'above',
              'type' => 'hidden',
              'weight' => '8',
              'settings' => array(),
            ),
          ),
          'label' => 'Group membership',
          'required' => 0,
          'settings' => array(
            'behaviors' => array(
              'og_widget' => array(
                'status' => TRUE,
                'default' => array(
                  'widget_type' => 'options_select',
                ),
                'admin' => array(
                  'widget_type' => 'entityreference_autocomplete',
                ),
                'access_override' => 1,
              ),
            ),
            'user_register_form' => 1,
          ),
          'view modes' => array(
            'full' => array(
              'custom settings' => FALSE,
              'label' => 'Full',
              'type' => 'og_list_default',
            ),
            'teaser' => array(
              'custom settings' => FALSE,
              'label' => 'Teaser',
              'type' => 'og_list_default',
            ),
          ),
          'widget' => array(
            'weight' => '9',
            'type' => 'og_complex',
            'module' => 'og',
            'active' => 0,
            'settings' => array(),
          ),
          'field_name' => 'og_user_node',
          'entity_type' => 'user',
          'bundle' => 'user',
          'deleted' => '0',
        ),
      ),
    ),
  );
}