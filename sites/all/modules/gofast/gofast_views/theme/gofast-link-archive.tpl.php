<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a class="btn btn-sm ctools-use-modal on-node-lock-disable center-block sidebar-items <?php print $link_class ?>" href="<?php print $href; ?>">
      <div class="list-items-icons"><i class="fa fa-archive"></i></div>
      <?php print $text; ?>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-archive"></i></div>
      <?php print $text; ?>
  </a>
<?php endif; ?>
