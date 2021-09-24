<?php include_once 'MobileDetect.php'; ?>
<div class="Navigation">
  <div class="breadcrumb navigation_simplified Navigation__tabs Navigation__tabs_w_33">
    <ul class="nav nav-tabs nav-justified ">
      <li>
        <a id="navigation_dashboard" class="item_navigation" aria-controls="dashboard" role="tab" data-toggle="tab" href="#navDashboard">
          <i class="fa fa-th"></i>
          <?php print t('Dashboard'); ?>
        </a>
      </li>
      <li>
        <a id="navigation_browser" class="item_navigation" aria-controls="browser" role="tab" data-toggle="tab" href="#navBrowser">
          <i class="fa fa-folder-open"></i>
          <?php print t('Spaces / Documents', array(), array('context' => 'gofast:gofast_mobile')); ?>
        </a>
      </li>
      <li role="presentation" class="active">
        <a id="navigation_activity" class="item_navigation" aria-controls="activity" role="tab" data-toggle="tab" href="#navActivity">
          <i class="fa fa-bars"></i>
          <?php print t('Activity'); ?>
        </a>
      </li>
    </ul>
  </div>

  <div id="home_navigation_content" class="content well well-sm Navigation__content">
    <div class="tab-content Navigation__tabsContent">
      <div id="navActivity" role="tabpanel" class="tab-pane fade in active">
        <?php print gofast_activity_feed_display(FALSE, TRUE); ?>
      </div>
      <div id="navBrowser" role="tabpanel" class="tab-pane fade">
        <?php $detect = new Mobile_Detect; ?>
        <?php if ($detect->isMobile() && !$detect->isTablet()) : ?>
          <?php print theme('gofast_mobile_ajax_file_browser'); ?>
        <?php else : ?>
          <?php print theme('ajax_file_browser', array('browser' => TRUE)); ?>
        <?php endif; ?>
      </div>
      <div id="navDashboard" role="tabpanel" class="tab-pane fade">
        <?php print gofast_dashboard_dashboard_page(); ?>
      </div>
    </div>
  </div>
</div>
