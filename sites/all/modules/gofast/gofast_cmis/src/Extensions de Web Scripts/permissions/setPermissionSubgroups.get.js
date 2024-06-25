var renderArray = {};

if (args.nodeRef !== null) {

  //search for the folder node using lucene search
  var folderNode = search.findNode(args.nodeRef);
  //determine si c'est un groupe de premier niveau ou un sous groupe
  var grouptype = args.node_type;
  //unique_name_group correspond au nom du groupe tel qu'il est dans ldap. Dans ldap, pour garantir l'unicite des groupes, on concatene le gid drupal avec le nom du groupe
  var unique_name_group = args.unique_name;
  
  var template_folder = args.template_folder;

  if (folderNode !== null) {

    var groupname = folderNode.name;

    renderArray.name = folderNode.name;
    renderArray.title = folderNode.properties.title;
    renderArray.desc = folderNode.properties.description;
    renderArray.groupName = groupname;
    renderArray.groupType = grouptype;
    renderArray.uniqueNameGroup = unique_name_group;
    renderArray.permissions = {};

    var re = /#(\d*)/;
    var groupid = re.exec(unique_name_group);

    groupname = unique_name_group;

    // Set folder non-inherited
    folderNode.setInheritsPermissions(false);

    // Remove all the old permissions
    var permissions = folderNode.getPermissions();
    for each (var permission in permissions)
    {
      var group_array = permission.split(";");
      group = group_array[1];
      try {
        folderNode.removePermission(group_array[2], group);
      } catch (ex) {
      }
    }

    // Add the new permissions, will be blank until next LDAP synch cron
    if (grouptype === "private_space") {
      renderArray.permissions.coordinator = {"Coordinator": "GROUP_" + unique_name_group};

      folderNode.setPermission("Coordinator", "GROUP_" + unique_name_group);
    } else if (grouptype === "og_public") {
      renderArray.permissions.standard = {"Standard": "GROUP_EVERYONE"};

      folderNode.setPermission("Standard", "GROUP_EVERYONE");
    } else if (grouptype === "folders_templates_folder") {
      renderArray.permissions.coordinator = {"Coordinator": "GROUP_" + unique_name_group};

      folderNode.setPermission("Coordinator", "GROUP_" + unique_name_group);
    } else if (grouptype === "root_space") {
		renderArray.permissions.standard = {"Consumer": "GROUP_" + unique_name_group};
		
		folderNode.setPermission("Consumer", "GROUP_" + unique_name_group);
    } else if (template_folder !== null) {
        renderArray.permissions.standard = {"Consumer": "GROUP_" + unique_name_group + "_STANDARD"};
        renderArray.permissions.coordinator = {"Coordinator": "GROUP_" + unique_name_group + "_ADMIN"};
        renderArray.permissions.consumer = {"Consumer": "GROUP_" + unique_name_group};
        
        folderNode.setPermission("Consumer", "GROUP_" + unique_name_group + "_STANDARD");
        folderNode.setPermission("Coordinator", "GROUP_" + unique_name_group + "_ADMIN");
        folderNode.setPermission("Consumer", "GROUP_" + unique_name_group);
    } else {
      renderArray.permissions.standard = {"Standard": "GROUP_" + unique_name_group + "_STANDARD"};
      renderArray.permissions.coordinator = {"Coordinator": "GROUP_" + unique_name_group + "_ADMIN"};
      renderArray.permissions.consumer = {"Consumer": "GROUP_" + unique_name_group};

      folderNode.setPermission("Standard", "GROUP_" + unique_name_group + "_STANDARD");
      folderNode.setPermission("Coordinator", "GROUP_" + unique_name_group + "_ADMIN");
      folderNode.setPermission("Consumer", "GROUP_" + unique_name_group);
    }
    folderNode.save();

  } else {
    renderArray.status = "KO";
    renderArray.message = "The reference is wrong or does not exist anymore";
  }
} else {
  renderArray.status = "KO";
  renderArray.message = "The argument reference is mandatory";
}

model.myStatus = jsonUtils.toJSONString(renderArray);
