var selected_tab_wf = '0';
var d = new Date();
var last_reconnect_session = d.getTime();


(function ($, Gofast, Drupal) {
  'use strict';

  Drupal.gofast_workflows = Drupal.gofast_workflows || {};
   Gofast.already_check_login = false;


   Drupal.behaviors.gofast_workflows_tabs_document = {
        attach: function (context, settings) {
           $("#lightDashboardDocumentMyParentTab:not(.tab_processed)").addClass("tab_processed").click(function(){
              // alert("coucou");
               $("#lightDashboardDocumentMyTab").click();             
           });
           
            $("#lightDashboardDocumentOtherParentTab:not(.tab_processed)").addClass("tab_processed").click(function(){
              //  alert("coucou2");
               $("#lightDashboardDocumentOtherTab").click();             
           });
             $("#lightDashboardDocumentHistoryParentTab:not(.tab_processed)").addClass("tab_processed").click(function(){
              // alert("coucou");
               $("#lightDashboardDocumentHistoryTab").click();             
           });
           
            $("#lightDashboardDocumentNewParentTab:not(.tab_processed)").addClass("tab_processed").click(function(){
              //  alert("coucou2");
               $("#lightDashboardDocumentNewTab").click();             
           });
         
    }
   };


   $(document).ready(function(){
         var current_user = Gofast.get("user");
         if(current_user.uid == 0){
             //on the page load, we are not corrected so we are into login page, force to logout from Bonita
             $.get( "/bonita/logoutservice", function( data ) {
              });

             if(window.location.pathname.includes("/search/solr/")){
                 window.location.href = "/";
             }
         }
            // $("#tabs_wf").tabs({selected: selected_tab_wf});
             //on memorise le tab selectionné (pour s'en reservir lors du reload ajax du contenu)
             $("#tabs_wf_tasks, #tabs_wf_processes, #tabs_wf_processes_archived").click(function(){
                 selected_tab_wf = $(this).attr("fragment");
             });
        });





Drupal.gofast_workflows.showWFDocs = function(elt){
   var nid = jQuery(elt).data('nid');
   $(elt).parent().find('#wf_multiple_docs_'+nid).css('display', "block");
 }

Drupal.gofast_workflows.hideWFDocs = function(elt){
   var nid = jQuery(elt).data('nid');
   $(elt).parent().find('#wf_multiple_docs_'+nid).css('display', "none");
 }

        /*
 *
 * FONCTION TASK WORKFLOW
 *
 */

 Drupal.gofast_workflows.ceo_vision_js_automatic_reload_dashboard = function(){

        $(".ctools-close-modal:not(.processed)").click(function(){
                   Drupal.gofast_workflows._ceo_vision_js_automatic_reload_dashboard()
         }).addClass('processed');

      //$("#modal-content").css("background-image", "url('/drupal/sites/default/files/user-wallpaper-1424637025.png')");
 }

Drupal.gofast_workflows._ceo_vision_js_automatic_reload_dashboard = function(){
   return;
    if($("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows").size() != 0){
                    $.ajax({
                      url:"/workflow/rapiddashboard?async=true",
                      type: "GET",
                      dataType:'html',
                      success:function(response){
                              $("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows .gofast-block-outer").html(response);
                              //gofast.workflow.workflow_bloc.needRefresh = true;
                             // gofast.workflow.workflow_document_bloc.needRefresh = true;
                              Drupal.attachBehaviors($(".gofast-block-outer"));
                      }
                    });
    }
 }




 Drupal.gofast_workflows.ceo_vision_js_process_pageflow = function (processName, processVersion, processId, taskId){
     if(processName == "bdm"){
         var prefix_url = '/bonita/portal/resource/app/GoFAST/historyBdm/content/?persistenceId=';
         var iframe = '<iframe src="'+prefix_url+processId+'&locale='+ Gofast.get("user").language +'&app=GoFAST" id="bonita_form" style="width:100%;height:550px;border:none;"></iframe>';
     }else{
            if(taskId == ""){
                var task_parameter = '';
                var recap = "&recap=true";
            }else{
                /*var task_parameter = '&task='+taskId;
                var recap = "";*/
              var task_parameter = '';
                var recap = "&recap=true";
            }
            var prefix_url = '/bonita/portal/resource/processInstance/';
            var iframe = '<iframe src="'+prefix_url+processName+'/'+processVersion+'/content?id='+processId+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;height:550px;border:none;"></iframe>';
      }
        /* if(Drupal.settings.isMobile){
             jQuery("#bonita_form_process").prop("src", $(iframe).attr("src"));
             Gofast.removeLoading();
            jQuery("#refresh-pagedashboard").removeClass("gofast_display_none");
         }else{ */
            Gofast.modal(iframe, Drupal.t("Process resume" , {}, {'context' : 'gofast:gofast_workflows'}));
        // }
        Drupal.gofast_workflows.ceo_vision_js_automatic_reload_dashboard();

 }

Drupal.gofast_workflows.ceo_vision_js_delete_task = function(TaskId){
    var sentence_confirmation = Drupal.t("Are you sure you want to remove this process?", {}, {'context' : 'gofast:gofast_workflows'});
    var html_content = sentence_confirmation+"<br /><br /><input class='btn btn-sm btn-success' type='button' onClick='Drupal.gofast_workflows.ceo_vision_js_delete_task_execute(\""+TaskId+"\");' value='"+Drupal.t('Validate', {}, {'context' : 'gofast:gofast_workflow'})+"'/>";
      //gofast_modal(html_content, Drupal.t("Delete the process", {}, {'context' : 'gofast:gofast_workflows'}));
      Gofast.modal(html_content, Drupal.t("Delete the process" , {}, {'context' : 'gofast:gofast_workflows'}));
 }

Drupal.gofast_workflows.ceo_vision_js_delete_task_execute = function(TaskId){

     $.ajax({
               url:"/workflow/api/delete/case",
               data:  "caseid="+TaskId,
               type: "GET",
               dataType:'json',
               contentType: "application/json",
               success:function(response){
                   Drupal.CTools.Modal.dismiss();
                   location.reload();
               }
             })
 }


Drupal.gofast_workflows.ceo_vision_js_comment_create = function(ProcessId){
    var content_comment = $("#bonita_comment_create_input").val();
    var put_data = {"content":content_comment,"processInstanceId":+ProcessId}
     $.ajax({
               url:"/bonita/API/bpm/comment/",
               data:  JSON.stringify(put_data),
               type: "POST",
               dataType:'json',
               contentType: "application/json",
               success:function(response){
                   Drupal.CTools.Modal.dismiss();
               }
             })


 }

Drupal.behaviors.bonita  = {

     attach: function(context) {
        /*if(typeof Drupal.settings.gofast_workflows != "undefined"){
            Drupal.gofast_workflows.ceo_vision_js_login(Drupal.settings.gofast_workflows.bonita_username, null);
        }*/
    }

}

Drupal.behaviors.changeWfButonHrefDocument = {
    attach: function (context) {
        $('.GofastNode [id^=wf-process-]:not(.processed)').addClass("processed").change(function () {
            
            var id_select = this.id;
            var process_id = id_select.replace('wf-process-', '');
            var profil_id = this.value;
            var name_profil = $("#" + id_select +" option:selected").text();
            var onClickStr = $(".GofastNode .btn-process-startit-" + process_id).attr("onclick");

            var startIndexEdit = onClickStr.lastIndexOf(',', onClickStr.lastIndexOf(',') - 1); // start index
            var endIndexEdit = onClickStr.lastIndexOf(',');   // end index
            var preStrEdit = onClickStr.substring(0, startIndexEdit+1);
            var postStrEdit = onClickStr.substring(endIndexEdit, onClickStr.length);
            var onClickStrEdit = preStrEdit + '"edit"' + postStrEdit;   // outputs

            if (profil_id == 0){ // in case of no profile selected
                profil_id == ""; // set profile to nothing

                // disable edit buton front + remove attribute onclick
                $(".GofastNode #task_edit_" + process_id).css('cursor', 'not-allowed'); // 'default' to revert
                $(".GofastNode #task_edit_" + process_id).css('opacity', '0.4');               
                $(".GofastNode #task_edit_" + process_id).removeAttr("onclick");

                // disable delete buton front + remove attribute onclick
                $(".GofastNode #task_delete_" + process_id).css('cursor', 'not-allowed'); // 'default' to revert
                $(".GofastNode #task_delete_" + process_id).css('opacity', '0.4');
                $(".GofastNode #task_delete_" + process_id).removeAttr("onclick");
            } else { // in case of a profile is selected

                // enable edit buton front + add attribute on click
                $(".GofastNode #task_edit_" + process_id).css('cursor', 'pointer'); // 'default' to revert
                $(".GofastNode #task_edit_" + process_id).css('opacity', '1');
                $(".GofastNode #task_edit_" + process_id).attr("onclick", onClickStrEdit);

                // enable delete buton front + add attribute on click
                $(".GofastNode #task_delete_" + process_id).css('cursor', 'pointer'); // 'default' to revert
                $(".GofastNode #task_delete_" + process_id).css('opacity', '1');
                $(".GofastNode #task_delete_" + process_id).attr("onclick", "Drupal.gofast_workflows.ceo_vision_popup_delete_profil_generate('" + profil_id + "','" + name_profil+"')");
            }

            jQuery(".GofastNode .btn-process-startit-" + process_id).each(function () {
                var startIndex = onClickStr.lastIndexOf(",") + 1;  // start index
                var endIndex = onClickStr.lastIndexOf(")"); // end index
                var preStr = onClickStr.substring(0, startIndex);
                var postStr = onClickStr.substring(endIndex + 1, onClickStr.length - 1);
                var result = preStr + '"' + profil_id + '"' + postStr;   // outputs
                $(this).attr("onclick", result);
            });
            
            jQuery(".GofastNode .btn-process-editmodel-" + process_id).each(function () {
                onClickStr = $(this).attr("onclick");
                var startIndex = onClickStr.lastIndexOf(",") + 1;  // start index
                var endIndex = onClickStr.lastIndexOf(")"); // end index
                var preStr = onClickStr.substring(0, startIndex);
                var postStr = onClickStr.substring(endIndex + 1, onClickStr.length - 1);
                var result = preStr + '"' + profil_id + '"' + postStr;   // outputs
                $(this).attr("onclick", result);
            });

        });
    }
}

Drupal.behaviors.changeWfButonHref = {
    attach: function (context) {
        $('[id^=wf-process-]:not(.processed)').addClass("processed").change(function () {
            
            var id_select = this.id;
            var process_id = id_select.replace('wf-process-', '');
            var profil_id = this.value;
            var name_profil = $("#" + id_select +" option:selected").text();
            var onClickStr = $(".btn-process-startit-" + process_id).attr("onclick");

            var startIndexEdit = onClickStr.lastIndexOf(',', onClickStr.lastIndexOf(',') - 1); // start index
            var endIndexEdit = onClickStr.lastIndexOf(',');   // end index
            var preStrEdit = onClickStr.substring(0, startIndexEdit+1);
            var postStrEdit = onClickStr.substring(endIndexEdit, onClickStr.length);
            var onClickStrEdit = preStrEdit + '"edit"' + postStrEdit;   // outputs

            if (profil_id == 0){ // in case of no profile selected
                profil_id == ""; // set profile to nothing

                // disable edit buton front + remove attribute onclick
                $("#task_edit_" + process_id).css('cursor', 'not-allowed'); // 'default' to revert
                $("#task_edit_" + process_id).css('opacity', '0.4');       
                $("#task_edit_" + process_id).removeAttr("onclick");

                // disable delete buton front + remove attribute onclick
                $("#task_delete_" + process_id).css('cursor', 'not-allowed'); // 'default' to revert
                $("#task_delete_" + process_id).css('opacity', '0.4'); 
                $("#task_delete_" + process_id).removeAttr("onclick");
            } else { // in case of a profile is selected

                // enable edit buton front + add attribute on click
                $("#task_edit_" + process_id).css('cursor', 'pointer'); // 'default' to revert
                $("#task_edit_" + process_id).css('opacity', '1');
                $("#task_edit_" + process_id).attr("onclick", onClickStrEdit);

                // enable delete buton front + add attribute on click
                $("#task_delete_" + process_id).css('cursor', 'pointer'); // 'default' to revert
                $("#task_delete_" + process_id).css('opacity', '1'); // 'default' to revert
                $("#task_delete_" + process_id).attr("onclick", "Drupal.gofast_workflows.ceo_vision_popup_delete_profil_generate('" + profil_id + "','" + name_profil+"')");
            }

            jQuery(".btn-process-startit-" + process_id).each(function () {               
                var onClickStr2 = $(this).attr("onclick");  
                var startIndex = onClickStr2.lastIndexOf(",") + 1;  // start index
                var endIndex = onClickStr2.lastIndexOf(")"); // end index
                var preStr = onClickStr2.substring(0, startIndex);
                var postStr = onClickStr2.substring(endIndex + 1, onClickStr2.length - 1);
                var result = preStr + '"' + profil_id + '"' + postStr;   // outputs                                        
                $(this).attr("onclick", result);
            });
            
            jQuery(".btn-process-editmodel-" + process_id).each(function () {
                onClickStr = $(this).attr("onclick");
                var startIndex = onClickStr.lastIndexOf(",") + 1;  // start index
                var endIndex = onClickStr.lastIndexOf(")"); // end index
                var preStr = onClickStr.substring(0, startIndex);
                var postStr = onClickStr.substring(endIndex + 1, onClickStr.length - 1);
                var result = preStr + '"' + profil_id + '"' + postStr;   // outputs
                $(this).attr("onclick", result);
            });

        });
    }
}



    Drupal.gofast_workflows.ceo_vision_popup_delete_profil_generate = function (profilID,profilName) {
        var title = Drupal.t("Delete process model", {}, { context: "gofast:gofast_workflows" });
        var html = "<h4>" + Drupal.t('Are you sure you want to delete the procces model: "%profilname" ?', { '%profilname': profilName }, { context: "gofast:gofast_workflows" }) + "</h4>";
        html += "<br /><br />";
        html += '<button id="deleteButton" class="btn btn-danger btn-sm icon-before" type="submit" onClick="Drupal.gofast_workflows.ceo_vision_js_delete_profil(\'' + profilID +'\')"><span class="icon glyphicon glyphicon-trash"></span>' + ' ' + Drupal.t('Delete') + '</button>';
        // show modal
        Gofast.modal(html, title, { allowStretch: true });
    }


    Drupal.gofast_workflows.ceo_vision_js_delete_profil = function (profilID) {

        $.ajax({
            url: Drupal.settings.gofast.baseUrl + "/api/workflow/profil",
            method: "DELETE",
            timeout: 0,
            data: JSON.stringify({ "id": profilID }),
            contentType: 'application/json; charset=utf-8',
            success: function (data) {
                // show valdiation toast
                Gofast.toast(Drupal.t("Workflow model successfully deleted", {}, { context: 'gofast:ajax_file_browser' }), "success");
                Drupal.CTools.Modal.dismiss();
            },
            error: function (xhr, textStatus, error) {
                var errMsg = textStatus;
                if (xhr.responseText) {
                    errMsg = $.parseJSON(xhr.responseText);
                }
                // show error toast
                Gofast.toast(Drupal.t(errMsg.message, {}, { context: 'gofast:ajax_file_browser' }), "error");
                Drupal.CTools.Modal.dismiss();
            }
        });
    }

Drupal.gofast_workflows.ceo_vision_js_check_login = function(callback){
        if(Gofast.already_check_login === true){
            if(typeof callback === "function"){
                 var executeCallbackAfterParallelLogin = setInterval(function() {
                        if(Gofast.already_check_login === false){
                                clearInterval(executeCallbackAfterParallelLogin);
                    		callback();
                        }
                     }, 1000); // check every 1000ms
            }
            return;
        }

        Gofast.already_check_login = true;
		 var URL = "/bonita/apps/appDirectoryBonita/home/";

                $.ajax({
                url: URL,

                complete: function(xhr) {
                    var status =xhr.status;
                    var response_length = xhr.getResponseHeader('Content-Length');

                   if(status !== 200 || response_length < 1){
                      Drupal.gofast_workflows.ceo_vision_js_login(Drupal.settings.gofast_workflows.bonita_username, null, callback);
                   }else{
                       Gofast.already_check_login = false;
                       if(typeof callback === "function"){
                          callback();
                       }
                   }
                }
        });
 }

 Gofast.get_bonita_token = function () {
    var token;
    if(typeof Drupal.settings.gofast === "undefined"){ //GOFAST-3374
      return false;
    }

    if(typeof Drupal.settings.pass_reset != "undefined"){
      return;
    }

     $.ajax({
            url : Drupal.settings.gofast.baseUrl+'/workflow/token',
            type : 'GET',
            async: true,
            success : function(content){
               Gofast.bonita_token = content.replace(/ /g,'').replace(/\n/g, '');
            }
          });
       //return password;
  };

Drupal.gofast_workflows.ceo_vision_js_login = function(myusername, mypassword, callback){
        if(typeof Drupal.settings.pass_reset != "undefined" || typeof Drupal.settings.bonita_authentification_problem != "undefined"){
           return;
         }

       if(myusername === null){
           return;
       }

        if (!Date.now) {
            Date.now = function() { return new Date().getTime(); }
        }
        var bonita_cookie = Gofast.getCookie("bonita_sess_timestamp");
        var now = Math.floor(Date.now() / 1000);
            if(mypassword == null){
               Gofast.get_bonita_token();
               var checkExistPassword = setInterval(function() {
                   if (Gofast.bonita_token !== "" && Gofast.bonita_token !== "undefined" && Gofast.bonita_token !== undefined) {
                   mypassword = Gofast.bonita_token;
                   clearInterval(checkExistPassword);
                   var URL = "/bonita/loginservice?redirectUrl=";
                  if(mypassword !== "" && mypassword !== null){
                        var put_data = {"username":myusername,"password":mypassword, "redirect":"false"};
                        $.ajax({
                              url:URL,
                              data: put_data,
                              type: "POST",
                              //dataType:'json',
                              contentType: "application/x-www-form-urlencoded",
                              success:function(response){
                                  Gofast.already_check_login = false;
                                   if(typeof callback === "function"){
                                        callback();
                                   }else{
                                       Gofast.setCookie("bonita_sess_timestamp",Math.floor(Date.now() / 1000));
                                       $("#bonita_light_dashboard_placeholder").replaceWith('<iframe src="/bonita/portal/resource/app/GoFAST/lightDashboard/content/?app=GoFAST&locale='+ Gofast.get("user").language +'" id="bonita_form_process" style="width:100%;height:100%;min-height:550px;border:none;"></iframe>');
                                   }
                              }
                            });
                  }
                }

             }, 500); // check every 500ms
            }
 }



 Drupal.gofast_workflows.ceo_vision_js_task_doit = function(taskID, processName, userID, taskName, force_assign, modal = true){
            if (typeof force_assign === 'undefined') {
                force_assign = "false";
            }

           if(force_assign == "true"){
                    //on est dans le cas ou la tache n'est pas assignée specifiquement au user courant mais a un acteur Bonita.
                    //dans ce cas, il faut assigner la tache au user courant lorsque celui-ci charge le formulaire de la tache
                   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
                   var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/reassign/task/validate";
                   var new_assign_user = $("#select_new_user").val();
                   var put_data = {new_assign_user: new_assign_user, action: "task", task_id: taskID};
                   $.ajax({
                     url: URI,
                     data:  put_data,
                     type: "POST",
                     dataType:'json',
                     success:function(data){
                        Gofast.addLoading();
                        Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                            var prefix_url = '/bonita/portal/resource/taskInstance/';
                            var iframe = '<div style="padding:0px;height:100%;"><iframe src="'+prefix_url+processName+'/'+taskName+'/content/?id='+taskID+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;height:100%;min-height:550px;border:none;float:left;"></iframe></div>';
                            if(modal == true){
                                var iframe = '<div style="padding:0px;height:100%;"><iframe src="'+prefix_url+processName+'/'+taskName+'/content/?id='+taskID+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;height:100%;min-height:550px;border:none;float:left;"></iframe></div>';
                                Gofast.addLoading();
                                Gofast.modal(iframe, Drupal.t("Execute the task", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true });
                            }else{
                                var iframe = '<div id="bonita_form_container" style="padding:0px;height:310px;display:none;overflow:visible;"><iframe src="'+prefix_url+processName+'/'+taskName+'/content/?id='+taskID+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;min-height:310px;border:none;float:left;"></iframe></div>';
                                $("#document__infotab.active").removeClass("active");
                                $('a[href$="#document__infotab"]').removeClass("active");
                                $("#lightDashboardDocumentMyParentTab").click();                               
                                $("#lightDashboardDocumentMy #bonita_form_process").css("min-height", "0px");
                                //$("#lightDashboardDocumentMy #bonita_form_process").css("margin-bottom", "30px");
                                $("#lightDashboardDocumentMy #bonita_form_process").after(iframe);
                                $("#lightDashboardDocumentMy #bonita_form_process").addClass('forcefully-loaded');
                                var task_name = $("#lightDashboardDocumentMy #bonita_form_process").contents().find(".fa-flag-o").next().html();
                                var title_do_task = "<div style='width:100%;text-align:center;'><h4 style='display: block;margin-left: auto;margin-right: auto;'>"+Drupal.t("Do your task :", {}, {'context' : 'gofast:gofast_workflows'})+" "+task_name+"</h4></div>";
                                $("#lightDashboardDocumentMy #bonita_form_process").after(title_do_task);


                               var checkExistsDocumentTasksListOpenTask = setInterval(function() {
                                if (jQuery("#lightDashboardDocumentMy #bonita_form").contents().find("form").length) {
                                   clearInterval(checkExistsDocumentTasksListOpenTask);
                                   setTimeout(function(){  
                                        $("#lightDashboardDocumentMy #bonita_form").contents().find("form").parent().next().css("display", "none");
                                        $("#lightDashboardDocumentMy #bonita_form").contents().find("form").css("width", "99%");
                                        $("#lightDashboardDocumentMy #bonita_form").contents().find(".col-xs-12.ng-scope.thumbnail").css("display", "none");
                                        $("#bonita_form_container").css("display", "block");
                                    }, 100);    
                                }

                               }, 500);       
                            }       
                        });
                     }
                   });

            }else{
              
                Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
                    var prefix_url = '/bonita/portal/resource/taskInstance/';
                     //var prefix_url = '/bonita/portal/homepage';
                   if(modal == true){
                       var iframe = '<div style="padding:0px;height:100%;"><iframe src="'+prefix_url+processName+'/'+taskName+'/content/?id='+taskID+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;height:100%;min-height:550px;border:none;float:left;"></iframe></div>';                     
                       Gofast.modal(iframe, Drupal.t("Execute the task", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true });
                    }else{
                        var iframe = '<div id="bonita_form_container" style="padding:0px;height:310px;display:none;overflow:visible;"><iframe src="'+prefix_url+processName+'/'+taskName+'/content/?id='+taskID+'&locale='+ Gofast.get("user").language +'" id="bonita_form" style="width:100%;min-height:310px;border:none;float:left;"></iframe></div>';
                        $("#node-tabsHeader a ").removeClass("active");
                        $(".header_tasks_tab").addClass("active");
                        $("#lightDashboardDocumentMyParentTab").click();  
                        $("#lightDashboardDocumentMy #bonita_form_process").css("min-height", "0px");
                        //$("#lightDashboardDocumentMy #bonita_form_process").css("margin-bottom", "30px");
                        $("#lightDashboardDocumentMy #bonita_form_process").after(iframe);
                        $("#lightDashboardDocumentMy #bonita_form_process").addClass('forcefully-loaded');
                        var task_name = $("#lightDashboardDocumentMy #bonita_form_process").contents().find(".fa-flag-o").next().html();
                        var title_do_task = "<div style='width:100%;text-align:center;'><h4 style='display: block;margin-left: auto;margin-right: auto;'>"+Drupal.t("Do your task :", {}, {'context' : 'gofast:gofast_workflows'})+" "+task_name+"</h4></div>";
                        $("#lightDashboardDocumentMy #bonita_form_process").after(title_do_task);
                       
                       
                       var checkExistsDocumentTasksListOpenTask = setInterval(function() {
                        if (jQuery("#lightDashboardDocumentMy #bonita_form").contents().find("form").length) {
                           clearInterval(checkExistsDocumentTasksListOpenTask);
                           setTimeout(function(){  
                                $("#lightDashboardDocumentMy #bonita_form").contents().find("form").parent().next().css("display", "none");
                                $("#lightDashboardDocumentMy #bonita_form").contents().find("form").css("width", "99%");
                                $("#lightDashboardDocumentMy #bonita_form").contents().find(".col-xs-12.ng-scope.thumbnail").css("display", "none");
                                $("#bonita_form_container").css("display", "block");
                            }, 100);    
                        }

                       }, 500);       
                    }

                });
            }

            var checkExist = setInterval(function() {
                if ($("#bonita_form").contents().find('#bonita_form_confirm_message').length) {
                  if(typeof Drupal.settings.gofast_workflows.bonita_timer_refresh === "undefined"){
                      Drupal.settings.gofast_workflows.bonita_timer_refresh = 1000;
                  }
                   setTimeout(function() {
                        Gofast.closeModal();
                        Gofast.toast(Drupal.t("Task executed", {}, {'context' : 'gofast:gofast_workflows'}));
                        clearInterval(checkExist);
                                Gofast.processAjax(window.location.pathname);
                   }, Drupal.settings.gofast_workflows.bonita_timer_refresh);
                }

             }, 2000);
 }

 /*Drupal.gofast_workflows.ceo_vision_js_process_pageflow = function(processName, processVersion, processId, taskId){
        if(taskId == ""){
            var task_parameter = '';
            var recap = "&recap=true";
        }else{
            var task_parameter = '&task='+taskId;
            var recap = "";
        }
        //si c'est safari l'url est legerement differente car sinon bug... :-(
       if($.browser.safari){
           var prefix_url = '/bonita/portal/homepage';
       }else{
           var prefix_url = '/bonita';
       }
        var iframe = '<div style="padding:20px;"><iframe src="'+prefix_url+'?ui=form&locale=fr#form='+processName+'--'+processVersion+'$recap&mode=form&instance='+processId+task_parameter+recap+'" id="bonita_form" style="width:550px;height:550px;border:none;"></iframe></div>';
        gofastAddLoading();
        gofast_modal(iframe, Drupal.t("Process resume"));
        ceo_vision_js_automatic_reload_dashboard();

 }*/

 Drupal.gofast_workflows.ceo_vision_js_process_startit = function(processID, processName, reference, reference_liste,action_profil , profil_id){
     Gofast.addLoading();

     Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
        var prefix_url = '/bonita/portal/resource/process/';

        var processNameData = processName.split('|');

        processName = processNameData[0].replace("--", "/");
        var processLabel = processNameData[1];
        reference = reference.replace(/\+/g, " ");
         var iframe = '<div style="padding:0px;height:100%;"><iframe src="' + prefix_url + processName + '/content/?id=' + processID + '&locale=' + Gofast.get("user").language + '&nids=' + reference + '&id_profil=' + profil_id + '&action_profil=' + action_profil+'" id="bonita_form_process" style="width:100%;height:100%;min-height:550px;border:none;"></iframe></div>';

        reference = decodeURI(reference);
        if(reference != ""){
        if(reference_liste != ""){
            var docname = Drupal.t("Documents from your cart");
                var title_modal = Drupal.t('Workflow', {}, {'context' : 'gofast:gofast_workflow'}) +": "+processLabel+" - "+docname;
        }else{
                var docname = (reference.split('`')[1]).replace('|', '');
                var title_modal = Drupal.t('Workflow', {}, {'context' : 'gofast:gofast_workflow'}) +": "+processLabel+" - "+docname;
        }
        }else{
            var title_modal = Drupal.t('Workflow', {}, {'context' : 'gofast:gofast_workflow'}) +": "+processLabel ;
        }

        Gofast.modal(iframe, title_modal, { allowStretch: true });

        Drupal.gofast_workflows.ceo_vision_js_automatic_reload_dashboard();
        $('#modalBackdrop').remove();
     });
 }

  Drupal.gofast_workflows.ceo_vision_js_process_viewit = function(processID, processName){
    $.ajax({
               url:"/workflow/api/process/getgraph/"+processID+"/"+processName+"",
               type: "GET",
               dataType:'html',
               success:function(response){
                   Gofast.modal(response, Drupal.t("View the process", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true });
               }
             })
 }


