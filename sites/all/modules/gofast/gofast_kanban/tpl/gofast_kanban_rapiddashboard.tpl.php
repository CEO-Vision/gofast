
<div class="gofast-block-outer community-rapid-dashboard" style="display: block; width: 859.5px; font-size: 12px; min-height:550px;">
  <div class="pointeur"></div>
  
  <style>
  
 /* Rapid dashboard community */
div.gofast-block-outer.community-rapid-dashboard{
  font-size: 12px;
}

.community-rapid-dashboard .task_in_todoliste_inner,
.community-rapid-dashboard .deadline_box_in_rapide_todoliste{
  border : 0px none;
}

.gf-kanban-task-icon-default{
  background-color: #2ecc71;
  color : white;
  padding : 2px;
  font-weight: bold;
}

.deadline-nearly-reached:not(.date-str) {
  background-color: #f0ad4e;
  color : white;
  padding : 2px;
  font-weight: bold;
}

.deadline-reached:not(.date-str){
  background-color: #d9534f;
  color : white;
  padding : 2px;
  font-weight: bold;
}

.deadline-nearly-reached-off:not(.date-str), .deadline-reached-off:not(.date-str){
  background-color: #888c9b;
  color : white;
  padding : 2px;
  font-weight: bold; 
}

.date-str.deadline-nearly-reached {
  color: #f0ad4e;
  font-weight: bold;
}

.date-str.deadline-reached{
  color: #d9534f;
  font-weight: bold;
}

.date-str.deadline-nearly-reached-off, .date-str.deadline-reached-off{
  color: #888c9b;
  font-weight: bold; 
}


</style>
  
  <div class="gofast-block-inner">
    
    <section id="block-gofast-" class="block block-gofast clearfix">

      <h2 class="block-title"><?php echo t('Workflows and Tasks', array(), array('context' => 'gofast_kanban')); ?></h2>


      <!-- THEME DEBUG -->
      <!-- CALL: theme('workflow_rapide_dashboard') -->
      <!-- BEGIN OUTPUT from 'sites/all/modules/gofast/gofast_workflows/gofast_workflows_rapide_dashboard.tpl.php' -->
      <!-- DIV globale du bloc --> 
      <div class="gofast-block2">
        <div style="float:left;  margin-bottom:5px; margin-left:5px;position:absolute;right:55px;">
<!--          <div class="btn-group" role="group">
            <button id="refresh-pagedashboard" type="button" class="btn btn-default gofast_display_none"><i class="fa fa-arrow-left"></i></button>
            <button id="refresh-lightdashboard" type="button" class="btn btn-default"><i class="fa fa-refresh"></i></button>-->
            <script>
//              var dropdownInterval = setInterval(function () {
//                if (typeof jQuery === "function" && typeof jQuery().dropdown === "function") {
//                  clearInterval(dropdownInterval);
//                  jQuery("#dropdown-rapid").dropdown();
//                  jQuery("#refresh-lightdashboard").click(function () {
//                    Drupal.gofast_workflows.ceo_vision_js_check_login(function () {
//                      jQuery('iframe#bonita_form_process')[0].contentWindow.location.reload(true);
//                    });
//                  });
//                  jQuery("#refresh-pagedashboard").click(function () {
//                    location.reload();
//                  });
//                }
//              }, 500);
            </script>
          <!--</div>-->
        </div>

        <div style="clear:both;"></div>
        <div style="padding:0px;height:100%;">

          <div class="container-fluid"> 
            <div class="row"> 

              <!-- tab headers -->
              <ul class="nav nav-tabs" > 
                <li class="active">
                  <a href="" class="">
                    <tab-heading translate="" ><span class=""><?php echo t('My current tasks', array(), array('gofast')); ?></span></tab-heading>
                  </a>
                </li> 
<!--                <li class="">
                  <a href="" class="">
                    <tab-heading translate=""><span><?php echo t("Tasks I assigned to others", array(), array('gofast')); ?></span></tab-heading>
                  </a>
                </li> -->
              </ul>

              <!-- tab contents -->
              <div class="tab-content">
                <div class="tab-pane active">
                  <div class="col-xs-12"> 
                    <div class="row"> 
                      <div class="component col-xs-12 "> 
                        <custom-gofast-tasks-table>
                          <div class="table-responsive" style="overflow:visible;">

                            <table class="table table-hover"  id ="gf_kanban_tasks">
                              <thead>
                                <tr>
                                  <th></th>
                                </tr>
                              </thead>

                              <tbody >
                                
                                <?php if(count($tasks) ===0) :?>
                                <tr style="cursor:auto;" class="">
                                  <td>
                                    <div class="task_in_todoliste" style="background-color: #f9f9f9;border: 1px solid #eee;list-style: none;padding: 6px 9px;position: relative;">
                                      <?php echo t('No tasks assigned', array(), array('context' => 'gofast_kanban')); ?>
                                    </div>
                                  </td>
                                </tr>
                                <?php endif; ?>

                                <?php //foreach tasks for kanban ?>
                                <?php foreach ($tasks as $key => $task): ?>
                                  <?php echo theme('kanban_rapiddashboard_task', array('task' => $task)); ?> 
                                <?php endforeach; ?>

                              </tbody>
                            </table>
                            
                            <nav class="text-center" style="margin-top:15px;">
                                <ul class="pagination" style="margin-top:25px;margin-bottom:5px;" id="path_pager"></ul>
                            </nav>
                            
                            <?php
                              $configure_pager_script = "jQuery(document).ready(function(){
                                jQuery('#gf_kanban_tasks > tbody').pager({pagerSelector : '#path_pager', perPage: 5, numPageToDisplay : 5, showPrevNext: true});
                              });";
                              drupal_add_js($configure_pager_script, 'inline');
                            ?>

                          </div>
                        </custom-gofast-tasks-table>
                      </div>
                    </div>
                  </div>
                </div>

                <!--<div class="tab-pane"></div>-->


              </div>
            </div>
          </div>
        </div>   
      </div>
    </section>

  </div>
</div>



