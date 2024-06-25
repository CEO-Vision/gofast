<div class="col-md-9 docs-buttons" id="cropper-buttons">
    <div class="btn-group">
        <button type="button" class="btn btn-sm btn-primary crop-buttons" id="btnRotateLeft" data-method="rotate" data-option="-45" title="<?php print t('Rotate Left', array(), array('context' => 'gofast:gofast_user')); ?>">
        <span class="docs-tooltip" data-toggle="" title="">
            <span class="fa fa-rotate-left"></span>
        </span>
        </button>
        <button type="button" class="btn btn-sm btn-primary" id="btnRotateRight" data-method="rotate" data-option="45" title="<?php print t('Rotate Right', array(), array('context' => 'gofast:gofast_user')); ?>">
        <span data-toggle="" title="" data-original-title="cropper.rotate(45)">
            <span class="fa fa-rotate-right"></span>
        </span>
        </button>
    </div>
    <button type="button" class="btn btn-sm btn-primary" id="btnReset" data-method="reset" title="<?php print t('Reset', array(), array('context' => 'gofast')); ?>" id="reset">
        <span class="docs-tooltip" data-toggle="" title="">
        <span class="fa fa-refresh"></span> <?php print t('Reset', array(), array('context' => 'gofast')); ?>
        </span>
    </button>
    <div>
        <label for="inputImage" class="btn btn-sm btn-primary btn-upload crop-buttons" id="btnInputImgAvatar" data-toggle="" title="<?php print t('Import image with Blob URLs', array(), array('context' => 'gofast')); ?>"><i class="fa fa-upload"></i><?php print t('Upload', array(), array('context' => 'gofast')); ?></label>
        <input type="file" class="sr-only" id="inputImage" name="file" accept="image/*">
    </div>
    <button type="button" class="btn btn-sm btn-success crop-buttons" <?= $id_attribute ?> id="save"><?php print t('Save', array(), array('context' => 'gofast')); ?></button>
</div><!-- /.docs-buttons -->