Drupal.gofast_workflows.ceo_vision_js_task_next = function(task_name, nid, task_id){
  gofastAddLoading();

  var url = "/ajax/workflow/courrier/next/"+task_name+"/"+nid+"/"+task_id;

  $.ajax({
    url: url, // le nom du fichier indiqué dans le formulaire
    type: "GET", // la méthode indiquée dans le formulaire (get ou post)
    dataType: 'html',
    success:function(data){
       gofastRemoveLoading();
       //location.reload();
    }
  });
}

// fonction de soumission specifique a l'attribution du répondeur
Drupal.gofast_workflows.ceo_vision_js_task_validate_choose_responser = function(task_id, task_name , nid){
  gofastAddLoading();

  var url = "/ajax/workflow/courrier/next/chooseresponser/"+task_id;
  var name_responser = $("#choose_responser_input").val();
  var put_data = {responser: name_responser, task_name: task_name, nid: nid, task_id: task_id};


  $.ajax({
    url: url,
    data:  put_data,
    type: "POST",
    dataType:'json',
    success:function(data){
       gofastRemoveLoading();
       //location.reload();
    }
  });
}

// fonction de soumission specifique a l'attribution du validateur du courrier sortant
Drupal.gofast_workflows.ceo_vision_js_task_validate_choose_validateur = function(task_id, task_name , nid){
  gofastAddLoading();

  var url = "/ajax/workflow/courrier/next/choosevalidateur/"+task_id;
  var name_validateur = $("#choose_validateur_input").val();
  var put_data = {validateur: name_validateur, task_name: task_name, nid: nid, task_id: task_id};


  $.ajax({
    url: url,
    data:  put_data,
    type: "POST",
    dataType:'json',
    success:function(data){
       gofastRemoveLoading();
       //location.reload();
    }
  });
}


