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
global $conf;
global $user;
$detect = new Mobile_Detect();
$is_mobile = ($detect->isMobile() || $detect->isTablet() || $detect->is('iPad') || gofast_mobile_is_mobile_domain());
$is_mobile_device = ($detect->isMobile() || $detect->isTablet() || $detect->is('iPad'));
global $user;
$gofast_url_doc = "https://gofast-docs.readthedocs.io/" . $user->language . "/4.0/docs-gofast-users/doc-gofast-guide-utilisateurs.html";
?>

<?php
global $base_url;
$http_bind_url = 'https://' . $conf['gofast-comm_domain'] . '/http-bind';
$poll_url = $base_url . "/gofast/poll";
// weirdness of strpos() forces us to make a !false check, happily when we'll upgrade to PHP8 we'll have str_contains()
if (!strpos($_SERVER['REQUEST_URI'], 'search/solr') === FALSE) {
  // one part of the urlencode (but not the entirety of it) messes up with the apachesolr request when the facetapi query string is present
  // we workaround this issue here
  $search_url = str_replace("%20", " ", str_replace("52", "", $_SERVER['REQUEST_URI']));
  // but REQUEST_URI converts back " " into "%20" so we re-replace it to prevent an infinite redirect loop
  // this has to be the ugliest workaround ever
  if ($search_url !== str_replace("%20", " ", $_SERVER['REQUEST_URI'])) header("Location: $search_url");
}
?>

<?php //if (FALSE) : ?>
<?php if (isset($conf['gofast-atatus-key'])) : ?>
    <script src="https://dmc1acwvwny3.cloudfront.net/atatus-spa.js"></script>
  <script type="text/javascript">
    atatus.config('<?php echo variable_get('gofast-atatus-key'); ?>', {
      ignoreUrls: ['<?php echo $http_bind_url; ?>', '<?php echo $poll_url; ?>']
    }).install();

    var atatusInterval = setInterval(function() {
      if (typeof Gofast == "object" &&
        typeof Gofast._settings == "object" &&
        typeof Gofast._settings.gofast_version == "string" &&
        typeof Gofast._settings.gofast == "object" &&
        typeof Gofast._settings.gofast.user == "object" &&
        typeof Gofast._settings.gofast.user.uid == "string") {
        atatus.setVersion(Gofast._settings.gofast_version);
        atatus.setUser(Gofast._settings.gofast.user.uid);
        clearInterval(atatusInterval);
      }
    }, 500);
  </script>
<?php endif; ?>
<link rel="stylesheet" href="/sites/all/libraries/flag-icon-css/css/flag-icon.css">

<script src="/sites/all/modules/gofast/gofast_workflows/dynatable/jquery.dynatable.js" type="text/javascript"></script>
<script src="/sites/all/modules/gofast/gofast_workflows/jquery-paginate.min.js" type="text/javascript"></script>

