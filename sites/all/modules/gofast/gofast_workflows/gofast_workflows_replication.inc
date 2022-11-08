<?php



function gofast_workflows_get_cookie($admin = false, $real_password = false, $myuser = NULL){
    if($admin == false){
        if(empty($myuser)){
            global $user;
            $myuser = $user;
        }
            if(isset($_SESSION['bonita_cookie_problem_' . $myuser->uid])){
                return;
            }
            $username = $myuser->name;
            if($real_password == false){
                $bonita_id = gofast_workflows_get_user_id($myuser);
                $password = gofast_workflows_get_bonita_token($bonita_id);
            }else{
                 $password = $real_password;
            }
            $baseURL = URL_BONITA;   
            $cookie_name = "cookie_bonita".$user->name.".txt";
            $data = array('username' => $username, 'password' => $password, 'redirect' => 'false');
    }else{
          
            $username = BONITA_TECHNICAL_LOGIN;    
            $password = BONITA_TECHNICAL_PASSWORD;
            $baseURL = URL_BONITA;   

            $cookie_name = "cookie_bonita".$username.".txt";
            $data = array('username' => $username, 'password' => $password, 'redirect' => 'false');
    }  
    $date_modif_cookie = @filemtime ('sites/default/files/swf/'.$cookie_name);
    if(time() - $date_modif_cookie > 60*5){
        //watchdog("debug get cookie", $cookie_name);
        setcookie('bonita_sess_timestamp', '0', 0, '/', "", true);  
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $baseURL.'/loginservice');
        curl_setopt($ch, CURLOPT_POST, 1);
        curl_setopt($ch, CURLOPT_POSTFIELDS, gofast_workflows_prepare_post_fields($data));
        curl_setopt($ch, CURLOPT_COOKIEJAR, 'sites/default/files/swf/'.$cookie_name);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 2); 
        curl_setopt($ch, CURLOPT_TIMEOUT, 2);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
         if($admin == false){
            $content = gofast_workflows_login_curl_exec($ch, 'sites/default/files/swf/'.$cookie_name);
         }else{
            $content = gofast_workflows_login_curl_exec($ch);
         }
        curl_close($ch);
    }else{      
        $content = "";
    }
    
   return $content;
        
        
}



function gofast_workflows_create_user($myuser = null, $password = null){
    
    //on créer le cookie en tant qu'admin bonita
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    //on prepare les infos du user que l'on va créer
    if($myuser){  
       
        $username = $myuser->name; 
        $firstname = $myuser->ldap_user_givenname[LANGUAGE_NONE][0]['value'];
        $lastname = $myuser->ldap_user_sn[LANGUAGE_NONE][0]['value'];
        $password = "password";
        if(mb_detect_encoding($username, 'UTF-8', true) != false){
            //$encoded_username = utf8_encode($username);
            $encoded_username = $username;
        }else{
            $encoded_username = $username;
        }
         if(mb_detect_encoding($password, 'UTF-8', true) != false){
            $encoded_password = utf8_encode($password);
        }else{
            $encoded_password = $password;
        }
        //if(mb_detect_encoding($firstname, 'UTF-8', true) != false){
        //    $encoded_firstname = utf8_encode($firstname);
        //}else{
            $encoded_firstname = $firstname;
        //} 
        //if(mb_detect_encoding($lastname, 'UTF-8', true) != false){
        //    $encoded_lastname = utf8_encode($lastname);
        //}else{
            $encoded_lastname = $lastname;
        //}
    }else{
         global $user;  
        $username = $user->name;    
        $password = "password";

        $firstname = $user->ldap_user_givenname[LANGUAGE_NONE][0]['value'];
        $lastname = $user->ldap_user_sn[LANGUAGE_NONE][0]['value'];
        if(mb_detect_encoding($username, 'UTF-8', true) != false){
            $encoded_username = utf8_encode($username);        
        }else{
            $encoded_username = $username;
        }
        if(mb_detect_encoding($password, 'UTF-8', true) != false){
            $encoded_password = utf8_encode($password);
        }else{
            $encoded_password = $password;
        }
        if(mb_detect_encoding($firstname, 'UTF-8', true) != false){
            $encoded_firstname = utf8_encode($firstname);
        }else{
            $encoded_firstname = $firstname;
        } 
        if(mb_detect_encoding($lastname, 'UTF-8', true) != false){
            $encoded_lastname = utf8_encode($lastname);
        }else{
            $encoded_lastname = $lastname;
        }
    }
    $baseURL = URL_BONITA;     
    $data = array('userName' => $encoded_username, 'password' => $encoded_password, "password_confirm" => $encoded_password, "firstname" => $encoded_firstname ,"lastname" => $encoded_lastname, "enabled" => "true");
 
    $content = gofast_workflows_curl_create_user($data, $cookie_name);
    
// var_dump($content);
    $infos_return_user = json_decode($content);
    
    //une fois le user crée, je lui attribue le rôle user
    $data = array('profile_id' => "1", 'member_type' => "USER", 'user_id' => $infos_return_user->id);   
    $content = gofast_workflows_curl_add_role_user($data, $cookie_name);
    
    
    //une fois le user crée et le profil attribué, je met le user dans le groupe ou se trouve tous les utilisateurs
    $group_id = gofast_workflows_get_utilisateur_group_id();  
    //on recupere l'id du role standard   
    $role_id = gofast_workflows_get_standard_role_id();
    $data = array('group_id' => "$group_id", 'role_id' => "$role_id", 'user_id' => "$infos_return_user->id");
   
    $content = gofast_workflows_curl_add_user_into_group($data, $cookie_name);
    $bonita_uid = gofast_workflows_get_user_id($myuser);
   return $content;  
        
} 



