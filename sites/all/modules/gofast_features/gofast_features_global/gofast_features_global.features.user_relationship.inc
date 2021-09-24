<?php
/**
 * @file
 * gofast_features_global.features.user_relationship.inc
 */

/**
 * Implements hook_user_relationships_default_relationships().
 */
function gofast_features_global_user_relationships_default_relationships() {
  $relationships = array();

  // Exported user_relationship style: relation.
  $relationships['relation'] = array(
    'machine_name' => 'relation',
    'name' => 'Relation',
    'plural_name' => 'Relations',
    'is_oneway' => 0,
    'is_reciprocal' => 0,
    'requires_approval' => 1,
    'expires_val' => 0,
    'reverse_name' => '',
    'name_capitalized' => '',
    'plural_name_capitalized' => '',
    'reverse_name_capitalized' => '',
    'reverse_plural_name' => '',
    'reverse_plural_name_capitalized' => '',
  );

  return $relationships;
}
