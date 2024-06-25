<div class='alert alert-custom alert-notice alert-light-warning' role='alert'>
    <div class='alert-icon'><i class='flaticon-warning'></i></div>
    <div class='alert-text m-0'>
        <span><?= t("You are going to remove all selected items from the bookmarks.", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></span>
    </div>
</div>
<div id="bookmarkCollectionUnflagSubmit" onclick='
    let treeId = "<?= $treeId ?>";
    if(Gofast.Bookmark_Collection.tree[treeId] == undefined){
        Gofast.addLoading()
        Gofast.Bookmark_Collection.loadTree(treeId).then(() => {
            let tree = Gofast.Bookmark_Collection.tree[treeId];
            Gofast.Bookmark_Collection.bookmarkMultipleItems(event, <?= json_encode($itemIds); ?>, $("#"+treeId).data("selected-bcid"), tree.targetTreeId, "<?= $itemType ?>")
            Gofast.removeLoading()
        })
    } else {
        let tree = Gofast.Bookmark_Collection.tree[treeId];
        Gofast.Bookmark_Collection.bookmarkMultipleItems(event, <?= json_encode($itemIds); ?>, $("#"+treeId).data("selected-bcid"), tree.targetTreeId, "<?= $itemType ?>")
    }'
    class="btn btn-success btn-sm" value="Save"><?= t("Save") ?></div>
<div class="btn btn-secondary btn-sm" value="Cancel" onclick="Drupal.CTools.Modal.dismiss()"><?= t("Cancel") ?></div>
