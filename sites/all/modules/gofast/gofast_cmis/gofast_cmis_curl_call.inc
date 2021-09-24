<?php

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
function gofast_cmis_webservice_item_onlyoffice_hash($reference, $clear = null, $force = null) {

  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }

  if($clear == false){
      $clear = null;
  }

  $url = "http://localhost:8080/alfresco/service/updateOnlyofficeHash?reference=" . $reference . "&clear=" . $clear . "&force=" . $force;
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
  curl_setopt($ch, CURLOPT_URL, "http://localhost:8080/alfresco/s/impersonate?username=" . $username);
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
 * fonction qui appel le webscript JS d'alfresco crée par CEO-Vision et qui récupere l'arborescence des dossiers
 * auxquels le user a accès en dessous du dossier recu en parametre ($reference)
 *
 * @global type $user
 * @param string $reference
 * @param string filter_documents "documents" to get only documents, "folders"
 * to get only folders and "groups" to get only groups, "templates" to get a
 * list of all available templates for the user queryring. leave empty for all
 * or set "all"
 * @return type
 */
function gofast_cmis_webservice_item_get_descendants($reference, $param_documents = "all", $async = false, $as_admin = FALSE) {

  if (strpos($reference, "workspace") === false) {
    $reference = "workspace://SpacesStore/" . $reference;
  }
  global $user;

  //$ticket = gofast_cmis_get_user_ticket();

  if($async == true){
      $restrictdepth= "true";
  }else{
      $restrictdepth= "false";
  }

  $url = "http://localhost:8080/alfresco/service/get/descendants/?reference=" . $reference . "&type=" . $param_documents . "&restrictdepth=".$restrictdepth;
  watchdog("debug descendant url", $url);

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
    return array_filter($descendants_final);
  }
  else {
    return $descendants_final;
  }
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
function gofast_cmis_webservice_item_generate_preview($node_id) {

  // If the file is not generated (pdf/jpg...etc.)
  $node = node_load($node_id);
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
    return json_encode(array('status' => 'OK', 'type' => $type, 'link' => gofast_cmis_node_get_pdf_link($node), "title" => $node->title));
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

  return $result;
}

