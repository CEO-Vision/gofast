<div id="fullscreen-node">
    <ul class="nav nav-tabs nav-justified" role="tablist">
      <li role="presentation" class="active"><a href="#oghome" aria-controls="oghome" role="tab" data-toggle="tab"><?php print t("Home"); ?></a></li>
      <li role="presentation"><a href="#ogmember" aria-controls="oglocation" role="tab" data-toggle="tab"><?php print t("Members"); ?></a></li>
      <li role="presentation"><a href="#oglocation" aria-controls="oglocation" role="tab" data-toggle="tab"><?php print t("Locations"); ?></a></li>
    </ul>
    
    <?php
      $ulid = $content['field_description']['#object']->field_userlist_ulid[LANGUAGE_NONE][0][value];
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);    
    ?>
    
    <div class="tab-content content well well-sm">
         <div role="tabpanel" class="tab-pane active" id="oghome">
             <?php print $content['field_description']['#object']->field_description[LANGUAGE_NONE][0][value];?>
          </div>
          <div role="tabpanel" class="tab-pane" id="ogmember">
            <?php print $userlist_members ?>
          </div>
          <div role="tabpanel" class="tab-pane" id="oglocation">
              <?php 
                $ulid  = $node->field_userlist_ulid['und'][0]['value'];
                $entity = entity_load_single('userlist', $ulid);
              
                //Get all userlist's groups
                $groups_ul = gofast_userlist_og_get_groups_by_userlist($entity);

                foreach($groups_ul['node'] as $nid_ul){
                      if(!gofast_og_is_root_space(node_load($nid_ul))){
                          $path_userlist[$nid_ul] = gofast_cmis_space_get_drupal_path($nid_ul); //Get breadcrumbs for all groups
                      }
                } 
                if (empty($path_userlist)){
                    print t("The userlist haven't locations",array(),array('context'=> 'gofast:gofast_userlist'));
                }
                
                asort($path_userlist);
                foreach($path_userlist as $nid_ul=>$path){ 
                      gofast_get_node_space_breadcrumb_async($nid_ul,NULL,TRUE,$ulid); //Get breadcrumbs for all groups
                 } ?>
          </div>
    </div>

</div>
<script type='text/javascript'>
  Drupal.behaviors.gofast_node_actions = {
        attach: function (context) {
          if(jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')){
            jQuery("#contextual-actions-loading").removeClass('not-processed');
            jQuery.get(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", function( data ) {
              jQuery("#contextual-actions-loading").remove();
              jQuery(data).insertAfter("#breadcrumb-alt-lock");
              Drupal.attachBehaviors();
              if (jQuery('#unlock_document_span').length){
                  jQuery("li>a.on-node-lock-disable").addClass('disabled');
              }
            });
            jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
            jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $nid; ?>", function( data ) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast").replaceWith(data);
              Drupal.attachBehaviors();
            });
            Drupal.behaviors.gofast_node_actions = null;
          }
        }
      };
      
      <?php
        if($node->type === "alfresco_item"){
      ?>

          //Tells the page template that we will handle navigation
          Gofast.mobileNavigationHandled = true;

          //Triger the file browser navigation when we are ready and connected
          function triggerMobileNodeNavigation(){
            if(typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false){ //Not yet ready
              setTimeout(triggerMobileNodeNavigation, 1000);
            }else{ //Ready !
              Gofast.ITHitMobile.navigate("<?php print gofast_cmis_get_first_available_location($node); ?>");
            }
          }
          triggerMobileNodeNavigation();
      <?php
        }
      ?>        
</script>