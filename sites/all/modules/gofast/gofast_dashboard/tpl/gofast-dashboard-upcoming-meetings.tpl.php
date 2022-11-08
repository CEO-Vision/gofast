 <?php global $user;
    $account = $user;
 ?>
<div class="table-responsive">
  <table id="table-upcoming-meetings" class="table table-hover table-striped" style="table-layout:fixed;">
    <tbody>
      <?php foreach ($meetings as $key => $meeting) : ?>
        <tr class="text-truncate">
          <td class="td-field-date">
            <span class="dashboard-calendar-deadline"><?php echo format_date(strtotime(gofast_change_time_zone($meeting->field_date_value, 'UTC', $account->timezone)) , 'short', '', date_default_timezone_get()); ?></span>
          </td>
          <td class="td-field-nid d-none"><?php echo $meeting->nid ?></td>
          <td class="td-field-title text-truncate">
            <i class="fas fa-video fa-1x"></i>
            <a href="/node/<?php echo $meeting->nid?>" title="<?php echo $meeting->title ?>"><?php echo $meeting->title ?></a>
          </td>
        </tr>
      <?php endforeach; ?>
    </tbody>
  </table>
  <nav class="text-center mt-6 dashboard-pagination-bottom">
    <ul class="pagination pagination-sm justify-content-center" id="path_pager_upcoming_meetings"></ul>
  </nav>
</div>

<script type='text/javascript'>
    jQuery(document).ready(function(){
        jQuery('#table-upcoming-meetings > tbody').pager({pagerSelector : '#path_pager_upcoming_meetings', perPage: 7, numPageToDisplay : 5, showPrevNext: false});
    });

</script>
