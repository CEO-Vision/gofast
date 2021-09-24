
//search for the folder node using lucene search
var node = search.findNode(args.reference);
var comment = args.comment

//we make a fake save to change last modifier
var old_description = node.properties.description;
node.properties.description = "temp";
node.save();
node.properties.description = old_description;
node.save();
var versionItem = node.createVersion(comment, true);

function versionHistoryToObject(versionHistory) {
  var version = {};
  version.label = versionHistory.label;
  version.createdDate = utils.toISO8601(versionHistory.createdDate);
  version.creator = versionHistory.creator;
  version.type = versionHistory.type;
  version.description = versionHistory.description;
  version.nodeRef = versionHistory.nodeRef;
  return version;
}

model.myStatus = jsonUtils.toJSONString(versionHistoryToObject(versionItem));