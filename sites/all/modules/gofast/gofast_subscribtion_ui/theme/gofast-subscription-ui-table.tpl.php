<div class="h-100 w-100" >
  <div id="gofastSubscriptionsTable" class="datatable datatable-bordered datatable-head-custom" data-columns='<?php echo $columns ?>' data-data='<?php echo $data ?>'></div>
</div>

<div id="subscriptionSelectedElements" class="modal-footer-element">
  <span>
    <span id="subscriptionSelectedElementsCount">0</span> <?php echo t("selected elements", array(), array('context' => 'gofast:gofast_subscription_ui')); ?>
  </span>
  
  <div id="subscriptionSelectedElementsActions" class="d-none">
    <span class="subscriptionSelectedElementsAction">
    <?php echo html_entity_decode(drupal_render(drupal_get_form('gofast_subscription_ui_frequency_placeholder_form'))); ?>
    </span>
    
    <span class="subscriptionSelectedElementsAction">
      <a id="subscriptionSelectedElementsDelete" href='#' class="btn btn-link-primary btn-icon btn-lg mx-2 no-footer">
        <i class="fa fa-trash text-danger"></i>
      </a>
    </span>
  </div>
</div>
<script>
  jQuery(document).ready(function() {
    jQuery("#subscriptionSelectedElementsDelete").on("click", () => jQuery("#gofastSubscriptionsTable").KTDatatable().reload());
  });
</script>