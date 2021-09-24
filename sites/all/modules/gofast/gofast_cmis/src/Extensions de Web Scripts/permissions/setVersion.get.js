/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search


var Node = search.findNode(args.reference);
if(Node.properties["cm:autoVersion"] != true){
        Node.properties["cm:autoVersion"]=true;
        Node.save();
}
        if(args.tag == 'true'){
                if(Node.versionHistory == null){
                        Node.createVersion("Version initiale", true);
                }else{
                }
        }


model.myStatus = "done";


