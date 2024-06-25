<?php global $base_url; ?>
<script src="<?php echo $base_url . "/sites/all/modules/gofast/gofast_directory/js/gofastAdminDirectoryTagsTable.js" ?>"></script>

<div id="container-selected-items" style="display:none;">
  <?php echo gofast_directory_tags_actions_get_all_actions(); ?>
</div>
<div class="h-100 w-100">
    <div id="gofastTagsTable" class="datatable datatable-bordered datatable-head-custom h-100" data-columns='<?php echo $columns ?>'></div>
</div>

<script>Gofast.initTagsDirectory();</script>