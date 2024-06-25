<?php
global $user;
$can_update = node_access('update', $node);
$is_not_deleted = $node->status == 1 || ($node->status == 0 && gofast_cmis_check_and_sync_node_status($node));
?>
<?php if(!$isAjax): ?>
<div class="card card-custom card-stretch h-auto">
    <?php if(!$only_article){ ?>
        <div class="gofastArticleBreadcrumb card-header min-h-50px flex-nowrap px-3">
            <?=  theme('gofast_menu_header_subheader', array('node' => $node, "hasContext" => $hasContext)) ?>
        </div>
    <?php } ?>
<?php endif; ?>
    <div id="fullscreen-node" class="h-100 w-100 card-body overflow-auto p-0" style="<?= $only_article ? "overflow: visible !important;" : "overflow-y: auto !important; overflow-x: hidden !important;" ?>">
        <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> h-100 w-100" <?php print $attributes; ?>>

            <?php if (isset($content['vud_node_widget_display'])) : ?>
                <div class="gofast-header">
                    <div style="float:right;">
                        <?php print $content['vud_node_widget_display']['#value']; ?>
                    </div>
                </div>
            <?php endif; ?>

            <div class="w-100" style="height:100%; <?php print $content_attributes; ?>">


                <!---->

                <script type="text/javascript">
                    Drupal.behaviors.dragdropinit = {
                        attach: function(context) {
                            Drupal.gofast_cmis.init_dragdrop(true);
                        }
                    }
                </script>
                <?php
                if (isset($content['comments']) && isset($content['links'])) {
                    // We hide the comments and links now so that we can render them later.
                    hide($content['comments']);
                    hide($content['links']);
                }
                ?>
                <?php if ($is_not_deleted): ?>
                <div class="<?php print !$only_article ? "p-4": ""; ?>">
                    <?php if (isset($description)) : ?>
                        <p class="gofastArticleDescription homeDescription text-muted w-100"><?= trim($description) ?></p>
                    <?php endif; ?>
                    <?php if ($only_article) : ?>
                    <div class="card card-custom mx-auto bg-white h-100 mb-4">
                        <div class="card-header border-0 px-4 py-2 min-h-40px bg-primary text-white">
                            <h3 class="card-title align-items-start flex-column">
                                <span class="card-label font-weight-bolder font-size-h4 text-white"><?php echo t('Content', array(), array('context' => 'gofast:gofast_og')) ?></span>
                            </h3>
                        </div>
                        <div class="homeArticleContainer image-input w-100">
                            <?php if ($can_update) : ?>
                            <label class="btn btn-xs btn-icon btn-circle btn-white btn-hover-text-primary btn-shadow" data-action="change" onClick="Gofast.triggerEditableInput('.gofastArticleContent.homeArticle > div')">
                                <i class="fas fa-edit icon-sm text-muted"></i>
                            </label>
                            <?php endif; ?>
                        </div>
                    <?php endif; ?>
                        <div class="gofastArticleContent homeArticle p-2 rounded shadow-sm" style="<?= !$only_article ? "" : "min-height: 300px;" ?>">
                            <?= $article_body ?: t('No content') ?>
                        </div>
                    <?php if ($only_article) : ?>
                    </div>
                    <?php endif; ?>
                </div>
                <?php else: ?>
                    <?php print theme('gofast_cmis_node_deleted', array('node' => $node)); ?>
                <?php endif; ?>
            </div>
        </div>
    </div>
<?php if(!$isAjax): ?>
</div>
<?php endif; ?>

<script type='text/javascript'>
    Drupal.behaviors.gofast_node_actions = {
        attach: function(context) {
            Gofast.gofast_main_block_breadcrumb(<?= json_encode(!$only_article) ?>);
            if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
                jQuery("#contextual-actions-loading").removeClass('not-processed');
                jQuery.get(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", function(data) {
                    jQuery("#contextual-actions-loading").replaceWith(data);
                    Drupal.attachBehaviors();
                    if (jQuery('#unlock_document_span').length) {
                        jQuery("li>a.on-node-lock-disable").addClass('disabled');
                    }
                });
            }
            Drupal.behaviors.gofast_node_actions = null;
        }
    };

    jQuery(document).ready(function() {
        // we make an additional check for homepage in case the user has displayed the homepage as an article by manually entering its node link
        window.initArticleEditableInputs(<?php echo $node->nid; ?>, "<?php echo $node->title; ?>", <?php echo json_encode($can_update) ?>, <?php echo json_encode(gofast_book_is_article_homepage($node->nid)) ?>);
        // display weight indicator in breadcrumb
        $.get('/space/book/' + Gofast.get("node").id + '/weight/get').done((result) => {
            if (!result.length || typeof result[0].body_summary == "undefined") {
                return;
            }
            let weight = result[0].body_summary;
            if (!weight) {
                return;
            }
            weight = "W" + weight.padStart(3, "0");
            $("#gofast-wiki-weight-indicator").text(weight);
        });
    <?php
    if ($node->type === "alfresco_item" || $node->type === 'article') {
    ?>

        //Tells the page template that we will handle navigation
        Gofast.mobileNavigationHandled = true;

        //Trigger the file browser navigation when we are ready and connected
        function triggerMobileNodeNavigation() {
            if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
                setTimeout(triggerMobileNodeNavigation, 1000);
            } else { //Ready !

                if (jQuery("#ithit-toggle").hasClass('hiddenithit')) {
                    // Explorer mobile is unfold, don't triggeer node navigate (no request webdav)
                    Gofast.ITHitMobile.getPathIfUnfload("<?php print gofast_cmis_get_first_available_location($node); ?>");
                } else {
                    Gofast.ITHitMobile.navigate("<?php print gofast_cmis_get_first_available_location($node); ?>");
                }
            }
        }
        triggerMobileNodeNavigation();
    <?php
    }
    ?>
    });
</script>
