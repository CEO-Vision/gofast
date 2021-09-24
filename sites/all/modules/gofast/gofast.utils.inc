<?php

/**
 * Check if the request is an ajax request.
 *
 * @return TRUE if the current request is an ajax request, FALSE otherwise.
 */
function gofast_request_is_ajax() {
  return !empty($_SERVER['HTTP_X_REQUESTED_WITH']) && strtolower($_SERVER['HTTP_X_REQUESTED_WITH']) === 'xmlhttprequest';
}

/**
 * Save a node technically, so the last modifier and the modification date are not modified
 *
 * @param $node
 *  The node to save
 * @return $node
 * the prepared node
 */
function gofast_prepare_node_save_technically($node){
    //we store the current modifier and modification date into technically fields attached to node
   $node->technically_save = true;
   $node->technically_changed = $node->changed;
   $_POST['prevent_notify'] = TRUE;
   return $node;
}

/**
 * Returns a full (unix|http) path depending on a given file ID.
 *
 * @param $fid
 *  The unique file ID
 * @param $unix
 *  Whether to return an http url or a unix path
 * @return string
 *  A full path url
 */
function gofast_get_path($fid, $unix = FALSE) {
  global $base_url, $base_path;
  if (!$file = file_load($fid))
    return 0;
  $url = file_create_url($file->uri);
  return $unix ? str_replace($base_url . '/', DRUPAL_ROOT . $base_path, $url) : $url;
}

/**
 * t() function wrapper
 */
function _t_($str, $var, $lang = 'fr') {
  $_var = trim($var);
  $str = str_replace($var, $_var, $str);
  if ($lang == 'fr' && in_array(strtolower(substr($_var, 0, 1)), array('a', 'e', 'i', 'u', 'o', 'y'))) {
    $str = str_replace(" de {$_var}", " d'{$_var}", $str);
  }
  return $str;
}

function gofast_date_form_birthdate($form, $form_state) {
  module_load_include('inc', 'date_api', 'date_api_elements');

  // Retrieve settings if any. Default value must be in 'Y-m-d' format.
  $settings = isset($form_state['build_info']['args'][0]) ? $form_state['build_info']['args'][0] : array();
  $settings += array('default' => date('m/d/Y', time()), 'date_format' => 'm/d/Y', 'hidden' => FALSE);

  // Allow user to pick date within a large year range in the past.
  $year_range = (1900 - date('Y')) . ':0';

  $form['birthdate'] = array(
    '#title' => '',
    '#type' => 'date_popup', // Provided by the date_popup module
    '#date_format' => $settings['date_format'], // j F Y', // Uses the PHP date() format - http://php.net/manual/en/function.date.php
    '#date_year_range' => $year_range, // Limits the year range to the next two upcoming years
    '#required' => TRUE,
    '#default_value' => $settings['default'],
    '#date_label_position' => 'none',
    '#required' => FALSE,
    'date' => array(
      '#default_value' => $settings['default'],
      '#value' => $settings['default']
    ),
    '#value' => array(
      'date' => $settings['default']
    )
  );

  if ($settings['hidden']) {
    $form['birthdate'] += array(
      '#prefix' => '<span style="display:none;">',
      '#suffix' => '</span>'
    );
  }

  return $form;
}

/**
 * Returns the given $array as an html string.
 *
 * @param array $array
 *  An array to print out.
 *
 * @param array $display_key [optional]
 *  Display array keys if set to TRUE, useful with associative array. Defaults
 *  to FALSE.
 *
 * @return an HTML string
 */
function array_to_html(array $array, $display_key = FALSE) {
  $out = '<ul>';
  foreach ($array as $k => $v) {
    $key = $display_key ? "{$k} => " : '';
    if (is_array($v)) {
      $out .= "<li> ".t($key, array(), array('context' => 'gofast')) . array_to_html($v, $display_key) . '</li>';
    }
    else {
      $out .= "<li> ".t($key, array(), array('context' => 'gofast')).t($v, array(), array('context' => 'gofast'))." </li>";
    }
  }
  return $out . '</ul>';
}

/**
 * Returns $array as an html string, with additional attributes.
 */
function array_to_html_opt($array, $list_attributes = NULL, $level = 0) {
  $ul_attr = '';
  if (is_array($list_attributes)) {
    $list_attributes['class'] .= " level-{$level}";
    foreach ($list_attributes as $attr => $value) {
      $ul_attr .= " {$attr}='{$value}'";
    }
  }
  $out = "<ul{$ul_attr}>";
  foreach ($array as $k => $v) {
    $li_attr = '';
    $v['attributes']['item'] = $k;
    foreach ($v['attributes'] as $attr => $value)
      $li_attr .= " {$attr}='{$value}'";
    if (isset($v['children'])) {
      if (is_array($v['children'])) {
        $out .= "<li{$li_attr}>" . array_to_html($v['children'], $level++) . '</li>';
      }
      else {
        $out .= "<li{$li_attr}>{$v['children']}</li>";
      }
    }
    else {
      $out .= is_array($v) ? array_to_html($v) : "<li{$li_attr}>{$v}</li>";
    }
  }
  return $out . '</ul>';
}

/**
 * Returns a themed dropdown menu, given an array of (toggle) options.
 */
function gofast_options_dropdown($options, $group_class = 'btn-group', $title = NULL) {
  $output = '';

  if (empty($options) || !is_array($options)) {
    return $output;
  }

  if (empty($title)) {
    $title = t('Options', array(), array('context' => 'gofast'));
  }

  $attr_title = t('Click to manage options', array(), array('context' => 'gofast'));

  $btn_cls = 'btn btn-secondary';
  $theme_settings = gofast_get_theme_settings();
  if (isset($theme_settings['bootstrap_button_size'])) {
//    $btn_cls .= ' ' . $theme_settings['bootstrap_button_size'];
  }

  $output .= "<div class='gofast-options {$group_class}'>";
  $output .= "<button type='button' class='{$btn_cls} dropdown-toggle' data-toggle='dropdown' title='{$attr_title}'>";
  $output .= $title . '<span class="caret" style="margin-left:5px;"></span>';
  $output .= '</button>';
  $output .= array_to_html_opt($options, array('class' => 'dropdown-menu', 'role' => 'menu'));
  $output .= '</div>';

  return $output;
}

/**
 * Helper that returns settings array for the current theme.
 */
function gofast_get_theme_settings() {
  $theme_name = variable_get('theme_default', 'bartik');
  return variable_get('theme_' . $theme_name . '_settings', array());
}

/**
 * Returns HTML for a generic HTML tag, with bootstrap tooltip attributes.
 *
 * @param type $array
 * @return string
 */
function gofast_make_tooltip($tip = NULL, $tag = 'i', $placement = 'left') {
  if (!$tip)
    return '';

  $attributes = array(
    'title' => $tip,
    'data-original-title' => $tip,
    'data-toggle' => 'tooltip',
    'data-placement' => $placement
  );

  return theme('html_tag', array('element' => array('#tag' => $tag, '#attributes' => $attributes)));
}

/**
 * fonction test pour renommer une entrée 'non-leaf' dans ldap
 */
function gofast_ldap_rename_entry($dn, $new_dn) {
  $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
  $success = FALSE;
  if ($LdapServer->search($dn, 'objectClass=*', array(), 0, 0, 0, NULL, LDAP_SCOPE_ONELEVEL)) {
    // Cannot rename a non-leaf entry, such an operation is only supported when
    // using the back-hdb database backend (slapd). As a workaround, we rebuild
    // the entire subtree with updated dn's...
    if (_gofast_ldap_clone_subtree($dn, $new_dn)) {
      // ... and if succeeded, delete the original subtree.
      $success = $LdapServer->delete($dn, TRUE);
//      $debug[] = array('LDAP DELETE' => array($dn));
    }
  }
  else {
    // This is a leaf entry, can be renamed safely.
    $LdapServer->connectAndBindIfNotAlready();
    $newrdn = gofast_ldap_get_rdn($new_dn);
    $newparent = gofast_ldap_get_parent_dn($new_dn);
    $success = @ldap_rename($LdapServer->connection, $dn, $newrdn, $newparent, TRUE);
  }

  return $success;
}

/**
 * Fonction test utilisée pour renommer une entrée 'non-leaf' dans ldap.
 *  -> recursive
 */
function _gofast_ldap_clone_subtree($dn, $new_dn, &$debug = array()) {

  $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
  $filter = 'objectClass=groupOfNames';
  $attributes = array('cn', 'member', 'ou', 'objectclass');

  /* 1. Retrieve the entry to rename, make a clone, then rename the clone and
   * add the new entry in the directory. */

  $entry = $LdapServer->search($dn, $filter, $attributes, 0, 0, 0, NULL, LDAP_SCOPE_BASE);

  if (!isset($entry[0]))
    return FALSE;

  $entry = $entry[0];
  $_attributes = array();

  // Only keep wanted attributes, filters out the others ('cn' is ignored too
  // because it is the rdn for 'groupOfNames' objects).
  foreach ($attributes as $attribute) {
    if (!isset($entry[$attribute]) || $attribute === 'cn')
      continue;
    unset($entry[$attribute]['count'], $entry['dn'], $entry['cn']);
    $_attributes[$attribute] = $entry[$attribute];
//    if (is_array($_attributes[$attribute])) {
//      foreach ($_attributes[$attribute] as $k => &$value) {
//        $value = strtolower($value);
//      }
//    }
//    else {
//      $_attributes[$attribute] = strtolower($_attributes[$attribute]);
//    }
  }

  $success = $LdapServer->groupAddGroup($new_dn, $_attributes);
  if (!$success)
    return FALSE;
//  $debug[] = array('LDAP ADD' => array($new_dn, $_attributes));

  /* 2. Manage subordinates entries. Foreach child, update the dn according to
   * its new parent, do a recursive call to rename all entries down the tree. */

  $parent_dn = $new_dn;
  $entries = $LdapServer->search($dn, $filter, $attributes, 0, 0, 0, NULL, LDAP_SCOPE_ONELEVEL);

  if (!isset($entry[0])) {
    // There is no child, this is not an error.
    return TRUE;
//    return 'no child';
  }

  unset($entries['count']);
//  $new_rdn = reset(explode(',', $parent_dn));
  $new_rdn = gofast_ldap_get_rdn($parent_dn);

  foreach ($entries as $i => $entry) {
    if (isset($entry['ou'][0]) && in_array($entry['ou'][0], array('ROLE_ADMIN', 'ROLE_STANDARD'))) {
      // This is a subentry for group role managment, rdn depends on the parent.
      $group_role = substr($entry['ou'][0], 5);
      $new_dn = "{$new_rdn}_{$group_role},{$parent_dn}";
    }
    else {
      // This is a subgroup entry, rdn remains the same.
      $new_dn = "cn={$entry['cn'][0]},{$parent_dn}";
    }
    // Rename the child entry with its updated dn.
    $success &= _gofast_ldap_clone_subtree($entry['dn'], $new_dn);
//    _gofast_ldap_clone_subtree($entry['dn'], $new_dn, $debug);
  }

  return $success;
//  return $debug;
}

function extract_file_extension($file_name) {
  return pathinfo($file_name, PATHINFO_EXTENSION);
}

/**
 * Generates a teaser from $body content.
 *
 * If the end of the teaser is not indicated using the <!--break--> delimiter
 * then we generate the teaser automatically, trying to end it at a sensible
 * place such as the end of a paragraph, a line break, or the end of a sentence
 * (in that order of preference).
 *
 * @param $body
 *   The content for which a teaser will be generated.
 *
 * @param $size [optional]
 *   Desired character length of the teaser. If omitted, the default value will
 *   be used. Ignored if the special delimiter is present in $body.
 *
 * @return string
 *   The generated teaser.
 */
function gofast_teaser($body, $size = 350) {
  return gofast_html_close_tag(call_user_func(function ($body, $size) {
            // If body is empty, there is nothing to do here.
            if (empty($body)) {
              return $body;
            }

            // Find where the delimiter is in the body
            $delimiter = strpos($body, '<!--break-->');

            // If the size is zero, and there is no delimiter, the entire body is the teaser.
            if (!$size && !$delimiter === FALSE) {
              return $body;
            }

            // If a valid delimiter has been specified, use it to chop off the teaser.
            if ($delimiter !== FALSE) {
              return substr($body, 0, $delimiter);
            }

            // If we have a short body, the entire body is the teaser.
            if (drupal_strlen($body) <= $size) {
              return $body;
            }

            // Try to split at paragraph or sentence boundaries.
            // The teaser may not be longer than maximum length specified. Initial slice.
            $teaser = truncate_utf8($body, $size);

            // Store the actual length of the UTF8 string -- which might not be the same
            // as $size.
            $max_rpos = strlen($teaser);

            // How much to cut off the end of the teaser so that it doesn't end in the
            // middle of a paragraph, sentence, or word.
            // Initialize it to maximum in order to find the minimum.
            $min_rpos = $max_rpos;

            // Store the reverse of the teaser.  We use strpos on the reversed needle and
            // haystack for speed and convenience.
            $reversed = strrev($teaser);

            // Build an array of arrays of break points grouped by preference.
            $break_points = array();

            // A paragraph near the end of sliced teaser is most preferable.
            $break_points[] = array('</p>' => 0);

            // If no complete paragraph then treat line breaks as paragraphs.
            $break_points[] = array('<br />' => 6, '<br>' => 4);

            // If the first paragraph is too long, split at the end of a sentence.
            $break_points[] = array('. ' => 1, '! ' => 1, '? ' => 1, '。' => 0, '؟ ' => 1);

            // Iterate over the groups of break points until a break point is found.
            foreach ($break_points as $points) {
              // Look for each break point, starting at the end of the teaser.
              foreach ($points as $point => $offset) {
                // The teaser is already reversed, but the break point isn't.
                $rpos = strpos($reversed, strrev($point));
                if ($rpos !== FALSE) {
                  $min_rpos = min($rpos + $offset, $min_rpos);
                }
              }

              // If a break point was found in this group, slice and return the teaser.
              if ($min_rpos !== $max_rpos) {
                // Don't slice with length 0.  Length must be <0 to slice from RHS.
                return ($min_rpos === 0) ? $teaser : substr($teaser, 0, 0 - $min_rpos);
              }
            }

            // If a break point was not found, still return a teaser.
            return $teaser;
          }, $body, $size));
}

