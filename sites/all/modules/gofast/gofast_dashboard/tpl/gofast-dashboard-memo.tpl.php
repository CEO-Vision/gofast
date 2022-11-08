<?php if(FALSE): ?>
<div class="col-xxl-4 col-lg-6">
   <div class="card card-custom card-stretch gutter-b">
        <div class="card-header">
            <div class="card-title">
                <h3 class="card-label">
                    <span class="font-weight-bolder font-size-h4 text-dark-75">
                        <?php print t('Memos', array(), array('context' => 'gofast_dashboard')) ?>
                    </span>
                </h3>
            </div>
        </div>
        <div class="card-body dashboard-memo-placeholder">
            <div class="loader-dashboard-block"></div>
        </div>
    </div>
</div>



<?php endif ?>




<div class="card card-stretch gutter-b card-custom ">
    <!--begin::Header-->
    <div class="card-header min-h-30px px-4">
        <h3 class="card-title my-4">
            <span class="card-label font-weight-bolder text-dark-75 "><?php print t('Memos', array(), array('context' => 'gofast_dashboard')) ?></span>
        </h3>
    </div>
    <!--end::Header-->
    <!--begin::Body-->
    <div class="card-body h-100 p-4 d-flex flex-column ">
        <div class="dashboard-memo-placeholder">
            <div class="loader-dashboard-block"></div>
        </div>
    </div>
    <!--end::Body-->
</div>

<script type='text/javascript'>
    jQuery(document).ready(function(){
        jQuery.post(location.origin+"/dashboard/ajax/memo", function(data){
            jQuery(".dashboard-memo-placeholder").find(".loader-dashboard-block").remove();
            jQuery(".dashboard-memo-placeholder").prepend(data);
            jQuery('#table_memo > tbody').pager({pagerSelector : '#memo_pager', perPage: 4, numPageToDisplay : 5});
        });
    });
    
</script>
