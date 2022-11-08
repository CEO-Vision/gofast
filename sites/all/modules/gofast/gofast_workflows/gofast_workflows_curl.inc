<?php

function gofast_workflows_curl_delete_case($case, $cookie_name){

    $baseURL = URL_BONITA;

    //connect
    $ch = curl_init();

    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/bpm/case/'.$case["rootCaseId"]);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");

    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);

    return $content;
}


function gofast_workflows_curl_create_user($data, $cookie_name){
    $baseURL = URL_BONITA;

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/user');
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));

    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);
    return $content;
}

function gofast_workflows_curl_delete_user($bonita_id, $cookie_name)
{
    $baseURL = URL_BONITA;

    //connect
    $ch = curl_init();

    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL . 'API/identity/user/' . $bonita_id);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE"); // note the DELETE here

    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/' . $cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);
    return $content;
}


function gofast_workflows_update_user($data,$bonita_id,$cookie_name){
     //connect
     $baseURL = URL_BONITA;
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/user/'.$bonita_id);
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT"); // note the PUT here
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);

    return $content;
}


function gofast_workflows_curl_add_role_user($data, $cookie_name){
        $baseURL = URL_BONITA;
        $ch2 = curl_init();
        curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen(json_encode($data)))
        );
        curl_setopt($ch2, CURLOPT_VERBOSE, true);
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/profileMember');
        curl_setopt($ch2, CURLOPT_POST, 1);
        curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));

        curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
        $content = gofast_workflows_curl_exec($ch2);

        curl_close($ch2);

        return $content;
}



function gofast_workflows_curl_add_user_into_group($data, $cookie_name){
    $baseURL = URL_BONITA;
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    //curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/207/'.$group_id.'/'.$role_id);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership');
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch2);
    curl_close($ch2);

    return $content;
}


function gofast_workflows_get_utilisateur_group_id(){
    gofast_workflows_get_cookie(true);
    $group_name = "Utilisateurs";
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group?p=0&c=100&f=name%3d'.$group_name);
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);
    $infos_return_group = json_decode($content);


    //s'il n'existe pas je le créer
    if(!isset($infos_return_group[0]->id)){

        $data = array('displayName' => $group_name, 'name' => $group_name);

        //connect
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen(json_encode($data)))
        );
        curl_setopt($ch, CURLOPT_VERBOSE, true);
        curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group');
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
        curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        $content =gofast_workflows_curl_exec($ch);

        curl_close($ch);

        $infos_return_group = json_decode($content);
        return $infos_return_group->id;

    }


    return $infos_return_group[0]->id;

}



function gofast_workflows_get_standard_role_id(){
    $role_name = "standard";
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    $ch = curl_init();
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/role?p=0&c=100&f=name%3d'.$role_name);
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    $infos_return_role = json_decode($content);

     //s'il n'existe pas je le créer
    if(!isset($infos_return_role[0]->id)){

        $data = array('displayName' => $role_name, 'name' => $role_name);

        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HTTPHEADER, array(
            'Content-Type: application/json',
            'Content-Length: ' . strlen(json_encode($data)))
        );
        curl_setopt($ch, CURLOPT_VERBOSE, true);
        curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/role');
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
        curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        $content = gofast_workflows_curl_exec($ch);

        $infos_return_role = json_decode($content);
        return $infos_return_role->id;

    }
    return $infos_return_role[0]->id;
}

function gofast_workflows_curl_get_user($myuser,$cookie_name){
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
        curl_setopt($ch, CURLOPT_POST, 0);
        curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
        //$bonita_user_id = ceo_vision_bonita_get_user_id($user);
        $url = URL_BONITA."API/identity/user";
        $params = "?f=userName=".gofast_remove_accents($myuser->name);

        curl_setopt($ch, CURLOPT_URL, $url.$params);
        $buf = gofast_workflows_curl_exec($ch);
        $array_results = json_decode($buf, true);

        return $array_results;


}




function gofast_workflows_curl_create_group($data, $cookie_name){

    $baseURL = URL_BONITA;

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group');
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);

    $infos_return_group = json_decode($content);

    return $infos_return_group;

}

function gofast_workflows_curl_update_group($data, $cookie_name, $bonita_groupId){

    $baseURL = URL_BONITA;

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group/'.$bonita_groupId);
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);

    curl_close($ch);

    $infos_return_group = json_decode($content);

    return $infos_return_group;
}




function gofast_workflows_curl_get_group($cookie_name, $parent_path, $group_name){
    $url = URL_BONITA."API/identity/group";
    //bug with ô
    $group_name = gofast_remove_accents($group_name);
    $params = "?p=0&c=100&f=parent_path%3d".rawurlencode($parent_path)."&f=name%3d".rawurlencode($group_name);

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url.$params);
    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);

    if(isset($array_results[0])){
         return $array_results[0];
    }else{
        return null;
    }

}

