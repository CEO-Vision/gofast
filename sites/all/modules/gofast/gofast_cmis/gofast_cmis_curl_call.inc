<?php

/**
 * Locations which will be loaded from cache and recomputed again by the cron every hour.
 * @warning The entire trees will be loaded from cache **without taking into account user permissions**.
 * @warning This cache will work only when loading groups and folders only.
 */
define('GOFAST_CMIS_CRON_CACHED_LOCATION_TREES', variable_get("gofast_cmis_cron_cached_location_trees", []));

define("LO_VERSION", "7.6");

/**
 * This constant has a list of supported file extensions for the
 * document preview feature. A document with an extension that is NOT in this 
 * constant will not be previewed.
 * @see https://api.onlyoffice.com/editors/conversionapi#request
 * 
 * @type array
 */
const SUPPORTED_PREVIEW_EXTENSIONS = ['csv', 'et', 'ett', 'fods', 'ods', 'ots', 'sxc', 'xls', 'xlsb', 'xlsm', 'xlsx', 'xlt', 'xltm', 'xltx', 'xml', 'dps', 'dpt', 'fodp', 'odp', 'otp', 'odg', 'pot', 'potm', 'potx', 'pps', 'ppsm', 'ppsx', 'ppt', 'pptm', 'pptx', 'sxi', 'djvu', 'doc', 'docm', 'docx', 'docxf', 'dot', 'dotm', 'dotx', 'epub', 'fb2', 'fodt', 'htm', 'html', 'mht', 'mhtml', 'odt', 'ott', 'oxps', 'pdf', 'rtf', 'stw', 'sxw', 'txt', 'wps', 'wpt', 'xps', 'xml'];

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to update node properties.
 * @param string $reference the node reference
 * @param array $options this is an associative array that should contain node properties attributes only.
 * @return boolean true if succeeded, false otherwise
 */
function gofast_cmis_webservice_item_update_properties($reference, $options, $asAdmin = TRUE) {

  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }

  $url_parameters = http_build_query($options);
  $url = "http://localhost:8080/alfresco/service/updateNodeProperties?reference=" . $reference . "&" . $url_parameters;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  if($asAdmin == TRUE){
    curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  }else{
    global $user;
    $username = $user->name;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url = $url . "&alf_ticket=" . $ticket;
  }
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = json_decode($buf);

  return $result->status === 'OK' ? TRUE : FALSE;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to update onlyoffice hash.
 * @param string $reference the node reference.
 * @return boolean true to clear, false otherwise
 */
function gofast_cmis_webservice_item_onlyoffice_hash($reference, $clear = null, $force = null, $just_get = null) {

  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }

  if($clear == false){
      $clear = null;
  }

  $url = "http://localhost:8080/alfresco/service/updateOnlyofficeHash?reference=" . $reference . "&clear=" . $clear . "&force=" . $force . "&just_get=" . $just_get . "&timestamp=" . time();
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());

  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);
  $output = trim(strip_tags($buffer));
  return $output;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to update node aspects.
 * @param string $reference the node reference
 * @return boolean true if succeeded, false otherwise
 */
function gofast_cmis_webservice_item_update_aspects($reference) {

  if (strpos($reference, "archive") === false) {
    $reference = "archive://SpacesStore/" . $reference;
  }
  $url = "http://localhost:8080/alfresco/service/set/aspects?reference=" . $reference;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = json_decode($buf);

  return $result->status === 'OK' ? TRUE : FALSE;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to get a ticket that we store later on drupal user variable.
 * @param type $username
 * @param type $password
 * @return boolean
 */
function gofast_cmis_webservice_generate_alfresco_ticket($username) {
  if(empty($username)){
      return false;
  }
  $ch = curl_init();

  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/impersonate?username=" . rawurlencode($username));
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);

  $result = $buffer;
  if (strpos($result, "TICKET_") === false) {
    return false;
  }

  return $result;
}

/**
 * @package gofast_cmis
 * this function calls the Alfresco webservice created by CEO-Vision to get all items in the given folder ($reference)
 * only items the user has access to will be returned
 *
 * @global type $user
 * @param string $reference
 * @param string filter_documents "documents" to get only documents, "folders"
 * to get only folders and "groups" to get only groups, "templates" to get a
 * list of all available templates for the user queryring. leave empty for all
 * or set "all"
 * @return array
 */
function gofast_cmis_webservice_item_get_descendants($reference, $param_documents = "all", $async = false, $as_admin = FALSE, $origine = NULL) {
  
  global $user;
  
  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }

  $cache_again = isset($_POST["force_caching"]) ? TRUE : FALSE;
  // The location is supposed to be loaded from cache, and we are not force-regenerating its cache
  if (!$cache_again && in_array($reference, GOFAST_CMIS_CRON_CACHED_LOCATION_TREES) && ($param_documents == "groupsfolders" || $param_documents == "folders")) {
    $locations = cache_get("gofast_cmis_cron_cached_location_" . $reference);
    if ($locations->data) {
      return $locations->data;
    } else {
      // Nothing found in cache: result of the request will be cached and we want to cache everything
      $cache_again = TRUE;
      $as_admin = TRUE;
    }
  }

  if($async == true){
      $restrictdepth= "true";
  }else{
      $restrictdepth= "false";
  }

  $url = "http://localhost:8080/alfresco/service/get/descendants/?reference=" . $reference . "&type=" . $param_documents . "&restrictdepth=".$restrictdepth;

  $ch = curl_init();
  if($as_admin == false){
    $username = $user->name;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url = $url . "&alf_ticket=" . $ticket;
  }else{
    $username = "admin";
    $password = gofast_get_admin_pwd();
    curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
  }
  if($origine != NULL){
    
      $url = $url . "&origine=" . rawurlencode($origine);
  }
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_URL, $url);

  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);
  $result = json_decode($buf);
  $descendants_final = array();
  
  if (!empty($result)) {
    foreach ($result as $key => $descendant) {
      if (in_array($param_documents, array("documents", "templates"))) {
        $descendants_final[$descendant->id] = $descendant;
      }
      else {
        $mydescendant = str_replace("/webdav", "", $descendant->url);
        $mydescendant = rawurldecode($mydescendant);
          $descendants_final[trim($mydescendant)] = isset($descendant->nid) ? $descendant->nid : trim($mydescendant);
      }
    }
    uksort($descendants_final, function($a, $b) {
      return strcasecmp($a, $b);
    });
  }

  // If we got there, it means the item cache is supposed to be regenerated, so we try to cache it again
  if ($cache_again) {
    cache_set("gofast_cmis_cron_cached_location_" . $reference, $descendants_final);
  }
  return $descendants_final;
}

