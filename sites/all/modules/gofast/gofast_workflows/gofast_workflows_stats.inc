<?php

/*
 * This function takes it's params from the workflow dashboard and return formatted data
 * with all the BDM processCurrent content. The purpose is to be used to generate an Excel file
 * @params : $params(array)
 * @return : array
*/
function gofast_workflows_stats_get_data($params){

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

    $output = [];

    //Retrieve the list of all cases we want to export
    $cases = gofast_api_workflows_dashboard($params, FALSE);

    foreach($cases as $case){
        $output[$case['id']] = [];
        //Get the processCurrent object of this case
        $pc_info = gofast_workflows_get_processcurrent_infos_from_pid($case['id']);
        
        $initiator = $pc_info[0]->INITIATOR;
        $processid = $pc_info[0]->PID;
        $title = $pc_info[0]->TITLE;
        preg_match('#\[(.*?)\]#', $title, $match);
        $status = $match[1];
        
        //Fill basic values
        $output[$case['id']]['#'] = $processid;
        $output[$case['id']]['Initiator'] = $initiator;
        $output[$case['id']]['Title'] = $title;
        $output[$case['id']]['Status'] = $status;
        
        $pc = gofast_workflows_get_processcurrent_from_pid($case['id']);
        foreach($pc as $pc_item){
            $type = $pc_item->TYPE;
            $name = $pc_item->NAME;
            $value = $pc_item->CONTENT_VALUE;

            //Check if the value of the processCurrent item is a json so we can parse it
            $decoded_value = json_decode($value, TRUE);
            if(json_last_error() === JSON_ERROR_NONE && is_array($decoded_value) && !empty($decoded_value)){
                //Iterrate into this JSON to retrieve values for our output
                $output[$case['id']] = $output[$case['id']] + gofast_workflows_stats_parse_data($decoded_value, $name . "_");
            }else{
                $output[$case['id']][$name] = $value;
            }
        }
    }
    
    //Call a hook to allow alteration of the data
    foreach(module_implements('alter_workflow_stats') as $module){
        $function = $module . '_alter_workflow_stats';
        $output = call_user_func_array($function, array($output));
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
function gofast_workflows_stats_parse_data($data, $prefix){
    $output = [];

    foreach($data as $key => $value) {
        if(is_array($value)) {
            $output = $output + gofast_workflows_stats_parse_data($value, $prefix . $key . '.');
        }
        else {
            $output[$prefix . $key] = $value;
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
    
    require_once libraries_get_path('excel_reader').'/Classes/PHPExcel.php';
    /** PHPExcel_Writer_Excel2007 */
    require_once libraries_get_path('excel_reader').'/Classes/PHPExcel/Writer/Excel2007.php';

    variable_set('gofast_workflows_stats_export_data', FALSE);
    $fid = rand(0, getrandmax());

    //Release Apache session
    print $fid;
    fastcgi_finish_request();

    // Create excel filename
    $filename = "export_".$fid.".xlsx";

    $params = $_POST;
    $datas = gofast_workflows_stats_get_data($params);

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
    $objPHPExcel = new PHPExcel();
    
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

    $objWriter = new PHPExcel_Writer_Excel2007($objPHPExcel);
    $objWriter->save("/var/www/d7/sites/default/files/".$filename);

    // The export is finished
    variable_set('gofast_workflows_stats_export_data', TRUE);

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
        // The export is finished
        variable_set('gofast_workflows_stats_export_data', TRUE);
        print 'Waiting'; exit;
    }
}


function excelColumnRange($lower, $upper) {
    ++$upper;
    for ($i = $lower; $i !== $upper; ++$i) {
        yield $i;
    }
}
