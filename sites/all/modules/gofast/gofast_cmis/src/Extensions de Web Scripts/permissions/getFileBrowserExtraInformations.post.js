/*
 * Implements JSON
 */
var JSONgf = {
    parse: function (sJSON) { return eval(sJSON); },
    stringify: (function () {
        var toString = Object.prototype.toString;
        var isArray = Array.isArray || function (a) { return toString.call(a) === '[object Array]'; };
        var escMap = { '"': '\\"', '\\': '\\\\', '\b': '\\b', '\f': '\\f', '\n': '\\n', '\r': '\\r', '\t': '\\t' };
        var escFunc = "" + function (m) { return escMap[m] || '\\u' + (m.charCodeAt(0) + 0x10000).toString(16).substr(1); };
        var escRE = "" + /[\\"\u0000-\u001F\u2028\u2029]/g;
        return function stringify(value) {
            if (value == null) {
                return 'null';
            } else if (typeof value === 'number') {
                return isFinite(value) ? value.toString() : 'null';
            } else if (typeof value === 'boolean') {
                return value.toString();
            } else if (typeof value === 'object') {
                if (typeof value.toJSON === 'function') {
                    return stringify(value.toJSON());
                } else if (isArray(value)) {
                    var res = '[';
                    for (var i = 0; i < value.length; i++)
                        res += (i ? ', ' : '') + stringify(value[i]);
                    return res + ']';
                } else if (toString.call(value) === '[object Object]') {
                    var tmp = [];
                    for (var k in value) {
                        if (value.hasOwnProperty(k))
                            tmp.push(stringify(k) + ': ' + stringify(value[k]));
                    }
                    return '{' + tmp.join(', ') + '}';
                }
            }
            return '"' + value.toString().replace(escRE, escFunc) + '"';
        };
    })()
};

//@params ownerifro == owner if read-only, which can happen with folders
function getFinalPermission(user_groups, permissions, node, ownerifro) {
    var readonly = false;
    var contributor = false;
    var administrator = false;

    //Content that does not include any edition permission
    var onlyreadonly = true;

    //Tells if we are owner
    var owner = false;

    //If we are owner of this document, we have complementary rights on it
    if (node.hasAspect("cm:ownable")) {
        if (person.properties.userName === node.properties.owner) {
            if (ownerifro) {
                owner = true;
            } else {
                return "owner";
            }
        }
        //The "creator" attribute exists only on folders
    } else {
        if (person.properties.userName === node.properties.creator) {
            if (ownerifro) {
                owner = true;
            } else {
                return "owner";
            }
        }
    }

    for (var k = 0; k < permissions.length; k++) {
        if (typeof permissions[k] === "undefined") {
            continue;
        }

        //First, we need to parse the group name and the associated permission
        var permission = {
            name: permissions[k].substr(permissions[k].indexOf(";") + 1, permissions[k].lastIndexOf(";") - permissions[k].indexOf(";") - 1),
            permission: permissions[k].substr(permissions[k].lastIndexOf(";") + 1)
        };

        if (permission.permission === "Coordinator" || permission.permission === "Standard") {
            //This content is not archived, DUA...
            onlyreadonly = false;
        }

        //Try to find matches in our groups
        for (var j = 0; j < user_groups.length; j++) {
            if (user_groups[j] === permission.name) { //This group permissions match one of our permissions
                if (permission.permission === "Coordinator") {
                    administrator = true;
                } else if (permission.permission === "Standard") {
                    contributor = true;
                } else if (permission.permission === "Consumer") {
                    readonly = true;
                }
            }
        }
    }

    //Finally, read variables and return proper result
    if (administrator) {
        return "administrator";
    } else if (readonly && owner) {
        //Special case when we are owner of a folder but RO in the space
        //This case is treated here in order not to return "contributor"
        return "owner";
    } else if (contributor) {
        return "contributor";
    } else if (onlyreadonly) {
        return "onlyreadonly";
    } else if (readonly) {
        return "readonly";
    } else {
        //Should never happen
        return null;
    }
}

//Get request content
var requestcontent = requestbody.content;

//Extract files and folders part
var requestparams = requestcontent.split("&");

// Decode each parts of request params
for (var index = 0; index < requestparams.length; index++) {
    requestparams[index] = decodeURIComponent(decodeURIComponent(requestparams[index]));
}

var requestfiles = requestparams[0].substr(6);
var requestfolders = requestparams[1].substr(8);

var files = JSONgf.parse(requestfiles);
var folders = JSONgf.parse(requestfolders);
var currentfolder = requestparams[2].substr(15);

var output_files_dates = [];
var output_files_permissions = [];
var output_files_visibility = [];
var output_folders_alf_refs = [];

var output_folders_visibility = [];
var output_folders_permissions = [];

var output_current_folder_permissions = [];

var output_files_nids = [];
var output_files_node_refs = [];

//Retrieve my groups to compare them with content groups
var user_groups_obj = people.getContainerGroups(person);
var user_groups = [];
for (var i = 0; i < user_groups_obj.length; i++) {
    user_groups.push(user_groups_obj[i].properties.authorityName);
}

//Fetch into files and retrieve the last version date, the permissions and the visibility
if (files !== null) {
    for (var i = 0; i < files.length; i++) {
        //search for the folder node using lucene search
        var node = companyhome.childByNamePath(files[i]);

        if (node === null) {
            output_files_dates.push(null);
            output_files_permissions.push(null);
            output_files_visibility.push(null);
        } else {
            try {
                //Retrieve last version date
                var version = node.properties['versionLabel'];
                var version_obj = node.getVersion(version);
                output_files_dates.push(utils.toISO8601(version_obj["createdDate"]));
            } catch (e) {
                logger.log(e);
                output_files_dates.push(null);
            }

            try {
                //Retrieve gofast nid
                var nid = node.properties['{gofast.model}nid'];
                output_files_nids.push(nid);
            } catch(e) {
                output_files_nids.push(false);
            }
            
            try {
                var node_ref = node.id;
                output_files_node_refs.push(node_ref);
            } catch (e) {
                logger(e)
                output_files_node_refs.push(false)
            }

            try {
                //Retrieve permissions
                var permissions = node.getPermissions();
                //Match file permissions with user permissions and extract the final permissions
                var final_permission = getFinalPermission(user_groups, permissions, node, false);
                output_files_permissions.push(final_permission);
            } catch (e) {
                logger.log(e);
                output_files_permissions.push(null);
            }

            try {
                //Retrieve visibility
                var parents = node.getParents();
                var visibility = [];

                for (vi = 0; vi < parents.length; vi++) {
                    visibility.push(parents[vi].getWebdavUrl());
                }

                output_files_visibility.push(visibility);
            } catch (e) {
                logger.log(e);
                output_files_visibility.push(null);
            }

        }
    }
}

//Fetch into folders and retrieve the last version date, the permissions and the visibility
if (folders !== null) {
    for (var i = 0; i < folders.length; i++) {
        //search for the folder node using lucene search
        var node = companyhome.childByNamePath(folders[i]);

        if (node === null) {
            output_folders_visibility.push(null)
            output_folders_permissions.push(null);
        } else {

            try {
                //Retrieve permissions
                var permissions = node.getPermissions();
                //Match file permissions with user permissions and extract the final permissions
                var final_permission = getFinalPermission(user_groups, permissions, node, true);
                output_folders_permissions.push(final_permission);
            } catch (e) {
                logger.log(e);
                output_folders_permissions.push(null);
            }

            try {
                //Retrieve visibility
                var parents = node.getParents();
                var visibility = [];

                for (vi = 0; vi < parents.length; vi++) {
                    visibility.push(parents[vi].getWebdavUrl());
                }

                output_folders_visibility.push(visibility);
            } catch (e) {
                logger.log(e);
                output_folders_visibility.push(null);
            }
            
            try {
                var alfRef = node.id;
                output_folders_alf_refs.push(alfRef);
            } catch(e){
                logger(e);
            }
        }
    }
}

//Retrieve current folder permissions
//search for the folder node using lucene search
var node = companyhome.childByNamePath(currentfolder);

if (node === null) {
    output_current_folder_permissions.push(null);
} else {

    try {
        //Retrieve permissions
        var permissions = node.getPermissions();
        //Match file permissions with user permissions and extract the final permissions
        var final_permission = getFinalPermission(user_groups, permissions, node, true);
        output_current_folder_permissions.push(final_permission);
    } catch (e) {
        logger.log(e);
        output_current_folder_permissions.push(null);
    }
}

var output = {
    files: {
        dates: output_files_dates,
        permissions: output_files_permissions,
        visibility: output_files_visibility,
        props: {
            nids: output_files_nids,
            nodeRefs: output_files_node_refs,
        }
    },
    folders: {
        permissions: output_folders_permissions,
        visibility: output_folders_visibility, 
        props: {
            folderRefs: output_folders_alf_refs,
        }
    },
    current_folder: {
        permissions: output_current_folder_permissions
    }
};

model.output = jsonUtils.toJSONString(output);
