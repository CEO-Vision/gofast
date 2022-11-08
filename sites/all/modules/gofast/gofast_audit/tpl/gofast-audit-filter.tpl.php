<div class="card card-custom gutter-b">
    <!--begin::Header-->
    <div class="card-header border-0 pt-6">
        <h3 class="card-title">
            <span class="card-label font-weight-bolder font-size-h4 text-dark-75"><?php print t('Audit filters') ?></span>
        </h3>
        <div class="card-toolbar">
            <?php
            $block = module_invoke('views', 'block_view', '-exp-gofast_audit-page');
            print drupal_render($block['content']);
            ?>
        </div>
        <!--end::Accordion-->
    </div>
</div>
