<div class="Navigation">
  <div class="breadcrumb navigation_simplified Navigation__tabs Navigation__tabs_w_50">
    <ul class="nav nav-tabs nav-justified">
      <li role="presentation" class="active">
        <a id="navigation_meetings" class="item_navigation" aria-controls="meetings" role="tab" data-toggle="tab" href="#navMeetings">
          <i class="fa fa-video-camera"></i>
          <?php print t('Meetings'); ?>
        </a>
      </li>
      <li role="presentation">
        <a id="navigation_deadlines" class="item_navigation" aria-controls="deadlines" role="tab" data-toggle="tab" href="#navDeadlines">
          <i class="fa fa-file"></i>
          <?php print t('Documents deadlines', array(), array('context' => 'gofast_cdel')); ?>
        </a>
      </li>
    </ul>
  </div>

  <div id="home_navigation_content" class="content well well-sm Navigation__content">
    <div class="tab-content Navigation__tabsContent">
      <div id="navMeetings" role="tabpanel" class="tab-pane fade  in active">
        <?php
        if (!empty(views_get_view_result('upcoming', 'upcoming_meetings'))) {
          $upcoming_meetings = views_embed_view('upcoming', 'upcoming_meetings');
          print $upcoming_meetings;
        } else {
          $msg = '</br><p> <b>' . t('No meeting is currently scheduled.', array(), array('context' => 'gofast_simple'));
          if (drupal_valid_path('node/add/conference')) {
            $msg .= '  <a href="/node/add/conference" style="opacity: 1;">' . t('Create a meeting', array(), array('context' => 'gofast_simple')) . ' ? </a>';
          }
          $msg .= '</p> </b></br>';
          print $msg;
        }
        ?>
      </div>
      <div id="navDeadlines" role="tabpanel" class="tab-pane fade">
        <?php
        if (!empty(views_get_view_result('upcoming', 'upcoming_deadlines'))) {
          $upcoming_deadlines = views_embed_view('upcoming', 'upcoming_deadlines');
          print $upcoming_deadlines;
        } else {
          print '</br><p> <b>' . t('No deadline is currently defined.', array(), array('context' => 'gofast_simple')) . '</p> </b></br>';
        }
        ?>
      </div>
    </div>

  </div>
</div>

<style>
  .main-container {
    width: 90% !important;
  }
</style>

<script>
  function triggerCalendarNavigation() {
    jQuery('#home_navigation_content .pagination a').click(function(e) {
      e.preventDefault();
      e.stopPropagation();
      var url = jQuery(this).attr('href');
      jQuery.get(url,
        function(data, textStatus, jqXHR) {
          jQuery('#home_navigation_content #navCalendar .view-display-id-page_4').remove();
          jQuery('#home_navigation_content').append(data);
          Drupal.attachBehaviors();
        }
      );
    });
  }
  triggerCalendarNavigation();
</script>
