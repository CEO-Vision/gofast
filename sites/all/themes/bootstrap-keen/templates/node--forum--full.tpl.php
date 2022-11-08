<?php

$page = theme('gofast_forum', $variables);
$page_content = gofast_create_page_content($page, 'custom');

print $page_content;
