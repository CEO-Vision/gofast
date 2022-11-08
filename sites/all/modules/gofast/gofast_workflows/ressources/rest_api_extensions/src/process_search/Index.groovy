package rest.controller
import groovy.json.JsonBuilder
import groovy.json.JsonSlurper
import groovy.json.JsonOutput

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
import org.bonitasoft.engine.bpm.process.ArchivedProcessInstance;
import org.bonitasoft.engine.bpm.process.ProcessInstanceSearchDescriptor;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstanceSearchDescriptor;
import org.bonitasoft.engine.bpm.flownode.HumanTaskInstance;
import org.bonitasoft.engine.bpm.flownode.ArchivedHumanTaskInstance;
import com.company.model.ProcessCurrent;
import com.company.model.ProcessCurrentDAO;
import com.company.model.ProcessHistory;
import com.company.model.ProcessHistoryDAO;
import java.text.Normalizer;

import java.util.logging.Logger;

public class Index implements RestApiController {
    
    public static String stripAccents(String s) 
    {
        s = Normalizer.normalize(s, Normalizer.Form.NFKD);
        s = s.replaceAll("[\\p{InCombiningDiacriticalMarks}]", "");
        return s;
    }

    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder apiResponseBuilder, RestAPIContext context) {
        Logger logger= Logger.getLogger("org.bonitasoft");
        APIClient apiClient = context.apiClient;
        Map<String, String> response = [:];
        int responseCode = 201;
        def range_string = "0-0/0";
        
        //GOFAST-6499 : Major part of the code has been moved to a GoFAST API for performance reasons
        //This API now just calls for the GoFAST API (Ressource : workflows; Action : dashboard)

        //Prepare parameters to send to GoFAST
        def p = request.getParameter "p"
        def c = request.getParameter "c"
            
        if (p != null) {
            p = p as int
        }
        
        if (c != null) {
            c = c as int
        }
        
        def startedby = request.getParameter "creator";
        def type = request.getParameter "type";
        def state = request.getParameter "state";
        def title = request.getParameter "title";
        def started = request.getParameter "started";
        def deadline = request.getParameter "deadline";
        def documents = request.getParameter "documents";
        def users = request.getParameter "users";
        def custom = request.getParameter "custom";
        def current_user = apiClient.session.getUserId().toString();

        def url_string = "http://localhost/api/workflows/dashboard?p=" + p + "&c=" + c + "&startedby=" + startedby + "&type=" + type + "&state=" + state + "&title=" + title + "&started=" + started + "&deadline=" + deadline + "&documents=" + documents + "&users=" + users + "&current_user=" + current_user + "&custom=" + custom;
        url_string = url_string.replaceAll(" ", "%20");
        URL url = new URL(url_string);
        String content = url.getText();
            
        def results = new JsonSlurper().parseText(content.trim());
            
        //Paginate
        def total_number = results.size();
        def first_index = p*c;
        def last_index = first_index+c;
        range_string = first_index.toString() + "-" + last_index.toString() + "/" + "9999999";
            
        //Render the results
        response.with {
            put "response",new JsonBuilder(results)
            put "pagination",range_string
        }
        
        //Build the response and send it
        apiResponseBuilder.with {
	    withAdditionalHeader("Content-Range", range_string)
            withResponse(new JsonBuilder(response).toPrettyString())           
            withResponseStatus(responseCode)
			
            build()
        }
    }
}