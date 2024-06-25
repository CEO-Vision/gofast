<?php

/* 
 * GoFAST API
 * WIP
 * 
 * How to use : 
 * Name your callback :  gofast_api_RESSOURCE_ACTION
 * This function will be callable using the URL /api/RESSOURCE/ACTION.
 * Parameters can be passed through POST body or URL params
 * 
 * Exemple : /api/gofast/get_version
 * Will match gofast_api_gofast_get_version
 * 
 * The output of the function must be an array with at least an HTTP return code
 */

/*
 * Implements hook_menu
 * As the API is part of the gofast module, this hook is called
 * in the hook_menu of the gofast module
 */
function gofast_api_menu(){
  $items = array();
  $items['api'] = array(
    'title' => 'GoFast API',
    'description' => 'GoFast API service',
    'page callback' => 'gofast_api',
    'page arguments' => array(1,2),
    'access callback' => TRUE,
  );
  return $items;
}

/*
 * CORE FUNCTION - DO NOT MODIFY UNLESS YOU KNOW WHAT YOU DO
 * 
 * Entry point for the GoFAST API
 * This function will check if a ressource and an action are mentionned as POST or GET param
 * Then, it will check if the function gofast_api_RESSOURCE_ACTION exists
 * Then, it will call the function and ask the output rendering
 */
function gofast_api($ressource = null, $action = null){
  $output = array();
  global $user;

  //Prevent using a ressource that is actually a method
  if(in_array(strtoupper($ressource), array('GET', 'POST', 'PUT', 'DELETE', 'OPTIONS'))){
      gofast_api_forbidden("Forbidden usage of a method as a ressource");
  }
  
  //Retrieve parameters and headers
  $params = array_merge($_POST, $_GET, getallheaders());
  $params['method'] = $_SERVER['REQUEST_METHOD'];
  
  //Default content type : application/json
  $params['Content-Type'] = empty($params['Content-Type']) ? "application/json" : $params['Content-Type'];
  
  if(strpos($params['Content-Type'], "application/json") !== FALSE && json_decode(file_get_contents("php://input"), true) != null){
    $params = array_merge($params, json_decode(file_get_contents("php://input"), true));
  }
  
  $authorization = $_SERVER['REDIRECT_HTTP_AUTHORIZATION'];
  $token = isset($params['Token']) ? $params['Token'] : $params['token'];
  
  //Check if mandatory parameters are mentionned
  $ressource = empty($ressource) ? $_GET['ressource'] : $ressource;
  $action = empty($action) ? $_GET['action'] : $action;
  $ressource = empty($ressource) ? $_POST['ressource'] : $ressource;
  $action = empty($action) ? $_POST['action'] : $action;
  if(empty($ressource)){ //No ressource requested
    $output = gofast_api_mandatory_parameter("ressource");
    gofast_api_output($output);
  }
  if(empty($action)){ //No action requested
    $output = gofast_api_mandatory_parameter("action");
    gofast_api_output($output);
  }
  
  if(empty($params)){ //No params
    $params = array();
  }

  //Make params available everywhere
  $_POST['API_PARAMS'] = $params;
  
  //Check if we need authentication
  if($user->uid == 0 && !empty($authorization)){
    //Decode authentication header
    $authorization = str_replace('Basic ', '', $authorization);
    $authorization = base64_decode($authorization);
    $authorization = explode(":", $authorization);
    
    $login = $authorization[0];
    $password = $authorization[1];
    $user_check = user_load_by_name($login);
    $usurped = TRUE;
    usurp($user_check->uid);
    
    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $LdapServer->connectAndBindIfNotAlready();
    
    if($LdapServer->bind(gofast_ldap_user_dn($user_check), $password, FALSE) == LDAP_SUCCESS && $user_check->status == 1){ //Authentify against drupal
      //Authentication successfull
      gofast_cmis_retrieve_and_store_ticket($user);
      $LdapServer->disconnect();
      $LdapServer->connectAndBindIfNotAlready();
      
      //Register successful authrntication
      flood_register_event('failed_login_attempt_ip');
      flood_clear_event('failed_login_attempt_user', $params['auth']['localpart']);
      _login_security_remove_events($login);
    }else{ //Authentication failed
      usurp(FALSE);
      
      //Register failed authentication
      flood_register_event('failed_login_attempt_ip', variable_get('user_failed_login_ip_window', 3600));
      flood_register_event('failed_login_attempt_user', variable_get('user_failed_login_user_window', 21600), $login);
      _login_security_add_event($login, ip_address());
      $track = [ 'values' => [ 'name' => $login ] ];
      login_security_validate(null, $track);
      
      $output = gofast_api_forbidden("Bad authentication method provided");
      gofast_api_output($output);
    }
  }
  if($user->uid == 0 && !empty($token)){
      //Check if we have a corresponding token
      $db_token = db_select("gofast_token", "gt")
              ->fields('gt', array("uid", "token"))
              ->condition("token", $token)
              ->condition("timestamp", time(), ">")
              ->execute()
              ->fetchAll();
      
      if(count($db_token) == 1){
          //Authentication successfull
          $usurped = TRUE;
          usurp($db_token[0]->uid);
          gofast_cmis_retrieve_and_store_ticket($user);
      }else{
          usurp(FALSE);
          $output = gofast_api_forbidden("Bad authentication method provided");
          gofast_api_output($output);
      }
  }
  
  if($params['method'] == "OPTIONS"){ //OPTIONS request
    //Check if the required action exists for the requested ressource with the requested METHOD
    $funct = "gofast_api_options_" . $ressource . '_' . $action;

    if(function_exists($funct)){
      $output = call_user_func($funct, $params);
      if($usurped){
          usurp(FALSE);
      }
      gofast_api_output($output);
    }else{
        //All checks passed, call the action
        gofast_api_options();
        $output = gofast_api_success("OPTIONS");
        if($usurped){
            usurp(FALSE);
        }
    }
  }else{ //Other request
    //Check if the required action exists for the requested ressource
    $funct = "gofast_api_" . $ressource . '_' . $action;

    if(!function_exists($funct)){
      $output = gofast_api_not_implemented("This ressource or this action");
      if($usurped){
          usurp(FALSE);
      }
      gofast_api_output($output);
    }
    
    //All checks passed, call the action 
    $output = call_user_func($funct, $params);
    if($usurped){
      usurp(FALSE);
    }
  }
  gofast_api_output($output);
}

