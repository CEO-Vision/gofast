function gofast_recurse(el) {
	stat_recurse = stat_recurse+1;
	if(!el.getIsLocked()){
		setAspect(el);
		var children = el.childFileFolders(true, true);
		if(children){
			for(var j=0; j < children.length; j++) {
				var isContainer = children[j].getIsContainer();	
				var gofastIsLocked = children[j].getIsLocked();
				if(!gofastIsLocked){
					if (isContainer == 1) {
						gofast_recurse(children[j]);
					}
				}
			}
		}
	}
}

function setAspect(node){
	stat_set_aspect = stat_set_aspect+1;
	node.save();
	if(node.addAspect("gofast:drupalorigin")){
		logger.log("ADD: Aspect drupalorigin" + " of folder/file " + node['name']);
		stat_set_aspect = stat_set_aspect+1;
	}
	else{
		logger.log("FAIL TO ADD: Aspect drupalorigin" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect drupalorigin" + " of folder/file " + node['name']+"<br /><br />";
		stat_fail_aspect = stat_fail_aspect+1;
	}
	if(node.addAspect("gofast:nodeproperties")){
		logger.log("ADD: Aspect nodeproperties" + " of folder/file " + node['name']);
		stat_set_aspect = stat_set_aspect+1;
	}
	else{
		logger.log("FAIL TO ADD: Aspect nodeproperties" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect nodeproperties" + " of folder/file " + node['name']+"<br /><br />";
		stat_fail_aspect = stat_fail_aspect+1;
	}
	if(node.addAspect("emailserver:aliasable")){
		logger.log("ADD: Aspect aliasable" + " of folder/file " + node['name']);
		stat_set_aspect = stat_set_aspect+1;
	}
	else{
		logger.log("FAIL TO ADD: Aspect aliasable" + " of folder/file " + node['name']);
		model.output = model.output+"FAIL TO ADD: Aspect aliasable" + " of folder/file " + node['name']+"<br /><br />";
		stat_fail_aspect = stat_fail_aspect+1;
	}
	node.save();
}

var stat_recurse = 0;
var stat_set_aspect = 0;
var stat_fail_aspect = 0;
//We get the entire repository
var root_childs = userhome.getParent().getChildren();
for(var d in root_childs){
	if(root_childs[d]['name'] == 'Espace racine'){
		var node = root_childs[d];
	}
}
//We get the child folders of this repository
model.output = "Executing...<br /><br />";
var t = node.childFileFolders(true, true);
var alldescendants = [];
for(var i = 0; i < t.length; i++){
	if(t[i]['name'] == 'Sites' || t[i]['name'] == 'Espaces Utilisateurs'){
		logger.log("_______Global recursing in " + t[i]['name']);
		gofast_recurse(t[i]);
	}
}

model.output = model.output+"End of work. " + stat_recurse + " folders recursivly reached. " + stat_set_aspect + " successful aspect affectation. " + stat_fail_aspect + " failed aspect affectation.<br /><br />";
