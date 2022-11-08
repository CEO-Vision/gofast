<!-- START gofast-menu-create.tpl.php -->
<?php echo theme('gofast_navbar_item', ['icon' => 'fa fa-plus']); ?>

<!-- <li class="nav-item dropdown no-arrow">
    <a class="nav-link dropdown-toggle" href="#" id="gofast-menu-create-dropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="fas fa-plus"></i>
    </a>
    <ul class="dropdown-menu multi-level" role="menu" aria-labelledby="gofast-menu-create-dropdown">
        <?php foreach ($links as $link) : ?>
            <li class="dropdown-item <?php if ($link['submenu']) {
                                            print 'dropdown-submenu';
                                        } ?>">
                <a href="<?php print $link['href'] ?>">
                    <i class="<?php print $link['icon'] ?>"></i>
                    <p><?php print t($link['label']) ?></p>
                    <i class="fas fa-chevron-right"></i>
                </a>
                <?php if ($link['submenu']) : ?>
                    <ul class="dropdown-menu multi-level" role="menu" aria-labelledby="dropdownMenu">
                        <?php foreach ($link['submenu'] as $link) : ?>
                            <li class="dropdown-item">
                                <a href="<?php print $link['href'] ?>">
                                    <i class="<?php print $link['icon'] ?>"></i>
                                    <p><?php print t($link['label']) ?></p>
                                    <i class="fas fa-chevron-right"></i>
                                </a>
                            </li>
                        <?php endforeach; ?>
                    </ul>
                <?php endif; ?>
            </li>
        <?php endforeach; ?>
    </ul>
</li> -->
<!-- END gofast-menu-create.tpl.php -->
