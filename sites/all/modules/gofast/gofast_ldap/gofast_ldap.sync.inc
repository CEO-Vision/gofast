<?php

define('GOFAST_LDAP_MAX_SYNC_PER_CRON', 50);

/*
 * This function will synchronize the Drupal user database with the configured
 * remote directory
 * @param $remote_accounts : The result of an admin search query on the distant
 *                           directory.
 */
function gofast_ldap_sync_directory($remote_accounts){
  //Firstly, compare current database against remote directory to block/unblock accounts
  gofast_ldap_sync_block_accounts($remote_accounts);
  
  //Then, synchronize the accounts
  gofast_ldap_synchronize_accounts($remote_accounts);
}

/*
 * This function will block the Drupal users that are NOT in the remote directory
 * @param $remote_accounts : The result of an admin search query on the distant
 *                           directory.
 */
function gofast_ldap_sync_block_accounts($remote_accounts){
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  //Key remote accounts by username
  foreach($remote_accounts as $k => $account){
    $remote_account_by_uname[$account[$sync_settings['mapping']['uid']][0]] = $account;
  }
  
  $users = db_query("select name, status, uid, sasl_auth_value from users INNER JOIN field_data_sasl_auth ON uid=entity_id")->fetchAllAssoc('uid');
  
  foreach($users as $k => $rquery){
    $status = $rquery->status;
    $uid = $rquery->uid;
    $name = $rquery->name;
    $sasl = $rquery->sasl_auth_value;
    
    if($uid == 0 || $uid == 1){
      continue;
    }
    
    if(empty($remote_account_by_uname[$name]) && $status == 1 && $sasl == 1){
      //Log
      watchdog('Directory Synchronization', "Blocking user " . $uid . "/" . $name, array(), WATCHDOG_INFO);
      
      //Block the user
       gofast_user_leave_user($uid);
      //$my_user = user_load($uid);
      //$edit = array('status' => 0);
      //user_save($my_user, $edit);
    }else if(!empty($remote_account_by_uname[$name]) && $status == 0){
      //Log
      watchdog('Directory Synchronization', "Unblocking user " . $uid . "/" . $name, array(), WATCHDOG_INFO);
      
      //unblock the user
      gofast_user_unleave_user($uid);
      //$my_user = user_load($uid);
      //$edit = array('status' => 1);
      //user_save($my_user, $edit);
    }
  }
}


/*
 * This function will synchronize the accounts retrieved from the distant Directory
 * if there is more than GOFAST_LDAP_MAX_SYNC_PER_CRON accounts, the synchronization
 * will occur in multiple crons
 */
function gofast_ldap_synchronize_accounts($remote_accounts){
  //Check if we have accounts to synchronize
  if(count($remote_accounts) == 0){
    variable_set('gofast_ldap_processing_sync', 0);
    variable_set('gofast_ldap_remote_accounts', array());
    return;
  }
  
  $count = 0;
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  unset($remote_accounts['count']);
  
  foreach($remote_accounts as $k => $account){
    $uname = $account[$sync_settings['mapping']['uid']][0];
    if(empty($uname)){
      continue;
    }
    $user = user_load_by_name($uname);
    
    if($user == FALSE){
      //We need to create the user as it's not registered yet
      watchdog('Directory Synchronization', "Creating user " . $uname, array(), WATCHDOG_NOTICE);
      gofast_ldap_synchronize_create_account($account);
    }else{
      //User is registered on the platform and we got it's informations from the 
      //remote Directory, we can synchronize it.
      watchdog('Directory Synchronization', "Updating user " . $uname, array(), WATCHDOG_NOTICE);
      gofast_ldap_synchronize_update_account($account);
    }
    
    unset($remote_accounts[$k]);
    variable_set('gofast_ldap_remote_accounts', $remote_accounts);
    
    if($count == GOFAST_LDAP_MAX_SYNC_PER_CRON){
      return;
    }
    $count++;
  }
  
  //All accounts have been synchronized, end of synchronization
  watchdog('Directory Synchronization', "All accounts have been synchronized", array(), WATCHDOG_INFO);
  variable_set('gofast_ldap_processing_sync', 0);
  variable_set('gofast_ldap_remote_accounts', array());
  return;
}

/*
 * This function will create an account retrieved from the distant directory
 */
