<?php


function gofast_workflows_api_edit_deadline(){
    //on recupere le taskId en parametre
    $taskId = $_GET["taskId"];
    $task = gofast_workflows_get_task_object($taskId);
    $output = "";

    //Seul l'auteur de la tache (ou du process parent) peut changer la deadline
    global $user;
    //$current_bonita_uid = ceo_vision_bonita_get_user_id($user);
    $current_bonita_uid = gofast_workflows_get_user_id($user);
    if($task["started_by"] == 0){
       $task["case_object"] = gofast_workflows_api_get_case_object($task["rootCaseId"]);
    }

   //on verifie si le user courant est l'auteur du WF
   if($task["case_object"][0]["started_by"] != $current_bonita_uid){
      $output .= "<div style='padding:20px;'>";
      $output .= t("Only the owner of this process can edit the deadline");
      $output .= "</div >";
      print $output;
      exit;
   }
   //on construit le formulaire de changement de date
    $output .= "<div style='padding:20px;'>";
    $output .= "<h3>".t("Edit deadline")."</h3>";
    $output .= '<script>
        jQuery(function() {
          jQuery( "#new_deadline" ).datepicker({dateFormat: "dd-mm-yy"});
        });
        </script>';
    $output .= '<input id="new_deadline" name="bday">';
    $output .= "<input type='hidden' id='task_id' name='task_id' value='".$taskId."' />";
    $output .= "<div><input style='margin-top:5px;' type='button' id='edit_deadline_validate' value='".t("Validate")."' onClick='Drupal.gofast_workflows.ceo_vision_js_edit_deadline_validate(\"".$taskId."\");' ></div>";
    $output .= "</div>";
    print $output;
}

function gofast_workflows_api_edit_deadline_validate(){
     $data = $_POST;
     $output = "";

    //je recupere le taskId
    $taskId = $_POST["task_id"];
    $task_object = gofast_workflows_api_get_case_object($taskId);

    $new_deadline = $_POST["new_deadline"];
    $new_deadline = str_replace("/", "-", $new_deadline);
    $new_deadline_formatted = date("D M d 00:00:00 T Y", strtotime($new_deadline));

     //Seul l'auteur de la tache (ou du process parent) peut changer la deadline
    global $user;
    $current_bonita_uid = gofast_workflows_get_user_id($user);
     //on verifie si le user courant est l'auteur du WF
   if($task_object["started_by"] != $current_bonita_uid){
      $output .= "<div style='padding:20px;'>";
      $output .= t("Only the owner of this process can edit the deadline");
      $output .= "</div >";
      print $output;
      exit;
   }



    //je recupere dans la variable de deadline dans l'objet de la tache
    gofast_workflows_set_case_variables(BONITA_DEADLINE_PROCESS, $new_deadline_formatted, $task_object["rootCaseId"], "java.util.Date");
   // gofast_workflows
    $return = json_encode($data);
    print $return;
}


/* fonction qui renvoit une liste d'utilisateur (format chaine ["user1","user2"]) utilisable dans un formulaire Bonita par exemple*/
function gofast_workflows_api_liste_users(){
    module_load_include('inc', 'gofast_og', 'gofast_og.admin');

    //on recupere login et mot de passe
    $login = $_GET["login"];
    $relations = false;
    $type_map = false;
    if(isset($_GET["groupe"])){
        $groupe = $_GET["groupe"];
    }
    if(isset($_GET["relations"])){
        $relations = true;
    }

    if(isset($_GET["type_map"])){
        $type_map = true;
    }



    //on n'autorise que les requetes internes (entre le serveur et lui même)
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
        drupal_access_denied();
        exit;
    }

    $output = "";

    //je load le user recu en parametre
    $myuser = user_load_by_name(array('name' => trim($login)));
    usurp($myuser->uid);
     //si jamais on a recu un groupe en parametre, je ne liste que les users de ce groupe
     if(isset($groupe)){
         $groupe_object = node_load(array('title' => $groupe, 'type' =>'group_node'));
          $members =  get_members_id_group($groupe_object->nid);
          if(count($members) > 0){
             $authorizer_users = $members;
          }


     }elseif($relations === true){ //si jamais on a recu le parametre relation, on ne liste que les relations du user
         //TODO adapter aux nouvelles API de relation
         $authorizer_users = gofast_user_get_relationships($myuser->uid, 1);
     }else{
        //on recupere tous les autres users que ce user a le droit de visualiser

        $authorizer_users = gofast_og_get_visible_users();
         /*$all_users = entity_load('user');
         foreach($all_users as $uid=>$account){
             if(user_view_access($uid)){
                 $authorizer_users[$uid] = $uid;
             }
         }*/
     }
    $output .= "[";
    //$output .= "{";
    //on rajouter le user courant
     if($type_map === true){
        $mybonita_id = gofast_workflows_get_user_id($myuser);
        $output .= '"'.$myuser->ldap_user_givenname[LANGUAGE_NONE][0]['value'].' '.$myuser->ldap_user_sn[LANGUAGE_NONE][0]['value'].'":"'.$mybonita_id.'",';
     }else{
        $output .= '"'.$myuser->name.'",';
     }
    foreach($authorizer_users as $uid=>$displayname){
        if($uid != $myuser->uid){
            $thisuser = new stdClass();
            $thisuser->uid = $uid;
            $thisuser->name = $displayname;
            if($type_map === true){
                $bonita_id = gofast_workflows_get_user_id($thisuser);
                $output .= '"'.gofast_remove_accents($thisuser->name).'":"'.$bonita_id.'",';
            }else{
                 $output .= '"'.$thisuser->name.'",';
            }
        }
    }
//    //TODO temporaire pour pouvoir l'utiliser dpuis le studio
     // $output .= '"william jobs":"1",';



    $output .= "]";
     //$output .= "}";
     //$output = '{"sjeandroz","cpotter"}';

    usurp(FALSE);
    print $output;
}




function gofast_workflows_api_get_node_from_url(){

    //on n'autorise que les requetes internes (entre le serveur et lui même)
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
        //TODO comment during develop
        drupal_access_denied();
        exit;
    }

    if(isset($_GET["reference"])){
       $nid = gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$_GET["reference"]);
       $node = node_load($nid);
       $node_infos = array("node_title" => $node->title, 'node_path' => "node/". $node->nid, 'node_nid' => $node->nid, 'node_reference' => $node->reference);


    }elseif($_GET["url"]){
        $url = $_GET["url"];
        $node_infos = gofast_workflows_get_node_infos_from_url($url);

        if($node_infos == null){
            $node_infos = $node_infos = array("node_title" => "", 'node_path' => "", 'node_nid' => "", 'node_reference' => "workspace://SpacesStore/");
        }
    }else{
        $nid = $_GET["nid"];
        $node = node_load($nid);
        $node_infos = array("node_title" => $node->title, 'node_path' => "node/". $node->nid, 'node_nid' => $node->nid, 'node_reference' => str_replace("workspace://SpacesStore/", "", $node->reference));

    }
    $node_infos["node_title"] = str_replace("'", " ", $node_infos["node_title"]);



    drupal_json_output($node_infos);

}

function gofast_workflows_api_validate_access_path() {
    if (empty($_GET["path"]) || empty($_GET["uids"]) || empty($_GET["valuetype"])){
        print 0;
        exit;
    }
    $path = urldecode(gofast_xss_clean($_GET["path"]));
    $value_type = gofast_xss_clean($_GET["valuetype"]);
    $uids = explode("/", urldecode(gofast_xss_clean($_GET["uids"])));
    $gid = gofast_og_get_group_id_from_title_without_cmis($path, TRUE);
    if (!$gid) {
        print "Group matching path \"{$path}\" was not found";
        exit();
    }
    $group = node_load($gid);
    foreach ($uids as $uid) {
        $uid = trim($uid);
        if ($value_type == "uname") {
            $account = user_load_by_name($uid);
        } else {
            $account = user_load($uid);
        }
        if (!$account) {
            print "User matching id \"{$uid}\" was not found";
            exit();
        }
        $is_member = og_get_membership("node", $gid, "user", $account->uid);
        if (!$is_member) {
            $is_member = gofast_userlist_og_is_user_member_of_space($gid, $account);
        }
        if (!$is_member) {
            $is_member = gofast_userlist_og_is_user_admin_of_space($gid, $account->uid);
        }
        if (!$is_member) {
            $display_name = $account->ldap_user_displayname['und'][0]['value'];
            print "{$display_name} has no access to group {$group->title}";
            exit();
        }
    }
    print 0;
    exit;
}


