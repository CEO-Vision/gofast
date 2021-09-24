<div class="panel panel-default">
  <div class="panel-heading">
      <div style="margin-bottom: 5px;"><?php print theme('gofast_node_icon_format', array('node' => node_load($nid_source))) . node_load($nid_source)->title ?></div>
      <span><?php print t("Version comparator : Version", array(), array("context" => "gofast:gofast_pdf_compare")) . " " . $version_source . " " . t("to", array(), array("context" => "gofast:gofast_pdf_compare"))  . " " . $version_dest; ?></span>
  </div>
  <div id="pdf_compare_content" class="panel-body">
      <div class="loader-comparator"></div>
      <p style="text-align: center;font-size: 1.5em"><?php print t("Looking for differences...", array(), array("context" => "gofast:gofast_pdf_compare")); ?></p>
  </div>
</div>

<button class="btn btn-default btn-sm pdf_version_back"><i class="fa fa-arrow-left"></i> <?php print t('Back to the document',array(),array('context'=>'gofast:gofast_pdf_compare'));?></button>

<script>

//Check differences
jQuery.get("/pdf_compare_ajax/<?php print $nid_source; ?>/<?php print $version_source; ?>/<?php print $version_dest; ?>", function(r){
    jQuery("#pdf_compare_content").html(r);
});
jQuery('.pdf_version_back').click(function(){
   window.location = "/node/<?php print $nid_source?>"; 
});

</script>