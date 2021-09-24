<?php if (isset($href)) : ?>
  <a <?php print ($disabled == true) ? '' : 'href="' . $href . '"'; ?> class="<?php print $link_class; ?> btn btn-sm center-block sidebar-items <?php echo ($disabled == true) ? 'disabled' : ''; ?>" title="<?php print $title; ?>" <?php echo ($disabled == true) ? 'disabled' : ''; ?>>
    <div class="list-items-icons"><span class="fa fa-plus"></span></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
