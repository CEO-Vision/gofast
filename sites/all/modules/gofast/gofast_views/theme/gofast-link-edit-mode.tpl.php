<?php if (!isset($disabled)) : ?>
  <?php if (isset($href)) : ?>
    <a nid="<?php print $nid ?>" href="<?php print $href ?>" class="<?php print $link_class ?> btn btn-sm  on-node-lock-disable center-block sidebar-items" alf_id="<?php print $alf_id ?>" is_office="<?php print $isoffice ? "true" : "false"; ?>" title="<?php print $title; ?>">
      <div class="list-items-icons"><i class="fa fa-edit"></i></div>
      <p><?php print $text; ?></p>
    </a>
  <?php endif; ?>
<?php else :  ?>
  <a class="btn btn-sm center-block sidebar-items" disabled>
    <div class="list-items-icons"><i class="fa fa-edit"></i></div>
    </p><?php print $text; ?></p>
  </a>
<?php endif; ?>
