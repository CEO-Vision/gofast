function PbTableCtrl($scope, $http, $sce, $filter) {
     $scope.pagination = [];
     
     
    
     $scope.process_ids = "";
     $scope.$watch("properties.content", function(){
          if(typeof $scope.properties.content == "undefined"){
              return;
          }
         $scope.final_content = [];
         $scope.build_pagination();

         $scope.properties.content.forEach(function(myProcessContent) {
            $scope.task_ids = $scope.task_ids+myProcessContent.id+"-";
             
            //Fill task content
            var myTask = {}
            myTask.id = myProcessContent.id;
            myTask.start = myProcessContent.start;
            myTask.state = myProcessContent.state;
            myTask.deadline = myProcessContent.deadline;
            myTask.title = myProcessContent.title;
            myTask.type = myProcessContent.type;
            myTask.startedby = myProcessContent.startedby;
            myTask.todo_count = myProcessContent.todo_count;
            myTask.done_count = myProcessContent.done_count;
			myTask = set_deadline_color(myProcessContent, myTask);
			myTask.actor = get_initiator_html(myTask.processHistory, myTask);
			myTask.hid = myProcessContent.hid;
			myTask.documents = myProcessContent.documents;
			
			if(myTask.state == "finished"){
			    myTask.icon = "fa-check";
			    myTask.margin = "1";
			}else{
			    myTask.icon = "fa-clock-o";
			    myTask.margin = "3";
			}
			
            //Push content to final array
            $scope.final_content.push(myTask);
         });
   
     });
        

  this.isArray = Array.isArray;
  
    $scope.build_pagination = function(){
          $scope.$watch("properties.pageCount", function(){
              
          if(typeof $scope.properties.pageCount == "undefined"){
              return;
          }
          $scope.pagination = [];
          var results_count = $scope.properties.pageCount.split("/")[1];
          var number_page = results_count / 10;
          
          var i;
          for (i = 0; i < number_page; i++) {
                page_label = i + 1;
                if(i == $scope.properties.page){
                    var btn_class = "btn_active";
                }else{
                    var btn_class = "";
                }
                var my_page_object = {number:i, label:page_label, btn_class:btn_class}
                $scope.pagination.push(my_page_object);
           }
        });
        
  }
  
  
   $scope.change_page = function($event){
       if($scope.properties.page != $event.target.id.replace("page_", "")){
           $scope.properties.content.length = 0
           $scope.task_ids = "";
           $scope.final_content = [];
           $scope.properties.page = $event.target.id.replace("page_", "");
        }
       
   }
   
function get_initiator_html(myProcessHistory, myTask){
      if(myTask.startedby > 0){
          var url = "/api/user/picture?username="+myTask.startedby;
           $http.get(url).then( 
                       function successCallback(response) {
                            var label_actor = $filter('gfTranslate')("label.started_by");
                            myTask.actor = $sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                       }    
                ); 
      }else{
          return $filter('gfTranslate')("label.started_auto");
      }

}
   
   function set_deadline_color(processVariables, myTask){
        myTask.has_deadline = true;
        if(processVariables.deadline === null || typeof processVariables.deadline == "undefined" || processVariables.deadline == ""){
            processVariables.deadline = " / ";
            myTask.has_deadline = false;
            myTask.deadline_color = "#5bc0de";
        }else{
            var d = new Date(processVariables.deadline);
            var timestamp_now = new Date().getTime() / 1000;
            var timestamp = d.getTime() / 1000;
              
            if(timestamp_now > timestamp){
                myTask.deadline_color = "#c0392b";
            }else if(timestamp - timestamp_now < 60*60*24){
                myTask.deadline_color = "#d35400";
            }else{
                myTask.deadline_description = "";
                myTask.deadline_color = "#2ecc71";
            }
        }
        
        if(myTask.state == "finished"){
            myTask.deadline_color = "#2ecc71";
        }
      return myTask;
  }
  
  this.isClickable = function () {
    return $scope.properties.isBound('selectedRow');
  };

  this.selectRow = function (row) {
    if (this.isClickable()) {
      $scope.properties.selectedRow = row;
      window.parent.parent.Gofast.gofast_workflow_show_details(row.id, row.type, row.title, row.hid, row.documents);
    }
  };

  this.isSelected = function(row) {
    return angular.equals(row, $scope.properties.selectedRow);
  };

}
