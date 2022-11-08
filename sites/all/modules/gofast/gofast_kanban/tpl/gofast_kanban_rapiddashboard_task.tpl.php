
<?php

  $node = node_load($task['nid']);
 // $canDelete = node_access('delete', $node, $user ) ? 'true' : 'false';
?>


<tr style="cursor:auto;" class="">
  <td>
    <div class="task_in_todoliste" style="background-color: #f9f9f9;border: 1px solid #eee;list-style: none;padding: 6px 9px;position: relative;">
      <div class="task_in_todoliste task_in_todolist_inner" style="padding-left:70px;border : 0px none;" title="">
        <span  class="<?php echo $task['deadline_color_indicator']; ?> gf-kanban-task-icon-default" style="position: absolute;margin-left: -70px;margin-top: -6px;height: 57px;width: 60px;font-size:14px;">
          <i class="fa fa-clock-o fa-3x" style="color:white;margin-top:8px;margin-left:12px;"></i>
        </span>
        <div style="float:right;">
          <span  class="card-text actor_container" style="display: inline-block;clear:both;">
            <div style="clear:both;"><?php echo t('Responsible', array(), array('context' => 'gofast_kanban')); ?>  : 
              
              <?php $uid= $task['person_in_charge']; ?>
              <span onclick="event.preventDefault(); Gofast.processAjax( 'user/'<?php echo $uid;?>);">
                <?php
                 
                  echo theme('user_picture', array('account' => node_load($uid),
                      'popup' => FALSE,
                      'dimensions' => array('width' => '20px', 'height' => '20px'))
                  )
                  ?>
              </span>
            </div>
          </span> 
        </div>
        
        <div style="padding-left:20px;">
          <div class="row">
            <span style="color:#777;font-weight: bold;width:200px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;" title="<?php echo t('Completed up to @completion', array('@completion'  => $task['progress']), array('context' => 'gofast_kanban')); ?>%" >
              <i class="fab fa-trello"></i>
              <span class="card-title"><?php echo $task['title']; ?></span>
            </span>
            <span style="color:#777;font-weight: bold;width:270px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;" title="<?php echo $task['first_item_label'];?> ( <?php echo t('Completed up to @completion', array('@completion'  => $task['progress']), array('context' => 'gofast_kanban')); ?>%)">
              <i class="fa fa-flag-o"></i>
              <span class="card-subtitle mb-2 text-muted "><?php echo $task['first_item_label'];?> ( <?php echo t('Completed up to @completion', array('@completion'  => $task['progress']), array('context' => 'gofast_kanban')); ?>%)</span>
            </span>
          </div>
          <div class="row">
            <div>
              <div class="deadline_box_in_rapide_todoliste" style="border : 0px none;float:left;max-width:125px;max-height:22px;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;">
                <i class="fa fa-calendar"></i> <span title="<?php echo t('Start date', array(), array('context' => 'gofast_kanban')); ?>" ><?php echo $task['created_date']; ?></span>
              </div>
              <div class="deadline_box_in_rapide_todoliste" style="border : 0px none;font-weight:bold;float:left;width:125px;text-align:center;max-height:22px;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display: inline-block;">
                <i class="fa fa-clock-o" style="color: #337ab7;"></i> <span class="<?php echo $task['deadline_color_indicator']; ?> date-str" title="<?php echo t('Deadline', array(), array('context' => 'gofast_kanban')); ?>"><?php echo $task['deadline']; ?></span>
              </div>

              <div class="deadline_box_in_rapide_todoliste" style="float:left;max-width:350px;/*max-height:22px;*/margin-left:-9px;/*overflow:hidden;*/word-break:break-all;">
                <div class=" card-text document_container">
                 
                  <?php if( count($task['attachments']) > 1 ): ?>
                    <?php $doc = node_load($task['attachments'][0]); ?>
                    <span  id="wf_multiple_docs_<?php echo $task['nid']; ?>" data-nid="<?php echo $task['nid']; ?>" class="task_documents_details" onmouseout="$(this).css('display', 'none');" style="display: none; position: absolute; z-index: 999999; margin-top: 20px;">
                      <div class="panel panel-primary">
                        <div class="panel-heading"><?php echo t('Contents linked', array(), array('context' => 'gofast_kanban')); ?></div>
                        <div class="panel-body">
                          <?php foreach ($task['attachments'] as $doc_nid): ?>
                            <?php $doc2 = node_load($doc_nid); ?>
                            <div class="/*deadline_box_in_rapide_todoliste*/" style="max-width:685px;max-height:22px;" title="<?php echo $doc2->title ?>">
                              <span style="float: left; margin-top:-2px;color:#000000"></span>
                              <span style="max-width:680px;white-space: nowrap;overflow:hidden;text-overflow:ellipsis;-o-text-overflow:ellipsis;display:inline-block;">
                                <span onclick="Gofast.processAjax('/node/<?php echo $doc2->nid; ?>');modalContentClose();">
                                  <div class="gofast-title">
                                     <?php echo theme('gofast_node_icon_format', array('node' => $doc2)) ?>
                                    <span class="gf-kanban-node-title"><?php echo $doc2->title ?></span>
                                  </div>
                                </span>
                              </span>
                            </div>
                          <?php endforeach; ?>
                        </div>
                      </div>  
                    </span>
                  
