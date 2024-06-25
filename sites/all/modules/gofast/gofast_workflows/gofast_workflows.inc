<?php

function gofast_workflows_curl_exec($ch){
   curl_setopt($ch, CURLOPT_PROXY, '');
   $temps_debut = microtime(true);
   global $user;
   if(isset($_SESSION['bonita_cookie_problem_' . $user->uid])){
       //thare was a problem with cookie creation previously. DOn't try again until next logout/login
       return;
   }
   $buf = curl_exec($ch);

   $decoded_result = json_decode($buf, true);
   if(isset($decoded_result["exception"])){
       $buf = null;
   }
   $temps_fin = microtime(true);
  //watchdog('Bonita request time', round($temps_fin - $temps_debut, 4));
   return $buf;
}

function gofast_workflows_login_curl_exec($ch, $cookie_file = null){
   curl_setopt($ch, CURLOPT_PROXY, '');
   $temps_debut = microtime(true);
   global $user;
   if(isset($_SESSION['bonita_cookie_problem_' . $user->uid]) && $cookie_file !== null){
       //thare was a problem with cookie creation previously. DOn't try again until next logout/login
       return;
   }

   $buf = curl_exec($ch);
   curl_close($ch);
   $decoded_result = json_decode($buf, true);

   //check if a cookie file was created or not. if not, it means the login process was not well, so inform the user about that
   if($cookie_file !== null) {
       $buf = null;
        //unable to genere session cookie. Set a flag to inform the user and prevent next requests
        global $user;
       // $_SESSION['bonita_cookie_problem_' . $user->uid] = "true";
    }
   $temps_fin = microtime(true);
  //watchdog('Bonita request time', round($temps_fin - $temps_debut, 4));
   return $buf;
}