function gofast_cmis_webservice_item_get_onlyoffice_preview($cache_doc_id){
   //split $cache_doc_id with _, to separate alfresco_item and timestamp
    $alfresco_item = explode("_", $cache_doc_id)[0];
    $timestamp = explode("_", $cache_doc_id)[1];

    //get node from $alfresco_item
    $node = node_load(gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$alfresco_item));

    if(isset($node->nid)){
        if(node_access('view', $node)){
            $filename = "/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id;
             if(file_exists($filename)){
                header('Content-Type: application/pdf');
                header("Content-Transfer-Encoding: Binary");
                header("Content-disposition: attachment; filename=\"" . basename($cache_doc_id) . "\"");
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
function gofast_cmis_webservice_item_generate_onlyoffice_preview($node_id) {

    global $base_url;
    // If the file is not generated (pdf/jpg...etc.)
    $node = node_load($node_id);
    $node_extension = gofast_cmis_node_get_extension($node);
    $not_alfresco_generated = in_array($node_extension, array('docx','dotx','xltx','potx','pptx','ppsx','pdf'));
    if(!$not_alfresco_generated) {
	return json_encode(array('status' => 'FALLBACK'));
    }
    if(module_exists('gofast_community')){
      return json_encode(array('status' => 'FALLBACK'));
    }
    $excluded_previews = variable_get("gofast_soffice_preview_exclude", array());
    $reference = gofast_cmis_node_get_item_id(node_load($node_id));
    if (in_array($reference, array_flip($excluded_previews))) {
	unset($excluded_previews[$reference]);
	variable_set("gofast_soffice_preview_exclude", $excluded_previews);
    }

    ## condition if onlyoffice answer
    ## call onlyoffice pdf transformer
    // Document's name
    $doc_name = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:contentStreamFileName'];

    // Document's last modification date
    $doc_last_modification_date = gofast_cmis_item_get($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'])->properties['cmis:lastModificationDate'];

    // Document id
    $doc_id = gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']) . '_' . GenerateRevisionId($doc_last_modification_date);


    //First, check if the cache file already exists
    //cache doc name is composed of alfresco item id then modification timestamp
    $cache_doc_id = gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']) . '_' . strtotime($doc_last_modification_date);
    if(file_exists("/var/www/d7/sites/default/files/oo_previews/".$cache_doc_id)){
        //cache file already exists ( the name contains timestamp so we are sur it's related to this version)
        return json_encode(array('EndConvert' => 'True' , 'status' => 'OK', 'FileUrl' => $base_url.'/gofast/get_onlyoffice_preview/'.$cache_doc_id));
    }

    //check if an old cache version exists ( in order to delete it)
    $list = glob('/var/www/d7/sites/default/files/oo_previews/'.gofast_cmis_get_raw_item_id($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']) . '_*');
    if(count($list) > 0){
        foreach($list as $filepath){
              unlink($filepath);
        }
    }


    ## url
    $url_alfresco_content = $base_url . "/alfresco/s/api/node/content/" . str_replace(":/","",$reference) . "?alf_ticket=" . gofast_cmis_get_user_ticket();
    ## the JSON data.
    $jsonData = array(
      'filetype' => gofast_cmis_node_get_extension($node),
      'key' => $doc_id,
      "outputtype" => "pdf",
      "title" => $node->title,
      "url" => $url_alfresco_content,
      "spreadsheetLayout" => []
    );
    ## encode the array into JSON.
    $jsonDataEncoded = json_encode($jsonData);

    # api url
    $url = DOC_SERV_CONVERTER_URL;
    ## initiate cURL.
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    //Tell cURL that we want to send a POST request.
    //Set the content type to application/json
    curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json'));
    curl_setopt($ch, CURLOPT_POST, 1);
    //Attach our encoded JSON string to the POST fields.
    curl_setopt($ch, CURLOPT_POSTFIELDS, $jsonDataEncoded);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
    curl_setopt($ch, CURLOPT_PROXY, '');
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    //Execute the request
    $exec = curl_exec($ch);
    $xml = simplexml_load_string($exec);

    //if the pdf has been correctly generated, download and store the file into GF temp file
    $success = json_decode(json_encode($xml))->EndConvert;
    $file_url = json_decode(json_encode($xml))->FileUrl;

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
    $result = json_encode($xml);
    return $result;
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
  $url_update_document_permissions = 'http://localhost:8080/alfresco/service/set/multi/?role=Standard&reference=' . $node_reference . '&spaces=' . str_replace("%5C%2C", "%2C", implode(';', $groups)) . '&private_spaces=' . implode(';', $private_spaces);
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

  $buf = strip_tags($buffer);
  $result = trim($buf);
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
  exec('curl -X PUT -u admin:' . gofast_get_admin_pwd() . ' "http://localhost:8080/alfresco/service/api/archive/archive/SpacesStore/' . $ref . '"', $output);

  return $output;
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
  $unarchive_document = $unarchive ? 'true' : 'false';
  $validators = $unarchive ? 'null' : 'adm';
  $arg_folder = $folder ? 'true' : 'false';
  $output = array();
  if($unarchive == TRUE){

  }else{
      $url = 'http://localhost:8080/alfresco/service/set/node/archive/permission/?reference=' . rawurlencode($node_reference);
  }
  exec("curl --user admin:" . gofast_get_admin_pwd() . " '" . $url . "'");

  if($unarchive){
      $properties['gofast:preventDelete'] = 'false';
      gofast_cmis_item_update_properties($node_reference, $properties, false, true);
  }
  return $output;
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
  exec("curl --user admin:" . gofast_get_admin_pwd() . " '" . $url . "'");
  return $output;
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

  asort($permissions);
  return $permissions;
}
