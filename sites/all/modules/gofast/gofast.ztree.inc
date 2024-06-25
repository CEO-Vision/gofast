<?php

/**
 * Extends du hook_library pour inclure la librairie ztree nécessaire pour l'édition inline/popup
 *
 * @return string
 */
function gofast_ztree_libraries_info(&$libraries) {
  $libraries['ztree'] = array(
    'name' => 'ztree',
    'vendor url' => 'http://www.ztree.me/v3/main.php',
    'download url' => 'https://git.oschina.net/zTree/zTree_v3/repository/archive/master',
    'version' => '3.5.24',
    'version callback' => 'short_circuit_version',
    'files' => array(
      'js' => array(
        'js/jquery.ztree.all.js',
        'js/jquery.ztree.exhide.min.js', // This allow hide/filter
      ),
      'css' => array(
        'css/zTreeStyle/zTreeStyle.css'
      ),
    ),
  );
}

/**
 * Extends hook_menu()
 */
function gofast_ztree_menu() {
  $items = array();
  $dev_mode = gofast_dev_mode();

  // This is the block with only ztree component
  $items['ztree/%/%'] = array(
    'title' => 'Ztree',
    'description' => "Display ztree",
    'page callback' => 'gofast_get_ztree_block_content',
    'page arguments' => array(1, 2),
    'access callback' => $dev_mode,
    'type' => MENU_CALLBACK,
  );

  // This is the block with the ztree + location items
  $items['ztree_location/%/%/%/%'] = array(
    'title' => 'Ztree',
    'description' => "Display ztree location widget",
    'page callback' => 'gofast_get_ztree_location_block_content',
    'page arguments' => array(1, 2, 3, 4),
    'access callback' => $dev_mode,
    'type' => MENU_CALLBACK,
  );

  $items['ztree_location/rendered/%/%'] = array(
    'title' => 'Ztree location widget rendered',
    'description' => "Render and return ztree location widget content",
    'page callback' => 'gofast_ztree_get_ztree_location_content',
    'page arguments' => array(2, 3),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
    'delivery callback' => 'gofast_ajax_delivery',
  );

  $items['ztree/templates/async'] = array(
    'page callback' => 'gofast_ztree_templates_build_async',
    'type' => MENU_CALLBACK,
    'access arguments' => array('access content'),
    'access callback' => 'user_access'
  );

  $items['ztree_location/async'] = array(
    'title' => 'Ztree location widget rendered',
    'description' => "Render and return ztree location widget content",
    'page callback' => 'gofast_ztree_async_json',
    'page arguments' => array(),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
    'delivery callback' => 'gofast_ajax_delivery',
  );

  $items['ztree_location_members/async'] = array(
    'title' => 'Ztree location and members widget rendered',
    'description' => "Render and return ztree location and members widget content",
    'page callback' => 'gofast_ztree_async_json',
    'page arguments' => array(),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
    'delivery callback' => 'gofast_ajax_delivery',
  );

  $items['ztree/values_async/%'] = array(
    'title' => 'Get ztree values async',
    'page callback' => 'gofast_ztree_values_async_json',
    'page arguments' => array(2),
    'access arguments' => array('access content'),
    'access callback' => 'user_access',
    'type' => MENU_CALLBACK,
  );

  return $items;
}


/*
 * This function loads ztree values asynchrounsly and send them to the client
 */
function gofast_ztree_values_async_json($component){
    $output = "";

    switch($component){
        case 'ztree_component_content_templates':
            $output = gofast_cmis_alfresco_item_node_get_form_user_templates();
            break;
        default:
            break;
    }

    print $output;
    exit;
}


/**
 * This method returns all the spaces and spaces' folders that an user can see.
 * If 1st parameter is set to TRUE, returns only the spaces where the user is member of (or public).
 * @param boolean $spaces_only returns only spaces where member has membership (or public). Default FALSE
 * @return array the list of spaces, plus the sub-folder if specified.
 */
function gofast_ztree_get_paths($spaces_only = FALSE, $account = null, $origine = null) {

  global $user;
  $filter = $spaces_only ? "groups" : "groupsfolders";
  $all_path = gofast_cmis_get_emplacements_cache($user->uid, $filter, $origine);
  return $all_path;
}

/**
 * This function returns the children paths of a given node (nid). Also returns the space path.
 * @param int $space_nid
 * @return type
 */
function gofast_ztree_space_get_paths($space_nid) {
  $og_paths = array();
  $space_path = gofast_cmis_space_get_webdav_path($space_nid);
  $og_paths[$space_nid] = $space_path;
  $group_children = gofast_cmis_get_children($space_path);
  if (!empty($group_children)) {
    $og_paths += array_flip($group_children);
  }
  asort($og_paths);
  return $og_paths;
}

/**
 * This function normalizes the list given in parameter in order to get a list
 * of paths. If the entries are paths we do nothing, if it's space names,
 * transforms the list of names in list of paths.
 * @param type $list the input list that could be paths or list of space names
 * @return array
 */
function gofast_ztree_normalize_list($list) {
  $sorted_list = array();
  // If the given array of path are real paths or list of spaces
  foreach ($list as $key => $list_item) {
    if (is_object($list_item) && intval($list_item->nid) !== 0) {
      $sorted_list[$key] = gofast_cmis_space_get_webdav_path($list_item->nid);
    }
    else {
      if (intval($key) !== 0) {
        $sorted_list[$key] = gofast_cmis_space_get_webdav_path($key);
      }
      else {
        $sorted_list[$key] = $list_item;
      }
    }
  }
  $sorted_list = gofast_ztree_get_drupal_path_from_webdav_path($sorted_list);
  asort($sorted_list);

  return $sorted_list;
}

/**
 * This method displays a ztree widget only.
 * @param string $id the name of the widget (it means context)
 * @param array $array_paths a collection of visible paths
 * @param array $selected_paths a collection of pre-selected paths (can be paths that are not in visible paths collection)
 * @param array $disabled_paths a collection of disabled paths (can be paths that are not in visible paths collection)
 * @param array $obfuscated_paths a collection of obfuscated paths (can be paths that are not in visible paths collection)
 * @param array $options a collection of options to send to js widget
 * @return array the generated block
 */
function gofast_ztree_block_content($id, $array_paths = array(), $options = array(), $path_options = array(), $async = false) {
  global $user;
  $content = array();

  $path_options += array(
    'selected_paths' => array(),
    'disabled_paths' => array(),
    'non_member_paths' => array(),
    'check_disabled_paths' => array(),
    'obfuscated_paths' => array(),
    'templates_paths' => array(),
  );

  foreach ($path_options as $key => $path_option) {
    if (is_array($path_option) && !empty($path_option)) {
     if($async == false){
      $path_options[$key] = gofast_ztree_normalize_list($path_option);
      $array_paths = gofast_ztree_normalize_list($array_paths);
     }else{
      $path_options[$key] = $path_option;
     }
      //Free the memory
      unset($path_option);
    }
  }

  //check that the default value was not added on the disabled path
  if(count($path_options["selected_paths"]) > 0){
      foreach($path_options["selected_paths"] as $gid_selected=>$path_selected){
         if(isset($path_options["disabled_paths"][$gid_selected])){
             unset($path_options["disabled_paths"][$gid_selected]);
         }
      }
  }

  $selected_and_selectable_og = $array_paths;
  foreach ($path_options['selected_paths'] as $key => $selected_location) {
    if (!in_array($selected_location, $array_paths, TRUE)) {
       $selected_and_selectable_og[$key] =  $selected_location;
    }
  }

  $content['user_visible_paths'] = $selected_and_selectable_og;
  $content['pre_selected_paths'] = $path_options['selected_paths'];
  $content['disabled_paths'] = $path_options['disabled_paths'];
  $content['obfuscated_paths'] = $path_options['obfuscated_paths'];
  $content['templates_paths'] = $path_options['templates_paths'];

  // If there is no data, return empty array
  if (empty($array_paths) && empty($path_options['selected_paths']) && empty($path_options['disabled_paths']) && empty($path_options['obfuscated_paths']) && empty($path_options['templates_paths'])) {
    return $content;
  }

  $path_options['check_disabled_paths'] = array();
  // Then, we prepare the Json to be used by the ztree component
  if($async == false){
    $tree = gofast_ztree_array_path_to_nested_objects($selected_and_selectable_og, $path_options);
  }else{
    $tree = gofast_ztree_array_path_to_nested_objects_async($selected_and_selectable_og, $path_options);
  }
  $json = $tree->__toString();

  $content_widget_alfresco_emplacement = $json;

  libraries_load('ztree');

  $widget_id = $id === NULL ? 'new' : $id;
  $ztree_id = "ztree_component_" . $widget_id;

  // We set the generated json in JS object so we can retrieve it on page load behiavor

  $my_settings = array('data_tree' => $content_widget_alfresco_emplacement, "ztree_options" => $options, "async" => $async);

  $widget_addons = array();
  $is_single = isset($options["single_location"]) && $options["single_location"] === true;
  if (isset($options["widget_locations"]) && $options["widget_locations"] === "true") {
    $widget_addons[] = '<div class="ui-selected-locations' . ($is_single ? ' ui-single-location' : '') . '"></div>';
  }


  if (isset($options["form"]) && $id != "locations") {

       //If the user is broadcaster, he can publish to location where he is not a member of.
      global $user;
      $mynode = node_load($options["form"]["id"]);
      if (gofast_user_is_broadcaster($user) && ($mynode->type == "alfresco_item" || $mynode->type == "article")) {
        $attributes = [
          'class' => [' form-control-tags js-tagify'],
          //'data-enforce'=>'', //  Comment : Do not allow putting data that dose not exist | Decomment : allow putting data that dose not exist
          'data-user' => '', // show ac users
          'data-node' => '', // show ac node
          //'data-userlist' => '', // show ac userlist
          // 'data-taxonomy_term' => '' // show ac taxonomy term
          'data-broadcast' => '', //Caution : Override all permissions to allow broadcasting
        ];
        
        $form['broadcast_og'] = array(
         '#title' => t("Broadcast : Share this document to a space you're not in"),
         '#type' => 'textfield',
         '#name' => 'ac-list-tags-broadcast',
         '#maxlength' => '', // no maxlength
         '#default_value' => '',
         '#prefix' => "<div style='clear:both;'>",
         '#suffix' => "</div>",
         '#description' => "<p class='text-muted'>" . t("Start typing the name of a space or a user"),
         '#attributes' => $attributes
        );

        $html_form = "<div id='broadcast_xeditable' style='float:left;margin-top:30px;'><h4>".t("Broadcast", array(), array('context' => 'gofast'))."</h4>".drupal_render($form)."</div>";
      }else{
          $html_form = "";
      }




    $hidden_form_selected_path = '<form action="' . $options["form"]['url'] . '" style="">'.$html_form
            . '<select style="display: none;" class="form-selected-locations" multiple name="value[]">';
    foreach ($selected_and_selectable_og as $key => $path) {
      $exists = in_array($path, $path_options['selected_paths']);
      $selected = $exists ? ' selected="selected"' : '';
      $hidden_form_selected_path .= '<option value="' . $key . '" ' . $selected . '>' . $path . '</option>';
    }
    $hidden_form_selected_path .= '<input type="hidden" name="pk" value="' . $options["form"]['id'] . '" />';
    $hidden_form_selected_path .= '<input type="hidden" name="name" value="' . $options["form"]['field_name'] . '" />';
    $hidden_form_selected_path .= '</form>';
    $hidden_form_selected_path .= '<div class="ztree-buttons">
          <button type="submit" class="btn btn-success btn-sm ztree-locations-submit">
            <i class="glyphicon glyphicon-ok"></i>
            ' . t("Apply") . '
          </button>
          <button type="button" class="btn btn-default btn-sm ztree-locations-cancel">
            <i class="glyphicon glyphicon-remove"></i>
            ' . t("Cancel") . '
          </button>
        </div>';
    $widget_addons[] = $hidden_form_selected_path;
  }

  // Finally, we construct all the HTML that will be rendered
  $content['content']["#markup"] = '
          <div class="ztree-widget">
            <div class="ztree-browser">
              <div class="ztree ztree-component" id="' . $ztree_id . '"></div>
              ' . implode('', $widget_addons) . '
            </div>
          </div>';
  $content['content']['#attached']['js'][] = drupal_get_path("module", "gofast") . "/js/gofast_ztree.js";
  $content['content']['#attached']['js'][] = array(
    'data' => array($ztree_id => $my_settings),
    'type' => 'setting',
  );

  return $content;
}

