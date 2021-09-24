
<?php

  $node = node_load($task['nid']);
  $canDelete = node_access('delete', $node, $user ) ? 'true' : 'false';
?>

    <!-- .task-issue -->
    <div class="task-issue" data-nid='<?php echo $task['nid'] ?>' data-kanbannid="<?php echo $task['kanban_nid'] ?>" <?php if($canDelete === 'true'): ?> style="cursor:move;" title="<?php echo t('Move card', array(), array('context' => 'gofast_kanban')); ?>" <?php endif; ?>
         data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" >
      <!-- .card -->
      <div class="card">
        <!-- .card-header -->
        <div class="card-header">
          <h4 class="card-title">
            <span class="gf-link-to" data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" data-can-delete="<?php echo $canDelete; ?>"  
                  data-toggle="modal" data-action="edit" data-eltid="<?php echo $task['nid'] ?>" data-elttype="task" 
                  data-target="#kanbanModal" title="<?php echo t('View card', array(), array('context' => 'gofast_kanban')); ?>">
                  <?php echo $task['title']; ?>
            </span>
<!--            <button class="btn btn-light btn-icon text-muted" data-toggle="modal" data-action="edit" data-can-delete="<?php echo $canDelete; ?>"  
                    data-eltid="<?php echo $task['nid'] ?>" data-elttype="task" data-target="#kanbanModal" title="<?php echo t('View card', array(), array('context' => 'gofast_kanban')); ?>" 
                    data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view">
              <i class="fa fa-eye"></i>
            </button>-->
          </h4>
          <h6 class="card-subtitle text-muted">
            <?php if (!empty($task['deadline'])) :?>
            <span class="due-date"><i class="fa fa-clock-o <?php echo $task['deadline_color_indicator'] ?>"></i>&nbsp;<?php echo $task['deadline']; ?></span>
            <?php endif; ?>
          </h6>
        </div>
        <!-- /.card-header -->

        <!-- .card-body -->
        <div class="card-body pt-0" data-toggle="modal" data-action="edit" data-eltid="<?php echo $task['nid'] ?>" 
                 data-can-delete="<?php echo $canDelete; ?>"  data-elttype="task" data-target="#kanbanModal" 
                 title="<?php echo t('View card', array(), array('context' => 'gofast_kanban')); ?>" data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" >
          <!-- .list-group -->
          <div class="list-group">
            <!-- .list-group-item -->
            <div class="list-group-item">
              <a href="#" class="stretched-link"></a>
              <!-- .list-group-item-body -->
              <div class="list-group-item-body">
             
                <!-- members -->
                
                <?php $members = user_load_multiple($task['members']) ?>
                <?php foreach( $members as $uid => $member): ?> 
                <figure class="user-avatar user-avatar-sm" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($uid) ?>">
                  <?php echo theme('user_picture', 
                        array( 'account' => $member, 
                               'popup' => FALSE, 
                               'dimensions' => array('width' => '15px', 'height' => '15px'))
                        )
              ?>
                </figure>
                <?php endforeach; ?>
                <!-- /members -->
              </div>
              <!-- /.list-group-item-body -->
            </div>
            <!-- /.list-group-item -->
            <div class="list-group-item pt-0"  data-toggle="modal" data-action="edit" data-eltid="<?php echo $task['nid'] ?>" 
                 data-can-delete="<?php echo $canDelete; ?>"  data-elttype="task" data-target="#kanbanModal" 
                 title="<?php echo t('View card', array(), array('context' => 'gofast_kanban')); ?>" data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" >
                <a href="#" class="stretched-link"></a> <!-- .list-group-item-body -->
                <div class="list-group-item-body">
                  <div class="progress progress-xs">
                    <div class="progress-bar bg-success" role="progressbar" style="width: <?php echo $task['progress'] ?>%;" aria-valuenow="0" aria-valuemin="0" aria-valuemax="100"></div>
                  </div>
                </div>
                <div class="list-group-item-figure">
                  <span class="todos"><?php echo $task['nb_items_completed'] ?>/<?php echo $task['nb_items'] ?></span>
                </div> 
              </div>
          </div>
          <!-- /.list-group -->
        </div>
        <!-- /.card-body -->

        <!-- .card-footer -->
        <div class="card-footer">
          <!--<a href="#" data-toggle="modal"  data-action="edit" data-elttype="task" data-eltid="<?php echo $task['nid'] ?>" data-target="#kanbanModal" title="View task" data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" class="card-footer-item card-footer-item-bordered text-muted">-->
          <span  style="cursor: pointer;" class="card-footer-item card-footer-item-bordered text-muted"  data-toggle="modal" data-action="edit" data-eltid="<?php echo $task['nid'] ?>" 
                 data-can-delete="<?php echo $canDelete; ?>"  data-elttype="task" data-target="#kanbanModal" 
                 title="<?php echo t('View card', array(), array('context' => 'gofast_kanban')); ?>" data-url="/modal/ajax/task/<?php echo $task['nid'] ?>/view" > 
          <i class="oi oi-comment-square mr-1"></i> <?php print $task['comments_count']?>
          </span>
          <!--</a>-->
        </div>
        <!-- /.card-footer -->
      </div>
      <!-- .card -->
    </div>
    <!-- /.task-issue -->
