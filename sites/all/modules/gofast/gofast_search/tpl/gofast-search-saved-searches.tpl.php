<div class="card card-custom pb-4 <?php if(gofast_essential_is_essential() && !gofast_mobile_is_phone()){echo "d-none";} ?>">
    <!--begin::Header-->
    <div class="card-header border-0 pt-4 min-h-40px px-2">
        <ul class="nav nav-tabs nav-fill w-100" role="tablist" style="flex-wrap: nowrap;">
            <li class="nav-item">
                <a class="nav-link active d-flex justify-content-between align-items-center px-3" id="searchtab_current" href="#search_current" data-toggle="tab" aria_controls="search_current">
                    <span class="nav-text"><?= t("Current search", array(), array("context" => "gofast")) ?></span><i class="fas fa-search text-primary" style="font-size: 12px;"></i>
                </a>
            </li>
            <li class="nav-item">
                <a class="nav-link d-flex justify-content-between align-items-center px-3" id="searchtab_saved" href="#search_saved" data-toggle="tab" aria-controls="search_saved">
                <span class="nav-text"><?= t("Saved", array(), array("context" => "gofast:gofast_search")) ?></span><i class="fa fa-floppy-o text-primary" style="font-size: 12x;" aria-hidden="true"></i>
                </a>
            </li>
        </ul>
    </div>
    <!--end::Header-->
    <div class="card-body tab-content pt-3 pb-4">
        <div class="tab-pane fade active show" id="search_current" role="tabpanel" aria-labelledby="searchtab_current">
            <div class="d-flex justify-content-between align-items-center mb-2">
                <div>
                    <div class="card-label text-dark-75"><?= $results[0]['keywords'] ?: '' ?></div>
                    <div class="text-muted font-weight-bold font-size-sm"><?= format_plural($results_count, "@count result", "@count results") ?> </div>
                </div>
                <a class="ctools-use-modal" href="/modal/nojs/search/save"><button class="btn btn-icon btn-text-primary btn-hover-light-primary btn-sm"><i class="fa fa-floppy-o text-primary" style="font-size: 12x;" aria-hidden="true"></i></button></a>
            </div>
            <?php $block = module_invoke("current_search", "block_view", "gofast_current_search_block");
                echo render($block["content"]);
            ?>
        </div>
        <div class="tab-pane fade " id="search_saved" role="tabpanel" aria-labelledby="searchtab_saved">
            <?php
            $block = module_invoke('gofast_search', 'block_view', 'gofast_saved_searches');
            print $block['content'];
            ?>
        </div>
    </div>
</div>
