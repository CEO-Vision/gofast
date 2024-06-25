<div class="d-flex mb-5">
    <button type="button" class="btn btn-white btn-sm addBookmarkCollectionButton" onclick="Gofast.Bookmark_Collection.createBookmarkCollection('bookmark_dashboard_space_tree')">
        <i class="fa fa-plus" aria-hidden="true"></i> <?= t("New", array(), array("context" => "gofast:gofast_bookmark_collection")); ?>
    </button>
    <div id="bookmark_dashboard_space_tree_search" class="input-group">
        <div class="input-group-prepend"><span class="input-group-text"><i class="fas fa-filter icon-nm"></i></span></div>
        <input id="bookmark_dashboard_space_tree_search_input" type="text" class="form-control form-control-sm m-0 h-100" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:gofast_menu')); ?>" aria-describedby="sizing-addon3">
    </div>
</div>
<div id="bookmarkDashboardSpaceTreeContainer" class="bookmark_tree_container h-100 processed" data-treeid="bookmark_dashboard_space_tree">
    <?= theme("gofast_bookmark_collection_tree", array("treeId" => "bookmark_dashboard_space_tree")); ?>
</div>