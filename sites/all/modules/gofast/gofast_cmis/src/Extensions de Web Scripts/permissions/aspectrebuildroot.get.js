function gofast_recurse(el) {
	if(!el.getIsLocked()){
		setAspect(el);
		if(el.getName() == 'Sites'){
			var children = el.childFileFolders(true, true);
			if(children){
				for(var j=0; j < children.length; j++) {
					var gofastIsLocked = children[j].getIsLocked();
					if(!gofastIsLocked){
						setAspect(children[j]);
					}
				}
			}
		}
	}
}

function setAspect(node){
	node.save();
	if(node.addAspect("gofast:drupalorigin")){
		logger.log("ADD: Aspect drupalorigin" + " of folder/file " + node['name']);
	}
	else{
		logger.log("FAIL TO ADD: Aspect drupalorigin" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect drupalorigin" + " of folder/file " + node['name']+"<br /><br />";
	}
	if(node.addAspect("gofast:nodeproperties")){
		logger.log("ADD: Aspect nodeproperties" + " of folder/file " + node['name']);
	}
	else{
		logger.log("FAIL TO ADD: Aspect nodeproperties" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect nodeproperties" + " of folder/file " + node['name']+"<br /><br />";
	}
	if(node.addAspect("emailserver:aliasable")){
		logger.log("ADD: Aspect aliasable" + " of folder/file " + node['name']);
	}
	else{
		logger.log("FAIL TO ADD: Aspect aliasable" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect aliasable" + " of folder/file " + node['name']+"<br /><br />";
	}
	node.save();
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
	if(t[i]['name'] == 'Sites' || t[i]['name'] == 'Espaces Utilisateurs'){
		logger.log("_______Global recursing in " + t[i]['name']);
		gofast_recurse(t[i]);
	}
}

model.output = model.output+"End of work. ";
