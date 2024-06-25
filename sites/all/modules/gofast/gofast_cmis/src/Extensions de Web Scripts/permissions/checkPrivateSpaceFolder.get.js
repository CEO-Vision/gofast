model.output = "";
var root_childs = userhome.getParent().getChildren();
for(var d in root_childs){
	if(root_childs[d]['name'] == 'Espace racine'){
		var node = root_childs[d];
	}
}

//We get the child folders of this repository
var t = node.childFileFolders(true, true);

for(var i = 0; i < t.length; i++){
	if(t[i]['name'] == 'Sites'){
		var document = t[i];
	}
}

check_private_space_folder(document);

function check_folder_perms(node)
{
    for each (n in node.children)
    {
        if(n.isContainer){
             if(!n.inheritsPermissions()){
                var permissions = n.getPermissions();
                if(permissions.length == 0){
                    //n.setInheritsPermissions(true);
                    logger.log("permission problem on folder: "+n.displayPath+"/"+n.name);
                }    
            }    
            check_folder_perms(n);
        }
    }
}

function check_private_space_perms(node, should_fix){
    
    var permissions = node.getPermissions();
    
    //logger.log(node.properties['{gofast.model}nid']);
    
    if (permissions.length == 0 || permissions.length > 1) {
        logger.log("Wrong permission for this space : "+n.displayPath+"/"+n.name);
        
        if(should_fix == true){
            
            var unique_name_group = "_#"+node.properties['{gofast.model}nid'];
            if(groups.getGroup(unique_name_group)!= null){
                model.output = model.output+"Permissions repaired on "+unique_name_group+"<br />";
                n.setPermission("Coordinator", "GROUP_" + unique_name_group);
                n.save();
            
                 logger.log("--> [OK] Perms fixed ");
            }else{
                logger.log("--> [ERROR] group : ["+unique_name_group+"] not found");
            }
        }
        
    }    
    
}


function check_private_space_folder(node)
{
    var max_check = 5000;
    var should_fix = true;
    var i = 0;
    for each (n in node.children)
    {
        logger.log(n.name);
        if(n.isContainer && n.properties['{gofast.model}bundle'] == 'private_space'){
        
        //    logger.log("Check permission for folder(s) in private space: "+n.displayPath+"/"+n.name);
            check_private_space_perms(n, should_fix);
            //check_folder_perms(n);
        }
        
        i++;
        if(i >= max_check){
            logger.log("Stop here"+n.displayPath+"/"+n.name);
            break;
        }
        
    
    }
}