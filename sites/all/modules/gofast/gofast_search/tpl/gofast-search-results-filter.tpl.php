<!-- START gofast-search-results-filter.tpl.php -->
<div class="card card-custom card-stretch card-simplified" id="gofastSearchResultsFilter">    
    <?= theme("gofast_search_saved_searches", ["results" => $results, "results_count" => $results_count]) ?>
    <div class="card card-custom overflow-auto <?php if(gofast_essential_is_essential() && !gofast_mobile_is_phone()){echo "d-none";} ?>">
        <!--begin::Header-->
        <div class="card-header border-0 pt-4 px-3 min-h-40px">
            <h3 class="card-title">
                <span class="card-label font-weight-bolder font-size-h4 text-dark-75"><?= t("Search Filters") ?></span>
            </h3>
        </div>
        <!--end::Header-->
        <div class="card-body d-flex flex-column px-0 pt-1 pb-4" id="facetapi_search_filters">
            <div class="px-3">
                <?php
                $options = [];
                $strict_default_value = $_COOKIE["strict_search"];
                if ($strict_default_value == "true" || !isset($_COOKIE["strict_search"])) {
                    $strict_default_value = 1;
                } else {
                    $strict_default_value = 0;
                }
                $options["strict"] = [
                    "value" => $strict_default_value,
                    "title" => t("Strict search", array(), array("context" => "gofast:gofast_search")),
                    "help" => t("A strict search means all keywords are mandatories ( except if they start by - ) and they must be exactly the same as on the document", array(), array("context" => "gofast:gofast_search"))
                ];
                foreach (gofast_search_options() as $name => $option) {
                    $options[$name] = $option;
                }
                foreach ($options as $name => $option) :
                    if (!empty($option['title']) && ($name === "strict" || $name === "retain-filters")) :    
                ?>
                        <div class="w-100 justify-content-between align-items-center py-1 d-flex">
                            <div>
                                <label title="<?= $option['title'] ?>" class="col-form-label py-0"><?= $option['title'] ?></label>
                                <?php if (isset($option["help"])) { ?>
                                    <i title="<?= $option["help"]; ?>" class="fa fa-question-circle" style=" color: #777;cursor:pointer;"></i>
                                <?php } ?>
                            </div>
                            <span class="switch switch-icon switch-sm">
                                <label>
                                    <input type="checkbox" item=<?= $name ?> class="stream_filter_switch" <?php if ($option['value'] == "1") { echo 'checked'; } ?>>
                                    <span></span>
                                </label>
                            </span>
                        </div>
                <?php
                    endif;
                endforeach;
                ?>
                <div class="px-3 overflow-auto mt-4 accordion accordion-light accordion-toggle-plus">
                    <div class="card">
                        <div class="card-header">
                            <div data-target="#filter-standard-apachesolrgofast-solr-block" data-toggle="collapse" class="card-title p-0 pt-5 collapsed cursor-pointer d-flex justify-content-between align-items-center">
                                <?php print (t("General filters", array(), array('context' => 'gofast'))); ?>
                            </div>
                        </div>
                        <div class="card-body">
                            <section  class="block block-facetapi contextual-links-region facetapi-collapsible clearfix facetapi-collapsible-processed navi clearfix">
                                <ul class="facetapi-gofast-facetapi-links facetapi-facet-created facetapi-collapsible collapse facetapi-collapsible-processed navi"  id="filter-standard-apachesolrgofast-solr-block" >
                                    <?php foreach ($options as $name => $option)  :
                                    if (!empty($option['title']) && ($name !== "strict"  && $name !== "retain-filters")) :
                                    ?>
                                        <div class="w-100 justify-content-between align-items-center py-1 d-flex">
                                            <div>
                                                <label title="<?= $option['title'] ?>" class="col-form-label py-0"><?= $option['title'] ?></label>
                                                <?php if (isset($option["help"])) { ?>
                                                    <i title="<?= $option["help"]; ?>" class="fa fa-question-circle" style=" color: #777;cursor:pointer;"></i>
                                                <?php } ?>
                                            </div>
                                            <span class="switch switch-icon switch-sm">
                                                <label>
                                                    <input type="checkbox" item=<?= $name ?> class="stream_filter_switch" <?php if ($option['value'] == "1") { echo 'checked'; } ?>>
                                                    <span></span>
                                                </label>
                                            </span>
                                        </div>
                                        <?php 
                                    endif;
                                    endforeach;?>
                                </ul>
                            </section>
                        </div>
                    </div>
                    <?php
                    // we load the deltas directly from the db to avoid issues with ajaxification
                    $deltas = gofast_facetapi_get_deltas_from_db();
                    foreach ($deltas as $delta) {
                        // then we load the blocks matching the deltas, avoiding module_invoke() which tends to skip some hooks...
                        $block_load = block_load("facetapi", $delta);
                        $block_content = _block_render_blocks(array($block_load));
                        $build = _block_get_renderable_array($block_content);
                        // ... and render them on the fly
                        echo drupal_render($build["facetapi_$delta"]);
                    }
                    ?>
                </div>
            </div>
        </div>
    <?php $detect = new Mobile_Detect(); ?>
    </div>
</div>
<?php if (gofast_essential_is_essential() && !gofast_mobile_is_phone()) : ?> 
<div id="filterSideButton" class="<?= gofast_essential_is_essential()  ? "expand" : "invisible" ?>" onclick="Gofast.Essential.toggleSearchFilterTab()"> 
    <i class="fas fa-2x fa-filter"></i>
    <i class="fa fa-2x fa-chevron-left"></i>
</div>  
<?php endif; ?>

 <?php if ($detect->isTablet()|| $detect->isMobile()): ?>
    <style>
      .GofastNodeOg{
        padding-right: 68px !important;
      }
    </style>
<?php endif; ?>

<!-- END gofast-search-results-filter.tpl.php -->
