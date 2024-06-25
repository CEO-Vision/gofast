<?php 
$private_space = gofast_og_get_user_private_space($user, false);

?>
<div class="w-100 gofast-topbar<?= gofast_essential_is_essential() ? '' : ' topbar' ?>">
    <div class="w-100 justify-content-between header-menu header-menu-layout-default " id="gf-topbar-menu">
        <ul class="menu-nav">
            <!--begin::Logo-->
            <li class="menu-item menu-item-submenu">
                <a id="topbarNavLogoButton" <?= gofast_essential_is_essential() ? "" :  "href='/".variable_get('site_frontpage', 'activity')."'"?> class="brand-logo <?= gofast_essential_is_essential() ? 'btn' : '' ?>">
                    <img alt="Logo" src="<?= theme_get_setting('logo') ?? '/sites/all/modules/gofast/img/logo_enterprise.png' ?>" class="h-30px" />
                </a>
            </li>
            <li class="menu-item menu-item-submenu menu-item-rel" data-menu-toggle="hover" aria-haspopup="true" id="gofastMenuTopbarCreateMenuItem">
                <button class="btn btn-icon btn-clean btn-dropdown btn-lg">
                    <i class="fas fa-plus"></i>
                </button>
                <div class="menu-submenu menu-submenu-classic menu-submenu-left" data-hor-direction="menu-submenu-left">
                    <ul class="menu-subnav">
                        <h4 class="text-dark font-weight-bold" style="padding-left: 1rem">
                            <?= t('New', array(), array("context" => "gofast")) ?>
                        </h4>
                        <li class="menu-item" aria-haspopup="true" id="">
                            <a href="/node/add/conference" target="" class="menu-link">
                                <i class="menu-icon fas fa-video"></i>
                                <span class="menu-text"><?= t('Conference') ?></span>
                            </a>
                        </li>
                        <li class="menu-item" aria-haspopup="true" id="">
                            <a href="/node/add/alfresco-item" target="" class="menu-link">
                                <i class="menu-icon far fa-file"></i>
                                <span class="menu-text"><?= t('File, Document') ?></span>
                            </a>
                        </li>
                        <?php if (gofast_og_is_user_space_administrator()) : ?>
                        <li class="menu-item menu-item-submenu" data-menu-toggle="hover" aria-haspopup="true" id="">
                            <a href="" class="menu-link menu-toggle mega-menu-item">
                                <i class="menu-icon fas fa-folder-plus"></i>
                                <span class="menu-text"><?= t('Space') ?></span>
                                <i class="menu-arrow"></i>
                            </a>
                            <div class="menu-submenu menu-submenu-classic menu-submenu-right">
                                <ul class="menu-subnav h-100">
                                    <li class="menu-item" aria-haspopup="true" id="">
                                        <a href="/node/add/group" target="" class="menu-link">
                                            <i class="menu-icon fas fa-users n-color"></i>
                                            <span class="menu-text"><?= t('Group') ?></span>
                                        </a>
                                    </li>
                                    <li class="menu-item" aria-haspopup="true" id="">
                                        <a href="/node/add/organisation" target="" class="menu-link">
                                            <i class="menu-icon fas fa-sitemap n-color"></i>
                                            <span class="menu-text"><?= t('Organisation') ?></span>
                                        </a>
                                    </li>
                                    <li class="menu-item" aria-haspopup="true" id="">
                                        <a href="/node/add/public" target="" class="menu-link">
                                            <i class="menu-icon fas fa-share-alt n-color"></i>
                                            <span class="menu-text"><?= t('Public') ?></span>
                                        </a>
                                    </li>
                                    <li class="menu-item" aria-haspopup="true" id="">
                                        <a href="/node/add/extranet" target="" class="menu-link">
                                            <i class="menu-icon fas fa-globe-europe n-color"></i>
                                            <span class="menu-text"><?= t('Extranet') ?></span>
                                        </a>
                                    </li>
                                </ul>
                            </div>
                        </li>
                        <?php endif; ?>
                        <?php if (gofast_user_is_business_admin()): ?>
                            <li class="menu-item" aria-haspopup="true" id="">
                                <a href="/modal/nojs/contact/add" target="" class="menu-link ctools-use-modal">
                                    <i class="menu-icon fas fa-address-book"></i>
                                    <span class="menu-text"><?= t('Contact') ?></span>
                                </a>
                            </li>
                            <li class="menu-item" aria-haspopup="true" id="">
                                <a href="/admin/people/create" target="" class="menu-link">
                                    <i class="menu-icon fas fa-user-plus"></i>
                                    <span class="menu-text"><?= t('User') ?></span>
                                </a>
                            </li>
                            <li class="menu-item" aria-haspopup="true" id="">
                                <a href="/userlist/add" target="" class="menu-link">
                                    <i class="menu-icon fas fa-user-friends"></i>
                                    <span class="menu-text"><?= t("Userlist", array(), array("context" => "gofast")) ?></span>
                                </a>
                            </li>
                        <?php endif; ?>
                    </ul>
                </div>
            </li>
            <li class="menu-item menu-item-submenu" data-toggle="tooltip" data-title="<?php print t('Dashboard') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
                <a id="topbarNavDashboardButton" class="btn btn-icon btn-clean btn-dropdown btn-lg">
                    <i class="menu-icon fas fa-tachometer-alt"></i>
                </a>
            </li>
            <li class="menu-item menu-item-submenu" data-toggle="tooltip" data-title="<?php print t('Activity Feed') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
                <a id="topbarNavActivityFeedButton" class="btn btn-icon btn-clean btn-dropdown btn-lg">
                    <i class="menu-icon fas fa-list-alt"></i>
                </a>
            </li>
            <li class="menu-item menu-item-submenu" data-toggle="tooltip" data-title="<?php print t('File Browser') ?>" data-animation="true" data-trigger="hover" data-placement="bottom" data-boundary="window">
                <a id="topbarNavFileBrowserButton" class="btn btn-icon btn-clean btn-dropdown btn-lg">
                    <img src="/sites/all/themes/bootstrap-keen/img/collaborative_space.svg" alt="" class="menu-svg-img">
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

<script type="text/javascript">
    jQuery(document).ready(()=>{
        // Prevent About menu items to trigger the parent element onclick event
        jQuery("#gofastAboutMenu .menu-item").on("click", (e) => {
            e.stopPropagation()
        })
    })
</script>