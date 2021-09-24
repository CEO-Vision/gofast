<?php
$node_path = gofast_cmis_space_get_webdav_path_node_page($node->nid);
$path = drupal_get_path('module', 'gofast_ajaxification');
?>


<script>
  if (typeof Gofast.processAjax !== "undefined") {
    Gofast.processAjax("/home_page_navigation?&path=<?php print $node_path; ?>#navBrowser");

  } else {
    window.location.href = window.location.origin + "/home_page_navigation?&path=<?php print $node_path; ?>#navBrowser";
  }
</script>
