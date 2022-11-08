<?php if (module_exists('gofast_workflows') && ($node->type == 'alfresco_item' || $node->type == 'article')) {
    print theme("workflow_rapide_dashboard_document", array("node" => $node));
} ?>
