package com.ceovision.rest.api;

import groovy.json.JsonBuilder

import javax.servlet.http.HttpServletRequest
import javax.servlet.http.HttpServletResponse

import org.apache.http.HttpHeaders
import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.client.methods.HttpPost
import org.apache.http.entity.StringEntity
import org.bonitasoft.engine.api.APIClient;
import org.bonitasoft.engine.api.IdentityAPI
import org.bonitasoft.engine.api.ProcessRuntimeAPI
import org.bonitasoft.engine.bpm.flownode.ActivityInstance
import org.bonitasoft.engine.exception.UpdateException
import org.bonitasoft.engine.identity.User
import org.bonitasoft.engine.identity.Group
import org.bonitasoft.web.extension.ResourceProvider
import org.bonitasoft.web.extension.rest.RestApiResponse
import org.bonitasoft.web.extension.rest.RestApiResponseBuilder
import java.util.logging.Logger;

import org.bonitasoft.web.extension.rest.RestAPIContext
import org.bonitasoft.web.extension.rest.RestApiController

import java.time.LocalDate
import groovy.json.JsonOutput

class Index implements RestApiController {
    @Override
    RestApiResponse doHandle(HttpServletRequest request, RestApiResponseBuilder responseBuilder, RestAPIContext context) {
		Logger logger = Logger.getLogger("org.bonitasoft");

        // Retrieve taskids parameter
        def taskIds = request.getParameter("taskids");
		if (taskIds == null) {
			return buildResponse(responseBuilder, HttpServletResponse.SC_BAD_REQUEST,"""{"error" : "the parameter 'taskids' is missing"}""")
        }
		def tasksList = taskIds.split(",");
		def targetUserId = request.getParameter("userid");		
		
		APIClient apiClient = context.apiClient;
		ProcessRuntimeAPI processAPI = apiClient.processAPI;
        IdentityAPI identityAPI = apiClient.identityAPI;
		def currentUserId = apiClient.session.getUserId();
		try {
			tasksList.each {
				logger.info("Trying to update actors of user task ${it}");
				Long taskId = Long.parseLong(it);
                // We don't make any change regarding the target actor if the current user is not allowed to execute the task
				Boolean canExecuteTask = processAPI.canExecuteTask(taskId, currentUserId);
				if (canExecuteTask && targetUserId != null) {
					// We need to update a subprocess and a task variable for updateActorsOfUserTask to do the magic
					ActivityInstance userTask = processAPI.getActivityInstance(taskId);
					processAPI.updateProcessDataInstance("login",  userTask.parentProcessInstanceId, targetUserId);
					processAPI.updateActivityDataInstance("assignee", taskId, targetUserId);
					// Update history
					User currentUser = identityAPI.getUser(currentUserId)
					String userName = currentUser.getUserName();
					String userDisplayName = currentUser.firstName + " " + currentUser.lastName;
					String targetUserDisplayName = "";
                    // In case it's a userlist, we parse the data a bit differently
					if (targetUserId.startsWith("ul_")) {
						Group targetUserlist = identityAPI.getGroupByPath(targetUserId);
						targetUserDisplayName = targetUserlist.displayName;
					} else {
						if (targetUserId.isNumber()) {
							User targetUser = identityAPI.getUser(Long.parseLong(targetUserId));
							targetUserId = targetUser.getUserName();
							targetUserDisplayName = targetUser.firstName + " " + targetUser.lastName;
						} else {
							User targetUser = identityAPI.getUserByUserName(targetUserId);
							targetUserId = targetUser.getUserName();
							targetUserDisplayName = targetUser.firstName + " " + targetUser.lastName;
						}
					}
                    // Get all the data needed for the history update request
					String userJsonString = '{"username": "'+targetUserId+'", "displayname" : "'+targetUserDisplayName+'"}';
					def currentDate = new Date();
					String currentDateString = currentDate.getTime().toString();
					String taskDisplayName = userTask.displayName;
					String taskObject = '{"id": '+taskId+', "type": "userTask", "step": "task_assigned", "name": "A task has been reassigned", "description" : "'+ taskDisplayName +'", "new_actor_displayname": "'+ targetUserDisplayName+'", "new_actor_login": "'+ targetUserId + '", "actor_displayname": "'+userDisplayName+'", "actor_login": "'+userName+'", "date" : "'+currentDateString+'"}';
					String urlAddLineToHistory = "http://localhost/api/workflows/insert_line_to_history";
					def dataMap = [
						"current_user": currentUser.userName,
						"case_id": userTask.rootContainerId,
						"user_object": userJsonString,
						"task_id": taskId,
						"line_date": currentDateString,
						"task_object": taskObject,
					];
					def jsonString = JsonOutput.toJson(dataMap)
                    // Make the actual request to update the history
                    HttpClient client = HttpClientBuilder.create().build();
					HttpPost requestPost = new HttpPost(urlAddLineToHistory);
					requestPost.addHeader("Content-Type", "application/json");
					StringEntity entity = new StringEntity(jsonString);
					requestPost.setEntity(entity);
					client.execute(requestPost);
				}
                // Will update the assignments relying on the actor filter on the task
				processAPI.updateActorsOfUserTask(taskId);
			}
		} catch(UpdateException e) {
			logger.severe("Error on updating a user task: ${e.getMessage()}");
		}

        // Send the result as a JSON representation
        // You may use buildPagedResponse if your result is multiple
        return buildResponse(responseBuilder, HttpServletResponse.SC_OK, new JsonBuilder([message: "OK"]).toPrettyString())
    }

    /**
     * Build an HTTP response.
     *
     * @param  responseBuilder the Rest API response builder
     * @param  httpStatus the status of the response
     * @param  body the response body
     * @return a RestAPIResponse
     */
    RestApiResponse buildResponse(RestApiResponseBuilder responseBuilder, int httpStatus, Serializable body) {
        return responseBuilder.with {
            withResponseStatus(httpStatus)
            withResponse(body)
            build()
        }
    }
}
