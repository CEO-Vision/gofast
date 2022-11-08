//search for the folder node using lucene search
var node = search.findNode(args.reference);
var render = "";
var document_type = args.type;
var restrictdepth = args.restrictdepth;
var origine = encodeURI(decodeURIComponent(args.origine));
var depth = 0;

var privateSpacePath;

//debug
//restrictdepth = "true";

var descendants = "";
var arraydescendants = [];

// Prevent empty origine
if (origine === null) {
  origine = "/Sites/";
};

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
      element['creator'] = history[0].creator;
      element['version'] = history[0].label;
      element['date_version'] = utils.toISO8601(history[0].createdDate);
      element["url"] = node_document.properties["cm:name"] + "**" + node_document.nodeRef + "**" + history[0].creator + "**" + node_document.size + "**" + history[0].label + "**" + utils.toISO8601(history[0].createdDate) + "**";
    } else {
      element['creator'] = node_document.properties["cm:creator"];
      element['version'] = "1.0";
      element['date_version'] = utils.toISO8601(node_document.properties["cm:created"]);
      element["url"] = node_document.properties["cm:name"] + "**" + node_document.nodeRef + "**" + node_document.properties["cm:creator"] + "**" + node_document.size + "**1.0**" + utils.toISO8601(node_document.properties["cm:created"]) + "**";
    }
    element['name'] = node_document.properties["cm:name"];
    element['id'] = node_document.nodeRef;
    element['size'] = node_document.size;
    element['path'] = node_document.webdavUrl;
    element['ismirrored'] = false;
    for (var property in node_document.properties) {
      if (property.indexOf("gofast.model") > 0) {
        element[property.substr(14)] = node_document.properties[property];
      }
    }
    //element['nid'] = node_document.properties["{gofast.model}nid"];
    arraydescendants.push(element);
  }
}

function getFolder(node_folder, isGroup) {

  var currentPath = origine;
  // Remove '/Sites/' from the path (in origine there isn't '/webdav/')
  currentPath = currentPath.substr(currentPath.indexOf("/Sites/") + "/Sites/".length - 1);

  var currentNode = node_folder.webdavUrl;
  // Remove '/webdav/Sites/' from the path
  currentNode = currentNode.substr(currentNode.indexOf("/webdav/Sites/") + "/webdav/Sites/".length - 1);

  var element = [];
  var arrayNode = [];
  var webdavUrl = node_folder.webdavUrl;

  // In case of first getDescendants call (where origine is /Sites/), if there is a mirror whith a wrong path (if main emplacement is a space instead of private space) then we will fix it
  if (isGroup && origine == "/Sites/") {
    // Split currentNode and get last element
    var arrayCurrentNode = currentNode.split("/");
    var lastElement = arrayCurrentNode[arrayCurrentNode.length - 1];
    var groups = ["_Groups", "_Extranet", "_Public", "_Organization", "FOLDERS%20TEMPLATES"];
    if (groups.includes(lastElement) == false) {
      // Keep actual private space path
      privateSpacePath = currentNode;
    }
  }


  if (node_folder.isContainer && !isGroup && node_folder.hasPermission("Write") == true) {

    // Check if element webdav url begin with the node webdav url
    if (currentNode.indexOf(currentPath) === -1 || currentPath == "/") {
      arrayNode = currentNode.split('/');
      currentPath = currentPath.split('/');

      // Check if we need to fix the folder path (if main emplacement is a space instead of private space)
      var fixPrivateSpace = false;
      var goodPath = "";
      if (origine == "/Sites/" && "/" + arrayNode[1] != privateSpacePath) {
        fixPrivateSpace = true;
        goodPath = "/Sites" + privateSpacePath;
      }
      
      // Remove space from the path to get the mirror path
      if (currentPath != "," || fixPrivateSpace) {
        // Remove each element begin by "_"
        for (var i = 0; i < arrayNode.length; i++) {
          if (nodeIsGroup(arrayNode[i])) {
            arrayNode.splice(i, 1);
            i--;
          }
        }

        // Remove each element begin by "_"
        for (var i = 0; i < currentPath.length; i++) {
          if (nodeIsGroup(currentPath[i])) {
            currentPath.splice(i, 1);
            i--;
          }
        }
      }

      arrayNode = arrayNode.join('/');
      currentPath = currentPath.join('/');


      // Remove path already visited
      arrayNode = decodeURIComponent(arrayNode).replace(decodeURIComponent(currentPath), '');
      
      
      // Fix webdavUrl
      if (fixPrivateSpace) {
        webdavUrl = "/webdav" + goodPath + "/" + arrayNode;
      } else {
        webdavUrl = "/webdav" + origine + arrayNode;
      }
    }
    element["url"] = webdavUrl;
    element['name'] = node_folder.properties["cm:name"];
    element['id'] = node_folder.nodeRef;
    for (var property in node_folder.properties) {
      if (property.indexOf("gofast.model") > 0) {
        element[property.substr(14)] = node_folder.properties[property];
      }
    }
    arraydescendants.push(element);
  }
}



function getGroup(node_group, isGroup) {
  var element = [];
  if (node_group.isContainer && isGroup) {
    element["url"] = node_group.webdavUrl;
    for (var property in node_group.properties) {
      if (property.indexOf("gofast.model") > 0) {
        element[property.substr(14)] = node_group.properties[property];
      }
    }
    element['name'] = node_group.properties["cm:name"];
    element['id'] = node_group.nodeRef;
    element['ismirrored'] = false;
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

function getDescendants(node, recursion) {
  // Looping for each children of node
  if (node !== null) {
    for each(var child in node.children) {
      // Excluding alfresco technical folders
      if (child.name.indexOf('surf-config') !== -1) {
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
      if (restrictdepth == "true") {
        if (recursion == true || recursion == "template") {

          if (document_type === "templates") {
            if (recursion == "template") {
              getDescendants(child, false);
            } else {
              getDescendants(child, "template");
            }
          } else {
            if (child.isContainer && !node.name.equals("TEMPLATES")) {
              getDescendants(child, false);
            }
          }
        }
      } else {
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
