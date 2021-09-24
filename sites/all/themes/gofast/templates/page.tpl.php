<?php

/**
 * @file
 * Default theme implementation to display a single Drupal page.
 *
 * The doctype, html, head and body tags are not in this template. Instead they
 * can be found in the html.tpl.php template in this directory.
 *
 * Available variables:
 *
 * General utility variables:
 * - $base_path: The base URL path of the Drupal installation. At the very
 *   least, this will always default to /.
 * - $directory: The directory the template is located in, e.g. modules/system
 *   or themes/bartik.
 * - $is_front: TRUE if the current page is the front page.
 * - $logged_in: TRUE if the user is registered and signed in.
 * - $is_admin: TRUE if the user has permission to access administration pages.
 *
 * Site identity:
 * - $front_page: The URL of the front page. Use this instead of $base_path,
 *   when linking to the front page. This includes the language domain or
 *   prefix.
 * - $logo: The path to the logo image, as defined in theme configuration.
 * - $site_name: The name of the site, empty when display has been disabled
 *   in theme settings.
 * - $site_slogan: The slogan of the site, empty when display has been disabled
 *   in theme settings.
 *
 * Navigation:
 * - $main_menu (array): An array containing the Main menu links for the
 *   site, if they have been configured.
 * - $secondary_menu (array): An array containing the Secondary menu links for
 *   the site, if they have been configured.
 * - $breadcrumb: The breadcrumb trail for the current page.
 *
 * Page content (in order of occurrence in the default page.tpl.php):
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title: The page title, for use in the actual HTML content.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 * - $messages: HTML for status and error messages. Should be displayed
 *   prominently.
 * - $tabs (array): Tabs linking to any sub-pages beneath the current page
 *   (e.g., the view and edit tabs when displaying a node).
 * - $action_links (array): Actions local to the page, such as 'Add menu' on the
 *   menu administration interface.
 * - $feed_icons: A string of all feed icons for the current page.
 * - $node: The node object, if there is an automatically-loaded node
 *   associated with the page, and the node ID is the second argument
 *   in the page's path (e.g. node/12345 and node/12345/revisions, but not
 *   comment/reply/12345).
 *
 * Regions:
 * - $page['help']: Dynamic help text, mostly for admin pages.
 * - $page['highlighted']: Items for the highlighted content region.
 * - $page['content']: The main content of the current page.
 * - $page['sidebar_first']: Items for the first sidebar.
 * - $page['sidebar_second']: Items for the second sidebar.
 * - $page['header']: Items for the header region.
 * - $page['footer']: Items for the footer region.
 *
 * @see bootstrap_preprocess_page()
 * @see template_preprocess()
 * @see template_preprocess_page()
 * @see bootstrap_process_page()
 * @see template_process()
 * @see html.tpl.php
 *
 * @ingroup themeable
 */


global $language;
$gofast_url_doc = 'https://gofast-docs.readthedocs.io/en/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html';
if ($language->language == 'fr') {
  $gofast_url_doc = 'https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html';
}
?>

<!-- START  PAGE TEMPLATEE -->

<link rel="stylesheet" href="/sites/all/themes/gofast/assets/fontawesome/css/all.css">
<link rel="stylesheet" href="/sites/all/themes/gofast/css/style.css">

