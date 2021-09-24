//Hide data dictionary for all users except administrators

var datadictionary = companyhome.childByNamePath("Dictionnaire de données");
var imaphome = companyhome.childByNamePath("Racine IMAP");
var imapattach = companyhome.childByNamePath("Pièces jointes IMAP");
var espaceinvite = companyhome.childByNamePath("Espace invité");
var espaceuser = companyhome.childByNamePath("Espaces Utilisateurs");


  imaphome.setInheritsPermissions(false);
  imapattach.setInheritsPermissions(false);
  imapattach.removePermission("FullControl");
  espaceinvite.removePermission("Consumer");
  espaceuser.setInheritsPermissions(false);

var list = datadictionary.children;

for (var i in list) {
   var child = list[i];
   
   child.setInheritsPermissions(false);
   child.setPermission("Consumer", "GROUP_EVERYONE");   
}

datadictionary.removePermission("Consumer");

model.property = "OK";
