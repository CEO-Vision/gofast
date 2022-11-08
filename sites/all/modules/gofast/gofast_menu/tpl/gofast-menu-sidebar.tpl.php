<!-- START gofast-menu-sidebar.tpl.php -->
<nav class="bg-dark sidebar d-flex flex-column h-100">
  <div class="sidebar-brand p-2 m-auto">
    <a class="brand-logo" href="">
      <img class="" src="" alt="GOFAST">
    </a>
  </div>
  <div class="sidebar-content d-flex flex-column justify-content-between pt-2 pb-2">
    <?php foreach ($menus as $menu ) : ?>
    <ul class="nav nav-pills flex-column">
        <?php foreach ($menu as $item ) : ?>
        <li class="nav-item mt-1 mb-1">
            <a class="nav-link d-flex flex-column align-items-center justify-content-center p-1" href="<?php print $item['href'] ?>">
                <i class="<?php print $item['icon'] ?>"></i>
                <span><?php print t($item['label']) ?></span>
            </a>
        </li>
        <?php endforeach; ?>
    </ul>
    <?php endforeach; ?>
  </div>
</nav>
<!-- END gofast-menu-sidebar.tpl.php -->