function gofast_html_close_tag($html) {
  $list = array();
  $closing_tag = '';

  preg_match_all('/<[^>]*>/', $html, $tags);

  foreach ($tags[0] as $tag) {
    if ($tag{1} != '/' && preg_match('/<([a-z]+[0-9]*)/i', $tag, $match)) {
      // Opening tag.
      $list[] = $match[1];
    }
    elseif (preg_match('/<\/([a-z]+[0-9]*)/i', $tag, $match)) {
      // Closing tag
      preg_match('/<\/([a-z]+[0-9]*)/i', $tag, $match);

      // Strip tag
      for ($i = count($list) - 1; $i >= 0; $i--) {
        if ($list[$i] == $match[1]) {
          $list[$i] = '';
        }
      }
    }
  }

  for ($i = count($list) - 1; $i >= 0; $i--) {
    if ($list[$i] != '' && $list[$i] != 'br') {
      $closing_tag .= '</' . $list[$i] . '>';
    }
  }

  return $html . $closing_tag;
}

/**
 * Helper function - return a safe (PHP identifier) vocabulary name.
 *
 * @param integer $vid
 * @return string
 */
function gofast_get_vocab_name($vid, $label = FALSE) {
  $names = &drupal_static(__FUNCTION__, array());

  if (!isset($names[$vid]) || $label && !isset($names['label'][$vid])) {
    $vocab_name = db_query('SELECT v.name FROM {taxonomy_vocabulary} v WHERE v.vid = :vid', array(':vid' => $vid))->fetchField();
    if ($label) {
      $names['label'][$vid] = $vocab_name;
    }
    else {
      $names[$vid] = preg_replace('/[^a-zA-Z0-9_\x7f-\xff]/', '_', $vocab_name);
      // Fallback for names ending up all as '_'.
      $check = rtrim($names[$vid], '_');
      if (!$check) {
        $names[$vid] = '_' . $vid . '_';
      }
    }
  }
  return $label ? $names['label'][$vid] : $names[$vid];
}

/**
 * Helper function - return a vocabulary machine name.
 *
 * @param integer $vid
 * @return string
 */
function gofast_get_vocab_machine_name($vid) {
  $names = &drupal_static(__FUNCTION__, array());

  if (!isset($names[$vid])) {
    $names[$vid] = db_query('SELECT v.machine_name FROM {taxonomy_vocabulary} v WHERE v.vid = :vid', array(':vid' => $vid))->fetchField();
  }
  return $names[$vid];
}

function gofast_decrypt2($key, $string) {
  return rtrim(mcrypt_decrypt(MCRYPT_RIJNDAEL_256, md5($key), base64_decode($string), MCRYPT_MODE_CBC, md5(md5($key))), "\0");
}

/*
 * TO be used when updating to php7
 */
function gofast_encrypt($key, $string) {
  $ciphers = openssl_get_cipher_methods();
  if(array_search('AES-256-CBC-HMAC-SHA256', $ciphers) !== false){
    return base64_encode(openssl_encrypt($string, 'AES-256-CBC-HMAC-SHA256', md5(md5($key))));
  }else{
    return base64_encode(openssl_encrypt($string, 'aes-256-ofb', md5(md5($key))));
  }
}

function gofast_decrypt($key, $string) {
  $ciphers = openssl_get_cipher_methods();
  if(array_search('AES-256-CBC-HMAC-SHA256', $ciphers) !== false){
    return rtrim(openssl_decrypt( base64_decode($string), 'AES-256-CBC-HMAC-SHA256', md5(md5($key))), "\0");
  }else{
     return rtrim(openssl_decrypt( base64_decode($string), 'aes-256-ofb', md5(md5($key))), "\0");
  }
}

function _gofast_set_user_key($uid, $key = NULL) {
  static $_key = array();
  if (empty($uid) || (!isset($key) && !isset($_key[$uid]))) {
    return FALSE;
  }
  if (isset($key)) {
    $_key[$uid] = $key;
  }
  return $_key[$uid];
}

/**
 * Deletes a cookie.
 *
 * @param string $name
 *  The name of the cookie to delete.
 */
function gofast_delete_cookie($name) {
  global $cookie_domain;
  unset($_COOKIE[$name]);
  setcookie($name, '', time() - 3600, '/', $cookie_domain, TRUE, TRUE);
}

/**
 * This method returns the HTTP code of a given URL. If the url does not contain domain, assumes we want to get current domain.
 * @param type $url the URL we want to get its HTTP code
 * @return int the HTTP code
 */
function gofast_get_http_code($url) {
  $full_url = $url;
  $ch = curl_init();
  global $prevent_check_alfresco_status;
  if($prevent_check_alfresco_status == true && strpos($url, '/alfresco/') !== FALSE){

      $add_message = true;
         if(module_exists('gofast_community')){
            if(current_path() == "Welcome"){
               $warning_message = '';
            }else{
               $warning_message = t('There is a problem contacting Alfresco. Please reload your web page', array(), array('context' => 'gofast'));
            }
        }else{
         $warning_message = t('There is a problem contacting Alfresco. Please reload your web page', array(), array('context' => 'gofast'));
         }
         $all_messages = drupal_get_messages("warning", false);
         if(count($all_messages["warning"]) > 0){
             foreach($all_messages["warning"] as $message){
                 if($warning_message == $message){
                     $add_message = false;
                 }
             }
         }
         if($add_message == true){
             drupal_set_message($warning_message, "warning");
         }

      return;
  }

  //Retreive JSESSIONID if existing  to re-use it
  global $user;
  $cookie_name = "sites/default/files/swf/"."cookie_alfresco".$user->name.".txt";

  curl_setopt($ch, CURLOPT_URL, $full_url);
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, TRUE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  curl_setopt($ch, CURLOPT_COOKIEFILE, $cookie_name);
  curl_setopt($ch, CURLOPT_COOKIEJAR, $cookie_name);

  $header = curl_exec($ch);
  $info = curl_getinfo($ch, CURLINFO_HTTP_CODE);
  curl_close($ch);
  if(intval($info) == 0 && strpos($url, '/alfresco/') !== FALSE){
      //request into Alfresco has timeout, to prevent timeout all platforme, we set a flag ( global variable) to indicate to redo this request until the next page refresh
      $prevent_check_alfresco_status = true;
  }
  return intval($info);
}

/**
 * Returns field values as entities if possible,
 * Can also return only first value.
 *
 * @param type $entity_type
 * @param type $entity
 * @param type $field_name
 * @param type $get_delta
 * @param type $get_key
 * @return type
 */
function field_fetch_field_values($entity_type, $entity, $field_name, $get_delta = NULL, $get_key = NULL) {
  $values = array();
  if (isset($entity->$field_name) && !empty($entity->$field_name)) {
    foreach (field_get_items($entity_type, $entity, $field_name) as $delta => $item) {
      $value = $item;
      $keys = array_keys($item);
      if (count($keys) == 1) {
        $key = $keys[0];
        switch ($key) {
          case 'nid':
            $entity = entity_load('node', array($item[$key]));
            $value = array_shift($entity);
            break;
          case 'uid':
            $entity = entity_load('user', array($item[$key]));
            $value = array_shift($entity);
            break;
          case 'tid':
            $entity = entity_load('taxonomy_term', array($item[$key]));
            $value = array_shift($entity);
            break;
          case 'vid':
            $entity = entity_load('taxonomy_vocabulary', array($item[$key]));
            $value = array_shift($entity);
            break;
          case 'value':
            $value = $item['value'];
            break;
        }
      }
      else {
        if ($get_key && isset($item[$get_key])) {
          $value = $item[$get_key];
        }
        elseif (array_key_exists('value', $item)) {
          $value = isset($item['safe_value']) ? $item['safe_value'] : $item['value'];
        }
      }
      $values[$delta] = $value;
    }
  }
  if (is_numeric($get_delta)) {
    return isset($values[$get_delta]) ? $values[$get_delta] : NULL;
  }
  return $values;
}

/*
 * Matches each symbol of PHP date format standard
 * with jQuery equivalent codeword
 * @author Tristan Jahier
 */

function dateformat_PHP_to_bootstrapDatePicker($php_format) {
  $SYMBOLS_MATCHING = array(
    // Day
    'd' => 'dd',
    'D' => 'D',
    'j' => 'd',
    'l' => 'DD',
    'N' => '',
    'S' => '',
    'w' => '',
    'z' => 'o',
    // Week
    'W' => '',
    // Month
    'F' => 'MM',
    'm' => 'mm',
    'M' => 'M',
    'n' => 'm',
    't' => '',
    // Year
    'L' => '',
    'o' => '',
    'Y' => 'yyyy',
    'y' => 'yy',
    // Time
    'a' => '',
    'A' => '',
    'B' => '',
    'g' => '',
    'G' => '',
    'h' => 'hh',
    'H' => 'hh',
    'i' => 'ii',
    's' => '',
    'u' => ''
  );
  $jqueryui_format = "";
  $escaping = false;
  for ($i = 0; $i < strlen($php_format); $i++) {
    $char = $php_format[$i];
    if ($char === '\\') { // PHP date format escaping character
      $i++;
      if ($escaping)
        $jqueryui_format .= $php_format[$i];
      else
        $jqueryui_format .= '\'' . $php_format[$i];
      $escaping = true;
    }
    else {
      if ($escaping) {
        $jqueryui_format .= "'";
        $escaping = false;
      }
      if (isset($SYMBOLS_MATCHING[$char]))
        $jqueryui_format .= $SYMBOLS_MATCHING[$char];
      else
        $jqueryui_format .= $char;
    }
  }
  return $jqueryui_format;
}

/**
 * Returns the last JSON error (if any) occurred encoding / decoding.
 * Also log a message according to json_last_error() output.
 *
 * @param $log The Log output level :
 *    - 0 => No log.
 *    - 1 => Only if an error occured.
 *    - 2 => Always.
 */
function gofast_json_get_error($log = 1) {
  $error = json_last_error();
  switch ($error) {
    case JSON_ERROR_NONE:
      $success = TRUE;
      $msg = 'No error has occurred';
      break;
    case JSON_ERROR_DEPTH:
      $msg = 'Maximum stack depth exceeded';
      break;
    case JSON_ERROR_STATE_MISMATCH:
      $msg = 'Invalid or malformed JSON : Underflow or the modes mismatch';
      break;
    case JSON_ERROR_CTRL_CHAR:
      $msg = 'Unexpected control character found, possibly incorrectly encoded';
      break;
    case JSON_ERROR_SYNTAX:
      $msg = 'Syntax error, malformed JSON';
      break;
    case JSON_ERROR_UTF8:
      $msg = 'Malformed UTF-8 characters, possibly incorrectly encoded';
      break;
    default:
      $msg = 'Unknown error';
  }

  $msg .= ' - caller: ' . gofast_get_caller();

  if ($log === 2 || $log && !$success) {
    watchdog('JSON Last Error', $msg, [], WATCHDOG_ERROR);
  }

  return $error;
}

/**
 * Returns an array listing Gofast modules.
 */
function gofast_get_modules_list($include_features = FALSE) {
  $list = array();
  $modules = system_get_info('module');

  foreach ($modules as $name => $info) {
    if ($name === 'gofast' || strpos($name, 'gofast') === 0)
      $list[$name] = $info['name'];
  }

  if ($include_features === FALSE) {
    $list = array_flip(array_filter(array_flip($list), function($module) {
              return strpos($module, 'gofast_features') !== 0;
            }));
  }

  return $list;
}

/**
 * Returns whether the passed in array is an associative array or not. More
 * precisely, it will return FALSE if $array is a 0-indexed sequential array.
 * Note that array("0" => 'a', "1" => 'b', "2" => 'c') will be considered as
 * non-associative.
 *
 * @param array $array
 * @return boolean
 */
function is_assoc(array $array) {
  return !empty($array) && array_keys($array) !== range(0, count($array) - 1);
}

/**
 * fonction qui renvoit true si le navigateur est autre que IE ou si c'est IE superieur à 8, false si c'est IE8
 * @return boolean
 */
function gofast_browser_ie_upper_8() {
  preg_match('/MSIE (.*?);/', $_SERVER['HTTP_USER_AGENT'], $matches);
  if (count($matches) < 2) {
    preg_match('/Trident\/\d{1,2}.\d{1,2}; rv:([0-9]*)/', $_SERVER['HTTP_USER_AGENT'], $matches);
  }

  if (count($matches) > 1) {
    //Then we're using IE
    $version = $matches[1];

    switch (true) {
      case ($version <= 8):
        //IE 8 or under!
        return false;
        break;

      case ($version == 9 || $version == 10):
        //IE9 & IE10!
        return true;
        break;

      case ($version == 11):
        //Version 11!
        return true;
        break;

      default:
        return true;
    }
  }
  return true;
}

/**
 * Wrapper function, gets browser capabilities informations and caches it in a
 * static variable, based on the HTTP User-Agent header that is sent to server.
 *
 * @see get_browser()
 *
 * @return object
 *  An object containing browser informations and capabilities.
 */
