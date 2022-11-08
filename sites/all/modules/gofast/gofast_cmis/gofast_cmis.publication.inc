<?php

define('GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT', 0);
define('GOFAST_CMIS_PUBLICATION_TYPE_PDF', 1);

define('GOFAST_CMIS_PUBLICATION_FIELD', 'field_publication');

define('GOFAST_CMIS_PUBLICATION_SUFFIX', '_PUB');

/**
 * Returns wether the node is published or not
 * @param type $node
 * @return type
 */
function gofast_cmis_node_is_published($node) {
  return isset($node->{GOFAST_CMIS_PUBLICATION_FIELD}[LANGUAGE_NONE][0]['target_id']) ? $node->{GOFAST_CMIS_PUBLICATION_FIELD}[LANGUAGE_NONE][0]['target_id'] : FALSE;
}

/**
 * returns wether the $account can publish or not.
 * @global $user;
 * @param User $account the account to check, null to check current
 * @param node $node the node the check against
 * @return type
 */
function gofast_cmis_user_can_publish($node, $account = NULL) {
  if ($account === NULL) {
    global $user;
    $account = $user;
  }
  //si le user est auteur du noeud, administrateur ou publicateur, on renvoit true
  return node_access('update', $node , $account) || gofast_user_is_broadcaster($account);
}

/**
 * This function allows to return the source node of the publication.
 * @param type $node
 * @return type
 */
function gofast_cmis_get_publication_source($node) {
  $nid = db_select('field_data_field_publication', 'f')
          ->fields('f', array('entity_id'))
          ->condition('field_publication_target_id', $node->nid)
          ->execute()
          ->fetchField();

  return $nid;
}

/**
 * This is the form that allow to publish a node.
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @param type $node
 * @return int
 */
function gofast_cmis_node_publish_form($form, &$form_state) {

  $node = $form_state['build_info']['args'][0];

  $form['nid'] = array(
    '#type' => 'hidden',
    '#title' => t('Subject'),
    '#default_value' => $node->nid,
    '#value' => $node->nid,
    '#size' => 60,
    '#maxlength' => 128,
  );

  global $user;

  // We need to check if the node is inside a mirror folder in order to block multifiling if necessary
  // Check if the node is in a mirror folder
  $reference = $node->reference;

  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);

  $from_mirror = false;
  foreach ($folder_parents as $parent) {
    $parent_reference = gofast_cmis_item_get_by_path($parent)->properties['alfcmis:nodeRef'];
    $parents_parents = gofast_cmis_webservice_get_node_parents($parent_reference);
    // If more than 1 parents, it's a mirroring
    if (count($parents_parents) > 1) {
      $from_mirror = true;
    }
  }
 
  if($from_mirror){
    $form['from_mirror'] = array(
      '#markup' => '<div id="is-from-mirror" class="alert alert-custom alert-notice alert-light-warning fade show" role="alert"><div class="alert-icon"><i class="flaticon-warning"></i><div class="alert-text ml-2">' . t('This document is inside a mirror folder then you can\'t select other locations for the publication') . '</div></div><div class="alert-text"></div></div>',
    );
  }
  
  //on affiche la checkbox de selection ou non de transformation
  //tout d'abord on recupere le type de document que l'on souhaite publier,
  //car si c'est déjà un PDF, on ne propose pas de transformation
  $cmis_object_file_origine = gofast_cmis_item_get($node->reference);
  $mimetype = isset($cmis_object_file_origine) ? $cmis_object_file_origine->properties['cmis:contentStreamMimeType'] : '';

  $array_transformation_choices = array(GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT => t("No transformations"));
  if ($mimetype === "application/pdf") {
    $description = t("You can\'t transform this document because it is already a PDF");
  }
  else {
    //avant de proposer une transformation, je verifie si le document d'origine possède bien sa version PDF.
    // si pour X raison ce document ne possède pas de transformation PDF je ne la propose pas
    $json_pdf = gofast_cmis_webservice_item_generate_onlyoffice_preview($node->nid);
    if(!empty(json_decode($json_pdf)->FileUrl)){
        $pdf_exists = true;
    }else{
        $url = gofast_cmis_node_get_pdf_link($node);
        $pdf_exists = gofast_get_http_headers($url) === 200;
    }

    $description = t("Transformation is not available for this document");
    if ($pdf_exists) {
      $array_transformation_choices[GOFAST_CMIS_PUBLICATION_TYPE_PDF] = "PDF";
      $description = t("You can select original format (%1) or PDF transformation.", array("%1" => $mimetype));
    }
  }
  $format_tid = $node->{'field_format'}[LANGUAGE_NONE][0]['tid'];
  $format_picture = taxonomy_get_term_by_name('Picture', 'format');
  reset($format_picture);
  $first_key = key($format_picture);
  if ($format_tid != $first_key){
      $form['transformation'] = array(
        '#type' => 'select',
        '#title' => "<b>" . t("Transform the document") . '<span data-toggle="" title="' . htmlentities($description) . '">  <i class="fa fa-question-circle"></i></span> </b>',
        '#options' => $array_transformation_choices,
        '#default_value' => isset($array_transformation_choices[GOFAST_CMIS_PUBLICATION_TYPE_PDF]) ? GOFAST_CMIS_PUBLICATION_TYPE_PDF : GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT,
      );
  }


  $form['keep_metadata'] = array(
  '#type' => 'checkbox',
  '#title' => t('Keep original metadatas', array(), array("context" => "gofast")),
  '#default_value' => TRUE
  );


  $form['major_version_orig_file'] = array(
  '#type' => 'checkbox',
  '#title' => t('Tag original file as a major version', array(), array("context" => "gofast")),
  );

    $form['locations_checks'] = array(
        '#type' => 'item',
        '#title' => "<b>" . t('Locations selected for your publication') . "</b>",
        '#suffix' => "<div class='ui-locations-check' style='min-width:800px;margin-bottom:10px;'><i>" . t('You have not chosen locations to add...') ."</i></div>",
    );

  $all_og = array();
  $bundles = gofast_og_node_types();
  unset($bundles['private_space']);
  foreach (gofast_og_get_spaces_by_bundle(array_keys($bundles)) as $space_bundle) {
    $bundle_ogs = array_combine(array_keys($space_bundle), array_keys($space_bundle));
    $all_og += $bundle_ogs;
  }
  $private_space_nid = gofast_og_get_user_private_space()->nid;
  $all_og[$private_space_nid] = intval($private_space_nid);

  $form[GOFAST_OG_CONTENT_MEMBERSHIP_FIELD] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $all_og,
    '#attributes' => array("class" => array("gofast_display_none"))
  );


  $selected_options = array_map(function($element) {
    return $element['value'];
  }, $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE]);

   $selected_options_fliped = array();
   foreach($selected_options as $key=>$option){
      ## need to get access to all private spaces or spaces we dont have access to.
      $nid_selected_options = $node->og_group_content_ref[LANGUAGE_NONE][$key]['target_id'];
      if(!$nid_selected_options){
        $selected_options_fliped["/Sites"] = "/Sites";
        unset($selected_options[$key]);
      }elseif ($nid_selected_options && og_user_access('node', $nid_selected_options, 'create alfresco_item content') == TRUE){
        $selected_options_fliped[$option] = $option;
      }else{
        unset($selected_options[$key]);
      }
    }
    array_values($selected_options);
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#multiple'] = TRUE;
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#title'] = "<b>" . t("Select target of your publication") . "</b>";
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#required'] = FALSE;
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#type'] = 'select';
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#options'] = $selected_options_fliped;
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#default_value'] = $selected_options;
    $form[GOFAST_CMIS_LOCATIONS_FIELD]['#value'] = $selected_options;
    $form[GOFAST_CMIS_LOCATIONS_FIELD]["#attributes"]["class"][] = "gofast_display_none";
    $form[GOFAST_CMIS_LOCATIONS_FIELD]["#disable_selected"] = TRUE;


  ##GOFAST-5769
  if (gofast_user_is_broadcaster($user) && !$from_mirror) {
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

 }

  // Add event click to modal submit trigger
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit', array(), array('context' => 'gofast')),
    '#prefix' => '',
    '#suffix' => '',
    '#weight' => 10,
    '#ajax' => array(
      'wrapper' => 'ajax_content',
      'callback' => 'gofast_cmis_node_publish_form_submit',
      'event' => 'click'
    ),
    '#attributes' => array('class' => array('btn btn-sm btn-success'))
  );

  $form['#attached']['js'][] = array(
    'type' => 'file',
    'group' => JS_THEME + 1,
    'data' => drupal_get_path('module', 'gofast') . '/js/gofast_ajax_form.js',
  );


