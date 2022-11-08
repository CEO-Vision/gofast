<li class="menu-item menu-item-submenu menu-item-rel <?php echo $link['class'] ?>" data-menu-toggle="hover" aria-haspopup="true">
    <a href="/user" class="h-40px w-40px p-0 symbol symbol-40 menu-profile">
        <img src="<?= $user->picture ? file_create_url(file_load($user->picture)->uri) : "/sites/all/themes/bootstrap-keen/keenv2/assets/media/users/blank.png" ?>" class="h-100 align-self-end" alt="" />
    </a>
    <div class="menu-submenu menu-submenu-classic <?php echo $link['subclass'] ?>">
        <ul class="menu-subnav">
            <?php foreach ($links as $link) : ?>
                <?php echo theme('gofast_menu_menu_item', ['link' => $link]); ?>
            <?php endforeach ?>
        </ul>
    </div>
</li>