function gofast_ldap_synchronize_create_account($account){
  $sasl = variable_get('gofast_sasl_auth', 0);
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  $uname = $account[$sync_settings['mapping']['uid']][0];
  //Prepare account fields
  $mapping = $sync_settings['mapping'];
  $options = array();
  foreach($mapping as $field => $remote_field){
    if(empty($remote_field)){
      continue;
    }
    switch($field){
      case 'email':
        if(!empty($account[$remote_field][0])){
          $options['mail'] = $account[$remote_field][0];
        }
        break;
      case 'title':
        if(!empty($account[$remote_field][0])){
          $options['ldap_user_title'] = $account[$remote_field][0];
        }
        break;
      case 'company':
        if(!empty($account[$remote_field][0])){
          $options['ldap_user_o'] = $account[$remote_field][0];
        }
        break;
      case 'phone':
        if(!empty($account[$remote_field][0])){
          $options['ldap_user_telephonenumber'] = $account[$remote_field][0];
        }
        break;
      case 'mobile_phone':
        if(!empty($account[$remote_field][0])){
          $options['ldap_user_mobile'] = $account[$remote_field][0];
        }
        break;
    }
  }
  
  //Getting name
  if($mapping['fullname'] && !empty($account[$mapping['fullname']][0])){
    $name_exploded = explode(' ', $account[$mapping['fullname']][0]);
    if(count($name_exploded) <= 1){
      $options['ldap_user_givenname'] = $name_exploded[0];
      $options['ldap_user_sn'] = $name_exploded[0];
    }else{
      $options['ldap_user_givenname'] = array_shift($name_exploded);
      $sn = implode(" ", $name_exploded);
      $options['ldap_user_sn'] = $sn;
    }
  }else if (!empty($account[$mapping['firstname']][0]) && !empty($account[$mapping['lastname']][0])){
    $options['ldap_user_givenname'] = $account[$mapping['firstname']][0];
    $options['ldap_user_sn'] = $account[$mapping['lastname']][0];
  }
  
  //Getting main organization
  if(!empty($account[$mapping['main_orga']][0])){
    $main_orga = $account[$mapping['main_orga']][0];
    $nodes = node_load_multiple(NULL, array('title' => $main_orga, "type" => "organisation"));
    
    if(count($nodes) != 1){
      watchdog('Directory Synchronization', "Unable to attach the user to it's main organization because " . count($nodes) . " match were found for " . $main_orga, array(), WATCHDOG_ERROR);
    }else{
      $node = array_shift($nodes);
      $options['ldap_user_ou'] =  $node->nid;
    }
  }
  
  //Create the account
  $creation = gofast_user_create($uname, GOFAST_ROLE_CONTRIBUTOR, $options, $sasl);
  
  if(!$creation){
    watchdog('Directory Synchronization', "Unable to create the account : " . implode(', ', drupal_get_messages()['error']), array(), WATCHDOG_ERROR);
  }
}

/*
 * This function will update an account retrieved from the distant directory
 */