/**
 * @package gofast_cmis
 * use Alfresco API to get descendants of given folder ($reference)
 * it can't differentiate folders from groups and documents from templates
 * but is much faster than using the webservice
 */
function gofast_cmis_alfresco_api_get_descendants($reference, $target_documents = "all", $as_admin = FALSE, $recursive = FALSE, $permissions = FALSE) {
  $curl = curl_init();
  $url_parameters = "?include=properties,path";
  if ($permissions) {
    $url_parameters .= ",allowableOperations";
  }
  if (strpos($target_documents, "folders") !== FALSE) {
    $url_parameters .= "&where=(isFolder=true)";
  }
  if ($target_documents == "documents") {
    $url_parameters .= "&where=(isFile=true)";
  }
  $url_parameters .= "&maxItems=1000000000";
  $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/".gofast_cmis_get_raw_item_id($reference)."/children" . $url_parameters;
  if($as_admin == TRUE){
    curl_setopt($curl, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  } else {
    global $user;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE) {
        $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url .= "&alf_ticket=".$ticket."";
  }
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "GET");
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  $result = curl_exec($curl);
  $results = [];
  foreach (json_decode($result)->list->entries as $entry) {
    $item = new stdClass();
    if ($permissions && isset($entry->entry->allowableOperations)) {
      $item->canUpdate = in_array("update", $entry->entry->allowableOperations);
    }
    $item->path = $entry->entry->path->name;
    $item->name = $entry->entry->name;
    $item->properties = $entry->entry->properties;
    $item->id = $entry->entry->id;
    if ($target_documents == "all") {
      $item->isFile = $entry->entry->isFile;
      $item->isFolder = $entry->entry->isFolder;
    }
    if ($recursive && $item->isFolder) {
      $item->children = gofast_cmis_alfresco_api_get_descendants($item->id, $target_documents, $as_admin, $recursive, $permissions);
    }
    $results[] = $item;
  }
  return $results;
}

/**
 * @package gofast_cmis
 * use Alfresco API to insert some item: faster and allow custom properties at insert time (which is not the case with cmis)
 */
function gofast_cmis_alfresco_api_insert_item($parent_item_id, $title, $content, $properties = array(), $asAdmin = FALSE) {
  // FIRST REQUEST: CREATE EMPTY FILE
  $curl = curl_init();
  $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/".gofast_cmis_get_raw_item_id($parent_item_id)."/children";
  if($asAdmin == TRUE){
    curl_setopt($curl, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  } else {
    global $user;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE) {
      $ticket = gofast_cmis_get_user_ticket();
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url .= "?alf_ticket=".$ticket."";
  }
  $post_fields = [
    "name" => $title,
    "nodeType" => "cm:content",
    "properties" => $properties,
  ];
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($post_fields));
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  $buffer = curl_exec($curl);
  curl_close($curl);
  $result = json_decode($buffer);
  if (!isset($result->entry->id)) {
    return FALSE;
  }

  // SECOND REQUEST: PUT CONTENT INTO THE EMPTY FILE
  $inserted_id = $result->entry->id;
  $curl = curl_init();
  $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/" . gofast_cmis_get_raw_item_id($inserted_id) . "/content";
  if($asAdmin == TRUE){
    curl_setopt($curl, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  } else {
    global $user;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE) {
      $ticket = gofast_cmis_get_user_ticket();
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url .= "?alf_ticket=".$ticket.""; 
  }

  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/octet-stream'));
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'PUT');
  curl_setopt($curl, CURLOPT_POSTFIELDS, $content);

  $buffer = curl_exec($curl);
  $result = json_decode($buffer);
  curl_close($curl);

  return $inserted_id;
}

/**
 * @package gofast_cmis
 * use Alfresco API to move (faster) given item id ($item_id) to destination folder with reference $parent_ref
 */
function gofast_cmis_alfresco_api_move_item($item_id, $parent_ref, $asAdmin = TRUE) {
  $curl = curl_init();
  $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/".gofast_cmis_get_raw_item_id($item_id)."/move";
  if($asAdmin == TRUE){
    curl_setopt($curl, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  } else {
    global $user;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE) {
    $ticket = gofast_cmis_get_user_ticket();
        $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $url .= "&alf_ticket=".$ticket."";
  }
  $target_folder = [
      "targetParentId" => gofast_cmis_get_raw_item_id($parent_ref)
    ];
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "POST");
  curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($target_folder));
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  $result = curl_exec($curl);
  curl_close($curl);
  return $result;
}

function gofast_cmis_webservice_preview_modal(){
    $nid = $_GET["nid"];
    if(!isset($nid)){
        return;
    }

    print $nid;
}


/**
 * @package gofast_cmis
 * This function tries to get / generate a preview for a given node reference.
 * @param int $node_id the node id
 */
