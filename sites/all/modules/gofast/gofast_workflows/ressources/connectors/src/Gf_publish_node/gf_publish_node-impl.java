/**
 * 
 */
package org.mycompany.connector;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.HttpClientBuilder;
import org.bonitasoft.engine.connector.ConnectorException;

import groovy.json.JsonBuilder;
import groovy.json.JsonSlurper;
import groovy.json.internal.LazyMap;

/**
*The connector execution will follow the steps
* 1 - setInputParameters() --> the connector receives input parameters values
* 2 - validateInputParameters() --> the connector can validate input parameters values
* 3 - connect() --> the connector can establish a connection to a remote server (if necessary)
* 4 - executeBusinessLogic() --> execute the connector
* 5 - getOutputParameters() --> output are retrieved from connector
* 6 - disconnect() --> the connector can close connection to remote server (if any)
*/
public class Gf_publish_nodeImpl extends AbstractGf_publish_nodeImpl {
	String token;
	@Override
	protected void executeBusinessLogic() throws ConnectorException{
		//Get access to the connector input parameters
		//getAuthor();
		//getNid();
		//getLocations();
		HttpClient client = HttpClientBuilder.create().build();
		try {		
			JsonBuilder builder = new groovy.json.JsonBuilder(getLocations());
			String json_string_locations = builder.toString();
			
			String url_edit_node = "http://localhost/api/node/publication";
			HttpPost request_post = new HttpPost(url_edit_node);
			
			request_post.addHeader("Content-Type", "application/json");
			request_post.addHeader("token", token);
			String json = "{\"locations\": "+json_string_locations+", \"nid\" : \""+getNid()+"\"}";
		    StringEntity entity = new StringEntity(json);
		   
		    request_post.setEntity(entity);				
			 
		    HttpResponse response_post = client.execute(request_post);
			BufferedReader rd_post = new BufferedReader(
			new InputStreamReader(response_post.getEntity().getContent()));
	
			StringBuffer result_post = new StringBuffer();
			String line_post = "";
			while ((line_post = rd_post.readLine()) != null) {
				result_post.append(line_post);
			}			
			
			setOutputParameter("output",result_post.toString());
	
		} catch (ClientProtocolException e) {
			setOutputParameter("output", e.getMessage());
			
		}catch (IOException e) {
			setOutputParameter("output", e.getMessage());
		}
		
	
	 }

	@Override
	public void connect() throws ConnectorException{
		//[Optional] Open a connection to remote server			
		String author = getAuthor();
		String url = "http://localhost/api/login/token?name="+author;
		HttpClient client = HttpClientBuilder.create().build();
		HttpGet request = new HttpGet(url);
		try {
			HttpResponse response = client.execute(request);
			BufferedReader rd = new BufferedReader(
			new InputStreamReader(response.getEntity().getContent()));

			StringBuffer result = new StringBuffer();
			String line = "";
			while ((line = rd.readLine()) != null) {
				result.append(line);
			}		

			JsonSlurper jsonSlurper = new JsonSlurper();
			Object json_result = jsonSlurper.parseText( result.toString());
			token = ((LazyMap) json_result).get("token").toString();
			
		} catch (ClientProtocolException e) {
			setOutputParameter("output", e.getMessage());	
		} catch (IOException e) {
			setOutputParameter("output", e.getMessage());
		}
	
	}

	@Override
	public void disconnect() throws ConnectorException{
		//[Optional] Close connection to remote server
	
	}

}