<!--                    <span style="cursor:pointer;max-width:685px;max-height:22px;" onmouseover="$(this).parent().find('#wf_multiple_docs_'+$(this).data('nid')).css('display', 'block');" onmouseout="/*$(this).parent().find('#wf_multiple_docs_'+$(this).data('nid')).css('display', 'none');*/" data-nid="<?php echo $task['nid']; ?>">
                      <?php //echo theme('gofast_node_icon_format', array('node' => $doc)) ?>
                      <a href="../node/<?php //echo $doc->nid ?>" target="_blank" class="gofast-non-ajax">
                        <span class="gf-kanban-node-title"><?php //echo $doc->title ?></span>
                      </a>
                      <span class="fa fa-caret-down" title="Documents" style="float:left;margin-top:4px;margin-left:5px;position:absolute;">
                        <span style="clear:both;"></span>
                      </span>
                    </span>-->
                  
                    <span style="cursor:pointer;max-width:685px;max-height:22px;" 
                        onmouseover="console.log($(this).parent().find('#wf_multiple_docs_'+$(this).data('nid'))); $(this).parent().find('#wf_multiple_docs_'+$(this).data('nid')).css('display', 'block');" onmouseout="$(this).parent().find('#wf_multiple_docs_'+$(this).data('nid')).css('display', 'none');" data-nid="<?php echo $task['nid']; ?>">
                      <?php echo theme('gofast_node_icon_format', array('node' => $doc)) ?>
                      <a href="../node/<?php echo $doc->nid ?>" target="_blank" class="gofast-non-ajax">
                        <span class="gf-kanban-node-title"><?php echo $doc->title ?>
                        </span>
                      </a>
                      <span class="fa fa-caret-down" title="Documents" style="margin-top:4px;margin-left:5px;/*float:left;position:absolute;*/">
                        <span style="clear:both;"></span>
                      </span>
                      
                    </span>

                  <?php else: ?>
                    <?php if( isset($task['attachments'][0]) ) :?>
                     <?php $doc = node_load($task['attachments'][0]); ?>
                    <span>
                      <?php echo theme('gofast_node_icon_format', array('node' => $doc)) ?>
                      <a href="../node/<?php echo $doc->nid ?>" target="_blank" class="gofast-non-ajax ">
                        <span class="gf-kanban-node-title"><?php echo $doc->title ?></span>
                      </a>
                     </span>
                     <?php endif; ?>
                  <?php endif; ?>
                  
                </div>
              </div>
              
              
              <div id="wf-buttons" style="float: right;margin-right: 15px;margin-top: 5px;">
                
                <span style="cursor:pointer;" >
                  <a class="btn btn-default wf-button wf-button-blue" style="padding:1px 6px;width:22px;color: #337ab7;"href="/node/<?php echo $task['nid']; ?>" >
                    <span class="fa fa-info gofast_wf_link"></span>
                  </a> 
                </span>
              </div>
            </div>
          </div>
        </div>
        <div style="clear:both;"></div>
      </div>
    </div>
  </td>
</tr>