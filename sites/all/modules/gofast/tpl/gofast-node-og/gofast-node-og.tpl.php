<script type="text/javascript">atatus.setTags(['space']);</script >
<div id="node-<?php print $node->nid; ?>" class="mainContent GofastNodeOg gofast-og-page <?php print $classes; ?> " <?php print $attributes; ?>>
  <div class="card card-custom card-stretch GofastNodeOg__container" <?php print $content_attributes; ?>>
    <?php if (gofast_group_is_archive($node)) { ?>
      <div class="alert alert-custom alert-notice alert-light-warning">
          <div class="alert-icon"><i class="flaticon-warning"></i></div>
          <div class="alert-text"><?php print t('This space is archived', array(), array('context' => 'gofast')) ?></div>
          <div class="alert-close">
            <button type="button" class="close" data-dismiss="alert" aria-label="Close">
              <span aria-hidden="true"><i class="ki ki-close"></i></span>
            </button>
          </div>
      </div> 
    <?php } ?>
    <div class="card-header h-50px min-h-50px border border-0 flex-nowrap">
      <?php print theme('gofast_menu_header_subheader', array('node' => $node)); ?>
    </div>
    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column">
      <div class="w-100 px-2">
          <?php foreach ($menus as $name => $menu) : ?>
          <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap <?php print $name ?>" id="gofastBrowserNavTabs" role="tablist">
            <?php foreach ($menu['links'] as $link) : ?>
              <?php if($link['dropdown']) : ?>
                    <li class="nav-item dropdown">
                        <a class="nav-link px-2 d-flex justify-content-center dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
                        <span class="nav-icon">
                        <i class="<?php print $link['icon'] ?>"></i>
                        </span>
                            <span class="nav-text"><?php print $link['label']; ?></span>
                        </a>
                        <div class="dropdown-menu">
                          <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                              <a class="dropdown-item" data-toggle="tab" id="<?php print $dropdown_link['id']; ?>" aria-controls="<?php print $dropdown_link['href']; ?>" href="#<?php print $dropdown_link['href']; ?>">
                                <span class="navi-icon pr-2">
                                    <i class="<?php print $dropdown_link['icon'] ?>"></i>
                                </span>
                                  <span class="navi-text"><?php print $dropdown_link['label']; ?></span>
                              </a>
                          <?php endforeach; ?>
                        </div>
                    </li>
              <?php else : ?>
                    <li class="nav-item <?php if($link['dropdown']){ echo 'dropdown'; } ?><?php if($link['disabled'] == true){ echo 'disabled'; } ?>">
                        <a class="nav-link px-2 d-flex justify-content-center <?php if($link['disabled'] == true){ echo 'disabled'; } ?>" id="<?php print $link['id']; ?>" aria-controls="<?php print $link['href']; ?>" data-toggle="tab" href="#<?php print $link['href']; ?>">
                        <span class="nav-icon">
                        <i class="<?php print $link['icon'] ?>"></i>
                        </span>
                            <span class="nav-text"><?php print $link['label']; ?></span>
                        </a>
                    </li>
              <?php endif; ?>
            <?php endforeach; ?>
          </ul>
          <?php endforeach; ?>
      </div>
      <div class="h-100 w-100 overflow-hidden" >
        <div class="tab-content h-100 w-100" id="gofastBrowserContentPanel">
          <?php foreach ($links as $link) : ?>
            <?php if($link['dropdown']) : ?>
                <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                    <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="<?php print $dropdown_link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $dropdown_link['id']; ?>">
                        <?php print $dropdown_link['content']; ?>
                    </div>
                <?php endforeach; ?>
            <?php else : ?>
                <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="<?php print $link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $link['id']; ?>">
                    <?php print $link['content']; ?>
                </div>
            <?php endif; ?>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </div>
</div>

<script type='text/javascript'>  
  jQuery(document).ready(function() {
    //Attach behaviors after a clic on the "Documents" tab once the file browser is visible - GOFAST-7633
    if(typeof Gofast.behaviors_browser_interval === "object"){
      clearInterval(Gofast.behaviors_browser_interval);
    }
    
    jQuery("#ogtab_documents").click(function(){
      Gofast.behaviors_browser_interval = setInterval(function(){
        if(jQuery("#ogdocuments").css("display") === "block"){
          clearInterval(Gofast.behaviors_browser_interval);
          Drupal.attachBehaviors();
          Gofast.ITHit.reset_full_browser_size();
        }
      }, 500);
    });
    
    if (location.hash == "" || location.hash.startsWith("#ogdocuments")) {
      jQuery("#ogtab_documents").click();
    }
    if (location.hash.startsWith("#ogconversation")) {
      showIframeRiot();
    }
    if (location.hash.startsWith("#oghome")) {
      jQuery("#ogtab_home").click();
    }
    jQuery("#ogtab_conversation").click(showIframeRiot);

    function showIframeRiot() {
      if (document.getElementById("DivRiot")) {
        jQuery('#DivRiot').remove();
        jQuery('#ogconversation').append('<iframe src="/sites/all/libraries/riot/index.html#/room/<?php echo $node->field_riot_identifier[LANGUAGE_NONE][0]['value']; ?>" id="gf_conversation" style="width:100%;height: calc(100vh - 180px);border:none;"></iframe>');
      }
    }
  });

  Drupal.behaviors.gofast_node_actions_breadcrumb = {
    attach: function(context) {
      if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
        jQuery("#contextual-actions-loading").removeClass('not-processed');
        jQuery.post(location.origin + "/gofast/node-actions/<?php echo $node->nid; ?>", {fromBrowser: location.hash == "" || location.hash.startsWith("#ogdocuments")}, function(data) {
          jQuery("#contextual-actions-loading").replaceWith(data);
          Drupal.attachBehaviors();
        });
        jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
        jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $node->nid; ?>", function(data) {
          jQuery(".loader-breadcrumb").remove();
          jQuery(".breadcrumb-gofast").replaceWith(data);
          Drupal.attachBehaviors();
        });
        Drupal.behaviors.gofast_node_actions_breadcrumb = null;
      }
    }
  };

  Drupal.behaviors.gofast_node_content_low_width = {
      attach: function() {
          if ((jQuery(window).width() < 765) && jQuery('.gofast-node-og').length)  {
            jQuery('.gofast-content').css('grid-template-columns', '1fr');
          }
      }
  }
</script>
