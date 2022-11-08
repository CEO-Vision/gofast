/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var node = search.findNode(args.reference);
var validators = args.validators.split(";");
var inverse = args.inverse;

if(inverse == 'true'){
	var permissions = node.getPermissions();
	for each (p in permissions)
	{
      		var group_array = p.split(";");
      		group = group_array[1];
        	try{
			 node.removePermission(group_array[2],group);
        	}catch(ex){

        	}
	}
	node.setInheritsPermissions(true);

}else{
	node.setInheritsPermissions(false);
	node.setPermission("Consumer", "GROUP_EVERYONE");
	for each (v in validators)
	{
		//set permission customer to everybody except validators
		node.setPermission("Coordinator", v);
	}
}
model.myStatus = "Permission was set successfully!";
