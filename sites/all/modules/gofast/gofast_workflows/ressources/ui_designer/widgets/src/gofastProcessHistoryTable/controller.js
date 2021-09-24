function PbTableCtrl($scope, $http, $sce, $filter) {
     $scope.final_content = [];

     $scope.$watch("properties.instancesIds", function(){
          if(typeof $scope.properties.instancesIds == "undefined"){
              return;
          }
         
           for (var property in $scope.properties.instancesIds) {
                if ($scope.properties.instancesIds.hasOwnProperty(property)) {
                       //load process object manually
                    $http.get("/bonita/API/bdm/businessData/com.company.model.ProcessHistory/"+$scope.properties.instancesIds[property].persistenceId).then( 
                        function successCallback(response) {
                            var processObject = new Object();
                            processObject.title = response.data.title;
                            processObject.start_date = response.data.start_date;
                            processObject.deadline = get_deadline_html(response, processObject);
                            processObject.actor = get_initiator_html(response, processObject);
                            processObject.persistenceId = response.data.persistenceId;
                            processObject.finished_date = get_finished_date(response);
                            $scope.final_content.push(processObject);
                        }
                    );
           }   
         }
    
     } );        

  this.isArray = Array.isArray;

 function get_finished_date(ProcessHistory){

       var last_line = ProcessHistory.data.lines[ProcessHistory.data.lines.length-1];
       var finished_date = last_line.line_date;
       return finished_date;
 }

  function get_initiator_html(myProcessHistory, myTask){
      var initiator_string = myProcessHistory.data.initiator;
      var url = "/api/user/picture?username="+initiator_string;
       $http.get(url).then( 
                   function successCallback(response) {
                        var label_actor = $filter('gfTranslateHistory')("label.started_by");
                        myTask.actor = $sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                   }    
            );  
  }
  
    $scope.ceo_vision_js_process_pageflow = function(){
      var row = $scope.properties.selectedRow;
      console.log(row);
      window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_process_pageflow("bdm", "", row.persistenceId,"");
      
  };

  this.isClickable = function () {
    return $scope.properties.isBound('selectedRow');
  };

  this.selectRow = function (row) {
    if (this.isClickable()) {
      $scope.properties.selectedRow = row;
    }
  };
  
    function get_deadline_html(processVariables, myTask){
      var d = new Date(processVariables.end_date);
      var timestamp_now = new Date().getTime() / 1000;
      var timestamp = d.getTime() / 1000;
      
      if(timestamp_now > timestamp){
           var label_deadline = $filter('gfTranslateHistory')("label.process_outdated");
           myTask.deadline_description = label_deadline;
           myTask.deadline_color = "#c0392b";
       }else if(timestamp - timestamp_now < 60*60*24){
           var label_deadline = $filter('gfTranslateHistory')("label.process_soon_outdated");
           myTask.deadline_description = label_deadline;
           myTask.deadline_color = "#d35400";
       }else{
           myTask.deadline_description = "";
           myTask.deadline_color = "#2ecc71";
       }
      
    myTask.has_deadline = true;
    if(processVariables.end_date === null || typeof processVariables.end_date == "undefined"){
        processVariables.end_date = " / ";
        myTask.has_deadline = false;
    }
      var deadline_html = processVariables.end_date;
    
      return deadline_html;
  }

  this.isSelected = function(row) {
    return angular.equals(row, $scope.properties.selectedRow);
  };
  
}