function gofast_workflows_api_validate_access_document(){
    $return = array("node_access" => "false");

    if(isset($_GET["reference"]) && isset($_GET["uid"])){

        //on verifie le type de parametre reference que l'on a recu
        //car on peut aussi bien recevoir une reference de doc ou une url
        $type_file_param = $_GET["type_file_param"];
        if($type_file_param == "url"){
            $node_infos = gofast_workflows_get_node_infos_from_url($_GET["reference"]);
            if($node_infos == null){
                $nid = null;
            //$node_infos = $node_infos = array("node_title" => "", 'node_path' => "", 'node_nid' => "", 'node_reference' => "workspace://SpacesStore/");
            }else{
                $reference = $node_infos["node_reference"];
                $nid = gofast_ajax_file_browser_get_nid_from_reference($reference);
            }

        }else{
            //on recupere le nid de la reference recu
            //on split la chaine de reference recu car potentiellement on peut recevoir plusieurs documents
            $array_ref = explode(";", $_GET["reference"]);
            if($array_ref[0] == ""){
                unset($array_ref[0]);
            }

            $nid = array();
            if(count($array_ref) > 0){
                foreach($array_ref as $key_ref=>$ref){
                    if($ref != ""){
                        $nid[] = $ref;
                    }
                }
            }

        }
        //on split le parametre uid selon le caractere ; car on est succeptible d'en recevoir plusieurs
        //$array_uids = split(";", $_GET["uid"]);
        $array_uids = explode(";", $_GET["uid"]);
        if(count($array_uids) > 0){
            foreach($array_uids as $uid){
                if($uid != ""){
                    $account = user_load_by_name(trim($uid));
                    //if no account is found, make sure no success ("0") value is returned to Bonita
                    if (!$account) {
                        print ""; exit;
                    }
                    if(is_array($nid)){
                        foreach($nid as $mynid){
                            $node = node_load(trim($mynid));
                            if(node_access('view', $node, $account)){
                                $return = array("node_access" => "true");
                            }else{
                                $return = t("The @title document is not available for @username. If the user were to view the document, the document would be made exceptionally available to the user for the duration of the task. Please be sure to know what you're doing before submitting.", ["@title" => $node->title, "@username" => ($account->ldap_user_givenname[LANGUAGE_NONE][0]["value"] . " " . $account->ldap_user_sn[LANGUAGE_NONE][0]["value"])], ["context" => "gofast:gofast_workflows"]);
                                  print $return;
                                 exit;
                            }
                        }
                    }else{
                        if($nid){
                            $node = node_load(trim($nid));
                            if(node_access('view', $node, $account)){
                                $return = array("node_access" => "true");
                            }else{
                                $return = t("The @title document is not available for @username. If the user were to view the document, the document would be made exceptionally available to the user for the duration of the task. Please be sure to know what you're doing before submitting.", ["@title" => $node->title, "@username" => ($account->ldap_user_givenname[LANGUAGE_NONE][0]["value"] . " " . $account->ldap_user_sn[LANGUAGE_NONE][0]["value"])], ["context" => "gofast:gofast_workflows"]);
                                 print $return;
                                 exit;
                            }
                        }
                    }
                }
            }
        }
    }

     print 0; exit;
}



/** @todo remove this function after sufficient testing */
function gofast_workflows_api_sendmail(){

    //on n'autorise que les requetes internes (entre le serveur et lui même)
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
        drupal_access_denied();
        exit;
    }
    gofast_workflows_get_cookie(true);
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $bonita_user_id = true;

    $data = utf8_encode(file_get_contents('php://input'));
    //TODO temporaire
    //$data = '{"caseId":"4046", "login":"elavault", "message":"Coucou le Workflow est fini!!!"}';
    ## GOFAST-5599 : Update display of message (\n doesn't work)
    $data = str_replace('\n','</br>',$data);
    $data = str_replace("\x09", "", $data);

    $array_data = json_decode($data, true);

    //ensuite on determine a qui on va envoyer ce mail (tous les acteurs du WF)
   $liste_destinataires = array();
    //tout d'abord on envoi ce mail au user dont le login est recu en parametre (l'acteur de la tache qui a declenché cet envoi)
   $login = $array_data["login"];

   if(is_numeric($login)){
       $drupal_uid = gofast_workflows_get_drupalid_from_bonitaid($login);
       $last_actor = user_load($drupal_uid);
   }else if(strpos($login, "USERLIST_") === 0){ //Check if the recepient is a userlist
       $ulid = explode("_", trim($login))[1];
       $group_members = gofast_userlist_get_members($ulid);
       
       foreach ($group_members as $uid => $member) {
          $user_members = user_load($uid);
          // Get only users active to send mail
          if ($user_members->status == 1){
            $last_actor = user_load($uid);
            $liste_destinataires[$uid] = $last_actor;
          }
       }
   }else{
       //on verifie si $login est juste un username ou une liste de username separé par ;
       $array_login = explode(";", $login);
       if(count($array_login)>1){
           foreach($array_login as $mylogin){
                $last_actor = user_load_by_name(trim($mylogin));
                $liste_destinataires[$last_actor->uid] = $last_actor;
           }
       }else{
            //$last_actor = user_load(array('name' => trim($login)));
          $last_actor = user_load_by_name(trim($login));
       }
   }
   $_POST['langcode'] = $last_actor->language;

   $liste_destinataires[$last_actor->uid] = $last_actor;

   //si il faut notifier l'initiateur du WF je le recupere
   $notify_author = $array_data["notify_author"];

//$caseObject = array_shift(array_values($caseObject));
    $caseObject = gofast_workflows_api_get_case_object($array_data["caseId"], true);
    $started_by = $caseObject["started_by"];

    //si pas de champs started_by, on est surement dans le cas d'un processus démarré par un autre processus parent
    //Je loead donc le processus parent pour recuperer son initiateur

    if($started_by == "0" && $caseObject["id"] !== $caseObject["rootCaseId"]){
        $rootcaseObject = gofast_workflows_api_get_case_object($caseObject["rootCaseId"], true);
        $started_by = $rootcaseObject["started_by"];
    }
    $started_by_object = gofast_workflows_get_drupalid_from_bonitaid($started_by, true);

   if($notify_author != "false"){
        //on recupere l'initiateur de la tache, et s'il est different du user récupere juste avant, on lui envoi également le mail
        //d'abord on recupere l'object du case qui viens de se terminé
        //$caseObject = ceo_vision_get_list_actives_cases(false, $array_data["caseId"], false, true);

        if($started_by_object->uid !== $last_actor->uid){
            //$liste_destinataires[] = $started_by_object;
             watchdog("GoFast Workflow sendmail author", $started_by_object->uid);
            if($array_data["subject_author"] !== ""){
                $subject_author = $array_data["subject_author"];
            }else{
                $subject_author = $array_data["subject"];
            }
            if($array_data["message_author"] !== ""){
                $message_author = $array_data["message_author"];
            }else{
                $message_author = $array_data["message"];
            }
            $message_author = gofast_workflows_replace_email_masks(rawurldecode($message_author), $rootcaseObject);
            // $generic_message = gofast_workflows_api_sendmail_gettext_linkdashboard($caseObject["rootCaseId"]);

            $subject_author = t("Process", array(), array('context' => 'gofast:gofast_workflows'))." : ".$subject_author;
            $recpt = array(array('recpt' => $started_by_object->uid,
                            'method' => 'to'));

            $mail = array(
              'body' => str_replace("+", " ", rawurldecode($message_author)),
              'title' => "GOFAST",
              'subject' => str_replace("+", " ", rawurldecode($subject_author)),
              'footer' => t('Workflow powered by GoFAST', array(), array('context' => 'gofast:gofast_workflows')),
            );
            gofast_mail_queue_api_queue_ext($mail,  $recpt, time());

        }
   }

   $subject = $array_data["subject"];
   $message = $array_data["message"];

   //on remplace certains "masques" du contenu (par exemple le nom de domaine).
   $subject = gofast_workflows_replace_email_masks($subject, $rootcaseObject);
   $message = gofast_workflows_replace_email_masks($message, $rootcaseObject);

   $generic_message = gofast_workflows_api_sendmail_gettext_linkdashboard($caseObject["rootCaseId"]);
   foreach($liste_destinataires as $destinataire){
      watchdog("GoFast Workflow sendmail", $destinataire->uid);
      $recpt = array(array('recpt' => $destinataire->uid,
                            'method' => 'to'));
    $mail = array(
        'body' => $message,
        'title' => t("Workflow", array(), array('context' => "gofast:gofast_workflows")),
        'subject' => $subject,
        'footer' => ""
    );
    gofast_mail_queue_api_queue_ext($mail,  $recpt, time());

   }

}