/**
 * This method replace a string by another string of the same length but with 'x' characters.
 * @param type $string the string to obfuscate.
 * @return string the string obfuscated.
 */
function gofast_ztree_obfuscate_string($string) {
  $obfuscated_parts = array();
  foreach (explode('/', $string) as $part) {
    if (!in_array($part, array('Groupes', 'Organisations'))) {
      $obfuscated_parts[] = str_repeat("x", 5);
    }
    else {
      $obfuscated_parts[] = $part;
    }
  }
  return implode('/', $obfuscated_parts);
}

function gofast_ztree_get_obfuscated_path($path) {
  $parts = explode('/', $path);
  $gid = gofast_og_get_group_id_from_title($path, TRUE);
  if ($gid !== FALSE) {
    $group = array_pop($parts);
    $group_title = node_access("view", node_load($gid)) ? $group : 'xxxxx';
    return $group_title;
  }
  else {
    $parent_group = null;
    while ($parent_group === null) {
      $part = array_pop($parts);
      $parent_group = gofast_og_get_group_id_from_title(implode('/', $parts), TRUE);
    }
  }
}

/**
 * This method renders a widget depending to context
 * @param type $context alfresco_item | article | user | any other
 * @param type $nid the nid of the context
 * @param type $inline display the widget inline (alone) or with form location widget
 * @param type $url the url of the form submit (not inline only)
 * @param type $field the field to update (not inline only)
 * @return string the widget rendered with js included.
 */
function gofast_ztree_get_ztree_location_content($nid) {
  $node = node_load($nid);
  $wrapper = entity_metadata_wrapper('node', $node);

  if ($node->type === "alfresco_item" || $node->type === "article") {
    $visible_paths = gofast_ztree_get_paths();
    $selected_paths = $wrapper->{GOFAST_CMIS_LOCATIONS_FIELD}->value();
    $ztree_options = array("widget_locations" => "true",
      "form" => array(
        'field_name' => GOFAST_CMIS_LOCATIONS_FIELD,
        'id' => $node->nid,
        'url' => '/update_node_field'
    ));
  }
  else {
    $visible_paths = gofast_ztree_get_paths(TRUE);
    $selected_paths = $wrapper->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}->value();
    $ztree_options = array("widget_locations" => "true",
      "form" => array(
        'field_name' => GOFAST_OG_CONTENT_MEMBERSHIP_FIELD,
        'id' => $node->nid,
        'url' => '/update_node_field'
    ));
  }

  $ztree_options = array();
  $paths_options += array(
    'selected_paths' => $selected_paths,
  );
  $ztree_widget = gofast_ztree_block_content($nid, $visible_paths, $ztree_options, $paths_options, true);

  // We unset ztree variables so we can render the ztree without errors
  unset($ztree_widget['user_visible_paths']);
  unset($ztree_widget['pre_selected_paths']);
  unset($ztree_widget['disabled_paths']);
  unset($ztree_widget['obfuscated_paths']);
  return drupal_render($ztree_widget);
}

class ztree_tree {

  public $children = [];

  public function getChild($name) {
    foreach ($this->children as $child) {
      if ($child->id === $name) {
        return $child;
      }
    }
  }

  public function addChild(ztree_node $node) {
    $this->children[] = $node;
    $this->isParent = true;
    return $this->children;
  }

  public function __toString() {
    return json_encode($this->children);
  }

  public function obfuscateName() {
    $this->name = str_repeat("x", strlen($this->name));
  }

  public function deobfuscateName() {
    $this->obfuscated = FALSE;
    $this->name = $this->id;
    if ($this->name !== 'Sites') {
      $this->nocheck = FALSE;
      $this->obfuscated = FALSE;
      $this->chkDisabled = FALSE;
    }
  }

}

class ztree_node extends ztree_tree {

  public $name;
  public $id;
  public $ename;
  public $isParent;
  public $open;
  public $checked;
  public $nocheck;
  public $chkDisabled;
  public $icon;
  public $gid;
  public $last_depth;
  public $obfuscated;
  public $is_template;
  public $is_mirror;
  public $non_member;
  public $isHidden;
  public $showLine;

  /**
   *
   * @param type $name
   * @param type $path
   * @param type $gid
   * @param type $last_depth
   */
  public function __construct($name, $path, $gid, $last_depth) {
    $this->id = $name;
    $this->name = $name;
    $this->ename = $path;
    //debug
    //$this->isParent = FALSE;
    $this->isParent = TRUE;
    $this->gid = $gid;
    $this->last_depth = $last_depth;
    $this->checked = FALSE;
    $this->nocheck = FALSE;
    $this->obfuscated = FALSE;
    $this->chkDisabled = FALSE;
    $this->non_member = FALSE;
    $this->isHidden = FALSE;
    $this->is_template = FALSE;
    $this->is_mirror = FALSE;
    $this->showLine = TRUE;

    switch ($name) {
      case 'Sites':
        $this->nocheck = FALSE;
        $this->chkDisabled = FALSE;
        $this->showLine = TRUE;
        $this->open = TRUE;
        break;
      default:
        $this->open = FALSE;
        break;
    }
  }

  private function get_icon_space() {
    $type = '';
    $re_private_space = "/^\\/(?!(Groups|Organisations|Public|Extranet))([^\\/]+)/";
    $private_space_matches = array();
    preg_match($re_private_space, $this->ename, $private_space_matches);
    if (isset($private_space_matches[1])) {
      $type = 'Private_space';
    }
    else {
      $re_space = "/([^\\/]+)/";
      $space_type_matches = array();
      preg_match($re_space, $this->ename, $space_type_matches);

      if (isset($space_type_matches[1])) {
        $type = $space_type_matches[1];
      }
    }
    return $type;
  }

  private function get_icon_space_async() {
    $type = '';
    $re_private_space = "/^\\/(?!(Groups|Organisations|Public|Extranet))([^\\/]+)/";

    //split path by /
    $array_path = explode("/", $this->ename);
    if(isset($array_path[2])){
        if($array_path[2] == '_Groups' || $array_path[2] == 'Groups'){
            $type = "Groups";
        }elseif($array_path[2] == '_Organisations'){
             $type = "Organisations";
        }elseif($array_path[2] == 'Organisations'){
             $type = "Organisations";
        }elseif($array_path[2] == '_Extranet'){
             $type = "Extranet";
        }elseif($array_path[2] == 'Extranet'){
             $type = "Extranet";
        }elseif($array_path[2] == '_Public'){
             $type = "Public";
        }elseif($array_path[2] == 'Public'){
             $type = "Public";
        }else{
             $type = "Private_space";
        }
    }else{
         $type = "";
    }
    return $type;
  }

