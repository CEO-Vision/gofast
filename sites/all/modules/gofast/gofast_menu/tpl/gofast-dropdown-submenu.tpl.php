<li class="dropdown-submenu">
    <a class="dropdown-item dropdown-toggle" href="<?php echo $link['href'] ?>"><i class="<?php echo $link['icon']; ?>"></i><?php echo $link['label'] ?><i class="fas fa-chevron-right"></i></a>
    <?php echo theme('gofast_dropdown_menu', ['menu' => $link['menu']]) ?>
</li>