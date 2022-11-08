<?php $theme = theme('gofast_stats_global_dashboard_content') ?>
<?php $container_fluid = theme('gofast_content_container_fluid', array('content' => $theme)); ?>
<?php print theme('gofast_content', array('container' => $container_fluid, 'subheader' => "<br />")); ?>