/*
 * CORE FUNCTION - DO NOT MODIFY UNLESS YOU KNOW WHAT YOU DO
 * 
 * Answer to an OPTIONS request
 */
function gofast_api_options(){
  drupal_add_http_header("Access-Control-Allow-Headers", "Access-Control-Allow-Origin, Access-Control-Allow-Headers, Access-Control-Allow-Methods");
}

/*
 * CORE FUNCTION - DO NOT MODIFY UNLESS YOU KNOW WHAT YOU DO
 * 
 * Render and print the output of the API
 */
function gofast_api_output($output){
  //Retrieve parameters
  $content_type = $output['Content-Type'];
  $content_disposition = $output['Content-Disposition'];
  $code = $output['code'];
  
  if(!is_array($output['data']) && (empty($output['data'])) || empty($content_type) || empty($code)){ //Check if we have all needed informations
      $output = gofast_api_internal_server_error("Bad response");
  }
  //Prepare the output
  $output = $output['data'];
  
  //Attach headers
  drupal_add_http_header('Content-Type', $content_type);
  
  if(!empty($content_disposition)){
      drupal_add_http_header('Content-Disposition', $content_disposition);
  }
  
  drupal_add_http_header('Status', $code);
  
  switch($content_type){ //Fetch into content types and render
    case 'application/json':
    case 'application/json; charset=UTF-8':
    case 'application/x-www-form-urlencoded';
    case 'application/x-www-form-urlencoded; charset=UTF-8':
      print(json_encode($output));
      exit;
      break;
    case 'application/octet-stream';
    case 'application/pdf';
      print($output);
      exit;
      break;
    default:
      gofast_api_not_implemented("This content type");
      break;
  }
}

/*
 * Implements API gofast_api_RESSOURCE_ACTION
 * @ressource gofast
 * @action get_version
 * @params 
 *    $full : Tell either we need to return the full output or just the version
 * 
 * Return the current gofast version
 */
function gofast_api_gofast_get_version($full = TRUE){
  $output = array();
  
  $manifest = gofast_update_get_release_manifest();
  $version = gofast_update_get_gofast_version($manifest);
  
  //PLEASE READ : This is a bad thing to do, we will need to update GoFAST COMM update script and then use gofast_api_success() here.
  
  if(isset($version['infos'])){
    $full ? $output['data'] = $version : $output['data'] = $version['infos']['versionNumber'];
    //Also return repository server address
    $output['repo'] = GOFAST_REPOSITORY_SERVER;
  }
  $output['Content-Type'] = "application/json";
  $output['code'] = "200 OK";
  drupal_add_http_header('Content-Type', $output['Content-Type']);
  drupal_add_http_header('Status', $output['code']);
  print json_encode($output);
  exit;
}

/*
 * Function used to prepare a 403 Unauthorized response
 */
function gofast_api_not_authorized($message = "Not authorized"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = '401 Unauthorized';
  $output['data'] = array('message' => $message); 
  gofast_api_output($output);
}

/*
 * Function used to prepare a 403 Forbidden response
 */
function gofast_api_forbidden($message = "Forbidden"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = '403 Forbidden';
  $output['data'] = array('message' => $message);
  gofast_api_output($output);
}

/*
 * Function used to prepare a 404 Not found
 * @params
 *    $message : Message to send
 */
function gofast_api_not_found($message = "Not found"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = '404 Not Found';
  $output['data'] = array('message' => $message);
  gofast_api_output($output);
}

/*
 * Function used to prepare a 500 Internal Server Error
 */
function gofast_api_internal_server_error($message = "Error"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = '500 Internal Server Error';
  $output['data'] = array('message' => $message);
  gofast_api_output($output);
}

/*
 * Function used to prepare a 501 Not Implemented
 * @params
 *    $subject : Inform on what is not implemented
 */
function gofast_api_not_implemented($subject = "This"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = '501 Not Implemented';
  $output['data'] = array('message' => $subject . " is not implemented by the server");
  gofast_api_output($output);
}

/*
 * Function to prepare a 400 Bad Request response because of a mandatory parameter missing
 * @params
 *    $param_name : Name of the missing mandatory parameter
 */
function gofast_api_mandatory_parameter($param_name = "There"){
  $output = array();
  $output['Content-Type'] = "application/json";
  $output['code'] = "400 Bad Request";
  $output['data'] = array('message' => $param_name . " is a mandatory parameter");
  gofast_api_output($output);
}

/*
 * Function to prepare a 400 Bad Request response because of a mandatory parameter missing
 * @params
 *    $param_name : Name of the missing mandatory parameter
 */
function gofast_api_success($output, $code = "200 OK", $content_type = "application/json", $content_disposition = null,$return_value=FALSE){
  $data = $output;
  $output = array();
  $output['data'] = $data;
  $output['Content-Type'] = $content_type;
  $output['Content-Disposition'] = $content_disposition;
  $output['code'] = $code;
  if ($return_value == TRUE){
    return $output;
  }
  gofast_api_output($output);
}
