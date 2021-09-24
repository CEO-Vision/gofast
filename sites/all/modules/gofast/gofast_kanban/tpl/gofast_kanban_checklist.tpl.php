<?php

  $node = node_load($todolist['task_nid']);
  $canEdit = node_access('update', $node, $user );
    
?>
<div class="task-checklists">
  <!-- .form-group -->
  <div class="form-group">
    <div class="d-flex justify-content-between">
      <label><?php echo $todolist['label']; ?></label>
      <span class="text-muted">(<?php echo $todolist['nb_items_completed'] ?>/<?php echo $todolist['nb_items'] ?>)</span>
    </div>
    <!-- .progress -->
    <div class="progress progress-sm">
      <div class="progress-bar bg-primary" role="progressbar" aria-valuenow="<?php echo $todolist['progress']; ?>" aria-valuemin="0" aria-valuemax="100" style="width: <?php echo $todolist['progress'] . '%'; ?>">
        <span class="sr-only"><?php echo t('@progress % Complete', array('@progress' => $todolist['progress']), array('context' => 'gofast_kanban')); ?></span>
      </div>
    </div>
    <!-- /.progress -->
  </div>


  <!-- .form-group -->
  <div class="form-group">
    <!-- save task todos to this input hidden -->
    <input type="hidden" name="vtTodos">
    <!-- .todo-list -->
    <div id="vtTodos" class="todo-list">

      <?php foreach ($todolist['items'] as $key => $item): ?>
      
      <?php 
      $canCheckTodo = gofast_kanban_checklistItem_canDo($item->ciid, $user); //FALSE; 
      ?>
      
        <!-- .todo -->
        <div class="todo">
          <div class='container-fluid'>
            <form action="/kanban/task/update/todo/<?php echo $item->ciid ?>" data-taskid="<?php echo $todolist['task_nid'] ?>" >
              <!-- .custom-control -->
              <div class="row todo-details-<?php echo $item->ciid ?>" data-ciid="<?php echo $item->ciid ?>"  >
                <div class="custom-control custom-checkbox col-6 gf-kanban-not-editing <?php echo ($canCheckTodo || $canEdit)? '' : 'readonly'; ?>" >
                  <?php if ($canCheckTodo || $canEdit) : ?>
                  <input type="checkbox" class="custom-control-input todo-status " id="vtodo<?php echo $key ?>" value="0" <?php echo ($item->status == 1) ? "checked" : ""; ?> onchange="KanbanBoard.updateTodoStatus($(this));">                 
                  <label class="custom-control-label" for="vtodo<?php echo $key ?>"><?php echo $item->label ?></label>
                  <?php else: ?>
                  <i class="fa <?php echo ($item->status == 1) ? 'fa-check-square-o' : 'fa-square-o' ?>"></i>&nbsp;<label><?php echo $item->label ?></label>
                  <?php endif; ?>
                  
                </div>
                <?php if($canEdit) : ?>
                <div class="col-6 gf-kanban-editing" style="display:none; flex:1;"> 
                  <input class="form-control form-control-reflow" id="edit-label-<?php echo $key ?>" name="label" autocomplete="off" value="<?php echo $item->label ?>" /> 
                </div>
                <?php endif; ?>

                <div class="col-3" title="<?php echo t('Assigned to : @user', array('@user' => gofast_user_get_display_name_sql($item->uid)), array('context' => 'gofast_kanban')); ?>">
                  <?php if (!empty($item->uid)): ?>
                    <span class="gf-kanban-not-editing" onclick="KanbanBoard.editTodo($('.btn-edit-ciid-<?php echo $item->ciid ?>'));" >
                      <figure class="user-avatar user-avatar-sm" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($item->uid) ?>">
                        <?php
                        echo theme('user_picture', array('account' => user_load($item->uid),
                            'popup' => FALSE,
                            'dimensions' => array('width' => '24px', 'height' => '24px')
                            )
                        )
                        ?>
                      </figure>
                      <?php echo gofast_user_get_display_name_sql($item->uid); ?>
                    </span>
                  <?php else: ?>
                    <span class="gf-kanban-not-editing /*badge badge-secondary*/" onclick="KanbanBoard.editTodo($('.btn-edit-ciid-<?php echo $item->ciid ?>'));" >
                      <em><?php echo t('Nobody assigned', array(), array('context' => 'gofast_kanban')) ?></em>
                    </span>
                  <?php endif; ?>

  <!--<input class="gf-kanban-todo-assignee gf-kanban-editing" style="display:none;"/>-->
                   <?php if($canEdit) : ?>
                  <span class="gf-kanban-editing"style="display:none;" >
                    <select class="gf-kanban-todo-assignee " name="person-in-charge" data-user-lang="<?php echo $user->language; ?>"  placeholder="<?php echo t('Choose an assignee', array(), array('context' => 'gofast_kanban')); ?>" >
                      <?php if (!empty($item->uid)): ?>
                        <option value="<?php echo $item->uid ?>" selected="selected"><?php echo gofast_user_get_display_name_sql($item->uid); ?></option>
                       <?php endif; ?>
                    </select>
                  </span>  
                  <?php endif; ?>
                </div>
                <div class="col-2 form-group gf-kanban-field-edit" onclick="KanbanBoard.editTodo($('.btn-edit-ciid-<?php echo $item->ciid ?>'));" >
                  <?php if (!empty($item->deadline)) : ?>
                    <span class="gf-kanban-not-editing"><i class="fa fa-clock-o"></i>&nbsp;<?php echo format_date($item->deadline, 'privatemsg_years') ?></span>
                  <?php else : ?>
                    <span class="gf-kanban-not-editing"><i class="fa fa-clock-o"></i>&nbsp;
                      <em><?php echo t('No deadline', array(), array('context' => 'gofast_kanban')) ?></em>
                    </span>
                  <?php endif; ?>
                  <?php if($canEdit) : ?>
                  <span class="gf-kanban-editing" style="display:none;" >
                    <div class="input-group">
                      <input class="form-control form-control-reflow flatpickr-input gf-kanban-task-deadline" data-toggle="flatpickr" type="text" id="edit-deadline-<?php echo $key ?>" name="deadline" placeholder="<?php echo t('Select a deadline', array(), array('context' => 'gofast_kanban')); ?>" value="<?php echo $item->deadline ?>" readonly="readonly"/> 
                      <div class="input-group-append">
                        <button type="button" class="btn btn-secondary" onclick="KanbanBoard.clearDate($(this));"><i class="fa fa-times"></i></button>
                      </div>
                    </div>
                  </span>
                 <?php endif; ?>
                </div>
                <!-- /.custom-control -->
               
                <div class="col-2">
                   <?php if($canEdit) : ?>
                  <!-- .todo-actions -->
                  <div class="gf-kanban-todo-actions todo-actions pr-1 gf-kanban-not-editing">
                    <button type="button" data-ciid='<?php echo $item->ciid ?>' class="btn btn-sm btn-light btn-edit-ciid-<?php echo $item->ciid ?>" onclick="KanbanBoard.editTodo($(this));"><i class="fa fa-edit"></i></button>
                    <button type="button" data-ciid='<?php echo $item->ciid ?>' class="btn btn-sm btn-light"  onclick='KanbanBoard.preDeleteTodo(<?php echo $item->ciid ?>);'><i class="fa fa-trash"></i><?php //echo t('Delete', array(), array('context' => 'gofast_kanban'));     ?></button>
                  </div>
                  <div class="pr-1 gf-kanban-editing" style="display:none;padding-left:5px;">
                    <button type="button" class="btn btn-sm btn-subtle-success update-todo" onclick="KanbanBoard.updateTodo($(this));"><i class="fa fa-check"></i></button>
                    <button type="button" class="btn btn-sm btn-light cancel-update-todo" onclick="KanbanBoard.cancelEditTodo($(this));"><i class="fa fa-times"></i></button>
                  </div>
                  <!-- /.todo-actions -->
                  <?php endif; ?>
                </div>
              </div>
            </form>
          </div>
        </div>
        <!-- /.todo -->
      <?php endforeach; ?>
      <script type="text/javascript">
        jQuery("input.gf-kanban-task-deadline").flatpickr({
          'dateFormat': 'U',
          'altInput': true,
          'altFormat': 'Y-m-d'
        });
      </script>

      <script  type="text/javascript">
        var placeholder_text = $('select.gf-kanban-todo-assignee:first').attr('placeholder');
        var user_language = $('select.gf-kanban-todo-assignee:first').data('user-lang');
        
        console.log('language='+user_language);
        
        jQuery('select.gf-kanban-todo-assignee').select2({
          language : user_language,
          ajax: {
            url: function (params) {
              return '/kanban/autocomplete/user/<?php echo $node->og_group_content_ref[LANGUAGE_NONE][0]['target_id'] ?>/'+params.term;
            },
            delay : 250,
            dataType: 'json',
            type : 'POST',
            processResults: function (data) {
              //console.log(data);
              var pattern = '<[0-9]*>';
              var results = [];

              $.each(data, function(key, item){
                var newKey_raw = key.match(pattern);
                var newKey = newKey_raw[0].replace('<', '').replace('>', '');

                results.push({'id': newKey, 'text': key, 'html' : item});
              });
              return {'results': results};
            }
          },
          templateResult: function(data) {
            var elt = document.createElement('span');
            $(elt).html(data.html);
            return $(elt).html();
          },
          escapeMarkup: function(markup) {
            return markup;
          },
          allowClear: true,
          placeholder: placeholder_text ,
          dropdownParent: $("#kanbanModal")
        });

      </script>

    </div>
    <!-- /.todo-list -->
<?php if($canEdit) : ?>
    <?php echo render($form); ?>
<?php endif; ?>
  </div>
</div>