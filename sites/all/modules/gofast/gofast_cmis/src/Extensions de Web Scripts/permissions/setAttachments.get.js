/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var folderNode = search.findNode(args.folderName);

//if(folderNode.isInheritsPermissions == true){
folderNode.setInheritsPermissions(false);
folderNode.takeOwnership(); 
//var myparent = folderNode.parent;

var myspace = folderNode.parent.name;
var myparent = folderNode.parent;
var ariane = "";
if(myspace == "Public"){
	var old = "Public";
}else{
	var old = "";
}
while (myspace != "Groupes" && myspace != "Organisations" && myspace != "Public" )
{
	old = myparent.name;
        ariane = "/"+myspace+ariane;
        myparent = myparent.parent;
        myspace = myparent.name;
}



//folderNode.setPermission("Consumer","GROUP_"+old);

//on change aussi le owner des documents dans ce dossier
changeownercontent(folderNode,old);

model.myStatus = old;
//}else{
//model.myStatus = "already executed";
//}


function changeownercontent(node,old)
{
        for each (n in node.children)
        {
                if(n.isDocument)
                {
			n.takeOwnership();
			if(old == "Public"){
				 n.setPermission("Consumer","GROUP_EVERYONE");
				// n.setPermission("Coordinator","GROUP_MANAGER");
			}else{
				//n.setPermission("Consumer","GROUP_"+old);
				n.setInheritsPermissions(false);
			}
                }
                if(n.isContainer)
                        changeownercontent(n,old);
        }
}

