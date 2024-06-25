<?php


/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource mail
 * @action autocomplete
 * @methods GET
 */
function gofast_api_mail_spaces($params)
{
  switch ($params['method']) {
    case 'GET':
      gofast_api_get_mail_spaces($params);
      break;
    default:
      gofast_api_not_implemented("This method");
      break;
  }
}

function gofast_api_get_mail_spaces($params)
{
  $spaces = array();
  $spaces_id = gofast_mail_inbound_outbound_get_mail_spaces();

  if(!$spaces_id){
    gofast_api_internal_server_error("Unable to retrieve mail spaces");
  }

    foreach($spaces_id as $key => $space){
    $nid = $space->entity_id;
    $title = gofast_get_node_title($nid);
    $spaces[] = array(
      "nid" => $nid,
      "title" => $title
    );
  }

  $output = array(
    'content' => json_encode($spaces)
  );

  gofast_api_success($output);
}



/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource mail
 * @action metadata
 * @methods GET
 */
function gofast_api_mail_metadata($params)
{
  switch ($params['method']) {
    case 'POST':
      gofast_api_post_mail_metadata($params);
      break;
    default:
      gofast_api_not_implemented("This method");
      break;
  }
}


function gofast_api_post_mail_metadata($params)
{
  $params = array_merge($params, json_decode(file_get_contents('php://input'), true));
  //Check content type
  if (strpos($params['Content-Type'], "application/json") === FALSE) {
    return gofast_api_not_implemented("This Content-Type");
  }

  //Check authentication
  global $user;
  if ($user->uid == 0) {
    gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }
  //Check if we have a nid param
  if (isset($params['nid'])) {
    $nid = $params['nid'];
  } else {
    gofast_api_mandatory_parameter("nid");
  }

  $node = node_load($nid);

  //Check if we retrieved a node
  if ($node == null) {
    gofast_api_internal_server_error("Unable to load node with nid : " . $nid);
  }

  //Check node access
  if (!node_access('update', $node)) {
    gofast_api_forbidden("You don't have the permission to update this node");
  }

  //The list of allowed fields
  $allowed_fields = array(
    'field_category',
    'field_state',
    'field_criticity',
    'field_mail_object',
    'field_mail_rid',
    'field_mail_sender',
    'field_mail_instruction',
    'field_impute_to',
    'field_mandatory_answer',
    'field_arrival_departure_link',
    'field_service_recipient',
    'field_arrival_departure_date',
    'field_user_recipient',
    'field_acknowledge_number'
  );

  //Get edited fields
  $edited_fields = array();

  foreach ($params as $key => $param) {
    $param = rawurldecode($param);
    $param = str_replace("+", " ", $param);

    if (empty($param)) {
      continue;
    }

    if (in_array($key, $allowed_fields, TRUE)) {
      //This is a requested change, check integrity of the provided values
      if (is_numeric($param) || is_string($param)) {
        //Integrity verified, register for change
        $edited_fields[$key] = $param;
        continue;
      }

      if (!is_array($param) || count($param) < 1) {
        gofast_api_internal_server_error("Bad format for field " . $key);
      }

      foreach ($param as $k => $value) {
        if (!is_numeric($value) && !is_string($value)) {
          gofast_api_internal_server_error("Bad format for value " . $k . " of field " . $key);
        }
      }

      //Integrity verified, register for change
      $edited_fields[$key] = $param;
    }
  }

  //Check if we do have a field to edit
  if (count($edited_fields) < 1) {
    gofast_api_mandatory_parameter('field_XXX');
  }

  //Prepare and process the edition
  $output = array();

  foreach ($edited_fields as $field => $value) {
    switch ($field) {
      case 'field_category':
      case 'field_state':
      case 'field_criticity':

        if(is_string($value) && !empty($value)){
            $value = array_keys(taxonomy_get_term_by_name($value))[0];
        }

        if (empty($value)) {
          break;
        }

        $node->$field[LANGUAGE_NONE][0]['tid'] = $value;
        $output[] = array(
          $field => array(
            "nameEnter" => $params[$field],
            "newMetadata" => $node->$field[LANGUAGE_NONE][0]['tid'],
            "status" => "OK",
          )
        );

        break;
      default:
        $node->$field[LANGUAGE_NONE][0]['value'] = $value;
        $node->$field[LANGUAGE_NONE][0]['safe_value'] = $value;
        $output[] = array(
            $field => array(
              "nameEnter" => $params[$field],
              "newMetadata" => $node->$field[LANGUAGE_NONE][0]['value'],
              "status" => "OK",
            )
          );
        break;
    }
  }

  node_save($node);
  gofast_api_success($output);
}

