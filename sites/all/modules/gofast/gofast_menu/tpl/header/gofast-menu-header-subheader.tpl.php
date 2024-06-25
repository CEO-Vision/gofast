<div class="card-title text-truncate justify-content-start w-100 h-100" id="gofastMenuHeaderSubheader">
    <?php print $breadcrumb; ?>
</div>

<div class="card-toolbar align-items-start <?= gofast_essential_is_essential() ? 'flex-nowrap' : '' ?>">
    <?php $detect = new Mobile_Detect(); ?>
    <?php if (gofast_essential_is_essential() && $node->type == "alfresco_item" && (!$detect->isMobile() || $detect->isTablet())) : ?>
        <div id="navigationButtons" class="d-flex justify-content-between" style="left: 85%; top: 0.5rem;  width: 140px; margin-right:15px;">
            <div>
                <a id="node-previous-content-button" class="btn <?= $hasContext ? "btn-primary" : "noContext"; ?> btn-icon btn-sm position-relative">
                    <i class="ki ki-bold-arrow-back text-white icon-nm"></i>
                </a>
            </div>
                <div>
                    <a id="node-exit-button" class="btn btn-primary btn-icon btn-sm position-relative">
                        <i class="ki ki-bold-close text-white icon-nm"></i>
                    </a>
                </div>
            <div>
                <a id="node-next-content-button" class="btn <?= $hasContext ? "btn-primary" : "noContext"; ?> btn-icon btn-sm position-relative">
                    <i class="ki ki-bold-arrow-next text-white icon-nm"></i>
                </a>
            </div>
          <div>
            <a id="node-full-screen-button" class="btn btn-primary btn-icon btn-sm position-relative">
              <i class="fa fa-arrows-alt text-white icon-nm"></i>
            </a>
          </div>
        </div>

    <?php endif; ?>
    <?php if(gofast_essential_is_essential() && $node->type == "webform" && (!$detect->isMobile() || $detect->isTablet())) :?>
        
        <div id="navigationButtons" class="d-flex justify-content-between" style="left: 85%; top: 0.5rem;  width: 60px; margin-right:15px;">
            <div>
                <a id="node-exit-button" class="btn btn-primary btn-icon btn-sm position-relative">
                    <i class="ki ki-bold-close text-white icon-nm"></i>
                </a>
            </div>
        </div>
    <?php endif;?>
    
    <div class="btn-toolbar <?= gofast_essential_is_essential() ? 'flex-nowrap' : '' ?>" role="toolbar" aria-label="...">
        <div class="btn-group" id="" role="group" <?= gofast_essential_is_essential() && !$detect->isMobile() && $node->type == "alfresco_item" ? "style='width: 170px'" : "" ?>>
            <?php if($node->type == "alfresco_item" && $node->status != 0): ?>
                <!-- REFRESH BUTTON -->
                <div id="refresh_actions_button" class="d-none btn-group btn-group-xs">
                    <a type="button" class="btn btn-outline-secondary btn-icon btn-sm position-relative disabled" id="refresh-preview" disabled="" onclick="Drupal.gofast_cmis.reloadPreview();">
                        <i class="fa fa-refresh icon-nm"></i>
                    </a>
                </div>
            <?php endif; ?>
            
            <!--begin::Contextual actions-->
            <?php foreach($contextual_actions as $action):?>
                <?php print $action; ?>
            <?php endforeach?>
            <!--end::Contextual actions-->
        </div>
    </div>
</div>

<script>
Drupal.behaviors.gofast_header_subheader = {
    attach: function(context) {
        if(!Gofast.Essential || !Gofast._settings.isEssential){return;}
        
        if (($(".GofastNode").length == 0 && $("#forum_breadcrumb").length == 0 && (Gofast.get("node") != undefined && Gofast.get("node").type != "forum")) || ($('[id=gofastMenuHeaderSubheader]').length == $('[id=gofastMenuHeaderSubheader].processed').length)) {
            return;
        }
        
        //Prenvent multiple calls
        $("[id=gofastMenuHeaderSubheader]").each((i,el)=>{
            if(!$(el).hasClass("processed")){
                $(el).addClass("processed")
            }
        })
        
        //Check if our node is a book
        <?php $book = isset($node->book) && !empty($node->book); ?>
        
        //May be deprecated, used for wiki navigation before
        <?php
            /*if($book){
                $paths = array_map(function($el) use ($node) {
                    return "/alfresco/webdav" . $node->path . "/" . $el->name . ".html";
                }, $node->book);
                $string_paths = implode(":", $paths);
            }*/
        ?>
        
        Gofast.Essential.handleDocumentPage("<?php echo $node->type; ?>", "<?php echo $node->status; ?>");
        Gofast.Essential.handleWikiForumInDocumentLayer("<?php echo $node->type; ?>", "<?php echo $node->status; ?>", "<?php echo $book; ?>");
    }
}
</script>
