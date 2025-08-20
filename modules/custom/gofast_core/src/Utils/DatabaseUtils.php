<?php

namespace Drupal\gofast_core\Utils;

/**
 * Core reusable logic for Drupal database alterations.
 *
 * @package Drupal\gofast_core\Utils
 */
class DatabaseUtils {
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
      self::$logger = \Drupal::logger('gofast_core');
    }
  }

  /**
   * Sets the auto-increment value for a specified table.
   *
   * @param string $table_name
   *   The name of the table to adjust.
   * @param int $start_value
   *   The starting value for auto-increment.
   */
  public static function setAutoIncrementValue($table_name, $start_value) {
    self::initialize();

    self::$logger->info('Setting auto-increment value for table @table to @value', [
      '@table' => $table_name,
      '@value' => $start_value,
    ]);

    $escaped_table_name = \Drupal::database()->escapeTable($table_name);
    $query = "ALTER TABLE {" . $escaped_table_name . "} AUTO_INCREMENT = $start_value";
    \Drupal::database()->query($query);
  }

}
