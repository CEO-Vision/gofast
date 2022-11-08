<?php


function theme_process_description($process){
    $json_description_object = $process["displayDescription"];
    $json_description_object = str_replace("\'","'", $json_description_object);
    $description_array = json_decode($json_description_object, true);
    $output = $description_array["description"];

    $return_array = array("output" => $output,"is_document" => $description_array["is_document"]);

    return $return_array;
}

function theme_link_start_process_popup($variables){
  $process = $variables['process'];
   $reference = utf8_decode($variables["reference"]);
   if(! str_ends_with(urldecode($reference), '|') ){
       $referenceListe = $reference;
   }else{
       $referenceListe = "";
   }
   $content = $variables["content"];
   $processID = $process["id"];
   $profilID = $variables["profil_id"];
   $processName =  $process["name"]."--".$process["version"]."|".t($process["name"], array(), array('context'=> 'gofast:gofast_workflow'))."/".$process["version"] ;
   $title_button = t("Start this workflow", array(), array('context' => 'gofast:gofast_workflows'));
   $output = "<span class=\"btn-process-startit-". $processID."\" onClick='Drupal.gofast_workflows.ceo_vision_js_process_startit(\"".$processID."\", \"".$processName."\", \"".str_replace("'", " ", $reference)."\", \"".$referenceListe. "\" , \"\", \"".$profilID."\")'  id='task_next_".$processID."' style='cursor:pointer;vertical-align: middle;' title='".$title_button."' >".$content."</span>";

   return $output;
}

function theme_link_start_process_popup_from_cart($variables){
   $process = $variables['process'];
   $reference = utf8_decode($variables["reference"]);
   if(! str_ends_with(urldecode($reference), '|') ){
       $referenceListe = $reference;
   }else{
       $referenceListe = "";
   }

   $content = $variables["content"];
   $processID = $process["id"];
   $profilID = $variables["profil_id"];
   $processName = $process["name"]."--".$process["version"]."|".t($process["name"], array(), array('context'=> 'gofast:gofast_workflow'))."/".$process["version"] ;
   $title_button = t("Start this workflow with documents from your cart", array(), array('context' => 'gofast:gofast_workflows'));
   $output = "<span class=\"btn-process-startit-". $processID."\" onClick='Drupal.gofast_workflows.ceo_vision_js_process_startit(\"".$processID."\", \"".$processName."\", \"".str_replace("'", " ", $reference)."\", \"".$referenceListe. "\" , \"\", \"".$profilID."\")'  id='task_next_".$processID."' style='cursor:pointer;vertical-align: middle;' title='".$title_button."' >".$content."</span>";
   return $output;
}

function theme_link_show_diagram_popup($variables){
    $process = $variables['process'];
    $style = $variables['style'];
    $processID = $process["id"];
    $processName = $process["name"]."--".$process["version"];
    $graph_name = str_replace("--", "_", $processName);
    $title_button_view = t("View this workflow diagram", array(), array('context' => 'gofast:gofast_workflows'));
    $output = "<span onClick='Drupal.gofast_workflows.ceo_vision_js_process_viewit(\"".$processID."\", \"".$graph_name."\")' "
          ." alt='View Diagram' id='process_vew_".$processID."' style='cursor:pointer;$style' title='".$title_button_view."' >"
          ."  <span class=\"".BONITA_WF_ICON__SHOW_PROCESS_IMG." gofast_wf_link\" ></span>"
          ."</span>";

    return $output;
}


