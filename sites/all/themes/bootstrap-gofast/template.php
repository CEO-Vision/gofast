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
function bootstrap_gofast_select($variables) {
  $element = $variables['element'];
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . bootstrap_gofast_form_select_options($element) . '</select>';
}

function bootstrap_gofast_form_select_options($element, $choices = NULL) {
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
function bootstrap_gofast_menu_link__main_menu($variables) {
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


function bootstrap_gofast_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if(empty($breadcrumb)) {
    return;
  }
  $output = '';
  $title_plus = t("Show more breadcrumb");
  $title_minus = t("Show less breadcrumb");
  if (isset($breadcrumb[0]) && !is_array($breadcrumb[0])) {
    array_shift($breadcrumb);
    $items = array();
    foreach ($breadcrumb as $item) {
      if (!is_array($item)) {
        $items[] = $item;
      }
      else {
        $items[] = $item['data'];
      }
    }
    return '<div class="breadcrumb gofast breadcrumb-gofast">' . implode(' » ', $items) . '</div>';
  }
  else {
    $output = '<div class="breadcrumb gofast breadcrumb-gofast">';
    
    $full_breadcrumb = $breadcrumb;
    $reverse_bc = array_reverse($breadcrumb);
    $array_clone = $reverse_bc;
    $first_element_bc = array_shift($array_clone);
    if(isset($first_element_bc['data'])) {
      array_shift($reverse_bc);
      $full_breadcrumb = array_reverse($reverse_bc);
    }

    foreach ($full_breadcrumb as $key => $crumbs) {
      if(isset($crumbs['data'])) {
        continue;
      }
      array_shift($crumbs);
      $line = implode(' » ', $crumbs);
      //if ($key !== count($breadcrumb) - 1) {
        if ($key === 0) {
          $class = "gofast_breadcrumb_display";
        }
        else {
          $class = "gofast_breadcrumb_hidden gofast_breadcrumb_hidden_origine";
        }
        $output .= "<div id='" . $key . "' class='" . $class . "' style='margin:2px;' >" . $line;
        if ($key === 0 && count($full_breadcrumb) > 1) {
          $output .= " <i class='glyphicon glyphicon-plus-sign' id='gofast_breadcrumb_more' style='cursor:pointer;color:black;' title=\"" . $title_plus . "\" ></i>";
        }
        $output .= "</div>";
      //}
    }
    $output .= "</div>";

    $output .= "<style type='text/css'> .gofast_breadcrumb_hidden { display : none; }</style>";
    $output .= '<script type="text/javascript">
                       jQuery("#gofast_breadcrumb_more").click(function(){
                                    jQuery(".gofast_breadcrumb_hidden_origine").toggleClass( "gofast_breadcrumb_hidden");
                                    if(jQuery(this).hasClass("glyphicon-plus-sign")){
                                        jQuery(this).removeClass("glyphicon-plus-sign").addClass("glyphicon-minus-sign").attr("title", "' . $title_minus . '");
                                    }else{
                                        jQuery(this).removeClass("glyphicon-minus-sign").addClass("glyphicon-plus-sign").attr("title", "' . $title_plus . '");
                                    }
                        })    
                  </script>';
  }

  return $output;
}

/**
 * Overrides theme_textfield().
 */
function bootstrap_gofast_textfield($variables) {
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
    
    $ac_icon = empty($element['#no_icon']) ? '<span class="input-group-addon">' . _bootstrap_icon('refresh') : '';
    $style = $ac_icon ? '' : 'style="width:100%;"';
    $output = '<div class="input-group" ' . $style . '>' . $output . $ac_icon . '</span></div>';
    
    $extra = '<input' . drupal_attributes($attributes) . ' />';
  }

  return $output . $extra;
}

/**
 * Theme override for bootstrap_search_form_wrapper.
 */
function bootstrap_gofast_bootstrap_search_form_wrapper($variables) {
  $output = '<div class="input-group" style="width:100%;">';
  $output .= $variables['element']['#children'];
  
  $output .= '<span class="input-group-btn">';
  $output .= '<button type="submit" class="btn btn-default" style="border-left:none;">';
  $output .= _bootstrap_icon('search');
  $output .= '</button>';
  $output .= '</span>';
  
  if (isset($variables['element']['#wrap'])) {
    $output .= $variables['element']['#wrap'];
    unset($variables['element']['#wrap']);
  }
  
  $output .= '</div>';
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
function bootstrap_gofast_facetapi_title($variables) {
   // return t(ucwords(drupal_strtolower($variables['title'])));
//  $variables['title'] = t( $variables['title'], array(), array('context' => 'gofast:gofast-search'));
  return t('@title', array('@title' => $variables['title']));
}

/**
 * @override the sort list in apachesolr sort block.
 * @see theme_apachesolr_sort_link()
 */
function bootstrap_gofast_apachesolr_sort_list($variables) {
  foreach ($variables['items'] as $key => &$item) {
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
function bootstrap_gofast_links__locale_block(&$variables) {
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

function bootstrap_gofast_preprocess_node(&$variables) {
  $variables['author_pane'] = theme('gofast_forum_simple_author_pane', array('context' => $variables['node']));
}

function bootstrap_gofast_preprocess_comment(&$variables) {
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
function bootstrap_gofast_username($variables) {
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
function bootstrap_gofast_menu_local_tasks_alter(&$data, $router_item, $root_path) {
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
function bootstrap_gofast_image_style($variables) {
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
  $variables['path'] = image_style_url($variables['style_name'], $variables['path']);
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
function bootstrap_gofast_menu_link__user_menu(array $variables) {
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
function bootstrap_gofast_password($variables) {
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

function bootstrap_gofast_preprocess_html(&$variables) {
  $variables['classes_array'][] = 'body_display_none';
  //add new font
  drupal_add_css('sites/all/themes/bootstrap-gofast/fonts/Roboto.css', array('group' => CSS_THEME ));
}

function bootstrap_gofast_preprocess_views_view_table(&$variables) {
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
function bootstrap_gofast_theme_registry_alter(&$theme_registry) {
  
  if(module_exists('entity_menu_links')){
    // Make sure that menu links don't get themed like regular entities.
    $hooks = preg_grep('/^menu_link(\.|__).+$/', array_keys($theme_registry));
    foreach ($hooks as $hook) {
      $theme_registry[$hook]['render element'] = 'element';
      $theme_registry[$hook]['base hook'] = 'menu_link';
    }
  } 
}

function bootstrap_gofast_facetapi_deactivate_widget($variables) {
  $button_delete_search = ' <button type="button" class="btn btn-default" style="color: #2ecc71;padding:1px;"><span style="color:#2980b9;padding:3px 4px 4px 4px;" class="ctools-use-modal fa fa-times" title="'.t("Remove this search filter",  array(), array('context' => 'gofast:search')).'"></span></button>&nbsp;';

  return $button_delete_search;
}