// fonction utilisé pour une tache simple de validation (oui ou non)
Drupal.gofast_workflows.ceo_vision_js_task_validate_validate = function(task_id, task_name , nid, id_input){
  gofastAddLoading();

  var url = "/ajax/workflow/courrier/next/validate/"+task_id;
  var is_validate = $("#"+id_input).val();

  var put_data = {validate: is_validate, task_name: task_name, nid: nid, task_id: task_id};


  $.ajax({
    url: url,
    data:  put_data,
    type: "POST",
    dataType:'json',
    success:function(data){
       gofastRemoveLoading();
       //location.reload();
    }
  });
}




Drupal.gofast_workflows.ceo_vision_js_process_get_comments = function(processID){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/'),
   URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/comments/"+processID;

  $.ajax({
    url:URI,
    dataType:'html',
    success:function(data){
     gofast_modal(data, "comments");
    }
  })

}

Drupal.gofast_workflows.ceo_vision_js_process_get_case = function(caseID){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/'),
   URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/case/"+caseID;

  $.ajax({
    url:URI,
    dataType:'html',
    success:function(data){
        gofast_modal(data, Drupal.t("Current Process", {}, {'context' : 'gofast:gofast_workflows'}));
        $("#modal-content").addClass("modal-content-workflow");
    }
  })

}

