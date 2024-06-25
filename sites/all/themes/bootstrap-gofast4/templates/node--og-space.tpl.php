<?php

  libraries_load('x-editable');
      drupal_add_js(drupal_get_path('module', 'gofast') . '/js/gofast_xeditable.js', array('type' => 'file', 'weight' => 5));

?>
<div id="fullscreen-node">
   <?php
      $json_books = gofast_book_get_json_books(array(arg(1)));
      libraries_load('ztree');
      $path = drupal_get_path('module', 'gofast_book');
      drupal_add_js($path . '/js/gofast_book_block.js');
      $settings = array('data_tree' => $json_books, "is_document" => "true");
      drupal_add_js(array('gofast_book_tree' => $settings), 'setting');

   if(gofast_group_is_archive($node)){ ?>
    <div class="alert alert-warning">
        <h4 style="font-size: 12px "><?php print t('This space is archived', array(), array('context' => 'gofast')) ?></h4>
    </div>
   <?php } ?>
   <div id="node-<?php print $node->nid; ?>" class="gofast-og-page <?php print $classes; ?> clearfix"<?php print $attributes; ?>>

    <div class="content"<?php print $content_attributes; ?>>
      <div>
        <ul class="nav nav-tabs nav-justified" role="tablist">
          <li role="presentation" class="active"><a id="ogtab_home" href="#oghome" aria-controls="oghome" role="tab" data-toggle="tab"><?php print t("Home"); ?></a></li>
          <li role="presentation"><a href="#ogactivity" aria-controls="ogactivity" role="tab" data-toggle="tab" id="tab_ogactivity"><?php print t("Activity"); ?></a></li>
          <li role="presentation"><a href="#ogstats" aria-controls="ogstats" role="tab" data-toggle="tab" id="tab_ogstats"><?php print t("Statistics"); ?></a></li>
          <?php $node_path = gofast_cmis_space_get_webdav_path_node_page($node->nid); ?>
          <span style='display:none;' id='webdav_path'><?php print $node_path; ?></span>
            <!-- <li><a href="/gofast/browser" onclick="Gofast.setMemorizedPath('<?php echo $node_path; ?>');" ><?php print t("Documents"); ?></a></li> -->
           <li role="presentation">
              <a id="ogtab_documents" href="#ogdocuments" aria-controls="ogdocuments" role="tab" data-toggle="tab" >
              <?php print t("Documents"); ?>
              </a>
          </li>
          <?php if($node->type != "public"): ?>
          <li role="presentation"><a href="#ogkanban" aria-controls="ogkanban" role="tab" data-toggle="tab"><?php print t('Tasks', array(), array('context' => 'gofast_kanban')); ?></a></li>
          <?php endif;?>
          <li role="presentation"><a href="#ogcalendar" aria-controls="ogcalendar" role="tab" data-toggle="tab"><?php print t("Calendar"); ?></a></li>
         <?php if(gofast_og_is_entity_hide_members_tab($node)): ?>
            <li role="presentation" class="disabled"><a href="#ogmembers" aria-controls="ogmembers" class="disabled" role="tab"  data-toggle="tab" id="tab_ogmembers_disabled"><?php print t("Members"); ?></a></li>
         <?php else: ?>
            <li role="presentation"><a href="#ogmembers" aria-controls="ogmembers" role="tab"  data-toggle="tab" id="tab_ogmembers"><?php print t("Members"); ?></a></li>
         <?php endif; ?>


        <li role="presentation"><a id="ogtab_conversation" href="#ogconversation" aria-controls="ogconversation" role="tab" data-toggle="tab"><?php print t("Chat"); ?></a></li>

        </ul>

        <div class="tab-content content well well-sm">
          <div role="tabpanel" class="tab-pane active" id="oghome">
              <span></span>
          </div>
          <div role="tabpanel" class="tab-pane" id="ogactivity">
              <div class="loader-blog"></div>
          </div>
          <div role="tabpanel" class="tab-pane" id="ogstats">

          </div>
          <div role="tabpanel" class="tab-pane" id="ogdocuments">
            <?php
            print theme('ajax_file_browser');
            ?>
            <script>
              //Tells the page template that we will handle navigation
              Gofast.mobileNavigationHandled = true;

              //Triger the file browser navigation when we are ready and connected
              function triggerNavigation(){
                if (typeof Gofast.ITHit === "undefined" || typeof Gofast.ITHit.Uploader === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
                  setTimeout(triggerNavigation, 1000);
                }else{ //Ready !
                  //Get params from URL
                  var params = {};
                  if (location.search) {
                      var parts = location.search.substring(1).split('&');

                      for (var i = 0; i < parts.length; i++) {
                          var nv = parts[i].split('=');
                          if (!nv[0]) continue;
                          params[nv[0]] = nv[1] || true;
                      }
                  }
                  Gofast.ITHit.loadTree();
                  if(typeof params.path === "undefined"){ //No path provided, navigate to default path
                    Gofast.ITHit.navigate("<?php print $node_path; ?>");
                    Gofast.ITHitMobile.navigate("<?php print $node_path; ?>");
                  }else{ //Path provided, navigate to path
                    Gofast.ITHit.navigate(params.path);
                    Gofast.ITHitMobile.navigate(params.path);
                  }
                  //Attach events to the browser
                  Gofast.ITHit.attachBrowserEvents();
                  //Init queue mechanism if needed
                  if(Gofast.ITHit.activeQueue === false){
                    Gofast.ITHit.refreshQueue();
                  }
                  //Set drag and drop zone for upload
                  Gofast.ITHit.Uploader.DropZones.RemoveById('file_browser_full_files');
                  Gofast.ITHit.Uploader.DropZones.RemoveById('file_browser_full_upload_table');

                  Gofast.ITHit.Uploader.DropZones.AddById('file_browser_full_files');
                  Gofast.ITHit.Uploader.DropZones.AddById('file_browser_full_upload_table');
                  //Add events handlers for upload queue
                  Gofast.ITHit.attachUploadEvents();
                }
              }
              triggerNavigation();

              <?php if($_POST['gofast_og_wrong_path']){
                        $_POST['gofast_og_wrong_path'] = FALSE;
             ?>
                        Gofast.toast(Drupal.t("Unable to find this space's folder", {}, {context: 'gofast:ajax_file_browser'}), "warning");
             <?php } ?>
            </script>
          </div>
          <?php if($node->type != "public"): ?>
          <div role="tabpanel" class="tab-pane" id="ogkanban">
            <?php $kanban_id = gofast_kanban_get_space_kanban($node->nid)[0];  ?>
            <?php $card_to_display = isset($_GET['card_id'])? '/card/'.$_GET['card_id'] : '' ; ?>
              <iframe src="/kanban/<?php echo $kanban_id. $card_to_display; ?>" id="gf_kanban" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe>
              <script type="text/javascript">
                (function ($, Gofast, Drupal) {
                    'use strict';
                    Gofast.reloadKanbanFromPollingExternal = function (kanbanId) {
                        $('#gf_kanban')[0].contentWindow.Gofast.reloadKanbanFromPolling(kanbanId);
                    }
                })(jQuery, Gofast, Drupal);
              </script>
          </div>
          <?php endif; ?>
          <div role="tabpanel" class="tab-pane" id="ogcalendar">
            <?php
            print views_embed_view('calendar', 'page_1');
            ?>
          </div>
          <div role="tabpanel" class="tab-pane" id="ogmembers">
            <?php
            if(!gofast_og_is_entity_hide_members_tab($node)){
                print $space_members;
            }
            ?>
          </div>


          <div role="tabpanel" class="tab-pane" id="ogconversation">
            <?php if($node->field_riot_identifier[LANGUAGE_NONE][0]['value'] !=''): ?>
              <div id="DivRiot"></div>
                <!--<iframe src="/sites/all/libraries/riot/index.html#/room/<?php echo $node->field_riot_identifier[LANGUAGE_NONE][0]['value']; ?>" id="gf_conversation" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe> -->
            <?php else : ?>
                <span class="RiotMessageRoom"> <?php print t('This collaboratif space does not have any chatroom yet.');?>
                <?php global $user;
                if (in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $node->nid, $user->uid), true) || $user->uid == 1) : ?>
                    <?php print t('The administrator of this space can create a chatroom via the context actions menu.');?>
                     ( <i class="fa fa-bars" aria-hidden="true"></i> )
                    </span>
                <?php else : ?>
                    <?php print t('Please contact a space administrator (“Members” tab) to ask for the creation of a linked chatroom.');?></span>
                <?php endif; ?>

            <?php endif; ?>
          </div>

        </div>
      </div>

    </div>

  </div>
