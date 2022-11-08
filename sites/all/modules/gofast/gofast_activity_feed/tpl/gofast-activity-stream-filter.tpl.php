<div class="d-flex flex-column h-100">
    <div class="card card-custom mb-4 p-1" hidden>
        <div class="dropzone dropzone-default dz-clickable p-4" id="fast_drag_drop">
            <div class="dropzone-msg dz-message needsclick m-0">
                <span class="drop-area" id="fast_drag_drop"><?php echo t("Drag&Drop file here", array(), array('context' => 'gofast')); ?></span>
                <script type="text/javascript">
                    Drupal.behaviors.dragdropActivity = {
                        attach: function(context) {
                            //Drupal.gofast_cmis.init_dragdrop(false);
                        }
                    }
                </script>
                <progress id="progress" class="mt-5px w-100" style="display:none;"></progress>
            </div>
        </div>
    </div>

    <div class="card card-custom overflow-auto">
        <!--begin::Header-->
        <div class="card-header border-0 px-4 pt-4 min-h-40px">
            <h3 class="card-title align-items-start flex-column">
                <span class="card-label font-weight-bolder font-size-h4 text-dark-75"><?php echo t('Activity stream filters', array(), array('context' => 'gofast:gofast_views')) ?></span>
            </h3>
            <div class="card-toolbar" hidden>
                <a class="btn btn-icon btn-text-danger btn-hover-light-danger btn-xs gofast_stream_filter_clean_filters"><i class="fas fa-trash-alt"></i></a>
            </div>
        </div>
        <!--end::Header-->

        <!--begin::Body-->
        <div class="card-body py-2 px-0 d-flex flex-column">
            <div class="px-4">
                <tags class="tagify form-control mb-2 p-4" tabindex="-1" id="gofast_activity_stream_filter_tags_container">
                </tags>
            </div>


            <div class="mb-4 px-4">
                <?php foreach ($filters['singleFilters'] as $filter): ?>
                <div class="d-flex w-100 justify-content-between align-items-center py-1">
                    <label class="col-form-label py-0 mr-4"><?php echo $filter['label'] ?></label>
                    <span class="switch switch-icon switch-sm">
                        <label>
                            <input type="checkbox" name="select" class="stream_filter_switch" id="<?php echo $filter['id'] ?>" data-filter="<?php echo $filter['data_filter'] ?>">
                            <span></span>
                        </label>
                    </span>
                </div>
                <?php endforeach ?>
            </div>
            <!--begin::Accordion-->
            <div class="accordion accordion-light accordion-toggle-plus overflow-auto px-4" id="gofast_activity_filter_accordion">

                <?php foreach ($filters['accordionStateFilter'] as $filter): ?>
                <div class="card">
                    <div class="card-header" id="">
                        <div class="card-title collapsed" data-toggle="collapse" data-target="#gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" aria-expanded="false">
                        <i class="<?php echo $filter['icon'] ?>"></i>
                        <?php echo $filter['label'] ?>
                        </div>
                    </div>
                    <div id="gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" class="collapse" style="" data-parent="#gofast_activity_filter_accordion">
                        <div class="card-body navi">
                            <?php foreach($filter['states'] as $state): ?>
                                <li class="navi-item">
                                    <a class="navi-link gofast_stream_filter_state py-1" data-id="<?php echo $state['id'] ?>" data-label="<?php echo $state['label'] ?>" href="#">
                                        <span class="navi-bullet">
                                            <i class="bullet"></i>
                                        </span>
                                        <span class="navi-text"><?php echo $state['label'] ?></span>
                                    </a>
                                </li>
                            <?php endforeach ?>
                        </div>
                    </div>
                </div>
                <?php endforeach ?>

                <?php foreach ($filters['accordionFilter'] as $filter): ?>
                <div class="card">
                    <div class="card-header" id="">
                        <div class="card-title collapsed" data-toggle="collapse" data-target="#gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" aria-expanded="false">
                        <i class="<?php echo $filter['icon'] ?>"></i>
                        <?php echo $filter['label'] ?>
                        </div>
                    </div>
                    <div id="gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" class="collapse" style="" data-parent="#gofast_activity_filter_accordion">
                        <div class="card-body">
                            <div id='' class='tree-demo gofast_stream_filter_ztree' data-tree="<?php echo $filter['data_tree'] ?>"></div>
                        </div>
                    </div>
                </div>
                <?php endforeach ?>

                <?php foreach ($filters['accordionActorsFilter'] as $filter): ?>
                <div class="card">
                    <div class="card-header" id="">
                        <div class="card-title collapsed" data-toggle="collapse" data-target="#gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" aria-expanded="false">
                        <i class="<?php echo $filter['icon'] ?>"></i>
                        <?php echo $filter['label'] ?>
                        </div>
                        </div>
                        <div id="gofast_stream_filter_accordion_<?php echo $filter['id'] ?>" class="collapse" style="" data-parent="#gofast_activity_filter_accordion">
                            <div class="card-body">
                                <div class="input-icon w-100">
                                    <input type="text" name="displayname" class="form-control GofastDirectoryUsersFilter__displayname" id="kt_datatable_search_query" placeholder="<?php echo t('Enter display name') ?>" />
                                    <span>
                                        <i class="flaticon2-search-1 text-muted"></i>
                                    </span>
                                </div>
                            </div>
                            <div id='kt_actors' class='actors-tab gofast_stream_filter_actors datatable datatable-bordered datatable-head-custom' data-columns='<?php echo $columns ?>'></div>
                        </div>
                    </div>
                </div>
                <?php endforeach ?>
            </div>
        <!--end::Accordion-->
    </div>
</div>