$publication_information = t("Your publication title will be suffixed with <strong>%suffix</strong> before the extension.", array('%suffix' => GOFAST_CMIS_PUBLICATION_SUFFIX));

  $form['#validate'][] = 'gofast_cmis_node_publish_form_validate';
  return $form;
}

/**
 * Hook form validate on node_publish_form
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_node_publish_form_validate(&$form, &$form_state) {
  //We clear the form errors as Drupal throws a fake error
  drupal_get_messages();

  $form['#submit'] = array();
  $node = $form_state['build_info']['args'][0];
  $array_path = array();
  foreach ($form_state['input'][GOFAST_CMIS_LOCATIONS_FIELD] as $location) {
    if (intval($location) !== 0) {
      $group_path = gofast_cmis_space_get_webdav_path($location);
      $array_path[$group_path] = $group_path;
    }
    else {
      $array_path[$location] = $location;
    }
  }

  $form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD] = $array_path;
  $form_state['selected_groups'] = array_keys($form_state['values'][GOFAST_OG_CONTENT_MEMBERSHIP_FIELD]);

  if (empty($array_path) && empty($form_state['input'])) {
    form_set_error(GOFAST_CMIS_LOCATIONS_FIELD, t('Path cannot be empty', array(), array('context' => 'gofast:gofast_cmis')));
    return;
  }
  else {
    $pathinfo = pathinfo($node->title);

    if (intval($form_state['values']['transformation']) === GOFAST_CMIS_PUBLICATION_TYPE_PDF) {
      $transformation_extension = '.pdf';
    }
    else {
      $transformation_extension = isset($pathinfo['extension']) && $pathinfo['extension'] !== NULL ? '.' . $pathinfo['extension'] : '';
    }

    $publication_title = $pathinfo['filename'] . GOFAST_CMIS_PUBLICATION_SUFFIX . $transformation_extension;

    $form_state['values']['title'] = $publication_title;
    $existing_locations = gofast_cmis_check_file_exists_in_paths($publication_title, $array_path);
    if (!empty($existing_locations)) {
      $paths_as_list = '';
      foreach ($existing_locations as $location) {
        $paths_as_list .= '<li>' . $location . '</li>';
      }
      form_set_error(GOFAST_CMIS_LOCATIONS_FIELD, t('The file cannot be sent.'
                                      .' There is a file with same name in the following paths :', array(), array('context' => 'gofast:gofast_cmis'))
                                      .' <br /><ul>' . $paths_as_list . '</ul>' );
      
      return;
    }
  }
  
  }

function gofast_cmis_publish_get_ajax_commands($publication_nid, &$form, &$form_state) {
    global $user;
  $commands = array();
  ctools_include('modal');
  ctools_include('ajax');
  //if ($errors = form_get_errors()) {
  if (FALSE == TRUE) {
    $form_state['rebuild'] = TRUE;
    $error_msg = theme('status_messages');
    $output = drupal_rebuild_form($form['#form_id'], $form_state, $form);
    // $commands[] = ajax_command_html('#messages-placeholder', $error_msg);
    $output = $error_msg . render($output);
    $output = gofast_normalize_string_from_ajaxifying($output);
    $commands[] = array(
      'command' => 'error_creating_node',
      'form' => $output,
      'custom_fields' => array(GOFAST_OG_CONTENT_MEMBERSHIP_FIELD),
      'errors' => $errors,
      'wrapper' => '#modal-content'
    );
  } else {
    if ($publication_nid) {
      $form_state['values']['nid'] = $publication_nid;
      $form_state['nid'] = $publication_nid;

      $nid_node = $form_state['build_info']['args'][0]->nid;
      $last_event_unserialized["mod_timestamp"] = time();
      $last_event_unserialized["mod_author"] = $user->uid;
      $event_type = "publication_created";
      $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => $event_type);
      $event = serialize($event);
      $last_event_serialized = rawurlencode($event);
      gofast_audit_insert_line_audit($nid_node, $event_type, $last_event_serialized, $last_event_unserialized);

      $commands[] = ajax_command_html('#ctools-add-js', "<script type='text/javascript'>
        window.location.href = '/node/" . $publication_nid."';
        </script>"
      );

      $commands[] = ctools_modal_command_dismiss();
    }
  }

  return $commands;
}

/**
 * Hook form submit on node_publish_form
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_node_publish_form_submit($form, &$form_state) {

  global $user;

  $node = $form_state['build_info']['args'][0];
  $array_path = isset($form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD]) ? $form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD] : array();

  $broadcast_values = $form_state['input']['ac-list-tags-broadcast'];
  $broadcast_array = json_decode(trim($broadcast_values));
  if(count($broadcast_array) > 0 && $broadcast_array[0] != ""){
    foreach($broadcast_array as $key => $broadcast_object){
      if($broadcast_object->type == "user"){
        $private_gid = gofast_og_get_user_private_space(user_load($broadcast_object->value), FALSE);
        $path = gofast_cmis_space_get_webdav_path($private_gid);
        $array_path[$path] = $path;
        $form_state['selected_groups'][] = $private_gid;
      }else{
        $path = gofast_cmis_space_get_webdav_path($broadcast_object->value);
        $array_path[$path] = $path;
        $form_state['selected_groups'][] = $broadcast_object->value;
      }
    }
  }

  $file = gofast_cmis_item_get_content_publication($node, intval($form_state['values']['transformation']));

  ##GOFAST-5769
  if(empty($form_state['input']['ac-list-tags-broadcast'])){
    $is_broadcaster = 0;
  }else{
    $is_broadcaster = 1;
  }
  $options = array(
    'author' => $user,
    'locations' => $array_path,
    'language' => $node->language,
    'parent_publication_id' => $node->nid,
    'parent_spaces' => $form_state['selected_groups'],
    'main_location' => reset($array_path),
    'file' => $file,
    'publish_as_broadcaster' => $is_broadcaster
  );

    //if needed, tag original file as major version
  if($form_state['values']['major_version_orig_file']){
      $parent_node = node_load($node->nid);
      gofast_cmis_tag_major_version($parent_node, "");
  }

  //if needed, keep some metadata from original node
  if($form_state['values']['keep_metadata']){
      $source_node = node_load($node->nid);
       $options["tags"] = $source_node->{'field_tags'}[LANGUAGE_NONE];
       $options["criticity"] = $source_node->{'field_criticity'}[LANGUAGE_NONE];
       $options["document_author"] = $source_node->{'field_document_author'}[LANGUAGE_NONE];
       $options["category"] = $source_node->{'field_category'}[LANGUAGE_NONE];
  }


  $publication = gofast_cmis_publication_create($form_state['values']['title'], $options);
  
  $commands = gofast_cmis_publish_get_ajax_commands($publication->nid, $form, $form_state);
  
  print(ajax_render($commands));
  exit;

//  $form_state['redirect'] = array('node/' . $publication->nid);
//  drupal_redirect_form($form_state);
}

/**
 * This is the form that allow to publish nodes.
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @return int
 */