<!-- START  Main Container -->
<div id="go-main-container" class="go-container">

  <!-- START GOFAST Sidebar -->
  <div id="go-main-sidebar"class="go-sidebar">

    <!-- LOGO -->
    <div class="navbar-header" style="margin-left: 0.5%;">
      <?php global $user; ?>
      <?php if ($logo) : ?>
        <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" style="display:inline;" />
        </a>
      <?php endif; ?>

      <?php if (!empty($site_name)) : ?>
        <a class="name navbar-brand" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>"><?php print $site_name; ?></a>
      <?php endif; ?>

      <!-- .btn-navbar is used as the toggle for collapsed navbar content -->
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
    </div>
    <ul class="navbar-nav " id="accordionSidebar">

      <!-- Sidebar - Brand -->
      <a class="d-flex align-items-center justify-content-center p-4 gofast-sidebar-brand" href="index.html">

          <img class="img-fluid" src="/img/logo@2x.png" alt="">


      </a>

      <!-- Divider -->
      <hr class="sidebar-divider my-0">

      <!-- Nav Item - Dashboard -->
      <li class="nav-item">
        <a class="nav-link" href="#">
          <i class="fas fa-fw fa-tachometer-alt"></i>
          <span>Dashboard</span></a>
      </li>
      <li class="nav-item">
        <a class="nav-link" href="#">
          <i class="fas fa-list-alt"></i>
          <span>Activité</span></a>
      </li>

      <!-- Divider -->
      <hr class="sidebar-divider">

      <!-- Nav Item - Pages Collapse Menu -->


      <!-- Annuaire Collapse -->
      <li class="nav-item">
        <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseAnnuaire" aria-expanded="true" aria-controls="collapseTwo">
          <i class="fas fa-network-wired"></i>
          <span>Annuaires</span>
        </a>
        <div id="collapseAnnuaire" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionSidebar">
          <div class="bg-white py-2 collapse-inner rounded">
            <a class="collapse-item" href="#">Groups</a>
            <a class="collapse-item" href="#">Organisation</a>
            <a class="collapse-item" href="#">Extrenet</a>
            <a class="collapse-item" href="#">Public</a>
            <a class="collapse-item" href="gofast_annuaire2.html">Utilisateurs</a>
            <a class="collapse-item" href="#">Contributeurs Actifs</a>
            <a class="collapse-item" href="#">Utilisateurs inactifs</a>
          </div>
        </div>
      </li>


      <!-- Espaces Collapse -->
      <li class="nav-item">
        <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseEspaces" aria-expanded="true" aria-controls="collapseTwo">
          <i class="fas fa-server"></i>
          <span>Mes espaces / Explorateur</span>
        </a>
        <div id="collapseEspaces" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionSidebar">
          <div class="bg-white py-2 collapse-inner rounded">
            <a class="collapse-item" href="#">Explorateur</a>
            <a class="collapse-item" href="#">Extranet</a>
            <a class="collapse-item" href="#">Groupes</a>
            <a class="collapse-item" href="#">Organisation</a>
            <a class="collapse-item" href="#">Public</a>
          </div>
        </div>
      </li>



      <!-- Divider -->
      <hr class="sidebar-divider">


      <!-- Contenu Collapse -->
      <li class="nav-item">
        <a class="nav-link collapsed" href="#" data-toggle="collapse" data-target="#collapseContenu" aria-expanded="true" aria-controls="collapseTwo">
          <i class="fas fa-eye"></i>
          <span>Dernieres Contenus vus </span>
        </a>
        <div id="collapseContenu" class="collapse" aria-labelledby="headingTwo" data-parent="#accordionSidebar">
          <div class="bg-white py-2 collapse-inner rounded">
            <a class="collapse-item text-truncate" href="buttons.html">testrail-report-37.pdf</a>
            <a class="collapse-item text-truncate" href="buttons.html">looper-v1.3.0.zip</a>
            <a class="collapse-item text-truncate" href="cards.html">Next GoFAST</a>
            <a class="collapse-item text-truncate" href="buttons.html">Mon Espace Privé</a>
            <a class="collapse-item text-truncate" href="buttons.html">161201_aife_users.xls.xlsx</a>
            <a class="collapse-item text-truncate" href="buttons.html">Script de démo de la GoFAST 3.docx</a>
            <a class="collapse-item text-truncate" href="buttons.html">Brochure_DUA-LES_ELIMINATION_ 2012.pdf</a>
          </div>
        </div>
      </li>


    </ul>
    <!-- SIDE MENU -->
    <div class="nav-item collapsed m-0">
      <hr class="sidebar-divider my-1">
      <a class="nav-link collapsed" href="#" id="exploreteurToggle">
        <i class="fas fa-folder-open"></i>
        <span>explorateur</span>
      </a>
    </div>
  </div>
  <!-- End GOFAST Sidebar -->

  <!-- START GOFAST CONTAINER -->
  <div id="go-container" class="d-flex flex-column go-wrapper">

    <!-- START NAVBAR -->
    <nav class="d-flex justify-content-between bg-white shadow " id="go-navbar">

      <!-- start nevbar menu -->
      <div class="go-navbar-menu" id="go-navbar-menu">
        <?php print gofast_menu_magical_menu(); ?>
        <?php if (!empty($page['navigation'])) : ?>
          <?php print render($page['navigation']); ?>
        <?php endif; ?>
      </div>
      <!-- end nevbar menu -->

      <!-- start nevbar search -->
      <!-- end nevbar search -->

      <!-- start nevbar params -->
      <div class="go-navbar-params d-flex justify-between" id="go-navbar-params">

        <?php if (isset($lang_switch)) : ?>
          <!-- Gofast language quick switch -->
          <div class="go-navbar-params-lang" id="gofast-lang-switch">
            <?php print $lang_switch; ?>
          </div>
        <?php endif; ?>


        <?php global $user; ?>
        <?php if ($user->uid) { ?>
          <!-- Gofast help Params -->
          <div class="go-navbar-menu-item dropdown">
            <?php if (module_exists("gofast_community")) { ?>
              <?php
              $manifest = gofast_update_get_release_manifest();
              $hotfix_available = gofast_update_get_available_hotfix_version($manifest);
              $version_available = gofast_update_get_available_version($manifest);
              if (!empty($hotfix_available || !empty($version_available))) { ?>
                <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-help-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                  <i class="fas fa-exclamation-circle"></i>
                </a>
              <?php } else { ?>
                <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-help-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                  <i class="far fa-question-circle"></i>
                </a>
              <?php } ?>
            <?php } else { ?>
              <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-help-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                <i class="far fa-question-circle"></i>
              </a>
            <?php } ?>
            <ul class="dropdown-menu " aria-labelledby="go-navbar-menu-help-item">
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
                <a class="center-block sidebar-items ctools-use-modal" href="/gofast/nojs/versions">
                  <div class="list-items-icons"><i class="fa fa-question-circle" style=" color: #777;"></i></div>
                  <p><?php print t('About', array(), array('context' => 'gofast')); ?></p>
                </a>
              </li>
              <li>
                <a class="center-block sidebar-items" href="<?php print $gofast_url_doc; ?>" target="_blank">
                  <div class="list-items-icons"><i class="fa fa-book" style=" color: #777;"></i></div>
                  <p><?php print t('Documentation', array(), array('context' => 'gofast')); ?></p>
                </a>
              </li>
              <li>
                <a class="center-block sidebar-items" href="http://community.ceo-vision.com" target="_blank">
                  <div class="list-items-icons"><i class="fa fa-comments" style=" color: #777;"></i></div>
                  <p><?php print t('Forum', array(), array('context' => 'gofast')); ?></p>
                </a>
              </li>
              <!-- Uncomment when tours are added to PC (not simplified) version -->
              <!-- <li>
                        <a onclick="Gofast.tour.tourButtonAction(event)">
                          <span class="fa-stack fa-1x" style="transform:scale(0.5) translate(-1em,-1em); margin-right:-1em;margin-bottom:-1em">
                            <i class="fa fa-comment fa-stack-2x" style="color:#888"></i>
                            <i class="fa fa-question fa-stack-1x fa-inverse" style="transform:scale(1.5)"></i>
                          </span>
                          <?php // print t('Launch help tour',array(),array('context'=>'gofast_tour'))
                          ?>
                        </a>
                      </li> -->
              <!-- <li>
                          <?php // if($_SERVER['SERVER_NAME'] != $_SERVER['SERVER_ADDR']){
                          ?>
                              <a href=" <?php // global $mobile_url; print $mobile_url
                                        ?>"><i class="fa fa-mobile" aria-hidden="true" style="margin-left: 1px;margin-right: 2px;font-size:17px;color: #777;">  </i><?php // print " "; print t('Mobile version',array(), array('context' => 'gofast'));
                                                                                                                                                                    ?>
                              </a>
                          <?php //} ?>
                      </li> -->
              <?php if (module_exists("gofast_community")) { ?>
                <?php if (!empty($hotfix_available || !empty($version_available))) { ?>
                  <li id="update_gofast">
                    <a href="/admin/config/gofast/update" style='color:#d14;'><i class="fa fa-exclamation-circle" style="color:red;"></i> <?php print t('Update', array(), array('context' => 'gofast')); ?></a>
                  <?php } else { ?>
                  <li>
                    <a href="/admin/config/gofast/update"><i class="fa fa-exclamation-circle" style="color: #777;"></i> <?php print t('Update', array(), array('context' => 'gofast')); ?></a>
                  <?php } ?>
                  </li>
                <?php } ?>
            </ul>
          </div>
        <?php } ?>



      </div>
      <!-- end nevbar params -->
    </nav>
    <!-- END NAVBAR -->



    <div class="d-flex" id="go-main-content">

      <div class="" id="go-explorer">
        <?php
          if (user_is_logged_in()) {
            print(theme('ajax_file_browser_mobile'));
          }
        ?>
      </div>

      <div class="" id="go-ajax-content">

        <div id="ajax_content">

          <!-- RENDER PAGE CONTENT -->
          <?php print render($page['content']); ?>
          <!-- END RENDER PAGE CONTENT -->


        </div>

      </div>

      <div class="" id="go-chat">
      </div>

    </div>


  </div>
   <!-- END GOFAST CONTAINER -->