function theme_task_line($variables){
    $task = $variables['task'];
    $todo_liste = $variables['todo_liste'];
    //on recupere la liste des colonnes qu'on affichera dans ce tableau
    $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task();

    //on recupere les variables du processus en cours
    $case_variables = gofast_workflows_get_case_variables_from_id($task["caseId"]);

    //on recupere l'objet du processus (case) en cours
    //$case_object = ceo_vision_workflow_api_get_case_object($task["caseId"]);
    $case_object = gofast_workflows_api_get_case_object($task["parentCaseId"]);



    $output = "<tr>";
    $i = 0;
    global $user;
    $process = $task["case_object"]["processDefinitionId"];
    foreach($array_show_fields_list_tasks as $key=>$title){
        //on affiche le bouton d'affichage des commentaires
        if($title == "__bpm_actions__"){
            //Si la tache est attribué a un user autre que le user courant (cela signifie qu'on l'affiche dans le détail d'un case) le theming est legerement different
            if($task["assigned_id"] !== gofast_workflows_get_user_id($user)){
               //$output .= "<td>".ceo_vision_get_comments_button_from_process($task["caseId"])."</td>";
            }else{
                //$output .= "<td>".ceo_vision_get_comments_button_from_process($task["caseId"]);

                $output .= "</td>";

            }
        }elseif($title == "__bpm_infos__"){
            //on recupere le html des case_variables destinées a l'utilisation (convention de nommage gofast_***)
            $output .= "<td>".theme("case_variables", array('task' => $task))."</td>";
        }elseif($title == "__processName__"){
            //on recupere le nom du processus
            $output .= "<td>".theme("link_show_diagram_popup", array('process' => $process, 'style' => "float:left;"))." ";
            //si c'est un sous processus, je recupere le nom du processus parent et pas de l'enfant

            if(isset($case_object["Id"]) && $case_object["rootCaseId"] != $case_object["Id"]){
                $root_case_object = gofast_workflows_api_get_case_object($case_object["rootCaseId"]);
                $display_name_process = $root_case_object["processDefinitionId"]["displayName"];
            }else{
                $display_name_process = $case_object["processDefinitionId"]["displayName"];
            }

            $output .= "<span title='".$display_name_process."' style='width:100px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;'>".$display_name_process."</span>";
            $output .= "</td>";
        }elseif($title == "__".BONITA_DEADLINE_PROCESS."__"  ){
            if(isset($case_variables[BONITA_DEADLINE_PROCESS]["value"]) && $case_variables[BONITA_DEADLINE_PROCESS]["value"] != 'null'){
                //TODO verif de droit avant d'afficher le onclick de changement de deadline
                $dl_value = format_date(strtotime($case_variables[BONITA_DEADLINE_PROCESS]["value"]), 'custom', 'd/m/y');
                $output .= "<td ><span onclick='ceo_vision_js_edit_deadline(\"".$case_object["rootCaseId"]."\")' title='".$dl_value."'>".$dl_value."</span></td>";
            }else{
                $output .= "<td >".t("No deadline", array(), array('context' => 'gofast:gofast_workflows'))."</td>";
            }

        }elseif($title == "__".BONITA_TITLE_PROCESS."__"){
           //on recupere dans l'objet json de la description du process si il possède un pageflow personnalisé ou non
           $description_array = json_decode($case_object["processDefinitionId"]["description"], true);
           $output .= "<td >";
           $output .= "<span class=\"gofast_wf_actions\">";
           //if($description_array["is_specific_pageflow"] == "TRUE"){
                if($task["assigned_id"] == gofast_workflows_get_user_id($user)){
                        $output .= " ".theme("link_show_pageflow_popup",array('case' => $case_object , 'process' => $case_object["rootCaseId"], 'taskId' => $task["id"],'archived' => NULL, 'style' => "margin-top:-16px;"));
                }
          // }


          $output .= theme("link_show_diagram_popup", array('process' => $process, 'style' => ''))." ";
          $output .= theme("link_show_delete_case_popup", array("case" => $case_object, "style" => "margin-top:-12px;margin-right:10px;"));
          $output .= "<span style='width:130px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;' title=\"".$case_variables[BONITA_TITLE_PROCESS]["value"]."\">".$case_variables[BONITA_TITLE_PROCESS]["value"]."</span>";
          $output .= "</span>";

          $output .= "</td>";
        }elseif($title == "__userId__"){
            //on affiche ici soit l'acteur de la tache (a qui elle est assigné) si c'est une tache assignée a quelq'un d'autre que le user courant
            //soit l'initiateur du workflow dont fait parti la tache si elle nous est assignée
            if($todo_liste == true){
                //on est dans le cas de notre todo liste donc on affiche ici l'initiateur du workflow
                if($case_object["started_by"] == 0 ){
                    $case_object = gofast_workflows_api_get_case_object($task["rootCaseId"]);
                    $task["case_object"]["started_by"] = $case_object["started_by"];

                }
                $output .= "<td >".theme("picture_bonita", array("bonita_uid" => $case_object["started_by"]));

                $output .= theme("link_show_reassign_task_popup", $task);
                $output .= "</td>";
            }else{
                //on est dans le cas de l'affichage des taches affectées a autrui dont on est l'auteur du processus
                $output .= "<td >".theme("picture_bonita", array("bonita_uid" => $task["assigned_id"])).theme("link_show_reassign_task_popup", $task)."</td>";
            }
        }elseif($title == "__".BONITA_DOCUMENT_PROCESS."__"){
            //we check if there are multiple doc into the process

             if(strpos($case_variables[BONITA_DOCUMENT_PROCESS]["value"], ";") !== FALSE){
                            $nids = explode(";", $case_variables[BONITA_DOCUMENT_PROCESS]["value"]);
                            if(count($nids) > 0){
                                 $output .= "<td><span data-nid='".$case_variables[BONITA_DOCUMENT_PROCESS]["case_id"]."' onmouseover='Drupal.gofast_workflows.showWFDocs(this)' onmouseout='Drupal.gofast_workflows.hideWFDocs(this)' class='dashboard-mail-details' id='wf_multiple_docs_".$case_variables[BONITA_DOCUMENT_PROCESS]["case_id"]."' style='display:none;position:absolute;z-index:999;margin-top:20px;'><div class='panel panel-primary'><div class='panel-heading'>".t("Documents into this process", array(), array('context' => 'gofast:gofast_workflows'))."</div><div class='panel-body'>";
                                foreach($nids as $nid){
                                    $nid = gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$nid);
                                    if($nid){
                                        $mynode = node_load($nid);
                                       // $link_node_html = "<span style='float: left; margin-top:-2px;color:#000000'></span><span style='max-width:180px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display:inline-block;'>".l($mynode->title, 'node/' . $mynode->nid, array('attributes' => array("nid" => $mynode->nid, "class" => "ajax-navigate", "title" => $mynode->title),  'html' => TRUE))."</span>";
                                       $link_node_html = "<span style='float: left; margin-top:-2px;color:#000000'></span><span style='max-width:180px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display:inline-block;'>". theme('node_title', array('node' => $mynode, "icon_size" => 24))."</span>";
                                       $link_node_html = str_replace('width="24"', 'width="16px"', $link_node_html);
                                       $link_node_html = str_replace('height="24"', 'height="16px"', $link_node_html);
                                        $output .= "<div class='deadline_box_in_rapide_todoliste' style='float:left;max-width:185px;max-height:22px;' title=\"".$mynode->title."\">".$link_node_html."</div>";
                                    }
                                }
                                 $output .= '</div></div></span><div class="deadline_box_in_rapide_todoliste" style="float:left;max-width:185px;max-height:22px;" onmouseover="Drupal.gofast_workflows.showWFDocs(this)" onmouseout="Drupal.gofast_workflows.hideWFDocs(this)" data-nid="'.$case_variables[BONITA_DOCUMENT_PROCESS]["case_id"].'"><span class="fa-file-pdf-o" title="Documents"></span>'.t("Multiple documents", array(), array("context" => "gofast:gofast_workflows")).'</div></td>';

                            }
                }else{
                    $nid = gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$case_variables[BONITA_DOCUMENT_PROCESS]["value"]);
                    if($nid){
                        $mynode = node_load($nid);
                        $link_node_html = "<span style='width:110px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;'>".theme('node_title', array('node' => $mynode, "icon_size" => 24))."</span>";
                        $link_node_html = str_replace('width="24"', 'width="18px"', $link_node_html);
                        $link_node_html = str_replace('height="24"', 'height="18px"', $link_node_html);
                        $output .= "<td>".$link_node_html."</td>";
                    }else{
                       $output .= "<td>".t("No document", array(), array('context' => 'gofast:gofast_workflows'))."</td>";
                    }
                }

        }elseif($title == "__started_date__"){
             $sd_value = format_date(strtotime($task["reached_state_date"]), 'custom', 'd/m/y');
             $output .= "<td ><span title='".$sd_value."'>".$sd_value."</span></td>";
        }else{
            if($i == 1){
                if($task["assigned_id"] == ""){
                    $bonita_user_id = "NULL";
                }else{
                    $bonita_user_id = "NULL";
                }

                 //si la tache n'est pas assignée a un utilisateur spécifique (donc assigné à un acteur et non pas un user specifique) j'indique a la fonction JS de forcer l'assignation avant l'affichage du formulaire
                if($task["assigned_id"] == "" || $task["force_assign"] == true){
                    $force_assign = "true";
                }else{
                    $force_assign = "false";
                }

                //si on est dans la TODO liste du user courant, j'attribue un evenement js sur le click du nom (afficher l'iframe de la tache)/ SInon rien
                 //if($todo_liste == true){
                 if($task["assigned_id"] == gofast_workflows_get_user_id($user)){
                        $output .= "<td><span class='gofast_workflows_title_task_doit' style='cursor:pointer;' onClick='Drupal.gofast_workflows.ceo_vision_js_task_doit(\"".$task["id"]."\", \"".str_replace("'", "\\'", $task["case_object"]["processDefinitionId"]["name"])."/".$task["case_object"]["processDefinitionId"]["version"]."\", \"".$bonita_user_id."\", \"".rawurlencode($task["name"])."\" , \"".$force_assign."\");'>".$task[$title]."</span></td>";
                 }else{
                     $output .= "<td><span>".$task[$title]."</span></td>";
                 }
            }else{
                 if($task["assigned_id"] == "" || $task["force_assign"] == true){
                        $force_assign = "true";
                 }else{
                        $force_assign = "false";
                 }
                  if($title == "displayName" && ($task["assigned_id"] == gofast_workflows_get_user_id($user) || ($task["assigned_id"] == "" && $todo_liste == true))){
                    $content = "<span class=\"".BONITA_WF_ICON__DO_ACT." gofast_wf_link\"></span>";
                    $output .= "<td>";
                    $output .= theme("link_show_taskform_popup", array("task" => $task, "content" => $content));
                    // $output .= theme("link_show_taskdescription_popup",array("task" => $task, "style" => "float:left;"));
                    $output .= "<span class='gofast_workflows_title_task_doit' task_id='task_line_".$task["caseId"]."' onClick='Drupal.gofast_workflows.ceo_vision_js_task_doit(\"".$task["id"]."\", \"".str_replace("'", "\\'", $task["case_object"]["processDefinitionId"]["name"])."/".$task["case_object"]["processDefinitionId"]["version"]."\", \"".NULL."\", \"".rawurlencode($task["name"])."\", \"".$force_assign."\");' style='cursor:pointer;width:130px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;' title='".$task[$title]."'>".$task[$title]."</span>";

                 }else{
                     $output .= "<td><span style='width:130px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;'>".$task[$title]."</span>";
                 }
                 $output .= "</td>";
            }

        }
       $i++;
    }
    $output .= "</tr>";
    return $output;
}


