var nodeRef = args.nodeRef;
var propertyName = args.propertyName;
var targetValue = args.targetValue;

var folderNode = search.findNode(nodeRef);

if(targetValue == "Confidential"){
    targetValue = "Confidential Data"; 
}

function checkPropertyRecursively(folderNode) {
    var results = [];
    
    // Check files in the current folder
    var folderFiles = folderNode.children;
    for (var i = 0; i < folderFiles.length; i++) {
        var file = folderFiles[i];
        if (file.isDocument) {
            var propertyValue = file.properties[propertyName];
            results.push({
                name: file.name,
                found: propertyValue === targetValue, 
                targetValue: targetValue, 
                propertyValue: propertyValue, 
            });
        }
    }

    // Recursively check subfolders
    var subfolders = folderNode.children;
    for (var j = 0; j < subfolders.length; j++) {
        var subfolder = subfolders[j];
        if (subfolder.isContainer) {
            results = results.concat(checkPropertyRecursively(subfolder));
        }
    }

    return results;
}

var result = checkPropertyRecursively(folderNode);

result = jsonUtils.toJSONString(result);
model.hasFilesWithMetadataField = result;



