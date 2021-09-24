<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a href="<?php print $href; ?>" class="<?php print $link_class; ?> btn btn-sm center-block sidebar-items">
      <div class="list-items-icons"><i class="fa fa-archive"></i></div>
      <p><?php print $text; ?></p>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-archive"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
