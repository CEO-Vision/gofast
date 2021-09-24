<?php

/**
 * @file search-results.tpl.php
 * @override default theme implementation for displaying search results.
 *
 * This template collects each invocation of theme_search_result(). This and
 * the child template are dependent to one another sharing the markup for
 * definition lists.
 *
 * Available variables:
 * - $search_results: All results as it is rendered through
 *   search-result.tpl.php
 * - $module: The machine-readable name of the module (tab) being searched, such
 *   as "node" or "user".
 *
 *
 * @see template_preprocess_search_results()
 * @see Gofast Search preprocess function
 *
 * @ingroup themeable
 */

//print '<pre>'. (print_r($variables, 1)) .'</pre>';
?>

<div class="row">
  <div class="col-sm-9">
    <?php
    if ($search_results) : ?>
      <dl class="search-results apachesolr_search-results">
        <?php print $search_results; ?>
      </dl>
      <?php print $pager; ?>

    <?php else : ?>
      <h2><?php print t('Your search yielded no results'); ?></h2>
      <?php print search_help('search#noresults', drupal_help_arg()); ?>
    <?php endif; ?>
  </div>
  <div class="col-sm-3">
    <?php
    if (user_is_logged_in()) {
      print theme('gofast_mobile_panel');
    }
    ?>
  </div>
</div>