function gofast_api_mail_locations($params){
  //Don't allow external access to this API as it's called by the old Java API internally
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
      //gofast_api_forbidden("Unavailable action for external requester");
  }
  watchdog('jle', json_encode($params));
  //Check if we have a nid param
  if (isset($params['nids'])) {
    $nids = $params['nids'];
  } else {
    gofast_api_mandatory_parameter("nids");
  }

  $nids = explode(",", $nids);

  //Prepare and process the edition
  $output = array();

  //Fetch into nids and retrieve mail space location
  foreach($nids as $nid){
      if(is_numeric(trim($nid))){
        $node = node_load(trim($nid));
        $path = gofast_cmis_space_get_webdav_path($node->field_mail_subspace_nid['und'][0]['value']);

        if($path == '/Sites/_Organisations/_SE/_Traitement des courriers'){
            $output[] = '/Sites/_Organisations/_SE';
        }else if($path != "/Sites"){
            $output[] = $path;
        }
      }else{
        switch(trim($nid)){
            case 'QuestionsTIC':
                $output[] = '/Sites/_Groups/_Questions TIC';
                break;
            case 'QuestionsPOSTES':
                $output[] = '/Sites/_Groups/_Questions Postes';
                break;
            case 'QuestionsJuridiques':
                $output[] = '/Sites/_Groups/_Questions Juridiques';
                break;
            case 'Questionséconomiques':
                $output[] = '/Sites/_Groups/_Questions économiques';
                break;
            default:
                break;
        }
      }
  }

  gofast_api_success($output);
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource user
 * @action autocomplete
 * @methods GET
 */
function gofast_api_mail_autocomplete($params){
    switch($params['method']){
    case 'GET':
        gofast_api_get_mail_autocomplete($params);
        break;
    default:
        gofast_api_not_implemented("This method");
        break;
    }
}

function gofast_api_get_mail_autocomplete($params){
    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a str param
    if(isset($params['str'])){
        $str = $params['str'];
    }else{
        gofast_api_mandatory_parameter("str");
    }

    //Check if we have a space param
    if(isset($params['space'])){
        $space = $params['space'];
    }else{
        gofast_api_mandatory_parameter("space");
    }

    if(strlen($str) < 1){
        gofast_api_success(array());
    }

    $options_ac_user = array(
      'format_key_callback' => 'gofast_user_api_autocomplete_format_key',
      'format_value_callback' => 'gofast_user_api_autocomplete_format_value'
    );

    $output = gofast_ac_query($str, 'user', $options_ac_user, false, array($space));

    gofast_api_success($output);
}


/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource mailwf
 * @action start
 * @methods GET
 */

function gofast_api_mail_start_outbound_workflow($params){
  watchdog('START WORKFLOW MAIL OUTBOUND', json_encode($params));
  
  //Check if we have a str param
  if(isset($params['documents'])){
      $list_nids = $params['documents'];
  }else{
      gofast_api_mandatory_parameter("documents");
  }
  
  //Check if we have a space param
  if(isset($params["departmentName"])){
      $departmentName = $params["departmentName"];
  }else{
      gofast_api_mandatory_parameter("departmentName");
  }
  
  //Check if we have a actors param
  if(isset($params['listInboundActors'])){
    $listInboundActors = $params['listInboundActors'];
  }else{
    gofast_api_mandatory_parameter("listInboundActors");
  }
  
  //Check if we have a actors param
  if(isset($params['listOutboundInitActors'])){
    $listOutboundInitActors = $params['listOutboundInitActors'];
  }else{
    gofast_api_mandatory_parameter("listOutboundInitActors");
  }
  
  $output = gofast_mail_start_outbound_workflow($list_nids, $departmentName, $listInboundActors, NULL, TRUE, $listOutboundInitActors);

  gofast_api_success($output);
}

