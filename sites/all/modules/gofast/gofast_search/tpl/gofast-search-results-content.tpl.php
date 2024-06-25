<?php

$block = block_load('apachesolr_search', 'sort');
$block_array = _block_render_blocks(array($block));
if (!empty($block_array)) {
    $block_array['apachesolr_search_sort']->subject = '';
    $render_array = _block_get_renderable_array($block_array);
}
?>
<div class="card card-custom card-stretch overflow-hidden searchResultsContent <?= gofast_essential_is_essential() && !gofast_mobile_is_phone() ? "d-none" : ""; ?>" id="gofastSearchResultsContent">
    <?php if(!gofast_essential_is_essential()) :?>
    <div class="card-header d-flex border-0 px-4 pt-4 min-h-40px">
        <div class="card-title flex-grow-1">
            <?php echo drupal_render(drupal_get_form('search_form')); ?>
        </div>
    </div>
    <?php endif; ?>
    <div class="card-body d-flex flex-column h-100 px-0 pb-0 pt-3">
        <?php
            if (!empty($suggestions)):
            // we'll build the suggestion link from the current link not to lose activated search facets
            $actual_link = "https://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
            foreach ($suggestions as $keyword => $suggestion):
                $suggestLinkParsed = "/search/solr/" . $suggestion->suggestion[0]->word;
                if (!empty($_SERVER["QUERY_STRING"])) {
                    // don't keep the ajaxification "url" query param in the suggestion link (just keep the filters)
                    $queryString = preg_replace('/url=[^&?]*/', '', rawurldecode($_SERVER["QUERY_STRING"]));
                    if (!str_starts_with($queryString, "?")) {
                        $queryString = "?" . $queryString;
                    }
                    $suggestLinkParsed .= $queryString;
                }
                ?>
            <div class="px-6 card-text"><?= t('Did you mean') . " <a href='" . $suggestLinkParsed . "'>" . $suggestion->suggestion[0]->word . "</a> " . t('instead of @keyword ?', array("@keyword" => $keyword), array("context" => "gofast:gofast_search")) ?></div>
        <?php
            endforeach;
            endif;
        ?>
        <div id="gofastSearchSortBy" class="px-6 d-flex flex-column justify-content-center align-items-start">
            <div class="my-2 d-flex flex-lg-row align-items-lg-center flex-column align-items-start" style="gap: .5rem;">
                <?php if (!empty($block_array) && $results_count > 0) : ?>
                    <small class="text-truncate"><?= t('Sort by:') ?></small>
                    <div role="group" aria-label="<?= t('Sort by:') ?>">
                    <?php print render($render_array); ?>
                    </div>
                <?php endif; ?>
            </div>
            <div class="d-none" id="searchBoxesCountWrapper">
                <a id="addToCart" type="button" class="btn btn-xs btn-light btn-hover-primary btn-icon mr-2 dropdown-toggle" data-toggle="dropdown">
                    <i class="fas fa-bars"></i>
                </a>
                <ul class="dropdown-menu dropdown-menu-left gofast-dropdown-menu navi navi-hover navi-link-rounded-lg px-1 py-5">
                  <li class="navi-item">
                    <a onClick='Gofast.search.getAlfrescoItemForAddToCart()' class="center-block sidebar-items navi-link" aria-labelledby="addToCart" href="">
                      <span class="navi-icon list-items-icons"><i class="fas fa-shopping-basket" aria-hidden="true"></i></span>
                      <span class="navi-text"><?php echo t('Add search results to cart', array(), array('context' => 'gofast:gofast_search')); ?></span>
                    </a>
                  </li>
                </ul>
                <span class="text-muted"><span id="searchBoxesCount">0</span></span>
            </div>
        </div>
        <div class="px-6 pt-4 h-100 apachesolr_search-results overflow-auto" >
            <?php if ($results_count > 0) : ?>
                <?php print $search_results; ?>
            <?php else : ?>
                <h2><?php print t('Your search yielded no results'); ?></h2>
                <?php print search_help('search#noresults', drupal_help_arg()); ?>
            <?php endif ?>
        </div>
    </div>
    <div class="card-footer py-0 px-3">
        <!--begin::Pagination-->
        <div class="d-flex justify-content-center align-items-center flex-wrap">
            <?php print $pager; ?>
        </div>
        <!--end:: Pagination-->
    </div>
</div>
<script>
    jQuery(document).ready(function() {
        if(Gofast.search.string_nids) {
            Gofast.search.string_nids = undefined;
        }
        
        if(Gofast._settings.isEssential){
            if($("#searchPageLayer").length && $("#gofastSearchResultsContent").hasClass("d-none")){
                $("#gofastSearchResultsContent").removeClass("d-none")
            }
        }
        // show breadcrumbs in spaces tooltips
        jQuery("[data-toggle='search-tooltip']")
            .tooltip({
                template: "<div class=\"tooltip search-tooltip\" role=\"tooltip\"><div class=\"arrow\"></div><div class=\"tooltip-inner\"></div></div>",
                placement: "top",
                html: true,
                title: '<div class="spinner spinner-track spinner-primary d-inline-flex position-absolute"></div>',
            })
            .on('show.bs.tooltip', Gofast.hideTooltipsOnTooltipShowCallback)
            .on("inserted.bs.tooltip", function(e) { 
                if($(e.target).attr("data-loaded")){
                    return;
                }
                const tooltip_nid = $(e.target).attr("data-nid");
                jQuery("[data-toggle='search-tooltip']:not([data-nid='" + tooltip_nid + "'])").tooltip("hide");
                jQuery(".search-tooltip .spinner").css("transform", "translateX(-.75rem)");
            })
            .on("show.bs.tooltip", function(e) {
                $(e.target).attr("data-hidden",false);
            })
            // only load data once
            .on("shown.bs.tooltip", function(e) {
                const tooltip = $(e.target);
                // defensive check to be 100% sure ajax call will not be made twice
                if (tooltip.hasClass("processed")) {
                    return;
                }
                tooltip.addClass("processed");
                const options = {"only_title" : false, "from_tooltip": true, "only_first": true};
                jQuery.get(location.origin + "/gofast/node-breadcrumb/" + tooltip.attr("data-nid") + "?options=" + JSON.stringify(options), function(data) {
                tooltip.data('bs.tooltip').config.title = data;
                tooltip.attr("data-loaded", true);
                if(tooltip.attr("data-hidden") != 'true'){
                    tooltip.tooltip("show");
                }
                });
            })
            .on("hide.bs.tooltip", (e) => {
                $(e.target).attr("data-hidden",true);
            });
    });
</script>
