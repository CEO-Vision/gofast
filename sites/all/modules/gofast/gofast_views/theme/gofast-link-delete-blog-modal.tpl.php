<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a href="<?php print $href; ?>" class="<?php print $link_class; ?> navi-link">
      <span class="navi-icon"><i class="fa fa-trash-o"></i></span>
      <span class="navi-text"><?php print $text; ?></span>
    </a>
  <?php endif; ?>
<?php else : ?>
  <a class="btn btn-sm center-block sidebar-items navi-link" disabled>
    <span class="navi-icon"><i class="fa fa-trash-o"></i></span>
    <span class="navi-text"><?php print $text; ?></span>
  </a>
<?php endif; ?>