  /**
   * Return webfont corresponding png file
   * @param type $input
   * @return string
   */
  public function convert_fa_to_img($input) {

    $matcher = array(
        'fa-file-word-o' => 'word.png',
        'fa-file-o file-other' => 'other.png',
        'fa-file-powerpoint-o' => 'powerpoint.png',
        'fa-home' => 'home.png',
        'fa-globe' => 'globe.png',
        'fa-file-text-o' => 'text.png',
        'fa-comments-o' => 'comments.png',
        'fa-file-code-o' => 'code.png',
        'fa-file-image-o' => 'image.png',
        'fa-sitemap' => 'sitemap.png',
        'fa-newspaper' => 'ballot.png',
        'fa-file-pdf-o pdf-image' => 'pdf-image.png',
        'fa-file-pdf-o' => 'pdf.png',
        'fa-share-alt' => 'share.png',
        'fa-file-excel-o' => 'excel.png',
        'fa-users' => 'users.png',
        'fa-video-camera' => 'conference.png',
        'fa-file-sound-o' => 'audio.png',
        'fa-list-alt file-webform' => 'webform.png',
        'fa-file-o file-visio' => 'visio.png',
        'fa-file-video-o' => 'video.png',
        'fa-file-image-o image-svg' => 'svg.png',
        'fa-id-card-o' => 'profile.png',
        'fa-file-text-o file-odg' => 'odg.png',
        'fa-envelope-o' => 'mail.png',
        'fa-file-o file-cao' => 'cao.png',
        'fa-file-archive-o' => 'archive.png',
        'fa-trello' => "trello.png"
    );
    foreach ($matcher as $fa => $png) {
      if ($input == $fa) {
        return $png;
      }
    }
    return 'other.png';
  }

  /**
   *
   * @return type
   */
  public function update_icon_template() {
    $type = '';
    $spaces = array('Groups', 'Organisations', 'Public', 'Extranet');
    $path_tail =  array_pop(explode("/", $this->crumb));

    // TEMPLATES folder
    if (!$this->is_template && !in_array($this->ename, $spaces) && strpos($this->ename, TEMPLATES_FOLDER_NAME) !== FALSE) {
      $type = 'folder';
    // SPACE
    }elseif(!$this->is_template && (in_array($this->ename, $spaces) || $path_tail[0] == "_")) {
      $type = $this->get_icon_space();
    // FOLDER
    }elseif(!$this->is_template) {
      $type = 'folder';
    // FILE
    }elseif ($this->is_template && $this->last_depth && $this->name !== 'None') {
      $extension = pathinfo($this->name)['extension'];
      $term_id = gofast_taxonomy_get_taxo_id_from_extension($extension);
      $icons = gofast_taxonomy_load_icons();
      $fa_icon = isset($icons[$term_id]) ? $icons[$term_id] : 'fa-file-o';
      $icon =  '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/'.$this->convert_fa_to_img($fa_icon);
      $this->icon = str_replace(' ', '%20', $icon);
      $this->isParent = 0;
      return;
    // FALLBACK
    } else {
      $type = $this->get_icon_space();
    }

    $this->icon = str_replace(' ', '%20',gofast_ztree_get_node_icon($type));
  }

  public function update_icon() {
    $type = '';
    if (intval($this->gid) === 0) {
      $type = 'folder';
    }
    else {
      $type = $this->get_icon_space();
    }
    $this->icon = gofast_ztree_get_node_icon($type);
  }

   public function update_icon_async() {
    $type = '';
    if (intval($this->gid) === 0) {
      if($this->is_mirror){
        $type = 'mirror';
      }else{
        $type = 'folder';
      }
    }
    else {
      $type = $this->get_icon_space_async();
    }
    $this->icon = gofast_ztree_get_node_icon($type);
  }

}

/**
 * This method generates a ztree object containing all the data given in paths.
 * @param type $array_path the list of all paths we want in the tree
 * @param array $array_options an array of options that alters the paths :
 * <ul>
 * <li>selected_paths a list of pre-selected paths</li>
 * <li>disabled_paths a list of paths that need to be disabled</li>
 * <li>check_disabled_paths a list of paths that cannot be checked</li>
 * <li>obfuscated_paths a list of paths that need to be obfuscated</li>
 * <li>non_member_paths a list of paths the user is not member of</li>
 * <li>templates_paths a list of template paths</li>
 * </ul>
 * @param type $delimiter the delimiter of the paths (usually /)
 * @return boolean|ztree_tree false if no path array is set, tree otherwise.
 */
function gofast_ztree_array_path_to_nested_objects_async($array_path = array(), $array_options = array(), $delimiter = '/', $origine = null, $nid = null , $is_publication = false) {
  if($nid !== null){
      $current_node = node_load($nid);
  }
  if (!is_array($array_path)) {
    return false;
  }

  // This is the declaration of the variables that are in $array_options
  $selected_paths;
  $disabled_paths;
  $check_disabled_paths;
  $obfuscated_paths;
  $non_member_paths;
  $templates_paths;
  $not_managed;
  $disable_space_check;

  extract($array_options);

  foreach ($array_path as $key => $path) {
    if($origine){

      $path = str_replace($origine, "", $path);
      $array_path[$key] = $path;
    }
  }
  // Sort paths in ascending order, case-insensitive, spaces first
  uasort($array_path, function($path_a, $path_b){
    // Take only the last part of the path to compare them
    $path_a = end(explode("/", $path_a));
    $path_b = end(explode("/", $path_b));
    // If we compare a space and a folder put the space before
    if(str_starts_with($path_a, "_") XOR str_starts_with($path_b, "_")){
      return str_starts_with($path_a, "_") ? -1 : 1;
    }
    // If we compare two space or two folder, sort normally case-insensitive
    return strtoupper($path_a) <=> strtoupper($path_b);
  });

  $tree = new ztree_tree;
  $last_depth = false;

  // We proceed to user accessible paths
  foreach ($array_path as $gid => $path) {
    if (strpos($path, "Wikis") != FALSE) {
      continue;
    }
    $is_non_member_paths = false;
    /*if (in_array($path, $non_member_paths)) {
      $is_non_member_paths = true;
    } */
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    $og_space = node_load($gid);
    $index = -1;
    foreach ($parts as $part) {
      $index++;
      $parent_computed_path = $computed_path;
      $computed_path .= '/' . $part;


      //add members if necessary
      if (!$node->getChild($part) ){

        $last_depth = $index === count($parts) - 1;

        if(isset($array_options['spaces_members']['display']) && $array_options['spaces_members']['display'] == TRUE
            && ($origine."".$computed_path != '/Sites' && $_GET['members'] !== "false")
          ) {

          $members_already_loaded = $node->getChild(t('Members', array(), array('context' => 'gofast'))) ;

          if ( ! $members_already_loaded
             && ( $last_depth == true && $origine != "") || ( $last_depth != true && $origine == "") // asynchronous request (i.e. origine defined) or not last depth
             && ($origine."".$parent_computed_path != '/Sites' ) // not a root space nor a private one
          ) {

            //add user to the node
            if($last_depth != true){

              $current_options = $array_options['spaces_members'];
              if(! in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $node->gid))){
                $current_options['chkDisabled'] = TRUE;
              }
              gofast_ztree_add_node_members($node, $node->gid, 'active', $current_options);

            }else{

              $current_options = $array_options['spaces_members'];
              if(! in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $gid))){
                $current_options['chkDisabled'] = TRUE;
              }
              gofast_ztree_add_node_members($node, $gid, 'active', $current_options);
            }
          }
        }
        if( strlen($part) > 0 ){ //avoid creation of empty node
          $node->addChild($node = new ztree_node($part, $origine."".$computed_path, $gid, $last_depth));

          if ($index === 0) {
            $node->open = TRUE;
          }
          $node->update_icon_async();
        }
      }
      else {
        $node = $node->getChild($part);
      }
      if ($path === $origine."".$computed_path) {
        $node->non_member = $is_non_member_paths;
        $node->isHidden = $is_non_member_paths ? TRUE : FALSE;
      }
      if(gofast_og_is_root_space($og_space) && isset($array_options['root_spaces_selection']) && $array_options['root_spaces_selection'] == FALSE){
        $node->nocheck = TRUE;
      }

      if($disable_space_check && $og_space != false){ //TODO Pass param in ztree_location/async
         $node->nocheck = TRUE;
      }

      //prevent choose some groups depending on permission
      //WARNING : This permission check should NOT be here, skip it with a target condition if your tree doesn't need permission check
      if(isset($og_space->nid) && !$not_managed){
            if(!og_user_access("node", $gid, "create alfresco_item content")){
                $node->nocheck = TRUE;
            }
      }

    }
  }

  foreach ($disabled_paths as $gid => $path) {
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      if ($node->getChild($part) != null){
          $node = $node->getChild($part);
          if (isset($node) && $node->ename === $path || isset($node) && $node->ename == $gid) {
            $node->open = TRUE;
            $node->nocheck = TRUE;
            if (!gofast_og_is_root_space(node_load($node->gid))){
              $node->open = FALSE;
              if(gofast_group_is_archive(node_load($node->gid))){
                  $node->icon = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/folder-archive-primary.png';
              }else{
                  //$node->icon = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/ban.png';
              }
            }
          }
      }
    }
  }

  foreach ($selected_paths as $gid => $path) {
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      if(isset($node)){
        $node = $node->getChild($part);
        if (isset($node) && $path === $computed_path) {
          $node->open = TRUE;
          $node->checked = TRUE;
        }
      }
    }
  }
    if (!$is_publication){

      //Manage readonly selected spaces/folders
      foreach ($selected_paths as $selected_id => $path) {

        if ($current_node->type !== 'alfresco-item' && $current_node->type !== 'article') {
          // Note : perms are the same for all node => explains the usage of alfresco_item for testing access
          if (is_int($selected_id) && !og_user_access("node", $selected_id, "create alfresco_item content")) {
            $check_disabled_paths[$selected_id] = $path;
          }
          // Manage specific case where space was created by the current user and he's not member anymore
          else if (is_int($selected_id) && og_user_access("node", $selected_id, "delete alfresco_item content") && !og_is_member('node', $selected_id, 'user') && !gofast_userlist_og_is_user_member_of_space($selected_id) ) {
            $check_disabled_paths[$selected_id] = $path;
          }
        }
        else {
          if (is_int($selected_id) && (!og_user_access("node", $selected_id, "delete alfresco_item content") && (!node_access("delete", $current_node)))) {
            $check_disabled_paths[$selected_id] = $path;
          }
          // Manage specific case where space was created by the current user and he's not member anymore
          else if (is_int($selected_id) && og_user_access("node", $selected_id, "delete alfresco_item content") && !og_is_member('node', $selected_id, 'user') && !gofast_userlist_og_is_user_member_of_space($selected_id) ) {
            $check_disabled_paths[$selected_id] = $path;
          }
        }
      }
    }

  foreach ($check_disabled_paths as $gid => $check_disabled_path) {
    $node = $tree;
    $computed_path = '';
    if (substr($check_disabled_path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($check_disabled_path, 1));
    }
    else {
      $parts = explode($delimiter, $check_disabled_path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      if(isset($node)){
      $node = $node->getChild($part);
      if (isset($node) && $check_disabled_path === $computed_path) {
        $node->chkDisabled = true;
      }
    }
    }
  }
  return $tree;
}