function gofast_get_browser() {
  static $browser = NULL;
  if (!$browser && isset($_SERVER['HTTP_USER_AGENT'])) {
    $browser = get_browser();
  }
  if (isset($browser->browser_name_regex)) {
    // Fix encoding issues (@see https://bugs.php.net/bug.php?id=68021) until we
    // can upgrade to php >= 5.4.32 (current version 5.4.16).
    $browser->browser_name_regex = mb_convert_encoding($browser->browser_name_regex, 'UTF-8', 'ISO-8859-1');
  }
  return $browser;
}

/**
 * Return the browser name (i.e. $browser->browser value according to the HTTP
 * User-Agent header that is detected when the request was sent).
 */
function gofast_get_browser_name() {
  $browser = gofast_get_browser();
  return isset($browser->browser) ? $browser->browser : '';
}

/**
 * Returns HTML for a button element. To get a button FORM element, use the
 * theme('button') function.
 *
 * @param string $label
 *  The label to display in button element.
 *
 * @param string $path [optional]
 *  If set, the button element is wrapped in an anchor tag and $path is used to
 *  define the anchor's href attribute.
 *
 * @param string $btn_cls [optional]
 *  A class name to add to the button element. If not set 'btn-default' is used.
 *
 * @param string $glyph_class [optional]
 *  A glyphicon class to add to the button's inner tag.
 *
 * @param array $attr [optional]
 *  An associative array of HTML attributes to apply to the button tag. If the
 *  element 'class' is included, it must be an array; 'title' must be a string;
 *  other elements are more flexible (@see drupal_attributes()).
 *
 * @return string
 *  The constructed HTML.
 */
function gofast_button($label, $path = '', $btn_cls = '', $glyph_class = '', $attr = array()) {
  $btn_cls = array_merge(array('btn'), $btn_cls ? explode(' ', $btn_cls) : array('btn-default'));
  $label = ' ' . trim($label) . ' ';
  $modal = FALSE;

  $theme_settings = gofast_get_theme_settings();
  if (isset($theme_settings['bootstrap_button_size'])) {
    $btn_cls[] = $theme_settings['bootstrap_button_size'];
  }

  $attr['type'] = 'button';
  $attr['class'] = isset($attr['class']) ? $attr['class'] : array();
  $attr['class'] = array_merge($btn_cls, $attr['class']);

  if (($key = array_search('ctools-use-modal', $attr['class'])) !== FALSE) {
    $modal = TRUE;
    unset($attr['class'][$key]);
  }

  $button = '<button' . drupal_attributes($attr) . '">';

  if (!empty($glyph_class)) {
    $button .= '<span class="glyphicon ' . $glyph_class . '"></span>';
  }

  $button .= $label;

  if (!empty($path)) {
    $options = array('html' => TRUE);
    if ($modal) {
      $options['attributes'] = array('class' => array('ctools-use-modal'));
    }
    $button .= '</button>';
    $button = l($button, $path, $options);
  }
  else {
    $button .= '</button>';
  }

  return $button;
}

/**
 * Helper function to send immediate notification to administrators.
 */
function gofast_mail_report($subject, $message, $context = array()) {
  global $base_url;
  $subject = '[GoFast Report] ' . $subject;
  $pre = '<h2 style="color:#888888;">GoFast Error Report</h2>';
  $env = "<h4 style='color:#888888;'>Environment : <a href='{$base_url}'>{$base_url}</a></h4>";
  $message = "{$pre}{$env}<br />{$message}<br /><br />";
  $support = (object) array(
            'uid' => true,
            'name' => 'Administrateur',
            'mail' => user_load('5')->mail
  );
//  gofast_send_notifications($support, $subject, $message, $context, 'phpmailer');
//  _dump(array('recipient' => $support, 'subject' => $subject, 'message' => $message, 'context' => $context), 'mail_report');
}

/**
 * Helper, returns whether or not code runs on dev or (pre)production server.
 */
function gofast_dev_mode() {
  global $base_url;
  return in_array($base_url, [
   'https://gofast-dev.ceo-vision.com',
   'https://gofast-dev2.ceo-vision.com',
   'https://gofast-search.ceo-vision.com',
//   'https://gofast-preprod.ceo-vision.com',
  ]);
}

/**
 * Returns a new array that is a one-dimensional flattening of this array
 * (recursively). That is, for every element that is an array, extract its
 * elements into the new array.
 *
 * @param array $array
 *  The array to flatten.
 *
 * @param boolean $preserve_keys
 *  Whether or not to preserve array keys.
 */
function array_flatten(array $array, $preserve_keys = TRUE) {
  $return = array();
  $function = $preserve_keys ?
          function($val, $key) use (&$return) {
    $return[$key] = $val;
  } :
          function($val, $key) use (&$return) {
    $return[] = $val;
  };
  array_walk_recursive($array, $function);
  return $return;
}

/**
 * Iterate through all form END children (last leaves only)
 *
 * @param type $form
 *  A full or a part of a form array.
 *
 * @param callable $callback
 *  Callable function callback. Callback params are :
 *   - $element: the form element
 *   - $key: the form element key
 */
function _iterate_form(&$form, callable $callback) {
  foreach (element_children($form) as $key) {
    $element = &$form[$key];
    $children = array_intersect_key($element, array_flip(element_children($element)));
    if (empty($children)) {
      call_user_func_array($callback, array(&$element, $key));
    }
    else {
      _iterate_form($element, $callback);
    }
  }
}

/**
 * Helper that usurps a user given its $uid. This allows to run the script with
 * usurped user as current user.
 *
 * Caution :
 *  - You must run usurp(FALSE); after ursurping a user to restore your session.
 *  - It's up to the caller to check if $uid is valid. If not valid, a broken
 *  account will override the current user session, which causes unpredictable
 *  behavior.
 *
 * @param mixed $uid
 *  If a valid user id is passed in, usurp the user corresponding to this uid.
 *  If set to FALSE, restore the original user session.
 */
function usurp($uid = FALSE) {
  static $_user = NULL;
  global $user;

  if ($uid) {
    //to prevent switching user bugs for "classic" users, this function can be called only for admin or anonymous users
    if($user->uid != 0 && $user->uid != 1 && $uid != 1 && $uid != -1){
        watchdog('Gofast Utils', 'Prevent usurp called by user '.$user->uid." with uid ".$uid);
        return;
    }
    $_user = $user;
    drupal_save_session(FALSE);
    $user = user_load($uid);
  }
  elseif ($uid === FALSE) {
    $user = $_user;
    drupal_save_session(TRUE);
  }

  return $user;
}

/**
 * Inserts a new key/value pair before a given key in the array.
 *
 * @param $needle
 *  The key to insert before.
 * @param array $array
 *  An array to insert into.
 * @param $key
 *  The key to insert.
 * @param $value
 *  The value to insert.
 *
 * @return boolean
 *  TRUE if operation succeeds, FALSE otherwise.
 *
 * @see array_insert_after()
 */
function array_insert_before($needle, array &$array, $key, $value) {
  if (array_key_exists($needle, $array)) {
    $new = array();
    foreach ($array as $k => $v) {
      if ($k === $needle) {
        $new[$key] = $value;
      }
      $new[$k] = $v;
    }
    $array = $new;
    return TRUE;
  }
  return FALSE;
}

/**
 * Inserts a new key/value pair after a given key in the array.
 *
 * @param $needle
 *  The key to insert after.
 * @param array $array
 *  An array to insert into.
 * @param $key
 *  The key to insert.
 * @param $value
 *  The value to insert.
 *
 * @return boolean
 *  TRUE if operation succeeds, FALSE otherwise.
 *
 * @see array_insert_before()
 */
