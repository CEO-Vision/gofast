/*
 * Add mail rules to document
 */
logger.log("==== " + "STARTING SCRIPT " + "UPDATE ASPECTS" + " ====");

/*
 * GLOBAL VARIABLES
 */
var mailnodeproperties = "{gofastMail.model}mail";

/*
 * Update aspects if needed
 */
function updateAspects(document) {

  if (document.isDocument) {

    if (document.hasAspect("gofastMail:mail") == false) {
      document.addAspect("gofastMail:mail");
      performRequest = false;
      logger.log("add aspects mail on node : " + document.name);
    } else {
      logger.log("already have aspects mail on node : " + document.name);
    }
  }
}

var document = search.findNode(args.reference);
updateAspects(document);

model.myStatus = "OK";

logger.log("==== " + "ENDING SCRIPT " + "UPDATE ASPECTS" + " ====");

