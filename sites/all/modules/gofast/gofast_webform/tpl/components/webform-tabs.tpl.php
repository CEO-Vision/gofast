<!-- START webform-tabs.tpl.php -->
<div class="d-flex flex-column p-4 h-100">
    <ul class="nav nav-tabs" id="myTab" role="tablist">
        <li class="nav-item">
            <a class="nav-link active" id="fillout-tab" data-toggle="tab" href="#filloutPanel" role="tab" aria-controls="filloutPanel" aria-selected="true"><?= t("Fill out", [], ['context' => 'gofast:gofast_webform']) ?></a>
        </li>
        <?php if (node_access('update', $node)) : ?>
            <li class="nav-item">
                <a class="nav-link" id="manage-tab" data-toggle="tab" href="#managePanel" role="tab" aria-controls="managePanel" aria-selected="false"><?= t("Manage", [], ['context' => 'gofast:gofast_webform']) ?></a>
            </li>
            <li class="nav-item">
                <a class="nav-link" id="results-tab" data-toggle="tab" href="#resultsPanel" role="tab" aria-controls="resultsPanel" aria-selected="false"><?= t("Results", [], ['context' => 'gofast:gofast_webform']) ?></a>
            </li>
        <?php endif; ?>
        <li class="nav-item">
            <a class="nav-link" id="submission-tab" data-toggle="tab" href="#submissionPanel" role="tab" aria-controls="submissionPanel" aria-selected="false"><?= t("Your submissions", [], ['context' => 'gofast:gofast_webform']) ?></a>
        </li>
    </ul>
    <div class="border-bottom border-left border-right h-100 p-4 rounded-sm tab-content overflow-hidden" id="myTabContent">
        <div class="tab-pane fade show active h-100 overflow-auto" id="filloutPanel" role="tabpanel" aria-labelledby="fillout-tab" data-scroll="true" data-wheel-propagation="true">
            <?= theme("gofast_webform_panels_filloutPanel", ["node" => $node, 'form' => drupal_get_form("webform_client_form_$node->nid", $node)]) ?>
        </div>
        <?php if (node_access('update', $node)) : ?>
            <div class="tab-pane fade h-100 overflow-auto" id="managePanel" role="tabpanel" aria-labelledby="manage-tab" data-scroll="true" data-wheel-propagation="true">
                <?= theme("gofast_webform_panels_managePanel") ?>
            </div>
            <div class="tab-pane fade h-100 overflow-auto" id="resultsPanel" role="tabpanel" aria-labelledby="results-tab" data-scroll="true" data-wheel-propagation="true">
                <?= theme("gofast_webform_panels_resultsPanel") ?>
            </div>
        <?php endif; ?>
        <div class="tab-pane fade h-100 overflow-auto" id="submissionPanel" role="tabpanel" aria-labelledby="submission-tab" data-scroll="true" data-wheel-propagation="true">
            <?= theme("gofast_webform_panels_submissionPanel") ?>
        </div>
    </div>
</div>
<!-- END webform-tabs.tpl.php -->
<script>
    jQuery(document).ready(function() {
        // if we reload the page, we want to display the current tab content
        Drupal.attachBehaviors();
        if (window.location.hash) {
            let kebabHash = window.location.hash.replace(/[A-Z]/g, x => "-" + x.toLowerCase());
            jQuery(kebabHash.replace("panel", "tab")).trigger("tap");
        }
    });
</script>