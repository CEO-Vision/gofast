<div class="header-menu-wrapper header-menu-wrapper-left gf-header-menu-wrapper" id="kt_header_menu_wrapper">
    <!--begin::Header Menu-->
    <div id="kt_header_menu" class="header-menu header-menu-mobile header-menu-layout-default gofast-headerMenu">
        <!--begin::Header Nav-->
        <ul class="menu-nav">
            <?php foreach ($menus as $link): ?>
                <?php echo theme('gofast_menu_header_menu_item', ['link' => $link]);?>
            <?php endforeach ?>
        </ul>
        <ul class="menu-nav">
            <?php foreach ($spaces as $link): ?>
                <?php echo theme('gofast_menu_header_menu_item', ['link' => $link]);?>
            <?php endforeach ?>
        </ul>
        <!--end::Header Nav-->
    </div>
    <!--end::Header Menu-->
</div>