function gofast_cmis_manage_publications_form($form, &$form_state) {
  $selected_items_json = array();
  global $user;

  // Extract a variable set in gofast_ajax_file_browser.js to get all paths selected when you click on "manage publications"
  if(variable_get("ithit_bulk_".$user->uid, NULL)){
    $selected_items_json = json_decode(rawurldecode(variable_get("ithit_bulk_".$user->uid, NULL)));
    variable_del("ithit_bulk_".$user->uid);
  }
  // Extract a variable set in gofast_ajax_file_browser.js to get all paths selected when you click on "manage publications" in the cart
  if(variable_get("ithit_bulk_cart_".$user->uid, NULL)){

    //Get all nid node in the cart
    $selected_items_json = json_decode(rawurldecode(variable_get("ithit_bulk_cart_".$user->uid, NULL)));
    $nid_cart = array();
    $title_cart = array();
    // Reach all nid and transform it to a path (available with folders)
    foreach($selected_items_json as $select){
      $node = node_load($select->url);
      $paths = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
      foreach($paths as $path){
        array_push($nid_cart, $path['value'] . '/' . $node->title);
        array_push($title_cart,$node->title);
      }
    }
    foreach($nid_cart as $key=>$path_cart){
      $selected_items_json[$key]->url = '/alfresco/webdav' . $path_cart;
    }
    variable_del("ithit_bulk_cart_".$user->uid);
  }


  /*if (isset($_COOKIE['ithit_bulk'])) {
    $selected_items_json = json_decode($_COOKIE['ithit_bulk']);
  }*/


  // Sorting the items received in parameter (Folders first, then Resource)
  usort($selected_items_json, function($a, $b) {
    return $a->type > $b->type;
  });

  $items_by_type = array();
  foreach ($selected_items_json as $selected_item_type) {
    $items_by_type[$selected_item_type->type][] = $selected_item_type->url;
  }

  $selected_nids = array();
  foreach ($items_by_type as $type => $items) {
    foreach ($items as $item_path) {
      //Force replication of this content if it's not yet replicated
      $_GET['href'] = $item_path;
      gofast_cmis_replicate(FALSE);

      $alfresco_path = str_replace("/alfresco/webdav", "", $item_path);
      $item = gofast_cmis_item_get_by_path($alfresco_path);
      if (isset($item->id)) {
        if(isset($item->properties['gofast:nid'])){
          if($item->properties['gofast:nid'] == 0){
            $selected_nids[rand(-9999999, -1)] = $alfresco_path;
          }else{
            $selected_nids[$item->properties['gofast:nid']] = $alfresco_path;
          }
        }else{
          if(gofast_ajax_file_browser_get_nid_from_reference($item->properties['alfcmis:nodeRef']) == 0){
            $selected_nids[rand(-9999999, -1)] = $alfresco_path;
          }else{
            $selected_nids[gofast_ajax_file_browser_get_nid_from_reference($item->properties['alfcmis:nodeRef'])] = $alfresco_path;
          }
        }
      }
    }
  }
  //used later into async request
  //  variable_set("ithit_bulk_async_".$user->uid, $selected_nids);

  $form_state['selected_nids'] = array_keys($selected_nids);
  $form['selected_nids'] = array(
    '#type' => 'textfield',
    '#default_value' => json_encode(array_keys($selected_nids)),
    '#maxlength' => "99999"
  );

  $form['selected_nids']['#attributes']['class'][] = "gofast_display_none";

  $nodes = explode(',',$form['selected_nodes_ids']['#default_value']);
  $nodes = str_replace("[",'',$nodes);
  $nodes = str_replace("]",'',$nodes);
  foreach($nodes as $key=>$nid){
    $node = node_load($nid);
    $cmis_object_file_origine = gofast_cmis_item_get($node->reference);
    $mimetype = isset($cmis_object_file_origine) ? $cmis_object_file_origine->properties['cmis:contentStreamMimeType'] : '';
    $array_transformation_choices = array(GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT => t("No transformations"));
    if ($mimetype === "application/pdf") {
      $description = 0;
    }
    else {
      //avant de proposer une transformation, je verifie si le document d'origine possède bien sa version PDF.
      // si pour X raison ce document ne possède pas de transformation PDF je ne la propose pas
      $url = gofast_cmis_node_get_pdf_link($node);
      $pdf_exists = gofast_get_http_headers($url) === 200;

      $description = t("Transformation is not available for these documents");
      if ($pdf_exists) {
        $array_transformation_choices[GOFAST_CMIS_PUBLICATION_TYPE_PDF] = "PDF";
        $description = t("You can select original format or PDF transformation.");
      }
    }
    $format_tid = $node->{'field_format'}[LANGUAGE_NONE][0]['tid'];
    $format_picture = taxonomy_get_term_by_name('Picture', 'format');
    reset($format_picture);
    $first_key = key($format_picture);
    if ($format_tid != $first_key){
      $form['transformation'] = array(
        '#type' => 'select2',
        '#title' => "<b>" . t("Transform the document") . '<span data-toggle="" title="' . htmlentities($description) . '">  <i class="fa fa-question-circle"></i></span> </b> ',
        '#options' => $array_transformation_choices,
        '#attributes' => array("class" => array("d-flex", "flex-colum"))
      );
    }
  }
  $all_og = array();
  $bundles = gofast_og_node_types();
  unset($bundles['private_space']);
  foreach (gofast_og_get_spaces_by_bundle(array_keys($bundles)) as $space_bundle) {
    $bundle_ogs = array_combine(array_keys($space_bundle), array_keys($space_bundle));
    $all_og += $bundle_ogs;
  }
  $private_space_nid = gofast_og_get_user_private_space()->nid;
  $all_og[$private_space_nid] = intval($private_space_nid);

  $form[GOFAST_OG_CONTENT_MEMBERSHIP_FIELD] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => $all_og,
    '#attributes' => array("class" => array("gofast_display_none"))
  );


  $form['locations_checks'] = array(
    '#type' => 'item',
    '#title' => t('Locations selected to publish'),
    '#suffix' => "<div class='ui-locations-check' style='min-width:800px;margin-bottom:10px;'><i>" . t('You did not choose a location for publishing ...') ."</i></div>",
  );


  //Get root spaces
  $groups = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Groups");
  $organisations = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Organisations");
  $extranet = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Extranet");
  $public = gofast_ajax_file_browser_get_nid_from_href("/Sites/_Public");
  $ztree = array(
    $groups => "/Sites/_Groups",
    $organisations => "/Sites/_Organisations",
    $extranet => "/Sites/_Extranet",
    $public => "/Sites/_Public",
  );

  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#multiple'] = TRUE;
  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#title'] = t("Select locations where your selected documents will be published", array(), array('context' => 'gofast'));
  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#required'] = FALSE;
  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#type'] = 'select';
  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#options'] = $ztree;
  $form[GOFAST_CMIS_LOCATIONS_FIELD]['#value'] = $ztree;
  $form[GOFAST_CMIS_LOCATIONS_FIELD]["#attributes"]["class"][] = "gofast_display_none";

  if(!empty($selected_nids)){
    $_SESSION['selected_file_path'] = $selected_nids;
  }

  if (gofast_user_is_broadcaster($user)) {
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
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t("Save", array(), array('context' => 'gofast')),
  );
  return $form;
  }


