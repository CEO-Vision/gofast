

<?php if (isset($output)) : ?>
  <div class="gofast-node-actions dropdown<?php print implode(' ', $class); ?>">
    <a class="btn btn-light btn-xs btn-icon mr-2 dropdown-hover" type="button" id="dropdownMenu1" data-toggle="dropdown">
      <span class="fa fa-bars"></span>
      <?php if (isset($text)) : ?>
        <span class="actions-title">&nbsp;<?php print $text; ?></span>
      <?php endif; ?>
    </a>
    <?php print $output; ?>
  </div>

<?php endif; ?>
