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
?>

<script src="/sites/all/modules/gofast/gofast_workflows/dynatable/jquery.dynatable.js" type="text/javascript"></script>
<script src="/sites/all/modules/gofast/gofast_workflows/jquery-paginate.min.js" type="text/javascript"></script>

<header id="navbar" role="banner" class="<?php print $navbar_classes; ?>">
  <?php if (isset($lang_switch)): ?>
    <!-- Gofast language quick switch -->
    <div id="gofast-lang-switch">
      <?php print $lang_switch; ?>
    </div>
  <?php endif; ?>
  <div class="navbar-header" style="margin-left: 5%;">
    <?php if ($logo): ?>
    <a class="logo navbar-btn pull-left" href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>">
      <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
    </a>
    <?php endif; ?>

    <?php if (!empty($site_name)): ?>
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
  <div class="container">

    <?php if (!empty($primary_nav) || !empty($secondary_nav) || !empty($page['navigation'])): ?>
        <div class="navbar-collapse collapse">
          <nav id="gofast_nav" role="navigation">
            <?php if (!empty($page['navigation'])): ?>
              <?php print render($page['navigation']); ?>
            <?php endif; ?>
            <?php if (!empty($secondary_nav)): ?>
              <?php print render($secondary_nav); ?>
            <?php endif; ?>
             <?php if (!empty($primary_nav)): ?>
              <?php print render($primary_nav); ?>
            <?php endif; ?>
          </nav>
        </div>

       

<!--      <div id="gofast_book_content" class="gofast_book_content navbar-inverse">
        <a id="gofast_edit_lock" class="btn btn-lg disabled" style="float:right; padding:initial;" href="#">
          <span class="fa fa-lock"></span>
        </a>
        <div id="ztree" class="ztree"></div>
      </div>-->
    <?php endif; ?>
  </div>
  
  <?php global $user; ?>
  <?php if ( $user->uid ) { ?>
    <div class="visible-lg gofast-version-btn">
      <a class="btn btn-sm ctools-use-modal" href="/gofast/nojs/versions" style=" color: #777;">
        <i class="fa fa-question-circle-o fa-2x" aria-hidden="true"></i>
      </a>
    </div>
  <?php } ?>
    
</header>

<div class="main-container container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)): ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header> <!-- /#page-header -->

  <div class="row">

    <?php if (!empty($page['sidebar_first'])): ?>
      <aside class="col-sm-3" role="complementary">
        <?php print render($page['sidebar_first']); ?>
      </aside>  <!-- /#sidebar-first -->
    <?php endif; ?>
    
    <section<?php print $content_column_class; ?> id="gofast_over_content">
      <div id="messages-placeholder"></div>
      <div id="ajax_content">
        <?php if (!empty($page['highlighted'])): ?>
          <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
        <?php endif; ?>
        <?php 
        if (!empty($breadcrumb)): 
          print $breadcrumb; 
        endif;
        ?>
        <?php if (!empty($contextual_actions)): ?>
          <?php // print render($contextual_actions); ?>
        <?php endif; ?>

        <?php print $messages; ?>
        

        <a id="main-content"></a>

        <!-- IF WE HAVE NODE OBJECT, WE WANT TO DELEGATE TITLE IN NODE TPL -->
        <?php if( !isset($node) ): ?>
        <?php endif; ?>
        <?php if (!empty($tabs)): ?>
          <?php print render($tabs); ?>
        <?php endif; ?>
        <?php if (!empty($page['help'])): ?>
          <?php print render($page['help']); ?>
        <?php endif; ?>
        <?php if (!empty($action_links)): ?>
          <ul class="action-links"><?php print render($action_links); ?></ul>
        <?php endif; ?>
        <?php print render($page['content']); ?>
      <div>
    </section>

    <?php //if (!empty($page['sidebar_second'])): ?>
      <aside class="col-sm-3" role="complementary" style="width:25%;height:900px;">           
        <?php print render($page['sidebar_second']); ?>
      </aside>  <!-- /#sidebar-second -->
    <?php //endif; ?>

  </div>
</div>
<footer class="footer container">
  <?php print render($page['footer']); ?>
</footer>

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
      <div style="text-align: center;" ><?php print t('Loading...', array(), array('context' => 'gofast')) ?></div>
    </div>
  </div>
</div>
<div id="tempContainerItHit"></div>
<?php
  if (isset($ajaxFileBrowserMobile)) {
    print $ajaxFileBrowserMobile;
  }
?>