function gofast_workflows_api_sendmail_taskdone(){

    //on n'autorise que les requetes internes (entre le serveur et lui même)
    if(gofast_workflows_is_external_api()){
        drupal_access_denied();
        exit;
    }
    gofast_workflows_get_cookie(true);

    $caseObject = gofast_workflows_api_get_case_object($_GET["caseId"], true);
   
    $title_process = $_GET["title"];
    $step = $_GET["step"];
    if($step !== "end_process"){
         print('OK');
        fastcgi_finish_request();
        usurp(1);
        sleep(20);
    }else{    
        usurp(1);    
    }

   //get all wf actors
   $case_variables = gofast_workflows_get_case_variables_from_id($caseObject["rootCaseId"]);
   if(isset($_GET["destinataire"])){
    $liste_destinataires[] = $_GET["destinataire"];
   }else{
    $liste_destinataires = explode(",",str_replace(array("[", "]"), array("", ""),$case_variables["list_all"]["value"]));
   }
   //loop over all recipients to get userlist members if there are any
   $final_liste_destinataires = [];
   foreach($liste_destinataires as $destinataire) {
    if (str_starts_with($destinataire, "ul_")) {
        $userlist_members = gofast_userlist_get_members_without_entity_load(str_replace("ul_", "", $destinataire), FALSE);
        foreach($userlist_members as $member){
            $username = $member->username;
            $final_liste_destinataires[$username] = $username;
        }
    } else {
        //we also use the value as a key to easily avoid duplicate values
        $destinataire = trim($destinataire);
        $final_liste_destinataires[$destinataire] = $destinataire;
    }
   }
   foreach($final_liste_destinataires as $destinataire){
    gofast_workflow_api_sendmail_taskdone_send($destinataire, $step, $title_process, $caseObject);
   }

    if($step == "end_process"){
          print('OK');
          exit;
    }
}

/**
 * Send a workflow notification for given:
 * @param string destinataire the target username
 * @param string step the step name (task_done, task_assigned, remind_task_assigned, end_process)
 * @param string title_process the name of the process instance
 * @param array caseObject the process instance data as retrieved by gofast_workflows_api_get_case_object
 */
function gofast_workflow_api_sendmail_taskdone_send($destinataire, $step, $title_process, $caseObject) {
    $destinataire_object = user_load_by_name(trim($destinataire));
    $_POST['langcode'] = $destinataire_object->language;
    $recpt = array(array('recpt' => $destinataire_object->uid, 'method' => 'to'));
    $processHistory = gofast_workflows_get_processhistory_from_pid($caseObject["rootCaseId"]);
    // In case mail has been sent from a context where processCurrent is unavailable
    if (strlen($title_process) == 0) {
        $title_process = $processHistory[0]->TITLE;
    }
    
    switch($step){
        case "task_done":
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{A user finished a task}} " .$title_process;
            break;
        case "task_assigned":
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{You have been assigned on a task}} " .$title_process;
            break;
        case "remind_task_assigned":
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{Process deadline tomorrow}} ";
            break;
        case "document_already_certified":
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{A document can not be signed}}";
            break;
        case "end_process":
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{process finished}} " .$title_process;
            break;
        default:
            $subject = "[{{Workflow}} " . variable_get('site_name') . "] {{Document broadcast}} : {{A user finished a task}} " .$title_process;
            break;
    }

    $assignee = user_load_by_name($destinataire_object->name);
    //now this function must be contextual to the step ( see "subject" previous ).
    $message = gofast_workflow_api_sendmail_taskdone_build_body($caseObject, $assignee, $step, $processHistory);

    //on remplace certains "masques" du contenu (par exemple le nom de domaine).
    $subject = gofast_workflows_replace_email_masks($subject, $caseObject);
  
    $mail = array(
        'body' => $message,
        'title' => t("Workflow", array(), array('langcode' => $assignee->language, 'context' => "gofast:gofast_workflows")),
        'subject' => $subject,
        'footer' =>  t('Workflow powered by GoFAST', array(), array('langcode' => $assignee->language, 'context' => 'gofast:gofast_workflows')),
    );
    
    gofast_mail_queue_api_queue_ext($mail,  $recpt, time());
}

function gofast_workflow_api_get_intermediate_step() {
    return ["document_already_certified"];
}

