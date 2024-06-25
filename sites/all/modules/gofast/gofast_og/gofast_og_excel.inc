<?php
include_once __DIR__ . '/gofast_og.bulk.inc';

define('GOFAST_OG_EXCEL_NOT_MEMBER', 'not member');
define('GOFAST_OG_EXCEL_RO', 'RO');
define('GOFAST_OG_EXCEL_ADMIN', 'ADMIN');
define('GOFAST_OG_EXCEL_STANDARD', 'RW');

function gofast_og_mass_users_import_interface(){
    $form = drupal_render(drupal_get_form("gofast_og_mass_users_importform")); 
    $output = '<div class="container-fluid h-100 py-0" id="kt_content"><div class="gofast-content h-100"><div id="gofastContainer" class="gofast-content--full mainContent fullScreen"><div class="mainContent">'; 
    $output .= '<div class="card card-custom GofastForm__CardContainer"><div class="card-body">'; 
    $output .= $form; 
    $output .= '</div></div></div></div></div></div>'; 
    return $output;  
}

function gofast_og_mass_users_importform($form,&$form_state){
    $form['#attributes']['enctype'] = 'multipart/form-data';
    
    $form["action"] = array(
        '#type' => 'select',
        '#title' => t('Action'),                  
        '#options' => array("0" => t("Import file", array(), array("context" => "gofast")), "1" => t("Export simple file", array(), array("context" => "gofast")), "2" => t("Export complete file", array(), array("context" => "gofast"))),
        '#required' => true,        
        '#multiple' => false,       
      );
    
   /* $form["file"] = array(
        '#type'   => "file",
        '#title' => t('XLS File'),
        '#size' => 20,       
        //'#description' => t('The XLS file containing one line per document to fill'),
        '#required' => FALSE,
        '#upload_validators'  => array("file_validate_extensions" => array("xlsx")),
        '#attributes' => array('style' => array('padding:0px 0px;'))
    );*/
    $form["file"] = array(
    '#type' => 'file',
    '#title' => t('Choose a file', array(), array('context' => 'gofast:gofast_cmis')),
    '#description' => t('Maximum size : !filesize', array('!filesize' => '35M'), array('context' => 'gofast')),
    '#default_value' => isset($form['#node']->reference) ? $form['#node']->reference : '',
    '#required' => FALSE,
    '#size' => 20,
    '#suffix' => theme('gofast_cmis_upload_suffix'),
    '#upload_validators'  => array("file_validate_extensions" => array("xlsx")),
    );

    $attributes = [    
        'class' => [' form-control-tags js-tagify'],    
        'data-get-spaces' => '',
        'data-exclude-root-spaces' => '', 
        'data-user' => ''
      ]; 
     $form["space"] = array(
      '#title' => t("Space or users", array(), array("context" => "gofast")),
      '#type' => 'textfield',
      '#default_value' => "",
      '#maxlength' => '', // no maxlength
      '#attributes' => $attributes,
      '#name' => 'ac-list-tags-list-spaces',
      );
     
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t("Save"),
      '#submit' => array('gofast_og_mass_users_importform_submit'),
      '#weight' => 2,
     
   );
    
    return $form;
}

function gofast_og_mass_users_importform_validate($form,&$form_state){
    $action = $form_state["values"]["action"];

    //export action
    if($action == 0){
        $validators = array();
        $validators['file_validate_extensions'] = array();
        $file = file_save_upload('file', $validators, "public://", FILE_EXISTS_REPLACE);
        if($file == NULL){
                form_set_error("file", t("You must select a file", array(),array("context" => "gofast")));
        }

     }
  $errors = form_get_errors();
  if(!empty($errors)){
       drupal_goto("og/excel/manage");
       exit;
        return $form;
  }
}

