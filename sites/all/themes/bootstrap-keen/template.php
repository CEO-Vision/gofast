<?php
/**
 * @file
 * template.php
 *
 * This file should only contain light helper functions and stubs pointing to
 * other files containing more complex functions.
 *
 * The stubs should point to files within the `theme` folder named after the
 * function itself minus the theme prefix. If the stub contains a group of
 * functions, then please organize them so they are related in some way and name
 * the file appropriately to at least hint at what it contains.
 *
 * All [pre]process functions, theme functions and template implementations also
 * live in the 'theme' folder. This is a highly automated and complex system
 * designed to only load the necessary files when a given theme hook is invoked.
 * @see _bootstrap_theme()
 * @see theme/registry.inc
 *
 * Due to a bug in Drush, these includes must live inside the 'theme' folder
 * instead of something like 'includes'. If a module or theme has an 'includes'
 * folder, Drush will think it is trying to bootstrap core when it is invoked
 * from inside the particular extension's directory.
 * @see https://drupal.org/node/2102287
 */



/**
 * CEO-Vision
 * @see https://api.drupal.org/api/drupal/includes%21theme.inc/function/theme/7
 */


/**
 * This method allow adding extra attributes to options.
 * @param type $variables
 * @return type
 */
function bootstrap_keen_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  if(!in_array('simple-select',$element['#attributes']['class']) && !in_array('gofast_display_none',$element['#attributes']['class'])){
    _form_set_class($element, array('select2 gofastSelect2'));
  }
  return '<select' . drupal_attributes($element['#attributes']) . '>' . bootstrap_keen_form_select_options($element) . '</select>';
}

function bootstrap_keen_form_select_options($element, $choices = NULL) {
  if (!isset($choices)) {
    $choices = $element ['#options'];
  }

  $value_valid = isset($element ['#value']) || array_key_exists('#value', $element);
  $value_is_array = $value_valid && is_array($element ['#value']);
  $options = '';
  $dataAttr = isset($element['#extra_option_attributes']) ? $element['#extra_option_attributes'] : null;

  foreach ($choices as $key => $choice) {
    if (is_array($choice)) {
      $options .= '<optgroup label="' . check_plain($key) . '">';
      $options .= form_select_options($element, $choice);
      $options .= '</optgroup>';
    }
    elseif (is_object($choice)) {
      $options .= form_select_options($element, $choice->option);
    }
    else {
      $key = (string) $key;
      if ($value_valid && (!$value_is_array && (string) $element ['#value'] === $key || ($value_is_array && in_array($key, $element ['#value'])))) {
        $selected = ' selected="selected"';
      }
      else {
        $selected = '';
      }
      $groupid = $dataAttr !== null ? ' data-groupid="'. $dataAttr[$key] .'"' : '';
      $options .= '<option value="' . check_plain($key) . '"' . $selected . '' . $groupid . '>' . check_plain($choice) . '</option>';
    }
  }
  return $options;
}

/**
 * Hook menu_link for main_menu.
 * This method allow multiple depth item navigation through main menu.
 * @param type $variables
 * @return type
 */
