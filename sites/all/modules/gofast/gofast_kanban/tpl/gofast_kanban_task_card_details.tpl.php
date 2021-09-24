<div class="task-details">
  <?php
  $node = node_load($task->nid);
  $canEdit = node_access('update', $node, $user);


  $canComment = node_access('update', $node, $user) || gofast_kanban_task_can_comment($task->nid, $user);
  ?>

  <!---------------------------------------------------------------------------->
  <!-- TASK TITLE -->
  <div class="row my-3 mt-1">
    <div class="col-6 gf-kanban-field-edit container-fluid"> 
<!--      <div class="row">-->
        <span class="gf-kanban-not-editing <?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>">
          <h5 id="modalViewTaskLabel" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?>><?php echo $task->title ?></h5>
        </span>
      
        <?php if ($canEdit): ?>
          <span class="gf-kanban-editing"  style="display:none;">
            <form id="gf-kanban-task-edit-label" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-label" data-taskid="<?php echo $task->nid; ?>">
              <input id="task-label"class="form form-control" name="label" value="<?php echo $task->title ?>" /> 
            </form>
          </span>     
          <div class="gf-kanban-editing" style="display:none;">
            <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
            <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
          </div>
        <?php endif; ?>
      <!--</div>-->
    </div>

    <!---------------------------------------------------------------------------->
    <!-- TASK DUE DATE (DEADLINE) -->
    <div class="col-6 gf-kanban-field-edit container-fluid">
      <div class="row <?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>">
        <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php echo t('Due date', array(), array('context' => 'gofast_kanban')) ?> &nbsp;
        </h6>
        <span class="gf-kanban-not-editing" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?>> 
          <?php if (!empty($task->field_date[LANGUAGE_NONE][0]['value'])): ?>
            <?php
            //convert date into timestamp 
            $date_deadline = new DateTime($task->field_date[LANGUAGE_NONE][0]['value']);
            $timestamp_deadline = $date_deadline->getTimestamp();
            ?>
          &nbsp; <?php echo format_date($timestamp_deadline, 'privatemsg_years') ?>
          <?php else: ?>

          <?php endif; ?>
        </span>
        
        <?php if ($canEdit): ?>
          <span class="gf-kanban-editing"  style="display:none;">

            <form id="gf-kanban-task-edit-deadline" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-deadline" data-taskid="<?php echo $task->nid; ?>">
              <div class="input-group">
                <input name="deadline"  id="task-deadline"type="text" class="form-control form-control-reflow flatpickr-input" data-toggle="flatpickr" value="<?php echo $timestamp_deadline; ?>" style="width:80px;">
                <div class="input-group-append">
                  <button type="button" class="btn btn-secondary" onclick="KanbanBoard.clearDate($(this));"><i class="fa fa-times"></i></button>
                </div>
              </div>
            </form>
            <script type="text/javascript">
              jQuery("input#task-deadline").flatpickr({
                'dateFormat': 'U',
                'altInput': true,
                'altFormat': 'Y-m-d'
              });
            </script>
          </span>
          <span class="gf-kanban-editing" style="display:none;">
            <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
            <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
          </span>
        <?php endif; ?>
      </div>
    </div>
  </div>

  <div class="row my-3">

    <!---------------------------------------------------------------------------->
    <!-- TASK PERSON-IN-CHARGE -->
    <div class="col-6 mb-2 task-person-in-charge gf-kanban-field-edit">
      <span class="<?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>">
        <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php echo t('Responsible', array(), array('context' => 'gofast_kanban')); ?>
        </h6>     
        <span class="gf-kanban-not-editing" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php if (!empty($task->field_person_in_charge[LANGUAGE_NONE][0]['target_id'])) : ?>
            <?php $person_in_charge_uid = $task->field_person_in_charge[LANGUAGE_NONE][0]['target_id']; ?>
            <a href="#" class="link-text" data-toggle="tooltip" title="@<?php echo gofast_user_get_login($person_in_charge_uid) ?>">
              <figure class="user-avatar" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($person_in_charge_uid) ?>">
                <?php
                echo theme('user_picture', array('account' => user_load($person_in_charge_uid),
                    'popup' => FALSE,
                    'dimensions' => array('width' => '24px', 'height' => '24px')
                    )
                )
                ?>
              </figure><?php echo gofast_user_get_display_name_sql($person_in_charge_uid) ?>
            </a>
          <?php else: ?>
            <em><?php echo t('Nobody', array(), array('context' => 'gofast_kanban')); ?></em>
          <?php endif; ?>
        </span>
      </span>

        <?php if ($canEdit): ?>
          <span class="gf-kanban-editing"  style="display:none;">
            <form id="gf-kanban-task-edit-person-in-charge" name="person-in-charge" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-person-in-charge" data-taskid="<?php echo $task->nid; ?>">
              <select class="task-person-in-charge form form-control" id="task-person-in-charge"  name="person-in-charge">
                <?php if (!empty($task->field_person_in_charge[LANGUAGE_NONE][0]['target_id'])) : ?>
                  <?php $person_in_charge_uid = $task->field_person_in_charge[LANGUAGE_NONE][0]['target_id']; ?>
                  <option value="<?php echo $person_in_charge_uid ?>" selected="selected"><?php echo gofast_user_get_display_name_sql($person_in_charge_uid) ?></option>
                <?php endif; ?>
              </select>
            </form>
            <script type="text/javascript">
              jQuery('select#task-person-in-charge').select2({
                ajax: {
                  url: function (params) {
                    return '/kanban/autocomplete/user-not-readonly/<?php echo $task->og_group_content_ref[LANGUAGE_NONE][0]['target_id']; ?>/' + params.term;
                  },
                  delay : 250,
                  dataType: 'json',
                  method: 'POST',
                  processResults: function (data) {
                    //console.log(data);
                    var pattern = '<[0-9]*>';
                    var results = [];

                    $.each(data, function (key, item) {
                      var newKey_raw = key.match(pattern);
                      var newKey = newKey_raw[0].replace('<', '').replace('>', '');
                      
                      results.push({'id': newKey, 'text': key, 'html' : item });
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
                placeholder: window.parent.Drupal.t('Search a user', {}, {'context': 'gofast_kanban'}),
                dropdownParent: $("#kanbanModal")
              });

            </script> 
          </span>
          <span class=" gf-kanban-editing" style="display:none;">
            <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
            <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
          </span>
        <?php endif; ?>
    </div>

    <!---------------------------------------------------------------------------->
    <!-- TASK ASSIGNEE(S) -->
    <div class="col-6 mb-2  gf-kanban-field-edit" style="margin-left:-10px;">
      <div class="assignee">
        <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php echo t('Participant(s)', array(), array('context' => 'gofast_kanban')); ?>
        </h6>
        <span class="gf-kanban-not-editing" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?>>
          <div class="avatar-group">
            <?php if (count($task->field_members[LANGUAGE_NONE]) > 0) : ?>
            <?php foreach ($task->field_members[LANGUAGE_NONE] as $key => $elt): ?>
              <figure class="user-avatar" data-toggle="tooltip" title="<?php echo gofast_user_get_display_name_sql($elt['target_id']) ?>"> 
                <?php $member = user_load($elt['target_id']); ?>
                <?php
                echo theme('user_picture', array('account' => $member,
                    'popup' => FALSE,
                    'dimensions' => array('width' => '24px', 'height' => '24px'))
                )
                ?>
              </figure>
            <?php endforeach; ?>
            <?php else: ?>
              <em><?php echo t('Nobody', array(), array('context' => 'gofast_kanban')); ?></em>
            <?php endif; ?>
          </div>
        </span>
        <?php if ($canEdit): ?>
          <span class="gf-kanban-editing"  style="display:none;">
            <form id="gf-kanban-task-edit-assignees" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-assignees" data-taskid="<?php echo $task->nid; ?>">
              <select class="form form-control" id="task-assignees" name="members" multiple="multiple">
                <?php foreach ($task->field_members[LANGUAGE_NONE] as $key => $elt): ?>
                  <option value="<?php echo $elt['target_id'] ?>" selected="selected"><?php echo gofast_user_get_login($elt['target_id']) ?></option>
                <?php endforeach; ?>
              </select>
            </form>
            <script type="text/javascript">
              jQuery('select#task-assignees').select2({
                ajax: {
                  url: function (params) {
                    return '/kanban/autocomplete/user/<?php echo $task->og_group_content_ref[LANGUAGE_NONE][0]['target_id']; ?>/' + params.term;
                  },
                  delay : 250,
                  dataType: 'json',
                  method: 'POST',
                  processResults: function (data) {
                    
                    var results = [];

                    //Case to integrate userlist in selection 
//                    var pattern = /data-id=\"[0-9]*/; 
//                    var pattern_type = /data-type=\"[a-z]*/;
//                    $.each(data, function (key, item) {
//
//                      var newKey = newKey_raw[0].replace('<', '').replace('>', '');
//
//                      var newKey_raw = item.match(pattern);
//                      var keyType_raw = item.match(pattern_type);
//
//                      var newKey = newKey_raw[0].replace('data-id="', '');
//                      var newKeyType = keyType_raw[0].replace('data-type="', '');
//
//                      results.push({'id': newKey+'_'+newKeyType, 'text': key, 'html' : item });
//                    });
                    
                    var pattern = '<[0-9]*>';
                    $.each(data, function (key, item) {
                      var newKey_raw = key.match(pattern);
                      var newKey = newKey_raw[0].replace('<', '').replace('>', '');

                      results.push({'id': newKey, 'text': key, 'html' : item });
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
                multiple: true,
                allowClear: true,
                placeholder: window.parent.Drupal.t('Search users', {}, {'context': 'gofast_kanban'})
              });
            </script> 
          </span>
          <span class="gf-kanban-editing" style="display:none;">
            <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
            <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
          </span>
        <?php endif; ?>
      </div>
    </div>
  </div>
  
  <div class="row my-3">
    <!---------------------------------------------------------------------------->
    <!-- TASK STATUS-->
    <div class="col-6 task-status gf-kanban-field-edit container-fluid">
      <div class="row <?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>" style="margin-left:0px;">
        <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php echo t('Status', array(), array('context' => 'gofast_kanban')); ?>  &nbsp;
        </h6>     
        <span class="gf-kanban-not-editing" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
          <?php if (!empty($task->field_state)) : ?>
            <?php $task_status = $task->field_state[LANGUAGE_NONE][0]['tid']; ?>
            <?php echo i18n_taxonomy_localize_terms(taxonomy_term_load($task_status))->name; ?>
          <?php else: ?>
            <em><?php echo t('None', array(), array('context' => 'gofast_kanban')); ?></em>
          <?php endif; ?>
        </span>
        
        <?php if ($canEdit): ?>
          <span class="gf-kanban-editing"  style="display:none; width:60%;" >
            <form id="gf-kanban-task-edit-status" name="status" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-status" data-taskid="<?php echo $task->nid; ?>">
              <select class="task-status form form-control" id="task-status"  name="status" >
                
                <?php foreach($all_status = gofast_kanban_get_available_status() as $key => $status): ?>
                  <?php $selected = ''; ?>
                  <?php if (! empty($task->field_state) &&  $task->field_state[LANGUAGE_NONE][0]['tid'] == $status['tid']) : ?>
                    <?php $selected = 'selected="selected"'; ?>
                  <?php endif; ?>
                  <option value="<?php echo $status['tid'] ?>" <?php echo $selected ; ?> ><?php echo i18n_taxonomy_localize_terms(taxonomy_term_load($status['tid']))->name; ?></option>
                <?php endforeach; ?>
              </select>
            </form>
            <script type="text/javascript">
              
              jQuery('select#task-status').select2({
                dropdownParent: $("#kanbanModal")
              });
            </script> 
          </span>
          <span class=" gf-kanban-editing" style="display:none;">
            <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
            <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
          </span>
        <?php endif; ?>
      </div>

      
    </div>
    
    <!---------------------------------------------------------------------------->
    <!-- TASK LABEL(S) -->
    <div class="col-6 mb-3">
<!--      <h6>Labels</h6>
      <span class="tile bg-green"></span>
      <span class="tile bg-pink"></span>
      <span class="tile bg-yellow"></span>
      <div class="dropdown d-inline-block">
        <a href="#" class="tile" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
          <i class="fa fa-plus"></i>
        </a>
        <div class="dropdown-arrow"></div>
        {% include ui/dropdown-labels-02.html %}
      </div>-->
    </div>
  </div>
    <!---------------------------------------------------------------------------->
    <!-- TASK VISIBILITY(S) -->
    <!-- Enable visibility for task in parent board synthesis -->
<!--    <div class="col-12 mb-2">
      <div class="parent-board-synthesis-visibility gf-kanban-field-edit">
        <h6><?php echo t("Parent space's board synthesis", array(), array('context' => 'gofast_kanban')); ?> &nbsp;<i class="fa fa-question-circle"></i></h6>


        <?php if ($canEdit): ?>
          <div class="custom-control custom-checkbox">
            <form id="gf-kanban-task-edit-content-visibility" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-content-visibility" data-taskid="<?php echo $task->nid; ?>">
              <input type="checkbox" class="custom-control-input" name="content-visibility" id="task-content-visibility" <?php echo ($task->content_visibility[LANGUAGE_NONE][0]['value'] == 0 ) ? 'checked="checked"' : ''; ?> onChange="KanbanBoard.updateTask($(this));" >
              <label class="custom-control-label" for="task-content-visibility"><?php echo t('Meta-task', array(), array('context' => 'gofast_kanban')) ?></label>
            </form>
          </div>
        <?php else: ?>
          <div class="">
            <?php if ($task->content_visibility[LANGUAGE_NONE][0]['value'] == 0): ?>
              <i class="fa fa-check-square-o" ></i>
            <?php else : ?>
              <i class="fa fa-square-o" ></i>
            <?php endif; ?>
            <label class="" for="task-content-visibility"><?php echo t('Meta-task', array(), array('context' => 'gofast_kanban')) ?></label>
          </div>
        <?php endif; ?>
      </div>
    </div>  -->

  <!---------------------------------------------------------------------------->
  <!-- TASK DESCRIPTION -->
  <div class="mb-2 task-description gf-kanban-field-edit">
    <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
      <?php echo t('Description', array(), array('context' => 'gofast_kanban')); ?>
    </h6>
    <span class="gf-kanban-not-editing  <?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> >
        <pre class="gf-kanban-card-desc"><?php echo strlen($task->body[LANGUAGE_NONE][0]['value']) > 0 ? urldecode(str_replace(array("\n", "\t"), "", $task->body[LANGUAGE_NONE][0]['value'])): "&nbsp; "; ?></pre>
    </span>
    <?php if ($canEdit): ?>
      <span class=" gf-kanban-editing" style="display:none;">
        <div>
          <form id="gf-kanban-task-edit-description" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-description" data-taskid="<?php echo $task->nid; ?>">
            <textarea id="task-description" class="form form-control" name="description"><?php echo urldecode(trim($task->body[LANGUAGE_NONE][0]['value'])); ?></textarea>
          </form>
          <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
          <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
        </div>
      </span>
    <?php endif; ?>
  </div>


  <!---------------------------------------------------------------------------->
  <!-- TASK ATTACHMENTS -->
  <div class="task-attachements gf-kanban-field-edit">
    <h6 <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?> > 
      <?php echo t('Attachment(s)', array(), array('context' => 'gofast_kanban')); ?>
    </h6>
    <span class="gf-kanban-not-editing <?php if ($canEdit): ?>gf-kanban-show-editable<?php endif; ?>" <?php if ($canEdit): ?> onclick="KanbanBoard.editTask($(this));"<?php endif; ?>>
      <div class="list-group">
      <?php if ( count($task->field_target_link[LANGUAGE_NONE]) == 0 ){ echo "&nbsp;" ; } ?>
      <?php foreach ($task->field_target_link[LANGUAGE_NONE] as $key => $elt): ?>
        <?php $node = node_load($elt['target_id']); ?>

        <span class="list-group-item">
            <span class="list-group-item-figure"><?php echo theme('gofast_node_icon_format', array('node' => $node)) ?></span>
            <span class="list-group-item-body"><a href="<?php echo $base_url ?>/node/<?php echo $node->nid ?>" target="_blank" class="gofast-non-ajax "><span class="gf-kanban-node-title"><?php echo $node->title ?></a></span>
        </span>
      <?php endforeach; ?>
      </div>
    </span>
    <?php if ($canEdit): ?>
      <span class=" gf-kanban-editing" style="display:none;">
        <div>
          <form id="gf-kanban-task-edit-attachement" action="/kanban/task/<?php echo $task->nid; ?>/update" data-field="task-attachements" data-taskid="<?php echo $task->nid; ?>">
            <select id="task-attachements" class="form form-control" name="attachements" multiple="multiple"> 
            <?php foreach ($task->field_target_link[LANGUAGE_NONE] as $key => $elt): ?>
            <?php $node = node_load($elt['target_id']); ?>
              <option value="<?php echo $elt['target_id']?>" selected="selected"><?php echo $node->title ?></option>
            <?php endforeach; ?>
            </select>
          </form>
           <script type="text/javascript">
              jQuery('select#task-attachements').select2({
                ajax: {
                  url: function (params) {
                    return '/kanban/autocomplete/node/<?php echo $task->og_group_content_ref[LANGUAGE_NONE][0]['target_id']; ?>/' + params.term;
                  },
                  delay : 250,
                  dataType: 'json',
                  method: 'POST',
                  processResults: function (data) {
                    var pattern = '<[0-9]*>';
                    var results = [];

                    $.each(data, function (key, item) {
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
                multiple: true,
                allowClear: true,
                placeholder: window.parent.Drupal.t('Search for documents', {}, {'context': 'gofast_kanban'})
              });
            </script> 
          <button type="button" class="btn btn-sm btn-subtle-success update-task" onclick="KanbanBoard.updateTask($(this));"><i class="fa fa-check"></i></button>
          <button type="button" class="btn btn-sm btn-light cancel-update-task" onclick="KanbanBoard.cancelEditTask($(this));"><i class="fa fa-times"></i></button>
        </div>
      </span>
    

    <?php endif; ?>
  </div>  

</div>

<hr>

<!-- CheckList(s) -->
<?php foreach ($task_todolists as $key => $task_todolist): ?>
  <?php echo theme('kanban_checklist', array('todolist' => $task_todolist, 'form' => $todo_form)); ?> 
<?php endforeach; ?>

<hr>

<!-- Comments -->
<?php if ($canComment): ?>
  <?php echo render($comment_form); ?>
  <hr>
<?php endif; ?>


<!-- Activities -->
<?php //$task_activities = array();  ?>
<div class="task-activities">
  <?php echo theme('kanban_activities', array('activities' => $task_activities)); ?> 
</div>
