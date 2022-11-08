/**
 * This file is intended for several helpers used in generic node templates
 */

/** ABSTRACT LOGIC */
// given a {property: value, otherProperty: otherValue} object, add some inline CSS style on the element
var _handleCustomCSSStyle = (element, style) => {
  for (const property in style) {
    element.style[property] = style[property];
  }
};

var _gofastPostSimulator = async (
  props,
  url = Drupal.settings.basePath + "update_node_field"
) => {
  Gofast.addLoading();
  
  let formData = new FormData();
  for (let prop in props) {
    formData.append(prop, props[prop]);
  }

  try {
    var path = "/alfresco/webdav" + jQuery("#webdav-path").text();
    
    await fetch(url, {
      method: "POST",
      body: formData,
    });

    // Refresh node actions (alfresco_item && article) after title update
    if(props['name'] == 'title'){
      Gofast.gofast_refresh_fast_actions_node(props['pk']);
      
      //Refresh GoFAST file browser
      if(jQuery("#file_browser_full_container").length){
        //Get element in the file browser zTree
        var zElement = Gofast.ITHit.tree.getNodeByParam("path", path);

        if (zElement !== null) {
          //We found it in thz zTree, rename it !
          var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
          
          var new_path = path.split('/');
          new_path.pop();
          new_path.push('_' + props['value']);
          new_path = new_path.join('/');
          
          zElement.name = '_' + props['value'];
          zElement.path = new_path;
          Gofast.ITHit.tree.editName(zElement);
          Gofast.ITHit.tree.removeChildNodes(zElement);
          zElement.isParent = true;
          Gofast.ITHit.tree.refresh();
          Gofast.ITHit.tree.selectNode(selectedNode);
        }
        
        Gofast.ITHit.currentPath = Gofast.ITHit.currentPath.replace(path, new_path);
        Gofast.ITHit.reload();
      }
    }
    Gofast.removeLoading();
  } catch (e) {
    console.log(e.message);
    Gofast.removeLoading();
  }
};

/** CONCRETE LOGIC */
let _crumbTitleInput = null;
let _articleTitleInput = null;

window.initBreadCrumb = () => {
  if (document.querySelector(".breadcrumb-item .EditableInput__value")) {
    return;
  }
  let nid = "";
  // for now we manually empty the x-editable _but_
  // @todo it would be cleaner to slim down gofast_node_get_crumb_path() and gofast_node_get_crumbs()
  if(Gofast.breadcrumb_gid){
    nid = Gofast.breadcrumb_gid;
    Gofast.breadcrumb_gid = null;
  }else{
    node = Gofast.get("node");
    if (!node) {
      return;
    }
    nid = node.id;
  }

  $.get("/gofast/user/cani/update/" + nid, function(canEdit){
    if (document.querySelector(".breadcrumb-item .EditableInput__value")) {
      return;
    }

    const crumbItem = document.querySelector(".breadcrumb-item > b");
    if (!crumbItem) {
      return;
    }
    const title = crumbItem.innerText;
    crumbItem.innerHTML = "";
    _crumbTitleInput = GofastEditableInput(crumbItem, title, "text", {
      save: async (newTitle) => {
      _gofastPostSimulator({
        pk: nid,
        name: "title",
        value: newTitle,
      });
      if (_articleTitleInput) _articleTitleInput.setData(newTitle);
      },
      isEditable: canEdit,
      showConfirmationButtons: true,
      widenInput: true,
    });
  });
};

window.initDocumentEditableInputs = async () => {
  // mainly duplicates of initArticleEditableInputs, to be refactored
  const node = Gofast.get("node");
  const endpoint = "/gofast/user/cani/update/" + node.id;

  Drupal.settings.gofast.JSCallsIndex = Drupal.settings.gofast.JSCallsIndex || [];
  if (Drupal.settings.gofast.JSCallsIndex.includes(endpoint)) {
    return;
  }
  Drupal.settings.gofast.JSCallsIndex.push(endpoint);

  let canEdit = false;
  await $.get("/gofast/user/cani/update/" + node.id, function(data) {
    canEdit = data;
  });
  Drupal.settings.gofast.JSCallsIndex.filter(endpoint => endpoint != endpoint);

  if (!node || !canEdit) {
    return;
  }
  const element = document.querySelector(".gofastSummaryContent");
  if (!element || element.querySelector(".EditableInput__value")) {
    return;
  }
  let content = element.innerHTML;
  element.innerHTML = "";
  if (content == "") {
    $(element).hide();
  }
  GofastEditableInput(element, content, "ckeditor-classic", {
    save: async (newContent) => {
      _gofastPostSimulator({
        pk: node.id,
        name: "body",
        value: newContent,
      });
    },
    isEditable: canEdit,
  });
}

window.initArticleEditableInputs = async (nid = null, title = null, canUpdate = null) => {
  let node;
  if(nid == null){
    node = Gofast.get("node");
  }else{
    node = new Object();
    node.id = nid;
    node.title = title;
  }
  const endpoint = "/gofast/user/cani/update/" + node.id;

  Drupal.settings.gofast.JSCallsIndex = Drupal.settings.gofast.JSCallsIndex || [];
  if (Drupal.settings.gofast.JSCallsIndex.includes(endpoint)) {
    return;
  }
  Drupal.settings.gofast.JSCallsIndex.push(endpoint);

  let canEdit = false;
  if (canUpdate != null) {
    canEdit = canUpdate;
  } else {
    await $.get(endpoint, function(data) {
      canEdit = data;
    });
  }
  Drupal.settings.gofast.JSCallsIndex.filter(endpoint => endpoint != endpoint);

  if (!node || !canEdit) {
    return;
  }

  const classToFieldIndex = {
    gofastArticleTitle: "title",
    gofastArticleDescription: "field_description",
    gofastArticleContent: "body",
  }

  const isFromOgHome = window.location.hash.startsWith("#oghome");

  for (const className in classToFieldIndex) {
      const element = document.querySelector("." + className);
      if (!element || element.querySelector(".EditableInput__value")) continue;
      let content = element.innerHTML;
      if (className == "gofastArticleTitle") content = decodeURIComponent(node.title).replace(".html", "").replaceAll("+", " ");
      element.innerHTML = "";
      let contentType = "text";
      if (className == "gofastArticleContent") contentType = "ckeditor-full";
      if (className == "gofastArticleContent" && !content.trim().length) content = Drupal.t("No content. Please add a description.", {}, {context: "gofast"});

      const articleInput = GofastEditableInput(element, content, contentType, {
        save: async (newContent) => {
          _gofastPostSimulator({
            pk: node.id,
            name: classToFieldIndex[className],
            value: newContent,
          });
          if (className == "gofastArticleTitle" && _crumbTitleInput) _crumbTitleInput.setData(newContent);
        },
        isEditable: canEdit,
        programmaticTrigger: isFromOgHome ? null : true,
        showConfirmationButtons: className == "gofastArticleContent",
      });
      if (className == "gofastArticleTitle" && _articleTitleInput) _articleTitleInput = articleInput;
  }
};