function array_insert_after($needle, array &$array, $key, $value) {
  if (array_key_exists($needle, $array)) {
    $new = array();
    foreach ($array as $k => $v) {
      $new[$k] = $v;
      if ($k === $needle) {
        $new[$key] = $value;
      }
    }
    $array = $new;
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_element_info_alter()
 *
 * Alter the element type information returned from modules.
 *
 * @param type $type
 *  All element type defaults as collected by hook_element_info().
 */
function gofast_element_info_alter(&$type) {
  if (isset($type['textfield'])) {
    // Prepend our process function to apply extended autocomplete settings.
    $type['textfield']['#xac'] = NULL;
    array_unshift($type['textfield']['#process'], 'gofast_process_xac');
  }
}

/**
 * Process function to prepare extended autocomplete data.
 *
 * @param $element
 *   A textfield element with a #autocomplete_path.
 *
 * @return array
 *   The processed form element.
 */
function gofast_process_xac($element) {
  if (isset($element['#xac']['autocomplete_path'])) {
    $element['#autocomplete_path'] = $element['#xac']['autocomplete_path'];
    $xac = array($element['#id'] => $element['#xac']);
    $element['#attributes']['class'][] = 'xAC';
    $element['#attached']['js'][] = array(
      'data' => array('xac' => $xac),
      'type' => 'setting'
    );
  }
  return $element;
}

/**
 * Defines the current context.
 *
 * @see gofast_get_context()
 */
function gofast_set_context($ctxt = NULL) {
  $context = &drupal_static(__FUNCTION__);

  /*if (isset($context)) {
    return $context;
  }*/

  $context = isset($ctxt) ? $ctxt : array();

  $context += array(
    'space' => FALSE,
    'path' => $_GET['q'],
  //  'entity' => FALSE,
    'is_front' => drupal_is_front_page()
  );

  if (!array_key_exists('search', $context)) {
    $item = menu_get_item();
    $page = apachesolr_search_page_load('core_search');
    $context['search'] = $page['search_path'] === $item['path'];
  }

  // Add shortcut keys for entities if loaded.
  if (!empty($context['entity_type'])) {
    $key = in_array($context['entity_type'], array('node', 'user')) ? $context['entity_type'][0] . 'id' : 'etid';
    $context[$key] = $context['entity_id'];
    $context[$context['entity_type']] = TRUE;
  }

  // Send context to the browser.
  drupal_add_js(array('gofast' => array('context' => $context)), 'setting');

  return $context;
}

/**
 * Get the context of the current page / script.
 *
 *  A context array contains several properties, each key is a context property
 *  with each property being non exclusive. That means the caller is free to
 *  determine whether an hypothetical (targeted) context matches a specific
 *  property or a combination (union|intersection) of properties.
 *
 *  - 'path': the current path of the page.
 *  - 'search': boolean stating whether or not user is on a search page.
 *  - 'space': states whether or not user is viewing a space node.
 *  - 'entity': an entity object if viewing an entity in 'full' mode, FALSE
 *    otherwise. If an entity is set, additional parameters are provided :
 *    - 'entity_id': specify the entity id.
 *    - 'entity_type': specify the entity type.
 *    Shortcuts are automatically added, e.g. for a node :
 *    - 'node' => TRUE
 *    - 'nid' => [nid]
 *
 * @return mixed
 *  An array of context property if the context is defined, NULL otherwise.
 */
function gofast_get_context() {
  return gofast_set_context();
}

/**
 * Calling this function ensures we have at least a default context structure
 * set and that the object is sent to the client even if the context has not
 * been explicitly set.
 */
function gofast_context_fallback() {
  // NULL is intended here, defaults should be handled right in the function
  // gofast_set_context() so that fallback can work properly even when there
  // is a context since we use the union operator to merge defaults.
  $ctxt = NULL;
  gofast_set_context($ctxt);
}

/**
 * Creates a Drupal Ajax 'toast' command. Instructs client to toast a message.
 *
 * @param string $message
 *  The message to display.
 *
 * @param string $type [optional]
 *  The type of toast message to display. Defaults to 'info'.
 */
function gofast_command_toast_message($message, $type = 'info', $title = NULL) {
  return array(
    'command' => 'toast',
    'message' => $message,
    'type' => $type,
    'title' => $title
  );
}

/**
 * Creates a Drupal Ajax 'triggerEvent' command. Instructs the client to trigger
 * a javascript event.
 *
 * @param string $context
 *  DOM id of the element to set as the event context.
 *
 * @param string $event_type
 *  A JavaScript event type, such as 'click' or 'submit'.
 *
 * @param mixed $data [optional]
 *  Array of additional parameters to pass along to the event handler.
 */
function gofast_command_trigger_event($context, $event_type, $data = NULL) {
  return array(
    'command' => 'triggerEvent',
    'eventType' => $event_type,
    'context' => $context,
    'data' => $data
  );
}

/**
 * Creates a Drupal Ajax 'callback' command. Instructs the client to execute a
 * a given function callback.
 *
 * @param string $callback
 *  A javascript function callback.
 *
 * @param mixed $data [optional]
 *  Array of additional parameters to pass along to the function callback.
 */
function gofast_command_callback($callback, $data = NULL) {
  return array(
    'command' => 'callback',
    'callback' => $callback,
    'data' => $data
  );
}

/**
 * Creates a Drupal Ajax 'openWindow' command. Instructs the client to execute a
 * a given function callback.
 *
 * @param string $url
 *  The URL to open
 *
 * @param boolean $newtab
 *  Tells if it should be open in a new tab or not, default is true
 */
function gofast_command_open_window($url, $newtab = true) {
  return array(
    'command' => 'openWindow',
    'url' => $url,
    'newtab' => $newtab
  );
}

/**
 * Creates a Drupal Ajax 'processAjax' command. Instructs the client to
 * redirrect to a page using ajax callback
 *
 * @param string $callback
 *  A javascript function callback.
 *
 * @param mixed $data [optional]
 *  Array of additional parameters to pass along to the function callback.
 */
function gofast_command_processAjax($href) {
  return array(
    'command' => 'processAjax',
    'href' => $href
  );
}

/**
 * Creates a Drupal Ajax 'scrollToComment' command. Instructs the client to
 * redirrect to a page using ajax callback
 *
 * @param string $callback
 *  A javascript function callback.
 *
 * @param mixed $data [optional]
 *  Array of additional parameters to pass along to the function callback.
 */
function gofast_command_scrollToComment($href_comment) {
  return array(
    'command' => 'scrollToComment',
    'hrefComment' => $href_comment
  );
}

/**
 * This function allows to transform the generated strings (ex: id="edit-action--2") into id="edit-action"
 * which avoid the missing selectors by id in the behaviors when ajaxifying
 */
function gofast_normalize_string_from_ajaxifying($output) {
  $re = '/(id|for|data-target)="([^"]*)--[0-9]+([^"]*)"/';
  $subst = '$1="$2$3"';
  $ret = preg_replace($re, $subst, $output);
  return $ret;
}

/**
 * Return the title of the given Node
 * @param type $nid
 * @param type $bundle
 * @return string
 */
function gofast_get_node_title($nid, $bundles=array(), $rename_private = FALSE){
  $og_label = '';

  $result = db_select('node', 'n')
      ->fields('n', array('title', 'type', 'uid'))
      ->condition('n.nid', $nid, '=')
      ->execute()
      ->fetchAssoc();

   if( count($result) > 0){
      if($result['type'] == 'private_space' && $rename_private === 2){
        $og_label = user_load($result['uid'])->name;
      }else if($result['type'] == 'private_space' && $rename_private){
        $og_label = gofast_user_display_name($result['uid']);
      }else{
        $og_label = $result['title'];
      }
   }

  return $og_label;
}

function gofast_get_node_title_multiple($nids, $bundles=array(), $rename_private = FALSE){
  $titles = [];

  $results = db_query("SELECT nid,title,type,uid FROM node WHERE nid IN(" . implode(",", $nids) . ") ORDER BY FIELD (nid, " . implode(",", $nids) . ")");

  if (empty($results)) {
    return $titles;
  }

  foreach ($results as $nid => $result) {
    $og_label = '';
    if ($result->type === 'private_space' && $rename_private === 2) {
      $og_label = user_load($result->uid)->name;
    }
    else if ($result->type === 'private_space' && $rename_private) {
      $og_label = gofast_user_display_name($result->uid);
    }
    else {
      $og_label = $result->title;
    }
    $titles[$nid] = $og_label;
  }

  return $titles;
}

/*
 * function which return true if the group receive in parameter is archived, false otherwhise
 */
function gofast_group_is_archive($node){
    if(isset($node->field_archive[LANGUAGE_NONE])){
            if($node->field_archive[LANGUAGE_NONE][0]["value"] == 0){
               return false;
            }else{
                return true;
            }
    }elseif(!isset($node->field_archive) || count($node->field_archive) == 0){
        return false;
    }else{
        return false;
    }
    $array_object["tags"] = $string_tags;
    $array_object["target_link"] = $node->field_target_link[LANGUAGE_NONE][0]['target_id'];
    $array_object["comment_count"] = $node->comment_count;


    if($full == true){
        //TODO get cmis infos
}
    return drupal_json_encode($array_object);
}

function gofast_get_json_object_from_node($node, $full = false){
    $array_object = array();
    $array_object["title"] = $node->title;
    $array_object["language"] = $node->language;
    $array_object["created"] = $node->created;
    $array_object["changed"] = $node->changed;
    //$array_object["body"] = $node->body;
    $array_object["category"] = taxonomy_term_load($node->field_category[LANGUAGE_NONE][0]['tid'])->name;
    $array_object["criticity"] = taxonomy_term_load($node->field_criticity[LANGUAGE_NONE][0]['tid'])->name;
    $array_object["document_author"] = $node->field_document_author[LANGUAGE_NONE][0]['value'];
    $array_object["external_page_url"] = $node->field_external_page_url[LANGUAGE_NONE][0]['value'];
    $array_object["format"] = taxonomy_term_load($node->field_format[LANGUAGE_NONE][0]['tid'])->name;
    $array_object["publication"] = $node->field_publication[LANGUAGE_NONE][0]['target_id'];
    $array_object["field_checkout_infos"] = $node->field_checkout_infos[LANGUAGE_NONE][0]['value'];
    $array_object["field_fdl"] = $node->field_fdl[LANGUAGE_NONE][0]['target_id'];
    foreach($node->field_trigger_event[LANGUAGE_NONE] as $event){
        $array_object["field_trigger_event"] .= taxonomy_term_load($event['tid'])->name . ";";
    }
    $array_object["field_cei"] = $node->field_cei[LANGUAGE_NONE][0]['target_id'];
    $array_object["reference"] = $node->reference;
    $array_object["state"] = taxonomy_term_load($node->field_state[LANGUAGE_NONE][0]['tid'])->name;
    $string_tags = "";
    if(count($node->field_tags[LANGUAGE_NONE])){
        foreach($node->field_tags[LANGUAGE_NONE] as $object_tag){
            $string_tags .= taxonomy_term_load($object_tag["tid"])->name.";";
        }
    }
    if(count($node->field_trigger_event_history[LANGUAGE_NONE])){
        foreach($node->field_trigger_event_history[LANGUAGE_NONE] as $object){
            $string_trigger .= taxonomy_term_load($object["value"])->name . ";";
        }
    }
    if(count($node->field_trigger_event_owners[LANGUAGE_NONE])){
        foreach($node->field_trigger_event_owners[LANGUAGE_NONE] as $object){
            $string_otrigger .= $object["target_id"] . ";";
        }
    }
    $array_object["tags"] = $string_tags;
    $array_object["field_trigger_event_history"] = $string_trigger;
    $array_object["field_trigger_event_owners"] = $string_otrigger;
    $array_object["target_link"] = $node->field_target_link[LANGUAGE_NONE][0]['target_id'];
    $array_object["comment_count"] = $node->comment_count;

    //if the node is a space, construct an array with members list, classified by roles
    if(gofast_og_is_space($node)){
        $members = gofast_og_get_members($node);
        if(count($members > 0)){
            foreach($members as $uid){
                $role = og_get_user_roles("node", $node->nid, $uid, FALSE);
                $role_string = reset($role);
                $array_object[$role_string][$uid] = $uid;
            }
            sort($array_object["group contributor"]);
            $array_object["group contributor"] = implode(",", $array_object["group contributor"]);
            sort($array_object["administrator member"]);
            $array_object["administrator member"] = implode(",", $array_object["administrator member"]);
            sort($array_object["read only member"]);
            $array_object["read only member"] = implode(",", $array_object["read only member"]);
        }

    }

    if($full == true){
        //TODO get cmis infos
    }
    return drupal_json_encode($array_object);
}

function gofast_get_json_object_from_orig_node($nid, $orig_domain){
  $url = $orig_domain."/check/integrity?nid=".$nid;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  //curl_setopt($ch, CURLOPT_HEADER, TRUE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  curl_setopt($ch, CURLOPT_PROXY, "");
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 0);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 0);
  $buf = curl_exec($ch);

  curl_close($ch);
  //var_dump($nid);var_dump($buf);var_dump($url);exit;
  return $buf;
}

function gofast_compare_json_objects($json_orig, $json_dest){
    $object_orig = drupal_json_decode($json_orig);
    $object_dest = drupal_json_decode($json_dest);

    if(!empty($object_orig["field_checkout_infos"][0]['value'])){
        $object_orig["field_checkout_infos"] = $object_orig["field_checkout_infos"][0]['value'];
        $object_orig["field_checkout_infos"] = str_replace("{", "", $object_orig["field_checkout_infos"]);
        $object_orig["field_checkout_infos"] = str_replace("}", "", $object_orig["field_checkout_infos"]);
    }else{
        $object_orig["field_checkout_infos"] = NULL;
    }

    if(!empty($object_orig["field_cei"][0]['nid'])){
        $object_orig["field_cei"] = $object_orig["field_cei"][0]['nid'];
    }else{
        $object_orig["field_cei"] = NULL;
    }

    if(!empty($object_orig["field_fdl"][0]['nid'])){
        $object_orig["field_fdl"] = $object_orig["field_fdl"][0]['nid'];
    }else{
        $object_orig["field_fdl"] = NULL;
    }

    foreach($object_orig["field_trigger_event_history"] as $object){
      if(!empty($object)){
        $output_teh .= $object . ";";
      }
    }
    $object_orig["field_trigger_event_history"] = $output_teh;

    foreach($object_orig["field_trigger_event_owners"] as $object){
      if(!empty($object['uid'])){
        $output_own .= $object['uid'] . ";";
      }
    }
    $object_orig["field_trigger_event_owners"] = $output_own;

    $diff = array();
    foreach($object_dest as $key=>$value){
        if($object_orig[$key] != $object_dest[$key]){
            $diff[$key] = $object_orig[$key]." / ".$object_dest[$key];
        }
    }

    return $diff;
}

function gofast_batch_integrity(){
    $orig_domain = $_GET["orig_domain"];
    $batch = array(
            'title' => t('Check integrity'),
            'operations' => array(
              array('batch_check_integrity', array($gid, $orig_domain)),
            ),
            'finished' => 'batch_check_integrity_finish',
          );
    batch_set($batch);
    // Only needed if not inside a form _submit handler.
    // Setting redirect in batch_process.
    batch_process("node");
}

function gofast_get_nodes_for_integrity_check(){
    //$nids = array("1096","1097","1090","1095","381");
     $res = db_query("SELECT nid
          FROM {node}
          WHERE status = 1 AND type != 'private_space'", array());

    $nids = array();
  foreach ($res as $nid) {
      $nids[] = $nid->nid;
  }
    return $nids;
}

function batch_check_integrity($gid,$orig_domain,&$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    $all_nids = gofast_get_nodes_for_integrity_check();
    $context['sandbox']['max'] = count($all_nids);
  }



  $all_nids = gofast_get_nodes_for_integrity_check();

  $limit = 1;
  $cut_all_nids = array_slice($all_nids,$context['sandbox']['current_node'], $limit, true);

  foreach($cut_all_nids as $key => $nid){
    $node = node_load($nid, NULL, TRUE);

    $json_orig = gofast_get_json_object_from_orig_node($node->nid, $orig_domain);
    $json_dest = gofast_get_json_object_from_node($node);

    $diff = gofast_compare_json_objects($json_orig,$json_dest);

    $context['results'][$node->nid] = $diff;
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $key+1;
    $context['message'] = $node->title;
  }


  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}


function batch_check_integrity_finish($success, $results, $operations) {
  if ($success) {
    $message = format_plural(count($results), 'One post processed.', '@count posts processed.');
  }
  else {
    $message = t('Finished with an error.');
  }
  drupal_set_message($message);
  // Providing data for the redirected page is done through $_SESSION.
  $diff = array();
  foreach ($results as $key=> $result) {
    if(count($result)> 0){
        $diff[$key] = $result;
    }

  }

  variable_set("gofast_result_integrity_check", $diff);

}

function gofast_array_diff_recursive($aArray1, $aArray2, $compare_keys = TRUE, $base_array = array()) {
  $aReturn = array();

  foreach ($aArray1 as $mKey => $mValue) {
    if (array_key_exists($mKey, $aArray2)) {
      if (is_array($mValue)) {
        $aRecursiveDiff = gofast_array_diff_recursive($mValue, $aArray2[$mKey], $compare_keys, $aArray2);
        if (count($aRecursiveDiff)) { $aReturn[$mKey] = $aRecursiveDiff; }
      } else {
        if($compare_keys){
          if ($mValue != $aArray2[$mKey]) {
            $aReturn[$mKey] = $mValue;
          }
        }else{
          if (!in_array($aArray1, $base_array, TRUE)) {
            $aReturn[$mKey] = $mValue;
          }
        }
      }
    } else {
      $aReturn[$mKey] = $mValue;
    }
  }
  return $aReturn;
}

// Remove unwanted HTML comments
function gofast_remove_html_comments($content = '') {
	return preg_replace('/<!--(.|\s)*?-->/', '', $content);
}

