<div class="card card-custom card-stretch<?= gofast_essential_is_essential() ? " isStackedLayer" : "" ?>">
  <div class="card-header min-h-50px flex-nowrap px-3">
    <?php print theme('gofast_menu_header_subheader', array('node' => $node)); ?>
  </div>
  <div id="fullscreen-node" class="h-100 w-100 card-body overflow-auto p-0">
    <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> h-100 w-100" <?php print $attributes; ?>>

      <?php if (isset($content['vud_node_widget_display'])) : ?>
        <div class="gofast-header">
          <div style="float:right;">
            <?php print $content['vud_node_widget_display']['#value']; ?>
          </div>
        </div>
      <?php endif; ?>

      <div class="h-100 w-100" <?php print $content_attributes; ?>>


        <!---->

        <script type="text/javascript">
          Drupal.behaviors.dragdropinit = {
            attach: function(context) {
              Drupal.gofast_cmis.init_dragdrop(true);
            }
          }
        </script>
        <!--  <p class="drop-area drop-area-processed" id="fast_drag_drop"> -->
        <?php

        // We hide the comments and links now so that we can render them later.
        hide($content['comments']);
        hide($content['links']);

        print theme("gofast_webform_webform_tabs", ["node" => $node]);
        ?>
        <!--   </p>-->
      </div>
    </div>
  </div>
</div>

<script type='text/javascript'>
  Drupal.behaviors.gofast_node_actions = {
    attach: function(context) {
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
</script>
