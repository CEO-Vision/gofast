<?php

/*
 * This function takes it's params from the workflow dashboard and return formatted data
 * with all the BDM processCurrent content. The purpose is to be used to generate an Excel file
 * @params : $params(array)
 * @return : array
*/
function gofast_workflows_stats_get_data($params, $for_export = false){
    
    global $user;
    
    $bonita_uid = gofast_workflows_get_bonitaids_from_uids(array($user->uid));
    $params = [
        'p' => 0,
        'c' => 999999999,
        'creator' => $params['creator'],
        'type' => $params['type'],
        'title' => $params['title'],
        'users' => $params['users'],
        'documents' => $params['documents'],
        'deadline' => $params['deadline'],
        'started' => $params['started'],
        'state' => $params['state'],
        'custom' => [$params['custom_0'], $params['custom_1']],
        'current_user' => $bonita_uid[0]
    ];

    $datas = [];
    //Retrieve the list of all cases we want to export
    $cases_ids = gofast_api_get_case_ids($params);
    foreach($cases_ids as $case_id){
        $datas[$case_id] = [];
        //Get the processCurrent object of this case
        $pc_info = gofast_workflows_get_processcurrent_infos_from_pid($case_id);
        
        $initiator = $pc_info[0]->INITIATOR;
        $processid = $pc_info[0]->PID;
        $title = $pc_info[0]->TITLE;
        preg_match('#\[(.*?)\]#', $title, $match);
        $status = $match[1];
        
        //Fill basic values
        $datas[$case_id]['#'] = $processid;
        $datas[$case_id]['Initiator'] = $initiator;
        $datas[$case_id]['Title'] = $title;
        $datas[$case_id]['Status'] = $status;
        
        $pc = gofast_workflows_get_processcurrent_from_pid($case_id);
        foreach($pc as $pc_item){
            $type = $pc_item->TYPE;
            $name = $pc_item->NAME;
            $value = $pc_item->CONTENT_VALUE;

            //Check if the value of the processCurrent item is a json so we can parse it
            $decoded_value = json_decode($value, TRUE);
            if(json_last_error() === JSON_ERROR_NONE && is_array($decoded_value) && !empty($decoded_value)){
                //Iterrate into this JSON to retrieve values for our output
                $datas[$case_id] = gofast_workflows_stats_parse_data($decoded_value, $name . "_", $datas[$case_id]) + $datas[$case_id];
            }else{
                if(array_key_exists($name, $datas[$case_id])){
                    $datas[$case_id][$name] .= ";" . $value;
                }else{
                    $datas[$case_id][$name] = $value;
                }
            }
        }
    }

    //Call a hook to allow alteration of the data
    foreach(module_implements('alter_workflow_stats') as $module){
        $function = $module . '_alter_workflow_stats';
        $output = call_user_func_array($function, array($datas, $params['type']));
    }

    if(empty($output) && $for_export){
        $output = $datas;
    }

    return $output;
}

/*
 * This function takes data from the function above and tries to iterrate in it
 * to return a flattened array containing the full path (usefull to get data from fields)
 * Exemple : Array['a1'][0]['fields']['b1']['value']=x becomes Array['a1.0.fields.b1.value']=x
 * This could be implemented in a more general utils file
 * @params : $data(array)
 * @params : $prefix(string) : A prefix before the final key (Ex : Array['prefix_xxx.yyy'])
 * @return : array
*/
function gofast_workflows_stats_parse_data($data, $prefix, $current_output = []){
    $output = [];

    foreach($data as $key => $value) {
        if(is_array($value)) {
            $output = $output + gofast_workflows_stats_parse_data($value, $prefix . $key . '.', $current_output);
        }
        else {
            if(array_key_exists($prefix . $key,$current_output)){
                $output[$prefix . $key] .= $current_output[$prefix . $key] . ";" . $value;
            }else{
                $output[$prefix . $key] = $value;
            }
        }
    }
    return $output;
}

/*
 * This function will export workflows data to an Excel file
 *
 * @return void
 */
