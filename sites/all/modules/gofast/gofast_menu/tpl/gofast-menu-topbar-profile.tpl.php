<li class="menu-item menu-item-submenu menu-item-rel m-auto min-w-40px p-0" id="gf-profile-menu" data-menu-toggle="hover" aria-haspopup="true">
  <!--begin::Toggle-->
  <?= theme("user_picture", ["account" => $user, "style" => "thumbnail", "popup" => FALSE]) ?>
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