<?php if (!$user->login) : ?>
  <div id="page" class="h-100">
    <div class="d-flex flex-column flex-root h-100">
      <!--begin::Login-->
      <div class="login login-1 login-signin-on d-flex flex-column flex-lg-row flex-column-fluid bg-white" id="kt_login">
        <!--begin::Aside-->
          <?php if (!$is_mobile_device) : ?>
        <div class="login-aside d-flex flex-column flex-row-auto" style="background-color: #337ab7;">
          <!--begin::Aside Top-->
          <div class="d-flex flex-column-auto flex-column pt-15">
            <!--begin::Aside header-->
            <a href="#" class="text-center mb-15">
              <img src="/sites/all/themes/bootstrap-keen/Logo_GoFAST de CEO-Vision_fr_blanc.png" alt="logo" class="h-70px">
            </a>
            <!--end::Aside header-->
            <!--begin::Aside title-->
            <h3 class="font-weight-bolder text-center font-size-h4 font-size-h1-lg text-white">
              TECHNOLOGY MADE SIMPLE
            </h3>
            <!--end::Aside title-->
          </div>
          <!--end::Aside Top-->
          <!--begin::Aside Bottom-->
          <div class="aside-img d-flex flex-row-fluid bgi-no-repeat bgi-position-y-bottom bgi-position-x-center" style="background-image: url(/sites/all/themes/bootstrap-keen/keenv2/assets/media/svg/illustrations/gofast-login.png);background-size: contain;"></div>
          <!--end::Aside Bottom-->
        </div>
          <?php endif; ?>
        <!--end::Aside-->
        <!--begin::Content-->
        <div class="login-content flex-row-fluid d-flex flex-column justify-content-center position-relative overflow-hidden p-7 mx-auto">
          <!--begin::Content body-->
          <div class="d-flex flex-column-fluid flex-center">
            <!--begin::Signin-->
            <div class="content-main-contianer d-flex h-100 w-100 justify-content-center" id="content-main-container">
              <div class="my-20" style=" width: 100%;">
                <div id="ajax_content">
                  <div id="block-user-login-messages">
                    <?php print $messages; ?>
                  </div>
                  <?php print render($page['content']); ?>
                </div>
              </div>
            </div>
            <!--end::Signin-->
            <!--begin::Signup-->
            <!--end::Signup-->
            <!--begin::Forgot-->
            <!--end::Forgot-->
          </div>
          <!--end::Content body-->
          <div class="login-footer__container d-flex justify-content-center align-items-end py-7 py-lg-0">
           <span class="login-footer font-weight-bolder font-size-h6 mr-1 "><i class="fas fa-2x fa-comments mr-2 align-middle" aria-hidden="true"></i><a href="https://community.ceo-vision.com" target="#blank" class="text-primary font-weight-bolder font-size-h5"><?php print t('Any question?'); ?></a></span>
           <span class="login-footer font-weight-bolder font-size-h6 ml-10 mr-2"> <i class="fas fa-2x fa-book mr-2 align-middle" aria-hidden="true"></i><a href="https://gofast-docs.readthedocs.io/<?= $user->language ?>/4.0/docs-gofast-users/doc-gofast-guide-utilisateurs.html" target="#blank" class="text-primary font-weight-bolder font-size-h5"><?php print t('Documentation') ?></a></span>
          </div>
        </div>
        <!--end::Content-->
      </div>
      <!--end::Login-->
    </div>

    <!--end::Login-->
  </div>
<?php else : ?>
  <div id="page" class="h-100 overflow-hidden">
    <!--begin::Main-->
    <!--begin::Header Mobile-->
    <?php echo theme('gofast_menu_header_mobile'); ?>
    <!--end::Header Mobile-->
    <div class="d-flex flex-column flex-root h-100">
      <!--begin::Page-->
      <div class="d-flex flex-row flex-column-fluid page h-100">
        <!--begin::Aside-->
        <?php echo theme('gofast_menu_aside'); ?>
        <!--end::Aside-->
        <!--begin::Wrapper-->
        <div class="d-flex flex-column flex-row-fluid wrapper" id="kt_wrapper" <?php if ($is_mobile) : ?>style="height: 100%;"<?php endif; ?>>
          <!--begin::Header-->
          <?php echo theme('gofast_menu_header'); ?>
          <!--end::Header-->
          <!--begin::Content-->
          <div class="content-main-contianer d-flex h-100 position-relative" <?= $is_mobile_device ? "style='padding-right: 0;'" : "" ?> id="content-main-container">
            <?php if (!$is_mobile) : ?>
            <!-- START EXPLORER -->
            <?php if($user->uid != 0): ?>
              <div id="explorer" class="explorer ">
                <div id="explorer-toggle" class=""><i class="fas fa-chevron-right"></i></div>

                <div class="explorer-main-container">
                  <!-- Nav tabs -->
                  <ul class="nav nav-tabs" role="tablist">
                    <li class="nav-item active">
                      <a class="nav-link py-6" id="explorer-file-browser" data-toggle="tab" href="#file-browser" role="tab" aria-controls="file-browser" aria-selected="true">Explorer</a>
                    </li>
                    <li class="nav-item">
                      <a class="nav-link py-6" id="explorer-wiki" data-toggle="tab" href="#wiki" role="tab" aria-controls="wiki" aria-selected="false">Wikis</a>
                    </li>
                    <li class="nav-item">
                      <a class="nav-link py-6" id="explorer-forum" data-toggle="tab" href="#expl-forum" role="tab" aria-controls="forum" aria-selected="false">Forums</a>
                    </li>
                  </ul>
                  <?php $explorer = render($page['explorer']); ?>
                  <!-- Tab panes -->
                  <div class="tab-content pb-4 overflow-auto flex-fill">
                    <div class="tab-pane active" id="file-browser" role="tabpanel" aria-labelledby="explorer-file-browser">
                      <!-- START explorer region -->
                      <?php print $explorer; ?>
                      <!-- END explorer region -->
                    </div>
                    <div class="tab-pane" id="wiki" role="tabpanel" aria-labelledby="explorer-wiki">
                      <!-- START explorer region -->
                      <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl position-absolute" style="top: calc(50% - 6em); left: calc(50% - 4em);"></div>
                      <!-- END explorer region -->
                    </div>
                    <div class="tab-pane" id="expl-forum" role="tabpanel" aria-labelledby="explorer-forum">
                      <!-- START explorer region -->
                        <?php
                           // print gofast_forum_get_forums_view();
                        ?>
                      <!-- END explorer region -->
                    </div>
                    <!-- <div class="tab-pane" id="settings" role="tabpanel" aria-labelledby="settings-tab">...</div> -->
                  </div>
                </div>
              </div>
            <?php endif; ?>
            <!-- END EXPLORER -->
            <?php endif; ?>
            <div id="gofast_over_content"  class="h-100 <?php if($is_mobile_device) echo "gofast_over_content_mobile" ?>">
              <div id="ajax_content" class=" h-100">
                <?php print render($page['content']); ?>
              </div>
            </div>
              <?php if (!$is_mobile_device) : ?>
            <!-- START RIOT -->
            <div id="riot">
              <?php print render($page['riot']); ?>
            </div>
            <!-- END RIOT -->
              <?php endif; ?>
          </div>
          <!--end::Content-->
          <!--begin::Footer-->
          <footer class="footer container d-none">
            <?php print render($page['footer']); ?>
          </footer>
          <!--end::Footer-->
        </div>
        <!--end::Wrapper-->
      </div>
      <!--end::Page-->
    </div>
    <!--end::Main-->
  </div>
