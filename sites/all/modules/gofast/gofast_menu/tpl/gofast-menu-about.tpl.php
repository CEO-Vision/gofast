<!-- START gofast-menu-about.tpl.php -->
<li class="nav-item dropdown no-arrow">
    <a class="nav-link dropdown-toggle" href="#" id="gofast-menu-about-dropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="<?php print $main_icon ?>"></i>
    </a>
    <ul class="dropdown-menu dropdown-menu-right" role="menu" aria-labelledby="gofast-menu-about-dropdown">
        <?php foreach ($links as $link ) : ?>
        <li class="dropdown-item">
            <a href="<?php print $link['href'] ?>">
                <div class="dropdown-item--label">
                    <i class="<?php print $link['icon'] ?>"></i>
                    <p><?php print t($link['label'])?></p>
                </div>
                <i class="fas fa-chevron-right d-none"></i>
            </a>
        </li>
        <?php endforeach; ?>
    </ul>  
</li>
<!-- END gofast-menu-about.tpl.php -->