/*
 * Implements gofast_api_RESSOURCE_ACTION
 * @ressource mailwf
 * @action start
 * @methods GET
 */

function gofast_api_mail_start_workflow($params){

  watchdog('debug_amrtp', json_encode($params));
  //Check authentication

  //Check if we have a str param
  if(isset($params['documents'])){
      $list_nids = $params['documents'];
  }else{
      gofast_api_mandatory_parameter("documents");
  }

  //Check if we have a str param
  if(isset($params['listInboundActors'])){
      $listInboundActors = $params['listInboundActors'];
  }else{
      gofast_api_mandatory_parameter("listInboundActors");
  }
  //Check if we have a space param
  if(isset($params["departmentName"])){
      $departmentName = $params["departmentName"];
  }else{
      gofast_api_mandatory_parameter("departmentName");
  }

  //Check if we have a space param
  if(isset($params['isImputedSE'])){
      $isImputedSE = $params['isImputedSE'];
  }else{
      gofast_api_mandatory_parameter("isImputedSE");
  }

  if($isImputedSE == "true"){
    $isImputedSE =  true;
  }else{
    $isImputedSE = false;
  }


  $output = gofast_mail_inbound_outbound_start_workflow_outbound($list_nids, $departmentName, $isImputedSE, $listInboundActors);

  gofast_api_success($output);
}

/*
 * Implements GoFAST API
 * @ressource mail
 * @action get_imputation_actors
 * @methods GET
 *
 * Return the actors to impute
 */
function gofast_api_mail_get_imputation_actors($params){
  //Don't allow external access to this API
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
      gofast_api_forbidden("Unavailable action for external requester");
  }

  //Check if we have a nid param
  if (isset($params['nid'])) {
    $nid = $params['nid'];
  } else {
    gofast_api_mandatory_parameter("nid");
  }

  //Fetch into nids and retrieve mail space location
  $node = node_load($nid);

  $ulid = $node->field_mail_ulid['und'][0]['value'];
  $uids = array_keys(gofast_userlist_get_members($ulid));
  $bonita_uids = gofast_workflows_get_bonitaids_from_uids($uids);

  gofast_api_success($bonita_uids);
}

function gofast_api_user_main_orga($params){
  switch($params['method']){
    case 'GET':
        gofast_api_user_get_main_orga($params);
        break;
    default:
        gofast_api_not_implemented("This method");
        break;
    }
}

/*
 * Implements GoFAST API
 * @ressource user
 * @action get_main_orga
 * @methods GET
 *
 * Return the actors to impute
 */
function gofast_api_user_get_main_orga($params){

  global $user;
  //Check if we have a uid param
  if (isset($params['uid'])) {
    $uid = $params['uid'];
  } else {
    $uid = $user->uid;
  }
  //Fetch into nids and retrieve mail space location
  $current_user = user_load($uid);
  
  $main_orga_nid = $current_user->ldap_user_ou[LANGUAGE_NONE][0]['value'];
  $main_orga_nid = str_replace('_#', '', $main_orga_nid);
  
  gofast_api_success($main_orga_nid);
}


function gofast_api_node_readonly($params){
  switch($params['method']){
    case 'POST':
      gofast_api_node_set_readonly($params);
      break;
    default:
      gofast_api_not_implemented("This method");
      break;
    }
}


/*
 * Implements GoFAST API
 * @ressource node
 * @action set_readonly
 * @methods SET
 *
 * Return the actors to impute
 */
