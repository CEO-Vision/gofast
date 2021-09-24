<?php if ($is_confidential) : ?>
  <a class="btn btn-sm center-block sidebar-items" disabled="disabled">
    <div class="list-items-icons"><i class="fa fa-envelope"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>

<?php elseif (isset($href)) : ?>
  <a class="btn btn-sm center-block sidebar-items <?php print $class; ?>" href="<?php print $href; ?>">
    <div class="list-items-icons"><i class="fa fa-envelope"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>
<?php endif; ?>
