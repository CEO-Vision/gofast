<ul class="nav nav-tabs nav-justified">
  <li class="active stats_header" id="users_stats_header">
    <a><?php print t('Users statistics', array(), array('context' => 'gofast:stats')); ?></a>
  </li>
  <li class="stats_header" id="documents_stats_header">
    <a><?php print t('Documents statistics', array(), array('context' => 'gofast:stats')); ?></a>
  </li>
  <li class="stats_header" id="spaces_stats_header">
    <a><?php print t('Spaces statistics', array(), array('context' => 'gofast:stats')); ?></a>
  </li>
</ul>

<div id="users_stats_container" class="stats_container panel panel-default" style="margin: 0">
  <div class="panel-body">
    <div id="user_export_btn_group" class="btn-group btn-group" role="group" aria-label="...">
        <button style="margin-right: 30px;" onclick='Gofast.download_users_stats("user_stats", jQuery("#gofast-stats-global-filter-users-form").find(".selection-tags").children())' id="user_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
        <span><i class="fa fa-info-circle" style="color: #3498db;"></i> <?php print t("You can select spaces in the text input to export memberships between users and these spaces", array(), array('context' => "gofast:gofast_stats")); ?></span>
    </div>
    <div id="users_stats_filter">
      <?php print drupal_render(drupal_get_form('gofast_stats_global_filter_users_form')); ?>
    </div>
    <div id="users_chart_container">
      <div id="user_charts_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
        <button id="user_charts_btn_group_1w" type="button" class="btn btn-default"><?php print t('1W', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="user_charts_btn_group_1m" type="button" class="btn btn-default"><?php print t('1M', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="user_charts_btn_group_1y" type="button" class="btn btn-default"><?php print t('1Y', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="user_charts_btn_group_2y" type="button" class="btn btn-default"><?php print t('2Y', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="user_charts_btn_group_3y" type="button" class="btn btn-default"><?php print t('3Y', array(), array('context' => 'gofast:stats')); ?></button>
      </div>
      <div id="users_chart_loader" class="loader-blog"></div>
    </div>
    <div id="users_doughnut_state_container">
      <div id="users_doughnut_state_loader" class="loader-blog"></div>
      <canvas id="users_doughnut_state"></canvas>
    </div>
    <div id="users_doughnut_role_container">
      <div id="users_doughnut_role_loader" class="loader-blog"></div>
      <canvas id="users_doughnut_roles"></canvas>
    </div>
    <div id="users_doughnut_active_container">
      <div id="users_doughnut_active_loader" class="loader-blog"></div>
      <canvas id="users_doughnut_active"></canvas>
    </div>
  </div>
</div>

<div id="documents_stats_container" class="panel panel-default stats_container" style="margin: 0">
  <div class="panel-body">
    <div id="documents_chart_container">
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
      <div id="documents_doughnut_storage_loader" class="loader-blog"></div>
      <canvas id="documents_doughnut_storage"></canvas>
    </div>
    <div id="documents_doughnut_indexation_container">
      <div id="documents_doughnut_indexation_loader" class="loader-blog"></div>
      <canvas id="documents_doughnut_indexation"></canvas>
    </div>
    <div id="document_charts_btn_group_cs" class="btn-group btn-group-xs" role="group" aria-label="...">
        <button id="document_charts_btn_group_category" type="button" class="btn btn-default"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="document_charts_btn_group_state" type="button" class="btn btn-default"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
        <button id="document_charts_btn_group_criticity" type="button" class="btn btn-default"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
    </div>
    <div id="documents_radar_category_state_container">
      <div id="documents_radar_category_state_loader" class="loader-blog"></div>
      <canvas id="documents_radar_category_state"></canvas>
    </div>
    <div id="documents_export_container">
      <h3 style="text-align:center;"><?php echo t("Export documents list"); ?></h3>
      <?php print drupal_render(gofast_stats_list_docs()); ?>
    </div>
  </div>
  
</div>
    
  <div id="spaces_stats_container" class="panel panel-default stats_container" style="margin: 0">
    <div class="panel-body">
      <div id="spaces_stats_export" style="margin-bottom: 15px;">
        <button style="margin-right: 10px; margin-left:18px;" onclick="Gofast.download_users_stats('global_space_stats')" id="user_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
        <span><i class="fa fa-info-circle" style="color: #3498db;"></i> <?php echo t("Export the list of all spaces with their administrators and locations.", array(), array('context' => 'gofast:gofast_stats')); ?> <strong><?php echo t("This might take a while !", array(), array('context' => 'gofast:gofast_stats')); ?></strong></span>
      </div>
      <div id="spaces_chart_container">
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
        <div id="space_bar_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
          <button id="space_bar_btn_group_activity" type="button" class="btn btn-default"><?php print t('The most actives', array(), array('context' => 'gofast:stats')); ?></button>
          <button id="space_bar_btn_group_content" type="button" class="btn btn-default"><?php print t('The most filled', array(), array('context' => 'gofast:stats')); ?></button>
          <button id="space_bar_btn_group_members" type="button" class="btn btn-default"><?php print t('The most populated', array(), array('context' => 'gofast:stats')); ?></button>
        </div>
        <div id="space_bar_export_btn_group" class="btn-group btn-group-xs" role="group" aria-label="...">
          <button onclick='Gofast.download_users_stats("space_stats")' id="space_bar_export_btn_group_xlsx" type="button" class="btn btn-default"><span class="fa fa-file-excel-o"></span></button>
        </div>
      <div id="spaces_bar_top_container">
        <canvas id="spaces_bar_top"></canvas>
        <div id="spaces_bar_top_loader" class="loader-blog"></div>
      </div>
    </div>
  </div>

<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/Chart.bundle.min.js" ?>"></script>
<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/Chart.min.js" ?>"></script>
<script type="text/javascript" src="<?php global $base_url; echo $base_url . "/sites/all/modules/gofast/gofast_stats/js/gofast_stats.js" ?>"></script>