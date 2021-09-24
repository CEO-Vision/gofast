<?php

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action content
 * @methods GET,POST
 */
function gofast_api_node_content($params){
    //Handle methods
    switch($params['method']){
        case 'GET':
            gofast_cmis_api_get_node_content($params);
            break;
        case 'POST':
            gofast_cmis_api_post_node_content($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

function gofast_cmis_api_get_node_content($params){
    //Check content type and content disposition
    if(strpos($params['Content-Type'], "application/octet-stream") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }
    if(strpos($params['Content-Disposition'], "attachment") === FALSE){
        return gofast_api_not_implemented("This Content-Disposition");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    $content = gofast_cmis_item_get_content($node->field_reference[LANGUAGE_NONE][0]['value']);

    if(empty($content)){ //Check if we retrieved the content
       gofast_api_internal_server_error("Alfresco content not found for this node (Internal error)");
    }

    gofast_api_success($content, "200 OK", "application/octet-stream", 'attachment; filename="' . $node->title . '"');
}

function gofast_cmis_api_post_node_content($params){

    //Check content type and content disposition
    if(strpos($params['Content-Type'], "multipart/form-data") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Get params and check mandatory params
    $nid = !empty($params['nid']) ? $params['nid'] : file_get_contents($_FILES['nid']['tmp_name']);
    if(empty($nid)){
        gofast_api_mandatory_parameter("nid");
    }

    $comment_message = !empty($params['comment']) ? $params['comment'] : file_get_contents($_FILES['comment']['tmp_name']);
    $major_version = !empty($params['major_version']) ? $params['major_version'] : file_get_contents($_FILES['major_version']['tmp_name']);
    $content = file_get_contents($_FILES['file']['tmp_name']);

    //If we don't have a file in the 'file' field, try to get it from another one
    if(empty($content) && count($_FILES > 0)){
        $content = file_get_contents(reset($_FILES)['tmp_name']);
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    $archived_node = gofast_get_content_state_archived($node);
    $retention_node = false;
    if(module_exists('gofast_retention')){
      if( gofast_retention_get_retention_date($node) !== NULL){
        $retention_node = true;
      }
    }

    if(!node_access('update', $node) || $archived_node || $retention_node){
       gofast_api_forbidden("You don't have the permission to update this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not versionalble for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not versionable for an unpublished node");
    }

    if(empty($content)){ //Check if we retrieved the content
        gofast_api_mandatory_parameter("The body");
    }

    //Check if the node contains a reference
    $reference = $node->field_reference[LANGUAGE_NONE]['0']['value'];
    if(empty($reference)){
        gofast_api_internal_server_error("Unable to find an Alfresco reference for this node");
    }

    //Here, we can upload the file safely to Alfresco
    $updated_item = gofast_cmis_item_set_content($reference, $content);

    if($major_version == 1){
        if($comment_message === FALSE){
            gofast_cmis_tag_major_version($node, "");
        }else{
            gofast_cmis_tag_major_version($node, $comment_message);
        }
    }else{
        $comment = new stdClass();
        $comment->nid = $node->nid;
        $comment->cid = 0;
        $comment->pid = 0;
        $comment->uid = $user->uid;
        $comment->is_anonymous = 0;
        $comment->status = COMMENT_PUBLISHED;
        $comment->language = $node->language;
        $comment->subject = t('Minor version : ', array(), array('context' => 'gofast'));
        $comment->comment_body[LANGUAGE_NONE][0]['value'] = $comment_message;
        $comment->comment_body[LANGUAGE_NONE][0]['format'] = 'full_html';

        comment_submit($comment);
        comment_save($comment);
        node_save($node);
    }

    gofast_api_success(array('success' => TRUE, 'nid' => $node->nid, 'link' => '/node/' . $node->nid, "date" => date("c")));
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action preview
 * @methods GET
 */
function gofast_api_node_preview($params){
    //Check content type and content disposition
    if(strpos($params['Content-Type'], "application/pdf") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }
    if(strpos($params['Content-Disposition'], "attachment") === FALSE){
        return gofast_api_not_implemented("This Content-Disposition");
    }

    //Check method
    if($params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    $generation = gofast_cmis_webservice_item_generate_preview($node->nid);
    $generation = json_decode($generation, TRUE);

    if($generation['status'] != "OK"){
        gofast_api_internal_server_error("Preview generattion has failed for " . $node->title);
    }

    $content = file_get_contents("http://localhost" . gofast_cmis_node_get_pdf_link($node));
    if(empty($content)){ //Check if we retrieved the content
       gofast_api_internal_server_error("Alfresco content not found for this node (Internal error)");
    }

    gofast_api_success($content, "200 OK", "application/pdf", 'attachment; filename="' . $node->title . '.pdf"');
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action preview_link
 * @methods GET
 */
function gofast_api_node_preview_link($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }


    global $base_url;
    $url = $base_url . gofast_cmis_node_get_pdf_link($node);

    $url_object = json_decode(gofast_cmis_webservice_item_generate_onlyoffice_preview($node->nid));

    if(isset($url_object->FileUrl)){
        $url = "/sites/all/libraries/pdf/web/viewer_gofast.html?v=226&file=".$url_object->FileUrl;
    }
     gofast_api_success(array(
        'link' => $url,
    ));
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action version
 * @methods GET
 */
function gofast_api_node_version($params){
    //Handle methods
    switch($params['method']){
        case 'GET':
            gofast_cmis_api_get_node_version($params);
            break;
         case 'POST':
            gofast_cmis_api_set_node_major_version($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action versions
 * @methods GET
 */
function gofast_api_node_versions($params){
    //Handle methods
    switch($params['method']){
        case 'GET':
            gofast_cmis_api_get_node_versions($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action archive
 * @methods GET
 */
function gofast_api_node_archive($params){
    //Handle methods
    switch($params['method']){
         case 'POST':
            gofast_cmis_api_set_node_archive($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action status
 * @methods GET
 */
function gofast_api_node_status($params){
    //Handle methods
    switch($params['method']){
         case 'POST':
            gofast_cmis_api_set_node_delete_restore($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}



function gofast_cmis_api_set_node_delete_restore($params){
     //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "POST"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    if(isset($params['restore'])){
        $restore = $params['restore'];
    }else{
        gofast_api_mandatory_parameter("restore");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('update', $node)){
       gofast_api_forbidden("You don't have the permission to update this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }



    if($restore === "true"){
        //TODO improve this to manage response from Alfresco
         $ret = gofast_cmis_restore_document_alfresco($node);
        $response = json_decode(implode('', $ret));
        $node->status = 1;
        node_save($node);
    }else{
         if (node_access('delete', $node) === TRUE) {

            //check if it's a published document or not
            if( gofast_cmis_get_publication_source($node) !== FALSE){ //delete publication and link if needed
                gofast_cmis_publication_delete($node);
            }

            node_unpublish_action($node, array());
            node_save($node);

            try {
              gofast_cmis_node_delete($node);
            }
            catch (CMISException $e) { }

         }else{
             gofast_api_forbidden("You don't have the permission to delete this node");
         }
    }

     gofast_api_success(array(
        'nid' => $node->nid
    ));
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action publication
 * @methods GET
 */
function gofast_api_node_publication($params){
    //Handle methods
    switch($params['method']){
         case 'GET':
            gofast_cmis_api_get_node_publication($params);
            break;
         case 'POST':
            gofast_cmis_api_set_node_publication($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

function gofast_cmis_api_get_node_version($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    $node_versions = array_reverse(gofast_cmis_webservice_item_get_versions($node->field_reference[LANGUAGE_NONE][0]['value']));

    foreach($node_versions as &$version){
        unset($version->nodeRef);
        unset($version->name);
        unset($version->length);
        unset($version->mimetype);
        unset($version->author);
        $version->created = strtotime($version->createdDate);
        unset($version->createdDate);
        $version->version = $version->label;
        unset($version->label);

        if(empty($version->description)){
            unset($version->description);
        }else{
            $version->comment = $version->description;
            unset($version->description);
        }
    }

    gofast_api_success($version);
}

function gofast_cmis_api_get_node_versions($params){
    $output = array();

    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    $node_versions = array_reverse(gofast_cmis_webservice_item_get_versions($node->field_reference[LANGUAGE_NONE][0]['value']));

    foreach($node_versions as &$version){
        unset($version->nodeRef);
        unset($version->name);
        unset($version->length);
        unset($version->mimetype);
        unset($version->author);
        $version->created = strtotime($version->createdDate);
        unset($version->createdDate);
        $version->version = $version->label;
        unset($version->label);

        if(empty($version->description)){
            unset($version->description);
        }else{
            $version->comment = $version->description;
            unset($version->description);
        }

        $output['list'][] = $version;
        $output['html'] .= "v<a href='/cmis/browser?id=workspace%3A//SpacesStore/" . $node->field_reference[LANGUAGE_NONE][0]['value'] . "%3B" . $version->version . "' title='" . date("d/m/yy - H:m", $version->created) . " par " . $version->creator . " ". $version->comment ."' style='font-weight:bold;'>" . $version->version . "</a>, ";
    }
    $output['html'] = substr($output['html'], 0, -2);
    gofast_api_success($output);
}

function gofast_cmis_api_set_node_major_version($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "POST"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a comment_message param
    if(isset($params['comment_message'])){
        $comment_message = $params['comment_message'];
    }

    if(isset($params['create_comment'])){
        $create_comment = $params['create_comment'];
    }else{
        gofast_api_mandatory_parameter("create_comment");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('update', $node)){
       gofast_api_forbidden("You don't have the permission to update this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }



    $version_item = gofast_cmis_webservice_item_set_versions_major(gofast_cmis_node_get_item_id($node), $comment_message);

    if($create_comment === "true"){
        $comment = new stdClass();
        $comment->nid = $node->nid;
        $comment->cid = 0;
        $comment->pid = 0;
        $comment->uid = $user->uid;
        $comment->is_anonymous = 0;
        $comment->status = COMMENT_PUBLISHED;
        $comment->language = $node->language;
        $comment->subject = t('Major version : ', array(), array('context' => 'gofast')) . $version_item->label;
        $comment->comment_body[LANGUAGE_NONE][0]['value'] = $comment_message;
        $comment->comment_body[LANGUAGE_NONE][0]['format'] = 'full_html';

        comment_submit($comment);
        comment_save($comment);
        node_save($node);
    }

     gofast_api_success(array(
        'version_label' => $version_item->label
    ));
}





function gofast_cmis_api_set_node_archive($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "POST"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    if(isset($params['unarchive'])){
        $unarchive = $params['unarchive'];
    }else{
        gofast_api_mandatory_parameter("unarchive");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('update', $node)){
       gofast_api_forbidden("You don't have the permission to update this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    if($unarchive === "true"){
         gofast_cmis_node_unarchive($node);
    }else{
         gofast_cmis_node_archive($node);
    }

     gofast_api_success(array(
        'nid' => $node->nid
    ));
}

function gofast_cmis_api_get_node_publication($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

     $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    if(isset($node->field_publication[LANGUAGE_NONE][0]['target_id'])){
        $publication_nid = $node->field_publication[LANGUAGE_NONE][0]['target_id'];
    }else{
        $publication_nid = null;
    }

    $output = array("publication_nid" => $publication_nid);

    gofast_api_success($output);
}

function gofast_cmis_api_set_node_publication($params){
    watchdog("debug api publication", json_encode($params));


     //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a locations param
    if(isset($params['locations'])){
        $locations = $params['locations'];
    }else{
        gofast_api_mandatory_parameter("locations");
    }

     //Check if we have a force_create param
    if(isset($params['force_create'])){
        $force_create = $params['force_create'];
    }else{
       $force_create = "false";
    }

      //Check if we have a synchro_metadata param
    if(isset($params['synchro_metadata'])){
        $synchro_metadata = $params['synchro_metadata'];
    }else{
       $synchro_metadata = "false";
    }

    //Check if we have a param to no transform doc
    if(isset($params['prevent_transform'])){
       $prevent_transform = $params['prevent_transform'];
    }else{
       $prevent_transform = "false";
    }

    //Check if we have a param to synchronize_versions
    if(isset($params['synchronize_versions'])){
        $synchronize_versions = $params['synchronize_versions'];
    }else{
       $synchronize_versions = "false";
    }

     //Check if we have a param to prevent creating comment during major version
    if(isset($params['prevent_comment'])){
        $prevent_comment = $params['prevent_comment'];
    }else{
        $prevent_comment = "false";
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    if(isset($node->field_publication[LANGUAGE_NONE][0]['target_id'])){
         // Update the publication

         //if the new publication is not on the same format as previous one, change also the title ( extension ). Alfresco should manage correctly the mimetype
         if($prevent_transform == "false"){
                $file = gofast_cmis_item_get_content_publication($node, GOFAST_CMIS_PUBLICATION_TYPE_PDF);
                $extension = pathinfo($node->title, PATHINFO_EXTENSION);
                $published_node = node_load($node->field_publication[LANGUAGE_NONE][0]['target_id']);
                $publish_extension = pathinfo($published_node->title, PATHINFO_EXTENSION);
                //$publication_title = str_replace(".".$extension, "", $published_node->title).".pdf";
                $publication_title = str_replace(array(".".$extension, ".".$publish_extension), array("", ""), $published_node->title).".pdf";
         }else{
                $file = gofast_cmis_item_get_content_publication($node, GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT);
                //get the original extension
                $orig_extension = pathinfo($node->title, PATHINFO_EXTENSION);
                $published_node = node_load($node->field_publication[LANGUAGE_NONE][0]['target_id']);
                $publish_extension = pathinfo($published_node->title, PATHINFO_EXTENSION);
                $publication_title = str_replace(".".$publish_extension, ".".$orig_extension, $published_node->title);
         }


        //$file = gofast_cmis_item_get_content_publication($node, GOFAST_CMIS_PUBLICATION_TYPE_PDF);
        $publicated_nid = $node->{GOFAST_CMIS_PUBLICATION_FIELD}[LANGUAGE_NONE][0]['target_id'];
        $publicated_node = node_load($publicated_nid);
        $publicated_reference = gofast_cmis_node_get_item_id($publicated_node);
        $publicated_item = gofast_cmis_item_get($publicated_reference);
        $updated_item = gofast_cmis_item_set_content($publicated_reference, file_get_contents($file->filepath), $file->filemime, array(), FALSE);
        sleep(2);

       if($publication_title !==  $published_node->title){
           gofast_cmis_item_rename($publicated_reference, $publication_title, FALSE);
           $publicated_node->title = $publication_title;
           $publicated_node->{GOFAST_CMIS_FILENAME_FIELD}[LANGUAGE_NONE][0]["value"] = $publication_title;
            $publicated_node = gofast_prepare_node_save_technically($publicated_node);
            $ruid = $publicated_node->revision_uid;
            node_save($publicated_node);
            db_update('node_revision')
              ->fields(array('uid' => $ruid))
              ->condition('nid', $publicated_node->nid)
              ->execute();
           gofast_cmis_correct_mimetype($publicated_nid, false);
       }

         // tag as major version ( check) if we have to create a comment or not
        if($prevent_comment == 'true'){
            $version_item = gofast_cmis_webservice_item_set_versions_major(gofast_cmis_node_get_item_id($publicated_node), "");
        }else{
            gofast_cmis_tag_major_version($publicated_node, "");
        }

        //store versions informations into corresponding field ( field_publication_history )
        $source_list = gofast_cmis_webservice_item_get_versions($node->reference, true);
        $source_version = $source_list[0]->label;

        $published_list = gofast_cmis_webservice_item_get_versions($publicated_node->reference, true);
        $published_version = $published_list[0]->label;

        if($synchronize_versions == "true"){
                gofast_cmis_synchronize_version_publication($node, $publicated_node);
        }

        $new_field_publication_history = array();
        $existing_field_publication_history_value = $node->field_publication_history[LANGUAGE_NONE][0]["value"];
        $existing_field_publication_history_value = json_decode($existing_field_publication_history_value, true);
        $existing_field_publication_history_value[$source_version] = array("source_version" => $source_version , "published_version" => $published_version, "date" => time(), "comment" => $form_state['values']['tag_comment'], "creator" => $user->name);
        $new_field_publication_history[LANGUAGE_NONE][0]["value"]  = json_encode($existing_field_publication_history_value);

        $node->field_publication_history = $new_field_publication_history;
        field_attach_update('node', $node);

          if($synchro_metadata  == "true"){
                $publicated_node->field_category = $node->field_category;
                $publicated_node->field_criticity = $node->field_criticity;
                $publicated_node->field_date = $node->field_date;
                $publicated_node->field_tags = $node->field_tags;

                $publicated_node = gofast_prepare_node_save_technically($publicated_node);
                 $ruid = $publicated_node->revision_uid;
                 node_save($publicated_node);
                 db_update('node_revision')
                   ->fields(array('uid' => $ruid))
                   ->condition('nid', $publicated_node->nid)
                   ->execute();
            }


         $output = array("publication_nid" => $publicated_nid);
    }else{

            $locations_final = $locations;
            //if locations is empty, use original node location instead
            if(count($locations) == 0 || $locations[0] == ""){
                $locations_final =  array($node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]["value"]);
                 watchdog("debug api publication new locations", json_encode($locations_final));
            }

            if($prevent_transform == "false"){
                $file = gofast_cmis_item_get_content_publication($node, GOFAST_CMIS_PUBLICATION_TYPE_PDF);
                $extension = pathinfo($node->title, PATHINFO_EXTENSION);
                $publication_title = str_replace(".".$extension, "", $node->title)."_PUB.pdf";
            }else{
                $file = gofast_cmis_item_get_content_publication($node, GOFAST_CMIS_PUBLICATION_TYPE_DEFAULT);
                $extension = pathinfo($node->title, PATHINFO_EXTENSION);
                $title_without_extension = str_replace("." . $extension, "", $node->title) . "_PUB";
                $publication_title = $title_without_extension . $extension;
            }

            foreach($locations_final as $path){
                 $gid = gofast_og_get_group_id_from_title_2(htmlspecialchars_decode($path), TRUE);
                 $form_state['selected_groups'][] = $gid;
            }

           $options = array(
             'author' => $user,
             'locations' => $locations_final,
             'language' => $node->language,
             'parent_publication_id' => $node->nid,
             'parent_spaces' => $form_state['selected_groups'],
             'main_location' => reset($locations_final),
             'file' => $file,
             'publish_as_broadcaster' => false
           );


            if(gofast_cmis_publication_check_existing_publication_location(reset($locations_final)) === false){
                 if($force_create == "true"){
                      gofast_cmis_publication_force_create_missing_path(reset($locations_final));
                 }else{
                      gofast_api_internal_server_error("The path ".reset($locations_final)." doesn't exists");
                 }
            }

            $publication = gofast_cmis_publication_create($publication_title, $options);

            if($synchro_metadata  == "true"){
                $publication->field_category = $node->field_category;
                $publication->field_criticity = $node->field_criticity;
                $publication->field_date = $node->field_date;
                $publication->field_tags = $node->field_tags;

                $publication = gofast_prepare_node_save_technically($publication);
                 $ruid = $publication->revision_uid;
                 node_save($publication);
                 db_update('node_revision')
                   ->fields(array('uid' => $ruid))
                   ->condition('nid', $publication->nid)
                   ->execute();
            }

            if($synchronize_versions == "true"){
                gofast_cmis_synchronize_version_publication($node, $publication);
            }

             $output = array("publication_nid" => $publication->nid);
    }

    gofast_api_success($output);
}


/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action version
 * @methods GET
 */
function gofast_api_comment_comment($params){
    //Handle methods
    switch($params['method']){
        case 'GET':
            gofast_api_get_comment_comment($params);
            break;
        case 'PUT':
            gofast_api_put_comment_comment($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

function gofast_api_put_comment_comment($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "PUT"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    $params = array_merge($params, json_decode(file_get_contents('php://input'), true));



    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a subject param
    if(isset($params['subject'])){
        $subject = str_replace("+", " ", rawurldecode($params['subject']));
    }else{
        gofast_api_mandatory_parameter("subject");
    }

    //Check if we have a body param
    if(isset($params['body'])){
        $body = str_replace("+", " ", rawurldecode($params['body']));
    }else{
        gofast_api_mandatory_parameter("body");
    }

    //Check if we have a is_private param
    if(isset($params['is_private'])){
        $is_private = $params['is_private'];
    }else{
        $is_private = 0;
    }

     //Check if we have a is_annotation param
    if(isset($params['is_annotation'])){
        $is_annotation = $params['is_annotation'];
    }else{
        $is_annotation = 0;
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to comment this node");
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("You cannot comment an unpublished node");
    }

    $comment = new stdClass();
    $comment->nid = $node->nid;
    $comment->cid = 0;
    $comment->pid = 0;
    $comment->uid = $user->uid;
    $comment->is_anonymous = 0;
    $comment->status = COMMENT_PUBLISHED;
    $comment->language = $node->language;
    $comment->subject = $subject;
    $comment->comment_body[LANGUAGE_NONE][0]['value'] = $body;
    $comment->comment_body[LANGUAGE_NONE][0]['format'] = 'full_html';
    $comment->field_comment_is_private[LANGUAGE_NONE][0]['value'] = $is_private;
    if(intval($is_annotation) == 1){
        $comment->field_is_annotation[LANGUAGE_NONE][0]['value'] = intval($is_annotation);
    }
    comment_submit($comment);
    comment_save($comment);
    node_save($node);

    gofast_api_success(array(
        'cid' => $comment->cid
    ));
}

function gofast_api_get_comment_comment($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check method
    if($params['method'] != "GET"){
        gofast_api_not_implemented("This method");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a cid param
    if(isset($params['cid'])){
        $cid = $params['cid'];
    }else{
        gofast_api_mandatory_parameter("cid");
    }

    $comment = comment_load($cid);

    //Check if we retrieved a node
    if($comment == null){
        gofast_api_internal_server_error("Unable to load comment with cid : " . $cid);
    }

    //Check node access
    if(!comment_access('view', $comment)){
       gofast_api_forbidden("You don't have the permission to view this comment");
    }

    gofast_api_success(array(
        'cid' => $comment->cid,
        'nid' => $comment->nid,
        'uid' => $comment->uid,
        'subject' => $comment->subject,
        'body' => $comment->comment_body[LANGUAGE_NONE][0]['value'],
        'is_private' => $comment->field_comment_is_private[LANGUAGE_NONE][0]['value']
    ));
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource node
 * @action locations
 * @methods GET,PUT,DELETE
 */
function gofast_api_node_locations($params){
    //Handle methods
    switch($params['method']){
        case 'GET':
            gofast_cmis_api_get_node_locations($params);
            break;
        case 'POST':
            if($params['delete'] == true){
                gofast_cmis_api_delete_node_locations($params);
            }else{
                gofast_cmis_api_post_node_locations($params);
            }
            break;
        case 'PUT':
            gofast_cmis_api_put_node_locations($params);
            break;
        default:
            gofast_api_not_implemented("This method");
    }
}

function gofast_cmis_api_get_node_locations($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    //Reload node
    gofast_process_location_check_async($nid, true, false, false);
    $node = node_load($nid, NULL, FALSE);

    $locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];

    $output = array();
    foreach($locations as $location){
        $output[] = $location['value'];
    }

    gofast_api_success($output);
}

function gofast_cmis_api_post_node_locations($params){
    $output = array();

    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a nid param
    if(isset($params['locations'])){
        $given_locations = $params['locations'];
    }else{
        gofast_api_mandatory_parameter("locations");
    }

    if(strpos($nid, ",") !== FALSE){
        $nids = explode(",", $nid);
    }else{
        $nids = array($nid);
    }

    foreach($nids as $nid){
        $node = node_load($nid);

        //Check if we retrieved a node
        if($node == null){
            gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
        }

        //Check node access
        if(!node_access('view', $node)){
           gofast_api_forbidden("You don't have the permission to view this node");
        }

        //Check if this node has an Alfresco content linked
        if($node->type !== "alfresco_item"){
           gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
        }

        //Check if this node is deleted
        if($node->status == 0){
          gofast_api_not_found("Alfresco content not found for an unpublished node");
        }

        $locations_initial = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];

        $locations_initial_flat = array();
        foreach($locations_initial as $location){
            $locations_initial_flat[] = $location['value'];
        }

        $locations_final = array_merge($locations_initial_flat, $given_locations);
        $locations_final = array_unique($locations_final);

        //Update locations
        $_POST['pk'] = $nid;
        $_POST['name'] = GOFAST_CMIS_LOCATIONS_FIELD;
        $_POST['value'] = $locations_final;
        $_POST['non_xeditable'] = TRUE;
        gofast_update_node_field();

        //Reload node, cleaning cache
        gofast_process_location_check_async($nid, true, false, true);
        $node = node_load($nid, NULL, TRUE);

        //Reloading locations to output

        $locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];

        foreach($locations as $location){
            $output[$nid][] = $location['value'];
        }
    }

    gofast_api_success($output);
}

function gofast_cmis_api_put_node_locations($params){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a nid param
    if(isset($params['locations'])){
        $locations = $params['locations'];
    }else{
        gofast_api_mandatory_parameter("locations");
    }

    $node = node_load($nid);

    //Check if we retrieved a node
    if($node == null){
        gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
    }

    //Check node access
    if(!node_access('view', $node)){
       gofast_api_forbidden("You don't have the permission to view this node");
    }

    //Check if this node has an Alfresco content linked
    if($node->type !== "alfresco_item"){
       gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
    }

    //Check if this node is deleted
    if($node->status == 0){
      gofast_api_not_found("Alfresco content not found for an unpublished node");
    }

    //Update locations
    $_POST['pk'] = $nid;
    $_POST['name'] = GOFAST_CMIS_LOCATIONS_FIELD;
    $_POST['value'] = $locations;
    $_POST['non_xeditable'] = TRUE;
    gofast_update_node_field();

    //Reload node, cleaning cache
    gofast_process_location_check_async($nid, true, false, true);
    $node = node_load($nid, NULL, TRUE);

    //Reloading locations to output

    $locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];

    $output = array();
    foreach($locations as $location){
        $output[] = $location['value'];
    }

    gofast_api_success($output);
}

function gofast_cmis_api_delete_node_locations($params){
    $output = array();

    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a nid param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

    //Check if we have a nid param
    if(isset($params['locations'])){
        $given_locations = $params['locations'];
    }else{
        gofast_api_mandatory_parameter("locations");
    }

    if(strpos($nid, ",") !== FALSE){
        $nids = explode(",", $nid);
    }else{
        $nids = array($nid);
    }

    foreach($nids as $nid){

        $node = node_load($nid);

        //Check if we retrieved a node
        if($node == null){
            gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
        }

        //Check node access
        if(!node_access('view', $node)){
           gofast_api_forbidden("You don't have the permission to view this node");
        }

        //Check if this node has an Alfresco content linked
        if($node->type !== "alfresco_item"){
           gofast_api_not_found("Alfresco content not found for node type : " . $node->type);
        }

        //Check if this node is deleted
        if($node->status == 0){
          gofast_api_not_found("Alfresco content not found for an unpublished node");
        }

        $initial_locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
        $initial_locations_flat = array();
        foreach($initial_locations as $location){
            $initial_locations_flat[] = $location['value'];
        }

        //Remove asked locations
        $locations_final = array();
        foreach($initial_locations_flat as $location){
            if(!in_array($location, $given_locations, TRUE)){
                $locations_final[] = $location;
            }
        }

        //Update locations
        $_POST['pk'] = $nid;
        $_POST['name'] = GOFAST_CMIS_LOCATIONS_FIELD;
        $_POST['value'] = $locations_final;
        $_POST['non_xeditable'] = TRUE;
        gofast_update_node_field();

        //Reload node, cleaning cache
        //gofast_process_location_check_async($nid, true, false, true);
        $node = node_load($nid, NULL, TRUE);

        //Reloading locations to output

        $locations = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];

        foreach($locations as $location){
            $output[$nid][] = $location['value'];
        }
    }

    gofast_api_success($output);
}
