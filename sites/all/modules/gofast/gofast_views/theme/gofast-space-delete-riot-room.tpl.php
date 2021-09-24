<?php if (isset($href)) : ?>
  <a <?php print ($disabled==true) ? '' : 'href="'.$href.'"'; ?> class="<?php print $link_class; ?> btn btn-sm center-block sidebar-items" title="<?php print $title; ?>"  <?php echo ($disabled==true) ? 'disabled' : ''; ?>>
    <div class="list-items-icons"><i class="fa fa-trash"></i></div>
    <p><?php print $text; ?></p>
  </a>
<?php endif; ?>
