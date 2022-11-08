<ul class="navi navi-hover navi-link-rounded" id="gofastFavoritesFolder">
    <?php foreach($folders as $folder) : ?>
    <li class="d-flex navi-item" id="">
        <a class="navi-link  min-w-100 mr-n7" href="<?php echo $folder["unthemed_link"]; ?>">
            <span class="navi-icon">
                <i class="fas <?php echo $folder['icon']; ?>" title="<?php echo $folder['folder_name']; ?>"></i>
            </span>
            <span class="navi-text text-truncate"><?php echo $folder['folder_name']; ?></span>
        </a>
        <span class="navi-icon align-self-center mx-3 menu-topbar-favorites-folders-delete">
            <?php echo $folder['delete']; ?>
        </span>
    </li>
    <?php endforeach; ?>
</ul>

<nav class="text-center mt-4">
    <ul class="pagination pagination-sm justify-content-center" id="gofast-favorites-folders-pager"></ul>
</nav>

<script type="text/javascript">
    jQuery(document).ready(function() {
        jQuery('#gofastFavoritesFolder').pager({pagerSelector : '#gofast-favorites-folders-pager', perPage: 10, numPageToDisplay : 5, isFlex : true});
    })
</script>