function gofast_workflows_curl_get_userlist($cookie_name, $ulid){
    $url = URL_BONITA."API/identity/group";
    $params = "?p=0&c=100&f=name%3d" . "ul_" . $ulid;

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url.$params);
    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);

    if(isset($array_results[0])){
         return $array_results[0];
    }else{
        return null;
    }

}

function gofast_workflows_curl_get_members_group_bonita($bonita_groupid){
    $url = URL_BONITA."API/identity/user";
    $params = "?p=0&c=10000&o=lastname%20ASC&f=enabled%3dtrue&f=group_id%3d".$bonita_groupid;

    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url.$params);
    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);
    return $array_results;
}




/* fonction qui rajoute le user bonita recu en parametre dans le groupe bonita recu en parametre */
function gofast_workflows_curl_delete_user_from_bonitagroup($bonita_uid, $bonita_groupid){
    $cookie_name = "cookie_bonitainstall.txt";
    $baseURL = URL_BONITA;

    //on recupere l'id du role standard
    $role_id = gofast_workflows_get_standard_role_id();
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/'.$bonita_uid."/".$bonita_groupid."/".$role_id);
    curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch2);
    curl_close($ch2);

    return $content;
}



/* fonction qui rajoute le user bonita recu en parametre dans le groupe bonita recu en parametre */
function gofast_workflows_curl_add_user_into_bonitagroup($bonita_uid, $bonita_groupid){
    //gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    //on recupere l'id du role standard
    $role_id = gofast_workflows_get_standard_role_id();
    $data = array('group_id' => "$bonita_groupid", 'role_id' => "$role_id", 'user_id' => "$bonita_uid");
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    //curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/207/'.$group_id.'/'.$role_id);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership');
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch2);
    curl_close($ch2);

    return $content;
}

function gofast_workflows_deploy_business_data_model(){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    //Firstly, stop the BPM services
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/system/tenant/1');
    curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    $data = array("paused" => "true");
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    gofast_workflows_curl_exec($ch2);


    //Import the Business data model
    $data = array('fileUpload' => "bdm.zip");
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    //curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/207/'.$group_id.'/'.$role_id);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/tenant/bdm');
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    gofast_workflows_curl_exec($ch2);


    //We can enable the BPM services
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/system/tenant/1');
    curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    $data = array("paused" => "false");
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    gofast_workflows_curl_exec($ch2);
}