/**
 * This method generates a ztree object containing all the data given in paths.
 * @param type $array_path the list of all paths we want in the tree
 * @param array $array_options an array of options that alters the paths :
 * <ul>
 * <li>selected_paths a list of pre-selected paths</li>
 * <li>disabled_paths a list of paths that need to be disabled</li>
 * <li>check_disabled_paths a list of paths that cannot be checked</li>
 * <li>obfuscated_paths a list of paths that need to be obfuscated</li>
 * <li>non_member_paths a list of paths the user is not member of</li>
 * <li>templates_paths a list of template paths</li>
 * </ul>
 * @param type $delimiter the delimiter of the paths (usually /)
 * @return boolean|ztree_tree false if no path array is set, tree otherwise.
 */
function gofast_ztree_array_path_to_nested_objects($array_path = array(), $array_options = array(), $delimiter = '/') {
  if (!is_array($array_path)) {
    return false;
  }

  // This is the declaration of the variables that are in $array_options
  $selected_paths;
  $disabled_paths;
  $check_disabled_paths;
  $obfuscated_paths;
  $non_member_paths;
  $templates_paths;
  $templates_folder_paths;

  extract($array_options);
  asort($array_path);

  $tree = new ztree_tree;
  // We proceed to user accessible paths
  foreach ($array_path as $gid => $path) {
      $gid2 = $gid;
    $is_non_member_paths = false;
    if (in_array($path, $non_member_paths)) {
      $is_non_member_paths = true;
    }
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    $og_space = node_load($gid);
    $index = -1;
    foreach ($parts as $part) {
      $index++;
      $computed_path .= '/' . $part;
      if (!$node->getChild($part)) {
        if($computed_path == '/' . $part ){ // for root node if not accessible to user
          $current_node = gofast_cmis_item_get_by_path('/Sites'.str_replace('/', '/_',$computed_path), TRUE);
          if ($gid == gofast_og_get_user_private_space()->nid){
              $current_node = gofast_og_get_user_private_space();
          }
          $gid2 = $current_node->properties['gofast:nid'];
          if ($gid == gofast_og_get_user_private_space()->nid){
              $gid2 = $current_node->nid;
          }
          $last_depth = $index === count($parts) - 1;
          $node->addChild($node = new ztree_node($part, $computed_path, $gid2, $last_depth));

        }else{
          $last_depth = $index === count($parts) - 1;
          if($last_depth == 1){
              $gid2 = $gid;
          }
          $node->addChild($node = new ztree_node($part, $computed_path, $gid2, $last_depth));
          if( isset($array_options['spaces_members']['display'])
            && $array_options['spaces_members']['display'] == TRUE
            && ! gofast_og_is_root_space($og_space))
          {
            //add user to the node
            gofast_ztree_add_node_members($node, $gid2, 'active', $array_options['spaces_members']);
          }
        }


        if ($index === 0) {
          $node->open = TRUE;
        }
        $node->update_icon();

        if(!array_search($computed_path, $array_path)){
             $node->nocheck = TRUE;
        }

      }
      else {
        $node = $node->getChild($part);
      }
      if ($path === $computed_path) {
        $node->non_member = $is_non_member_paths;
        $node->isHidden = $is_non_member_paths ? TRUE : FALSE;
      }
      if(gofast_og_is_root_space($og_space) && isset($array_options['root_spaces_selection']) && $array_options['root_spaces_selection'] == FALSE){
        $node->nocheck = TRUE;
      }
    }
  }
  foreach ($disabled_paths as $gid => $path) {
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      if ($node->getChild($part) != null){
          $node = $node->getChild($part);
          if (isset($node) && $path === $computed_path) {
            $node->open = TRUE;
            $node->nocheck = TRUE;
            if (isset($node->gid) && isset(node_load($node->gid)->nid) && !gofast_og_is_root_space(node_load($node->gid)) && og_user_access('node', $node->gid, 'create alfresco_item content')){
              if(gofast_group_is_archive(node_load($node->gid))){
                  $node->icon = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/folder-archive-primary.png';
              }else{
                  //$node->icon = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/ban.png';
              }
            }

          }
      }
    }
  }

  foreach ($selected_paths as $gid => $path) {
    $node = $tree;
    $computed_path = '';
    if (substr($path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($path, 1));
    }
    else {
      $parts = explode($delimiter, $path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      $node = $node->getChild($part);
      if (isset($node) && $path === $computed_path) {
        $node->open = TRUE;
        $node->checked = TRUE;
      }
    }
  }

  foreach ($check_disabled_paths as $gid => $check_disabled_path) {
    $node = $tree;
    $computed_path = '';
    if (substr($check_disabled_path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($check_disabled_path, 1));
    }
    else {
      $parts = explode($delimiter, $check_disabled_path);
    }
    foreach ($parts as $part) {
      $computed_path .= '/' . $part;
      $node = $node->getChild($part);
      if (isset($node) && $check_disabled_path === $computed_path) {
        $node->chkDisabled = true;
      }
    }
  }

  foreach ($templates_paths as $path_with_group_prefix => $templates_path) {
    $node = $tree;
    $computed_path = '';
    $path_with_group_prefix = str_replace("/Sites", "", $path_with_group_prefix);
    if (substr($templates_path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($templates_path, 1));
      $parts_with_group_prefix = explode($delimiter, substr($path_with_group_prefix, 1));
    }
    else {
      $parts = explode($delimiter, $templates_path);
      $parts_with_group_prefix = explode($delimiter, $path_with_group_prefix);
    }

    foreach ($parts as $index => $part) {
      $computed_path .= '/' . $part;
      $node = $node->getChild($part);
      $node->crumb = $parts_with_group_prefix[$index];
      $node->nocheck = TRUE;
      $node->open = TRUE;
      if (isset($node) && $templates_path === $computed_path) {
        $node->is_template = TRUE;
        $node->nocheck = FALSE;
      }
      $node->update_icon_template();
    }
  }

  foreach ($templates_folder_paths as $gid => $template_folder_path) {
    $node = $tree;
    $computed_path = '';
    if (substr($template_folder_path, 0, 1) === '/') {
      $parts = explode($delimiter, substr($template_folder_path, 1));
    }
    else {
      $parts = explode($delimiter, $template_folder_path);
    }
    foreach ($parts as $key => $part) {

      ## we can only check when the actual node if it's a folder template
      if ($key < 2){
          $computed_path .= '/' . $part;
          $node = $node->getChild($part);
          if($node->is_template != 1){
              $node->nocheck = TRUE;
              $node->open = TRUE;
          }
          if (isset($node) && $template_folder_path === $computed_path) {
            $node->is_template = TRUE;
            $node->nocheck = FALSE;
          }
      }else{
          $computed_path .= '/' . $part;
          $node = $node->getChild($part);
          $node->nocheck = TRUE;
      }
    }
  }
  return $tree;
}

/**
 *
 * @param type $node
 * @param type $gid
 * @param type $state
 */
function gofast_ztree_add_node_members(&$node, $gid, $state=NULL, $options=array()){

  $group_entity = node_load($gid, null, TRUE);
  $members_uid = gofast_og_get_members($group_entity, $state);

  $query = db_select('users', 'u');
  $query->fields('u', array('uid','name'));
  $query->join('field_data_ldap_user_givenname', 'a', 'a.entity_id = u.uid');
  $query->join('field_data_ldap_user_sn', 'b', 'b.entity_id = u.uid');
  $query->fields('a', array('ldap_user_givenname_value'));
  $query->fields('b', array('ldap_user_sn_value'));
//  $query->condition('u.name', 'adm', '<>');
  $query->condition('u.status', 1);
  $query->condition('u.uid', $members_uid, 'IN');
  $query->orderBy('b.ldap_user_sn_value', 'ASC');

  $results = $query->execute();

  if ($results->rowCount() > 0) {

      $ztree_node_member = new ztree_node(t('Members', array(), array('context' => 'gofast')), '', $gid.'_all', 0);
      $ztree_node_member->icon = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon/users-members-primary.png';
      if ($options['chkDisabled'] == TRUE) {
        $ztree_node_member->chkDisabled = TRUE;
        $ztree_node_member->nocheck = TRUE;
      }
      $ztree_node_member->isParent = TRUE;

      $members_roles = array();
    if (isset($options['displayUserRole']) && $options['displayUserRole'] == TRUE) {
      $members_roles = gofast_og_get_users_roles('node', $gid, $members_uid);
    }

    while ($curr_member = $results->fetchObject()) {
      $curr_member_fullname = strtoupper($curr_member->ldap_user_sn_value).' '.$curr_member->ldap_user_givenname_value;

      if (isset($options['displayUserRole']) && $options['displayUserRole'] == TRUE) {
        $roles = $members_roles[$curr_member->uid]->name ;
        $curr_member_fullname.= ' - ' . t($roles, array(), array('context' => 'gofast')) . '';

      }

      //add new ztree_node to node !
      $ztree_node = new ztree_node($curr_member_fullname, '', $curr_member->uid, 0);
      $ztree_node->icon = gofast_ztree_get_node_icon('user');

      if ($options['chkDisabled'] == TRUE) {
        $ztree_node->chkDisabled = TRUE;
        $ztree_node->nocheck = TRUE;
      }
      $ztree_node->isParent = FALSE;

      if ($curr_member->uid > 1 /*&& $curr_member->name != 'adm' && $curr_member->status != 0 */) { //hide adm + locked users
        $ztree_node_member->addChild($ztree_node);
      }
    }
    $node->addChild($ztree_node_member);

  }
}

