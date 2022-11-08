<!-- START webform-panels-filloutPanel.tpl.php -->
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformDescription">
    <div class="card ">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#collapseWebformDescription">
                <i class="fas fa-info-circle"></i>
                <?= t("Description") ?>
            </div>
        </div>
        <div id="collapseWebformDescription" class="collapse show" data-parent="#webformDescription">
            <div class="card-body">
                <?= strlen($node->body[LANGUAGE_NONE][0]["value"]) > 1000 ? substr($node->body[LANGUAGE_NONE][0]["value"], 0, 1000) . "..." : $node->body[LANGUAGE_NONE][0]["value"] ?>
            </div>
        </div>
    </div>
</div>
<div class="accordion accordion-solid accordion-toggle-plus gutter-b" id="webformClient">
    <div class="card">
        <div class="card-header">
            <div class="card-title" data-toggle="collapse" data-target="#collapseWebformClient">
                <i class="far fa-file-alt"></i>
                <?= t("Form") ?>
            </div>
        </div>
        <!--begin::Form-->
        <div id="collapseWebformClient" class="collapse show" data-parent="#webformClient">
            <?php
            if ($form["#node"]->webform["status"] == 1) {
                echo drupal_render($form);
            } else {
            ?>
            <div class="alert alert-custom alert-notice alert-light-warning fade show my-5" role="alert">
                <div class="alert-icon"><i class="flaticon-warning"></i></div>
                <div class="alert-text"><?= t("The webform is closed for now. You can contact its creator if you need more information on this matter.", array(), array("context" => "gofast:gofast_webform")) ?></div>
                <div class="alert-close">
                    <button type="button" class="close" data-dismiss="alert" aria-label="Close">
                        <span aria-hidden="true"><i class="ki ki-close"></i></span>
                    </button>
                </div>
            </div>
            <?php
            }
            ?>
        </div>
    </div>
</div>
<script>
    // we may have to set the action attr to /gofast_ajaxification/ajax?url=${previousActionAttr}
    document.querySelectorAll('.webform-submit, .webform-next').forEach((button) => {
        button.classList.add('ctools-use-modal');
    });
</script>
<!-- END webform-panels-filloutPanel.tpl.php -->