<?php if (!isset($disabled)) : ?>
  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?>" href="<?php print $href; ?>">
    <div class="list-items-icons"><i class="fa fa-book"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-book"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
