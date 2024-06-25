
<?php $theme = theme('gofast_node_og', array('node' => $node, 'space_members' => $space_members, 'hasEssentialSpaceActions' => $hasEssentialSpaceActions)); ?>
<?php $subheader = theme('gofast_menu_header_subheader', array('node' => $node)); ?>
<?php $container_fluid = theme('gofast_content_container_fluid', array('content' => $theme)); ?>
<?php print theme('gofast_content', array('container' => $container_fluid, 'subheader' => $subheader)); ?>
