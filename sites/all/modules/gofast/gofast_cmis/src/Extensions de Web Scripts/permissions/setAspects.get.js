/**
DATE : 25/04/2017
DESCRIPTION
This script is called by drupal when we need to update aspects on a node.

PARAMETERS
reference : 				(first argument) is mandatory, it's the node id on which we update the aspects
*/

var renderArray = {};

/**
This function updates all the properties of the node aspect.
*/
function updateAspects(node) {
    if(node.hasAspect("cm:versionable") == false){		
		node.addAspect("cm:versionable");
		logger.log("add aspect versionable on node : " + node.name);
	}else{
		if(node.properties["autoVersionOnUpdateProps"] == true){
			node.properties["autoVersionOnUpdateProps"] = false;
			node.save();
		}
	}


	if(node.hasAspect("gofast:drupalorigin") == false){
	node.addAspect("gofast:drupalorigin");
	node.save();
	 logger.log("add aspects on node : " + node.name);
	}else{
		 logger.log("already have aspects on node : " + node.name);
	}
	if(node.hasAspect("gofast:nodeproperties") == false){
	node.addAspect("gofast:nodeproperties");
	node.save();
	 logger.log("add aspects on node : " + node.name);
	}else{
		 logger.log("already have aspects on node : " + node.name);
	}
}

// If there is a reference, otherwise do nothing
if (args.reference !== null) {
    var updatedProperties = {};
    for (var key in args) {
        if (key !== "reference") {
            updatedProperties[key] = args[key];
        }
    }

    var rootNode = search.findNode(args.reference);

    if (rootNode !== null) {
        renderArray.status = "OK";
        updateAspects(rootNode);
    } else {
        renderArray.other = utils.getNodeFromString(args.reference);
        renderArray.status = "KO";
        renderArray.message = "The reference is wrong or does not exist anymore";
    }
} else {
    renderArray.status = "KO";
    renderArray.message = "The argument reference is mandatory";
}

model.myStatus = jsonUtils.toJSONString(renderArray);
