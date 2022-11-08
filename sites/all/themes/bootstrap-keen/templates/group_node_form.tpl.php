<div class="card card-custom GofastForm__CardContainer">
    <div class="card-body">
        <div class="GofastForm__Field GofastForm__Field--title">
            <?php echo render($form['title']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--description">
            <?php echo render($form['field_description']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--content">
            <?php echo render($form['body']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--broadcast">
            <?php echo render($form['og_group_ref']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--folder">
            <div class="d-flex" style="gap: 2rem;">
                <div class="w-75">
                    <?php echo render($form['og_ztree_templates_folder']); ?>
                </div>
                <div class="w-25 accordion accordion-solid accordion-toggle-plus my-2">
                    <div class="card">
                        <div class="card-header">
                            <div class="card-title collapsed" data-toggle="collapse" data-target="#collapse-space-logo"><?= t("Custom logo", [], ["context" => "gofast:gofast_og"]) ?></div>
                        </div>
                        <div id="collapse-space-logo" class="collapse">
                            <div class="card-body">
                                <?php echo render($form['space_logo']); ?>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
        <?php echo render($form['actions']); ?>
        <div class="d-none"><?php echo drupal_render_children($form); ?></div>
    </div>
</div>

<script>
    jQuery(document).ready(function () {
        window.initFileInput({
                maxFileSize: 2000000,
                maxNumberOfFiles: 1,
                allowedFileTypes: ["image/jpeg", "image/png", "image/webp"],
            },
            true);
    });
</script>
