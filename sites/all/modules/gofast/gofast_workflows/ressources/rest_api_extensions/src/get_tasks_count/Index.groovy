package rest.controller
import groovy.json.JsonBuilder

import org.bonitasoft.web.extension.rest.*;
import org.bonitasoft.engine.api.APIClient;
import org.bonitasoft.engine.api.ProcessAPI;
import javax.servlet.http.HttpServletRequest;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstanceSearchDescriptor;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstance;
import org.bonitasoft.engine.bpm.flownode.ActivityInstanceCriterion;






public class Index implements RestApiController {

    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder apiResponseBuilder, RestAPIContext context) {

       // get the list of all Business Data
       APIClient apiClient = context.apiClient;
       ProcessAPI processAPI = apiClient.processAPI;
       Map<String, String> response = [:]
       int responseCode = 201;
      
				
		def finalListHumanTaskInstance = [];
		def current_user_id = apiClient.session.getUserId();
		
        try{

		  // def count = apiClient.processAPI.getNumberOfPendingHumanTaskInstances(current_user_id);
           def count = apiClient.processAPI.getNumberOfAssignedHumanTaskInstances(current_user_id);
		   final int limit = (int) 1;
		   final List<HumanTaskInstance> userTaskInstances =  apiClient.processAPI.getAssignedHumanTaskInstances(current_user_id, 0, limit, ActivityInstanceCriterion.REACHED_STATE_DATE_DESC);
		    response.with {
					put "count",count       
			}
             response.with {
					put "uid",current_user_id       
			}
			response.with {
					put "last_task_id",userTaskInstances[0].getId().toString();     
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
