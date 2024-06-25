<?php

/**
 * Implements hook_form().
 */
function gofast_mail_inbound_outbound_mail_space_options_form($form, &$form_state)
{
  $form = array();
  $space_id = $form_state['build_info']['args']['1'];
  $space = node_load($space_id);
  $ulid = $space->field_mail_ulid[LANGUAGE_NONE][0]['value'];
  $userlist = entity_load_single('userlist', $ulid);
  $subspace_nid = $space->field_mail_subspace_nid[LANGUAGE_NONE][0]['value'];
  // If not mark as mail space, user can create
  if(empty($ulid)){
    $form['validate'] = array(
      '#markup' => "<div>Cet espace n'est pas marqué comme un espace traitant du courrier,
      Voulez vous le marquer ? </div>"
    );

    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Valider',
    );
  }else{
    $form['ulid'] = array(
      '#type' => 'textfield',
      '#default_value' => $ulid,
      '#attributes' => array('class' => array('gofast_display_none'))
    );

    $form['information'] = array(
      '#markup' => "<div><strong>Cette espace est marqué comme un espace traitant du courrier</strong></div></br>"
    );

    $form['mail_userlist'] = array(
      '#markup' => "<span>La liste d'utilisateur associée à cet espace de traitement de courrier: </span><a class='gofast-non-ajax' href='/node/" . $userlist->nid . "' target='_blank'><i class='fa fa-users userlist'></i> " . gofast_get_node_title($userlist->nid) . "</a></br>"
    );
    $form['mail_subspace'] = array(
      '#markup' => "<span>L'espace associé à cet espace de traitement de courrier : </span><a class='gofast-non-ajax' href='/node/" . $subspace_nid . "' target='_blank'><i class='fa fa-users'></i>" . gofast_get_node_title($subspace_nid) . "</a></br>"
    );

    
    ## TODO DEACTIVATION 
    /*$form['deactivate'] = array(
      '#markup' => "</br><div><strong>Vous pouvez désactiver cet espace de traitement de mails</strong></div></br>"
    );

    $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => 'Désactiver',
    );*/

  }

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function gofast_mail_inbound_outbound_mail_space_options_form_submit($form, &$form_state)
{

  global $user;

  $space_id = $form_state['build_info']['args']['1'];
  $ulid = $form_state['values']['ulid'];
  if(empty($ulid)){
    gofast_mail_inbound_outbound_mark_as_mail_space($space_id);
  }else{
    gofast_mail_inbound_outbound_unmark_as_mail_space($space_id, $ulid);
  }
}

/**
 * Mark space as 'Traitement courrier'
 *
 * @param string $space_id
 * @return void
 */
function gofast_mail_inbound_outbound_mark_as_mail_space($space_id){
  global $user;

  if (empty($space_id)) {
    return;
  }

  $space = node_load($space_id);

  // Get admins of the space
  $users_admin = gofast_mail_inbound_outbound_get_admin_space($space_id);

  // Create userlist "Traitement courrier ESPACEXYZ"
  $userlist_id = gofast_mail_inbound_outbound_create_userlist(node_load($space_id)->title, $users_admin);

  // Create sub-spaces name "Traitement courrier"
  if(empty($space->field_mail_subspace_nid)){
    $new_sub_space_id = gofast_mail_inbound_outbound_create_mail_subspace($space_id);
  }else{
    $new_sub_space_id = $space->field_mail_subspace_nid[LANGUAGE_NONE][0]['value'];
  }

  // Add userlist to space with rid administrator member
  $g_roles_query = og_roles('node', $space->type , $new_sub_space_id, FALSE, FALSE);
  foreach ($g_roles_query as $rgkey => $role) {
    if ($role == 'administrator member') {
      $admin_rgid = $rgkey;
    }
  }
  gofast_userlist_og_add_membership($new_sub_space_id, $userlist_id, $admin_rgid);

  // Revoke current user role of new sub space
  og_role_revoke('node', $new_sub_space_id, $user->uid, $admin_rgid);
  gofast_og_unsubscribe_user($new_sub_space_id, $user->uid);

  // Add field to group node
  $space->field_mail_ulid[LANGUAGE_NONE]['0']['value'] = $userlist_id;
  $space->field_mail_subspace_nid[LANGUAGE_NONE]['0']['value'] = $new_sub_space_id;
  node_save($space);
  
  // Create progress status folder
  $subspace_node = node_load($new_sub_space_id);
  $reference = $subspace_node->field_folder_reference[LANGUAGE_NONE][0]['value'];

  // Create inbound mail folder
  $inbound_folder_item = gofast_cmis_item_folder_insert('Courrier entrant', $reference);
  $inbound_folder_ref = $inbound_folder_item->properties['alfcmis:nodeRef'];

  // Create outbound mail folder
  $outbound_folder_item = gofast_cmis_item_folder_insert('Courrier sortant', $reference);
  $outbound_folder_ref = $outbound_folder_item->properties['alfcmis:nodeRef'];
  
  // Create progression folder 
  foreach (array($inbound_folder_ref, $outbound_folder_ref) as $ref) {
    gofast_cmis_item_folder_insert('A traiter', $ref);
    gofast_cmis_item_folder_insert('En cours', $ref);
    gofast_cmis_item_folder_insert('Traité', $ref);
  }
}