function gofast_workflows_get_process_tasklist($processId){
    $output = "<div style='padding:20px;'>";
    global $user;
    $bonita_id = gofast_workflows_get_user_id($user);
    $list_actives_tasks = gofast_workflows_get_list_actives_tasks(false,$processId, false, false);
    if(count($list_actives_tasks) > 0){
        $output .= "<table class='actives_tasks_table table table-bordered gofast_wf_table' id='actives_tasks_table'>";

        $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task();
        $output .= "<thead><tr>";
        foreach($array_show_fields_list_tasks as $key=>$title){
             if($title == "__userId__"){
                $output .=  "<th>".t("Assigned to", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
             }else{
                $output .=  "<th>".t($key, array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }
        }
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_tasks as $key=>$task){
            if(isset($task["workflowInstance"]["isActive"] ) && $task["workflowInstance"]["isActive"] === false){
                continue;
            }

            // pour chaque champs que l'on affiche dans le tableau, j'affiche la valeur de ce champs pour cette tache
            $output .=  theme("task_line", array('task' => $task, 'todo_liste' => false));


        }
        $output .= "<tbody>";
        $output .= "</table>";
   }
    $output .= "</div>";
    print $output;




    /*



      $output .= "<div style='padding:20px;'>";
    global $user;
    $bonita_id = ceo_vision_bonita_get_user_id($user);
    $list_actives_tasks = ceo_vision_get_list_actives_tasks(false,$processId, false, false);
    if(count($list_actives_tasks) > 0){
        $output .= "<table class='actives_tasks_table table table-bordered' id='actives_tasks_table'>";
        $array_show_fields_list_tasks = ceo_vision_get_show_fields_list_task();
        $output .= "<thead><tr>";
        foreach($array_show_fields_list_tasks as $key=>$title){
             if($title == "__userId__"){
               $output .= "<th>".t("Assigned to")."</th>";
            }else{
                $output .= "<th>".t($key)."</th>";
            }
        }
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_tasks as $key=>$task){
            if($task["workflowInstance"]["isActive"] === false){
                continue;
            }

            // pour chaque champs que l'on affiche dans le tableau, j'affiche la valeur de ce champs pour cette tache
            $output .=  theme("task_line", $task, false);


        }
        $output .= "<tbody>";
        $output .= "</table>";
   }
    $output .= "</div>";
    print $output;*/
}



/*
 * fonction qui renvoit le html formatté des taches actives pour le user courant
 */
function gofast_workflows_get_html_list_actives_tasks($archived = false, $arrayTodoList = null){
    if($arrayTodoList == null){
        $list_actives_tasks = gofast_workflows_get_list_actives_tasks($archived );
    }else{
        $list_actives_tasks = $arrayTodoList;
    }
    $output = "";
    if(count($list_actives_tasks) > 0){
        $output = "<table class='actives_tasks_table table table-bordered gofast_wf_table' id='actives_tasks_table'>";
        $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task();
        $output .= "<thead><tr>";
        foreach($array_show_fields_list_tasks as $key=>$title){
             if($title == "__userId__"){
                $output .=  "<th id=\"th_".$title."\" >".t("Author", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }else{
                $output .=  "<th id=\"th_".$title."\" >".t($key, array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }
        }
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_tasks as $key=>$task){
            if (isset($task["workflowInstance"]["isActive"]) && $task["workflowInstance"]["isActive"] === false){
                continue;
            }

            // pour chaque champs que l'on affiche dans le tableau, j'affiche la valeur de ce champs pour cette tache
            $output .=  theme("task_line", array('task' => $task, 'todo_liste' => true));

        }
        $output .= "<tbody>";
        $output .= "</table>";
    }

    return $output;
}

/**
 * @param string $case_id
 * @param int $account
 * @param boolean|int $nid if is an int, will also check if the related document is in the workflow
 * Given a Bonita process instance id and a Drupal uid, check if the user is an assignee of an active task in the process instance.
 * This will work with every workflow since it doesn't rely on specific workflow variables.
 * This will work with tasks assigned to userlists as long as the tasks have been started.
 */
function gofast_workflows_has_user_active_task_in_workflow($case_id, $uid = 0, $nid = FALSE) {
    gofast_workflows_activate_bonita_connection();
    if ($uid == 0) {
        global $user;
        $account = $user;
    } else {
        $account = user_load($uid);
    }

    // Check if assignee is in workflow
    $bonita_id = gofast_workflows_get_user_id($account);
    $matching_assignees = db_select("flownode_instance", "fi", array("target" => "bonita"));
    $matching_assignees->condition("fi.rootContainerId", $case_id)
        ->condition("fi.kind", "user")
        ->condition("fi.assigneeId", $bonita_id);
    $matching_assignees_count = (int) $matching_assignees->countQuery()->execute()->fetchField();
    if (!$nid) {
    return $matching_assignees_count > 0;
    }

    if ($matching_assignees_count <= 0) {
        return FALSE;
    }
    // If a document to check is given, check it's in the workflow
    $list_nids = reset(gofast_workflows_get_task_variable_from_db($case_id, "list_nids", "PROCESS_INSTANCE"));
    if (!$list_nids) {
        return;
    }
    // Lists are stored as XML strings in Bonita database, so we have to parse it
    $xml = simplexml_load_string($list_nids);
    $nids_in_workflow = array();

    foreach ($xml->children() as $child) {
        $nids_in_workflow[] = (string) $child;
    }
    // Provided document is not in the workflow: don't allow access
    if (!in_array($nid, $nids_in_workflow)) {
        return FALSE;
    }
    // Otherwise allow access
    return TRUE;
}

/**
 * Get a Bonita task variable without having to make an API request
 * @param $container_type if set to PROCESS_INSTANCE, will get a process variable instead of a task variable
 * @warning will work only on ready tasks
 */
function gofast_workflows_get_task_variable_from_db($taskId, $variable_name, $container_type = "ACTIVITY_INSTANCE") {
    gofast_workflows_activate_bonita_connection();
    $tasks = db_select("data_instance", "da", array("target" => "bonita"));
    $tasks->fields("da", array("clobValue"));
    $tasks->condition("da.containerId", $taskId)
        ->condition("da.name", $variable_name)
        ->condition("da.containerType", $container_type);
    return $tasks->execute()->fetchCol();
}

/**
 * This is intended to retrieve several task objects at once using the database query for greater performance
 * @return array complete task object matching the task ids given in parameter
 */
function gofast_workflows_get_task_objects_from_db($taskIds) {
    if (empty($taskIds)) {
        return [];
    }
    gofast_workflows_activate_bonita_connection();
    $query = db_select("flownode_instance", "fi", array("target" => "bonita"));
    $query->fields("fi", ["displayDescription", "executedBy", "rootContainerId", "displayName", "executedBySubstitute", "description", "actorId", "name", "id"]);
    $query->addField("fi", "stateName", "state");
    $query->addExpression("FROM_UNIXTIME(ROUND(claimedDate / 1000))", "assigned_date");
    $query->addExpression("FROM_UNIXTIME(ROUND(expectedEndDate / 1000))", "dueDate");
    $query->addExpression("FROM_UNIXTIME(ROUND(reachedStateDate / 1000))", "reached_state_date");
    $query->addExpression("FROM_UNIXTIME(ROUND(lastUpdateDate / 1000))", "last_update_date");
    $query->addExpression("'USER_TASK'", "type");
    $query->addExpression("'normal'", "priority");
    $query->addField("fi", "assigneeId", "assigned_id");
    $query->addField("fi", "rootContainerId", "caseId");
    $query->addField("fi", "rootContainerId", "rootCaseId");
    $query->addField("fi", "parentContainerId", "parentCaseId");
    $query->condition("id", $taskIds, "IN");
    $task_objects = $query->execute()->fetchAll();
    return $task_objects;
}

/**
 * @return type complete task object matching the task id given in parameter
 */
function gofast_workflows_get_task_object($taskId){
    global $user;

     if($user->uid == 0 || $user->uid == 1){
       //gofast_workflows_get_cookie(true);
        $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
        $bonita_user_id = true;
     }else{
        global $user;
        gofast_workflows_get_cookie();
        $cookie_name = "cookie_bonita".$user->name.".txt";
        $bonita_user_id = gofast_workflows_get_user_id($user);

     }
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
        curl_setopt($ch, CURLOPT_POST, 0);
        curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

       if($bonita_user_id){
            $url = URL_BONITA."API/bpm/humanTask/".$taskId;
            $params = "?d=processDefinitionId";

            curl_setopt($ch, CURLOPT_URL, $url.$params);
            $buf = gofast_workflows_curl_exec($ch);

            $array_results = json_decode($buf, true);
            $array_results_formatted = array();
            if(count($array_results)> 0){
                    //j'enrichi l'objet $task avec le case et le processDefinition dont la tache fait parti
                    $task = $array_results;
                    $caseObject = gofast_workflows_api_get_case_object($array_results["parentCaseId"], false);
                    $task["case_object"] = $caseObject;
            }
       }else{
           $task = array();
       }
       return $task;

}


/*
 * fonction qui renvoit la liste des taches actives pour le user courant
 */
function gofast_workflows_get_list_actives_tasks($archived = false, $rootCaseId = false, $filterbyuid = true, $alreadyexecuted = false, $include_case_object = true, $user_uid = null){
    if(empty($user_uid)){
        global $user;
        $user_drupal = $user;
    } else{
        $user_drupal = user_load($user_uid);
    }
     $array_results_formatted = array();

     if($user->uid == 0 || $user->uid == 1){
       //gofast_workflows_get_cookie(true);
        $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
        if(isset($user_drupal) && $user_drupal->uid != 1){
            $bonita_user_id = gofast_workflows_get_user_id($user_drupal);
        }else{
            $bonita_user_id = true;
        }
     }else{
        gofast_workflows_get_cookie();
        $cookie_name = "cookie_bonita".$user_drupal->name.".txt";
        $bonita_user_id = gofast_workflows_get_user_id($user_drupal);

     }
        //Filter by process definition ID to not display some unwanted processes - Include static cache for recursive usage
        static $processes_in_active_tasks = [];
        if(isset($processes_in_active_tasks[$user_drupal->uid])){
            $processes = $processes_in_active_tasks[$user_drupal->uid];
        }else{
            $processes = gofast_workflows_get_list_available_processes(false, false, $user_drupal->uid, false);
            $processes_in_active_tasks[$user_drupal->uid] = $processes;
        }
        
        foreach(module_implements("workflows_processes_light_dashboard") as $module){
            $processes = call_user_func($module . "_workflows_processes_light_dashboard", $processes);
        }
        $processes = array_keys($processes);

         //if admin, bypass this
         if($user_drupal->uid == 1){
            $processes = array(0);
         }                
        foreach($processes as $process){
            $ch = curl_init();
            curl_setopt($ch, CURLOPT_HEADER, 0);
            curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
            curl_setopt($ch, CURLOPT_POST, 0);
            curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

           if($bonita_user_id){
                if($archived == false){
                    $url = URL_BONITA."API/bpm/humanTask";
                    $params = "?p=0&c=99999&o=priority%20DESC";

                    if($alreadyexecuted == false){
                        $params .= "&f=state%3ready";
                    }else{
                        //$params .= "&f=state%3ready";
                    }
                    if($filterbyuid == true){
                        $params .= "&f=user_id%3d".$bonita_user_id;
                    }
                    if($rootCaseId != false){
                         $params .= "&f=caseId%3d".$rootCaseId;
                    }
                    $params .= "&d=processDefinitionId";
                }else{
                    $url = URL_BONITA."API/bpm/archivedHumanTask";
                    $params = "?p=0&c=1000";
                     if($alreadyexecuted == false){
                        $params .= "&f=state%3ready";
                    }else{
                        //$params .= "&f=state%3ready";
                    }
                    if($filterbyuid == true){
                        $params .= "&f=user_id%3d".$bonita_user_id;
                    }
                    if($rootCaseId != false){
                       // var_dump($rootCaseId);
                         $params .= "&f=caseId%3d".$rootCaseId;
                    }
                }
                if($user_drupal->uid != 1){
                 $params .= "&f=processId%3d".$process;
                }
                
                curl_setopt($ch, CURLOPT_URL, $url.$params);

                $buf = gofast_workflows_curl_exec($ch);
                $array_results = (array) json_decode($buf, true);
                if(count($array_results)> 0){
                    foreach($array_results as $key=>$task){
                        if($include_case_object == true){
                            //j'enrichi l'objet $task avec le case et le processDefinition dont la tache fait parti
                            $caseObject = gofast_workflows_api_get_case_object($task["parentCaseId"], false);

                            $task["case_object"] = $caseObject;
                        }
                        $array_results_formatted[$task["id"]] = $task;
                    }
                }
           }else{
               $array_results_formatted = array();
           }
       }


       return $array_results_formatted;

}

//API to get all processes related to a specific nid
function gofast_api_process_document($params, $api = TRUE){
    //Check content type
    if(strpos($params['Content-Type'], "application/json") === FALSE){
        return gofast_api_not_implemented("This Content-Type");
    }

    //Check authentication
    global $user;
    if($user->uid == 0){
       gofast_api_not_authorized("Unavailable ressource for anonymous user");
    }

    //Check if we have a vocabulary_name param
    if(isset($params['nid'])){
        $nid = $params['nid'];
    }else{
        gofast_api_mandatory_parameter("nid");
    }

   $string_param_nid = '%"nid":"'.$nid.'"%';
   $query = "SELECT * FROM PROCESSHISTORY p WHERE p.persistenceId IN ( SELECT PROCESSHISTORY_PID FROM PROCESSHISTORY_LINES ph WHERE ph.LINEHISTORY_PID IN (SELECT LINEHISTORY_PID FROM LINEHISTORY_CONTENTS lh WHERE lh.CONTENTHISTORY_PID IN (SELECT persistenceId FROM CONTENTHISTORY c WHERE c.content_value LIKE '$string_param_nid' AND c.type = 'node')))";

   $mysql_result = ceo_vision_workflow_execute_bonita_query_bdm($query);

    //check if we have to returns tasks or just caseIds
     if(isset($params['return'])){
        $return = $params['return'];
     }

     //filter process to get only closed in case of listing History of a document
    if($return == "instanceids"){
        if(count($mysql_result) > 0){
           foreach($mysql_result as $key=>$myresult){
               $pid_query = "select * from process_instance where id = $myresult->PID";
               $pid_result = ceo_vision_workflow_execute_bonita_query($pid_query);
               if(count($pid_result) != 0){
                   unset($mysql_result[$key]);
               }
           }
       }
    }


     if($return != "instanceids"){
       //we also have to search for olds process ( bonita6)
        $list_wf = gofast_workflows_get_task_from_document(node_load($nid));
        if(count($list_wf) > 0){
            foreach($list_wf as $task){
                $task_object = new stdClass();
                $task_object->PID = $task["rootCaseId"];
                $mysql_result[$task["rootCaseId"]] = $task_object;
            }
        }
     }

    $output = array();
    if(isset($mysql_result) && count($mysql_result) > 0){
         if($return == "process_filter"){
                $process_filters = "caseids=";
                $already_pid = array();
               if(count($mysql_result) > 0){
                    foreach($mysql_result as $result){
                        if(!isset($already_pid[$result->PID])){
                            $process_filters .= $result->PID."-";
                            $already_pid[$result->PID] = $result->PID;
                        }
                    }
               }else{
                 $process_filters .= "1";
               }
                 $output = array(
                        'process_filters' => $process_filters,
                 );
         }elseif($return == "instanceids"){
               foreach($mysql_result as $result){
                    $output[] = array(
                        'persistenceId' => $result->persistenceId,
                        'PID' => $result->PID,
                        'TITLE' => $result->TITLE,
                    );
                }

         }else{
                foreach($mysql_result as $result){
                    $output[$result->PID] = array(
                        'persistenceId' => $result->persistenceId,
                        'PID' => $result->PID,
                        'TITLE' => $result->TITLE,
                    );
                }
               $output = array($output);
            }
    }


    if($api){
        gofast_api_success($output);
    }else{
        return $output;
    }


}

function gofast_workflows_get_processcurrent_from_pid($pid){
   $query = "select TYPE,NAME,CONTENT_VALUE from PROCESSCURRENT INNER JOIN PROCESSCURRENT_CONTENTS ON PROCESSCURRENT.persistenceId=PROCESSCURRENT_CONTENTS.PROCESSCURRENT_PID INNER JOIN CONTENTCURRENT ON PROCESSCURRENT_CONTENTS.CONTENTCURRENT_PID = CONTENTCURRENT.persistenceId WHERE PID=" . $pid . ";";
   return ceo_vision_workflow_execute_bonita_query_bdm($query);
}

function gofast_workflows_get_processhistory_from_pid($pid){
   $query = "select * from PROCESSHISTORY INNER JOIN PROCESSHISTORY_LINES ON PROCESSHISTORY.persistenceId=PROCESSHISTORY_LINES.PROCESSHISTORY_PID INNER JOIN LINEHISTORY ON PROCESSHISTORY_LINES.LINEHISTORY_PID = LINEHISTORY.persistenceId WHERE PROCESSHISTORY.PID=" . $pid . ";";
   return ceo_vision_workflow_execute_bonita_query_bdm($query);
}

function gofast_workflows_get_processcurrent_infos_from_pid($pid){
   $query = "select * from PROCESSCURRENT WHERE PID=" . $pid . ";";
   return ceo_vision_workflow_execute_bonita_query_bdm($query);
}

function gofast_workflows_get_processhistory_infos_from_pid($pid){
   $query = "select * from PROCESSHISTORY WHERE PID=" . $pid . ";";
   return ceo_vision_workflow_execute_bonita_query_bdm($query);
}

function ceo_vision_workflow_execute_bonita_query_bdm($query){
    $mysql_result = array();
    $VALEUR_hote ='localhost';
    $VALEUR_port ='3306';
    $VALEUR_nom_bd = variable_get_value('bonita_mysql_db')."_bdm";
    $VALEUR_user = variable_get_value('bonita_mysql_user');
    $VALEUR_mot_de_passe = variable_get_value('bonita_mysql_password');

    $connexion = new PDO('mysql:host='.$VALEUR_hote.';port='.$VALEUR_port.';dbname='.$VALEUR_nom_bd.";charset=utf8", $VALEUR_user, $VALEUR_mot_de_passe);
    $resultats=$connexion->query($query);
    if(is_object($resultats)){
        $resultats->setFetchMode(PDO::FETCH_OBJ);
        while( $resultat = $resultats->fetch() )
        {
               $mysql_result[] = $resultat;
        }
        $resultats->closeCursor();
    }

    return $mysql_result;
}

function ceo_vision_workflow_execute_bonita_query_bdm_mysqli($query){
    $mysql_result = array();
    $VALEUR_hote ='localhost:3306';
    $VALEUR_nom_bd = variable_get_value('bonita_mysql_db')."_bdm";
    $VALEUR_user = variable_get_value('bonita_mysql_user');
    $VALEUR_mot_de_passe = variable_get_value('bonita_mysql_password');

    $mysqli = new mysqli($VALEUR_hote, $VALEUR_user, $VALEUR_mot_de_passe, $VALEUR_nom_bd);
    $mysqli->multi_query($query);

    do {
        if ($res = $mysqli->store_result()) {
            $mysql_result = json_decode(json_encode($res->fetch_all(MYSQLI_ASSOC)));
            $res->free();
        }
    } while ($mysqli->more_results() && $mysqli->next_result());

    return $mysql_result;
}


function  gofast_workflows_get_task_from_document($node, $finished = false){
    if ($node->type !== 'alfresco_item') {
        return array();
    }

    $reference_document = str_replace("workspace://SpacesStore/", "", $node->reference);

   // $query = 'select * from data_instance where name="gofast_document_reference" and clobValue="'.$reference_document.'"';
     $query = 'select * from data_instance where name="gofast_document_reference" and clobValue LIKE "%'.$reference_document.'%"';

    $mysql_result = ceo_vision_workflow_execute_bonita_query($query);
    $new_tasks = array();
    if(count($mysql_result) > 0){
        foreach($mysql_result as $caseId){
            if($finished == false){
                $case_tasks = gofast_workflows_get_list_actives_tasks(false, $caseId,false,false);
            }else{
                $case_tasks = gofast_workflows_get_list_actives_tasks(true, $caseId,false,false);
            }
            if(count($case_tasks) > 0){
                foreach($case_tasks as $taskId=>$task_object){
                        //si le assigned_id de la tache est vide, je vérifie si la tache est accessible a l'utiliseur courant ou non
                        if($task_object["assigned_id"] == ""){
                            global $liste_actives_tasks_all_global;
                            if(isset($liste_actives_tasks_all_global[$task_object["id"]])){
                                //$task["assigned_id"] = true signifie que la tache n'est pas assignée au user mais qu'elle lui est accessible
                                $task_object["assigned_id"] = true;
                            }else{
                                 $task_object["assigned_id"] = false;
                            }
                        }
                    $new_tasks[$taskId] = $task_object;
                }
            }
        }
    }

    return $new_tasks;


}

function ceo_vision_workflow_execute_bonita_query($query){
    $mysql_result = array();
    $VALEUR_hote ='localhost';
    $VALEUR_port ='3306';
    $VALEUR_nom_bd = variable_get_value('bonita_mysql_db');
    $VALEUR_user = variable_get_value('bonita_mysql_user');
    $VALEUR_mot_de_passe = variable_get_value('bonita_mysql_password');

    $connexion = new PDO('mysql:host='.$VALEUR_hote.';port='.$VALEUR_port.';dbname='.$VALEUR_nom_bd, $VALEUR_user, $VALEUR_mot_de_passe);
    $resultats=$connexion->query($query);
    $resultats->setFetchMode(PDO::FETCH_OBJ);
    while( $resultat = $resultats->fetch() )
    {
           $mysql_result[] = $resultat->containerId;
    }
    $resultats->closeCursor();

    return $mysql_result;
}



/*fonction qui renvoit la liste des taches actives que l'on a assignés a d'autres utilisateurs
 * necessitede recevoir en parametre la liste de toutes les taches actives, obtenue grace a ceo_vision_get_list_actives_cases() */
function gofast_workflows_get_list_actives_tasks_others($list_actives_cases, $bonita_uid){
     //on stocke dans un tableau toutes les cases dont on est l'auteur
    $my_list_actives_cases = array();
    if(count($list_actives_cases) > 0){
        foreach($list_actives_cases as $key=>$active_case){
            if($active_case["started_by"] == $bonita_uid){
                $my_list_actives_cases[$key] = $active_case;
            }
        }


    }

    //si ce tableau des cases dont on est l'auteur n'est pas vide, je recupere les taches actives QUI NE ME SONT PAS ASSIGNEES pour chacuns de ces cases

     $liste_actives_tasks_to_other = array();
    if(count($my_list_actives_cases) > 0){
        foreach($my_list_actives_cases as $key=>$active_case){
             $list_actives_tasks = gofast_workflows_get_list_actives_tasks(false, $active_case["rootCaseId"], false, false);
             //si elle n'est pas assignée au user courant je la garde, sinon non (car si elle est assignée au user courant, elle apparait déjà dans la TODO liste)
             if(count($list_actives_tasks) > 0){
                foreach($list_actives_tasks as $id_task => $task){
                    if($task["assigned_id"] !== $bonita_uid){
                        $liste_actives_tasks_to_other[$id_task] = $task;
                    }
                }
             }
        }
    }

    return  $liste_actives_tasks_to_other;
}


function gofast_workflows_get_list_actives_tasks_all($bonita_uid, $return_objects = true){
  $query = 'select f.id as containerId from flownode_instance f inner join process_instance p on f.rootContainerId = p.id where (f.assigneeId="'.$bonita_uid.'") or (p.startedBy="'.$bonita_uid.'" and f.assigneeId!="0")';
  //for the moment we are obliged to call this webservice because direct sql query only get tasks directly assigned to current user, not tasks assigned to actor
  $assigned_tasks = gofast_workflows_get_list_actives_tasks( false, false,  true,  false, false);
  $keys_assigned_tasks = array_keys($assigned_tasks);
  $mysql_result = ceo_vision_workflow_execute_bonita_query($query);

  $new_tasks = array();
  $liste_actives_tasks_all = array();
    if(count($mysql_result) > 0 || count($keys_assigned_tasks) > 0){
        $mysql_result = array_unique(array_merge($mysql_result, $keys_assigned_tasks));
        foreach($mysql_result as $taskId){
            if($return_objects == true){
                $task_object = gofast_workflows_get_task_object($taskId);
            }else{
                $task_object = array();
            }
             $liste_actives_tasks_all[$taskId] = $task_object;
        }
    }

    /* $query = 'select f.id as containerId from flownode_instance f inner join process_instance p on f.rootContainerId = p.id where (f.assigneeId="'.$bonita_uid.'") or (p.startedBy="'.$bonita_uid.'" and f.assigneeId!="0")';

    $mysql_result = ceo_vision_workflow_execute_bonita_query($query);

    $new_tasks = array();
    $liste_actives_tasks_all = array();


    if(count($mysql_result) > 0){
        foreach($mysql_result as $taskId){
             $task_object = gofast_workflows_get_task_object($taskId);
             $liste_actives_tasks_all[$taskId] = $task_object;
        }
    }*/


    return $liste_actives_tasks_all;
}


/*
 * fonction qui renvoit la liste des cases (instance de workflow) actifs pour le user courant
 */
function gofast_workflows_get_list_actives_cases($archived = false, $rootCaseId = false, $filterbyuser = true, $admin = false, $todoliste = null){

    if($admin == false){
        global $user;
        $cookie_name = "cookie_bonita".$user->name.".txt";
    }else{
        $cookie_name = "cookie_bonitainstall.txt";
        $user->name = "install";
    }
    $array_caseId = array();
    if($todoliste != null){
        //on construit un tableau a partir de la todoliste recu en parametre. ce tableau ne contient que les id des Case dont font parti les taches
        //cela permettra de comparer avec les ID des cases que l'on va recevoir dans la requete juste en dessous et recuperer les cases qui manquent

        if(count($todoliste) > 0){
            foreach($todoliste as $taskId=>$task_array){
                $array_caseId[$task_array["caseId"]] = $task_array["caseId"];
            }
        }

    }

        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
        curl_setopt($ch, CURLOPT_POST, 0);
        curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
        $bonita_user_id = gofast_workflows_get_user_id($user);

       if($bonita_user_id){

            if($archived == false){
                $url = URL_BONITA."API/bpm/case";
                $params = "?p=0&c=1000&f=state%3ready";
                if($filterbyuser == true){
                   $params .= "&f=user_id%3d".$bonita_user_id;
                }
                if($rootCaseId != false){
                     $params .= "&f=rootCaseId%3d".$rootCaseId;
                }
                //$params .= "&d=processId";
                $params .= "&d=processDefinitionId";

            }else{
                $url = URL_BONITA."API/bpm/archivedCase";
                $params = "?p=0&c=1000";
                if($filterbyuser == true){
                   $params .= "&f=user_id%3d".$bonita_user_id."";
                }
                if($rootCaseId != false){
                     $params .= "&f=rootCaseId%3d".$rootCaseId;
                }
                 $params .= "&d=processDefinitionId";
            }

            curl_setopt($ch, CURLOPT_URL, $url.$params);
            $buf = gofast_workflows_curl_exec($ch);
            $array_results = json_decode($buf, true);
            $array_results_formatted = array();

            if(count($array_results)> 0){
                foreach($array_results as $key=>$task){
                    $array_results_formatted[$task["id"]] = $task;
                    //on supprime ce processus du tableau $array_caseId pour pouvoir facilement a la fin trouver les processus qui mansuent
                   unset($array_caseId[$task["id"]]);

                }

                if(count($array_caseId) > 0){
                    foreach($array_caseId as $caseId){
                        $url = URL_BONITA."API/bpm/case/".$caseId;
                        curl_setopt($ch, CURLOPT_URL, $url.$params);
                        $buf = gofast_workflows_curl_exec($ch);
                        $array_results = json_decode($buf, true);
                        $array_results_formatted[$caseId] = $array_results;
                    }
                }
            }
       }else{
           $array_results_formatted = array();
       }

       return $array_results_formatted;

}



/*
 * fonction qui renvoit le html formatté des cases (instances de WF) actives pour le user courant
 */
function gofast_workflows_get_html_list_actives_cases($arrayTodoList = null){
    //on recupere les "cases" dont on fait parti (les workflow dont on fait parti mais dont on a pas forcement de tache en cours)
    $list_actives_cases = gofast_workflows_get_list_actives_cases(false, false, true, false, $arrayTodoList);

    $output = "";
    if(count($list_actives_cases) > 0){
        $output = "<table class='actives_cases_table table table-bordered' id='actives_cases_table'>";
        $output .= "<thead><tr>";
        $output .= "<th id=\"th_process_title\">".t("Process title", array(), array('context' => 'gofast:gofast_workflows'))." ".theme("link_show_processtitle_help_popup")."</th>";
        $output .= "<th id=\"th_process_type\">" . t("Process type", array(), array('context' => 'gofast:gofast_workflows')) . "</th>";
        $output .= "<th id=\"th_process_type\">".t("Process model", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th id=\"th_process_tasks\">".t("Tasks", array(), array('context' => 'gofast:gofast_workflows'))." ".theme("link_show_tasktitle_help_popup")."</th>";
        //$output .= "<th id=\"th_process_\">".t("Finished tasks")." ".theme("link_show_tasktitle_help_popup")."</th>";
        $output .= "<th id=\"th_process_start\">".t("Start date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th id=\"th_process_dl\">".t("Deadline", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        //$output .= "<th>".t("Actions")."</th>";
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_cases as $key=>$case){

            $case_variables = gofast_workflows_get_case_variables_from_id($case["rootCaseId"]);
            //on recupere la definition du process dont fait partie ce case
            //$processDefinition = ceo_vision_get_details_process($case["processDefinitionId"]);
            $output .= "<tr>";

            //titre du processus (variable gofast_processus_title)
            //si le processus comporte un Pageflow de résumé, on affiche le bouton qui permet de le consulter
            $description_array = json_decode($case["processDefinitionId"]["description"], true);
            //if($description_array["is_specific_pageflow"] == "TRUE"){
                $process_title  = theme("link_show_pageflow_popup", $case, NULL, FALSE, "float:none")." ";
            //}
            if(isset($case_variables[BONITA_TITLE_PROCESS]["value"])){
                $process_title .= $case_variables[BONITA_TITLE_PROCESS]["value"];
            }else{
                $process_title .= t("No process title for this process", array(), array('context' => 'gofast:gofast_workflows'));
            }

            $output .= "<td><span style='width:210px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;'>".$process_title."</span></td>";

            //Nom du process
            $output .= "<td>".theme("link_show_diagram_popup", array('process' => $case["processDefinitionId"], 'style' => "float:left;"))." <span style='float:left;width:185px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;'>".$case["processDefinitionId"]["displayName"]."</span></td>";

            //on affiche le boutton qui ouvre la popup avec les taches actives dans ce process
            $html_button_actives_tasks = theme("link_show_actives_tasklist_from_process_popup", array('processId' => $case["rootCaseId"]));
            $output .= "<td>".$html_button_actives_tasks;
             //on affiche le boutton qui ouvre la popup avec les taches actives dans ce process
            $html_button_finished_tasks = theme("link_show_finished_tasklist_from_process_popup",array('processId' => $case["rootCaseId"]));
            $output .= " | ".$html_button_finished_tasks;
            //on affiche le bouton de suppression du process en cours (les controles d'accès sont faits dans la fonction de theme)
            $html_button_delete_case = theme("link_show_delete_case_popup", $case);
            $output .= " | ".$html_button_delete_case;

            $output .= "</td>";



            //$output .= "<td>".$html_button_finished_tasks."</td>";

             //date de début
            $output .= "<td>".format_date(strtotime($case["start"]), 'custom', 'd/m/y')."</td>";


            //date d'écheance si elle existe
            if(isset($case_variables[BONITA_DEADLINE_PROCESS]["value"]) && $case_variables[BONITA_DEADLINE_PROCESS]["value"] != "null"){
                $deadline = format_date(strtotime($case_variables[BONITA_DEADLINE_PROCESS]["value"]), 'custom', 'd/m/y');
            }else{
                $deadline = t("No deadline", array(), array('context' => 'gofast:gofast_workflows'));
            }
            $output .= "<td>".$deadline."</td>";

            $output .= "</tr>";
        }
        $output .= "</tbody></table>";
    }

    return $output;
}


function gofast_workflows_get_html_list_available_processes($reference = false){

      $list_available_processes = gofast_workflows_get_list_available_processes();

    $output = "";
    if(count($list_available_processes) > 0){
        
        $array_show_fields_list_processes = gofast_workflows_get_show_fields_list_processes();
        $output .= "<table class='available_process_table table table-bordered' id='available_process_table'><thead><tr>";
        foreach($array_show_fields_list_processes as $key=>$title){
             $output .=  "<th>".t($key, array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        }

        //on rajoute les actions
       $output .="<th>".t("Manage model", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
       $output .= "</tr></thead>";

        foreach($list_available_processes as $key=>$process){

            $output .= "<tr>";

            // title
            $content = "<span style='font-weight:bold;'>" . t($process["displayName"], array(), array('context' => 'gofast:gofast_workflows')) . "</span>";
            $output .= "<td class=\"gofast_wf_actions\">" . theme("link_start_process_popup", array('process' => $process, "reference" => $reference, "content" => $content)) . "</td>";

            // Process Model
            $output .= "<td class=\"gofast_wf_profil\" style=\"display: flex; align-items: center; justify-content: space-between;\">";

            // We load all saved profil to display multiple line for each process with saved profils in a droplist
            $saved_profils = gofast_workflows_profil_get_all_from_type_wf($process["displayName"]);

            if(in_array($process["name"], variable_get("gofast_workflows_processes_models", array('Document broadcast', 'Courrier Sortant')))){

                if(! str_ends_with(urldecode($reference), '|') ){
                    $referenceListe = $reference;
                }else{
                    $referenceListe = "";
                }
                 $processID = $process["id"];
                $processName = $process["name"]."--".$process["version"]."|".t($process["name"] , array(), array('context'=> 'gofast:gofast_workflow'))." (v ".$process["version"].")";
                $addOnlick = "Drupal.gofast_workflows.ceo_vision_js_process_startit('".$processID."', '".$processName."', '".str_replace("'", " ", $reference)."', '".$referenceListe. "' , 'new', '')";

                //add element to be able to start WF without any saved profil
                $actions = gofast_workflows_get_availables_buttons_from_process($process, $reference, $process['id']);
                $output .=  theme("workflows_process_model", array('profils' => $saved_profils, 'process_id'=> $process['id'], 'addOnclick'=> $addOnlick, 'actions' => $actions));
            }else{
                $output .= t("This process is not compatible with process models", array(), array('context' => 'gofast:gofast_workflows'));
                $output .= gofast_workflows_get_availables_buttons_from_process($process, $reference, $process['id'], FALSE);
            }           

            // version
           // $output .= "<td>" . $process["version"] . "</td>";

            // description
            //$process_description_array = theme("process_description", $process);
            //$output .= "<td>" . $process_description_array["output"] . "</td>";
            
             //  action
           $model_actions = theme("workflows_process_model_actions", array('profils' => $saved_profils, 'process_id'=> $process['id'], 'addOnclick'=> $addOnlick));      
           $output .= "<td class=\"gofast_wf_actions\" >" . $model_actions . "</td>";

           $output .= "</tr>";
      
        }

           
        $output .= "</table>";
    }else{
        $output .= t("No process available", array(), array('context' => 'gofast:gofast_workflows'));
    }

    return $output;
}



/*
 * fonction qui renvoit le html formatté des cases (instances de WF) actives pour le user courant
 */
function gofast_workflows_get_html_list_archived_cases(){
    //on recupere les "cases" dont on fait parti (les workflow dont on fait parti mais dont on a pas forcement de tache en cours)
    $list_actives_cases = gofast_workflows_get_list_actives_cases(true);

    //je retri le tableau par ordre d'archivage décroissant
    $list_actives_cases_ordered = array();
    foreach($list_actives_cases as $key=>$case){
        $list_actives_cases_ordered[$case["archivedDate"]] = $case;
    }
   krsort($list_actives_cases_ordered);

    $output = "";
    if(count($list_actives_cases) > 0){
        $output = "<table class='archived_cases_table table table-bordered' id='archived_cases_table'>";
        $output .= "<thead><tr>";
        $output .= "<th >".t("Process type", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Tasks history", array(), array('context' => 'gofast:gofast_workflows'))." ".theme("link_show_tasktitle_help_popup")."</th>";
        $output .= "<th>".t("Author", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Start date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("End date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_cases_ordered as $key=>$case){
            //$case_variables = ceo_vision_bonita_get_case_variables_from_id($case["rootCaseId"]);

            //on recupere la definition du process dont fait partie ce case
            //$processDefinition = ceo_vision_get_details_process($case["processDefinitionId"]);
            $output .= "<tr>";
            $process_title = " ".theme("link_show_pageflow_popup", $case, NULL, true, "float:left;");
            $process_title .= $case["processDefinitionId"]["displayName"];



            $output .= "<td>".$process_title."</td>";


             //on affiche le boutton qui ouvre la popup avec les taches actives dans ce process
            $html_button_finished_tasks = theme("link_show_finished_tasklist_archived_from_process_popup", array('processId' => $case["rootCaseId"]));
            $output .= "<td>".$html_button_finished_tasks."</td>";

            //auteur

            $output .= "<td>".theme("picture_bonita", array("bonita_uid" => $case["started_by"]))."</td>";

            //date de début
            $output .= "<td>".gofast_workflows_format_date($case["start"])."</td>";

            //date de fin
            $output .= "<td>".gofast_workflows_format_date($case["archivedDate"])."</td>";

            $output .= "</tr>";
        }
        $output .= "</tbody></table>";
    }

    return $output;
}




function gofast_workflows_get_html_list_actives_tasks_others(){
    //d'abord je récupere la listes des cases actifs dont le user courant est l'auteur
    //je recupere l'id bonita du user courant
    global $user;
    $bonita_uid = gofast_workflows_get_user_id($user);
    $list_actives_cases = gofast_workflows_get_list_actives_cases();

    $liste_actives_tasks_to_other = gofast_workflows_get_list_actives_tasks_others($list_actives_cases, $bonita_uid);
    $output = "";
    if(count($liste_actives_tasks_to_other) > 0){
        $output = "";
        $output = "<table class='actives_tasks_table gofast_wf_table table table-bordered' id='actives_tasks_others_table'>";
        $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task();
        $output .= "<thead><tr>";
        foreach($array_show_fields_list_tasks as $key=>$title){
            //cas un peu particulier du champs user qui peut a la fois servir a afficher a qui est attribuée la tache, ou bien si on est dans la TODO liste
            //qui nous a attribué cette tache (l'auteur de la case)
            if($title == "__userId__"){
                $output .=  "<th>".t("Assigned to", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }else{
                $output .=  "<th>".t($key, array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }
        }
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($liste_actives_tasks_to_other as $key=>$task){
            // pour chaque champs que l'on affiche dans le tableau, j'affiche la valeur de ce champs pour cette tache
            $output .=  theme("task_line", array('task' => $task, 'todo_liste' => false));

        }
        $output .= "<tbody>";
        $output .= "</table>";
    }

    return $output;
}


/*
 * fonction qui renvoit la liste des processes dipsonibles pour le user courant
 */
function gofast_workflows_get_list_available_processes($filter_is_document = false, $restrict = true, $uid = null, $enabled = true){

       if($uid == null){
            global $user;
       }else{
            $user = user_load($uid);
       }

       $bonita_id = gofast_workflows_get_user_id($user);
       $cookie_name = "cookie_bonita".$user->name.".txt";
       $ch = curl_init();
       curl_setopt($ch, CURLOPT_HEADER, 0);
       curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
       curl_setopt($ch, CURLOPT_POST, 0);
       curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/$cookie_name");

      if($restrict){
          $filter_restrict = "&f=user_id%3d".$bonita_id;
      }

      if($enabled){
          $activation_state = "&f=activationState%3dENABLED";
      }

      $url = URL_BONITA."API/bpm/process?p=0&c=100&o=displayName%20ASC" . $activation_state . $filter_restrict;

       curl_setopt($ch, CURLOPT_URL, $url);

       $buf = gofast_workflows_curl_exec($ch);

        $array_results = (array) json_decode($buf, true);
        $array_results_formatted = array();

       if(count($array_results)> 0){
            foreach($array_results as $key=>$process){
                $array_results_formatted[$process["id"]] = $process;
            }
        }

        //si le parametre $filter_is_document vaut true, je filtre les process qui concernent les doc (dans l'objet json de la description il faut que le param is_document = true)
       if($filter_is_document == true){
           foreach($array_results_formatted as $key=>$process){
               $description_json = $process["displayDescription"];
               $description_array = json_decode($description_json, true);
               if($description_array["is_document"] !== "TRUE"){
                   unset($array_results_formatted[$key]);
               }
           }
       }
        return $array_results_formatted;

}





function gofast_workflows_get_html_history(){

    $hook = 'theme_history';
    $output = "";
    /*foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      $function(&$output);
    }*/

    //aucun hook n'a renvoyé d'output
    if($output == ""){
        $output = _gofast_workflows_get_html_history();
    }

    return $output;


}

function _gofast_workflows_get_html_history(){
      //on recupere les lignes dans la table ceo_vision_workflow_history
    $list_history_cases = gofast_workflows_get_list_history_cases();


    $output = "";
    if(count($list_history_cases) > 0){
        $output = "<table class='archived_cases_table table table-bordered' id='archived_cases_table'>";
        $output .= "<thead><tr>";
        $output .= "<th>".t("Process type", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Process title", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Author", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Document", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Version", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Start date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("End date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Status", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "<th>".t("Details", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_history_cases as $key=>$case){
            $output .= "<tr'>";
            if($case->etat_wf == 1){
                $etat_string = t("Opened", array(), array('context' => 'gofast:gofast_workflows'));
            }else{
                 $etat_string = t("Closed", array(), array('context' => 'gofast:gofast_workflows'));
            }

            if($case->timestamp_close != null && $case->timestamp_close != 0){
                $end_date = format_date($case->timestamp_close, 'custom', "d/m/y");
            }else{
                $end_date = " - ";
            }
                $output .= "<td>".$case->gofast_type_processus."</td>";
                $output .= "<td>".$case->gofast_titre_processus."</td>";
                $output .= "<td>".theme('username', user_load($case->uid))."</td>";
                $output .= "<td>".theme('document_link_bonita',$case->gofast_document_reference)."</td>";
                $output .= "<td>".$case->gofast_document_reference_version."</td>";
                $output .= "<td>".format_date($case->timestamp, 'custom', "d/m/y")."</td>";
                $output .= "<td>".$end_date."</td>";
                $output .= "<td>".$etat_string."</td>";
                $html_detail = gofast_workflows_get_html_history_detail($key);
                $output .= "<td>".$html_detail."</td>";
            $output .= "</tr>";
        }
        $output .= "</tbody></table>";
    }

    return $output;
}


function gofast_workflows_get_html_history_detail($pid){

    $hook = 'theme_history_detail';
    $output = "";
    /*foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      $function($pid,&$output);
    }*/

    //aucun hook n'a renvoyé d'output
    if($output == ""){
        $output = _gofast_workflows_get_html_history_detail($pid, $output);
    }

    return $output;


}

function _gofast_workflows_get_html_history_detail($pid, &$output){
    $output .= "<div style='overflow:hidden;'><div class='wf_history_details' style='max-height:150px;background-position:98% 2%;'>";

    $list_history_details = gofast_workflows_get_list_history_details($pid);
    if(count($list_history_details) > 0){
        foreach($list_history_details as $row => $detail){
            $output .= "<div style='border: 1px solid #c0c0c0;padding:2px;margin-top:4px;'>";
            foreach($detail as $name=>$value){
                $output .= "<div style='min-width:250px;'>";
                if(gofast_workflows_get_detail_type_from_name($name) == "user"){
                    $output .= "<b>".$name."</b> : ".theme("user_bonita", $value);
                }elseif(gofast_workflows_get_detail_type_from_name($name) == "date"){
                    $output .= "<b>".$name."</b> : ".$value;
                }else{
                    $output .= "<b>".$name."</b> : ".$value;
                }
                $output .= "</div>";
            }
            $output .= "</div>";
        }
    }

    $output .= "</div></div>";
    return $output;
}

 function gofast_workflows_api_delete_case($api = TRUE){

    global $user;

    $caseId = $_GET["caseid"];
    $case = gofast_workflows_api_get_case_object($caseId, false);

    if($case){

        $process_current_infos = gofast_workflows_get_processcurrent_infos_from_pid($case['id'])[0];

        //before to delete, call custom hook to allow modules to execute custom actions
         foreach(module_implements('workflows_case_delete') as $module){
             call_user_func_array($module . '_workflows_case_delete', array(&$case));
        }

       gofast_workflows_get_cookie(true);
       $cookie = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
       gofast_workflows_curl_delete_case($case, $cookie);

        //Insert into audit
        $event = array('mod_author' => $user->uid, 'mod_timestamp' => time(), 'event' => 'workflow_delete', "worklow_name" => $process_current_infos->TITLE);
        $event = serialize($event);
        $last_event_serialized = rawurlencode($event);
        $last_event_unserialized["mod_timestamp"] = time();
        $last_event_unserialized["mod_author"] = $user->uid;
        gofast_audit_insert_line_audit(0, 'workflow_delete', $last_event_serialized, $last_event_unserialized);

        //TODO Send mail to inform all actors
        if($api){
            drupal_json_output(array("state" => "OK"));
            exit;
        }
    }
    if($api){
        drupal_json_output(array("state" => "KO"));
        exit;
    }
}


function gofast_workflows_api_get_case_object($caseId, $admin = false){

    if($admin == false){
        global $user;
        $bonita_user_id = gofast_workflows_get_user_id($user);
        $cookie_name = "cookie_bonita".$user->name.".txt";
    }else{
        $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
        global $user;
        $bonita_user_id = true;
    }


    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HEADER, 0);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
    curl_setopt($ch, CURLOPT_POST, 0);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

    $html_return = "";
    if($bonita_user_id){
        $url = URL_BONITA."API/bpm/case/".$caseId."?d=processDefinitionId";
        curl_setopt($ch, CURLOPT_URL, $url);
        $buf = gofast_workflows_curl_exec($ch);
        $array_results = json_decode($buf, true);

        return $array_results;
    }else{
        return false;
    }

}



/*
 * fonction qui renvoit la liste des champs que l'on affiche dans le tableau de la liste des taches actives pour le user courant.
 * En parametre on peut recevoir le nom d'un workflow specifique si jamais il est surchargé dans Drupal au niveau de l'UI
 */
function gofast_workflows_get_show_fields_list_task($name_workflow = null){

    if($name_workflow){
        $fields = array("title" => "displayName",
                        "document" => "document",
                        "Description tache" => "description",
                        //"display_name" => "displayName",
                        //"comment" => "bpm_comment",
                        //"limit_date" => "dueDate",
                        );
    }else{
//         $fields = array("Nom" => "displayName",
//                        "Infos de la tache" => "__bpm_infos__",
//                        "Description du processus" => "description",
//                        "Commentaires" => "__bpm_comment__",
//                        );

        //la convention __nom__ indique que l'on va traiter individuellement ces champs. Sinon il faut mettre le nom du champs tel qu'il est dans l'objet $task pour qu'il s'affiche directement
        $fields = array(t("Task", array(), array('context' => 'gofast:gofast_workflows'))." ".theme("link_show_tasktitle_help_popup") => "displayName",
                        t("Process")." ".theme("link_show_processtitle_help_popup") => "__".BONITA_TITLE_PROCESS."__",
                        //"Description tache" => "displayDescription",
                        //"Process type" => "__processName__",
                        "User" => "__userId__",
                        "Document" => "__".BONITA_DOCUMENT_PROCESS."__",
                        "Creation" => "__started_date__",
                        "Deadline" => "__".BONITA_DEADLINE_PROCESS."__",
                        //"Com." => "__bpm_actions__",
                        );
    }

    return $fields;
}


/*
 * fonction qui renvoit la liste des champs que l'on affiche dans le tableau de la liste des processes dispo pour le user courant
 */
function gofast_workflows_get_show_fields_list_processes(){
     $fields = array("Process type" => "displayName",
                     "Process model" => "processModel",
                    // "Version" => "version",
                     //"Status" => "activationState",
                     //"Description" => "__displayDescription__", // ce champs contient un objet json qui lui même contient plusieurs infos
                     //"Profil" => "Profil"
                     );

    return $fields;
}

function gofast_workflows_get_case_variables_from_id($case_id){

    global $user;
    if($user->uid == 0 || $user->uid == 1){
        $cookie_name = "cookie_bonitainstall.txt";
    }else{
        $cookie_name = "cookie_bonita".$user->name.".txt";
    }
    $url = URL_BONITA."API/bpm/caseVariable";
    $params = "?p=0&c=100&f=case_id%3d".$case_id."&d=description";

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url.$params);

    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);
    //on reformate le resultat pour utiliser le nom des variable comme clé du tableau
    $formatted_case_variables = array();
    if(count((array)$array_results) > 0){
        foreach($array_results as $case_variable){
             $formatted_case_variables[$case_variable["name"]] = $case_variable;
        }
    }

    return $formatted_case_variables;

}

function gofast_workflows_set_case_variables($variable_name, $variable_value, $caseId, $variable_type = "java.lang.String"){

   global $user;
    if($user->uid == 0 || $user->uid == 1){
        $cookie_name = "cookie_bonitainstall.txt";
    }else{
        $cookie_name = "cookie_bonita".$user->name.".txt";
    }

    $url = URL_BONITA."API/bpm/caseVariable/$caseId/$variable_name";
    $data = array('type' => $variable_type, 'value' => "$variable_value");

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen(json_encode($data)))
    );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT"); // note the PUT here
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($data));
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url);

     $buf = gofast_workflows_curl_exec($ch);

    $array_results = json_decode($buf, true);

    return $array_results;
}



/*
 * fonction qui renvoi le code html des boutons dispo en fonction de la tache courante
 * $process est le tableau representant du process courant
 */

function gofast_workflows_get_availables_buttons_from_process($process, $reference = false, $profil_id = false, $model = true){
   $output = "";
   $processID = $process["id"];

   $content = "<span class=\"".BONITA_WF_ICON__START_PROCESS." gofast_wf_link\" alt='Start process' id='task_next_".$processID."' ></span>";
   $output .= '<span class="gofast_wf_actions">';
   $output .= theme("link_start_process_popup", array('process' => $process, "reference" => $reference, "content" => $content , "profil_id" => $profil_id));
   if($reference == false && $model == true){
        global $user;
        $reference_cart = "";
        $query = db_query("SELECT n.title, entity_id, flagging.entity_type, flagging_id, flagging.uid name, flagging.fid FROM flagging INNER JOIN flag ON flagging.fid = flag.fid INNER JOIN node n on n.nid = flagging.entity_id WHERE flagging.uid=".$user->uid." AND (name='cart') AND n.status = 1");

        foreach($query as $occur){
            $reference_cart = $reference_cart.$occur->entity_id . "`" . $occur->title ."|";
        }
        $reference_cart = rtrim($reference_cart, "|");
        $content = "<span class=\"".BONITA_WF_ICON__START_PROCESS_FROM_CART." gofast_wf_link\" alt='Start process from cart' id='task_next_".$processID."' ></span>";     
        $output .= theme("link_start_process_popup_from_cart", array('process' => $process, "reference" => rawurlencode($reference_cart), "content" => $content , "profil_id" => $profil_id));
   }
   //$output .= theme("link_show_diagram_popup",  array('process' => $process, "style" => ""));
   $output .= '</span>';

   return $output;
}


function gofast_workflows_get_image_process($processId, $process_name){
    //on copie l'image du process dans le repertoire swf dans l'arborescence Drupal
    $output = "<img src='/sites/default/files/".gofast_xss_clean($process_name).".png?rand=".time()."' />";
    print $output;

}



/*
 * fonction qui renvoit l'id drupal (uid) du id (bonita ID) recu en parametre
 */
function gofast_workflows_get_drupalid_from_bonitaid($bonita_id, $returnobject = false){

    if($bonita_id == -1 || $bonita_id == 0 || $bonita_id === null){
        return false;
    }

    //ceo_vision_bonita_get_cookie(true);
    $cookie_name = "cookie_bonitainstall.txt";

     //on charge la variable Drupal qui contient l'association entre le drupal_id et le bonita_id
    $variable_association = variable_get(VARIABLE_NAME_ID_BONITA, array());
    $drupal_id = array_search($bonita_id, $variable_association);

    if($drupal_id){
       if($returnobject == true){
           $myuser = user_load($drupal_id);
           return $myuser;
        }else{
            return $drupal_id;
        }
    }else{
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER,1);
        curl_setopt($ch, CURLOPT_POST, 0);
        curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
        //$bonita_user_id = ceo_vision_bonita_get_user_id($user);
        $url = URL_BONITA."API/identity/user/".$bonita_id;

        curl_setopt($ch, CURLOPT_URL, $url);
        $buf = gofast_workflows_curl_exec($ch);

        $array_results = (array) json_decode($buf, true);

        if(count($array_results) > 0){
            $username = $array_results["userName"];
        }

        $myuser = user_load_by_name(trim($username));
        $variable_association[$myuser->uid] = $bonita_id;
        variable_set(VARIABLE_NAME_ID_BONITA, $variable_association);
        if($returnobject == true){
             return $myuser;
        }else{
            return $myuser->uid;
        }
    }

}





function gofast_workflows_get_process_finishedtasklist_archived($processId){
    $output = "<div style='padding:20px;'>";
    global $user;
    $bonita_id = gofast_workflows_get_user_id($user);
    $list_actives_tasks = gofast_workflows_get_list_actives_tasks(true,$processId, false, false);
    if(count($list_actives_tasks) > 0){
        $output .= "<table class='actives_tasks_table gofast_wf_table table table-bordered' id='actives_tasks_table'>";

        $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task_archived();
        $output .= "<thead><tr>";
        foreach($array_show_fields_list_tasks as $key=>$title){
             if($title == "__userId__"){
                $output .=  "<th>".t("Assigned to", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
             }elseif($title == "__started_date__"){
                $output .=  "<th>".t("Finished date", array(), array('context' => 'gofast:gofast_workflows'))."</th>";
             }else{
                $output .=  "<th>".t($key, array(), array('context' => 'gofast:gofast_workflows'))."</th>";
            }
        }
        $output .= "</tr></thead>";
        $output .= "<tbody>";
        foreach($list_actives_tasks as $key=>$task){
            if(isset($task["workflowInstance"]["isActive"] ) && $task["workflowInstance"]["isActive"] === false){
                continue;
            }

            // pour chaque champs que l'on affiche dans le tableau, j'affiche la valeur de ce champs pour cette tache
            $output .=  theme("task_line_archived", $task, false);


        }
        $output .= "<tbody>";
        $output .= "</table>";
   }
    $output .= "</div>";
    print $output;
}


/*
 * fonction qui renvoit la liste des champs que l'on affiche dans le tableau de la liste des taches actives pour le user courant.
 */
function gofast_workflows_get_show_fields_list_task_archived(){
     $fields = array("Task name" => "name",
                     "Task description" => "displayDescription",
                     "Finished date" => "__finished_date__",
                     "User" => "__userId__",
                    );

    return $fields;
}


function gofast_workflows_get_color_from_deadline($deadline){
   $array_color = array();
   $array_color["color"] = "#2ecc71";

   //on convertit la deadline en timestamp;
   $timestamp_deadline = strtotime($deadline);
   $timestamp_now = time();

   if($timestamp_now > $timestamp_deadline){
       $array_color["color"] = "#c0392b";
       $array_color["description"] = t("This process had outdated it deadline", array(), array('context' => 'gofast:gofast_workflows'));
   }elseif($timestamp_deadline - $timestamp_now < 60*60*24){
       $array_color["color"] = "#d35400";
       $array_color["description"] = t("This process will soon reach it deadline", array(), array('context' => 'gofast:gofast_workflows'));
   }
   return $array_color;

}


/* fonction qui renvoit des infos sur le noeud dont l'url est recu en parametre.
 * Cela peut etre une url avec l'ancre de navigation ajax, une url avec pathauto ou une url classique node/XX
 */
function gofast_workflows_get_node_infos_from_url($full_url){
    $parsed_url = parse_url($full_url);

    $path = $parsed_url["path"];

    if($path == ""){
        return null;
    }

        //on enleve un eventuel parametre de langue dans le path
        $language_list_clean = array();
        $language_list = language_list();
        $path_without_lang = $path;
        foreach($language_list as $key=>$language){
            if($language->enabled == '1'){
                $path_without_lang = str_replace("/".$language->prefix."/", "", $path_without_lang);
            }
        }

       $path_without_lang = rawurldecode($path_without_lang);

       //on supprime le / au debut de chaine s'il existe
       if($path_without_lang[0] == "/"){
           $path_without_lang = substr($path_without_lang,1);
       }


       //on test la fonction menu_get_item pour savoir si le path est de type node/xx
       $node_object = menu_get_item($path_without_lang);


       if(!$node_object){
            $node_object = drupal_lookup_path("source", $path_without_lang);
            $node = node_load(str_replace("node/", "", $node_object));
       }else{
         $node = node_load(str_replace("node/", "", $path_without_lang));
       }


    if(!isset($node->reference)){
        $node->reference = "workspace://SpacesStore/".$node->nid;
    }

    $array_return = array("node_title" => $node->title, 'node_path' => "node/". $node->nid, 'node_nid' => $node->nid, 'node_reference' => $node->reference);

    return $array_return;
}



function gofast_workflows_get_number_pending_tasks(){
    global $user;

    $count_actives_tasks = gofast_workflows_get_infos_task_count_rest_api()["count"];
    $list_kanban_tasks = gofast_kanban_get_user_tasks($user->uid, FALSE);
    return $count_actives_tasks + count($list_kanban_tasks);
}



function gofast_get_workflow_action_node($node, $empty = false) {
  if($empty == true){
    $list_wf = array();
  }else{
    //search old WF
    $list_wf = gofast_workflows_get_task_from_document($node);
    //search new WF
    $string_param_nid = '%"nid":"'.$node->nid.'"%';
    $query = "SELECT * FROM PROCESSHISTORY p WHERE p.persistenceId IN ( SELECT PROCESSHISTORY_PID FROM PROCESSHISTORY_LINES ph WHERE ph.LINEHISTORY_PID IN (SELECT LINEHISTORY_PID FROM LINEHISTORY_CONTENTS lh WHERE lh.CONTENTHISTORY_PID IN (SELECT persistenceId FROM CONTENTHISTORY c WHERE c.content_value LIKE '$string_param_nid' AND c.type = 'node')))";

    $mysql_result = ceo_vision_workflow_execute_bonita_query_bdm($query);

    $list_tasks = array();
    $count_my_assigned_tasks = 0;
    $count_other_assigned_tasks = 0;
    if(count($mysql_result) > 0){
        global $user;
        $bonita_assignee_id =  gofast_workflows_get_user_id($user);
        foreach($mysql_result as $result){
           $tasks_from_pid = gofast_workflows_get_list_actives_tasks(false, $result->PID, false, false, false);
           foreach ($tasks_from_pid as $task) {
                if ($task["assigned_id"] == $bonita_assignee_id) {
                    $count_my_assigned_tasks++;
                } else {
                    $count_other_assigned_tasks++;
                }
           }
          // $list_tasks = array_merge($list_tasks, $tasks_from_pid);
           $list_tasks = $list_tasks + $tasks_from_pid;
        }
    }


    //$list_wf = array_merge($list_wf, $list_tasks);
    $list_wf = $list_wf + $list_tasks;
    if($list_wf == FALSE){
        $list_wf = array();
    }
  }

  $comments_actions = array();

  // New comments
  //if (count($list_wf) > 0) {
    $wf_count = count($list_wf);
    $new_comments_class = $wf_count ? ' new-comments' : '';
    $btn_classes = BONITA_WF_ICON__SHOW_PROCESS_IMG . $new_comments_class;
    global $base_url;
    if(gofast_essential_is_essential()){
        $href = $base_url . "/workflow/rapiddashboard";
        $classes = array('ctools-modal-gofast-workflow-document');
    }else{
        $href = "/gofast/nojs/workflow/dashboard/{$node->nid}";
        $classes = $classes = array('ctools-use-modal ctools-modal-gofast-workflow-document');
    }
    $comment_button = array(
      'id' => 'document_wf',
      'alt' => t('Workflows', array(), array('context' => 'gofast:gofast_workflows')),
      'title' => t("Workflows", array(), array('context' => 'gofast:gofast_workflows')),
      'button-text' => $wf_count,
      'my-assigned-tasks' => $count_my_assigned_tasks ?? 0,
      'other-assigned-tasks' => $count_other_assigned_tasks ?? 0,
      'icon-class' => $btn_classes,
      'href' => $href,
      'classes' => $classes
    );
    $comments_actions[] = $comment_button;

  //}
  return $comments_actions;
}


function gofast_workflows_get_available_processes($print = true){
    $reference = $_GET["document"];
    if($reference == "cart"){
        global $user;
        $reference = "";
        $query = db_query("SELECT n.title, entity_id, flagging.entity_type, flagging_id, flagging.uid name, flagging.fid FROM flagging INNER JOIN flag ON flagging.fid = flag.fid INNER JOIN node n on n.nid = flagging.entity_id WHERE flagging.uid=".$user->uid." AND (name='cart') AND n.status = 1");
  
        foreach($query as $occur){
            $reference = $reference.$occur->entity_id . "`" . $occur->title ."|";
        }
        $reference=rtrim($reference, "|");
    }
    $html = "<div style=''>".gofast_workflows_get_html_list_available_processes(urlencode($reference))."</div>";

    if($print == true){
        print $html;
    }else{
        return $html;
    }
}

/*
 * Warning : Format param is no longer needed as we want a similar date formatting in all platform views
 */
function gofast_workflows_format_date($mydate, $format = 'd/m/y'){
    /*if($mydate == 'null'){
        return "";
    }

    try{
        $UTC = new DateTimeZone("UTC");
        $newTZ = new DateTimeZone("Europe/Paris");
        $date = new DateTime($mydate, $UTC );
        $new_date = $date->setTimezone( $newTZ );

        $return = format_date(strtotime(apachesolr_date_iso(strtotime($mydate))), 'custom', $format,$date->getOffset());

        return $return;
    }catch(Exception $e){

    }*/
    return format_date(strtotime($mydate), 'privatemsg_years');
}

function gofast_workflows_reassign_validate(){
     $data = $_POST;

    //je recupere le taskId
    $taskId = $_POST["task_id"];
    $action = $_POST["action"];
    $user_id = $_POST["new_assign_user"];
    //je verifie si la tache est bien actuellement assignée au user courant car si ce n'est pas le cas, on considere qu'il n'a pas le droit de reassigner la tache
    $task_object = gofast_workflows_get_task_object($taskId);
    //je verifie si elle est réassignable. Si non je ne fais rien
    /*$is_reassignable = theme("link_show_reassign_task_popup", $task_object);
    if($is_reassignable == false){
        $return = json_encode(array("is_reassignable" => "false"));
        print $return;
    }*/


    global $user;
    $current_bonita_uid = gofast_workflows_get_user_id($user);

     //Je recupere le parametre action.
     // S'il vaut "task" je modifie l'assignation que de la tache recu en parametre
     // S'il vaut "lane" je modifie également l'attribution de l'acteur de la lane dont fait partie la tache
     if($action == "task"){
         $return = gofast_workflows_assign_task_to_user($taskId, $current_bonita_uid);
     }elseif($action == "lane"){
         /*gofast_workflows_assign_task_to_user($taskId, $user_id);
         //je recupere dans la variable is_reassignable de la tache, quel est le nom de la variable global du processus qu'il faut mettre à jour pour changer l'acteur de la lane
         $is_reassignable = ceo_vision_workflow_get_activity_variable(BONITA_TASK_REASSIGNABLE, $taskId);
         if(isset($is_reassignable) && $is_reassignable["value"] != false){
             $variable_name_actor = str_replace("lane:", "", $is_reassignable["value"]);
             $drupal_uid = ceo_vision_bonita_get_drupalid_from_bonitaid($user_id);
             $node_author = user_load($drupal_uid);
             ceo_vision_bonita_set_case_variable($variable_name_actor, $node_author->name, $task_object["caseId"]);
         } */

     }

    $return = json_encode($return);
    print $return;
    exit;

}

function gofast_workflows_assign_task_to_user($task_id, $user_id = false){
    gofast_workflows_get_cookie(true);
    //si pas de parametre user_id, je prend celui du user courant
    if($user_id == false){
        global $user;
        $user_id = gofast_workflows_get_user_id($user);
    }

    //d'abord on déassigne la tache
    global $user;
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $data= array("assigned_id" => "");

    $url = URL_BONITA."API/bpm/humanTask/".$task_id;
    $data_string = json_encode($data);

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($data_string))
    );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);
    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT"); // note the PUT here
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);
    curl_setopt($ch, CURLOPT_URL, $url);

    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);


    //puis on la réassigne
    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";
    $data= array("assigned_id" => $user_id);

    $url = URL_BONITA."API/bpm/humanTask/".$task_id;
    $data_string = json_encode($data);

    //connect
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_HTTPHEADER, array(
        'Content-Type: application/json',
        'Content-Length: ' . strlen($data_string))
    );
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($ch, CURLOPT_VERBOSE, true);


    curl_setopt($ch, CURLOPT_POST, 1);
    curl_setopt($ch, CURLOPT_CUSTOMREQUEST, "PUT"); // note the PUT here
   // curl_setopt($ch, CURLOPT_PUT, 1);
    curl_setopt($ch, CURLOPT_POSTFIELDS, $data_string);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

    curl_setopt($ch, CURLOPT_URL, $url);

    $buf = gofast_workflows_curl_exec($ch);
    $array_results = json_decode($buf, true);

    return $array_results;
}

