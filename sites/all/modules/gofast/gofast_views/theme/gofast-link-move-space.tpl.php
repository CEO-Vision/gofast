<?php if (isset($href)) : ?>
  <a href="<?php print $href; ?>" class="<?php print $link_class; ?> btn btn-sm on-node-lock-disable center-block sidebar-items">
    <div class="list-items-icons"><i class="fa fa-random"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
