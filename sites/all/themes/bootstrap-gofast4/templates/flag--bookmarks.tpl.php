<?php if ($needs_wrapping_element): ?>
  <div class="flag-outer flag-outer-<?php print $flag_name_css; ?>">
  <?php endif; ?>
  <span class="<?php print $flag_wrapper_classes; ?>">
    <?php if ($link_href): ?>
      <a href="<?php print $link_href; ?>" title="<?php print $link_title; ?>" class="btn-sm <?php print $flag_classes ?>" rel="nofollow"><span class="fa fa-bookmark"></span> <?php print $link_text; ?></a><!--<span class="flag-throbber">&nbsp;</span>-->
      <?php else: ?>
      <span class="<?php print $flag_classes ?>"><?php print $link_text; ?></span>
    <?php endif; ?>
    <?php //if ($after_flagging): ?>
<!--      <span class="<?php //print $message_classes; ?>">
        <?php //print $message_text; ?>
      </span>-->
    <?php //endif; ?>
  </span>
  <?php if ($needs_wrapping_element): ?>
  </div>
<?php endif; ?>