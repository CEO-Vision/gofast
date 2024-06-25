<?php if(!$ajax){
    //print theme('gofast_dashboard_dashboard_breadcrumb', array("activity" => TRUE));
?>
<?php $user_is_admin = array_intersect([
  'administrator',
  'business administrator',
], $user->roles); ?>

<div class="card card-custom card-stretch p-2">
    <?php if (!gofast_mobile_is_phone()): ?>
        <!--begin::Header-->
    <div class="card-header border-0 py-0 px-5 min-h-auto">
        <div class="card-toolbar w-100 d-flex justify-content-center">
          <?php if ($user_is_admin) : ?>
              <div id="gofast-blog-container"></div>
          <?php endif; ?>
        </div>
    </div>
    <!--end::Header-->
    <?php endif; ?>

    <!--begin::Body-->
    <div id="activity-feed-container" class="card-body pt-0 pb-4 px-4 h-100  position-relative " >

    <?php } ?>
        <div id="activity-feed" class="GofastActivityFeed">
            <div class="GofastActivityFeed__table">
                <table id="activity-feed-table" class="table table-vertical-center table-head-custom " data-ismobile=<?= $is_mobile?>>
                    <tbody>
                    <?php if (!$is_mobile) { ?>
                    <tr>
                        <th></th>
                        <th><?php echo t('Title', array(), array('context' => 'gofast')); ?></th>
                        <th><?php echo t('Spaces', array(), array('context' => 'gofast')); ?></th>
                    </tr>
                    <?php } ?>
                    <?php echo $table_content; ?>
                    </tbody>
                </table>
            </div>
            <?php if(!empty($table_content) || !$ajax){ ?>
            <div class="GofastActivityFeed__loader">
            <div class="spinner spinner-track spinner-primary d-inline-flex gofast-spinner-xxl"></div>
            </div>
            <?php }else{
                print "<center>" . t("The activity feed is empty with these filters", array(), array('context' => "gofast")) . "<center><br />";
            } ?>
            <div class="d-flex justify-content-center align-items-center flex-wrap mb-2 GofastActivityFeed__pagination">
                <div id="activity-feed-pagination" class="d-flex flex-wrap py-2 mr-3">
                </div>
            </div>
        </div>

    </div>
    <span id="activity-feed-page" style="display: none;"><?php echo $page; ?></span>

</div>



<?php if(gofast_essential_is_essential()){ ?>
<style>
    @media (min-width: 768px){
        .col-sm-9 {
            width: 100%;
        }
    }
</style>

<?php } ?>

<script>
    jQuery(document).ready(function(){
        Gofast.removeLoading();
        if($(".GofastActivityFeed__loader").length > 0){
            Gofast.reload_activity_feed();
        }
    });
</script>