function gofast_workflows_deploy_gofast_application(){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    //Get potential existing application
    //Get available pages list
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application?c=1&d=profileId&d=createdBy&d=updatedBy&d=layoutId&p=0');
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    $available_apps = json_decode(curl_exec($ch2), TRUE);

    if(count($available_apps) > 0){
        //Destroy existing application
        $ch2 = curl_init();
        curl_setopt($ch2, CURLOPT_VERBOSE, true);
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application/'.$available_apps[0]["id"]);
        curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "DELETE");

        curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
        curl_exec($ch2);
    }

    //Create the application
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json;charset=UTF-8',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application');
    curl_setopt($ch2, CURLOPT_POST, 1);
    $data = array(
            "displayName" => "GoFAST",
            "description" => "GoFAST application",
            "profileId" => "1",
            "token" => "GoFAST",
            "version" => "1.0"
        );
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');

    $application = json_decode(curl_exec($ch2), TRUE);

    $application_id = $application['id'];

    //Get available pages list
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/page?c=100&f=contentType%3Dpage&p=0');
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    $available_pages = json_decode(curl_exec($ch2), TRUE);

    //Search for our pages
    foreach($available_pages as $available_page){
        if($available_page['urlToken'] == "custompage_LightDashboard"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboard",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }
        if($available_page['urlToken'] == "custompage_LightDashboardDocumentMy"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboardDocumentMy",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }
        if($available_page['urlToken'] == "custompage_LightDashboardDocumentOther"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboardDocumentOther",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }
        if($available_page['urlToken'] == "custompage_LightDashboardDocumentHistory"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboardDocumentHistory",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }
        if($available_page['urlToken'] == "custompage_LightDashboardMy"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboardMy",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }
        if($available_page['urlToken'] == "custompage_LightDashboardOther"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "lightDashboardOther",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }

        if($available_page['urlToken'] == "custompage_HistoryBdm"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "historyBdm",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }

        if($available_page['urlToken'] == "custompage_TasksInProcess"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "tasksInProcess",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }

        if($available_page['urlToken'] == "custompage_FullDashboardSearch"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "fullDashboardSearch",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }

        if($available_page['urlToken'] == "custompage_BlockDashboard"){
            //Bind the page
            $ch2 = curl_init();
            curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
                'Content-Type: application/json;charset=UTF-8',
                )
            );

            curl_setopt($ch2, CURLOPT_VERBOSE, true);
            curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/living/application-page');
            curl_setopt($ch2, CURLOPT_POST, 1);
            $data = array(
                    "applicationId" => $application_id,
                    "pageId" => $available_page['id'],
                    "token" => "blockDashboard",
                );
            curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
            curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
            curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
            curl_setopt($ch2, CURLOPT_PROXY, '');
            curl_exec($ch2);
        }

    }


}

function gofast_workflows_deploy_page($name){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    //first, check if a page exists with same name
    $decoded_name = str_replace("page-", "",  $name);
    $decoded_name = str_replace(".zip", "",  $decoded_name);
    gofast_workflows_get_cookie(true);
        $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
        $baseURL = URL_BONITA;

        //first, check if a page exists with same name
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HTTPHEADER, array(
            'Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryf49xBgZOk14Acele',
            )
        );

        curl_setopt($ch, CURLOPT_VERBOSE, true);
        curl_setopt($ch, CURLOPT_URL, $baseURL.'API/portal/page?p=0&c=100&s='.$decoded_name );
        curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($ch, CURLOPT_PROXY, '');
        $response = json_decode(curl_exec($ch))[0];
        if(isset($response->id)){
           $page_id = $response->id;
       }else{
             $page_id = null;
       }


    //Send the file to the server
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryf49xBgZOk14Acele',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'portal/pageUpload?action=add');
    curl_setopt($ch2, CURLOPT_POST, 1);
    $data = array("name" => $name, "file" => curl_file_create("/var/www/d7/sites/all/modules/gofast/gofast_workflows/ressources/ui_designer/pages/build/" . $name));
    curl_setopt($ch2, CURLOPT_POSTFIELDS, $data);
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    $temp_file = curl_exec($ch2);

    //Ask the server for file integration
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json;charset=UTF-8',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    if($page_id !== null){
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/page/'.$page_id);
        curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    }else{
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/page');
    }
    curl_setopt($ch2, CURLOPT_POST, 1);

    $data = array("formError" => "", "pageZip" => $temp_file);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    curl_exec($ch2);
}

function gofast_workflows_deploy_rest_api_extension($name){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    //first, check if a page exists with same name
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryf49xBgZOk14Acele',
        )
    );
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/portal/page?p=0&c=100');
    curl_setopt($ch, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_PROXY, '');
    $response = json_decode(curl_exec($ch));
    foreach($response as $resource){
        if(isset($resource->id) && $resource->contentName == $name){
           $page_id = $resource->id;
           $action = "edit";
           break;
        }else{
           $page_id = null;
           $action = "add";
        }
    }

    //Send the file to the server
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryf49xBgZOk14Acele',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'portal/pageUpload?action=' . $action);
    curl_setopt($ch2, CURLOPT_POST, 1);
    $data = array("name" => $name, "file" => curl_file_create("/var/www/d7/sites/all/modules/gofast/gofast_workflows/ressources/rest_api_extensions/build/" . $name));
    curl_setopt($ch2, CURLOPT_POSTFIELDS, $data);
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    $temp_file = curl_exec($ch2);

    //Ask the server for file integration
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json;charset=UTF-8',
        )
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    if($page_id !== NULL){
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/page/' . $page_id);
        curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    }else{
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/portal/page');
        curl_setopt($ch2, CURLOPT_POST, 1);
    }
    $data = array("formError" => "", "pageZip" => $temp_file);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch2, CURLOPT_PROXY, '');
    curl_exec($ch2);
}


