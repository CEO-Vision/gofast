<?php if ($link_href): ?>
    <a class="btn btn-sm" href="<?php print $link_href; ?>" title="<?php print $link_title; ?>" class="<?php print $flag_classes ?>" rel="nofollow">
        <span class="glyphicon glyphicon-trash"></span>
        <?php //print $link_text; ?>
    </a>
    <?php else: ?>
    <span class="<?php print $flag_classes ?>"><?php //print $link_text; ?></span>
<?php endif; ?>
<?php if ($after_flagging): ?>
    <span class="<?php print $message_classes; ?>">
        <?php print $message_text; ?>
    </span>
<?php endif; ?>
