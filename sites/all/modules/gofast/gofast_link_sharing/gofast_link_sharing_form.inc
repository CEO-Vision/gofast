<?php

/**
 * @file
 * Link_sharing_form integration for the Gofast_link_sharing module.
 */


/**
 * Form constructor for the gofast_link_sharing form
 *
 * @param node $node
 *  The node "document" that will be shared
 *
 * @see function gofast_link_sharing_form_validate()
 * @see function gofast_link_sharing_form_submit()
 *
 * @ingroup forms
 *
 */
function gofast_link_sharing_form($form, &$form_state, $node){
  global $user;

  $user_details = user_load($user->uid);
  $current_user_fullname=  gofast_user_display_name($user_details);
  $file_sharing_link = gofast_link_sharing_build_link($node->nid);

  $form['from_name'] = array(
    '#type' => 'hidden',
    '#title' => t('Your Name', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('Myself', array(), array('context' => 'gofast')),
    '#required' => TRUE,
    '#default_value' => $current_user_fullname ,
  );

  $form['from_addr'] = array(
    '#type' => 'hidden',
    '#value' => $user->mail,
  );

  $form['to'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient(s)', array(), array('context' => 'gofast')). ' *',
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t('Email of the person to whom the document will be shared', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => FALSE,
    '#autocomplete_path' => 'gofast_user_userlist_space_autocomplete',
    '#attributes' => array('class' => array('labelize-autocomplete labelize-insert'))
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject', array(), array('context' => 'gofast')),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Subject for the email that will be sent', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => TRUE,
    '#default_value' => $current_user_fullname.' '.t('shared with you a document on the ', array(), array('context' => 'gofast:gofast_link_sharing','langcode' => $user->language)) . variable_get('site_name', 'GoFAST 3'),
  );

  $form['link'] = array(
    '#markup' => '<div class="form-item form-item-link form-group">'
                . '<label class="control-label" for="edit-link">'.t('Link to the document %title', array('%title' => $node->title ), array('context' => 'gofast:gofast_link_sharing')).'</label>'
                . '<div><a title="' .t('Copy the link') . '"href="#" onclick=\'event.preventDefault();event.stopPropagation();Gofast.copyToClipboard("'.$file_sharing_link.'")\'>'.$file_sharing_link.'</a><a title="'.t('Copy the link') .'" style="padding: 2px 7px; vertical-align: middle; color:#3498db; margin-left:10px;" class="btn-sm btn btn-default dropdown-toggle" onclick=\'event.preventDefault();event.stopPropagation();Gofast.copyToClipboard("'.$file_sharing_link.'")\'><i class="fa fa-files-o"></i></a></div>'
                . '</div>',
  );

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => $node->title,
  );

  $form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );

  $form['url'] = array(
    '#type' => 'hidden',
    '#value' => $file_sharing_link,
  );

  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Your message', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#default_value' => '',
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('This message will be included in the email that will be sent', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => FALSE,
  );

  $form['node'] = array(
    '#type' => 'hidden',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send', array(), array('context' => 'gofast')),
    '#validate' => array('gofast_link_sharing_form_validate'),
    '#attributes' => array('class' => array('btn', 'btn-success', 'btn-sm')),
  );
  return $form;
}

/**
 * Form validation handler for gofast_link_sharing_form()
 *
 * @see gofast_link_sharing_form_submit()
 */
function gofast_link_sharing_form_validate($form, &$form_state){

    ## check if Submit button has been pressed
    if (isset($form_state['values']['op']) && $form_state['values']['op'] == t('Send', array(), array('context' => 'gofast'))) {


    ## recovery of the data to be analyzed (email address or uid)
    $recipient_addresses = array();
    $recipients_value = json_decode($form_state['input']['edit-' . str_replace("_", "-", $form['to']['#name']) . '-hidden-values']);

    ## GOFAST-5180 get all values if the user separates email addresses with spaces, commas or semicolons
    if($form_state['input']['to'] !== null && $form_state['input']['to'] !== ""){

        ## check if there are no invalid characters
//        if (preg_match('/[^A-Za-z0-9.#\\-\_\$\,\;\@]/', $form_state['input']['to'])){
//            form_set_error('to', t('There are invalid characters', array(), array('context' => 'gofast')));
//            return;
//        }
        if (strpos($form_state['input']['to'],";") == TRUE){
            $array_input_addresses = str_replace(' ', '', explode(';',$form_state['input']['to']));
        }
        if(strpos($form_state['input']['to'],",") == TRUE){
            $array_input_addresses = str_replace(' ', '',explode(',',$form_state['input']['to']));
        }
        if(empty($array_input_addresses) && strpos($form_state['input']['to']," ") == TRUE ){
            $array_input_addresses = str_replace(' ','',explode(' ',$form_state['input']['to']));
        }
        if (!empty($array_input_addresses)){
            $recipients_value = array_merge($array_input_addresses, $recipients_value);
        }else{
            $recipients_value[] = $form_state['input']['to'];
        }
        $recipients_value = array_filter($recipients_value);
    }

    ## check if the number of recipients is not empty
    if(count($recipients_value) <1){
       form_set_error('to', t('You must fill all mandatory fields', array(), array('context' => 'gofast')));
       return;
    }

    // Fill 'to' with the hidden input of autocomplete field
    // and if node not in Extranet -> disabled capability to share with external people
    foreach ($recipients_value as $recipient) {
      if ($recipient->type === 'user') {
        $space_user = $recipient->id;
        $recipient_addresses[] = $space_user;
      }
      if ($recipient->type === 'node') {
        // Get nid from the group
        $node = node_load($recipient->id);
        // Get member id from the group
        $group_members = gofast_og_get_members_userlist_included($node,'active');
        foreach ($group_members as $member) {
            if (user_load($member)->status == 1){
                $recipient_addresses[] = $member;
            }
        }
      }
      else if($recipient->type === 'userlist'){

        // Get the ULID from the userlist to send mails
        $ulid = $recipient->id;
        // Get all members of the group
        $group_members = gofast_userlist_get_members($ulid);
        foreach ($group_members as $uid => $member) {
          $user_members = user_load($uid);
          // Get only users active to send mail
          if ($user_members->status == 1){
            $recipient_addresses[] = $uid;
          }

        }
      }
      else if(valid_email_address($recipient)){

//        if(! external_share_allowed($form_state['values']['node_id'])){
//          form_set_error('to',
//                    t('This document must be located in "Extranet" to be '
//                      . 'shared with people external to GoFast (%recipient)',
//                      array( '%recipient' => $recipient ), array('context' => 'gofast:gofast_link_sharing')
//                    )
//                 );
//        }
        $recipient_addresses[] = $recipient;
      }
    }

    ## store recipient ids or adresses in the form
    $recipient_addresses = array_unique($recipient_addresses);
    $form_state['values']['to'] = implode(',', $recipient_addresses);
  }

}