function gofast_og_mass_users_import_file_decode($file){
    set_time_limit(3000);
   
    /** PHPSpreadSheet */
    require_once libraries_get_path('phpspreadsheet').'/vendor/autoload.php';
    $file_path = file_stream_wrapper_get_instance_by_uri('public://')->realpath();
    $objPHPExcel = \PhpOffice\PhpSpreadsheet\IOFactory::load($file_path."/".$file->filename);
    $sheet = $objPHPExcel->getSheet(0);
    
    $data = array();
    
    foreach($sheet->getRowIterator() as $key_row=>$row) {
     
        $gid = 0;
        $login = "";
        foreach ($row->getCellIterator() as $key_cell=>$cell) {          
                 switch($key_cell){
                    case 'A':
                        $login = $cell->getValue();                      
                    break;
                    case "H":
                        $group_id = $cell->getValue();
                        if($group_id !== ""){
                            $group = node_load($group_id);                         
                            if(isset($group->nid)){
                                $gid = $group->nid;
                                $data[$login][$gid]["gid"] = $gid;
                                $data[$login][$gid]["title"] = $group->title;
                            }
                        }
                     case "J":
                        $permission = $cell->getValue();
                        $data[$login][$gid]["permission"] = gofast_og_excel_get_role_name_from_alias($permission);
                    case "K":
                        $modification = $cell->getValue();
                        if($modification == "0"){
                            unset($data[$login][$gid]);
                        }
                    break;
                }
        }
    }
    $data_converted = array();
    if(count((array)$data) > 0){
        foreach($data as $login=>$infos){
            if($login != "Login" && count((array)$infos) > 0){
                $data_converted[] = array($login=>$infos);
            }
        }
    }
    file_delete($file);
    drupal_unlink($file_path."/".$file->filename);
    return $data_converted;
}

function gofast_og_mass_users_importform_submit($form,&$form_state){    
  set_time_limit(3000);
    $action = $form_state["values"]["action"];
    $spaces = $form_state["values"]["space"];
    $array_spaces = json_decode($form_state['input']['ac-list-tags-list-spaces']);
    
    //export action
    if($action == 1){
      //export simple
       $_GET["export_type"] = "mini";
       $_GET["spaces"] = $array_spaces;
        //import 
        $batch = array(
        'title' => 'Construction de la liste',
        'operations' => array(
          array('gofast_og_batch_excel_users_file', array($array_spaces, $_GET["export_type"])),
        ),
        'finished' => 'gofast_og_batch_excel_users_file_finished', 
        'progress_message' => "",
      );
    }elseif($action == 2){
      //export full
      $batch = array(
        'title' => 'Construction de la liste',
        'operations' => array(
          array('gofast_og_batch_excel_users_file', array($array_spaces, "full")),
        ),
        'finished' => 'gofast_og_batch_excel_users_file_finished', 
        'progress_message' => "",
      );
    }else{
        //import    
        $validators = array();
        $validators['file_validate_extensions'] = array();
        $file = file_save_upload('file', $validators, "public://");
        
      
       // var_dump(file_get_contents($file->uri));
        $data = gofast_og_mass_users_import_file_decode($file);
    
        $batch = array(
        'title' => 'Import de la liste',
        'operations' => array(
            array('gofast_og_batch_excel_users_file_import', array($data)),
        ),
        'finished' => 'gofast_og_batch_excel_users_file_import_finished', 
        'progress_message' => "",
      );
    }
    

    batch_set($batch);
    // Only needed if not inside a form _submit handler.
    // Setting redirect in batch_process.
    batch_process("node");

}

