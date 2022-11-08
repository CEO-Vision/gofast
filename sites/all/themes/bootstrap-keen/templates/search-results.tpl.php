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


$page = theme('gofast_search_results_content', ["results" => $results, "search_results" => $search_results, "results_count" => $results_count, "pager" => $pager, "suggestions" => $suggestions]);
$sideContent = theme("gofast_search_results_filter", ["results" => $results, "results_count" => $results_count]);
$page_content = gofast_create_page_content($page, 'content-block-right' , $sideContent);

print $page_content;