function gofast_remove_accents($str) {
  $a = array('À', 'Á', 'Â', 'Ã', 'Ä', 'Å', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', 'Ø', 'Ù', 'Ú', 'Û', 'Ü', 'Ý', 'ß', 'à', 'á', 'â', 'ã', 'ä', 'å', 'æ', 'ç', 'è', 'é', 'ê', 'ë', 'ì', 'í', 'î', 'ï', 'ñ', 'ò', 'ó', 'ô', 'õ', 'ö', 'ø', 'ù', 'ú', 'û', 'ü', 'ý', 'ÿ', 'Ā', 'ā', 'Ă', 'ă', 'Ą', 'ą', 'Ć', 'ć', 'Ĉ', 'ĉ', 'Ċ', 'ċ', 'Č', 'č', 'Ď', 'ď', 'Đ', 'đ', 'Ē', 'ē', 'Ĕ', 'ĕ', 'Ė', 'ė', 'Ę', 'ę', 'Ě', 'ě', 'Ĝ', 'ĝ', 'Ğ', 'ğ', 'Ġ', 'ġ', 'Ģ', 'ģ', 'Ĥ', 'ĥ', 'Ħ', 'ħ', 'Ĩ', 'ĩ', 'Ī', 'ī', 'Ĭ', 'ĭ', 'Į', 'į', 'İ', 'ı', 'Ĳ', 'ĳ', 'Ĵ', 'ĵ', 'Ķ', 'ķ', 'Ĺ', 'ĺ', 'Ļ', 'ļ', 'Ľ', 'ľ', 'Ŀ', 'ŀ', 'Ł', 'ł', 'Ń', 'ń', 'Ņ', 'ņ', 'Ň', 'ň', 'ŉ', 'Ō', 'ō', 'Ŏ', 'ŏ', 'Ő', 'ő', 'Œ', 'œ', 'Ŕ', 'ŕ', 'Ŗ', 'ŗ', 'Ř', 'ř', 'Ś', 'ś', 'Ŝ', 'ŝ', 'Ş', 'ş', 'Š', 'š', 'Ţ', 'ţ', 'Ť', 'ť', 'Ŧ', 'ŧ', 'Ũ', 'ũ', 'Ū', 'ū', 'Ŭ', 'ŭ', 'Ů', 'ů', 'Ű', 'ű', 'Ų', 'ų', 'Ŵ', 'ŵ', 'Ŷ', 'ŷ', 'Ÿ', 'Ź', 'ź', 'Ż', 'ż', 'Ž', 'ž', 'ſ', 'ƒ', 'Ơ', 'ơ', 'Ư', 'ư', 'Ǎ', 'ǎ', 'Ǐ', 'ǐ', 'Ǒ', 'ǒ', 'Ǔ', 'ǔ', 'Ǖ', 'ǖ', 'Ǘ', 'ǘ', 'Ǚ', 'ǚ', 'Ǜ', 'ǜ', 'Ǻ', 'ǻ', 'Ǽ', 'ǽ', 'Ǿ', 'ǿ', 'Ά', 'ά', 'Έ', 'έ', 'Ό', 'ό', 'Ώ', 'ώ', 'Ί', 'ί', 'ϊ', 'ΐ', 'Ύ', 'ύ', 'ϋ', 'ΰ', 'Ή', 'ή');
  $b = array('A', 'A', 'A', 'A', 'A', 'A', 'AE', 'C', 'E', 'E', 'E', 'E', 'I', 'I', 'I', 'I', 'D', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'U', 'U', 'U', 'U', 'Y', 's', 'a', 'a', 'a', 'a', 'a', 'a', 'ae', 'c', 'e', 'e', 'e', 'e', 'i', 'i', 'i', 'i', 'n', 'o', 'o', 'o', 'o', 'o', 'o', 'u', 'u', 'u', 'u', 'y', 'y', 'A', 'a', 'A', 'a', 'A', 'a', 'C', 'c', 'C', 'c', 'C', 'c', 'C', 'c', 'D', 'd', 'D', 'd', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'E', 'e', 'G', 'g', 'G', 'g', 'G', 'g', 'G', 'g', 'H', 'h', 'H', 'h', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'I', 'i', 'IJ', 'ij', 'J', 'j', 'K', 'k', 'L', 'l', 'L', 'l', 'L', 'l', 'L', 'l', 'l', 'l', 'N', 'n', 'N', 'n', 'N', 'n', 'n', 'O', 'o', 'O', 'o', 'O', 'o', 'OE', 'oe', 'R', 'r', 'R', 'r', 'R', 'r', 'S', 's', 'S', 's', 'S', 's', 'S', 's', 'T', 't', 'T', 't', 'T', 't', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'W', 'w', 'Y', 'y', 'Y', 'Z', 'z', 'Z', 'z', 'Z', 'z', 's', 'f', 'O', 'o', 'U', 'u', 'A', 'a', 'I', 'i', 'O', 'o', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'U', 'u', 'A', 'a', 'AE', 'ae', 'O', 'o', 'Α', 'α', 'Ε', 'ε', 'Ο', 'ο', 'Ω', 'ω', 'Ι', 'ι', 'ι', 'ι', 'Υ', 'υ', 'υ', 'υ', 'Η', 'η');
  return str_replace($a, $b, $str);
}

/*
 * Change time zone
 * @param $dateString
 *   The date to convert
 * @param $timeZoneSource
 *   The $dateString time zone
 * @param $timeZoneTarget
 *   The wanted time zone
 * @return
 *   The date formatted as string
 */
function gofast_change_time_zone($dateString, $timeZoneSource = null, $timeZoneTarget = null)
{
  if (empty($timeZoneSource)) {
    $timeZoneSource = date_default_timezone_get();
  }
  if (empty($timeZoneTarget)) {
    $timeZoneTarget = date_default_timezone_get();
  }

  $dt = new DateTime($dateString, new DateTimeZone($timeZoneSource));
  $dt->setTimezone(new DateTimeZone($timeZoneTarget));

  return $dt->format("Y-m-d H:i:s");
}


function gofast_api_get_render_all_comments($node){
    $comment_default_per_page = variable_get('comment_default_per_page_' . $node->type, 50);
    variable_set('comment_default_per_page_' . $node->type, 9999999);
    $node_view = node_view($node);
    $node_view['comments'] = comment_node_page_additions($node);
    $comment_render = drupal_render($node_view['comments']);
    variable_set('comment_default_per_page_' . $node->type, 1);
    print $comment_render;
}

function gofast_get_reverse_url_alias($path){
     // var_dump(strpos($path, 'content/'));exit;
    if (strpos($path, 'content/') === false) {
        return false;
    }

    $node_string = db_query('SELECT src FROM {'.GOFAST_REVERSE_ALIAS_REDIRECTION_TABLE.'}  WHERE dst = :dst', array(':dst' => $path))->fetchField();
    if($node_string !== false){
       return str_replace("node/", "", $node_string);
    }else{
        return false;
    }

}

function gofast_form_unset_error($name) {
  $errors = &drupal_static('form_set_error', array());
  $removed_messages = array();
  if (isset($errors[$name])) {
    $removed_messages[] = $errors[$name];
    unset($errors[$name]);
  }
  $_SESSION['messages']['error'] = array_diff($_SESSION['messages']['error'], $removed_messages);

  if (empty($_SESSION['messages']['error'])) {
    unset ($_SESSION['messages']['error']);
  }

}

function gofast_resynchro_ldap_membership_one_user($account){
    $uid = $account->uid;

    //in order to load spaces even if we are during hook_login
    $account = user_load($uid);

    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $all_groups = gofast_og_get_spaces_by_user($account, TRUE, FALSE, FALSE,FALSE);
    $must_be_manager = false;
    $member_cn = gofast_ldap_user_dn($account);
    $count_public = 0;
    foreach($all_groups as $key=>$space){
        $gid = $key;
        if($gid == 0){
            continue;
        }

        //check if this user is already correctly set into ldap
        //first check membership ( don't care of role )

    $space = node_load($gid);

    //if it's a public space, increment counter
    if($space->type == "public"){
        $count_public = $count_public + 1;
    }

    $dn = gofast_ldap_space_dn($space);
    $members = $LdapServer->groupAllMembers($dn);
     if(array_search(strtolower($member_cn), array_map('strtolower', $members)) === false){
            watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE", "Membership of user ".$account->uid." added on space ".$space->nid);
            $membership = new OgMembership();
            $membership->entity_type = 'user';
            $membership->field_name = GOFAST_OG_USER_MEMBERSHIP_FIELD;
            $membership->gid = $gid;
            $membership->etid = $uid;
            $membership->state = 1;
            gofast_ldap_og_membership_insert($membership);
      }

        $roles = gofast_og_get_user_roles($gid, $uid);
        $role = array_shift(array_values( $roles));
        if($role == "administrator member" && $space->type != "private_space"){
            $must_be_manager = true;
        }
        $rid = array_keys($roles)[0];
         //check if the user already have this role into LDAP object
         $role_suffix = gofast_ldap_og_roles_map($role);
         if($role_suffix === "ADMIN"){
              $dn = gofast_ldap_space_dn($space);
              $cn = gofast_ldap_space_cn($space);
              $members = $LdapServer->groupAllMembers("cn={$cn}_ADMIN,{$dn}");
               if(array_search($member_cn,$members) === false){
                watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE", "Admin role of user ".$account->uid." added on space ".$space->nid);
                gofast_ldap_og_role_grant('node', $gid, $uid, $rid);
               }
         }elseif($role_suffix === "STANDARD"){
              $dn = gofast_ldap_space_dn($space);
               $cn = gofast_ldap_space_cn($space);
              $members = $LdapServer->groupAllMembers("cn={$cn}_STANDARD,{$dn}");
               if(array_search($member_cn,$members) === false){
                watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE", "Standard role of user ".$account->uid." added on space ".$space->nid);
                gofast_ldap_og_role_grant('node', $gid, $uid, $rid);
               }
         }

    }

    //check if user is correctly set into LDAP for userlists
     $userlists = gofast_userlist_get_userlists_by_user($account);

        if(count($userlists)){
            foreach($userlists as $key=>$userlist){
                $ulid = $userlist->ulid;
                $userlist = entity_load_single('userlist', $ulid);
                $dn_userlist = array('dn' => array(UserListEntity::getDn($userlist)));
                $members_userlist_ldap = $LdapServer->groupAllMembers($dn_userlist["dn"][0]);
                if(array_search(strtolower($member_cn), array_map('strtolower', $members_userlist_ldap)) === false){
                    watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON USERLIST", "Membership of user ".$account->uid." added on userlist ".$userlist->ulid);
                    $member = array('dn' => array(gofast_ldap_user_dn($account)));
                    $LdapServer->groupAddMember($dn_userlist["dn"][0], $member_cn);
                }
            }
        }

    //check if the user is not into Public spaces ( it can happened sometime )
    //get all public spaces
     $root_spaces = gofast_og_get_root_spaces(FALSE, TRUE);
      foreach($root_spaces as $nid){ //We fetch into the root spaces (excluding private spaces)
        $node = node_load($nid);
        $bundle = $node->type;
        if($bundle == 'public'){
          $public = $node;
        }
      }
    $public_ids = gofast_og_get_children($public->nid, TRUE, FALSE, TRUE);
    if(!gofast_user_is_extranet($account) && $count_public != count($public_ids)+1 && count($public_ids) !== 0){
         watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON PUBLIC SPACES", "user ".$account->uid);
         gofast_og_user_rebuild_base_memberships($account);
    }

    //check if user is on a space on LDAP but not on Drupal
    gofast_resynchro_ldap_remove_bad_ldap($account);


     if($must_be_manager == true){
        //check if the user has the manager's role
        if(!gofast_user_is_manager($account)){
              $role_manager = user_role_load_by_name(GOFAST_ROLE_MANAGER);
              user_multiple_role_edit(array($account->uid), 'add_role', $role_manager->rid);
        }
    }else{
         if(gofast_user_is_manager($account)){
              $role_manager = user_role_load_by_name(GOFAST_ROLE_MANAGER);
              user_multiple_role_edit(array($account->uid), 'remove_role', $role_manager->rid);
        }
    }
}

function gofast_resynchro_ldap_remove_bad_ldap($account){
 $member_cn = gofast_ldap_user_dn($account);
 $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
 $ldap_spaces = $LdapServer->groupUserMembershipsFromEntry($member_cn, false);
 $isAdmin= !empty($account->roles['3']);
 $addFolderTemplate = false;
 foreach($ldap_spaces as $mydn){
      if (strpos($mydn, 'cn=ADMIN_GOFAST') !== false){
        if($isAdmin){
          if($addFolderTemplate === false){
            continue;
          }
        }
      }else{
        if ($isAdmin) {
          $addFolderTemplate = true;
        }
      }
      $gid = gofast_ldap_gid_from_dn($mydn);
      if( $gid == false){
           //userlist
            //get nid from cn
            $query =  db_select('field_revision_field_ldap_group_dn', 'n')
          ->fields('n', array('entity_id'))
          ->condition('field_ldap_group_dn_value', $mydn)
          ->execute();
           $result = $query->fetch();
           $gid = $result->entity_id;

           $userlist_node = node_load($gid);
           $ulid = $userlist_node->field_userlist_ulid[LANGUAGE_NONE][0]["value"];
           $is_member = gofast_userlist_is_member_of($ulid, $account->uid);

            if(!$is_member){
                 $member = array('dn' => array($member_cn));
                 $LdapServer->groupRemoveMember($mydn, $member);
                 watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE", "Remove user ".$account->uid." from LDAP entry ".$mydn);
            }

       }else{
            //check if user is member of this space
             $is_member = og_is_member("node", $gid, 'user', $account);
            if(!$is_member){
                    // Remove user membership from the corresponding ldap entry (groups).
                     $node = node_load($gid);
                     if($node->type == "private_space"){
                         return;
                     }
                     $dn = gofast_ldap_space_dn($node);
                     $member = array('dn' => array($member_cn));

                     $LdapServer->groupRemoveMember($dn, $member);

                     // Space dn and relative dn are needed to specify which space role entry is
                     // going to be provisioned.
                     $space = node_load($gid);
                     $cn = gofast_ldap_space_cn($space);
                     $dn = gofast_ldap_space_dn($space);

                     $LdapServer->groupRemoveMember("cn={$cn}_ADMIN,{$dn}", $member);
                     $LdapServer->groupRemoveMember("cn={$cn}_STANDARD,{$dn}", $member);
                     watchdog("GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE", "Remove user ".$account->uid." from LDAP entry ".$mydn);
            }
      }

    }
    if($addFolderTemplate){
    // Add the user into ADMIN_GOFAST Ldap entity
    $ldap_basedn = variable_get('gofast_ldap_int_base_dn');
    $attributes = array();
    $attributes['objectclass'] = array('groupOfNames');
    $attributes['description'] = GOFAST_ADMIN_PLATFORM;
    $attributes['cn'] = GOFAST_ADMIN_PLATFORM;
    $gofast_ldap_gofast_admin_basedn = 'cn=' . $attributes['cn'] . ',ou=Groups,' . $ldap_basedn;
      watchdog('GOFAST REBUILD MEMBERSHIP ONE USER ON SPACE', "Remove user ".$account->uid." from LDAP entry ADMIN_GOFAST");
      $LdapServer->groupAddMember($gofast_ldap_gofast_admin_basedn, $account);
    }
}

function gofast_repair_membership_one_user($account){
    $uid = $account->uid;

    $all_groups = $account->og_user_node["und"];
    foreach($all_groups as $key=>$space){
        $gid = $space["target_id"];
        $role = gofast_og_get_user_roles($gid, $uid);
        if(count($role) == 0){
            gofast_og_unsubscribe_user($gid, $uid);
        }
    }
}

function gofast_resynchro_ldap_membership_one_space($space){
   $members = gofast_og_get_members($space);
     $theorically_ro = array();
     $theorically_standard = array();
     $theorically_admin = array();
     foreach($members as $uid){
        if($uid == 1){continue;}
        $membership = og_get_membership('node', $space->nid, 'user', $uid);
        $account = user_load($membership->etid);
        $member_cn = gofast_ldap_user_dn($account);
        $role = gofast_og_get_user_roles($membership->gid, $membership->etid);
        $role =  array_shift(array_values($role));
         if($role == "read only member"){
              $theorically_ro[] =  $member_cn;
         }elseif($role == "group contributor"){
              $theorically_standard[] =  $member_cn;
              $theorically_ro[] =  $member_cn;
         }elseif($role == "administrator member"){
              $theorically_admin[] =  $member_cn;
              $theorically_ro[] =  $member_cn;
        }

      }

        $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
        $dn = gofast_ldap_space_dn($space);
        $cn = gofast_ldap_space_cn($space);

       //check if ldap entity exists
       $group_entry =  $LdapServer->dnExists($dn, 'ldap_entry', array());
       if($group_entry == null){
           gofast_ldap_node_insert($space);
       }

        $member = array('dn' => array(gofast_ldap_user_dn($account)));
        $ldap_ro = _gofast_remove_admin_and_userslists_ldap_members_integrity_check($LdapServer->groupAllMembers($dn));
        $ldap_admin = _gofast_remove_admin_and_userslists_ldap_members_integrity_check($LdapServer->groupAllMembers("cn={$cn}_ADMIN,{$dn}"));
        $ldap_standard = _gofast_remove_admin_and_userslists_ldap_members_integrity_check($LdapServer->groupAllMembers("cn={$cn}_STANDARD,{$dn}"));

       //compare each arrays
       if(count(array_udiff($ldap_ro,$theorically_ro, 'strcasecmp')) > 0 || count(array_udiff($ldap_admin,$theorically_admin, 'strcasecmp')) > 0 || count(array_udiff($ldap_standard,$theorically_standard, 'strcasecmp')) > 0
          || count(array_udiff($theorically_ro, $ldap_ro, 'strcasecmp')) > 0 || count(array_udiff($theorically_admin, $ldap_admin, 'strcasecmp')) > 0 || count(array_udiff($theorically_standard, $ldap_standard, 'strcasecmp')) > 0  ){
           watchdog("GOFAST REBUILD MEMBERSHIP SPACE", $space->nid);

            $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
            $dn = gofast_ldap_space_dn($space);
            $cn = gofast_ldap_space_cn($space);

           //first, manage when a user is on LDAP but not on Drupal
           if(count(array_udiff($theorically_ro, $ldap_ro, 'strcasecmp')) > 0 || count(array_udiff($ldap_ro, $theorically_ro, 'strcasecmp' )) > 0){
                $not_in_drupal = array_udiff($ldap_ro, $theorically_ro, 'strcasecmp');
                $not_in_ldap = array_udiff($theorically_ro, $ldap_ro, 'strcasecmp');
                if(count($not_in_drupal) > 0){
                    foreach($not_in_drupal as $entry){
                        $LdapServer->groupRemoveMember($dn,  $entry);
                    }
                }
                if(count($not_in_ldap) > 0){
                    foreach($not_in_ldap as $entry){
                        $LdapServer->groupAddMember($dn,  $entry);
                    }
                }
           }

            if(count(array_udiff($theorically_admin, $ldap_admin, 'strcasecmp')) > 0 || count(array_udiff($ldap_admin, $theorically_admin, 'strcasecmp')) > 0){
                $not_in_drupal = array_udiff($ldap_admin, $theorically_admin, 'strcasecmp');
                $not_in_ldap = array_udiff($theorically_admin, $ldap_admin, 'strcasecmp');
                if(count($not_in_drupal) > 0){
                    foreach($not_in_drupal as $entry){
                         $LdapServer->groupRemoveMember("cn={$cn}_ADMIN,{$dn}",  $entry);
                    }
                }
                if(count($not_in_ldap) > 0){
                    foreach($not_in_ldap as $entry){
                        $LdapServer->groupAddMember("cn={$cn}_ADMIN,{$dn}",  $entry);
                    }
                }
           }

            if(count(array_udiff($theorically_standard, $ldap_standard, 'strcasecmp')) > 0 || count(array_udiff($ldap_standard, $theorically_standard, 'strcasecmp' )) > 0){
                $not_in_drupal = array_udiff($ldap_standard, $theorically_standard, 'strcasecmp');
                $not_in_ldap = array_udiff($theorically_standard, $ldap_standard, 'strcasecmp');
                if(count($not_in_drupal) > 0){
                    foreach($not_in_drupal as $entry){
                       $LdapServer->groupRemoveMember("cn={$cn}_STANDARD,{$dn}",  $entry);
                    }
                }
                if(count($not_in_ldap) > 0){
                    foreach($not_in_ldap as $entry){
                        $LdapServer->groupAddMember("cn={$cn}_STANDARD,{$dn}",  $entry);
                    }
                }

           }

      }

}

function _gofast_remove_admin_and_userslists_ldap_members_integrity_check($members){
    if(count($members) > 0){
          foreach($members as $key=>$member){
                   if(strpos($member, "uid=admin")  !== FALSE || strpos($member, "ou=UserLists")  !== FALSE){
                              unset($members[$key]);
                   }
          }
    }

    return $members;
}


function gofast_block_users_massively($block = array(), $pass = array(), $exceptions = array("", "adm", "admin")){
  set_time_limit(0);

  foreach (entity_load('user') as $user) { //Fetch into users
    $mail = $user->mail;
    $login = $user->name;
    $uid = $user->uid;

    if (in_array($login, $exceptions, TRUE)) { //This user is an exception and shouldn't be blocked
      print "EXCEPTION : The user $login/$uid is registered as an exception. Won't block.\n";
      continue;
    }

    foreach ($pass as $pattern) { //Check all patterns that should pass the test
      if (strrpos($mail, $pattern) !== FALSE) { //Match found
        print "PASS : The user $login/$uid is registered as an allowed user. Won't block.\n";
        continue 2;
      }
    }

    foreach ($block as $pattern) { //Check all patterns that shouldn't pass the test
      if (strrpos($mail, $pattern) !== FALSE) { //Match found
        print "BLOCK : The user $login/$uid is registered as an unallowed user. Will block.\n";

        //Block the user
        $user->status = 0;
        user_save($user);

        continue 2;
      }
    }

    //We don't know what to do with this user
    print "UNREGISTERED : The user $login/$uid is not registered. Won't block, you may consider to do some manual actions.\n";
  }
}


function gofast_is_node_inside_space($node,$gid){
    $node_groups = $node->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}[LANGUAGE_NONE];
    if(count($node_groups) > 0){
        foreach($node_groups as $key=>$group_array){
            if($group_array["target_id"] == $gid){
                return true;
            }
        }
    }
    return false;
}