function gofast_workflow_api_sendmail_taskdone_build_body($caseObject, $assignee, $step, $processHistory){
    $bonita_assignee_id =  gofast_workflows_get_user_id($assignee);
    $my_author =  gofast_workflows_get_drupalid_from_bonitaid($caseObject["started_by"], true);

    //we get all pending "human tasks" for this case, using permissions of the recipient to filter tasks accordingly
    usurp($assignee->uid);
    $tasks_from_pid = gofast_workflows_get_list_actives_tasks(false, $caseObject["rootCaseId"], false, false, true);
    usurp(FALSE);
    
    $list_tasks = array();
    $list_tasks_assigned_user = array();
    // An intermediate step is a step triggered while no new task has been done yet: in this case there is no new task to execute so we just skip this section
    if(!in_array($step, gofast_workflow_api_get_intermediate_step()) && count($tasks_from_pid) > 0){
        foreach($tasks_from_pid as $task){
            $group_assignee = [];
            $group_assignee = gofast_workflows_get_task_variable_from_db($task["id"], "assignee");
            if (!empty($group_assignee) && str_starts_with($group_assignee[0], "ul_")) {
                $userlist = entity_load_single("userlist", str_replace("ul_", "", $group_assignee[0]));
                $task["assignedDisplayName"] = $userlist->name;
                $task["assignedDisplayType"] ??= "fas fa-users";
                $members = array_map(fn($el) => $el["value"], $userlist->field_userlist_members[LANGUAGE_NONE]);
                if(in_array($assignee->uid, $members)) {
                    array_push($list_tasks_assigned_user, $task);
                    continue;
                }
            }
            if($task["assigned_id"] == $bonita_assignee_id){
                $task["assignedDisplayName"] ??= gofast_user_display_name($assignee);
                $task["assignedDisplayType"] ??= "fas fa-single-user";
                array_push($list_tasks_assigned_user, $task);
                continue;
            }
            if($task["name"] == "Etape faite" || $task["name"] == "Acceptation Refus" || $task["name"] == "Signature Yousign"){
                $assigned = $task["assigned_id"] ? gofast_workflows_get_drupalid_from_bonitaid($task["assigned_id"], true) : null;
                $task["assignedDisplayName"] ??= gofast_user_display_name($assigned); // set assignedDisplayName only if not already set
                $task["assignedDisplayType"] ??= "fas fa-user-single"; // set assignedDisplayType only if no already set
                array_push($list_tasks, array("name" => $task["name"], "displayName" => $task["displayName"], "assignedDisplayName" => $task["assignedDisplayName"], "assignedDisplayType" => $task["assignedDisplayType"], "dueDate" => $task["assigned_date"]));
            }
        }
    }

    $author_comment = "";
    $process_current = gofast_workflows_get_processcurrent_from_pid($caseObject["rootCaseId"]);
    // $process_current_infos = gofast_workflows_get_processcurrent_infos_from_pid($caseObject["rootCaseId"]);
    if(count($process_current) > 0){
        foreach($process_current as $process_current_item){
            if($process_current_item->TYPE == "string" && $process_current_item->NAME == "Comment"){
                    $author_comment = $process_current_item->CONTENT_VALUE;
            }
        }
    }

    foreach ($processHistory as $index => $historyItem) {
        $query = "select * from CONTENTHISTORY WHERE persistenceId=(SELECT MAX(CONTENTHISTORY_PID) FROM LINEHISTORY_CONTENTS WHERE  LINEHISTORY_PID = ".$historyItem->LINEHISTORY_PID.");";
        $results =  ceo_vision_workflow_execute_bonita_query_bdm($query);
        $processHistory[$index]->TASK_COMMENT = "";
        foreach($results as $result) {
            if($result->TYPE == "string" && $result->NAME == "Comment"){
                $processHistory[$index]->TASK_COMMENT = $result->CONTENT_VALUE;
            }
        }
    }
    
    //Fetch into history (connector)
    $history = array_reverse(array_map(function ($item) {
        $taskItem = json_decode($item->TASK_OBJECT);
        $taskItem->comment = $item->TASK_COMMENT;
        return $taskItem;
    }, $processHistory));

    //Fetch into all retrieved documents (connector)
    $documents_info = array();
    foreach($process_current as $process_current_item){
        if($process_current_item->TYPE == "node"){
            $documents_info[] = trim($process_current_item->CONTENT_VALUE);
        }
    }

    $author = user_load($my_author);

    $author_pic = '<a href="/user/' . $author->uid . '" title="View user profile."><img style="border-radius: 5px; width:14px;" typeof="foaf:Image" src="' . gofast_get_url_picture_by_id($author->picture->fid) . '" alt="' . t("@user's picture", array('@user' => format_username($author)), array('context' => 'gofast:gofast_user')) . '" title="' . t("@user's picture", array('@user' => format_username($author)), array('context' => 'gofast:gofast_user')) . '" /></a>';

    $body = theme("gofast_workflows_email_taskdone_body", array(
        "process_name" => $caseObject["processDefinitionId"]["displayName"],
        "assignee_language" => $assignee->language,
        "assignee_firstname" => $assignee->ldap_user_givenname[LANGUAGE_NONE][0]['value'],
        "assignee_fullname" => gofast_user_display_name($assignee),
        "author_fullname" => gofast_user_display_name($my_author),
        "author_pic" => $author_pic,
        "author_comment" => $author_comment,
        "list_tasks_assigned_user" => $list_tasks_assigned_user,
        "documents_info" => $documents_info,
        "list_tasks" => $list_tasks,
        "history" => $history,
        "step" => $step,
    ));

    return $body;
}


function gofast_workflows_replace_email_masks($message, $rootcaseObject){
    //liste des masks que l'on recherche et que l'on remplace
    $masks = array("%domain_name%");


    global $base_url;
    $replace = array("https://".parse_url($base_url, PHP_URL_HOST));

    $message = str_replace($masks, $replace, $message);

    //Translation masks
    $message = preg_replace_callback("/{{(.*?)}}/", function($match){
        $match[1] = str_replace("<strong style='color:#2ecc71'>", "!strong_tag_start_accepted", $match[1]);
        $match[1] = str_replace("<strong style='color:#c0392b'>", "!strong_tag_start_refused", $match[1]);
        $match[1] = str_replace("</strong>", "!strong_tag_end", $match[1]);
        if(strpos($match[1], "|||") !== FALSE){
            //We have translation a exclusion pattern : "translated|||not_translated|||translated"
            $texclusion_pattern = explode("|||", $match[1]);
            return t($texclusion_pattern[0], array("!strong_tag_start_accepted" => "<strong style='color:#2ecc71'>", "!strong_tag_start_refused" => "<strong style='color:#c0392b'>", "!strong_tag_end" => "</strong>"), array('context' => 'gofast:gofast_workflows', 'langcode' => $_POST['langcode'])).
                    $texclusion_pattern[1].
                    t($texclusion_pattern[2], array("!strong_tag_start_accepted" => "<strong style='color:#2ecc71'>", "!strong_tag_start_refused" => "<strong style='color:#c0392b'>", "!strong_tag_end" => "</strong>"), array('context' => 'gofast:gofast_workflows', 'langcode' => $_POST['langcode']));
        }else{
            return t($match[1], array("!strong_tag_start_accepted" => "<strong style='color:#2ecc71'>", "!strong_tag_start_refused" => "<strong style='color:#c0392b'>", "!strong_tag_end" => "</strong>"), array('context' => 'gofast:gofast_workflows', 'langcode' => $_POST['langcode']));
        }
    }, $message);

    //Transformation masks
    $message = preg_replace_callback("/%user_icon:(.*?)%/", function($match){
        $account = is_numeric("$1") ? user_load("$1") : user_load_by_name($match[1]);
        $user_picture = theme('user_picture', array('account' => $account, 'dimensions' => array('width' => '15px', 'height' => '15px')));
        return "<img" . preg_replace('/(.*)<img(.*)\/>(.*)/sm', '\2', str_replace('<span>', '<span style="display:none;">', $user_picture)) . "/>";
    }, $message);

    $message = preg_replace_callback("/%node_icon:(.*?)%/", function($match){
        $node_icon = theme('node_title', array('node' => node_load($match[1]), 'link' => FALSE));
        return gofast_mail_queue_fa_png(str_replace('<span>', '<span style="display:none;">', $node_icon));
    }, $message);
    
    $message = preg_replace_callback("/%node_title:(.*?)%/", function($match){
        $node_title = gofast_get_node_title($match[1]);
        return $node_title;
    }, $message);

    $message = preg_replace_callback("/%timestamp_to_date:(.*?)%/", function($match){
        if($_POST['langcode'] == 'en'){
            return format_date($match[1], 'custom', "D, m/d/y - H:i", NULL, $_POST['langcode']);
        }else{
            return format_date($match[1], 'custom', "D, d/m/y - H:i", NULL, $_POST['langcode']);
        }
    }, $message);

    $message = preg_replace_callback("/%mstimestamp_to_date:(.*?)%/", function($match){
        if($_POST['langcode'] == 'en'){
            return format_date(intval((int)$match[1]/1000), 'custom', "D, m/d/y - H:i", NULL, $_POST['langcode']);
        }else{
            return format_date(intval((int)$match[1]/1000), 'custom', "D, d/m/y - H:i", NULL, $_POST['langcode']);
        }
    }, $message);
    
    $message = preg_replace_callback("/%site_name%/", function($match){
        return variable_get('site_name');
    }, $message);

    return $message;
}

