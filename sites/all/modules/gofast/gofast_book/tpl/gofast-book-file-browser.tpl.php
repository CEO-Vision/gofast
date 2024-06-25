<!-- START gofast-book-file-browser.tpl.php -->
<div class="book-explorer-wrapper <?= isset($widget) ? "book-explorer-widget" : "book-explorer-main" ?> d-flex flex-column w-100 max-h-100">
    <div id="book_explorer_header">
        <div id="book_explorer_toolbar_search" class="input input-group-sm">
            <div class="input-group">
                <input id="book_explorer_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
                <div class="input-group-append dropdown no-arrow" id="file_browser_mobile_toolbar_refresh_group">
                    <button title="<?php echo t('Refresh'); ?>" id="file_browser_books_mobile_tooolbar_refresh" type="button" class="btn input-group-text no-footer" <?= $widget ? "data-widget" : "" ?> <?= $has_links ? "data-has-links" : "" ?>><i class="fa fa-refresh" aria-hidden="true"></i></button>
                </div>
                <?php if (!isset($widget) || $has_links) : ?>
                <a href="/node/add/article" title="<?= t("Wikis") ?>" type="button" class="btn btn-icon btn-light-primary ml-2"><i class="fas fa-plus"></i></a>
                <?php endif; ?>
            </div>
        </div>
    </div>
    <div id="book_explorer_body" class="book-explorer-body panel-body">

    <div id="empty-home-page-wiki" class="d-none">
        <div class="w-100 book-explorer-element-visible book-explorer-element" data-placement="top" data-toggle="tooltip" data-trigger="hover" data-original-title="<?= t("This space home page doesn't have any wiki article.", array(), array("context:gofast_book")); ?>">
            <div class="book-explorer-element-seechild"></div>
            <i class="fas fa-book book-explorer-element-icon"></i>
            <div class="book-explorer-element-name">
                <a href="" class="wiki-tree-widget-item-name item-name"></a>
            </div>
        </div>
        <hr>
    </div>
        <?= empty($books) ? theme("gofast_book_no_book") : $books ?>
    </div>  
</div>
<!-- END gofast-book-file-browser.tpl.php -->
<script>
    jQuery(document).ready(function() {
        // uncollapse on link click
        jQuery(".book-explorer-element-name:not(.processed)").on("click", function(e) {
            $(this).addClass("processed");
            const arrow = jQuery(e.currentTarget).closest('tr').find(".book-explorer-element-open");
            if (arrow.hasClass("ki-bold-arrow-next")) {
                arrow.click();
            }
        });
        // uncollapse on icon click
        jQuery(".book-explorer-element-open:not(.wiki-processed)").addClass("wiki-processed").on("click", Gofast.book.treeWidgetItemCollapseCallback);
        if(jQuery("#wiki").hasClass("active")) {
            jQuery(".explorer-main-container .nav.nav-tabs a.active:not('#explorer-wiki')").removeClass('active');
        }
        jQuery("[id='file_browser_books_mobile_tooolbar_refresh']").on("click", Gofast.book.refreshBrowser);
        jQuery("[id='book_explorer_toolbar_search_input']").on("keyup", Gofast.book.searchBrowser);
        <?php if (isset($widget) && !$has_links) : ?>
            jQuery(".wiki-tree-widget-item-name:not(.wiki-processed)").addClass("wiki-processed").on("click", Gofast.book.treeWidgetItemCallback);
        <?php endif;
            if (!isset($widget) || $has_links) : ?>
            jQuery("[data-toggle='tooltip']").tooltip();
        <?php endif; ?>
    });
</script>