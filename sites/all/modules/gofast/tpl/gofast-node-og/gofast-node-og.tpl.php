<?php $detect = new Mobile_Detect(); ?>

<div id="node-<?php print $node->nid; ?>" class="essentialFileBrowser mainContent GofastNodeOg gofast-og-page <?php print $classes; ?> <?php print gofast_essential_is_essential() ? 'd-flex' : '';?>" <?php print $attributes; ?>>
    <?php if($user->field_atatus_tracking[LANGUAGE_NONE]['0']['value'] == 2) : ?>
        <script type="text/javascript">atatus.setTags(['space']);</script>
    <?php endif; ?>
  <?php if(gofast_essential_is_essential() && !gofast_mobile_is_phone()): ?>
    <div id="gofast_file_browser_side_content" class="gofast-file-browser-side-content-tabs d-flex flex-column h-100 bg-white" style="min-width: 320px;">
      <ul class="nav nav-tabs nav-fill" role="tablist">
        <li class="nav-item" data-title="<?php print t('Collaborative Spaces') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
          <a class="nav-link cursor-pointer gofast-file-browser-side-content-tab d-flex justify-content-center" id="nav_mobile_file_browser_full_tree_container" data-toggle="tab" data-target="#mobile_file_browser_full_tree_container" role="tab" aria-selected="true">
            <div class="nav-icon"><i class="fas fa-sitemap n-color"></i></div>
          </a>
        </li>
        <li class="nav-item" data-title="<?php print t('Wikis') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
          <a class="nav-link cursor-pointer gofast-file-browser-side-content-tab d-flex justify-content-center" id="nav_mobile_file_browser_wiki_container" data-toggle="tab" data-target="#mobile_file_browser_wiki_container" role="tab" aria-selected="true">
            <div class="nav-icon"><i class="fad fa-book"></i></div>
          </a>
        </li>
        <li class="nav-item" data-title="<?php print t('Forums') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
          <a class="nav-link cursor-pointer gofast-file-browser-side-content-tab d-flex justify-content-center" id="nav_mobile_file_browser_forum_container" data-toggle="tab" data-target="#mobile_file_browser_forum_container" role="tab" aria-selected="true">
            <div class="nav-icon"><i class="fad fa-comments"></i></div>
          </a>
        </li>
      </ul>
      <div class="tab-content h-100 border border-1 card card-custom">
        <div id="mobile_file_browser_full_tree_container" class="tab-pane pl-4 min-h-150px h-100 position-relative">
          <div id="file_browser_full_tree" class="">
                <ul id="file_browser_full_tree_element" class="ztree overflow-auto h-100"></ul>
          </div>
        </div>
        <div id="mobile_file_browser_wiki_container" class="tab-pane pl-4 min-h-150px h-100 position-relative">
          <div id="file_browser_wiki" class="d-flex overflow-auto max-h-100">
          <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl position-absolute" style="top: calc(50% - 6em); left: calc(50% - 2em);"></div>
          </div>
        </div>
        <div id="mobile_file_browser_forum_container" class="tab-pane pl-4 min-h-150px h-100 position-relative">
          <div id="file_browser_forum" class="d-flex max-h-100">
          <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl position-absolute" style="top: calc(50% - 6em); left: calc(50% - 2em);"></div>
          </div>
        </div>
      </div>
    </div>
    <?php endif; ?>
  <div class="card card-stretch GofastNodeOg__container <?php print gofast_essential_is_essential() ? 'w-100' : 'card-custom';?>" <?php print $content_attributes; ?>>
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
    <?php if(!gofast_essential_is_essential()) :?>
    <div class="card-header h-50px min-h-50px border border-0 flex-nowrap">
      <?php print theme('gofast_menu_header_subheader', array('node' => $node)); ?>
    </div>
    <?php endif;?>

    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column
        <?php if ($hidden_filebrowser) { print 'd-none';} ?>" 
        <?= gofast_essential_is_essential() ? 'id="fileBrowserLayer"' : "" ?>>
        
        <?php print theme('essential_node_og_file_browser_tab_menu',
          array('menus' => $menus, 'hidden_filebrowser' => $hidden_filebrowser))
        ?>
        <?php if (gofast_essential_is_essential()): ?>
            <?php print theme('essential_file_browser_history', 
            array('hidden_filebrowser' => $hidden_filebrowser,
            'hasEssentialSpaceActions' => $hasEssentialSpaceActions, 
            '$selectedPath' => $selectedPath)) ?>    
            <?php endif; ?>
            <?php print theme('essential_node_og_file_browser_content_panel',
          array('links' => $links, 'hidden_filebrowser' => $hidden_filebrowser)) ?>
    </div>
  </div>
