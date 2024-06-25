<?php

/**
 * function to get value of all mail metadtas of a node
 *
 * @param object $node
 * @return array $node_metadata
 */
function gofast_mail_inbound_outbound_get_extra_metadatas($node) {

  $node_metadata = array();
  $mail_metadata = json_decode(variable_get('gofast_mail_metadata'));

  // Reach all metadata and fill the array
  foreach ($mail_metadata as $metadata) {
    $machine_name = str_replace('field_', '', $metadata);
    $node_metadata[$metadata] = array(
      'machine_name' => $machine_name,
      'value' => $node->$metadata[LANGUAGE_NONE][0]['value']
    );
  }

  return $node_metadata;
}

/**
 * Create subspace mail
 *
 * @param string $parent_id
 * @return string $_POST['new_space_nid] nid of subspace created
 */
function gofast_mail_inbound_outbound_create_mail_subspace($parent_id)
{

  global $user;

  $parent = node_load($parent_id);
  $file_decoded_name = 'Traitement des courriers';
  $options = array(
    'author' => $user->uid,
    'description' => t('~ created automatically ~', array(), array('context' => 'gofast')), // this field is required
    'body' => '',
    'parent' => $parent_id,
  );
  gofast_og_create($file_decoded_name, $parent->type, $options);
  return $_POST['new_space_nid'];
}

/**
 * Get admin members of the given space
 *
 * @param string $parent_id
 * @return array $users_admins
 */
function gofast_mail_inbound_outbound_get_admin_space($parent_id)
{
  $users_admins = gofast_userlist_og_get_node_members_by_role($parent_id, array(OG_STATE_ACTIVE), "administrator member");
  return $users_admins;
}

/**
 * Create mail userlist
 *
 * @param string $space_name
 * @param array $admins_users
 * @return string $ulid
 */
function gofast_mail_inbound_outbound_create_userlist($space_name, $admins_users)
{

  // create userlist
  $name_userlist = "Traitement courrier " . $space_name;
  $description = "Cette liste utilisateur est administratrice de l'espace 'Traitement courrier' de l'espace " . $space_name;
  $nid = gofast_userlist_create_userlist($name_userlist,  $description);
  $mail_userlist = node_load($nid);

  //Get userlist roles
  $roles_query = og_roles('node', "userlist", $nid, FALSE, FALSE);
  foreach ($roles_query as $rkey => $roles) {
    if ($roles == GOFAST_OG_ROLE_ADMIN) {
      $admin_rid = $rkey;
    }
    if ($roles == GOFAST_OG_ROLE_READ_ONLY) {
      $readonly_rid = $rkey;
    }
    if ($roles == GOFAST_OG_ROLE_STANDARD) {
      $contributor_rid = $rkey;
    }
  }

  $admins_uid = array();

  // Regroup all admins uid (userlist && members)
  foreach ($admins_users as $archivist => $admin_user) {
    if($admin_user->entity_type == 'userlist'){
      $userlist_members = gofast_userlist_get_members($admin_user->etid, FALSE);
      $userlist_uid_members = array_keys($userlist_members);
      $admins_uid = array_merge($admins_uid, $userlist_uid_members);
    }else{
      $uid = $admin_user->etid;
      $admins_uid[] = $uid;
    }
  }

  // Add role
  foreach(array_unique($admins_uid) as $key => $admin_uid){
    gofast_og_subscribe_user($nid, $admin_uid);
    og_role_grant('node', $nid, $admin_uid, $admin_rid);
  }

  // Add members to userlist
  gofast_userlist_add_members($nid, array_unique($admins_uid));

  $ulid = $mail_userlist->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
  return $ulid;
}

/**
 * Get all mail spaces id
 *
 * @return array $results
 */
function gofast_mail_inbound_outbound_get_mail_spaces(){
  $query = db_select('field_data_field_mail_ulid', 'fulid');
  $query->fields('fulid', array('entity_id'));
  $results = $query->execute()->fetchAll();
  return $results;
}

/**
 * Start mail outbound workflow
 *
 * @param string $inboundNids
 * @param string $departmentName
 * @param string $listInboundActors
 * @return void
 */
