/**
DATE : 01/02/2016
DESCRIPTION
This script is called by drupal when updating a node.
It updated all the properties of a document looking URL arguments.

PARAMETERS
reference : 	(first argument) is mandatory, it's the node id on which we update the properties
nid : 				refers to drupal node id, should be set at node creation at least.
bundle : 		refers to node bundle.
isgroup : 		tells wether the node is a group/organization or not.
preventDelete : whether the node is deletable
---- The following fields are not mandatory ----
summary : 		the summary or description of the node
tags : 			all the tags of the node (a list)
category : 		the category of the node
criticity :		the criticity of the node
state : 			the state of the node
*/

logger.log("==== " + "STARTING SCRIPT " + "SCRIPT UPDATE GOFAST ASPECT" + " ====");

var render = "";
var renderArray = {};
var gofastAspect = "{gofast.model}nodeproperties";

/**
This function add recursively the custom aspect to all the children content specified in parameters.
Note that here we should never set parameters, only the reference and the loop will add aspect to every children.
*/
function updateChildren(node) {
	for (let child of node.children) {
		checkAspect(child);
		updateChildren(child);
	}
}

/**
This function checks if the node has the aspect, if not, add it
*/
function checkAspect(node) {
	if (!node.hasAspect(gofastAspect)) {
		node.addAspect(gofastAspect);
		renderArray.aspect = gofastAspect + " added on node " + node.id + " (" + node.properties['cm:name'] + ")";
		render += gofastAspect + " added on node " + node.id + " (" + node.properties['cm:name'] + ")<br />";
	} else {
		renderArray.aspect = gofastAspect + " already found in node " + node.id + " (" + node.properties['cm:name'] + ")";
		render += gofastAspect + " already found in node " + node.id + " (" + node.properties['cm:name'] + ")<br />";
	}
}

/**
This function updates all the properties of the node aspect.
*/
function updateProperties(node, properties) {
	renderArray.properties = {};
	for (var property in properties) {
		node.properties['gofast:' + property] = properties[property];
		node.save();
		renderArray.properties[property] = "Updated " + property + " with value " + properties[property];
		render += "Updated " + property + " with value " + properties[property] + "<br \>";
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
		if (Object.keys(updatedProperties).length > 0) {
			checkAspect(rootNode);
			updateProperties(rootNode, updatedProperties);
		} else {
			updateChildren(rootNode);
		}
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
logger.log("==== " + "ENDING SCRIPT " + "SCRIPT UPDATE GOFAST ASPECT" + " ====");
