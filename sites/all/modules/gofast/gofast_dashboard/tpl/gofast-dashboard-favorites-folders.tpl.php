<div id="dashboard-block-folders" class="panel panel-dashboard panel-dashboard-big panel-default">
  <div class="panel-heading">
    <div class="row">
      <div class="col-sm-10" style="font-weight: bold">
        <?php print t('My favorite folders', array(), array('context' => 'gofast_dashboard')) ?>
      </div>
      <div class="col-sm-1">
        <a href="/modal/nojs/dashboard_add_folder_to_dashboard" class="ctools-use-modal"  data-toggle="tooltip" title="<?php echo t('Pin new folder', array(), array('context' => 'gofast_cdel')); ?>" >
          <span class="fa fa-plus"></span>
        </a>
      </div>
      <div class="col-sm-1">
        <?php if(gofast_mobile_is_mobile_domain()): ?>
          <a href="/home_page_navigation?&path=/Sites#navBrowser" data-toggle="tooltip" title="<?php echo t('Go to the file browser', array(), array('context' => 'gofast_cd74')); ?>">
        <?php else: ?>
          <a href="/gofast/browser" data-toggle="tooltip" title="<?php echo t('Go to the file browser', array(), array('context' => 'gofast_cd74')); ?>">
        <?php endif; ?>
            <span class="fa fa-folder-open"></span>
          </a>
      </div>
    </div>
  </div>
  <div class="panel-body dashboard-folders-placeholder">
   <?php global $language; ?>
    <table id="table_favorite_path" class="table table-hover table-striped" style="margin-bottom: -8px;" >
        <thead></thead>
        <tbody>
          <?php if(count($favorite_folders) > 0): ?>
            <?php foreach ($favorite_folders as $folder): ?>
            <tr>
              <td>
                  <span class="">
                    <?php echo $folder["icon"]; ?>
                    <?php echo $folder["link"]; ?>
                  </span>
              </td>
              <td style="width: 50px;">
                  <a href="<?php echo $folder["unthemed_link"]; ?>" title="<?php echo t('Go to file browser', array(), array('context' => 'gofast:gofast_dashboard')); ?>" style="margin-right: 8px;">
                    <span class="fa fa-arrow-right"></span>
                  </a>
                  <a href="#" onClick="Gofast.ITHit.unbookmarkFolder('/alfresco/webdav<?php echo $folder['unthemed_path']; ?>'); jQuery(this).parent().parent().remove(); jQuery('#table_favorite_path > tbody').pager({pagerSelector : '#path_pager', perPage: 9, numPageToDisplay : 5, showPrevNext: false});">
                      <span class="fa fa-trash" title="<?php echo t('Remove from bookmarks', array(), array('context' => 'gofast:gofast_dashboard')); ?>"></span>
                  </a>
              </td>
            </tr>
            <?php endforeach; ?>
          <?php else: ?>
              <tr>
                <td><?php echo t('No favorite path.', array(), array('context' => 'gofast_dashboard')) ?></td>
              </tr>
          <?php endif; ?>
        </tbody>
    </table>

    <nav class="text-center" style="margin-top:15px;">
        <ul class="pagination" style="margin-top:25px;margin-bottom:5px;" id="path_pager"></ul>
    </nav>
  </div>
</div>

  <script type='text/javascript'>
   jQuery(document).ready(function(){
         jQuery('#table_favorite_path > tbody').pager({pagerSelector : '#path_pager', perPage: 9, numPageToDisplay : 5, showPrevNext: false});
    });

  </script>
