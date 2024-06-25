logger.log("==== " + "STARTING SCRIPT " + "SCRIPT GET PREVIEW" + " ====");

var response = {};

if (args.reference !== null) {
  var node = search.findNode(args.reference);

  var thumbnail = null;
  if (node !== null) {
    thumbnail = node.getThumbnail("pdf");
  }
  var force_recreate = false;
   if(thumbnail !== null){
       if(thumbnail.properties["modified"] < node.properties["modified"]){
           //thumbnail = null;
           force_recreate = true;
       }
   }

  if (thumbnail === null || thumbnail.size === 0 || force_recreate === true)
  {
    // Remove broken thumbnail
    if (thumbnail !== null || force_recreate === true)
    {
      thumbnail.remove();
    }
    // Try to generate new thumbnail (+ auto rendition)
    try {
      logger.log("GENERATING THUMBNAIL");
      var generated_thumbnail = node.createThumbnail("pdf");
      response.status = "OK";
      response.value = generated_thumbnail;
	  response.reference = args.reference;
    } catch (ex) {
      logger.log("THUMBNAIL GENERATION ERROR, SENDING SOFFICE RESTART COMMAND");
      var url = "http://localhost/alfresco_script.php?op=restart_soffice&noderef=" + args.reference + "&err=" + encodeURIComponent(ex);
      XMLHttpRequest.close();
      XMLHttpRequest.open("GET", url, false, "user", "pass");
      XMLHttpRequest.send("");
      simplehttpresult = XMLHttpRequest.getResponseText();
      XMLHttpRequest.close();

      response.status = "KO";
      response.message = "The preview could not be generated";
	  response.ex = ex;
    }
  } else {
    logger.log("THUMBNAIL EXISTS, RETURNING THE THUMBNAIL");
    response.status = "OK";
    response.value = thumbnail;
    response.reference = args.reference;
    response.title = node.name;
  }

} else {
  response.status = "KO";
  response.message = "The argument reference is mandatory";
}

model.property = jsonUtils.toJSONString(response);

/*var node = search.findNode(args.reference);
 var thumbnail_result = "no error";
 //thumbnail_result = node.createThumbnail("webpreview", false);
 var def = renditionService.createRenditionDefinition("pdf", "reformat");
 def.parameters['mime-type'] = "application/pdf";
 //def.execute(node);
 try {
 def.execute(node);
 } catch (ex) {
 //d'abord on detemrine si l'erreur est du a un transformer introuvable ou un timeout
 var n = encodeURIComponent(ex).indexOf("timeout");
 if (n == -1) {
 
 } else {
 simplehttpresult = SimpleHttpConnection
 .getContentAsString("http://localhost/drupal/alfresco_script.php?op=restart_soffice&noderef=" + args.reference + "&err=" + encodeURIComponent(ex));
 }
 
 }
 //var pdfFile = renditionService.render(node, def);
 //node.transformDocument("application/pdf");
 model.property = "debug";*/

logger.log("==== " + "ENDING SCRIPT " + "SCRIPT GET PREVIEW" + " ====");