function gofast_workflows_replace_email_mask_comment($email_body , $rootcaseObject){
   $mask_before_comment = "%start_comment%";
   $mask_after_comment = "%end_comment%";

   //on recupere l'auteur du processus
   global $base_url;
   $started_by = $rootcaseObject["started_by"];
   $started_by_object = gofast_workflows_get_drupalid_from_bonitaid($started_by, true);

   //$picture = l("<img width='40px' height ='40px' src=\"".$base_url."/".$picture_src."\" id='".time().rand(0,2000)."'>",$base_url.'/user/'.$started_by_object->uid,array('html'=>true, 'attributes' => array()));
   usurp(1);
   $picture = theme('user_picture', array('account' => $started_by_object));
   $html_before_comment = '<table width="100%" cellspacing="0" cellpadding="0" border="0" style="border-bottom:solid 20px #fff;">
    <tr>
        <td>
            <table width="100%" cellspacing="0" cellpadding="10" border="0" style="border-collapse:separate !important; border:1px solid #d9d9d9; border-radius:4px; background-color:#fafafa; ">
                <tr>
                    <td style="padding:10px;">
                        <table width="100%" cellspacing="0" cellpadding="0" border="0">
                            <tr>
                                <td width="40" height="40" valign="top" style="width:40px; max-width:40px; height:40px; max-height:40px;">
                                    <table width="40" height="40" cellspacing="0" cellpadding="0" border="0" style="background:#fff; border:0;">
                                        <tr>
                                            <td width="40" height="40" valign="middle" style="width:40px; height:40px; border-collapse:collapse; line-height:100%; padding:0;">
                                                <div class="picture">
                                                    '.$picture.'
                                                </div>
                                            </td>
                                        </tr>
                                    </table>
                                </td>
                                <td width="10" valign="top" style="font-size:1px"></td>
                                <td valign="middle">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="font-size:12px;">
                                        <tr>
                                            <td valign="top" style="color: #666666; font-family: Arial; font-size: 13px; font-weight: normal; line-height: 150%;">
                                                <span style="color:#202020; font-weight:bold;">'.$started_by_object->profile_firstname.' '.$started_by_object->profile_lastname.'</span>                                            </td>
                                        </tr>
                                                                                    <tr>
                                                <td valign="bottom" style="color: #666666; font-family: Arial; font-size: 12px; font-weight: normal; line-height: 150%; padding-top:1px;">
                                                </td>
                                            </tr>
                                                                            </table>
                                </td>
                            </tr>
                        </table>
                        <table width="90%" cellspacing="0" cellpadding="0" border="0" align="center">
                            <!-- comment section -->
                            <tr>
                                <td valign="top">
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="left" style="border-collapse:separate !important;">
                                        <tr>
                                            <td height="10">
                                                <!-- margin -->
                                            </td>
                                        </tr>
                                        <tr>
                                            <td style="background-color: #F9F9F9; border:1px solid #dddddd; border-radius:5px;">
                                                <table width="100%" cellspacing="0" cellpadding="10" border="0" align="center">
                                                    <tr>
                                                        <td width="5" valign="top" style="padding:10px; font-size:1px"></td>
                                                        <td style="padding:10px; color: #666666; font-family: Arial; font-size: 14px; font-weight: normal; line-height: 150%;">
                                                            <blockquote style="font-size:12px; color:#636363; overflow:auto; margin:0px 15px; line-height:150%;">';

   $email_body = str_replace($mask_before_comment, $html_before_comment, $email_body);


   $html_after_comment =                                   '</blockquote>
                                                            </td>
                                                        <td width="5" valign="top" style="padding:10px; font-size:1px"></td>
                                                    </tr>
                                                </table>
                                            </td>
                                        </tr>
                                    </table>
                                    <table width="100%" cellspacing="0" cellpadding="0" border="0" align="center" style="font-size:12px;">
                                        <tr>
                                            <td height="10" style="height:10px; max-height:10px; font-size:10px; line-height:100%">
                                                &nbsp; <!-- margin -->
                                            </td>
                                        </tr>
                                        <tr>
                                            <td width="75">

                                            </td>
                                            <td style="border:none; text-decoration:none; font-family:\'Helvetica Neue\',Helvetica,Arial,sans-serif; color:#999999; text-align:right;">
                                                '.format_date(time()).'                                            </td>
                                        </tr>
                                    </table>
                                </td> <!-- comment section end -->
                            </tr>
                        </table>
                    </td>
                </tr>
            </table>
        </td>
    </tr>
</table>';

 $email_body = str_replace($mask_after_comment, $html_after_comment, $email_body);
    // $email_body = $email_body.$comment_themed;
 return $email_body;
}


function gofast_workflows_api_sendmail_gettext_linkdashboard($task_id = ""){
    $message = "<br />Vous pouvez effectuer vos taches en cours depuis <a href='".$GLOBALS['base_url']."/workflow/dashboard?task=".$task_id."';>cette page</a>";
    return $message;
}

function gofast_workflows_api_liste_emplacements(){
     //on n'autorise que les requetes internes (entre le serveur et lui même)
     if(gofast_workflows_is_external_api()){
        drupal_access_denied();
        exit;
    }

    $output = "";

    //on recupere le parametre du chemin racine
    $root_path = $_GET["root_path"];

    //on recupere le username du user qui effectue l'appel
     $login = $_GET["login"];
     //je load le user recu en parametre
     $myuser = user_load(array('name' => trim($login)));

     //on recupere la variable qui contient tous les emplacements accessibles a l'utilisateur
     //$all_locations = variable_get("alf_emplacements_".$myuser->uid, array());
     $all_locations = gofast_ztree_get_paths(false,$myuser);

    $output .= "[";

    foreach($all_locations as $location){
        //todo filtrer par root_path
            $output .= '"'.$location.'",';
    }

    $output .= "]";

    print $output;
}



function gofast_workflows_api_move_document(){
    watchdog("debug move", "debug");
    //on n'autorise que les requetes internes (entre le serveur et lui même)
    if(gofast_workflows_is_external_api()){
        drupal_access_denied();
        exit;
    }


    $data = $_GET["data"];
    $data = str_replace("[", "{", $data);
    $data = str_replace("]", "}", $data);
    $array_data = json_decode($data, true);
   if(strpos($array_data["ref_document"], "workspace://SpacesStore/") === false){
    $reference = "workspace://SpacesStore/".$array_data["ref_document"];
   }else{
       $reference = $array_data["ref_document"];
   }

    $process_id = $array_data["caseId"];
    $destination_folder = $array_data["dossier_cible"];
    $destination_group = $array_data["espace_cible"];
    $full_path = $array_data["full_path"];
    $auteur_deplacement = $array_data["auteur_deplacement"];

    $document_nid = gofast_ajax_file_browser_get_nid_from_reference($reference);
    $document_node = node_load($document_nid);

    if(!$document_node){

        drupal_json_output(array("return_code" => "Bad document node"));
        exit;
    }


    //on recupere le document alfresco associé a la reference recu en parametre
    global $cmis_sudo_admin;
    $cmis_sudo_admin = true;
    $repositoryId = gofast_cmis_get_repository();
    $cmis_object = cmisapi_getObject($repositoryId, $reference);
    if(!isset($cmis_object->properties['cmis:objectId'])){
       drupal_json_output(array("return_code" => "Bad document reference"));
       exit;
    }

    //on fait quelques verifications sur le chemin
    if($full_path == "-"){
         drupal_json_output(array("return_code" => "Bad path"));
          exit;
    }

    //si on a recu un parametre full_path, on fait juste un move vers cet emplacement
    if($full_path !== null && ($full_path !== "" || $full_path !== " ")){
        $path_destination = rawurldecode($full_path);

        $current_parent_id = cmisapi_getFolderParent($repositoryId, $document_node->reference);
        $current_parent_id =  $current_parent_id->objectList[0]->properties['cmis:objectId'];
    }else{

            if($destination_group !== ""){
                //on charge le noeud du groupe dont le nom a été recu en parametre
                $root_group = node_load_by_title(array('title' => $destination_group, 'type' => "orga"));
                if(!$root_group){
                    $root_group = node_load(array('title' => $destination_group, 'type' => "group_node"));
                }

                if(!$root_group){
                    drupal_json_output(array("return_code" => "Bad root group"));
                    exit;
                }
            }else{
                //on charge le groupe du document recu en parametre (le premier groupe si présent dans plusieurs)
                 $root_group_nid = reset($document_node->og_groups);
                 $root_group = node_load($root_group_nid);

                if(!$root_group){
                    drupal_json_output(array("return_code" => "Bad root group"));
                    exit;
                }

            }

              $current_parent_id = cmisapi_getFolderParent($repositoryId, $document_node->reference);
              $current_parent_id =  $current_parent_id->objectList[0]->properties['cmis:objectId'];

              //je construit le chemin de la nouvelle destination
              //pour cela je recupere le tableau qui contient tous les emplacements au sein du root_group
              $list_path = get_json_data_alfresco($root_group->nid);
             // var_dump($list_path);
              if(count($list_path) > 0){
                  foreach($list_path as $path){
                      //je decoupe l'emplacement selon les / et je garde la derniere occurence
                      $array_path_fragment = explode("/", $path);
                      $last_fragment = end($array_path_fragment);

                      //on compare ce nom de dossier avec le dossier de destination souhaité
                      if($last_fragment == $destination_folder){
                           $path_destination = $path;
                      }
                  }
              }
    }



      $destination_object = cmisapi_getObjectByPath($repositoryId,  rawurlencode($path_destination));
      $reference_destination_folder = $destination_object->properties["cmis:objectId"];
     watchdog("debug move",rawurlencode($path_destination ));
      if($reference_destination_folder == ""){
           drupal_json_output(array("return_code" => "Bad destination folder".$path_destination));
           exit;
      }
      watchdog("debug root move",$reference_destination_folder);
      cmisapi_moveObject($repositoryId, $cmis_object->properties['cmis:objectId'], $reference_destination_folder, $current_parent_id);

      if($destination_group !== "" && $destination_group !== NULL){
        if(!$root_group->nid){
            $root_group->nid = get_group_id_from_title($full_path, true);
        }
        $og_groups = array($root_group->nid => $root_group->nid);
        $document_node->og_groups = $og_groups;
        $document_node->notifications_content_disable = 1;

        ceo_vision_save_node_technicly($document_node);
        //je surcharge l'auteur du noeud drupal
        if(isset($auteur_deplacement) && $auteur_deplacement != ""){
            $author =   gofast_workflows_get_drupalid_from_bonitaid($auteur_deplacement, true);
            ceo_vision_replace_revision_uid($author->name,$document_node);
        }
      }

      $return = json_encode(array("return_code" => "OK"));
      print $return;
      exit;

}

