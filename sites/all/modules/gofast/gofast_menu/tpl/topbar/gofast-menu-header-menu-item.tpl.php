<?php if (!empty($link['menu'])): ?>
  <li class="menu-item menu-item-submenu <?php echo $link['class'] ?>" data-menu-toggle="hover" aria-haspopup="true" id="<?php echo $link['id'] ?>">
      <a href="<?php echo $link['href'] ?>" class="menu-link menu-toggle d-flex d-lg-none">
          <i class="menu-icon <?php echo $link['icon'] ?> "></i>
          <span class="menu-text"><?php echo $link['label'] ?></span>
          <i class="menu-arrow"></i>
      </a>
      <a href="<?php echo $link['href'] ?>" class="btn btn-icon btn-clean btn-dropdown btn-lg d-none d-lg-flex">
          <i class="<?php echo $link['icon'] ?>"></i>
      </a>

      <?php if (strpos($link['subclass'], 'menu-submenu-fixed') > 0): ?>
      
        <div class="menu-submenu <?php echo $link['subclass'] ?>" >
            <div class="menu-subnav h-100">
                <ul class="menu-content h-100">
                  <?php echo theme('gofast_menu_menu_content', ['links' => $link['menu']]); ?>
                </ul>
            </div>
        </div>

      <?php else : ?>
      
        <div class="menu-submenu menu-submenu-classic <?php echo $link['subclass'] ?>">
            <ul class="menu-subnav">
                <?php foreach ($link['menu'] as $link): ?>
                  <?php echo theme('gofast_menu_menu_item', ['link' => $link]); ?>
                <?php endforeach ?>
            </ul>
        </div>
      <?php endif; ?>


  </li>
<?php else: ?>
  <li class="menu-item" aria-haspopup="true">
      <a href="<?php echo $link['href'] ?>" class="menu-link">
          <i class="menu-icon <?php echo $link['icon'] ?>"></i>
          <span class="menu-text"><?php echo $link['label'] ?></span>
      </a>
  </li>
<?php endif; ?>