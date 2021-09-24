<?php

 /**
   * Implement HOOK_node_presave()
   * @param type $node
   * @param type $delete
   * @param type $update
   */
 function gofast_userlist_node_presave($node, $delete = false, $update = false) {
  
  if ($node->type === 'userlist') {
    
    
    watchdog('gofast_userlist', '%name() - members value = %value ', array('%name' => __FUNCTION__, '%value' => $node->field_userlist_members), WATCHDOG_INFO);    
    try {      
      
      $is_new_item = !empty($node->is_new) || empty($node->nid);
      
      if($is_new_item){
        // Create the correspondoing UserList entity
        $entity = entity_create('userlist', array());
        $entity->name = $node->title;
        $entity->from_ldap = 0;
        
        //add members
        if ($node->field_userlist_members == NULL){
            $entity->field_userlist_members[LANGUAGE_NONE] = NULL;            
        }else{
            $members = explode(',', $node->field_userlist_members);
            foreach($members as $key => $member){
              $entity->field_userlist_members[LANGUAGE_NONE][$key]['value'] = $member;
            }
        }
        
        $entity->save();

        //update node userlist with the newly created entity id
        $node->field_userlist_ulid[LANGUAGE_NONE][0]['value'] = $entity->ulid;
        $node->field_ldap_group_dn[LANGUAGE_NONE][0]['value'] = UserListEntity::getDn($entity->ulid);
      
        
      }else{
                
        $entity = entity_load_single('userlist', $node->field_userlist_ulid[LANGUAGE_NONE][0]['value']);
        if(!empty($node->title)){
            $entity->name = $node->title;
        }else{
            $node->title = $node->field_userlist_name;
            $entity->name = $node->title;
        }

        if ($node->field_userlist_members == NULL){
            $entity->field_userlist_members[LANGUAGE_NONE] = NULL;            
        }else{
            $members = explode(',', $node->field_userlist_members);
            $entity->field_userlist_members[LANGUAGE_NONE] = array();
            foreach($members as $key => $member){
              $entity->field_userlist_members[LANGUAGE_NONE][$key]['value'] = $member; 
            }
        }
        //field_attach_update('userlist', $entity);
        entity_save('userlist', $entity);
        
      }
        
    }
    catch (Exception $ex) {
      throw $ex;
    }
  }
}

 /**
   * Implement HOOK_node_insert()
   * @param Node $node
   */
function gofast_userlist_node_insert($node) {
  if ($node->type === 'userlist') {

    $entity = entity_load_single('userlist', $node->field_userlist_ulid[LANGUAGE_NONE][0]['value']);
    $entity->nid = $node->nid;

    // save Userlist nid in Userlist entity  
    entity_save('userlist', $entity);
    
    
    //Send welcome message to members
    $members=explode(',',$node->field_userlist_members);
    foreach ($members as $uid) {
      $member=user_load($uid);
      $msg = t('Welcome to ' , array(), ['langcode' => $member->language, 'context' => 'gofast_userlist']).$node->title;   
      gofast_mail_add_user_to_userlist($uid,$node->nid, $msg, 'MEM');
    }
  }
}

 /**
   * Implement HOOK_node_delete()
   * @param type $node
   * @param type $delete
   * @param type $update
   */
 function gofast_userlist_node_delete($node, $delete = FALSE, $update = FALSE) {
  
  if ($node->type === 'userlist') {
    try {
      // Delete the correspondoing UserList entity
      $ulid = $node->field_userlist_ulid[LANGUAGE_NONE][0]['value'];
      $entity = entity_load('userlist', array($ulid));

      if(! empty($entity[$ulid])){
        $entity[$ulid]->delete();
      }
    }
    catch (Exception $ex) {
      throw $ex;
    }
  }
}