/**
 * @param object $profile profile fetched from the gofast_wf_profil table
 * @return object|boolean the actual profile if the current user has access to at least one space the profile belongs to, otherwise FALSE
 */
function gofast_worflows_profil_handle_space_restriction($profile) {
    global $user;
    $can_access = FALSE;
    $gids = explode(",",  $profile->gids);
    // check permissions and format spaces info
    foreach ($gids as $gid) {
        $in_space = gofast_og_get_user_final_roles_for_space("node", $gid, $user->uid);
        if ($in_space) {
            $can_access = TRUE;
        }
        $profile->spaces[] = gofast_ac_format_value_json("node", node_load($gid));
    }
    // if user is not in one of the target spaces, don't return the profile
    if ($can_access) {
        return $profile;
    }
    return FALSE;
}

function gofast_workflows_profil_get($id){
    $profile = db_select("gofast_wf_profil", "p")
        ->fields("p", array())
        ->condition("id", $id)
        ->execute()->fetchAll();
    $profile = reset($profile);
    $profile->spaces = [];
    // profile has no space restriction: return it right away
    if (strlen($profile->gids)== 0) {
        return $profile;
    }
    return gofast_worflows_profil_handle_space_restriction($profile);
}

function gofast_workflows_profil_get_all_from_type_wf($type_wf, $version = null){
    $ids = db_select("gofast_wf_profil", "p")
        ->fields("p", array("id"))
        ->condition("type_wf", $type_wf);
    if ($version) {
        $ids = $ids->condition("version_wf", $version);
    }
    $ids = $ids->execute()->fetchCol();
    $profiles = [];
    foreach ($ids as $id) {
        $profile = gofast_workflows_profil_get($id);
        if ($profile) {
            $profiles[] = $profile;
        }
    }
    return $profiles;
}

