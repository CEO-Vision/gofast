<div id="fullscreen-node">
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
      
      jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Description") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find(".field-name-body").html() + '</div></div>');
      
      var form = jQuery(".node-webform > .content.well.well-sm").find("form");
      if(form.length === 0){
        jQuery(".node-webform > .content.well.well-sm").append("<div class='panel panel-danger'><div class='panel-heading'><i class='fa fa-lock' aria-hidden='true'></i> <?php echo t("Form") ?></div></div>");
      }else{
        form.html("<div class='panel panel-default'><div class='panel-heading'><?php echo t("Form") ?></div><div class='panel-body'>" + jQuery(".node-webform > .content.well.well-sm").find("form").html() + '</div></div>');
      }
</script>