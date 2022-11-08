/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
logger.log("args : "+ jsonUtils.toJSONString(args));
var node = search.findNode(args.reference);

	// Set folder non-inherited
	node.setInheritsPermissions(false);

	// Remove all the old permissions
	var permissions = node.getPermissions();
	for each (var permission in permissions){
		var group_array = permission.split(";");
		group = group_array[1];
		try {
		node.removePermission(group_array[2], group);
		} catch (ex) {
		}
	}

	logger.log("Permission reset for " + node.name);

	var list_groups = decodeURIComponent(args.spaces);
	var array_spaces = list_groups.split(";");

		for each (g in array_spaces){
				logger.log("Coordinator: GROUP__#" + g + "_ADMIN");
				node.setPermission("Coordinator", "GROUP__#"+g+"_ADMIN");
				
				logger.log("Consumer: GROUP__#" + g);
				node.setPermission("Consumer", "GROUP__#"+g);
		}
		
	logger.log("Saving node");
	node.properties['description'] = "homepage";
	node.save();

	model.myStatus = jsonUtils.toJSONString(node.getPermissions());
