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
<link type="text/css" rel="stylesheet" href="/sites/all/modules/gofast/css/font-awesome.css" media="all">



<?php echo theme($theme_name, array(
  'navbar_classes' => $navbar_classes,
  'logo' => $logo,
  'site_name', $site_name,
  'front_page' => $front_page,
  'page' => $page,
  'search_form_class' => $search_form_class,
  'icon_form_class' => $icon_form_class,
  'lang_switch' => $lang_switch,
  'site_slogan' => $site_slogan,
  'breadcrumb' => $breadcrumb,
  'content_column_class' => $content_column_class,
  'contextual_actions' => $contextual_actions,
  'messages' => $messages,
  'primary_nav' => $primary_nav,
  'secondary_nav' => $secondary_nav,
  'node' => $node,
  'tabs' => $tabs,
  'action_links' => $action_links,
)); ?>

<?php
//$nav_page =  strpos(current_path(), 'tasks_page_navigation') === FALSE ? FALSE : TRUE;
$search_page = strpos(current_path(), 'search/solr') === FALSE ? FALSE : TRUE;
?>

<div class="main-container container Container">

  <header role="banner" id="page-header">
    <?php if (!empty($site_slogan)) : ?>
      <p class="lead"><?php print $site_slogan; ?></p>
    <?php endif; ?>

    <?php print render($page['header']); ?>
  </header>
  <!-- /#page-header -->

  <div class="row Container__mainContent">

      <div class="col-sm-12 col-md-12">

      <section <?php print $content_column_class; ?> id="gofast_over_content">
        <?php print $messages; ?>
        <?php if (!empty($page['highlighted'])) : ?>
          <div class="highlighted jumbotron"><?php print render($page['highlighted']); ?></div>
        <?php endif; ?>

        <div id="messages-placeholder"></div>

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
      </section>

      </div>


    <?php if (!empty($page['sidebar_second'])) :   ?>
      <aside class="col-sm-3" role="complementary" style="width:25%;height:900px;">
        <?php print render($page['sidebar_second']); ?>
      </aside> <!-- /#sidebar-second -->
    <?php endif; ?>
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
      <div style="text-align: center;"><?php print t('Loading...', array(), array('context' => 'gofast')) ?></div>
    </div>
  </div>
</div>

