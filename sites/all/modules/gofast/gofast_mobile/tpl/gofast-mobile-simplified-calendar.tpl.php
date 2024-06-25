<?php global $base_url; ?>
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
                            <i class="fas fa-video"></i>
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
                            <div id="navMeetings" role="tabpanel" class="tab-pane fade in active show">
                                <?php
                                    $placeholder = '</br><p> <b>' . t('No meeting is currently scheduled.', [], ['context' => 'gofast_simple']);
                                    if (drupal_valid_path('node/add/conference')) {
                                    $placeholder .= '  <a href="/node/add/conference" style="opacity: 1;">' . t('Create a meeting', [], ['context' => 'gofast_simple']) . ' ? </a>';
                                    }
                                    $placeholder .= '</p> </b></br>';
                                ?>
                                <?= theme("gofast_mobile_simplified_calendar_table", [
                                    "contents" => $meetings,
                                    "columns" => [t("Name"), t("Start"), t("End")],
                                    "theme" => "gofast_mobile_simplified_calendar_meeting_row",
                                    "placeholder" => $placeholder]) ?>

                            </div>
                            <nav class="text-center mt-4">
                                <ul class="pagination pagination-sm justify-content-center" id="goFastMeetingContent">
                                </ul>
                            </nav>
                            <div id="navDeadlines" role="tabpanel" class="tab-pane fade table-responsive">
                                <?= theme("gofast_mobile_simplified_calendar_table", [
                                    "contents" => $deadlines,
                                    "columns" => [t("Title"), t("Deadline")],
                                    "theme" => "gofast_mobile_simplified_calendar_deadline_row",
                                    "placeholder" => t('No deadline is currently defined.', [], ['context' => 'gofast_simple'])]) ?>
                            </div>
                            <nav class="text-center mt-4">
                                <ul class="pagination pagination-sm justify-content-center" id="goFastDeadlineContent">
                                </ul>
                            </nav>
                        </div>
                    </div>
            </div>
        </div>
    </div>
</div>

<script type="text/javascript">
    jQuery(document).ready(function() {
        jQuery('#navDeadlines tbody').pager({pagerSelector : '#goFastDeadlineContent', perPage: 11, numPageToDisplay : 5, isFlex : false});
        jQuery('#navMeetings tbody').pager({pagerSelector : '#goFastMeetingContent', perPage: 11, numPageToDisplay : 5, isFlex : false});
    })
</script>