function gofast_workflows_dashboard_export(){
    set_time_limit(0);
    ini_set("memory_limit", "-1");
    
  /** PHPSpreadSheet */
  require_once libraries_get_path('phpspreadsheet').'/vendor/autoload.php';
    
    $fid = rand(0, getrandmax());
    
    //Release Apache session
    print $fid;
    fastcgi_finish_request();

    // Create excel filename
    $filename = "export_".$fid.".xlsx";

    $params = $_POST;
    $datas = gofast_workflows_stats_get_data($params, true);

    $array_libelles = array();
    
    
    foreach ($datas as $matricule => $agent_data) {
        foreach($agent_data as $libelle => $value){
            
            // Insert $libelle into an array and check if it already exists
            if(!in_array($libelle, $array_libelles)){
                $array_libelles[] = $libelle;
            }
        }
    }

    
    // Create a new PHPExcel object
    $objPHPExcel = new \PhpOffice\PhpSpreadsheet\Spreadsheet();
    
    // Create excel header
    $i = 0;
    $columnRange =iterator_to_array(excelColumnRange('A', 'ZZ'));
    foreach($array_libelles as $libelle){
        $objPHPExcel->getActiveSheet()->SetCellValue($columnRange[$i].'1', $libelle);
        $i++;
    }

    // Create excel agent content
    $agent_iteration = 2;
    foreach ($datas as $caseId => $agent_data) {
        foreach($agent_data as $libelle => $value){
            
            // Get position of $libelle in the array
            $position = array_search($libelle, $array_libelles);
            
            // Insert $value into the excel cell
            $objPHPExcel->getActiveSheet()->SetCellValue($columnRange[$position]. $agent_iteration, $value);
            
        }
        // Increment
        $agent_iteration++;
    }    


    // Save Excel 2007 file

    $objWriter = new \PhpOffice\PhpSpreadsheet\Writer\Xlsx($objPHPExcel);
    $objWriter->save("/var/www/d7/sites/default/files/".$filename);
}

/*
 * This function will check if the export is finished
 */
function gofast_workflows_dashboard_export_check(){

    $fid = $_GET['fid'];
    
    // Check state of the export

    $filename = "export_".$fid.".xlsx";
    $file = '/var/www/d7/sites/default/files/'.$filename;

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
    }else{
        print 'Waiting'; exit;
    }
}


function excelColumnRange($lower, $upper) {
    ++$upper;
    for ($i = $lower; $i !== $upper; ++$i) {
        yield $i;
    }
}

/*
 * This function will generate stats for a given process
 * This is an async process so the stats have to be retrieved later using gofast_workflows_dashboard_stats_check
*/
function gofast_workflows_dashboard_stats($type, $return = FALSE, $for_export = FALSE){
    set_time_limit(0);
    ini_set("memory_limit", "-1");
    $fid = rand(0, getrandmax());
    //Release Apache session
    if(!$return){
        print $fid;
        fastcgi_finish_request();
    }
    variable_set('gofast_workflows_stats_display_' . $fid, FALSE);
    //Export data for in progress processes
    $params = [
        'type' => $type,
        'users' => [],
        'documents' => [],
        'state' => 'progress',
        'custom' => ["ignore", "ignore", "ignore"]
    ];
    $progress_datas = gofast_workflows_stats_get_data($params, $for_export);
    //Export data for finished processes
    $params = [
        'type' => $type,
        'users' => [],
        'documents' => [],
        'state' => 'finished',
        'custom' => ["ignore", "ignore", "ignore"]
    ];
    $finished_datas = gofast_workflows_stats_get_data($params, $for_export);
    
    $datas = $progress_datas+$finished_datas;
    
    //Call a hook to allow alteration of the data
    foreach(module_implements('alter_workflow_graphs_data') as $module){
        $function = $module . '_alter_workflow_graphs_data';
        $datas = call_user_func_array($function, array($datas, $type));
    }
    $output_data = [];

    // Associate content by header
    foreach ($datas as $caseId => $agent_data) {
        foreach($agent_data as $header => $value){
            $output_data[$header][] = $value;
        }
    }
    
    // Sort $datas to get a count of each value
    $sort_datas = gofast_workflows_stats_count_values_data($output_data);
    
    //Call a hook to allow alteration of the data
    foreach(module_implements('alter_workflow_graphs') as $module){
        $function = $module . '_alter_workflow_graphs';
        $sort_datas = call_user_func_array($function, array($sort_datas, $datas, $type));
    }
    
    if($return){
        return $sort_datas;
    }
    variable_set('gofast_workflows_stats_display_' . $fid, json_encode($sort_datas));
}

