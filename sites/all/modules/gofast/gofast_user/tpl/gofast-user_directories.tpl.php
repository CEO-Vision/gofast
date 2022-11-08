<?php
$subheader = theme('gofast_menu_header_subheader');
$container_fluid = theme('gofast_content_container_fluid', array('content' => $content));
print theme('gofast_content', array('container' => $container_fluid, 'subheader' => $subheader));