Drupal.gofast_workflows.ceo_vision_js_process_get_task = function(taskID){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/'),
   URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/task/details/"+taskID;

  $.ajax({
    url:URI,
    dataType:'html',
    success:function(data){
        gofast_modal(data, Drupal.t("Current task", {}, {'context' : 'gofast:gofast_workflows'}));
        $("#modal-content").addClass("modal-content-workflow");
    }
  });

}

Drupal.gofast_workflows.ceo_vision_js_process_get_actives_tasklist = function(caseId){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/'),
   URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/activetasklist/"+caseId;

  $.ajax({
    url:URI,
    dataType:'html',
    success:function(data){
        Gofast.modal(data, Drupal.t("Active tasks", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true }) ;
        $("#modal-content").addClass("modal-content-workflow");
    }
  });
}


Drupal.gofast_workflows.ceo_vision_js_process_get_finished_tasklist = function(caseId, archived){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
  // if(archived == "true"){
       var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/finishedtasklist_archived/"+caseId;
  // }else{
   //     var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/finishedtasklist/"+caseId;
  // }

  $.ajax({
    url:URI,
    dataType:'html',
    success:function(data){
        Gofast.modal(data, Drupal.t("Finished tasks", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true }) ;
        $("#modal-content").addClass("modal-content-workflow");
    }
  });
}