</div>
<script type='text/javascript'>
  jQuery(document).ready(function(){
    if (location.hash == ""){
      jQuery("#ogtab_documents").click();
    }
    if (location.hash == "#ogconversation"){
      showIframeRiot();
    }
    jQuery("#ogtab_conversation").click(showIframeRiot);
    function showIframeRiot(){
      if (document.getElementById("DivRiot")){
        jQuery('#DivRiot').remove();
        jQuery('#ogconversation').append('<iframe src="/sites/all/libraries/riot/index.html#/room/<?php echo $node->field_riot_identifier[LANGUAGE_NONE][0]['value']; ?>" id="gf_conversation" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe>');
      }
    }
  });

  Drupal.behaviors.gofast_node_actions_breadcrumb = {
        attach: function (context) {
          if(jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')){
            jQuery("#contextual-actions-loading").removeClass('not-processed');
            jQuery.get(location.origin + "/gofast/node-actions/<?php echo $nid; ?>", function( data ) {
              jQuery("#contextual-actions-loading").remove();
              jQuery("#breadcrumb-alt-actions").remove();
              jQuery(data).insertAfter("#breadcrumb-alt-lock");
              Drupal.attachBehaviors();
            });
            jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
            jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $nid; ?>", function( data ) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast").replaceWith(data);
              Drupal.attachBehaviors();
            });
            Drupal.behaviors.gofast_node_actions_breadcrumb = null;
          }
        }
      };
</script>
