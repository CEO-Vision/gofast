
//search for the folder node using lucene search
var node = search.findNode(args.reference);
var only_last = args.last;
logger.log(args.newfunction);


        /*
        * Update aspects if needed
        * Warning : In some case, save the node (trigger again the rules etc...)
        */
        function updateAspects() {
                if (node.isDocument) {

                        if (node.hasAspect("cm:versionable") == false) {
                                node.addAspect("cm:versionable");
                                performRequest = false;
                                logger.log("add aspect versionable on node : " + node.name);
                        } else {
                                if (node.properties["autoVersionOnUpdateProps"] == true) {
                                        node.properties["autoVersionOnUpdateProps"] = false;
                                        node.save();
                                        performRequest = false;
                                }
                        }


                        if (node.hasAspect("gofast:drupalorigin") == false) {
                                node.addAspect("gofast:drupalorigin");
                                node.addAspect("gofast:nodeproperties");
                                performRequest = false;
                                logger.log("add aspects on node : " + node.name);
                        } else {
                                logger.log("already have aspects on node : " + node.name);
                        }
                }
        }

        if(node == null){
        model.myStatus = "unable to find doc";
        }else{
        updateAspects();

        if(args.newfunction === null) {

                function versionHistoryToObject(versionHistory, last) {
                        var version = {};
                        version.label = versionHistory.label;
                        version.createdDate = utils.toISO8601(versionHistory.createdDate);
                        version.creator = versionHistory.creator;
                        version.type = versionHistory.type != '' ? versionHistory.type : "MAJOR";
                        version.description = versionHistory.description;
                        version.nodeRef = versionHistory.nodeRef;
                        var properties = JSON.stringify(versionHistory.versionProperties);
                        properties = properties.substring(properties.indexOf("node-uuid\":\"")+12);
                        version.uuid = properties.substr(0, properties.indexOf('"'));

                        if(last == true){
                                version.author = node.properties["author"];
                                version.mimetype = node.mimetype;
                                version.name = node.name;
                                version.length = node.size;
                        }
                        return version;
                }

                 function nodeToObject(node) {
                        var version = {};                    
                        var history = node.getVersionHistory();
                        if(history !== null){
                                if (history.length > 0) {
                                        node.properties["modifier"] = history[0].creator;
                                        node.properties["modified"] = history[0].createdDate;
                                }
                        }
                        version.label = node.properties["versionLabel"];
                        version.createdDate = utils.toISO8601(node.properties["created"]);
                        version.modifiedDate = utils.toISO8601(node.properties["modified"]);
                        version.creator = node.properties["creator"];
                        version.type = node.type != '' ? node.type : "MAJOR";
                        version.description = node.description;
                        version.nodeRef = node.nodeRef;
                        version.author = node.properties["author"];
                        version.modifier = node.properties["modifier"];
                        version.mimetype = node.mimetype;
                        version.name = node.name;
                        version.length = node.size;
                        return version;
                }

                if(only_last == "true"){
                        var versions = [];
                        //var history = node.getVersionHistory();
                        //var history = node.versionHistory;
                        versions.push(nodeToObject(node));
                }else{
                        var history = node.getVersionHistory();

                        var versions = [];
                        for(var i in history){
                                if(i == 0){
                                        versions.push(versionHistoryToObject(history[i], true));
                                }else{
                                        versions.push(versionHistoryToObject(history[i], false));
                                }
                        }
                }
                model.myStatus = jsonUtils.toJSONString(versions);
        } else {
        var last = args.last;
        var history = node.versionHistory;
        var renderArray = {};
        var render = "";
        var versions = [];
        if(last == "true"){
                if(history != null){
                        render = history[0].label;
                        render += ";"+utils.toISO8601(history[0].createdDate);
                        render += ";"+history[0].creator;
                        versions.push(render);
                }else{
                        render = "1.0";
                        versions.push(utils.toISO8601(node.properties["cm:created"]) + ';' + node.properties["cm:creator"]);
                }
        } else{
                for(var i in history){
                versions.push(history[i].label);
                }
        }

        function versionHistoryToObject(versionHistory) {
                var version = {};
                version.label = versionHistory.label;
                version.createdDate = utils.toISO8601(versionHistory.createdDate);
                version.creator = versionHistory.creator;
                var properties = JSON.stringify(versionHistory.versionProperties);
                properties = properties.substring(properties.indexOf("node-uuid\":\"")+12);
                version.uuid = properties.substr(0, properties.indexOf('"'));
                return version;
        }

        //render = utils.toISO8601(history[1].createdDate);
        model.myStatus = versions.join(';');
        }
        }



