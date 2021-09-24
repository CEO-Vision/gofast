
//search for the folder node using lucene search
var node = search.findNode(args.reference);
if(node === null){
  model.myStatus = "unable to find doc";
}else{      
    var permissions_return = [];
    var permissions_node = node.getPermissions();
    var is_inherit = node.inheritsPermissions();
    if(is_inherit == true){
       permissions_return.push("inherit_permission");
    }else{
        for(var i in permissions_node){ 
            if(permissions_node[i].replace("ALLOWED;GROUP_", "").split(";")[0] != ""){          
                    permissions_return.push(permissions_node[i].replace("ALLOWED;GROUP_", ""));
            }	      
        }
    }
    model.myStatus = jsonUtils.toJSONString(permissions_return);
}



