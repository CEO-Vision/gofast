<?php


/**
 * Implements hook_date_format_types().
 */
function gofast_date_format_types() {
  return array(
    'privatemsg_current_day' => 'Privatemsg: Current day',
    'privatemsg_current_year' => 'Privatemsg: Current year',
    'privatemsg_years' => 'Privatemsg: Other years',
    'short_without_hours' => 'Short without hours',
    'extra_short' => 'Extra short',
  );
}


/**
 * Implements hook_date_formats().
 */
function gofast_date_formats() {
  
  $formats = array();
  $formats[] = array(
    'type' => 'long',
    'format' => 'l, j F, Y - H:i',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'long',
    'format' => 'l, F j, Y - g:ia',
    'locales' => array('nl', 'en'),
  );
  $formats[] = array(
    'type' => 'medium',
    'format' => 'D, d/m/Y - H:i',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'medium',
    'format' => 'D, m/d/Y - g:ia',
    'locales' => array('nl', 'en'),
  );
  $formats[] = array(
    'type' => 'short',
    'format' => 'd/m/Y - H:i',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'short',
    'format' => 'm/d/Y - g:ia',
    'locales' => array('nl','en'),
  );
  $formats[] = array(
    'type' => 'privatemsg_current_day',
    'format' => 'H:i',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'privatemsg_current_day',
    'format' => 'g:i a',
    'locales' => array('nl','en'),
  );
  $formats[] = array(
    'type' => 'privatemsg_current_year',
    'format' => 'j M',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'privatemsg_current_year',
    'format' => 'M j',
    'locales' => array('nl', 'en'),
  );
  $formats[] = array(
    'type' => 'privatemsg_years',
    'format' => 'd/m/y',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'privatemsg_years',
    'format' => 'm/d/y',
    'locales' => array('nl', 'en'),
  );
  $formats[] = array(
    'type' => 'short_without_hours',
    'format' => 'd/m/Y',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'short_without_hours',
    'format' => 'm/d/Y',
    'locales' => array('nl', 'en'),
  );
  $formats[] = array(
    'type' => 'extra_short',
    'format' => 'd/m/y - H:i',
    'locales' => array('fr'),
  );
  $formats[] = array(
    'type' => 'extra_short',
    'format' => 'm/d/y - H:i',
    'locales' => array('nl', 'en'),
  );
  return $formats;
}


/**
 * Enforce setting of default date_format per type and per language
 */
function gofast_set_default_date_formats(){
    
  $date_formats = module_invoke('gofast', 'date_formats');
  foreach ($date_formats as $date_format) {
    foreach ($date_format['locales'] as $locale) {
      if (drupal_multilingual()) {
        locale_date_format_save($locale, $date_format['type'], $date_format['format']);
      }
    }
  }
}