function gofast_cmis_webservice_item_generate_preview($node_id, $readfile = FALSE) {

  // If the file is not generated (pdf/jpg...etc.)
  $node = node_load($node_id);
  $reference = gofast_cmis_node_get_item_id($node);
  $ticket = gofast_cmis_get_user_ticket();

  if ($readfile && isset($_GET["only_print"])) {
    $content_type = gofast_get_mime_content_type($node->title);
    header('Content-Type: ' . $content_type);
    header("Content-Transfer-Encoding: Binary");
    header("Content-disposition: inline; filename=\"" . $node->title . "\"");
    $full_doc_link = "http://localhost:8080/alfresco/service/api/node/workspace/SpacesStore/" . gofast_cmis_get_raw_item_id($reference) . "/content?alf_ticket=" . $ticket;
    readfile($full_doc_link);
    exit();
  }

  $format_tid = $node->{'field_format'}[LANGUAGE_NONE][0]['tid'];
  $not_alfresco_generated = in_array($format_tid, array(
    gofast_taxonomy_get_taxo_id_from_extension("pdf"),
    gofast_taxonomy_get_taxo_id_from_extension("jpg"),
    gofast_taxonomy_get_taxo_id_from_extension("pdf_image")
  ));

  if($not_alfresco_generated) {
    if($format_tid === gofast_taxonomy_get_taxo_id_from_extension("pdf") || $format_tid === gofast_taxonomy_get_taxo_id_from_extension("pdf_image")) {
      $type = 'PDF';
    } else {
      $type = 'other';
    }
    if(!$readfile){
      return json_encode(array('status' => 'OK', 'type' => $type, 'link' => gofast_cmis_node_get_pdf_link($node), "title" => $node->title));
    }
  }

  $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
  $reference = gofast_cmis_node_get_item_id(node_load($node_id));
  if (in_array($reference, array_flip($excluded_previews))) {
    unset($excluded_previews[$reference]);
    variable_set("gofast_soffice_preview_exclude", $excluded_previews);
  }

  $url = "http://localhost:8080/alfresco/service/get/preview/?reference=" . rawurlencode($reference);

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url);
  $buffer = curl_exec($ch);
  $result = strip_tags($buffer);

  $result_object = json_decode($result);
  if($result_object->value == null){
      if(!gofast_get_soffice_status()){
          $result_object->value = "soffice_down";
          $result = json_encode($result_object);
      }
  }
  
  if($readfile){
    gofast_cmis_webservice_item_generate_onlyoffice_preview($node_id, true);
  }else{
    return $result;
  }
}

function gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id){
    //split $cache_doc_id with _, to separate alfresco_item and timestamp
    $affixes = explode("_", $cache_doc_id);
    $prefix = $affixes[0];
    $suffix = $affixes[1];
  
    //if the preview has not been generated by OO: we already have a node id and the node has not been converted into pdf
    if ($prefix == "notconverted") {
      $node = node_load($suffix);
      $extension = strtolower(gofast_cmis_node_get_extension($node));
      $mimetype = gofast_cmis_get_mimetype_extension_match_array()[$extension];
      $node_title = $node->title;
    } else {
      $node = node_load(gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$prefix));
      $extension = strtolower(gofast_cmis_node_get_extension($node));
      $mimetype = "application/pdf";
      $node_title = str_replace($extension,'pdf',$node->title);
    }
    if(!in_array($extension, SUPPORTED_PREVIEW_EXTENSIONS))
      exit;
    
    if(isset($node->nid)){
        $has_access = node_access('view', $node);
        if (!$has_access && isset($_GET["caseId"])) {
          $case_id = gofast_xss_clean($_GET["caseId"]);
          $has_access = gofast_workflows_has_user_active_task_in_workflow($case_id, 0, $node->nid);
        }
        if($has_access){
            $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
             if(file_exists($filename)){
                header('Content-Type: ' . $mimetype);
                header("Content-Transfer-Encoding: Binary");
                header("Content-disposition: inline; filename=\"" . $node_title . "\"");
                readfile($filename);
             }

        }
    }
}

/**
 * @package gofast_cmis
 * This function tries to get / generate an onlyoffice preview for a given node reference.
 * @param int $node_id the node id
 */
