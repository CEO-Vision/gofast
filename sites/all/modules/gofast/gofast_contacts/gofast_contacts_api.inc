<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function gofast_api_contact_autocomplete($params){
    switch($params['method']){
        case 'GET':
            gofast_contacts_get_contact_autocomplete($params);
            break;
        default:
            gofast_api_not_implemented("This method");
            break;
    }
}

function gofast_contacts_get_contact_autocomplete($params){
    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a str param
    if(isset($params['str'])){
        $str = $params['str'];
    }else{
        gofast_api_mandatory_parameter("str");
    }

    if(strlen($str) < 1){
        gofast_api_success(array());
    }

    $options_ac_contact = array(
        'bundle' => array('contact'),
        'format_key_callback' => 'gofast_contacts_api_autocomplete_format_key',
        'format_value_callback' => 'gofast_contacts_api_autocomplete_format_value'
    );

    $output = gofast_ac_query($str, 'node', $options_ac_contact);

    gofast_api_success($output);
}


function gofast_contacts_api_autocomplete_format_key($entity_type, $entity) {
    return $entity->nid;
}

function gofast_contacts_api_autocomplete_format_value($entity_type, $entity) {
    $name = $entity->field_contact_name[LANGUAGE_NONE][0]['value'];
    $firstname = $entity->field_contact_firstname[LANGUAGE_NONE][0]['value'];
    $displayname = $name." ".$firstname;
    $phone = $entity->field_contact_phone[LANGUAGE_NONE][0]['value'];
    $society = $entity->field_contact_entity[LANGUAGE_NONE][0]['value'];
    $mail = $entity->field_contact_email[LANGUAGE_NONE][0]['value'];
    return array('nid' => $entity->nid, 'name' => $name, 'firstname' => $firstname, 'displayname' => $displayname , 'email' => $mail, 'entity' => $society, 'mobile' => $phone);
}

function gofast_contacts_query_first_and_last_name_alter(QueryAlterableInterface $query) {
    $word = $query->getMetaData('str');
    $str = '%'.$word.'%';
    
    //Join tables
    $query->rightJoin('field_data_field_contact_name', 'n', 'node.nid = n.entity_id');
    $query->rightJoin('field_data_field_contact_firstname', 'fn', 'node.nid = fn.entity_id');

    //Build or condition
    $or = db_or()->condition('n.field_contact_name_value', $str, 'LIKE')
            ->condition('fn.field_contact_firstname_value', $str, 'LIKE');
    $query->condition($or);

}