function theme_case_variables($variables){
    $task = $variables['task'];
    $case = $variables['case'];
    if($case == null){
        $caseId = $task["caseId"];
    }else{
        $task["processId"]["name"] = $case["name"];
        $caseId = $case["id"];
    }
    $case_variables = gofast_workflows_get_case_variables_from_id($caseId);
    $output = "<ul>";
    //tout d'abord on rajouter le nom du case
    $output .= "<li>".t("Workflow name", array(), array('context' => 'gofast:gofast_workflows'))." : ".$task["processId"]["name"]."</li>";
    if(count($case_variables) > 0){
        foreach($case_variables as $variable_name=>$variable){
            //on recupere les 7 premieres lettres du nom de la variable
            $begin_string =substr($variable_name, 0, 7);
            if($begin_string == "gofast_" && $variable_name !== "gofast_document_reference"){
                $clean_name = str_replace("gofast_", "", $variable_name);
                $clean_name = str_replace("_", " ", $clean_name);
                $output .= "<li>".$clean_name." : ".$variable["value"];
            }elseif($variable_name == "gofast_document_reference"){
                    $nid = gofast_ajax_file_browser_get_nid_from_reference("workspace://SpacesStore/".$variable["value"]);
                    if($nid){
                        $mynode = node_load($nid);
                        $link_node_html = ceo_vision_ui_get_icone_from_type($mynode)." ".l($mynode->title, 'node/' . $mynode->nid, array('attributes' => array("nid" => $mynode->nid, "class" => "ajax-navigate", "title" => $mynode->title),  'html' => TRUE));
                        $output .= "<li>".$link_node_html."</li>";
                    }
            }
        }
    }
    $output .= "</ul>";
    return $output;
}



