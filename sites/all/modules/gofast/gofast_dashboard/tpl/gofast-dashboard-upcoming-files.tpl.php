<div class="table-responsive">
  <table id="table-upcoming-files" class="table table-hover table-striped" style="table-layout:fixed;">
    <tbody>
      <?php foreach ($files as $key => $file) : ?>
        <tr class="text-truncate">
          <td class="td-field-date w-25">
            <span class="dashboard-calendar-deadline"><?php echo format_date(strtotime($file->field_date_value), 'short_without_hours'); ?></span>
          </td>
          <td class="td-field-nid d-none"><?php echo $file->nid ?></td>
          <td class="td-field-title w-75 text-truncate">
            <?php $icon = gofast_taxonomy_icon_filename($file->field_format_tid); ?>
            <span class="fa <?php echo $icon; ?>"></span>
            <a href="/node/<?php echo $file->nid ?>" title="<?php echo $file->title ?>"><?php echo $file->title ?></a>
          </td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>

  <nav class="text-center mt-6 dashboard-pagination-bottom">
    <ul class="pagination pagination-sm justify-content-center" id="path_pager_upcoming_files"></ul>
  </nav>
</div>


<script type='text/javascript'>
    jQuery(document).ready(function(){
        jQuery('#table-upcoming-files > tbody').pager({pagerSelector : '#path_pager_upcoming_files', perPage: 7, numPageToDisplay : 5, showPrevNext: false});
    });

</script>
