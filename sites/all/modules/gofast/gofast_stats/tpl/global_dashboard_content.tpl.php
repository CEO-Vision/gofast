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
                  
                  <div id="users_chart_container" class="gutter-b">
                    <h2><?php print t("Created users and logins") ?></h2>
                    <div id="user_charts_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                      <button id="user_charts_btn_group_1w" type="button" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="user_charts_btn_group_1m" type="button" class="btn btn-default"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="user_charts_btn_group_1y" type="button" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="user_charts_btn_group_2y" type="button" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="user_charts_btn_group_3y" type="button" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                    <div id="users_chart_loader" class="loader-blog"></div>
                  </div>

                  <div class="d-flex flew-wrap">
                    <div class="col-5">
                      <div class="w-100">
                        <div id="users_doughnut_state_container">
                          <h2><?php print t("Users status") ?></h2>
                          <div id="users_doughnut_state_loader" class="loader-blog"></div>
                          <div id="users_doughnut_state"></div>
                        </div>
                      </div>
                      <div class="w-100">
                        <div id="users_doughnut_active_container">
                          <h2><?php print t("Users activity") ?></h2>
                          <div id="users_doughnut_active_loader" class="loader-blog"></div>
                          <div id="users_doughnut_active"></div>
                        </div>
                      </div>
                    </div>

                    <div class="col-7">
                      <div id="users_doughnut_role_container">
                        <h2><?php print t("Users roles") ?></h2>
                        <div id="users_doughnut_role_loader" class="loader-blog"></div>
                        <div id="users_doughnut_roles"></div>
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
                  <div id="documents_chart_container" class="gutter-b">
                      <h2><?php print t("Documents count over time") ?></h2>
                      <div id="document_charts_mode_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                        <button id="document_charts_btn_group_evolution" type="button" class="btn btn-default"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_periodic" type="button" class="btn btn-default"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                      </div>
                    <div id="document_charts_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                      <button id="document_charts_btn_group_1w" type="button" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="document_charts_btn_group_1m" type="button" class="btn btn-default"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="document_charts_btn_group_1y" type="button" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="document_charts_btn_group_2y" type="button" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                      <button id="document_charts_btn_group_3y" type="button" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                    <div id="documents_chart_loader" class="loader-blog"></div>
                  </div>
                  <div id="documents_doughnut_storage_container">
                    <h2><?php print t("Storage") ?></h2>
                    <div id="documents_doughnut_storage_loader" class="loader-blog"></div>
                    <div id="documents_doughnut_storage"></div>
                  </div>
                  <div id="documents_doughnut_indexation_container">
                    <h2><?php print t("Indexing") ?></h2>
                    <div id="documents_doughnut_indexation_loader" class="loader-blog"></div>
                    <div id="documents_doughnut_indexation"></div>
                  </div>
                  <div>
                    <div class="col-5">
                      <div class="w-100">
                        <h2><?php print t("Documents metadata") ?></h2>
                        <div id="document_charts_btn_group_cs" class="btn-group btn-group-xs" role="group" aria-label="...">
                            <button id="document_charts_btn_group_category" type="button" class="btn btn-default"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="document_charts_btn_group_state" type="button" class="btn btn-default"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="document_charts_btn_group_criticity" type="button" class="btn btn-default"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="documents_radar_category_state_container">
                          <div id="documents_radar_category_state_loader" class="loader-blog"></div>
                          <div id="documents_radar_category_state"></div>
                        </div>
                      </div>
                    </div>
                  </div>

                  <div id="documents_export_container">
                    <h3 style="text-align:center;"><?php echo t("Export documents list"); ?></h3>
                    <?php print drupal_render(gofast_stats_list_docs()); ?>
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
                        <button style="margin-right: 10px; margin-left:18px;" onclick="Gofast.download_users_stats('global_space_stats')" id="user_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
                        <span><i class="fa fa-info-circle" style="color: #3498db;"></i> <?php echo t("Export the list of all spaces with their administrators and locations.", array(), array('context' => 'gofast:gofast_stats')); ?> <strong><?php echo t("This might take a while !", array(), array('context' => 'gofast:gofast_stats')); ?></strong></span>
                      </div>
                      
                      <hr />
                      
                      <div id="spaces_chart_container" class="gutter-b">
                          <h2><?php print t("Spaces count over time") ?></h2>
                          <div id="space_charts_mode_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                            <button id="space_charts_btn_group_evolution" type="button" class="btn btn-default"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="space_charts_btn_group_periodic" type="button" class="btn btn-default"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                          </div>
                        <div id="space_charts_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button id="space_charts_btn_group_1w" type="button" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_1m" type="button" class="btn btn-default"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_1y" type="button" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_2y" type="button" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_charts_btn_group_3y" type="button" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="spaces_chart_loader" class="loader-blog"></div>
                      </div>
                        <h2><?php print t("Activity") ?></h2>
                        <div id="space_bar_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button id="space_bar_btn_group_activity" type="button" class="btn btn-default"><?php print t('The most actives', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_bar_btn_group_content" type="button" class="btn btn-default"><?php print t('The most filled', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_bar_btn_group_members" type="button" class="btn btn-default"><?php print t('The most populated', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="space_bar_export_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
                          <button onclick='Gofast.download_users_stats("space_stats")' id="space_bar_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
                        </div>
                      <div id="spaces_bar_top_container">
                        <div id="spaces_bar_top"></div>
                        <div id="spaces_bar_top_loader" class="loader-blog"></div>
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
