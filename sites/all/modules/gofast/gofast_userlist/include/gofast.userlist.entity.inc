<?php

/**
 * Extending the Entity for the UserList entity.
 */
class UserListEntity extends Entity {

  /**
   * Change the default URI from default/id to userlist/id
   */
  protected function defaultUri() {
    return array('path' => 'userlist/' . $this->identifier());
  }

  static function getDn($userlist){

    $userlist_ulid = NULL;
    if(is_object($userlist)){
      $userlist_ulid = $userlist->ulid;
    }else{
       $userlist_ulid = $userlist;
    }

    return 'cn=UserList_' . $userlist_ulid . ',' . variable_get('gofast_ldap_userlist_base_dn');
  }

}

/* * *************************************************************************** */

/**
 * Extending the EntityAPIController for the UserList entity.
 */
class UserListEntityController extends EntityAPIController {

  const USERLIST_LDAP_ROOTDN = 'UserLists';

  /**
   * Entity Userlist buildContent
   * @param type $entity
   * @param type $view_mode
   * @param type $langcode
   * @param type $content
   * @return type
   */
  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {

    $build = parent::buildContent($entity, $view_mode, $langcode, $content);

    // Our additions to the $build render array
    $build['name'] = array(
      '#type' => 'markup',
      '#markup' => check_plain($entity->name),
      '#prefix' => '<div>',
      '#suffix' => '</div>'
    );

    return $build;
  }

