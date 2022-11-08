/*
 * Add mail rules to document
 */
logger.log("==== " + "STARTING SCRIPT " + "REMOVE MAIL ASPECTS" + " ====");

/*
 * GLOBAL VARIABLES
 */
var mailnodeproperties = "{gofastMail.model}mail";

/*
 * Update aspects if needed
 */
function updateAspects(document) {

  if (document.isDocument) {

    if (document.hasAspect("gofastMail:mail") == true) {
      document.removeAspect("gofastMail:mail");
      performRequest = false;
      logger.log("Remove aspects mail on node : " + document.name);
    } else {
      logger.log("Don't have aspects mail on node : " + document.name);
    }
  }
}

var document = search.findNode(args.reference);
updateAspects(document);

model.myStatus = "OK";

logger.log("==== " + "ENDING SCRIPT " + "REMOVE MAIL ASPECTS" + " ====");

