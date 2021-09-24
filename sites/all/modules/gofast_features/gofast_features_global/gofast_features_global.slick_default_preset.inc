<?php
/**
 * @file
 * gofast_features_global.slick_default_preset.inc
 */

/**
 * Implements hook_slick_default_presets().
 */
function gofast_features_global_slick_default_presets() {
  $export = array();

  $preset = new stdClass();
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 1;
  $preset->name = 'gofast_3_7_0';
  $preset->label = 'GoFAST 3.7.0';
  $preset->breakpoints = 0;
  $preset->skin = '3d-back';
  $preset->options = array(
    'optimized' => 1,
    'general' => array(
      'normal' => '',
      'thumbnail' => '',
      'template_class' => '',
      'goodies' => array(
        'arrow-down' => 0,
        'pattern' => 0,
        'random' => 0,
      ),
      'arrow_down_target' => '',
      'arrow_down_offset' => '',
    ),
    'settings' => array(
      'asNavFor' => '',
      'prevArrow' => '<button type="button" data-role="none" class="slick-prev" aria-label="Previous" tabindex="0" role="button">Previous</button>',
      'nextArrow' => '<button type="button" data-role="none" class="slick-next" aria-label="Next" tabindex="0" role="button">Next</button>',
      'focusOnSelect' => FALSE,
      'initialSlide' => 0,
      'lazyLoad' => 'ondemand',
      'rtl' => FALSE,
      'rows' => 1,
      'slidesPerRow' => 1,
      'slide' => '',
      'slidesToShow' => 1,
    ),
  );
  $export['gofast_3_7_0'] = $preset;

  return $export;
}