function theme_picture_bonita($variables){
    $bonita_uid = $variables['bonita_uid'];
    $output = "";

    //on recupere le uid drupal du bonita_id recu en parametre
    $myuser = gofast_workflows_get_drupalid_from_bonitaid($bonita_uid, true);

    //$output .= theme('username', $myuser);
    //$output .= theme('username', array('account' => $myuser, 'popup' => TRUE));
    $output .= theme('user_picture', array('account' => $myuser, 'dimensions' => 20));
    return $output;
}

function theme_link_show_actives_tasklist_from_process_popup($variables){
    $processId = $variables['processId'];
    $title_button_view = t("View active tasks from this process", array(), array('context' => 'gofast:gofast_workflows'));
    $list_actives_tasks = gofast_workflows_get_list_actives_tasks(false, $processId, false, true);
    $output = count($list_actives_tasks);
    if(count($list_actives_tasks) !== 0){
      $output .= " <span onClick='Drupal.gofast_workflows.ceo_vision_js_process_get_actives_tasklist(\"".$processId."\")' "
              ." alt='edit' id='task_view_".$processId."' style='cursor:pointer;' title='".$title_button_view."' >"
              ."  <span class='".BONITA_WF_ICON__SEE_TODO_ACT." gofast_wf_link'></span>"
              ."</span>";

    }

    return $output;
}


