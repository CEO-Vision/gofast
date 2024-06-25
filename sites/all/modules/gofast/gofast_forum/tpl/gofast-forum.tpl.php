<?php
/**
  This file overrides forum-post of advanced-forum module (3rd module)
 */

    //Check if comment is private to apply the proper class
    if($comment->field_comment_is_private[LANGUAGE_NONE][0]['value']){
        $classes .= " gofast-comment-is-private";
    }

?>
<div class="h-100 w-100 <?= gofast_essential_is_essential() ? 'overflow-auto' : ''; ?>">
    <div class="card card-custom" id="forum_breadcrumb">
        <div class="card-header min-h-50px flex-nowrap px-3">
            <?php print theme('gofast_menu_header_subheader', ['node' => $node]); ?>
        </div>
    </div>

<div class="forum-node-wrapper pb-5">
    <div id="forum-container">
        <?php print theme('gofast_forum_node_header', ['node' => $node, 'links' => $links]); ?>
    </div>

    <?php // comments are loaded by the sidebar template ?>
    <div id="comments-container" class="card card-custom card-stretch pt-4" style="height: 15rem !important;">
        <div class="spinner spinner-track spinner-primary gofast-spinner-xxl mx-auto"></div>
    </div>
</div>
</div>
<script>
    Drupal.behaviors.gofast_node_actions = {
      attach: function(context) {
        if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
          jQuery("#contextual-actions-loading").removeClass('not-processed');
          jQuery.get(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", function(data) {
            jQuery("#contextual-actions-loading").replaceWith(data);
            Drupal.attachBehaviors();
          });
          Drupal.behaviors.gofast_node_actions = null;
        }
      }
    };
    jQuery(document).ready(async function() {
        <?php if (gofast_essential_is_essential()) : ?>
            $("#nav_mobile_file_browser_forum_container").click();
        <?php endif; ?>
        if (window.location.hash.startsWith("#comment-")) {
            // we wan't be sure the comment exists in the page before the comments have been loaded
            await new Promise(function(resolve) {
                const waitForCommentsContainerInterval = setInterval(function() {
                    const hasSpinner = document.querySelector("#comments-container .spinner");
                    if (hasSpinner) {
                        return;
                    }
                    clearInterval(waitForCommentsContainerInterval);
                    resolve();
                }, 250)
            });
            // do we have the comment on the page?
            if (!$(window.location.hash).length) {
                return;
            }
            // wait a bit to make sure element position props have been calculated
            await new Promise((resolve) => setTimeout(() => resolve(), 1000));
            $(window.location.hash)[0].scrollIntoView({ behavior: 'smooth' });
        }
        $("#explorer-forum").tab("show");
        $(".explorer-main-container .nav.nav-tabs a.active:not('#explorer-forum')").removeClass('active');
        if (!$("#explorer-toggle").hasClass("open")) {
            $("#explorer-toggle").click();
        }
    });
</script>
