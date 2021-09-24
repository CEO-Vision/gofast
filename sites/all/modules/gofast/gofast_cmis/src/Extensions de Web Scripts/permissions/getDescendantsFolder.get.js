//search for the folder node using lucene search
var node = search.findNode(args.reference);
var render = "";
var document_type = args.type;
var restrictdepth = args.restrictdepth;
var depth = 0;
//debug
//restrictdepth = "true";

var descendants = "";
var arraydescendants = [];

if (document_type === null) {
  document_type = "all";
}

function nodeIsGroup(nodeName) {
  return nodeName.substr(0, 1) === "_";
}

function getDocument(node_document) {
  var element = [];
  if (node_document.isDocument) {
    var history = node_document.versionHistory;

    if (history !== null) {
	  element['creator'] =  history[0].creator;
	  element['version'] =  history[0].label;
	  element['date_version'] =  utils.toISO8601(history[0].createdDate);
      element["url"] = node_document.properties["cm:name"] + "**" + node_document.nodeRef + "**" + history[0].creator + "**" + node_document.size + "**" + history[0].label + "**" + utils.toISO8601(history[0].createdDate) + "**";
    } else {
	  element['creator'] =  node_document.properties["cm:creator"];
	  element['version'] =  "1.0";
	  element['date_version'] =  utils.toISO8601(node_document.properties["cm:created"]);
      element["url"] = node_document.properties["cm:name"] + "**" + node_document.nodeRef + "**" + node_document.properties["cm:creator"] + "**" + node_document.size + "**1.0**" + utils.toISO8601(node_document.properties["cm:created"]) + "**";
    }
	  element['name'] =  node_document.properties["cm:name"];
	  element['id'] =  node_document.nodeRef;
	  element['size'] =  node_document.size;
	  element['path'] = node_document.webdavUrl;
	  for (var property in node_document.properties) {
			if(property.indexOf("gofast.model") > 0) {
				element[property.substr(14)] = node_document.properties[property];
			}
		}
	  //element['nid'] = node_document.properties["{gofast.model}nid"];
    arraydescendants.push(element);
  }
}

function getFolder(node_folder, isGroup) {
  var element = [];
  if (node_folder.isContainer && !isGroup && node_folder.hasPermission("Write") == true) {
    element["url"] = node_folder.webdavUrl;
		arraydescendants.push(element);
  }
}

function getGroup(node_group, isGroup) {
  var element = [];
  if (node_group.isContainer && isGroup) {
    element["url"] = node_group.webdavUrl;
	for (var property in node_group.properties) {
			if(property.indexOf("gofast.model") > 0) {
				element[property.substr(14)] = node_group.properties[property];
			}
		}
		arraydescendants.push(element);
  }
}

function getTemplates(node_template) {
  for each(var child in node_template.children) {
    if (child.isDocument) {
      getDocument(child);
    } else {
      getTemplates(child);
    }
  }
}

function getDescendants(node, recursion)
{
  // Looping for each children of node
  if (node !== null) {
    for each (var child in node.children)
    {
	  // Excluding alfresco technical folders
	  if(child.name.indexOf('surf-config') !== -1) {
		continue;
	  }
      var isGroup = nodeIsGroup(child.name);

      if (document_type === "documents") {
        getDocument(child);
      } else if (document_type === "folders") {
        getFolder(child, isGroup);
      } else if (document_type === "groups") {
        getGroup(child, isGroup);
	  } else if (document_type === "groupsfolders") {
	    getFolder(child, isGroup);
	    getGroup(child, isGroup);
      } else if (document_type === "templates") {
        if (child.name.equals("TEMPLATES")) {
          getTemplates(child);
        }
      } else {
        getDocument(child);
        getFolder(child, isGroup);
        getGroup(child, isGroup);
      }
	  if(restrictdepth == "true" ){		
		if(recursion == true || recursion == "template"){		 
			 
		    if(document_type === "templates"){
				if(recursion == "template"){
					getDescendants(child, false);
				}else{
					getDescendants(child, "template");
				}
			}else{
				if (child.isContainer && !node.name.equals("TEMPLATES")) {
					getDescendants(child, false);
				}
			}
	    }
	  }else{
		   if (child.isContainer && !node.name.equals("TEMPLATES")) {				
				getDescendants(child, true);
			 }
	  }
	 
    }
  }
}

getDescendants(node, true);

descendants = jsonUtils.toJSONString(arraydescendants);
render = descendants;

model.myStatus = render;