/**
 * This method returns a path for a given type.
 * @param type $type
 * @return string
 */
function gofast_ztree_get_node_icon($type) {

  $icon_home = '/'.drupal_get_path('module', 'gofast_mail_queue').'/icon';

  switch ($type) {
    case 'root':
      return '/sites/default/files/icons/parallel_tasks-16-primary.png';
    case 'Private_space':
      return $icon_home.'/home-primary.png';
    case 'Groups':
      return $icon_home.'/users-primary.png';
    case 'Organisations':
      return $icon_home.'/sitemap-primary.png';
    case 'Extranet':
      return $icon_home.'/globe-primary.png';
    case 'Public':
      return $icon_home.'/share-primary.png';
    case 'folder':
      return  $icon_home.'/folder-primary.png';
    case 'mirror':
      return  $icon_home.'/folders-primary.svg';
    case 'user' :
      return  $icon_home.'/user-primary.png';
    default:
      return $icon_home.'/other-primary.png';
  }
}

/**
 * This function returns the form field for a given form_id
 * @return type
 */
function gofast_ztree_get_eligible_forms() {
  return array(
    'node_delete_confirm' => 'target',
    'alfresco_item_node_form' => GOFAST_OG_CONTENT_MEMBERSHIP_FIELD,
    'forum_node_form' => GOFAST_OG_CONTENT_MEMBERSHIP_FIELD,
    'webform_node_form' => GOFAST_OG_CONTENT_MEMBERSHIP_FIELD,
    'group_node_form' => GOFAST_OG_PARENT_GROUP_FIELD,
    'organisation_node_form' => GOFAST_OG_PARENT_GROUP_FIELD,
    'public_node_form' => GOFAST_OG_PARENT_GROUP_FIELD,
    'extranet_node_form' => GOFAST_OG_PARENT_GROUP_FIELD,
    'user_register_form' => GOFAST_OG_USER_MEMBERSHIP_FIELD,
    'user_profile_form' => GOFAST_OG_USER_MEMBERSHIP_FIELD,
    'gofast_cmis_node_publish_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'gofast_taxonomy_add_locations_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'gofast_taxonomy_manage_folder_locations_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'gofast_taxonomy_manage_locations_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'gofast_cmis_manage_publications_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'gofast_dashboard_add_folder_form' => GOFAST_CMIS_LOCATIONS_FIELD,
    'conference_node_form' => array(
        "fieldset" => "folders",
        "field" => GOFAST_CMIS_LOCATIONS_FIELD
    ),
    'gofast_og_space_admin_add_members_form' => 'spaces',
    'gofast_og_space_admin_edit_members_form' => 'spaces',
    'gofast_chat_join_space_room_form' => 'spaces',
    'gofast_dashboard_add_space_shortcut_form' => 'spaces',
    'gofast_og_move_space_form' => GOFAST_OG_PARENT_GROUP_FIELD,
    'gofast_stats_list_docs_form' => GOFAST_CMIS_LOCATIONS_FIELD,
  );
}

/**
 * Implements hook_form_alter
 */
function gofast_ztree_form_alter(&$form, &$form_state) {
  $form_id = $form_state['build_info']['form_id'];

  if (!$form_state['programmed'] && in_array($form_id, array_keys(gofast_ztree_get_eligible_forms()))) {
    $field_name = gofast_ztree_get_eligible_forms()[$form_id];

    // We add a custom key to get the field in the form_after_build
    $form_state['ztree_field'] = array(
      '#type' => 'hidden',
      '#value' => $field_name
    );

    // Do show ztree on delete_confirm_form only if node is space
    if ($form_id === "node_delete_confirm" && !gofast_og_is_space($form['#node'])) {
      return;
    }

    // GOFAST-10137 - Do not show ztree on node edit form if metadata is being edited
    if($form_state['edit_metadata']){
      return;
    }

    $form['#after_build'][] = 'gofast_ztree_after_build';
  }
}

/**
 * Form after-build callback.
 */
