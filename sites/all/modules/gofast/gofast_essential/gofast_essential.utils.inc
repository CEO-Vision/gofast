<?php

/**
 * Check if the current version of gofast for the current user
 *
 * @return bool $is_essential
 */
function gofast_essential_is_essential()
{
  global $user;
  $detect = new Mobile_Detect();

  $account = user_load($user->uid);

  $is_essential = FALSE;

  if($account->field_version[LANGUAGE_NONE][0]['value'] == "Essential" || $detect->isTablet()){
    $is_essential = TRUE;

  }

  // Implements hook_gofast_essential_is_essential_alter().
  foreach (module_implements("essential_is_essential_alter") as $module) {
    $is_essential_state = call_user_func($module . "_essential_is_essential_alter");
    if ($is_essential_state != 'skip') {
      // convert the string to boolean
      $is_essential = filter_var($is_essential_state, FILTER_VALIDATE_BOOLEAN);
    }
  }

  return $is_essential;
}
