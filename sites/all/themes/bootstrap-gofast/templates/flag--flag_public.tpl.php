<?php if ($needs_wrapping_element) : ?>
  <div class="flag-outer flag-outer-<?php print $flag_name_css; ?>">
  <?php endif; ?>
  <span class="<?php print $flag_wrapper_classes; ?>">
    <?php if ($link_href) : ?>
      <a href="<?php print $link_href; ?>" title="<?php print $link_title; ?>" class="btn btn-sm center-block sidebar-items <?php print $flag_classes ?>" rel="nofollow">
        <div class="list-items-icons"><i class="fa fa-star"></i></div>
        <p><?php print $link_text; ?></p>
      </a>
      <!--<span class="flag-throbber">&nbsp;</span>-->
    <?php else : ?>
      <div class="list-items-icons"><i class="<?php print $flag_classes ?>">
          <p><?php print $link_text; ?></p>
        </i></div>
    <?php endif; ?>
    <?php //if ($after_flagging):
    ?>
    <!--      <span class="<?php //print $message_classes;
                            ?>">
        <?php //print $message_text;
        ?>
      </span>-->
    <?php //endif;
    ?>
  </span>
  <?php if ($needs_wrapping_element) : ?>
  </div>
<?php endif; ?>