function gofast_cmis_webservice_item_generate_eml_preview($node_id, $print_doc = FALSE) {
    global $base_url;
    // If the file is not generated (pdf/jpg...etc.)
    $node = node_load($node_id);    
    $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
    $reference = gofast_cmis_node_get_item_id(node_load($node_id));
    if (in_array($reference, array_flip($excluded_previews))) {
      unset($excluded_previews[$reference]);
      variable_set("gofast_soffice_preview_exclude", $excluded_previews);
    }
  
      ## condition if onlyoffice answer
      ## call onlyoffice pdf transformer
      // Document's last modification date
      $doc_last_modification_date = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:lastModificationDate'];
  
      $doc_raw_item_id =  gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
  
      // Document id
      $doc_id = $doc_raw_item_id . '_' . GenerateRevisionId($doc_last_modification_date);
  
      //First, check if the cache file already exists
      //cache doc name is composed of alfresco item id then modification timestamp
      $cache_doc_id = $doc_raw_item_id . '_' . strtotime($doc_last_modification_date);
      if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id)){
          //cache file already exists ( the name contains timestamp so we are sur it's related to this version)
          if($print_doc){
            gofast_cmis_webservice_item_get_eml_preview($cache_doc_id);
            return;
          }else{
            return json_encode(array('EndConvert' => 'True' , 'status' => 'OK', 'FileUrl' => $base_url.'/gofast/get_onlyoffice_preview/'.$cache_doc_id));
          }
      }
  
      gofast_delete_oo_previews($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
      
      require_once('/var/www/d7/sites/all/libraries/mimedecode/mimeDecode.php');
      $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
    
      ini_set('memory_limit', '512MB');
      
      $file_content = gofast_cmis_item_get_content($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
    
      $file = fopen($filename, "w");
      fwrite($file, $file_content);
      fclose($file);
    
      $params = array(
        'input' => $file_content,
        'crlf' => "\r\n",
        'include_bodies' => TRUE,
        'decode_headers' => TRUE,
        'decode_bodies' => FALSE
      );
      
       //si c'est un .msg
      $cmisobject = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
      $mimetype = $cmisobject->properties['cmis:contentStreamMimeType'];
      $mail_mimedecode = new Mail_mimeDecode($file_content);
      $mail = $mail_mimedecode->decode($params);
    
    
      /* parse the message and return a mime message resource */
      $mime = mailparse_msg_parse_file($filename);
      /* return an array of message parts - this contsists of the names of the parts
       * only */
      $struct = mailparse_msg_get_structure($mime);
    
      /* on recupere la liste des sections du mail */
      $list_sections = array();
      $list_sections_charset = array();
      foreach ($struct as $st) {
    
        $section = mailparse_msg_get_part($mime, $st);
        $info = mailparse_msg_get_part_data($section);
        $list_sections[$st] = $info["content-type"];
        $list_sections_charset[$st] = $info["charset"];
      }
    
    
      //on choisit la meilleur section a afficher
      $showpart_html = array_search("text/html", $list_sections);
      $showpart_text = array_search("text/plain", $list_sections);
      if ($mimetype == "application/vnd.ms-outlook") {
        //je le transforme en .eml
        $doc_path = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
        $command = "java -jar " . GOFAST_TIKA_PATH . " -x ".$doc_path;
          try {
            ini_set('memory_limit', '-1');
            exec($command, $result);
          }
          catch (Exception $e) {

          }
          $result = implode('', $result);
        }elseif ($showpart_html !== false) {
        //partie html
        $sec = mailparse_msg_get_part($mime, $showpart_html);
        $info = mailparse_msg_get_part_data($sec);
    
        $contents = mailparse_msg_extract_part_file($sec, $filename, NULL);
        $content = $contents;
        $content = str_replace("charset=UTF-8", "", $content);
        $content = str_replace("charset=utf-8", "", $content);
        $result =  mb_convert_encoding($content, "UTF-8", $info["charset"]);
      }
      elseif ($showpart_text !== false) {
        //partie texte
        $sec = mailparse_msg_get_part($mime, $showpart_text);
        $contents = mailparse_msg_extract_part_file($sec, $filename, NULL);
        $content = nl2br($contents);
        $result =  mb_convert_encoding($content, "UTF-8", mb_detect_encoding($content, "UTF-8, ISO-8859-1, ISO-8859-15", true));
      }
      else {
        //pas de partie exploitable          
      }
      
      $file = fopen($filename, "w");
      fwrite($file, $result);
      fclose($file);
      
      if($print_doc){
        gofast_cmis_webservice_item_get_eml_preview($cache_doc_id);
      }else{
        return $filename;
      }
  }
  
  /**
 * @package gofast_cmis
 * This function generates an SVG preview for a DWG document.
 * @param int $node_id the node id
 */
function gofast_cmis_webservice_item_generate_dwg_preview($node_id) {
  global $base_url;
  
  $node = node_load($node_id);    
  $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
  
  $reference = gofast_cmis_node_get_item_id(node_load($node_id));
  if (in_array($reference, array_flip($excluded_previews))) {
    unset($excluded_previews[$reference]);
    variable_set("gofast_soffice_preview_exclude", $excluded_previews);
  }

  // Get document's last modification date and raw alfresco id
  $doc_last_modification_date = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:lastModificationDate'];
  $doc_raw_item_id =  gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
  
  //First, check if the cache file already exists
  //cache doc name is composed of alfresco item id then modification timestamp
  $cache_doc_id = $doc_raw_item_id . '_' . strtotime($doc_last_modification_date);
  if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id)){
      if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id.".dwg")){
        //Generation in progress
        gofast_cmis_webservice_item_get_dwg_preview($cache_doc_id, TRUE);
      }else{
        //cache file already exists ( the name contains timestamp so we are sur it's related to this version)
        gofast_cmis_webservice_item_get_dwg_preview($cache_doc_id);
      }
      return;
  }
  
  //Generate the preview
  $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
  
  ini_set('memory_limit', '512MB');
  
  $file_content = gofast_cmis_item_get_content($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
  
  $file = fopen($filename . ".dwg", "w");
  fwrite($file, $file_content);
  fclose($file);

  //Print generation information to the user
  gofast_cmis_webservice_item_get_dwg_preview($cache_doc_id, TRUE);
  fastcgi_finish_request();
  
  //Send our dwg content to the decoder, then delete the initial file
  shell_exec('/opt/qcadcam/dwg2svg -f -equal-margins=0 -a -s 1:1 -min-lineweight=15mm -g -embed-images -platform offscreen -outfile='.$filename.' "'.$filename.'.dwg"');
  unlink($filename.'.dwg');
}
  
  function gofast_cmis_webservice_item_get_eml_preview($cache_doc_id){
    //split $cache_doc_id with _, to separate alfresco_item and timestamp
     $alfresco_item = explode("_", $cache_doc_id)[0];
     $timestamp = explode("_", $cache_doc_id)[1];
 
     //get node from $alfresco_item
     $node = node_load(gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$alfresco_item));
     
     $extension = strtolower(gofast_cmis_node_get_extension($node));
     $node_title_pdf = str_replace($extension,'pdf',$node->title);
     
     if(isset($node->nid)){
         if(node_access('view', $node)){
             $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
              if(file_exists($filename)){
                 header('Content-Type: text/html');
                 header("Content-Transfer-Encoding: Binary");
                 header("Content-disposition: inline; filename=\"" . $node_title_pdf . "\"");
                 readfile($filename);
              }
 
         }
     }
 }
 
 function gofast_cmis_webservice_item_get_dwg_preview($cache_doc_id, $generating = FALSE){
  //split $cache_doc_id with _, to separate alfresco_item and timestamp
   $alfresco_item = explode("_", $cache_doc_id)[0];
   $timestamp = explode("_", $cache_doc_id)[1];

   //get node from $alfresco_item
   $node = node_load(gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$alfresco_item));
   
   $extension = strtolower(gofast_cmis_node_get_extension($node));
   $node_title_pdf = str_replace($extension,'swg',$node->title);
   
   if(isset($node->nid)){
       if(node_access('view', $node)){
           if($generating){
              header('Content-Type: text/html');
              header("Content-Transfer-Encoding: Binary");
              header("Content-disposition: inline; filename=\"" . $node_title_pdf . "\"");
              //Inform the user that the preview is in progress
              print theme('gofast_cmis_preview_dwg', ['generating' => TRUE]);
              return;
            }
            
            $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
            if(file_exists($filename)){
              header('Content-Type: text/html');
              header("Content-Transfer-Encoding: Binary");
              header("Content-disposition: inline; filename=\"" . $node_title_pdf . "\"");
              
              // Send the file with Enabled SVG zoom JS feature 
              print theme('gofast_cmis_preview_dwg', ['header' => TRUE]);
              readfile($filename);
              print theme('gofast_cmis_preview_dwg', ['footer' => TRUE]);
            }
       }
   }
}

