<span class="gf-contextual-link">
  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?>" id="btn-unblock" href="<?php if (isset($href)) print $href; ?>" data-toggle="tooltip" data-placement="top" title="<?php echo t('Edit the picture', array(), array("context" => "gofast:gofast_user")) ?>">
    <div class="list-items-icons"><i class="fas <?php if ($only_icon) {
                                                  echo "fa-lg";
                                                } ?>  fa-pen-square fa-2x p-1" style="padding-right: 6px;"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>
</span>