<div id="delete_space_modal_container">
  <?php if(gofast_og_check_replication_delete_space($gid)): ?>
    <h3 class="confirmation_header">
      <?php print t('Are you sure you want to delete this space ? This destructive action cannot be undone', array(), array('context' => 'gofast:og'));?>.
    </h3>
    <br />
    <div class="form-group delete_space_confirm_name_container" >
      <label for="delete_space_confirm_name"><?php print t('Please type the name of this space to confirm this action', array(), array('context' => 'gofast:og'));?>
    <span>: <?php echo node_load($gid)->title ?></span>
    </label>
      <input type="text" required class="form-control" placeholder="<?php print t("Please type the name of this space here",  array(), array('context' => 'gofast:og')) ?>" id="delete_space_confirm_name" name="delete_space_confirm_name" value="" />
    </div>
   
    <button type="button" id="deleteButton" class="btn btn-danger" disabled onClick="Drupal.deleteSpace(<?php echo $gid; ?>)">
      <i class="fa fa-trash"></i> <?php echo t('Delete space'); ?>
    </button>
  <?php else: ?>
    <?php print t('Some documents of this space are currently being processed due to a move or a deletion, so you can\'t delete this space for the moment', array(), array('context' => 'gofast:og'));?>
  <?php endif; ?>
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
<style>
  .confirmation_header{
    font-weight: bold;
    font-size: 16px;
    color: #d01d31 !important;
  }
  #delete_space_modal_container{
    min-width: 600px;
    margin-top: 2rem;
  }
  .delete_confirmation{
    top: 2rem;
  }
    #delete_space_confirm_name{
    width: 40%;
  }

  .delete_space_confirm_name_container label span{
    font-weight: bold;
  }
   
  .delete_space_confirm_name_container{
    margin-top:2rem;
  }
  
</style>
<script>
  $(document).ready(function() {
    $("#delete_space_confirm_name").on("keyup change", function() {
      const inputVal = $(this).val();
      const nodeTitle = "<?php echo preg_replace('/\b_/', '', node_load($gid)->title); ?>";
      if (inputVal === nodeTitle) {
        $(".btn-danger").attr("disabled", false);
      } else {
        $(this).focus();
        $(".btn-danger").attr("disabled", true);
      }
    });

    $("#delete_space_confirm_name").on("change", function() {
      if ($(this).val() === "") {
        $(".btn-danger").attr("disabled", true);
      }
    });
  });
</script>
