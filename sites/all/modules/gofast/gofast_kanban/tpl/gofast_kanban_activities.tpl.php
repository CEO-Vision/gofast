<div class="timeline timeline-justified timeline-2">
    <div class="timeline-bar"></div>
    
    <div class="timeline-items">
        <?php foreach ($activities as $key => $activity): ?>      
        <div class="timeline-item">
          <div class="timeline-badge"></div>
          <div class="timeline-content d-flex justify-content-between">
            <span class="mr-3 w-75">                
                  <div class="timeline-media border-0">
                      <img title="<?php echo $activity['event_details']['who']['name'] ?>" class="w-20px" alt="Pic" src="<?php echo $activity['event_details']['who']['picture'] ?>">
                      <a href="/user/<?php print $activity['event_details']['who']['uid'] ?>">
                        <?php echo $activity['event_details']['who']['name'] ?>
                      </a>
                  </div>
                
                  <span class="gf-timeline-action" >
                      
                    <?php if ($activity['event_type'] == 'COMMENT'): ?>
                      <?php echo t('commented', array(), array('context' => 'gofast_kanban'));?>  
                      
                    <?php elseif ($activity['event_type'] == 'TASK'): ?>
                      
                      <?php echo t($activity['event_details']['what']['action'], array(
                        '%old_column' => $activity['event_details']['what']['value']['old'], 
                        '%new_column' => $activity['event_details']['what']['value']['new'],
                        '!new_column' => $activity['event_details']['what']['value']['new'] ), 
                      array('context' => 'gofast_kanban'));?>
                      
                    <?php elseif ($activity['event_type'] == 'CHECKLIST'): ?>
                      
                      <?php echo t($activity['event_details']['what']['action'], array(
                        '%old_column' => $activity['event_details']['what']['value']['old'], 
                        '%new_column' => $activity['event_details']['what']['value']['new'],  
                        '%label' => $activity['event_details']['what']['label'],
                        '%fields' => is_array($activity['event_details']['what']['field_updated']) ? implode(', ', $activity['event_details']['what']['field_updated']) : $activity['event_details']['what']['field_updated']
                      ), array('context' => 'gofast_kanban'));?>
                    <?php endif; ?>
                  </span>
            </span>
            <span class="text-muted text-right w-25"><?= format_date($activity['event_timestamp'], "short") ?></span>
          </div>
        </div>
        <?php endforeach; ?>        
    </div>
</div>


