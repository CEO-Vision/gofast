<?php // there is no specific module for archiving and since this archive-purposed template will be displayed in a modal,
// it seems logical to put it here 
?>

<div class="panel panel-default manage-bulkactions-users-panel">
    <div class="panel-body">
        <span id="uid" style="display:none;"><?php echo $uid; ?></span>
        <span id="action" style="display:none;"><?php echo $action; ?></span>
        <span id="options" style="display:none;"><?php echo !$options ? "" : implode(",", $options); ?></span>
        <?php echo $title_action ?> <strong id="title"><?php echo $title; ?></strong> :
        <div class="manage-bulkactions-users-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast')) ?></div>
    </div>
</div>