Drupal.gofast_workflows.ceo_vision_js_process_get_available_processes = function(reference){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
   var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/process/availables";

    if(reference == null){
         var data = "";
         var title_modal = Drupal.t("Start a process", {}, {'context' : 'gofast:gofast_workflows'});
    }else if(reference == "cart"){
        var data = "document=cart";
        var title_modal = Drupal.t("Start a process on the documents into your cart", {}, {'context' : 'gofast:gofast_workflows'});
    }else{
        reference = reference.replace(/\&/g, '%26');
        var data = "document="+reference;
        var docname = reference.split('||')[1];
        var title_modal = Drupal.t("Start a process on the document", {}, {'context' : 'gofast:gofast_workflows'})+" "+docname;
    }
  $.ajax({
    url:URI,
    data:data,
    dataType:'html',
    success:function(data){
        Gofast.modal(data, "GoFast", { allowStretch: true });
        $("#modal-content").addClass("modal-content-workflow");
    }
  });
}


Drupal.gofast_workflows.ceo_vision_js_edit_deadline = function(taskId){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
   var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/edit/deadline";


  var data = "taskId="+taskId;

  $.ajax({
    url:URI,
    data:data,
    dataType:'html',
    success:function(data){
       Gofast.modal(data, Drupal.t("Edit deadline", {}, {'context' : 'gofast:gofast_workflows'}), { allowStretch: true });
       Drupal.gofast_workflows._ceo_vision_js_automatic_reload_dashboard();
    }
  });
}

