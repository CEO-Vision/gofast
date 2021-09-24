<?php 
global $user;
  $canEdit = node_access('update', node_load($kanban_nid)); // for administrator
  $canCreateTask =  og_user_access('node', $kanban_space_nid, 'create task content', $user);
?>

<div class="tasks" data-kanbannid="<?php echo $kanban_nid ?>" data-tid="<?php echo $tasklist['id'] ?>"   >
  <!-- .tasks-header -->
  <div class="task-header" <?php if($canEdit): ?> style="cursor:move;" title="<?php echo t('Move column', array(), array('context' => 'gofast_kanban')); ?>"<?php endif; ?> >
      <h3 class="task-title mr-auto gf-kanban-not-editing">
        <?php echo $tasklist['title']; ?>
        <span class="text-muted">(<?php echo count($tasks) ?>)</span>

      </h3>
      <div class="dropdown gf-kanban-not-editing">
      <!--<button class="btn btn-light btn-icon text-muted" data-toggle="modal" data-target="#kanbanModal" title="Add task" data-url="/kanban/<?php echo $kanban_nid ?>/add/task">-->

      <?php if ($canCreateTask) : ?>
        <button class="btn btn-light btn-icon text-muted" title="<?php echo t("Add a new card", array(), array('context' => 'gofast:gofast_kanban')) ?>" 
                onclick="window.parent.window.Gofast.display_modal_form('/modal/ajax/node/<?php echo $kanban_nid ?>/add/task/<?php echo $tasklist['id'] ?>', '<?php echo t("Add a new card", array(), array('context' => 'gofast:gofast_kanban')) ?>')">
          <i class="fa fa-plus-circle"></i>
        </button>  
      <?php endif; ?>
      <?php if ($canEdit): ?>
        <button class="btn btn-light btn-icon text-muted dropdown-toggle gf-kanban-dropdown" id="dropdownMenu-<?php echo $tasklist['id']?>" title="<?php echo t("More actions ...", array(), array('context' => 'gofast:gofast_kanban')) ?>" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
            <i class="fa fa-ellipsis-v"></i>
        </button>
        <div class="dropdown-menu dropdown-menu-right" aria-labelledby="dropdownMenu-<?php echo $tasklist['id']?>">
          <button class="dropdown-item" type="button" data-nid='<?php echo $kanban_nid ?>' onclick="KanbanBoard.editColumn($(this))" ><?php echo t('Rename column', array(), array('context' => 'gofast_kanban')); ?></button>
          <button class="dropdown-item" type="button" data-nid="<?php echo $kanban_nid ?>" data-eltid="<?php echo $tasklist['id'] ?>" onclick="KanbanBoard.preDeleteColumn(<?php echo $tasklist['id'] ?>, <?php echo $kanban_nid ?> );"><?php echo t('Delete column', array(), array('context' => 'gofast_kanban')); ?></button>
        </div>
      <?php endif; ?>
    </div>
    <?php if ($canEdit): ?>
      <div class="gf-kanban-editing row task-title mr-auto " style="display:none;">
        <form id="gf-kanban-column-edit-label-<?php echo $tasklist['id'] ?>" class="gf-kanban-column-edit-label" action="/kanban/<?php echo $kanban_nid ?>/column/<?php echo $tasklist['id'] ?>/update" data-field="column-label-<?php echo $tasklist['id'] ?>" data-kanbannid="<?php echo $kanban_nid ?>">
          <input id="column-label-<?php echo $tasklist['id'] ?>" class="form form-control" name="label" value="<?php echo $tasklist['title'] ?>" /> 
          <button type="button" class="btn btn-sm btn-subtle-primary update-column" onclick="KanbanBoard.updateColumn($(this));"><i class="fa fa-check"></i></button>
          <button type="button" class="btn btn-sm btn-light cancel-update-column" onclick="KanbanBoard.cancelEditColumn($(this));"><i class="fa fa-times"></i></button>
        </form>
      </div>
    <?php endif; ?>

  </div>
  <!-- /.tasks-header -->

  <!-- .task-body -->
  <div class="task-body" id="taskstatus_<?php echo $tasklist['id'] ?>" data-columnId="<?php echo $tasklist['id'] ?>" >

      <?php foreach( $tasks as $key => $task ): ?>
        <?php echo theme('kanban_task', array('task'=> $task) ); ?> 
      <?php endforeach; ?>

  </div>
  <!-- /.task-body -->
</div>
