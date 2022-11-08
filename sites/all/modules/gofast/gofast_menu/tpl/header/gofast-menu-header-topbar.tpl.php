<div class="topbar w-100 gofast-topbar">
    <div class="w-100 justify-content-between header-menu header-menu-layout-default " id="gf-topbar-menu">
        <ul class="menu-nav">
            <!--begin::Logo-->
            <li class="menu-item menu-item-submenu">
                <a href="/<?php if(!gofast_mobile_is_mobile_domain()){ variable_get('site_frontpage', 'activity'); }else{ echo 'home_page_navigation#navBrowser'; } ?>" class="brand-logo">
                    <img alt="Logo" src="<?= theme_get_setting('logo') ?? '/sites/all/modules/gofast/img/logo_enterprise.png' ?>" class="h-30px" />
                </a>
            </li>
            <!--end::Logo-->
            <?php foreach ($rightSection as $link) : ?>
                <?php echo theme('gofast_menu_topbar_menu_item', ['link' => $link]); ?>
            <?php endforeach ?>
        </ul>
        <div class="d-flex align-items-center w-100 p-4">
            <div class="typeahead w-100">
                <?php echo drupal_render(drupal_get_form('search_block_form')); ?>
            </div>
        </div>
        <ul class="menu-nav">
            <li class="menu-item menu-item-submenu menu-item-rel" data-menu-toggle="hover" aria-haspopup="true">
                <a href="/modal/nojs/cart" class="btn btn-icon btn-clean btn-lg ctools-use-modal">
                    <i class="fas fa-shopping-basket"></i>
                </a>
            </li>
            <?php echo $language; ?>
            <?php foreach ($leftSection as $link) : ?>
                <?php echo theme('gofast_menu_topbar_menu_item', ['link' => $link]); ?>
            <?php endforeach ?>
            <!--begin::User-->
            <?php echo theme('gofast_menu_topbar_profile'); ?>
            <!--end::User-->
        </ul>
    </div>
</div>