Drupal.gofast_workflows.ceo_vision_js_task_reassign = function(taskId){
   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
   URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/reassign/task";


  var data = "taskId="+taskId;

  $.ajax({
    url:URI,
    data:data,
    dataType:'html',
    success:function(data){
        gofast_modal(data, Drupal.t("Reassign the task", {}, {'context' : 'gofast:gofast_workflows'}));
        $("#modal-content").addClass("modal-content-workflow");
        ceo_vision_js_automatic_reload_dashboard();
    }
  });
}

// fonction utilisé pour valider le formulaire de réassignation de tache
Drupal.gofast_workflows.ceo_vision_js_reassign_validate = function(taskId, action){

   var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
   var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/reassign/task/validate";

  var new_assign_user = $("#select_new_user").val();

  var put_data = {new_assign_user: new_assign_user, action: action, task_id: taskId};

  $.ajax({
    url: URI,
    data:  put_data,
    type: "POST",
    dataType:'json',
    success:function(data){
       $(".modal-header a").click();
       Drupal.CTools.Modal.dismiss();

    }
  });
}

// fonction utilisé pour valider le formulaire de réassignation de tache
Drupal.gofast_workflows.ceo_vision_js_edit_deadline_validate = function(taskId, action){
     Gofast.addLoading();

  var myUrl = $(document)[0].URL.replace(location.hash,"").split('/');
  var URI = myUrl[0] + "//" + myUrl[2] + Drupal.settings.basePath + "workflow/api/edit/deadline/validate";

  var new_date = $("#new_deadline").val();


  var put_data = {new_deadline: new_date, task_id: taskId};


  $.ajax({
    url: URI,
    data:  put_data,
    type: "POST",
    dataType:'json',
    success:function(data){
        $(".ctools-close-modal").click();
        Drupal.gofast_workflows._ceo_vision_js_automatic_reload_dashboard();
        Gofast.removeLoading();
    }
  });
}


Drupal.behaviors.dynatable = {

     attach: function() {
return;
    var myuser = Gofast.get("user");
    if(myuser.uid == 1){
        return;
    }

  var dynatable = $("#actives_tasks_table, #actives_tasks_others_table,  #actives_cases_table, #available_process_table, #archived_cases_table").dynatable({
                features: {
                  pushState: false
                },
                table: {
                    defaultColumnIdStyle: 'camelCase',
                    columns: null,
                    headRowSelector: 'thead tr', // or e.g. tr:first-child
                    bodyRowSelector: 'tbody tr',
                    headRowClass: null
              },params :{
                   records :  Drupal.t('tasks',{}, {'context' : 'gofast'}),
              },inputs: {
                    queries: null,
                    sorts: null,
                    multisort: ['ctrlKey', 'shiftKey', 'metaKey'],
                    page: null,
                    queryEvent: 'blur change',
                    recordCountTarget: null,
                    recordCountPlacement: 'after',
                    paginationLinkTarget: null,
                    paginationLinkPlacement: 'after',
                    paginationClass: 'dynatable-pagination-links',
                    paginationLinkClass: 'dynatable-page-link',
                    paginationPrevClass: 'dynatable-page-prev',
                    paginationNextClass: 'dynatable-page-next',
                    paginationActiveClass: 'dynatable-active-page',
                    paginationDisabledClass: 'dynatable-disabled-page',
                    paginationPrev: Drupal.t('Previous',{}, {'context' : 'gofast'}),
                    paginationNext: Drupal.t('Next',{}, {'context' : 'gofast'}),
                    paginationGap: [1,2,2,1],
                    searchTarget: null,
                    searchPlacement: 'before',
                    perPageTarget: null,
                    perPagePlacement: 'before',
                    perPageText: Drupal.t('Show :',{}, {'context' : 'gofast'}),
                    recordCountText: Drupal.t('Show :',{}, {'context' : 'gofast'}),
                    recordCountFilteredText : Drupal.t("(filtered from {recordCountTotal} total records)", {}, {'context' : 'gofast'}),
                    recordCountShownText : Drupal.t("{recordCountShown} of ", {}, {'context' : 'gofast'}),
                    recordCountBoundsText : Drupal.t(" {recordCountBoundStart} to {recordCountBoundEnd} of ", {}, {'context' : 'gofast'}),
                    processingText: 'Processing...',
                    searchText: Drupal.t('Search :',{}, {'context' : 'gofast'}),
                    records: "Résultats"
                },
                 dataset: {
                    perPageDefault: 20,
                    //perPageOptions:[3, 6]
                  }
            }).bind('dynatable:afterProcess', Drupal.gofast_workflows.updateChart);

   dynatable = $("#actives_tasks_table,#actives_tasks_others_table, #actives_cases_table, #available_process_table, #archived_cases_table").data('dynatable');
     if(dynatable){
          dynatable.paginationPerPage.set(10);
            dynatable.process();
     }


    //si dans l'url il y a un parametre indiquant une tache en particulier, on higlight celle-ci
        /*  var task_param = geturlparameter("task");
          //je cherche la ligne du tableau correspondant a cette tache
          var task_line = $("span[task_id='task_line_"+task_param+"']");

          if(task_line.length > 0){
              var line = task_line.parent().parent();
              if(line){
                  line.css("background-color", "#F78181");
              }
          }else{
               if(dynatable){
                    dynatable.queries.runSearch(task_param);
                    dynatable.process();
                    var task_line = $("span[task_id='task_line_"+task_param+"']");
                    var line = task_line.parent().parent();
                    if(line){
                        line.css("background-color", "#F78181");
                    }
                }
          }*/


     }

 }

