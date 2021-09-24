/*Alter permissions on an archived document or folder using Alfresco javascript API*/
var node = search.findNode(args.reference);

//Get node current permissions
var permissions = node.getPermissions();

//Remove inheritence if needed
node.setInheritsPermissions(false);
    //Fetch into current permissions
    for each (p in permissions)
    {
            var group_array = p.split(";");
            group = group_array[1];
            try{
                //replace all classic RO permission by DUA_Archived permission               
		if(group_array[1].substr(-6) == "_ADMIN" || group_array[1].substr(-9) == "_STANDARD"){
                   //This is a space not RO permission, removes it
		   node.removePermission(group_array[2],group);  
		 node.setPermission("DUA_Archived",group);
		}else if(group_array[2] == "Coordinator"){
                    //This is a private space, set it to RO
                    node.removePermission(group_array[2],group);
                    node.setPermission("DUA_Archived",group);   
                }else{
                    //This is another RO permission, set it again in case the inheritence removes it
                    node.setPermission(group_array[2],group);
                }
                			
            }catch(ex){

            }
    }
    
node.properties['gofast:preventDelete'] = true;
node.save();
model.myStatus = "Permission was set successfully!";
