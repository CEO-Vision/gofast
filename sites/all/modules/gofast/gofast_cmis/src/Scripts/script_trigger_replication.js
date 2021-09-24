logger.log("==== " + "STARTING SCRIPT " + "SCRIPT SYNCHRONIZE" + " ====");
logger.log('Script called on ' + document.name + ' / ' + document.id);
    
/*
 * Implements JSON
 */
var JSONgf = {
    parse: function(sJSON) { return eval('(' + sJSON + ')'); },
    stringify: (function () {
      var toString = Object.prototype.toString;
      var isArray = Array.isArray || function (a) { return toString.call(a) === '[object Array]'; };
      var escMap = {'"': '\\"', '\\': '\\\\', '\b': '\\b', '\f': '\\f', '\n': '\\n', '\r': '\\r', '\t': '\\t'};
      var escFunc = "" + function (m) { return escMap[m] || '\\u' + (m.charCodeAt(0) + 0x10000).toString(16).substr(1); };
      var escRE = "" + /[\\"\u0000-\u001F\u2028\u2029]/g;
      return function stringify(value) {
        if (value == null) {
          return 'null';
        } else if (typeof value === 'number') {
          return isFinite(value) ? value.toString() : 'null';
        } else if (typeof value === 'boolean') {
          return value.toString();
        } else if (typeof value === 'object') {
          if (typeof value.toJSON === 'function') {
            return stringify(value.toJSON());
          } else if (isArray(value)) {
            var res = '[';
            for (var i = 0; i < value.length; i++)
              res += (i ? ', ' : '') + stringify(value[i]);
            return res + ']';
          } else if (toString.call(value) === '[object Object]') {
            var tmp = [];
            for (var k in value) {
              if (value.hasOwnProperty(k))
                tmp.push(stringify(k) + ': ' + stringify(value[k]));
            }
            return '{' + tmp.join(', ') + '}';
          }
        }
        return '"' + value.toString().replace(escRE, escFunc) + '"';
      };
    })()
  };

/*
 * GLOBAL VARIABLES
 */
var gofastAspect = "{gofast.model}nodeproperties";
var drupalOriginAspect = "{gofast.model}drupalorigin";
var performRequest = true;

/*
 * Freeze the script for milliseconds
 * @param milliseconds
 *    Number of milliseconds
 */
function sleep(milliseconds) {
  logger.log("Waiting for " + milliseconds + ' ms');
  var start = new Date().getTime();
  for (var i = 0; i < 1e7; i++) {
    if ((new Date().getTime() - start) > milliseconds) {
      break;
    }
  }
  logger.log("Sleep finished. Continuing");
}

/*
 * Send an alert E-mail to CEO-Vision team
 * @param subject
 *    The subject of the message
 * @param message
 *    What will be writter at the top of the body
 * @param error
 *    The technical error displayed at the end of the E-mail
 * @param noderef
 *    The alfresco reference of the document
 * @param name
 *    The title of the document
 * @param space
 *    The calculated space of the document (DEPRECATED)
 * @param person
 *    The person who initiated the action
 * @param destination
 *    The path of the document (DEPRECATED)
 */
function sendMail(subject, message, error, noderef, name, space, person, destination){
 try {
  var mailUser = people.getPerson("admin");
  var mail = actions.create("mail");
  mail.parameters.to = "support@ceo-vision.com";
  mail.parameters.subject = subject;
  mail.parameters.html = "<html><head> <meta http-equiv='Content-Type' content='text/html; charset=UTF-8'> <meta property='og:title' content='GoFast Notifications'> <title>GoFast</title> <style type='text/css'> #edits-metadatas tr td th{border: 1px solid grey;}</style> </head> <body leftmargin='0' marginwidth='0' topmargin='0' marginheight='0' offset='0' style='background-color: #E6E6E6; width: 100% !important; -webkit-text-size-adjust: none; margin: 0; padding: 0;'> <center> <table id='top' border='0' cellpadding='0' cellspacing='0' height='95%' width='60%' min-width='640px' style='height: 95% !important; margin: 0; padding: 0; width:70%; min-width:640px; background-color: #E6E6E6;'> <tbody><tr> <td width='95%' align='center' valign='top' style='padding-top: 0px; border-collapse: collapse;'> <table align='center' border='0' cellpadding='0' cellspacing='0' width='100%' style='border: 1px solid #DDDDDD; background-color: #EFEFEF; width:100%;'> <tbody><tr> <td align='center' valign='top' style='border-collapse: collapse;'> <table align='center' border='0' cellpadding='0' cellspacing='0' width='100%' style='background-color: #FFFFFF; border: 0; text-align:left;'> <tbody><tr class='gofast-notification-header'> <td align='left' width='100%' style='border-collapse: collapse; color: #202020; font-family: sans-serif; line-height: 100%; padding: 0; text-align: left; vertical-align: middle; width:100%;'> <table align='left' border='0' cellpadding='0' cellspacing='0' width='100%'' height='40' style='background-color: #2B2B2B; border: 0;'> <tbody><tr> <td width='20%' style='width:10%; border-collapse: collapse; color: #202020; font-family: sans-serif; font-size: 30px; line-height: 100%; padding: 0; text-align: left; vertical-align: middle;'> </td><td width='100' height='50' valign='middle' style='width:100px; height:40px; border-collapse: collapse; color: #202020; font-family: sans-serif; line-height: 100%; padding: 0; text-align: left;'> </td><td style='background-color: #2B2B2B; color: #9d9d9d; border-collapse: collapse; font-family: sans-serif; font-size: 24px; line-height: 100%; text-align:left; vertical-align: middle;'> GoFAST Report </td><td> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; </td></tr></tbody></table> </td></tr><tr> <td height='20'> </td></tr></tbody></table> </td></tr><tr> <td align='center' valign='top' style='border-collapse: collapse;'> <table border='0' cellpadding='0' cellspacing='0' width='100%' style='border-collapse: collapse;'> <tbody><tr> <td> <table border='0' cellpadding='20' cellspacing='0' width='100%'> <tbody><tr> <td valign='top' align='center' style='border-collapse: collapse; background-color: #FFFFFF; padding:0px;'> <table width='100%' align='center' cellspacing='0' cellpadding='0' border='0' style='width:100%;'> <tbody><tr> <td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>"+ message +"</td></tr></tbody> </table> </td></tr><tr width='80%'> <td valign='top' align='center' style='border-collapse: collapse; background-color: #FFFFFF; padding:0px;' width='80%'> <table width='80%' align='center' cellspacing='0' cellpadding='0' border='0' style='width:100%;'> <tbody> <tr> <td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>Node reference</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>Title</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>Space ID</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>Creator</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>Destination path</td></tr><tr> <td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>" + noderef + "</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>" + name + "</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>" + space + "</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>" + person + "</td><td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>" + destination + "</td></tr></tbody> </table> </td></tr></tbody></table> </td></tr></tbody></table></td></tr><tr> <td style='color:#505050; font-family:Arial; font-size:12px; line-height:150%; text-align:left;'>  Error: " + error + "</td></tr></tbody> </table> </td></tr></tbody></table> </td></tr></tbody></table> </td></tr><tr> <td> <table width='100%' align='center' height='30' border='0' cellpadding='0' cellspacing='0' style='background-color: #2B2B2B;'> <tbody><tr> <td> </td></tr></tbody></table> </td></tr><tr> <td align='center' valign='top' style='border-collapse: collapse;'> <table width='100%' height='80' border='0' cellpadding='0' cellspacing='0' style='background-color: #F0F0F0; border-top: 0;'> <tbody><tr> <td valign='middle' style='border-collapse:collapse; padding-left:20px; padding-right:20px;'> <table border='0' cellpadding='10' cellspacing='0' width='100%'> <tbody><tr> <td valign='top' align='center' style='border-collapse: collapse; color:#999999; font-size:11px; line-height:14px; font-family:arial,Arial,sans-serif;'> GoFAST Report notification E-mail </td></tr></tbody></table> </td></tr></tbody></table> </td></tr></tbody></table> <br></td></tr></tbody></table> </center> </body></html>";
  //mail.execute(mailUser);
  logger.log("Sending mail "+mail.parameters.html);
 }catch (e) {
    logger.log("Error sending mail");
  }
}

/*
 * Close the XH Request as it seems to be shared between scripts
 */
function closeXHR(){
  try {
  // Try to close the XHR Object
    XMLHttpRequest.close();
    logger.log("Closing XHR Object");
  }catch (ex) {
    logger.log("XHR Object is already closed");
  }
}

/*
 * Send the synchronization request
 * @param nodes
 *    The node that will be sent to drupal
 *      noderef
 *        The alfresco reference of the document
 *      name
 *        The title of the document
 *      space
 *        The calculated space of the document (DEPRECATED)
 *      person
 *        The person who initiated the action
 *      destination
 *        The path of the document (DEPRECATED)
 *      messageto
 *        The mistery of this function (DEPRECATED)
 *      author
 *        The author of the document (DEPRECATED)
 */
function sendRequest(nodes) {
  logger.log("Request sending initiated");
  var scriptname = "script trigger replication";
  
  //We check if a mandatory parameter is missing
  try {
    for each(var n in nodes){
      if(n.noderef === null || n.name === null || n.space === null || n.person === null || n.destination === null){
        //A mandatory parameter is missing !
        logger.log("Request not sent : Missing GoFAST mandatory parameter. A mail has been sent to CEO-Vision team !");
        if(n.noderef === null){n.noderef = 'null'}; if(n.name === null){n.name = 'null'}; if(n.space === null){n.space = 'null'}; if(n.person === null){n.person = 'null'};if(n.destination === null){n.destination = 'null'}

        //We format a mail and send it to CEO-Vision support team
        var subject = "[GoFast Report] Replication failed (" + scriptname + ")";
        var message = "Alfresco replication failed on a document. A mandatory parameter was missing during replication. The Replication request wasn't sent to Drupal.";
        var error = "Missing mandatory parameter";
        sendMail(subject, message, error, n.noderef, n.name, n.space, n.person, n.destination);
      }
    }
    
    //Waiting for the XHR variable to be accessible
    var waitBreaker = 0;
    while(XMLHttpRequest.getReadyState() != 0){
      if(waitBreaker > 1000){
        closeXHR();
        throw "XHR variable is not accessible (1000 tries)";
      }
      sleep(100);
      waitBreaker ++;
    }
    
    //Send the request to Drupal
    var url = "http://localhost/alfresco_script.php";
    var params = "nodes=" + JSONgf.stringify(nodes);
    XMLHttpRequest.open("POST", url, false, "user", "pass");
    XMLHttpRequest.send(params);
    logger.log("Request has been sent");
    
    //We get the XHR response, it should be "OK"
    var response = XMLHttpRequest.getResponseText();
    if(response == "OK"){
      logger.log("Drupal answered OK");
      closeXHR();
    }
    else{
      logger.log("Drupal didn't answered OK");
      logger.log("Drupal answered " + response);
      //We throw an error to retry
      throw "Drupal answer is " + response;
    }
  } catch (ex) {
    closeXHR();
    
    //An error has occured, we'll retry in 500 ms
    sleep(500);
    
      try{
        var error = String(ex);
        
        //Waiting for the XHR variable to be accessible
        var waitBreaker = 0;
        while(XMLHttpRequest.getReadyState() != 0){
          if(waitBreaker > 1000){
            closeXHR();
            throw "XHR variable is not accessible (1000 tries)";
          }
          sleep(100);
          waitBreaker ++;
        }
        
        var url = "http://localhost/alfresco_script.php";
        var params = "nodes=" + JSONgf.stringify(nodes);
        XMLHttpRequest.open("POST", url, false, "user", "pass");
        XMLHttpRequest.send(params);
        logger.log("Request has been sent (2nd try)");

        //We get the XHR response, it should be "OK"
        var response = XMLHttpRequest.getResponseText();
        if(response == "OK"){
          logger.log("Drupal answered OK (2nd try) A mail has been sent to CEO-Vision team");
          var subject = "[GoFast Report] Replication warn (" + scriptname + ")";
          var message = "Alfresco replication faced an issue on a document. The request was successfully sent to Drupal after another try.";
          var error = ex;
          //sendMail(subject, message, error, JSONgf.stringify(nodes));
          closeXHR();
        }
        
        else{
          logger.log("Drupal didn't answered OK. A mail has been sent to CEO-Vision team");
          //We throw an error to retry
          throw "Drupal answer is " + response;
        }
        
      }catch(ex_retry){ //2nd error
        closeXHR();
        var error = String(ex_retry);
        logger.log("Fatal exit : A mail has been sent to CEO-Vision team !");
        //An error occured, we send a mail to CEO-Vision team
        var subject = "[GoFast Report] Replication failed (" + scriptname + ")";
        var message = "Alfresco replication failed, Alfresco cannot replicate this document.";
        var error = "First error : " + ex + " - Second error : " + ex_retry;
        sendMail(subject, message, error, JSONgf.stringify(nodes));
      }
  }
}

/*
 * @param node
 *    The document
 * @returns weither the node is a group or not
 */
function nodeIsGroup(node) {
  if (node.hasAspect(gofastAspect)) {
    logger.log("Node " + node.name + " is group : " + node.properties['{gofast.model}isgroup']);
    return node.properties['{gofast.model}isgroup'];
  } else {
    logger.log("Node " + node.name + " is group : " + node.name.substr(0, 1));
    return node.name.substr(0, 1) === "_";
  }
}

/**
 * Si le createur du noeud est admin, je verifie si le champs auteur est remplit. si oui c'est celui la que j'utilise pour envoyer a drupal
 */
function getCurrentUser() {
  var user = person.properties.userName;
  if (person.properties.userName === "admin" && document.properties["cm:author"] != null) {
    user = encodeURIComponent(document.properties["cm:author"]);
  }
  return user;
}

/*
 *	Returns whether the current document is a content handeled by drupal
 */
function isDrupalContent() {
  var drupal_content_re = /\/webdav\/Sites\/_.*/g;
  var is_drupal_content = drupal_content_re.exec(document.webdavUrl) !== null;
  return is_drupal_content;
}

/*
 * Update aspects if needed
 * Warning : In some case, save the document (trigger again the rules etc...)
 */
function updateAspects(){
  if(document.isDocument){

      if(document.hasAspect("cm:versionable") == false){		
          document.addAspect("cm:versionable");
          performRequest = false;
          logger.log("add aspect versionable on node : " + document.name);
      }else{
          if(document.properties["autoVersionOnUpdateProps"] == true){
              document.properties["autoVersionOnUpdateProps"] = false;
              document.save();
              performRequest = false;
          }
      }


      if(document.hasAspect("gofast:drupalorigin") == false){
      document.addAspect("gofast:drupalorigin");
      document.addAspect("gofast:nodeproperties");
      performRequest = false;
       logger.log("add aspects on node : " + document.name);
      }else{
           logger.log("already have aspects on node : " + document.name);
      }
  }
}
try{  
  if (person.properties.userName !== "admin" && person.properties.userName !== "System") {
    updateAspects();
    //Fail conditions
    if(nodeIsGroup(document)){
      throw "Performing operations on a group is not allowed.";
    }
    
    if((document.isDocument && isDrupalContent())) {
  logger.log('permission delete : '+document.hasPermission("Delete"));
   if(document.hasPermission("Delete") == false){
        if(document.hasAspect('sys:pendingDelete')){
           logger.log('Prevent this deletion caused by parent folder deletion');
           throw "ROLLBACK : Prevent this deletion caused by parent folder deletion"; 
        }
    }
    
      logger.log("drupalOrigin : " + document.properties['{gofast.model}origin']);
      logger.log("node name : " + document.name);

      var noderef = encodeURIComponent(document.nodeRef);
      var docname = encodeURIComponent(document.name);
      var author = encodeURIComponent(document.properties["cm:author"]);

      var parent_space = null;
      for(var j=0; j < document.parents.length; j++){
	if(document.parents[j].hasPermission("Read")){
            parent_space = document.parents[j];
            break;
        }else{
              logger.log("unable to access parent, trying next");
        }	
      }
      
        /*var parent_space = document.parent; */      
        if(parent_space !== null){
            while (!nodeIsGroup(parent_space)) {
              parent_space = parent_space.parent;
            }
            var parent_name = encodeURIComponent(parent_space.name);
            var space = parent_space.properties['{gofast.model}nid'];
            var person = getCurrentUser();
            //var destination = parent_space.webdavUrl.substring(7);
             var destination = document.parents[j].webdavUrl.substring(7);
        }else{
            logger.log("Unable to access parent folder");
            var parent_space = "";          
            var parent_name = "";
            var space = "";   
            var destination = "";
        }
        
      var messageto = encodeURIComponent(document.properties.addressee);
      if (messageto !== null) {
        messageto = messageto.replace(/"/g, '');
        messageto = encodeURIComponent(messageto);
      }
  /***************************************************/

      if (1 || (document.hasAspect(drupalOriginAspect) && !document.properties['{gofast.model}origin'])) {
          logger.log("SYNCING DOCUMENT");
          logger.log("Sending request to drupal.");
          logger.log("Node ref: " + noderef);
          logger.log("Document name: " + docname);
          logger.log("Spaces: " + space);
          logger.log("Creator: " + person);
          logger.log("Destination: " + destination);
          logger.log("Message to: " + messageto);
          logger.log("Author: " + document.properties["cm:author"]);
          var node = [];
          node.push({
              op: "Sync", 
              noderef: noderef, 
              name: docname, 
              space: space, 
              person: encodeURIComponent(person), 
              destination: destination, 
              messageto: messageto, 
              author: author
            });
          sendRequest(node);
      }
    }
    else{
      throw "This node hasn't passed any test to process a synchronization request" ;
    }
  }
  else{
    throw "This is a technical request, no replication";
  }
}catch(e){
  logger.log("Error: " + e);
    logger.log('permission delete : '+document.hasPermission("Delete"));
   if(document.hasPermission("Delete") == false){
        if(document.hasAspect('sys:pendingDelete')){
            logger.log('Prevent this deletion caused by parent folder deletion');
            throw "ROLLBACK : Prevent this deletion caused by parent folder deletion"; 
        }
    }
}

logger.log("==== " + "ENDING SCRIPT " + "SCRIPT SYNCHRONIZE" + " ====");