function theme_link_show_delete_case_popup($variables){
    if(!isset($variables["case"])){
        return "";
    }
    $case = $variables["case"];
    if(!isset($variables["style"])){
       $style = "";
    }else{
       $style = $variables["style"];
    }
    if($case["started_by"] == 0 ){
        $case = gofast_workflows_api_get_case_object($case["rootCaseId"]);
        $case["case_object"]["started_by"] = $case["started_by"];

    }
    global $user;
    $bonita_user_id = gofast_workflows_get_user_id($user);
    $output = "";

    if($bonita_user_id == $case["started_by"]){
        $title_button_view = t("Delete this process");
       if(current_path() == "workflow/dashboard"){
         $output .= "<span onClick='Drupal.gofast_workflows.ceo_vision_js_delete_task(\"".$case["rootCaseId"]."\");'"
                    ."alt='delete' class='workflow_remove_process' style='cursor:pointer;".$style."' title='".$title_button_view."' >"
                    ."  <span class=\"".BONITA_WF_ICON__DELETE_PROCESS." gofast_wf_link\"></span>"
                    ."</span>";
       }else{
         $output .= "<span onClick='Drupal.gofast_workflows.ceo_vision_js_delete_task(\"".$case["rootCaseId"]."\");'"
                    ."alt='delete' class='workflow_remove_process' style='cursor:pointer;".$style."' title='".$title_button_view."' >"
                    ."  <button type='button' class='btn btn-default wf-button wf-button-red'><span class=\"".BONITA_WF_ICON__DELETE_PROCESS." gofast_wf_link\"></span></button>"
                    ."</span>";
       }


    }
    return $output;
}

