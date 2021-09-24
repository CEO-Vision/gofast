<?php

/**
 * @file
 * Include the different setup (administration forms) for the
 * table of contents module.
 */


/**
 * Return the form used for the filter settings.
 *
 * @param $format_array The currently selected input $format_array.
 */
function _tableofcontents_filter_settings($format_array) {
  $format = ($format_array == 'block')?$format_array:$format_array['#format']->format;
  $settings = variable_get("tableofcontents_filter_settings_{$format}", array());

  $form['tableofcontents'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents'),
    '#collapsible' => TRUE,
    '#tree' => TRUE,
    '#description' => t('This filter adds a table of contents referencing headers found in a node. If no headers are defined in the node content, then no table of content is added (whether or not a [toc ...] is defined.)'),
  );


  // On/Off features
  $form['tableofcontents']['on_off'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents On/Off features'),
    '#collapsible' => TRUE,
    '#description' => t('Select when and how the Table of Contents is added or removed to your pages.'),
  );

  $form['tableofcontents']['on_off']['hide'] = array(
    '#title' => t('Hide the table of contents tags'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['on_off']['hide']) ? $settings['on_off']['hide'] : FALSE,
    '#description' => 'When checked, all the table of contents are removed without any additional tests.',
  );

  $form['tableofcontents']['on_off']['automatic'] = array(
    '#title' => t('Whether an automatic table of content should be added'),
    '#type' => 'select',
    '#options' => array(
      0 => t('Do not automatically add a table of content'),
      1 => t('If no [toc ...], automatically add one at the top of the page'),
      2 => t('If no [toc ...], automatically add one at the bottom of the page'),
      3 => t('If no [toc ...], create and cache it but don\'t put it on the page'),
    ),
    '#default_value' => isset($settings['on_off']['automatic']) ? $settings['on_off']['automatic'] : 0,
    '#description' => t('Please, note that there is a minimum limit (see below) that needs to be reached for the table of content to be added.'),
  );

  $form['tableofcontents']['on_off']['min_limit'] = array(
    '#title' => t('Number of headers before an automatic table of content is added'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($settings['on_off']['min_limit']) ? $settings['on_off']['min_limit'] : 5,
    '#description' => t('When no [toc ...] is defined and the automatic feature is turned on, a table of contents will automatically be added only if at least that many headers are present.'),
  );

  // Table of Contents box
  $form['tableofcontents']['box'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents Box'),
    '#collapsible' => TRUE,
    '#description' => t('How the box looks like.'),
  );

  $form['tableofcontents']['box']['title'] = array(
    '#title' => t('Table of Contents Title'),
    '#type' => 'textfield',
    '#size' => 32,
    '#maxlength' => 64,
    '#default_value' => isset($settings['box']['title']) ? $settings['box']['title'] : t('Table of Contents'),
    '#description' => t('Enter a default title for each Table of Contents. This will be translated for each individual page.'),
  );

  $headers = array(1 => 'h1', 'h2', 'h3', 'h4', 'h5', 'h6');

  $form['tableofcontents']['box']['minlevel'] = array(
    '#title' => t('Minimum heading level'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => $headers,
    '#default_value' => isset($settings['box']['minlevel']) ? $settings['box']['minlevel'] : 'h2',
  );

  $form['tableofcontents']['box']['maxlevel'] = array(
    '#title' => t('Maximum heading level'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => $headers,
    '#default_value' => isset($settings['box']['maxlevel']) ? $settings['box']['maxlevel'] : 'h3',
  );

  $form['tableofcontents']['box']['hide_show'] = array(
    '#title' => t('Include link to hide/show table of contents'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['box']['hide_show']) ? $settings['box']['hide_show'] : TRUE,
  );

  $form['tableofcontents']['box']['collapsed'] = array(
    '#title' => t('Start with the table of content collapsed'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['box']['collapsed']) ? $settings['box']['collapsed'] : FALSE,
  );

  // Headers
  $form['tableofcontents']['header'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents Header Handling'),
    '#collapsible' => TRUE,
    '#description' => t('Handling of the headers by the filter.'),
  );

  $id_options = array(
    'digits' => 'Strip all digits (0-9)',
    'dashes' => 'Strip all dash characters (-)',
    'periods' => 'Strip all period characters (.)',
    'underscores' => 'Strip all underscore characters (_)',
    'colons' => 'Strip all colon characters (:)',
  );
  $form['tableofcontents']['header']['id_strip'] = array(
    '#title' => t('Select what is stripped from the header titles'),
    '#type' => 'checkboxes',
    '#options' => $id_options,
    '#default_value' => isset($settings['header']['id_strip']) ? $settings['header']['id_strip'] : array(),
    '#description' => t('By default, identifiers are valid HTML identifiers. All are not valid JavaScript identifiers and can cause other side effects. You may therefore need to constrain those identifiers some more. Identifiers must start with a letter (A-Z and a-z) and can be followed by letters (A-Z and a-z), dashes (-), digits (0-9), periods (.), colons (:), and underscores (_).<br /><span style="color: red;">WARNING:</span> existing identifier are not being changed by this module. In other words, if it looks like this stripping feature does not work, please, edit your page(s) and check whether you already defined identifiers...'),
  );

  $form['tableofcontents']['header']['id_prefix'] = array(
    '#title' => t('ID Prefix'),
    '#description' => t('Word to prefix an ID whenever nothing else is available or when you do not use the header title or random schemes.'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['header']['id_prefix']) ? $settings['header']['id_prefix'] : 'hdr',
  );

  $form['tableofcontents']['header']['id_sep'] = array(
    '#title' => t('ID separator'),
    '#description' => t('The separator used whenever an identifier is appeneded at the end of the identifier. Also used as the identifier section separator.'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['header']['id_sep']) ? $settings['header']['id_sep'] : '-',
  );

  $options = array(
    'title'     => 'Use header title',
    'random'    => 'Create a random identifier',
    'increment' => 'Use the "Identifier introducer" and an incrementing number',
    'sections'  => 'Use the "Identifier introducer" and the sections',
    'custom'    => 'Custom: call module_invoke("tableofcontents", $id) -- requires a module or theme that understands this API.',
  );
  $form['tableofcontents']['header']['id_gen'] = array(
    '#title' => t('How to generate missing header identifiers'),
    '#type' => 'radios',
    '#options' => $options,
    '#default_value' => isset($settings['header']['id_gen']) ? $settings['header']['id_gen'] : 'title',
  );

  $form['tableofcontents']['header']['allowed'] = array(
    '#title' => t('List of tags allowed in table headers'),
    '#type' => 'textfield',
    '#default_value' => isset($settings['header']['allowed']) ? $settings['header']['allowed'] : TABLEOFCONTENTS_ALLOWED_TAGS,
    '#maxlength' => 256,
  );

  // Back to Top
  $form['tableofcontents']['back_to_top'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents Back to Top Links'),
    '#collapsible' => TRUE,
    '#description' => t('Defines the Back to Top link information (i.e. label, location, etc.)'),
  );

  $form['tableofcontents']['back_to_top']['label'] = array(
    '#title' => t('Back to top label'),
    '#type' => 'textfield',
    '#size' => 35,
    '#default_value' => isset($settings['back_to_top']['label']) ? $settings['back_to_top']['label'] : '',
    '#description' => t('The message to display at the top or bottom of each paragraph with a link back to the table of contents. Leave empty to avoid this link.'),
  );

  $form['tableofcontents']['back_to_top']['location'] = array(
    '#title' => t('Back to top location'),
    '#type' => 'select',
    '#options' => array(
      'header' => t('Under the headers'),
      'bottom' => t('At the bottom of the paragraph'),
    ),
    '#default_value' => isset($settings['back_to_top']['location']) ? $settings['back_to_top']['location'] : 'bottom',
  );

  $form['tableofcontents']['back_to_top']['minlevel'] = array(
    '#title' => t('Minimum level where Back to Top appears'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => $headers,
    '#default_value' => isset($settings['back_to_top']['minlevel']) ? $settings['back_to_top']['minlevel'] : 'h2',
  );

  $form['tableofcontents']['back_to_top']['maxlevel'] = array(
    '#title' => t('Maximum level where Back to Top appears'),
    '#type' => 'select',
    '#multiple' => FALSE,
    '#options' => $headers,
    '#default_value' => isset($settings['back_to_top']['maxlevel']) ? $settings['back_to_top']['maxlevel'] : 'h4',
  );

  $form['tableofcontents']['back_to_top']['anchor'] = array(
    '#title' => t('Back to top anchor'),
    '#type' => 'textfield',
    '#size' => 35,
    '#default_value' => isset($settings['back_to_top']['anchor']) ? $settings['back_to_top']['anchor'] : 'toc',
    '#description' => t('Specify the name of the anchor where you want the Back to top links to go. The default is <em>toc</em> which is the table of contents. Other anchor often used are <em>header, page, screen, wrapper</em>.'),
  );

  $form['tableofcontents']['back_to_top']['scroll'] = array(
    '#title' => t('Scroll back to the table of contents'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['back_to_top']['scroll']) ? $settings['back_to_top']['scroll'] : FALSE,
    '#description' => t('Use the local scroll with jquery to scroll back to the table of contents.'),
  );

  // Numbering
  $form['tableofcontents']['numbering'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents Numbering'),
    '#collapsible' => TRUE,
    '#description' => t('Defines the table of contents and headers numbering method.'),
  );

  $form['tableofcontents']['numbering']['method'] = array(
    '#title' => t('Numbering method'),
    '#type' => 'select',
    '#options' => array(
      0 => t('No number'),
      4 => t('Browser numbering (<ol> tag)'),
      1 => t('Numbers 1., 2., 3. (like <ol>)'),
      2 => t('Sub-numbers 1., 1.1, 1.2, 2., 2.1, 2.2, etc.'),
      3 => t('Sub-numbers with zero 1.0, 1.1, 1.2, 2.0, 2.1, 2.2, etc.'),
    ),
    '#default_value' => isset($settings['numbering']['method']) ? $settings['numbering']['method'] : 0,
    '#description' => t('Select the type of numbering.'),
  );

  $form['tableofcontents']['numbering']['headers'] = array(
    '#title' => t('Add the number to the headers'),
    '#type' => 'checkbox',
    '#default_value' => isset($settings['numbering']['headers']) ? $settings['numbering']['headers'] : FALSE,
    '#description' => t('Also add the numbers shown in the table of contents to the headers.'),
  );

  $form['tableofcontents']['numbering']['mode'] = array(
    '#title' => t('Numbering mode'),
    '#type' => 'select',
    '#options' => array(
      0 => t('Decimal (1, 2, 3...)'),
      1 => t('Roman (I, II, III, ...)'),
      2 => t('Roman (i, ii, iii, ...)'),
      3 => t('Letters (A, B, C, ...)'),
      4 => t('Letters (a, b, c, ...)'),
      5 => t('Hexadecimal (0x00, 0x01, 0x02, ...)'),
    ),
    '#default_value' => isset($settings['numbering']['mode']) ? $settings['numbering']['mode'] : 0,
    '#description' => t('Select decimal, roman, or letters.'),
  );

  $form['tableofcontents']['numbering']['prefix'] = array(
    '#title' => t('Numbering prefix'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($settings['numbering']['prefix']) ? $settings['numbering']['prefix'] : '',
    '#description' => t('The characters added at the start. Often used for an opening parenthesis.'),
  );

  $form['tableofcontents']['numbering']['separator'] = array(
    '#title' => t('Numbering separator'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($settings['numbering']['separator']) ? $settings['numbering']['separator'] : '.',
    '#description' => t('The characters added between each number.'),
  );

  $form['tableofcontents']['numbering']['suffix'] = array(
    '#title' => t('Numbering suffix'),
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($settings['numbering']['suffix']) ? $settings['numbering']['suffix'] : '.',
    '#description' => t('The characters added at the end. Often used for a closing parenthesis.'),
  );

  return $form;
}

/**
 * Saves the filter settings.
 */
function _tableofcontents_filter_settings_submit($form, &$form_state) {
  $format = $form_state['values']['format'];
  $settings = $form_state['values']['filters']['filter_toc']['settings']['tableofcontents'];
  variable_set("tableofcontents_filter_settings_{$format}", $settings);
}

/**
 * This function makes sure that the table of content is hidden in the teaser
 * if so requested by the user.
 *
 * @param $node The node which teaser will be tweaked
 */
function _tableofcontents_hide_in_teaser(&$node) {
  // node got a teaser?
  if (!$node->body[$node->language][0]['summary']) {
    return;
  }

  // node uses our filter?
  $filters = filter_list_format($node->body[$node->language][0]['format']);
  if (!isset($filters['tableofcontents/0'])) {
    return;
  }

  // any [toc ...] tag in the teaser?
  $new_teaser = preg_replace('%(<!--\s*tableofcontents([^>]*)-->|\[\[TOC.*?\]\]|(<(div|p)(\s+[^>]*)?>\s*)?\[toc.*?\](\s*</(div|p)>)?)%', '', $node->teaser);
  if ($node->body[$node->language][0]['summary'] == $new_teaser) {
    // okay, no [toc ...], but maybe we need to hide the table of content?
    if (!variable_get('automatic_' . $node->format, 0)) {
      return;
    }
  }

  if (strpos($node->body[$node->language][0]['value'], '<!--break-->') !== FALSE) {
    // We've specified the split, but the teaser is shown in full
    // view. So, we now have to convert it so that the table of
    // content is hidden in the teaser.
    $body = '<!--break-->' . str_replace('<!--break-->', '', $node->body[$node->language][0]['value']);
    if ($body != $node->body[$node->language][0]['value']) {
      $node->body[$node->language][0]['value'] = $body;
      drupal_set_message(t("The content you saved contains a table of contents. A separate summary (teaser) has been automatically created without the table of contents at the top. If you make any further changes, be sure to check the summary field to see if your changes apply there as well."));
    }
  }
  else {
    // This is the case where no teaser was specified by the user.
    // We add an explicit split teaser.
    $node->body[$node->language][0]['value'] = '<!--break-->' . $node->body[$node->language][0]['value'];
    drupal_set_message(t("The summary (teaser) was automatically split from the body as site settings does not allow table of contents in summaries. If you make any further changes, be sure to check the summary field to see if your changes apply there as well."));
  }

  // Remove toc from teasers.
  $node->body[$node->language][0]['summary'] = $new_teaser . '<div>[toc hidden:1]</div>';
}

/**
 * Add a field so users can ask the TOC to be generated in a
 * node without the use of the filter [toc].
 */
function _tableofcontents_node_form_alter(&$form) {
  $nid = $form['nid']['#value'];
  if ($nid) {
    $node = node_load($nid);
    $toc_automatic = variable_get('nodetype_toc_automatic_' . $node->type, 0);
  }
  else {
    $node = (object)array(
      'toc_automatic' => 0,
    );
    $toc_automatic = variable_get('nodetype_toc_automatic_' . $form['type']['#value'], 0);
  }
  if ($toc_automatic == 99) {
    $options = array(
      0 => t('No table of contents'),
      1 => t('Add the table at the top'),
      2 => t('Add the table at the bottom'),
    );
    $form['toc_automatic'] = array(
      '#title' => t('Add a table of content to this node'),
      '#type' => 'select',
      '#options' => $options,
      '#default_value' => $node->tableofcontents_toc_automatic,
      '#description' => t('Select where you want the table of content, or no table.<br/><small>Note that the filter automatic feature takes precedence.</small>'),
    );
  }
}

/**
 * Add a field to the node type so one can define the automatic
 * table of content type on a per type basis.
 */
function _tableofcontents_nodetype_form_alter(&$form) {
  $form['tableofcontents'] = array(
    '#type' => 'fieldset',
    '#title' => t('Table of Contents'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Defines whether a table of content is automatically created on those pages and whether the node_view() function is used along with the filter.'),
    '#group' => 'additional_settings',
  );

  $options = array(
     0 => 'No table of contents',
     1 => 'Add the table at the top',
     2 => 'Add the table at the bottom',
    99 => 'Let user choose on node add/edit',
  );
  $form['tableofcontents']['toc_automatic'] = array(
    '#type' => 'select',
    '#title' => t('Choose where the automatic table of contents is shown'),
    '#options' => $options,
    '#default_value' => variable_get('nodetype_toc_automatic_' . $form['#node_type']->type, 0),
    '#description' => t('Select whether the table of content should be shown or not on this type of node.'),
  );

  $form['tableofcontents']['vtoc'] = array(
    '#title' => t('Transform [vtoc] tags'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('nodetype_toc_vtoc_' . $form['#node_type']->type, FALSE),
    '#description' => t('Select this option to allow [vtoc] (usually instead of [toc], although if you do not use the filter, both [vtoc] and [toc] will be transformed.) The difference is with the teasers. [vtoc] only works with the Node View hook, not the filters. This means we have the $teaser flag available and know exactly whether the teaser is being generated or not. There are several drawbacks, however: (1) no other filter runs after the table of contents changes, although the data should already be sanetize, there could be a security issue; (2) it does not work with Views and many other modules that will get the body content without running the node_prepare() function; (3) this only works within a node, no other type of data whether it supports a filter or not, will not support a table of content.'),
  );

  $form['tableofcontents']['remove_from_teaser'] = array(
    '#title' => t('Remove table of contents from the teaser'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('nodetype_toc_remove_from_teaser_' . $form['#node_type']->type, TRUE),
    '#description' => t('This is the main reason to support [vtoc]: a way to remove the table of contents from your teasers without adding a [toc hide=1;] tag in the teaser. However, as specified in the [vtoc] above, there are drawbacks to this method.'),
  );

  $form['#submit'][] = '_tableofcontents_nodetype_form_alter_submit';
}

/**
 * Save the user selection.
 */
function _tableofcontents_nodetype_form_alter_submit($form, &$form_state) {
  variable_set('nodetype_toc_automatic_' . $form['#node_type']->type, $form_state['values']['toc_automatic']);
  variable_set('nodetype_toc_vtoc_' . $form['#node_type']->type, $form_state['values']['vtoc']);
  variable_set('nodetype_toc_remove_from_teaser_' . $form['#node_type']->type, $form_state['values']['remove_from_teaser']);
}

// vim: ts=2 sw=2 et syntax=php