function gofast_workflows_profil_create($name, $value, $type_wf, $version_wf, $gids){
    global $user;
    $uid = $user->uid;
    db_insert("gofast_wf_profil")
        ->fields(array(
        'name' => $name,
        'gids' => $gids,
        'value' => $value,
        'type_wf' => $type_wf,
        'version_wf' => $version_wf,
        'uid' => $uid,
        ))
        ->execute();
}

function gofast_workflows_profil_edit($id, $name, $value, $type_wf, $version_wf, $gids){
    db_update("gofast_wf_profil")
        ->fields(array(
        'name' => $name,
        'gids' => $gids,
        'value' => $value,
        'type_wf' => $type_wf,
        'version_wf' => $version_wf,
        ))
        ->condition('id', $id)
        ->execute();
}

function gofast_workflows_profil_delete($id)
{
    $result = db_query("DELETE FROM {gofast_wf_profil} WHERE  id=". $id);
    return $result;
}


function gofast_workflows_parse_bonita_java_variable($variable_value){
    $list_all_signers = str_replace("=", ":" , $variable_value);
    $list_all_signers = str_replace("[", "" , $list_all_signers);
    $list_all_signers = str_replace("]", "" , $list_all_signers);
    $array_list_all_signers = explode("},", $list_all_signers );
    $final_result = array();
    foreach($array_list_all_signers as $signer){
        $signer = str_replace("{", "" , $signer);
        $signer = str_replace("}", "" , $signer);
        $array_signer = explode(",", $signer  );
        $final_array_signer = array();
        foreach( $array_signer as $data_signer){
            list($k, $v) = explode(":", $data_signer);
            $final_array_signer[ trim($k) ] = $v;
        }
        $final_result[] =  $final_array_signer;
    }
  
 return $final_result;
}

