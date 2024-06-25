<!-- START ajax_file_browser_mobile.tpl.php -->
<div class="ajax-file-browser" >
  <div id="file_browser_mobile_header" class="">
    <div id="file_browser_mobile_header_breadcrumb">
      <ul></ul>
    </div>
    <div id="file_browser_mobile_toolbar_search" class="input-group input-group-sm">
      <div class="input-group">
        <input id="file_browser_mobile_toolbar_search_input" type="text" class="form-control" placeholder="<?php echo t('Filter', array(), array('context' => 'gofast:ajax_file_browser')); ?>" aria-describedby="sizing-addon3">
        <div class="input-group-append dropdown no-arrow" id="file_browser_mobile_toolbar_refresh_group">
          <button title="<?php echo t('Refresh'); ?>" id="file_browser_mobile_tooolbar_refresh" type="button" class="btn input-group-text dropdown-toggle" ><i class="fa fa-refresh" aria-hidden="true"></i></button>
        </div>
      </div>
    </div>
    <div id="" class="btn-group">
      <button type="button" id="file_browser_tooolbar_manage" class="btn btn-default btn-sm dropdown-toggle" data-toggle="dropdown" aria-haspopup="true" style="display: none"><i class="fa fa-gear" aria-hidden="true" disabled></i> <?php echo t('Manage', array(), array('context' => 'gofast:ajax_file_browser')); ?> <span class="caret"></span></button>
      <ul class="dropdown-menu">
        <?php
        $attr = array(
          'onClick' => "Gofast.ITHitMobile.bulkSelected(event)",
        );
        print '<li>' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal manage-taxonomy', 'fa fa-tags', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal add-locations', 'fa fa-share-alt n-color', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal manage-publications', 'fa fa-arrow-up', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal manage-mail-sharing', 'fa fa-envelope', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'archive_open_span', 'ctools-use-modal bulk-archive', 'fa fa-archive', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Add to cart', array(), array('context' => 'gofast')), '/modal/nojs/bulk_add_to_cart', 'cart_open_span', 'ctools-use-modal add_to_cart', 'fas fa-shopping-basket', $attr) . '</li>';
        print '<li>' . gofast_dropdown_link(t('Manage Metadata', array(), array('context' => 'gofast')), '/modal/nojs/manage-taxonomy', 'taxonomy_open_span', 'ctools-use-modal bulk_taxonomy manage-taxonomy gofast_display_none', 'fa fa-tags') . '</li>';
        print '<li>' . gofast_dropdown_link(t('Share/Add locations', array(), array('context' => 'gofast')), '/modal/nojs/add-locations', 'locations_open_span', 'ctools-use-modal bulk_add_locations add-locations gofast_display_none', 'fa fa-share-alt n-color') . '</li>';
        print '<li>' . gofast_dropdown_link(t('Create publications', array(), array('context' => 'gofast')), '/modal/nojs/manage-publications', 'publications_open_span', 'ctools-use-modal bulk_publications manage-publications gofast_display_none', 'fa fa-arrow-up') . '</li>';
        print '<li>' . gofast_dropdown_link(t('Share by email', array(), array('context' => 'gofast')), '/modal/nojs/manage-mail-sharing', 'linksharing_open_span', 'ctools-use-modal bulk_mail_sharing manage-mail-sharing gofast_display_none', 'fa fa-envelope') . '</li>';
        print '<li>' . gofast_dropdown_link(t('Archive content'), '/modal/nojs/bulk-archive', 'taxonomy_open_span', 'ctools-use-modal bulk_archive bulk-archive gofast_display_none', 'fa fa-archive') . '</li>';
        ?>
      </ul>
    </div>
  </div>
  <div id="file_browser_mobile_files" class="panel-body">
    <table id="file_browser_mobile_files_table" class="table">
    </table>
  </div>
  <div id="file_browser_mobile_queue" class="panel-body">

  </div>
</div>
<!-- END ajax_file_browser_mobile.tpl.php -->