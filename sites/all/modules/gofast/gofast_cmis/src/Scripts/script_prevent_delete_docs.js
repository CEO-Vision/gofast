logger.log("==== " + "STARTING SCRIPT " + "SCRIPT PREVENT DELETE DUA" + " ====");
logger.log('Script called on ' + document.name + ' / ' + document.id);

	var gofastAspect = "{gofast.model}nodeproperties";
	var prevent_delete = false;
  
	if(document.hasAspect(gofastAspect)) {
		prevent_delete = document.properties['gofast:preventDelete'];
	}

	if(!prevent_delete || person.properties.userName == "admin"){
            
	}else{
      var oldNode = search.findNode('workspace://SpacesStore/' + document.id);
      

      if(document.hasAspect('sys:pendingDelete')){
        logger.log('PREVENT DELETE');
        throw "ROLLBACK : Delete a document which has reached his DUA is not authorized"; 
      }
    }


logger.log("==== " + "ENDING SCRIPT " + "SCRIPT PREVENT DELETE DUA" + " ====");