/**
 * Form submit handler for gofast_link_sharing_form()
 *
 * @see gofast_link_sharing_form_validate()
 *
 * @param type $form
 * @param type $form_state
 */
function gofast_link_sharing_form_submit($form, &$form_state){

  global $user;
  global $base_url;

  $user_name = gofast_user_display_name($user);
  $user_mail = $user->mail;

  ## get all node informations
  $node = node_load($form_state['values']['node_id']);
  $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
  $document_pic = gofast_mail_queue_fa_png($node_icon);


  // send mail for share the link of a document
  if (isset($form_state['values']['op']) && $form_state['values']['op'] == t('Send', array(), array('context' => 'gofast'))) {

    $recpts = gofast_linksharing_build_receipt_mail($form_state);

    $info_recipients = json_decode($form_state['input']['edit-to-hidden-values']);


    ## get document version
    $node_ref = gofast_cmis_node_get_item_id($node);
    $document_version = gofast_cmis_webservice_item_get_versions($node_ref)[0]->label;
    $recipient= NULL;
    $recipients_ids_list = explode(',',$form_state['values']['to']);
    $copy_recipients_ids_list = $recipients_ids_list;

    ## reach all recipient informations to send mail to each users
    $already_add_toast = false;
    foreach($recpts as $recpt){
      $recpt_mail = array();
        $recpt_mail[] = $recpt;

        ## get the language of the recipient
        $l = array('langcode' => $recpt['language'], 'context' => 'gofast:gofast_link_sharing');
        if ($recpt['method'] == 'to'){
          ## get all mails of receipt
          $recipient= $recpt['recpt'];
          $id_recpt = array_shift($recipients_ids_list);

          # create a unique link for each dest
          $file_sharing_link_dest = gofast_link_sharing_build_link($form_state['values']['node_id'],$id_recpt,$user->uid,$document_version);
          ## store it
          $form_state['values']['url'] = $file_sharing_link_dest;

          ## get default site name
          if (!module_exists('gofast_community'))
          { $defaultSiteName = "GoFAST"; }
          else
          { $defaultSiteName = "GoFAST Community"; }
          $site_name = variable_get('site_name', $defaultSiteName);

          $title = t('Document Sharing' , array(), $l);
          $subject = $form_state['values']['subject'];
          $footer = t('Message sent from %site_name', array('%site_name' => $site_name), $l);
          $body = theme('gofast-link-sharing-body', array(
            'author_pic' => theme('user_picture', array('account' => $user)),
              'author_name' => $user_name,
              'recip_name' => $recipient,
              'message' => nl2br($form_state['values']['message']),
              'node_title' => $form_state['values']['title'],
              'node_link' => $form_state['values']['url'],
              'expiry_msg' => t('This link will be functional for the next ' . '%exp_period. After this, it will be disabled.',
              array('%exp_period' => t(DEFAULT_EXPIRY_PERIOD_STRING, array(), $l)),
              $l),
              'l' => $l,
              'document_pic' => $document_pic,
            ));
            if (count($recpts) == 1){
              $recpt_mail[] = end($recpts);
            }
            $mail = array (
              'subject' => $subject,
              'title' => $title,
              'footer' => $footer,
              'body' => $body,
            );
            $ret = gofast_mail_queue_api_queue_ext($mail, $recpt_mail, time(), $user->uid);
            if($already_add_toast == false){
              flood_register_event('print_mail');
              drupal_set_message(t('An email has been sent to the user(s) with the document\'s sharing link.'));
            }
            $already_add_toast = true;
          }
        }
        if (count($recpts) > 1 ){
        $mail_active_user[] = array('recpt' => $user_mail, 'method' => 'to' );
        foreach ($copy_recipients_ids_list as $recpt_mail_recpt) {
          if (is_numeric($recpt_mail_recpt)){
            $user_dest  = user_load($recpt_mail_recpt);
            $mail_list .=  $user_dest->mail . '</br>';
          }else{
            $mail_list .= $recpt_mail_recpt . '</br>';
          }
        }

        $subject = t('You shared a document with users in ', array(), array('context' => 'gofast:gofast_link_sharing'))." ".$defaultSiteName;
        $body = theme('gofast-link-sharing-body-all-mail', array(
          'author_name' => $user_name,
          'recip_name' => $user_dest->name,
          'mail_list' => $mail_list,
          'message' => nl2br($form_state['values']['message']),
          'node_title' => $form_state['values']['title'],
          'node_link' => $form_state['values']['url'],
          'expiry_msg' => t('This link will be functional for the next ' . '%exp_period. After this, it will be disabled.',
          array('%exp_period' => t(DEFAULT_EXPIRY_PERIOD_STRING, array(), $l)),
          $l),
          'l' => $l,
          'document_pic' => $document_pic,
        ));

        $mail = array(
          'body' => $body,
          'title' => $title,
          'subject' => $subject,
          'footer' => $footer
        );
      }

      $ret = gofast_mail_queue_api_queue_ext($mail,  $mail_active_user, time(), $user->uid);
      if ($ret == TRUE) {
        flood_register_event('print_mail');
    }
  }
  $form_state['redirect'] = 'node';
}


