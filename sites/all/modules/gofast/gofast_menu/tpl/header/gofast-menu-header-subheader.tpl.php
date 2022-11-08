<div class="card-title text-truncate justify-content-end d-inline-block w-100">
    <?php print $breadcrumb; ?>
</div>
<div class="card-toolbar align-items-start">
    <div class="btn-toolbar" role="toolbar" aria-label="...">        
        <div class="btn-group" id="" role="group">
            <?php if($node->type == "alfresco_item"): ?>
                <!-- REFRESH BUTTON -->
                <div id="refresh_actions_button" class="d-none btn-group btn-group-xs">
                    <a type="button" class="btn btn-outline-secondary btn-icon btn-sm position-relative disabled" id="refresh-preview" disabled="" onclick="Drupal.gofast_cmis.reloadPreview();">
                        <i class="fa fa-refresh icon-nm"></i>
                    </a>
                </div>
            <?php endif; ?>
            
            <!--begin::Contextual actions-->
            <?php //echo  $contextual_actions?>
            <?php foreach($contextual_actions as $action):?>
                <?php print $action; ?>
            <?php endforeach?>
            <!--end::Contextual actions-->
        </div>
    </div>
</div>

