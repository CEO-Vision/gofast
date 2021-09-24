<div id="delete_space_modal_container">
  <?php print t('Are you sure you want to delete this space ? This destructive action cannot be undone', array(), array('context' => 'gofast:og'));?>
  <br />
  <button type="button" class="btn btn-danger" onClick="Drupal.deleteSpace(<?php echo $gid; ?>)">
    <i class="fa fa-trash"></i> <?php echo t('Delete'); ?>
  </button>
</div>

<div id="delete_space_modal_process_container" style="display:none; min-width:600px;">
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="delete_step_1"><?php echo t("Step 1: Delete the documents.", array(), array('context' => 'gofast:og')); ?></div>
      
      <ul>
        <li id="delete_step_1_1"><?php echo t("Process multifiled documents", array(), array('context' => 'gofast:og')); ?></li>
        <li id="delete_step_1_2"><?php echo t("Delete the not multifiled documents", array(), array('context' => 'gofast:og')); ?></li>
      </ul>
    </div>
  </div>
  
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="delete_step_2"><?php echo t("Step 2: Delete the folders.", array(), array('context' => 'gofast:og')); ?></div>
    </div>
  </div>
  
  <div class="panel panel-default">
    <div class="panel-body">
      <div id="delete_step_3"><?php echo t("Step 3: Delete the space.", array(), array('context' => 'gofast:og')); ?></div>
    </div>
  </div>
</div>