<?php
/**
 * @file
 * gofast_features_global.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function gofast_features_global_filter_default_formats() {
  $formats = array();

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = array(
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Full HTML.
  $formats['full_html'] = array(
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 0,
    'status' => 1,
    'weight' => 1,
    'filters' => array(
      'filter_url' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_toc' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(
          'tableofcontents' => array(
            'on_off' => array(
              'hide' => 0,
              'automatic' => 3,
              'min_limit' => 2,
            ),
            'box' => array(
              'title' => 'Table of Contents',
              'minlevel' => 1,
              'maxlevel' => 6,
              'hide_show' => 1,
              'collapsed' => 0,
            ),
            'header' => array(
              'id_strip' => array(
                'digits' => 0,
                'dashes' => 0,
                'periods' => 0,
                'underscores' => 0,
                'colons' => 0,
              ),
              'id_prefix' => 'hdr',
              'id_sep' => '-',
              'id_gen' => 'title',
              'allowed' => '<em> <i> <strong> <b> <u> <del> <ins> <sub> <sup> <cite> <strike> <s> <tt> <span> <font> <abbr> <acronym> <dfn> <q> <bdo> <big> <small>',
            ),
            'back_to_top' => array(
              'label' => '',
              'location' => 'bottom',
              'minlevel' => 1,
              'maxlevel' => 1,
              'anchor' => 'toc',
              'scroll' => 0,
            ),
            'numbering' => array(
              'method' => 2,
              'headers' => 1,
              'mode' => 0,
              'prefix' => '',
              'separator' => '.',
              'suffix' => '.',
            ),
          ),
        ),
      ),
      'filter_autop' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_htmlcorrector' => array(
        'weight' => 10,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: PHP code.
  $formats['php_code'] = array(
    'format' => 'php_code',
    'name' => 'PHP code',
    'cache' => 0,
    'status' => 1,
    'weight' => 11,
    'filters' => array(
      'php_code' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Plain text.
  $formats['plain_text'] = array(
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => 10,
    'filters' => array(
      'filter_html_escape' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => 1,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
      'filter_autop' => array(
        'weight' => 2,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
