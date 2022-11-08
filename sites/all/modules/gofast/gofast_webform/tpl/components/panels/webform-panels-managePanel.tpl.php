<!-- START webform-panels-managePanel.tpl.php -->
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformConfigure">
    <div class="card ">
        <div class="card-header">
            <div class="card-title collapsed" data-toggle="collapse" data-target="#collapseWebformConfigure">
                <i class="fas fa-cog"></i>
                <?= t("Configuration") ?>
            </div>
        </div>
        <div id="collapseWebformConfigure" class="collapse" data-parent="#collapseWebformConfigure">
            <div class="card-body webformConfigurator">
            </div>
        </div>
    </div>
</div>
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformBuild">
    <div class="card ">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#collapseWebformBuild">
                <i class="fas fa-hammer"></i>
                <?= t("Edition") ?>
            </div>
        </div>
        <div id="collapseWebformBuild" class="collapse show" data-parent="#collapseWebformBuild">
            <div class="card-body webformBuilder">
            </div>
        </div>
    </div>
</div>
<!-- END webform-panels-managePanel.tpl.php -->