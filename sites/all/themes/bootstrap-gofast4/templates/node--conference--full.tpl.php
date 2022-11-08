<div id="fullscreen-node">
  <div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

    <div class="gofast-header">
      <?php if (isset($content['vud_node_widget_display'])) : ?>
        <div style="float:right;">
          <?php print $content['vud_node_widget_display']['#value']; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    hide($content['links']);
    ?>
    <?php if(isset ($conference_content) && $conference_content !== ""){ ?>
      <div class="panel panel-info">
        <div class="panel-heading">
          <h3 class="panel-title"><?php print t('Informations') ?></h3>
        </div>
        <div class="panel-body">
          <?php print $conference_content ?>
        </div>
      </div>
    <?php } ?>
    <?php if(isset ($gofast_documents_list) && $gofast_documents_list !== ""){ ?>
      <div class="panel panel-info">
        <div class="panel-heading">
          <h3 class="panel-title"><?php print t('Documents') ?></h3>
        </div>
        <div class="panel-body">
          <?php print $gofast_documents_list; ?>
        </div>
      </div>
    <?php }?>
    <?php if(isset ($gofast_folders_list) && $gofast_folders_list !== ""){ ?>
      <div class="panel panel-info">
        <div class="panel-heading">
          <h3 class="panel-title"><?php print t('Linked folders') ?></h3>
        </div>
        <div class="panel-body">
          <?php print $gofast_folders_list; ?>
        </div>
      </div>
    <?php }?>
    <div class="panel panel-info">
      <div class="panel-heading">
        <h3 class="panel-title"><?php print t('Participants') ?></h3>
      </div>
      <div class="panel-body">
        <table width="100%">
          <tr>
            <td width="50%">
              <div><strong><?php print t('Gofast participants') ?></strong></div>
            </td>
            <td width="50%">
              <div><strong><?php print t('Other participants') ?></strong></div>
            </td>
          </tr>
          <tr>
            <td width="50%">
              <div>         
                  <?php print $gofast_participants_email_list ?>
                  <div style='clear:both;'></div>
              </div>
            </td>
            <td width="50%">
              <div>
                <ul class="list-group">
                  <?php print $other_participants_email_list ?>
                </ul>
                <div style='clear:both;'></div>
              </div>
            </td>
          </tr>
          <tr>
            <td width="50%">
              <div><strong><?php print t('Meeting Owner'); ?></strong></div>
            </td>
            <td width="50%">
              <div><strong><?php print t('Meeting Date');  ?></strong></div>
            </td>
          </tr>
          <tr>
            <td width="50%">
              <div>
                <?php print $conference_owner; ?>
                <div style='clear:both;'></div>
              </div>
            </td>
            <td width="50%">
              <div>
                <?php print $conference_datetime; ?><br /><?php print $conference_end_datetime; ?>
                <div style='clear:both;'></div>
              </div>
            </td>
          </tr>
        </table>
      </div>
    </div>
    <div class="panel panel-success" id="panel_conference_url">
      <div class="panel-heading">
        <h3 class="panel-title"><?php print t('Meeting actions') ?></h3>
      </div>
      <div class="panel-body">
        <div id="conference-links" class="btn-group" role="group">
          <a target="_blank" href="<?php print $conference_url_external ?>" id="conference-pc-link-start" type="button" class="btn btn-success"><?php print t('Start conference') ?></a>
          <button id="conference-pc-link-display" type="button" class="btn btn-default"><?php print t('Display PC link') ?></button>
          <button id="conference-pc-link-copy" type="button" class="btn btn-info"><?php print t('Copy link to clipboard') ?></button>
        </div>
          <div style='margin-top:10px;text-align:center;'><a href="<?php print str_replace(CONFERENCE_URL, "https://meet.jit.si", $conference_url_external); ?>" target="_blank"><?php print t("If you find any problems, all participants can try to use this link (shared Jitsi SaaS)"); ?></a></div>
        <div id="conference-pc-link">
          <a id="conference-pc-link-raw" target="_blank" href="<?php print $conference_url_external ?>"><?php print $conference_url_external ?></a>
        </div>
      </div>
    </div>
    <div id="report_detection_media">
      <?php
        if ($report) {
          print $report;
        }
      ?>
    </div>
    <div id="comments-container">
      <div>
        <?php
// Si pas de commentaires sur le noeud, on affiche quand meme la div du 
// container des commentaires, pour pouvoir la mettre à jour dynamiquement
// en JS.
        if (count($content['comments']) === 1) :
          print '<div id="comments" class="comment-wrapper">';
        endif;

        print render($content['comments']);

        if (count($content['comments']) === 1) {
          print '</div>';
        }
        ?>
      </div>
    </div>
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
              Drupal.attachBehaviors();
            });
            jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
            jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $nid; ?>", function( data ) {
              jQuery(".loader-breadcrumb").remove();
              jQuery(".breadcrumb-gofast").replaceWith(data);
            });
          }
        }
      };
</script>