function gofast_api_node_set_readonly($params){

  //Don't allow external access to this API
  watchdog('debug amrtp', 'Je passe ici');
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    gofast_api_forbidden("Unavailable action for external requester");
  }
  gofast_cmis_retrieve_and_store_ticket(user_load_by_name("admin"));
  //Check if we have a nid param
  if (isset($params['nid'])) {
    $nid = $params['nid'];
  } else {
    gofast_api_mandatory_parameter('nid');
  }
  gofast_retention_set_node_readonly(node_load($nid));

  $node_reference = gofast_cmis_node_get_item_id(node_load($nid));
  $permissions = gofast_cmis_webservice_item_get_permissions($node_reference);

  foreach($permissions as $permission){
    if(strpos($permission, 'DUA_Archived')){
      gofast_api_success('OK');
    }
  }

  gofast_api_output('Permission was not applied');

}

/*
 * Implements GoFAST API
 * @ressource mail
 * @action imputation_title
 * @methods GET
 *
 * Return the node title of an imputation
 */
function gofast_api_mail_imputation_title($params){
watchdog("jleman", json_encode($params));
  //Don't allow external access to this API
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    //gofast_api_forbidden("Unavailable action for external requester");
  }

  //Check if we have a nid param
  if (isset($params['imputation'])) {
    $imputation = $params['imputation'];
  } else {
    gofast_api_mandatory_parameter('imputation');
  }

  $output = "";

  if(!empty($imputation)){
    if(is_numeric($imputation)){
      $node = node_load($imputation);
      $output = $node->title;
    }else{
      $copies = explode(',', $imputation);

      foreach($copies as $copy){
        $node = node_load(trim($copy));
        $output .= $node->title . ", ";
      }

      $output = rtrim($output, ", ");
    }
  }

  //Don't use regular API output as it messes up with Groovy
  print $output;
  exit;
}


function gofast_api_workflows_userlist_actors($params){
  switch($params['method']){
    case 'GET':
        gofast_api_workflows_userlist_actors_get($params);
        break;
    default:
        gofast_api_not_implemented("This method");
        break;
    }
}


function gofast_api_workflows_userlist_actors_get($params){
  
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    //gofast_api_forbidden("Unavailable action for external requester");
  }

  // Get name step 
  if (isset($params['step'])) {
    $step = $params['step'];
  } else {
    gofast_api_mandatory_parameter('step');
  }
  

  $pid = gofast_workflows_get_inbound_mail_pid();
  
  // Get process id actors
  $actors = gofast_workflows_get_actors($pid);
  
  // Get userlists ids
  foreach($actors as $actor){
    $userlist_ids[$actor['name']] = $actor['id'];
  }
  
  switch($step){
      case '1':
        $actor_id = $userlist_ids['Service Courrier'];
      break;
      case '2':
        $actor_id = $userlist_ids['Responsable Courrier'];
      break;
      case '3':
        $actor_id = $userlist_ids['DG / DGA'];
      break;
  }
  
  // Get userlist id with getting group members
  $actor_members = gofast_workflows_get_actor_members($actor_id);
  $group_id = $actor_members[0]['group_id'];
  $group_members = gofast_workflows_curl_get_group_info($group_id);
  $ulid = str_replace('ul_', '', $group_members);
  
  // Load userlist
  $userlist = entity_load_single('userlist',$ulid);
  
  // Get userlist name
  $userlist_name = $userlist->name;
  
  // Api success
  if(!empty($userlist_name)){
    print $userlist_name;
    exit;
  }else{
    gofast_api_output('Userlist not found');
  }
}

function gofast_api_mail_get_register_number($params){
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    gofast_api_forbidden("Unavailable action for external requester");
  }
  
  // Get register number variable or init it
  $register_number = variable_get('gofast_mail_register_number', '0');
  
  // Increment
  $register_number++;
  
  // Api success
  if(!empty($register_number)){
    variable_set('gofast_mail_register_number', $register_number);
    print 'E' .$register_number;
    exit;
  }
}

