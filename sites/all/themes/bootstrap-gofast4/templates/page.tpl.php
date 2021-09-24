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

global $language;
$gofast_url_doc = 'https://gofast-docs.readthedocs.io/en/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html';
if ($language->language == 'fr') {
  $gofast_url_doc = 'https://gofast-docs.readthedocs.io/fr/latest/docs-gofast-users/doc-gofast-guide-utilisateurs.html';
}
?>


<?php if (isset($conf['gofast-atatus-key'])) : ?>
  <?php
  global $base_url;
  $http_bind_url = 'https://' . $conf['gofast-comm_domain'] . '/http-bind';
  $poll_url = $base_url . "/gofast/poll";
  ?>
  <script src="//dmc1acwvwny3.cloudfront.net/atatus-spa.js?v=4.0.3"></script>
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


<div class="page-main-container" id="page">


  <!-- START SIDEBAR -->
  <div id="sidebar" class="sidebar ">
    <div class="sidebar-logo-container ">
      <?php global $user; ?>
      <?php if ($logo) : ?>
        <a class="sidebar-logo" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" class="sidebar-logo-image" />
        </a>
      <?php endif; ?>
    </div>
    <!-- START sidebar region -->
      <?php print render($page['sidebar']); ?>
    <!-- END sidebar region -->
  </div>
  <!-- END SIDEBAR -->


  <!-- START main-container -->
  <div id="main-container" class="main-container">
    <!-- START navigation region -->
    <div id="navigation" class="navigation">
      <?php if (!empty($page['navigation'])) : ?>
        <?php print render($page['navigation']); ?>
      <?php endif; ?>

    </div>
    <!-- END navigation region -->

    <!-- START page main content -->
    <div class="page-container">
      <!-- START EXPLORER -->
      <?php if($user->uid != 0): ?>
        <div id="explorer" class="explorer ">
          <div id="explorer-toggle" class="btn btn-light"><i class="fas fa-chevron-right"></i></div>

          <div class="explorer-main-container">
            <!-- Nav tabs -->
            <ul class="nav nav-tabs" role="tablist">
              <li class="nav-item active">
                <a class="nav-link" id="explorer-file-browser" data-toggle="tab" href="#file-browser" role="tab" aria-controls="file-browser" aria-selected="true">Explorer</a>
              </li>
              <li class="nav-item">
                <a class="nav-link" id="explorer-wiki" data-toggle="tab" href="#wiki" role="tab" aria-controls="wiki" aria-selected="false">Wikis</a>
              </li>
              <li class="nav-item">
                <a class="nav-link" id="explorer-forum" data-toggle="tab" href="#expl-forum" role="tab" aria-controls="forum" aria-selected="false">Forums</a>
              </li>
            </ul>
            <?php $explorer = render($page['explorer']); ?>
            <!-- Tab panes -->
            <div class="tab-content">
              <div class="tab-pane active" id="file-browser" role="tabpanel" aria-labelledby="explorer-file-browser">
                <!-- START explorer region -->
                <?php print $explorer; ?>
                <!-- END explorer region -->
              </div>
              <div class="tab-pane" id="wiki" role="tabpanel" aria-labelledby="explorer-wiki">
                <!-- START explorer region -->
                <?php //Potentially add a way to either view the book on article or comments otherwise
                print gofast_book_block_view('gofast_book_group')['content'];
                ?>
                <!-- END explorer region -->
              </div>
              <div class="tab-pane" id="expl-forum" role="tabpanel" aria-labelledby="explorer-forum">
                <!-- START explorer region -->
                <?php
                print gofast_forum_get_forums_view();
                ?>
                <!-- END explorer region -->
              </div>
              <!-- <div class="tab-pane" id="settings" role="tabpanel" aria-labelledby="settings-tab">...</div> -->
            </div>
          </div>
        </div>
      <?php endif; ?>
      <!-- END EXPLORER -->
      <!-- START CONTENT -->
      <div class="content">
        <div class="main-container container content-main-contianer" id="content-main-container">



          <?php if (!empty($page['sidebar_first'])) : ?>
            <div class="content-main-contianer--sidebar" role="complementary">
              <?php print render($page['sidebar_first']); ?>
            </div>
            <!-- /#sidebar-first -->
          <?php endif; ?>

          <section class="content-main-contianer--content" id="gofast_over_content">
            <div id="messages-placeholder"></div>
            <div id="ajax_content">
              <?php if (!empty($page['highlighted'])) : ?>
                <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
              <?php endif; ?>
              <?php
              if (!empty($breadcrumb)) :
                print $breadcrumb;
              endif;
              ?>
              <?php if (!empty($contextual_actions)) : ?>
                <?php print render($contextual_actions); ?>
              <?php endif; ?>

              <?php print $messages; ?>


              <a id="main-content"></a>

              <!-- IF WE HAVE NODE OBJECT, WE WANT TO DELEGATE TITLE IN NODE TPL -->
              <?php if (!isset($node)) : ?>
              <?php endif; ?>
              <?php if (!empty($tabs)) : ?>
                <?php print render($tabs); ?>
              <?php endif; ?>
              <?php if (!empty($page['help'])) : ?>
                <?php print render($page['help']); ?>
              <?php endif; ?>
              <?php if (!empty($action_links)) : ?>
                <ul class="action-links"><?php print render($action_links); ?></ul>
              <?php endif; ?>
              <?php
              global $user;
              if ($user->uid == 0) {
                if ($page['content']["system_main"]["main"]["#markup"] == "Access denied") {
                  $page['content']["system_main"]["main"]["#markup"] = "";
                }
              }
              ?>
              <?php print render($page['content']); ?>
            </div>
          </section>

          <aside class="col-sm-3 content-main-contianer--sidebar" role="complementary">
            <?php print render($page['sidebar_second']); ?>
          </aside>
          <!-- /#sidebar-second -->

        </div>
      </div>
      <!-- END CONTENT -->
      <!-- START RIOT -->
      <div id="riot">
        <?php print render($page['riot']); ?>
        <header role="banner" id="page-header">
          <?php if (!empty($site_slogan)) : ?>
            <p class="lead"><?php print $site_slogan; ?></p>
          <?php endif; ?>

          <?php print render($page['header']); ?>
        </header>
      </div>
      <!-- END RIOT -->
    </div>
    <!-- END page main content -->
  </div>
  <!-- END main-container -->
</div>

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
<div id="jsxc-hidden-actions">
  <?php print gofast_dropdown_link(t("Add a contact", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/start-conversation', 'start_conversation_open_span', 'ctools-use-modal start-conversation', 'fa fa-user-plus'); ?>
  <br />
  <?php print gofast_dropdown_link(t("Join a space room", array(), array('context' => "gofast:gofast_chat")), '/modal/nojs/join-space-room', 'space_room_open_span', 'ctools-use-modal join-space-room', 'fa fa-users'); ?>
  <br />
</div>



<script src="/sites/all/themes/bootstrap-gofast4/js/core/page.js" type="text/javascript"></script>
<script src="/sites/all/themes/bootstrap-gofast4/js/components/dropdown.js" type="text/javascript"></script>
