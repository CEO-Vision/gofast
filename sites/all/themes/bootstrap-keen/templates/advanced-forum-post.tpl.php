    <?php
        if(!gofast_essential_is_essential()){
            
            $side_content = theme('gofast_node_forum_sidebar', array('node' => $node));
            $content = theme('gofast_forum', array('node' => $node, 'links' => $content['links']));
            $page = theme('gofast_node',array('content' => $content, 'side_content' => $side_content));
            $page_content = gofast_create_page_content($page, 'custom', '', 'gofast-content--collapsible-side');
    
            print $page_content;
        }
    ?>
