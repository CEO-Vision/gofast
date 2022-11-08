/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var Node = search.findNode(args.reference);


Node.setOwner(args.user);

model.myStatus = "done";


