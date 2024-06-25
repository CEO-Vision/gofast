<div id="file_browser_full_container" class="d-flex flex-column">
  <div id="file_browser_full_toolbar_container" class="mb-4">
    <div id="file_browser_full_toolbar" class="w-100">
      <div class="d-flex justify-content-between w-100">
        <div class="d-flex">
          <div class="btn-group">
            <button type="button" class="btn btn-white btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i id="file_browser_tooolbar_display_icon" class="fa fa-list" aria-hidden="true"></i> <?php echo t('Display', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
            <ul class="dropdown-menu text-truncate">
             <div class="navi navi-hover navi-link-rounded text-truncate min-w-250px">
              <li class="navi-item">
                  <a id="file_browser_tooolbar_display_details" class="navi-link">
                      <span class="navi-icon"><i class="fa fa-list" aria-hidden="true"></i></span>
                      <span class="navi-text"><?php echo t('Details', array(), array('context' => 'gofast:ajax_file_browser')); ?></span>
                  </a>
              </li>
              <li class="navi-item">
                  <a id="file_browser_tooolbar_display_icons" class="navi-link">
                      <span class="navi-icon"><i class="fa fa-picture-o" aria-hidden="true"></i></span>
                      <span class="navi-text"><?php echo t('Large icons', array(), array('context' => 'gofast:ajax_file_browser')); ?></span>
                  </a>
              </li>
             </div>
            </ul>
          </div>
          <div class="btn-group">
            <button type="button" id="file_browser_tooolbar_new_item" class="btn btn-white btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-plus" aria-hidden="true"></i> <?php echo t('New', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
            <ul class="dropdown-menu">
             <div class="navi navi-hover navi-link-rounded text-truncate min-w-250px">
              <li class="navi-item"><a id="file_browser_tooolbar_new_folder" class="navi-link">
                  <span class="navi-icon"><i class="fa fa-folder" aria-hidden="true"></i></span>
                  <span class="navi-text"><?php echo t('Folder', array(), array('context' => 'gofast:ajax_file_browser')); ?></span>
                </a></li>
              <li class="navi-item"><?php print gofast_dropdown_link(t('Folders from a template', array(), array('context' => 'gofast:ajax_file_browser')), '/modal/nojs/add_folder_template', 'file_browser_tooolbar_new_folder_template', 'ctools-use-modal add-folder-template', 'fa fa-folder', array('onClick' => "Gofast.ITHit.attachInputEvents()")); ?></li>
              <?php if (gofast_essential_is_essential()) { ?>
                <li class="navi-item"><?php print gofast_dropdown_link(t('Document(s)', array(), array('context' => 'gofast:ajax_file_browser')), '/modal/nojs/node/add/alfresco-item', 'add_alfresco_item', 'ctools-use-modal add-alfresco_item navi-link', 'fa fa-folder', array('onClick' => "Gofast.ITHit.attachInputEvents()")); ?></li>
              <?php } else { ?>
                <li class="navi-item"><a onclick="Gofast.ITHit.addAlfrescoItem(event);" id="file_browser_tooolbar_new_alfresco_item" class="center-block sidebar-items navi-link">
                    <span class="navi-icon"><i class="fa fa-file" aria-hidden="true"></i></span>
                    <span class="mb-0 navi-text"><?php echo t('Document(s)', array(), array('context' => 'gofast:ajax_file_browser')); ?></span>
                  </a></li>
                <li class="navi-item"><a onclick="Gofast.ITHit.addArticle(event);" id="file_browser_tooolbar_new_article" class="center-block sidebar-items navi-link">
                    <span class="navi-icon"><i class="far fa-ballot" aria-hidden="true"></i></span>
                    <span class="mb-0 navi-text"><?php echo t('Wiki Article', array(), array('context' => 'gofast:ajax_file_browser')); ?></span>
                  </a></li>
              <?php } ?>
             </div>
            </ul>
          </div>
          <div id="" class="btn-group">
            <button type="button" id="file_browser_tooolbar_manage" title="<?= t("Managing actions will not work if nothing is selected or if folders are selected.", array(), array("context" => "gofast:gofast_ajax_file_browser")) ?>" class="btn btn-disabled btn-sm dropdown-toggle" aria-haspopup="true"><i class="fa fa-gear" aria-hidden="true" disabled></i> <?php echo t('Manage', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
            <ul class="dropdown-menu">
             <div class="navi navi-hover navi-link-rounded text-truncate min-w-250px">
              <?php
              $attr = array(
                'onClick' => "Gofast.ITHit.bulkSelected(event)",
              );
              print '<li class="navi-item">' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal manage-taxonomy', 'fa fa-tags', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal add-locations', 'fa fa-share-alt n-color', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal manage-publications', 'fa fa-arrow-up', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal manage-mail-sharing', 'fa fa-envelope', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'archive_open_span', 'ctools-use-modal bulk-archive', 'fa fa-archive', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Add to cart', array(), array('context' => 'gofast')), '/modal/nojs/bulk_add_to_cart', 'cart_open_span', 'ctools-use-modal add_to_cart', 'fas fa-shopping-basket', $attr) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Delete', array(), array('context' => 'gofast')), '', 'cart_open_span', '', 'fa fa-trash', array('onClick' => "Gofast.ITHit.deleteSelected(event);")) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Download', array(), array('context' => 'gofast')), '', 'cart_open_span', '', 'fa fa-cloud-download', array('onClick' => "event.preventDefault();Gofast.ITHit.downloadSelected();")) . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal bulk_taxonomy manage-taxonomy gofast_display_none', 'fa fa-tags') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal bulk_add_locations add-locations gofast_display_none', 'fa fa-share-alt n-color') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal bulk_publications manage-publications gofast_display_none', 'fa fa-arrow-up') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal bulk_mail_sharing manage-mail-sharing gofast_display_none', 'fa fa-envelope') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'taxonomy_open_span', 'ctools-use-modal bulk_archive bulk-archive gofast_display_none', 'fa fa-archive') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Add to cart'), '/modal/nojs/bulk_add_to_cart', 'taxonomy_open_span', 'ctools-use-modal bulk_add_to_cart gofast_display_none', 'fas fa-shopping-basket') . '</li>';
              print '<li class="navi-item">' . gofast_dropdown_link(t('Compress'), '/modal/nojs/compress-files', 'taxonomy_open_span', 'ctools-use-modal compress_files gofast_display_none', 'fa fa-file-archive-o n-color') . '</li>';


              ?>
             </div>
            </ul>
          </div>
          <div id='file_browser_tooolbar_ccp' class="d-flex">
            <button title="<?php echo t('Copy'); ?>" id="file_browser_tooolbar_copy" type="button" class="btn btn-white btn-sm btn-icon" disabled><i class="fa fa-files-o" aria-hidden="true"></i></button>
            <button title="<?php echo t('Cut'); ?>" id="file_browser_tooolbar_cut" type="button" class="btn btn-white btn-sm btn-icon" disabled><i class="fa fa-scissors" aria-hidden="true"></i></button>
            <button title="<?php echo t('Paste'); ?>" id="file_browser_tooolbar_paste" type="button" class="btn btn-white btn-sm btn-icon" disabled><i class="fa fa-paste" aria-hidden="true"></i></button>
          </div>
          <div id='file_browser_tooolbar_cart' class="">
            <button title="<?php echo t('Add to cart'); ?>" id="file_browser_tooolbar_cart_button" type="button" class="btn btn-white btn-sm btn-icon" onclick="$('bulk_add_too_cart').click()" disabled><i class="fas fa-shopping-basket" aria-hidden="true"></i></button>
          </div>
          <?php print gofast_dropdown_link('', '/modal/nojs/bulk_add_to_cart', 'builk_open_span', 'ctools-use-modal bulk_add_to_cart gofast_display_none', 'fa fa-share-alt n-color'); ?>
          <?php if (gofast_essential_is_essential()) { ?>
            <div id="" class="btn-group">
              <button type="button" id="file_browser_tooolbar_contextual_actions" class="btn btn-white btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-bars" aria-hidden="true" disabled></i></button>
            </div>
          <?php } ?>
        </div>
        <div class="d-flex" >
          <div id="file_browser_full_toolbar_search" class="input-group">
            <div class="input-group-prepend"><span class="input-group-text"><i class="fas fa-filter icon-nm"></i></span></div>
            <input id="file_browser_full_toolbar_search_input" type="text" class="form-control form-control-sm m-0 h-100" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
          </div>
          <div id="file_browser_full_toolbar_info_icons">
            <!-- Loaded in navigation requests -->
          </div>
          <div id="file_browser_full_toolbar_refresh_group" class="btn-group">
            <button title="<?php echo t('Refresh'); ?>" id="file_browser_tooolbar_refresh" type="button" class="btn btn-white btn-sm btn-icon"><i class="fa fa-refresh" aria-hidden="true"></i></button>
          </div>
        </div>
      </div>
    </div>
  </div>
  <div class="d-flex flex-column">
    <div id="file_browser_tree_and_files" class="overflow-hidden">
      <?php if(!gofast_essential_is_essential()):?>
        <div id="file_browser_full_tree_container" class="pl-4 border border-1 bg-white min-h-150px">
          <div id="file_browser_full_tree" class="h-100">
            <ul id="file_browser_full_tree_element" class="ztree overflow-auto"></ul>
          </div>
        </div>
        <?php endif;?>
      <div id="file_browser_full_files_container" class="border border-1 bg-white min-h-150px">
        <div id="file_browser_full_files" class="h-100">
          <table id="file_browser_full_files_table" class="h-100 table overflow-hidden">
            <tr id="file_browser_full_files_header" class="w-100 d-flex h-35px" >
              <!-- We need to keep the elements on the same line to prevent unwanted spaces -->
              <th style="width:10%; display: inline-block;border-top:none;" class="pl-0" ><input id="gofastBrowserMagicCheckbox" type="checkbox"></th>
              <th id="name_header" class="file_table_header" style="width:45%; display: inline-block;border-top:none;"><?php echo t('Name', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
              <th id="size_header" class="file_table_header" style="width:10%; display: inline-block;border-top:none;"><?php echo t('Size', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
              <th id="type_header" class="file_table_header" style="width:10%; display: inline-block;border-top:none;"><?php echo t('Type', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
              <th id="modified_header" class="file_table_header" style="width:10%; display: inline-block;border-top:none;"><?php echo t('Modified', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
              <th id="info_header" class="file_table_header" style="width:10%; display: inline-block;border-top:none;"><?php echo t('Info', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
            </tr>
          </table>
        </div>
      </div>
    </div>
    <div id="file_browser_full_upload_container" class="border border-1 min-h-150px h-25">
      <div id="file_browser_full_upload" class="panel-body">
        <button id="file_browser_full_upload_button" type="button" style="height:20px;padding-left:5px;padding-right:2px;padding-top:0px;padding-bottom:22px;right:2.8%;margin-top:9px;position:absolute;z-index:2;display:none;" class="btn btn-danger" onclick="Gofast.ITHit.cancelAllUpload();">
          <i class="fa fa-times"></i>
        </button>
        <table id="file_browser_full_upload_table" class="table">
          <tr id="file_browser_full_upload_table_head" style="width:100%; display: inline-block;">
            <!-- We need to keep the elements on the same line to prevent unwanted spaces -->
            <th style="width:5%; display: inline-block;border-top:none;"></th>
            <th style="width:65%; display: inline-block;border-top:none;"><?php echo t('File', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
            <th style="width:10%; display: inline-block;border-top:none;"><?php echo t('Operation', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
            <th style="width:18%; display: inline-block;border-top:none;"><?php echo t('Progression', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
          </tr>
          <tr id="file_browser_full_upload_label_container" style="width: 100%; display: block;">
            <td id="file_browser_full_upload_label" style="width: 100%; display: inline-block; border-top: none; color: var(--gray-dark);" class="text-center py-1"><?= t("Click or drag your documents and folders here to share in", [], ["context" => "gofast:gofast_ajax_file_browser"]) . " " . urldecode($node->title) ?></td>
            <td id="file_browser_full_upload_sublabel" style="width: 100%; display: inline-block; border-top: none; color: var(--gray-dark);" class="text-center py-1"><small><em><?= t("Your files will be secured in a sovereign storage ruled only by french and european laws", [], ["context" => "gofast:gofast_ajax_file_browser"]) ?></em></small></td>
          </tr>
        </table>
        <input class="d-none" type="file" multiple id="file_browser_full_upload_table_file_input">
      </div>
    </div>
  </div>
</div>

<?php
if (!gofast_essential_is_essential()) {
  //Hide mobile browser
?>
  <style>
    #file_browser_mobile_container,
    #ithit-toggle {
      display: none;
    }

    .main-container {
      margin-left: auto !important;
    }
  </style>
<?php
}

if ($browser) {
?>
  <script>
    jQuery(document).ready(function() {
      //Trigger the file browser navigation when we are ready and connected
      function triggerNavigation() {
        if (typeof Gofast.ITHit === "undefined" || typeof Gofast.ITHit.Uploader === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
          setTimeout(triggerNavigation, 1000);
        } else { //Ready !
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
          if (typeof params.path !== "undefined") { //Path provided, navigate to path
            Gofast.ITHit.navigate(params.path, false, true, null, null, null, "backgroundNavigation");
          } else if(!isNaN(location.pathname.split("/")[2]) && Gofast._settings.isEssential){
            Gofast.Essential.navigateFileBrowser(location.pathname.split("/")[2])
          } else if (typeof Gofast.get("space") == "string") {
            Gofast.ITHit.navigate(Gofast.get("space"));
          } else { 
            Gofast.ITHit.navigate('/alfresco/webdav/Sites', false, true, null, null, null, "backgroundNavigation"); //No path provided, navigate to default path
          }
          //Attach events to the browser
          Gofast.ITHit.attachBrowserEvents();
          //Init queue mechanism if needed
          if (Gofast.ITHit.activeQueue === false) {
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

      //Allow to resize the ztree and file part of GFB horizontally
      jQuery("#file_browser_full_tree_container").resizable({
        alsoResize: "#file_browser_full_tree_element",
        handles: 'e',
        resize: function(e, ui) {
          //Also resize file block
          jQuery("#file_browser_full_files_container").width(jQuery("#file_browser_full_container").width() - jQuery("#file_browser_full_tree_container").width());
          jQuery("#file_browser_full_files_container table").width(jQuery("#file_browser_full_files_container").width() - 20);
          jQuery("#file_browser_full_files_container").css("margin-left", jQuery("#file_browser_full_tree_container").width());
        }
      });
    });
  </script>

<?php
} else if (!gofast_essential_is_essential()) {
?>
  <script>
    jQuery(document).ready(function() {
      //Allow to resize the files part of GFB vertically
      jQuery("#file_browser_full_files_container").resizable({
        alsoResize: "#file_browser_full_files_table, #file_browser_full_tree_container, #file_browser_full_tree_element, #file_browser_tree_and_files",
        handles: 's',
        resize: function(e, ui) {
          //Fix some jQuery UI calculation errors after resizing resizing
          jQuery("#file_browser_full_files_table").height(jQuery("#file_browser_full_files_container").height());
          jQuery("#file_browser_full_tree_container").height(jQuery("#file_browser_full_files_container").height());
          jQuery("#file_browser_full_tree_element").height(jQuery("#file_browser_full_files_container").height());
        }
      });

      //Allow to resize the upload part of GFB vertically
      jQuery("#file_browser_full_upload_container").resizable({
        alsoResize: "#file_browser_full_upload_table",
        handles: 's',
        resize: function(e, ui) {
          //Fix some jQuery UI calculation errors after resizing resizing
          jQuery("#file_browser_full_upload_table").height(jQuery("#file_browser_full_upload_container").height());
        }
      });

      //Allow to resize the ztree and file part of GFB horizontally
      jQuery("#file_browser_full_tree_container").resizable({
        alsoResize: "#file_browser_full_tree_element",
        handles: 'e',
        resize: function(e, ui) {
          //Also resize file block
          jQuery("#file_browser_full_files_container").width(jQuery("#file_browser_full_container").width() - jQuery("#file_browser_full_tree_container").width());
          jQuery("#file_browser_full_files_container table").width(jQuery("#file_browser_full_files_container").width() - 20);
          jQuery("#file_browser_full_files_container").css("margin-left", jQuery("#file_browser_full_tree_container").width());
        }
      });
    });
  </script>
<?php
}
?>

<script>
  jQuery(document).ready(function() {
    // we make sure the filebrowser dimensions are correctly set here so it's correctly displayed even if the document is already ready (ajax-load)
    function triggerResetFullBrowserSize() {
      if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false) {
        setTimeout(triggerResetFullBrowserSize, 1000);
      } else {
        Gofast.ITHit.reset_full_browser_size();
      }
    }
    triggerResetFullBrowserSize();
    <?php
    $is_new = abs($node->created - time()) < 30;
    // node has succesfully been created but is still being generated on the alfresco store
    if ($is_new && $_POST['gofast_og_wrong_path']) {
      $node_path = gofast_cmis_space_get_webdav_path_node_page($node->nid);
    ?>
      // display a fake node waiting for the newly created group to be available
      var nodePath = "<?= $node_path ?>".trim();
      var nodeName = "<?= gofast_get_node_title($node->nid) ?>".trim();
      var nodeName = nodeName.startsWith("_") ? nodeName : "_" + nodeName;
      var nodeId = "<?= $node->nid ?>".trim();
      Gofast.temporarySpaceDisplay(nodePath, nodeName, nodeId);
    <?php
    }
    ?>
  });
</script>
