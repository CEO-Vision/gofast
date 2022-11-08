<div class="card card-custom card-stretch gutter-b">
    <!--begin::Header-->
    <div class="card-header border-0 pt-6">
        <h3 class="card-title align-items-start flex-column">
            <span class="card-label font-weight-bolder font-size-h4 text-dark-75">Its Spaces</span>
            <span class="text-muted mt-3 font-weight-bold font-size-lg">49 Acual Spaces</span>
        </h3>
        <div class="card-toolbar">
            <!--begin::Nav-->
            <ul class="nav nav-pills nav-pills-sm flex-nowrap justify-content-end">
                <!--begin::Nav Item-->
                <li class="nav-item ml-1" data-toggle="popover" data-placement="top" data-content="Organisation" data-delay='{ "show": 500, "hide": 100 }'>
                    <a class="nav-link btn btn-icon btn-sm  active" data-toggle="tab" href="#tab_organisation" >
                        <span class="nav-icon">
                            <i class="fas fa-sitemap"></i>
                        </span>

                    </a>
                </li>
                <!--end::Nav Item-->
                <!--begin::Nav Item-->
                <li class="nav-item ml-1" data-toggle="popover" data-placement="top" data-content="Groups" data-delay='{ "show": 500, "hide": 100 }'>
                    <a class="nav-link btn btn-icon btn-sm  " data-toggle="tab" href="#tab_group">
                        <span class="nav-icon">
                            <i class="fas fa-users"></i>
                        </span>

                    </a>
                </li>
                <!--end::Nav Item-->
                <!--begin::Nav Item-->
                <li class="nav-item ml-1" data-toggle="popover" data-placement="top" data-content="Public" data-delay='{ "show": 500, "hide": 100 }'>
                    <a class="nav-link btn btn-icon btn-sm " data-toggle="tab" href="#tab_public">
                        <span class="nav-icon">
                            <i class="fas fa-share-alt"></i>
                        </span>

                    </a>
                </li>
                <!--end::Nav Item-->
                <!--begin::Nav Item-->
                <li class="nav-item ml-1" data-toggle="popover" data-placement="top" data-content="Extranet" data-delay='{ "show": 500, "hide": 100 }'>
                    <a class="nav-link btn btn-icon btn-sm " data-toggle="tab" href="#tab_extranet">
                        <span class="nav-icon">
                            <i class="fas fa-globe-americas"></i>
                        </span>
                    </a>
                </li>
                <!--end::Nav Item-->

            </ul>
            <!--end::Nav-->
        </div>
    </div>
    <!--end::Header-->
    <!--begin::Body-->
    <div class="card-body pt-2">
        <!--begin::Tab Content-->
        <div class="tab-content mt-5" id="myTabMixed2" >
            <?php print theme('gofast_user_profile_espace_panel', array('espace' => 'group', 'isActive' => '')); ?>
            <?php print theme('gofast_user_profile_espace_panel', array('espace' => 'organisation', 'isActive' => '')); ?>
            <?php print theme('gofast_user_profile_espace_panel', array('espace' => 'public', 'isActive' => '')); ?>
            <?php print theme('gofast_user_profile_espace_panel', array('espace' => 'extranet', 'isActive' => '')); ?>
        </div>
        <!--end::Tab Content-->
    </div>
    <!--end::Body-->
</div>
