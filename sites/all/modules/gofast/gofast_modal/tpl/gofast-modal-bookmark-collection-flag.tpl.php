<div id="bookmarkFlagModalHeader">
    <div class='alert alert-custom alert-notice alert-light-info' role='alert'>
        <div class='alert-icon'><i class='flaticon-information'></i></div>
        <div class='alert-text m-0'>
            <span><?= t("Select an existing bookmark collection to put this item.", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></span>
            <br>
            <span><?= t("Don't select anything if you want to place it at the root.", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></span>
        </div>
    </div>
    <?php if($hasChildren): ?>
        <p><?= t("All your bookmark collections :", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></p>
    <?php endif; ?>
    <div class="d-flex justify-content-center mb-10">
        <button type="button" class="btn btn-white btn-sm no-footer addBookmarkCollectionButton" onclick="Gofast.Bookmark_Collection.createBookmarkCollection('<?= $treeId ?>')">
            <i class="fa fa-plus" aria-hidden="true"></i> <?= t("New", array(), array("context" => "gofast:gofast_bookmark_collection")); ?>
        </button>
        <div id="<?= $treeId ?>_search" class="input-group">
            <div class="input-group-prepend"><span class="input-group-text"><i class="fas fa-filter icon-nm"></i></span></div>
            <input id="<?= $treeId ?>_search_input" type="text" class="form-control form-control-sm m-0 h-100" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:gofast_bookmark_collection')); ?>" aria-describedby="sizing-addon3">
        </div>
    </div>
    <span id="emptyBookmarkCollectionMessage" class="<?= $hasChildren ? "d-none" : "" ?> font-italic"><?= t("You don't have any bookmark collection. To create one, use the \"New\" button or the right-click context menu.", array(), array("context" => "gofast:gofast_bookmark_collection")) ?></span>
</div>
<div id="bookmarkFlagTreeContainer" class="bookmark_tree_container">
    <ul id="<?= $treeId ?>" class="ztree overflow-auto"></ul>
</div>
<div id="bookmarkCollectionFlagSubmit" onclick='
    let treeId = "<?= $treeId ?>";
    let tree = Gofast.Bookmark_Collection.tree[treeId];
    Gofast.Bookmark_Collection.bookmarkMultipleItems(event, <?= json_encode($itemIds); ?>, $("#"+treeId).data("selected-bcid"), tree.targetTreeId, "<?= $itemType ?>")'
    class="btn btn-success btn-sm" value="Save"><?= t("Validate") ?></div>
<div class="btn btn-secondary btn-sm" value="Cancel" onclick="Drupal.CTools.Modal.dismiss()"><?= t("Cancel") ?></div>
<script>
  $(document).ready(()=>{
    let treeId = "<?= $treeId ?>"
    Gofast.Bookmark_Collection.loadTree(treeId)
  })
</script>