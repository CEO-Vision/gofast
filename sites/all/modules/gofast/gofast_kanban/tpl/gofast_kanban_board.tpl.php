<?php 
  global $user;
  $canEdit = node_access('update', node_load($kanban_project['nid']));
  
  $user_role = reset(gofast_og_get_user_final_roles_for_space('node', $kanban_project['space_nid']));
?>

    <div class="app">
      <!-- .page-inner -->
      <div class="page-inner page-inner-fill">
        <!-- .page-navs -->
        <header class="page-navs shadow-sm pr-3">
          <!-- .btn-account -->
          <a href="" class="btn-account">
            <div class="account-summary">
              <h1 class="card-title"> <?php echo $kanban_project['title']; ?> </h1>
<!--              <h6 class="card-subtitle text-muted"> 4 deadline · 2 overdue </h6>-->
            </div>
          </a> <!-- /.btn-account -->
          <!-- right actions  -->
              <div class="ml-auto">
<!--                               invite members 
                  <div class="dropdown d-inline-block">
                      <button type="button" class="btn btn-light btn-icon" title="Invite members" data-toggle="dropdown" data-display="static" aria-haspopup="true" aria-expanded="false"><i class="fas fa-user-plus"></i></button>
                      <div class="dropdown-arrow"></div> .dropdown-menu 
                      <div class="dropdown-menu dropdown-menu-right dropdown-menu-rich stop-propagation">
                          <div class="dropdown-header"> Add members </div>
                          <div class="form-group px-3 py-2 m-0">
                              <input type="text" class="form-control" placeholder="e.g. @bent10" data-toggle="tribute" data-remote="assets/data/tribute.json" data-menu-container="#people-list" data-item-template="true" data-autofocus="true" data-tribute="true"> <small class="form-text text-muted">Search people by username or email address to invite them.</small>
                          </div>
                          <div id="people-list" class="tribute-inline stop-propagation"></div><a href="#" class="dropdown-footer">Invite member by link <i class="far fa-clone"></i></a>
                      </div> /.dropdown-menu 
                  </div> /invite members -->
                  <!--<button type="button" class="btn btn-light btn-icon" data-toggle="page-expander" title="Expand board"><i class="oi oi-fullscreen-enter fa-rotate-90 fa-fw"></i></button>--> 
                  <button type="button" class="btn btn-light btn-icon" data-toggle="modal" data-target="#modalBoardConfig" title="Show menu"><i class="fa fa-cog fa-fw"></i></button>
              </div> <!-- /right actions -->
        </header><!-- /.page-navs -->
        
        <!-- SEARCH + FILTER -->
        <div class="px-4 mt-4">
          <div class="input-group has-clearable">
            <button type="button" class="close show" aria-label="Clear" id="gf_kanban_search_clear" data-kanbannid="<?php echo $kanban_project['nid']; ?>" onclick="KanbanBoard.search($(this));" ><span aria-hidden="true"><i class="fa fa-times-circle"></i></span></button> 
            <label class="input-group-prepend" for="gf_kanban_search"><span class="input-group-text"><span class="oi oi-magnifying-glass"></span></span></label> 
            <input type="text" class="form-control" data-kanbannid="<?php echo $kanban_project['nid']; ?>" id="gf_kanban_search" placeholder="<?php echo t('Search....', array(), array('context' => 'gofast_kanban'))?>" value="" onchange="KanbanBoard.search($(this));" onkeydown="KanbanBoard.search($(this));">
          </div>
        </div>
        <!-- .board -->
        <div id="board" class="board" data-kanbanid="<?php echo $kanban_project['nid']; ?>"  data-user-role="<?php echo $user_role ?>" data-card-to-display="<?php echo $card_to_display ?>" > 
          <!-- .tasks -->
          
          <?php foreach ($kanban_project['tasklists'] as $key => $tasklist): ?>
            <?php echo theme('kanban_column', array('tasklist' => $tasklist, 
                                                    'tasks' => $kanban_project['tasks'][$tasklist['id']],
                                                    'kanban_nid' => $kanban_project['nid'],
                                                    'kanban_space_nid' => $kanban_project['space_nid'])); ?> 
          <?php endforeach; ?>

          <?php if ($canEdit): ?>
          <div class="tasks-action">
            <!-- .publisher -->
            <div class="publisher">
              <!-- .publisher-input -->
              <div class="publisher-input pr-0">
                <input class="form-control gf-kanban-new-column-name" placeholder="<?php echo t('+ Enter column title', array(), array('context' => 'gofast_kanban')); ?>">
              </div><!-- /.publisher-input -->
              <!-- .publisher-actions -->
              <div class="publisher-actions">
                <!-- .publisher-tools -->
                <div class="publisher-tools pb-0">
                  <button type="submit" class="btn btn-primary" data-kanbannid="<?php echo $kanban_project['nid'];?>" onclick="KanbanBoard.addColumn($(this));"><?php echo t('Add Column', array(), array('context' => 'gofast_kanban')); ?></button> 
                  <button type="button" class="btn btn-light"><?php echo t('Cancel', array(), array('context' => 'gofast_kanban')); ?></button>
                </div><!-- /.publisher-tools -->
              </div><!-- /.publisher-actions -->
            </div><!-- /.publisher -->
          </div>
          <?php endif; ?>
        </div><!-- /.board -->
      </div><!-- /.page-inner -->
    </div>
    
    <div class="modal fade" id="kanbanModal" role="dialog" aria-labelledby="kanbanModalLabel" aria-hidden ="true" data-keyboard="false" data-backdrop="static" >
      <div class="modal-dialog modal-lg modal-dialog-scrollable" role="document">
        <div class="modal-content">
          <div class="modal-header">
            <h5 class="modal-title">Modal title</h5>
            <button type="button" class="close gf-card-modal-pre-dismiss" aria-label="Close">
              <span aria-hidden="true">&times;</span>
            </button>
          </div>
          <div class="modal-body">
            <p>Modal body text goes here.</p>
          </div>
          <div class="modal-footer">
            <div class="gf-btn-action">
              <button type="button" class="btn btn-secondary gf-card-modal-pre-dismiss" ><i class="fa fa-times"></i>&nbsp;<?php echo t('Close', array(), array('context' => 'gofast_kanban')); ?></button>
              <button type="button" class="btn btn-secondary gf-card-modal-dismiss" data-dismiss="modal" style="display:none;"><i class="fa fa-times"></i>&nbsp;<?php echo t('Close', array(), array('context' => 'gofast_kanban')); ?></button>
              <span class='modal-contextual-actions'></span>
            </div>
            <div class=" gf-btn-action-message" style="display:none;">
              <div class="alert alert-warning"><?php echo t('There is unsaved modification. If you confirm, it will close the popup and these unsaved data will be lost.', array(), array('context'=>'gofast_kanban')) ?>
                <input class="btn btn btn-success" type="button" onClick="kanbanBoard.closeKanbanModal();" value="<?php echo t('Validate', array(), array('context' => 'gofast_kanban')); ?>" />
                <input class="btn btn btn-cancel" type="button" onClick="KanbanBoard.hideBtnActionMessage();"  value="<?php echo t('Cancel', array(), array('context' => 'gofast_kanban')); ?>" />
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>

  </div>

  <style>
    body{
      -webkit-user-select: none !important;
    }
  </style>