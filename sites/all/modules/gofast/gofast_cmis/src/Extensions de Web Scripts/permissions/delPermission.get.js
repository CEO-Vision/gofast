/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
//var folderNode =  search.luceneSearch("TYPE:\"{http://www.alfresco.org/model/content/1.0}folder\" AND @cm\\:name:"+args.folderName);
var folderNode = search.findNode(args.folderName);
//make sure we only get one node

//del permission “Coordinator” to user with username received in parameter
folderNode.removePermission("Coordinator", args.username);
model.myStatus = "Permission was removed!";
