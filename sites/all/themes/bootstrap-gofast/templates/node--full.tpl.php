<div id="fullscreen-node">
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix" <?php print $attributes; ?> <div class="gofast-header">
    <?php if (isset($content['vud_node_widget_display'])) : ?>
      <div style="float:right;">
        <?php print $content['vud_node_widget_display']['#value']; ?>
      </div>
    <?php endif; ?>
  </div>

  <div class="content well well-sm" <?php print $content_attributes; ?>>


    <?php

    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);

    if ($node->type === 'alfresco_item') {
        //Retrieve saved documents form configuration
        $default_documents_form_configuration = array(
            'ticket' => 1,
            'ticket_path_length' => 200,
            'gofast_onlyoffice_ro_preview' => FALSE,
        );
        $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
        if($node->status == 1 && $documents_form_defaults['gofast_onlyoffice_ro_preview'] && in_array(strtolower(gofast_cmis_node_get_extension($node)), gofast_onlyoffice_viewable_document_extensions())){
            $final_content_with_iframe = gofast_onlyoffice_editor($node, TRUE);
        }else{
            
        }
      if($final_content_with_iframe == "RELOAD"){
          print "<script>window.location.reload();</script>";
      }else{
        print $final_content_with_iframe;
      }
    } else {
      print render($content);
    }
    ?>
  </div>

  <div id="comments-container">
    <div>
      <?php
      // Si pas de commentaires sur le noeud, on affiche quand meme la div du
      // container des commentaires, pour pouvoir la mettre à jour dynamiquement
      // en JS.
      print '<div id="comments" class="comment-wrapper">';
      print '<div class="loader-blog"></div>';
      print '</div>';
      ?>
    </div>
  </div>
  <?php
  if (TRUE) {
    print "<script>jQuery(document).ready(function(){  setTimeout(function(){
                                               Gofast.loadcomments(" . $node->nid . ");
                                              }, 2000);});</script>";
  } else {
    print "<script>jQuery(document).ready(function(){
                Gofast.checkReply();  });</script>";
  }
  ?>
</div>

<script type='text/javascript'>
  Drupal.behaviors.gofast_node_actions = {
    attach: function(context) {
      if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
        jQuery("#contextual-actions-loading").removeClass('not-processed');
        jQuery.get(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", function(data) {
          jQuery("#contextual-actions-loading").remove();
          jQuery(data).insertAfter("#breadcrumb-alt-lock");
          Drupal.attachBehaviors();
          if (jQuery('#unlock_document_span').length) {
            jQuery("li>a.on-node-lock-disable").addClass('disabled');
          }
        });
        Drupal.behaviors.gofast_node_actions = null;
      }
    }
  };

  <?php
  if ($node->type === "alfresco_item") {
  ?>

    //Tells the page template that we will handle navigation
    Gofast.mobileNavigationHandled = true;

    //Trigger the file browser navigation when we are ready and connected
    function triggerMobileNodeNavigation() {
      if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
        setTimeout(triggerMobileNodeNavigation, 1000);
      } else { //Re
        Gofast.ITHitMobile.selectedTitle = "<?php print $node->title; ?>";
        if (jQuery("#ithit-toggle").hasClass('hiddenithit')) {
          // Explorer mobile is unfold, don't triggeer node navigate (no request webdav)
          Gofast.ITHitMobile.getPathIfUnfload("<?php print gofast_cmis_get_first_available_location($node); ?>");
        } else {
          Gofast.ITHitMobile.navigate("<?php print  gofast_cmis_get_first_available_location($node); ?>");
        }
      }
    }
    triggerMobileNodeNavigation();
  <?php
  }
  ?>
</script>
