/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var Node = search.findNode(args.reference);
var Destination = search.findNode(args.ref_dest);

Node.copy(Destination, true);
model.myStatus = "debug";


