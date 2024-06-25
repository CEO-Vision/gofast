<div class="card gutter-b card-custom mt-4">
    <div class="card-header d-flex align-items-center justify-content-between">
        <div class="h3 mb-2"><?php print theme('gofast_node_icon_format', array('node' => node_load($nid_source), 'size' => 2)) . node_load($nid_source)->title ?></div>
        <span class="h3"><?php print t("Version comparator : Version", array(), array("context" => "gofast:gofast_pdf_compare")) . " " . $version_source . " " . t("to", array(), array("context" => "gofast:gofast_pdf_compare"))  . " " . $version_dest; ?></span>
    </div>
    <?= theme("gofast_pdf_compare_loader") ?>
    <div class="card-footer">
        <button class="btn btn-default btn-sm pdf_version_back"><i class="fa fa-arrow-left"></i> <?php print t('Back to the document', array(), array('context' => 'gofast:gofast_pdf_compare')); ?></button>
    </div>
</div>


<script>
    //Check differences
    jQuery.get("/pdf_compare_ajax/<?php print $nid_source; ?>/<?php print $version_source; ?>/<?php print $version_dest; ?>", function(r) {
        jQuery("#pdf_compare_content").html(r);
    });
    jQuery('.pdf_version_back').click(function() {
        window.location = "/node/<?php print $nid_source ?>";
    });
</script>