function gofast_get_node_status_from_nid($nid){
     $status = db_select('node_revision')
          ->fields('node_revision', array('status'))
          ->condition('nid', $nid, '=')
          ->execute()
          ->fetchField();

     return $status;
}

/**
 * Creating date collection between two dates
 *
 * <code>
 * <?php
 * # Example 1
 * date_range("2014-01-01", "2014-01-20", "+1 day", "m/d/Y");
 *
 * # Example 2. you can use even time
 * date_range("01:00:00", "23:00:00", "+1 hour", "H:i:s");
 * </code>
 *
 * @author Ali OYGUR <alioygur@gmail.com>
 * @param start timestamp
 * @param stop timestamp
 * @param string step
 * @param string date of output format
 * @return array
 */
function gofast_time_range($current, $last, $step = '+1 day') {

    $dates = array();

    while( $current <= $last ) {

        $dates[] = $current;
        $current = strtotime($step, $current);
    }

    return $dates;
}

/*
 * Build an array containing a value multiple times
 */
function gofast_build_array_repeat($value, $repeat){
  $return = array();
  foreach(range(1, $repeat) as $v){
    $return[] = $value;
  }
  return $return;
}

/*
 * Format array of times
 */
function gofast_format_date_array($times, $format = 'medium'){
  $return = array();

  foreach($times as $time){
    $return[] = format_date($time, $format);
  }

  return $return;
}

function gofast_folder_size ($dir)
{
    $size = 0;
    foreach (glob(rtrim($dir, '/').'/*', GLOB_NOSORT) as $each) {
        $size += is_file($each) ? filesize($each) : folderSize($each);
    }
    return $size;
}


function gofast_node_alfresco_item_integrity_check($node){
    $report = array("nid" => $node->nid);

    //first we check if the node is an alfresco item
    if ($node->type !== 'alfresco_item'){
        $report["type"]["status"] = "error";
        $report["type"]["message"] = "Node is not an alfresco item";
        return $report;
    }

    // Check integrity between Alfresco location and node field location
    $parent = gofast_cmis_item_get_parent($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
    $parents_formatted = array();
    if(count($parent->objectList) > 0){
       foreach($parent->objectList as $myparent){
           $parents_formatted[] = array("value" => htmlspecialchars($myparent->properties["cmis:path"]));
       }
    }

    $is_equal = $parents_formatted === $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
    if($is_equal === false){
        $report["locations"]["status"] = "error";
        $report["locations"]["message"] = "Node locations are not corrects.<br />";
        $report["locations"]["message"] .= "Alfresco : ".json_encode($parents_formatted)."<br />";
        $report["locations"]["message"] .= "Drupal : ".json_encode($node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE]);
    }


    //check if spaces corresponds to locations
    $current_groups_array = array();
    $groups_array = array();
    foreach($node->og_group_content_ref[LANGUAGE_NONE] as $space){
      $current_groups_array[$space["target_id"]] = $space["target_id"];
    }
    sort($current_groups_array);

    foreach($parents_formatted as $key=>$parent_path){
       $group_id = gofast_og_get_group_id_from_title_2(htmlspecialchars_decode($parent_path["value"]), TRUE);
       $groups_array[$group_id] = $group_id;
    }
    sort($groups_array);

    if($groups_array !== $current_groups_array){
        $report["spaces"]["status"] = "error";
        $report["spaces"]["message"] = "Node spaces are not corrects.<br />";
        $report["spaces"]["message"] .= "Theorical : ".json_encode($groups_array)."<br />";
        $report["spaces"]["message"] .= "Current : ".json_encode($current_groups_array);
    }

    //check Alfresco permissions
    $permissions = gofast_cmis_webservice_item_get_permissions($node->reference);
    //if the document inherit permissions, it means it's member of only one space. If not, there is a problem
    if($permissions[0] == "inherit_permission"){
        if(count($current_groups_array) > 1){
            $report["permissions"]["status"] = "error";
            $report["permissions"]["message"] = "Node permissions are not corrects.The node is member of multiple spaces, but it inherit permissions <br />";
       }
    }else{
       $result_permissions = array();
       foreach($current_groups_array as $space_id){
           foreach($permissions as $permission_string){
                    if(strpos($permission_string,"_#".$space_id."_") !== FALSE || strpos($permission_string,"_#".$space_id.";") !== FALSE ){
                                  $result_permissions[$space_id] = $result_permissions[$space_id] +1;
                    }
           }
      }
      //then we check if the $result_permissions contains one line for each space,with value 3
        foreach($current_groups_array as $space_id){
                  if(isset($result_permissions[ $space_id]) && $result_permissions[$space_id] == 3){

                  }else{
                            $report["permissions"]["status"] = "error";
                            $report["permissions"]["message"] .= "Node permissions are not corrects.The node is member of multiple spaces, but it doesn't have correct permissions for space with id ".$space_id."<br />";
                 }
        }
    }

    return $report;
}

function gofast_dashboard(){
   $status = variable_get("gofast_status",  array());

   $alfresco_process_rendered = theme("gofast_dashboard_process", array("name" => "alfresco", "state" => $status["alfresco"]["state"], "timestamp" =>  $status["alfresco"]["timestamp"], "button" => true, "autorestart" => $status["alfresco"]["autorestart"]));
   $bonita_process_rendered = theme("gofast_dashboard_process", array("name" => "bonita", "state" => $status["bonita"]["state"], "timestamp" =>  $status["bonita"]["timestamp"], "button" => true, "autorestart" => $status["bonita"]["autorestart"]));
   $solr_process_rendered = theme("gofast_dashboard_process", array("name" => "solr", "state" => $status["solr"]["state"], "timestamp" =>  $status["solr"]["timestamp"], "button" => true, "autorestart" => $status["solr"]["autorestart"]));
   $soffice_process_rendered = theme("gofast_dashboard_process", array("name" => "soffice", "state" => $status["soffice"]["state"], "timestamp" =>  $status["soffice"]["timestamp"], "button" => true, "autorestart" => $status["soffice"]["autorestart"]));
   $cron_process_rendered = theme("gofast_dashboard_process", array("name" => "cron", "state" => $status["cron"]["state"], "timestamp" =>  $status["cron"]["timestamp"], "button" => false, "autorestart" => "false"));

    $return = theme('gofast_dashboard', array('alfresco_status' => $alfresco_process_rendered,
                                               'bonita_status' => $bonita_process_rendered,
                                               'solr_status' =>$solr_process_rendered,
                                               'soffice_status' => $soffice_process_rendered,
                                               'cron_status' => $cron_process_rendered,
                                        ));
    return $return;
}

