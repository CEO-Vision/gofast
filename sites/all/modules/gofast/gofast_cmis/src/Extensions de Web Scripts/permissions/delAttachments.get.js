/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var folderNode = search.findNode(args.folderName);

if(args.attach == "true"){
  	var attachfolder = folderNode.assocs["imap:attachmentsFolder"][0];
	supp(attachfolder);
	folderNode.remove();
	attachfolder.remove();
}else{
	supp(folderNode);
        folderNode.remove();
}
model.myStatus = args.attach;


function supp(node)
{
        for each (n in node.children)
        {
                if(n.isDocument)
                {
			n.remove();
                }
                else if(n.isContainer){
                        supp(n);
		}
        }
}

