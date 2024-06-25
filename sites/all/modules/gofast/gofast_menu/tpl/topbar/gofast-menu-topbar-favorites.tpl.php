<div class="block-bookmarks d-flex flex-column" id="gofast_topbar_flag_bookmarks_block">    
    <ul class="nav nav-tabs nav-fill text-center gofastBookmarksTabs" role="tablist">
        <li class="nav-item" id="contentFavoritesTab">
            <a class="nav-link active" id="gofastFavoriteContentTab" data-toggle="tab" href="#gofastFavoriteContentTabContent" role="tab" aria-controls="gofastFavoriteContentTabContent" aria-selected="true">
                <div><?php echo t("Favorites content", array(), array("gofast")); ?></div>
            </a>
        </li>
        <li class="nav-item" id="foldersFavoritesTab">
            <a class="nav-link" id="gofastFavoriteFolderTab" data-toggle="tab" href="#gofastFavoriteFolderTabContent" role="tab" aria-controls="gofastFavoriteFolderTabContent" aria-selected="false">
                <div><?php echo t("Favorites folders", array(), array("gofast")); ?></div>
            </a>
        </li>
    </ul>
    <div class="tab-content p-2 flex-grow-1">
        <div class="tab-pane fade show active" id="gofastFavoriteContentTabContent" role="tabpanel" aria-labelledby="gofastFavoriteContentTab">
            <div class="d-flex justify-content-center mb-10">
                <button type="button" class="btn btn-white btn-sm addBookmarkCollectionButton" onclick="Gofast.Bookmark_Collection.createBookmarkCollection('bookmark_content_tree')">
                    <i class="fa fa-plus" aria-hidden="true"></i> <?= t("New", array(), array("context" => "gofast:gofast_bookmark_collection")); ?>
                </button>
                <div id="bookmark_content_tree_search" class="input-group">
                    <div class="input-group-prepend"><span class="input-group-text"><i class="fas fa-filter icon-nm"></i></span></div>
                    <input id="bookmark_content_tree_search_input" type="text" class="form-control form-control-sm m-0 h-100" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:gofast_menu')); ?>" aria-describedby="sizing-addon3">
                </div>
            </div>
            <div id="bookmarkContentTreeContainer" class="bookmark_tree_container" data-treeid="bookmark_content_tree">
                <div class="loader-blog"></div>
            </div>
        </div>
        <div class="tab-pane fade" id="gofastFavoriteFolderTabContent" role="tabpanel" aria-labelledby="gofastFavoriteFolderTab">
            <div class="d-flex justify-content-center mb-10">
                <button type="button" class="btn btn-white btn-sm addBookmarkCollectionButton" onclick="Gofast.Bookmark_Collection.createBookmarkCollection('bookmark_folder_tree')">
                    <i class="fa fa-plus" aria-hidden="true"></i> <?= t("New", array(), array("context" => "gofast:gofast_bookmark_collection")); ?>
                </button>
                <div id="bookmark_folder_tree_search" class="input-group">
                    <div class="input-group-prepend"><span class="input-group-text"><i class="fas fa-filter icon-nm"></i></span></div>
                    <input id="bookmark_folder_tree_search_input" type="text" class="form-control form-control-sm m-0 h-100" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:gofast_menu')); ?>" aria-describedby="sizing-addon3">
                </div>
            </div>
            <div id="bookmarkFolderTreeContainer" class="bookmark_tree_container" data-treeid="bookmark_folder_tree"></div>
        </div>
    </div>
</div>