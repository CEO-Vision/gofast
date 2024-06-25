<!--begin::Row-->
<div id="gofastContainer" class="gofast-content--full mainContent fullScreen <?= ((gofast_essential_is_essential() && !gofast_mobile_is_phone()) && ($node->type == "alfresco_item" || $node->type == "webform")) ? 'essential' : ''?> <?= $customGrid ?: '' ?>">
    <?php echo $content ?>
</div>
<script type="text/javascript">
    jQuery(document).ready(()=>{
        if(Gofast._settings.isEssential && !Gofast._settings.isMobileDevice){
            var node = Gofast._settings.gofast.node;
            if(node != undefined && (node.type == "alfresco_item" || node.type == "webform")){
                jQuery(".gofast-content--full.mainContent.fullScreen").addClass("essential")
            }
        }
    })
</script>
<!--end::Row-->
