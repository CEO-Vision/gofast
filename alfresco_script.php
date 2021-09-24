<?php

if (extension_loaded('newrelic')) { // Ensure PHP agent is available
            newrelic_background_job();
 }
 
/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

/**
 * Bootstraping drupal so we can directly run node insert
 */
include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

include(DRUPAL_ROOT . '/sites/default/settings.php');
include(DRUPAL_ROOT . '/sites/all/modules/gofast/gofast_cmis/gofast_cmis_cron.inc');

write_log_info("begin of script", false);

$login_bdd = $databases['default']['default']['username'];
$mdp_bdd = $databases['default']['default']['password'];
$db_connexion = null;
$domain_url = "http://localhost/";

//Inform Alfresco that we received the request, then close the connection and continue the PHP script
//We do that to let alfresco release it's lock on the node and to improve end-user performances
print('OK');
fastcgi_finish_request();
set_time_limit(0);


// --------------------------
// Manage soffice restart
// --------------------------
if($_GET['op'] == GOFAST_CMIS_CRON_OPERATION_RESTART_SOFFICE){
      write_log_info("Operation: restart_soffice", false);
      execute_soffice_restart_command();
      exit;
}

// ------------------------------- 
// Request variables
// ------------------------------- 
$nodes = json_decode($_POST['nodes'], TRUE);
write_log_info($_POST['nodes']);
//For each node asked by the request, we trigger the replication
foreach($nodes as $node){

  $type = $_GET['type'] = $node['type'];
  $messageto = $_GET['messageto'] = $node['messageto'];
  $name = $_GET['name'] = $node['name'];
  $person = $_GET['person'] = $node['person'];
  $space = $_GET['space'] = $node['space'];
  $destination = $_GET['destination'] = $node['destination'];
  $group = $_GET['group'] = $node['group'];
  $noderef = $_GET['noderef'] = $node['noderef'];
  $op = $_GET['op'] = $node['op'];

  write_log_info(":noderef = {$noderef}, :name = {$name}, :type = {$type}, :space = {$space}, :person = {$person}, :destination = {$destination}, :op = {$op}, :messageto = {$messageto}", false);


  // ------------------------------- 
  // Exit conditions
  // ------------------------------- 
  if ($name === "pdf") {
    write_log_info("Name is 'pdf', exiting", false);
    exit;
  }

  //empeche la replication des lock
  if (strstr($name, ".~lock") || strstr($name, ".~$") || strstr($name, "~$")) {
    write_log_info("It's a log file, exiting", false);
    exit;
  }

  //empeche la replication des fichiers commencants par .
  if (isset($name[0]) && $name[0] == ".") {
    write_log_info("File starting by . are ignored, exiting", false);
    exit;
  }

  //empeche la replication des fichiers  .tmp
  if (strstr($name, ".tmp")) {
    write_log_info(".tmp files are ignored, exiting", false);
    exit;
  }

  //empeche la replication des fichiers thumbs.db
  if (strstr($name, "Thumbs.db")) {
    write_log_info("thumbs.db files are ignored, exiting", false);
    exit;
  }

  write_log_info("Current operation : " . $op, false);

  /*if($op === "start_replication") {
    write_log_info("Starting the replication", false);
    check_items_processable();
    return;
  }*/

  switch ($op) {
    case GOFAST_CMIS_CRON_OPERATION_RESTART_SOFFICE:
      $op = GOFAST_CMIS_CRON_OPERATION_RESTART_SOFFICE;
      write_log_info("Operation: restart_soffice", false);
      execute_soffice_restart_command();
      break;
    case GOFAST_CMIS_CRON_OPERATION_SYNC:
      $op = GOFAST_CMIS_CRON_OPERATION_SYNC;
      write_log_info("Operation: Sync", false);
      alfresco_script_synchronize();
      break;
    default:
      write_log_info("Unknown operation ! A mail was sent to CEO-Vision support team", false);
      alfresco_script_send_alert_email("Unknown operation", TRUE);
      break;
  }
}

/*
 * This function send an alert mail to CEO-Vision support team
 * @param $reason
 *   The reason of the alert
 * @param fail
 *   Is this error resulting in a replication fail
 */
