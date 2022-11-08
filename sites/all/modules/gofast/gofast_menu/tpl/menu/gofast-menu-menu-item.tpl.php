<?php if (!empty($link['menu']) || $link['has_submenu'] == TRUE ): ?>
    <li class="menu-item menu-item-submenu <?php echo $link['class'] ?>" data-menu-toggle="hover" aria-haspopup="true" id="<?php echo $link['id'] ?>" <?php if(isset($link['attrs']['gid'])):?> data-gid="<?php echo $link['attrs']['gid'] ?>" <?php endif; ?>>
        <a
            <?php if(isset($link['href'])): ?>
                href="<?php echo $link['href'] ?>"
            <?php endif ?>
            class="menu-link menu-toggle mega-menu-item <?php echo $link['linkClass'] ?>">
            <?php if(isset($link['icon'])): ?>
                <i class="menu-icon <?php echo $link['icon'] ?>"></i>
            <?php else: ?>
                <i class="menu-bullet menu-bullet-dot"><span></span></i>
            <?php endif ?>
            <span class="menu-text"><?php echo $link['label'] ?></span>
            <i class="menu-arrow"></i>
        </a>
        <?php if (!empty($link['menu']) ): ?>
        <div class="menu-submenu menu-submenu-classic <?php echo $link['subclass'] ?>" >
            <ul class="menu-subnav h-100">
                <?php foreach ($link['menu'] as $link): ?>
                    <?php echo theme('gofast_menu_menu_item', ['link' => $link]);?>
                <?php endforeach ?>
            </ul>
        </div>
        <?php endif;?>
    </li>
<?php else: ?>
    <li class="menu-item <?php echo $link['class']; ?>" aria-haspopup="true" id="<?php echo $link['id'] ?>" <?php if(isset($link['attrs']['gid'])):?> data-gid="<?php echo $link['attrs']['gid'] ?>" <?php endif; ?>>
        <a href="<?php echo $link['href'] ?>" target="<?php echo $link['target'] ?>" class="menu-link <?php echo $link['linkClass'] ?>">
            <?php if(isset($link['icon'])): ?>
                <?php if(!empty($link['icon'])): ?>
                    <i class="menu-icon <?php echo $link['icon'] ?>"></i>
                <?php elseif(isset($link['svg']) && !empty($link['svg'])): ?>
                    <div class="menu-icon">
                    <img src="<?php print $link['svg'] ?>" alt="" class="menu-svg-img">
                    </div>
                <?php endif; ?>
            <?php else: ?>
                <i class="menu-bullet menu-bullet-dot"><span></span></i>
            <?php endif ?>
            <span class="menu-text"><?php echo $link['label'] ?></span>
        </a>
    </li>
<?php endif; ?>
<script>
jQuery(document).ready(function() {
    if(document.URL.includes(Drupal.settings.mobile_prefix_url)) {
        jQuery("#kt_aside_menu .menu-item a").click(function () { 
            jQuery("#kt_aside").removeClass('aside-on');
        });
    }
});
</script>