function gofast_workflows_get_user_tasks_infos($task_ids) {
    global $base_url;
    $url = $base_url . "/bonita/API/extension/getTasksAllInfos";
    $url = $url . "?" . http_build_query(array("taskids" => implode("-",$task_ids)));

    $cookie_name = "cookie_bonita".BONITA_TECHNICAL_LOGIN.".txt";

    $ch = curl_init();

    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_COOKIEFILE, "sites/default/files/swf/".$cookie_name);

    $response = curl_exec($ch);
    curl_close($ch);
    if ($response != null) {
        return $response;
    } else {
        return null;
    }
}

function gofast_workflows_get_task_type_label($task_type){
    $all_task_types = ["validate" => t("For validation", array(), array("context" => "gofast:gofast_workflows")),
                        "sign" => t("For signature", array(), array("context" => "gofast:gofast_workflows")), 
                        "contribute" => t("For contribution", array(), array("context" => "gofast:gofast_workflows")), 
                        "inform" => t("For information", array(), array("context" => "gofast:gofast_workflows")), 
                        "comment" => t("For comment", array(), array("context" => "gofast:gofast_workflows")),
                        "custom" => $task_type,
                        "sign_yousign" => t("For signature (Yousign)", array(), array("context" => "gofast:gofast_workflows")),
                        "sign_yousign_advanced" => t("For advanced signature (Yousign)", array(), array("context" => "gofast:gofast_workflows")),
                        "sign_digitalsign" => t("For signature (Digitalsign)", array(), array("context" => "gofast:gofast_workflows")),
                    ];
    if(in_array($task_type, array_keys($all_task_types))){
        return $all_task_types[$task_type];
    }
}