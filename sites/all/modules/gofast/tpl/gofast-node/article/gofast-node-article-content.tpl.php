<?php
global $user;
$can_update = node_access('update', $node);
$is_not_deleted = $node->status == 1 || ($node->status == 0 && gofast_cmis_check_and_sync_node_status($node));
?>
<div class="card card-custom card-stretch">
    <?php if(!$only_article){ ?>
        <div class="gofastArticleBreadcrumb card-header min-h-50px flex-nowrap px-3">
            <?= $is_not_deleted ? theme('gofast_menu_header_subheader', array('node' => $node)) : "" ?>
        </div>
    <?php } ?>
    <div id="fullscreen-node" class="h-100 w-100 card-body overflow-auto p-0">
        <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> h-100 w-100" <?php print $attributes; ?>>

            <?php if (isset($content['vud_node_widget_display'])) : ?>
                <div class="gofast-header">
                    <div style="float:right;">
                        <?php print $content['vud_node_widget_display']['#value']; ?>
                    </div>
                </div>
            <?php endif; ?>

            <div class="w-100" style="<?php print !$only_article ? "height: 100%" : "height: 300px"; ?>" <?php print $content_attributes; ?>>


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
                        <p class="gofastArticleDescription text-muted"><?= $description ?></p>
                    <?php endif; ?>
                    <div class="gofastArticleContent p-4 <?= $can_update ? 'bg-secondary' : 'card' ?> rounded shadow-sm" style="<?php print !$only_article ? "" : "min-height: 270px"; ?>">
                        <?= $article_body ?: t('No content') ?>
                    </div>
                </div>
                <?php else: ?>
                    <?php print theme('gofast_cmis_node_deleted', array('node' => $node)); ?>
                <?php endif; ?>
            </div>
        </div>
    </div>

</div>

<script type='text/javascript'>
    Drupal.behaviors.gofast_node_actions = {
        attach: function(context) {
            if (jQuery(".breadcrumb-gofast").length !== 0 && !jQuery(".breadcrumb-gofast").hasClass('processed')) {
          jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
          var options = {"only_title" : false, "only_first": false};
            jQuery.get(location.origin + "/gofast/node-breadcrumb/" + Gofast.get('node').id + "?options=" + JSON.stringify(options), function(data) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast:not('.breadcrumb-gofast-full')").replaceWith(data);
            });
        }
            
            if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
                jQuery("#contextual-actions-loading").removeClass('not-processed');
                jQuery.get(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", function(data) {
                    jQuery("#contextual-actions-loading").replaceWith(data);
                    Drupal.attachBehaviors();
                    if (jQuery('#unlock_document_span').length) {
                        jQuery("li>a.on-node-lock-disable").addClass('disabled');
                    }
                });
                Drupal.behaviors.gofast_node_actions = null;
            }
        }
    };

    jQuery(document).ready(function() {
        window.initArticleEditableInputs(<?php echo $node->nid;?>, "<?php echo $node->title;?>", <?php echo json_encode($can_update) ?>);
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
</script>
