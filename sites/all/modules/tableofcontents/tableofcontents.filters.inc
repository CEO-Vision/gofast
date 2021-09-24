<?php
/**
 * @file
 * Table of Contents - Versatile system for generating Tables of Contents for fields - filters.
 */

/**
 * Implements hook_filter_info().
 */
function _tableofcontents_filter_info() {
  $filters['filter_toc'] = array(
    'title' => t('Table of contents'),
    'description' => t('Inserts a table of contents in place of [toc ...] tags.'),
    'process callback' => 'tableofcontents_filter_process',
    'prepare callback' => 'tableofcontents_filter_prepare',
    'settings callback' => 'tableofcontents_filter_settings',
    'cache' => FALSE,
    'tips callback' => '_tableofcontents_filter_tips',
  );
  return $filters;
}

/**
 * Prepare the text for the table of content.
 *
 * Simply sorts out any pre-marked
 */
function _tableofcontents_filter_prepare($text, $filter, $format, $langcode, $cache, $cache_id) {
  if (!$text) {
    return $text;
  }

  // support for PEAR wiki (http://drupal.org/node/150067#comment-937519)
  $text = str_replace('[[TOC]]', '[toc]', $text);

  // And replace pre-set versions with our version
  return preg_replace_callback(
    array('%<!--\s*tableofcontents([^>]*?)-->%', '%\[\[TOC(.*?)\]\]%'),
    '_tableofcontents_replace_comments',
    $text
  );
}

/**
 * Replace <!-- tableofcontents {settings} -->
 * and [[TOC {settings}]] with [toc {settings}]
 */
function _tableofcontents_replace_comments($matches) {
  return '[toc ' . $matches[1] . ']';
}

/**
 * Process the text for the table of content.
 *
 * This adds the information about the [toc] to the text
 * regardless of whether it will actually be converted
 * to a [toc] in the end.
 */
function _tableofcontents_filter_process($text, $filter, $format, $langcode, $cache, $cache_id) {
  if (!$text) {
    return $text;
  }

  $encoded_toc = '';
  $toc = $filter->settings['tableofcontents'];

  // Does this have [toc] already?
  if (strpos($text, '[toc')===FALSE) {
    // No it doesn't...
    static $default;
    if (!isset($default)) {
      // Just do this once, in case it's wanted again.
      $default = _tableofcontents_toc_encode($toc);
    }
    // No, just encode the full default settings
    $encoded_toc = $default;

    // Do we want this at the top or bottom (or nowhere?)
    switch ($toc['on_off']['automatic']) {
      case 0:
        // Actually not required.
        break;
      case 1:
        $text = '[toc]' . $text;
        break;
      case 2:
        $text .= '[toc]';
        break;
    }
  }
  else {
    // Yes, so extract toc settings from [toc] in text,
    // then merge with defaults and encode
    $new_toc = _tableofcontents_toc_extract($text);
    $toc = merge_arrays($toc, $new_toc);
    $encoded_toc = _tableofcontents_toc_encode($toc);
  }

  // Replace the old [toc] with the new [toc]
#  tableofcontents_set()
  return preg_replace(TABLEOFCONTENTS_REMOVE_PATTERN, "[toc $encoded_toc]", $text) ;
}

/**
 * Encode the given 'toc' settings into a string
 */
function _tableofcontents_toc_encode($toc, $prefix = '') {
  static $encoded = '';
  foreach ($toc as $k => $v) {
    if (is_array($v)) {
      _tableofcontents_toc_encode($v, "$prefix$k::");
    }
    else {
      $encoded .= "$prefix$k=" . urlencode($v) . ' ';
    }
  }
  return $encoded;
}

function merge_arrays($a, $b) {
  foreach($b as $k => $v) {
    $a[$k] = (array_key_exists($k, $a) && is_array($v)) ? merge_arrays($a[$k], $b[$k]) : $v;
  }
  return $a;
}

/**
 * Implements hook_filter_FILTER_tips().
 */
function _tableofcontents_filter_tips($filter, $format, $long = FALSE) {
  if (!$long) {
    return t('Use [toc ...] to insert a mediawiki style collapsible table of contents.');
  }
  return t('Every instance of "[toc ...]" in the input text will be replaced with a collapsible mediawiki-style table of contents. Accepts options for title, list style, minimum heading level, and maximum heading level, and attachments as follows: [toc list: ol; title: Table of Contents; minlevel: 2; maxlevel: 3; attachments: yes;]. All arguments are optional.');
}