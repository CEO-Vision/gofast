
<li class="menu-item p-2 overflow-hidden w-275px <?php echo $class; ?>" >
    <ul class="menu-inner h-100 w-100 scroll scroll-pull" data-scroll="true" data-wheel-propagation="true">
        <?php foreach ($links as $link): ?>
          <?php echo theme('gofast_menu_menu_item', ['link' => $link]); ?>
        <?php endforeach ?>
    </ul>
</li>





