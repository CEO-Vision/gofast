<?php global $base_url; ?>
<script src="<?php echo $base_url . "/sites/all/modules/gofast/gofast_directory/js/gofastAdminDirectoryCategoriesTable.js" ?>"></script>

<div id="container-selected-items" style="display:none;">
  <?php echo gofast_directory_categories_actions_get_all_actions(); ?>
</div>
<div class="w-100" style="height: 80%">
    <div id="gofastCategoriesTable" class="datatable datatable-bordered datatable-head-custom h-100" data-columns='<?php echo $columns ?>'></div>
</div>

<script>Gofast.initCategoriesDirectory();</script>