<?php
/**
 * @file
 * gofast_features_global.radioactivity_decay_profile.inc
 */

/**
 * Implements hook_default_radioactivity_decay_profile().
 */
function gofast_features_global_default_radioactivity_decay_profile() {
  $export = array();

  $radioactivity_decay_profile = new stdClass();
  $radioactivity_decay_profile->disabled = FALSE; /* Edit this to true to make a default radioactivity_decay_profile disabled initially */
  $radioactivity_decay_profile->api_version = 1;
  $radioactivity_decay_profile->machine_name = 'scoring';
  $radioactivity_decay_profile->name = 'Scoring';
  $radioactivity_decay_profile->description = '';
  $radioactivity_decay_profile->enable_decay = 2;
  $radioactivity_decay_profile->granularity = '600';
  $radioactivity_decay_profile->half_life = 345600;
  $radioactivity_decay_profile->cut_off = '0.5';
  $radioactivity_decay_profile->storage = 'Deferred';
  $export['scoring'] = $radioactivity_decay_profile;

  return $export;
}
