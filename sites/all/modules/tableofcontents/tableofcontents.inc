<?php
/**
 * @file
 * Table of Contents - Versatile system for generating Tables of Contents for fields - processing.
 */

/**
 * This function goes through all the headers found in the text.
 *
 * @todo The pattern used assumes that you have at most ONE header per
 * line AND that the whole header is defined on ONE line.
 *
 * @param $toc The table of content object
 * @param $format The format being worked on
 * @param $text The text to be parsed
 *
 * @return The text with headers transformed to include an identifier
 */
function _tableofcontents_headers($text) {
  $toc =& tableofcontents_toc();
  $toc['back_to_top']['link'] = theme('tableofcontents_back_to_top', array('toc' => $toc));

  // note that the pattern below assumes that the headers
  // are properly defined in your HTML (i.e. a header cannot
  // include another)
  //
  // Note: we support having a [collapse] tag just before a header
  //       and even possibly a [/collapse] just before that!
  $result = preg_replace_callback(
    '%((?:(?:<p(?:\s[^>]*)?'.'>\s*)?\[/collapse\](?:</p\s*>\s*)?)?'
      . '(?:<p(?:\s[^>]*)?'.'>\s*)?\[collapse[^]]*?\](?:</p\s*>\s*)?)?'
      . '<h([1-6])(\s+[^>]*?)?'.'>(.*?)</h[1-6]\s*>%si',
    '_tableofcontents_replace_headers',
    $text
  );

  return $result;
}

/**
 * This function changes a header attributes. It adds an identifier in case
 * there are none. It registers the identifier if there is already one.
 *
 * Note that the attributes (2nd match) always starts with a space if it
 * exists.
 *
 * @param $matches The matches (level, attributes and title)
 *
 * @return The header with an identifier.
 */
