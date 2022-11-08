package rest.controller
import groovy.json.JsonBuilder

import org.bonitasoft.web.extension.rest.*
import org.apache.http.HttpHeaders;
import org.bonitasoft.engine.api.APIClient;
import org.bonitasoft.engine.api.BusinessDataAPI;
import org.bonitasoft.engine.api.IdentityAPI;
import org.bonitasoft.engine.api.ProcessAPI;
import org.bonitasoft.engine.api.ProfileAPI;
import org.bonitasoft.engine.bdm.Entity;
import org.bonitasoft.engine.bdm.dao.BusinessObjectDAO;
import org.bonitasoft.engine.bpm.data.ArchivedDataInstance;
import org.bonitasoft.engine.bpm.data.ArchivedDataNotFoundException;
import org.bonitasoft.engine.bpm.data.DataInstance;
import org.bonitasoft.engine.bpm.data.DataNotFoundException;
import org.bonitasoft.engine.bpm.document.Document;
import org.bonitasoft.engine.bpm.document.ArchivedDocument;
import org.bonitasoft.engine.bpm.document.ArchivedDocumentsSearchDescriptor;
import org.bonitasoft.engine.bpm.document.DocumentCriterion;
import org.bonitasoft.engine.bpm.document.DocumentDefinition;
import org.bonitasoft.engine.bpm.document.DocumentListDefinition;
import org.bonitasoft.engine.bpm.flownode.FlowElementContainerDefinition;
import org.bonitasoft.engine.bpm.parameter.ParameterCriterion;
import org.bonitasoft.engine.bpm.parameter.ParameterInstance;
import org.bonitasoft.engine.bpm.process.DesignProcessDefinition;
import org.bonitasoft.engine.business.data.BusinessDataReference;
import org.bonitasoft.engine.business.data.MultipleBusinessDataReference;
import org.bonitasoft.engine.business.data.SimpleBusinessDataReference;
import org.bonitasoft.engine.session.APISession;
import org.bonitasoft.web.extension.rest.RestAPIContext;
import org.bonitasoft.web.extension.rest.RestApiController;
import org.bonitasoft.web.extension.rest.RestApiResponse;
import org.bonitasoft.web.extension.rest.RestApiResponseBuilder;
import org.bonitasoft.engine.search.SearchOptionsBuilder;
import org.bonitasoft.engine.search.SearchResult;
import javax.servlet.http.HttpServletRequest
import org.bonitasoft.engine.bpm.process.ProcessInstance;
import org.bonitasoft.engine.bpm.process.ProcessInstanceSearchDescriptor;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstanceSearchDescriptor;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstance;
import java.text.SimpleDateFormat; 
import java.text.DateFormat;
import java.util.Date;



