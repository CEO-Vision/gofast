(function ($, Gofast, Drupal) {

    Gofast = Gofast || {};

    /*
    * GoFAST Bookmark Collection main library
    */
    Gofast.Bookmark_Collection = {

        tree: [],

        init_load_depth: null, // Set default depth loaded at tree initialization

        expand_load_depth: 2, // Set the depth loaded on expand in the method loadTreePartFromTreeNode

        base_tree_ids: ["bookmark_content_tree", "bookmark_folder_tree"], // Tree ids that are used in the db

        loadTree: async function (treeId = "bookmark_content_tree") {
            var onlyBookmarkCollections = false;
            var itemType = "content"
            let targetTreeId = treeId
            // Configure ztree settings
            var settings = {
                data: {
                    simpleData: {
                        enable: true,
                        idKey: "id",
                        pIdKey: "pId",
                        rootPId: null,
                    },
                    render: {
                        title: function(title, treeNode){
                            return treeNode.oldname ?? treeNode.name;
                        },
                    }
                },
                edit: {
                    enable: true,
                    showRemoveBtn: false,
                    showRenameBtn: false,
                    editNameSelectAll: true,
                    drag: {
                        isMove: true,
                        isCopy: false,
                        prev: Gofast.Bookmark_Collection.isSameTree,
                        inner: Gofast.Bookmark_Collection.canInner,
                        next: Gofast.Bookmark_Collection.isSameTree,
                    },
                },
                view: {
                    nodeClasses: {add: ['d-flex']},
                    addDiyDom: Gofast.Bookmark_Collection.addRemoveButton,
                },
                callback: {
                    onRightClick: Gofast.Bookmark_Collection.onRightClick,
                    beforeRightClick: Gofast.Bookmark_Collection.beforeRightClick,
                    onDragMove: Gofast.Bookmark_Collection.onDragMove,
                    beforeDrop: Gofast.Bookmark_Collection.beforeDrop,
                    onDrop: Gofast.Bookmark_Collection.onDrop,
                    beforeRename: Gofast.Bookmark_Collection.beforeRename,
                    onDblClick: Gofast.Bookmark_Collection.onDblClick,
                    beforeExpand: Gofast.Bookmark_Collection.beforeExpand,
                    onCheck: Gofast.Bookmark_Collection.onCheck,
                    beforeClick: Gofast.Bookmark_Collection.beforeClick,
                    onClick: Gofast.Bookmark_Collection.onClick,
                    onMouseUp: Gofast.Bookmark_Collection.onMouseUp,
                }
            }

            // Make sure to have "bookmark" in the start of treeId
            switch(treeId) {
                case "bookmark_content_tree": 
                    itemType = "content";
                    targetTreeId = "bookmark_content_tree"
                    break;
                case "bookmark_flag_tree":
                    onlyBookmarkCollections = true;
                    settings.check = {
                        enable: true,
                        chkStyle: "radio",
                        radioType: "all",
                    }
                    targetTreeId = "bookmark_content_tree"
                    break;
                case "bookmark_folder_tree":
                    itemType = "folder"
                    targetTreeId = "bookmark_folder_tree";
                    break;
                case "bookmark_folder_flag_tree":
                    onlyBookmarkCollections = true;
                    settings.check = {
                        enable: true,
                        chkStyle: "radio",
                        radioType: "all",
                    }
                    targetTreeId = "bookmark_folder_tree";
                    break;
                case "bookmark_dashboard_space_tree": 
                    itemType = "space";
                    targetTreeId = "bookmark_content_tree"
                    break;
                case "bookmark_dashboard_document_tree": 
                    itemType = "document";
                    targetTreeId = "bookmark_content_tree"
                    break;
                case "bookmark_dashboard_folder_tree": 
                    itemType = "folder";
                    targetTreeId = "bookmark_folder_tree"
                    break;
            }
            // Get all bookmark collections and contents in the specified depth
            await $.post("/bookmark_collection/get", { bcid: null, isAjax: true, depth: Gofast.Bookmark_Collection.init_load_depth, onlyBookmarkCollections: onlyBookmarkCollections, treeId: targetTreeId, itemType: itemType }).done((data) => {
                var zNodes = data
                // Make the root node open by default
                zNodes["open"] = true

                // Make the first level open by default
                if(zNodes.children){
                    zNodes.children.forEach(treeNode => {
                        if(treeNode.type === "bookmark_collection"){
                            treeNode.open = true;
                        }
                    })
                }
                
                Gofast.Bookmark_Collection.tree = Gofast.Bookmark_Collection.tree ?? {}
                Gofast.Bookmark_Collection.tree[treeId] = $.fn.zTree.init($("#"+treeId), settings, zNodes)
                $(`[data-treeid=${treeId}] .loader-blog`).remove();
                Gofast.Bookmark_Collection.fuzzySearch(treeId, "#"+treeId+"_search_input", true, true)
                Gofast.Bookmark_Collection.tree[treeId]["targetTreeId"] = targetTreeId
                Gofast.Bookmark_Collection.tree[treeId]["itemType"] = itemType
                $("body").on("click", (event) => {
                    if($("#"+treeId).find(event.target).length || $(event.target).attr("id") == treeId){
                        return;
                    }
                    Gofast.Bookmark_Collection.tree[treeId].cancelSelectedNode();
                })

                // Trigger contextual menu if right click in the ztree container
                $(`[data-treeid=${treeId}].bookmark_tree_container`).on("mousedown", (event) => {
                    // Prevent showing the global contextual menu on tree node
                    if($(event.target).is("[treenode_a]") || $(`[data-treeid=${treeId}] [treenode_a]`).has($(event.target)).length){
                        return;
                    }
                    if(event.which == 3) {
                        Gofast.Bookmark_Collection.onRightClick(event, treeId, null)
                    }
                }).on("contextmenu", (event) => {
                    event.preventDefault()
                })
            })
        },
        /**
         * Keep favorite dropdown open even if the mouse is outside while dragging an item
         */
        onDragMove: function (event, treeId, treeNodes) {
            // Only open dropdown when moving items from the base trees (trees in the bookmark menu)
            if(Gofast.Bookmark_Collection.base_tree_ids.includes(treeId)){
                if(!$("#gofast_topbar_flag_bookmarks").hasClass("menu-item-hover")){
                    $("#gofast_topbar_flag_bookmarks").addClass("menu-item-hover");
                }
            }
        },
        /**
         * Prevent drag & drop from other trees
         */
        beforeDrop: function (treeId, treeNodes, targetNode, moveType){
            return Gofast.Bookmark_Collection.isSameTree(treeId, treeNodes);
        },
        /**
         * Move all selected items to the hovered bookmark collection
         */
        onDrop: function (event, treeId, treeNodes, targetNode, moveType) {
            // If the target element when drop is NOT a children of the favorite dropdown, hide it
            if(!($("#gofast_topbar_flag_bookmarks").find($(event.target)).length || $(event.target).attr("id") == "gofast_topbar_flag_bookmarks")){
                $("#gofast_topbar_flag_bookmarks").removeClass("menu-item-hover");
            }
            if(targetNode == null){
                if(moveType == null){ // If we drop on the arrow icon don't move anything
                    return;
                } else { // If we drop on the outer part move nodes to the "root" bookmark collection
                    targetNode = Gofast.Bookmark_Collection.tree[treeId].getNodeByParam("bcid", null)
                    treeNodes.forEach((item) => {
                        Gofast.Bookmark_Collection.tree[treeId].moveNode(targetNode, item, "inner")
                    })
                }
            }

            // Prevent drop inside non bookmark collection item
            if(moveType == "inner" && targetNode.type !== "bookmark_collection"){
                return;
            }
            treeNodes.forEach((treeNode) => {
                let container_id = null;
                if(moveType == "inner"){
                    container_id = targetNode.bcid
                } else {
                    let parentNode = Gofast.Bookmark_Collection.tree[treeId].getNodeByTId(targetNode.parentTId);
                    container_id = parentNode.bcid
                }
                let item_id = null;
                
                if (treeNode.type == "content") {
                    item_id = treeNode.nid
                } else if (treeNode.type == "bookmark_collection") {
                    item_id = treeNode.bcid
                } else if(treeNode.type == "folder"){
                    item_id = treeNode.reference
                }
                Gofast.Bookmark_Collection.moveBookmarkItem(item_id, treeNode.type, container_id, treeId)
            })
        },
        /**
         * Trigger onRightClick method if the return value is true
         */
        beforeRightClick: function (treeId, treeNode) {
            // Trigger onRightClick method only if the right clicked item is a treeNode (Right click on expand arrow will not work)
            if (treeNode == null) {
                return false;
            } else {
                return true;
            }
        },
        onRightClick: function (event, treeId, treeNode) {
            event.preventDefault()

            // Remove this code only when the working actions for content are showing (alfresco_item, space, ...)
            // if(treeNode != undefined && (treeNode.type == "content" || treeNode.type == "folder")){
            //     return;
            // }

            // If multiple items are selected, make the right clicked node selected only
            Gofast.Bookmark_Collection.tree[treeId].selectNode(treeNode)

            let menuParent = $("body")
            //If another menu is open, destroy it
            if (menuParent.find('#gofast-bookmarks-node-actions').is('.open') !== false) {
                menuParent.find('#gofast-bookmarks-node-actions').remove();
            }
            var menu = $('<div id="gofast-bookmarks-node-actions"><div class="dropdown-menu dropdown-menu-md py-5" aria-labelledby="dropdown-"><ul class="navi navi-hover navi-link-rounded-lg px-1"><li><div class="loader-activity-menu-active"></div></li></ul></div></div>').appendTo(menuParent);

            //Show the menu and position it
            menu.addClass('open');
            menu.css('left', event.pageX - menuParent.offset().left);
            menu.css('top', event.pageY - menuParent.offset().top);

            const buildContextualActionsMenu = function(data){
                if ($(data).find('ul').length == 0) { //Empty menu
                    menu.remove();
                    return;
                }

                $(menu).find("ul").html($(data).find('ul').html());
                Drupal.attachBehaviors();

                // Submenu is always out of the window, then reposition it
                var submenu = menu.children().children('.dropdown-submenu').children('.dropdown-menu');
                $(submenu).css('bottom', '0');

                //Check if the menu is out of the window, reposition it if needed
                var bottom = menu[0].getBoundingClientRect().top + menu[0].scrollHeight;
                if (window.innerHeight < bottom) {
                    var diff = bottom - window.innerHeight;
                    $(menu).css('top', parseInt($(menu).css("top")) - diff);
                }
                
                $("#gofast-bookmarks-node-actions .navi-link").one("click", (e) => {
                    e.preventDefault()
                    e.stopImmediatePropagation()
                    Gofast.Bookmark_Collection.removeContextualMenu()
                })
            }
            // Build different contextual actions menu based on the item type
            let targetTreeId = Gofast.Bookmark_Collection.tree[treeId].targetTreeId;
            if(treeNode == undefined){
                $.post("/bookmark_collection/contextual_action", { treeId: treeId, targetTreeId: targetTreeId }).done((data) => {
                    buildContextualActionsMenu(data)
                })
            } else if(treeNode.type == "bookmark_collection"){
                $.post("/bookmark_collection/contextual_action", { treeId: treeId, itemId: treeNode.bcid, itemType: treeNode.type, targetTreeId: targetTreeId }).done((data) => {
                    buildContextualActionsMenu(data)
                })
            } else if (treeNode.type == "content"){
                // $.post(location.origin + "/gofast/node-actions/"+treeNode.nid, { fromTree: true, fromBookmark: true }).done((data) => {
                $.post("/bookmark_collection/contextual_action", { itemId: treeNode.nid, itemType: treeNode.type, targetTreeId: targetTreeId }).done((data) => {
                    buildContextualActionsMenu(data)
                });
            } else if (treeNode.type == "folder"){
                // $.post(location.origin + "/gofast/node-actions/filebrowser", { fromTree: true, selected: [treeNode.path]}).done((data) => {
                $.post("/bookmark_collection/contextual_action", { itemId: treeNode.reference, itemType: treeNode.type, targetTreeId: targetTreeId }).done((data) => {
                    buildContextualActionsMenu(data)
                })
            }
        },
        /**
         * Process check to validate the name before renaming
         */
        beforeRename: function(treeId, treeNode, newName, isCancel){
            // Check if the treeNode is a bookmark collection
            if (treeNode.type == "bookmark_collection") {
                // If the bcid is equal to 0, then it's a new bookmark collection and we want to make a different treatment in onRename method
                if(treeNode.bcid == 0){
                    // If we cancel the naming of a new bookmark collection, remove it
                    if(isCancel || newName == ""){
                        Gofast.Bookmark_Collection.tree[treeId].removeNode(treeNode)
                    } else {
                        let parentNode = Gofast.Bookmark_Collection.tree[treeId].getNodeByTId(treeNode.parentTId)
                        let targetTreeId = Gofast.Bookmark_Collection.tree[treeId].targetTreeId
                        // Create new bookmark collection in the given parent and return bcid of the new bookmark collection
                        $.post("/bookmark_collection/add/" + parentNode.bcid, { name: newName, treeId: targetTreeId }).done((bcid) => {
                            if(bcid == "false"){
                                Gofast.toast(Drupal.t("This name is already used by another bookmark collection !", {}, { context: "gofast:gofast_bookmark_collection" }), "error")
                                // Use the setTimeout to prevent not putting the previous name
                                setTimeout(function() {
                                    Gofast.Bookmark_Collection.tree[treeId].cancelEditName()
                                }, 0);
                                Gofast.Bookmark_Collection.tree[treeId].removeNode(treeNode)
                                return false;
                            } else {
                                // Update the fake node bcid with the real bcid in the database
                                treeNode.bcid = +bcid
                                Gofast.Bookmark_Collection.tree[treeId].updateNode(treeNode)
                                
                                // Add also the node in other trees for preventing reload
                                Gofast.Bookmark_Collection.getAllTreeIds(treeId, true).forEach(otherTreeId => {
                                    var newNode = { name: newName, type: "bookmark_collection", iconSkin: "fas ztreeFa fa-star n-color bookmarkCollectionIcon ", bcid: bcid };
                                    parentNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("bcid", parentNode.bcid)
                                    Gofast.Bookmark_Collection.tree[otherTreeId].addNodes(parentNode, newNode)
                                })
                                Gofast.toast(Drupal.t("The bookmark collection has been added successfully.", {}, { context: "gofast:gofast_bookmark_collection" }), "info")
                            }
                        })
                    }
                } else {
                    // If the user submit the rename
                    if(!isCancel){
                        if(newName == ""){ // Prevent renaming a bookmark collection with an empty name
                            Gofast.toast(Drupal.t("The name can't be empty.", {}, { context: "gofast:gofast_bookmark_collection" }), "error")
                            setTimeout(function() {
                                Gofast.Bookmark_Collection.tree[treeId].cancelEditName()
                            }, 0);
                            return false;
                        } else if(treeNode.name == newName) { // There's no need to trigger the renaming mechanism if the name is the same as before.
                            setTimeout(function() {
                                Gofast.Bookmark_Collection.tree[treeId].cancelEditName()
                            }, 0);
                            return false;
                        } else {
                            let targetTreeId = Gofast.Bookmark_Collection.tree[treeId].targetTreeId
                            // If a node already exist, trigger an error and abort the renaming
                            $.post("/bookmark_collection/rename/" + treeNode.bcid, { newName: newName, treeId: targetTreeId }).done((alreadyExistingName) => {
                                if(alreadyExistingName == "true"){
                                    Gofast.toast(Drupal.t("This name is already used by another bookmark collection !", {}, { context: "gofast:gofast_bookmark_collection" }), "error")
                                    // Blur the edit input and don't change the original name value
                                    Gofast.Bookmark_Collection.tree[treeId].cancelEditName()
                                    return false;
                                } else {
                                    Gofast.toast(Drupal.t("The bookmark collection has been renamed successfully.", {}, { context: "gofast:gofast_bookmark_collection" }), "info")
                                    // Blur the edit input and set the new name to the node
                                    Gofast.Bookmark_Collection.tree[treeId].cancelEditName(newName)

                                    // Rename also the node in other trees for preventing reload
                                    Gofast.Bookmark_Collection.getAllTreeIds(treeId, true).forEach(otherTreeId => {
                                        let targetTreeNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("bcid", treeNode.bcid);
                                        targetTreeNode.name = newName;
                                        Gofast.Bookmark_Collection.tree[otherTreeId].updateNode(targetTreeNode)
                                    })
                                    return false;
                                }
                            })
                            return false;
                        }
                    }
                }
            }
            return true;
        },
        /**
         * Make the user redirect to the node when double clicking on it
         */
        onDblClick: function(event, treeId, treeNode) {
            if(treeNode == null){
                return;
            }

            if(treeNode.type == "content"){
                if(Gofast._settings.isEssential){
                    Gofast.Essential.processEssentialAjax("/node/"+treeNode.nid)
                } else {
                    Gofast.processAjax("/node/"+treeNode.nid)
                }
            } else if(treeNode.type == "folder"){
                $.get("/ajax/getnidfromhref", { href: Gofast.ITHit.getSpacePath(treeNode.path) }).done((space_nid) => {
                    if(Gofast._settings.isEssential) {
                        Gofast.Essential.processEssentialAjax("/node/"+space_nid+"?path="+treeNode.path)
                    } else {
                        Gofast.processAjax("/node/"+space_nid+"?path="+treeNode.path)
                    }
                })
            }
        },
        /**
         * Load bookmark collection children items when expanding at specific depth
         */
        beforeExpand: function(treeId, treeNode) {
            // If init_load_depth is null, this means that we load all the tree at the init step
            if(Gofast.Bookmark_Collection.init_load_depth == null){
                return
            }
            let treePath = treeNode.getPath() // treePath include the current treeNode
            // Load children if the expanded node is at the last depth loaded from the initialization
            if(treePath.length - 1 == Gofast.Bookmark_Collection.init_load_depth && (treeNode.children == null || treeNode.children.length == 0)) {
                Gofast.Bookmark_Collection.loadTreePartFromTreeNode(treeId, treeNode)
            } else {
                let loadedPath = (treePath.length - 1) - Gofast.Bookmark_Collection.init_load_depth
                if((loadedPath % Gofast.Bookmark_Collection.expand_load_depth) == 0){
                    Gofast.Bookmark_Collection.loadTreePartFromTreeNode(treeId, treeNode)
                }
            }
        },
        /**
         * Store the selected treeNode bcid, in order to bookmark the item to the selected bookmark collection
         */
        onCheck: function(event, treeId, treeNode){
            if(treeNode.checked){
                $("#"+treeId).data("selected-bcid", treeNode.bcid)
            } else { // If no bookmark collection is selected, put the item to the root
                $("#"+treeId).data("selected-bcid", null)
            }
        },
        beforeClick: function(treeId, treeNode, clickFlag){
            // Store selected items for shift+click multiple select action
            if (!clickFlag || Gofast.Bookmark_Collection.tree[treeId].getSelectedNodes().length === 0) {
                Gofast.Bookmark_Collection.tree[treeId].selectedItems = null;
            } else {
                Gofast.Bookmark_Collection.tree[treeId].selectedItems = Gofast.Bookmark_Collection.tree[treeId].getSelectedNodes();
            }
            return true;
        },
        /**
         * Handle click event to manage radio button tree and multiple select with shift key
        */
        onClick: function(event, treeId, treeNode, clickFlag) {
            // If the shift key is pressed and an element is already selected
            if(event.shiftKey && Gofast.Bookmark_Collection.tree[treeId].selectedItems){
                const lastSelectedItem = Gofast.Bookmark_Collection.tree[treeId].selectedItems.last();
                // If the selected item is in the same location as the last selected item
                if(treeNode.parentTId == lastSelectedItem.parentTId){
                    var allItems = Gofast.Bookmark_Collection.tree[treeId].getNodesByParam("parentTId", treeNode.parentTId);
                    const lastSelectedItemIndex = allItems.indexOf(lastSelectedItem)
                    const selectedItemIndex = allItems.indexOf(treeNode);
                    // Get all items between the shift clicked item and the previous selected item
                    const startIndex = Math.min(selectedItemIndex, lastSelectedItemIndex);
                    const endIndex = Math.max(selectedItemIndex, lastSelectedItemIndex);
                    var itemsToSelect = allItems.slice(startIndex, endIndex);
                    // Add all previous selected items to select them again
                    itemsToSelect = itemsToSelect.concat(Gofast.Bookmark_Collection.tree[treeId].selectedItems)
                    itemsToSelect.forEach((item) => {
                        // If an item from the previous selected items is not in the same location, don't select it
                        if(item.parentTId == treeNode.parentTId){
                            Gofast.Bookmark_Collection.tree[treeId].selectNode(item, true, true);
                        }
                    })
                }
            }
            // Toggle the check state of treeNode in tree with radio buttons 
            if(treeNode == null || Gofast.Bookmark_Collection.tree[treeId].setting.check.enable == false){
                return
            }
            // Toggle check on the clicked node and allow triger onCheck callback
            Gofast.Bookmark_Collection.tree[treeId].checkNode(treeNode, null, null, true)
        },
        onMouseUp: function(event, treeId, treeNode) {
            // Action when using middle click
            if(event.which == 2){
                if(treeNode != null){
                    if(treeNode.type == "content"){
                        window.open(location.origin + "/node/" + treeNode.nid);
                    }
                    if(treeNode.type == "folder"){
                        $.get("/ajax/getnidfromhref", { href: Gofast.ITHit.getSpacePath(treeNode.path) }).done((space_nid) => {
                            window.open(location.origin + "/node/" + space_nid + "?path=" + treeNode.path)
                        })
                    }
                }
            }
        },
        /**
         * Prevents treeNodes whose dropInner attribute is set to false from being highlighted when hovered over in a drag-and-drop operation
         */
        canInner: function(treeId, treeNodes, targetNode) {
            if(targetNode != null && targetNode.dropInner == false){
                return false;
            }
            
            return Gofast.Bookmark_Collection.isSameTree(treeId, treeNodes);
        },
        isSameTree: function(treeId, treeNodes, targetNode) {
            // If at least one item as not the same tree id than this tree, don't drop
            const treeNodeTreeId = treeNodes[0].tId.replace(/(_\d*)$/, "")
            if(treeNodeTreeId != treeId) {
                return false;
            }
            return true;
        },
        /**
         * Add a remove button next to content / folder item
         */
        addRemoveButton: function(treeId, treeNode) {
            if(treeNode.type === "bookmark_collection") {
                return;
            }
            var liObj = $(`#${treeId} #${treeNode.tId}`);
            if($(`#removeBtn_${treeNode.tId}`).length) {
                return;
            }
            var removeBtn = $(`<span role="button" class="fa fa-trash float-right" id="removeBtn_${treeNode.tId}"></span>`);
            removeBtn.on("click", (e) => {
                if(treeNode.type == "content"){
                    Gofast.Bookmark_Collection.bookmarkItem(e, treeNode.nid, null, treeId, treeNode.type);
                } else if(treeNode.type == "folder") {
                    Gofast.Bookmark_Collection.bookmarkItem(e, treeNode.reference, null, treeId, treeNode.type);
                }
            })
            liObj.append(removeBtn)
        },
        /**
         * Load part of bookmark collection children to prevent performance issue
         * It's using the expand_load_depth constant to be able to load more or less children depth
         */
        loadTreePartFromTreeNode: function(treeId, treeNode){
            if(treeNode.children == null || treeNode.children.length == 0){
                let targetTreeId = Gofast.Bookmark_Collection.tree[treeId].targetTreeId
                $.post("/bookmark_collection/get", { bcid: treeNode.bcid, isAjax: true, depth: Gofast.Bookmark_Collection.expand_load_depth, treeId: targetTreeId }).done((data) => {
                    if(data["children"] == undefined){
                        treeNode.isParent = false
                        Gofast.Bookmark_Collection.tree[treeId].updateNode(treeNode)
                    } else {
                        var zNodes = data["children"]
                        Gofast.Bookmark_Collection.tree[treeId].addNodes(treeNode, zNodes)
                    }
                })
            }
        },
        /**
         *  Create a new, empty bookmark collection at the root with a name input field
         */
        createBookmarkCollection: function (treeId, bcid = null) {
            if(bcid == ""){
                bcid = null;
            }
            // Create a new fake node
            var newNode = { name: "", type: "bookmark_collection", iconSkin: "fas ztreeFa fa-star n-color bookmarkCollectionIcon ", bcid: 0 };
            var parentNode = Gofast.Bookmark_Collection.tree[treeId].getNodeByParam("bcid", bcid)
            var newTreeNode = Gofast.Bookmark_Collection.tree[treeId].addNodes(parentNode, newNode)
            // Trigger node editing to make user choose the bookmark collection name
            setTimeout(()=>{
                Gofast.Bookmark_Collection.tree[treeId].editName(newTreeNode[0])
            }, 0)
        },
        /**
         * Remove bookmark folder and all it's children
         */
        removeBookmarkCollection: function (treeId, bcid) {
            var targetTreeId = Gofast.Bookmark_Collection.tree[treeId].targetTreeId
            $.post("/bookmark_collection/remove/" + bcid, { isAjax: true, treeId: targetTreeId }).done((isDeleted) => {
                if (isDeleted) {
                    Gofast.toast(Drupal.t("Bookmark collection successfully deleted !", {}, { context: "gofast:gofast_bookmark_collection" }), "info")
                    
                    // Remove the bookmark collection in all related tree (using same targetTreeId)
                    Gofast.Bookmark_Collection.getAllTreeIds(treeId).forEach(relatedTreeId => {
                        var treeNode = Gofast.Bookmark_Collection.tree[relatedTreeId].getNodeByParam("bcid", bcid)
                        Gofast.Bookmark_Collection.tree[relatedTreeId].removeNode(treeNode)
                    })
                } else {
                    Gofast.toast(Drupal.t("You can't delete this bookmark collection.", {}, { context: "gofast:gofast_bookmark_collection" }), "error")
                }
            });
            Drupal.CTools.Modal.dismiss()
        },
        /**
         * Trigger the bookmark collection name edition field
         */
        renameBookmarkCollection: function(treeId, bcid) {
            var treeNode = Gofast.Bookmark_Collection.tree[treeId].getNodeByParam("bcid", bcid)
            Gofast.Bookmark_Collection.tree[treeId].selectNode(treeNode)
            setTimeout(()=>{
                Gofast.Bookmark_Collection.tree[treeId].editName(treeNode)
            }, 0)
        },
        /**
         * Remove the contextual menu
         */
        removeContextualMenu: function(){
            // Remove contextual menu
            if ($('#gofast-bookmarks-node-actions').is('.open') !== false) {
                $('#gofast-bookmarks-node-actions').remove();
            }
        },
        /**
         * Add / Remove from bookmark the given content with the itemId (nid for content, reference for folder)
         */
        bookmarkItem: function (e, itemId, bcid = null, treeId, itemType) {
            e.preventDefault();
            $('#gofast-bookmarks-node-actions').remove();
            let bookmarkItem = undefined
            // Check if the tree has already been loaded before making action on it
            if(Gofast.Bookmark_Collection.tree[treeId] != undefined){
                // Remove the bookmark item in all related tree (using same targetTreeId)
                Gofast.Bookmark_Collection.getAllTreeIds(treeId).forEach(relatedTreeId => {
                    if(itemType == "content"){
                        bookmarkItem = Gofast.Bookmark_Collection.tree[relatedTreeId].getNodeByParam("nid", itemId);
                    } else if(itemType == "folder"){
                        bookmarkItem = Gofast.Bookmark_Collection.tree[relatedTreeId].getNodeByParam("reference", itemId);
                    }
                    // If the item is already bookmarked, remove it from the tree
                    if(bookmarkItem != undefined){
                        Gofast.Bookmark_Collection.tree[relatedTreeId].removeNode(bookmarkItem);
                    }
                })
            }
            if(itemType == "content"){
                $.post("/bookmark_collection/flag_content/" + itemId, { isAjax: true }).done((action) => {
                    // Refresh the tree if a new content is bookmarked
                    if(action == "flag"){
                        Gofast.Bookmark_Collection.moveBookmarkItem(itemId, itemType, bcid, treeId)
                        Gofast.toast(Drupal.t("Content(s) added to the bookmarks", {}, { context: "gofast:gofast_bookmark_collection" }), "success");
                    } else {
                        Gofast.toast(Drupal.t("Content(s) removed from bookmarks", {}, { context: "gofast:gofast_bookmark_collection" }), "success");
                    }
                });
            } else if (itemType == "folder"){
                $.post(location.origin + "/ajax_file_browser/bookmark_folder", { folder_reference: itemId }).done((action)=> {
                    if(action == "flag"){
                        Gofast.Bookmark_Collection.moveBookmarkItem(itemId, itemType, bcid, treeId)
                        Gofast.toast(Drupal.t("Folder(s) added to the bookmarks", {}, { context: "gofast:gofast_bookmark_collection" }), "success");
                    } else {
                        Gofast.toast(Drupal.t("Folder(s) removed from bookmarks", {}, { context: "gofast:gofast_bookmark_collection" }), "success");
                    }
                    Gofast.removeLoading()
                })
            }
            Drupal.CTools.Modal.dismiss()
        },
        /**
         * Bookmark a list of item, and add them to a bookmark collection if specified
         * @param {*} e JavaScript event object
         * @param {*} itemIds Ids of the items (nid, alfresco reference for folder)
         * @param {*} bcid Id of the destination bookmark collection
         * @param {*} treeId tree id
         * @param {*} itemType Type of the items (folder, space, document, bookmark collection, ...)
         */
        bookmarkMultipleItems: function(e, itemIds, bcid = null, treeId, itemType){
            itemIds.forEach((itemId) => {
                Gofast.Bookmark_Collection.bookmarkItem(e, itemId, bcid, treeId, itemType);
            })
            Drupal.CTools.Modal.dismiss()
        },
        /**
         * Change the location of an item
         * @param {*} itemId Id of the item (nid, alfresco reference for folder)
         * @param {*} type Type of the item (folder, space, document, bookmark collection, ...)
         * @param {*} containerId id of the destination bookmark collection
         * @param {*} treeId tree id 
         */
        moveBookmarkItem: async function(itemId, type, containerId, treeId = null){
            //Prevent append bookmark collection to itself
            if(type == "bookmark_collection" && itemId == containerId){
                return;
            }
            // Move the item in the db
            $.post("/bookmark_collection/append", { 
                item_id: itemId, item_type: type, container_id: containerId, treeId: treeId 
            }).done((response) => {
                // Once the node has been moved in the db, change the state without reloading the trees
                Gofast.Bookmark_Collection.getAllTreeIds(treeId).forEach(otherTreeId => {
                    let targetNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("bcid", containerId);
                    let movedNode = null;
                    if(type == "content"){
                        movedNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("nid", itemId);
                    } else if(type == "folder"){
                        movedNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("reference", itemId);
                    } else if(type == "bookmark_collection"){
                        movedNode = Gofast.Bookmark_Collection.tree[otherTreeId].getNodeByParam("bcid", itemId);
                    }
                    // If the moved node does not exist in the tree, create it at the right place
                    if(movedNode == null && response["treeNode"]){
                        if(response.treeNode.type == Gofast.Bookmark_Collection.tree[otherTreeId].itemType
                            || response.treeNodeType == Gofast.Bookmark_Collection.tree[otherTreeId].itemType){
                            Gofast.Bookmark_Collection.tree[otherTreeId].addNodes(targetNode, response["treeNode"])
                        }
                    // If the moved node exist in the tree, just move it to the right location
                    } else {
                        Gofast.Bookmark_Collection.tree[otherTreeId].moveNode(targetNode, movedNode, "inner", true);
                    }
                })
            })
        },
        /**
         * Retrieve all tree id, or tree id of tree with same treeTargetId
         * This is mainly used for updating other tree without refreshing them
         * @param {*} updatedTreeId Set to null if all tree id wanted or give a treeId to get all related tree
         * @param {*} exlude If set to true will not return the given treeId
         * @returns Return an array of treeIds
         */
        getAllTreeIds: function(updatedTreeId = null, exlude = false){
            
            let targetTreeId = null;
            if(updatedTreeId != null){
                // If we are updating one of the base tree but it is not initialized yet, prevent error because tree object is null
                if(Gofast.Bookmark_Collection.tree[updatedTreeId]){
                    targetTreeId = Gofast.Bookmark_Collection.tree[updatedTreeId].targetTreeId
                } else if(Gofast.Bookmark_Collection.base_tree_ids.includes(updatedTreeId)) {
                    targetTreeId = updatedTreeId
                }
            }
            // Make an array of all treeIds that also use the same targetTreeId
            const allTreeIds = Object.keys(Gofast.Bookmark_Collection.tree).filter(treeId => {
                // Also return the given treeId if exclude is set to true
                if(exlude && (treeId == updatedTreeId)){
                    return false;
                }
                if(targetTreeId == null || Gofast.Bookmark_Collection.tree[treeId].targetTreeId == targetTreeId){
                    return true;
                }
                return false;
            })
            return allTreeIds
        },
        /**
         * Instanciate a filter input
         * This code comes from the zTree demo page (https://www.treejs.cn/v3/demo.php#_516)
         */
        fuzzySearch: function(zTreeId, searchField, isHighLight, isExpand){
            var zTreeObj = Gofast.Bookmark_Collection.tree[zTreeId];//get the ztree object by ztree id

            var nameKey = zTreeObj.setting.data.key.name; //get the key of the node name
            isHighLight = isHighLight===false?false:true;//default true, only use false to disable highlight
            isExpand = isExpand?true:false; // not to expand in default
            zTreeObj.setting.view.nameIsHTML = isHighLight; //allow use html in node name for highlight use
            
            var metaChar = '[\\[\\]\\\\\^\\$\\.\\|\\?\\*\\+\\(\\)]'; //js meta characters
            var rexMeta = new RegExp(metaChar, 'gi');//regular expression to match meta characters
            
            // keywords filter function 
            function ztreeFilter(zTreeObj,_keywords,callBackFunc) {
                if(!_keywords){
                    _keywords =''; //default blank for _keywords 
                }
                
                // function to find the matching node
                function filterFunc(node) {
                    if(node && node.oldname && node.oldname.length>0){
                        node[nameKey] = node.oldname; //recover oldname of the node if exist
                    }
                    zTreeObj.updateNode(node); //update node to for modifications take effect
                    if (_keywords.length == 0) {
                        //return true to show all nodes if the keyword is blank
                        zTreeObj.showNode(node);
                        zTreeObj.expandNode(node,isExpand);
                        return true;
                    }
                    //transform node name and keywords to lowercase
                    if (node[nameKey] && node[nameKey].toLowerCase().indexOf(_keywords.toLowerCase())!=-1) {
                        if(isHighLight){ //highlight process
                            //a new variable 'newKeywords' created to store the keywords information 
                            //keep the parameter '_keywords' as initial and it will be used in next node
                            //process the meta characters in _keywords thus the RegExp can be correctly used in str.replace
                            var newKeywords = _keywords.replace(rexMeta,function(matchStr){
                                //add escape character before meta characters
                                return '\\' + matchStr;
                            });
                            node.oldname = node[nameKey]; //store the old name  
                            var rexGlobal = new RegExp(newKeywords, 'gi');//'g' for global,'i' for ignore case
                            //use replace(RegExp,replacement) since replace(/substr/g,replacement) cannot be used here
                            node[nameKey] = node.oldname.replace(rexGlobal, function(originalText){
                                //highlight the matching words in node name
                                var highLightText =
                                    '<span style="color: whitesmoke;background-color: darkred;">'
                                    + originalText
                                    +'</span>';
                                return 	highLightText;					
                            });
                            zTreeObj.updateNode(node); //update node for modifications take effect
                            // Fix wrong title attribute causing root node to show if searched
                            $(`#${node.tId}>a`).attr("title", node.oldname)
                        }
                        zTreeObj.showNode(node);//show node with matching keywords
                        return true; //return true and show this node
                    }
                    
                    zTreeObj.hideNode(node); // hide node that not matched
                    return false; //return false for node not matched
                }
                
                var nodesShow = zTreeObj.getNodesByFilter(filterFunc); //get all nodes that would be shown
                processShowNodes(nodesShow, _keywords);//nodes should be reprocessed to show correctly
            }
            
            /**
             * reprocess of nodes before showing
             */
            function processShowNodes(nodesShow,_keywords){
                if(nodesShow && nodesShow.length>0){
                    //process the ancient nodes if _keywords is not blank
                    if(_keywords.length>0){ 
                        $.each(nodesShow, function(n,obj){
                            var pathOfOne = obj.getPath();//get all the ancient nodes including current node
                            if(pathOfOne && pathOfOne.length>0){ 
                                //i < pathOfOne.length-1 process every node in path except self
                                for(var i=0;i<pathOfOne.length-1;i++){
                                    zTreeObj.showNode(pathOfOne[i]); //show node 
                                    zTreeObj.expandNode(pathOfOne[i],true); //expand node
                                }
                            }
                        });	
                    }else{ //show all nodes when _keywords is blank and expand the root nodes
                        var rootNodes = zTreeObj.getNodesByParam('level','0');//get all root nodes
                        $.each(rootNodes,function(n,obj){
                            zTreeObj.expandNode(obj,true); //expand all root nodes
                        });
                    }
                }
            }
            
            //listen to change in input element
            $(searchField).bind('input propertychange', function() {
                var _keywords = $(this).val();
                searchNodeLazy(_keywords); //call lazy load
            });
        
            var timeoutId = null;
          var lastKeyword = '';
            // excute lazy load once after input change, the last pending task will be cancled  
            function searchNodeLazy(_keywords) {
                if (timeoutId) { 
                    //clear pending task
                    clearTimeout(timeoutId);
                }
                timeoutId = setTimeout(function() {
              if (lastKeyword === _keywords) {
                return;
              }
                    ztreeFilter(zTreeObj,_keywords); //lazy load ztreeFilter function 
                    // $(searchField).focus();//focus input field again after filtering
              lastKeyword = _keywords;
                }, 500);
            }
        }
    }

})(jQuery, Gofast, Drupal);