/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
logger.log("args : "+ jsonUtils.toJSONString(args));
var node = search.findNode(args.reference);
var role = args.role;
//on supprime toutes les permissions sur le doc
var permissions = node.getPermissions();

var spaces = args.spaces;
var private_spaces = args.private_spaces;

var array_spaces = spaces.split(";");
var array_private_spaces = private_spaces.split(";");

var length_array_spaces = array_spaces.length;
var length_private_array_spaces = array_private_spaces.length;
if(length_array_spaces == 1 && spaces === ""){
    length_array_spaces = 0;
}
if(length_private_array_spaces == 1 && private_spaces === ""){
    length_private_array_spaces = 0;
}

var sum = (parseInt(length_private_array_spaces) + parseInt(length_array_spaces));
logger.log("sum : "+sum);
if(sum <= 1){
    logger.log("if : "+sum);
    node.setInheritsPermissions(true);
    
    // Remove all the old permissions
    var permissions = node.getPermissions();
    for each (var permission in permissions)
    {
      var group_array = permission.split(";");
      group = group_array[1];
      try {
            node.removePermission(group_array[2], group);
      } catch (ex) {
      }
    }

    model.myStatus = jsonUtils.toJSONString(node.getPermissions());

}else{
logger.log("else : "+sum);
// Set folder non-inherited
node.setInheritsPermissions(false);

// Remove all the old permissions
var permissions = node.getPermissions();
for each (var permission in permissions)
{
  var group_array = permission.split(";");
  group = group_array[1];
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

if(array_spaces.length + array_private_spaces === 1) {
	node.setInheritsPermissions(true);
} else {
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
}

logger.log("Saving node");
//node.save();

model.myStatus = jsonUtils.toJSONString(node.getPermissions());


}