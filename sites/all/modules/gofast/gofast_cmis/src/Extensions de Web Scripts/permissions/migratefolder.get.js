function gofast_recurse(el) {
	logger.log("RECURSE !");
	if(!el.getIsLocked()){
		var children = el.childFileFolders(true, true);
		if(children){
			for(var j=0; j < children.length; j++) {
				logger.log(children[j].getName());
				if(children[j].getName() == 'Groupes'){
					children[j].setName('_Groups');
					gofast_recurse(children[j]);
				}
				if(children[j].getName() == 'Public'){
					children[j].setName('_Public');
				}
				if(children[j].getName() == 'Organisations'){
					children[j].setName('_Organisations');
				}
				if(children[j].getName() == 'Extranet'){
					children[j].setName('_Extranet');
					children[j].move(siteNode);
				}
			}
		}
	}
}

model.output = "Executing...<br /><br />";
var root_childs = userhome.getParent().getChildren();
for(var d in root_childs){
	if(root_childs[d]['name'] == 'Espace racine'){
		var node = root_childs[d];
	}
}
//We get the child folders of this repository
var t = node.childFileFolders(true, true);

for(var i = 0; i < t.length; i++){
	if(t[i]['name'] == 'Sites'){
		var siteNode = t[i];
		gofast_recurse(t[i]);
	}
}

model.output = "End of work. ";
