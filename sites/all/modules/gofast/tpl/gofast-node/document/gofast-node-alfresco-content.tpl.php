<?php if(!$isAjax): ?>
<div class="card card-custom card-stretch<?= gofast_essential_is_essential() ? " isStackedLayer" : "" ?>">
  <div class="card-header min-h-50px flex-nowrap px-3">
      <?php print theme('gofast_menu_header_subheader', array('node' => $node, "hasContext" => $hasContext)); ?>
  </div>
<?php endif; ?>
  <div id="fullscreen-node" class="h-100 w-100 card-body overflow-auto p-0">
    <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> h-100 w-100" <?php print $attributes; ?>>

      <?php if (isset($content['vud_node_widget_display'])) : ?>
        <div class="gofast-header">
            <div style="float:right;">
              <?php print $content['vud_node_widget_display']['#value']; ?>
            </div>
        </div>
      <?php endif; ?>

      <div class="h-100 w-100 d-flex flex-column overflow-hidden" <?php print $content_attributes; ?>>
      
  <script type="text/javascript">
      Drupal.behaviors.dragdropinit = {
              attach: function(context) {
                  Drupal.gofast_cmis.init_dragdrop(true);
              }
      }
  </script>
  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);

    //Print preview / content
    print gofast_cmis_get_content_preview($node);
  ?>
      </div>
    </div>
  </div>
  <script type='text/javascript'>
    Drupal.behaviors.gofast_node_actions = {
      attach: function(context) {
        Gofast.gofast_main_block_breadcrumb(true);

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

    // some content may have transparency: remove background spinner once content is loaded
    if (typeof $contentFrame == "undefined") {
      let $contentFrame;
    }
    $contentFrame = jQuery("#container_preview_element > *:first-child:not(.processed)");
    if ($contentFrame.length) {
      // this needs to be attached after content element has been inserted but before the whole DOM is ready since the load event may be triggered sooner than the ready event
      $contentFrame.addClass("processed").load(function() {
        jQuery(this).parent().addClass("no-spinner");
      });
    }

    jQuery(document).ready(function() {
        window.initDocumentEditableInputs();
        if(!Gofast._settings.isEssential){return;}
        Gofast.Essential.handleDocumentPage();
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
<?php if(!$isAjax): ?>
</div>
<?php endif; ?>

<?php $detect = new Mobile_Detect(); ?>
<?php if (gofast_essential_is_essential() && $node->type == "alfresco_item" && (!$detect->isMobile() || $detect->isTablet()) && !$isAjax) : ?>
  <div id="fullscreenNavigationButtons" class="justify-content-between normal-screen" style="left: 85%; top: 0.5rem;  width: 100px; margin-right:15px;">
    <div>
      <a id="node-previous-content-button" class="btn <?= $hasContext ? "btn-primary" : "noContext"; ?> btn-icon btn-sm position-relative">
        <i class="ki ki-bold-arrow-back text-white icon-nm"></i>
      </a>
    </div>
    <div>
      <a id="node-next-content-button" class="btn <?= $hasContext ? "btn-primary" : "noContext"; ?> btn-icon btn-sm position-relative">
        <i class="ki ki-bold-arrow-next text-white icon-nm"></i>
      </a>
    </div>
    <div>
      <a id="node-normal-screen-button" class="btn btn-primary btn-icon btn-sm position-relative">
        <i class="fa fa-compress text-white icon-nm"></i>
      </a>
    </div>
  </div>
<?php endif; ?>