function gofast_og_batch_excel_users_file($array_spaces,$type,&$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    if(count((array)$array_spaces) == 0){
        $query = db_select('users', 'u')
                ->fields('u', array('name', 'uid'))
                ->condition('status', 1)
                ->condition('uid', 0, '<>')
                ->condition('uid', 1, '<>')
                ->execute();
        $all_uids = $query->fetchAll();
    }else{
        $all_uids = array();
        foreach($array_spaces as $array_space){
             if($array_space->type == "node"){
                $all_uids = array_merge_recursive(gofast_og_get_members(node_load($array_space->value)), $all_uids);
            }else{
                 $all_uids[] = $array_space->value;
            }
        }
        $all_uids = array_unique($all_uids);
    }
    
    $context['sandbox']['max'] = count($all_uids);
  }

  
 if(count((array)$array_spaces) == 0){
        $query = db_select('users', 'u')
                ->fields('u', array('name', 'uid'))
                ->condition('status', 1)
                ->condition('uid', 0, '<>')
                ->condition('uid', 1, '<>')
                ->execute();
        $all_uids = $query->fetchAll();
 }else{
         $all_uids = array();
        foreach($array_spaces as $array_space){
            if($array_space->type == "node"){
                $all_uids = array_merge_recursive(gofast_og_get_members(node_load($array_space->value)), $all_uids);
            }else{
                 $all_uids[] = $array_space->value;
            }
        }
        $all_uids = array_unique($all_uids);
 }
  $limit = 10;
  $cut_all_uids = array_slice($all_uids,$context['sandbox']['current_node'], $limit, true);

  //$context['results']["params"] = array("gids" => $array_spaces);
   $all_og = array();
   if($type == "full"){       
        $bundles = gofast_og_node_types();
        unset($bundles['private_space']);
        foreach (gofast_og_get_spaces_by_bundle(array_keys($bundles)) as $space_bundle) {
          $bundle_ogs = array_combine(array_keys($space_bundle), array_keys($space_bundle));
          $all_og += $bundle_ogs;
        }             
    }
  
  foreach($cut_all_uids as $key => $uid){   
     if(isset($uid->uid)){
       $myuser = user_load($uid->uid);  
     }else{ 
       $myuser = user_load($uid);
     }
   
     if($myuser->status == 0){
         $context['sandbox']['progress']++;
        $context['sandbox']['current_node'] = $key+1;
        continue;
     }
     
    if(count((array)$all_og) == 0){
     //iterate all spaces the user is member of
     foreach($myuser->og_user_node[LANGUAGE_NONE] as $group_object){     
        $space = node_load($group_object["target_id"]);
        if(!gofast_og_is_root_space($space) && $space->type != "alfresco_item" && isset($space->nid)){ 
            $user_object = new stdClass();
            $user_object->name = $myuser->name;
            $user_object->firstname = $myuser->ldap_user_givenname[LANGUAGE_NONE][0]["value"];
            $user_object->lastname = $myuser->ldap_user_sn[LANGUAGE_NONE][0]["value"];
            $user_object->status = $myuser->status;
            $user_object->date_login = format_date($myuser->login, 'custom', 'd/m/Y H:i');
            $ou_gid = gofast_ldap_gid_from_dn('cn=' . $myuser->ldap_user_ou[LANGUAGE_NONE][0]['value']);
            $user_object->ou = gofast_get_node_title($ou_gid);     
            $array_infos["user"] = $user_object;
            $space_object = new stdClass();
            $space_object->title = $space->title;
            $space_object->type = $space->type;
            $space_object->nid = $space->nid;
            $roles = gofast_og_get_user_roles($group_object["target_id"], $myuser->uid);
            if(gofast_og_excel_get_alias_from_role_name(array_values($roles)[0]) !== GOFAST_OG_EXCEL_NOT_MEMBER){
                $space_object->role =  gofast_og_excel_get_alias_from_role_name(array_values($roles)[0]);
                $array_infos["group"] = $space_object;
                $context['results'][] = $array_infos ;       
                $context['message'] = $myuser->name;
            }else{
                $space_object->role =  GOFAST_OG_EXCEL_RO;
                $array_infos["group"] = $space_object;
                $context['results'][] = $array_infos ;       
                $context['message'] = $myuser->name;
            }
        }       
      
     }       
    }else{
       //iterate all spaces 
        foreach($all_og as $gid){
            $space = node_load($gid);          
            if(!gofast_og_is_root_space($space)){ 
                $user_object = new stdClass();
                $user_object->name = $myuser->name;
                $user_object->firstname = $myuser->ldap_user_givenname[LANGUAGE_NONE][0]["value"];
                $user_object->lastname = $myuser->ldap_user_sn[LANGUAGE_NONE][0]["value"];
                $user_object->status = $myuser->status;
                $user_object->date_login = format_date($myuser->login, 'custom', 'd/m/Y H:i');
                $ou_gid = gofast_ldap_gid_from_dn('cn=' . $myuser->ldap_user_ou[LANGUAGE_NONE][0]['value']);
                $user_object->ou = gofast_get_node_title($ou_gid);      
                $array_infos["user"] = $user_object;
                $space_object = new stdClass();
                $space_object->title = $space->title;
                $space_object->type = $space->type;
                $space_object->nid = $space->nid;
                $roles = gofast_og_get_user_roles($gid, $myuser->uid);
                $space_object->role =  gofast_og_excel_get_alias_from_role_name(array_values($roles)[0]);
                $array_infos["group"] = $space_object;
                $context['results'][] = $array_infos ;          
                $context['message'] = $myuser->name;
            }       
            
        }
    }
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $key+1;
  }
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}


