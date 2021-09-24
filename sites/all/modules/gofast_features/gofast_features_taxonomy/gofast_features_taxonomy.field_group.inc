<?php
/**
 * @file
 * gofast_features_taxonomy.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gofast_features_taxonomy_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomies|node|alfresco_item|form';
  $field_group->group_name = 'group_taxonomies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'alfresco_item';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Attributes',
    'weight' => '28',
    'children' => array(
      0 => 'field_category',
      1 => 'field_format',
      2 => 'field_tags',
      3 => 'field_criticity',
      4 => 'field_document_author',
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
  $field_groups['group_taxonomies|node|alfresco_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomies|node|article|form';
  $field_group->group_name = 'group_taxonomies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'article';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Attributes',
    'weight' => '20',
    'children' => array(
      0 => 'field_category',
      1 => 'field_format',
      2 => 'field_tags',
      3 => 'field_criticity',
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
  $field_groups['group_taxonomies|node|article|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_taxonomies|node|forum|form';
  $field_group->group_name = 'group_taxonomies';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'forum';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_vt_document';
  $field_group->data = array(
    'label' => 'Attributes',
    'weight' => '12',
    'children' => array(
      0 => 'field_format',
      1 => 'field_tags',
      2 => 'field_category',
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
  $field_groups['group_taxonomies|node|forum|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Attributes');

  return $field_groups;
}