function gofast_linksharing_build_receipt_mail($form_state){
    //build recipients to the mail
    $recpts = array();
    $to_array = array_unique(explode(',', $form_state['values']['to']));
    foreach($to_array as $to){
      if (ctype_digit($to)){ // Verify if it's an uid
          $to_user= user_load($to);
          $to_mail= $to_user->mail;
          $to_language = $to_user->language;
          $recpts[] = array('recpt' => $to_mail,'language' => $to_language,  'method' => 'to');
      }else{ // else it's an external email adress
          $recpts[] = array('recpt' => $to,'language' => $user->language,  'method' => 'to');
      }
    }
    //add current_user mail to cc
    if(count($recpts)==1){
        $recpts[] = array('recpt' => $form_state['values']['from_addr'], 'method' => 'cc' );
    }
    return $recpts;
}


/**
 * This is the form that allow to share by mail more than one documents.
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @return int
 */
function gofast_link_sharing_manage_mail_sharing_form($form, &$form_state) {
  global $user;

  $user_details = user_load($user->uid);
  $current_user_fullname=  gofast_user_display_name($user_details);

  #Destinataire
  $form['from_name'] = array(
    '#type' => 'hidden',
    '#title' => t('Your Name', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#size' => 60,
    '#maxlength' => 60,
    '#description' => t('Myself', array(), array('context' => 'gofast')),
    '#required' => TRUE,
    '#default_value' => $current_user_fullname ,
  );

  $form['from_addr'] = array(
    '#type' => 'hidden',
    '#value' => $user->mail,
  );

  $form['to'] = array(
    '#type' => 'textfield',
    '#title' => t('Recipient(s)', array(), array('context' => 'gofast')). ' *',
    '#size' => 60,
    '#maxlength' => 256,
    '#description' => t('Email of the person to whom the document will be shared', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => FALSE,
    '#autocomplete_path' => 'gofast_user_userlist_space_autocomplete',
    '#attributes' => array('class' => array('labelize-autocomplete labelize-insert'))
  );

  $form['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject', array(), array('context' => 'gofast')),
    '#size' => 60,
    '#maxlength' => 128,
    '#description' => t('Subject for the email that will be sent', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => TRUE,
    '#default_value' => $current_user_fullname.' '.t('shared with you documents on the ', array(), array('context' => 'gofast:gofast_link_sharing','langcode' => $user->language)) . variable_get('site_name', 'GoFAST 3'),
  );


  $selected_items_json = array();
  // Extract a variable set in gofast_ajax_file_browser.js to get all paths selected when you click on "manage shares by mail"
  if(variable_get("ithit_bulk_".$user->uid, NULL)){
      $selected_items_json = json_decode(rawurldecode(variable_get("ithit_bulk_".$user->uid, NULL)));
      variable_del("ithit_bulk_".$user->uid);
  }
  // Extract a variable set in gofast_ajax_file_browser.js to get all paths selected when you click on "manage shares by mail" in the cart
  if(variable_get("ithit_bulk_cart_".$user->uid, NULL)){

      //Get all nid node in the cart
      $selected_items_json = json_decode(rawurldecode(variable_get("ithit_bulk_cart_".$user->uid, NULL)));
      $nid_cart = array();
      $title_cart = array();
      // Reach all nid and transform it to a path (available with folders)
      foreach($selected_items_json as $select){
          $node = node_load($select->url);
          $paths = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE];
          foreach($paths as $path){
              array_push($nid_cart, $path['value'] . '/' . $node->title);
              array_push($title_cart,$node->title);
          }
      }
      foreach($nid_cart as $key=>$path_cart){
              $selected_items_json[$key]->url = '/alfresco/webdav' . $path_cart;
          }
      variable_del("ithit_bulk_cart_".$user->uid);
  }


  // Sorting the items received in parameter (Folders first, then Resource)
  usort($selected_items_json, function($a, $b) {
    return $a->type > $b->type;
  });

  $items_by_type = array();
  foreach ($selected_items_json as $selected_item_type) {
    $items_by_type[$selected_item_type->type][] = $selected_item_type->url;
  }

  $selected_nids = array();
  foreach ($items_by_type as $type => $items) {
    if ($type === 'Folder') {
        foreach($items as $item_path){
            $alfresco_path = str_replace("/alfresco/webdav", "", $item_path);
            $folder_item = gofast_cmis_item_get_by_path($alfresco_path,TRUE);
            $descendants = gofast_cmis_item_get_children($folder_item->id, FALSE, 'documents');
            foreach ($descendants as $descendant) {
              if (isset($descendant->nid)) {
                $selected_nids[$descendant->nid] = str_replace('webdav/','',$descendant->path);
              }
            }
        }
    }else {
      foreach ($items as $item_path) {
        //Force replication of this content if it's not yet replicated
        $_GET['href'] = $item_path;
        gofast_cmis_replicate(FALSE);

        $alfresco_path = str_replace("/alfresco/webdav", "", $item_path);
        $item = gofast_cmis_item_get_by_path($alfresco_path);
        if (isset($item->id)) {
            if(isset($item->properties['gofast:nid'])){
                if($item->properties['gofast:nid'] == 0){
                  $selected_nids[rand(-9999999, -1)] = $alfresco_path;
                }else{
                  $node = node_load($item->properties['gofast:nid']);
              //Exclude unsharable confidential documents
              $is_confidential = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Confidential Data";

                  if($is_confidential){
                      drupal_set_message($node->title . " " . t("can't be shared because it's a confidential document", array(), array('context' => "gofast:gofast_link_sharing")), "warning");
                      continue;
                  }

                  $is_internal = isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Internal Distribution";
                  if ($is_internal) {
                    drupal_set_message($node->title . " " . t("Document for Internal Distribution: sharing in Extranet spaces prohibited", array(), array('context' => "gofast:gofast_link_sharing")), "warning");
                    continue;
                  }

                  $selected_nids[$item->properties['gofast:nid']] = $alfresco_path;
                }
            }else{
                if(gofast_ajax_file_browser_get_nid_from_reference($item->properties['alfcmis:nodeRef']) == 0){
                  $selected_nids[rand(-9999999, -1)] = $alfresco_path;
                }else{
                  $selected_nids[gofast_ajax_file_browser_get_nid_from_reference($item->properties['alfcmis:nodeRef'])] = $alfresco_path;
                }
            }
        }
      }
    }
  }
//  print_r($selected_nids); exit;
  $form_state['selected_nodes_ids'] = array_keys($selected_nids);
  $form['selected_nodes_ids'] = array(
      '#type' => 'textfield',
      '#default_value' => json_encode(array_keys($selected_nids)),
      '#maxlength' => "99999"
  );
  $form['selected_nodes_ids']['#attributes']['class'][] = "gofast_display_none";
  foreach (array_unique($title_cart) as $title) {
    $rendered_items .= '<ul><li>' . $title . '</li></ul>';
  }
  if(empty($title_cart)){
      foreach(array_keys($selected_nids) as $select_nid){
          $rendered_items .= '<ul><li>' . node_load($select_nid)->title . '</li></ul>';
      }
  }


  $nodes = explode(',',$form['selected_nodes_ids']['#default_value']);
  $nodes = str_replace("[",'',$nodes);
  $nodes = str_replace("]",'',$nodes);
  $nodes_title = array();
  $nodes_nids = array();
  $nodes_links = array();
  foreach($nodes as $key=>$nid){
      $file_sharing_link = gofast_link_sharing_build_link($nid);
      $links .= '<label class="control-label" for="edit-link">'.t('Link to the document %title', array('%title' => node_load($nid)->title ), array('context' => 'gofast:gofast_link_sharing')).'</label>'
                 . '<div>'
                . '<div><a title="' .t('Copy the link') . '"href="#" onclick=\'event.preventDefault();event.stopPropagation();Gofast.copyToClipboard("'.$file_sharing_link.'")\'>'.$file_sharing_link.'</a><a title="'.t('Copy the link') .'" style="padding: 2px 7px; vertical-align: middle; color:#3498db; margin-left:10px;" class="btn-sm btn btn-default dropdown-toggle" onclick=\'event.preventDefault();event.stopPropagation();Gofast.copyToClipboard("'.$file_sharing_link.'")\'><i class="fa fa-files-o"></i></a></div>'
                 . '</div>';
      $nodes_title[$key] = node_load($nid)->title;
      $nodes_nids[$key] = $nid;
      $nodes_links[$key] = $file_sharing_link;
  }


  $form['link'] = array(
    '#markup' => '<div class="form-item form-item-link form-group" style="max-height:200px;overflow-y:scroll;">'
                    .$links
                .'</div>',
  );

  $form['title'] = array(
    '#type' => 'hidden',
    '#value' => json_encode($nodes_title),
  );

  $form['node_id'] = array(
    '#type' => 'hidden',
    '#value' => json_encode($nodes_nids),
  );

  $form['url'] = array(
    '#type' => 'hidden',
    '#value' => json_encode($nodes_links),
  );

  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Your message', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#default_value' => '',
    '#cols' => 60,
    '#rows' => 5,
    '#description' => t('This message will be included in the email that will be sent', array(), array('context' => 'gofast:gofast_link_sharing')),
    '#required' => FALSE,
  );

  $form['node'] = array(
    '#type' => 'hidden',
    '#value' => json_encode($nodes_nids),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send', array(), array('context' => 'gofast')),
    '#validate' => array('gofast_link_sharing_manage_mail_sharing_form_validate'),
    '#attributes' => array('class' => array('btn', 'btn-success', 'btn-sm')),
  );
  return $form;
}


