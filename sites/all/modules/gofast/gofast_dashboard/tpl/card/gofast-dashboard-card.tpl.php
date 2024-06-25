<div class="card card-stretch card-custom ">
    <!--begin::Header-->
    <div class="card-header min-h-30px px-4">
        <h3 class="card-title my-4">
            <span class="card-label font-weight-bolder text-dark-75 "><?php print t($label, array(), array('context' => 'gofast_dashboard')) ?></span>
        </h3>
        <div class="card-toolbar">
            <?php print $toolbar ?>
        </div>
    </div>
    <!--end::Header-->
    <!--begin::Body-->
    <div class="card-body h-auto p-4">
        <div id="<?php echo $block_id ?>">
            <div class="spinner spinner-primary mt-15"></div>
        </div>
    </div>
    <!--end::Body-->
</div>
