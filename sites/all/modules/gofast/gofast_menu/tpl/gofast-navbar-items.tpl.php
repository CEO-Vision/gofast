<?php foreach ($nav_items as $nav_item) : ?>
  <?php print theme('gofast_navbar_item', ['icon' => $nav_item['icon']]); ?>
<?php endforeach; ?>