function gofast_og_batch_excel_users_file_finished($success, $results, $operations){
    ini_set("memory_limit", "1024M");
    set_time_limit(3000);
    /** PHPSpreadSheet */
    require_once libraries_get_path('phpspreadsheet').'/vendor/autoload.php';

    $filename = "liste_users";

    $objPHPExcel = new \PhpOffice\PhpSpreadsheet\Spreadsheet();
    $objPHPExcel->setActiveSheetIndex(0);
    $objPHPExcel->getActiveSheet()->SetCellValue('A1', "Login");
    $objPHPExcel->getActiveSheet()->SetCellValue('B1', "Nom");
    $objPHPExcel->getActiveSheet()->SetCellValue('C1', "Prénom");
    $objPHPExcel->getActiveSheet()->SetCellValue('D1', "Statut");
    $objPHPExcel->getActiveSheet()->SetCellValue('E1', "Dernière connection");
    $objPHPExcel->getActiveSheet()->SetCellValue('F1', "Organisation principale");
    $objPHPExcel->getActiveSheet()->SetCellValue('G1', "Nom de l'espace collaboratif");
    $objPHPExcel->getActiveSheet()->SetCellValue('H1', "ID de l'espace collaboratif");
    $objPHPExcel->getActiveSheet()->SetCellValue('I1', "Type d'espace collaboratif");
    $objPHPExcel->getActiveSheet()->SetCellValue('J1', "Droits");
    $objPHPExcel->getActiveSheet()->SetCellValue('K1', "Modification");

    $i=2;
    foreach($results as $result){
      
        $account = $result["user"];
        $group = $result["group"]; 
        
        $objPHPExcel->getActiveSheet()->SetCellValue('A'.$i, $account->name);
        $objPHPExcel->getActiveSheet()->SetCellValue('B'.$i, $account->lastname);
        $objPHPExcel->getActiveSheet()->SetCellValue('C'.$i, $account->firstname);
        $objPHPExcel->getActiveSheet()->SetCellValue('D'.$i, $account->status);
        $objPHPExcel->getActiveSheet()->SetCellValue('E'.$i, $account->date_login);
        $objPHPExcel->getActiveSheet()->SetCellValue('F'.$i, $account->ou);
        $objPHPExcel->getActiveSheet()->SetCellValue('G'.$i, $group->title);
        $objPHPExcel->getActiveSheet()->SetCellValue('H'.$i, $group->nid);
        $objPHPExcel->getActiveSheet()->SetCellValue('I'.$i, t($group->type));
        $objPHPExcel->getActiveSheet()->SetCellValue('J'.$i, $group->role);
        $objPHPExcel->getActiveSheet()->SetCellValue('K'.$i, 0);
        $i++;     
    }
    $objWriter = new \PhpOffice\PhpSpreadsheet\Writer\Xlsx($objPHPExcel);
    $objWriter->save("/var/tmp/$filename.xlsx");
    
      $file = "/var/tmp/$filename.xlsx";

    if (file_exists($file)) {
        header('Content-Description: File Transfer');
        header('Content-Type: application/octet-stream');
        header('Content-Disposition: attachment; filename='.basename($file));
        header('Content-Transfer-Encoding: binary');
        header('Expires: 0');
        header('Cache-Control: must-revalidate');
        header('Pragma: public');
        header('Content-Length: ' . filesize($file));
        ob_clean();
        flush();
        readfile($file);
        exit;
    }
}