/**
 * @package gofast_cmis
 * In case we need to display a preview for a user which doesn't have access to the document
 * and the document is not convertible by OO, we can use this function to make a temporary copy.
 * Making a copy avoid exposing an alfresco ticket to unauthorized user.
 * @param int $node_id
 * @param string $alfresco_url the url as it is
 * @return string $url a link to the preview usable at least for the next 30mn
 *
 */
function gofast_cmis_webservice_item_generate_notconverted_preview($node_id, $alfresco_url) {
  global $base_url;
  $doc_id = "notconverted_" . $node_id;
  $file = fopen("/var/www/d7/sites/default/files/oo_previews/" . $doc_id, "w+");
  fwrite($file, file_get_contents($base_url . $alfresco_url));
  fclose($file);
  $url  = $base_url.'/gofast/get_onlyoffice_preview/'.$doc_id;
  return $url;
}


/**
 * Use OO ConvertService to convert given node found in given URI to target output type.
 * $doc_id is not mandatory, but let you target an existing OO cached document if needed
 * @return $xml the XML-encoded response
 */
function gofast_cmis_convert_document($node, $uri, $outputtype, $doc_id = NULL) {
  //Body
  $post_fields = array(
    'filetype' => gofast_cmis_node_get_extension($node),
    'key' => $doc_id ?? gofast_generate_uuid(),
    "outputtype" => $outputtype,
    "title" => $node->title,
    "url" => $uri,
    "spreadsheetLayout" => []
  );

  //API RUL
  $url = DOC_SERV_CONVERTER_URL;
  $url = str_replace("https://", "https://internal-", $url);
  //Initiate cURL.
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  //Tell cURL that we want to send a POST request.
  //Set the content type to application/json
  curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
  curl_setopt($ch, CURLOPT_POST, 1);
  //Attach our encoded JSON string to the POST fields.
  curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($post_fields));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_PROXY, '');
  curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
  curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
  //Execute the request
  $exec = curl_exec($ch);
  $xml = simplexml_load_string($exec);

  //Return response
  return $xml;
}

/**
 * @package gofast_cmis
 * This function tries to get / generate an onlyoffice preview for a given node reference.
 * @param int $node_id the node id
 */
function gofast_cmis_webservice_item_generate_onlyoffice_preview($node_id, $print_doc = FALSE, $as_admin = FALSE) {
  global $base_url;
  // If the file is not generated (pdf/jpg...etc.)
  $node = node_load($node_id);
  $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
  $reference = gofast_cmis_node_get_item_id($node);
  if (in_array($reference, array_flip($excluded_previews))) {
    unset($excluded_previews[$reference]);
    variable_set("gofast_soffice_preview_exclude", $excluded_previews);
  }

    ## condition if onlyoffice answer
    ## call onlyoffice pdf transformer
    // Document's last modification date
    $doc_last_modification_date = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:lastModificationDate'];

    $doc_raw_item_id =  gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);

    // Document id
    $doc_id = $doc_raw_item_id . '_' . GenerateRevisionId($doc_last_modification_date);

    //First, check if the cache file already exists
    //cache doc name is composed of alfresco item id then modification timestamp
    $cache_doc_id = $doc_raw_item_id . '_' . strtotime($doc_last_modification_date);
    if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id)){
        //cache file already exists ( the name contains timestamp so we are sur it's related to this version)
        if($print_doc){
          gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id);
          return;
        }else{
          return json_encode(array('EndConvert' => 'True' , 'status' => 'OK', 'FileUrl' => $base_url.'/gofast/get_onlyoffice_preview/'.$cache_doc_id));
        }
    }

    gofast_delete_oo_previews($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);

    if ($as_admin) {
      $ticket = gofast_cmis_webservice_generate_alfresco_ticket("admin");
    } else {
      global $user;
      $ticket = gofast_cmis_webservice_generate_alfresco_ticket($user->name);
    }

    ## url
    $url_alfresco_content = $base_url . "/alfresco/s/api/node/content/" . str_replace(":/","",$reference) . "?alf_ticket=" . $ticket;

    $xml = gofast_cmis_convert_document($node, $url_alfresco_content, "pdf", $doc_id);
    $success = json_decode(json_encode($xml))->EndConvert;
    $file_url = json_decode(json_encode($xml))->FileUrl;

    ## if the pdf has been correctly generated, download and store the file into GF temp file
    if($success == "True"){
        //Download and store the pdf
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $file_url);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($ch, CURLOPT_PROXY, '');
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        $exec = curl_exec($ch);

        $file = fopen("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id, "w+");
        fwrite($file, $exec);
        fclose($file);
        $xml->FileUrl = $base_url.'/gofast/get_onlyoffice_preview/'.$cache_doc_id;
    }
    
    if($print_doc){
      gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id);
    }else{
      $result = json_encode($xml);
      return $result;
    }
}



/**
 * @package gofast_cmis
 * This function tries to get / generate an soffice preview for a given node reference.
 * @param int $node_id the node id
 */
