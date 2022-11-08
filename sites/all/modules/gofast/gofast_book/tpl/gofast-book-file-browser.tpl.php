<!-- START gofast-book-file-browser.tpl.php -->
<div class="book-explorer-wrapper">
    <div id="book_explorer_header">
        <div class="book-explorer-title d-flex align-items-center justify-content-between">
            <span><?= t("Wikis") ?></span>
            <a href="/node/add/article" title="<?= t("Wikis") ?>" type="button" class="btn btn-icon btn-light-primary btn-xs"><i class="fas fa-plus"></i></a>
        </div>
        <div id="book_explorer_toolbar_search" class="input input-group-sm">
            <div class="input-group">
                <input id="book_explorer_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
                <div class="input-group-append dropdown no-arrow" id="file_browser_mobile_toolbar_refresh_group">
                    <button title="<?php echo t('Refresh'); ?>" id="file_browser_books_mobile_tooolbar_refresh" type="button" class="btn input-group-text" ><i class="fa fa-refresh" aria-hidden="true"></i></button>
                </div>            
            </div>    
        </div>
    </div>
    <div id="book_explorer_body" class="book-explorer-body panel-body">
        <?php print $books; ?>
    </div>  
</div>
<!-- END gofast-book-file-browser.tpl.php -->
<script>
    jQuery(document).ready(function() {
        // uncollapse on link click
        jQuery(".book-explorer-element-name").on("click", function(e) {
            const arrow = jQuery(e.currentTarget).closest('tr').find(".book-explorer-element-open");
            if (arrow.hasClass("ki-bold-arrow-next")) {
                arrow.click();
            }
        });
        // uncollapse on icon click
        jQuery(".book-explorer-element-open").on("click", function() {
            let _this = jQuery(this).parent().parent();
            let id = jQuery(_this).attr('id');
            let childs_parents_doms = jQuery(_this).siblings().find(".book-explorer-element-parent");
            jQuery.each(childs_parents_doms, function(k, elem) {
                if(jQuery(elem).text().trim() === id) {
                    if(jQuery(elem).parent().attr('class').includes("book-explorer-element-visible")) {
                        jQuery(elem).parent().find(".book-explorer-element-open").addClass("ki-bold-arrow-next").removeClass("ki-bold-arrow-down");                
                    }
                    jQuery(elem).parent().toggleClass("book-explorer-element-visible").toggleClass("book-explorer-element-collapsed");
                }
            });
            
            if(jQuery(this).attr('class').includes('ki-bold-arrow-next')) {
                jQuery(this).removeClass("ki-bold-arrow-next").addClass("ki-bold-arrow-down");
            }else jQuery(this).addClass("ki-bold-arrow-next").removeClass("ki-bold-arrow-down");
            
        });
        if(jQuery("#wiki").hasClass("active")) {
            jQuery(".explorer-main-container .nav.nav-tabs a.active:not('#explorer-wiki')").removeClass('active');
        }
        jQuery("[data-toggle='tooltip']").tooltip();
    });
</script>