<div class="block-bookmarks" id="gofast_topbar_flag_bookmarks_block">    
    <ul class="nav nav-tabs nav-fill text-center gofastBookmarksTabs" role="tablist">
        <li class="nav-item" id="contentFavoritesTab" onclick="Gofast.Display_FavoritesFolders(event);">
            <a class="nav-link active" id="gofastFavoriteContentTab" data-toggle="tab" href="#gofastFavoriteContentTabContent" role="tab" aria-controls="gofastFavoriteContentTabContent" aria-selected="true">
                <div><?php echo t("Favorites content", array(), array("gofast")); ?></div>
            </a>
        </li>
        <li class="nav-item" id="foldersFavoritesTab" onclick="Gofast.Display_FavoritesFolders(event);">
            <a class="nav-link" id="gofastFavoriteFolderTab" data-toggle="tab" href="#gofastFavoriteFolderTabContent" role="tab" aria-controls="gofastFavoriteFolderTabContent" aria-selected="false">
                <div><?php echo t("Favorites folders", array(), array("gofast")); ?></div>
            </a>
        </li>
    </ul>
    <div class="tab-content p-2">
        <div class="tab-pane fade show active" id="gofastFavoriteContentTabContent" role="tabpanel" aria-labelledby="gofastFavoriteContentTab">
            <div class="gofast-bookmarks-block-inner"></div>
        </div>
        <div class="tab-pane fade" id="gofastFavoriteFolderTabContent" role="tabpanel" aria-labelledby="gofastFavoriteFolderTab">
            <div class="gofast-bookmarks-block-inner"></div>
        </div>
    </div>
</div>