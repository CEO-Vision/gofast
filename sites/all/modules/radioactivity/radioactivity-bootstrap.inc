<?php

/**
 * This file is used both in drupal and in callback files.
 */

define('VAR_RADIOACTIVITY_DRUPAL_ROOT_DEPTH_LIMIT', 10);

// prepare variables
if (!defined("DRUPAL_ROOT")) {
  // We're not in drupal but we need 'some' functionality so...
  _radioactivity_light_initialization();
}
else {
  // We're in drupal, setup necessary vars
  define("VAR_RADIOACTIVITY_CHECKSUM_SALT", variable_get("radioactivity_checksum_salt", "undefined"));
  define("VAR_RADIOACTIVITY_TEMP_DIR", variable_get('radioactivity_temp_dir', sys_get_temp_dir()));
  if (class_exists('Memcache') || class_exists("Memcached")) {
    define("VAR_RADIOACTIVITY_MEMCACHED_HOST", variable_get("radioactivity_memcached_host", "localhost"));
    define("VAR_RADIOACTIVITY_MEMCACHED_PORT", variable_get("radioactivity_memcached_port", "11211"));
    define("VAR_RADIOACTIVITY_MEMCACHED_PREFIX", variable_get("radioactivity_memcached_prefix", ""));
  }
  if (class_exists("Redis")) {
    define("VAR_RADIOACTIVITY_REDIS_HOST", variable_get("radioactivity_redis_host", "localhost"));
    define("VAR_RADIOACTIVITY_REDIS_PORT", variable_get("radioactivity_redis_port", "6379"));
  }
}

/**
 * Get the config file path of R
 */
function _radioactivity_get_config_file_path() {
  $dir = dirname(__FILE__);
  $config_file = $dir . "/radioactivity-bootstrap.cfg.inc";
  return $config_file;
}

/**
 * Do a light system initialization
 */
function _radioactivity_light_initialization() {
  if (!defined("RADIOACTIVITY_BOOTSTRAPPED")) {

    $config_file = _radioactivity_get_config_file_path();

    if (file_exists($config_file)) {

      include ($config_file);

    }
    else {

      _radioactivity_require_bootstrapping();
      // Grab the checksum variable
      $var = variable_get('radioactivity_checksum_salt', 'undefined');
      define("VAR_RADIOACTIVITY_CHECKSUM_SALT", $var);
      define("VAR_RADIOACTIVITY_TEMP_DIR", variable_get('radioactivity_temp_dir', sys_get_temp_dir()));
      if (!variable_get('radioactivity_config_warning')) {
        variable_set("radioactivity_config_warning", TRUE);
      }
      if (class_exists('Memcache') || class_exists("Memcached")) {
        define("VAR_RADIOACTIVITY_MEMCACHED_HOST", variable_get("radioactivity_memcached_host", "localhost"));
        define("VAR_RADIOACTIVITY_MEMCACHED_PORT", variable_get("radioactivity_memcached_port", "11211"));
        define("VAR_RADIOACTIVITY_MEMCACHED_PREFIX", variable_get("radioactivity_memcached_prefix", ""));
      }
      if (class_exists("Redis")) {
        define("VAR_RADIOACTIVITY_REDIS_HOST", variable_get("radioactivity_redis_host", "localhost"));
        define("VAR_RADIOACTIVITY_REDIS_PORT", variable_get("radioactivity_redis_port", "6379"));
      }
    }

    define("RADIOACTIVITY_BOOTSTRAPPED", TRUE);
  }
}

/**
 * Do a light boostrap
 */
function _radioactivity_require_bootstrapping() {
  // use the VERSION to figure out if we've done bootstrapping already
  if (!defined("VERSION")) {

    include "radioactivity.module";

    if (defined("VAR_RADIOACTIVITY_DRUPAL_ROOT")) {
      define('DRUPAL_ROOT', VAR_RADIOACTIVITY_DRUPAL_ROOT);
      chdir(DRUPAL_ROOT);
    }
    else {
      // Look up Drupal root directory.
      $depth = 0;
      do {
        chdir('../');
        if (file_exists('./includes/bootstrap.inc')) {
          define('DRUPAL_ROOT', getcwd());
          break;
        }
        $depth++;
      } while ($depth < VAR_RADIOACTIVITY_DRUPAL_ROOT_DEPTH_LIMIT);
    }

    if (!file_exists('./includes/bootstrap.inc')) {
      die("Unable to figure out bootstrapping directory!");
    }

    require_once './includes/bootstrap.inc';
    drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
    if (!variable_get('radioactivity_bootstrap_warning')) {
      variable_set("radioactivity_bootstrap_warning", TRUE);
    }
  }
}

/**
 * Internal function to filter nested arrays().
 * @param type $array
 */
function _radioactivity_filter_nested_array($array) {
  return !is_array($array) ? TRUE : FALSE;
}

/**
 * Generate a checksum for given data
 */
function _radioactivity_checksum_generate($data) {
  $temp = array_filter($data, "_radioactivity_filter_nested_array");
  unset($temp['checksum']);
  ksort($temp);
  $temp = join(',', $temp);
  return md5(VAR_RADIOACTIVITY_CHECKSUM_SALT . $temp);
}

/**
 * Validate checksum against given data
 */
function _radioactivity_checksum_validate($data, $checksum) {
  return strcmp(_radioactivity_checksum_generate($data), $checksum) === 0;
}

/**
 * Validate (and filter) a payload
 */
function _radioactivity_validate_incident($incident) {
  return _radioactivity_checksum_validate($incident, $incident['checksum']);
}

/**
 * Prepare payload
 */
function _radioactivity_prepare_incident($incident) {
  ksort($incident);
  $incident['checksum'] = _radioactivity_checksum_generate($incident);
  return $incident;
}
