logger.log("==== " + "STARTING SCRIPT " + "SCRIPT PREVENT DELETE SPACE FOLDER" + " ====");
logger.log('Script called on ' + document.name + ' / ' + document.id);
if(document.hasPermission("Write") == false){

} else {
	var gofastAspect = "{gofast.model}nodeproperties";
	var prevent_delete = false;

	if(document.hasAspect(gofastAspect)) {
		prevent_delete = document.properties['gofast:preventDelete'];
	}

	if(!prevent_delete){
            //not a space, but prevent a simple folder to be prefixed by _
            if(document.name.substring(0, 1) == "_" && person.properties.userName !== "admin"){
                 logger.log('Start a folder name with _ is not authorized');
                 throw "ROLLBACK : Start a folder name with _ is not authorized"; 
            }
	}else{
                if(person.properties.userName == "admin"){                 
                   document.properties['description'] = document.name;
                   document.save();
               }else{          
                   //WARN : Space folder rename allowed until catch is possible : GOFAST-4100
                   if(document.properties['description'] != document.name && person.properties.userName !== "admin" && document.properties['description'] != "" ){
                     logger.log('Edition of ' + document.name + ' will lead to a crash.');
                     throw "ROLLBACK : Edition of a space folder is not authorized"; 
                   }
              }
       }
}

logger.log("==== " + "ENDING SCRIPT " + "SCRIPT DELETE CONTENT FOLDER" + " ====");