function bootstrap_keen_menu_link__main_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';
  global $user;
  if ($element['#original_link']['link_path'] === 'user') {
    // Merge in the user-menu links.
    $user_menu = menu_tree('user-menu');
    $output = drupal_render($user_menu);
    if (preg_match('/^<ul[^<>]*>(.*)<\/ul>$/s', $output, $matches)) {
      return $matches[1];
    }
  }

  if ($element['#below'] || $element["#original_link"]["router_path"] == "node/%") {

    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] == 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    } elseif ((!empty($element['#original_link']['depth'])) && $element['#original_link']['depth'] > 1) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      //$element['#attributes']['class'][] = 'dropdown-submenu';
      $element['#localized_options']['html'] = TRUE;
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    } else {
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      //Add caret when needed
      if($element["#original_link"]["router_path"] == "node/add/alfresco-item"){
        $sub_menu = str_replace('>' . t('Content') . '</a>', '>' . t('Content') . "<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
        $sub_menu = str_replace('>' . t('Space') . '</a>', '>' . t('Space') . "<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
      }
      if($element["#original_link"]["router_path"] == "gofast/browser"){
        $sub_menu = str_replace('>' . t('Groups') . '</a>', ">" . t('Groups') . "<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
        $sub_menu = str_replace('>Organisations</a>', ">Organisations<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
        $sub_menu = str_replace('>' . t('Extranet') . '</a>', ">" . t('Extranet') . "<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
        $sub_menu = str_replace('>' . t('Public') . '</a>', ">" . t('Public') . "<span class='fa fa-caret-right' aria-hidden='true' style='position:absolute; right:5px; margin-top:2px;'></span></a>", $sub_menu);
      }
      $element['#title'] .= ' <span class="caret"></span>';
      //$element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    }

    if($element["#original_link"]["router_path"] == "node/%"){
        if($element["#original_link"]["link_title"] == "My Private Space"){
            $private_gid = gofast_og_get_user_private_space($user, FALSE);
            $element["#original_link"]["link_path"] = "node/".$private_gid;
            $element["#original_link"]["#href"] = "node/".$private_gid;
            $element["#href"] = "node/".$private_gid;
        }
        $element['#below'] = array();
        //$element['#attributes']['class'][] = 'dropdown-submenu';
        $element['#localized_options']['html'] = TRUE;
        $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
        $gid = str_replace("node/", "", $element["#original_link"]["link_path"]);
        $sub_menu = '<ul class="dropdown-menu gofast_menu_async" id="main_menu_'.$gid.'" gid="'.$gid.'"></ul>';

    }
  }
  if ($element['#href'] == $_GET['q'] && !($element['#href'] == '<front>' || drupal_is_front_page()) && empty($element['#localized_options']['language'])) {
    $element['#attributes']['class'][] = 'active';
  }

  //in some case we put the title into t() function
  if(isset($element['#localized_options']["identifier"])){
      $title = $element['#title'];
  }else{
      if($element["#original_link"]["depth"] <= 2){
        $title = t($element["#original_link"]['link_title'],array(), array('context' => 'gofast'));
      }else{
         $title = $element["#original_link"]['link_title'];
      }
  }

  $output = l($title, $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}


/**
 * Overrides theme_textfield().
 */
function bootstrap_keen_textfield($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'text';
  element_set_attributes($element, array(
    'id',
    'name',
    'value',
    'size',
    'maxlength',
  ));
  _form_set_class($element, array('form-text'));

  //Remove form-text class as it set an unwanted margin
  unset($element['#attributes']['class'][array_search('form-text', $element['#attributes']['class'])]);

  // if(in_array('gofastDatetimepicker',$element['#attributes']['class'])){
  //      $element['#attributes']['data-toggle'] = 'datetimepicker';
  // }
  $output = '<input' . drupal_attributes($element['#attributes']) . ' />';

  $extra = '';
  if ($element['#autocomplete_path']) {
    drupal_add_library('system', 'drupal.autocomplete');
    $element['#attributes']['class'][] = 'form-autocomplete';

    $attributes = array();
    $attributes['type'] = 'hidden';
    $attributes['id'] = $element['#attributes']['id'] . '-autocomplete';
    $attributes['value'] = url($element['#autocomplete_path'], array('absolute' => TRUE));
    $attributes['disabled'] = 'disabled';
    $attributes['class'][] = 'autocomplete';

    //$ac_icon = empty($element['#no_icon']) ? '<span class="input-group-addon">' . _bootstrap_icon('refresh') : '';
    //$style = $ac_icon ? '' : 'style="width:100%;"';
    //$output = '<div class="textfield-wrapper" >' . $output . $ac_icon . '</span></div>';

    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  return $output . $extra;
}

/**
 * Theme override for bootstrap_search_form_wrapper.
 */
function bootstrap_keen_bootstrap_search_form_wrapper($variables) {

  $output .= $variables['element']['#children'];

  return $output;
}

/**
 * Returns HTML for the facet title, usually the title of the block.
 *
 * @param $variables
 *   An associative array containing:
 *   - title: The title of the facet.
 *   - facet: The facet definition as returned by facetapi_facet_load().
 *
 * @ingroup themeable
 */
function bootstrap_keen_facetapi_title($variables) {
   // return t(ucwords(drupal_strtolower($variables['title'])));
//  $variables['title'] = t( $variables['title'], array(), array('context' => 'gofast:gofast-search'));
  return t('@title', array('@title' => $variables['title']));
}

/**
 * @override the sort list in apachesolr sort block.
 * @see theme_apachesolr_sort_link()
 */
function bootstrap_keen_apachesolr_sort_list($variables) {
  foreach ($variables['items'] as $key => &$item) {
    if(gofast_essential_is_essential()){
      $item = str_replace('search/solr', 'essential/get_node_content_part/search/all',$item);
    }
    $item = array(
      'data' => $item,
      'class' => array('gofast-inline-list')
    );
  }
  return theme('item_list', array('items' => $variables['items']));
}

/**
 * @override links theme in the locale block (lang switch).
 */
function bootstrap_keen_links__locale_block(&$variables) {
  foreach($variables['links'] as $langcode => $link) {
    $link['attributes']['title'] = $link['title'];
    $link['attributes']['class'][] = 'gofast-link';
    $link['title'] = $langcode;

    // Alter the key here so we can use our class.
    $variables['links'][$langcode . ' gofast-inline-list'] = $link;
    unset ($variables['links'][$langcode]);
  }
  $content = theme_links($variables);
  return $content;
}

function bootstrap_keen_preprocess_node(&$variables) {
  $variables['author_pane'] = theme('gofast_forum_simple_author_pane', array('context' => $variables['node']));
}

function bootstrap_keen_preprocess_comment(&$variables) {
  // Forum permalink.

  static $post_number;
  if (!isset($post_number)) {
    $post_number = 1;
  }

  $node = $variables['node'];
  $comment = $variables['comment'];

  $posts_per_page = variable_get('comment_default_per_page_' . $node->type, 50);
  $page_number = !empty($_GET['page']) && is_numeric($_GET['page']) ? $_GET['page'] : 0;

  // Page_number sanity check.
  if ($page_number > floor($node->comment_count / $posts_per_page)) {
    $page_number = floor($node->comment_count / $posts_per_page);
  }

  $topic_id = advanced_forum_node_is_styled($node);
  $post_number_delta = ($topic_id) ? 1 : 0;
  $post_position = ($page_number * $posts_per_page) + $post_number + $post_number_delta;

  $linktext = t('Permalink') . ' #' . $post_position;
//  $reply_text = t("(Reply to #!post_position)", array('!post_position' => advanced_forum_post_position($node, $comment)));
//  $linkpath = "node/$node->nid";
//  if ($page_number) {
//    $query = array('page' => $page_number);
//  }
//  // Assemble the link.
//  $fragment = 'comment-' . $comment->pid;
//  $variables['in_reply_to'] = l($reply_text, $linkpath, array('query' => empty($query) ? array() : $query, 'fragment' => $fragment));

  $uri = entity_uri('comment', $variables['comment']);

  $uri['options'] += array(
    'absolute' => TRUE,
    'alias' => TRUE, // prevent alias lookup
    'fragment' => 'comment-' . $variables['comment']->cid,
    'attributes' => array(
      'class' => array('permalink'),
      'rel' => 'bookmark'
    )
  );
  // Adjust comment timestamp to match node template.
  $variables['date'] = $variables['created'];

  $variables['author_pane'] = theme('gofast_forum_simple_author_pane', array('context' => $comment));
  $variables['permalink'] = l($linktext, "/node/".$node->nid, $uri['options']);
  $post_number++;
}

/**
 * Returns HTML for a username, potentially linked to the user's page.
 *
 * @param $variables
 *   An associative array containing:
 *   - account: The user object to format.
 *   - name: The user's name, sanitized.
 *   - extra: Additional text to append to the user's name, sanitized.
 *   - link_path: The path or URL of the user's profile page, home page, or
 *     other desired page to link to for more information about the user.
 *   - link_options: An array of options to pass to the l() function's $options
 *     parameter if linking the user's name to the user's page.
 *   - attributes_array: An array of attributes to pass to the
 *     drupal_attributes() function if not linking to the user's page.
 *   - picture: if set, display HTML returned by 'user_picture' theme.
 *
 * @see template_preprocess_username()
 * @see template_process_username()
 * @see gofast_user_preprocess_username()
 * @see gofast_user_preprocess_picture()
 */
function bootstrap_keen_username($variables) {
  $spacer = empty($variables['picture']) ? '' : '<span style="padding-left:5px;"></span>';
  unset($variables['link_options']['attributes']['title']);

  if (isset($variables['link_path'])) {
    // We have a link path, so we should generate a link using l().
    // Additional classes may be added as array elements like
    // $variables['link_options']['attributes']['class'][] = 'myclass';
    $output = l($variables['picture'] . $spacer . $variables['name'] . $variables['extra'], $variables['link_path'], $variables['link_options']);
  }
  else {
    // Modules may have added important attributes so they must be included
    // in the output. Additional classes may be added as array elements like
    // $variables['attributes_array']['class'][] = 'myclass';
    $output = '<span' . drupal_attributes($variables['attributes_array']) . '>' . $variables['picture'] . $spacer . $variables['name'] . $variables['extra'] . '</span>';
  }
  return $output;
}

/**
 * Implements of hook_menu_local_tasks_alter().
 */
function bootstrap_keen_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  // Prevent local tasks rendering (tabs) while preserving menu router items.
  $data = array();
}

/**
 * Returns HTML for an image using a specific image style.
 *
 * @param $variables
 *   An associative array containing:
 *   - style_name: The name of the style to be used to alter the original image.
 *   - path: The path of the image file relative to the Drupal files directory.
 *     This function does not work with images outside the files directory nor
 *     with remotely hosted images. This should be in a format such as
 *     'images/image.jpg', or using a stream wrapper such as
 *     'public://images/image.jpg'.
 *   - width: The width of the source image (if known).
 *   - height: The height of the source image (if known).
 *   - override_base_dim: Boolean to override base width/height.
 *   - alt: The alternative text for text-based browsers.
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 *
 * @ingroup themeable
 */
function bootstrap_keen_image_style($variables) {
  // Determine the dimensions of the styled image.
  $dimensions = array(
    'width' => $variables['width'],
    'height' => $variables['height'],
  );

  if (!$variables['override_base_dim']) {
    image_style_transform_dimensions($variables['style_name'], $dimensions);
  }

  $variables['width'] = $dimensions['width'];
  $variables['height'] = $dimensions['height'];

  // Determine the URL for the styled image.
  $variables['path'] = gofast_image_style_url($variables['style_name'], $variables['path']);
  return theme('image', $variables);
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_menu_link()
 *
 * @ingroup theme_functions
 */
function bootstrap_keen_menu_link__user_menu(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $profile = NULL;

  if ($element['#below'] && (!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
    // Add our own wrapper.
    unset($element['#below']['#theme_wrappers']);
    $sub_menu = '<ul class="dropdown-menu user-menu">' . drupal_render($element['#below']) . '</ul>';
    // Generate as standard dropdown.
    $element['#title'] .= ' <span class="caret"></span>';
    $element['#attributes']['class'][] = 'dropdown';
    $element['#localized_options']['html'] = TRUE;

    // Set dropdown trigger element to # to prevent inadvertant page loading
    // when a submenu link is clicked.
    $element['#localized_options']['attributes']['data-target'] = '#';
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';

    global $user;
    $account = user_load($user->uid);
    $profile = theme('username', array('account' => $account, 'popup' => FALSE, 'menu' => TRUE));
    // Fix active path match.
    $element['#href'] .= '/' . $user->uid;
  }
  if ($element['#href'] == $_GET['q'] && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $output = $profile ? $profile : l($element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Returns HTML for a password form element.
 *
 * @override
 *  Let us choose whether or not to populate password field (#default_value).
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #title, #value, #description, #size, #maxlength,
 *     #required, #attributes.
 *
 * @ingroup themeable
 */
function bootstrap_keen_password($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'password';
  $map = array('id', 'name', 'size', 'maxlength');

  if (isset($element['#default_value'])) {
    $map[] = 'value';
    _form_set_class($element, array('protected'));
  }

  element_set_attributes($element, $map);
  _form_set_class($element, array('form-text'));

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

function bootstrap_keen_preprocess_html(&$variables) {
  $variables['classes_array'][] = 'body_display_none';
  //add new font
  drupal_add_css('sites/all/themes/bootstrap-gofast/fonts/Roboto.css', array('group' => CSS_THEME ));
}

function bootstrap_keen_preprocess_views_view_table(&$variables) {
  if ($variables['view']->name === 'gofast_private_msg') {
    global $user;
    foreach ($variables['result'] as $key => $result) {
      $thread_id = $result->thread_id;
      $is_new = gofast_privatemsg_does_thread_have_new_message($thread_id, $user);
      if ($is_new == 1) {
        $unread_count_for_thread = gofast_privatemsg_count_unread_message_for_thread($thread_id, $user);
        $variables['rows'][$key]['is_new'] = '<span class="badge badge-notify" id="badge-message-'.$thread_id.'" style="visibility: visible;">'.$unread_count_for_thread.'</span>';
      } else {
        $variables['rows'][$key]['is_new'] = '<span id="is_new_'.$thread_id.'"></span>';
      }
    }
  }
}

/**
 * Implements hook_theme_registry_alter().
 */
function bootstrap_keen_theme_registry_alter(&$theme_registry) {

  if(module_exists('entity_menu_links')){
    // Make sure that menu links don't get themed like regular entities.
    $hooks = preg_grep('/^menu_link(\.|__).+$/', array_keys($theme_registry));
    foreach ($hooks as $hook) {
      $theme_registry[$hook]['render element'] = 'element';
      $theme_registry[$hook]['base hook'] = 'menu_link';
    }
  }
}

/**
 *  Implement hook_js_alter()
 */

 /**
  * Implements hook_js_alter().
  */
 function bootstrap_keen_js_alter(&$js) {
 // Add Bootstrap settings.
  $js['settings']['data'][]['bootstrap'] = array(
    'anchorsFix' => bootstrap_setting('anchors_fix'),
    'anchorsSmoothScrolling' => bootstrap_setting('anchors_smooth_scrolling'),
    'formHasError' => (int) bootstrap_setting('forms_has_error_value_toggle'),
    'popoverEnabled' => bootstrap_setting('popover_enabled'),
    'popoverOptions' => array(
      'animation' => (bool) bootstrap_setting('popover_animation'),
      'html' => (int) bootstrap_setting('popover_html'),
      'placement' => bootstrap_setting('popover_placement'),
      'selector' => bootstrap_setting('popover_selector'),
      'trigger' => implode(' ', array_filter(array_values((array) bootstrap_setting('popover_trigger')))),
      'triggerAutoclose' => (int) bootstrap_setting('popover_trigger_autoclose'),
      'title' => bootstrap_setting('popover_title'),
      'content' => bootstrap_setting('popover_content'),
      'delay' => (int) bootstrap_setting('popover_delay'),
      'container' => bootstrap_setting('popover_container'),
    ),
    'tooltipEnabled' => bootstrap_setting('tooltip_enabled'),
    'tooltipOptions' => array(
      'animation' => (bool) bootstrap_setting('tooltip_animation'),
      'html' => (bool) bootstrap_setting('tooltip_html'),
      'placement' => bootstrap_setting('tooltip_placement'),
      'selector' => bootstrap_setting('tooltip_selector'),
      'trigger' => implode(' ', array_filter(array_values((array) bootstrap_setting('tooltip_trigger')))),
      'delay' => (int) bootstrap_setting('tooltip_delay'),
      'container' => bootstrap_setting('tooltip_container'),
    ),
  );
 }

function bootstrap_keen_facetapi_deactivate_widget($variables) {
  $button_delete_search = '<span><i class="fa fa-times facetapi-icon" aria-hidden="true"'.t("Remove this search filter",  array(), array('context' => 'gofast:search')) . '"></i></span>'; 

  return $button_delete_search;
}

function bootstrap_keen_preprocess_block(&$variables) {
  $variables['theme_hook_suggestions'][] = 'block__' . $variables['block']->region;
  $variables['theme_hook_suggestions'][] = 'block__' . $variables['block']->module;
  $variables['theme_hook_suggestions'][] = 'block__' . $variables['block']->delta;

  // Add block description as template suggestion
  $block = block_custom_block_get($variables['block']->delta);

  // Transform block description to a valid machine name
  if (!empty($block['info'])) {
    setlocale(LC_ALL, 'en_US');

    // required for iconv()
    $variables['theme_hook_suggestions'][] = 'block__' . str_replace(' ', '_', strtolower(iconv('UTF-8', 'ASCII//TRANSLIT', $block['info'])));
  }
}

function bootstrap_keen_form_element(&$variables){
  $element = &$variables['element'];
  $name = !empty($element['#name']) ? $element['#name'] : FALSE;
  $type = !empty($element['#type']) ? $element['#type'] : FALSE;
  $wrapper = isset($element['#form_element_wrapper']) ? !!$element['#form_element_wrapper'] : TRUE;
  $form_group = isset($element['#form_group']) ? !!$element['#form_group'] : $wrapper && $type && $type !== 'hidden';
  $checkbox = $type && $type === 'checkbox';
  $radio = $type && $type === 'radio';
  $file = $type && $type === 'file';

  // Create an attributes array for the wrapping container.
  if (empty($element['#wrapper_attributes'])) {
    $element['#wrapper_attributes'] = array();
  }
  $wrapper_attributes = &$element['#wrapper_attributes'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add wrapper ID for 'item' type.
  if ($type && $type === 'item' && isset($element['#markup']) && !empty($element['#id'])) {
    $wrapper_attributes['id'] = $element['#id'];
  }

  // Check for errors and set correct error class.
  if ((isset($element['#parents']) && form_get_error($element) !== NULL) || (!empty($element['#required']) && (!isset($element['#value']) || $element['#value'] === '') && bootstrap_setting('forms_required_has_error'))) {
    $wrapper_attributes['class'][] = 'has-error';
  }

  // Add necessary classes to wrapper container.
  $wrapper_attributes['class'][] = 'form-item';
  if ($name) {
    $wrapper_attributes['class'][] = 'form-item-' . drupal_html_class($name);
  }
  if ($type) {
    $wrapper_attributes['class'][] = 'form-type-' . drupal_html_class($type);
  }
  if (!empty($element['#attributes']['disabled'])) {
    $wrapper_attributes['class'][] = 'form-disabled';
  }
  if (!empty($element['#autocomplete_path']) && drupal_valid_path($element['#autocomplete_path'])) {
    $wrapper_attributes['class'][] = 'form-autocomplete';
  }

  // Checkboxes and radios do no receive the 'form-group' class, instead they
  // simply have their own classes.
  if ($checkbox || $radio) {
    $wrapper_attributes['class'][] = drupal_html_class($type);
    $wrapper_attributes['class'][] = 'align-items-start d-flex flex-column';
    if($checkbox) $wrapper_attributes['class'][] = 'mb-5';
    if(!in_array('gofast_display_none', (array) $element['#attributes']['class'])){
        $element['#children'] = $element['#children'] . '<span class="mr-2"></span>';
    }
  } else if ($file) {
      $wrapper_attributes['class'][] = 'uppy mb-5';
  } else if ($form_group) {
      $wrapper_attributes['class'][] = 'form-group';
  }


  if ($file) {
      $element['#field_prefix'] = '<span style="display: none;">';
      $element['#field_suffix'] =
                '</div>'
          . '</div>'
          . '<div class="uppy-list"></div>'
          .     '<div class="uppy-status">'
          .     '</div>'
          .     '<div class="uppy-informer uppy-informer-min">'
          .     '</div>'
          . '</span>';
  }

  // Create a render array for the form element.
  $build = array(
    '#form_group' => $form_group,
    '#attributes' => $wrapper_attributes,
  );

  if ($wrapper) {
    $build['#theme_wrappers'] = array('container__form_element');

    // Render the label for the form element.
    /* @noinspection PhpUnhandledExceptionInspection */
    $build['label'] = array(
      '#markup' => theme('form_element_label', $variables),
      '#weight' => $element['#title_display'] === 'before' ? 0 : 2,
    );
  }

  // Checkboxes and radios render the input element inside the label. If the
  // element is neither of those, then the input element must be rendered here.
  if (!$checkbox && !$radio) {
    $prefix = isset($element['#field_prefix']) ? $element['#field_prefix'] : '';
    $suffix = isset($element['#field_suffix']) ? $element['#field_suffix'] : '';
    if ((!empty($prefix) || !empty($suffix)) && (!empty($element['#input_group']) || !empty($element['#input_group_button']))) {
      if (!empty($element['#field_prefix'])) {
        $prefix = '<span class="input-group-prepend">' . $prefix . '</span>';
      }
      if (!empty($element['#field_suffix'])) {
        $suffix = '<span class="input-group-append">' . $suffix . '</span>';
      }

      // Add a wrapping container around the elements.
      $input_group_attributes = &_bootstrap_get_attributes($element, 'input_group_attributes');
      $input_group_attributes['class'][] = 'input-group';
      $prefix = '<div' . drupal_attributes($input_group_attributes) . '>' . $prefix;
      $suffix .= '</div>';
    }

    // Build the form element.
    $build['element'] = array(
      '#markup' => $element['#children'],
      '#prefix' => !empty($prefix) ? $prefix : NULL,
      '#suffix' => !empty($suffix) ? $suffix : NULL,
      '#weight' => 1,
    );
  }

  // Construct the element's description markup.
  if (!empty($element['#description'])) {
    $build['description'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('text-muted'),
      ),
      '#weight' => isset($element['#description_display']) && $element['#description_display'] === 'before' ? 0 : 20,
      0 => array('#markup' => filter_xss_admin($element['#description'])),
    );
  }

  // Render the form element build array.
  return drupal_render($build);
}

function bootstrap_keen_form_element_label(&$variables) {
  $element = $variables['element'];
  // Extract variables.
  $output = '';

  $title = !empty($element['#title']) ? filter_xss_admin($element['#title']) : '';

  // Only show the required marker if there is an actual title to display.
  $marker = array('#theme' => 'form_required_marker', '#element' => $element);
  if ($title && $required = !empty($element['#required']) ? drupal_render($marker) : '') {
    $title .= ' ' . $required;
  }

  $display = isset($element['#title_display']) ? $element['#title_display'] : 'before';
  $type = !empty($element['#type']) ? $element['#type'] : FALSE;
  $checkbox = $type && $type === 'checkbox';
  $radio = $type && $type === 'radio';
  $file = $type && $type === 'file';

  // Immediately return if the element is not a checkbox or radio and there is
  // no label to be rendered.
  if (!$checkbox && !$radio && !$file && ($display === 'none' || !$title)) {
    return '';
  }

  // Retrieve the label attributes array.
  $attributes = &_bootstrap_get_attributes($element, 'label_attributes');

  if ($checkbox && substr($element['#name'], 0, 6) === 'shares') {
    $attributes['class'] = array("checkbox", "checkbox-outline", "checkbox-outline-2x", "checkbox-success");
  }
  if ($checkbox && strpos($element['#name'], "_bs_switch") != FALSE) {
    $attributes['class'][] = "switch";
    $attributes['class'][] = "switch-sm";
    $attributes['class'][] = "switch-icon";
    $attributes['class'][] = "gofast-switch-icon";
  }
  // Add Bootstrap label class.
  if ($checkbox) {
      $attributes['class'][] = 'checkbox';
      // GOFAST-6821 fix checkbox and radio spacing
      $attributes['class'][] = "mr-3";
  } else if ($radio) {
      $attributes['class'][] = 'radio';
      // GOFAST-6821 fix checkbox and radio spacing
      $attributes['class'][] = "mr-3";
  }  else if ($file) {
      $attributes['class'][] = 'uppy-input-label btn btn-light-primary btn-sm btn-bold no-footer';
  } else {
      $attributes['class'][] = 'control-label';
  }

  // Add the necessary 'for' attribute if the element ID exists.
  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Checkboxes and radios must construct the label differently.
  if ($checkbox || $radio) {
    if ($display === 'before') {
      $output .= $title;
    }
    elseif ($display === 'none' || $display === 'invisible') {
      $output .= '<span class="element-invisible">' . $title . '</span>';
    }
    // Inject the rendered checkbox or radio element inside the label.
    if (!empty($element['#children'])) {
      $output .= $element['#children'];
    }
    if ($display === 'after') {
      $output .= $title;
    }
  }
  // Otherwise, just render the title as the label.
  else {
    // Show label only to screen readers to avoid disruption in visual flows.
    if ($display === 'invisible') {
      $attributes['class'][] = 'element-invisible';
    }
    $output .= $title;
  }

  if ($file) {
      return '<div class="uppy-wrapper"><div class="uppy-Root uppy-FileInput-container"> <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
}


function bootstrap_keen_preprocess_user_picture(&$variables) {
  $variables['user_picture'] = '';
  if (variable_get('user_pictures', 0)) {
    $account = $variables['account'];
    if (!empty($account->picture)) {

      // @TODO: Ideally this function would only be passed file objects, but
      // since there's a lot of legacy code that JOINs the {users} table to
      // {node} or {comments} and passes the results into this function if we
      // a numeric value in the picture field we'll assume it's a file id
      // and load it for them. Once we've got user_load_multiple() and
      // comment_load_multiple() functions the user module will be able to load
      // the picture files in mass during the object's load process.
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $filepath = $account->picture->uri;
      }
    }
    elseif (variable_get('user_picture_default', '')) {
      $filepath = variable_get('user_picture_default', '');
    }
    if (isset($filepath)) {
      $alt = t("@user's picture", array(
        '@user' => format_username($account),
      ));

      // If the image does not have a valid Drupal scheme (for eg. HTTP),
      // don't load image styles.
      if (module_exists('image') && file_valid_uri($filepath)) {
        $variables['user_picture'] = theme('image_style', array(
          'style_name' => "thumbnail",
          'path' => $filepath,
          'alt' => $alt,
          'title' => $alt,
          'attributes' => $variables['attributes']
        ));
      }
      else {
        $variables['user_picture'] = theme('image', array(
          'path' => $filepath,
          'alt' => $alt,
          'title' => $alt,
          'attributes' => $variables['attributes']
        ));
      }
      if (!empty($account->uid) && user_access('access user profiles')) {
        $attributes = array(
          'attributes' => array(
            'title' => t('View user profile.'),
            'class' => array('symbol', (isset($variables['dimensions'])) ? 'symbol-'.$variables['dimensions'] : 'symbol-40'),
          ),
          'html' => TRUE,
        );
        $variables['user_picture'] = l($variables['user_picture'], "user/{$account->uid}", $attributes);
      } elseif (user_access('access user profiles')) {
        $variables['user_picture'] = "<span class=\"symbol symbol-" . (isset($variables['dimensions']) ? $variables['dimensions'] : "40") . "\">" . $variables['user_picture'] . "</span>";
      }
    }
  }
}

/** Override theme_file_upload_help to properly display the file upload popover */
function bootstrap_keen_file_upload_help(array $variables) {
  // If popover's are disabled, just theme this normally.
  if (!bootstrap_setting('popover_enabled')) {
    return theme_file_upload_help($variables);
  }

  $build = array();
  if (!empty($variables['description'])) {
    $build['description'] = array(
      '#markup' => $variables['description'] . '<br>',
    );
  }

  $descriptions = array();
  $upload_validators = $variables['upload_validators'];
  if (isset($upload_validators['file_validate_size'])) {
    $descriptions[] = t('Files must be less than !size.', array('!size' => '<strong>' . format_size($upload_validators['file_validate_size'][0]) . '</strong>'));
  }
  if (isset($upload_validators['file_validate_extensions'])) {
    $descriptions[] = t('Allowed file types: !extensions.', array('!extensions' => '<strong>' . check_plain($upload_validators['file_validate_extensions'][0]) . '</strong>'));
  }
  if (isset($upload_validators['file_validate_image_resolution'])) {
    $max = $upload_validators['file_validate_image_resolution'][0];
    $min = $upload_validators['file_validate_image_resolution'][1];
    if ($min && $max && $min == $max) {
      $descriptions[] = t('Images must be exactly !size pixels.', array('!size' => '<strong>' . $max . '</strong>'));
    }
    elseif ($min && $max) {
      $descriptions[] = t('Images must be between !min and !max pixels.', array('!min' => '<strong>' . $min . '</strong>', '!max' => '<strong>' . $max . '</strong>'));
    }
    elseif ($min) {
      $descriptions[] = t('Images must be larger than !min pixels.', array('!min' => '<strong>' . $min . '</strong>'));
    }
    elseif ($max) {
      $descriptions[] = t('Images must be smaller than !max pixels.', array('!max' => '<strong>' . $max . '</strong>'));
    }
  }

  if ($descriptions) {
    $id = drupal_html_id('upload-instructions');
    $build['instructions'] = array(
      '#theme' => 'link__file_upload_requirements',
      // @todo remove space between icon/text and fix via styling.
      '#text' => '<button class="btn btn-xs btn-icon btn-light-primary"><i class="fas fa-question"></i></button> ' . t('More information'),
      '#path' => '#',
      '#options' => array(
        'attributes' => array(
          'data-toggle' => 'popover',
          'data-target' => "#$id",
          'data-html' => "true",
          'data-placement' => 'bottom',
          'data-title' => t('File requirements'),
        ),
        'html' => TRUE,
        'external' => TRUE,
      ),
    );
    $build['requirements'] = array(
      '#theme_wrappers' => array('container__file_upload_requirements'),
      '#attributes' => array(
        'id' => $id,
        'class' => array('element-invisible', 'help-block'),
      ),
    );
    $build['requirements']['validators'] = array(
      '#theme' => 'item_list__file_upload_requirements',
      '#items' => $descriptions,
    );
  }

  return drupal_render($build);
}
