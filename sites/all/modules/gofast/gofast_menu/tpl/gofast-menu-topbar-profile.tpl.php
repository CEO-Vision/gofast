<li class="menu-item menu-item-submenu menu-item-rel" data-menu-toggle="hover" aria-haspopup="true">
  <!--begin::Toggle-->
  <a class="menu-link menu-toggle menu-profile topbar-item ml-4" href="/user">
    <div class="btn btn-icon btn-light-primary h-40px w-40px p-0" id="kt_quick_user_toggle">
      <img src="<?= $user->picture ? file_create_url(file_load($user->picture)->uri) : "/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png" ?>" class="h-100 align-self-end symbol" alt="" />
    </div>
  </a>
  <!--end::Toggle-->
  <!--begin::Dropdown-->
  <div class="menu-submenu menu-submenu-classic menu-submenu-right max-w-200px" data-hor-direction="menu-submenu-right">
    <!--begin::Nav-->
    <ul class="menu-subnav navi navi-hover navi-active">
      <?php foreach ($links as $link) : ?>
        <li class="navi-item">
          <a class="navi-link <?php echo $link['class'] ?>" href="<?php echo $link['href'] ?>">
            <span class="navi-icon"><i class="<?php echo $link['icon'] ?>"></i></span>
            <span class="navi-text"><?php echo $link['label'] ?></span>
          </a>
        </li>
      <?php endforeach ?>
    </ul>
    <!--end::Nav-->
  </div>
  <!--end::Dropdown-->
</li>