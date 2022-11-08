<!-- START gofast-forum-file-browser.tpm.php -->
<div class="forum-explorer-wrapper">
    <div id="forum_explorer_header">
        <div class="forum-explorer-title">
            <span>Forums</span>
        </div>
        <div id="forum_explorer_toolbar_search" class="input input-group-sm">
            <div class="input-group">
                <input id="forum_explorer_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
                <div class="input-group-append dropdown no-arrow" id="file_browser_mobile_toolbar_refresh_group">
                    <button title="<?php echo t('Refresh'); ?>" id="file_browser_forums_mobile_tooolbar_refresh" type="button" class="btn input-group-text dropdown-toggle" ><i class="fa fa-refresh" aria-hidden="true"></i></button>
                </div>
            </div>    
        </div>
    </div>
    <div id="forum_explorer_body" class="forum-explorer-body panel-body">
        <?php print $forums; ?>
    </div>  
</div>
<!-- END gofast-forum-file-browser.tpl.php -->
<script>
    jQuery(document).ready(function() {
        jQuery("#expl-forum .scrolltoanchor").off("click");
        jQuery("#expl-forum .scrolltoanchor").on("click", (e) => { e.preventDefault; e.stopPropagation(); document.querySelector("#" + e.target.href.split("#")[1]).scrollTo({ behavior: 'smooth' })});
        if(jQuery("#explorer-forum").hasClass("active")) {
            jQuery(".explorer-main-container .nav.nav-tabs a.active:not('#explorer-forum')").removeClass('active');
        }
    });
</script>