/**
 * Form validation handler for gofast_link_sharing_manage_mail_sharing_form()
 *
 * @see gofast_link_sharing_manage_mail_sharing_form()
 */
function gofast_link_sharing_manage_mail_sharing_form_validate($form, &$form_state){
    if (isset($form_state['values']['op']) && $form_state['values']['op'] == t('Send', array(), array('context' => 'gofast'))) {

    $recipient_addresses = array();
    $recipients_value = json_decode($form_state['input']['edit-' . str_replace("_", "-", $form['to']['#name']) . '-hidden-values']);
    if($form_state['input']['to'] !== null && $form_state['input']['to'] !== ""){
        if(filter_var($form_state['input']['to'],FILTER_VALIDATE_EMAIL)){
            $recipients_value[] = $form_state['input']['to'];
        }else{
            form_set_error('to' , t('You must give a valid email address',array(),array('context' => 'gofast')));
            return;
        }
    }
    if(count($recipients_value) <1){
       form_set_error('to', t('You must fill all mandatory fields', array(), array('context' => 'gofast')));
       return;
    }

    // Fill 'to' with the hidden input of autocomplete field
    // and if node not in Extranet -> disabled capability to share with external people
    foreach ($recipients_value as $recipient) {
      if ($recipient->type === 'user') {
        $space_user = $recipient->id;
        $recipient_addresses[] = $space_user;
      }
      if ($recipient->type === 'node') {
        // Get nid from the group
        $node = node_load($recipient->id);
        // Get member id from the group
        $group_members = gofast_og_get_members_userlist_included($node,'active');
        foreach ($group_members as $member) {
            $user = user_load($member);
            if ($user->status == 1){
                $recipient_addresses[] = $member;
            }
        }
      }
      else if($recipient->type === 'userlist'){

        // Get the ULID from the userlist to send mails
        $ulid = $recipient->id;
        // Get all members of the group
        $group_members = gofast_userlist_get_members($ulid);
        foreach ($group_members as $uid => $member) {
          $user_members = user_load($uid);
          // Get only users active to send mail
          if ($user_members->status == 1){
            $recipient_addresses[] = $uid;
          }
        }
      }
      else if(valid_email_address($recipient)){
//        foreach(json_decode($form_state['input']['node_id']) as $key=>$nid){
//            if(! external_share_allowed($nid)){
//              form_set_error('to',
//                        t('This document must be located in "Extranet" to be '
//                          . 'shared with people external to GoFast (%recipient)',
//                          array( '%recipient' => $recipient ), array('context' => 'gofast:gofast_link_sharing')
//                        )
//                     );
//            }
//
//        }
        $recipient_addresses[] = $recipient;
      }
    }
    $recipient_addresses = array_unique($recipient_addresses);
    $form_state['values']['to'] = implode(',', $recipient_addresses);
  }

}



