<?php
 
/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', "/var/www/d7");

/**
 * Bootstraping drupal
 */
include_once DRUPAL_ROOT . '/includes/bootstrap.inc';
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);

watchdog("debug webdav type", $_SERVER['REQUEST_METHOD']);
watchdog("debug webdav url", str_replace("/var/www/d7", "", $_SERVER['PATH_TRANSLATED']));
global $user;
$string_headers = "";
$excluded_headers = array("Atatus-Apm-Traceparent", "Origin", "Referer", "Content-Length", "X-Forwarded-Server", "X-Forwarded-Host", "X-Forwarded-For", "Cookie","Sec-Fetch-Dest", "Sec-Fetch-User", "Sec-Fetch-Mode", "Sec-Fetch-Site",
                      "Connection", "Accept-Language","Accept", "Accept-Encoding", "Content-Type", "Sec-Ch-Ua-Platform", "Host", "User-Agent", "Upgrade-Insecure-Requests", "Sec-Ch-Ua-Platform", "Sec-Ch-Ua-Mobile", "Sec-Ch-Ua", "Depth");
foreach(getallheaders() as $key=>$value){
    if(!in_array($key, $excluded_headers)){
        $string_headers .= trim(str_replace("gofast-preprod.ceo-vision.com", "localhost",$key)).":".trim(str_replace("gofast-preprod.ceo-vision.com", "localhost",$value).";");
    }
}

if($user->uid != 0){
    $method = $_SERVER['REQUEST_METHOD'];  
    $webdav_url = str_replace("/var/www/d7", "", $_SERVER['PATH_TRANSLATED']);
    $ticket = $_SESSION['gofast_user_alf_ticket'];
    $url = "http://localhost:8080/alfresco/webdav".$webdav_url."?ticket=".$ticket;
    $request_body = file_get_contents('php://input');
    $request_body = str_replace('<?xml version="1.0"?>', "", $request_body);
    $ch = curl_init();
    $depth = $_SERVER["HTTP_DEPTH"];
    if($depth !== null){
       $webdav_headers = "depth:1";
       $string_headers .= "depth:1";
      // curl_setopt($ch, CURLOPT_HTTPHEADER, array($webdav_headers));
    }
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    if($method == "MOVE"){
       $webdav_headers = "destination:".$_SERVER["HTTP_DESTINATION"].";overwrite:F";
       curl_setopt($ch, CURLOPT_HTTPHEADER, array($webdav_headers)); 
       curl_setopt($ch, CURLOPT_RETURNTRANSFER, 0);
    }
    
   // print_r("<pre>");print_r(getallheaders());print_r($string_headers);exit;
    watchdog("debug webdav headers", $string_headers);
   // $webdav_headers = $string_headers;
    curl_setopt($ch, CURLOPT_HTTPHEADER, array($string_headers));
      
    
    curl_setopt($ch, CURLOPT_POSTFIELDS, $request_body);    
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $method);
  
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_TIMEOUT, 3);
    $buffer = curl_exec($ch);   
  //  print_r($webdav_headers);
  //  print_r("<pre>");print_r($buffer);exit;
    $buffer = str_replace("[Up a level]</a>", "[Up a level]</a></td>", $buffer);
    $buffer = str_replace("&nbsp;", "   ", $buffer);
    $httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    http_response_code($httpcode);
    header('Content-Type: text/xml;charset=UTF-8'); 
    print $buffer;
    exit;
}else{
  $user_ticket = str_replace("ticket=","",$_SERVER['QUERY_STRING']);
  $url = "http://localhost/alfresco/service/api/login/ticket/" . $user_ticket . "?alf_ticket=" . $user_ticket;
  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_setopt($ch, CURLOPT_FILETIME, TRUE);
  curl_setopt($ch, CURLOPT_NOBODY, FALSE);
  curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
  curl_setopt($ch, CURLOPT_HEADER, TRUE);
  curl_setopt($ch, CURLOPT_TIMEOUT, 3);

  $header = curl_exec($ch);
  $info = curl_getinfo($ch, CURLINFO_HTTP_CODE);
  curl_close($ch);
  if($info !== 200){
    watchdog("debug webdav http code error", $httpcode);
    print_r("NOT NONNECTED");exit;
  }else {
    $method = $_SERVER['REQUEST_METHOD'];  
    $webdav_url = str_replace("/var/www/d7", "", $_SERVER['PATH_TRANSLATED']);
    $ticket = $user_ticket;
    $url = "http://localhost:8080/alfresco/webdav".$webdav_url."?ticket=".$ticket;
    $request_body = file_get_contents('php://input');
    $request_body = str_replace('<?xml version="1.0"?>', "", $request_body);
    
    $ch = curl_init();
    $depth = $_SERVER["HTTP_DEPTH"];
    if($depth !== null){
       $webdav_headers = "depth:1";
       $string_headers .= "depth:1";
       //curl_setopt($ch, CURLOPT_HTTPHEADER, array($webdav_headers));
    }
   
     watchdog("debug webdav headers", $string_headers);
   
    if($method == "HEAD"){
        curl_setopt($curl, CURLOPT_HEAD, true);
        curl_setopt($curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_URL, $url);
    }else{
        curl_setopt($ch, CURLOPT_HTTPHEADER, array($string_headers));
        curl_setopt($ch, CURLOPT_POSTFIELDS, $request_body); 
        curl_setopt($ch, CURLOPT_CUSTOMREQUEST, $method);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_TIMEOUT, 3);
    }
   
   
    $buffer = curl_exec($ch);
    $buffer = str_replace("[Up a level]</a>", "[Up a level]</a></td>", $buffer);
    $buffer = str_replace("&nbsp;", "   ", $buffer);
    $httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    watchdog("debug webdav http code", $httpcode);
    http_response_code($httpcode);
   // if($method !== "HEAD"){
         watchdog("debug webdav buffer", json_encode($buffer));
        header('Content-Type: text/xml;charset=UTF-8'); 
   // }
    print $buffer;
    exit;
  }
}


