/*
 * Add archive rules to document 
 */
logger.log("==== " + "STARTING SCRIPT " + "UPDATE ASPECTS" + " ====");
logger.log('Script called on ' + document.name + ' / ' + document.id);

/*
 * GLOBAL VARIABLES
 */
var archivenodeproperties = "{gofast.model}archivenodeproperties";

/*
 * Update aspects if needed
 */
function updateAspects(){
    
  if(document.isDocument){

      if(document.hasAspect("gofast:archivenodeproperties") == false){
      document.addAspect("gofast:archivenodeproperties");
      performRequest = false;
      logger.log("add aspects achive on node : " + document.name);
      }else{
          logger.log("already have aspects archive on node : " + document.name);
      }
  }
}

updateAspects();

logger.log("==== " + "ENDING SCRIPT " + "UPDATE ASPECTS" + " ====");



