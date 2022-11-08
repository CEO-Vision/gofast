<ul class="dropdown-menu">
    <?php foreach ($menu as $link): ?>
      <?php if (!$link['menu']): ?>
        <li><a class="dropdown-item" href="<?php echo $link['href'] ?>"><i class="<?php echo $link['icon']; ?>"></i><?php echo $link['label'] ?></a></li>
      <?php else: ?>
        <?php echo theme('gofast_dropdown_submenu', ['link' => $link]) ?>
      <?php endif; ?>
    <?php endforeach ?>
</ul>