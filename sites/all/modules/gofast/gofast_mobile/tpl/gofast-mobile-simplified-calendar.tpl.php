<div class="mainContent GofastMobileCalendar p-3 h-100 gofast-mobile-calendar-page"
     id="gofast-mobile-calendar">
    <div class="card card-custom card-stretch GofastMobileHome__container">
        <div class="card-body d-flex p-0 flex-column">
            <div class="w-100 px-2">
                <ul class="nav nav-tabs nav-justified">
                    <li class="nav-item ">
                        <a class="nav-link px-2 d-flex justify-content-center active"
                           id="navigation_meetings" aria-controls="navMeetings"
                           data-toggle="tab" href="#navMeetings">
                        <span class="nav-icon">
                        <i class="fa fa-video-camera"></i>
                        </span>
                            <span class="nav-text">
                    <?php print t('Meetings'); ?>
                </span>
                        </a>
                    </li>
                    <li class="nav-item ">
                        <a class="nav-link px-2 d-flex justify-content-center"
                           id="navigation_deadlines"
                           aria-controls="navDeadlines"
                           data-toggle="tab" href="#navDeadlines">
                        <span class="nav-icon">
                        <i class="fa fa-file"></i>
                        </span>
                            <span class="nav-text">
                    <?php print t('Documents deadlines'); ?>
                </span>
                        </a>
                    </li>
                </ul>
            </div>
            <div class="container-fluid h-100 py-0" id="kt_content">
                <div id="messages-placeholder"></div>
                    <div id="home_navigation_content"
                         class="content well well-sm Navigation__content">
                        <div class="tab-content Navigation__tabsContent">
                            <div id="navMeetings" role="tabpanel"
                                 class="tab-pane fade in active show">
                              <?php
                              if (!empty(views_get_view_result('upcoming', 'upcoming_meetings'))) {
                                $upcoming_meetings = views_embed_view('upcoming', 'upcoming_meetings');
                                print $upcoming_meetings;
                              }
                              else {
                                $msg = '</br><p> <b>' . t('No meeting is currently scheduled.', [], ['context' => 'gofast_simple']);
                                if (drupal_valid_path('node/add/conference')) {
                                  $msg .= '  <a href="/node/add/conference" style="opacity: 1;">' . t('Create a meeting', [], ['context' => 'gofast_simple']) . ' ? </a>';
                                }
                                $msg .= '</p> </b></br>';
                                print $msg;
                              }
                              ?>
                            </div>
                            <div id="navDeadlines" role="tabpanel"
                                 class="tab-pane fade">
                              <?php
                              if (!empty(views_get_view_result('upcoming', 'upcoming_deadlines'))) {
                                $upcoming_deadlines = views_embed_view('upcoming', 'upcoming_deadlines');
                                print $upcoming_deadlines;
                              }
                              else {
                                print '</br><p> <b>' . t('No deadline is currently defined.', [], ['context' => 'gofast_simple']) . '</p> </b></br>';
                              }
                              ?>
                            </div>
                        </div>
                    </div>
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
        jQuery('#home_navigation_content .pagination a').click(function (e) {
            e.preventDefault();
            e.stopPropagation();
            var url = jQuery(this).attr('href');
            jQuery.get(url,
                function (data, textStatus, jqXHR) {
                    jQuery('#home_navigation_content #navCalendar .view-display-id-page_4').remove();
                    jQuery('#home_navigation_content').append(data);
                    Drupal.attachBehaviors();
                }
            );
        });
    }

    triggerCalendarNavigation();
</script>