/**
 * Form submit handler for gofast_link_sharing_manage_mail_sharing_form()
 *
 * @see gofast_link_sharing_manage_mail_sharing_form_validate()
 */
function gofast_link_sharing_manage_mail_sharing_form_submit($form, &$form_state){

  //Give all informations for the asynchronous request
  $users_uid = explode(',',$form_state['values']['to']);

  // Get nids
  $nids = $form_state['values']['selected_nodes_ids'];

  //Get subject
  $subject = $form_state['values']['subject'];

  //Get message
  if(!empty($form_state['values']['message'])){
      $message = $form_state['values']['message'];
  }else{
      $message = t('No message',array(),array('context' => 'gofast'));
  }
  $html = "";

  foreach($users_uid as $key=>$uid){
      $title = $form_state['values']['title'][$key];
      //Create all theme for the modal
      $html .= theme('gofast_manage_linksharing_progression', array('uid' => $uid,'nids' => $nids,'subject' => $subject ,'message'=>$message));
      }

      $commands[] = ctools_modal_command_dismiss();

      //Display a modal that tracks the progress of publications
      $commands[] = ctools_modal_command_display(t("In progress", array(), array('context' => 'gofast:taxonomy')), $html);

      //Call asynchronous function
      $commands[] = gofast_command_callback('Gofast.manage_linksharing_process');
      $info_recipients = json_decode($form_state['input']['edit-to-hidden-values']);
      gofast_link_sharing_send_mail_to_transmitter($form,$form_state);
      foreach(json_decode($nids) as $nid){
          gofast_audit_linksharing(node_load($nid),$info_recipients);
          gofast_message_ext_create_linksharing_entity(node_load($nid), $info_recipients);
      }

      print(ajax_render($commands));
      exit;
}

/**
 * Sending an acknowledgment of receipt of the documents sent with the persons concerned
 * @global type $user
 * @param type $form
 * @param type $form_state
 */
