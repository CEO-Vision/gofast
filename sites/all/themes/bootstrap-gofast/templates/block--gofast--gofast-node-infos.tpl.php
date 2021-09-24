<!-- START block--gofast--gofast-node-infos.tpl.php -->
<section id="<?php print $block_html_id; ?>" class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h2<?php print $title_attributes; ?>><?php print t($title, array(), array('context' => 'gofast')); ?></h2>
  <?php endif;?>
  <?php print render($title_suffix); ?>

    <div class="tab-content" id="gofast-node-infos-tab-content">
        <?php print $content ?>
    </div>


</section>

<!-- END block--gofast--gofast-node-infos.tpl.php -->