function alfresco_script_send_alert_email($reason, $fail = FALSE){
  
  // ------------------------------- 
  // Request variables
  // ------------------------------- 
  $op = $_GET["op"];
  $name = get_parameter_value("name");
  $person = get_parameter_value("person");
  $path = get_parameter_value("destination");
  $gid = get_parameter_value("groupe");
  $noderef = get_parameter_value("noderef");
  
  //Prepare mail
  $criticity = $fail ? "failed" : "warn";
  $subject = "[GoFast Report] Replication " . $criticity . " (Drupal alfresco_script.php)";
  $title = "GoFast Report";
  $footer = "GoFast Report notification E-mail";
  
  $body = "Drupal received a replication request but an error occured. Criticity: " . $criticity;
  $body .= "<br />Reason: " . $reason;
  $body .= "<div><table>";
  $body .= "<tr><td>Node reference</td><td>Operation</td><td>Title</td><td>Space ID</td><td>Creator</td><td>Destination path</td>";
  $body .= "<tr><td>". $noderef ."</td><td>". $op ."</td><td>". $name ."</td><td>". $gid ."</td><td>". $person ."</td><td>". $path ."</td></tr>";
  $body .= "</table></div>";
  
  $recpt = array(array('recpt' => 'support@ceo-vision.com', 'method' => 'to'));
  
  //Send mail
  gofast_mail_queue_api_send_mail($subject, $title, $footer, $body, $recpt);
}

/*
 * Trigger the replication using instant replication mode
 */
function alfresco_script_synchronize(){
  // -------------------------------
  // Request variables
  // -------------------------------
  $name = get_parameter_value("name");
  $person = get_parameter_value("person");
  $path = get_parameter_value("destination");
  $gid = get_parameter_value("space");
  $noderef = get_parameter_value("noderef");
  $author = get_parameter_value("author");
  $op = $_GET["op"];
  
  //Ask database to know what to do with the request
  $presence = check_item_already_present($noderef, $op);
  
  //Insert the row in the table if needed
  if($presence == "UNKNOWN"){ //No entry found
    write_log_info("No other entry found in database, processing the request", false);
    
    if(alfresco_script_replication_mode(user_load_by_name($person)->uid)){ //Mode: Instant replication
      $row = insert_db_row($noderef, GOFAST_CMIS_CRON_PROCESSING_PROCESS, $op, $name, $person, $path, $gid, $author);
      
      //Process the item
      module_load_include('inc', 'gofast_cmis', 'gofast_cmis_cron');
      write_log_info("Mode : Instant replication", false);
      $return = gofast_cmis_process_item($noderef, $name, $person, $path, $gid, $author);
      usurp(-1);
      
      //Delete the row at the end of the process
      if($return != 2){
        delete_db_row($row);
      }
    }
    
    else{ //Mode : Cron replication
      write_log_info("Mode : Cron replication", false);
      $row = insert_db_row($noderef, GOFAST_CMIS_CRON_PROCESSING_WAIT, $op, $name, $person, $path, $gid, $author);
    }
    write_log_info("Processing finished !", false);
  }
  else if($presence == "FULL"){ //Already in queue
    write_log_info("This request is already processing, exiting", false);
    exit();
  }
  else{ //Shouldn't happend
    write_log_info("Unknown item presence state, exiting and sending a mail to CEO-Vision support team", false);
    alfresco_script_send_alert_email("Unknown item presence state", TRUE);
    exit();
  }
}

function alfresco_script_replication_mode($uid){
  $connexion = get_db_connexion();

  $stmt = $connexion->prepare("SELECT state from alfresco_replication WHERE uid = :uid");
  $stmt->bindParam(':uid', $uid);
  $stmt->execute();

  $result = $stmt->fetchAll();

  $count = count($result);
  
  if($count > GOFAST_CMIS_REPLICATING_MAX_ACTIVITY){ //Mode cron
    return FALSE;
  }
  else{ //Mode instant replication
    return TRUE;
  }
}

/**
 * This function creates a file that triggers soffice restart.
 */
function execute_soffice_restart_command() {
  $file = fopen(DRUPAL_ROOT . "/sites/default/files/restart_soffice.txt", "a+");
  fwrite($file, $_SERVER['REQUEST_URI'] . "\n\n");
  fclose($file);
}

/**
 * This method returns parameter value if exists, empty string otherwise
 * @param type $param_name the parameter to get in $_GET request variable
 * @return string the value of the parameter if exists, empty string otherwise.
 */
function get_parameter_value($param_name) {
  return isset($_GET[$param_name]) ? $_GET[$param_name] : "";
}

