<?php $theme = theme('gofast_node_userlist', array('node' => $node, 'content' => $content)); ?>
<?php $subheader = theme('gofast_menu_header_subheader', array('node' => $node)); ?>
<?php $container_fluid = theme('gofast_content_container_fluid', array('content' => $theme)); ?>
<?php print theme('gofast_content', array('container' => $container_fluid, 'subheader' => $subheader)); ?>
