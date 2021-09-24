<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a class="btn btn-sm ctools-use-modal ctools-modal-center center-block sidebar-items" href="<?php print $href; ?>" title="<?php print $title; ?>">
      <div class="list-items-icons"><i class="fa fa-comment"></i></div>
      <p><?php print $text; ?></p>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-comment"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