function theme_gofast_dashboard_process($variables){
    $name = $variables["name"];
    $state = $variables["state"];
    $timestamp = $variables["timestamp"];
    $button = $variables["button"];
    $autorestart = $variables["autorestart"];
    $return = "";

    //state
    if($state == "KO"){
        $return .= "<div class='panel panel-danger' style='margin:3px;'>";
    }else{
        $return .= "<div class='panel panel-success' style='margin:3px;'>";
    }

    //Title
    $return .= '<div class="panel-heading">'.$name.'</div>';

    //Body
    $return .= '<div class="panel-body" style="height:110px;">';

    if($state == "KO"){
        $return .= t("Service down since")." ".date("j/m/Y H:i:s", $timestamp);
    }else{
      $return .= t("Service up since")." ".date("j/m/Y H:i:s", $timestamp);
    }
    if($button == true){
        $button_restart =  '<button onClick="Gofast.dashboardRestartConfirm(\''.$name.'\');" title="' . t('Restart') . '" type="button" class="btn btn-success"><i class="fa fa-play" aria-hidden="true"></i> ' . t('Restart', array(), array('context' => 'gofast')) . '</button>';
        $button_stop =  '<button onClick="Gofast.dashboardStopConfirm(\''.$name.'\');" title="' . t('Stop') . '" type="button" class="btn btn-danger"><i class="fa fa-stop" aria-hidden="true"></i> ' . t('Stop', array(), array('context' => 'gofast')) . '</button>';
        if($autorestart == "false"){
            $button_ar =  '<button onClick="Gofast.dashboardEnableARConfirm(\''.$name.'\');" title="' . t('Enable AR') . '" type="button" class="btn btn-success"><i class="fa fa-play" aria-hidden="true"></i> ' . t('Enable AR', array(), array('context' => 'gofast')) . '</button>';
        }else{
            $button_ar = '<button onClick="Gofast.dashboardDisableARConfirm(\''.$name.'\');" title="' . t('Disable AR') . '" type="button" class="btn btn-danger"><i class="fa fa-stop" aria-hidden="true"></i> ' . t('Disable AR', array(), array('context' => 'gofast')) . '</button>';
        }
        $return .= '<div class="btn-group" role="group" style="float:right; margin-top:30px;">' . $button_restart.$button_stop.$button_ar . '</div>';
    }
    $return .= "</div></div>";
    return $return;
}

function gofast_dashboard_restart_service($called_manually = false){
    $service_name = $_GET["service"];
     switch ($service_name) {
          case 'alfresco':
            $file = fopen("/var/www/d7/sites/default/files/restart_alfresco.txt", "w+");
            fwrite($file, "restart");
            fclose($file);
            $return = array("OK");
          break;
          case 'bonita':
            $file = fopen("/var/www/d7/sites/default/files/restart_bonita.txt", "w+");
            fwrite($file, "restart");
            fclose($file);
            $return = array("OK");
          break;
          case 'solr':
            $file = fopen("/var/www/d7/sites/default/files/restart_solr.txt", "w+");
            fwrite($file, "restart");
            fclose($file);
            $return = array("OK");
          break;
          case 'soffice':
            $file = fopen("/var/www/d7/sites/default/files/restart_soffice.txt", "w+");
            fwrite($file, "restart");
            fclose($file);
            $return = array("OK");
          break;
          default:
            $return = array("KO");
     }
   if($called_manually == false){
    drupal_json_output($return);
    exit;
   }
}

function gofast_dashboard_autorestart_service(){
   $service_name = $_GET["service"];
   $action = $_GET["action"];
   $return = array("KO");

   if($service_name == "alfresco" || $service_name == "bonita" || $service_name == "solr" || $service_name == "soffice"){
        $gofast_status = variable_get("gofast_status", array());
        if($action == "enableAR"){
            $gofast_status[$service_name]["autorestart"] = "true";
            variable_set("gofast_status",  $gofast_status);
            $return = array("OK");
        }elseif($action == "disableAR"){
            $gofast_status[$service_name]["autorestart"] = "false";
            variable_set("gofast_status",  $gofast_status);
            $return = array("OK");
        }
   }
   drupal_json_output($return);
   exit;
}

function gofast_dashboard_stop_service(){
    $service_name = $_GET["service"];
     switch ($service_name) {
          case 'alfresco':
            $file = fopen("/var/www/d7/sites/default/files/stop_alfresco.txt", "w+");
            fwrite($file, "stop");
            fclose($file);
            $return = array("OK");
          break;
          case 'bonita':
            $file = fopen("/var/www/d7/sites/default/files/stop_bonita.txt", "w+");
            fwrite($file, "stop");
            fclose($file);
            $return = array("OK");
          break;
          case 'solr':
            $file = fopen("/var/www/d7/sites/default/files/stop_solr.txt", "w+");
            fwrite($file, "stop");
            fclose($file);
            $return = array("OK");
          break;
          case 'soffice':
            $file = fopen("/var/www/d7/sites/default/files/stop_soffice.txt", "w+");
            fwrite($file, "stop");
            fclose($file);
            $return = array("OK");
          break;
          default:
            $return = array("KO");
     }
   drupal_json_output($return);
   exit;
}

function gofast_get_soffice_status(){
  $filename = "/var/www/d7/sites/default/files/soffice_status.txt";
  $file = fopen($filename, "r");
  $status = fread($file, filesize($filename));
  fclose($file);

  if(trim($status) == "soffice:OK"){
      return true;
  }else{
      return false;
  }


}

function gofast_check_service_autorestart_activated($service_name){
     $gofast_status = variable_get("gofast_status", array());

     if($gofast_status[$service_name]["autorestart"] == "false"){
         return false;
     }else{
         return true;
     }
}

/*
 * API to add stamp into a PDF document
 * $_GET["nid"] contains the node id
 * $_GET["stamp_text"] contains the stamp text. use following mask to insert variables :
 * %current_date% => current date
 * TODO : add more if needed
 * $_GET["position"] position to put the stamp. See https://manuals.setasign.com/api-reference/setapdf/c/SetaPDF.Stamper#constant_POSITION_CENTER_BOTTOM
 */
function gofast_stamp_add(){
    //first we check if the user is authenticated or not. If not, we only allow this function if the request is made locally ( from Bonitasoft for exemple )
    global $user;
    if($user->uid == 0){
        if($_SERVER["REMOTE_ADDR"] !== "127.0.0.1" && $_SERVER["REMOTE_ADDR"] !== "::1"){
            drupal_access_denied();
            exit;
        }
    }

    //check if the node param is correct
    $nid = $_GET["nid"];
    if(isset($nid)){
        $node = node_load($nid);
        if(!isset($node->nid)){
            drupal_access_denied();
            exit;
        }
       $node_tid = $node->field_format[LANGUAGE_NONE][0]["tid"];
       $tid_pdf =  gofast_taxonomy_get_taxo_id_from_extension("pdf");
       $tid_pdf_image = gofast_taxonomy_get_taxo_id_from_extension("pdf_image");
       if($node_tid != $tid_pdf && $node_tid != $tid_pdf_image){
            drupal_access_denied();
            exit;
       }
    }

    //get the stamp text
     require_once(drupal_get_path('module', 'gofast') .'/gofast.pdf_stamper.api.inc');
    $stamp_text = $_GET["stamp_text"];
    $stamp_text = str_replace("%current_date%", date("j/m/Y H:i:s"), $stamp_text);

    if(isset($_GET["position"])){
        //check if the value is correct
        $string_position = $_GET["position"];
        switch ($string_position) {
           case 'POSITION_CENTER_BOTTOM' :
               $position = SetaPDF_Stamper::POSITION_CENTER_BOTTOM;
              break;
           case 'POSITION_CENTER_MIDDLE' :
               $position = SetaPDF_Stamper::POSITION_CENTER_MIDDLE;
              break;
           case 'POSITION_CENTER_TOP' :
              $position = SetaPDF_Stamper::POSITION_CENTER_TOP;
              break;
           case 'POSITION_LEFT_BOTTOM' :
              $position = SetaPDF_Stamper::POSITION_LEFT_BOTTOM;
              break;
           case 'POSITION_LEFT_MIDDLE' :
               $position = SetaPDF_Stamper::POSITION_LEFT_MIDDLE;
              break;
           case 'POSITION_LEFT_TOP' :
              $position = SetaPDF_Stamper::POSITION_LEFT_TOP;
              break;
           case 'POSITION_RIGHT_BOTTOM' :
              $position = SetaPDF_Stamper::POSITION_RIGHT_BOTTOM;
              break;
           case 'POSITION_RIGHT_MIDDLE' :
               $position = SetaPDF_Stamper::POSITION_RIGHT_MIDDLE;
              break;
           case 'POSITION_RIGHT_TOP' :
               $position = SetaPDF_Stamper::POSITION_RIGHT_TOP;
            break;
           default:
               $position = SetaPDF_Stamper::POSITION_CENTER_BOTTOM;
           break;
          }
        }else{
            $position = SetaPDF_Stamper::POSITION_CENTER_BOTTOM;
        }

    if (isset($_GET['showOnPage'])){
      $string_showOnPage = $_GET['showOnPage'];
        switch ($string_showOnPage) {
          case 'PAGES_ALL' :
            $page_location = SetaPDF_Stamper::PAGES_ALL;
          break;
          case 'PAGES_EVEN' :
            $page_location = SetaPDF_Stamper::PAGES_EVEN;
          break;
          case 'PAGES_FIRST' :
            $page_location = SetaPDF_Stamper::PAGES_FIRST;
          break;
          case 'PAGES_LAST' :
            $page_location = SetaPDF_Stamper::PAGES_LAST;
          break;
          case 'PAGES_ODD' :
            $page_location = SetaPDF_Stamper::PAGES_ODD;
          break;
          default :
            $page_location = SetaPDF_Stamper::PAGES_LAST;
        break;
        }
    }else{
      $page_location = SetaPDF_Stamper::PAGES_LAST;
    }
    if(isset($_GET['textColor'])){
      $textColor = $_GET['textColor'];
    }
    if(isset($_GET['translate_y'])){
      $translateY = $_GET['translate_y'];
    }else{
      $translateY = 0;
    }
    $options = array(
    'position' => $position,
    'showOnPage' => $page_location,
    'translateX' => -60,
    'translateY' => $translateY,
    );
    $return = gofast_pdf_stamper_apply_stamp($node, $stamp_text, $options, $textColor);

}

function gofast_get_user_status_from_uid($uid){
    $query = "SELECT status FROM {users} WHERE uid = '".$uid."'";
    $results = db_query($query)->fetchAll();

    return boolval ($results[0]->status);
}

/*
 * This function get all drupal messages and transform them into ajax commands
 * $status_as_success set to TRUE means status drupal message will be sent as
 * success toast commands
 */
function gofast_messages_to_commands($status_as_success = FALSE){
  $commands = array();

  //Call hook_gofast_messages_alter
  foreach(module_implements('gofast_messages_alter') as $module){
    call_user_func_array($module . '_gofast_messages_alter', array(&$_SESSION['messages']));
  }

  $messages_by_type = drupal_get_messages();
  foreach($messages_by_type as $type_name => $type){
    foreach($type as $message){
      if($type_name == "status"){
        if($status_as_success){
          $type_name = "success";
        }else{
          $type_name = "info";
        }
      }
      $commands[] = gofast_command_toast_message($message, $type_name);
    }
  }
  return $commands;
}

function gofast_get_active_user(){
    $query = "SELECT * FROM {users} WHERE status = 1 ORDER BY name";
    $results = db_query($query)->fetchAll();

    return $results;
}

function gofast_generate_uuid() {
    return sprintf( '%04x%04x-%04x-%04x-%04x-%04x%04x%04x',
        // 32 bits for "time_low"
        mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ),

        // 16 bits for "time_mid"
        mt_rand( 0, 0xffff ),

        // 16 bits for "time_hi_and_version",
        // four most significant bits holds version number 4
        mt_rand( 0, 0x0fff ) | 0x4000,

        // 16 bits, 8 bits for "clk_seq_hi_res",
        // 8 bits for "clk_seq_low",
        // two most significant bits holds zero and one for variant DCE1.1
        mt_rand( 0, 0x3fff ) | 0x8000,

        // 48 bits for "node"
        mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff ), mt_rand( 0, 0xffff )
    );
}

/**
 *  Function create multidimensional array unique for any single key index.
 * @param type $array
 * @param type $key
 * @return array
 */