function gofast_mail_start_outbound_workflow($inboundNids = NULL, $departmentName = NULL, $listInboundActors = NULL, $listNids = NULL, $isResponse = TRUE, $listOutboundInitActors = NULL){
  
  gofast_workflows_get_cookie(true);
  $cookie_name = "cookie_bonitaadm.txt";

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_POST, 0);
  curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/$cookie_name");

  $url = URL_BONITA . "API/bpm/process?p=0&c=10&o=displayName%20ASC&f=name%3dCourrier%20sortant";
  curl_setopt($ch, CURLOPT_URL, $url);
  $array_results = json_decode(gofast_workflows_curl_exec($ch), true);
  $workflow_process_id = end($array_results)['id'];
  
  //Convert listInboundActors into good values for UI Designer (Display Name (mail / username)) 
  $inboundActors = array();
  $array_actors = array_unique(json_decode($listInboundActors,true));
  
  foreach ($array_actors as $actor_username) {
    // Check if user exist in gofast
    $actor_user = user_load_by_name($actor_username);
    if(!empty($actor_user->uid)){
      $inboundActors[] = array(
        'title' => $actor_user->ldap_user_displayname[LANGUAGE_NONE]['0']['value'] . ' (' . $actor_username . ' / ' . $actor_user->mail . ')',
        'uid' => $actor_username
      );
    }
  }
  
  if($isResponse){
    $comment = "Ce processus est généré par un courrier entrant necessitant une réponse";
  }else{
    $comment = "Ce processus de courrier sortant est generé automatiquement";
  }
  
  # Get variables
  $variables = array(
    "processInitInput" => array(
      "title" => "Courrier sortant",
      "comment" => $comment,
      "deadline" => "",
      "register_date" => "",
      "register_number" => "",
      "mail_object" => "",
      "mail_recipient" => "",
      "is_validation_ordered" => false,
      "is_signature_ordered" => false,
      "nids" => !empty($listNids) ? $listNids : [],
      "is_response" => $isResponse,
      "auto_launch" => $isResponse ? false : true,
      "acknowledgment" => false,
      "transform_before_signature" => false,
      "alreadyWrite" => false,
      "department" => !empty($departmentName) ? $departmentName : "",
      "uids_types" => [],
      "inbound_nids" => !empty($inboundNids) ? json_decode($inboundNids) : [],
      "inbound_actors" => !empty($inboundActors) ? json_encode($inboundActors) : "",
      "outbound_actors" => !empty($listOutboundInitActors) ? json_decode($listOutboundInitActors) : []
    )
  );
  
  $url = URL_BONITA . "API/bpm/process/" . $workflow_process_id . "/instantiation";
  $data_string = json_encode($variables);

  curl_setopt($ch, CURLOPT_HTTPHEADER, array(
      'Content-Type: application/json',
      'Content-Length: ' . strlen($data_string)
  ));
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_VERBOSE, true);


  curl_setopt($ch, CURLOPT_POST, 1);
  curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
  curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/" . $cookie_name);

  curl_setopt($ch, CURLOPT_URL, $url);

  $array_results = gofast_workflows_curl_exec($ch);
  curl_close($ch);
  return $array_results;
}


function gofast_mail_inbound_outbound_start_workflow_outbound($list_nids, $departmentName, $isImputedSE, $listInboundActors){

    watchdog("debug start workflow amrtp outbound", json_encode($list_nids));
    //we search for the processDefinitionId corresponding to our workflow

    $return_cookie = gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonitaadm.txt";

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_POST, 0);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/$cookie_name");

    $url = URL_BONITA . "API/bpm/process?p=0&c=10&o=displayName%20ASC&f=name%3dCourrier%20sortant%20AMRTP";
    curl_setopt($ch, CURLOPT_URL, $url);
    $array_results = json_decode(gofast_workflows_curl_exec($ch), true);
    $workflow_process_id = end($array_results)['id'];

    # Get variables
    $variables = array(
      "comment" => "Ce processus est généré par un courrier entrant necessitant une réponse",
      "document" => "",
      "isResponse" => true,
      'isImputedSE' => $isImputedSE,
      "departmentName" => $departmentName,
      'listInboundActors' => json_decode($listInboundActors, true),
      "listInboundMails" => json_decode($list_nids,true),
      "annexes" => []
    );
    watchdog('debug_amrtp', json_encode($variables));

    $url = URL_BONITA . "API/bpm/process/" . $workflow_process_id . "/instantiation";
    // $encoded_data =  preparePostFields($data);
    //,'variables':[{'name':'home','value':'sfgs'},{'name':'addr','value':'234234'}] - See more at: http://community.bonitasoft.com/answers/start-case-rest-api-and-jquery#sthash.QyFYpPmy.dpuf
    $data_string = json_encode($variables);

    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($data_string)
    ));
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);


    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/" . $cookie_name);

    curl_setopt($ch, CURLOPT_URL, $url);

    $array_results = gofast_workflows_curl_exec($ch);
    curl_close($ch);
    return $array_results;
}

