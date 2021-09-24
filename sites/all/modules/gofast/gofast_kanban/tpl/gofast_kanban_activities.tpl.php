<div class="container" >
  <div class="row justify-content-end">
    <div class="col-2" style="text-align: right;" >
      <button type="button" class="btn btn-subtle-dark" id='gf_task_display_details' data-hide="1" onclick='KanbanBoard.showActivityDetails();'><?php print t('Display details', array(), array('context' => 'gofast_kanban')); ?></button>
    </div>
  </div>  
</div>

<ul class="timeline">
  <!-- .timeline-item -->
  
   
  
  <?php foreach($activities as $activity): ?>
  
  <li class="timeline-item <?php echo ($activity['event_type'] != 'COMMENT')? 'gf-timeline-other' : '';  ?>">
    <!-- .timeline-figure -->
    <div class="timeline-figure">
      <span class="tile tile-circle tile-sm">
        
        <?php if($activity['event_type'] == 'COMMENT'): ?>
          <i class="oi oi-chat fa-lg"></i>
        <?php elseif($activity['event_type'] == 'TASK'): ?>
            <i class="fa fa-calendar-o fa-lg"></i>
        <?php elseif($activity['event_type'] == 'CHECKLIST'): ?>
            <?php if($activity['event_details']['what']['event'] == 'ETDL'): ?>
              <i class="fa fa-check fa-lg"></i>
            <?php else : ?>
              <i class="fa fa-list fa-lg"></i>
            <?php endif; ?>
        <?php else: ?> 
          <i class="fa fa-cube fa-lg"></i>
        <?php endif; ?>  
      </span>
    </div>
    <!-- /.timeline-figure -->

    <!-- .timeline-body -->
    <div class="timeline-body">
      <!-- .media -->
      <div class="media">
        <!-- .media-body -->
        <div class="media-body">
          
            <!------------------ COMMENTS ------------------------------->
            <?php if ($activity['event_type'] == 'COMMENT'): ?>
            <span class="gf-timeline-comment">
              <h6 class="timeline-heading">  
                <figure class="user-avatar" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($activity['event_details']['who']['uid']) ?>"> 
                <?php $member = user_load($activity['event_details']['who']['uid']); ?>
                <?php
                echo theme('user_picture', array('account' => $member,
                    'popup' => FALSE,
                    'dimensions' => array('width' => '24px', 'height' => '24px'))
                )
                ?>
                </figure>
                <a href="/user/<?php print $activity['event_details']['who']['uid'] ?>">
                    <?php echo $activity['event_details']['who']['name']?>
                </a>
                <span class="gf-timeline-action"><?php echo t('commented', array(), array('context' => 'gofast_kanban'));?></span>
              </h6>
              <p class="mb-0">
                <span class='kanban-comment gf-kanban-not-editing'>
                  <pre class="gf-kanban-comment"><?php echo $activity['event_details']['what']['comment_body'] ?></pre>
                </span>
                <form action='/kanban/task/update/comment/<?php echo $activity['event_details']['what']['comment_id'] ?>' data-taskid="<?php print $activity['event_task_nid'] ?>" >
                  <span class='comment-edit-form gf-kanban-editing' style="display:none;">
                    <textarea id="comment-edit-value" name="comment_body" class="form-control"><?php echo $activity['event_details']['what']['comment_body'] ?></textarea>
                  </span>
                </form>
                <div class="conversation-meta gf-kanban-not-editing">
                  <?php if( comment_access('edit', entity_load_single('comment', $activity['event_details']['what']['comment_id']), $user)) : ?>
                  <a href="#" onclick='KanbanBoard.editComment($(this));'>
                      <?php echo t('Edit', array(), array('context' => 'gofast_kanban')); ?>
                  </a>
                  .
                  <?php endif; ?>
                  <?php if( comment_access('edit', entity_load_single('comment', $activity['event_details']['what']['comment_id']), $user )) : ?>
                  <a href="#" onclick='KanbanBoard.preDeleteComment(<?php echo $activity['event_details']['what']['comment_id'] ?>)' data-commentid="<?php echo $activity['event_details']['what']['comment_id'] ?>">
                    <?php echo t('Delete', array(), array('context' => 'gofast_kanban')); ?>
                  </a>
                  <?php endif; ?>
                </div>
                <div class="conversation-meta gf-kanban-editing" style="display:none;">

                  <?php if( comment_access('edit', entity_load_single('comment', $activity['event_details']['what']['comment_id']), $user)) : ?>
                  <a href="#" onclick='KanbanBoard.updateComment($(this));'><?php echo t('Save', array(), array('context' => 'gofast_kanban')); ?></a>
                   · 
                  <a href="#" onclick='KanbanBoard.cancelEditComment($(this));'><?php echo t('Cancel', array(), array('context' => 'gofast_kanban')); ?></a> 
                  <?php endif; ?>
                </div>

              </p>
              <p class="timeline-date d-sm-none">
                <?php print format_date($activity['event_timestamp'] ,'short'); ?>
              </p>
            </span>
              
            <!------------------ TASKS ------------------------------->
            <?php elseif ($activity['event_type'] == 'TASK'): ?>
            <span class="gf-timeline-other">
              <h6 class="timeline-heading">  
                <figure class="user-avatar" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($activity['event_details']['who']['uid']) ?>"> 
                  <?php $member = user_load($activity['event_details']['who']['uid']); ?>
                  <?php
                  echo theme('user_picture', array('account' => $member,
                      'popup' => FALSE,
                      'dimensions' => array('width' => '24px', 'height' => '24px'))
                  )
                  ?>
                </figure>
                <a href="/user/<?php print $activity['event_details']['who']['uid'] ?>">
                  <?php echo $activity['event_details']['who']['name'] ?>
                </a>
                <span class="gf-timeline-action" >
                  <?php echo t($activity['event_details']['what']['action'], array(
                        '%old_column' => $activity['event_details']['what']['value']['old'], 
                        '%new_column' => $activity['event_details']['what']['value']['new'],
                        '!new_column' => $activity['event_details']['what']['value']['new'] ), 
                      array('context' => 'gofast_kanban'));?>
                </span>
                
              </h6>
              <p class="mb-0">
                
              </p>
              <p class="timeline-date d-sm-none">
                <?php print format_date($activity['event_timestamp'] ,'short'); ?>
              </p>
            </span>
            
               
            <!------------------ CHECKLIST ------------------------------->
            <?php elseif ($activity['event_type'] == 'CHECKLIST'): ?>
            <span class="gf-timeline-other">
              <h6 class="timeline-heading">  
                <figure class="user-avatar" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($activity['event_details']['who']['uid']) ?>"> 
                  <?php $member = user_load($activity['event_details']['who']['uid']); ?>
                  <?php
                  echo theme('user_picture', array('account' => $member,
                      'popup' => FALSE,
                      'dimensions' => array('width' => '24px', 'height' => '24px'))
                  )
                  ?>
                </figure>
                <a href="/user/<?php print $activity['event_details']['who']['uid'] ?>">
                  <?php echo $activity['event_details']['who']['name'] ?>
                </a>
                <span class="gf-timeline-action" >
                  <?php echo t($activity['event_details']['what']['action'], array(
                        '%old_column' => $activity['event_details']['what']['value']['old'], 
                        '%new_column' => $activity['event_details']['what']['value']['new'],  
                        '%label' => $activity['event_details']['what']['label'],
                        '%fields' => is_array($activity['event_details']['what']['field_updated']) ? implode(', ', $activity['event_details']['what']['field_updated']) : $activity['event_details']['what']['field_updated']
                      ), array('context' => 'gofast_kanban'));?></span>
              </h6>
              <p class="mb-0">
                
              </p>
              <p class="timeline-date d-sm-none">
                <?php print format_date($activity['event_timestamp'] ,'short'); ?>
              </p>
            </span> 
              
            <!------------------ OTHER  ------------------------------->
            <?php else: ?>
              
              
            <?php endif; ?>  

        </div>
        <!-- /.media-body -->

        <!-- .media-right -->
        <div class="d-none d-sm-block">
          <span class="timeline-date"><?php print format_date($activity['event_timestamp'] ,'short'); ?></span>
        </div>
        <!-- /.media-right -->
      </div>
      <!-- /.media -->
    </div>
    <!-- /.timeline-body -->
  </li>
  
 <?php endforeach; ?>
  <!-- /.timeline-item -->
</ul>