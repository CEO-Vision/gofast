<?php if (isset($href)) : ?>
  <a href="<?php print $href; ?>" class="<?php print $link_class; ?> btn btn-sm center-block sidebar-items" title="<?php print $title; ?>">
    <div class="list-items-icons"><i class="fa fa-plus"></i></div>
      <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