/**
 * Hook form validate on manage_publications_form
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_manage_publications_form_validate(&$form, &$form_state) {
  //We clear the form errors as Drupal throws a fake error
  drupal_get_messages();

  // Create nodes array
  $nodes = explode(',',$form_state['input']['selected_nids']);
  $nodes = str_replace("[",'',$nodes);
  $nodes = str_replace("]",'',$nodes);
  foreach($nodes as $key=>$nid){
    $node = node_load($nid);
    $array_path = array();
    foreach ($form_state['input'][GOFAST_CMIS_LOCATIONS_FIELD] as $location) {
      if (intval($location) !== 0) {
        $group_path = gofast_cmis_space_get_webdav_path($location);
        $array_path[$group_path] = $group_path;
      }
      else {
        $array_path[$location] = $location;
      }
    }

    $form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD] = $array_path;
    $form_state['selected_groups'] = array_keys($form_state['values'][GOFAST_OG_CONTENT_MEMBERSHIP_FIELD]);

    if (empty($array_path) && empty($form_state['input'])) {
      form_set_error(GOFAST_CMIS_LOCATIONS_FIELD, t('Path cannot be empty', array(), array('context' => 'gofast:gofast_cmis')));
      return;
    }
    else {
      $pathinfo = pathinfo($node->title);

      $exclude_pdf = ['PNG', 'JPG', 'JPEG'];

      if (intval($form_state['values']['transformation']) === GOFAST_CMIS_PUBLICATION_TYPE_PDF && !in_array(strtoupper($pathinfo['extension']), $exclude_pdf)) {
          $transformation_extension = '.pdf';
      }
      else {
        $transformation_extension = isset($pathinfo['extension']) && $pathinfo['extension'] !== NULL ? '.' . $pathinfo['extension'] : '';
      }
      $publication_title = $pathinfo['filename'] . GOFAST_CMIS_PUBLICATION_SUFFIX . $transformation_extension;

      $form_state['values']['title'][] = $publication_title;
      $existing_locations = gofast_cmis_check_file_exists_in_paths($publication_title, $array_path);
      if (!empty($existing_locations)) {
        $paths_as_list = '';
        foreach ($existing_locations as $location) {
          $paths_as_list .= '<li>' . $location . '</li>';
        }
        form_set_error(GOFAST_CMIS_LOCATIONS_FIELD, t('The file cannot be sent.'
        .' There is a file with same name in the following paths :', array(), array('context' => 'gofast:gofast_cmis'))
        .' <br /><ul>' . $paths_as_list . '</ul>' );
        return;
      }
    }

  }
  }



function gofast_cmis_manage_publications_get_ajax_commands($publication_nid, &$form, &$form_state) {
  $commands = array();
  ctools_include('modal');
  ctools_include('ajax');
  //if ($errors = form_get_errors()) {
    if(FALSE == TRUE){
      $form_state['rebuild'] = TRUE;
      $error_msg = theme('status_messages');
      $output = drupal_rebuild_form($form['#form_id'], $form_state, $form);
      // $commands[] = ajax_command_html('#messages-placeholder', $error_msg);
      $output = $error_msg . render($output);
      $output = gofast_normalize_string_from_ajaxifying($output);
      $commands[] = array(
        'command' => 'error_creating_node',
        'form' => $output,
        'custom_fields' => array(GOFAST_OG_CONTENT_MEMBERSHIP_FIELD),
        'errors' => $errors,
        'wrapper' => '#modal-content'
      );
    } else {
      if ($publication_nid) {
        $form_state['values']['nid'] = $publication_nid;
        $form_state['nid'] = $publication_nid;

      }
    }

    return $commands;
}



  /**
 * Hook form submit on cmis_manage_publications
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_manage_publications_form_submit($form, &$form_state) {
  // Create nodes array
  $nodes = explode(',',$form_state['input']['selected_nids']);
  $nodes = str_replace("[",'',$nodes);
  $nodes = str_replace("]",'',$nodes);


  // Give all informations for the asynchronous request

  // Emplacement to publish
  $locations = $form_state['values'][GOFAST_CMIS_LOCATIONS_FIELD];

  // Transformation pdf or not
  $transformation = $form_state['values']['transformation'];

  // Get locations for broadcaster
  $broadcast_values = $form_state['input']['ac-list-tags-broadcast'];
  $broadcast_array = json_decode(trim($broadcast_values));
  if(count($broadcast_array) > 0 && $broadcast_array[0] != ""){
    global $cmis_as_publisher;
    global $cmis_sudo_admin;
    $cmis_as_publisher = true;
    $cmis_sudo_admin = true;
    foreach($broadcast_array as $key => $broadcast_object){
      if($broadcast_object->type == "user"){
        $private_gid = gofast_og_get_user_private_space(user_load($broadcast_object->value), FALSE);
        $path = gofast_cmis_space_get_webdav_path($private_gid);
        $locations[$path] = $path;
        $form_state['selected_groups'][] = $private_gid;
      }else{
        $path = gofast_cmis_space_get_webdav_path($broadcast_object->value);
        $locations[$path] = $path;
        $form_state['selected_groups'][] = $broadcast_object->value;
      }
    }
  }

  //Insert a general progress bar for mass publication
  $html = '<div class="progress mb-4" id="publications-panels-progress"><div class="progress-bar" role="progressbar" style="width: 0%;" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100">0 / ' . count($nodes) . '</div></div>';
  foreach($nodes as $key=>$nid){
    $title = $form_state['values']['title'][$key];
    //Create publish modal theme
    $html .= theme('gofast_manage_publication_progression', array('nid' => $nid, 'transformation' => $transformation , 'title' => $title, 'locations' => $locations ,'locations_nid' => $form_state['selected_groups'], "is_broadcast" => $cmis_as_publisher));
  }

  //Remove the current modal (ztree)
  $commands[] = ctools_modal_command_dismiss();

  //Display a modal that tracks the progress of publications
  $commands[] = ctools_modal_command_display(t("In progress", array(), array('context' => 'gofast:taxonomy')), $html);

  //Call asynchronous function (call in gofast_cmis_publication.js)
  $commands[] = gofast_command_callback('Gofast.manage_publication_process');
  print(ajax_render($commands));
  exit;
}

/*
 * Process an item of the massive publication management
 */
