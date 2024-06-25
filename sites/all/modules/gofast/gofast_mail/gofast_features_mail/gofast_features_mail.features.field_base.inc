<?php

/**
 * @file
 * gofast_features_mail.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function gofast_features_mail_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_arrival_departure_date'.
  $field_bases['field_arrival_departure_date'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_arrival_departure_date',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Date and time of arrival/departure of the mail',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_arrival_departure_link'.
  $field_bases['field_arrival_departure_link'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_arrival_departure_link',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Arrival / Departure Link',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_impute_to'.
  $field_bases['field_impute_to'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_impute_to',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Impute',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_instruction'.
  $field_bases['field_mail_instruction'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_instruction',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Mail instruction',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_object'.
  $field_bases['field_mail_object'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_object',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Mail Object',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_rid'.
  $field_bases['field_mail_rid'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_rid',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Mail reference ID',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_sender'.
  $field_bases['field_mail_sender'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_sender',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Mail sender',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_subspace_nid'.
  $field_bases['field_mail_subspace_nid'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_subspace_nid',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mail_ulid'.
  $field_bases['field_mail_ulid'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mail_ulid',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_mandatory_answer'.
  $field_bases['field_mandatory_answer'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mandatory_answer',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Mandatory answer',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_service_recipient'.
  $field_bases['field_service_recipient'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_service_recipient',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'Service / Direction recipient',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_user_recipient'.
  $field_bases['field_user_recipient'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_user_recipient',
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'label' => 'User recipient',
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