function gofast_cmis_webservice_item_generate_soffice_preview($node_id, $print_doc = FALSE) {
    global $base_url;
    // If the file is not generated (pdf/jpg...etc.)
    $node = node_load($node_id);    
    $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
    $reference = gofast_cmis_node_get_item_id(node_load($node_id));
    if (in_array($reference, array_flip($excluded_previews))) {
      unset($excluded_previews[$reference]);
      variable_set("gofast_soffice_preview_exclude", $excluded_previews);
    }
  
      ## condition if onlyoffice answer
      ## call onlyoffice pdf transformer
      // Document's last modification date
      $doc_last_modification_date = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:lastModificationDate'];
  
      $doc_raw_item_id =  gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
  
      // Document id
      $doc_id = $doc_raw_item_id . '_' . GenerateRevisionId($doc_last_modification_date);
  
      //First, check if the cache file already exists
      //cache doc name is composed of alfresco item id then modification timestamp
      $cache_doc_id = $doc_raw_item_id . '_' . strtotime($doc_last_modification_date);
      if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id)){
          //cache file already exists ( the name contains timestamp so we are sur it's related to this version)
          if($print_doc){
            gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id);
            return;
          }else{
            return json_encode(array('EndConvert' => 'True' , 'status' => 'OK', 'FileUrl' => $base_url.'/gofast/get_onlyoffice_preview/'.$cache_doc_id));
          }
      }
  
      gofast_delete_oo_previews($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']);
  
       //Convert PDF with soffice
      putenv('PATH=/usr/local/bin:/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/sbin');
      $filepath = "/var/www/d7/sites/default/files/oo_previews";
      $temp_filename = "/var/www/d7/sites/default/files/swf/" . $cache_doc_id;
          
      global $user;
      $alfresco_ticket = gofast_cmis_retrieve_and_store_ticket($user);
      $object = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'], TRUE);
      $link = $object->links["edit-media"];
      $ddl_link = $link .'&alf_ticket='.$alfresco_ticket;
      //Download and add the file to the archive
      $return = shell_exec("wget -O \"$temp_filename\" \"$ddl_link\"");
      $return = shell_exec("libreoffice".LO_VERSION." --headless --convert-to pdf " . $temp_filename . " --outdir ".$filepath);
     
      shell_exec("mv ".$filepath."/".$cache_doc_id.".pdf ".$filepath."/".$cache_doc_id);
    
      unlink($temp_filename);
      if($print_doc){
        gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id);
      }else{
        return $filepath."/".$cache_doc_id;
      }
  }

/**
 * @package gofast_cmis
 * This method force the permissions for a folder in remote store.
 * fonction qui assigne ou réassigne (en clair qui remet à jour) les permissions appliqués sur le dossier Alfresco d'un groupe ou sous groups (ou orga ou sous orga)
 *
 * @param type $node
 */
function gofast_cmis_webservice_space_assign_permissions($node) {
  //$subgroup = (false === gofast_og_get_parent($node)) ? "false" : "true";
  $id_folder = rawurlencode(gofast_cmis_node_get_item_id($node));

  // If the node is private space or if the node group / orga is public or private. Default is private
  $group_type = "og_private";
  if (gofast_og_is_user_private_space($node)) {
    $group_type = "private_space";
  }
  else {
    if (gofast_og_is_space($node, false)) {
      if (gofast_og_is_root_space($node)) {
        $group_type = "root_space";
      }
      else {
        $group_type = "og_private";
      }
    }
  }
  $unique_name = rawurlencode(str_replace("\,", ",", gofast_ldap_space_cn($node)));
  //on appel l'url du script alfresco qui attribue les droits sur un dossier
  //voir scripts setPermissionSubgroups.get.*
  //folder correpsond a la reference (id) du dossier alfresco
  //subgroup est une chaine qui vaut "true" si c'est un sous groupe ou sous orga et "false" si c'est un group/orga de premier niveau
  //unique_name correspond au nom unique du groupe utilisé dans ldap (par exemple pour un groupe qui s'appel "mon groupe" et dont le noeud est le 50, ce nom sera "mon groupe_#50")
  //cela sert a avoir une unicité au niveau ldap

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  $url = "http://localhost:8080/alfresco/service/set/subfolder/permission/?nodeRef=" . $id_folder . "&unique_name=" . $unique_name . "&node_type=" . $group_type;
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  //watchdog("CURL CALL - SET PERMISSIONS SUBFOLDER", $url);
  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);
  $result = json_decode($buf);
  return $result;
}

/**
 * @package gofast_cmis
 * This method force the permissions for a folder in remote store.
 * fonction qui assigne ou réassigne (en clair qui remet à jour) les permissions appliqués sur le dossier Alfresco d'un dossier
 *
 * @param type $folder_reference
 */
function gofast_cmis_webservice_folder_assign_permissions($folder_reference,$unique_name,$group_type) {
  //on appel l'url du script alfresco qui attribue les droits sur un dossier
  //voir scripts setPermissionSubgroups.get.*
  //folder correpsond a la reference (id) du dossier alfresco
  //subgroup est une chaine qui vaut "true" si c'est un sous groupe ou sous orga et "false" si c'est un group/orga de premier niveau
  //unique_name correspond au nom unique du groupe utilisé dans ldap (par exemple pour un groupe qui s'appel "mon groupe" et dont le noeud est le 50, ce nom sera "mon groupe_#50")
  //cela sert a avoir une unicité au niveau ldap
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  $url = "http://localhost:8080/alfresco/service/set/subfolder/permission/?nodeRef=" . $folder_reference . "&unique_name=" . $unique_name . "&node_type=" . $group_type;
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  //watchdog("CURL CALL - SET PERMISSIONS SUBFOLDER", $url);
  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);
  $result = json_decode($buf);
  return $result;
}

/**
 * @package gofast_cmis
 * This function update a folder and set write permission for a given reference and username.
 * If the $reset is set to TRUE, removed the permission for the given username and reference.
 * @param int $reference the remote reference id of the node to update
 * @param string $username the username to allow or deny
 * @param boolean $reset FALSE to allow the user, TRUE to remove user permission. Default to FALSE.
 */
function gofast_cmis_webservice_item_set_permission($reference, $username, $reset=FALSE) {

  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }

  $reset_val = $reset ? '&reset=true' : '';

  $url = "http://localhost:8080/alfresco/service/set/folder/permission/?reference=" . rawurlencode($reference) . "&username=" . $username . $reset_val;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url);
  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);
  $result = json_decode($buf);
  return $result;
}

/**
 * @package gofast_cmis
 * This function forces the synchronization between alfresco and ldap and should
 * be run every time we update the groups before the setPermissions webscript.
 */
