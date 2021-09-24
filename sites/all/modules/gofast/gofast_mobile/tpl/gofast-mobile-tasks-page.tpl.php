<div class="Navigation">
  <div class="breadcrumb navigation_simplified Navigation__tabs Navigation__tabs_w_50">
    <ul class="nav nav-tabs nav-justified">
      <li role="presentation" class="active">
        <a id="navigation_workflow" class="item_navigation" aria-controls="activity" role="tab" data-toggle="tab" href="#navWorflow">
          <i class="fa fa-cogs"></i>
          <?php print t('Worflows'); ?>
        </a>
      </li>
      <li>
        <a id="navigation_kanban" class="item_navigation" aria-controls="browser" role="tab" data-toggle="tab" href="#navKanban">
          <i class="fa fa-trello"></i>
          <?php print t('Tasks'); ?>
        </a>
      </li>
    </ul>
  </div>

  <div id="home_navigation_content" class="content well well-sm Navigation__content">
    <div class="tab-content Navigation__tabsContent">
      <div id="navWorflow" role="tabpanel" class="tab-pane fade in active">
        <?php print gofast_workflows_dashboard_rapide(); ?>
      </div>
      <div id="navKanban" role="tabpanel" class="tab-pane fade">
        <?php print gofast_mobile_kanban_simplified_board(); ?>
      </div>
    </div>

  </div>
</div>

<style>
  .main-container {
    width: 90% !important;
  }
</style>