function gofast_manage_publications_process(){
  global $user;

  // Get all informations from the asynchronous request to process

  // Nid && title of the current document
  $nid = $_POST['process_nid'];
  $title = $_POST['process_title'];

  // Get the transformation (PDF or not)
  $transformation = $_POST['process_transformation'];

  // Get path and nid locations
  $locations = json_decode($_POST['process_locations']);
  $locations_nid = json_decode($_POST['process_locations_nid']);

  // Get if the current user is a broadcaster
  $is_broadcast = (int)$_POST['is_broadcast'];

  // Check if a publication already exist
  $node = node_load($nid);
  $cmis_object_file_origine = gofast_cmis_item_get($node->reference);
  $mimetype = isset($cmis_object_file_origine) ? $cmis_object_file_origine->properties['cmis:contentStreamMimeType'] : '';
  if (!empty(gofast_cmis_get_publication_source($node))){
    print 'is_publication';
    exit;
  }

// Check if the document is a PDF
  if ($mimetype === "application/pdf"){
    $transformation = 0;
  }
  $url = gofast_cmis_node_get_pdf_link($node);
  $pdf_exists = gofast_get_http_headers($url) === 200;

  if (!$pdf_exists && $transformation == 1){
    $transformation = 0;
    $can_pdf='no_pdf';
  }

  $array_path = isset($locations) ? $locations : array();

  $retention_node = false;
  if(module_exists('gofast_retention')){
    if( gofast_retention_get_retention_date($node) !== NULL){
      $retention_node = true;
    }
  }

  $archived_node = gofast_get_content_state_archived($node);
  if (node_access("update", $node) && !$archived_node && !$retention_node) {
    if(gofast_cmis_user_can_publish($node)) {

      if(is_numeric($nid) && $nid > 0 && $nid == round($nid)){

        $file = gofast_cmis_item_get_content_publication($node, intval($transformation));
        //Give all information in order to publish the node
        $options = array(
          'author' => $user,
          'locations' => $array_path,
          'language' => $node->language,
          'parent_publication_id' => $nid,
          'parent_spaces' => $locations_nid,
          'main_location' => reset($array_path),
          'file' => $file,
          'publish_as_broadcaster' => $is_broadcast,
        );
        $publication_field_emplacements = array();
        $publication = gofast_cmis_publication_create($title, $options);
        $publication_field_emplacements = $publication->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
        $publications_locations = array();
        foreach($publication_field_emplacements as $key=>$publication_emplacement){
          $publications_locations[$key] = $publication_emplacement['value'];
        }
        print(json_encode($publications_locations));
        exit;

      }
    }
  }
  print('');
  exit;
}


/**
 * This function returns the file used for publication regarding a selected type (PDF/node mimetype)
 * @param type $node the node from which we create the publication
 * @param type $type the type of the file we will retrieve
 * @return File the file that will be used for publication
 */
function gofast_cmis_item_get_content_publication($node, $type) {
  // We will generate the publication using PDF preview, else by document type
  if ($type === GOFAST_CMIS_PUBLICATION_TYPE_PDF) {

    $json_pdf = gofast_cmis_webservice_item_generate_onlyoffice_preview($node->nid);
    if(!empty(json_decode($json_pdf)->FileUrl)){
    $document_pdf_url = json_decode($json_pdf)->FileUrl;
    global $base_url;
    $doc_id = str_replace($base_url."/gofast/get_onlyoffice_preview/", "" , $document_pdf_url);
    if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$doc_id)){
        $oo_file = fopen("/var/www/d7/sites/default/files/oo_previews/".$doc_id, "r");
        $file_content = fread($oo_file, filesize("/var/www/d7/sites/default/files/oo_previews/".$doc_id));

    }

    }else{
	$document_pdf_url = gofast_cmis_node_get_pdf_link($node);
	$file_content = gofast_get_http_file($document_pdf_url);
    }
    $pathinfo = pathinfo($node->title);
    $new_node_title = $pathinfo['filename'] . ".pdf";
    $file_mime = "application/pdf";
  }
  else {
    $new_node_title = $node->title;
    $file_content = gofast_cmis_item_get_content($node->reference);
    $file_mime = gofast_cmis_item_get($node->reference)->properties['cmis:contentStreamMimeType'];
  }

  $public_path = DRUPAL_ROOT . '/' . variable_get('file_public_path', conf_path() . '/files');
  $file_path = "{$public_path}/{$new_node_title}";
  $written_file = fopen($file_path, "w+");
  fwrite($written_file, $file_content);
  fclose($written_file);

  $file = new stdClass();
  $file->filename = $new_node_title;
  $file->filepath = $file_path;
  $file->filemime = $file_mime;

  return $file;
}

/**
 * This is the form that allow to republish a node.
 * @param type $form
 * @param type $form_state
 * @param type $node
 * @return type
 */