function gofast_ztree_after_build($form, &$form_state) {

  $ztree_field = (string) $form_state['ztree_field']['#value'];
  $form_field = $form[$ztree_field];
  $form_id = $form_state['build_info']['form_id'];
  $node = $form_state['node'];

  if($form_id === 'gofast_taxonomy_add_locations_form' ||  $form_id === 'gofast_taxonomy_manage_locations_form' || $form_id === "gofast_taxonomy_manage_folder_locations_form" || $form_id === 'gofast_dashboard_add_folder_form' || $form_id === 'gofast_stats_list_docs_form'){
      $ztree_field = GOFAST_CMIS_LOCATIONS_FIELD;
      $form_field = $form[GOFAST_CMIS_LOCATIONS_FIELD];
      $nids = "";
      foreach($form_state["selected_nodes_ids"] as $key=>$nid){
        $nids .= $nid." ";
      }
  }

  if($form_id === 'gofast_cmis_manage_publications_form'){
      $ztree_field = GOFAST_CMIS_LOCATIONS_FIELD;
      $form_field = $form[GOFAST_CMIS_LOCATIONS_FIELD];
      $nids = "";
      foreach($form_state["selected_nodes_ids"] as $key=>$nid){
        $nids .= $nid." ";
      }
  }

  if($form_id === 'conference_node_form'){
      $ztree_field = GOFAST_CMIS_LOCATIONS_FIELD;
      $form_field = $form['folders'][GOFAST_CMIS_LOCATIONS_FIELD];
      $form[GOFAST_CMIS_LOCATIONS_FIELD] =  &$form['folders'][GOFAST_CMIS_LOCATIONS_FIELD];
  }

  $paths = array();
  $selected = array();
  $selected_paths = array();
  $disabled_paths = array();
  $ztree_options = array();
  $paths_options = array();

  switch ($ztree_field) {
    case GOFAST_OG_USER_MEMBERSHIP_FIELD:
      $type = 'user';
      break;
    case GOFAST_OG_CONTENT_MEMBERSHIP_FIELD:
      $type = 'content';
      $ztree_options = array("widget_locations" => "true");
      if ($form_id === 'alfresco_item_node_form' /*|| $form_id === 'article_node_form'*/) {
        $ztree_options += array("alfresco_document" => "true", "chkStyle" => "checkbox");
      }
      break;
    case GOFAST_OG_PARENT_GROUP_FIELD:
      $type = 'space';
      $ztree_options = array("chkStyle" => "radio", "radioType" => "all");
      break;
    case 'target':
      $type = 'custom';
      $ztree_options = array("chkStyle" => "radio", "radioType" => "all");
      break;
    case GOFAST_CMIS_LOCATIONS_FIELD:
      $type = 'locations';
      $ztree_options = array("widget_locations" => "true");
      if(isset($nids)){
        $ztree_options["form"]['id'] = $nids;
      }
      if ($form_id === 'gofast_dashboard_add_folder_form') {
        $ztree_options["disable_mirror_check"] = "true";
      }
      break;
    case 'spaces':
      if($form_id == 'gofast_og_space_admin_add_members_form'){
        $type = 'custom_space';
      }else if($form_id =='gofast_og_space_admin_edit_members_form'){
        $type = 'custom_space_member';
      }

      if($form_id == "gofast_chat_join_space_room_form"){
          $type = 'custom_space_chat';
          $ztree_options = array("chkStyle" => "radio", "radioType" => "all");
      }
      if($form_id == "gofast_dashboard_add_space_shortcut_form"){
          $type = 'custom_space_all';
          $ztree_options = array("widget_locations" => "true");
      }
        break;
    default:
      break;
  }

  if (isset($form['#ztree_options'])) {
    $ztree_options += $form['#ztree_options'];
  }

  if (in_array($type, array('user', 'content', 'locations'))) {
    if (in_array($form_id, array('alfresco_item_node_form'))) {
      $field = $form[GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE];
      if (isset($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]) && count($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD][LANGUAGE_NONE]) > 0) {
        $selected = array_map(function($element) use($field) {
          if (intval($element) !== 0) {
            return $field['#options'][$element];
          }
          else {
            return $element;
          }
        }, $field['#value']);
      }
      else {
        $selected = $field['#default_value'];
      }
      $paths = $field['#options'];
    }
    else if ($form_id === 'gofast_taxonomy_manage_locations_form' || $form_id === "gofast_taxonomy_manage_folder_locations_form" || $form_id === 'gofast_cmis_node_publish_form' || $form_id === 'gofast_taxonomy_add_locations_form' || $form_id === 'gofast_taxonomy_manage_folder_locations_form' || $form_id == 'gofast_cmis_manage_publications_form' || $form_id == 'gofast_dashboard_add_folder_form' || $form_id == "gofast_stats_list_docs_form" || $form_id === "conference_node_form") {
      $field = $form[GOFAST_CMIS_LOCATIONS_FIELD];
      if (isset($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD]) && count($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD]) > 0) {
        foreach ($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD] as $selected_location) {
          $array_id = array_search($selected_location, $field['#options']);
          $selected[$selected_location] = $array_id;
        }
      }
      else {
        $selected = array_map(function($element) {
          return $element['value'];
        }, (array) $field['#default_value']);
      }
      $paths = $field['#options'];
    }
    elseif($form_id === 'forum_node_form' || $form_id === 'article_node_form'){


      $field = $form_field[LANGUAGE_NONE];
      if(isset($form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default']) || isset($form_field[LANGUAGE_NONE][0]['default']['#default_value'])){
        if (count((array) $form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default']) > 0) {
          $selected = $form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default'];
        }
        else {
          $selected = $form_field[LANGUAGE_NONE][0]['default']['#default_value'];
        }
       foreach ($form_field[LANGUAGE_NONE][0]['default']['#options'] as $bundle) {
         if (is_array($bundle)) {
           $paths += $bundle;
         }
         $paths += gofast_ztree_get_drupal_path_from_webdav_path(array_map(function($element) {
                   return gofast_cmis_space_get_webdav_path($element);
                 }, gofast_og_get_root_spaces(FALSE, TRUE)));
       }
      }
    }
    else {
      // user form
      //remove "public" spaces
      $form_field[LANGUAGE_NONE][0]["default"]["#options"]["Public"] = array();

      $field = $form_field[LANGUAGE_NONE];
      if(isset($form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default']) || isset($form_field[LANGUAGE_NONE][0]['default']['#default_value'])){
        if (count($form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default']) > 0) {
          $selected = $form_state['values'][$ztree_field][LANGUAGE_NONE][0]['default'];
        }
        else {
          $selected = $form_field[LANGUAGE_NONE][0]['default']['#default_value'];
        }
       foreach ($form_field[LANGUAGE_NONE][0]['default']['#options'] as $bundle) {
         if (is_array($bundle)) {
           $paths += $bundle;
         }
         $paths += gofast_ztree_get_drupal_path_from_webdav_path(array_map(function($element) {
                   return gofast_cmis_space_get_webdav_path($element);
                 }, gofast_og_get_root_spaces(FALSE, TRUE)));
       }
      }
    }

    $paths_options['non_member_paths'] = isset($field['#options-not-member']) ? $field['#options-not-member'] : array();
    $paths_options['disabled_paths'] = isset($field['#options_disabled']) ? $field['#options_disabled'] : array();
    $paths_options['check_disabled_paths'] = isset($field['#options_check_disabled']) ? $field['#options_check_disabled'] : array();

    $paths = !is_array($paths) ? array() : $paths;
    $selected = !is_array($selected) ? array() : $selected;
    asort($paths);
    asort($selected);

    foreach ($paths as $key => $value) {
      if (intval($key) !== 0) {
        $current_node = node_load($key);
        //Disable root spaces
        if (!isset($form['root_space_selection']) && gofast_og_is_root_space($current_node) && !gofast_og_is_user_private_space($current_node)) {
          $disabled_paths[$key] = $value;
          continue;
        }
        if (og_user_access('node', $key, 'create alfresco_item content') == 0){
          $disabled_paths[$key] = $value;
        }
      }
      if ($form_id === 'article_node_form' || $form_id === 'alfresco_item_node_form' || $form_id === 'gofast_taxonomy_add_locations_form' || $form_id === 'gofast_taxonomy_manage_locations_form' || $form_id === "gofast_taxonomy_manage_folder_locations_form" || $form_id === 'gofast_dashboard_add_folder_form' || $form_id === "conference_node_form" || $form_id == "gofast_stats_list_docs_form") {
        if (in_array($value, $selected)) {
          unset($selected[array_search($key, $selected)]);
          $nid_selected_options = $node->og_group_content_ref['und'][$key]['target_id'];
          if (isset($nid_selected_options) && og_user_access('node', $nid_selected_options, 'create alfresco_item content') == 1){
            $selected_paths[$key] = $value;
          }else{
            unset($selected_options[$key]);
          }
          $selected_paths[$key] = $value;
        }
      }
      else {
        if (in_array($key, $selected)) {
          unset($selected[array_search($key, $selected)]);
          $nid_selected_options = $node->og_group_content_ref['und'][$key]['target_id'];
          if (isset($nid_selected_options) && og_user_access('node', $nid_selected_options, 'create alfresco_item content') == 1){
            $selected_paths[$key] = $value;
          }else{
            unset($selected_options[$key]);
          }
          $selected_paths[$key] = $value;
          if (isset($form_field['#disable_selected']) && $form_field['#disable_selected']) {
            $paths_options['check_disabled_paths'][$key] = $value;
          }
        }
      }
    }

    foreach ($selected_paths as $selected_id => $path) {
      if (is_int($selected_id) && !node_access('view', node_load($selected_id))) {
        $paths_options['check_disabled_paths'][$selected_id] = $path;
      }
    }
  }
  else if ($type === 'custom' || $type === 'custom_space' || $type === 'custom_space_member' || $type === "custom_space_chat" || $type === "custom_space_all") {
    $paths = $form_field['#options'];
    $selected_paths = array_slice($paths, 0, 1, TRUE);
    if($form_id  == 'gofast_og_space_admin_add_members_form'){
       $paths_options['root_spaces_selection'] = FALSE;
       $paths_options['spaces_members']['display'] = TRUE;
       $paths_options['spaces_members']['chkDisabled'] = TRUE;
       $selected_paths = array();
    }
    else if($form_id == 'gofast_og_space_admin_edit_members_form'){
       $paths_options['root_spaces_selection'] = FALSE;
       $paths_options['spaces_members']['display'] = TRUE;
       $paths_options['spaces_members']['chkDisabled'] = FALSE;
       $paths_options['spaces_members']['displayUserRole'] = TRUE;
       $selected_paths = array();
    }else if ($form_id == "gofast_chat_join_space_room_form"){
       $paths_options['root_spaces_selection'] = FALSE;
       $paths_options['spaces_members']['display'] = FALSE;
       $paths_options['spaces_members']['chkDisabled'] = FALSE;
       $paths_options['spaces_members']['displayUserRole'] = FALSE;
       $selected_paths = array();
    }else if ($form_id == "gofast_dashboard_add_space_shortcut_form"){
       $paths_options['root_spaces_selection'] = FALSE;
       $paths_options['spaces_members']['display'] = FALSE;
       $paths_options['spaces_members']['chkDisabled'] = FALSE;
       $paths_options['spaces_members']['displayUserRole'] = FALSE;
       $selected_paths = array();
    }
  }
  else {
    $node = $form_state['node'];
    $space_types = gofast_og_node_types();
    $space_type = $node->type;

    // Prevent issue if we do not have any spaces available (like admin user)
      //if(count($form_field[LANGUAGE_NONE][0]['default']["#default_value"]) == 0){
        //we check if the default value is a root space
          if($node->og_group_ref[LANGUAGE_NONE][0]["target_id"]){
              $root_node = node_load($node->og_group_ref[LANGUAGE_NONE][0]["target_id"]);
              $form_field[LANGUAGE_NONE][0]['default']["#options"][$space_types[$space_type]][$root_node->nid] = $root_node->title;
              $form_field[LANGUAGE_NONE][0]['default']["#default_value"] = $root_node->nid;
              $form[$ztree_field][LANGUAGE_NONE][0]['default']["#options"][$space_types[$space_type]][$root_node->nid] = $root_node->title;
              $form[$ztree_field][LANGUAGE_NONE][0]['default']["#default_value"] = $root_node->nid;
          }
     // }

    if (count((array) $form_field[LANGUAGE_NONE][0]['default']['#options']) > 0) {
      $paths = (array) isset($form_field[LANGUAGE_NONE][0]['default']['#options'][$space_types[$space_type]]) ? $form_field[LANGUAGE_NONE][0]['default']['#options'][$space_types[$space_type]] : array();
      if (count($paths) > 0) {
        $first_option = array_slice($paths, 0, 1, TRUE);
        $selected = !empty($form_field[LANGUAGE_NONE][0]['default']['#default_value']) ? $form_field[LANGUAGE_NONE][0]['default']['#default_value'] : array_flip($first_option);
        if(!is_array($form_field[LANGUAGE_NONE][0]['default']['#default_value'])){
            $selected = array();
            $selected[] = $form_field[LANGUAGE_NONE][0]['default']['#default_value'];
        }
        foreach ($paths as $gid => $space) {
          if (isset($form['root_space_selection']) && gofast_og_is_root_space($space)) {
            $disabled_paths[$gid] = $space;
            continue;
          }

          //we check if we are adminisrator of this entity
          global $user;
          $roles = gofast_og_get_user_final_roles_for_space('node', $gid, $user->uid);
          $role = reset($roles);

          //Retrieve saved spaces configuration, override permissions for 1st level spaces in GOFAST-5605
          $spaces_defaults = gofast_admin_get_space_defaults();
          $first_level_spaces = array();

          if($spaces_defaults['create_sub_space']){
            $first_level_spaces = array_merge(
                    gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_GROUPS_GID, FALSE, FALSE, TRUE),
                    gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_EXTRANET_GID, FALSE, FALSE, TRUE)
            );
          }
          if($role !== OG_ADMINISTRATOR_ROLE  && $gid != $form_field[LANGUAGE_NONE][0]['default']["#default_value"] && !in_array($gid, $first_level_spaces)){
            $disabled_paths[$gid] = $space;
            continue;
          }
            //we also have to check if the ancestors must be disabled or not
            $group = node_load($gid);
            $ancestors = gofast_og_get_ancestors($group, FALSE, TRUE);
            if(count($ancestors) > 0){
                 foreach($ancestors as $grid => $mygroup){
                   if(is_numeric($grid)){
                      $roles = gofast_og_get_user_final_roles_for_space('node', $grid, $user->uid);
                      $role = reset($roles);
                      if($role !== OG_ADMINISTRATOR_ROLE && !in_array($grid, $first_level_spaces)){
                        $disabled_paths[$grid] = $space;
                        continue;
                      }
                   }
                }
            }

          if (in_array($gid, $selected)) {
            unset($selected[array_search($gid, $selected)]);
            $selected_paths[$gid] = $space;
          }
        }
      }
    }

  }

  $paths_options['selected_paths'] = $selected_paths;
  $paths_options['disabled_paths'] = $disabled_paths;
  global $user;
  $request_field_archived = db_query("SELECT * FROM {field_data_field_archive} where field_archive_value = 1");
  $fields_archived = $request_field_archived->fetchAll();
  if ($form_id === 'alfresco_item_node_form' || $form_id === 'gofast_taxonomy_add_locations_form' || $form_id === 'gofast_taxonomy_manage_locations_form' || $form_id === "gofast_taxonomy_manage_folder_locations_form" || $form_id === 'gofast_og_space_admin_add_members_form' || $form_id === 'gofast_og_space_admin_edit_members_form'
           || $form_id == "gofast_chat_join_space_room_form"
           || $form_id == "gofast_dashboard_add_space_shortcut_form") {
           $ztree_block = gofast_ztree_block_content($type, $paths, $ztree_options, $paths_options, true);
       }else if($form_id == "gofast_dashboard_add_folder_form" || $form_id === "conference_node_form" || $form_id == "gofast_stats_list_docs_form"){
           $paths_options['disable_space_check'] = true;
           $ztree_block = gofast_ztree_block_content($type, $paths, $ztree_options, $paths_options, true);
       }else{
           foreach($fields_archived as $field_archived ){
              $isMember = (og_get_membership('node',$field_archived->entity_id,'user',$user->uid) != FALSE );
              //check membership from userlist
              $isMember_from_userlist =  gofast_userlist_og_is_user_member_of_space($field_archived->entity_id, $user);
              if ($isMember || $isMember_from_userlist) {
                $roles = gofast_og_get_user_final_roles_for_space('node', $field_archived->entity_id, $user->uid);
              }


              $isPending = (!isset($roles)) || empty($roles) && ( $isMember || $isMember_from_userlist);
              if (!$isPending && ($isMember || $isMember_from_userlist) ){
                  $paths_options['disabled_paths'][$field_archived->entity_id] = gofast_cmis_space_get_drupal_path($field_archived->entity_id);
              }
           }
         $ztree_block = gofast_ztree_block_content($type, $paths, $ztree_options, $paths_options, false);
   }


  // print_r("<pre>");print_r($ztree_block);exit;
   /*if(!is_array($form_field[LANGUAGE_NONE][0]['default']['#default_value'])){
        unset($ztree_block["disabled_paths"][$form_field[LANGUAGE_NONE][0]['default']['#default_value']]);
   }*/
  // We unset ztree variables so we can render the ztree without errors
  unset($ztree_block['user_visible_paths']);
  unset($ztree_block['pre_selected_paths']);
  unset($ztree_block['disabled_paths']);
  unset($ztree_block['obfuscated_paths']);

  if ($type === 'custom' || $type === 'custom_space' || $type === 'custom_space_member' || $type === "custom_space_chat" || $type === "custom_space_all") {
    $form[$ztree_field]['#field_suffix'] = drupal_render($ztree_block);
    $form[$ztree_field]["#attributes"]["class"][] = "gofast_display_none";
  }
  else if ($type === 'locations') {
    $form[$ztree_field]['#suffix'] = drupal_render($ztree_block);
  }
  else {
    $form[$ztree_field][LANGUAGE_NONE][0]['default']['#field_suffix'] = drupal_render($ztree_block);
    $form[$ztree_field][LANGUAGE_NONE][0]['default']["#attributes"]["class"][] = "gofast_display_none";
  }

  if($form_id === 'conference_node_form'){
      unset($form[GOFAST_CMIS_LOCATIONS_FIELD]);
  }

  return $form;
}

