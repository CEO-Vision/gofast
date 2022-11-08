<div id="<?php echo $container_id; ?>" class="<?php echo $container_class; ?>">
    <div class="xeditable-trigger-1">
        <a 
            href="<?php echo $href; ?>"
            id="manage-locations"
            class="btn btn-primary btn-sm p-2 ctools-use-modal xeditable-trigger<?= isset($relative_positioning) && $relative_positioning ? " top-0" : "" ?>"
            alt="<?php echo t('Edit', array(), array('context' => 'gofast')); ?>"

        >   
            <span class="font-weight-bolder">
                <?php echo t('Edit', array(), array('context' => 'gofast')); ?>
            </span>
        </a>
    </div>
</div>