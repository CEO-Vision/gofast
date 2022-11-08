<?php   

$page = theme('gofast_conference', $variables);
$page_content = gofast_create_page_content($page, 'custom');

print $page_content;
