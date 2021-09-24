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
import org.bonitasoft.engine.api.ProcessRuntimeAPI;

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


        try{
            // Convert parameters from string to int
            pid = pid as int
            List<ArchivedDataInstance> listDataInstance = processAPI.getArchivedProcessDataInstances(pid, 0,1000);
            response.with {
                put "response",new JsonBuilder(listDataInstance).toPrettyString()            
            }
         } catch(Exception ex) {
             response.with {
                put "response","Error : bad pid"           
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