function gofast_workflows_delete_user($bonita_userId){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    $baseURL = URL_BONITA;   

    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/user/'.$bonita_userId);

    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);
    
    curl_close($ch);

   return $content;  
        
}

function gofast_workflows_list_all_groups(){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    $baseURL = URL_BONITA;   

    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group?p=0&c=10000');

    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);
    
    curl_close($ch);

   return json_decode($content);  
        
} 

function gofast_workflows_delete_group($bonita_groupId){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    $baseURL = URL_BONITA;   

    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $baseURL.'API/identity/group/'.$bonita_groupId);

    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "DELETE");
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    $content = gofast_workflows_curl_exec($ch);
    
    curl_close($ch);

   return $content;  
        
} 


function gofast_workflows_delete_cookie($cookie_name){
    @drupal_unlink("sites/default/files/swf/".$cookie_name);
}
   


/* fonction qui remet à jour le mot de passe Bonita avec celui rentré par l'utilisateur pour se loger sur Drupal
 * On appel cette fonction lorque la fonction de login vers Bonita ne fonctionne pas
 */
function gofast_workflows_update_user_password($bonita_id, $password){
    
     //on créer le cookie en tant qu'admin bonita
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    //on prepare les infos du user que l'on va mettre à jour
    global $user; 
 
    $username = $user->name;  
    
    if(isset($_SESSION['bonita_cookie_problem_' . $user->uid])){
       unset($_SESSION['bonita_cookie_problem_' . $user->uid]);
    }
     
    if(mb_detect_encoding($password, 'UTF-8', true) != false){
        //$encoded_password = utf8_encode($password);
        $encoded_password = $password;
    }else{
        //$encoded_password = $password;
        $encoded_password = utf8_encode($password);
    }
    if(mb_detect_encoding($username, 'UTF-8', true) != false){
        //$encoded_username = utf8_encode($username);
        $encoded_username = $username;
    }else{
        $encoded_username = $username;
    }
    
  
    $data = array('userName' => $encoded_username, 'password' => $encoded_password, "password_confirm" => $encoded_password);

    //on supprime le cookie actuel
    $user_cookie_name = "cookie_bonita".$username.".txt";
    gofast_workflows_delete_cookie($user_cookie_name);
   
    $content = gofast_workflows_update_user($data,$bonita_id,$cookie_name);

    $infos_return_user = json_decode($content);
    
    return $infos_return_user;
}