function _tableofcontents_replace_headers($matches) {
  $toc =& tableofcontents_toc();
  if (!isset($toc['header']['h'])) {
    $toc['header'] += array(
      'h' => array(),
      'first' => TRUE,
      'translations' => array(),
      'counters' => array(0,0,0,0,0,0),
      'min' => 0,
      'max' => 0,
      'idx' => 0,
    );
    $toc['header']['level_from'] = (int) $toc['box']['minlevel'];
    $toc['header']['level_to'] = (int) $toc['box']['maxlevel'];
  }
  $toc_header =& $toc['header'];

  $h = (object) array(
    'level' => $matches[2],
    'attrs' => $matches[3],
    'title' => $matches[4],
    'ident' => '',
  );

  // increase this level and reset all the sub-levels
  $toc_header['counters'][$h->level]++;
  for ($l = $h->level + 1; $l <= 6; ++$l) {
    $toc_header['counters'][$l] = 0;
  }
  if ($toc_header['level_from'] > $h->level) {
    $toc_header['level_from'] = $h->level;
  }
  $toc_header['level_to'] = $h->level;

  // determine the min./max. on the spot
  if ($toc_header['min']) {
    if ($toc_header['min'] > $h->level) {
      $toc_header['min'] = $h->level;
    }
  }
  else {
    $toc_header['min'] = $h->level;
  }
  if ($toc_header['max']) {
    if ($toc_header['max'] < $h->level) {
      $toc_header['max'] = $h->level;
    }
  }
  else {
    $toc_header['max'] = $h->level;
  }

  // check for existing id and use that if found
  if (preg_match('/\sid=(?:"([^"]*?)"|\'([^\']*?)\'|([^\s"\'>]))/i', $h->attrs, $id)) {
    // id[1] is with "
    // id[2] is with '
    // id[3] is without any quotes
    $h->ident = $id[1] ? $id[1] : ($id[2] ? $id[2] : $id[3]);

    // check for unicity
    foreach ($toc_header['h'] as $header) {
      if ($header->ident == $h->ident) {
        drupal_set_message(t('Two or more anchor identifiers match each others. One of them will be modified. This error happens when some anchor identifiers are generated automatically and others are predefined. Or both are predefined and the operator made a mistake (maybe a copy &amp; paste?)'), 'warning', FALSE);
        // make it unique anyway
        $h->ident .= $toc_header['id_sep'] . $toc_header['idx']++;
        $h->attrs = preg_replace('/\sid=(?:"([^"]*?)"|\'([^\']*?)\'|([^\s"\'>]))/i',
          ' id="' . $h->ident . '"', $h->attrs);
        break;
      }
    }
  }
  else {
    switch ($toc_header['id_gen']) {
      case 'random':
        // generate a random ID and then ensure unicity
        do {
          $id = user_password(8); // system function to generate a password from letters/digits
          $found = FALSE;
          foreach ($toc_header['h'] as $header) {
            if ($header->ident == $id) {
              $found = TRUE;
              break;
            }
          }
        } while ($found);
        break;

      case 'increment':
        $id = $toc_header['id_prefix'] . $toc_header['id_sep'] . $toc_header['idx']++;
        break;

      case 'sections':
        $id = $toc_header['id_prefix'];
        for ($idx = $toc_header['level_from']; $idx <= $toc_header['level_to']; ++$idx) {
          $id .= $toc_header['id_sep'] . $toc_header['counters'][$idx];
        }
        break;

      case 'custom':
        // the callee has to edit the $h->ident and $h->attrs fields
        module_invoke_all('anchor_identifier', $toc, $h);
        $id = '';
        break;

      default: // case 'title'
        /* no existing identifier, create one using the header title
         *
         * HTML 4.01
         *
         * http://www.w3.org/TR/html4/types.html#h-6.2
         *
         * ID and NAME tokens must begin with a letter ([A-Za-z]) and
         * may be followed by any number of letters, digits ([0-9]),
         * hyphens ("-"), underscores ("_"), colons (":"), and periods (".").
         *
         * 1. convert &nbsp; and other spaces into underscores
         * 2. convert &mdash; or &ndash; to '--'
         * 3. convert &amp; to 'and'
         * 4. remove any other entities
         * 5. remove any incompatible character
         * 6. remove digits at the start of the name (we could also add a letter?)
         *
         * sanitize accents by luron & deviantintegral (e.g. �=>e)
         * thanks to pathauto module for i18n-ascii.txt file */
        if (!isset($toc_translations)) {
          $path = drupal_get_path('module', 'tableofcontents');
          $toc_translations = parse_ini_file($path . '/i18n-ascii.txt');
        }
        $title = strtr(strip_tags($h->title, $toc_header['allowed']), $toc_translations);

        $allowed_chars = '';
        if (empty($toc_header['id_strip']['dashes'])) {
          $allowed_chars = '-';
        }
        $allowed_chars .= 'A-Za-z';
        if (empty($toc_header['id_strip']['digits'])) {
          $allowed_chars .= '0-9';
        }
        if (empty($toc_header['id_strip']['periods'])) {
          $allowed_chars .= '.';
        }
        if (empty($toc_header['id_strip']['underscores'])) {
          $allowed_chars .= '_';
        }
        if (empty($toc_header['id_strip']['colons'])) {
          $allowed_chars .= ':';
        }
        $id = preg_replace(
          array(
            '/&nbsp;|\s/',
            '/\'/',
            '/&mdash;/',
            '/&ndash;/',
            '/&amp;/',
            '/&[a-z]+;/',
            '/[^' . $allowed_chars . ']/',
            '/^[-0-9._:]+/',
            '/__+/',
          ),
          array(
            '_',     // &nbsp; and spaces
            '-',     // apostrophe, so it makes things slightly more readable
            '--',    // &mdash;
            '--',    // &ndash;
            'and',   // &amp;
            '',      // any other entity
            '',      // any character that is invalid as an ID name
            '',      // any digits at the start of the name
            '_',     // reduce multiple underscores to just one
          ),
          strip_tags($title)
        );
        if (!$id) {
          // no identifier (i.e. title is composed exclusively of digits, entities, etc.)
          $id = $toc_header['id_prefix'] . $toc_header['id_sep'] . $toc_header['idx']++;
        }
        break;
    }
    if ($id != '') {
      // ensure unicity
      foreach ($toc_header['h'] as $header) {
        if ($header->ident == $id) {
          $id .= $toc_header['id_sep'] . $toc_header['idx']++;
          break;
        }
      }

      $h->ident = $id;

      // create a new header including the generated identifier
      $h->attrs .= ' id="' . $id . '"';
    }
  }

  $h->number = theme('tableofcontents_number', array('toc' => $toc));
  if ($toc['numbering']['headers']) {
    $number = $h->number;
  }
  else {
    $number = '';
  }

  $result = $matches[1] . '<h' . $h->level . $h->attrs . '>' . $number . $h->title . '</h' . $h->level . '>';

  // save that header
  $toc_header['h'][] = $h;

  // Add a back to top before the header?
  if ($h->level >= $toc['back_to_top']['minlevel']
      && $h->level <= $toc['back_to_top']['maxlevel']) {
    switch ($toc['back_to_top']['location']) {
      case 'header':
        $result .= $toc['back_to_top']['link'];
        break;

      default: //case 'bottom':
        if (!$toc_header['first']) {
          $result = $toc['back_to_top']['link'] . $result;
        }
        break;

    }
  }
  $toc_header['first'] = FALSE;

  tableofcontents_toc($toc);
  return $result;
}
