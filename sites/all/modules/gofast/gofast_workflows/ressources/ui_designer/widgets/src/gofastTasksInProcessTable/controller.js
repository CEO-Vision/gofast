function PbTableCtrl($scope, $http, $sce, $filter) {
     $scope.pagination = [];
     
     
    
     $scope.task_ids = "";
     $scope.$watch("properties.content", function(){
          if(typeof $scope.properties.content == "undefined"){
              return;
          }
         $scope.final_content = [];
         $scope.build_pagination();

         $scope.properties.content.forEach(function(myTask) {
                    myTask.title = myTask.name;
                    myTask.actor = get_initiator_html(myTask);
                    myTask.done = get_deadline_html(myTask);
                    myTask.start_date = myTask.start;
                    myTask.state = myTask.state;
                    
                    if(myTask.state == "ready"){
                        myTask.fa_state = "fa-arrow-right";
                        myTask.state = $filter('gfTranslate')("label.state_ready");
                        myTask.icon = "fa-clock-o";
                        myTask.margin = "3";
                    }else{
                        myTask.fa_state = "fa-check";
                        myTask.state = $filter('gfTranslate')("label.state_done");
                        myTask.icon = "fa-check";
                        myTask.margin = "1";
                    }
        
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
          var results_count = typeof $scope.properties.pageCount == "object" ? $scope.properties.pageCount.getResponseHeader('Content-Range').replace("0-0/", "") : $scope.properties.pageCount;
          var number_page = results_count / 5;
          
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

  $scope.ceo_vision_js_task_doit = function() {
      var row = $scope.properties.selectedRow;
      var force_assign = "false";
      if(row.assigned_id == 0){
           force_assign = "true";
      }
      window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_task_doit(row.id, row.processDefinititionSub.name+"/"+row.processDefinititionSub.version, "", row.name, force_assign);
  };

  $scope.ceo_vision_js_process_pageflow = function(){
     var row = $scope.properties.selectedRow;
     window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_process_pageflow("bdm", "", row.processHistory.persistenceId,"");

  };
  
    function get_initiator_html_old(myTask){
      //if task is assigned to current user, display initiator picture, else display assigned
    var initiator_string = myTask.assigned_id;
  
      var url = "/api/user/picture?username="+initiator_string;
       $http.get(url).then( 
                   function successCallback(response) {
                        myTask.actor = $sce.trustAsHtml(response.data.content);
                   }    
            ); 
     
  }

  function get_initiator_html(myTask){
         var initiator_string = myTask.assigneeId; 
  
      if(initiator_string == 0){
          initiator_string = $filter('gfTranslate')("label.unassigned");
      }else{
          var url = "/api/user/picture?username="+initiator_string;
           $http.get(url).then( 
                       function successCallback(response) {
                              var label_actor = $filter('gfTranslate')("label.assigned_to");
                              myTask.actor =$sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                       }    
                ); 
      }

  }
  
 function get_documents_html_old(myVariable, myTask){
      var documents_string = myVariable.value.replace(/\;/g, ",");
 
      var url = "/api/node/links?nids="+documents_string;
       $http.get(url).then( 
                   function successCallback(response) {
                        myTask.documents = $sce.trustAsHtml(response.data.content);
                   }    
            );  
  }
  

  function get_documents_html(myProcessCurrent, myTask){
      var documents_string = "";
      if(typeof myProcessCurrent.documents != "undefined"){
           myProcessCurrent.documents.forEach(function(nid) {
                documents_string = documents_string + nid +",";
          });
      }else{
          myProcessCurrent.contents.forEach(function(myProcessCurrentContent) {
              if(myProcessCurrentContent.type == "node"){
                  documents_string = documents_string + myProcessCurrentContent.content_value+",";
              }
          });
      }
      var url = "/api/node/links?nids="+documents_string;
       $http.get(url).then( 
                   function successCallback(response) {
                        myTask.documents = $sce.trustAsHtml(response.data.content);
                   }    
            );  
  }
  
  function get_deadline_html(myTask){
    myTask.has_deadline = true;
    if(myTask.done === null || typeof myTask.done == "undefined"){
        myTask.done = " / ";
        myTask.has_deadline = false;
        myTask.deadline_color = "#5bc0de";
        
    }else{
        myTask.deadline_color = "#2ecc71";
    }
      var deadline_html = myTask.done;
    
      return deadline_html;
  }

  this.isClickable = function () {
    return $scope.properties.isBound('selectedRow');
  };

  this.selectRow = function (row) {
    if (this.isClickable()) {
      $scope.properties.selectedRow = row;
    }
  };

  this.isSelected = function(row) {
    return angular.equals(row, $scope.properties.selectedRow);
  };

}
