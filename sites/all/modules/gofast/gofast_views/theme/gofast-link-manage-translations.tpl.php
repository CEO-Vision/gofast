<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a id="link_upload_new_version_modal" class="<?php print $link_class; ?> on-node-lock-disable btn btn-sm center-block sidebar-items" href="<?php print $href; ?>">
      <div class="list-items-icons"><i class="fa fa-flag"></i></div>
      <p><?php print $text; ?></p>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a id="link_upload_new_version_modal" class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-flag"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