function theme_link_show_finished_tasklist_from_process_popup($variables){
    $processId = $variables['processId'];
    $title_button_view = t("View finished tasks from this process", array(), array('context' => 'gofast:gofast_workflows'));
    $list_actives_tasks = gofast_workflows_get_list_actives_tasks(true, $processId, false, false);
    $output = count($list_actives_tasks);
  //  if(count($list_actives_tasks) !== 0){
          $output .= " <span onClick='Drupal.gofast_workflows.ceo_vision_js_process_get_finished_tasklist(\"".$processId."\")' "
              ." alt='edit' id='task_view_".$processId."' style='cursor:pointer;' title='".$title_button_view."' >"
              ."  <span class='".BONITA_WF_ICON__SEE_DONE_ACT." gofast_wf_link'></span>"
              ."</span>";

   // }

    return $output;
}


function theme_link_show_finished_tasklist_archived_from_process_popup($variables){
    $processId = $variables["processId"];
    $title_button_view = t("View tasks history from this archived process", array(), array('context' => 'gofast:gofast_workflows'));
    $list_actives_tasks = gofast_workflows_get_list_actives_tasks(true, $processId, false, false);
    $output = count($list_actives_tasks);
   // if(count($list_actives_tasks) !== 0){
          $output .= " <span onClick='Drupal.gofast_workflows.ceo_vision_js_process_get_finished_tasklist(\"".$processId."\", \"true\")' "
              ." alt='edit' id='task_view_".$processId."' style='cursor:pointer;' title='".$title_button_view."' >"
              ."  <span class='".BONITA_WF_ICON__SEE_DONE_ACT." gofast_wf_link'></span>"
              ."</span>";

    //}

    return $output;
}


function theme_task_line_archived($task, $todo_liste = true){
    //on recupere la liste des colonnes qu'on affichera dans ce tableau
    $array_show_fields_list_tasks = gofast_workflows_get_show_fields_list_task_archived();

    $output = "<tr>";
    $i = 0;
    global $user;
    $process = $task["case_object"]["processDefinitionId"];

    foreach($array_show_fields_list_tasks as $key=>$title){
        if($title == "__userId__"){
            $output .= "<td >".theme("picture_bonita",array("bonita_uid" => $task["assigned_id"]))."</td>";
        }elseif($title == "__started_date__"){
             $output .= "<td >".$task["reached_state_date"]."</td>";
        }elseif($title == "__finished_date__"){
             $output .= "<td >".$task["archivedDate"]."</td>";
        }
        else{
              $output .= "<td>".$task[$title];
              $output .= "</td>";


        }
       $i++;
    }
    $output .= "</tr>";
    return $output;
}

