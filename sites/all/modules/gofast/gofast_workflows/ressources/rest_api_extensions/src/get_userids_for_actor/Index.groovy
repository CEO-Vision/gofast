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
       def processDefinitionId = request.getParameter "processDefinitionId"
        if (processDefinitionId == null) {      
            response.with {
                put "response","Error : the parameter processDefinitionId is missing"           
            }  
            responseCode = 500;
        } 

		def actorName = request.getParameter "actorName"
        if (actorName == null) {      
            response.with {
                put "response","Error : the parameter actorName is missing"           
            }  
            responseCode = 500;
        } 		
		
		def finalListUsers = [];
		
        try{
			// Convert parameter from string to long
            processDefinitionId = processDefinitionId as long
			
			def all_users = processAPI.getUserIdsForActor(processDefinitionId, actorName, 0, 9999999);
			all_users.each{
				def myuser = [:];
				def actor =  apiClient.identityAPI.getUser(it);
				myuser.login = actor.userName;
				myuser.displayname = actor.firstName + " " + actor.lastName;
				finalListUsers.push(myuser);
			}
						   
		    response.with {
					put "response",new JsonBuilder(finalListUsers)       
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