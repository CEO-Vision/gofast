/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
/*var folderNode = search.findNode(args.folderName);

 //make sure we only get one node


 //set permission Monrole? to user with username received in parameter
 folderNode.setPermission("Coordinator", args.username);
 model.myStatus = "Permission was set successfully!";*/


var renderArray = {};

/**
 This function updates all the properties of the node aspect.
 */
function updatePermissions(node, user) {
  node.setPermission("Coordinator", user);
  renderArray.permission = { "Coordinator": user };
}

function removePermission(node, user) {
  var permissions = node.getPermissions();
  for (let permission of permissions) {
    var group_array = permission.split(";");
    var group = group_array[1];
    if (user === group) {
      try {
        node.removePermission(group_array[2], group);
        renderArray.permission = "reset : " + group_array[2] + " for " + group;
      } catch (ex) {
      }
    }
  }
}

// If there is a reference, otherwise do nothing
if (args.reference !== null) {
  var rootNode = search.findNode(args.reference);
  var userName = args.username;
  var reset = args.reset !== null ? true : false;

  if (rootNode !== null && userName !== null) {
    renderArray.status = "OK";
    if (!reset) {
      updatePermissions(rootNode, userName);
    } else {
      removePermission(rootNode, userName);
    }
  } else {
    renderArray.status = "KO";
    renderArray.message = "The reference or username is wrong or does not exist anymore";
  }
} else {
  renderArray.status = "KO";
  renderArray.message = "The argument reference is mandatory";
}

model.myStatus = jsonUtils.toJSONString(renderArray);
