<ul class="menu-nav">
    <?php foreach ($menus as $menu): ?>
         <?php if ($menu['label']): ?>
         <li class="menu-section">
             <h4 class="menu-text"><?php echo $menu['label'] ?></h4>
             <i class="menu-icon ki ki-bold-more-hor icon-md"></i>
         </li>
        <?php endif; ?>

        <?php foreach ($menu['menu'] as $link): ?>
        <li class="menu-item" aria-haspopup="true">
            <a href="<?php echo $link['href'] ?>" class="menu-link">
                <i class="menu-icon <?php echo $link['icon'] ?>"></i>
                <span class="menu-text"><?php echo $link['label'] ?></span>
            </a>
        </li>
        <?php endforeach ?>
    <?php endforeach ?>
</ul>