<div class="h-100 w-100" >
  <div id="gofastSubscriptionsTable" class="datatable datatable-bordered datatable-head-custom w-100" data-columns='<?php echo $columns ?>' data-data='<?php echo $data ?>'></div>
</div>

<script>
  jQuery(document).ready(function() {
    jQuery("#subscriptionSelectedElementsDelete").on("click", () => jQuery("#gofastSubscriptionsTable").KTDatatable().reload());
  });
</script>