<!-- START webform-panels-resultsPanel.tpl.php -->
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformResults">
    <div class="card ">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#collapseWebformResults">
                <i class="fas fa-chart-line"></i>
                <?= t("Statistics") ?>
            </div>
        </div>
        <div id="collapseWebformResults" class="collapse show" data-parent="#webformResults">
            <div class="card-body webformResultsStats">
            </div>
        </div>
    </div>
</div>
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformResultsExports">
    <div class="card ">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#collapseWebformResultsExports">
                <i class="fas fa-cloud-download-alt"></i>
                <?= t("Exports") ?>
            </div>
        </div>
        <div id="collapseWebformResultsExports" class="collapse show" data-parent="#webformResultsExports">
            <div class="card-body webformResultsExports">
            </div>
        </div>
    </div>
</div>
<?= theme("gofast_webform_panels_submissionPanel") ?>
<!-- END webform-panels-resultsPanel.tpl.php -->