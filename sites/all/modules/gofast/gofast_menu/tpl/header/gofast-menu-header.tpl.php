<div id="kt_header" class="header header-fixed h-55px <?= (gofast_essential_is_essential() && !gofast_mobile_is_phone()) ? 'essentialHeader' : '' ?>">
    <!--begin::Container-->
    <div class="container-fluid d-flex align-items-stretch justify-content-between">
        <!--begin::Topbar-->
        <?php 
        if(gofast_essential_is_essential()){
            echo theme('essential_header_topbar');
        } else {

            echo theme('gofast_menu_header_topbar');
        }
            ?>
        <!--end::Topbar-->
    </div>
    <!--end::Container-->
</div>
