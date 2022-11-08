<!-- START gofast-navbar-item.tpl.php -->
<li class="nav-item dropdown no-arrow" id="<?php echo $link['id'] ?>">
    <a class="nav-link dropdown-toggle" href="" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
      <i class="<?php echo $link['icon']; ?>"></i>
      <?php echo $link['label']; ?>
    </a>
    <?php if ($link['id_toggle']): ?>
      <?php echo theme('gofast_dropdown_dinamique_menu') ?>
    <?php else: ?>
      <?php echo theme('gofast_dropdown_menu', ['menu' => $link['menu']]) ?>
    <?php endif; ?>
</li>
<!-- START gofast-navbar-item.tpl.php -->
