<!-- START gofast-forum-file-browser.tpm.php -->
<div class="forum-explorer-wrapper w-100 d-flex flex-column">
    <div id="forum_explorer_header">
        <div id="forum_explorer_toolbar_search" class="input input-group-sm">
            <div class="input-group">
                <input id="forum_explorer_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
                <div class="input-group-append dropdown no-arrow" id="file_browser_mobile_toolbar_refresh_group">
                    <button title="<?php echo t('Refresh'); ?>" id="file_browser_forums_mobile_tooolbar_refresh" type="button" class="btn input-group-text" ><i class="fa fa-refresh" aria-hidden="true"></i></button>
                </div>
                <?php if(gofast_essential_is_essential() && !gofast_mobile_is_phone()): ?>
                    <a href="/node/add/forum" title="Forums" type="button" class="btn btn-icon btn-light-primary ml-2"><i class="fas fa-plus"></i></a>
                <?php endif; ?>
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
        $("#file_browser_forums_mobile_tooolbar_refresh").on("click", function() {
            const $forumTreeParentElement = $(this).closest(".forum-explorer-wrapper").parent();
            Gofast.reloadForums($forumTreeParentElement);
        });
        let targetInterval = false;
        jQuery("#expl-forum .scrolltoanchor").on("click", async (e) => {
            const [targetForumPath, targetCommentId] = e.currentTarget.getAttribute("href").split("#");
            let reload = true;
            // prevent page reload if user is already in the target page
            if (document.location.pathname == targetForumPath) {
                e.preventDefault();
                e.stopPropagation();
                reload = false;
            }
            let targetComment = null;
            // we wait for the page and comments to be loaded before scrolling to the target comment
            await new Promise(function(resolve) {
                const waitForForumLoadInterval = setInterval(function() {
                    const hasLoader = document.querySelector("#backdrop").style.display == "block";
                    const hasSpinner = document.querySelector("#comments-container .spinner");
                    targetComment = document.querySelector("#" + targetCommentId);
                    if (hasLoader || hasSpinner || !targetComment) {
                        return;
                    }
                    clearInterval(waitForForumLoadInterval);
                    resolve();
                }, 250);
            });
            // wait a bit to make sure element position props have been calculated
            if (reload) {
                await new Promise((resolve) => setTimeout(() => resolve(), 1000));
            }
            // scroll to target comment
            targetComment.scrollIntoView({ behavior: 'smooth' });
        });
        if(jQuery("#explorer-forum").hasClass("active")) {
            jQuery(".explorer-main-container .nav.nav-tabs a.active:not('#explorer-forum')").removeClass('active');
        }
    });
</script>