<?php // there is no specific module for archiving and since this archive-purposed template will be displayed in a modal,
// it seems logical to put it here 
?>

<div class="panel panel-default manage-archive-panel">
    <div class="panel-body">
        <span id="nid" style="display:none;"><?php echo $nid; ?></span>
        <?php echo t('Archiving of', array(), array('context' => 'gofast:cmis')); ?> <strong id="title"><?php echo $title; ?></strong> :
        <div class="manage-archive-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:cmis')) ?></div>
    </div>
</div>