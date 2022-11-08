<!-- START gofast-menu-profile.tpl.php -->
<li class="nav-item dropdown no-arrow">
    <a class="nav-link dropdown-toggle" href="#" id="gofast-menu-profile-dropdown" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="<?php print $profile ?>"></i>
    </a>
    <ul class="dropdown-menu multi-level dropdown-menu-right" role="menu" aria-labelledby="gofast-menu-profile-dropdown">
        <?php foreach ($profile_r as $link ) : ?>
        <li class="dropdown-item">
            <a href="<?php print $link['href'] ?>">
                <div class="dropdown-item--label">
                    <p><?php print t($link['label'])?></p>
                </div>
                <i class="fas fa-chevron-right"></i>
            </a>
        </li>
        <?php endforeach; ?>

        <?php print gofast_get_flag_lang_switcher_content(); ?>
    </ul>
</li>
<!-- END gofast-menu-profile.tpl.php -->