function gofast_workflows_api_update_history(){

  //on n'autorise que les requetes internes (entre le serveur et lui même)
  if(gofast_workflows_is_external_api()){
    drupal_access_denied();
    exit;
    }

    if(isset($_GET["pid"])){
        $pid = $_GET["pid"];
    }

    if(isset($_GET["history_variable_name"])){
        $history_variable_name = $_GET["history_variable_name"];
    }

    if(isset($_GET["close"])){
        $close = true;
    }else{
        $close = false;
    }


    if(!isset($pid) || !isset($history_variable_name)){
        watchdog("debug Workflow missig params", "debug Workflow missig params");
        return;
    }



    //on récupere les infos nécessaires sur le processus en cours et ses variables
    gofast_workflows_get_cookie(true);
   $case_object = gofast_workflows_api_get_case_object($pid, true);
   $variables = gofast_workflows_get_case_variables_from_id($pid);
   //on vérifie s'il existe déjà dans la table ceo_vision_workflow_history une ligne correspondante à ce process
    $count = db_query('SELECT COUNT(*) as count FROM {ceo_vision_wf_history} WHERE pid = '.$pid)->fetchObject();

    if ($count->count == 0) {
        //on insere la ligne correspondante dans cette table
        gofast_workflows_insert_process_row($case_object, $variables);
    }

    //la variable $close indique que cet update d'history correspond a la derniere étape d'un process, donc on doit mettre à jour la ligne correspondant au process, en changant l'état et en remplissant la colonne de timestmap de cloture
    if($close == true){
        gofast_workflows_close_process_row($case_object, $variables);
    }

    //ensuite on rmeplit (ou re-replit) la table ceo_vision_workflow_history_detail, avec le contenu de la variable history_variable_name
    gofast_workflows_insert_detail_rows($case_object, $variables[$history_variable_name], $variables);



}

function gofast_workflows_get_list_history_cases(){
     $result=db_query("SELECT * FROM {ceo_vision_wf_history} ORDER BY pid ASC");

     $return = array();
     while ($row = $result->fetchObject()) {
         $return[$row->pid] = $row;
     }

     return $return;
}

function gofast_workflows_get_list_history_cases_specific_wf($wf_name){
     $result=db_query("SELECT * FROM {ceo_vision_wf_history} WHERE gofast_type_processus = '".$wf_name."'  ORDER BY pid ASC");

     $return = array();
     while ($row = $result->fetchObject()) {
         $return[$row->pid] = $row;
     }

     return $return;
}

function gofast_workflows_get_specific_history_cases($pid){
     $result=db_query("SELECT * FROM {ceo_vision_wf_history} WHERE pid = $pid");
     $return = array();
     while ($row = $result->fetchObject()) {
         $return = $row;
     }

     return $return;
}

function gofast_workflows_get_list_history_details($pid){
    $result=db_query("SELECT * FROM {ceo_vision_wf_history_detail} WHERE pid = $pid");

     $return = array();
     while ($row = $result->fetchObject()) {
         $return[$row->row][$row->name] = $row->value;
     }

     return $return;
}

function gofast_workflows_get_list_history_all_details(){
    $result=db_query("SELECT * FROM {ceo_vision_wf_history_detail} ORDER BY pid DESC, row ASC");

     $return = array();
     while ($row = $result->fetchObject()) {
         $return[$row->pid][$row->row][$row->name] = $row->value;
     }

     return $return;
}

function gofast_workflows_insert_process_row($case_object, $variables){

    $pid = $case_object["id"];
    $uid = gofast_workflows_get_drupalid_from_bonitaid($case_object["started_by"]);
    $timestamp = strtotime($case_object["start"]);
    $gofast_document_reference = $variables["gofast_document_reference"]["value"];

    global $cmis_sudo_admin;
    $cmis_sudo_admin = true;
    $repositoryId = gofast_cmis_get_repository();
    $cmis_object = cmisapi_getObject($repositoryId, "workspace://SpacesStore/".$gofast_document_reference);
    $gofast_document_reference_version = $cmis_object->properties["cmis:versionLabel"];

    $gofast_type_processus = $case_object["processDefinitionId"]["displayName"];
    $gofast_titre_processus = $variables["gofast_titre_processus"]["value"];
    $gofast_date_limite =  $timestamp_deadline = strtotime($variables["gofast_date_limite"]["value"]);
    $etat_wf = 1;

      db_query("INSERT INTO {ceo_vision_wf_history} (pid,uid,timestamp,gofast_document_reference,gofast_document_reference_version,gofast_type_processus,gofast_titre_processus,etat_wf, gofast_date_limite) VALUES (:1,:2,:3,:4,:5,:6,:7,:8,:9)",
           array(":1" => $pid, ":2" =>$uid, ":3" => $timestamp, ":4" => $gofast_document_reference,":5" => $gofast_document_reference_version,":6" => $gofast_type_processus, ":7" => $gofast_titre_processus, ":8" => $etat_wf, ":9" => $gofast_date_limite));
}


function gofast_workflows_close_process_row($case_object, $variables){
     $pid = $case_object["id"];
     $etat_wf = 0;
     $timestamp_close = time();

      db_query("UPDATE {ceo_vision_wf_history} SET etat_wf = :1, timestamp_close = :2 WHERE pid = :3",
           array(":1" => $etat_wf, ":2" => $timestamp_close, ":3" => $pid));
}

