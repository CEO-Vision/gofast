logger.log("==== " + "STARTING SCRIPT " + "UPDATE ASPECTS" + " ====");
logger.log('Script called on ' + document.name + ' / ' + document.id);

/*
 * GLOBAL VARIABLES
 */
var gofastAspect = "{gofast.model}nodeproperties";
var drupalOriginAspect = "{gofast.model}drupalorigin";

/*
 * Update aspects if needed
 */
function updateAspects(){
  if(document.isDocument){

      if(document.properties["autoVersionOnUpdateProps"] == true){
        document.properties["autoVersionOnUpdateProps"] = false;
        document.save();
        performRequest = false;
      }
      
      if(document.hasAspect("cm:versionable") == false){		
          document.addAspect("cm:versionable");
          performRequest = false;
          logger.log("add aspect versionable on node : " + document.name);
      }


      if(document.hasAspect("gofast:drupalorigin") == false){
      document.addAspect("gofast:drupalorigin");
      document.addAspect("gofast:nodeproperties");
      performRequest = false;
       logger.log("add aspects on node : " + document.name);
      }else{
          var datenow = new Date();
          var documentDate = new Date(document.properties["created"]);
          if(datenow.getTime() - documentDate.getTime() < 2000 ){
            logger.log("Empty property nid on node " + document.name + " because it comes from a WebDAV copy.");
            //GOFAST-4582 This document has just been created from a webdav copy
            //Empty it's nid property to prevent a redirection to the original
            //document
            
            delete document.properties['gofast:nid'];
            document.save();
          }
          logger.log("already have aspects on node : " + document.name);
      }
     
      if(document.hasAspect("sys:hidden")){
          document.removeAspect("sys:hidden");
      }	
     /* if(document.hasAspect("cm:indexControl")){
          document.removeAspect("cm:indexControl");
      }	*/
  }else{
	if(document.hasAspect("gofast:nodeproperties") == false){
      document.addAspect("gofast:nodeproperties");
       performRequest = false;
       logger.log("add aspects on folder : " + document.name);
      }else{
           logger.log("already have aspects on node : " + document.name);
      }
  }
}

updateAspects();

logger.log("==== " + "ENDING SCRIPT " + "UPDATE ASPECTS" + " ====");