function gofast_cmis_node_republish_form($form, &$form_state) {

  $node = $form_state['build_info']['args'][0];

  $form["tag_comment"] = array(
    '#type' => "textarea",
    '#cols' => 50,
    "#title" => t("Comment"),
    '#attributes' => array('placeholder' => t('Add a comment', array(), array('context' => 'gofast:gofast_cmis')))
  );

    $form['major_version_orig_file'] = array(
     '#type' => 'checkbox',
     '#title' => t('Tag original file as a major version', array(), array("context" => "gofast")),
   );

 $form['keep_metadata'] = array(
  '#type' => 'checkbox',
  '#title' => t('Keep original metadatas', array(), array("context" => "gofast")),
  );

//  $form['submit'] = array(
//    '#type' => 'submit',
//    '#value' => t("Submit"),
//  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit', array(), array('context' => 'gofast')),
    '#prefix' => '',
    '#suffix' => '',
    '#weight' => 10,
    '#ajax' => array(
      'wrapper' => 'ajax_content',
      'callback' => 'gofast_cmis_node_republish_form_submit',
      'event' => 'click'
    ),
  );

  $form['#attached']['js'][] = array(
    'type' => 'file',
    'group' => JS_THEME + 1,
    'data' => drupal_get_path('module', 'gofast') . '/js/gofast_ajax_form.js',
  );

  $form['#validate'][] = 'gofast_cmis_node_republish_form_validate';

  return $form;
}

/**
 * Hook form validate on node_republish_form
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_node_republish_form_validate(&$form, &$form_state) {
  $form['#submit'] = array();
//  if (empty($form_state['values']['tag_comment'])) {
//    form_set_error('tag_comment', t("You have to set a comment."));
//  }

  return $form;
}

/**
 * Hook form submit on node_republish_form
 * @param type $form
 * @param type $form_state
 */
function gofast_cmis_node_republish_form_submit($form, &$form_state) {

  $node = $form_state['build_info']['args'][0];
  $publicated_nid = $node->{GOFAST_CMIS_PUBLICATION_FIELD}[LANGUAGE_NONE][0]['target_id'];
  $publicated_node = node_load($publicated_nid);
  $publicated_reference = gofast_cmis_node_get_item_id($publicated_node);
  $publicated_item = gofast_cmis_item_get($publicated_reference);

  $publication_type_pdf = $publicated_item->properties['cmis:contentStreamMimeType'] === 'application/pdf';
  $file = gofast_cmis_item_get_content_publication($node, intval($publication_type_pdf));

  $locations = array_map(function($element){return $element['value']; }, $publicated_node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE]);
  //$cmis_as_publisher = count(array_diff($locations, gofast_ztree_get_paths())) > 0;
    //determine if the user has access to the target document. if not (it means the publication creator was a broadcaster), the cmis requests must be done as admin
  global $user;
  if(!gofast_og_node_access($publicated_node, "update",$user)){
      $cmis_as_publisher = true;
  }else{
       $cmis_as_publisher = false;
  }

  //Update the selected folder to allow user to write in it.
  $location_item_ids = array();
  if ($cmis_as_publisher) {
    foreach ($locations as $location) {
      $location_item_ids[] = gofast_cmis_item_get_by_path($location)->id;
    }
    foreach ($location_item_ids as $location_item_id) {
      gofast_cmis_webservice_item_set_permission($location_item_id, $publicated_node->name);
    }
  }

  // Update the publication
  $updated_item = gofast_cmis_item_set_content($publicated_reference, file_get_contents($file->filepath), $file->filemime, array(), FALSE);

  // Create a comment
  gofast_cmis_tag_major_version($publicated_node, $form_state['values']['tag_comment']);

  //Then restore the initial folders permissions.
  if ($cmis_as_publisher) {
    foreach ($location_item_ids as $location_item_id) {
      gofast_cmis_webservice_item_set_permission($location_item_id, $node->name, TRUE);
    }
  }

  gofast_cmis_purge_published_temp_file($file->filepath);

    if($form_state['values']['major_version_orig_file']){
      $parent_node = node_load($node->nid);
      gofast_cmis_tag_major_version($parent_node, "");
  }

   if($form_state['values']['keep_metadata']){
         $source_node = node_load($node->nid);
         $publicated_node->{'field_criticity'}[LANGUAGE_NONE] = $source_node->{'field_criticity'}[LANGUAGE_NONE];
         $publicated_node->{'field_document_author'}[LANGUAGE_NONE] = $source_node->{'field_document_author'}[LANGUAGE_NONE];
         $publicated_node->{'field_category'}[LANGUAGE_NONE] = $source_node->{'field_category'}[LANGUAGE_NONE];
         field_attach_update('node', $publicated_node);
   }


//store versions informations into corresponding field ( field_publication_history )
 $source_list = gofast_cmis_webservice_item_get_versions($node->reference, true);
 $source_version = $source_list[0]->label;

 $published_list = gofast_cmis_webservice_item_get_versions($publicated_node->reference, true);
 $published_version = $published_list[0]->label;

 $new_field_publication_history = array();
 $existing_field_publication_history_value = $node->field_publication_history[LANGUAGE_NONE][0]["value"];
 $existing_field_publication_history_value = json_decode($existing_field_publication_history_value, true);
 $existing_field_publication_history_value[$source_version] = array("source_version" => $source_version , "published_version" => $published_version, "date" => time(), "comment" => $form_state['values']['tag_comment'], "creator" => $user->name);
 $new_field_publication_history[LANGUAGE_NONE][0]["value"]  = json_encode($existing_field_publication_history_value);

 $node->field_publication_history = $new_field_publication_history;
 field_attach_update('node', $node);

  return array('#type' => 'ajax', '#commands' => gofast_cmis_publish_get_ajax_commands($publicated_nid, $form, $form_state));


//  $form_state['redirect'] = array('node/' . $publicated_nid);
//  drupal_redirect_form($form_state);
}

/**
 * This function creates a publication from a file or a reference_file.
 * @param type $title
 * @param type $options
 * @return node the node created
 */