/* fonction qui replique sur Bonita le groupe GF recu en parametre (en conservant sa hierarchie) */
function gofast_workflows_create_group($group_node){
    
    //displayname
    $displayName = $group_node->title;
    $name = $group_node->title;
  
    //on recupere le noeud du parent de ce groupe
    $parent_object = _gofast_og_space_get_parent($group_node, true);

    
    if($parent_object !== false){
        //on est dans le cas d'un groupe ou d'une orga de premier niveau d'un point de vue Bonita (donc juste en dessous de Groupes ou Organisations)
        if(count($parent_object->og_group_ref) == 0){
            $bonita_parent_id = null;
            //Fix bug GOFAST-5091
            $name = $group_node->title."_".$group_node->nid;
            $displayName = $group_node->title."_".$group_node->nid;
        }else{
            $bonita_parent_object = gofast_workflows_get_bonitagroup_from_gofastgroup($parent_object);
           
            if($bonita_parent_object !== null){       
                $bonita_parent_id = $bonita_parent_object["id"];
            }else{
                watchdog("GOFAST : Bonita error getting parent group bonita id", "gid : ".$parent_object->nid);
                return null;
            }
        }
    }else{
        watchdog("GOFAST : Bonita error unable to create first parent node", "gid : ".$group_node->nid);
        //on est dans le cas ou la variable $group_node corespond au noeud de tout premier niveau (groupe ou organisation) donc on ne fait rien car on ne va pas le repliquer sur Bonita (pour l'instant en tout cas)
        return null;
        
    }

       
    //on créer le cookie en tant qu'admin bonita
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
  
    $data = array('displayName' => $displayName, 'name' => $name);
    
    if($bonita_parent_id){
      $data['parent_group_id'] = $bonita_parent_id;
    }
    
    $infos_created_group = gofast_workflows_curl_create_group($data, $cookie_name);
    gofast_workflows_synchronize_members_group($group_node);
    return $infos_created_group;
       
}

/*
 * Replicate a userlist in Bonita
 */
function gofast_workflows_create_userlist($userlist){
    
    //displayname
    $displayName = "ul_" . $userlist->ulid;
    $name = "ul_" . $userlist->ulid;

    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
  
    $data = array('displayName' => $displayName, 'name' => $name);
    
    $infos_created_group = gofast_workflows_curl_create_group($data, $cookie_name);
    gofast_workflows_synchronize_members_userlist($userlist);
    return $infos_created_group;
       
}

/* fonction qui renomme sur Bonita le groupe GF recu en parametre (en conservant sa hierarchie) */
function gofast_workflows_update_group($group_node, $old_group_node){
     watchdog("debug update entity3",$old_group_node->title );
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    //displayname  
    $name = $group_node->title."_".$group_node->nid;
    $displayName = $group_node->title."_".$group_node->nid;
  
    //on recupere le noeud du parent de ce groupe
    // TODO manage space move
    // $parent_object = _gofast_og_space_get_parent($group_node, true);
    $bonita_object = gofast_workflows_get_bonitagroup_from_gofastgroup($old_group_node);
           
    if($bonita_object !== null){       
        $bonita_id = $bonita_object["id"];
    }else{
        watchdog("GOFAST : Bonita error getting parent group bonita id", "gid : ".$old_group_node->nid);
        return null;
    }
    
   $data = array('displayName' => $displayName, 'name' => $name);
   watchdog("debug update entity4",json_encode($data) );
   $infos_updated_group = gofast_workflows_curl_update_group($data, $cookie_name, $bonita_id);

    return $infos_updated_group;
       
}

function gofast_workflows_update_userlist($userlist, $old_userlist){
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    
    //displayname  
    $ulid = $userlist->ulid;
  
    //on recupere le noeud du parent de ce groupe
    // TODO manage space move
    // $parent_object = _gofast_og_space_get_parent($group_node, true);
    $bonita_object = gofast_workflows_get_bonitagroup_from_userlist($userlist);
           
    if($bonita_object !== null){       
        $bonita_id = $bonita_object["id"];
    }else{
        return null;
    }
    
   $data = array('displayName' => 'ul_' . $ulid, 'name' => 'ul_' . $ulid);
   
   $infos_updated_group = gofast_workflows_curl_update_group($data, $cookie_name, $bonita_id);

   return $infos_updated_group;
       
}

function gofast_workflows_get_bonitagroup_from_gofastgroup($group_node){
    
    $path = gofast_cmis_space_get_drupal_path($group_node->nid);
    $array_path = explode("/", $path);
    if(count($array_path) > 0){
        foreach($array_path as $key=>$path){
           if($key == 2){
               $parent_gid = gofast_og_get_group_id_from_title_2("/Sites/_".$array_path[1]."/_".$array_path[2], TRUE);
               $array_path[2] = $array_path[2]."_".$parent_gid;
           }
        }
    }
    //no Orga or Group notion in Bonita
    $path_modified = str_replace("/Organisations", "", implode("/", $array_path));
    $path_modified = str_replace("/Groups", "", $path_modified);
    $path_modified = str_replace("/Extranet", "", $path_modified);
    $path_modified = str_replace("/Public", "", $path_modified);
    $path_modified = str_replace("/".$group_node->title."_".$group_node->nid, "", $path_modified);
    $path_modified = str_replace("/".$group_node->title, "", $path_modified);

    if($path_modified == ""){
         $group_name = $group_node->title."_".$group_node->nid;
    }else{
        $group_name = $group_node->title;
    }
    //on créer le cookie en tant qu'admin bonita
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
   $bonita_group_id = gofast_workflows_curl_get_group($cookie_name, $path_modified, $group_name);

   return $bonita_group_id;
    
}

