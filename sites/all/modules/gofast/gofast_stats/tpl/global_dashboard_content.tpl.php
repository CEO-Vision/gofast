<div class="card card-custom mt-4">
  <div class="card-body p-0">
    <!-- HEADER (Horizontal tabs) -->
    <ul class="nav nav-tabs nav-fill justify-content-center" id="myTab1" role="tablist">
        <li class="nav-item w-90px mx-5">
          <a class="nav-link px-2 d-flex justify-content-center" id="users_stats_header" aria-controls="users_stats" data-toggle="tab" href="#users_stats">
            <span class="nav-icon">
              <i class="fas fa-users n-color"></i>
            </span>
            <span class="nav-text"><?php print t('Users statistics', array(), array('context' => 'gofast:stats')); ?></span>
          </a>
        </li>

        <li class="nav-item w-90px mx-5">
          <a class="nav-link px-2 d-flex justify-content-center" id="documents_stats_header" aria-controls="documents_stats" data-toggle="tab" href="#documents_stats">
            <span class="nav-icon">
              <i class="fas fa-file"></i>
            </span>
            <span class="nav-text"><?php print t('Documents statistics', array(), array('context' => 'gofast:stats')); ?></span>
          </a>
        </li>

        <li class="nav-item w-90px mx-5">
          <a class="nav-link px-2 d-flex justify-content-center" id="spaces_stats_header" aria-controls="spaces_stats" data-toggle="tab" href="#spaces_stats">
            <span class="nav-icon">
              <i class="fas fa-sitemap n-color"></i>
            </span>
            <span class="nav-text"><?php print t('Spaces statistics', array(), array('context' => 'gofast:stats')); ?></span>
          </a>
        </li>
    </ul>

    <!-- Content -->
    <div class="tab-content" id="myTabContent1">
        <div class="tab-pane fade" id="users_stats" role="tabpanel" aria-labelledby="users_stats_header">
          <div class="card card-custom p-1">
            <div class="card-body">
              <div id="users_stats_container" class="stats_container panel panel-default" style="margin: 0">
                <div class="panel-body">
                  <div id="users_stats_filter">
                    <?php print drupal_render(drupal_get_form('gofast_stats_global_filter_users_form')); ?>
                  </div>
                  
                  <hr />
                  <div class="card card-custom shadow-sm mx-5" style="height: 45rem;">
                    <div class="card-header">
                      <h3 class="card-title"><?= t("Created users and logins") ?></h3>
                    </div>
                    <div id="users_chart_container" class="pb-6 card-body d-flex flex-column">
                      <div class="d-flex justify-content-between">
                        <div id="user_chart_container_mode_buttons" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button id="user_charts_btn_group_evolution" type="button" data-filter="evolution" class="btn btn-default"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="user_charts_btn_group_periodic" type="button" data-filter="periodic" class="btn btn-default default-value"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="user_chart_container_period_buttons" class="btn-group btn-group-sm" role="group" aria-label="...">
                          <button id="user_charts_btn_group_1w" type="button" data-filter="1week" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="user_charts_btn_group_1m" type="button" data-filter="1month" class="btn btn-default default-value"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="user_charts_btn_group_1y" type="button" data-filter="1year" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="user_charts_btn_group_2y" type="button" data-filter="2year" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="user_charts_btn_group_3y" type="button" data-filter="3year" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                      </div>
                      <div class="d-flex stats-container flex-grow-1">
                        <div class="stats-loader-container">
                          <div class="loader-blog"></div>
                        </div>
                      </div>
                    </div>
                  </div>
                  <div class="d-flex justify-content-between mx-5 mt-5 mb-10">
                      <div id="users-doughnut-container" class="col-4 mr-5 d-flex flex-column justify-content-between px-0">
                          <div class="card card-custom shadow-sm mb-5">
                            <div class="card-header">
                              <h3 class="card-title"><?= t("Users status") ?></h3>
                            </div>
                            <div id="users_doughnut_state_container" class="w-100 d-flex align-items-center justify-content-center">
                              <div class="stats-loader-container">
                                <div class="loader-blog"></div>
                              </div>
                            </div>
                          </div>
                          <div class="card card-custom shadow-sm">
                            <div class="card-header">
                              <h3 class="card-title"><?= t("Users activity") ?></h3>
                            </div>
                            <div id="users_doughnut_active_container" class="w-100 d-flex align-items-center justify-content-center">
                              <div class="stats-loader-container">
                                <div class="loader-blog"></div>
                              </div>
                            </div>
                          </div>
                      </div>
                      <div class="card card-custom shadow-sm flex-grow-1">
                        
                          <div class="card-header">
                            <h3 class="card-title"><?= t("Users roles") ?></h3>
                          </div>
                          <div id="users_doughnut_role_container" class="h-100 d-flex">
                            <div class="stats-loader-container">
                              <div class="loader-blog"></div>
                            </div>
                          </div>
                      </div>
                  </div>
                </div>

              </div>
            </div>
          </div>
        </div>

        <div class="tab-pane fade" id="documents_stats" role="tabpanel" aria-labelledby="documents_stats_header">
          <div class="card card-custom p-1">
            <div class="card-body">
              <div id="documents_stats_container" class="panel panel-default stats_container" style="margin: 0">
                <div class="panel-body">
                  <div id="documents_chart_container" class="gutter-b card card-custom shadow-sm">
                    <div class="card-header">
                      <h2 class="card-title"><?php print t("Documents count over time") ?></h2>
                    </div>
                    <div class="card-body">
                      <div class="d-flex justify-content-between">
                        <div id="documents_chart_container_mode_buttons" class="btn-group btn-group-sm" role="group" >
                            <button id="space_document_charts_btn_group_evolution" type="button" data-filter="evolution" class="btn btn-default document_charts_btn_group_evolution default-value"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_document_charts_btn_group_periodic" type="button" data-filter="periodic" class="btn btn-default document_charts_btn_group_periodic"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="documents_chart_container_period_buttons" class="btn-group btn-group-sm" role="group" >
                            <button id="space_document_charts_btn_group_1w" type="button" data-filter="1week" class="btn btn-default document_charts_btn_group_1w"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_document_charts_btn_group_1m" type="button" data-filter="1month" class="btn btn-default document_charts_btn_group_1m default-value"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_document_charts_btn_group_1y" type="button" data-filter="1year" class="btn btn-default document_charts_btn_group_1y"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_document_charts_btn_group_2y" type="button" data-filter="2year" class="btn btn-default document_charts_btn_group_2y"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_document_charts_btn_group_3y" type="button" data-filter="3year" class="btn btn-default document_charts_btn_group_3y"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                      </div>
                    </div>
                    <div class="d-flex stats-container pb-4" style="min-height: 30rem;">
                      <div class="stats-loader-container">
                        <div class="loader-blog"></div>
                      </div>
                    </div>
                  </div>
                  <div id="documents_doughnuts_container" class="d-flex justify-content-between gutter-b">
                    <div id="documents_doughnut_storage_container" class="card card-custom shadow-sm col-6 mr-4 px-0">
                      <div class="card-header">
                        <h2 class="card-title"><?php print t("Storage") ?></h2>
                      </div>
                      <div class="documents-doughnuts-box">
                        <div class="stats-loader-container">
                          <div class="loader-blog"></div>
                        </div>
                        <div id="documents_doughnut_storage" class="d-none"></div>
                      </div>
                    </div>
                    <div id="documents_doughnut_indexation_container" class="card card-custom shadow-sm flex-grow-1">
                      <div class="card-header">
                        <h2 class="card-title"><?php print t("Indexing") ?></h2>
                      </div>
                      <div class="documents-doughnuts-box">
                        <div class="stats-loader-container">
                          <div class="loader-blog"></div>
                        </div>
                        <div id="documents_doughnut_indexation" class="d-none"></div>
                      </div>
                    </div>
                  </div>
                  <div class="d-flex">
                    <div class="col-6 card card-custom shadow-sm mr-4 px-0">
                      <div class="card-header">
                        <h2 class="card-title"><?php print t("Documents metadata") ?></h2>
                      </div>
                      <div class="w-100 radar-chart-container d-flex flex-column flex-grow-1">
                        <div class="d-flex justify-content-center my-5">
                          <div id="documents_radar_container_metadata_buttons" class="btn-group btn-group-xs radar-chart-btn-group" role="group" aria-label="...">
                              <button id="document_charts_btn_group_category" type="button" class="btn btn-default document_charts_btn_group_category default-value" data-filter="category"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
                              <button id="document_charts_btn_group_state" type="button" class="btn btn-default document_charts_btn_group_state" data-filter="state"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
                              <button id="document_charts_btn_group_criticity" type="button" class="btn btn-default document_charts_btn_group_criticity" data-filter="criticity"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
                          </div>
                        </div>
                        <div id="documents_radar_category_state_container" class="flex-grow-1 d-flex justify-content-center align-items-center" style="aspect-ratio: 1;">
                          <div class="radar-box w-100" style="aspect-ratio: 1;">
                            <div id="documents_radar_category_state"></div>
                          </div>
                          <div class="stats-loader-container">
                            <div class="loader-blog"></div>
                          </div>
                        </div>
                      </div>
                    </div>
                    <div id="documents_export_container" class="flex-grow-1 card card-custom shadow-sm">
                      <div class="card-header">
                        <h3 class="card-title" style="text-align:center;"><?php echo t("Export documents list"); ?></h3>
                      </div>
                      <?php print drupal_render(gofast_stats_list_docs(only_form: TRUE)); ?>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
        <div class="tab-pane fade" id="spaces_stats" role="tabpanel" aria-labelledby="spaces_stats_header">
          <div class="card card-custom p-1">
            <div class="card-body">
              <div id="spaces_stats_container" class="panel panel-default stats_container" style="margin: 0">
                <div class="panel-body">
                  <div id="spaces_stats_export" style="margin-bottom: 15px;">
                    <button style="margin-right: 10px; margin-left:18px;" onclick="Gofast.download_stats('global_space_stats')" id="user_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
                    <span><i class="fa fa-info-circle" style="color: #3498db;"></i> <?php echo t("Export the list of all spaces with their administrators and locations.", array(), array('context' => 'gofast:gofast_stats')); ?> <strong><?php echo t("This might take a while !", array(), array('context' => 'gofast:gofast_stats')); ?></strong></span>
                  </div>
                  <hr />
                  <div class="card card-custom shadow-sm gutter-b" style="height: 45rem;">
                    <div class="card-header">
                      <h3 class="card-title"><?php print t("Spaces count over time") ?></h3>
                    </div>
                    <div id="spaces_chart_container" class="gutter-b card-body d-flex flex-column flex-grow-1">
                      <div class="d-flex justify-content-between">
                        <div id="space_chart_container_mode_buttons" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button id="space_charts_btn_group_evolution" data-filter="evolution" type="button" class="btn btn-default default-value"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_periodic" data-filter="periodic" type="button" class="btn btn-default"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="space_chart_container_period_buttons" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button id="space_charts_btn_group_1w" data-filter="1week" type="button" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_1m" data-filter="1month" type="button" class="btn btn-default default-value"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_1y" data-filter="1year" type="button" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_2y" data-filter="2year" type="button" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_3y" data-filter="3year" type="button" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                      </div>
                      <div class="stats-loader-container">
                        <div class="loader-blog"></div>
                      </div>
                    </div>
                  </div>
                  <div class="card card-custom shadow-sm">
                    <div class="card-header">
                      <h3 class="card-title"><?php print t("Activity") ?></h3>
                    </div>
                    <div id="spaces_bar_top_container" class="card-body d-flex flex-column" style="height: 35rem;">
                    <div>
                      <div id="space_bar_activity_buttons" class="btn-group btn-group-xs" role="group" aria-label="...">
                        <button id="space_bar_btn_group_activity" data-filter="activity" type="button" class="btn btn-default"><?php print t('The most actives', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_bar_btn_group_content" data-filter="content" type="button" class="btn btn-default"><?php print t('The most filled', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_bar_btn_group_members" data-filter="members" type="button" class="btn btn-default default-value"><?php print t('The most populated', array(), array('context' => 'gofast:stats')); ?></button>
                        <button onclick='Gofast.download_stats("space_stats")' id="space_bar_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
                      </div>
                    </div>
                      <div id="spaces_bar_top_box" class="flex-grow-1 d-flex">
                        <div class="stats-loader-container">
                          <div class="loader-blog"></div>
                        </div>
                      </div>
                    </div>
                  </div>
                </div>
              </div>
            </div>
          </div>
        </div>
    </div>
  </div>
</div>

<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/apexcharts.js" ?>"></script>
<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/gofast_stats.js" ?>"></script>