function gofast_og_batch_excel_users_file_import($data,&$context) {

  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0; 
    $context['sandbox']['max'] = count((array)$data);
  }


  $limit = 1;
  $cut_all_uids = array_slice($data,$context['sandbox']['current_node'], $limit, true);
  
  foreach($cut_all_uids as $key => $uid){ 
    //we get roles info for each user and for each spaces
    $login = key($uid);
    $myuser = user_load_by_name($login);
    $gids = array();
    foreach($uid[$login] as $infos){       
        $gids[$infos["gid"]] = array("role" => $infos["permission"], "space_name" => $infos["title"]);
    }

    if(count((array)$gids) > 0){
        //manage user role on each space
        foreach($gids as $gid => $role_info){  
             // check if gid really exists
             $node = node_load($gid);
             if(!isset($node->nid)){
               continue;
             }        
            //get current role on the current space for this user
            $current_role = og_get_user_roles('node', $gid, $myuser->uid, FALSE, TRUE);           
            if( array_shift(array_values($current_role)) == $role_info["role"]){
                 $context['results'][] = t("The user !user_name already have role !role into the space !space_name", array('!user_name' => $myuser->name, '!role' => $role_info["role"], "!space_name" => $role_info["space_name"]), array("context" => "gofast"));
            }else{
                //check if we must remove the user from the space
                if($role_info["role"] == GOFAST_OG_EXCEL_NOT_MEMBER){
                     global $must_propagate;
                    $must_propagate = false;
                     gofast_og_space_admin_delete_membership($gid, $myuser->uid);                      
                     $must_propagate = true;
                     $context['results'][] = t("The user !user_name has been removed from the space !space_name", array('!user_name' => $myuser->name, "!space_name" => $role_info["space_name"]), array("context" => "gofast"));
                }else{
                    //change or add role 
                    $og_role = gofast_og_space_admin_get_node_role('node', $gid, $role_info["role"]);
                    $og_role_id = key($og_role);             
                    $membership = og_get_membership('node', $gid, 'user', $myuser->uid);              
                    if( ! $membership ){
                       gofast_og_space_admin_add_membership($gid, $myuser->uid, $og_role_id);
                       $context['results'][] = t("The user !user_name' has been added into space !space_name with role !new_role", array('!user_name' => $myuser->name,"!new_role" => $role_info["role"], "!space_name" => $role_info["space_name"]), array("context" => "gofast"));                                     
                     }else{
                         gofast_og_space_admin_update_membership($gid, $myuser->uid, $role_info["role"]); 
                         $context['results'][] = t("The role of user !user_name' has been changed from !current_role to !new_role into space !space_name", array('!user_name' => $myuser->name,'!current_role' => array_shift(array_values($current_role)), "!new_role" => $role_info["role"], "!space_name" => $role_info["space_name"]), array("context" => "gofast"));                        
                     }
                }
            }
        }        
    }
   
    $context['message'] = $myuser->name;      
   
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $key+1;
  }
  
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}


function gofast_og_batch_excel_users_file_import_finished($success, $results, $operations){   
    set_time_limit(3000);
    /** PHPSpreadSheet */
    require_once libraries_get_path('phpspreadsheet').'/vendor/autoload.php';

    $filename = "result_import_liste_users";

    $objPHPExcel = new \PhpOffice\PhpSpreadsheet\Spreadsheet();
    $objPHPExcel->setActiveSheetIndex(0);
    $objPHPExcel->getActiveSheet()->SetCellValue('A1', "Login");
  

    $i=2;
    foreach($results as $result){       
        $objPHPExcel->getActiveSheet()->SetCellValue('A'.$i, $result);    
        $i++;     
    }
    $objWriter = new \PhpOffice\PhpSpreadsheet\Writer\Xlsx($objPHPExcel);
    $objWriter->save("/var/tmp/$filename.xlsx");
    
      $file = "/var/tmp/$filename.xlsx";

    if (file_exists($file)) {
        header('Content-Description: File Transfer');
        header('Content-Type: application/octet-stream');
        header('Content-Disposition: attachment; filename='.basename($file));
        header('Content-Transfer-Encoding: binary');
        header('Expires: 0');
        header('Cache-Control: must-revalidate');
        header('Pragma: public');
        header('Content-Length: ' . filesize($file));
        ob_clean();
        flush();
        readfile($file);
        exit;
    }
}

function gofast_og_excel_get_role_name_from_alias($alias){
    switch($alias){
      case GOFAST_OG_EXCEL_NOT_MEMBER: 
            return GOFAST_OG_EXCEL_NOT_MEMBER;
            break;
      case GOFAST_OG_EXCEL_RO:
          return 'read only member';
          break;
      case GOFAST_OG_EXCEL_ADMIN:
          return 'administrator member';
          break;
      case GOFAST_OG_EXCEL_STANDARD:
          return 'group contributor';
          break;
    } 
}

function gofast_og_excel_get_alias_from_role_name($role_name){
    switch($role_name){
      case GOFAST_OG_EXCEL_NOT_MEMBER: 
            return GOFAST_OG_EXCEL_NOT_MEMBER;
            break;
      case 'read only member':
          return GOFAST_OG_EXCEL_RO;
          break;
      case 'administrator member' :
          return GOFAST_OG_EXCEL_ADMIN;
          break;
      case 'group contributor':
          return GOFAST_OG_EXCEL_STANDARD;
          break;
      default:
          return GOFAST_OG_EXCEL_NOT_MEMBER;
          break; 
    } 
}



