/*Set permission to a folder using Alfresco javascript API*/

//search for the folder node using lucene search
var Node = search.findNode(args.reference);

//on recupere le dossier des pièces jointes de ce mail
var folder_attach= Node.assocs["imap:attachmentsFolder"][0];
var folder_destination = search.findNode(args.destination);
folder_attach.move(folder_destination);
model.myStatus = folder_attach.displayPath;