function gofast_unique_multidim_array($array,$key){
    $temp_array = array();
    $i = 0;
    $key_array = array();

    foreach($array as $val) {
        if (!in_array($val[$key], $key_array)) {
            $key_array[$i] = $val[$key];
            $temp_array[$i] = $val;
        }
        $i++;
    }
    return $temp_array;
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource drupal
 * @action variable
 * @methods GET, POST
 */
function gofast_api_drupal_variable($params){
    switch($params['method']){
        case 'GET':
            gofast_api_get_drupal_variable($params);
            break;
        case 'POST':
            gofast_api_post_drupal_variable($params);
            break;
        default:
            gofast_api_not_implemented("This method");
            break;
    }
}

function gofast_api_get_drupal_variable($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a name param
    if(isset($params['name'])){
        $name = $params['name'];
    }else{
        gofast_api_mandatory_parameter("name");
    }

    //Restrict access to protected variables
    if(strpos($name, "api_") !== 0){
        gofast_api_forbidden("This variable is not accessible from the GoFAST API");
    }

    $output = variable_get($name, "empty");

    gofast_api_success($output);
}

function gofast_api_post_drupal_variable($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a name param
    if(isset($params['name'])){
        $name = $params['name'];
    }else{
        gofast_api_mandatory_parameter("name");
    }

    //Check if we have a value param
    if(isset($params['value'])){
        $value = $params['value'];
    }else{
        gofast_api_mandatory_parameter("value");
    }

    //Restrict access to protected variables
    if(strpos($name, "api_") !== 0){
        gofast_api_forbidden("This variable is not accessible from the GoFAST API");
    }

    variable_set($name, $value);

    $output = $value;

    gofast_api_success($output);
}

/**
 * Get type of a node (usually called by *_get_item_type   below)
 *
 * @param $nid
 *  Node's ID
 *
 * @return
 *  A string that contains the referenced type
 */
function gofast_get_node_type($nid){
  $query = db_select('node', 'n')
          ->fields('n', array('type'))
          ->condition('nid', $nid)
          ->execute();
  $result = $query->fetch();
  switch($result->type){
    case 'alfresco_item':
      $return_type = "Document";
      break;
    case 'article':
      $return_type = "Article";
      break;
    case 'group':
      $return_type = "Group";
      break;
    case 'forum':
      $return_type = "Forum";
      break;
    case 'webform':
      $return_type = "Web Form";
      break;
    case 'organisation':
      $return_type = "Organisation";
      break;
    case 'extranet':
      $return_type = "Extranet";
      break;
    case 'public':
      $return_type = "Public";
      break;
    case 'private_space':
      $return_type = "Private Space";
      break;
    default:
      $return_type = $result->type;
      break;
  }

  return $return_type;
}

/*
 * Helper function to get space defaults
 */
function gofast_admin_get_space_defaults(){
  //Retrieve saved spaces configuration
  $default_spaces_configuration = array(
      'public_contrib' => variable_get('public_contributions', '0'),
      'create_sub_space' => FALSE,
  );
  return variable_get("spaces_defaults", $default_spaces_configuration);
}

/**
 * Returns the caller of this function caller.
 */
function gofast_get_caller($full = FALSE) {
  list(,, $caller) = debug_backtrace(DEBUG_BACKTRACE_IGNORE_ARGS, 3);
  return $full ? $caller : $caller['function'];
}


// ----------------- BEGIN Codeigniter XSS_CLEAR -----------------
// codeigniter cleanup from cross-site XSS xss_clean
// Security Class adapted to function
function remove_invisible_characters($str, $url_encoded = TRUE)
{
  $non_displayables = array();
  if ($url_encoded) {
    $non_displayables[] = '/%0[0-8bcef]/';
    $non_displayables[] = '/%1[0-9a-f]/';
  }
  $non_displayables[] = '/[\\x00-\\x08\\x0B\\x0C\\x0E-\\x1F\\x7F]+/S';
  do {
    $str = preg_replace($non_displayables, '', $str, -1, $count);
  } while ($count);
  return $str;
}

function _convert_attribute($match)
{
  return str_replace(array('>', '<', '\\'), array('>', '<', '\\\\'), $match[0]);
}

function _decode_entity($match)
{
  $str = $match[0];

  if (stristr($str, '&') === FALSE) {
    return $str;
  }
  $str = html_entity_decode($str, ENT_COMPAT, 'UTF-8');
  $str = preg_replace('~&#x(0*[0-9a-f]{2,5})~ei', 'chr(hexdec("\\1"))', $str);
  return preg_replace('~&#([0-9]{2,4})~e', 'chr(\\1)', $str);
}

function _compact_exploded_words($matches)
{
  return preg_replace('/\s+/s', '', $matches[1]) . $matches[2];
}

function _filter_attributes($str)
{
  $out = '';

  if (preg_match_all('#\s*[a-z\-]+\s*=\s*(\042|\047)([^\\1]*?)\\1#is', $str, $matches)) {
    foreach ($matches[0] as $match) {
      $out .= preg_replace("#/\*.*?\*/#s", '', $match);
    }
  }

  return $out;
}

function _js_link_removal($match)
{
  return str_replace(
    $match[1],
    preg_replace(
      '#href=.*?(alert\(|alert&\#40;|javascript\:|livescript\:|mocha\:|charset\=|window\.|document\.|\.cookie|<script|<xss|data\s*:)#si',
      '',
      _filter_attributes(str_replace(array('<', '>'), '', $match[1]))
    ),
    $match[0]
  );
}

function _js_img_removal($match)
{
  return str_replace(
    $match[1],
    preg_replace(
      '#src=.*?(alert\(|alert&\#40;|javascript\:|livescript\:|mocha\:|charset\=|window\.|document\.|\.cookie|<script|<xss|base64\s*,)#si',
      '',
      _filter_attributes(str_replace(array('<', '>'), '', $match[1]))
    ),
    $match[0]
  );
}

function _sanitize_naughty_html($matches)
{
  // encode opening brace
  $str = '<' . $matches[1] . $matches[2] . $matches[3];

  // encode captured opening or closing brace to prevent recursive vectors
  $str .= str_replace(
    array('>', '<'),
    array('>', '<'),
    $matches[4]
  );

  return $str;
}

// call the function
//from http://www.cnblogs.com/osfipin/
function gofast_xss_clean($str, $is_image = FALSE)
{
  /*
	 * Is the string an array?
	 *
	 */
  if (is_array($str)) {
    while (list($key) = each($str)) {
      $str[$key] = gofast_xss_clean($str[$key]);
    }

    return $str;
  }

  $str = remove_invisible_characters($str);

  // Validate Entities in URLs
  $hash = md5(time() + mt_rand(0, 1999999999));

  $str = preg_replace('|\&([a-z\_0-9\-]+)\=([a-z\_0-9\-]+)|i', $hash . "\\1=\\2", $str);
  $str = preg_replace('#(&\#?[0-9a-z]{2,})([\x00-\x20])*;?#i', "\\1;\\2", $str);
  $str = preg_replace('#(&\#x?)([0-9A-F]+);?#i', "\\1\\2;", $str);
  $str = str_replace($hash, '&', $str);

  $str = rawurldecode($str);

  /*
	 * Convert character entities to ASCII
	 *
	 * This permits our tests below to work reliably.
	 * We only convert entities that are within tags since
	 * these are the ones that will pose security problems.
	 *
	 */

  $str = preg_replace_callback("/[a-z]+=([\'\"]).*?\\1/si",  '_convert_attribute', $str);

  $str = preg_replace_callback("/<\w+.*?(?=>|<|$)/si",  '_decode_entity', $str);

  /*
	 * Remove Invisible Characters Again!
	 */
  $str = remove_invisible_characters($str);

  /*
	 * Convert all tabs to spaces
	 *
	 * This prevents strings like this: ja	vascript
	 * NOTE: we deal with spaces between characters later.
	 * NOTE: preg_replace was found to be amazingly slow here on
	 * large blocks of data, so we use str_replace.
	 */

  if (strpos($str, "\t") !== FALSE) {
    $str = str_replace("\t", ' ', $str);
  }

  /*
	 * Capture converted string for later comparison
	 */
  $converted_string = $str;

  // Remove Strings that are never allowed
  $_never_allowed_str = array(
    'document.cookie'  => '[removed]',
    'document.write'  => '[removed]',
    '.parentNode'    => '[removed]',
    '.innerHTML'    => '[removed]',
    'window.location'  => '[removed]',
    '-moz-binding'    => '[removed]',
    '<!--'        => '<!--',
    '-->'        => '-->',
    '<![CDATA['      => '<![CDATA[',
    '<comment>'      => '<comment>'
  );
  $str = str_replace(array_keys($_never_allowed_str), $_never_allowed_str, $str);


  $_never_allowed_regex = array(
    'javascript\s*:',
    'expression\s*(\(|&\#40;)', // CSS and IE
    'vbscript\s*:', // IE, surprise!
    'Redirect\s+302',
    "([\"'])?data\s*:[^\\1]*?base64[^\\1]*?,[^\\1]*?\\1?"
  );
  foreach ($_never_allowed_regex as $regex) {
    $str = preg_replace('#' . $regex . '#is', '[removed]', $str);
  }

  /*
	 * Makes PHP tags safe
	 *
	 * Note: XML tags are inadvertently replaced too:
	 *
	 * <?xml
	 *
	 * But it doesn't seem to pose a problem.
	 */
  if ($is_image === TRUE) {
    // Images have a tendency to have the PHP short opening and
    // closing tags every so often so we skip those and only
    // do the long opening tags.
    $str = preg_replace('/<\?(php)/i', "<?\\1", $str);
  } else {
    $str = str_replace(array('<?', '?' . '>'),  array('<?', '?>'), $str);
  }

  /*
	 * Compact any exploded words
	 *
	 * This corrects words like:  j a v a s c r i p t
	 * These words are compacted back to their correct state.
	 */
  $words = array(
    'javascript', 'expression', 'vbscript', 'script', 'base64',
    'applet', 'alert', 'document', 'write', 'cookie', 'window'
  );

  foreach ($words as $word) {
    $temp = '';

    for ($i = 0, $wordlen = strlen($word); $i < $wordlen; $i++) {
      $temp .= substr($word, $i, 1) . "\s*";
    }

    // We only want to do this when it is followed by a non-word character
    // That way valid stuff like "dealer to" does not become "dealerto"
    $str = preg_replace_callback('#(' . substr($temp, 0, -3) . ')(\W)#is', '_compact_exploded_words', $str);
  }

  /*
	 * Remove disallowed Javascript in links or img tags
	 * We used to do some version comparisons and use of stripos for PHP5,
	 * but it is dog slow compared to these simplified non-capturing
	 * preg_match(), especially if the pattern exists in the string
	 */
  do {
    $original = $str;

    if (preg_match("/<a/i", $str)) {
      $str = preg_replace_callback("#<a\s+([^>]*?)(>|$)#si", '_js_link_removal', $str);
    }

    if (preg_match("/<img/i", $str)) {
      $str = preg_replace_callback("#<img\s+([^>]*?)(\s?/?>|$)#si", '_js_img_removal', $str);
    }

    if (preg_match("/script/i", $str) or preg_match("/xss/i", $str)) {
      $str = preg_replace("#<(/*)(script|xss)(.*?)\>#si", '[removed]', $str);
    }
  } while ($original != $str);

  unset($original);

  // Remove evil attributes such as style, onclick and xmlns

  // All javascript event handlers (e.g. onload, onclick, onmouseover), style, and xmlns
  $evil_attributes = array('on\w*', 'style', 'xmlns', 'formaction');

  if ($is_image === TRUE) {
    /*
		 * Adobe Photoshop puts XML metadata into JFIF images,
		 * including namespacing, so we have to allow this for images.
		 */
    unset($evil_attributes[array_search('xmlns', $evil_attributes)]);
  }

  do {
    $count = 0;
    $attribs = array();

    // find occurrences of illegal attribute strings with quotes (042 and 047 are octal quotes)
    preg_match_all('/(' . implode('|', $evil_attributes) . ')\s*=\s*(\042|\047)([^\\2]*?)(\\2)/is', $str, $matches, PREG_SET_ORDER);

    foreach ($matches as $attr) {
      $attribs[] = preg_quote($attr[0], '/');
    }

    // find occurrences of illegal attribute strings without quotes
    preg_match_all('/(' . implode('|', $evil_attributes) . ')\s*=\s*([^\s>]*)/is', $str, $matches, PREG_SET_ORDER);

    foreach ($matches as $attr) {
      $attribs[] = preg_quote($attr[0], '/');
    }

    // replace illegal attribute strings that are inside an html tag
    if (count($attribs) > 0) {
      $str = preg_replace('/(<?)(\/?[^><]+?)([^A-Za-z<>\-])(.*?)(' . implode('|', $attribs) . ')(.*?)([\s><]?)([><]*)/i', '$1$2 $4$6$7$8', $str, -1, $count);
    }
  } while ($count);



  /*
	 * Sanitize naughty HTML elements
	 *
	 * If a tag containing any of the words in the list
	 * below is found, the tag gets converted to entities.
	 *
	 * So this: <blink>
	 * Becomes: <blink>
	 */
  $naughty = 'alert|applet|audio|basefont|base|behavior|bgsound|blink|body|embed|expression|form|frameset|frame|head|html|ilayer|iframe|input|isindex|layer|link|meta|object|plaintext|style|script|textarea|title|video|xml|xss';
  $str = preg_replace_callback('#<(/*\s*)(' . $naughty . ')([^><]*)([><]*)#is', '_sanitize_naughty_html', $str);

  /*
	 * Sanitize naughty scripting elements
	 *
	 * Similar to above, only instead of looking for
	 * tags it looks for PHP and JavaScript commands
	 * that are disallowed.  Rather than removing the
	 * code, it simply converts the parenthesis to entities
	 * rendering the code un-executable.
	 *
	 * For example:	eval('some code')
	 * Becomes:		eval('some code')
	 */
  $str = preg_replace('#(alert|cmd|passthru|eval|exec|expression|system|fopen|fsockopen|file|file_get_contents|readfile|unlink)(\s*)\((.*?)\)#si', "\\1\\2(\\3)", $str);


  // Final clean up
  // This adds a bit of extra precaution in case
  // something got through the above filters
  $str = str_replace(array_keys($_never_allowed_str), $_never_allowed_str, $str);

  foreach ($_never_allowed_regex as $regex) {
    $str = preg_replace('#' . $regex . '#is', '[removed]', $str);
  }

  /*
	 * Images are Handled in a Special Way
	 * - Essentially, we want to know that after all of the character
	 * conversion is done whether any unwanted, likely XSS, code was found.
	 * If not, we return TRUE, as the image is clean.
	 * However, if the string post-conversion does not matched the
	 * string post-removal of XSS, then it fails, as there was unwanted XSS
	 * code found and removed/changed during processing.
	 */

  if ($is_image === TRUE) {
    return ($str == $converted_string) ? TRUE : FALSE;
  }

  return $str;
}

// ----------------- END Codeigniter XSS_CLEAR -----------------



