<div class="d-flex row flex-wrap font-size-sm">
  <div class="col-12">
    <span class="font-weight-bolder mb-7"><?php echo t('Location/Sharing', array(), array('context' => 'gofast')) ?> :</span>
    <span class="ml-2 mb-7"><a data-toggle="tooltip" data-placement="top" title="<?= t('See authorized members', array(), array('context' => 'gofast')) ?>" class="ctools-use-modal node-info-member-link" href="/gofast/nojs/node/<?php echo $node_infos["node_nid"]; ?>/locations-members"><i class="fa fa-users"></i></a>&nbsp;<?php if($node_infos['has_extranet_location']) { ?><i class="fa fa-warning text-warning" data-toggle="tooltip" data-placement="top" title="<?= t("Shared with external users", array(), array("context" => "gofast:gofast_metadata")) ?>"></i><?php } ?></span>
    <div class="position-relative rounded bg-hover-light">
      <ul class="p-3 mb-0">
        <div class="breadcrumb-gofast breadcrumb-gofast-full"><div class="loader-breadcrumb"></div></div>
      </ul>
    </div>
  </div>
</div>
