

<?php if (isset($output)) : ?>

  <div class="gofast-node-actions btn-group <?php print implode(' ', $class); ?>" id="gofast-node-actions-microblogging">
    <a class="btn btn-default btn-xs dropdown-toggle" type="button" id="dropdownMenu1" data-toggle="dropdown">
      <span class="fa fa-bars"></span>
      <?php if (isset($text)) : ?>
        <span class="actions-title">&nbsp;<?php print $text; ?></span>
      <?php endif; ?>
    </a>
	<?php print $output; ?>
  </div>

<?php endif; ?>
