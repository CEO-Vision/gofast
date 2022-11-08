  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?> " <?php if (isset($disabled)) : ?> disabled <?php else : ?> href="<?php print $href; ?>" <?php endif; ?>>
    <div class="list-items-icons"><i class="fa fa-trash-o"></i></div>
    <p><?php print $text; ?></p>
    <?php if (isset($disabled)) : ?>
      &nbsp;&nbsp;<span data-toggle="tooltip" title="<?php echo t("You can not delete this userlist, because it's still a members of location(s)", array(), array('context' => 'gofast_userlist')); //htmlentities($description)
                                                      ?>"> <i class="fa fa-question-circle"></i> </span>
    <?php endif; ?>
  </a>
