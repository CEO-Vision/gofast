<?php

$page = theme('gofast_user_profile', $variables);
$page_content = gofast_create_page_content($page, 'custom');

print $page_content;
