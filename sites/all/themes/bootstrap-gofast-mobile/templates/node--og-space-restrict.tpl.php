<?php $node_path = gofast_cmis_space_get_webdav_path_node_page($node->nid); ?>

<script>Gofast.processAjax("/home_page_navigation?&path=<?php print $node_path; ?>#navBrowser");</script>