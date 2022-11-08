<?php

/*
 * Modal basic template
 *
 * Variables
 *
 * $title : modal title
 * $content : modal content (eg: form...)
 * $footer : modal footer (eg: button to submit...)
 */

?>

<!-- Modal-->
<div class="modal" id="gofast_basicModal" role="dialog" aria-labelledby="gofastBasicModal" aria-hidden="true">
    <div class="modal-dialog modal-lg modal-dialog-scrollable modal-dialog-centered" role="document">
        <div class="modal-content min-h-500px">
            <div class="modal-header">
                <div class="modal-title font-size-h5 text-white" id="modal-title"><?php print $title; ?></div>
                <button type="button" class="close" data-dismiss="modal" aria-label="Close">
                    <i aria-hidden="true" class="ki ki-close text-white"></i>
                </button>
            </div>
            <div id="modal-content" class="w-100 modal-body overflow-auto">
                <?php print $content; ?>
            </div>
            <?php if(isset($footer) && $footer != ''): ?>
                <div id="modal-footer" class="modal-footer d-flex justify-content-start">
                    <?php print $footer; ?>
                </div>
            <?php endif;?>
        </div>
    </div>
</div>