function gofast_workflows_deploy_new_version_standard_process($old_name, $new_name, $actor = "Utilisateurs"){
    //at this point, the .bar files are already uploaded into bonita server
    //first we add the processes
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $baseURL = URL_BONITA;

    $data = array('fileupload' => $new_name);
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    //curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/207/'.$group_id.'/'.$role_id);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/process');
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $process = json_decode(gofast_workflows_curl_exec($ch2));
    $process_id = $process->id;
    if($process->actorinitiatorid == -1){
        //we have to search for an actor from this process
        $ch2 = curl_init();
        curl_setopt($ch2, CURLOPT_VERBOSE, true);
        curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/actor?p=0&c=100&f=process_id='.$process_id);
        curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
        $actors_process_object = json_decode(gofast_workflows_curl_exec($ch2));

        $process_actorinitiatorid = $actors_process_object[0]->id;

    }else{
        $process_actorinitiatorid = $process->actorinitiatorid;
    }
    $process_version = $process->version;
    $process_name = $process->name;

    if($actor == "Utilisateurs"){
        $actor_id = gofast_workflows_get_utilisateur_group_id();
    }else{
        $actor_id = $actor;
    }

    //map actors
    $data = array('actor_id' => "$process_actorinitiatorid","member_type" => "GROUP", "group_id" => $actor_id);
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    //curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/identity/membership/207/'.$group_id.'/'.$role_id);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/actorMember');
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $actor_member_object = json_decode(gofast_workflows_curl_exec($ch2));


    //then we activate this process
    $data = array('activationState' => "ENABLED");
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/process/'.$process_id);
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $process_object = json_decode(gofast_workflows_curl_exec($ch2));




    //then disable the same process with previous version
   //first, search the process with same name than the new one, but with the previous version
    $ch2 = curl_init();

    $old_process_name = explode(('--'), $old_name)[0];
    $old_process_version = str_replace(".bar", "", explode(('--'), $old_name)[1]);

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/process/?f=name%3d'.rawurlencode($old_process_name).'&f=version%3d'.$old_process_version);
    print_r("calling " . $baseURL.'API/bpm/process/?f=name%3d'.rawurlencode($old_process_name).'&f=version%3d'.$old_process_version);
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $previous_process_object = json_decode(gofast_workflows_curl_exec($ch2));

    $previous_process_object_id = $previous_process_object[0]->id;



    //disable this process
    $data = array('activationState' => "DISABLED");
    $ch2 = curl_init();
    curl_setopt($ch2, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );

    curl_setopt($ch2, CURLOPT_VERBOSE, true);
    curl_setopt($ch2, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch2, CURLOPT_URL, $baseURL.'API/bpm/process/'.$previous_process_object_id);
    curl_setopt($ch2, CURLOPT_POST, 1);
    curl_setopt($ch2, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch2, CURLOPT_COOKIEFILE, 'sites/default/files/swf/'.$cookie_name);
    curl_setopt($ch2, CURLOPT_RETURNTRANSFER, true);
    $disabled_previous_process_object = json_decode(gofast_workflows_curl_exec($ch2));

}


function gofast_workflows_get_actor_members($actor_id){
    $url = URL_BONITA."API/bpm/actorMember";
    $params = "?p=0&c=10&f=actor_id%3d".$actor_id;

    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url.$params);
    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);

    return $array_results;
}

function gofast_workflows_get_actor_members_list($actor_id){

    $array_results = gofast_workflows_get_actor_members($actor_id);
    $string_result = "";
    if(count($array_results) > 0){
        foreach($array_results as $key=>$result){
            if($result["user_id"] != "-1"){
                 $myuser = gofast_workflows_get_drupalid_from_bonitaid($result["user_id"], true);
                 $string_result .= theme('user_picture', array('account' => $myuser, 'dimensions' => 20));
            }
        }
    }
    return $string_result;

}


function gofast_workflows_put_task_assignee($task_id, $bonita_uid){
        
    $url = URL_BONITA."API/bpm/userTask/" . $task_id;
    
    // get cookie
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";

    // Set new assignee id
    $data = array("assigned_id" => $bonita_uid);
        
    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT");
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_URL, $url);
    
    $buf = gofast_workflows_curl_exec($ch);
    $result = json_decode($buf, true);
    return $result;
}

function gofast_workflows_reassign_user_tasks_to_someone($user_uid, $target_bonita_uid){
    $tasks = gofast_workflows_get_list_actives_tasks(false,false,true,false,true,$user_uid);
    foreach($tasks as $id => $task){
        $taskId = $task['id'];
        gofast_workflows_put_task_assignee($taskId, $target_bonita_uid);
    }
}

function gofast_workflows_get_infos_task_count_rest_api(){
    global $user;

    if($user->uid == 0 || $user->uid == 1){
       $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
       $bonita_user_id = true;
    }else{
       gofast_workflows_get_cookie();
       $cookie_name = "cookie_bonita".$user->name.".txt";
       $bonita_user_id = gofast_workflows_get_user_id($user);

    }
       $ch = curl_init();
       curl_setopt($ch, CURLOPT_HEADER, 0);
       curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
       curl_setopt($ch, CURLOPT_POST, 0);
       curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

        $url = URL_BONITA."API/extension/tasksCount";
        curl_setopt($ch, CURLOPT_URL, $url);
        $buf = gofast_workflows_curl_exec($ch);

        $array_results = json_decode($buf, true);
          
    return $array_results;
    
}
