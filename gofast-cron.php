<?php

 if (extension_loaded('newrelic')) { // Ensure PHP agent is available
            newrelic_background_job();
 }

/**
 * @file
 * Handles incoming requests to fire off regularly-scheduled tasks (cron jobs).
 */
if (!file_exists('includes/bootstrap.inc')) {
  if (!empty($_SERVER['DOCUMENT_ROOT']) && file_exists($_SERVER['DOCUMENT_ROOT'] . '/includes/bootstrap.inc')) {
    chdir($_SERVER['DOCUMENT_ROOT']);
  }
  elseif (preg_match('@^(.*)[\\\\/]sites[\\\\/][^\\\\/]+[\\\\/]modules[\\\\/]([^\\\\/]+[\\\\/])?elysia(_cron)?$@', getcwd(), $r) && file_exists($r[1] . '/includes/bootstrap.inc')) {
    chdir($r[1]);
  }
  else {
    die("Cron Fatal Error: Can't locate bootstrap.inc. Check cron.php position.");
  }
}

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_override_server_variables(array(
  'SCRIPT_NAME' => '/cron.php',
));
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// Override session for admin op.
global $user;
drupal_save_session(FALSE);
$user = user_load(1);

// If we need some custom behavior when running the cron, add '?manual' to the
// request to make use of the code chunk below.
// -> wget -O - -q -t 1 http://localhost/gofast-cron.php?manual
if (isset($_GET['manual'])) {
  watchdog('cron', '--- manual cron ---');
  // ...
}

/**
 * Hardcode the cron key so that watchdog does not log it for readability.
 */
$_GET['cron_key'] = variable_get('cron_key', '1URNGOZEA-hZBoG8PwC8rQEyayUKz-QuqTbSkwKV5HI');

if (!isset($_GET['cron_key']) || variable_get('cron_key', 'drupal') != $_GET['cron_key']) {
  watchdog('cron', 'Cron could not run because an invalid key was used.', array(), WATCHDOG_NOTICE);
  drupal_access_denied();
}
elseif (variable_get('maintenance_mode', 0)) {
  watchdog('cron', 'Cron could not run because the site is in maintenance mode.', array(), WATCHDOG_NOTICE);
  drupal_access_denied();
}
elseif (variable_get('current_config_community', FALSE) == TRUE) {
  watchdog('cron', 'Cron could not run because the GoFAST Community is in configuration');
  drupal_access_denied();
}
else {
  watchdog('cron', '--- begin cron run ---');
  if (function_exists('elysia_cron_run')) {
    elysia_cron_run();
  }
  else {
    drupal_cron_run();
  }
  watchdog('cron', '--- cron run ended ---');
}
