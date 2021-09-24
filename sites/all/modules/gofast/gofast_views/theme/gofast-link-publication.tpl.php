<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a class="btn btn-sm <?php print $class; ?> center-block sidebar-items on-node-lock-disable" href="<?php print $href; ?>" title="<?php print $title; ?>">
      <div class="list-items-icons"><i class="fa <?php print $icon; ?>"></i></div>
      <p><?php if (isset($text)) print $text; ?></p>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa <?php print $icon; ?>"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>
<?php endif; ?>
