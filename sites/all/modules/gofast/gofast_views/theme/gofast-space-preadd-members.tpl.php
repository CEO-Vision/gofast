<?php if (isset($href)) : ?>
  <tr>
    <td> <a href="<?php print $href; ?>" class="<?php print $link_class; ?> btn btn-sm center-block sidebar-items" title="<?php print $title; ?>">
        <div class="list-items-icons"><i class="fa fa-user-plus"></i></div>
        <p><?php print $text; ?></p>
      </a>
    </td>
  </tr>
<?php endif; ?>