function gofast_api_mail_get_outbound_register_number($params){
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    gofast_api_forbidden("Unavailable action for external requester");
  }
  
  // Get register number variable or init it
  $register_number = variable_get('gofast_mail_register_number', '0');
  
  // Increment
  $register_number++;
  
  // Api success
  if(!empty($register_number)){
    variable_set('gofast_mail_register_number', $register_number);
    print 'S' . $register_number;
    exit;
  }
}


function gofast_api_mail_get_outbound_space($params){
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    gofast_api_forbidden("Unavailable action for external requester");
  }
  
  $outbound_path = "/Sites/_Groups/_Traitement Courrier/_Traitement Courrier Sortant";
  
  $gid  = gofast_ajax_file_browser_get_nid_from_href($outbound_path, TRUE);
  
  gofast_api_success($gid);
  
}


function gofast_api_mail_send_mail($params){
  if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
    gofast_api_forbidden("Unavailable action for external requester");
  }
  
  if (isset($params['list_nids'])) {
    $list_nids = json_decode($params['list_nids']);
  } else {
    gofast_api_mandatory_parameter('list_nids');
  }
  
  if (isset($params['mails'])) {
    $mails = $params['mails'];
  } else {
    gofast_api_mandatory_parameter('mails');
  }
  $mails = explode(',' , $mails);
  watchdog('debug_avanhove', json_encode($mails));
  watchdog('debug_avanhove', json_encode($list_nids));
  global $base_url;
  
  $nodes_informations = array();

  ## get informations of all nodes to send (icons,build the hash..)
  foreach ($list_nids as $key=>$nid){
    $node = node_load($nid);

    $node_title = $node->title;
    $nodes_informations[$key]['title'] = $node_title;
    $document_version = $node->field_current_version[LANGUAGE_NONE][0]['value'];
    $nodes_informations[$key]['version'] = $document_version;

    ## get node icon
    $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
    ## store the icon in node information
    $nodes_informations[$key]['icon'] = gofast_mail_queue_fa_png($node_icon);
    $nodes_informations[$key]['url'] = $base_url .'/node/' . $nid;
  }
  
  $user = user_load(4);
  $user_name = gofast_user_display_name($user);

  
  $defaultSiteName = "GoFAST";
  
  
  $l = array('langcode' => $user->language, 'context' => 'gofast:gofast_link_sharing');
  $subject = t('Reception d\'un courrier sortant depuis ' . variable_get('site_name', 'GoFast') , array(), $l);;  
  $title = t('Shared documents' , array(), $l);
  $message = t('Ce partage provient d\' un processus de Courrier Sortant' ,array(),array('context' => 'gofast'));
  $footer = t('Message sent from %site_name', array('%site_name' => $defaultSiteName), $l);
  foreach($mails as $mail){
    $mail_active_user = array();
    $mail_active_user[] = array('recpt' => $mail, 'method' => 'to' );
    $mail = trim($mail);
    $body = theme('gofast_manage_linksharing_body', array(
      'author_pic' => theme('user_picture', array('account' => $user, 'dimensions' => 40, 'attributes' => ['width' => 40, 'style' => "border-radius: 5px; width:40px;"])),
      'author_name' => $user_name,
      'author_name' => $user_name,
      'recip_name' => $mail,
      'nodes_informations' => $nodes_informations,
      'download' => gofast_link_sharing_build_link($list_nids, $mail, $user->uid, NULL, TRUE, TRUE),
      'mail_list' => $mails,
      'message' => nl2br($message),
      'expiry_msg' => t(
        'This link will be functional for the next ' . '%exp_period. After this, it will be disabled.',
        array('%exp_period' => t(DEFAULT_EXPIRY_PERIOD_STRING, array(), $l)),
        $l
      ),
      'l' => $l,
    ));
    //Send mail
    $mail = array(
      'body' => $body,
      'title' => $title,
      'subject' => $subject,
      'footer' => $footer
    );
    $ret = gofast_mail_queue_api_queue_ext($mail,  $mail_active_user, time());
    if ($ret == TRUE) {
        flood_register_event('print_mail');
    }
  }
  gofast_api_success('OK');
}