function gofast_workflows_get_bonitagroup_from_userlist($userlist){
   $ulid = $userlist->ulid;
    
   gofast_workflows_get_cookie(true);
   $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
   $bonita_group_id = gofast_workflows_curl_get_userlist($cookie_name, $ulid);

   return $bonita_group_id;
    
}


/* fonction qui resynchronize tous les membres du groupe Drupal recu en parametre avec les membres du groupe Bonita */
function gofast_workflows_synchronize_members_group($group_node, $just_add = false){
     //on recupere le groupe Bonita qui correspond au groupe drupal recu en parametre
    $bonita_group = gofast_workflows_get_bonitagroup_from_gofastgroup($group_node);
    
    //on recupere tous les membres du groupe Drupal recu en parametre
     $members = gofast_og_get_members_userlist_included($group_node);
     
  
     //d'abord on retire tous les membres sur Bonita
     $bonita_members = gofast_workflows_curl_get_members_group_bonita($bonita_group["id"]);
     $formatted_bonita_members = array();
     if(count($bonita_members) > 0){
             foreach( $bonita_members as $member_bonita ){
                    $formatted_bonita_members[$member_bonita["id"]] = $member_bonita;
              }
     }

     if($just_add == false){   
        if(count($bonita_members) > 0){
            foreach($bonita_members as $member_bonita){
                gofast_workflows_curl_delete_user_from_bonitagroup($member_bonita["id"], $bonita_group["id"]);
            }
        }   
     }
     
     
     foreach($members as $uid){
         //on recupere le bonita_id du membre
         $myuser = user_load($uid);
         
         $bonita_uid = gofast_workflows_get_user_id($myuser);          
          if($bonita_uid !== null){
               //check if we are in a complete resynchro or not
                if($just_add == false){   
                     gofast_workflows_curl_add_user_into_bonitagroup($bonita_uid, $bonita_group["id"]);  
                }else{
                       //we are not in a complete resynchro, so check if the user is already member into Bonita space or not
                       if(!isset($formatted_bonita_members[$bonita_uid])){                              
                                gofast_workflows_curl_add_user_into_bonitagroup($bonita_uid, $bonita_group["id"]); 
                       }
               }      
          }
     }
}

function gofast_workflows_synchronize_members_userlist($userlist){
    $bonita_group = gofast_workflows_get_bonitagroup_from_userlist($userlist);
    $members = $userlist->field_userlist_members[LANGUAGE_NONE];
       
     $bonita_members = gofast_workflows_curl_get_members_group_bonita($bonita_group["id"]);
     $formatted_bonita_members = array();
     if(count($bonita_members) > 0){
             foreach( $bonita_members as $member_bonita ){
                    $formatted_bonita_members[$member_bonita["id"]] = $member_bonita;
              }
     } 
     
     if(count($bonita_members) > 0){
         foreach($bonita_members as $member_bonita){
             gofast_workflows_curl_delete_user_from_bonitagroup($member_bonita["id"], $bonita_group["id"]);
         }
     }
     
     
     foreach($members as $uid){
         //on recupere le bonita_id du membre
         $myuser = user_load($uid['value']);
         
         $bonita_uid = gofast_workflows_get_user_id($myuser);          
          if($bonita_uid !== null){
               //check if we are in a complete resynchro or not
                if($just_add == false){   
                     gofast_workflows_curl_add_user_into_bonitagroup($bonita_uid, $bonita_group["id"]);  
                }else{
                       //we are not in a complete resynchro, so check if the user is already member into Bonita space or not
                       if(!isset($formatted_bonita_members[$bonita_uid])){                              
                                gofast_workflows_curl_add_user_into_bonitagroup($bonita_uid, $bonita_group["id"]); 
                       }
               }      
          }
     }
}


