<?php if ($is_user_tab) : ?>
  <div class="tab-pane fade h-100" id="users_stats" role="tabpanel" aria-labelledby="users_stats_header">
    <h2 class="text-center space-documents-stats-title w-100 my-8"><?= t("Space users statistics", array(), array("context" => "gofast:gofast_stats")); ?></h2>
      <div class="card card-custom shadow-sm mx-5" style="height: 45rem;">
        <div class="card-header">
          <h3 class="card-title"><?= t("Created users and logins") ?></h3>
        </div>
        <div id="users_chart_container" class="pb-6 card-body d-flex flex-column">
          <div class="d-flex justify-content-between">
            <div id="user_chart_container_mode_buttons" class="btn-group btn-group-xs px-8" role="group" aria-label="...">
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
<?php endif; ?>
<?php if ($is_document_tab) : ?>
  <div class="tab-pane fade h-100 d-flex" id="documents_stats" role="tabpanel" aria-labelledby="documents_stats_header">
      <div id="space-stats-container" class="space-documents-stats d-flex flex-column flex-grow-1">
        <div id="space-stats-title" class="row justify-content-end">
          <h2 class="text-center space-documents-stats-title col-4"><?= t("Space documents statistics", array(), array("context" => "gofast:gofast_stats")) ?> </h2>
          <div id="space-stats-export-container" class="col-1 d-flex align-items-center">
            <a href="/modal/nojs/stats/select_fields" id="space-stats-export-button" type="button" class="btn btn-secondary d-flex justify-content-center align-items-center gofast__popover ctools-use-modal" data-boundary="window" data-toggle="popover" data-placement="top" data-trigger="hover" data-html="true" data-container="body" data-content="<div class='py-2 px-4'><?= t("Export document space statistics with current subspace filter", array(), array("context" => "gofast:gofast_stats")) ?></div>">
              <span class="fa fa-file-excel-o"></span>
            </a>
          </div>
          <div class="switch-container d-flex col-3">
            <div id="space-stats-switch-title" class="d-flex align-items-center justify-content-between">
              <span class="text-center"><?= t("Show subspaces documents", array(), array("context" => "gofast:gofast_stats")) ?></span>
              <a id="space-stats-switch-tooltip" data-boundary="window" class="gofast__popover" data-toggle="popover" data-placement="top" data-trigger="hover" data-html="true" data-content="<div class='py-2 px-4'><?= t('If enabled, sub-space documents will be counted in the graphs below.', array(), array("context" => "gofast:gofast_stats")) ?></div>" data-container="body" href=""><i class="fad fa-question-circle" style="font-size: 1.5em;"></i></a>
            </div>
            <span class="switch switch-icon switch ml-4" <?= gofast_og_is_user_private_space(node_load($gid)) ? 'title="'.t("There is no subspaces in private space", array(), array("context" => "gofast:gofast_stats")).'"' : '' ?>>
                <label>
                    <input id="space-stats-switch-input" type="checkbox" item="stats-scope" data-scope="space_only" <?= gofast_og_is_user_private_space(node_load($gid)) ? 'disabled' : '' ?>>
                    <span></span>
                </label>
            </span>
          </div>
        </div>
        <div class="row w-100 justify-content-center flex-grow-1">
          <div class="col-7 card card-custom shadow-sm">
              <div id="documents_chart_container" class="w-100 h-100 d-flex flex-column card-body px-0">
                <div class="w-100 px-8">
                  <div class="d-flex justify-content-between">
                    <div id="documents_chart_container_mode_buttons" class="btn-group btn-group-sm" role="group" >
                        <button id="space_document_charts_btn_group_evolution" type="button" data-mode="evolution" class="btn btn-default document_charts_btn_group_evolution default-value"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_document_charts_btn_group_periodic" type="button" data-mode="periodic" class="btn btn-default document_charts_btn_group_periodic"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                    <div id="documents_chart_container_period_buttons" class="btn-group btn-group-sm" role="group" >
                        <button id="space_document_charts_btn_group_1w" type="button" data-period="1week" class="btn btn-default document_charts_btn_group_1w"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_document_charts_btn_group_1m" type="button" data-period="1month" class="btn btn-default document_charts_btn_group_1m default-value"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_document_charts_btn_group_1y" type="button" data-period="1year" class="btn btn-default document_charts_btn_group_1y"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_document_charts_btn_group_2y" type="button" data-period="2year" class="btn btn-default document_charts_btn_group_2y"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="space_document_charts_btn_group_3y" type="button" data-period="3year" class="btn btn-default document_charts_btn_group_3y"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                  </div>
                </div>
                <div class="separator separator-solid mt-5 separator-border-2 w-100 mx-auto"></div>
                <div class="d-flex stats-container h-100">
                  <div class="stats-loader-container">
                    <div class="loader-blog"></div>
                  </div>
                </div>
              </div>
              </div>
              <div class="col-4 card card-custom shadow-sm">
                  <div id="radar_chart_container" class="w-100 d-flex justify-content-center card-body flex-column radar-chart-container px-0 pb-0">
                    <div class="d-flex justify-content-center">
                      <div id="documents_radar_container_metadata_buttons" class="btn-group btn-group-sm radar-chart-btn-group" role="group">
                          <button id="space_document_charts_btn_group_category" type="button" class="btn btn-default default-value" data-metadata="category"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_document_charts_btn_group_state" type="button" class="btn btn-default" data-metadata="state"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
                          <button id="space_document_charts_btn_group_criticity" type="button" class="btn btn-default" data-metadata="criticity"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
                      </div>
                    </div>
                    <div class="separator separator-solid mt-5 separator-border-2 w-100 mx-auto"></div>
                    <div id="documents_radar_category_state_container" class="flex-grow-1 d-flex justify-content-center align-items-center">
                      <div class="stats-loader-container">
                        <div class="loader-blog"></div>
                      </div>
                      <div class="radar-box w-100" style="aspect-ratio: 1/1;">
                        <div id="documents_radar_category_state"></div>
                      </div>
                    </div>
                  </div>
              </div>
          </div>
      </div>
    </div>
  </div>
<?php endif; ?>
<script>
  $(document).ready(() => {
    Drupal.behaviors.ZZCToolsModal.attach();
  })
</script>