<?php endif; ?>



<div><?php print gofast_modal_prepare_modal(); ?></div>

<!-- Gofast JS/Overlay placeholders -->
<div id="preview_modal_global" style="position:fixed;top:50vh;left:50vw;transform: translate(-50%, -50%);width: 50%; height: auto;"></div>
<span class="gofast-clipboard"></span>
<div id="ctools-add-js"></div>
<div id="backdrop" style="z-index: 10000; display: none;">
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
      if (jQuery("#file_browser_mobile_files").length !== 0) {
        Gofast.ITHit.UploaderMobile.DropZones.AddById(
          "file_browser_mobile_files"
        );
      }
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
  // some versions of FF seem to append "=" to the hash, breaking the navigation
  if (location.hash.length && location.hash.slice(-1) == "=") {
    location.hash = location.hash.slice(0, -1);
  }
</script>

<!-- Hidden chat actions triggered with JSXC menus -->
<div id="jsxc-hidden-actions">
  <?php print gofast_dropdown_link(t("Add a contact", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/start-conversation', 'start_conversation_open_span', 'ctools-use-modal start-conversation', 'fa fa-user-plus'); ?>
  <br />
  <?php print gofast_dropdown_link(t("Join a space room", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/join-space-room', 'space_room_open_span', 'ctools-use-modal join-space-room', 'fa fa-users'); ?>
  <br />
  <?php
  $count = count(user_relationships_load(array("requestee_id" => $user->uid, "approved" => 0)));
  $context = gofast_get_context();
  $context['relationship_count'] = $count;
  gofast_set_context($context);
  if ($count > 0) {
    $class = "class='jsxc-count-highlight'";
  }
  print gofast_dropdown_link(t("Manage my relations", array(), array('context' => "gofast:gofast_chat")) . "<span id='relations-count' " . $class . ">(" . $count . ")</span>", '/modal/nojs/manage-relations', 'manage_relations_open_span', 'ctools-use-modal manage-relations', 'fa fa-address-book');
  ?>
</div>

<?php
// import core scripts for bootstrap-keen theme
drupal_add_js(drupal_get_path('theme', 'bootstrap_keen') . '/js/core/page.js');
drupal_add_js(drupal_get_path('theme', 'bootstrap_gofast4') . '/js/components/dropdown.js');
?>

<style>
  ::-webkit-scrollbar{
    width: 5px;
    height: 5px;
    }
::-webkit-scrollbar-thumb{
    background: rgba(200,200,200, 0.2);
    border-radius: 5px;
}
::-webkit-scrollbar-thumb:hover{
    background: rgba(200,200,200, 0.4);
}
::-webkit-scrollbar-track{
    background: #ffffff00;
}
</style>