//TODO fonction de synchro all groupes / users
/* fonction qui parcours tous les groupes GF et les synchronise sur Bonita */
function gofast_workflows_synchro_all_groups($delete_all = false){
    set_time_limit(0);
    
    if($delete_all == true){
            //first we remove all spaces
            $bonita_groups = gofast_workflows_list_all_groups();

            if(count($bonita_groups) > 0){
                foreach($bonita_groups as $bonita_group){
                    if($bonita_group->id != 1 && $bonita_group->name !== "Utilisateurs" && substr($bonita_group->name, 0, 3) != "ul_"){
                        gofast_workflows_delete_group($bonita_group->id);
                    }
                }
            }
    }
    
   $first_level_groups=  gofast_og_get_root_spaces(FALSE, TRUE);
    //pour chaque groupe parent, je vais créer les groupes Bonita correspond hierarchiquement
    foreach($first_level_groups as $groupid){
        $groupe_node = node_load($groupid);
        $return = gofast_workflows_create_group($groupe_node);
        //on synchronize les membres
        gofast_workflows_synchronize_members_group($groupe_node);
        $children = gofast_og_get_children($groupe_node->nid, true, false, true);
        if(count($children) > 0){
            foreach($children as $gid=>$subgroup){
                $subgroup_node = node_load($gid);
                $return = gofast_workflows_create_group($subgroup_node);
                gofast_workflows_synchronize_members_group($subgroup_node);
            }
        }

    }
}

/*
 * Synchronize all userlists
 */
function gofast_workflows_synchro_all_userlists($delete_all = false){
    set_time_limit(0);
    
    if($delete_all == true){
            //first we remove all spaces
            $bonita_groups = gofast_workflows_list_all_groups();

            if(count($bonita_groups) > 0){
                foreach($bonita_groups as $bonita_group){
                    if($bonita_group->id != 1 && $bonita_group->name !== "Utilisateurs" && substr($bonita_group->name, 0, 3) == "ul_"){
                        gofast_workflows_delete_group($bonita_group->id);
                    }
                }
            }
    }
    
   $userlists = entity_load('userlist');
   
    foreach($userlists as $userlist){
        gofast_workflows_create_userlist($userlist);
        gofast_workflows_synchronize_members_userlist($userlist);
    }
}


/* fonction qui synchronise tous les users, et les ajoute dans le groupe global Utilisateurs */
function gofast_workflows_synchro_all_users(){
    //on recupere tous les utilisateurs
    $result = db_query("select uid from users");
    while ($user = $result->fetchObject()) {
        $all_users[] = $user->uid;
    }
    
    foreach($all_users as $uid){
        //on charge l'objet du user en question
        $myuser = user_load($uid);
        if($myuser->name){
            $return = gofast_workflows_create_user($myuser);
        }
    }
}

/* fonction qui synchronise les managers de tous les users */
/*function gofast_workflows_synchro_manager_all_users(){
    //on recupere tous les utilisateurs
    $result = db_query("select uid from users");
    while ($user = db_fetch_object($result)) {
        $all_users[] = $user->uid;
    }
    
    foreach($all_users as $uid){
        //on charge l'objet du user en question
        $myuser = user_load($uid);
        if($myuser->name){         
            $return = ceo_vision_bonita_replic_manager($myuser);
        }
    }
}*/



/* fonction qui synchronise tous les users, et les ajoute dans le groupe global Utilisateurs */
function gofast_workflows_synchro_membership_all_users(){
    //on recupere tous les utilisateurs
    $result = db_query("select uid from users");
    while ($user = $result->fetchObject()) {
        $all_users[] = $user->uid;
    }

    
    $cookie_name = gofast_workflows_get_cookie(true);   
    foreach($all_users as $uid){
        //on charge l'objet du user en question
        $myuser = user_load($uid);
        if($myuser->name){
               //une fois le user crée et le profil attribué, je met le user dans le groupe ou se trouve tous les utilisateurs
                $group_id = gofast_workflows_get_utilisateur_group_id();  
                //on recupere l'id du role standard 
                $role_id = gofast_workflows_get_standard_role_id();
                $bonita_id = gofast_workflows_get_user_id($myuser);
                $data = array('group_id' => "$group_id", 'role_id' => "$role_id", 'user_id' => "$bonita_id");
                $ch2 = curl_init(); 
               $baseURL = URL_BONITA; 
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

        }
    }
}



 