function gofast_workflows_insert_detail_rows($case_object, $history_variable_name, $variables = array()){
  if(!isset($history_variable_name["value"])){
      watchdog("debug history_variable_name empty", $history_variable_name["name"]);
      return;
  }

  //on décode le json contenu dans la variable
  $replace  = array("{", "=", "}", ", ", "}\"", "\"{");
  $search = array("{\"", "\":\"", "\"}", "\", \"", "}", "{");
  $modified_value = str_replace($search, $replace, $history_variable_name["value"]);
  $array_history = json_decode($modified_value);

  if(count($array_history) > 0){
    //on vide de la table ceo_vision_workflow_history_detail les enregistrements qui concernent notre processus
     //db_query("DELETE FROM {ceo_vision_wf_history_detail} WHERE pid = %d ", $case_object["id"]);

     //puis on la re-remplit
     foreach($array_history as $key=>$row){
         //$row = end($array_history);
         //$key = key($array_history);
         $row = str_replace("{", "", $row);
         $row = str_replace("}", "", $row);
         $row_array = explode(",", $row);

         $count = db_query('SELECT COUNT(*) as count FROM {ceo_vision_wf_history_detail} WHERE pid = '.$case_object["id"].' AND row = '.$key.'')->fetchObject();
         if ($count->count == 0) {
            if(count($row_array ) > 0){
                foreach($row_array as $detail){
                    $detail_array = explode("=", $detail);
                    $detail_array[1] = gofast_workflows_replace_history_masks($detail_array[1], $variables);
                     db_query("INSERT INTO {ceo_vision_wf_history_detail} (pid,name,value,row) VALUES (:1,:2,:3,:4)",
                                   array(":1" => $case_object["id"],":2" => trim($detail_array[0]),":3" => $detail_array[1],":4" => $key));

                }
            }
         }

     }
   }

}

function gofast_api_workflows_insert_line_to_history($params) {
    extract($params);
    if (!isset($current_user) || !isset($case_id) || !isset($user_object) || !isset($line_date) || !isset($task_id) || !isset($task_object)) {
        gofast_api_mandatory_parameter();
    }

    $case_id = gofast_xss_clean($case_id);
    $current_uid = gofast_user_get_uid_by_login(gofast_xss_clean($current_user));
    $is_in_process = gofast_workflows_has_user_active_task_in_workflow($case_id, $current_uid);
    if (!$is_in_process) {
        gofast_api_not_authorized("You must have active tasks in the process instance to be able to add lines to its history");
    }
    // History insertion
    $user_object = gofast_xss_clean($user_object);
    $line_date = gofast_xss_clean($line_date);
    $task_id = gofast_xss_clean($task_id);
    $task_object = gofast_xss_clean($task_object);
    gofast_workflows_insert_line_to_history($case_id, $user_object, $line_date, $task_id, $task_object);
    // Send notification if needed
    $task_object = json_decode($task_object);
    $user_object = json_decode($user_object);
    if (isset($task_object->step)) {
        $destinataire = $user_object->username;
        $step = $task_object->step;
        $caseObject = gofast_workflows_api_get_case_object($case_id, TRUE);
        $title_process = "";
        gofast_workflow_api_sendmail_taskdone_send($destinataire, $step, $title_process, $caseObject);
    }
    gofast_api_success("OK");
}

/**
 * Given a Drupal account object, returns the user object expected by the Bonita BDM history
 */
function gofast_workflows_format_history_user_object($account) {
    $user_object = new stdClass();
    $user_object->username = $account->name;
    $user_object->displayname = gofast_user_display_name($account);
    return $user_object;
}

/**
 * Given a Drupal account object, a name, and a description, returns in an associative array the following items as expected by the Bonita BDM history:
 * $user_object
 * $line_date
 * $task_object
 */
function gofast_workflows_format_history_task_object($account, $name, $description) {
    $user_object = gofast_workflows_format_history_user_object($account);
    $line_date = time() * 1000;
    $task_object = new stdClass;
    $task_object->id = 0;
    $task_object->type = "userTask";
    $task_object->name = $name;
    $task_object->description = $description;
    $task_object->actor_displayname = $user_object->displayname;
    $task_object->actor_login = $account->name;
    $task_object->date = $line_date;
    return [$user_object, $line_date, $task_object];
}

/**
 * Add a document to a Bonita BDM history line, mainly intended to be called by gofast_workflows_insert_line_to_history.
 * @param int $line_persistence_id the history line id
 * @param stdClass $document the Drupal node
 * @param int $index must be incremented for each document added to the history line
 */
function gofast_workflows_add_document_to_history_line($line_persistence_id, $document, $index) {
    // Format document history line
    $document_object = new stdClass();
    $document_object->nid = $document->nid;
    $document_object->title = $document->title;
    $document_object_string = json_encode($document_object);

    // Insert history line content for document and get its id
    $content_history_name = "Document";
    $content_history_type = "node";
    db_insert("CONTENTHISTORY", array("target" => "bonita_bdm"))
        ->fields(array(
            'CONTENT_VALUE' => $document_object_string,
            'NAME' => $content_history_name,
            'persistenceVersion' => 1,
            'TYPE' => $content_history_type,
        ))->execute();
    $content_persistence_id = db_select("CONTENTHISTORY", "ch", array("target" => "bonita_bdm"))
        ->fields("ch", ["persistenceId"])
        ->condition("CONTENT_VALUE", $document_object_string)
        ->orderBy("persistenceId", "DESC")
        ->range(0, 1)
        ->execute()->fetchCol();
    if (empty($content_persistence_id)) {
        return FALSE;
    }
    $content_persistence_id = reset($content_persistence_id);

    // Link history content to history line
    db_insert("LINEHISTORY_CONTENTS", array("target" => "bonita_bdm"))
    ->fields(array(
        'LINEHISTORY_PID' => $line_persistence_id,
        'CONTENTHISTORY_PID' => $content_persistence_id,
        'contents_ORDER' => $index,
    ))->execute();
}

/**
 * Insert a line to the process instance history among bonita business data instances
 * Inserts directly into the database since Bonita Java API forbids it
 * @param string $case_id the process instance id
 * @param string $user_object a stringified json to display the "actor" field of the history line
 * @param string $line_data timestamp of the history line
 * @param string $task_id the user task id
 * @param string $task_object a stringified json formatted as the processHistory Bonita widget would expect it to be
 * 
 */
function gofast_workflows_insert_line_to_history($case_id, $user_object, $line_date, $task_id, $task_object, $documents = []) {
    gofast_workflows_activate_bonita_connection(TRUE);
    $transaction = db_transaction(NULL, array("target" => "bonita_bdm"));
    // Get ID of target processHistory business data instance
    $persistence_id = db_select("PROCESSHISTORY", "ph", array("target" => "bonita_bdm"))
        ->fields("ph", ["persistenceId"])
        ->condition("PID", $case_id)
        ->execute()->fetchCol();
    if (empty($persistence_id)) {
        return FALSE;
    }
    $persistence_id = reset($persistence_id);

    // Insert history line content for user and get its id
    $content_history_name = "User";
    $content_history_type = "user";
    if (str_contains($user_object, "ul_")) {
        $content_history_name = "Group";
        $content_history_type = "group";
    }
    db_insert("CONTENTHISTORY", array("target" => "bonita_bdm"))
        ->fields(array(
            'CONTENT_VALUE' => $user_object,
            'NAME' => $content_history_name,
            'persistenceVersion' => 0,
            'TYPE' => $content_history_type,
        ))->execute();
    $content_persistence_id = db_select("CONTENTHISTORY", "ch", array("target" => "bonita_bdm"))
        ->fields("ch", ["persistenceId"])
        ->condition("CONTENT_VALUE", $user_object)
        ->orderBy("persistenceId", "DESC")
        ->range(0, 1)
        ->execute()->fetchCol();
    if (empty($content_persistence_id)) {
        $transaction->rollback();
        return FALSE;
    }
    $content_persistence_id = reset($content_persistence_id);

    // Insert history line and get its id
    db_insert("LINEHISTORY", array("target" => "bonita_bdm"))
        ->fields(array(
            'LINE_DATE' => $line_date,
            'persistenceVersion' => 0,
            'TASK_ID' => $task_id,
            'TASK_OBJECT' => $task_object,
        ))->execute();
    $line_persistence_id = db_select("LINEHISTORY", "lh", array("target" => "bonita_bdm"))
        ->fields("lh", ["persistenceId"])
        ->condition("TASK_OBJECT", $task_object)
        ->orderBy("persistenceId", "DESC")
        ->range(0, 1)
        ->execute()->fetchCol();
    if (empty($line_persistence_id)) {
        $transaction->rollback();
        return FALSE;
    }
    $line_persistence_id = reset($line_persistence_id);

    // Link history line to history line content for user
    db_insert("LINEHISTORY_CONTENTS", array("target" => "bonita_bdm"))
        ->fields(array(
            'LINEHISTORY_PID' => $line_persistence_id,
            'CONTENTHISTORY_PID' => $content_persistence_id,
            'contents_ORDER' => 0,
        ))->execute();

    // Handle documents if given
    if (!empty($documents)) {
        foreach ($documents as $index => $document) {
            $index++;
            gofast_workflows_add_document_to_history_line($line_persistence_id, $document, $index);
        }
    }

    // Link processHistory to history line
    $previous_line = db_select("PROCESSHISTORY_LINES", "phl", array("target" => "bonita_bdm"))
            ->fields("phl", ["lines_ORDER"])
            ->condition("PROCESSHISTORY_PID", $persistence_id)
            ->orderBy("lines_ORDER", "DESC")
            ->range(0, 1)
            ->execute()->fetchCol();
    if (empty($previous_line)) {
        $transaction->rollback();
        return FALSE;
    }
    $previous_line = (int) reset($previous_line);
    $target_line = $previous_line + 1;
    db_insert("PROCESSHISTORY_LINES", array("target" => "bonita_bdm"))
        ->fields(array(
            'PROCESSHISTORY_PID' => $persistence_id,
            'LINEHISTORY_PID' => $line_persistence_id,
            'lines_ORDER' => $target_line,
        ))->execute();
}

