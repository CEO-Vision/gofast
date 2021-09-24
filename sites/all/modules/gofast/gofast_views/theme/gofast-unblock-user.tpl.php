<span>
  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?>" id="btn-unblock" href="<?php if (isset($href)) print $href; ?>" data-toggle="tooltip" data-placement="top" title="<?php echo t('Unblock this user', array(), array('context' => 'gofast')) ?>">
    <div class="list-items-icons"><i class="fa <?php if ($only_icon) {
                                                    echo "fa-lg";
                                                  } ?> fa-unlock" style="margin-left:1px;margin-right: 5.5px;"></i></div>
      <p><?php if (isset($text)) print $text; ?></p>
  </a>
</span>
