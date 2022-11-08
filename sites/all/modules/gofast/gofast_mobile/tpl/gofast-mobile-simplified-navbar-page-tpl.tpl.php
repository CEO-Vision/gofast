<?php $front_page = "/home_page_navigation#navBrowser"; ?>
<?php
global $user;
$gofast_url_doc = "https://gofast-docs.readthedocs.io/" . $user->language . "/4.0/docs-gofast-users/doc-gofast-guide-utilisateurs.html";

//Detect special conditions devices
$iPod    = stripos($_SERVER['HTTP_USER_AGENT'], "iPod");
$iPhone  = stripos($_SERVER['HTTP_USER_AGENT'], "iPhone");
$iPad    = stripos($_SERVER['HTTP_USER_AGENT'], "iPad");
$Android = stripos($_SERVER['HTTP_USER_AGENT'], "Android");
$webOS   = stripos($_SERVER['HTTP_USER_AGENT'], "webOS");


if ($iPod || $iPhone || $iPad) {
  $url = "https://apps.apple.com/app/vector/id1083446067";
} else if ($Android) {
  $url = "https://play.google.com/store/apps/details?id=im.vector.app";
}
?>
<header id="navbar" role="banner" class="<?php print $navbar_classes; ?> Header">
  <div class="Header__left">
    <div class="Header__logo">
      <?php if ($logo) : ?>
        <a class="Logo" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img class="Logo__image" src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php elseif (!empty($site_name)) : ?>
        <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>
    </div>
    <div class="Header__sidebarToggle">
      <?php if (user_is_logged_in()) : ?>
        <button type="button" onclick="Gofast.triggerNav()" id="gofast_togglebar">
          <i class="fa fa-bars"></i>
        </button>
      <?php endif; ?>
    </div>
  </div>
  <div class="Header__center">
    <?php if (!empty($page['navigation'])) : ?>
      <div class="<?php //print $search_form_class;
                  ?> Header__search">
        <?php print render($page['navigation']); ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="Header__right">
    <!-- BEGIN Icon user dropdown -->
    <?php if (!empty($secondary_nav)) : ?>
      <div class="Header__user">
        <?php print render($secondary_nav); ?>
      </div>
    <?php endif; ?>
    <!-- END Icon user dropdown  -->
    <!-- BEGIN language quick switch-->
    <?php if (isset($lang_switch)) : ?>
      <div class="Header__langue">
        <span id='mobile_switch_menu' style='color:#9d9d9d;padding-top: 8px;'>
          <a class="gofast-non-ajax" href="/home_page_navigation?language=nl" class="active">nl</a>|<a class="gofast-non-ajax" href="/home_page_navigation?language=en" class="current active">en</a>|<a class="gofast-non-ajax" href="/home_page_navigation?language=fr" class="active">fr</a>
        </span>
      </div>
    <?php endif; ?>
    <!-- END language quick switch  -->
    <!-- BEGIN GO FAST ABOUT  -->
    <div class="Header__about">
      <div class="visible-lg btn btn-sm gofast-about-btn" style="width:auto !important; position: relative !important;">
        <?php if (module_exists("gofast_community")) { ?>
          <?php
          $manifest = gofast_update_get_release_manifest();
          $hotfix_available = gofast_update_get_available_hotfix_version($manifest);
          $version_available = gofast_update_get_available_version($manifest);
          if (!empty($hotfix_available || !empty($version_available))) { ?>
            <i class="fa fa-exclamation-circle fa-2x dropdown-toggle dropdown dropbtn" data-toggle="dropdown"></i>
          <?php } else { ?>
            <i class="fa fa-question-circle fa-2x dropdown-toggle dropdown dropbtn" data-toggle="dropdown"></i>
          <?php } ?>
        <?php } else { ?>
          <i class="fa fa-question-circle fa-2x dropdown-toggle dropdown dropbtn" data-toggle="dropdown"></i>
        <?php } ?>
        <ul class="dropdown-menu dropdown-content" style="right: 0; left: auto;">
          <li>
            <a class="center-block sidebar-items" onclick="Gofast.tour.tourButtonAction(event)">
              <div class="list-items-icons">
                <span class="fa-stack fa-1x" style="transform:scale(0.5) translate(-1em,-1em);margin-right:-0.5em;margin-bottom:-1em">
                  <i class="fa fa-comment fa-stack-2x" style="color:#777"></i>
                  <i class="fa fa-question fa-stack-1x fa-inverse" style="transform:scale(1.5)"></i>
                </span>
              </div>
              <p><?php print t('Launch help tour', array(), array('context' => 'gofast:gofast_tour')) ?></p>
            </a>
          </li>
          <?php
          if (variable_get("gofast_carousel_active", FALSE)) {
          ?>
            <li>
              <a id="gofast_carousel_link" class="center-block sidebar-items ctools-use-modal" href="/gofast/nojs/carousel">
                <div class="list-items-icons"><i class="fa fa-plus" style=" color: #777;"></i></div>
                <p><?php print t('New features and improvements', array(), array('context' => 'gofast')); ?></p>
              </a>
            </li>
          <?php
          }
          ?>
          <li>
            <a class="center-block sidebar-items" href="http://community.ceo-vision.com" target="_blank">
              <div class="list-items-icons"><i class="fa fa-comments" style=" color: #777;"></i></div>
              <p><?php print t('Forum', array(), array('context' => 'gofast')); ?></p>
            </a>
          </li>
          <li>
            <a class="center-block sidebar-items" href="<?php print $gofast_url_doc; ?>" target="_blank">
              <div class="list-items-icons"><i class="fa fa-book" style=" color: #777;"></i></div>
              <p><?php print t('Documentation', array(), array('context' => 'gofast')); ?></p>
            </a>
          </li>
          <li>
            <?php if ($_SERVER['SERVER_NAME'] != $_SERVER['SERVER_ADDR']) { ?>
              <a class="center-block sidebar-items" href="/gofast/user/login/version/standard">
                <div class="list-items-icons"><i class="fa fa-laptop" aria-hidden="true" style="font-size:17px;color: #777;"></i></div>
                <p><?php print " ";
                    print t("GoFAST Plus", array(), array('gofast')); ?></p>
              </a>
            <?php } ?>
          </li>
          <li>
            <a class="center-block sidebar-items ctools-use-modal" href="/gofast/nojs/versions">
              <div class="list-items-icons"><i class="fa fa-question-circle" style=" color: #777;"></i></div>
              <p><?php print t('About', array(), array('context' => 'gofast')); ?></p>
            </a>
          </li>
          <?php if (module_exists("gofast_community")) { ?>
            <?php if (!empty($hotfix_available || !empty($version_available))) { ?>
              <li id="update_gofast">
                <a class="center-block sidebar-items" href="/admin/config/gofast/update">
                  <div class="list-items-icons"><i class="fa fa-exclamation-circle" style=" color: red;"></i></div>
                  <p><?php print t('Update', array(), array('context' => 'gofast')); ?></p>
                </a>
              <?php } else { ?>
              <li>
                <a class="center-block sidebar-items" href="/admin/config/gofast/update">
                  <div class="list-items-icons"><i class="fa fa-exclamation-circle" style=" color: #777;"></i></div>
                  <p><?php print t('Update', array(), array('context' => 'gofast')); ?></p>
                </a>
              <?php } ?>
              </li>
            <?php } ?>
        </ul>
      </div>
    </div>
    <!-- END GO FAST ABOUT  -->
  </div>

  <!-- BEGIN Sidebar -->
  <?php if (user_is_logged_in()) : ?>
    <div id="mySidebar" class="col-md-1 gofast_mobile_sidebar fadeInDown Header__sidebar">
      <ul>
        <li><a class="center-block gofast_mobile_link sidebar-items" href="<?php print $front_page; ?>">
            <div class="list-items-div"><i class="fa fa-home" aria-hidden="true"></i></div>
            <p><?php print t('Home') ?></p>
          </a>
        </li>
        <li><a href="#createMenu" class="dropdown-toggle collapsed center-block gofast_mobile_link sidebar-items gofast-non-ajax" data-toggle="collapse">
            <div class="list-items-div"><i class="fa fa-plus" aria-hidden="true"></i></div>
            <p><?php print t('Create', array(), array('context' => 'gofast:gofast_retention')) ?></p>
          </a>
          <ul class="list-unstyled collapse" id="createMenu">

            <?php if (drupal_valid_path('node/add/conference')) :  ?>
              <li>
                <a href="/node/add/conference" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;'>
                  <div class="list-items-div"><i class="fa fa-video-camera" aria-hidden="true"></i></div>
                  <p><?php print t('Conference') ?></p>
                </a>
              </li>
            <?php endif ?>

            <li>
              <a href="#createContent" class="center-block gofast_mobile_link sidebar-items dropdown-toggle collapsed gofast-non-ajax center-block gofast_mobile_link sidebar-items" data-toggle="collapse" style='padding-left: 20px !important;'>
                <div class="list-items-div"><i class="fa fa-list-alt" aria-hidden="true"></i></div>
                <p><?php print t('Content') ?></p>
              </a>
              <ul class="list-unstyled collapse" id="createContent">
                <li>
                  <a href="/node/add/alfresco-item" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 90px !important;'><?php print t('Document') ?></a>
                </li>
              </ul>
            </li>
            <?php if (drupal_valid_path('node/add/group') || drupal_valid_path('node/add/organisation') || drupal_valid_path('node/add/public') || drupal_valid_path('node/add/extranet')) :  ?>
              <li>
                <a href="#createSpaces" class="center-block gofast_mobile_link sidebar-items dropdown-toggle collapsed center-block gofast-non-ajax" data-toggle="collapse" style='padding-left: 20px !important;'>
                  <div class="list-items-div"><i class="fa fa-building" aria-hidden="true"></i></div>
                  <p><?php print t('Space') ?></p>
                </a>
                <ul class="list-unstyled collapse" id="createSpaces">
                  <?php if (drupal_valid_path('node/add/group')) :  ?>
                    <li>
                      <a href="/node/add/group" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 90px !important;'><?php print t('Group') ?></a>
                    </li>
                  <?php endif ?>
                  <?php if (drupal_valid_path('node/add/organisation')) :  ?>
                    <li>
                      <a href="/node/add/organisation" class="center-block gofast_mobile_link sidebar-items dropdown-toggle collapsed center-block gofast_mobile_link sidebar-items" data-toggle="collapse" style='padding-left: 90px !important;'><?php print t('Organisation') ?></a>
                    </li>
                  <?php endif ?>
                  <?php if (drupal_valid_path('node/add/public')) :  ?>
                    <li>
                      <a href="/node/add/public" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 90px !important;'><?php print t('Public') ?></a>
                    </li>
                  <?php endif ?>
                  <?php if (drupal_valid_path('node/add/extranet')) :  ?>
                    <li>
                      <a href="/node/add/extranet" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 90px !important;'><?php print t('Extranet') ?></a>
                    </li>
                  <?php endif ?>
                </ul>
              </li>
            <?php endif ?>

            <?php if (drupal_valid_path('admin/people/create')) :  ?>
              <li>
                <a href="/admin/people/create" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;'>
                  <div class="list-items-div"><i class="fa fa-user" aria-hidden="true"></i></div>
                  <p><?php print t('User') ?></p>
                </a>
              </li>
            <?php endif ?>

          </ul>
        </li>
        <li><a class="center-block gofast_mobile_link sidebar-items" href="/home_page_navigation?&path=/Sites/_<?php print $user->name ?>#navBrowser">
            <div class="list-items-div"><i class="fa fa-file-text" aria-hidden="true"></i></div>
            <p><?php print t('Private Documents', array(), array('context' => 'gofast:gofast_mobile')) ?></p>
          </a>
        </li>
        <li><a class="center-block gofast_mobile_link sidebar-items" href="/home_page_navigation?&path=/Sites#navBrowser">
            <div class="list-items-div"><i class="fa fa-folder-open" aria-hidden="true"></i></div>
            <p><?php print t('Spaces / Documents', array(), array('context' => 'gofast:gofast_mobile')) ?></p>
          </a>
        </li>
        <li>
          <a href="#navDirectories" class="center-block gofast_mobile_link sidebar-items dropdown-toggle collapsed gofast-non-ajax" data-toggle="collapse">
            <div class="list-items-div"><i class="fa fa-address-book" aria-hidden="true"></i></div>
            <p><?php print t('Directories') ?></p>
          </a>
          <ul class="list-unstyled collapse" id="navDirectories">
            <li>
              <a href="/og/list_grid" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;'>
                <div class="list-items-div"><i class="fa fa-building" aria-hidden="true"></i></div>
                <?php print t('Spaces') ?>
              </a>
            </li>
            <li>
              <a href="/user_listing_tab" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;'>
                <div class="list-items-div"><i class="fa fa-user" aria-hidden="true"></i></div>
                <?php print t('Users') ?>
              </a>
            </li>
            <li>
              <a href="/userlists" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;'>
                <div class="list-items-div"><i class="fa fa-users" aria-hidden="true"></i></div>
                <?php print t('Userlists') ?>
              </a>
            </li>
          </ul>
        </li>
        <li><a href="/tasks_page_navigation#lightDashboardMyTab" class="center-block gofast_mobile_link sidebar-items">
            <div class="list-items-div"><i class="fa fa-cogs" aria-hidden="true"></i></div>
            <p><?php print t('Workflows') ?></p>
          </a>
        </li>
        <li><a href="/calendar_simplified" class="center-block gofast_mobile_link sidebar-items">
            <div class="list-items-div"><i class="fa fa-calendar" aria-hidden="true"></i></div>
            <p><?php print t('Calendar') ?></p>
          </a>
        </li>
        <li>

          <a href="/conversation" class="center-block gofast_mobile_link sidebar-items">
            <!-- target="_blank" -->
            <div class="list-items-div"><i class="fa fa-comments" aria-hidden="true"></i></div>
            <p><?php print t('Chat') ?></p>
          </a>
        </li>
        <li><a href="/user" class="center-block gofast_mobile_link sidebar-items">
            <div class="list-items-div"><i class="fa fa-user" aria-hidden="true"></i></div>
            <p><?php print t('Profile') ?></p>
          </a>
        </li>
        <li><a href="/user/logout" class="center-block gofast_mobile_link sidebar-items">
            <div class="list-items-div"><i class="fa fa-sign-out" aria-hidden="true"></i></div>
            <p><?php print t('Logout') ?></p>
          </a>
        </li>
      </ul>
    </div>
  <?php endif; ?>
  <!-- END Sidebar  -->
</header>
