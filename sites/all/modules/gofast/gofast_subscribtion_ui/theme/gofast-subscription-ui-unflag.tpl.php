<a href="<?php echo $link; ?>" class="btn btn-link-primary btn-icon btn-lg mx-2 no-footer flag flag-action flag-link-toggle">
  <i class="fa fa-trash text-danger"></i>
</a>
<script>
  jQuery(document).ready(function() {
    jQuery("#gofastSubscriptionsTable .flag").on("click", () => jQuery("#gofastSubscriptionsTable").KTDatatable().reload());
  });
</script>