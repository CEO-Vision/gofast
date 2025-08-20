<?php

namespace Drupal\gofast_og\Utils;

use Drupal\Core\Language\LanguageInterface;
use Drupal\group\Entity\Group;

/**
 * Class MembershipUtils.
 *
 * @package Drupal\gofast_og\Utils
 */
class MembershipUtilsD7 {
  /**
   * The logger.
   *
   * @var \Drupal::logger
   */
  private static $logger;

  /**
   * Initialize static properties.
   */
  private static function initialize() {
    if (!isset(self::$logger)) {
      self::$logger = \Drupal::logger('gofast_og');
    }
  }

  /**
   * Adds a ghost membership entry for an entity in a group.
   *
   * @param string $entity_type
   *   The type of the entity (e.g., 'node').
   * @param int $entity_id
   *   The ID of the entity to be added to the group.
   * @param int $group_id
   *   The ID of the group where the entity should be added.
   *   This can be a (yet) non-existent group ID for a ghost entry.
   */
  public static function addGhostMembership($entity_type, $entity_id, $group_id) {
    self::initialize();

    // Load the entity, make sure it exists.
    $storage = \Drupal::entityTypeManager()->getStorage($entity_type);
    $entity = $storage->load($entity_id);
    if (!$entity) {
      return FALSE;
    }

    self::$logger->info('Adding ghost membership: entity_type=@type, entity_id=@id, group_id=@gid', [
      '@type' => $entity_type,
      '@id' => $entity_id,
      '@gid' => $group_id,
    ]);

    // Depending on the entity type and bundle, set the membership type.
    $plugin_id = "group_membership";
    $membership_type = "organic_group-group_membership";
    if ($entity_type == "node") {
      $bundle = $entity->bundle();
      $plugin_id = "group_node:$bundle";
      $membership_type = "organic_group-group_node-$bundle";
    }

    // Get relationship ID.
    try {
      $transaction = \Drupal::database()->startTransaction();
      $query = \Drupal::database()
        ->select('group_relationship', 'gr')
        ->fields('gr', ['id'])
        ->orderBy('id', 'DESC')
        ->range(0, 1);
      $highest_id = $query->execute()->fetchField();
      $relationship_id = $highest_id ? $highest_id + 1 : 1;

      $uuid_service = \Drupal::service('uuid');
      $uuid = $uuid_service->generate();

      // Insert relationship.
      $values = [
        'id' => $relationship_id,
        'type' => $membership_type,
        'uuid' => $uuid,
        'langcode' => LanguageInterface::LANGCODE_NOT_SPECIFIED,
      ];
      \Drupal::database()->insert('group_relationship')->fields($values)->execute();

      // Insert relationship data.
      $values = [
        'id' => $relationship_id,
        'entity_id' => $entity->id(),
        'label' => $entity->label(),
        'plugin_id' => $plugin_id,
        'type' => $membership_type,
        'group_type' => "organic_group",
        'gid' => $group_id,
        'uid' => \Drupal::currentUser()->id(),
        'created' => \Drupal::time()->getRequestTime(),
        'changed' => \Drupal::time()->getRequestTime(),
        'langcode' => LanguageInterface::LANGCODE_NOT_SPECIFIED,
        'default_langcode' => 1,
      ];
      \Drupal::database()->insert('group_relationship_field_data')->fields($values)->execute();
    }
    catch (\Exception $e) {
      // Rollback the transaction.
      $transaction->rollback();
      self::$logger->error('Failed to add ghost membership: @message', [
        '@message' => $e->getMessage(),
      ]);
      throw $e;
    }

    self::$logger->info('Ghost membership added: entity_type=@type, entity_id=@id, group_id=@gid', [
      '@type' => $entity_type,
      '@id' => $entity_id,
      '@gid' => $group_id,
    ]);
  }

  /**
   * Creates a group with a specific ID.
   *
   * @param string $group_name
   *   The name of the group to be created.
   * @param int $group_id
   *   The ID to be assigned to the group.
   *
   * @throws \Exception
   *   Throws exception if the group could not be created or saved.
   */
  public static function createGroupWithId($group_name, $group_id) {
    self::initialize();

    self::$logger->info('Creating group: group_name=@name, group_id=@id', [
      '@name' => $group_name,
      '@id' => $group_id,
    ]);

    try {
      $transaction = \Drupal::database()->startTransaction();

      $group = Group::create([
        'type' => "organic_group",
        'label' => $group_name,
      ]);
      // Bypass normal save operation to set the ID directly.
      $group->enforceIsNew();
      $group->set('id', $group_id);
      $group->save();

      self::$logger->info('Group created: group_name=@name, group_id=@id', [
        '@name' => $group_name,
        '@id' => $group_id,
      ]);
    }
    catch (\Exception $e) {
      // Rollback the transaction.
      $transaction->rollback();
      self::$logger->error('Failed to create group: @message', [
        '@message' => $e->getMessage(),
      ]);
      throw $e;
    }
  }

}
