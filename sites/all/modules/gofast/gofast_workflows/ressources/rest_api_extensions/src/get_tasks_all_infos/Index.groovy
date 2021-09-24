import groovy.json.JsonBuilder

import org.bonitasoft.web.extension.rest.*
import org.apache.http.HttpHeaders;
import org.bonitasoft.engine.api.APIClient;
import org.bonitasoft.engine.api.BusinessDataAPI;
import org.bonitasoft.engine.api.IdentityAPI;
import org.bonitasoft.engine.api.ProcessAPI;
import org.bonitasoft.engine.api.ProfileAPI;
import org.bonitasoft.engine.api.APIAccessor;
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
import org.bonitasoft.engine.bpm.flownode.ActivityInstance;
import org.bonitasoft.engine.api.ProcessRuntimeAPI;
import org.bonitasoft.engine.bpm.process.ProcessInstance;
import org.bonitasoft.engine.bpm.process.ProcessDefinition;
import com.company.model.ProcessCurrent;
import com.company.model.ProcessCurrentDAO;
import com.company.model.ProcessHistory;
import com.company.model.ProcessHistoryDAO;


public class Index implements RestApiController {

    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder apiResponseBuilder, RestAPIContext context) {

       APIClient apiClient = context.apiClient;
	   
       ProcessAPI processAPI = apiClient.processAPI;
	   
       Map<String, String> response = [:]
       int responseCode = 201;
       def taskids = request.getParameter "taskids"
        if (taskids == null) {      
            response.with {
                put "response","Error : the parameter taskids is missing"           
            }  
            responseCode = 500;
        }
		
		def finalListHumanTaskInstance = [];

		def current_user_id = apiClient.session.getUserId();
	  
	   
        try{
            def taskids_array = taskids.split('-');
			
			
			taskids_array.each{
                                        if(it == "kanban"){
                                            def myTask = [:];
                                            
                                            myTask.type = "kanban";
                                            
                                            finalListHumanTaskInstance.push(myTask);
                                        }else{
                                            it = it as int;

                                            //load task object
                                            ActivityInstance myTaskInstance = processAPI.getActivityInstance(it);                                                                         
                                            //load corresponding processDefinitition
                                            ProcessInstance myProcessInstance = processAPI.getProcessInstance(myTaskInstance.rootContainerId);
                                            ProcessDefinition myProcessDefinition = processAPI.getProcessDefinition(myProcessInstance.processDefinitionId);

                                            ProcessInstance myProcessInstanceSub = processAPI.getProcessInstance(myTaskInstance.parentProcessInstanceId);
                                            ProcessDefinition myProcessDefinitionSub = processAPI.getProcessDefinition(myProcessInstanceSub.processDefinitionId);



                                            //Load ProcessCurrent and ProcessHistory
                                            def ProcessCurrentDAO = apiClient.getDAO(ProcessCurrentDAO.class)       									
                                            def processCurrent = ProcessCurrentDAO.findByPid(myTaskInstance.rootContainerId.toString(), 0, 10);
                                            def ProcessHistoryDAO = apiClient.getDAO(ProcessHistoryDAO.class)       									
                                            def processHistory = ProcessHistoryDAO.findByPid(myTaskInstance.rootContainerId.toString(), 0, 10);


                                            def myTask = [:];

                                            myTask.processDefinitionId = myTask.processId = myTaskInstance.processDefinitionId.toString();
                                            myTask.rootCaseId = myTaskInstance.rootContainerId
                                            myTask.parentCaseId = myTaskInstance.parentContainerId
                                            myTask.assigneeId = myTaskInstance.assigneeId;
                                            myTask.assigned_id = myTaskInstance.assigneeId;
                                            myTask.flownodeDefinitionId = myTaskInstance.flownodeDefinitionId.toString();;
                                            myTask.id = myTaskInstance.id;
                                            myTask.parentProcessInstanceId = myTaskInstance.parentProcessInstanceId.toString();
                                            myTask.parentContainerId = myTaskInstance.parentContainerId;
                                            myTask.actorId = myTaskInstance.actorId;
                                            myTask.claimedDate = myTaskInstance.claimedDate;
                                            myTask.reachedStateDate = myTaskInstance.reachedStateDate;
                                            myTask.stateCategory = myTaskInstance.stateCategory;					
                                            myTask.displayDescription = myTaskInstance.displayDescription;
                                            myTask.name = myTaskInstance.name;
                                            myTask.priority = myTaskInstance.priority;
                                            myTask.executedByDelegate = myTaskInstance.executedByDelegate;
                                            myTask.rootContainerId = myTaskInstance.rootContainerId;
                                            myTask.type = myTaskInstance.type;				
                                            myTask.executedBy = myTaskInstance.executedBy;
                                            myTask.executedBySubstitute = myTaskInstance.executedBySubstitute;
                                            myTask.expectedEndDate = myTaskInstance.expectedEndDate;
                                            myTask.description = myTaskInstance.description;
                                            myTask.state = myTaskInstance.state;
                                            myTask.lastUpdateDate = myTaskInstance.lastUpdateDate;

                                            myTask.processInstance = myProcessInstance;	
                                            myTask.processInstanceId = myTask.processInstance.processDefinitionId.toString();
                                            myTask.processDefinitition = myProcessDefinition;
                                            myTask.processInstanceSub = myProcessInstanceSub;	
                                            myTask.processDefinititionSub = myProcessDefinitionSub;

                                            //check if the user is eligible for this task or not 
                                            def is_eligible = 0;
                                            if(myTask.assigneeId == 0){

                                                    def all_users = processAPI.getPossibleUsersOfHumanTask(myProcessInstanceSub.processDefinitionId, myTask.name, 0, 100);
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

                                            //if it's an old task process, retrieve process data differently

                                            if(processHistory.size() > 0){
                                                    myTask.processHistory = processHistory[0];
                                            }else{
                                                    def fakeProcessHistory = [:];

                                                    List<DataInstance> listDataInstance = processAPI.getProcessDataInstances(myTaskInstance.rootContainerId, 0,1000);
                                                    fakeProcessHistory.title = 	myTask.name;				
                                                    listDataInstance.each{
                                                            if(it.name == "gofast_titre_processus"){
                                                                    fakeProcessHistory.title = it.value;
                                                            }
                                                    }

                                                    fakeProcessHistory.initiator = myProcessInstance.startedBy.toString();
                                                    fakeProcessHistory.start_date = myProcessInstance.startDate;
                                                    myTask.processHistory = fakeProcessHistory;
                                            }
                                            if(processCurrent.size() > 0){
                                                    myTask.processCurrent = processCurrent[0];
                                            }else{

                                                    def documents = [];
                                                    def fakeProcessCurrent = [:];						
                                                    List<DataInstance> listDataInstance = processAPI.getProcessDataInstances(myTaskInstance.rootContainerId, 0,1000);
                                                    listDataInstance.each{
                                                            if(it.name == "gofast_document_reference"){
                                                                    documents.add(it.value);
                                                            }
                                                            if(it.name == "gofast_date_limite"){
                                                                    fakeProcessCurrent.end_date = it.value;
                                                            }

                                                    }

                                                    fakeProcessCurrent.documents = documents;
                                                    myTask.processCurrent = fakeProcessCurrent;

                                            }

                                            finalListHumanTaskInstance.push(myTask);				
                                        }
			}
		   
		    response.with {
					put "response",new JsonBuilder(finalListHumanTaskInstance)       
			}
           
         } catch(Exception ex) {
             response.with {
                put "response","Error :"+ex        
            } 
            responseCode = 500;  
        }
       

        apiResponseBuilder.with {
            withResponse(new JsonBuilder(response).toPrettyString())           
            withResponseStatus(responseCode)
            build()
        }
    }
}