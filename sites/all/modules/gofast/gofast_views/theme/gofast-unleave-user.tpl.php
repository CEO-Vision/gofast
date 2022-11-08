<span class="gf-contextual-link">
  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?>" id="btn-unblock" href="<?php if (isset($href)) print $href; ?>" data-toggle="tooltip" data-placement="top" title="<?php echo t('Re-enable this user') ?>">
    <div class="list-items-icons"><i class="fa <?php if ($only_icon) {
                                                  echo "fa-lg";
                                                } ?> fa-check" style="padding-right: 6px;"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>
</span>