function gofast_mail_inbound_outbound_unmark_as_mail_space($space_id, $ulid){
  global $user;

  if (empty($space_id) || empty($ulid)) {
    return;
  }

  $space = node_load($space_id);
  $subspace_nid = $space->field_mail_subspace_nid[LANGUAGE_NONE]['0']['value'];
  $userlist = entity_load_single('userlist', $ulid);
  $node_userlist = node_load($userlist->nid);

  // Add userlist administrator on admin member
  $userlist_admins = gofast_userlist_get_administrators($ulid, FALSE);

  // Add creator to userlist admins
  $userlist_creator_uid = $node_userlist->uid;
  $userlist_admins[$userlist_creator_uid] = array(
    'uid' => $userlist_creator_uid
  );

  $g_roles_query = og_roles('node', $space->type , '0' , FALSE, FALSE);
  foreach ($g_roles_query as $rgkey => $role) {
    if ($role == GOFAST_OG_ROLE_ADMIN) {
      $admin_rgid = $rgkey;
    }elseif ($role == GOFAST_OG_ROLE_READ_ONLY) {
      $readonly_rid = $rgkey;
    }else if ($role == GOFAST_OG_ROLE_STANDARD) {
      $contributor_rid = $rgkey;
    }

  }
  foreach ($userlist_admins as $uid => $userlist_admin) {
    gofast_og_subscribe_user($subspace_nid, $uid);
    usleep(50000);
    og_role_revoke('node', $subspace_nid, $uid, $readonly_rid);
    og_role_revoke('node', $subspace_nid, $uid, $contributor_rid);
    og_role_revoke('node', $subspace_nid, $uid, $admin_rgid);
    usleep(50000);
    og_role_grant('node', $subspace_nid, $uid, $admin_rgid);
  }

  // Delete userlist
  gofast_userlist_og_delete_membership($subspace_nid, $ulid);
  gofast_userlist_og_delete_membership($space_id, $ulid);

  gofast_userlist_delete_userlist($userlist);

  gofast_userlist_remove_empty_etid_from_og_membership_into_database($ulid);

  // Delete drupal fields from current space
  $space->field_mail_ulid = '';

  node_save($space);
}

function gofast_userlist_remove_empty_etid_from_og_membership_into_database($ulid){
  db_delete("og_membership")
    ->condition('etid', '0')
    ->condition('entity_type', 'userlist')
    ->execute();

  db_delete("og_membership")
    ->condition('etid', $ulid)
    ->condition('entity_type', 'userlist')
    ->execute();
}

function gofast_mail_inbound_outbound_form_alter(&$form, &$form_state){
     if($form['#form_id'] === 'alfresco_item_node_form'){
         $form["field_mail_object"]["#access"] = 0;
         $form["field_mail_rid"]["#access"] = 0;
         $form["field_mandatory_answer"]["#access"] = 0;
         $form["field_arrival_departure_link"]["#access"] = 0;
         $form["field_arrival_departure_date"]["#access"] = 0;
         $form["field_mail_state"]["#access"] = 0;
         $form["field_impute_to"]["#access"] = 0;
         $form["field_user_recipient"]["#access"] = 0;
         $form["field_service_recipient"]["#access"] = 0;
         $form["field_mail_instruction"]["#access"] = 0;
         $form["field_mail_sender"]["#access"] = 0;
         $form["field_mail_category"]["#access"] = 0;
         $form["field_acknowledge_number"]["#access"] = 0;
     }
     if($form['#form_id'] == 'group_node_form'){
         $form["field_mail_subspace_nid"]["#access"] = 0;
         $form["field_mail_ulid"]["#access"] = 0;
     }
     if($form['#form_id'] == 'organisation_node_form'){
         $form["field_mail_subspace_nid"]["#access"] = 0;
         $form["field_mail_ulid"]["#access"] = 0;
     }
     if($form['#form_id'] == 'extranet_node_form'){
         $form["field_mail_subspace_nid"]["#access"] = 0;
         $form["field_mail_ulid"]["#access"] = 0;
     }
     if($form['#form_id'] == 'public_node_form'){
         $form["field_mail_subspace_nid"]["#access"] = 0;
         $form["field_mail_ulid"]["#access"] = 0;
     }
}

