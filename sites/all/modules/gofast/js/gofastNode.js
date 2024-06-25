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
  if(!$("#fullscreen-node").length){
    Gofast.addLoading();
  }
  
  let formData = new FormData();
  for (let prop in props) {
    formData.append(prop, props[prop]);
  }

  try {
    var path = Gofast.ITHit.currentPath;
    
    await fetch(url, {
      method: "POST",
      body: formData,
    });
    
    if(props["name"] == "field_description"){
      Gofast.toast(Drupal.t("The description has been successfully updated"));
    }
    // Refresh node actions (alfresco_item && article) after title update
    if(props['name'] == 'title'){
      Gofast.gofast_refresh_fast_actions_node(props['pk']);
      
      //Refresh GoFAST file browser
      // Edit name in the ztree if we are not editing a document, preventing wrong rename when closing document after rename
      if(jQuery("#file_browser_full_container").length && $("#nodeContainer[data-isfullpage=true]").length == 0 && props["type"] != "alfresco_item"){
        var oldPath = path.split("/");
        var spaceElements = []; // Contains all spaces on the path
        for (var i = 0; i < oldPath.length; i++) {
          if (oldPath[i].startsWith('_')) {
            spaceElements.push(oldPath[i].trim());
          }
        }
        var splitString = "/alfresco/webdav/Sites/";
        var current_path = splitString + spaceElements.join('/');// path to the currently space in the zTree
        //Get element in the file browser zTree
        var zElement = Gofast.ITHit.tree.getNodeByParam("path", current_path);
        if (zElement !== null) {
          //We found it in thz zTree, rename it !
          var selectedNode = Gofast.ITHit.tree.getSelectedNodes()[0];
          var new_title = "_" + props["value"];
          spaceElements.pop(); // delete the old space's title
          spaceElements.push(new_title);
          var new_path = splitString + spaceElements.join('/');
          zElement.name = new_title; // new title for the space
          zElement.path = new_path; // new path for the space
          Gofast.ITHit.tree.editName(zElement);
          Gofast.ITHit.tree.removeChildNodes(zElement);
          zElement.isParent = true;
          Gofast.ITHit.tree.refresh();
          Gofast.ITHit.tree.selectNode(selectedNode);
          Gofast.ITHit.currentPath = Gofast.ITHit.currentPath.replace(path, new_path);
        }
        
        if (location.hash == "" || location.hash == "#ogdocuments") {
          Gofast.ITHit.reload();
        }
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
  const crumbItem = document.querySelector(".breadcrumb-item > b");
  if (!crumbItem) {
    return;
  }
  let nid = "";

  let attachedNid = crumbItem.getAttribute("data-nid");
  if(attachedNid != null) {
    nid = attachedNid;
  } else if (Gofast.breadcrumb_gid){
    nid = Gofast.breadcrumb_gid;
    Gofast.breadcrumb_gid = null;
  }else{
    node = Gofast.get("node");
    if (!node) {
      console.error("No node found in Gofast.get('node')");
      return;
    }
    nid = node.id;
  }
  let nidInHref = window.location.pathname.split("/")[2];
  if (!isNaN(nidInHref) && nidInHref != nid) {
    console.error("Nid in href is different from nid in breadcrumb");
    return;
  }

  $.get("/gofast/user/cani/update/" + nid, function(canEdit){
    const title = crumbItem.innerText;
    crumbItem.innerHTML = "";
    _crumbTitleInput = GofastEditableInput(crumbItem, title, "text", {
      save: async (newTitle) => {
      let nodeType = "";
      // Get node type to know if we are editing a space or an alfresco_item
      await $.get('/essential/get_node/'+nid).done((result)=>{
        let jsonData = JSON.parse(result)
        if(jsonData){
          nodeType = jsonData.type
        }
      })
      _gofastPostSimulator({
        pk: nid,
        name: "title",
        value: newTitle,
        type: nodeType
      }).then(() => {
        $.post('/gofast_cmis/after_rename_integrity', {nid: nid, old_title: title, new_title: newTitle}).done(function(data){
          if(data != 'ok'){
            //Integrity check has failed, report to the user
            Gofast.toast(
              Drupal.t(
                "An issue has been detected after your last rename operation. If something went wrong please try again or contact your administrator. The issue has already been reported.", 
                {}, 
                {context: "gofast:gofast_cmis"}
              ), 
              "warning", 
              Drupal.t("Issue reported to the technical support", {}, {context: "gofast:gofast_cmis"})
            );
          }
        });
      });
      if (_articleTitleInput) _articleTitleInput.setData(newTitle);
      },
      isEditable: canEdit,
      showConfirmationButtons: true,
      widenInput: true,
    });
  });
};

window.initTitleInput = () => {
  const titleItem = document.querySelector(".gofast-node-title-value > div");
  if (!titleItem) {
    return;
  }
  let nid = "";
  node = Gofast.get("node");
  if (!node) {
    console.error("No node found in Gofast.get('node')");
    return;
  }
  nid = node.id;
  const titleMetadata = titleItem.innerText.trim();
  titleItem.innerHTML = "";
  _titleFieldInput = GofastEditableInput(titleItem, titleMetadata, "text", {
    save: async (newTitle) => _gofastPostSimulator({pk: nid, name: "field_title", value: newTitle}),
    placeholder: Drupal.t("Click here to change the title metadata", {}, {'context' : 'gofast'}),
    showConfirmationButtons: $("#gofast-node-title-editable-input"),
    widenInput: true,
  });

};

window.initDocumentEditableInputs = async (nid = null, title = null, canUpdate = null) => {
  // mainly duplicates of initArticleEditableInputs, to be refactored
  var node = Gofast.get("node");
  if(node == undefined){
    node = Gofast.get("node");
  }
  const endpoint = "/gofast/user/cani/update/" + node.id;

  Drupal.settings.gofast.JSCallsIndex = Drupal.settings.gofast.JSCallsIndex || {};

  let canEdit = false;
  if (canUpdate != null) {
    canEdit = canUpdate;
  } else if (Object.keys(Drupal.settings.gofast.JSCallsIndex).includes(endpoint)) {
    canEdit = Drupal.settings.gofast.JSCallsIndex[endpoint];
  } else {
    await $.get(endpoint, function(data) {
      canEdit = data;
      Drupal.settings.gofast.JSCallsIndex[endpoint] = data;
    });
  }

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
  GofastEditableInput(element, content, "ckeditor-full", {
    save: async (newContent) => {
      _gofastPostSimulator({
        pk: node.id,
        name: "body",
        value: newContent,
      });
    },
    isEditable: canEdit,
    showConfirmationButtons: true
  });
}

window.initArticleEditableInputs = async (nid = null, title = null, canUpdate = null, isHomepage = false) => {
  let node;
  if(nid == null){
    node = Gofast.get("node");
  }else{
    node = new Object();
    node.id = nid;
    node.title = title;
  }
  const endpoint = "/gofast/user/cani/update/" + node.id;

  Drupal.settings.gofast.JSCallsIndex = Drupal.settings.gofast.JSCallsIndex || {};

  let canEdit = false;
  if (canUpdate != null) {
    canEdit = canUpdate;
  } else if (Object.keys(Drupal.settings.gofast.JSCallsIndex).includes(endpoint)) {
    canEdit = Drupal.settings.gofast.JSCallsIndex[endpoint];
  } else {
    await $.get(endpoint, function(data) {
      canEdit = data;
      Drupal.settings.gofast.JSCallsIndex[endpoint] = data;
    });
  }

  if (!node || !canEdit) {
    return;
  }

  const classToFieldIndex = {
    gofastArticleDescription: "field_description",
    gofastArticleContent: "body",
  }
  if (!isHomepage) {
    classToFieldIndex["gofastArticleTitle"] = "title";
  }

  for (const className in classToFieldIndex) {
      const element = document.querySelector("." + className);
      if (!element || element.querySelector(".EditableInput__value")) continue;
      let targetNid = node.id;
      let content = element.innerHTML.trim();

      if (className == "gofastArticleTitle") content = decodeURIComponent(node.title).replace(".html", "");
      element.innerHTML = "";
      let contentType = "text";
      if (className == "gofastArticleContent") contentType = "ckeditor-full";
      if (className == "gofastArticleContent" && !content.trim().length) content = Drupal.t("No content");
      if (className == "gofastArticleDescription" && element.getAttribute("data-gid") != null) {
        targetNid = element.getAttribute("data-gid");
      }

      const articleInput = GofastEditableInput(element, content, contentType, {
        save: async (newContent) => {
          _gofastPostSimulator({
            pk: targetNid,
            name: classToFieldIndex[className],
            value: newContent,
          });
          if (className == "gofastArticleTitle" && _crumbTitleInput) _crumbTitleInput.setData(newContent);
        },
        isEditable: canEdit,
        programmaticTrigger: true,
        showConfirmationButtons: className == "gofastArticleContent" || className == "gofastArticleDescription",
        widenInput: className == "gofastArticleDescription",
        useTextarea: className == "gofastArticleDescription",
      });
      if (className == "gofastArticleTitle" && _articleTitleInput) _articleTitleInput = articleInput;
  }
};

Gofast = Gofast || {};

/** this programmatically triggers an editable input, given the editable input has the "programmaticTrigger" prop */
Gofast.triggerEditableInput = function(selector, tab = null) {
  // go to the tab where the target editable input exists
  if (tab && !window.location.hash.startsWith(tab)) {
    const tabElement = $("[href='" + tab + "']");
    tabElement.click();
    // selector is updated to ensure we target the editable input _inside_ the tab container
    selector = tab + " " + selector;
  }
  // make sure the element matching the selector exists before triggering it
  const contentInterval = setInterval(function() {
    if(!$(selector).length) {
      return;
    }
    clearInterval(contentInterval);
    $(selector).trigger('click', { programmaticTriggered: true })
  }, 100);
}