function gofast_workflow_dashboard_stats_display_check(){
    $fid = $_GET['fid'];
    
    if(variable_get('gofast_workflows_stats_display_'.$fid) != FALSE){
        $result = variable_get('gofast_workflows_stats_display_'.$fid);
        variable_del('gofast_workflows_stats_display_'.$fid);
        print $result; exit;
    }else{
        print 'Waiting'; exit;
    }
}

/*
 * Check the current state of statistics generation process
 * Return the statistics if ready
*/
function gofast_workflows_dashboard_stats_check(){
    $fid = $_GET['fid'];
    
    // Check state of the export

    $filename = "export_". $fid .".xlsx";
    $file = '/var/www/d7/sites/default/files/'.$filename;

    if (file_exists($file)) {
        header('Content-Description: File Transfer');
        header('Content-Type: application/octet-stream');
        header('Content-Disposition: attachment; filename='.str_replace($fid, "statistiques", basename($file)));
        header('Content-Transfer-Encoding: binary');
        header('Expires: 0');
        header('Cache-Control: must-revalidate');
        header('Pragma: public');
        header('Content-Length: ' . filesize($file));
        ob_clean();
        flush();
        readfile($file);
        exit;
    }else{
        print 'Waiting'; exit;
    }
}

/**
 * Count all workflows datas values
 *
 * @param array $datas
 * @return array $sort_datas
 */
function gofast_workflows_stats_count_values_data($datas){
    $sort_datas = array();
    
    // Reach all datas adn increment each value
    foreach ($datas as $key => $key_values) {
        foreach ($key_values as $value){
            if (array_key_exists($value, $sort_datas[$key] ?? [])){
                $sort_datas[$key][$value]++;
            } else {
                $sort_datas[$key][$value] = 1;
            }
        }
    }
    
    return $sort_datas;
}

function gofast_workflows_stats_count_values_excel_export($type){
    set_time_limit(0);
    ini_set("memory_limit", "-1");
    
    /** PHPSpreadSheet */
    require_once libraries_get_path('phpspreadsheet').'/vendor/autoload.php';

    $fid = rand(0, getrandmax());

    //Release Apache session
    print $fid;
    fastcgi_finish_request();

    // Create excel filename
    $filename = "export_".$fid.".xlsx";

    $datas = gofast_workflows_dashboard_stats($type, TRUE, TRUE);
    
    // Create a new PHPExcel object
    $objPHPExcel = new \PhpOffice\PhpSpreadsheet\Spreadsheet();
    
    // Prepare each page with specific content
    $sheet_i = 0;
    foreach ($datas as $tab_title => $content) {
        //Create a sheet for our tab
        if($sheet != 0){
            $objPHPExcel->createSheet($sheet_i);
        }
        
        //Set tab title
        $sheet = $objPHPExcel->setActiveSheetIndex($sheet_i);
        $sheet->setTitle(substr($tab_title, 0, 29)); // PHPExcel_Writer_Excel2007 doesn't support longer titles
        //Get and unset technical values
        $label = $content['label'];
        $graph_type = $content['graph_type'];
        $format_type = $content['format_type'];
        unset($content['label']);
        unset($content['graph_type']);
        unset($content['format_type']);
        
        switch($format_type){
            case 'inline':
                $i = 1;
                foreach ($content as $line_t => $line_v) {
                    $sheet->setCellValue('A' . $i, $line_t);
                    $sheet->setCellValue('B' . $i, $line_v);
                    $i++;
                }
                break;
            case 'multiple':
                $sheet->setCellValue('A0', $label);
                $ih = 1;
                $columnRange =iterator_to_array(excelColumnRange('A', 'ZZ'));
                
                foreach ($content as $line_t => $line_v) {
                    //Set top label
                    $sheet->setCellValue($columnRange[$ih] . '1', $line_t);
                    $i = 2;
                    foreach($line_v as $line_v_label => $line_v_value){
                        //Set left label
                        $sheet->setCellValue('A' . $i, $line_v_label);
                        //Set value
                        $sheet->setCellValue($columnRange[$ih] . $i, $line_v_value);
                        $i++;
                    }
                    $ih++;
                }
                break;
            default:
                //Set top label
                $sheet->setCellValue('B1', $label);
                $i = 2;
                foreach ($content as $line_t => $line_v) {
                    //Set label and value
                    $sheet->setCellValue('A' . $i, $line_t);
                    $sheet->setCellValue('B' . $i, $line_v);
                    $i++;
                }
                break;
        }
        
        $sheet_i++;
    }

    // Save Excel 2007 file

    $objWriter = new \PhpOffice\PhpSpreadsheet\Writer\Xlsx($objPHPExcel);
    $objWriter->save("/var/www/d7/sites/default/files/".$filename);

}

