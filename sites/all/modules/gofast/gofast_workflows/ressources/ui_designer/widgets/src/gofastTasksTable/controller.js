function PbTableCtrl($scope, $http, $sce, $filter) {
     $scope.pagination = [];

     $scope.task_ids = "";
     $scope.$watch("properties.content", function(){
          if(typeof $scope.properties.content == "undefined"){
              return;
          }
         $scope.final_content = [];
         $scope.build_pagination();
         $scope.properties.content.forEach(function(myTaskContent) {
             $scope.task_ids = typeof myTaskContent.id !== "undefined" ? $scope.task_ids+myTaskContent.id+"-" : $scope.task_ids+"kanban-";
         });

         $http.get("/bonita/API/extension/getTasksAllInfos?taskids="+$scope.task_ids).then(
           function successCallback(response) {
                var i = 0;
                response.data.response.content.forEach(function(myTask) {

                    if(typeof myTask.type !== "undefined" && myTask.type == "kanban"){

                        var kanban_element = $scope.properties.content[i];

                        if(kanban_element.closest_deadline_color_indicator == "deadline-nearly-reached"){
                            myTask.deadline_color = "#d35400";
                        }else if(kanban_element.closest_deadline_color_indicator == "deadline-reached"){
                            myTask.deadline_color = "#c0392b";
                        }else if(kanban_element.closest_deadline_color_indicator == 'deadline-reached-off' || kanban_element.closest_deadline_color_indicator == 'deadline-nearly-reached-off' ){
                            myTask.deadline_color = "#b5b5c3";
                        }else{
                            myTask.deadline_color = "#2ecc71";
                        }

                        if(typeof kanban_element.closest_deadline !== "undefined" && kanban_element.closest_deadline !== ""){
                            myTask.deadline = kanban_element.closest_deadline;
                            myTask.has_deadline = true;
                        }else{
                            myTask.end_date = "  ";
                            myTask.deadline = "  ";
                        }

						myTask.deadline_timestamp = kanban_element.closest_deadline_timestamp;
                        myTask.actor = get_kanban_user_html(myTask, kanban_element.person_in_charge);
                        myTask.start_date = kanban_element.created_date;
                        myTask.alt_title = $filter('gfTranslate')("label.completed_at") + " " + kanban_element.progress + "%";
                        myTask.title = kanban_element.title;
                        myTask.displayDescription = kanban_element.first_item_label+" ("+myTask.alt_title+")";
                        myTask.type_icon = "fab fa-trello";
                        myTask.nid = kanban_element.nid;
                        myTask.documents = get_kanban_documents_html(kanban_element.attachments, myTask);
                    }else{

                        myTask.title = myTask.processHistory.title;
                        myTask.alt_title = myTask.title;
                        if($scope.properties.session.user_id == myTask.assigned_id){
                            myTask.is_author = true;
                        }else{
                            myTask.is_author = false;
                        }

						myTask.deadline_timestamp = new Date(myTask.processCurrent.end_date).getTime()/1000;
                        myTask.actor = get_initiator_html(myTask.processHistory, myTask);
                        myTask.documents = get_documents_html(myTask.processCurrent, myTask);
                        myTask.deadline = get_deadline_html(myTask.processCurrent,myTask);
                        myTask.start_date = myTask.processHistory.start_date;
                        myTask.processName = myTask.processInstance.name;
                        myTask.processVersion = myTask.processInstance.version;
                        myTask.processId = myTask.processInstance.id;
                        myTask.type_icon = "fas fa-cogs";
                        myTask.can_delete = get_variable_can_delete_instance(myTask.processCurrent, myTask.processInstance);
                    }

                    $scope.final_content.push(myTask);
                    i++;
           });

		   //Sort deadline for both process and kanban tasks
		   $scope.final_content.sort(function(a, b){
			   return a.deadline_timestamp - b.deadline_timestamp;
		   });

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

  $scope.ceo_vision_js_task_delete = function() {
      var row = $scope.properties.selectedRow;
      window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_delete_task(row.rootCaseId);
  };


  $scope.ceo_vision_js_process_pageflow = function(){
     var row = $scope.properties.selectedRow;
     if(row.type == "kanban"){
         window.parent.parent.Gofast.processAjax(window.parent.parent.location.origin + "/node/" + row.nid);
     }else{
       if(typeof row.processHistory.persistenceId != "undefined"){
            window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_process_pageflow("bdm", "", row.processHistory.persistenceId,"");
        }else{
            window.parent.parent.Drupal.gofast_workflows.ceo_vision_js_process_pageflow(row.processDefinitition.name, row.processDefinitition.version, row.rootCaseId, row.id);
        }
     }

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

  function get_initiator_html(myProcessHistory, myTask){
      //if task is assigned to current user, display initiator picture, else display assigned
      if( myTask.is_author == true){
        var initiator_string = myProcessHistory.initiator;
      }else{
         var initiator_string = myTask.assigneeId;
      }

      if(initiator_string == 0){
          initiator_string = myTask.actorId+"&actor=true";
      }
      var url = "/api/user/picture?username="+initiator_string;
       $http.get(url).then(
                   function successCallback(response) {
                      if( myTask.is_author == true){
                         var label_actor = $filter('gfTranslate')("label.started_by");
                         myTask.actor = $sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                      }else{
                          var label_actor = $filter('gfTranslate')("label.assigned_to");
                          myTask.actor =$sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                      }

                   }
            );

  }

    function get_kanban_user_html(myTask, uid){
      var url = "/api/user/picture?uid="+uid;
       $http.get(url).then(
                   function successCallback(response) {
                        var label_actor = $filter('gfTranslate')("label.responsible");
                        myTask.actor =$sce.trustAsHtml("<div style='clear:both;'>"+label_actor+"  : "+response.data.content+"</div>");
                   }
            );

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

  function get_kanban_documents_html(documents, myTask){
      var documents_string = "";
      if(typeof documents != "undefined"){
           documents.forEach(function(nid) {
                documents_string = documents_string + nid +",";
          });
      }
      var url = "/api/node/links?nids="+documents_string;
       $http.get(url).then(
                   function successCallback(response) {
                        myTask.documents = $sce.trustAsHtml(response.data.content);
                   }
            );
  }

  function get_variable_can_delete_instance(myProcessCurrent, processInstance){
       can_delete = false;
       if(typeof myProcessCurrent != "undefined" && typeof myProcessCurrent.contents != "undefined"){
            myProcessCurrent.contents.forEach(function(myProcessCurrentContent) {
                  if(myProcessCurrentContent.type == "technical" && myProcessCurrentContent.name == "can_delete_instance"){
                      if(myProcessCurrentContent.content_value == "true"){
                          //check if current user is initiator
                          if($scope.properties.session.user_id.toString() == processInstance.startedBy.toString()){
                              can_delete = true;
                          }else{
                              can_delete = false
                          }
                      }else{
                         can_delete = false;
                      }
                  }
            });
       }
          return can_delete;
  }

  function get_deadline_html(processVariables, myTask){
      var d = new Date(processVariables.end_date);
      var timestamp_now = new Date().getTime() / 1000;
      var timestamp = d.getTime() / 1000;

      if(timestamp_now > timestamp){
           var label_deadline = $filter('gfTranslate')("label.process_outdated");
           myTask.deadline_description = label_deadline;
           myTask.deadline_color = "#c0392b";
       }else if(timestamp - timestamp_now < 60*60*24){
           var label_deadline = $filter('gfTranslate')("label.process_soon_outdated");
           myTask.deadline_description = label_deadline;
           myTask.deadline_color = "#d35400";
       }else{
           myTask.deadline_description = "";
           myTask.deadline_color = "#2ecc71";
       }

    myTask.has_deadline = true;
    if(processVariables.end_date === null || typeof processVariables.end_date == "undefined"){
        processVariables.end_date = " none ";
        myTask.has_deadline = false;
        myTask.deadline_color = "#5bc0de";

    }
      var deadline_html = processVariables.end_date;

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