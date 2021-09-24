var node = search.findNode(args.reference);
var clear = args.clear
var force = args.force
var hash = null;

if(clear){
    node.properties["{}onlyoffice:editing-hash"] = null;
    node.save();
    var hash = "cleared";
}else if(force){
    hash = force;
    node.properties["{}onlyoffice:editing-hash"] = hash;
    node.save();
}else{
    if(node.properties["{}onlyoffice:editing-hash"] == null){
        hash = Math.random().toString(36).substr(2, 5)+Math.random().toString(36).substr(2, 5)+Math.random().toString(36).substr(2, 5)+Math.random().toString(36).substr(2, 5);
        node.properties["{}onlyoffice:editing-hash"] = hash;
        node.save();
    }else{
        hash = node.properties["{}onlyoffice:editing-hash"];
    }
}

model.hash = hash;