/**
 * This method inserts a new row corresponding to remote store item. These row are used for replication and contains all the necessary info for Drupal to process.
 * @param type $noderef the remote store reference
 * @param type $op the operation done in remote store
 * @param type $person the person that triggers this event on remote store
 * @param type $name the name of the node if needed
 * @param type $type the type of item replicated
 * @param type $space the root item in which the item is processed (ex: added in a parent folder)
 * @param type $destination TODO
 * @param type $messageto TODO
 */
function insert_db_row($noderef, $state, $op, $name, $person, $path, $gid, $author) {

  $connexion = get_db_connexion();
  
  $time = time();
write_log_info("Inserting: " . $noderef . $state . $op . $person, false);
  $stmt = $connexion->prepare("INSERT INTO alfresco_replication (noderef,name,person,path,gid,author,uid,op,state,runsince) VALUES (:noderef, :name, :person, :path, :gid, :author, :uid, :op, :state, :runsince)");
  $stmt->bindParam(':noderef', $noderef);
  $stmt->bindParam(':name', $name);
  $stmt->bindParam(':person', $person);
  $stmt->bindParam(':path', $path);
  $stmt->bindParam(':gid', $gid);
  $stmt->bindParam(':author', $author);
  $stmt->bindParam(':uid', user_load_by_name($person)->uid);
  $stmt->bindParam(':op', $op);
  $stmt->bindParam(':state', $state);
  $stmt->bindParam(':runsince', time());
  $result = $stmt->execute();
  $success = $result ? "true" : "false";
  
  $row = $connexion->lastInsertId();
  write_log_info("insert_db_row. Success = " . $success . ' ('.$row.')', false);
  if($success == "false"){
    alfresco_script_send_alert_email("Database insert failed for " . $noderef, TRUE);
    exit();
  }
  return $row;
}

/*
 * Delete the specified row in the alfresco replication table
 */
function delete_db_row($aid) {

  $connexion = get_db_connexion();
  
  $time = time();
  write_log_info("Deleting row: " . $aid, false);
  $stmt = $connexion->prepare("DELETE FROM alfresco_replication WHERE aid=:aid");
  $stmt->bindParam(':aid', $aid);
  $result = $stmt->execute();
  $success = $result ? "true" : "false";
  write_log_info("delete_db_row. Success = " . $success, false);
  if($success == "false"){
    alfresco_script_send_alert_email("Database delete failed for row ".$aid, TRUE);
    exit();
  }
  return TRUE;
}

/**
 * Check if another request is present and either, return the current state 
 * States:
 *  -UNKNOWN
 *    No other request found
 *  -PROCESSING
 *    The replication is processing
 *  -FULL
 *    A waiting request was already found
 * @param type $noderef
 * @param type $op
 * @return type
 */
function check_item_already_present($noderef, $op) {
  $connexion = get_db_connexion();

  $stmt = $connexion->prepare("SELECT state from alfresco_replication WHERE noderef = :noderef AND op = :op");
  $stmt->bindParam(':noderef', $noderef);
  $stmt->bindParam(':op', $op);
  $stmt->execute();

  $result = $stmt->fetchAll();

  $count = count($result);
  if($count == 0){ //No request
    $return =  "UNKNOWN";
  }
  else{
    $return = "FULL";
  }
  return $return;
}

/**
 * This method connects to the database and returns the PDO connexion objet.
 * If the PDO connexion already exists, returns the object.
 * @return type
 */
function get_db_connexion() {
  global $db_connexion, $login_bdd, $mdp_bdd;
  $logInfo = null !== $db_connexion ? "Retrieving previouly created connexion" : "Creating connexion : login = " . $login_bdd . ", pwd = " . $mdp_bdd;
  //write_log_info($logInfo, false);
  $db_connexion = null !== $db_connexion ? $db_connexion : new PDO('mysql:host=localhost;dbname=d7', $login_bdd, $mdp_bdd);
  return $db_connexion;
}

/**
 * This method logs each request made to the server and logs additionnal information if provided.
 * @param type $info the information we want to add to log line.
 * @param boolean $request boolean that indicates to log the request or not
 */
function write_log_info($info = null, $request = true) {
  $execution_date = date("Y-m-d H:i:s");
  $file = fopen("/var/www/d7/sites/default/files/logs/alfresco_script.log", "a+");
  $request_data = $request ? " - Request = " . $_SERVER['REQUEST_URI'] : "";
  $informations = null !== $info ? " - Infos = " . $info : "";
  fwrite($file, $execution_date . $request_data . $informations . "\n");
  fclose($file);
}

write_log_info("end of script", false);