// Drupal.behaviors.instanciate_rapide_dashboard = function(context){
Drupal.behaviors.instanciate_rapide_dashboard  = {

     attach: function(context) {
        var myuser = Gofast.get("user");
        if(typeof myuser == "undefined"){
            return;
        }
        if(myuser.uid == 1){
            return;
        }

        var already_pager = jQuery("#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows #container_todoliste .pagination-sm").html();
        if(already_pager == ""){
            jQuery('#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows #container_todoliste > div > ul.content').pager({pagerSelector : '#gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows #container_todoliste > ul.pagination ', perPage: 5});
            jQuery('#container_todoliste_others > div > ul.content').pager({pagerSelector : '#container_todoliste_others > ul.pagination', perPage: 5});
        }

         var already_pager_modal = jQuery("#modal-content #container_todoliste .pagination-sm").html();
        if(already_pager_modal == ""){
            jQuery('#modal-content #container_todoliste > div > ul.content').pager({pagerSelector : '#modal-content #container_todoliste > ul.pagination ', perPage: 5});
            jQuery('#container_todoliste_others > div > ul.content').pager({pagerSelector : '#container_todoliste_others > ul.pagination', perPage: 5});
        }
/*
            $("#container_todoliste", context).pajinate({
                                              items_per_page : 5,
                                              nav_label_first : "Prem.",
                                              nav_label_last : "Dern.",
                                              nav_label_prev : "Prec.",
                                              nav_label_next : "Suiv."
                                      });
             $("#container_todoliste_others", context).pajinate({
                                              items_per_page : 5,
                                              nav_label_first : "Prem.",
                                              nav_label_last : "Dern.",
                                              nav_label_prev : "Prec.",
                                              nav_label_next : "Suiv.",
                                              nav_panel_id    : ".page_navigation2"
                                      });
*/

             //$("#tabs_wf_rapid_tab:not(\".tabs_processed\"), #tabs_doc_wf:not(\".tabs_processed\")", context).addClass("tabs_processed").tab('show');

             //the reason for the odd-looking selector is to listen for the click event
            // on links that don't even exist yet - i.e. are loaded from the server.
            $('#tabs_wf_rapid:not(.tabs_processed)').on('click','#tabs_wf_rapid_tab a',function (e) {
                e.preventDefault();
                var url = $(this).attr("data-url");

                if (typeof url !== "undefined") {
                    var pane = $(this), href = this.hash;

                    // ajax load from data-url
                    $(href).load(url,function(result){
                        pane.tab('show');
                    });
                } else {
                    $(this).tab('show');
                }

                $(this).addClass("tabs_processed");
            });

    // });

    Drupal.gofast_workflows.ceo_vision_js_automatic_reload_dashboard();
    }

};




Drupal.gofast_workflows.updateChart = function(a){
     Drupal.behaviors.toggle_history_grid();
 }


 Drupal.behaviors.toggle_history_grid = function(context){
     $(".wf_history_details:not(.page-processed)", context).addClass('page-processed').toggle(
    function() {
        $(this).animate({maxHeight:2000},200);
        $(this).css("background-image" , 'url("/misc/menu-expanded.png")');
        $(this).css("background-repeat" , 'no-repeat');
    }, function() {
        $(this).css("background-image" , 'url("/misc/menu-collapsed.png")');
        $(this).css("background-repeat" , 'no-repeat');
        $(this).animate({maxHeight:150},200);
    }
);
}





Drupal.gofast_workflows.wfSetUnreadCount = function(data){
  if(data === "null"){
      //si on a pas d'objet data, on effectrue une requete ajax pour recuperer le nombre de taches dans la todolist
      $.ajax({
                url:"/workflow/number/todolist",
                dataType:'json',
                success:function(response){
                   var new_data = new Object();
                   new_data.workflows = response.count;
                   _wfSetUnreadCount(new_data);
                }
              });
  }else{
      _wfSetUnreadCount(data);
  }

 }

Drupal.gofast_workflows._wfSetUnreadCount = function(data){
  var notifUnread = $('.unread_workflows'),
  oldCount;
  var src_no_todo = "/sites/all/themes/fusion/fusion_starter/img/new/workflow.png";
  var src_todo = "/sites/all/themes/fusion/fusion_starter/img/new/workflow_active.png";
  if (data.workflows > 0) {
    oldCount = parseInt(notifUnread.text());
    if(isNaN(oldCount)) oldCount = 0;
    notifUnread.text(data.workflows);
    gofast.workflow.workflow_bloc.needRefresh = true;
    if(oldCount < data.workflows) {
      //gofast.workflow.workflow_bloc.needRefresh = true;
      $("#gofast-worfklow-icone").attr("src", src_todo);
    }
  } else {
    notifUnread.text('');
    $("#gofast-worfklow-icone").attr("src", src_no_todo);
  }
}

Drupal.behaviors.gofastWorkflowGetIconNode  = {
  attach: function(context) {

            var container = $("#breadcrumb-alt-wf", context);         
            if(container.size() != 0 && !container.hasClass("workflow_icone_processed")){
                 container.addClass("workflow_icone_processed");
                 var node = Gofast.get('node');
                 if (typeof node !== 'undefined'){
                 var lang = Drupal.settings.lang ? "/" + Drupal.settings.lang : "";
                
                 $.get(lang + "/ajax/workflow/icone/node/"+node.id, function(data) {                   
                      container.replaceWith(data.action);                  
                      $.extend(Drupal.settings.gofast.context, data.context);                     
                      var new_container = $("#breadcrumb-alt-wf", context);
                      new_container.addClass("workflow_icone_processed");
                      Drupal.attachBehaviors(new_container);
                   });
               }
         }

  }
};

Gofast.refreshWorkflowIcon = function(count){
    $(".gofast-task-notifiation").each(function(){
        $(this).html(count);
    })
    $("#refresh-lightdashboard-document").click();   
};

Gofast.gofast_workflow_search = function(e){
    if(typeof e === "object"){
        e.preventDefault();
    }

    //Retrieve form data
    var form_data = $("form[id^=\"gofast-workflow-dashboard-search-form\"]").serializeArray();
    
    //Save form data
    Gofast.gofast_workflow_save_filters(form_data);
    
    var data = {};
    form_data.forEach(function(e){
	    data[e.name.split("-").pop()] = e.value;
    });

    if(data.creator !== "" && typeof data.creator !== "undefined"){
        data.creator = JSON.parse(data.creator)[0].value;
    }

    //Prepare an array with the creator and the users to turn them into bonita ids
    if(data.users !== "" && typeof data.users !== "undefined"){
        data.users = JSON.parse(data.users).map(user => user.value);
        if(data.creator !== "" && typeof data.creator !== "undefined"){
            data.users.push( data.creator);
        }
    } else if(data.creator !== "" && typeof data.creator !== "undefined") { 
       data.users = [];    
       data.users.push(data.creator);
    }else {
       data.users = [];
    }

    //Retrieve bonita user ids from user ids
    $.get(location.origin + "/workflow/get_bonitaids_from_uids", {uids : data.users}, function(response){
        response = Object.values(JSON.parse(response));

        //Retrieve again form data
        var form_data = $("#gofast-workflow-dashboard-search-form").serializeArray();
        var data = {};
        form_data.forEach(function(e){
            data[e.name.split("-").pop()] = e.value;
        });

        //So we have the creator and the users bonita ids
        if(data.creator !== "" && typeof data.creator !== "undefined") {
            data.creator = response.shift();
        }

        data.users = response;

        //We have an array of node ids corresponding to the wanted documents
        if(data['ac-list-tags-list-documents'] !== "" && typeof data['ac-list-tags-list-documents'] !== "undefined") {
            data.documents = JSON.parse(data['ac-list-tags-list-documents']).map(document => document.value);
        } else {
            data.documents = [];
        }

        //Translate french format to english if needed and set them to proper date format
        var userlang = Gofast.get('user').language;
        if(data.started !== ""){
            data.started = moment(data.started, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).toDate();
            data.started.setTime(data.started.getTime() + (2*60*60*1000));
            data.started = data.started.toISOString();
        }

        if(data.deadline !== ""){
            data.deadline =  moment(data.deadline, GofastConvertDrupalDatePattern("moment", Drupal.settings.date_format_short, false)).toDate();
            data.deadline.setTime(data.deadline.getTime() + (2*60*60*1000));
            data.deadline = data.deadline.toISOString();
        }

        //Jsonify users and documents
        data.users = JSON.stringify(data.users);
        data.documents = JSON.stringify(data.documents);

        //Find custom data
        var custom = [];
        for(var i in data){
            if(i.indexOf("custom_") === 0){
                custom.push(data[i]);
            }
        }
        data.custom = JSON.stringify(custom);

        //Process the form to bonita
        Gofast.gofast_workflow_search_execute(data);
    });

};