</div>
<!-- END  Main Container -->



<!-- Verify if dashboard exist-->
<!-- Gofast JS/Overlay placeholders -->
<div id="preview_modal_global" style="position:fixed;top:80px;right:200px;width:550px;"></div>
<span class="gofast-clipboard"></span>
<div id="ctools-add-js"></div>
<div id="backdrop" style="z-index: 1000; display: none;">
  <div class="gofast-throbber">
    <div>
      <div class="loader-ajax">
        <div></div>
        <div></div>
        <div></div>
        <div></div>
        <div></div>
      </div>
      <div style="text-align: center;"><?php print t('Loading...', array(), array('context' => 'gofast')) ?></div>
    </div>
  </div>
</div>
<div id="tempContainerItHit"></div>
<?php
if (user_is_logged_in()) {
  print(theme('ajax_file_browser_mobile'));
}
?>

<script>
  //Triger the mobile file browser navigation when we are ready and connected
  function triggerMobileNavigation() {
    if (typeof Gofast.ITHit === "undefined" || Gofast.ITHit.ready === false || typeof Gofast.ITHitMobile === "undefined") { //Not yet ready
      if (typeof Drupal.settings.pass_reset !== "undefined") {
        //We are in password recovery mode, cancel action !
        jQuery("#file_browser_mobile_container").remove();
        jQuery("#ithit-toggle").remove();
        return;
      }
      setTimeout(triggerMobileNavigation, 1000);
    } else { //Ready !
      if (typeof Drupal.settings.pass_reset !== "undefined") {
        //We are in password recovery mode, cancel action !
        jQuery("#file_browser_mobile_container").remove();
        jQuery("#ithit-toggle").remove();
        return;
      }
      if (!Gofast.mobileNavigationHandled) { //Navigation hasn't already been handled (by node themes for exemple)
        Gofast.ITHitMobile.navigate(Gofast.ITHitMobile.currentPath);
      }
      //Set drag and drop zone for upload
      Gofast.ITHit.UploaderMobile.DropZones.AddById('file_browser_mobile_files');
      //Add events handlers for upload queue
      Gofast.ITHitMobile.attachUploadEvents();
      //Attach browser events
      Gofast.ITHitMobile.attachBrowserEvents();
      //Set margin to main container if needed
      if (Gofast.getCookie('mobile_browser_toggle') === "shown" && parseInt(jQuery('.main-container').css('margin-left')) <= 250 && parseInt(jQuery('.main-container').position().left) <= 250) {
        jQuery(".main-container").css('margin-left', '250px');
      }
    }
  }
  triggerMobileNavigation();
