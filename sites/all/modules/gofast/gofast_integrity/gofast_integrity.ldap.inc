<?php
function gofast_integrity_ldap_search_group($LdapServer, $gid, $field = "dn") {
    if (!$LdapServer) {
        $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
        $LdapServer->connectAndBindIfNotAlready();
    }
    $ldap_groups_dn = "ou=Groups,dc=" . explode("dc=", reset($LdapServer->basedn), 2)[1];
    $filter = "(cn=*" . $gid . ")";
    $attributes = array($field);
    $results = (array) $LdapServer->search($ldap_groups_dn, $filter, $attributes);
    //If multiple results, the last result being the more specific, previous results will match parent items
    $last_result = end($results)[$field];
    //If another field than "dn", values will be stored in an array
    return $last_result;
}


function gofast_integrity_check_create_space_ldap($LdapServer, $gid, &$failure) {
    $ldap_result = gofast_integrity_ldap_search_group($LdapServer, FALSE, $gid);
    if (!isset($ldap_result)) {
        $message = "Group reference is missing in LDAP server for space n°@gid.";
        watchdog("gofast_integrity_check_on_action", $message, array("@gid" => $gid), WATCHDOG_WARNING);
        $failure = TRUE;
    }
    if ($failure) {
        return str_replace("@gid", $gid, $message);
    }
}

function gofast_integrity_drupal_check_spaces_ldap_sync($items){
    $valid = array();
    $invalid = array();
    //Load ldap connection for groups
    $LdapServer = gofast_ldap_server_load(GOFAST_LDAP_INT_SERVER);
    $LdapServer->connectAndBindIfNotAlready();
    //Get the base_dn for Groups as the less specific organisational unit
    $ldap_groups_dn = "ou=Groups,dc=" . explode("dc=", reset($LdapServer->basedn), 2)[1];
    //Fetch into items
    foreach($items as $item){
        //Load Drupal node
        $node = node_load($item['nid']);
        //Get ldap distinguished name registered in Drupal db
        $dn = gofast_ldap_space_dn($node);
        if (!$dn) {
            $invalid[] = $item;
            continue;
        }
        $common_name = explode("cn=", $dn);
        //No cn is filled Drupal-side, something is wrong
        if (!isset($common_name[1])) {
            $invalid[] = $item;
            continue;
        }
        //Keep only the gid in the common name
        $gid_from_ldap_field = preg_replace("/\D*/", "", $common_name[1]);

        //Make ldap query to check if it matches data Drupal-side
        $ldap_result = gofast_integrity_ldap_search_group($LdapServer, $gid_from_ldap_field, "cn");

        //No data = no match, something is wrong
        if (!isset($ldap_result[0])) {
            $invalid[] = $item;
            continue;
        }
        $gid_from_ldap_server = preg_replace("/\D*/", "", $ldap_result[0]);
        //Data don't match, something is wrong
        if ($gid_from_ldap_server != $gid_from_ldap_field) {
            $invalid[] = $item;
            continue;
        }

        //Check if the gid filled in ldap matches the gid filled Alfresco-side
        $alf_ref = isset($node->{GOFAST_CMIS_FOLDER_REFERENCE_FIELD}[LANGUAGE_NONE][0])
            ? $node->{GOFAST_CMIS_FOLDER_REFERENCE_FIELD}[LANGUAGE_NONE][0]["value"]
            : gofast_cmis_node_get_reference_by_nid($item['nid'], FALSE, FALSE, TRUE);
        $alf_item = gofast_cmis_item_get($alf_ref);
        //We retrieved a folder or the data doesn't match, either case something is wrong
        if (!isset($alf_item->properties["gofast:nid"]) || $alf_item->properties["gofast:nid"] != $gid_from_ldap_field) {
            $invalid[] = $item;
            continue;
        }
        //This item is valid
        $valid[] = $item;
    }
    return array(
        "valid" => $valid,
        "invalid" => $invalid
    );
}