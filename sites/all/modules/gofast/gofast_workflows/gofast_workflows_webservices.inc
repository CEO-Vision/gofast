<?php


function gofast_workflows_api_edit_deadline(){
    //on recupere le taskId en parametre
    $taskId = $_GET["taskId"];
    $task = gofast_workflows_get_task_object($taskId);

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


function gofast_workflows_api_validate_access_document(){
    watchdog("debug access document", "debug");
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
                    if(is_array($nid)){
                        foreach($nid as $mynid){
                            $node = node_load(trim($mynid));
                            if(node_access('view', $node, $account)){
                                $return = array("node_access" => "true");
                            }else{
                                $return = "Le document ".$node->title." n'est pas accessible par l'utilisateur ".$account->ldap_user_givenname[LANGUAGE_NONE][0]["value"]." ".$account->ldap_user_sn[LANGUAGE_NONE][0]["value"];
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
                                $return = "Le document ".$node->title." n'est pas accessible par l'utilisateur ".$account->ldap_user_givenname[LANGUAGE_NONE][0]["value"]." ".$account->ldap_user_sn[LANGUAGE_NONE][0]["value"];
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
    $array_data = json_decode($data, true);

    //ensuite on determine a qui on va envoyer ce mail (tous les acteurs du WF)
   $liste_destinataires = array();
    //tout d'abord on envoi ce mail au user dont le login est recu en parametre (l'acteur de la tache qui a declenché cet envoi)
   $login = $array_data["login"];

   if(is_numeric($login)){
       $drupal_uid = gofast_workflows_get_drupalid_from_bonitaid($login);
       $last_actor = user_load($drupal_uid);
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
            $generic_message = gofast_workflows_api_sendmail_gettext_linkdashboard($caseObject["rootCaseId"]);

            $subject_author = t("Process", array(), array('context' => 'gofast:gofast_workflows'))." : ".$subject_author;
            $recpt = array(array('recpt' => $started_by_object->uid,
                            'method' => 'to'));

            $mail = array(
              'body' => str_replace("+", " ", rawurldecode($message_author)),
              'title' => "GOFAST",
              'subject' => str_replace("+", " ", rawurldecode($subject_author)),
              'footer' => ""
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


function gofast_workflows_replace_email_masks($message, $rootcaseObject){
    usurp(1);
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

    usurp(FALSE);
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
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
        drupal_access_denied();
        exit;
    }

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
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
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

        drupal_json(array("return_code" => "Bad document node"));
        exit;
    }


    //on recupere le document alfresco associé a la reference recu en parametre
    global $cmis_sudo_admin;
    $cmis_sudo_admin = true;
    $repositoryId = gofast_cmis_get_repository();
    $cmis_object = cmisapi_getObject($repositoryId, $reference);
    if(!isset($cmis_object->properties['cmis:objectId'])){
       drupal_json(array("return_code" => "Bad document reference"));
       exit;
    }

    //on fait quelques verifications sur le chemin
    if($full_path == "-"){
         drupal_json(array("return_code" => "Bad path"));
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
                    drupal_json(array("return_code" => "Bad root group"));
                    exit;
                }
            }else{
                //on charge le groupe du document recu en parametre (le premier groupe si présent dans plusieurs)
                 $root_group_nid = reset($document_node->og_groups);
                 $root_group = node_load($root_group_nid);

                if(!$root_group){
                    drupal_json(array("return_code" => "Bad root group"));
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
           drupal_json(array("return_code" => "Bad destination folder".$path_destination));
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
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
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
            if(count($row_array > 0)){
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
  $type_wf =  rawurldecode($params['type_wf']);
  $version_wf = $params['version_wf'];
 $result[] = array(
              'id' => $id,
              'name' => $name,
              'value' => $value,
              'type_wf' => $type_wf,
              'version_wf' => $version_wf,
              'uid' => $user->uid
              );
  /*gofast_api_success($result);
  watchdog("debug workflow", "put");
  exit;*/
 $profil = gofast_workflows_profil_edit($id,$name,json_encode($value),$type_wf,$version_wf);

    $result[] = array(
              'id' =>    $profil->id,
              'name' =>    $profil->name,
              'value' =>    $profil->value,
              'type_wf' => $profil->type_wf,
              'version_wf' => $profil->version_wf,
              'uid' => $profil->uid
              );
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
  $type_wf =  rawurldecode($params['type_wf']);
  $version_wf = $params['version_wf'];
 $result[] = array(
              'id' =>    "id",
              'name' =>    $name,
              'value' =>    $value,
              'type_wf' => $type_wf,
              'version_wf' => $version_wf,
              'uid' => $user->uid
              );
  /*gofast_api_success($result);
  watchdog("debug workflow", "put");
  exit;*/
 $profil = gofast_workflows_profil_create($name,json_encode($value),$type_wf,$version_wf);

    $result[] = array(
              'id' =>    $profil->id,
              'name' =>    $profil->name,
              'value' =>    $profil->value,
              'type_wf' => $profil->type_wf,
              'version_wf' => $profil->version_wf,
              'uid' => $profil->uid
              );
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