</script>

<!-- Hidden chat actions triggered with JSXC menus -->
<div id="jsxc-hidden-actions" class="">
  <?php print gofast_dropdown_link(t("Add a contact", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/start-conversation', 'start_conversation_open_span', 'ctools-use-modal start-conversation', 'fa fa-user-plus'); ?>
  <br />
  <?php print gofast_dropdown_link(t("Join a space room", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/join-space-room', 'space_room_open_span', 'ctools-use-modal join-space-room', 'fa fa-users'); ?>
  <br />
</div>



<script src="/sites/all/themes/gofast/js/jquery.slim.min.js"></script>
<script src="/sites/all/themes/gofast/js/popper.min.js"></script>
<script src="/sites/all/themes/gofast/js/bootstrap.min.js"></script>
<script src="/sites/all/modules/gofast/js/gofast.js"></script>

<!-- JQUERY MODULES -->
<script src="/sites/all/modules/gofast/gofast_workflows/dynatable/jquery.dynatable.js" type="text/javascript"></script>
<script src="/sites/all/modules/gofast/gofast_workflows/jquery-paginate.min.js" type="text/javascript"></script>

<!-- CUSTOM JS -->
<script src="/sites/all/themes/gofast/js/page.js" type="text/javascript"></script>

<!-- END  PAGE TEMPLATEE -->
