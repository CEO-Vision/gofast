/**
DATE : 15/03/2016
DESCRIPTION
This script is called by drupal when updating a node.
It updated all the properties of a document looking URL arguments.

PARAMETERS
reference : 				(first argument) is mandatory, it's the node id on which we update the properties
node-attributes :		any node attribute to be modified.
*/

var renderArray = {};

/**
This function updates all the properties of the node aspect.
*/
function updateProperties(node, properties) {
    renderArray.properties = {};
	if(node.hasAspect("gofast:nodeproperties") == false){
      node.addAspect("gofast:nodeproperties");      
       logger.log("add aspects on folder : " + node.name);
    }else{
           logger.log("already have aspects on node : " + node.name);
    }
    for (var property in properties) {
        if(property == "mimetype"){
             node.mimetype = properties[property];
        }else if(property == "name"){
             node.name = properties[property];
        }else{
            node.properties[property] = properties[property];
        }
        node.save();
        renderArray.properties[property] = "Updated " + property + " with value " + properties[property];
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
        updateProperties(rootNode, updatedProperties);
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