<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/apexcharts.js" ?>"></script>
<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/gofast_stats.js" ?>"></script>
<script type='text/javascript'>
  jQuery(document).ready(function() {
    for(let i=1; i <= 3; i++){
      $('#gofast_file_browser_side_content > ul > li:nth-child('+ i +')').tooltip();
    }
    //Attach behaviors after a clic on the "Documents" tab once the file browser is visible - GOFAST-7633
    if(typeof Gofast.behaviors_browser_interval === "object"){
      clearInterval(Gofast.behaviors_browser_interval);
    }

    jQuery("#ogtab_documents").click(function(){
      Gofast.behaviors_browser_interval = setInterval(function(){
        if(Gofast._settings.isEssential && !Gofast._settings.isMobileDevice){
          if(!$("#ogdocuments").hasClass("processed")){
            $("#ogdocuments").addClass("processed")
          } else {
            return;
          }
        }
        if(jQuery("#ogdocuments").css("display") === "block"){
          clearInterval(Gofast.behaviors_browser_interval);
          Drupal.attachBehaviors();
          Gofast.ITHit.reset_full_browser_size();
        }
      }, 500);
    });

    if($("#nav_mobile_file_browser_full_tree_container").length) {
      // no matter the hash, we wan't to display by default the ztree on the left
      $("#nav_mobile_file_browser_full_tree_container").tab("show");
      $("#nav_mobile_file_browser_wiki_container:not(.processed)").on("show.bs.tab", function() {
        $(this).addClass("processed");
        if(!$("#mobile_file_browser_wiki_container").find(".spinner").length) {
          return;
        }
        $.get(window.origin + "/gofast/book/explorer?widget=true&has_links=true").done(function(data){
          $("#file_browser_wiki").html(data);
          Drupal.attachBehaviors()
          Gofast.selectCurrentWikiArticle()
        });
      });

      $("#nav_mobile_file_browser_forum_container:not(.processed)").on("show.bs.tab", function() {

        if(!$("#mobile_file_browser_forum_container").find(".spinner").length) {
          return;
        }
        $.get("/essential/get_node_content_part/forumTab/0").done(function(data){
          $("#file_browser_forum").html(data);
        });
      })
    }

    if ((!$(".GofastNode").length && location.hash == "") || location.hash.startsWith("#ogdocuments")) {
      jQuery("#ogtab_documents").click();
    }
    if (location.hash.startsWith("#oghome")) {
      jQuery("#ogtab_home").click();
    }

    if(Gofast._settings.isEssential){
      //Initialize history selector
      Gofast.ITHit.initEssentialHistorySelector();
    }
  });

  Drupal.behaviors.gofast_node_actions_breadcrumb = {
    attach: function(context) {
      if (jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')) {
        jQuery("#contextual-actions-loading").removeClass('not-processed');
        var nid = <?= $node->nid ?>;
        if(Gofast._settings.isEssential){
          nid = Gofast.get('node').id;
        }
        jQuery.post(location.origin + "/gofast/node-actions/"+nid, {fromBrowser: location.hash == "" || location.hash.startsWith("#ogdocuments")}, function(data) {
          jQuery("#contextual-actions-loading").replaceWith(data);
          Drupal.attachBehaviors();
        });
        if((Gofast._settings.isEssential && <?= $node->type != "article" ?> == "true") || !Gofast._settings.isEssential){
          jQuery(".breadcrumb-gofast").append("<div class='loader-breadcrumb'></div>");
          jQuery.get(location.origin + "/gofast/node-breadcrumb/<?php echo $node->nid; ?>", function(data) {
            jQuery(".loader-breadcrumb").remove();
            jQuery(".breadcrumb-gofast").replaceWith(data);
            Drupal.attachBehaviors();
          });
        }
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
<style>
  #essential-actions > div > div.dropdown.ml-3{
    right: 8px!important;
    top: 4rem!important;
  }

  @media screen and (max-width: 1024px) {
    #gofastBrowserContentPanel > div.gofast-node-actions.open > div{
      max-height: 500px;
      overflow-y: scroll;
    }
  }
</style>
</div>

