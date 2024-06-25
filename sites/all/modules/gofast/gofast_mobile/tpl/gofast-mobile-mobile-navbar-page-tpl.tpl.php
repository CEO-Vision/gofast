<?php $detect = new Mobile_Detect;?>
<?php if(gofast_mobile_is_phone()): ?>
    <?php $front_page = "/home_page_navigation#navBrowser"; ?>
<?php else : ?>
    <?php $front_page = variable_get("site_frontpage", "activity"); ?>
<?php endif; ?>

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
        <div class="Header__user">
            <?php if (($user->uid !== '0') &&  (user_is_logged_in())) : ?>
                <?php
                global $user;
                global $base_url;
                $userData = user_load($user->uid);
                $avatar = $userData->picture->uri == null ? $base_url . '/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png' : file_create_url($userData->picture->uri);
                ?>
                <img class="" src="<?php print $avatar ?>">
            <?php endif; ?>
        </div>
    </div>

    <?php if (user_is_logged_in()) : ?>
        <div id="mySidebar" class="gofast_mobile_sidebar fadeInDown Header__sidebar">
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
                                    <div class="list-items-div"><i class="fas fa-video" aria-hidden="true"></i></div>
                                    <p><?php print t('conference') ?></p>
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
                <li><a href="/tasks_page_navigation" class="center-block gofast_mobile_link sidebar-items">
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
                    <a href="<?php print $url; ?>" class="center-block gofast_mobile_link sidebar-items" target="_blank">
                        <div class="list-items-div"><i class="fa fa-download " aria-hidden="true"></i></div>
                        <p><?php print t('Chat (download)') ?></p>
                    </a>
                </li>
                <li><a href="/user" class="center-block gofast_mobile_link sidebar-items">
                        <div class="list-items-div"><i class="fa fa-user" aria-hidden="true"></i></div>
                        <p><?php print t('Profile') ?></p>
                    </a>
                </li>
                <li><a href="#forInfo" class="dropdown-toggle collapsed center-block gofast_mobile_link sidebar-items gofast-non-ajax" data-toggle="collapse">
                        <div class="list-items-div"><i class="fa fa-question-circle" aria-hidden="true"></i></div>
                        <p><?php print t('For informations', array(), array('context' => 'gofast:gofast_mobile')) ?></p>
                    </a>
                    <ul class="list-unstyled collapse" id="forInfo">
                        <li>
                            <a href="<?php print $gofast_url_doc; ?>" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;' target="_blank">
                                <div class="list-items-div"><i class="fa fa-book" aria-hidden="true"></i></div>
                                <p><?php print t('Documentation') ?></p>
                            </a>
                        </li>
                        <li>
                            <a href="http://community.ceo-vision.com" class="center-block gofast_mobile_link sidebar-items" style='padding-left: 20px !important;' target="_blank">
                                <div class="list-items-div"><i class="fa fa-comments" aria-hidden="true"></i></div>
                                <p><?php print t('Forum') ?></p>
                            </a>
                        </li>
                        <li>
                            <a href="/gofast/nojs/versions" class="center-block gofast_mobile_link sidebar-items ctools-use-modal" style='padding-left: 20px !important;'>
                                <div class="list-items-div"><i class="fa fa-question-circle" aria-hidden="true"></i></div>
                                <p><?php print t('About') ?></p>
                            </a>
                        </li>
                    </ul>
                </li>
                <li><a href="/user/logout" class="center-block gofast_mobile_link sidebar-items">
                        <div class="list-items-div"><i class="fa fa-sign-out" aria-hidden="true"></i></div>
                        <p><?php print t('Logout') ?></p>
                    </a>
                </li>
                <?php if (isset($lang_switch)) : ?>
                    <!-- Gofast language quick switch -->
                    <li class="Header__sidebarLangue"><span id='mobile_switch_menu' style='color:#9d9d9d;'>
                            <a class="gofast-non-ajax" href="/home_page_navigation?language=nl" class="active">nl</a>|<a class="gofast-non-ajax" href="/home_page_navigation?language=en" class="current active">en</a>|<a class="gofast-non-ajax" href="/home_page_navigation?language=fr" class="active">fr</a>
                        </span></li>
                <?php endif; ?>
            </ul>
        </div>
    <?php endif; ?>
</header>
