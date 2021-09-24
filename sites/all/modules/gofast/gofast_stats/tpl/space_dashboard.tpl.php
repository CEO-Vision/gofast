<div>
  <ul id="stats-menu" class="nav nav-tabs nav-justified">
    <li class="active stats_header" id="users_stats_header">
      <a><?php print t('Members statistics', array(), array('context' => 'gofast:stats')); ?></a>
    </li>
    <li class="stats_header" id="documents_stats_header">
      <a><?php print t('Documents statistics', array(), array('context' => 'gofast:stats')); ?></a>
    </li>
  </ul>

  <div id="users_stats_container" class="stats_container panel panel-default" style="margin: 0">
    <div class="panel-body">
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
      <div id="document_charts_btn_group_cs" class="btn-group btn-group-xs" role="group" aria-label="...">
          <button id="document_charts_btn_group_category" type="button" class="btn btn-default"><?php print t('Category', array(), array('context' => 'gofast:stats')); ?></button>
          <button id="document_charts_btn_group_state" type="button" class="btn btn-default"><?php print t('State', array(), array('context' => 'gofast:stats')); ?></button>
          <button id="document_charts_btn_group_criticity" type="button" class="btn btn-default"><?php print t('Criticity', array(), array('context' => 'gofast:stats')); ?></button>
      </div>
      <div id="documents_radar_category_state_container">
        <canvas id="documents_radar_category_state"></canvas>
        <div id="documents_radar_category_state_loader" class="loader-blog"></div>
      </div>
    </div>
  </div>
</div>