<?php // Reach all the fields of the form ?>
<?php foreach ($fieldsets as $key => $fieldset): ?>
    <div id="accordion-search-<?= $key ?>" class="accordion accordion-solid accordion-toggle-plus gofastBoostrapPanel accordion-advanced-search-standard mb-5">
        <div class="card">
            <div class="card-header" id="section-header-<?= $key ?>">
                <h5 class="mb-0">
                    <div class="card-title collapsed" data-toggle="collapse" data-parent="#accordion-search-<?= $key ?>" data-target="#section-content-<?= $key ?>" aria-expanded="false">
                        <?= $fieldset['title'] ?>
                    </div>
                </h5>
            </div>
            <div id="section-content-<?= $key ?>" class="collapse" role="tabpanel" aria-labelledby="section-header-<?= $key ?>" data-parent="#accordion-search-<?= $key ?>">
                <div class="card-body">
                    <div class="form-group d-flex">
                        <div class="col-lg-12">
                            <?php $i = 0; ?>
                            <?php foreach ($fieldset['filters'] as $key => $field): ?>
                                <?php // Open a raw every modulo 2 ?>

                                <?php if ($field['filter_hidden'] || $field['type'] == "separator"): ?>
                                    <?php continue; ?>
                                <?php endif; ?>
                                <?php if ($i % 2 == 0): ?>
                                    <div class="form-group d-flex w-100">
                                <?php endif; ?>
                                        <div class="GofastForm__Field col-lg-6">
                                            <?= theme('gofast_search_advanced_field', array('field' => $field, 'key' => $key)); ?>
                                        </div>
                                <?php $i++; ?>
                                <?php // Close a raw every modulo 2 ?>
                                <?php if ($i % 2 == 0): ?>
                                    </div>
                                <?php endif; ?>
                            <?php endforeach; ?>
                            <?php // Close the raw if it's not closed ?>
                            <?php if ($i % 2 != 0): ?>
                            </div>
                            <?php endif; ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
<?php endforeach; ?>

