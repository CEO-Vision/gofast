<?php
$side_content = theme('gofast_node_sidebar', array('node' => $node));
$content = theme('gofast_webform_webform_container', array('node' => $node));
$page = theme('gofast_node', array('content' => $content, 'side_content' => $side_content, "node" => $node));
$page_content = gofast_create_page_content($page, 'custom', '', $custom_grid, $node);

print $page_content;
