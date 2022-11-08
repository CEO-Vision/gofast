<div class="panel panel-default manage-bulkactions-metatag-panel">
    <div class="panel-body">
        <span id="tid" style="display:none;"><?php echo $tid; ?></span>
        <span id="action" style="display:none;"><?php echo $action; ?></span>
        <?php echo $title_action ?> <strong id="title"><?php echo $title; ?></strong> :
        <div class="manage-bulkactions-metatag-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast')) ?></div>
    </div>
</div>