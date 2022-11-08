<div id="fullscreen-node">
  <ul class="nav nav-tabs nav-justified">
    <li role="presentation" id="webform-view-tab" class="webform-tab active">
      <a href="#"><?php print t("Fill out", array(), array('context' => 'gofast:gofast_webform')); ?></a>
    </li>
    <?php if(node_access('update', $node)){ ?>
    <li role="presentation" id="webform-edit-tab" class="webform-tab">
      <a href="#"><?php print t("Manage", array(), array('context' => 'gofast:gofast_webform')); ?></a>
    </li>
    <li role="presentation" id="webform-results-tab" class="webform-tab">
      <a href="#"><?php print t("Results", array(), array('context' => 'gofast:gofast_webform')); ?></a>
    </li>
    <?php } ?>
    <li role="presentation" id="webform-submissions-tab" class="webform-tab">
      <a href="#"><?php print t("Your submissions", array(), array('context' => 'gofast:gofast_webform')); ?></a>
    </li>
  </ul>
  <div id="webform-view-content" class="webform-content">
    <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
      <div class="content well well-sm"<?php print $content_attributes; ?>>
        <?php
          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);
          hide($contents['print_links']);
          hide($content['language']);
          hide($content['field_format']);
          hide($content['field_date']);
          hide($content['content_visibility']);
          hide($content['og_group_content_ref']);
          hide($content['field_fivestar']);
          print render($content);
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
        if(TRUE){       
        print "<script>jQuery(document).ready(function(){  setTimeout(function(){                                                
                                               Gofast.loadcomments(".$node->nid.");
                                              }, 2000);});</script>";
        }
        else{
          print "<script>jQuery(document).ready(function(){
                Gofast.checkReply();  });</script>";
        }
      ?>
  </div>
  </div>
  <div id="webform-edit-content" class="webform-content content well well-sm" style="display:none;">
    <!-- Waiting for the AJAX call -->
    <div class="loader-blog"></div>
  </div>
  <div id="webform-results-content" class="webform-content content well well-sm" style="display:none;">
    <!-- Waiting for the AJAX call -->
    <div class="loader-blog"></div>
  </div>
  <div id="webform-submissions-content" class="webform-content content well well-sm" style="display:none;">
    <!-- Waiting for the AJAX call -->
    <div class="loader-blog"></div>
  </div>
</div>
<script type='text/javascript'>
  Drupal.behaviors.gofast_node_actions_breadcrumb = {
        attach: function (context) {
          if(jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')){
            jQuery("#contextual-actions-loading").removeClass('not-processed');
            jQuery.get(location.origin + "/gofast/node-actions/<?php echo $nid; ?>", function( data ) {
              jQuery("#contextual-actions-loading").remove();
              jQuery(data).insertAfter("#breadcrumb-alt-lock");
            });
            jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
            jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $nid; ?>", function( data ) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast").replaceWith(data);
            });
          }
        }
      };
      
      //Add ajaxification to the submit button
      jQuery('.webform-submit, .webform-next').addClass('ctools-use-modal');
      jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Description") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html() + '</div></div>');
      
      var form = jQuery(".node-webform > .content.well.well-sm").find("form");
      if(form.length === 0){
        jQuery(".node-webform > .content.well.well-sm").append("<div class='panel panel-danger'><div class='panel-heading'><i class='fa fa-lock' aria-hidden='true'></i> <?php echo t("Locked Form") ?></div></div>");
      }else{
        form.html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Form") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find("form").html() + '</div></div>');
      }
</script>