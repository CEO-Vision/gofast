<?php if ($is_confidential) : ?>
  <a class="btn btn-sm center-block sidebar-items" href="#" disabled="disabled">
    <div class="list-items-icons"><i class="fa fa-cloud-download" aria-hidden="true"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>

<?php elseif (isset($ref)) : ?>
  <a class="btn btn-sm center-block sidebar-items" <?php print $disabled; ?> href="/cmis/browser?id=<?php print $ref; ?>" onclick="<?php print $onclick; ?>">
    <div class="list-items-icons"><i class="fa fa-cloud-download" aria-hidden="true"></i></div>
    <p><?php if (isset($text)) print $text; ?></p>
  </a>
<?php endif; ?>