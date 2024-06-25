<?php if (module_exists('gofast_workflows') && ($node->type == 'alfresco_item' || $node->type == 'article')) {
    print theme("workflow_rapide_dashboard_document", array(
        "node" => $node,
        'nb_assigned_tasks' => $nb_assigned_tasks,
        'nb_my_assigned_tasks' => $nb_my_assigned_tasks,
        'nb_other_assigned_tasks' => $nb_other_assigned_tasks
    ));
} ?>