Gofast.gofast_workflow_save_filters = function(form_data){
    $.cookie('gofast_workflow_dashboard_filters', JSON.stringify(form_data));
}

Gofast.gofast_workflow_apply_filters = function(){
    var form_data = [];
    var search_form = $("form[id^=\"gofast-workflow-dashboard-search-form\"]");
    var search_cookie_filters = $.cookie('gofast_workflow_dashboard_filters')
    
    if(search_cookie_filters){
        form_data = JSON.parse(search_cookie_filters);
    }
    
    form_data.forEach(function(e){
        if(e.name == "form_build_id" || e.name == "form_token" || e.name == "form_id" || e.name == "ac-list-tags-list-creator" || e.name == "ac-list-tags-list-documents" || e.name == "ac-list-tags-list-users"){ 
            return; 
        }
        
        search_form.find('[name="' + e.name + '"]').val(e.value).trigger('change');
    });
}

Gofast.gofast_workflow_search_execute = function(params){
    jQuery("#ajax_content").append("<style>.main-container{width: 90%;}</style>");
    Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
        var iframe = $("#bonita_full_dashboard_search");

        var userlang = Gofast.get('user').language;

        if(params !== null && typeof params !== "undefined"){
            //Encode arrays for IE
            params.documents = encodeURIComponent(params.documents);
            params.users = encodeURIComponent(params.users);
            params.custom = encodeURIComponent(params.custom);
            params.type = encodeURIComponent(params.type);

            params = $.param(params);
        }else{
            return;
        }

        iframe.prop("src", "/bonita/portal/resource/app/GoFAST/fullDashboardSearch/content/?app=GoFAST&locale=" + userlang + "&" + params);
    });
};

Gofast.gofast_workflow_show_details = function(pid, type, title, hid, documents){
    Gofast.addLoading();
    window.scrollTo(0, 0);
    jQuery("#ajax_content").append("<style>.main-container{width: 90%;}</style>");
    history.pushState({page: 1}, Drupal.t("Workflows dashboard", {}, {context: "gofast:gofast_workflows"}), "#details");
    $("#workflows-dashboard-search").hide();
    $("#workflows-dashboard-details").show();

    //Set breadcrumb
    $(".breadcrumb-gofast").html("<a href='#' onClick='Gofast.gofast_workflow_dashboard_back();'>" + Drupal.t("Workflows dashboard", {}, {context: "gofast:gofast_workflows"}) + "</a> >> " + type + " >> <strong>" + title + "</strong>");

    //Get user language
    var userlang = Gofast.get('user').language;

    //Set iframes src
    Drupal.gofast_workflows.ceo_vision_js_check_login(function(){
        $("#workflows-dashboard-tasks").prop("src", "/bonita/portal/resource/app/GoFAST/tasksInProcess/content/?app=GoFAST&pid=" + pid + "&locale="+ userlang);
        $("#workflows-dashboard-history").prop("src", "/bonita/portal/resource/app/GoFAST/historyBdm/content/?app=GoFAST&persistenceId=" + hid + "&locale=" + userlang);

        Gofast.removeLoading();

        $.get(location.origin + "/api/node/links?dashboard=true&nids=" + documents.join(","), function(response){
            $("#workflows-dashboard-documents").html(response.content);
    });

        //Call hooks after displaying te workflow details to allow modules to alter the view
        if(typeof Gofast.hooks.gofast_workflows.hook_after_display_search_details == "object"){
            for(var i in Gofast.hooks.gofast_workflows.hook_after_display_search_details){
                if(typeof Gofast.hooks.gofast_workflows.hook_after_display_search_details[i] == "function"){
                    Gofast.hooks.gofast_workflows.hook_after_display_search_details[i](pid, type, title, hid, documents);
                }
            }
        }
    });
};

Gofast.gofast_workflow_dashboard_back = function(){
    Gofast.addLoading();
    window.scrollTo(0, 0);
    $("#workflows-dashboard-search").show();
    $("#workflows-dashboard-details").hide();

    $(".breadcrumb-gofast").html(Drupal.t("Workflows dashboard", {}, {context: "gofast:gofast_workflows"}));
    Gofast.removeLoading();
};

  /*
   * Handle the downloading of stats
   */
  Gofast.download_workflow_fields = function(e){
    Gofast.modal('<div class="loader-sync-status"></div> ' + Drupal.t("Please hold on while your export is being generating. This process may take a few minutes.", {}, {context : "gofast_stats"}), Drupal.t("Your export is being generating", {}, {context : "gofast_stats"}), { allowStretch: true });
    //Check filters
    
    if(typeof e === "object"){
        e.preventDefault();
    }
    
    //Retrieve form data
    var form_data = $("form[id^=\"gofast-workflow-dashboard-search-form\"]").serializeArray();
    var data = {};
    form_data.forEach(function(e){
	    data[e.name.split("-").pop()] = e.value;
    });

    if(data.creator !== "" && typeof data.creator !== "undefined"){
        data.creator = JSON.parse(data.creator)[0].value;
    }

    //Prepare an array with the creator and the users to turn them into bonita ids
    if(data.users !== "" && typeof data.users !== "undefined"){
        data.users = JSON.parse(data.users).map(user => user.value);
        if(data.creator !== "" && typeof data.creator !== "undefined"){
            data.users[0] = data.creator;
        }
    } else if(data.creator !== "" && typeof data.creator !== "undefined") { 
       data.users = [];    
       data.users[0] = data.creator;
    }else {
       data.users = [];
    }

    $.post(location.origin + "/gofast_workflow_dashboard_export", data, function(fid){
        var downloadInterval = setInterval(function(){
            $.get(location.origin + "/gofast_workflow_dashboard_export_check?fid=" + fid, function(file){
               if(file !== "Waiting"){
                   clearInterval(downloadInterval);
                   Gofast.closeModal();
                   window.location = location.origin + "/gofast_workflow_dashboard_export_check?fid=" + fid;
               } 
            });
        }, 1000); 
    });
    
};


//Init hooks
Gofast.hooks.gofast_workflows = [];
Gofast.hooks.gofast_workflows.hook_after_display_search_details = [];

})(jQuery, Gofast, Drupal);