/*
 * Implements hook_alter_workflow_stats
 * Alter stats for Document broadcast workflows
*/ 
function gofast_workflows_alter_workflow_stats($stats, $type){
    global $base_url;
    
    if($type != "Document broadcast"){
        return [];
    }
    
    foreach($stats as $cid => &$case){
        //Unset unwanted values
        unset($case['Status']);
        unset($case['Comment']);
        unset($case['can_delete_instance']);
        unset($case['User_2']);
        unset($case['User_3']);
        unset($case['User_4']);
        
        //Process users and steps
        $users = explode(';', $case['User_0']);
        $steps = explode(';', $case['User_1']);
        
        unset($case['User_0']);
        unset($case['User_1']);
        
        foreach($users as $k => $uname){
            if(!empty($uname)){
                $case['User_' . $k] = $uname;
            }
        }
        
        //Translate steps for display
        foreach($steps as $k => $step){
            if(!empty($step)){
                switch($step){
                    case 'contribute':
                        $case['Step_' . $k] = t("For contribution", array(), array('context' => "gofast:gofast_workflows"));
                        break;
                    case 'inform':
                        $case['Step_' . $k] = t("For information", array(), array('context' => "gofast:gofast_workflows"));
                        break;
                    case 'validate':
                        $case['Step_' . $k] = t("For validation", array(), array('context' => "gofast:gofast_workflows"));
                        break;
                    case 'comment':
                        $case['Step_' . $k] = t("For comment", array(), array('context' => "gofast:gofast_workflows"));
                        break;
                    case 'custom':
                        $case['Step_' . $k] = t("Custom step", array(), array('context' => "gofast:gofast_workflows"));
                        break;
                    default:
                        if(strpos($step, "sign") !== FALSE){
                            $case['Step_' . $k] = t("For signature", array(), array('context' => "gofast:gofast_workflows"));
                        }else{
                            $case['Step_' . $k] = $step;
                        }
                }
            }
        }
        
        //Process documents
        $documents = explode(';', $case['Document']);
        unset($case['Document']);
        
        foreach($documents as $k => $nid){
            if(!empty($nid)){
                $case['Document_' . $k] = $base_url . '/node/' . trim($nid);
            }
        }
    }
    
    return $stats;
}

/*
 * Implements hook_alter_workflow_graphs
 * Alter graphs for Document broadcast workflows
*/ 
function gofast_workflows_alter_workflow_graphs($sort_datas, $datas, $type){
    if($type != "Document broadcast"){
        return [];
    }
    
    $output = [
        t("Process steps", array(), array('context' => "gofast:gofast_workflows")) => [
            t("For information", array(), array('context' => "gofast:gofast_workflows")) => 0,
            t("For comment", array(), array('context' => "gofast:gofast_workflows")) => 0,
            t("For contribution", array(), array('context' => "gofast:gofast_workflows")) => 0,
            t("For validation", array(), array('context' => "gofast:gofast_workflows")) => 0,
            t("For signature", array(), array('context' => "gofast:gofast_workflows")) => 0,
            t("Custom step", array(), array('context' => "gofast:gofast_workflows")) => 0,
            'label' => t("Process steps", array(), array('context' => "gofast:gofast_workflows")),
            'graph_type' => "bar",
        ]
    ];
    
    //count users and documents
    foreach($sort_datas as $field => $data){
        if(strpos($field, "Step") !== FALSE){
            //Add steps count
            foreach($data as $s_k => $s_val){
                $output[t("Process steps", array(), array('context' => "gofast:gofast_workflows"))][$s_k] += intval($s_val);
            }
        }
    }
    
    return $output;
}

/**
 * Get count of tasks which can be freely taken by the target user because of a userlist membership
 */
function gofast_workflows_get_userlist_tasks_count_for_user($account) {
    $userlists = gofast_userlist_get_userlists_by_user($account);
    $ulids = array_keys($userlists);
    $tasks_count = (int) gofast_workflows_get_userlist_tasks($ulids, TRUE);
    return $tasks_count;
}
