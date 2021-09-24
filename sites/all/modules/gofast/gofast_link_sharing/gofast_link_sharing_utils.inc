<?php

/**
 * Return if a gofast session is currently present in the browser
 * 
 * @param node $curr_user
 *    Node of the current_logged_user (if there is one)
 * @return boolean
 *    TRUE if a gofast session exists, else FALSE 
 */
function gofast_link_sharing_is_gofast_user($curr_user){
  $is_gofast_user = FALSE;
 
  if (isset($curr_user->uid) && $curr_user->uid != 0){
    $is_gofast_user = TRUE;
  }

  return $is_gofast_user;
}

/**
 * Return if the current user has permission to access the node
 * 
 * It checks if the current logged user can access to the document in
 * 'view' mode.
 * 
 * @param node $node
 *    Drupal node of the document to be access
 * @param node $curr_user
 *    Drupal current user
 * 
 * @return boolean
 *    TRUE if user can 'view' the document, else return FALSE
 */
function gofast_link_sharing_usr_has_access($node, $curr_user=NULL){
  //Check if user has access to the document
  $usr_has_access = FALSE;

  if( ! isset($curr_user) || $curr_user->uid == 0){
    return FALSE;
  }

  $curr_user_obj = user_load($curr_user->uid);
  if( node_access('view', $node, $curr_user_obj )){
    $usr_has_access = TRUE;
  }
  return $usr_has_access;
}

/**
 * Return the encrypted URL to access the document
 * 
 * @param int $nid
 *    NodeID of the document to share
 * @param int $version (optional)
 *    Specific version number of the document to share. If not provided, 
 *    the last version of the document will be shared 
 * @param boolean $exp_date (optional)
 *    Specify if the URL should have a expiry date. Default = TRUE.
 * @param boolean $multi
 *    If build a link for massive linksharing. Default = FALSE.
 * @param int $nid_unique
 *    Get the current NID if user has access to a node and if he is connected. Default = NULL.
 * @return string 
 *    The encrypted URL
 */
function gofast_link_sharing_build_link($nid, $dest_id= NULL  , $emetteur= NULL , $version = NULL,  $exp_date = TRUE, $multi = FALSE,$nid_unique=NULL){
  global $base_url;
  if ($multi){
      foreach($nid as $id){
          $node = node_load($nid);
          $is_internal = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Internal Distribution";
          $is_confidential = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Confidential Data";
      
          $params .= ($is_confidential || $is_internal) ? : '+' . $id;
      }
  }else{
      $node = node_load($nid);
      $is_internal = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Internal Distribution";
      $is_confidential = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Confidential Data";
      $params = ($is_confidential || $is_internal) ? : $nid;
  }
  if($params == "") {
      return;
  }
  
  if(isset($dest_id) && ! empty($dest_id)){
    $params.=','.$dest_id;
  }
  
    if(isset($emetteur) && ! empty($emetteur)){
    $params.=','.$emetteur;
  }
  
  if(isset($version) && ! empty($version)){
        $params.=','.$version;
    }
  
  if(isset($nid_unique) && ! empty($nid_unique)){
    $params.=','.$nid_unique;
  }
  
  if($exp_date == TRUE){
    $params.='#'.gofast_link_sharing_get_expiry_timestamp();
  }
  if ($multi){
      return $base_url.'/public/multi_sharing?hash='.urlencode(gofast_encrypt(CIPHER_KEY, $params));
  }else{
      return $base_url.'/public/sharing?hash='.urlencode(gofast_encrypt(CIPHER_KEY, $params));
  }
}


/**
 * Return the timestamp of the given expiry date (or of the DEFAULT_EXPIRY_PERIOD)
 * 
 * @param string $exp_period (optional)
 *    The expiry date as a string. If not provided it will use 
 *    the DEFAULT_EXPIRY_PERIOD
 *    
 * @return timestamp
 *    The timestamp corresponding to the given expiry date
 */
function gofast_link_sharing_get_expiry_timestamp($exp_period = NULL){
  if(isset($exp_period) && ! empty($exp_period)){
    return strtotime($exp_period);
  }else{
     return strtotime(DEFAULT_EXPIRY_PERIOD);
  }
}

/**
 * Return the decrypt informations contained in the shared URL
 * 
 * @param type $hash
 *    The hash parameter of the shared URL
 * @return mixed
 *    array(
 *      'nid'       => string,
 *      'version'   => string,
 *      'exp_date'  => string,
 *      'dest_id'   => string,
 *      'emetteur'  => string 
 *    )
 */
function gofast_link_sharing_link_decrypt($hash){  
  $hash =  gofast_decrypt(CIPHER_KEY,  $hash);
  $nid ='';
  $dest_id='';
  $emetteur = '';
  $version ='';
  $exp_date = '';
  //get expiry date if one set
  $tmp = explode('#', $hash);
  $file_info = $tmp[0];
  if(count($tmp) > 1){
    $exp_date = $tmp[1];
  }
   
  //get file informations (file nid and version if set)
  $tmp = explode(',', $file_info);
  $nid=$tmp[0];
  if(count($tmp)>3){
    $dest_id=$tmp[1];
    $emetteur=$tmp[2];
    $version = $tmp[3];
    if(isset($tmp[4])){
        $nid_unique=$tmp[4];
    }
  }
  $dest_id=$tmp[1];
  $emetteur=$tmp[2];

  $result = array(
    'nid' => $nid,
    'dest_id' => $dest_id,
    'emetteur' => $emetteur,
    'version' => $version,
    'nid_unique' => $nid_unique,
    'exp_date' => $exp_date,
  );
  return $result ;
}

/**
 * Return if the Document can be shared with external
 * 
 * A document can be shared with anonymous people only if it follows 
 * some conditions (like being located in a specific space).
 * 
 * @param node $node
 *    Drupal node of the Document
 * 
 * @return boolean
 *    TRUE if the document can be shared or FALSE if not
 */
function external_share_allowed($node){
  $can_be_share = FALSE;
  $node_elt = NULL;
  if(is_numeric($node)){
    $node_elt = node_load($node);
  }else{
    $node_elt = $node;
  }
  
  $emplacements = array();
  $emplacements = $node_elt->field_emplacement;
    
  foreach($emplacements as $emplacement){
    
    if( strpos(DEFAULT_EXTERNAL_SHARING_LOC, $emplacement[0]['value']) == 0 ){
      $can_be_share = TRUE;
    }
  }
  return $can_be_share;
}

