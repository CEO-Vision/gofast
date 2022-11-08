<ul class="menu-nav">
    <?php foreach ($sections as $section): ?>
         <?php if ($section['label'] && !empty($section['menu'])): ?>
         <li class="menu-section">
             <h4 class="menu-text"><?php echo $section['label'] ?></h4>
             <i class="menu-icon ki ki-bold-more-hor icon-md"></i>
         </li>
        <?php endif; ?>

        <?php foreach ($section['menu'] as $link): ?>
            <?php echo theme('gofast_menu_menu_item', ['link' => $link]);?>
        <?php endforeach ?>
    <?php endforeach ?>
</ul>