function gofast_ldap_synchronize_update_account($account){
  $sync_settings = variable_get('gofast_directory_sync_config', array());
  $uname = $account[$sync_settings['mapping']['uid']][0];
  $need_sync = false;
  $user = user_load_by_name($uname);
  
  if($user == false){
    watchdog('Directory Synchronization', "Unable to load the account " . $uname, array(), WATCHDOG_ERROR);
  }
  
  //Compare fields to update them if needed
  $mapping = $sync_settings['mapping'];
  foreach($mapping as $field => $remote_field){
    if(empty($remote_field)){
      continue;
    }
    switch($field){
      case 'email':
        if(!empty($account[$remote_field][0])){
          if($user->mail != $account[$remote_field][0]){
            watchdog('Directory Synchronization', "Updating email", array(), WATCHDOG_NOTICE);
            $user->mail=$account[$remote_field][0];
            $need_sync = true;
          }
        }
        break;
      case 'title':
        if($user->ldap_user_title[LANGUAGE_NONE][0]['value'] != $account[$remote_field][0]){
          watchdog('Directory Synchronization', "Updating title", array(), WATCHDOG_NOTICE);
          $user->ldap_user_title[LANGUAGE_NONE][0]['value']=$account[$remote_field][0];
          $need_sync = true;
        }
        break;
      case 'company':
        if($user->ldap_user_o[LANGUAGE_NONE][0]['value'] != $account[$remote_field][0]){
          watchdog('Directory Synchronization', "Updating company", array(), WATCHDOG_NOTICE);
          $user->ldap_user_o[LANGUAGE_NONE][0]['value']=$account[$remote_field][0];
          $need_sync = true;
        }
        break;
      case 'phone':
        if($user->ldap_user_telephonenumber[LANGUAGE_NONE][0]['value'] != $account[$remote_field][0]){
          watchdog('Directory Synchronization', "Updating telephone number", array(), WATCHDOG_NOTICE);
          $user->ldap_user_telephonenumber[LANGUAGE_NONE][0]['value']=$account[$remote_field][0];
          $need_sync = true;
        }
        break;
      case 'mobile_phone':
        if($user->ldap_user_mobile[LANGUAGE_NONE][0]['value'] != $account[$remote_field][0]){
          watchdog('Directory Synchronization', "Updating mobile phone number", array(), WATCHDOG_NOTICE);
          $user->ldap_user_mobile[LANGUAGE_NONE][0]['value']=$account[$remote_field][0];
          $need_sync = true;
        }
        break;
    }
  }
  
  //Getting name
  if(!empty($mapping['fullname']) && !empty($account[$mapping['fullname']][0])){
    $name_exploded = explode(' ', $account[$mapping['fullname']][0]);
    if(count($name_exploded) <= 1){
      $ldap_user_givenname = $name_exploded[0];
      $ldap_user_sn = $name_exploded[0];
    }else{
      $ldap_user_givenname = array_shift($name_exploded);
      $sn = implode(" ", $name_exploded);
      $ldap_user_sn = $sn;
    }
  }else if (!empty($account[$mapping['firstname']][0]) && !empty($account[$mapping['lastname']][0])){
    $ldap_user_givenname = $account[$mapping['firstname']][0];
    $ldap_user_sn = $account[$mapping['lastname']][0];
  }
  
  if($user->ldap_user_givenname[LANGUAGE_NONE][0]['value'] != $ldap_user_givenname){
    watchdog('Directory Synchronization', "Updating first name", array(), WATCHDOG_NOTICE);
    $user->ldap_user_givenname[LANGUAGE_NONE][0]['value']=$ldap_user_givenname;
    $need_sync = true;
  }
  if($user->ldap_user_sn[LANGUAGE_NONE][0]['value'] != $ldap_user_sn){
    watchdog('Directory Synchronization', "Updating sir name", array(), WATCHDOG_NOTICE);
    $user->ldap_user_sn[LANGUAGE_NONE][0]['value']=$ldap_user_sn;
    $need_sync = true;
  }
  
  //Getting main organization
  $ldap_user_ou = $account[$mapping['main_orga']][0];
  if(!empty($account[$mapping['main_orga']][0])){
    $main_orga = $account[$mapping['main_orga']][0];
    $nodes = node_load_multiple(NULL, array('title' => $main_orga, "type" => "organisation"));

    if(count($nodes) != 1){
      watchdog('Directory Synchronization', "Unable to attach the user to it's main organization because " . count($nodes) . " match were found for " . $main_orga, array(), WATCHDOG_ERROR);
    }else{
      $node = array_shift($nodes);
      if($user->ldap_user_ou[LANGUAGE_NONE][0]['value'] != "_#" . $node->nid){
        watchdog('Directory Synchronization', "Updating main organisation", array(), WATCHDOG_NOTICE);
        $user->ldap_user_ou[LANGUAGE_NONE][0]['value'] = "_#" . $node->nid;
        $need_sync = true;
      }
    }
  }
  
  if($need_sync){
    $updating = user_save($user);
    
    if($updating == FALSE){
      watchdog('Directory Synchronization', "Update of user " . $uname . "/" . $user->uid . " has failed", array(), WATCHDOG_ERROR);
    }else{
      watchdog('Directory Synchronization', "Successfull update of user " . $uname . "/" . $user->uid, array(), WATCHDOG_INFO);
    }
  }else{
    watchdog('Directory Synchronization', "No update needed for " . $uname . "/" . $user->uid, array(), WATCHDOG_INFO);
  }
}