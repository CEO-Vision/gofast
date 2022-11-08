<div class="d-flex flex-column-fluid">
  <!--begin::Container-->
  <div class="container">
    <!--begin::Profile Overview-->
    <div class="d-flex flex-row">
      <?php print theme('gofast_user_profile_personal_card', array('account' => $account)); ?>
      <!--begin::Content-->
      <div class="flex-row-fluid ml-lg-8">
        <!--begin::Row-->
        <div class="row">
          <div class="col-lg-12">
            <!--begin::List Widget 1-->
            <?php print theme('gofast_user_profile_espace_card'); ?>
            <!--end::List Widget 1-->
          </div>

        </div>
        <!--end::Row-->
        <!--begin::Row-->
        <div class="row">
          <div class="col-lg-6">
            <?php print theme('gofast_user_profile_team_card'); ?>
          </div>
          <div class="col-lg-6">
            <?php print theme('gofast_user_profile_relation_card'); ?>
          </div>
        </div>
        <!--end::Row-->
      </div>
      <!--end::Content-->
    </div>
    <!--end::Profile Overview-->
  </div>
  <!--end::Container-->
</div>
