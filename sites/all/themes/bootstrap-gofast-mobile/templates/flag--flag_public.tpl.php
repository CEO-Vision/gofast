<?php if ($link_href) : ?>
    <a class="btn btn-sm center-block sidebar-items <?php print $flag_classes ?>" href="<?php print $link_href; ?>" title="<?php print $link_title; ?>" rel="nofollow">
        <div class="list-items-icons"><i class="fa fa-star"></i></div>
        <p><?php print $link_text; ?></p>
    </a>
<?php else : ?>
    <div class="list-items-icons"><i class="<?php print $flag_classes ?>"></i></div>
    <p><?php print $link_text; ?><p>
    <?php endif; ?>
    <?php if ($after_flagging) : ?>
        <span class="<?php print $message_classes; ?>">
            <?php print $message_text; ?>
        </span>
    <?php endif; ?>
