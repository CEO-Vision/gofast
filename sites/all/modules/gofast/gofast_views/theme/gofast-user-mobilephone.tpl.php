<?php if (isset($tel)) { ?>
  <span class="gofast_download_link ">
    <a class="btn btn-xs gofast-callto <?php print $class; ?>" href="tel:<?php print $tel; ?>" style="margin-top: -8px;" data-toggle="tooltip" data-placement="top" title="<?php echo t('Call this user') ?>">
      <span class="fa fa-mobile fa-lg" style="margin-right: 8px; margin-left: 2px; margin-top: -10px"></span>
      <?php print $text; ?>
    </a>
  </span>
<?php } else { ?>
  <span class="gofast_download_link">
    <a class="btn btn-xs <?php print $tel; ?> disabled" style="margin-top: -8px;" data-toggle="tooltip" data-placement="top" title="<?php echo t('Call this user') ?>">
      <span class="fa fa-mobile fa-lg" style="margin-right: 8px; margin-left: 2px;"></span>
      <?php print $text; ?>
    </a>
  </span>
<?php } ?>