function gofast_cmis_publication_create($title, $options) {
  // Check author.
  if (!(is_object($options['author']) && $options['author']->uid)) {
    $options['author'] = $options['author'] && ($options['author'] = user_load($options['author'])) ? $options['author'] : user_load(GOFAST_USER_ADMINISTRATOR_ID);
    if ($options['author'] === FALSE) {
      watchdog('gofast_cmis', 'Cannot create alfresco_item node, no author provided', NULL, WATCHDOG_ERROR);
      return;
    }
  }

  $locations = array();
  foreach ($options['locations'] as $location) {
    $locations[] = array('value' => $location);
  }

  $cmis_as_publisher = $options['publish_as_broadcaster'] === 1 ? TRUE : FALSE;

  //Update the selected folder to allow user to write in it.
  $location_item_ids = array();
  if ($cmis_as_publisher) {
    foreach ($locations as $location) {
      //$location_item_ids[] = gofast_cmis_item_get_by_path($location['value'])->id;
    }
    foreach ($location_item_ids as $location_item_id) {
      //gofast_cmis_webservice_item_set_permission($location_item_id, $options['author']->name);
    }
  }

  // Upload the file to the remote locations (main location as main for publication if possible)
  $target_item = isset($options['main_location']) ? gofast_cmis_item_get_by_path($options['main_location']) : gofast_cmis_item_get_by_path($locations[0]['value']);
  $item = gofast_cmis_item_content_insert($target_item->id, $title, file_get_contents($options['file']->filepath), $options['file']->filemime, array(), $cmis_as_publisher);
  variable_set("cmis_creating_" . $item->properties['alfcmis:nodeRef'], "true");
  // Create the drupal node
  $node = new stdClass();
  $node->is_new = TRUE;
  $node->title = $title;
  $node->type = 'alfresco_item';
  $node->language = $options['language'];
  $node->options = array();
  $node->promote = NODE_NOT_PROMOTED;
  $node->module = 'node';
  $user = $options['author'];
  $node->uid = $user->uid;
  $node->status = NODE_PUBLISHED;
  $node->comment = COMMENT_NODE_OPEN;

  if(isset($options["tags"])){
       $node->{'field_tags'}[LANGUAGE_NONE] = $options["tags"];
  }
  if(isset($options["criticity"])){
       $node->{'field_criticity'}[LANGUAGE_NONE] = $options["criticity"];
  }
  if(isset($options["document_author"])){
       $node->{'field_document_author'}[LANGUAGE_NONE] = $options["document_author"];
  }

  if(isset($options["category"])){
       $node->{'field_category'}[LANGUAGE_NONE] = $options["category"];
  }

  $tag_publication = gofast_xeditable_terms_get_from_array(GOFAST_VID_TAGS, array('Publication'));
  $node->{'field_tags'}[LANGUAGE_NONE][]['tid'] = $tag_publication[0]->tid;

  $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] = $item->properties['alfcmis:nodeRef'];
  $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE] = $locations;
  $node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value'] = $locations[0];
  $node->{GOFAST_CMIS_FILENAME_FIELD}[LANGUAGE_NONE][0]['value'] = $title;

  //prevent automatic multifilling here, because for the moment, the $node object doesn't contains groups, so it will not work
  $_POST['prevent_automatic_multifilling'] = true;

  node_save($node);

  //Then restore the initial folders permissions.
  if ($cmis_as_publisher) {
    foreach ($location_item_ids as $location_item_id) {
     // gofast_cmis_webservice_item_set_permission($location_item_id, $options['author']->name, TRUE);
    }
  }

  // Set the parents groups for the new publication
  foreach ($options['parent_spaces'] as $space) {
    if(!empty($space)){
    gofast_og_subscribe_node(intval($space), $node->nid);
  }
  }

  if (isset($options['parent_publication_id']) && $node !== FALSE) {
    $parent_publication_node = node_load($options['parent_publication_id']);

    // This allow to add the "Published" tag to the source document.
    // This feature is currently de-activated and reported to later (need discussions).
    //$tag_publicated = gofast_xeditable_terms_get_from_array(GOFAST_VID_TAGS, array('Published'));
    //$parent_publication_node->{'field_tags'}[LANGUAGE_NONE][0]['tid'] = $tag_publicated[0]->tid;

    // Set the publication node id for the source document
    $parent_publication_node->field_publication = array(
      LANGUAGE_NONE => array(
        0 => array(
          'target_id' => $node->nid
        )
      )
    );

    //store versions informations into corresponding field ( field_publication_history )
    $source_list = gofast_cmis_webservice_item_get_versions($parent_publication_node->reference, true);
    $source_version = $source_list[0]->label;
    $existing_field_publication_history = array();
    $existing_field_publication_history[LANGUAGE_NONE][0]["value"] = json_encode(array($source_version => array("source_version" => $source_version , "published_version" => "1.0", "date" => time(), "creator" => $user->name)));

    $parent_publication_node->field_publication_history = $existing_field_publication_history;
    field_attach_update('node', $parent_publication_node);

  }

  gofast_cmis_purge_published_temp_file($options['file']->filepath);


  //used for fire the rule during node creation
  //see JIRA 2775
  $node = node_load($node->nid, NULL, TRUE);
  rules_invoke_event('node_insert',$node);

  node_access_acquire_grants($node);

  unset($_POST['prevent_automatic_multifilling']);
  global $cmis_as_publisher;
  $cmis_as_publisher = $options['publish_as_broadcaster'] === 1 ? TRUE : FALSE;
  gofast_cmis_automatic_multifilling($node);


  variable_del("cmis_creating_" . $item->properties['alfcmis:nodeRef']);
  return $node;
}

/**
 * This is the form that allow to remove a publication.
 * @param type $form
 * @param array $form_state
 * @return array the form
 */
function gofast_cmis_publication_delete_form($form, &$form_state) {
  $node = isset($form_state['build_info']['args'][0]->nid) ? $form_state['build_info']['args'][0] : FALSE;

  // These two submit handlers unpublish then remove link between node and publication
  $form['#submit'] = array(
    'gofast_ajax_node_unpublish',
    'gofast_cmis_publication_delete_form_submit'
  );

  $confirm_form = confirm_form(
          $form,
          t('Delete', array(), array('context' => 'gofast')) . ' '. $node->title,
          isset($_GET['destination']) ? $_GET['destination'] : 'node/' . $node->nid,
          t('Are you sure you want to delete the publication %title?', array('%title' => $node->title), array('context' => 'gofast:gofast_cmis')),
          t('Delete', array(), array('context' => 'gofast')),
          t('Cancel', array(), array('context' => 'gofast'))
  );
  $confirm_form['actions']['submit']['#attributes'] = array('class' => array('btn-success'));
  unset($confirm_form['actions']['cancel']);

  return  $confirm_form;
}

function gofast_cmis_publication_delete_form_submit($form, &$form_state) {
  $node = $form_state['build_info']['args'][0];
  if (isset($node->nid)) {
    gofast_cmis_publication_delete($node);
  }
  return TRUE;
}

/**
 * This function deletes a publication node. The unpublish is made with
 * gofast_ajax_node_unpublish form callback.
 * @param Object $node the node to unpublish
 */
function gofast_cmis_publication_delete($node) {
  $parent_publication_nid = gofast_cmis_get_publication_source($node);

  if ($parent_publication_nid !== null) {
    // Remove the publicated value on the parent node
    $parent_publication_node = node_load($parent_publication_nid);
    $parent_publication_node->{GOFAST_CMIS_PUBLICATION_FIELD}[LANGUAGE_NONE] = array();
    field_attach_update('node', $parent_publication_node);
  }
}