function gofast_cmis_webservice_force_alfresco_ldap_synch($full = false) {
    if($full == false){
        //if full = false, just execute the classic sync ( like it is each minute into the cron.). It will execute a differential synch
        $url = "http://localhost:8080/alfresco/service/triggerQuartzJob?jobname=ldapPeopleJobDetail";

        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_TIMEOUT, 5);

        $buffer = curl_exec($ch);
        $buf = strip_tags($buffer);
    }else{
        //execute a force full sync ( because sometime differential is buggy)
        //execute a request to simulate a Javascript Console execution
        $data = array('script' => "var ctxt, synchronizer;\n\nctxt = Packages.org.springframework.web.context.ContextLoader.getCurrentWebApplicationContext();\nsynchronizer = ctxt.getBean('userRegistrySynchronizer', Packages.org.alfresco.repo.security.sync.UserRegistrySynchronizer);\n\n// forceUpdate = false, isFullSync = false - change for full update / with deletions\nsynchronizer.synchronize(true, true);",
                     'transaction' => 'readwrite',
                     'runas' => 'admin',
                     'documentNodeRef' => '',
                     'spaceNodeRef' => '',
                     'template' => '',
                     'urlargs' => '' );

        global $user;
        $ticket = gofast_cmis_retrieve_and_store_ticket($user);
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_TIMEOUT, 3);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));

        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
        curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/de/fme/jsconsole/execute?alf_ticket=".$ticket);
        $buffer = curl_exec($ch);

    }

  return $buf;
}

function gofast_cmis_webservice_item_assign_permissions($node_reference, $groups, $private_spaces) {
  $url_update_document_permissions = 'http://localhost:8080/alfresco/service/set/multi/?role=Standard&reference=' . $node_reference . '&spaces=' . str_replace("%5C%2C", "%2C", implode(';', (array) $groups)) . '&private_spaces=' . implode(';', (array) $private_spaces);
  //watchdog("CMIS MULTIFILL", "Update node permissions : " . $url_update_document_permissions);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url_update_document_permissions);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);

  return $buf;
}

function gofast_cmis_webservice_item_assign_homepage_permissions($node_reference, $groups) {
  $url_update_document_permissions = 'http://localhost:8080/alfresco/service/set/homepage/?reference=' . $node_reference . '&spaces=' . str_replace("%5C%2C", "%2C", implode(';', $groups));
  //watchdog("CMIS MULTIFILL", "Update node permissions : " . $url_update_document_permissions);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url_update_document_permissions);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);

  return $buf;
}

function gofast_cmis_webservice_item_assign_multifiled_permissions($node_reference, $groups, $private_spaces) {
  $url_update_document_permissions = 'http://localhost:8080/alfresco/service/set/multiMigrate/?role=Standard&reference=' . $node_reference . '&spaces=' . implode(';', $groups) . '&private_spaces=' . implode(';', $private_spaces);
  //watchdog("CMIS MULTIFILL", "Update node permissions : " . $url_update_document_permissions);
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url_update_document_permissions);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  $buffer = curl_exec($ch);
  $buf = strip_tags($buffer);

  return $buf;
}

/**
 * @package gofast_cmis
 * This function returns all the versions of a given node
 *
 * @param node $node_reference the node reference on wich we want the versions
 * @param boolean $last  if true, will return only the last version
 * @return array<VersionHistory> array of VersionHistory objects
 */
function gofast_cmis_webservice_item_get_versions($node_reference, $last = false, $skip_cache = false) {
  $url = "http://localhost:8080/alfresco/service/get/version/?reference=" . $node_reference;
  if($last == true){
      $url .= "&last=true";
  }

  if($skip_cache == false){
    global $$url;
    if(isset($$url)){
       return $$url;
    }
  }
  $username = "admin";
  $password = gofast_get_admin_pwd();

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  $buffer = curl_exec($ch);
  $result = trim($buffer);
  $versions = json_decode($result);

  $$url = $versions;

  return $versions;
}

/**
 * @package gofast_cmis
 * This function creates a new major version with a specified comment.
 *
 * @param string $node_reference the node reference on wich we tag the new version
 * @param string $comment_message the comment message
 * @return VersionHistory object
 */
function gofast_cmis_webservice_item_set_versions_major($node_reference, $comment_message) {
 //$username = "admin";
  //$password = gofast_get_admin_pwd();
  global $user;
  $username = $user->name;
  $ticket = gofast_cmis_get_user_ticket();
  if($ticket == FALSE){
    $ticket = gofast_cmis_retrieve_and_store_ticket($user);
  }

  $url = 'http://localhost:8080/alfresco/service/set/version/major/?comment=' . rawurlencode($comment_message) . '&reference=' . $node_reference . "&alf_ticket=" . $ticket;

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_URL, $url);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = trim($buf);
  $versions = json_decode($result);

  return $versions;
}

/**
 * @package gofast_cmis
 * fonction qui execute un requete vers le webscript Java crée sur Alfresco
 *
 * @global type $user
 * @param type $op
 * @param type $ref
 * @param type $admin
 * @return type
 */
function gofast_cmis_webservice_execute_request($op, $ref, $admin = true) {
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);
  if ($admin == true) {
    curl_setopt($ch, CURLOPT_USERPWD, 'admin:' . gofast_get_admin_pwd());
  }
  else {
    global $user;
    $ticket = gofast_cmis_get_user_ticket();
    if($ticket == FALSE){
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
    }
    $ticket_param = "&alf_ticket=" . $ticket;
  }
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/service/ceov/webservices?ref=" . $ref . "&op=" . $op . $ticket_param);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = trim($buf);
  return $result;
}

/**
 * @package gofast_cmis
 * fonction qui effectue un appel vers le webservice Alfresco permettant de restaurer un document supprimé
 *
 * @global type $user
 * @param type $node
 */
function gofast_cmis_restore_document_alfresco($node) {
  $reference = $node->field_reference[LANGUAGE_NONE][0]['value'];
  if(empty($reference)){
    return FALSE;
  }
  $reference = str_replace('workspace', 'archive', $reference);
  gofast_cmis_webservice_item_update_aspects($reference);
  //on effectue l'appel curl pour restaurer le doc
  global $user;
  $output = array();
  $ref = gofast_cmis_get_raw_item_id(gofast_cmis_node_get_item_id($node));
  $url = "http://localhost:8080/alfresco/service/api/archive/archive/SpacesStore/" . $ref;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url);
  $output = curl_exec($ch);
  return json_decode($output) ?? [];
}

