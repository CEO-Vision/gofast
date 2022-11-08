<div class="card card-custom ">
    <div class="card-body p-0">
        <div class="pt-0 px-8 pb-4">
            <div class="gutter-b mt-4 row">
                <div class="align-items-center">
                    <div class="symbol symbol-100 flex-shrink-0">
                        <span class="symbol-label"><?php print $symbol; ?></span>
                    </div>
                </div>
                <div class="col-6 font-weight-bolder font-size-h2 text-dark-75 ml-3">
                    <?php echo $userlist_name; ?>
                </div>
                <div id="contextual-actions-loading" class="loader-breadcrumb not-processed"></div>
                <div id="userlist-node-actions">

                </div>
            </div>
            <div class="gutter-b mt-4">
                <span class="font-size-md text-muted text-hover-primary font-weight-bold mb-4 d-block text-uppercase"><?php echo t('Description', array(), array('context' => 'gofast:gofast_userlist')); ?></span>
                <p class="text-dark-75 font-size-lg font-weight-normal pt-2"><?php echo $description; ?></p>
            </div>
        </div>
    </div>
</div>

<script type='text/javascript'>
    jQuery(document).ready(function() {
        if(jQuery("#contextual-actions-loading").length !== 0 && jQuery("#contextual-actions-loading").hasClass('not-processed')){
            jQuery("#contextual-actions-loading").removeClass('not-processed');
            jQuery.get(location.origin + "/gofast/node-actions/" + Gofast.get('node').id, function(data){
                jQuery("#contextual-actions-loading").remove();
                jQuery('#userlist-node-actions').replaceWith(data.replace("w-100 ", ""));
                Drupal.attachBehaviors();
            });
        }
    });
</script>
