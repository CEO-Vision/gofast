<!-- START block--gofast--gofast-node-infos.tpl.php -->
<ul class="nav nav-pills">
  <li class="nav-item">
    <a class="nav-link active" href="#">Active</a>
  </li>
  <li class="nav-item">
    <a class="nav-link" href="#">Link</a>
  </li>
  <li class="nav-item">
    <a class="nav-link" href="#">Link</a>
  </li>
  <li class="nav-item">
    <a class="nav-link disabled" href="#">Disabled</a>
  </li>
</ul>

<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> clearfix card"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print t($title, array(), array('context' => 'gofast')); ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

    <div class="tab-content card-body" id="gofast-node-infos-tab-content">
        <?php print $content ?>
    </div>


</section>

<!-- END block--gofast--gofast-node-infos.tpl.php -->
