<?php

/**
 * @file
 * gofast_vud.tpl.php
 *
 * UpDown widget theme for Vote Up/Down
 */
?>
<div class="vud-widget vud-widget-updown d-flex flex-row align-items-center container m-0 p-0" style="gap: .25rem;" id="<?php print $id; ?>">
  <!-- BEGIN Thumbs up -->
  <?php if ($show_links) : ?>
    <?php if ($show_up_as_link) : ?>
      <a href="<?php print $link_up; ?>" rel="nofollow" class="<?php print $link_class_up; ?> btn btn-icon btn-icon-primary btn-link-primary btn-sm w-50">
      <?php endif; ?>
      <i class="far fa-thumbs-up updown-up icon-nm"></i>
      <div class="element-invisible <?php print $class_up;  ?> updown-up"><?php print t('Vote up!'); ?></div>
      <?php if ($show_up_as_link) : ?>
      </a>
    <?php endif; ?>
  <?php endif; ?>
  <!-- END Thumbs up -->

  <!-- BEGIN points -->
  <span class="m-auto px-1"><?php print $unsigned_points; ?></span>
  <!-- END points -->

  <!-- BEGIN Thumbs down -->
  <?php if ($show_links) : ?>
    <?php if ($show_down_as_link) : ?>
      <a href="<?php print $link_down; ?>" rel="nofollow" class="<?php print $link_class_down;  ?> btn btn-icon btn-icon-primary btn-link-primary btn-sm w-50">
      <?php endif; ?>
      <i class="far fa-thumbs-down updown-down icon-nm"></i>
      <div class="element-invisible"><?php print t('Vote down!'); ?></div>
      <?php if ($show_down_as_link) : ?>
      </a>
    <?php endif; ?>
  <?php endif; ?>
  <!-- END Thumbs down -->

  <?php if ($show_reset) : ?>
    <a href="<?php print $link_reset; ?>" rel="nofollow" class="<?php print $link_class_reset; ?>" title="<?php print $reset_long_text; ?>">
      <div class="<?php print $class_reset; ?>">
        <?php print $reset_short_text; ?>
      </div>
    </a>
  <?php endif; ?>
</div>