/**
 * This removes the temporary file created during the publication process.
 * @param type $filepath the file to remove.
 */
function gofast_cmis_purge_published_temp_file($filepath) {
  unlink($filepath);
}

/**
 * This function allows to create an alfresco_item document programmatically.
 * @param type $title
 * @param type $options
 * @return type
 */
function gofast_cmis_alfresco_item_create($title, $options = array()) {
  module_load_include('inc', 'node', 'node.pages');

  $form_state = array();

  // Merge in default options :
  $options += array(
    'author' => GOFAST_USER_ADMINISTRATOR_ID,
    'description' => '',
    'body' => '',
    'parent' => NULL
  );

  // Check author.
  if (!(is_object($options['author']) && $options['author']->uid)) {
    $options['author'] = $options['author'] && ($options['author'] = user_load($options['author'])) ? $options['author'] : user_load(GOFAST_USER_ADMINISTRATOR_ID);
    if ($options['author'] === FALSE) {
      watchdog('gofast_cmis', 'Cannot create alfresco_item node, no author provided', NULL, WATCHDOG_ERROR);
      return;
    }
  }

  $spaces = array();
  foreach ($options['parent_spaces'] as $parent_space) {
    $spaces[] = array('value' => intval($parent_space));
  }

  // Populate the fields shared by OG node bundles in node form. Fields that
  // are not populated here will take their default values.
  $form_state['values'] = array(
    'nid' => NULL,
    'vid' => NULL,
    'uid' => $options['author']->uid,
    'created' => time(),
    'type' => 'alfresco_item',
    'language' => $options['language'],
    'changed' => '',
    'title' => $title,
    'revision' => 0,
    'log' => '',
    'name' => $options['author']->name,
    'date' => '',
    'status' => NODE_PUBLISHED,
    'promote' => NODE_NOT_PROMOTED,
    'sticky' => NODE_NOT_STICKY,
    'filename' => $title,
    'body' => array(
      LANGUAGE_NONE => array(
        0 => array(
          'summary' => '',
          'value' => $options['body'],
          'format' => 'full_html'
        )
      )
    ),
    GOFAST_CMIS_LOCATIONS_FIELD => array(
      LANGUAGE_NONE => $options['locations']
    ),
    GOFAST_OG_CONTENT_MEMBERSHIP_FIELD => $spaces,
    'field_description' => array(
      LANGUAGE_NONE => array(
        0 => array(
          'value' => strval($options['description'])
        )
      )
    ),
    'comment' => '0',
    'op' => t('Save', array(), array('context' => 'gofast')),
  );

  $form_state['file'] = $options['file'];

  // Construct og node object
  $node = new stdClass();
  $node->is_new = TRUE;
  $node->type = 'alfresco_item';
  $node->language = $options['language'];
  $node->options = array();
  $node->promote = 0;
  $node->sticky = 0;
  $node->module = 'node';

  // Prepares the node object for being submitted (as a form argument). Add few
  // default values, and then invokes hook_prepare() on the node type module,
  // and hook_node_prepare() on all modules.
  node_object_prepare($node);

  // Since node_object_prepare() set the current global $user as the node author
  // we need to override this behavior to preserve the space manager preset.
  $node->uid = $options['author']->uid;
  $node->name = $options['author']->name;

  // Call the node_create form corresponding to $bundle (or content-type).
  drupal_form_submit("alfresco_item_node_form", $form_state, $node);
  $errors = form_get_errors();

  if ($errors) {
    return $errors;
  }
  else {
    // Do the related other stuff
    if (isset($options['parent_publication_id'])) {
      $parent_publication_node = node_load($options['parent_publication_id']);
      $parent_publication_node->field_publication = array(
        LANGUAGE_NONE => array(
          0 => array(
            'target_id' => $form_state['nid']
          )
        )
      );
      field_attach_update('node', $parent_publication_node);
    }
    return TRUE;
  }
}

function gofast_get_http_headers($url) {
  $full_url = strstr($url, 'http://localhost:8080') !== FALSE ? $url : 'http://localhost:8080' . $url;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $full_url);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, TRUE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $header = curl_exec($ch);
  $info = curl_getinfo($ch, CURLINFO_HTTP_CODE);
  curl_close($ch);
  return intval($info);
}

function gofast_get_onlyoffice_http_file($url) {
  $full_url = strstr($url, XMPP_DOMAIN) !== FALSE ? $url : XMPP_DOMAIN . $url;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $full_url);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_PROXY, '');
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, FALSE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $file = curl_exec($ch);
  curl_close($ch);
  return $file;
}

function gofast_get_http_file($url) {
  $full_url = strstr($url, 'http://localhost:8080') !== FALSE ? $url : 'http://localhost:8080' . $url;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $full_url);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, FALSE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $file = curl_exec($ch);
  curl_close($ch);
  return $file;
}

/*
 * Function used to automatically create the path $publication_path, into the Reference group
 */
function gofast_cmis_publication_force_create_missing_path($publication_path){
    //we explode the path into array
    $array_path = explode("/", $publication_path);

    //we reformat a little the array
    $formatted_array_path = array();
    $previous_path = "";

    if(count($array_path) > 0){
        foreach($array_path as $my_path){
            if($my_path !== ""){
                $formatted_array_path[] = $previous_path."/".$my_path;
                $previous_path = $previous_path."/".$my_path;
            }
        }
    }


    //foreach level of this path, we check if the folder exists into the Reference group
    if(count($formatted_array_path) > 0){
        $repositoryId=gofast_cmis_get_repository();
        $previous_path = "";
        foreach($formatted_array_path as $my_new_path){
            $publication_path_object=cmisapi_getObjectByPath($repositoryId,rawurlencode($my_new_path));
            if(!isset($publication_path_object->properties['cmis:objectId'])){
                 //if not, we create it
                $parent_folder_object = cmisapi_getObjectByPath($repositoryId,rawurlencode($previous_path));

                $new_folder_name = explode("/", $my_new_path);
                $new_folder_name =  end($new_folder_name);
                if(isset($parent_folder_object->properties['cmis:objectId'])){
                     cmisapi_createFolder($repositoryId, $parent_folder_object->properties['cmis:objectId'], $new_folder_name);
                }
            }
             //allow to easily get the parent folder
            $previous_path = $my_new_path;
        }
    }
}

/*
 * Function for testing if the publication path exists or not
 */
function gofast_cmis_publication_check_existing_publication_location($path){
    $repositoryId= gofast_cmis_get_repository();
    $publication_path_object=cmisapi_getObjectByPath($repositoryId,rawurlencode($path));

    if(isset($publication_path_object->properties['cmis:objectId'])){
        return true;
    }else{
        return false;
    }
}
