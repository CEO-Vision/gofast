<div class="d-flex flex-column h-100 w-100">
  <!-- HEADER (Horizontal tabs) -->
  <div class="d-none justify-content-end py-4">
    <ul class="nav nav-pills nav-pills-sm" id="myTab1" role="tablist">
        <li class="nav-item ">
          <a class="nav-link" id="users_stats_header" aria-controls="users_stats" data-toggle="tab" href="#users_stats">
            <span class="nav-icon">
              <i class="fas fa-users n-color"></i>
            </span>
            <span class="nav-text"><?php print t('Members statistics', array(), array('context' => 'gofast:stats')); ?></span>
          </a>
        </li>
        
        <li class="nav-item ">
          <a class="nav-link" id="documents_stats_header" aria-controls="documents_stats" data-toggle="tab" href="#documents_stats">
            <span class="nav-icon">
              <i class="fas fa-file"></i>
            </span>
            <span class="nav-text"><?php print t('Documents statistics', array(), array('context' => 'gofast:stats')); ?></span>
          </a>
        </li>
    </ul>
  </div>
  <div class="h-100 w-100 overflow-auto" >
    <div class="tab-content h-100 w-100">
        <div class="tab-pane fade h-100 " id="users_stats" role="tabpanel" aria-labelledby="users_stats_header">
          <div id="users_stats_filter" class="mb-8">
            <?php //print drupal_render(drupal_get_form('gofast_stats_global_filter_users_form', $gid)); ?>
          </div>
            <div class="col-12">  
              <div id="users_chart_container" class="pb-6">
                <div id="" class="btn-group btn-group-sm" role="group" aria-label="...">
                  <button id="user_charts_btn_group_1w" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                  <button id="user_charts_btn_group_1m" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                  <button id="user_charts_btn_group_1y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                  <button id="user_charts_btn_group_2y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                  <button id="user_charts_btn_group_3y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                </div>
                <div id="users_chart_loader" class="loader-blog"></div>
              </div>
            </div>
            <div class="d-flex flex-wrap">
                <div class="col-5">
                    <div class="w-100">
                        <div id="users_doughnut_state_container" class="h-100">
                        <div id="users_doughnut_state_loader" class="loader-blog"></div>
                        <div id="users_doughnut_state"></div>
                        </div>
                    </div>
                    <div class="w-100">
                        <div id="users_doughnut_active_container" class="h-100">
                        <div id="users_doughnut_active_loader" class="loader-blog"></div>
                        <div id="users_doughnut_active"></div>
                        </div>
                    </div>
                </div>
                <div class="col-7">
                    <div id="users_doughnut_role_container">
                        <div id="users_doughnut_role_loader" class="loader-blog"></div>
                        <div id="users_doughnut_roles"></div>
                    </div>
                </div>
            </div>

        </div>
        <div class="tab-pane fade h-100 " id="documents_stats" role="tabpanel" aria-labelledby="documents_stats_header">
          <div class="d-flex flex-wrap">
            <div class="col-7">
                <div id="documents_chart_container" class="w-100">
                    <div class="w-100 d-flex justify-content-between">
                    <div id="" class="btn-group btn-group-sm" role="group" >
                        <button id="document_charts_btn_group_evolution" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('Evolution', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_periodic" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('Periodic', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                    <div id="" class="btn-group btn-group-sm" role="group" >
                        <button id="document_charts_btn_group_1w" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_1m" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_1y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_2y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
                        <button id="document_charts_btn_group_3y" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
                    </div>
                    </div>
                    <div id="documents_chart_loader" class="loader-blog"></div>
                </div>
                </div>
                <div class="col-5">
                    <div class="w-100">
                        <div id="" class="btn-group btn-group-sm" role="group">
                            <button id="document_charts_btn_group_category" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="document_charts_btn_group_state" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
                            <button id="document_charts_btn_group_criticity" type="button" class="btn btn-outline-secondary btn-hover-primary"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
                        </div>
                        <div id="documents_radar_category_state_container">
                        <div id="documents_radar_category_state"></div>
                        <div id="documents_radar_category_state_loader" class="loader-blog"></div>
                        </div>
                    </div>
                </div>
            </div>
          </div>
        </div>
    </div>
  </div>
  <!-- Content -->
</div>