/**
 * Set alfresco mail aspect
 */
function gofast_mail_inbound_outbound_cmis_set_mail_aspect($reference){


  $url = "http://localhost:8080/alfresco/service/set/mail_aspects?reference=" . $reference;

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
 * Remove alfresco mail aspect
 */
function gofast_mail_inbound_outbound_cmis_remove_mail_aspect($reference){

  $url = "http://localhost:8080/alfresco/service/remove/mail_aspects?reference=" . $reference;

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

function gofast_workflows_get_inbound_mail_pid(){
  $cookie_name = "cookie_bonita" . BONITA_TECHNICAL_LOGIN . ".txt";
  gofast_workflows_delete_cookie($cookie_name);
  gofast_workflows_get_cookie(true);

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_POST, 0);
  curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/$cookie_name");

  $url = URL_BONITA . "API/bpm/process?p=0&c=10&o=displayName%20ASC&f=name%3dCourrier%20entrant";
  curl_setopt($ch, CURLOPT_URL, $url);
  $array_results = json_decode(gofast_workflows_curl_exec($ch), true);
  $workflow_process_id = end($array_results)['id'];
  
  return $workflow_process_id;
}


function gofast_workflows_get_actors($process_id){
  
  
  $url = URL_BONITA . "/API/bpm/actor?p=0&c=10&f=process_id=" . $process_id . "&n=users&n=group&n=roles&n=memberships";
  
  $cookie_name = "cookie_bonita" . BONITA_TECHNICAL_LOGIN . ".txt";
  gofast_workflows_delete_cookie($cookie_name);
  gofast_workflows_get_cookie(true);
  
  
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_POST, 0);
  curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/$cookie_name");
  curl_setopt($ch, CURLOPT_URL, $url);
  $process_actors = json_decode(gofast_workflows_curl_exec($ch), true);
  curl_close($ch);
  return $process_actors;
}


function gofast_workflows_curl_get_group_info($group_id){
  
  $url = URL_BONITA . "/API/identity/group/" . $group_id;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_HEADER, 0);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($ch, CURLOPT_POST, 0);
  curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/cookie_bonitaadm.txt");
  curl_setopt($ch, CURLOPT_URL, $url);
  $group_members = json_decode(gofast_workflows_curl_exec($ch), true);
  curl_close($ch);
  return $group_members;
}

function gofast_mail_inbound_outbound_download_zip(){

  //Check if we have a nid param
  if (isset($_GET['nids'])) {
    $nids = $_GET['nids'];
  } else {
    return;
  }
  
  if (isset($_GET['register_date'])) {
    $date = $_GET['register_date'];
  } else {
    return;
  }
  $date = date("d-m-Y", strtotime($date)); 
  
  if (isset($_GET['reference'])) {
    $reference = $_GET['reference'];
  } else {
    return;
  }

  $nids = json_decode($nids, true);
  // Render zip files
  $zip = gofast_multi_link_sharing_generate_zip_file($nids);
  //Prepare buffer for stream
  while (ob_get_level()) ob_end_clean();

  $file_name = "Courrier-sortant_" . $date . "-" . $reference . ".zip";

  ## send the file to the browser as a download
  header('Content-disposition: attachment; filename="'.$file_name.'"');
  header('Content-type: application/zip');
  header('Content-Length: ' . filesize($zip));
  readfile($zip);
  unlink($zip);

  # need to exit because other header overload both header
  print $zip;
  exit;
}