function gofast_workflows_replace_history_masks($value, $variables){
    watchdog("debug value history", $value);
    if($value == "%current_version"){
        //liste des masks que l'on recherche et que l'on remplace
        $masks = array("%current_version");

        $gofast_document_reference = $variables["gofast_document_reference"]["value"];
        global $cmis_sudo_admin;
        $cmis_sudo_admin = true;
        $repositoryId = gofast_cmis_get_repository();
        $cmis_object = cmisapi_getObject($repositoryId, "workspace://SpacesStore/".$gofast_document_reference);
        $current_version = $cmis_object->properties["cmis:versionLabel"];

        $replace = array($current_version);
        $new_value = str_replace($masks, $replace, $value);
    }else{
        $new_value = $value;
    }
    return $new_value;
}

function gofast_api_get_workflow_profil($params){
  //Check content type
  if (strpos($params['Content-Type'], "application/json") === FALSE) {
    return gofast_api_not_implemented("This Content-Type");
  }

  //Check authentication
  global $user;
  if ($user->uid == 0) {
    gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }

  //Check if we have an id param
  if (isset($params['id'])) {
    $id = $params['id'];
    if(!is_numeric($id)){
      gofast_api_mandatory_parameter("id must be numeric");
    }

   //load profil
   $profil = gofast_workflows_profil_get($id);

   if(!isset($profil->id)){
        gofast_api_internal_server_error("Unable to load a wf profil with id : " . $id);
        return;
   }

  $result[] = array(
    'id' =>    $profil->id,
    'name' =>    $profil->name,
    'spaces' =>  $profil->spaces,
    'value' =>    $profil->value,
    'type_wf' => $profil->type_wf,
    'version_wf' => $profil->version_wf,
    'uid' => $profil->uid
    );

  } else {
       if (isset($params['type'])) {
        $type = $params['type'];

        //TODO manage version param
         //load profil
        $profils = gofast_workflows_profil_get_all_from_type_wf($type);

        if(count($profils) == 0){
             gofast_api_internal_server_error("Unable to load profils with type : " . $type);
             return;
        }

        foreach($profils as $profil){
            $result[] = array(
              'id' =>    $profil->id,
              'name' =>    $profil->name,
              'spaces' =>  $profil->spaces,
              'value' =>    $profil->value,
              'type_wf' => $profil->type_wf,
              'version_wf' => $profil->version_wf,
              'uid' => $profil->uid
              );
        }


      } else {
        gofast_api_mandatory_parameter("id");
      }
  }


  gofast_api_success($result);
}


function gofast_api_patch_workflow_profil($params){
  //Check content type
  if (strpos($params['Content-Type'], "application/json") === FALSE) {
    return gofast_api_not_implemented("This Content-Type");
  }

  //Check authentication
  global $user;
  if ($user->uid == 0) {
    //gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }

  if(!isset($params['id'])) {
       gofast_api_mandatory_parameter("Id is a mandatory parameter");
       return;
    }

   if(!isset($params['name'])) {
       gofast_api_mandatory_parameter("Name is a mandatory parameter");
       return;
   }

    if(!isset($params['value'])) {
       gofast_api_mandatory_parameter("Value is a mandatory parameter");
       return;
   }

    if(!isset($params['type_wf'])) {
       gofast_api_mandatory_parameter("Type_wf is a mandatory parameter");
       return;
    }

    if(!isset($params['version_wf'])) {
       gofast_api_mandatory_parameter("Version_wf is a mandatory parameter");
       return;
    }

  $id =  $params['id'];
  $name =  $params['name'];
  $value = $params['value'];
  $gids = array_map(fn($el) => $el["value"], $params['spaces']);
  $gids = implode(",", $gids);
  $type_wf =  rawurldecode($params['type_wf']);
  $version_wf = $params['version_wf'];
  $result[] = array(
    'id' =>      "id",
    'name' =>    $name,
    'gids' =>  $gids,
    'value' =>   $value,
    'type_wf' => $type_wf,
    'version_wf' => $version_wf,
    'uid' => $user->uid
    );
  gofast_workflows_profil_edit($id, $name, json_encode($value), $type_wf, $version_wf, $gids);
  gofast_api_success($result);
}

function gofast_api_put_workflow_profil($params){
  //Check content type
  if (strpos($params['Content-Type'], "application/json") === FALSE) {
    return gofast_api_not_implemented("This Content-Type");
  }

  //Check authentication
  global $user;
  if ($user->uid == 0) {
    gofast_api_not_authorized("Unavailable ressource for anonymous user");
  }

   if(!isset($params['name'])) {
       gofast_api_mandatory_parameter("Name is a mandatory parameter");
       return;
   }

    if(!isset($params['value'])) {
       gofast_api_mandatory_parameter("Value is a mandatory parameter");
       return;
   }

    if(!isset($params['type_wf'])) {
       gofast_api_mandatory_parameter("Type_wf is a mandatory parameter");
       return;
    }

    if(!isset($params['version_wf'])) {
       gofast_api_mandatory_parameter("Version_wf is a mandatory parameter");
       return;
    }

  $name =  $params['name'];
  $value = $params['value'];
  $gids = array_map(fn($el) => $el["value"], $params['spaces']);
  $gids = implode(",", $gids);
  $type_wf =  rawurldecode($params['type_wf']);
  $version_wf = $params['version_wf'];
  $result[] = array(
              'id' =>      "id",
              'name' =>    $name,
              'gids' =>  $gids,
              'value' =>   $value,
              'type_wf' => $type_wf,
              'version_wf' => $version_wf,
              'uid' => $user->uid
              );
  gofast_workflows_profil_create($name, json_encode($value), $type_wf, $version_wf, $gids);
  gofast_api_success($result);
}

function gofast_api_delete_workflow_profil($params)
{
    //Check content type
    if (strpos($params['Content-Type'], "application/json") === FALSE) {
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if ($user->uid == 0) {
        gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a id param
    if (isset($params['id'])) {
        $id = $params['id'];
        if (!is_numeric($id)) {
            gofast_api_mandatory_parameter("id must be numeric");
        }
    } else {
        gofast_api_mandatory_parameter("Id is a mandatory parameter");
    }

    // cree une requette pour verifier si l'id existe ? pour elargir le champ d'erreur ?

    gofast_workflows_profil_delete($id);

    $result[] = array(
        'message' => "Profil with ID = ".$id." is Delete sucessfuly"
    );

    gofast_api_success($result);
}