function gofast_link_sharing_send_mail_to_transmitter($form,$form_state){
    global $user;
    global $base_url;

    ## get information of current user
    $user_name = gofast_user_display_name($user);
    $user_mail = $user->mail;

    ## get nids
    $nids = $form_state['values']['selected_nodes_ids'];
    $nodes_informations = array();

    ## get informations of all nodes to send (icons,build the hash..)
    foreach (json_decode($nids) as $key=>$nid){
      $node = node_load($nid);

      $node_title = $node->title;
      $nodes_informations[$key]['title'] = $node_title;

      ## get node icon
      $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
      ## store the icon in node information
      $nodes_informations[$key]['icon'] = gofast_mail_queue_fa_png($node_icon);
      $nodes_informations[$key]['url'] = $base_url .'/node/' . $nid;
    }

    $info_recipients= json_decode($form_state['input']['edit-to-hidden-values']);

    if (!empty($form_state['input']['to'])){
        $info_recipients[] = $form_state['input']['to'];
    }

    ## store all uid (or mail for extranet) in array
    $recipients_ids_list = array();
    foreach($info_recipients as  $info_recipient){

        ## get recipients to send the mails
        if ($info_recipient->type == user){
            array_push($recipients_ids_list, $info_recipient->id);
        }

        ## get recipients in the group to send mails
        else if ($info_recipient->type == node){
            ## get the NID from the group to send mails
            $node_id = node_load($info_recipient->id);
            ## get all members of the group
            $group_members = gofast_og_get_members($node_id,'active');
            foreach ($group_members as $member) {
                $user_members = user_load($member);
                ## get only users active to send mail
                if ($user_members->status == 1){
                    array_push($recipients_ids_list, $user_members->uid);
                }
            }
        }else if($info_recipient->type == 'userlist'){

            ## get the ULID from the userlist to send mails
            $ulid = $info_recipient->id;

            ## get all members of the group
            $group_members = gofast_userlist_get_members($ulid);
            foreach ($group_members as $uid => $member) {
                $user_members = user_load($uid);
                ## get only users active to send mail
                if ($user_members->status == 1){
                    array_push($recipients_ids_list, $user_members->uid);
                }
            }

        }else if(valid_email_address($info_recipient)){

            ## check if the document can be shared with an extranet
//            if(! external_share_allowed($form_state['values']['node_id'])){
//              form_set_error('to',
//                        t('This document must be located in "Extranet" to be '
//                          . 'shared with people external to GoFast (%recipient)',
//                          array( '%recipient' => $recipient ), array('context' => 'gofast:gofast_link_sharing')
//                        )
//                     );
//            }
            array_push($recipients_ids_list,$info_recipient);
        }
    }
    $mail_active_user[] = array('recpt' => $user_mail, 'method' => 'to' );

    ## store all mail in a array
    foreach (array_unique($recipients_ids_list) as $recpt_mail_recpt) {
        if (is_numeric($recpt_mail_recpt)){
            $user_dest  = user_load($recpt_mail_recpt);
            $mail_list .=  $user_dest->mail . '</br>';
        }else{
            $mail_list .= $recpt_mail_recpt . '</br>';
        }
    }

    ## get default site name
    if (!module_exists('gofast_community')){
        $defaultSiteName = "GoFAST";
    }else{
        $defaultSiteName = "GoFAST Community";
    }


    $l = array('langcode' => $user->language, 'context' => 'gofast:gofast_link_sharing');
    $subject = t('You shared documents with users in ', array(), array('context' => 'gofast:gofast_link_sharing'))." ".$defaultSiteName;
    $title = t('Information about shared documents' , array(), $l);
    if(!empty($form_state['values']['message'])){
        $message = $form_state['values']['message'];
    }else{
        $message = t('No message',array(),array('context' => 'gofast'));
    }
    $body = theme('gofast_manage_linksharing_body_all_mail', array(
        'author_name' => $user_name,
        'recip_name' => $user_dest->name,
        'nodes_informations' => $nodes_informations,
        'mail_list' => $mail_list,
        'message' => nl2br($message),
        'expiry_msg' => t('This link will be functional for the next ' . '%exp_period. After this, it will be disabled.',
        array('%exp_period' => t(DEFAULT_EXPIRY_PERIOD_STRING, array(), $l)),
        $l),
        'l' => $l,
        'document_pic' => $document_pic,
    ));
    $footer = t('Message sent from %site_name', array('%site_name' => $defaultSiteName), $l);

    ## send mail
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


/**
 * Function that sends asynchronously (see in file gofast_link_sharing.js) the mails to the different recipients
 * @global type $user
 * @global type $base_url
 * @return Returns an empty value to tell the JS code that the send is complete
 */
function gofast_manage_linksharing_process(){
      global $user;
      global $base_url;

      //Get current user information for the mail
      $user_name = gofast_user_display_name($user);
      $user_mail = $user->mail;

      //Get user id to send mail
      $uid = $_POST['process_uid'];
      //Get title mail
      $mail_subject = $_POST['process_subject'];
      //Get message mail
      $mail_message = $_POST['process_message'];

      //Get all documents nid to send
      $process_nids = json_decode($_POST['process_nids']);
      $nids = explode(',' , $process_nids);
      $nids = str_replace("[",'',$nids);
      $nids = str_replace("]",'',$nids);

      //Get user mail && language (condition extranet or no)
      if(!is_numeric($uid)){
          $recipient_user_mail = $uid;
          $recipient_user_language = $user->language;
      }else{
          $recipient_user = user_load($uid);
          $recipient_user_mail = user_load($uid)->mail;
          $recipient_user_language = user_load($uid)->language;
      }

      //Store recipient
      $recpts['to'] = array('recpt' => $recipient_user_mail,'language' => $recipient_user_language,  'method' => 'to');
      //Store current user
      if(count($recpts)==1){
        $recpts['cc'] = array('recpt' => $form_state['values']['from_addr'],  'method' => 'cc');
      }

      $nids_informations = array();
      //Get informations of all nodes to send (icons,build the hash..)
      foreach ($nids as $key=>$nid){
          $node = node_load($nid);
          $document_version = $node->field_current_version['und']['0']['value'];
          $hash = gofast_link_sharing_build_link($nids,$uid,$user->uid,$document_version,TRUE,TRUE,$nid);

          $node_title = $node->title;
          $nids_informations[$key]['title'] = $node_title;
          $nids_informations[$key]['version'] = $document_version;

          //Get node icon
          $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
          //Store the icon in node information
          $nids_informations[$key]['icon'] = gofast_mail_queue_fa_png($node_icon);
          $nids_informations[$key]['url'] = $hash ;
      }

      // Get default site name
      if (!module_exists('gofast_community')){
        $defaultSiteName = "GoFAST";
      }else{
        $defaultSiteName = "GoFAST Community";
      }
      // Get recipient language (current user language if it's an extranet user)
      $l = array('langcode' => $recpts['to']['language'], 'context' => 'gofast:gofast_link_sharing');
      $title = t('Shared documents' , array(), $l);
      $body = theme('gofast_manage_linksharing_body', array(
                  'author_pic' => theme('user_picture', array('account' => $user)),
                  'author_name' => $user_name,
                  'recip_name' => $recipient_user_mail,
                  'nodes_informations' => $nids_informations,
                  'download' => gofast_link_sharing_build_link($nids,$uid,$user->uid,NULL,TRUE,TRUE),
                  'message' => nl2br($mail_message),
                  'expiry_msg' => t('This link will be functional for the next ' . '%exp_period. After this, it will be disabled.',
                    array('%exp_period' => t(DEFAULT_EXPIRY_PERIOD_STRING, array(), $l)),
                    $l),
                  'l' => $l,
                  'document_pic' => $document_pic,
                 ));
      $footer = t('Message sent from %site_name', array('%site_name' => $defaultSiteName), $l);

      //Send mail
      $mail = array(
        'body' => $body,
        'title' => $title,
        'subject' => $mail_subject,
        'footer' => $footer
    );
    gofast_mail_queue_api_queue_ext($mail,  $recpts, time(), $user->uid);
    $ret = TRUE;

    if ($ret == TRUE) {
      flood_register_event('print_mail');
        drupal_set_message(t('An email has been sent to the user(s) with the document\'s sharing link.'));
      }
  print('');
  exit;
}

/**
 * Implements multi-sharing form (Check documents to download)
 * @global type $user
 * @param type $form
 * @param type $form_state
 * @return $form
 */
function gofast_multi_link_sharing_form($form, &$form_state) {

    global $user;
    global $base_url;


    $decrypt_datas = gofast_link_sharing_link_decrypt($_GET['hash']);
    $hash = $_GET['hash'];
    if(isset($decrypt_datas['nid_unique'])){
        $decrypt_nid_unique= $decrypt_datas['nid_unique'];
    }
    $decrypt_nid = explode('+',$decrypt_datas['nid']);

    $nids = array_filter($decrypt_nid);
    ## check if there is already a gofast session
    $is_gofast_user = gofast_link_sharing_is_gofast_user($user);
    if(isset($decrypt_datas['nid_unique'])){
        $node = node_load($decrypt_datas['nid_unique']);
        ## check if user has access to node
        $user_has_access = gofast_link_sharing_usr_has_access($node, $user);
        if($is_gofast_user && $user_has_access){
          $ddl_link = $base_url.":443".'/node/'.$decrypt_nid_unique;
          header('Location:'.$ddl_link);
          exit;
        }
    }
    $nids_title = array();
    foreach($nids as $key=>$nid){
        $node = node_load($nid);
        $version = $node->field_current_version['und']['0']['value'];
        $nids_title[$nid]=$node->title . '<code><strong> ' . t("Version : ", array(),array('context'=>'gofast:gofast_linksharing')) .$version . ' </strong></code>';
    }

    $form['documents'] = array(
      '#markup' => '<h3>' . t('Shared Documents : ', array(), array('context' => 'gofast:gofast_link_sharing')) . '</h4>',
    );

    $form['check_all'] = array(
     '#markup' => '<a id="edit-check-all" class="btn btn-sm btn-default" data-state="active" style="margin-top:20px;"><i class="fa fa-check"> </i>' .t(' Check all documents') . '</a>',
    );

    $form['links'] = array(
      '#title' => t('Choose documents you want to download'),
      '#type' => 'checkboxes',
      '#prefix' => '<div style="margin:30px;">',
      '#suffix' => '</div>',
      '#required' => TRUE,
      '#options' => $nids_title,
    );

    $form['actions']['submit'] = array(
      '#attributes' => array('class' => array('btn-primary')),
      '#type' => 'submit',
      '#prefix' => '<div style="margin-top:35px;">',
      '#suffix' => '</div>',
      '#value' => t('Download', array(), array("context" => 'gofast')),
    );


    return $form;
}

/**
 * Form validate handler for gofast_multi_link_sharing_form()
 *
 * @see gofast_link_sharing_form_validate()
 */
function gofast_multi_link_sharing_form_validate($form, &$form_state){
}

/**
 * Form submit handler for gofast_multi_link_sharing_form()
 *
 * @global $user
 * @global $base_url
 * @see gofast_link_sharing_form_validate()
 */
function gofast_multi_link_sharing_form_submit($form,&$form_state){
    global $user;

    usurp(1);
    set_time_limit(0);

    ## get documents checked
    $nodes_nid = $form['links']['#value'];

    ## create new zip object
    $zip = new ZipArchive();

    ## create a temp file & open it
    $tmp_file = "/var/www/d7/sites/default/files/".uniqid().".zip";
    $zip->open($tmp_file, ZipArchive::CREATE);
    $zip->addEmptyDir('.');

    ## close zip
    $zip->close();

    try{
        $alfresco_ticket = gofast_cmis_retrieve_and_store_ticket($user);
        usurp(false);

        foreach ($nodes_nid as $nid){
            $node = node_load($nid);
            $title = $node->title;
            $node_ref = gofast_cmis_node_get_item_id($node);
            $version = gofast_cmis_webservice_item_get_versions($node_ref)[0]->label;
            $extension = gofast_cmis_node_get_extension($node);
            $cmis_id = gofast_cmis_node_get_item_id($node);
            $object = gofast_cmis_item_get($cmis_id, TRUE);
            $link = $object->links["edit-media"];
            $ddl_link = $link .'&alf_ticket='.$alfresco_ticket;

            str_replace('.','_',$node->field_current_version['und']['0']['value']);
            $full_title = str_replace('.' . $extension , '_v' . $version . '.' . $extension,$title);

            //Download and add the file to the archive
            shell_exec("wget -O \"/var/www/d7/sites/default/files/$full_title\" \"$ddl_link\"");
            shell_exec("zip -urj $tmp_file \"/var/www/d7/sites/default/files/$full_title\"");
            unlink("/var/www/d7/sites/default/files/$full_title");
        }

        //Clear the user ticket
        gofast_cmis_unset_user_ticket();

        gofast_multi_link_sharing_send_mail($form,$form_state);

        //Prepare buffer for stream
        while (ob_get_level()) ob_end_clean();

        ## send the file to the browser as a download
        header('Content-disposition: attachment; filename=Documents_download.zip');
        header('Content-type: application/zip');
        header('Content-Length: ' . filesize($tmp_file));
        readfile($tmp_file);
        unlink($tmp_file);
        # need to exit because other header overload both header
        exit;
    }catch(Exception $e){
        gofast_cmis_unset_user_ticket();
    }
}

/**
 * Sending an email that a user has downloaded a shared document
 * @global type $base_url
 * @param type $form
 * @param type $form_state
 */
function gofast_multi_link_sharing_send_mail($form,$form_state){
    global $base_url;
    global $user;

    $decrypt_datas = gofast_link_sharing_link_decrypt($_GET['hash']);
    $nids = $form['links']['#value'];
    $emetteur = user_load($decrypt_datas['emetteur']);
    $version = $decrypt_datas['version'];
    $dest_id = $decrypt_datas['dest_id'];

    if(!is_numeric($dest_id)){
      ## not a GoFAST user
      $mail = $decrypt_datas['dest_id'];
      $nameDestinaire = $decrypt_datas['dest_id'];
    }else{
      $destinataire = user_load($dest_id);
      $nameDestinaire = gofast_user_display_name($destinataire);
    }

    $nodes_informations = array();
    $tab_int = 0;
    ## get all informations of all nodes shared
    foreach($nids as $nid){
        $node = node_load($nid);
        $node_title = $node->title;
        $nodes_informations[$tab_int]['title'] = $node_title;
        //Get node icon
        $node_icon = str_replace('<span>', '<span style="display:none;">', theme('node_title', array('node' => $node, 'link' => FALSE)));
        //Store the icon in node information
        $nodes_informations[$tab_int]['icon'] =  gofast_mail_queue_fa_png($node_icon);
        $nodes_informations[$tab_int]['url'] = $base_url .'/node/' . $nid;
        $tab_int += 1 ;
    }

    ## get default site name
    if (!module_exists('gofast_community')){
        $defaultSiteName = "GoFAST";
    }else{
        $defaultSiteName = "GoFAST Community";
    }

    usurp(1);
    $l = array('langcode' => $emetteur->language, 'context' => 'gofast:gofast_link_sharing');
    $title = t("Email sharing download",array(),array('langcode' => $emetteur->language, 'context' => 'sharing_dl'));
    $subject = t("@destinaire downloaded yours documents on the GoFast 3 plateform",array('@destinaire' => $nameDestinaire),array('langcode' => $emetteur->language,'context' => 'sharing_dl'));
    $body = theme('gofast-multi-sharing-download', array(
          'author_pic' => theme('user_picture', array('account' => $destinataire)),
          'author_name' => $nameDestinaire,
          'author_mail' => $mail,
          'recip_name' => $emetteur->mail,
          'nodes_informations' => $nodes_informations,
          'l' => $l,
         ));
    $footer = t('Message sent from ', array(), $l) . $defaultSiteName;
    usurp(false);
    $dest_mail=array();
    $dest_mail['0']['recpt'] = $emetteur->mail;
    $dest_mail['0']['method'] = 'to';

    ## send mail
    $mail = array(
        'body' => $body,
        'title' => $title,
        'subject' => $subject,
        'footer' => $footer
    );
    gofast_mail_queue_api_queue_ext($mail,  $dest_mail, time(), $dest_id);

    ## insert sharing_dl into audit
    $addr_ip = $_SERVER["REMOTE_ADDR"];
    $event_type = "sharing_dl";
    $last_event_unserialized["mod_timestamp"] = time();
    $last_event_unserialized["mod_author"] = 0;

    if($user->uid == 0){
	$last_event_unserialized["mod_ip"] = $addr_ip;
    }else{
	$last_event_unserialized["mod_ip"] = $user->uid;
    }

    foreach($nids as $nid){
	$node = node_load($nid);
	$node_version = $node->field_current_version[LANGUAGE_NONE][0]['value'];
	$last_event_unserialized["mod_version"] = $node_version;
	if($user->uid == 0){
	    $event = array('mod_author' => 0, 'mod_timestamp' => time(), "event" => $event_type, 'mod_version' => $node_version, 'mod_ip' => $addr_ip);
	}else{
	    $event = array('mod_author' => 0, 'mod_timestamp' => time(), "event" => $event_type, 'mod_version' => $node_version, 'mod_ip' => $user->uid);
	}
	$event = serialize($event);
	$last_event_serialized = rawurlencode($event);
        gofast_audit_insert_line_audit($nid,$event_type,$last_event_serialized, $last_event_unserialized );
    }
}
