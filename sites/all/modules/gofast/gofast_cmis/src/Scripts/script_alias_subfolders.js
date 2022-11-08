logger.log("==== " + "STARTING SCRIPT " + "SCRIPT ALIAS SUBFOLDER" + " ====");

function normalize_alias(name) {
  var result = name;
  var re = /\'|\s+|\·|\\|\/|,|:|;|!|\?|&|°/g;
  var subst = '-';

  result = result.trim().toLowerCase();
  result = String.prototype.replace.call(result, /^_|_$/, '');

  // Accents
  result = String.prototype.replace.call(result, /[èéêë]/g, 'e');
  result = String.prototype.replace.call(result, /[ç]/g, 'c');
  result = String.prototype.replace.call(result, /[àáäâ]/g, 'a');
  result = String.prototype.replace.call(result, /[ìíïî]/g, 'i');
  result = String.prototype.replace.call(result, /[ùúüû]/g, 'u');
  result = String.prototype.replace.call(result, /[òóöô]/g, 'o');

  // Punctuation
  result = String.prototype.replace.call(result, re, subst);
  result = String.prototype.replace.call(result, /-+/g, subst);
  result = String.prototype.replace.call(result, /_/g, '-');
  return result;
}

if (person.properties.userName !== "admin" && person.properties.userName !== "System") {
  if (document.isContainer === true)
  {
    var emailalias_before = document.properties["emailserver:alias"];

    var itemName = normalize_alias(document.name);
    var items = [itemName];
    var parent = document.parent;

    while (parent.name != space.name && parent.name != "Sites") {
      itemName = normalize_alias(parent.name);
      items.push(itemName);
      parent = parent.parent;
    }

    var path = items.reverse().join('.');

    logger.log("UPDATING ALIAS VALUE WITH : " + path);

    var props = new Array(1);
    props["emailserver:alias"] = path;
    document.addAspect("emailserver:aliasable", props);

    /*//on verifie si le dossier en question est juste en dessous de Groupe ou Orga/ Si oui on ne fait rien
     if(document.parent.name != space.name){
     var myparent = document.parent;
     var myspace = myparent.properties["cm:name"];
     var groupe = document.properties["cm:name"];

     while (myspace != space.name)
     {
     var groupe = normalize_alias(groupe);
     groupe = myspace+"."+groupe;
     myparent = myparent.parent;
     myspace = myparent.properties["cm:name"];
     }

     str = document.name;
     str = str.trim(); //replace('/^\s+|\s+$/g', ''); // trim
     str = str.toLowerCase();

     //si le dernier caractere est _ (sous groupe) je supprime ce _ pour le calcul de l'email alias
     if(str.length > 0){
     var first_character = str.charAt(1)
     if(first_character == "_"){
     str = str.slice(0, -1);
     }
     }


     // remove accents, swap ñ for n, etc
     var from = "'\s+àáäâèéëêìíïîòóöôùúüûñç·/_,:;!?&°";
     var to   = "--aaaaeeeeiiiioooouuuunc----------";
     var map = {};
     for (var i=0, l=from.length ; i<l ; i++) {
     str = str.replace(from.charAt(i), to.charAt(i));
     }

     str = str.replace('/[a-zA-Z0-9.\-]/g', '') // remove invalid chars
     .replace('/\s+/g', '-') // collapse whitespace and replace by -
     .replace('/-+/g', '-'); // collapse dashes

     //on recupere le nom du dossier qui correspond au groupe ou a l'orga
     var myspace = document.parent.properties["cm:name"];
     var myparent = document.parent;
     var groupe = document.properties["cm:name"];
     //groupe = document.name;

     while (myspace != space.name)
     {

     if(myspace.length > 0){
     //si le dernier caractere est _ (sous groupe) je supprime ce _ pour le calcul de l'email alias
     var last_character = myspace.charAt(myspace.length - 1)
     if(last_character == "-" || last_character == "_"){
     myspace = myspace.slice(0, -1);
     }

     }
     if(groupe.length > 0){
     //si le dernier caractere est _ (sous groupe) je supprime ce _ pour le calcul de l'email alias
     var last_character = groupe.charAt(groupe.length - 1)
     if(last_character == "-" || last_character == "_"){
     groupe = groupe.slice(0, -1);
     }
     }




     groupe = groupe.replace('/[a-zA-Z0-9.\-]/g', '') // remove invalid chars
     .replace('/\s+/g', '-') // collapse whitespace and replace by -
     .replace('/-+/g', '-'); // collapse dashes
     groupe = groupe.toLowerCase();
     var from = "' àáäâèéëêìíïîòóöôùúüûñç/_,:;!?&°";
     var to   = "--aaaaeeeeiiiioooouuuunc---------";
     for (var i=0, l=from.length ; i<l ; i++) {
     groupe = groupe.replace(from.charAt(i), to.charAt(i));
     }


     myspace = myspace.replace('/[a-zA-Z0-9.\-]/g', '') // remove invalid chars
     .replace('/\s+/g', '-') // collapse whitespace and replace by -
     .replace('/-+/g', '-'); // collapse dashes
     myspace = myspace.toLowerCase();
     for (var i=0, l=from.length ; i<l ; i++) {
     myspace = myspace.replace(from.charAt(i), to.charAt(i));
     }


     groupe = myspace+"."+groupe;
     myparent = myparent.parent;
     myspace = myparent.properties["cm:name"];
     }

     // remove accents, swap ñ for n, etc
     var from = "' àáäâèéëêìíïîòóöôùúüûñç/_,:;!?&°";
     var to   = "--aaaaeeeeiiiioooouuuunc---------";
     for (var i=0, l=from.length ; i<l ; i++) {
     groupe = groupe.replace(from.charAt(i), to.charAt(i));
     }
     //	if(document.properties["cm:description"] == "prevent_delete" && person.properties.userName != "admin"){
     //	        deleteGroup("prevent");
     //	}
     try{
     //PRONIC CONTOURNEMENT
     //var n=group.indexOf("pronic");
     //if(n == -1){
     var props = new Array(1);
     props["emailserver:alias"] = groupe;
     document.addAspect("emailserver:aliasable", props);
     //}
     }catch(ex){

     }
     }else{
     var groupe = document.name;
     groupe = groupe.replace('/^\s+|\s+$/g', ''); // trim
     groupe = groupe.toLowerCase();

     // remove accents, swap ñ for n, etc
     var from = "' àáäâèéëêìíïîòóöôùúüûñç/_,:;!?&°";
     var to   = "--aaaaeeeeiiiioooouuuunc---------";
     for (var i=0, l=from.length ; i<l ; i++) {
     groupe = groupe.replace(from.charAt(i), to.charAt(i));
     }

     var props = new Array(1);
     props["emailserver:alias"] = groupe;
     document.addAspect("emailserver:aliasable", props);
     //on est dans un dossier de groupe, donc envoi d'une requete http pour prevenir du changement de nom du groupe
     var myperson = person.properties.userName;
     if(groupe != emailalias_before){
     simplehttpresult = SimpleHttpConnection
     .getContentAsString("http://localhost/alfresco_script.php?op=ChangeGroupe&groupe="+document.nodeRef+"&person="+myperson);
     }


     }
     if(groupe != emailalias_before){
     simplehttpresult = SimpleHttpConnection
     .getContentAsString("http://localhost/alfresco_script.php?op=Invalide_cache&groupe="+document.nodeRef);
     }*/

  }
}

logger.log("==== " + "ENDING SCRIPT " + "SCRIPT ALIAS SUBFOLDER" + " ====");