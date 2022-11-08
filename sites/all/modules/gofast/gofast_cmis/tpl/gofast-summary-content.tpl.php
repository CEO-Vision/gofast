<div class="accordion accordion-toggle-arrow" id="gofastSummaryAccordion">
    <div class="card<?= $hide ? " d-none" : "" ?>">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#gofastSummaryContent">
                <i class="fas fa-pen"></i> <?= t("Resume") ?>
            </div>
        </div>
    </div>
    <div id="gofastSummaryContent" class="collapse card-body p-4" data-parent="#gofastSummaryAccordion">
        <div class='gofastSummaryContent bg-secondary rounded shadow-sm'>
            <?= $body ?>
        </div>
    </div>
</div>