  /**
   * Entity Userlist save
   * @param type $entity
   * @param \DatabaseTransaction $transaction
   */
  public function save($entity, \DatabaseTransaction $transaction = NULL) {

    $timer_start = microtime(true);
    watchdog('gofast_userlist', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

    $is_new_item = !empty($entity->is_new) || empty($entity->{$this->idKey});

    parent::save($entity, $transaction);

    //   try {
    //create LDAP Entry for the UserList
    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $LdapServer->connectAndBindIfNotAlready();
    $ldap_userlist_basedn = variable_get('gofast_ldap_userlist_base_dn', 'ou=' . UserListEntityController::USERLIST_LDAP_ROOTDN . ',ou=Groups,' . variable_get('gofast_ldap_int_base_dn'));

    if ($is_new_item) {

      //Create UserList rootDN if not already in LDAP
      UserListEntityController::_createUserlistRootDN();

      $attributes = array();
      $attributes['objectclass'] = array('groupOfNames');
      $attributes['cn'] = 'UserList_' . $entity->{$this->idKey};

      $userlist_dn = 'cn=' . $attributes['cn'] . ',' . $ldap_userlist_basedn;

      $result = $LdapServer->groupAddGroup($userlist_dn, $attributes);

      if (!$result) {
        //revert creation of userlist
        entity_delete('userlist', $entity->{$this->idKey});
        throw new Exception;
      }
      else {
        // add membership
        if ($entity->field_userlist_members[LANGUAGE_NONE] != NULL){
            foreach ($entity->field_userlist_members[LANGUAGE_NONE] as $member) {
              $user = user_load($member['value']);
              $result = $LdapServer->groupAddMember($userlist_dn, $user);
            }
        }
      }
    }
    else {

      $userlist_dn = 'cn=' . 'UserList_' . $entity->ulid . ',' . $ldap_userlist_basedn;
      $members = array();
      foreach ($entity->field_userlist_members[LANGUAGE_NONE] as $member) {
        $user = user_load($member['value']);
        $members[$user->uid] = gofast_ldap_user_dn($user);
      }
      $this->updateUserListMembers($entity, $userlist_dn, $members);

    }
//    }
//    catch (Exception $e) {
//       watchdog('gofast_userlist', '%name() ERROR : %e', array('%name' => __FUNCTION__, '%e' => $e->getMessage()), WATCHDOG_ERROR);
//    }
//    finally {
      $timer_stop = microtime(true);
      watchdog('gofast_userlist', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
//    }
  }

  /**
   * Entity Userlist delete
   * @param type $ids
   * @param \DatabaseTransaction $transaction
   */
  public function delete($ids, \DatabaseTransaction $transaction = NULL) {

    $timer_start = microtime(true);
    watchdog('gofast_userlist', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

    $entities = $ids ? $this->load($ids) : FALSE;
    if (!$entities) {
      // Do nothing, in case invalid or no ids have been passed.
      return;
    }

    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $LdapServer->connectAndBindIfNotAlready();

    foreach ($entities as $id => $entity) {

      //Init a db transaction to manage rollback if needed
      $transaction = isset($transaction) ? $transaction : db_transaction();
      try {

        db_delete($this->entityInfo['base table'])
            ->condition($this->idKey, $ids, 'IN')
            ->execute();

        if (isset($this->revisionTable)) {
          db_delete($this->revisionTable)
              ->condition($this->idKey, $ids, 'IN')
              ->execute();
        }

        //Remove LDAP part
        $userlist_dn = 'cn=UserList_' . $id . ',' . variable_get('gofast_ldap_userlist_base_dn');
        if ($LdapServer->dnExists($userlist_dn)) {
          $result = $LdapServer->delete($userlist_dn, TRUE);
          if (!$result) {
            throw new Exception;
          }
        }

        // Reset the cache as soon as the changes have been applied.
        $this->resetCache(array($id));
        $this->invoke('delete', $entity);

        // Ignore slave server temporarily (in case of db replication mecanism)
        db_ignore_slave();
      }
      catch (Exception $e) {
        $transaction->rollback();
        watchdog_exception($this->entityType, $e);
        throw $e;
      }
    }
    $timer_stop = microtime(true);
    watchdog('gofast_userlist', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
  }

  /**
   * Update members of Userlist
   * @param type $userlist_dn
   * @param type $members
   */
  function updateUserListMembers($entity, $userlist_dn, $members = array()) {

    $timer_start = microtime(true);
    watchdog('gofast_userlist', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $LdapServer->connectAndBindIfNotAlready();

    $former_members = $LdapServer->groupAllMembers($userlist_dn);
    $members_to_remove = $former_members;
    $members_to_add_audit = array();
    $members_to_remove_audit = array();

    $result = TRUE;
    foreach ($members as $member_uid => $member_dn) {

      $key = array_search(strtolower($member_dn), array_map('strtolower',$former_members));
      if ($key !== FALSE) { // already member
        unset($members_to_remove[$key]);
      }
      else { // new member

        $user = user_load($member_uid);
        $result = $LdapServer->groupAddMember($userlist_dn, $user);
        watchdog('gofast_userlist', 'ADD member=[%member] to userlist=[%userlist] ', array('%member' => $user->name, '%userlist' => $entity->name), WATCHDOG_INFO);

        // add notification to the new user for all the userlist spaces
        $gids = gofast_userlist_og_get_groups_by_userlist($entity->ulid, 'node');
        foreach($gids as $gid){
          //check if user is member of space without userlist
          if( !(og_get_membership('node', $gid, 'user', $member_uid))){
            $members_to_add_audit[$gid][] = $user->uid;
            $og_flag = flag_get_flag('subscribe_og');
            $og_flag->flag('flag', $gid, user_load($member_uid));

          }
         }
      }
    }

    //Remove membership
    foreach ($members_to_remove as $old_member) {

      $user = gofast_ldap_get_user_from_dn(strtolower($old_member));
      $result = $LdapServer->groupRemoveMember($userlist_dn, $old_member);
      watchdog('gofast_userlist', 'REMOVE member=[%member] from userlist=[%userlist] ', array('%member' => $old_member, '%userlist' => $entity->name), WATCHDOG_INFO);

      //remove from notification the user for all the userlist spaces
      $gids = gofast_userlist_og_get_groups_by_userlist($entity->ulid, 'node');
      foreach($gids as $gid){
        //check if user is member of space without userlist
        if( !(og_get_membership('node', $gid, 'user', $user->uid))){
          $members_to_remove_audit[$gid][] = $user->uid;
          gofast_subscription_ui_api_delete_subscriptions_by_uid_gid($user->uid, $gid);
        }
      }
    }
    if(!empty($members_to_add_audit)){
      gofast_userlist_insert_into_spaces_audit('add_member', $members_to_add_audit, $entity->ulid);
    }
    if(!empty($members_to_remove_audit)){
      gofast_userlist_insert_into_spaces_audit('delete_member', $members_to_remove_audit, $entity->ulid);
    }
    $timer_stop = microtime(true);
    watchdog('gofast_userlist', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
  }

  /**
   * Create root dn for UserLists entity
   */
 static function _createUserlistRootDN() {

    $timer_start = microtime(true);
    watchdog('gofast_userlist', '%name() START ', array('%name' => __FUNCTION__), WATCHDOG_INFO);

    try {
      $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
      $LdapServer->connectAndBindIfNotAlready();

      $ldap_basedn = variable_get('gofast_ldap_int_base_dn');

      $attributes = array();
      $attributes['objectclass'] = array('organizationalUnit');
      $attributes['ou'] = UserListEntityController::USERLIST_LDAP_ROOTDN;

      $gofast_ldap_userlist_basedn = 'ou=' . $attributes['ou'] . ',ou=Groups,' . $ldap_basedn;

      if (!$LdapServer->dnExists($gofast_ldap_userlist_basedn)) {
        $result = $LdapServer->createLdapEntry($attributes, $gofast_ldap_userlist_basedn);
        if (!$result) {
          throw new Exception;
        }
      }
      variable_set('gofast_ldap_userlist_base_dn', $gofast_ldap_userlist_basedn);
    }
    catch (Exception $e) {
      watchdog('gofast_userlist', '%name() ERROR : %e', array('%name' => __FUNCTION__, '%e' => $e->getTrace()), WATCHDOG_ERROR);
    } finally {
      $timer_stop = microtime(true);
      watchdog('gofast_userlist', '%name() END - [execution time = %time s]', array('%name' => __FUNCTION__, '%time' => ($timer_stop - $timer_start)), WATCHDOG_INFO);
    }
  }
}
