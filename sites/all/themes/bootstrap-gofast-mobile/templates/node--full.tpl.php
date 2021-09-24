<div id="fullscreen-node">
  <div id="tempContainerItHit"></div>
  <?php
  $detect = new Mobile_Detect;
  if (user_is_logged_in()) {
    print(theme('ajax_file_browser_mobile'));
    if ($detect->isMobile() || $detect->isTablet()) {
      print theme('gofast_mobile_panel', array('node' => $node));
    }
  }
  ?>

  <div class="Node conteiner">
    <div class="row">
      <div id="node-<?php print $node->nid; ?>" class="col-sm-9 <?php print $classes; ?> clearfix" <?php print $attributes; ?>>
        <div class="gofast-header">
          <?php if (isset($content['vud_node_widget_display'])) : ?>
            <div style="float:right;">
              <?php print $content['vud_node_widget_display']['#value']; ?>
            </div>
          <?php endif; ?>
        </div>
        <div id="breadcrumb-container"></div>
        <script>
          jQuery.get('/gofast/node-breadcrumb/' + <?php echo $node->nid; ?>, function(data) {
            jQuery("#breadcrumb-container").html(data);
            <?php if(gofast_mobile_is_mobile_domain() && $detect->isMobile()){ ?>
              jQuery("#breadcrumb-container").find(".breadcrumb > div > b").text("<?php echo $node->title; ?>")
            <?php } ?>
            jQuery(".breadcrumb-gofast").css("width", "100%");
            jQuery("#breadcrumb-container-buton-mobile").css("top", "5px");

            // on mobile move alert and info div inside #breadcrumb-container to have a correct buton show
            if (jQuery(".alert.alert-block.alert-dismissible.alert-warning.messages.warning").length) {
              jQuery(".alert.alert-block.alert-dismissible.alert-warning.messages.warning").appendTo("#breadcrumb-container");
            }
            if (jQuery(".alert.alert-block.alert-dismissible.alert-info.messages.info").length) {
              jQuery(".alert.alert-block.alert-dismissible.alert-info.messages.info").appendTo("#breadcrumb-container");
            }
          });
        </script>
        <div class="content well well-sm" <?php print $content_attributes; ?>>

          <?php

          // We hide the comments and links now so that we can render them later.
          hide($content['comments']);
          hide($content['links']);

          print "<script>jQuery(document).ready(function(){  setTimeout(function(){
                                               Gofast.loadcomments(" . $node->nid . ");
                                              }, 2000);});</script>";

          if ($node->type === 'alfresco_item') {
              //Retrieve saved documents form configuration
            $default_documents_form_configuration = array(
                'ticket' => 1,
                'ticket_path_length' => 200,
                'gofast_onlyoffice_ro_preview' => FALSE,
            );
            $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
            if($node->status == 1 && $documents_form_defaults['gofast_onlyoffice_ro_preview'] && in_array(strtolower(gofast_cmis_node_get_extension($node)), gofast_onlyoffice_viewable_document_extensions()) && empty($node->field_external_page_url['und'][0]['value'])){ 
                $final_content_with_iframe = gofast_onlyoffice_editor($node, TRUE);
            }else{
                $final_content_with_iframe = gofast_cmis_replace_iframe(render($content), $node);
            }

            if($final_content_with_iframe == "RELOAD"){
                print "<script>window.location.reload();</script>";
            }else{
              print $final_content_with_iframe;
            }
          } elseif ($node->type === 'conference') {
            $conference_content = $node->body[LANGUAGE_NONE][0]['value'];
            $gofast_participants = isset($node->field_existing_participants[LANGUAGE_NONE]) ? gofast_conference_build_gofast_participants_email_list($node->field_existing_participants[LANGUAGE_NONE]) : t('No Gofast\'s participants', array(), array('context' => 'gofast:gofast_conference'));
            $other_paticipants = isset($node->field_participants[LANGUAGE_NONE]) ? gofast_conference_build_other_participants_email_list($node->field_participants[LANGUAGE_NONE]) : t('No others participants', array(), array('context' => 'gofast:gofast_conference'));

            // TODO : Try to convert to the participant's timezone (Not easy)
            $conference_datetime = format_date(strtotime($node->field_date[LANGUAGE_NONE][0]['value']), 'medium', '', date_default_timezone_get());
            $owner = user_load($node->uid);
            $conference_owner = theme('user_picture', array('account' => $owner)) . ' ' . $owner->mail;

            if (isset($node->field_timestamp_target_link[LANGUAGE_NONE]) && count($node->field_timestamp_target_link[LANGUAGE_NONE]) > 0) {
              $conference_documents = $node->field_timestamp_target_link[LANGUAGE_NONE];
            }

            $body = theme('gofast_conference_body_mobile', array(
              'conference_url' => $conference_url,
              'gofast_participants' => $gofast_participants,
              'other_participants' => $other_paticipants,
              'conference_datetime' => $conference_datetime,
              'conference_content' => $conference_content,
              'conference_owner' => $conference_owner,
              'conference_documents' => $conference_documents,
            ));

            print $body;
          } else {
            print render($content);
          }
          ?>
        </div>
        <div id="comments-container">
          <?php
          // Si pas de commentaires sur le noeud, on affiche quand meme la div du
          // container des commentaires, pour pouvoir la mettre à jour dynamiquement
          // en JS.
          if (count($content['comments']) === 1) :
            print '<div id="comments" class="comment-wrapper">';
          endif;

          // If dont comment when ther is no comment Metatadata Bug appears
          //print render($content['comments']);

          if (count($content['comments']) === 1) :
            print '</div>';
          endif;
          ?>
        </div>
      </div>
      <?php if (!$detect->isMobile() && !$detect->isTablet()) { ?>
        <div class="col-sm-3">
          <?php print theme('gofast_mobile_panel', array('node' => $node)); ?>
        </div>
      <?php } ?>
    </div>
  </div>
</div>
</div>

<script>
  <?php
  if ($node->type === "alfresco_item") {
  ?>
    //Triger the mobile file browser navigation when we are ready and connected
    function triggerMobileNavigation() {
      if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false || typeof Gofast.ITHitMobile === "undefined") { //Not yet ready
        if (typeof Drupal.settings.pass_reset !== "undefined") {
          //We are in password recovery mode, cancel action !
          jQuery("#file_browser_mobile_container").remove();
          jQuery("#ithit-toggle").remove();
          return;
        }
        setTimeout(triggerMobileNavigation, 1000);
      } else { //Ready !
        Gofast.ITHitMobile.mobileVersion = true;
        if (typeof Drupal.settings.pass_reset !== "undefined") {
          //We are in password recovery mode, cancel action !
          jQuery("#file_browser_mobile_container").remove();
          jQuery("#ithit-toggle").remove();
          return;
        }
        if (!Gofast.mobileNavigationHandled) { //Navigation hasn't already been handled (by node themes for exemple)
          Gofast.ITHitMobile.selectedTitle = "<?php print $node->title; ?>";
          Gofast.ITHitMobile.navigate("<?php print gofast_cmis_get_first_available_location($node); ?>");
        }
        //Attach browser events
        Gofast.ITHitMobile.attachBrowserEvents();
        //Set margin to main container if needed
        if (Gofast.getCookie('mobile_browser_toggle') === "shown" && parseInt(jQuery('.main-container').css('margin-left')) <= 250 && parseInt(jQuery('.main-container').position().left) <= 250) {
          jQuery(".main-container").css('margin-left', '250px');
        }
      }
    }
    triggerMobileNavigation();
  <?php  } ?>

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
</script>