function theme_link_show_taskform_popup($variables){
    if(!isset($variables["task"])){
        return "";
    }
    $task = $variables["task"];
    $content = $variables["content"];
    //si la tache n'est pas assignée a un utilisateur spécifique (donc assigné à un acteur et non pas un user specifique) j'indique a la fonction JS de forcer l'assignation avant l'affichage du formulaire
    if($task["assigned_id"] == true || $task["force_assign"] == true){
        $force_assign = "true";
    }else{
        $force_assign = "false";
    }

    $output = "<span class='gofast_workflows_title_task_doit' style='cursor:pointer;' "
            . "onClick='Drupal.gofast_workflows.ceo_vision_js_task_doit(\"".$task["id"]."\", \"".str_replace("'", "\\'", $task["case_object"]["processDefinitionId"]["name"])."/".$task["case_object"]["processDefinitionId"]["version"]."\", \"".NULL."\", \"".rawurlencode($task["name"])."\", \"".$force_assign."\");' "
            . "title='".t("Execute the task", array(), array('context' => 'gofast:gofast_workflows'))."' >".$content."</span>";
    return $output;
}


function theme_link_show_taskdescription_popup($variables){
    if(!isset($variables["task"])){
        return "";
    }
    $task = $variables["task"];
    $style = $variables["style"];
    $output = "<span style='cursor:pointer;".$style."' "
        . "title=\"".t($task["displayDescription"], array(), array('context' => 'gofast:gofast_workflows'))."\" >"
        . "<span class=\"gofast_wf_link ".BONITA_WF_ICON__SEE_RESUME."\" ></span> "
        . "</span>";
    return $output;
}


function theme_link_show_pageflow_popup($variables){
    if(!isset($variables["case"])){
        return "";
    }


    $case = $variables["case"];
    $taskId = $variables["taskId"];
    $archived = $variables["archived"];
    $style = $variables["style"];

    if($archived == false){
        if($case["rootCaseId"] !== $case["id"]){
            //on est dans le cas d'un sous-processus
            $old_case = $case;
            $case = gofast_workflows_api_get_case_object($case["rootCaseId"]);

           // $case = ceo_vision_workflow_api_get_case_object($case["rootCaseId"]);
            $case_id = $case["id"];
        }else{
            $case_id = $case["id"];
        }
    }else{
         $case_id = $case["rootCaseId"];
    }

    global $user;
    $output = "";
    $bonita_id = gofast_workflows_get_user_id($user);
    //$bonita_id = ceo_vision_bonita_get_user_id($user);
    if($bonita_id !== $case['started_by'] && $archived == true){
        $output .= "";
    }else{
      if(current_path() == "workflow/dashboard"){
        $output .= "<span style='cursor:pointer;$style'"
                . " onClick='Drupal.gofast_workflows.ceo_vision_js_process_pageflow(\"".$case["processDefinitionId"]["name"]."\", \"".$case["processDefinitionId"]["version"]."\", \"".$case_id."\", \"".$taskId."\");' "
                . " title='".t("Show the resume", array(), array('context' => 'gofast:gofast_workflows'))."' >"
                . " <span class=\"".BONITA_WF_ICON__SEE_RESUME." gofast_wf_link\"></span> "
                . " </span> ";
      }else{
        $output .= "<span style='cursor:pointer;$style'"
                . " onClick='Drupal.gofast_workflows.ceo_vision_js_process_pageflow(\"".$case["processDefinitionId"]["name"]."\", \"".$case["processDefinitionId"]["version"]."\", \"".$case_id."\", \"".$taskId."\");' "
                . " title='".t("Show the resume", array(), array('context' => 'gofast:gofast_workflows'))."' >"
                . " <button type='button' class='btn btn-default wf-button wf-button-blue'><span class=\"".BONITA_WF_ICON__SEE_RESUME." gofast_wf_link\"></span></button> "
                . " </span> ";
      }
    }

    return $output;

}

function ceo_vision_get_ajax_theme_icone_node($node){

    $node_workflow_action = gofast_get_workflow_action_node($node);
    $workflow_action = theme('contextual_links', array('btn_group_id' => 'breadcrumb-alt-wf', 'buttons' => $node_workflow_action));    
    
    //Set the workflow count in the context
    $context['workflows_document'] = $node_workflow_action[0]['button-text'];    
    $new_context = gofast_set_context($context);
    drupal_json_output(array("action" => $workflow_action, "context" => $new_context));
    exit;
   
}

