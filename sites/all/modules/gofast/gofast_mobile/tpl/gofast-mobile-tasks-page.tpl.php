<div class="mainContent GofastMobileTaskPage p-3 h-100 gofast-mobile-task-page"
     id="gofast-mobile-task-page">
    <div class="card card-custom card-stretch GofastMobileTaskPage__container overflow-hidden">
        <div class="card-body d-flex p-0 flex-column">
            <div class="w-100 px-2">
                <ul class="nav nav-tabs nav-justified">
                    <li class="nav-item ">
                        <a class="nav-link px-2 d-flex justify-content-center active"
                           id="navigation_workflow" aria-controls="navWorkflow"
                           data-toggle="tab" href="#navWorkflow">
                        <span class="nav-icon">
                        <i class="fa fa fa-cogs"></i>
                        </span>
                            <span class="nav-text">
                    <?php print t('Worflows'); ?>
                </span>
                        </a>
                    </li>
                    <li class="nav-item ">
                        <a class="nav-link px-2 d-flex justify-content-center"
                           id="navigation_kanban"
                           aria-controls="navKanban"
                           data-toggle="tab" href="#navKanban">
                        <span class="nav-icon">
                        <i class="fa fa-file"></i>
                        </span>
                            <span class="nav-text">
                    <?php print t('Tasks'); ?>
                </span>
                        </a>
                    </li>
                </ul>
            </div>
            <div class="container-fluid h-100 py-0" id="kt_content">
                <div id="messages-placeholder"></div>
                    <div id="home_navigation_content"
                         class="well well-sm Navigation__content h-100">
                        <div class="tab-content Navigation__tabsContent h-100">
                            <div id="navWorkflow" role="tabpanel"
                                 class="tab-pane fade in active show h-100">
                              <?php print gofast_workflows_dashboard_rapide(null,true); ?>
                            </div>
                            <div id="navKanban" role="tabpanel"
                                 class="tab-pane fade h-100">
                              <?php print gofast_mobile_kanban_simplified_board(); ?>
                            </div>
                        </div>
                    </div>
            </div>
        </div>
    </div>
</div>

<style>
  .main-container {
    width: 90% !important;
  }
  .GofastMobileTaskPage #navKanban {
      height: auto !important;
  }
</style>