/**
 * @package gofast_cmis
 * fonction qui effectue un appel vers le webservice Alfresco permettant de récuperer le contenu d'un fichier
 * Utile lorsque la restauration ne fonctionne pas (par exemple l'emplacement du document n'existe plus donc impossible de le restaurer)
 * mais que le user veut quand même récuperer le contenu de son doc
 *
 * @param type $node
 */
function gofast_cmis_restore_document_alfresco_get_link_content($node) {
  $ref = gofast_cmis_get_raw_item_id(gofast_cmis_node_get_item_id($node));
  $url = '/alfresco/service/api/node/content/archive/SpacesStore/' . $ref . '/'.$node->title."?a=true";

  $link = "<a href='".$url."'>".t("Click here to download the deleted document", array(), array('context' => 'gofast:gofast_cmis'))."</a>";

  return $link;
}

/**
 * @package gofast_cmis
 * This function archives or unarchives an item
 *
 * @param string $node_reference the node reference
 * @return Array
 */
function gofast_cmis_webservice_item_archive($node_reference, $unarchive = FALSE, $folder = FALSE) {
  if($unarchive == TRUE){
    $properties['gofast:preventDelete'] = 'false';
    gofast_cmis_item_update_properties($node_reference, $properties, false, true);
  }else{
    $url = 'http://localhost:8080/alfresco/service/set/node/archive/permission/?reference=' . rawurlencode($node_reference);
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
    curl_setopt($ch, CURLOPT_URL, $url);
    $output = curl_exec($ch);
    return json_decode($output) ?? [];
  }

}

/**
 * @package gofast_cmis
 * This function changes the owner of an item
 *
 * @param string $node_reference the node reference
 * @return Array
 */
function gofast_cmis_webservice_item_set_owner($node_reference) {
  $output = array();
  $url = 'http://localhost:8080/alfresco/service/set/owner/?reference=' . rawurlencode($node_reference) . '&user=adm';
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin:" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, $url);
  $output = curl_exec($ch);
  return json_decode($output) ?? [];
}

function gofast_cmis_webservice_item_get_permissions($node_reference) {
  $url = "http://localhost:8080/alfresco/service/get/permissions/?reference=" . $node_reference;

  $username = "admin";
  $password = gofast_get_admin_pwd();

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, $username . ":" . $password);
  curl_setopt($ch, CURLOPT_URL, $url);
  $buffer = curl_exec($ch);

  $buf = strip_tags($buffer);
  $result = trim($buf);
  $permissions = json_decode($result);

  if (!$permissions) {
    return [];
  }

  asort($permissions);
  return $permissions;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to multifile a folder in specific spaces.
 * @param type $folder_source_reference
 * @param type $destination_source_reference
 * @return string
 */
function gofast_cmis_webservice_multifile_folder($folder_source_reference, $destination_source_reference)
{
  if (empty($folder_source_reference) && empty($destination_source_reference)) {
    return false;
  }
  $ch = curl_init();

  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/multifilefolder?folder_source=" . $folder_source_reference . "&destination=" . $destination_source_reference);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);
  $result = $buffer;

  return $result;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to remove multifile a folder in specific spaces.
 * @param type $folder_source_reference
 * @param type $parent_ref
 * @return string
 */
function gofast_cmis_webservice_remove_multifile_folder($folder_source_reference, $parent_ref)
{
  if (empty($folder_source_reference) || empty($parent_ref)) {
    return false;
  }
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/removemultifilefolder?folder_source=" . $folder_source_reference . "&parent=" . $parent_ref);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);
  $result = $buffer;

  return $result;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to get parents of a folder (return an array of all parents reference
 * @param type $folder_ref
 * @return array
 */
function gofast_cmis_webservice_get_parents_folder_path($folder_ref)
{
  if (empty($folder_ref)) {
    return false;
  }
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/getparentsfolder?folder=" . $folder_ref);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);
  $result = $buffer;

  $parents_ref = str_replace(' ', '', $result);
  $parents_ref = str_replace('[', '', $parents_ref);
  $parents_ref = str_replace(']', '', $parents_ref);
  $result = explode(',', $parents_ref);
  return $result;
}

/**
 * @package gofast_cmis
 * This method send a request using CURL to alfresco to get parents of a folder (return an array of all parents reference
 * @param type $folder_ref
 * @return array
 */
function gofast_cmis_webservice_get_node_parents($node_ref)
{
  if (empty($node_ref)) {
    return false;
  }
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/getnodeparents?node=" . $node_ref);
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);
  $buffer = curl_exec($ch);
  $result = $buffer;
  $result = explode('%%SEPARATOR%%', $result);
  $result = array_map('trim', $result);
  return $result;
}

// for some reason mirrored folders don't work with gofast_cmis_webservice_item_update_properties
// so if you have issues updating some folder props you should try with this more generic call
function gofast_cmis_set_folder_item_prop($item_id, $prop = "gofast:ismirrored", $value = TRUE)
{
  global $user;
  $ticket = gofast_cmis_get_user_ticket();
  if($ticket == FALSE) {
      $ticket = gofast_cmis_retrieve_and_store_ticket($user);
  }
  $url = "http://localhost:8080/alfresco/api/-default-/public/alfresco/versions/1/nodes/".gofast_cmis_get_raw_item_id($item_id)."/content?alf_ticket=".$ticket."";
  $curl = curl_init();
  curl_setopt($curl, CURLOPT_URL, $url);
  curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "PUT");
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl, CURLOPT_HTTPHEADER, array("Content-Type: application/json;"));
  $options = array("properties" => array(
    $prop => $value
  ));
  curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($options));
  $result = curl_exec($curl);
  return $result;
}

/**
 * Makes a webservice request to change a user's username
 * @param $new_username
 * @param null $user
 *
 * @return bool|string
 */
function gofast_cmis_change_username($old_username, $new_username): bool|string {

  if (empty($new_username)) {
    return false;
  }

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_USERPWD, "admin" . ":" . gofast_get_admin_pwd());
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/renameusername?old_username=$old_username&new_username=$new_username" );
  curl_setopt($ch, CURLOPT_TIMEOUT, 5);

  $response = curl_exec($ch);
  curl_close($ch);
  return $response;
}