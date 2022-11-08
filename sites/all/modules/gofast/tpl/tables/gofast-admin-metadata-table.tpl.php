<div class="card card-custom card-stretch mt-4" style="height: 97%;">
    <div id="container-selected-items" style="display:none;">
      <?php echo gofast_metatags_bulk_actions_get_all_actions(); ?>
    </div>
    <div class="card-body p-5 d-flex flex-column h-100">
        <div class="h-100 w-100" >
            <div id="gofastMetatagsTable" class="datatable datatable-bordered datatable-head-custom h-100" data-columns='<?php echo $columns ?>'></div>
        </div>
    </div>
</div>

<style>
    thead [data-field="links"] > span:after {
        visibility: hidden;
</style>