public class Index implements RestApiController {

    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder apiResponseBuilder, RestAPIContext context) {

       // get the list of all Business Data
       APIClient apiClient = context.apiClient;
       ProcessAPI processAPI = apiClient.processAPI;
       Map<String, String> response = [:]
       int responseCode = 201;
       def caseids = request.getParameter "caseids"
        if (caseids == null) {      
            response.with {
                put "response","Error : the parameter caseids is missing"           
            }  
            responseCode = 500;
        }
		
	    def assignid = request.getParameter "assignid"
        if (assignid == null) {      
            response.with {
                put "response","Error : the parameter assignid is missing"           
            }  
            responseCode = 500;
        }
		
		def notassignid = request.getParameter "notassignid"
        if (notassignid == null) {      
            response.with {
                put "response","Error : the parameter notassignid is missing"           
            }  
            responseCode = 500;
        }
		
		def finalListHumanTaskInstance = [];
		def current_user_id = apiClient.session.getUserId();
                def finalFinalListHumanTaskInstance = [];

		//get pagination params
		def p = request.getParameter "p"
                if (p != null) {
                     p = p as int
                }
		def c = request.getParameter "c"
                if (c != null) {
                    c = c as int
                }

		def range_string = "0-0/0";
		
        try{
            // Convert parameters from string to array
            def caseids_array = caseids.split('-');
			assignid = assignid as int
			notassignid = notassignid as int
			
			caseids_array.each{
				final SearchOptionsBuilder builder2 = new SearchOptionsBuilder(0, 100);
				builder2.filter(HumanTaskInstanceSearchDescriptor.PROCESS_INSTANCE_ID , it);
                                //builder2.sort(HumanTaskInstanceSearchDescriptor.EXPECTED_END_DATE , "ASC");
				final SearchResult<HumanTaskInstance> humanTaskInstanceResults = processAPI.searchHumanTaskInstances(builder2.done());
			
				humanTaskInstanceResults.result.each {
				
					def myTask = [:];
					
					myTask.processDefinitionId = myTask.processId = it.processDefinitionId.toString();
					myTask.rootCaseId = it.rootContainerId                                     
					myTask.parentCaseId = it.parentContainerId
					myTask.assigneeId = it.assigneeId;
					myTask.assigned_id = it.assigneeId;
					myTask.flownodeDefinitionId = it.flownodeDefinitionId.toString();;
					myTask.id = it.id;
					myTask.parentProcessInstanceId = it.parentProcessInstanceId.toString();
					myTask.parentContainerId = it.parentContainerId;
					myTask.actorId = it.actorId;
					myTask.claimedDate = it.claimedDate;
					myTask.reachedStateDate = it.reachedStateDate;
					myTask.stateCategory = it.stateCategory;
					myTask.displayDescription = it.displayDescription;
					myTask.name = it.name;
					myTask.priority = it.priority;
					myTask.executedByDelegate = it.executedByDelegate;
					myTask.rootContainerId = it.rootContainerId;
					myTask.type = it.type;				
					myTask.executedBy = it.executedBy;
					myTask.executedBySubstitute = it.executedBySubstitute;
					myTask.expectedEndDate = it.expectedEndDate;
					myTask.description = it.description;
					myTask.state = it.state;
					myTask.lastUpdateDate = it.lastUpdateDate;

                                        if(it.expectedEndDate != null){
                                            DateFormat dateFormat = new SimpleDateFormat("EEE MMM dd HH:mm:ss zzz yyyy");
                                            def mydate = dateFormat.parse(it.expectedEndDate.toString());
                                            def newDate = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss").format(mydate) 
                                            myTask.dueDate = newDate;
                                            myTask.dueDateTimestamp = dateFormat.parse(mydate.toString()).getTime();
                                            myTask.dueDateTimestamp = myTask.dueDateTimestamp / 1000;
                                        }else{
                                            myTask.dueDateTimestamp = "";
                                        }
					def is_eligible = 0;
					if(myTask.assigneeId == 0){
						
						def all_users = processAPI.getPossibleUsersOfHumanTask(it.processDefinitionId, myTask.name, 0, 100);
						all_users.each{
							if(it.id == current_user_id){
								is_eligible = 1;
							}
						}
					}
					if(myTask.assigneeId == current_user_id){
						is_eligible = 1;
					}
					myTask.is_eligible = is_eligible;
					
					if(assignid != 0){
						if(it.assigneeId == assignid || is_eligible == 1){
							finalListHumanTaskInstance.push(myTask);
						}
					}
					
					if(notassignid != 0){
						if(it.assigneeId != notassignid && is_eligible == 0){
							finalListHumanTaskInstance.push(myTask);
						}
					}
					
				}
			}



                           //build range string
                    if (p != null && c != null) { 
                        def total_number = finalListHumanTaskInstance.size();
                        range_string = "0-0/"+total_number.toString();
                        //extract finalListHumanTaskInstance resultats using pagination params
                        //calculate first index
                        def first_index = p*c;
                        def last_index = first_index+c;

                        def i = 0;
                        def pager = finalListHumanTaskInstance;
                        finalListHumanTaskInstance.each{                           
                             if(i >= first_index && i < last_index){                               
                                 finalFinalListHumanTaskInstance.push(it);                              
                             }
                             i++;
                        }
                    }else{
                        finalFinalListHumanTaskInstance = finalListHumanTaskInstance;
                    }
		   
		    response.with {
					put "response",new JsonBuilder(finalFinalListHumanTaskInstance)       
			}
           
         } catch(Exception ex) {
             response.with {
                put "response","Error :"+ex        
            } 
            responseCode = 500;  
        }
       

        apiResponseBuilder.with {
            withAdditionalHeader("Content-Range", range_string)
            withResponse(new JsonBuilder(response).toPrettyString())           
            withResponseStatus(responseCode)
            build()
        }
    }
}