<div class="gofast_wf_actions">
    <div>
            <span id="task_new_<?php print $variables['process_id'] ?>" onclick="<?php print $variables['addOnclick'] ?>" style="cursor:pointer;" title="<?php echo t("Create a new process model", array(), array("context" => "gofast:gofast_workflows")); ?>">
                <span class="fa fa-plus-square fa-lg gofast_wf_link">
                </span>
            </span>
            <span id="task_edit_<?php print $variables['process_id'] ?>" class='btn-process-editmodel-<?php print $variables['process_id'] ?>' style="cursor:not-allowed;opacity:0.4;" title="<?php echo t("Edit process model", array(), array("context" => "gofast:gofast_workflows")); ?>">
                <span class="fa fa-edit fa-lg gofast_wf_link">
                </span>
            </span>
            <span id="task_delete_<?php print $variables['process_id'] ?>" style="cursor:not-allowed;opacity:0.4" title="<?php echo t("Delete process model", array(), array("context" => "gofast:gofast_workflows")); ?>">
                <span class="fa fa-trash fa-lg gofast_wf_link">
                </span>
            </span>
     </div>
</div>
