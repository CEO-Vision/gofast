<?php $detect = new Mobile_Detect(); ?>
<?php if (($detect->isMobile() || $detect->isTablet() || gofast_essential_is_essential()) && $link['desktop_only']) : ?>
<?php else : ?>
  <?php if ($link['menu']) : ?>
    <?php if ($link['isSpace']) : ?>
      <li class="menu-item menu-item-submenu <?php echo $link['class'] ?>" data-menu-toggle="hover" aria-haspopup="true" id="<?php echo $link['id'] ?>">
        <a href="<?php echo $link['href'] ?>" class="menu-link menu-toggle d-flex d-lg-none">
          <i class="menu-icon <?php echo $link['icon'] ?> "></i>
          <span class="menu-text"><?php echo $link['label'] ?></span>
          <i class="menu-arrow"></i>
        </a>
        <a href="<?php echo $link['href'] ?>" class="btn btn-icon btn-clean btn-dropdown btn-lg d-none d-lg-flex">
          <?php if (isset($link['icon']) && !empty($link['icon'])) : ?>
            <i class="<?php echo $link['icon'] ?>"></i>
          <?php elseif (!empty($link['svg'])) : ?>
            <img class="menu-svg-img" src="<?php print $link['svg'] ?>" alt="">
          <?php endif; ?>
        </a>

        <?php if (strpos($link['subclass'], 'menu-submenu-fixed') > 0) : ?>

          <div class="menu-submenu <?php echo $link['subclass'] ?>">
            <div class="menu-subnav h-100">
              <h4 class="text-dark font-weight-bold" style="padding-right: 1rem;padding-top: 20px;padding-left: 1rem;"><?php print $link['title']; ?></h4>
              <ul class="menu-content h-100">
                <?php echo theme('gofast_menu_menu_content', ['links' => $link['menu']]); ?>
              </ul>
            </div>
          </div>

        <?php else : ?>

          <div class="menu-submenu menu-submenu-classic <?php echo $link['subclass'] ?>">
            <ul class="menu-subnav">
              <h4 class="text-dark font-weight-bold"><?php print $link['title']; ?></h4>
              <?php foreach ($link['menu'] as $link) : ?>
                <?php echo theme('gofast_menu_menu_item', ['link' => $link]); ?>
              <?php endforeach ?>
            </ul>
          </div>
        <?php endif; ?>
      </li>
    <?php else : ?>
      <li class="menu-item menu-item-submenu menu-item-rel <?php echo $link['class'] ?>" data-menu-toggle="hover" aria-haspopup="true" id="<?php echo $link['id'] ?>" <?= isset($link['onClick']) ? "onClick=\"" . $link['onClick'] . "\"" : "" ?>>
        <a <?php !isset($link['href']) || strlen($link['href']) == 0 ? '' : 'href="' . $link['href'] . '"' ?> class="btn btn-icon btn-clean btn-dropdown btn-lg">
          <?php if (isset($link['icon']) && !empty($link['icon'])) : ?>
            <i class="<?php echo $link['icon'] ?>"></i>
          <?php elseif (!empty($link['svg'])) : ?>
            <img src="<?php print $link['svg'] ?>" alt="">
          <?php endif; ?>
        </a>
        <div class="menu-submenu menu-submenu-classic <?php echo $link['subclass'] ?>">
          <ul class="menu-subnav">
            <h4 class="text-dark font-weight-bold" style="padding-left:1rem;"><?php print $link['title']; ?></h4>
            <?php foreach ($link['menu'] as $link) : ?>
              <?php echo theme('gofast_menu_menu_item', ['link' => $link]); ?>
            <?php endforeach ?>
          </ul>
        </div>

      </li>
    <?php endif; ?>
  <?php else : ?>
    <li class="menu-item menu-item-submenu menu-item-rel gofast-block" aria-expanded="false" data-menu-toggle="hover" aria-haspopup="true" id="<?php print $link['id']; ?>" data-pinned="false" data-unread="<?php print $link['count']; ?>">
      <?php if(!empty($link["href"])) : ?>
      <a href="<?php echo $link["href"] ?? '#'?>" role="button" class="btn btn-icon btn-clean btn-dropdown btn-lg">
      <?php else : ?>
      <a role="button" class="btn btn-icon btn-clean btn-dropdown btn-lg">
      <?php endif; ?>
        <?php if (isset($link['icon']) && !empty($link['icon'])) : ?>
          <i class="<?php echo $link['icon'] ?>"></i>
        <?php elseif (!empty($link['svg'])) : ?>
          <img src="<?php print $link['svg'] ?>" alt="">
        <?php endif; ?>
        <span class="label label-sm font-weight-bold label-danger position-absolute unread_notifications unread_count d-none" style="top: 7px; right: 7px;"><?php print $link['count']; ?></span>
      </a>
      <?php //print_r($link); 
      ?>
      <div class="menu-submenu menu-submenu-classic ">
        <h4 class="text-dark font-weight-bold"><?php print $link['title']; ?></h4>
        <div class="gofast-block-outer-new h-100">
          <div class="pointeur"></div>
          <div class="gofast-block-inner h-100">
            <!-- Block inner -->
            <div class="text-center">
              <div class="loader-blog"></div>
            </div>
          </div>
        </div>

      </div>
    </li>
  <?php endif; ?>
<?php endif; ?>