/*
 * Build the templates ztree async
 */
function gofast_ztree_templates_build_async(){
  $arr_values_combine = json_decode($_POST['arr_values_combine'], TRUE);
  $ztree_options = json_decode($_POST['ztree_options'], TRUE);
  $paths_options = json_decode($_POST['paths_options'], TRUE);

  if(!empty($paths_options['templates_folder_paths'])){
  $ztree_block = gofast_ztree_block_content('content_templates_folders', $arr_values_combine, $ztree_options, $paths_options, false);
    print "<script>Drupal.settings['ztree_component_content_templates_folders'] = {"
    . "async: false,"
    . "data_tree: '" . str_replace("'", "\'", $ztree_block['content']['#attached']['js'][1]['data']['ztree_component_content_templates_folders']['data_tree']) . "',"
    . "ztree_options: {alfresco_document: true, allow_uncheck: true, radioType: 'all'},"
    . "}</script>";
  }else{
      $ztree_block = gofast_ztree_block_content('content_templates', $arr_values_combine, $ztree_options, $paths_options, false);
      print "<script>Drupal.settings['ztree_component_content_templates'] = {"
      . "async: false,"
      . "data_tree: '" . str_replace("'", "\'", $ztree_block['content']['#attached']['js'][1]['data']['ztree_component_content_templates']['data_tree']) . "',"
      . "ztree_options: {alfresco_document: true, allow_uncheck: true, chkStyle: 'radio', radioType: 'all'},"
      . "}</script>";
  }

  // We unset ztree variables so we can render the ztree without errors
  unset($ztree_block['user_visible_paths']);
  unset($ztree_block['pre_selected_paths']);
  unset($ztree_block['disabled_paths']);
  unset($ztree_block['obfuscated_paths']);
  unset($ztree_block['templates_paths']);

  $render = drupal_render($ztree_block);
  print $render;
  exit;
}


function gofast_ztree_templates_after_build($form, &$form_state) {
  $ztree_field = 'templates';
  if (array_key_exists($ztree_field, $form)) {
    $form_field = $form[$ztree_field];
    $form_id = $form_state['build_info']['form_id'];

    $options = array();
    $selected = array();
    $selected_options = array();
    $ztree_options = array(
      "alfresco_document" => true,
      "chkStyle" => "radio",
      "radioType" => "all",
      'allow_uncheck' => true
    );
    if ($form_state['values'][$ztree_field] !== 0 && $form_state['values'][$ztree_field] !== '') {
      $selected = array($form_state['values'][$ztree_field]);
    }
    else {
      $selected = array($form_field['#default_value']);
    }
    $options = $form_field['#options'];

    $options = !is_array($options) ? array() : $options;
    $selected = !is_array($selected) ? array() : $selected;
    asort($options);
    asort($selected);

    foreach ($options as $key => $value) {
      if (in_array($key, $selected)) {
        unset($selected[array_search($key, $selected)]);
        $selected_options[$key] = $value;
      }
    }

    $values = array_values($options);
    $arr_values_combine = array_combine($values, $values);
    $paths_options = array(
      'selected_paths' => $selected_options,
      'templates_paths' => $arr_values_combine
    );



    //Ajaxified for performances reasons
    //$ztree_block = gofast_ztree_block_content('content_templates', $arr_values_combine, $ztree_options, $paths_options, false);

    $form['ztree_templates']['#markup'] = "<div id='async_ztree_templates'>";
    $form['ztree_templates']['#markup'] .= "<span id='selected_item' class='gofast_display_none'>" . $form['templates']['#default_value'] . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='arr_values_combine' class='gofast_display_none'>" . json_encode($arr_values_combine) . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='ztree_options' class='gofast_display_none'>" . json_encode($ztree_options) . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='paths_options' class='gofast_display_none'>" . json_encode($paths_options) . "</span>";
    $form['ztree_templates']['#markup'] .= "<div class='loader-templates'></div>";
    $form['ztree_templates']['#markup'] .= "</div>";
  }

  return $form;
}

/**
 * Create ztree emplacement to create asynchronous ztree
 * @param type $form
 * @param type $form_state
 * @return the form after build
 */
function gofast_ztree_folders_templates_after_build($form, &$form_state) {
  $ztree_field = 'templates';
  if (array_key_exists($ztree_field, $form)) {
    $form_field = $form[$ztree_field];
    $form_id = $form_state['build_info']['form_id'];

    $options = array();
    $selected = array();
    $selected_options = array();
    $ztree_options = array(
      "widget_locations" => true,
      "alfresco_document" => true,
      'allow_uncheck' => true
    );
    if ($form_state['values'][$ztree_field] !== 0 && $form_state['values'][$ztree_field] !== '') {
      $selected = array($form_state['values'][$ztree_field]);
    }
    else {
      $selected = array($form_field['#default_value']);
    }
    $options = $form_field['#options'];

    $options = !is_array($options) ? array() : $options;
    $selected = !is_array($selected) ? array() : $selected;
    asort($options);
    asort($selected);

    foreach ($options as $key => $value) {
      if (in_array($key, $selected)) {
        unset($selected[array_search($key, $selected)]);
        $selected_options[$key] = $value;
      }
    }

    $values = array_values($options);
    $arr_values_combine = array_combine($values, $values);
    $paths_options = array(
      'selected_paths' => $selected_options,
      'templates_folder_paths' => $arr_values_combine,
    );

    //Ajaxified for performances reasons
    //$ztree_block = gofast_ztree_block_content('content_templates', $arr_values_combine, $ztree_options, $paths_options, false);

    $form['ztree_templates']['#markup'] = "<div id='async_ztree_templates_folder'>";
    $form['ztree_templates']['#markup'] .= "<span id='selected_item' class='gofast_display_none'>" . $form['templates']['#default_value'] . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='arr_values_combine' class='gofast_display_none'>" . json_encode($arr_values_combine) . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='ztree_options' class='gofast_display_none'>" . json_encode($ztree_options) . "</span>";
    $form['ztree_templates']['#markup'] .= "<span id='paths_options' class='gofast_display_none'>" . json_encode($paths_options) . "</span>";
    $form['ztree_templates']['#markup'] .= "<div class='loader-templates'></div>";
    $form['ztree_templates']['#markup'] .= "</div>";
  }

  return $form;
}

/**
 *
 * @return type
 */
