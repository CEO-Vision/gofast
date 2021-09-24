<div id="file_browser_full_container">
  <div id="file_browser_full_toolbar_container" class="panel panel-default">
    <div id="file_browser_full_toolbar" class="panel-body">
      <div class="btn-group">
        <button type="button" class="btn btn-default btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i id="file_browser_tooolbar_display_icon" class="fa fa-list" aria-hidden="true"></i> <?php echo t('Display', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
        <ul class="dropdown-menu">
          <li><a id="file_browser_tooolbar_display_details" class="btn btn-sm"><i class="fa fa-list" aria-hidden="true"></i><?php echo t('Details', array(), array('context' => 'gofast:ajax_file_browser')); ?></a></li>
          <li><a id="file_browser_tooolbar_display_icons" class="btn btn-sm"><i class="fa fa-picture-o" aria-hidden="true"></i><?php echo t('Large icons', array(), array('context' => 'gofast:ajax_file_browser')); ?></a></li>
        </ul>
      </div>
      <div class="btn-group">
        <button type="button" id="file_browser_tooolbar_new_item" class="btn btn-default btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-plus" aria-hidden="true"></i> <?php echo t('New', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
        <ul class="dropdown-menu" style="width: 190px;">
          <li><a id="file_browser_tooolbar_new_folder" class="btn btn-sm center-block sidebar-items">
              <div class="list-items-icons"><i class="fa fa-folder" aria-hidden="true" style=" padding-right: 5px;"></i>
                <?php echo t('Folder', array(), array('context' => 'gofast:ajax_file_browser')); ?>
              </div>
            </a></li>
          <li><?php print gofast_dropdown_link(t('Folders from a template', array(), array('context' => 'gofast:ajax_file_browser')), '/modal/nojs/add_folder_template', 'file_browser_tooolbar_new_folder_template', 'ctools-use-modal add-folder-template', 'fa fa-file', array('onClick' => "Gofast.ITHit.attachInputEvents()")); ?></li>
          <?php if (gofast_mobile_is_mobile_domain()) { ?>
            <li><?php print gofast_dropdown_link(t('Document(s)', array(), array('context' => 'gofast:ajax_file_browser')), '/modal/nojs/node/add/alfresco-item', 'add_alfresco_item', 'ctools-use-modal add-alfresco_item', 'fa fa-file', array('onClick' => "Gofast.ITHit.attachInputEvents()")); ?></li>
          <?php } else { ?>
            <li><a onclick="Gofast.ITHit.addAlfrescoItem(event);" id="file_browser_tooolbar_new_alfresco_item" class="btn btn-sm center-block sidebar-items">
                <div class="list-items-icons"><i class="fa fa-file" aria-hidden="true" style=" padding-right: 5px;"></i>
                  <?php echo t('Document(s)', array(), array('context' => 'gofast:ajax_file_browser')); ?></div></a></li>
          <?php } ?>
        </ul>
      </div>
      <div id="" class="btn-group">
        <button type="button" id="file_browser_tooolbar_manage" class="btn btn-default btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true"><i class="fa fa-gear" aria-hidden="true" disabled></i> <?php echo t('Manage', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
        <ul class="dropdown-menu" style="width: 235px;">
          <?php
          $attr = array(
            'onClick' => "Gofast.ITHit.bulkSelected(event)",
          );
          print '<li>' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal manage-taxonomy', 'fa fa-tags', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal add-locations', 'fa fa-share-alt', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal manage-publications', 'fa fa-arrow-up', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal manage-mail-sharing', 'fa fa-envelope', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'archive_open_span', 'ctools-use-modal bulk-archive', 'fa fa-archive', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Add to cart', array(), array('context' => 'gofast')), '/modal/nojs/bulk_add_to_cart', 'cart_open_span', 'ctools-use-modal add_to_cart', 'fa fa-cart-plus', $attr) . '</li>';
          print '<li>' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal bulk_taxonomy manage-taxonomy gofast_display_none', 'fa fa-tags') . '</li>';
          print '<li>' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal bulk_add_locations add-locations gofast_display_none', 'fa fa-share-alt') . '</li>';
          print '<li>' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal bulk_publications manage-publications gofast_display_none', 'fa fa-arrow-up') . '</li>';
          print '<li>' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal bulk_mail_sharing manage-mail-sharing gofast_display_none', 'fa fa-envelope') . '</li>';
          print '<li>' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'taxonomy_open_span', 'ctools-use-modal bulk_archive bulk-archive gofast_display_none', 'fa fa-archive') . '</li>';
          ?>
        </ul>
      </div>
      <div id='file_browser_tooolbar_ccp' class="btn-group">
        <button title="<?php echo t('Copy'); ?>" id="file_browser_tooolbar_copy" type="button" class="btn btn-default btn-sm dropdown-toggle" disabled><i class="fa fa-files-o" aria-hidden="true"></i></button>
        <button title="<?php echo t('Cut'); ?>" id="file_browser_tooolbar_cut" type="button" class="btn btn-default btn-sm dropdown-toggle" disabled><i class="fa fa-scissors" aria-hidden="true"></i></button>
        <button title="<?php echo t('Paste'); ?>" id="file_browser_tooolbar_paste" type="button" class="btn btn-default btn-sm dropdown-toggle" disabled><i class="fa fa-clipboard" aria-hidden="true"></i></button>
      </div>
      <div id='file_browser_tooolbar_cart' class="btn-group">
        <button title="<?php echo t('Add to cart'); ?>" id="file_browser_tooolbar_cart_button" type="button" class="btn btn-default btn-sm dropdown-toggle" disabled><i class="fa fa-cart-plus" aria-hidden="true"></i></button>
      </div>
      <?php print gofast_dropdown_link('', '/modal/nojs/bulk_add_to_cart', 'builk_open_span', 'ctools-use-modal bulk_add_to_cart gofast_display_none', 'fa fa-share-alt'); ?>
      <?php if (gofast_mobile_is_mobile_domain()) { ?>
        <div id="" class="btn-group">
          <button type="button" id="file_browser_tooolbar_contextual_actions" class="btn btn-default btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false"><i class="fa fa-bars" aria-hidden="true" disabled></i></button>
        </div>
      <?php } ?>
      <div id="file_browser_full_toolbar_refresh_group" class="btn-group">
        <button title="<?php echo t('Refresh'); ?>" id="file_browser_tooolbar_refresh" type="button" class="btn btn-default btn-sm dropdown-toggle"><i class="fa fa-refresh" aria-hidden="true"></i></button>
      </div>
      <div id="file_browser_full_toolbar_search" class="input-group input-group-sm">
        <span class="input-group-addon" id="sizing-addon3"><span class="icon glyphicon glyphicon-search" aria-hidden="true"></span></span>
        <input id="file_browser_full_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
      </div>
      <div id="file_browser_full_toolbar_info_icons">
        <!-- Loaded in navigation requests -->
      </div>
    </div>
  </div>
  <div id="file_browser_full_tree_container" class="panel panel-default">
    <div id="file_browser_full_tree" class="panel-body">
      <ul id="file_browser_full_tree_element" class="ztree" style="width:100%; overflow:auto;"></ul>
    </div>
  </div>
  <div id="file_browser_full_files_container" class="panel panel-default">
    <div id="file_browser_full_files" class="panel-body">
      <table id="file_browser_full_files_table" class="table">
        <tr id="file_browser_full_files_header" style="width:100%; display: flex; height: 35px">
          <!-- We need to keep the elements on the same line to prevent unwanted spaces -->
          <th style="width:10%; display: inline-block;border-top:none;"></th>
          <th id="name_header" class="file_table_header" style="width:35%; display: inline-block;border-top:none;"><?php echo t('Name', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
          <th id="size_header" class="file_table_header" style="width:15%; display: inline-block;border-top:none;"><?php echo t('Size', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
          <th id="type_header" class="file_table_header" style="width:15%; display: inline-block;border-top:none;"><?php echo t('Type', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
          <th id="modified_header" class="file_table_header" style="width:15%; display: inline-block;border-top:none;"><?php echo t('Modified', array(), array('context' => 'gofast:ajax_file_browser')); ?><span class="gofast_display_none order_indicator fa fa-caret-down"></span><span class="gofast_display_none order_indicator fa fa-caret-up"></span></th>
          <th id="info_header" class="file_table_header" style="width:10%; display: inline-block;border-top:none;"><?php echo t('Info', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
        </tr>
      </table>
    </div>
  </div>
  <div id="file_browser_full_upload_container" class="panel panel-default">
    <div id="file_browser_full_upload" class="panel-body">

      <button type="button" style="height:20px;padding-left:5px;padding-right:5px;padding-top:0px;padding-bottom:0px;right: 2.8%;margin-top: 9px;position: absolute;z-index: 2;" class="btn btn-danger" onclick="Gofast.ITHit.cancelAllUpload();">
        <i class="fa fa-times"></i>
      </button>

      <table id="file_browser_full_upload_table" class="table">
        <tr style="width:100%; display: inline-block;">
          <!-- We need to keep the elements on the same line to prevent unwanted spaces -->
          <th style="width:5%; display: inline-block;border-top:none;"></th>
          <th style="width:65%; display: inline-block;border-top:none;"><?php echo t('File', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
          <th style="width:10%; display: inline-block;border-top:none;"><?php echo t('Operation', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
          <th style="width:18%; display: inline-block;border-top:none;"><?php echo t('Progression', array(), array('context' => 'gofast:ajax_file_browser')); ?></th>
        </tr>
      </table>
    </div>
  </div>
</div>

<?php
if (!gofast_mobile_is_mobile_domain()) {
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
    //Triger the file browser navigation when we are ready and connected
    function triggerNavigation() {
      if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false) { //Not yet ready
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
        if (typeof params.path === "undefined") { //No path provided, navigate to default path
          Gofast.ITHit.navigate('/alfresco/webdav/Sites');
        } else { //Path provided, navigate to path
          Gofast.ITHit.navigate(params.path);
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
        jQuery("#file_browser_full_tree_container").width(jQuery("#file_browser_full_tree_container").width() + 2);
        jQuery("#file_browser_full_files_container").width(jQuery("#file_browser_full_container").width() - jQuery("#file_browser_full_tree_container").width() - 4);
        jQuery("#file_browser_full_files_container").css("margin-left", jQuery("#file_browser_full_tree_container").width() + 2);
        jQuery("#file_browser_full_files_table").width("auto");
        jQuery("#file_browser_full_files_table").width("initial");
      }
    });
  </script>

  <style>

    #file_browser_full_files,
    #file_browser_full_files_table {
      height: 100% !important;
    }

    #file_browser_full_files_container {
      height: 65% !important;
    }

    #file_browser_full_tree,
    #file_browser_full_tree_element {
      height: 100% !important;
    }

    #file_browser_full_tree_container {
      height: 65% !important;
    }

    #file_browser_full_upload,
    #file_browser_full_upload_table {
      height: 100% !important;
    }

    #file_browser_full_upload_container {
      height: 28% !important;
    }

    aside,
    footer,
    .breadcrumb-gofast {
      display: none !important;
    }
  </style>
<?php
} else if (!gofast_mobile_is_mobile_domain()) {
?>
  <script>
    //Allow to resize the files part of GFB vertically
    jQuery("#file_browser_full_files_container").resizable({
      alsoResize: "#file_browser_full_files_table, #file_browser_full_tree_container, #file_browser_full_tree_element",
      handles: 's',
      resize: function(e, ui) {
        //Fix some jQuery UI calculation errors after resizing resizing
        jQuery("#file_browser_full_tree_container").width("auto");
        jQuery("#file_browser_full_tree_container").width("initial");
        jQuery("#file_browser_full_files_table").height(jQuery("#file_browser_full_files_container").height());
        jQuery("#file_browser_full_tree_element").height(jQuery("#file_browser_full_files_container").height());
        //jQuery("#file_browser_full_container").height(jQuery("#file_browser_full_container").height() - 2);
        jQuery("#file_browser_full_files_table").width(jQuery("#file_browser_full_files_container").width() - 5);
      }
    });

    //Allow to resize the upload part of GFB vertically
    jQuery("#file_browser_full_upload_container").resizable({
      alsoResize: "#file_browser_full_upload_table",
      handles: 's',
      resize: function(e, ui) {
        //Fix some jQuery UI calculation errors after resizing resizing
        jQuery("#file_browser_full_upload_table").height(jQuery("#file_browser_full_upload_container").height());
        jQuery("#file_browser_full_upload_table").width("auto");
        jQuery("#file_browser_full_upload_table").width("initial");
        //jQuery("#file_browser_full_container").height(jQuery("#file_browser_full_container").height() - 2);
      }
    });

    //Allow to resize the ztree and file part of GFB horizontally
    jQuery("#file_browser_full_tree_container").resizable({
      alsoResize: "#file_browser_full_tree_element",
      handles: 'e',
      resize: function(e, ui) {
        //Also resize file block
        jQuery("#file_browser_full_tree_container").width(jQuery("#file_browser_full_tree_container").width() + 2);
        jQuery("#file_browser_full_files_container").width(jQuery("#file_browser_full_container").width() - jQuery("#file_browser_full_tree_container").width() - 4);
        jQuery("#file_browser_full_files_container").css("margin-left", jQuery("#file_browser_full_tree_container").width() + 2);
        jQuery("#file_browser_full_files_table").width("auto");
        jQuery("#file_browser_full_files_table").width("initial");
      }
    });
  </script>
<?php
}
?>
