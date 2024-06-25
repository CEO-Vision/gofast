<div id="gofast-search-advanced-page" class="pb-2 pt-2 px-1 d-flex flex-column">
    <div class="accordion accordion-solid accordion-toggle-plus gofastBoostrapPanel" id="accordion1">
        <div class="card">
            <div class="card-header" id="heading1">
                <h5 class="mb-0">
                    <div class="card-title collapsed" data-toggle="collapse" data-target="#collapse1" aria-expanded="false">
                        <?php echo t('Search and history', array(), array('context' => 'gofast:gofast_search_advanced')); ?>
                    </div>
                </h5>
            </div>


            <div id="collapse1" class="collapse show" aria-labelledby="heading1" data-parent="#accordion1">
                <div class="card-body h-600px">
                    <div id="card-search-form-body">
                        <div id="search-form-body" class="mr-5">
                            <?php echo render(drupal_get_form('gofast_search_form')); ?>
                            <?php echo theme('gofast_search_advanced_form'); ?>
                            <div class="separator separator-solid separator-border-4 mt-4"></div>

                            <div id="search-form-specific-section"></div>

                            <div id="search-form-submit-section" class="mt-5 d-flex">
                                <div class="form-item form-type-textfield form-group col-lg-7 col-md-5">
                                    <label><?= t('Search name (to save in history)') ?></label>
                                    <input id="search-name-input" type="text" class="form-control form-control-lg">
                                </div>
                            </div>
                            <div class="d-flex flew-row align-items-center">
                                <button class="btn btn-sm btn-primary mr-2" id="submit-advanced-search"><?php print t('Search') ?></button>
                                <button class="btn btn-sm btn-default mr-2" id="submit-advanced-reset"><i class="fa fa-undo"></i></button>
                                <div class="radio-list" id="global-operator">
                                    <label class="radio radio-rounded">
                                        <input type="radio" name="global-operator" value="and" checked>
                                        <span></span>
                                        <?= t('Satisfy all conditions') ?>
                                    </label>
                                    <label class="radio radio-rounded">
                                        <input type="radio" name="global-operator" value="or">
                                        <span></span>
                                        <?= t('Satisfy at least one condition') ?>
                                    </label>
                                </div>
                            </div>
                        </div>
                        <div id="search-form-history">
                            <label><?= t('Search history'); ?></label>
                            <a href="/modal/nojs/search/advanced/history/clear/confirm" class="btn btn-default btn-sm ml-1 mb-2 ctools-use-modal"><i class="fa fa-trash text-danger"></i></a>
                            <div id="search-history">
                                <?php print theme('gofast_search_advanced_history'); ?>
                            </div>
                        </div>
                    </div>
                </div>

            </div>
        </div>
    </div>
        <div class="card card-custom mt-10">
            <div class="card-header">
                <h3 class="card-title"><?= t('Search results', array(), array('context' => 'gofast:gofast_search_advanced')); ?></h3>
                <div class="card-toolbar">
                    <button id="advanced-search-filter-column" class="btn btn-sm btn-icon btn-primary">
                        <i class="fal fa-cog"></i>
                    </button>
                </div>
            </div>
            <div class="card-body">
                <div class="h-100 w-100 mb-5">
                    <div id="gofastAdvancedSearchResults" class="datatable datatable-bordered datatable-head-custom h-100"></div>
                    <div id="gofastAdvancedSearchBlankSearch"></div>
                </div>
            </div>
        </div>

    <style>
        #card-search-form-body {
            display: grid;
            grid-template-columns: 56% 43%;
            grid-gap: 20px;
            height: 100%;
        }

        #search-form-body {
            grid-column-start: 1;
            overflow-y: scroll;
            height: 100%;
        }

        #search-form-history {
            grid-column-start: 2;
            overflow-y: scroll;
            width: 100%;
            padding-bottom: 20px;
            box-sizing: border-box;
            position: sticky;
            top: 0;
        }

        #search-history {
            border: 1px solid #e4e6ef;
            width: 100%;
            height: 90%;
            padding-top: 10px;
            box-sizing: border-box;
            overflow: scroll;
        }

        #search-history ul li {
            list-style: none;
        }

        .select2-container--default .select2-selection--single .select2-selection__rendered {
            padding: 0px;
        }

        .datatable.datatable-default>.datatable-table{
            overflow: auto !important;
        }

        .GofastTable{
            overflow: auto !important;
        }
        .GofastTable--scroll table tbody{
            overflow: visible !important;
        }
    </style>
