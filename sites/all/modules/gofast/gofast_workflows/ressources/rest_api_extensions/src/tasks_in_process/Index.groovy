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
import org.bonitasoft.engine.bpm.flownode.ArchivedHumanTaskInstance;



public class Index implements RestApiController {

    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder apiResponseBuilder, RestAPIContext context) {

       // get the list of all Business Data
       APIClient apiClient = context.apiClient;
       ProcessAPI processAPI = apiClient.processAPI;
       Map<String, String> response = [:]
       int responseCode = 201;
       def pid = request.getParameter "pid"
        if (pid == null) {      
            response.with {
                put "response","Error : the parameter pid is missing"           
            }  
            responseCode = 500;
        }
		
		def finalListHumanTaskInstance = [];
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
            // Convert parameters from string to int
            pid = pid as int
	 	   
				final SearchOptionsBuilder builder = new SearchOptionsBuilder(0, 100);
				builder.filter(HumanTaskInstanceSearchDescriptor.PROCESS_INSTANCE_ID , pid);
				final SearchResult<HumanTaskInstance> humanTaskInstanceResults = processAPI.searchHumanTaskInstances(builder.done());
			
				humanTaskInstanceResults.result.each {
				
					def myTask = [:];
                                        
					myTask.id = it.id;
					myTask.start = it.claimedDate;
					myTask.name = it.displayName;
					myTask.assigneeId = it.assigneeId;
					myTask.state = it.state;
                                        
					finalListHumanTaskInstance.push(myTask);
				}
                                
                                final SearchOptionsBuilder builder2 = new SearchOptionsBuilder(0, 100);
				builder2.filter(HumanTaskInstanceSearchDescriptor.PROCESS_INSTANCE_ID , pid);
				final SearchResult<ArchivedHumanTaskInstance> archivedHumanTaskInstanceResults = processAPI.searchArchivedHumanTasks(builder2.done());
			
				archivedHumanTaskInstanceResults.result.each {
				
					def myTask = [:];
					
					myTask.id = it.id;
					myTask.start = it.claimedDate;
                                        myTask.done = it.archiveDate;
					myTask.name = it.displayName;
					myTask.assigneeId = it.assigneeId;
					myTask.state = it.state;
                                        
					finalListHumanTaskInstance.push(myTask);
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
				put "response",new JsonBuilder(finalFinalListHumanTaskInstance);
                                put "pagination", range_string
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