function gofast_ztree_async_json($print = true){
  if (isset($_REQUEST["node"])) {
    $array_node = explode(" ", trim($_REQUEST["node"]));
    $node = node_load($array_node[0]);
  }
  else {
    global $user;
    if(variable_get("ithit_bulk_async_".$user->uid, NULL)){
        $array_node = variable_get("ithit_bulk_async_".$user->uid, NULL);
        if(is_array($array_node)){
            $array_node = array_keys($array_node);
            $node = node_load($array_node[0]);
            $_POST["node"] = $array_node[0];
        }else{
            $node = node_load($array_node);
            $_POST["node"] = $array_node;
        }
    }else{
        $node = new stdClass();
        //TODO Conditionning to swap to article node type
        $node->type = "alfresco_item";
        $node->nid = NULL;
    }
  }
  if (!isset($_REQUEST["ename"])) {
    $origine = null;
  }
  else {
    $origine = $_REQUEST["ename"];
  }

  if (isset($_REQUEST["template"])) {
    $template = true;
  }
  else {
    $template = false;
  }

  if (isset($_REQUEST["members"])) {
    $members = true;
  }
  else {
    $members = false;
  }

  if ($_REQUEST["notmanaged"]) {
    $notmanaged = true;
  }

  if ($_REQUEST["disable_space_check"]) {
    $disable_space_check = true;
  }

  if (isset($_REQUEST["publication"])) {
    $ispublication = true;
  }
  else {
    $ispublication = false;
  }
  if (!isset($_REQUEST["browser_path"])) {
    $browser_path = null;
  }
  else {
    $browser_path = $_REQUEST["browser_path"];
  }

  $is_internal = $_REQUEST["is_internal"] ? TRUE : FALSE;
  $is_confidential = $_REQUEST["is_confidential"] ? TRUE : FALSE;

  if (count((array) $array_node) > 1) {

    $path_options = gofast_get_node_locations_async($node, $origine, $template,null,$ispublication);
    foreach ($array_node as $nid) {
      $mynode = node_load($nid);
      $path_options_temp = gofast_get_node_locations_async($mynode, $origine, $template,null,$ispublication);
      $path_options["all_paths"] = $path_options_temp["all_paths"] + $path_options["all_paths"];
      $path_options["selected_paths"] = $path_options_temp["selected_paths"] + $path_options["selected_paths"];
      $path_options["check_disabled_paths"] = $path_options_temp["check_disabled_paths"] + $path_options["check_disabled_paths"];
      $path_options["disabled_paths"] = $path_options_temp["disabled_paths"] + $path_options["disabled_paths"];

      if($members == true){
        $path_options['spaces_members']['display'] = TRUE;
        $path_options['spaces_members']['chkDisabled'] = FALSE;
        if (isset($_REQUEST["chkDisabled"]) && $_REQUEST["chkDisabled"] == 1 ) {
          $path_options['spaces_members']['chkDisabled'] = TRUE;
        }
        $path_options['spaces_members']['displayUserRole'] = TRUE;
      }
    }
  }
  else {
    if ($members == true) {

      $path_options = gofast_get_node_locations_members_async($node, $origine, $notmanaged);
      $path_options['spaces_members']['display'] = TRUE;
      $path_options['spaces_members']['chkDisabled'] = FALSE;
      if (isset($_REQUEST["chkDisabled"]) && $_REQUEST["chkDisabled"] == 1) {
          $path_options['spaces_members']['chkDisabled'] = TRUE;
        }
        $path_options['spaces_members']['displayUserRole'] = TRUE;
    }else{
        if(is_object($node) && $node->type === "conference"){
          
          unset($path_options["selected_paths"]);
          foreach($node->field_linked_folders[LANGUAGE_NONE] as $selected_folder){
            $path_options['selected_paths'][$selected_folder['value']] = $selected_folder['value'];
          }
            $path_options = gofast_get_node_locations_async($node, $origine, $template , $browser_path, $ispublication, $node->field_linked_folders[LANGUAGE_NONE]);
        }else{
            
            $path_options = gofast_get_node_locations_async($node, $origine, $template, $browser_path, $ispublication, NULL, $is_confidential, $is_internal);
        }
    }
  }

  if($notmanaged){
      $path_options['not_managed'] = true;
  }

  if($disable_space_check){
      $path_options['disable_space_check'] = true;
  }

  //$path_options['selected_paths'] = gofast_ztree_get_drupal_path_from_webdav_path($path_options['selected_paths']);
  $all_paths = $path_options['all_paths'];

  $array_paths = gofast_ztree_normalize_list($all_paths);
  $selected_and_selectable_og = $all_paths;
  if (!$origine) {
    foreach ($path_options['selected_paths'] as $key => $selected_location) {
        if (!in_array(html_entity_decode($selected_location), $array_paths)) {
          $gid = $key;
        }
        $path_options['selected_paths'][$key] = $selected_location;
        $selected_and_selectable_og[$gid !== FALSE ? $gid : count($selected_and_selectable_og) + 1] = html_entity_decode($selected_location);
    }
  }

  // If there is no data, return empty array
  if (empty($array_paths) && empty($path_options['selected_paths']) && empty($path_options['disabled_paths']) && empty($path_options['obfuscated_paths']) && empty($path_options['templates_paths'])) {
    return $content;
  }

  // Then, we prepare the Json to be used by the ztree component
  if(count($path_options["selected_paths"]) > 0){
      foreach($path_options["selected_paths"] as $key=>$path){
          // /Sites is auto selected on creation, remove it from paths if selected at any moment to avoid unwanted locations
          if($path === "/Sites") {
              unset($path_options["selected_paths"][array_search($path, $path_options["selected_paths"])]);
              continue;
          }
          $decoded_path = html_entity_decode($path);
          if($decoded_path != $path){
              unset($path_options["selected_paths"][$key]);
              $path_options["selected_paths"][html_entity_decode($key)] = html_entity_decode($path);
          }

      }
  }

  //GOFAST-4667 Add the browser path to the selected path if we come from the browser
  if (isset($browser_path)){
     $path_options["selected_paths"][$browser_path] = $browser_path;
  }
  global $user;
  $request_field_archived = db_query("SELECT * FROM {field_data_field_archive} where field_archive_value = 1");
  $fields_archived = $request_field_archived->fetchAll();
  foreach($fields_archived as $field_archived ){
    $isMember = (og_get_membership('node',$field_archived->entity_id,'user',$user->uid) != FALSE );
    $isMember_from_userlist =  gofast_userlist_og_is_user_member_of_space($field_archived->entity_id, $user);

    //check membership from userlist
    if ($isMember || $isMember_from_userlist) {
      $roles = gofast_og_get_user_final_roles_for_space('node', $field_archived->entity_id, $user->uid);
    }

    $isPending = (!isset($roles)) || empty($roles) && $isMember;
      if (!$isPending && $isMember){
          $path_options['disabled_paths'][$field_archived->entity_id] = '/Sites' .  str_replace('/', '/_' , gofast_cmis_space_get_drupal_path($field_archived->entity_id)) ;
          $children_path = gofast_cmis_get_children(gofast_cmis_space_get_webdav_path($field_archived->entity_id));
           foreach ($children_path as $childpath){
               $folder_title = gofast_og_get_group_id_from_title_2($childpath,TRUE);
               if ($folder_title == $field_archived->entity_id){
                   $path_options['disabled_paths'][$childpath] = str_replace($origine, '' , $childpath) ;
               }
           }
      }
  }
  $tree = gofast_ztree_array_path_to_nested_objects_async($selected_and_selectable_og, $path_options, '/', $origine, $node->nid , $ispublication);

  //Fix GF4.0, /Sites checkbox appeared for some reason when selecting a space during Article creation so we make it impossible to check, and desactivate it.
  if(!$origine){
    $tree->{'children'}[0]->{"chkDisabled"} = TRUE;
    $tree->{'children'}[0]->{"nocheck"} = TRUE;
  }
  if (isset($_REQUEST["path_warnings"])) {
    $tree->{'children'}[0]->{"path_warnings"} = $_REQUEST["path_warnings"];
  }

  $json = $tree->__toString();

  if($print){
    print $json;
    exit;
  }else{
    return $json;
  }
}

/**
 * Used to retreive location managed by current user
 * at level N+1 from origin (if no origin provided from ROOT_SPACES)
 * @param type $node
 * @param type $origin
 * @return type
 */
function  gofast_get_node_locations_members_async($node = NULL, $origin = NULL, $notmanaged = FALSE){

  global $user;
  $all_paths = array();
  $selected_paths = array();
  $check_disabled_locations = array();
  $disabled_paths = array();

  if($notmanaged){
      $ogs = gofast_og_get_spaces_by_user($user, TRUE);
  }else{
      $ogs = gofast_og_get_spaces_by_user($user, FALSE);
  }
  $ogs_gids = array_keys($ogs);
  $temp_all_paths = gofast_cmis_space_get_drupal_path_multiple_nodes($ogs_gids);


  foreach ($temp_all_paths as $gid=>$path) {
    $ret = '/Sites';
    if (!empty($path)) {
      $parts = explode('/', $path);
      $ret .= implode('/_', $parts);
    }
    $all_paths[$gid] = str_replace("\\", ",", $ret);
  }

  if($origin == NULL){
    $origin = "/Sites/";
    $has_origine = NULL;
  }
  else {
    $has_origine = true;
    $origin = $origin.'/';
  }

  $origin_deep = substr_count($origin, '/');

  foreach ($all_paths as $gid => $path) {
    if(strpos($path.'/', $origin) === false ){
      unset($all_paths[$gid]);
    }else if( substr_count($path, '/') > ($origin_deep) ){
      unset($all_paths[$gid]);
    }
  }


  // This disables the root spaces (_Organisation, _Groups, _Public, _Extranet
  // and every user private spaces that are not current user private space).
  foreach ($all_paths as $gid => $path) {
    $parts = explode('/', $path);
    if (intval($gid) !== 0 && (count($parts) === 3 && $parts[2] !== '_'.$user->name)) {
      $disabled_paths[$gid] = $path;
    }
  }

  if(!$notmanaged){
    foreach($all_paths as $gid=> $path){
      if(! in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $gid))){
        $disabled_paths[$gid] = $path;
      }
    }
  }

   return array(
    'all_paths' => $all_paths,
    'selected_paths' => $selected_paths,
    'check_disabled_paths' => $check_disabled_locations,
    'disabled_paths' => $disabled_paths,
  );
}


/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource tree
 * @action locations
 * @methods GET
 */
function gofast_api_locations_tree($params){

    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "POST" && $params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check if we got a ename param
    if(!empty($params['ename'])){
        $_REQUEST['ename'] = $params['ename'];
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
        gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    gofast_api_success(array('tree' => gofast_ztree_async_json(false)));
}
