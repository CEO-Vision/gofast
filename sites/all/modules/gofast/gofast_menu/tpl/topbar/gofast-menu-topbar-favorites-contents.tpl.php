<?php $favoritesContentsId = $inMainContent ? "gofastFavoritesContentsInMainContent" : "gofastFavoritesContents"; ?>
<ul class="navi navi-hover navi-link-rounded" id="<?= $favoritesContentsId ?>">
    <?php if (empty($contents)) : ?>
        <h5><?= t("No favorites contents have been found", array(), array("context" => "gofast:gofast_menu")) ?></h5>
    <?php endif; ?>
    <?php foreach($contents as $node) : ?>
        <li class="d-flex navi-item" id="">
            <a class="navi-link min-w-100 mr-n7" title="<?php echo $node->title; ?>" href="/node/<?php echo $node->nid; ?>">
                <span class="navi-icon">
                   <?php echo theme("gofast_node_icon_format", array('node' => node_load($node->nid)));  ?>
                </span>
                <span class="navi-text text-truncate"><?php echo $node->title; ?></span>
            </a>
            <span class="navi-icon align-self-center mx-3 menu-topbar-favorites-delete">
                <?php echo $node->delete; ?>
            </span>
        </li>
    <?php endforeach; ?>
</ul>

<nav class="text-center mt-4">
    <ul class="pagination pagination-sm justify-content-center" id="gofast-favorites-contents-pager"></ul>
</nav>

<script type="text/javascript">
    jQuery(document).ready(function() {
        jQuery('#<?= $favoritesContentsId ?>').pager({pagerSelector : '#gofast-favorites-contents-pager', perPage: 10, numPageToDisplay : 5, isFlex : true});
    })
</script>
