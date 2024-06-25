<span class="mb-2"><?= t('Please select the columns you want to display') ?></span>
<div id="list-columns-filters" class="mt-5">
    <?php $i = 0; ?>
    <?php foreach ($columns as $metadatas_name => $metadatas) : ?>
        <div id="accordion-columns-filters-<?= $i ?>" class="accordion accordion-solid accordion-toggle-plus gofastBoostrapPanel accordion-advanced-search-standard mb-5">
            <div class="card">
                <div class="card-header" id="section-header-<?= $i ?>">
                    <h5 class="mb-0">
                        <div class="card-title collapsed" data-toggle="collapse" data-parent="#accordion-columns-filters-<?= $i ?>" data-target="#section-content-<?= $i ?>" aria-expanded="false">
                            <?= $metadatas_name ?>
                        </div>
                    </h5>
                </div>
                <div id="section-content-<?= $i ?>" class="collapse show" role="tabpanel" aria-labelledby="section-header-<?= $i ?>" data-parent="#accordion-columns-filters-<?= $i ?>">
                    <div class="card-body">
                        <div class="form-group d-flex">
                            <div class="col-lg-12">
                                <div class="row mb-2">
                                    <label class="checkbox mr-3 font-weight-bold">
                                        <input type="checkbox" id="check-all-columns-<?= $i ?>" class="check-all-columns" data-parent="#accordion-columns-filters-<?= $i ?>">
                                        <span class="mr-2"></span>
                                        <div class="checkbox-label"><?= t('Check all') ?></div>
                                    </label>
                                </div>
                                <div class="separator separator-solid my-3"></div>
                                <div class="row">
                                    <?php foreach ($metadatas as $key => $column) : ?>
                                        <div class="col-md-4">
                                            <div class="mb-2">
                                                <label class="checkbox mr-3">
                                                    <input type="checkbox" name="columns[]" value="<?php print $column['id']; ?>" <?php if ($column['checked']) : echo 'checked';
                                                                                                                                        endif; ?>>
                                                    <span class="mr-2"></span>
                                                    <?php print $column['title']; ?>
                                                </label>
                                            </div>
                                        </div>
                                    <?php endforeach; ?>
                                </div>
                                <?php // Close the raw if it's not closed 
                                ?>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <?php $i++; ?>
    <?php endforeach; ?>
</div>
<button type="button" id="submit-columns-filters" class="btn btn-sm btn-success">Valider</button>

<style>
    /* Style for the columns */
    .row {
        display: flex;
        flex-wrap: wrap;
        margin-right: -15px;
        margin-left: -15px;
    }

    .col-md-4 {
        flex: 0 0 33.333333%;
        max-width: 33.333333%;
        padding-right: 15px;
        padding-left: 15px;
    }
</style>

<script>
    // Check ths status of all checkboxes and check the check-all-columns checkbox if all the checkboxes are checked
    $('.accordion').each(function() {
        var allChecked = $(this).find('input[name="columns[]"]').length === $(this).find('input[name="columns[]"]:checked').length;
        $(this).find('.check-all-columns').prop('checked', allChecked);
        $(this).find('.checkbox-label').text(allChecked ? Drupal.t('Uncheck all') : Drupal.t('Check all'));
    });
    
    

</script>
