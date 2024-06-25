<?php
/**
 * @file
 * gofast_features_global.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gofast_features_global_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_body|node|alfresco_item|form';
  $field_group->group_name = 'group_body';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Summary',
    'weight' => '7',
    'children' => array(
      0 => 'body',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-body field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_body|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_book|node|forum|form';
  $field_group->group_name = 'group_book';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Book',
    'weight' => '17',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-book field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_book|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_book|node|webform|form';
  $field_group->group_name = 'group_book';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'book',
    'weight' => '42',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-book field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_book|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_container|node|task|form';
  $field_group->group_name = 'group_container';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'task';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'container',
    'weight' => '3',
    'children' => array(
      0 => 'group_row2',
      1 => 'group_row1',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'container',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'container gf-modal-container',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $field_groups['group_container|node|task|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_deadline|node|alfresco_item|form';
  $field_group->group_name = 'group_deadline';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Deadline',
    'weight' => '15',
    'children' => array(
      0 => 'field_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-deadline field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_deadline|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_deadline|node|article|form';
  $field_group->group_name = 'group_deadline';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Deadline',
    'weight' => '23',
    'children' => array(
      0 => 'field_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-deadline field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_deadline|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_deadline|node|forum|form';
  $field_group->group_name = 'group_deadline';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Deadline',
    'weight' => '16',
    'children' => array(
      0 => 'field_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-deadline field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_deadline|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_deadline|node|webform|form';
  $field_group->group_name = 'group_deadline';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Deadline',
    'weight' => '41',
    'children' => array(
      0 => 'field_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-deadline field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_deadline|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_empty_file|node|alfresco_item|form';
  $field_group->group_name = 'group_empty_file';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vertical_tab_input_file';
  $field_group->data = array(
    'label' => 'Create an empty file',
    'weight' => '33',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Create an empty file',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-empty-file field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_empty_file|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_external_links|node|alfresco_item|form';
  $field_group->group_name = 'group_external_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '13',
    'children' => array(
      0 => 'field_external_page_url',
      1 => 'field_target_link',
      2 => 'field_external_link_custom_data',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Links',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-external-links field-group-tab group-links',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_external_links|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_external_links|node|article|form';
  $field_group->group_name = 'group_external_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '21',
    'children' => array(
      0 => 'field_external_page_url',
      1 => 'field_target_link',
      2 => 'field_external_link_custom_data',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Links',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-links',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_external_links|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_external_links|node|forum|form';
  $field_group->group_name = 'group_external_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '15',
    'children' => array(
      0 => 'field_external_page_url',
      1 => 'field_external_link_custom_data',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-external-links field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_external_links|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_external_links|node|webform|form';
  $field_group->group_name = 'group_external_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Links',
    'weight' => '39',
    'children' => array(
      0 => 'field_external_page_url',
      1 => 'field_target_link',
      2 => 'field_external_link_custom_data',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-external-links field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_external_links|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gofast_sync|node|userlist|form';
  $field_group->group_name = 'group_gofast_sync';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'userlist';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Synchronisation avec GoFAST ▼',
    'weight' => '16',
    'children' => array(
      0 => 'field_is_gofast_sync',
      1 => 'field_gofast_filters',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Synchronisation avec GoFAST ▼',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'If you don\'t know how to configure this synchronisation, contact some business administrators or technical administrators, from <a href="/directory/users">users directory</a>
<br /><br />',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_gofast_sync|node|userlist|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_language|node|alfresco_item|form';
  $field_group->group_name = 'group_language';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Language',
    'weight' => '17',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-language field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_language|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_language|node|article|form';
  $field_group->group_name = 'group_language';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Language',
    'weight' => '25',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-language field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_language|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_language|node|forum|form';
  $field_group->group_name = 'group_language';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Language',
    'weight' => '18',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-language field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_language|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_language|node|webform|form';
  $field_group->group_name = 'group_language';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Language',
    'weight' => '43',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-language field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_language|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_ldap_sync|node|userlist|form';
  $field_group->group_name = 'group_ldap_sync';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'userlist';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'LDAP/AD Directory synchronization ▼',
    'weight' => '13',
    'children' => array(
      0 => 'field_base_dns',
      1 => 'field_filters',
      2 => 'field_is_ldap_sync',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'LDAP/AD Directory synchronization ▼',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => 'If you don\'t know how to configure this synchronisation, contact some business administrators or technical administrators, from <a href="/directory/users">users directory</a>
<br /><br />',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_ldap_sync|node|userlist|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_remote_url|node|alfresco_item|form';
  $field_group->group_name = 'group_remote_url';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vertical_tab_input_file';
  $field_group->data = array(
    'label' => 'Create from URL',
    'weight' => '34',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Create from URL',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-remote-url field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_remote_url|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_row1|node|task|form';
  $field_group->group_name = 'group_row1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'task';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_container';
  $field_group->data = array(
    'label' => 'row1',
    'weight' => '4',
    'children' => array(
      0 => 'field_date',
      1 => 'field_person_in_charge',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'row1',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'row',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
      'formatter' => '',
    ),
  );
  $field_groups['group_row1|node|task|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_row2|node|task|form';
  $field_group->group_name = 'group_row2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'task';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_container';
  $field_group->data = array(
    'label' => 'row2',
    'weight' => '7',
    'children' => array(
      0 => 'field_members',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => 'row2',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'row',
        'element' => 'div',
        'show_label' => '0',
        'label_element' => 'div',
        'attributes' => '',
      ),
      'formatter' => '',
    ),
  );
  $field_groups['group_row2|node|task|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomies|node|webform|form';
  $field_group->group_name = 'group_taxonomies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Attributes',
    'weight' => '38',
    'children' => array(
      0 => 'field_format',
      1 => 'field_category',
      2 => 'field_criticity',
      3 => 'field_tags',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-taxonomies field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_taxonomies|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_template_file|node|alfresco_item|form';
  $field_group->group_name = 'group_template_file';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vertical_tab_input_file';
  $field_group->data = array(
    'label' => 'Create from templates',
    'weight' => '32',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Create from templates',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-template-file field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_template_file|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_upload_file|node|alfresco_item|form';
  $field_group->group_name = 'group_upload_file';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vertical_tab_input_file';
  $field_group->data = array(
    'label' => 'Upload a file',
    'weight' => '31',
    'children' => array(),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Upload a file',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-upload-file field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_upload_file|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vertical_tab_input_file|node|alfresco_item|form';
  $field_group->group_name = 'group_vertical_tab_input_file';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'gofast_vertical_tab_input_file',
    'weight' => '2',
    'children' => array(
      0 => 'group_empty_file',
      1 => 'group_remote_url',
      2 => 'group_template_file',
      3 => 'group_upload_file',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-vertical-tab-input-file field-group-tabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_vertical_tab_input_file|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_document|node|alfresco_item|form';
  $field_group->group_name = 'group_vt_document';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'gofast_vertical_tabs_document',
    'weight' => '8',
    'children' => array(
      0 => 'group_book',
      1 => 'group_deadline',
      2 => 'group_external_links',
      3 => 'group_language',
      4 => 'group_vt_state',
      5 => 'group_taxonomies',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-vt-document field-group-tabs',
      ),
    ),
  );
  $field_groups['group_vt_document|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_document|node|article|form';
  $field_group->group_name = 'group_vt_document';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'gofast_vertical_tabs_document',
    'weight' => '4',
    'children' => array(
      0 => 'group_book',
      1 => 'group_deadline',
      2 => 'group_external_links',
      3 => 'group_language',
      4 => 'group_taxonomies',
      5 => 'group_vt_state',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-vt-document field-group-tabs',
      ),
    ),
  );
  $field_groups['group_vt_document|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_document|node|forum|form';
  $field_group->group_name = 'group_vt_document';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'gofast_vertical_tabs_document',
    'weight' => '4',
    'children' => array(
      0 => 'group_book',
      1 => 'group_deadline',
      2 => 'group_external_links',
      3 => 'group_language',
      4 => 'group_taxonomies',
      5 => 'group_vt_state',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-vt-document field-group-tabs',
      ),
    ),
  );
  $field_groups['group_vt_document|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_document|node|webform|form';
  $field_group->group_name = 'group_vt_document';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'gofast_vertical_tabs_document',
    'weight' => '4',
    'children' => array(
      0 => 'group_taxonomies',
      1 => 'group_external_links',
      2 => 'group_vt_state',
      3 => 'group_deadline',
      4 => 'group_book',
      5 => 'group_language',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-vt-document field-group-tabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_vt_document|node|webform|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_state|node|alfresco_item|form';
  $field_group->group_name = 'group_vt_state';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'state',
    'weight' => '14',
    'children' => array(
      0 => 'field_state',
      1 => 'field_validators',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'state',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-state field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_vt_state|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_state|node|article|form';
  $field_group->group_name = 'group_vt_state';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'state',
    'weight' => '22',
    'children' => array(
      0 => 'field_state',
      1 => 'field_validators',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'state',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-state field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_vt_state|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_state|node|forum|form';
  $field_group->group_name = 'group_vt_state';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'State',
    'weight' => '14',
    'children' => array(
      0 => 'field_validators',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'State',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-vt-state field-group-tab group-state',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_vt_state|node|forum|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_vt_state|node|webform|form';
  $field_group->group_name = 'group_vt_state';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'webform';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'state',
    'weight' => '40',
    'children' => array(
      0 => 'field_state',
      1 => 'field_validators',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-vt-state field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_vt_state|node|webform|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Attributes');
  t('Book');
  t('Create an empty file');
  t('Create from URL');
  t('Create from templates');
  t('Deadline');
  t('LDAP/AD Directory synchronization ▼');
  t('Language');
  t('Links');
  t('State');
  t('Summary');
  t('Synchronisation avec GoFAST ▼');
  t('Upload a file');
  t('book');
  t('container');
  t('gofast_vertical_tab_input_file');
  t('gofast_vertical_tabs_document');
  t('row1');
  t('row2');
  t('state');

  return $field_groups;
}
