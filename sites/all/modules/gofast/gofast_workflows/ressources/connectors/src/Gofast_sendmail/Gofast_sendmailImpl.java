/**
 * 
 */
package org.mycompany.connector;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.bonitasoft.engine.connector.ConnectorException;
import org.json.simple.JSONObject;


/**
 *The connector execution will follow the steps
 * 1 - setInputParameters() --> the connector receives input parameters values
 * 2 - validateInputParameters() --> the connector can validate input parameters values
 * 3 - connect() --> the connector can establish a connection to a remote server (if necessary)
 * 4 - executeBusinessLogic() --> execute the connector
 * 5 - getOutputParameters() --> output are retrieved from connector
 * 6 - disconnect() --> the connector can close connection to remote server (if any)
 */
public class Gofast_sendmailImpl extends AbstractGofast_sendmailImpl {

	@SuppressWarnings("unchecked")
	@Override
	protected void executeBusinessLogic() throws ConnectorException{
		//Get access to the connector input parameters
		//getDestinataire();
		//getSujet();
		//getMessage();
		//getNotifier_auteur();
		//getSujet_auteur();
		//getMessage_auteur();
	
		//TODO execute your business logic here 
		Long processInstanceId = getExecutionContext().getProcessInstanceId();
		
		//try{
			Boolean Notify_author = getNotifier_auteur();
			String Notify_author_string = "false";
			if(Notify_author){
				Notify_author_string = "true";
			}
			
			String login = getDestinataire();
			String message_iso = getMessage();
			String message = "";
			try {
				message = new String(message_iso.getBytes(), Charset.forName("UTF-8"));
			} catch (Exception e4) {
				// TODO Auto-generated catch block
				e4.printStackTrace();
			}
			String subject_iso = getSujet();
			String subject = "";
			try {
				subject = new String(subject_iso.getBytes(), Charset.forName("UTF-8"));
			} catch (Exception e3) {
				// TODO Auto-generated catch block
				e3.printStackTrace();
			}
			String message_author_iso = getMessage_auteur();
			String message_author = "";
			try {
				message_author = new String(message_author_iso.getBytes(), Charset.forName("UTF-8"));
			} catch (Exception e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
			}
			String subject_author_iso = getSujet_auteur();
			String subject_author = "";
			try {
				subject_author = new String(subject_author_iso.getBytes(), Charset.forName("UTF-8"));
			} catch (Exception e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
			}
			
			Map<String,Object> data = new HashMap<String, Object>();
			data.put("caseId", processInstanceId);
			data.put("login", login);
			data.put("message", message);
			data.put("subject", subject);
			data.put("notify_author", Notify_author_string);
			data.put("message_author", message_author);
			data.put("subject_author", subject_author);
			
			JSONObject json = new JSONObject();
			json.putAll(data);
			
			String json_string = json.toJSONString();

	    	String url = "http://localhost/workflow/api/sendmail";
	    	
	    	HttpClient httpClient = HttpClientBuilder.create().build();
	    	HttpPost request_post = new HttpPost(url);
	    	request_post.addHeader("Content-Type", "application/json");
	    	StringEntity entity;
			try {
				entity = new StringEntity(json_string);
				request_post.setEntity(entity);	
			} catch (UnsupportedEncodingException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			try {
				httpClient.execute(request_post);
			} catch (ClientProtocolException e) {
				// TODO Bloc catch généré automatiquement
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Bloc catch généré automatiquement
				e.printStackTrace();
			}

			
		//}catch (Exception e) {
	    	
		//}
		
		
		//WARNING : Set the output of the connector execution. If outputs are not set, connector fails
	
	 }

	@Override
	public void connect() throws ConnectorException{
		//[Optional] Open a connection to remote server
	
	}

	@Override
	public void disconnect() throws ConnectorException{
		//[Optional] Close connection to remote server
	
	}

}
