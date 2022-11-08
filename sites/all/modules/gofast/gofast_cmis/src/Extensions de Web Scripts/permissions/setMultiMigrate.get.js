/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
logger.log("args : "+ jsonUtils.toJSONString(args));
var node = search.findNode(args.reference);
var role = args.role;
//on supprime toutes les permissions sur le doc
var permissions = node.getPermissions();

/*node.setInheritsPermissions(false);
for each (p in permissions)
{
      var group_array = p.split(";");
      group = group_array[1];
	try{
      		//node.removePermission(role,group);
      		node.removePermission(group_array[0],group);
	}catch(ex){

	}
}*/

if(node.properties["autoVersionOnUpdateProps"] == true){									
  node.properties["autoVersionOnUpdateProps"] = false;
  node.save();
}

// Check inherited state of the folder
if(node.inheritsPermissions()){
	model.myStatus = jsonUtils.toJSONString(node.getPermissions());
}

else{

	// Remove all the old permissions
	var permissions = node.getPermissions();
	for each (var permission in permissions)
	{
	  var group_array = permission.split(";");
	  vargroup = group_array[1];
	  try {
		node.removePermission(group_array[2], group);
	  } catch (ex) {
	  }
	}

	logger.log("Permission reset for " + node.name);

	//node.removePermission("Standard");
	var list_groups = decodeURIComponent(args.spaces);
	var list_private_spaces = decodeURIComponent(args.private_spaces);
	var array_spaces = list_groups.split(";");
	var array_private_spaces = list_private_spaces.split(";");

		for each (g in array_spaces)
		{
			//MODIF READONLY
			//node.setPermission(role,"GROUP_"+g);
			if(role == "Consumer"){
				node.setPermission(role,"GROUP_"+g);
			}else{
				logger.log("Standard: GROUP_" + g + "_STANDARD");
				logger.log("Coordinator: GROUP_" + g + "_ADMIN");
				logger.log("Consumer: GROUP_" + g);
				
				node.setPermission("Standard","GROUP_"+g+"_STANDARD");
				node.setPermission("Coordinator", "GROUP_"+g+"_ADMIN");
				node.setPermission("Consumer", "GROUP_"+g);
			}
			//FIN MODIF READONLY		
		}
		for each (private_space in array_private_spaces)
		{
			if(role === "Consumer"){
				node.setPermission(role, private_space);
			}else{
				logger.log("Coordinator: GROUP_" + private_space);
				
				node.setPermission("Coordinator", "GROUP_"+private_space);
			}
		}

	logger.log("Saving node");
	//node.save();

	model.myStatus = jsonUtils.toJSONString(node.getPermissions());
}