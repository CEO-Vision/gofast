<?php


if(gofast_essential_is_essential()){
  if($node->type != "article"){
    $side_content = theme('gofast_node_sidebar', array('node' => $node));
    $content = theme('gofast_node_content', array('node' => $node));
    $page = theme('gofast_node',array('content' => $content, 'side_content' => $side_content, "node" => $node));
  }
} else {

  $side_content = theme('gofast_node_sidebar', array('node' => $node));
  $content = theme('gofast_node_content', array('node' => $node));
  $page = theme('gofast_node',array('content' => $content, 'side_content' => $side_content, "node" => $node));
}
$page_content = gofast_create_page_content($page, 'custom', '', $custom_grid, $node);

print $page_content;
?>
