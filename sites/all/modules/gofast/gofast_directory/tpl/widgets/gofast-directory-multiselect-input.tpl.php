<div class="gofast-directory-multiselect-input" data-submit="<?= $submit ?>" data-etid="<?= $entity_id ?>">
    <span class="gofast-directory-multiselect-span EditableInput__value editable d-block"><?= $placeholder ?></span>
    <div class="gofast-directory-multiselect-template d-none">
        <!-- We need this additional container around the selects so they can scroll without the buttons below -->
        <div class="gofast-directory-multiselect-selects-container">
            <div class="gofast-directory-multiselect-selects d-flex align-items-center">
                <?php foreach ($config as $key => $value) : ?>
                    <?php if (is_string($key) && is_array($value)) : ?>
                        <select class="form-control" name="gofast-directory-multiselect-select-<?= $key ?>">
                            <?php foreach ($value as $option_value => $option_title) : ?>
                                <option value="<?= $option_value ?>"<?= $default_values[$key] == $option_value ? " selected=\"true\"" : "" ?>><?= $option_title ?></option>
                            <?php endforeach; ?>
                        </select>
                    <?php endif; ?>
                    <?php if (is_string ($key) && is_string($value)) : ?>
                        <input class="form-control" name="gofast-directory-multiselect-select-<?= $key ?>" type="<?= $value ?>" value="<?= $default_values[$key] ?? "" ?>">
                    <?php endif ?>
                    <?php if (is_numeric($key)) : ?>
                        <span class="mx-2"><?= $value ?></span>
                    <?php endif; ?>
                <?php endforeach; ?>
            </div>
        </div>
        <span class="editableInputConfirmationButtons d-flex justify-content-center">
            <button data-toggle="tooltip" title="<?= $clear_tooltip ?>" class="btn btn-icon btn-sm clearButton"><i class="fa fa-trash text-secondary"></i></button>
            <button class="btn btn-icon btn-sm confirmButton"><i class="fas fa-check text-success"></i></button>
            <button class="btn btn-icon btn-sm cancelButton"><i class="fas fa-times text-danger"></i></button>
        </span>
    </div>
</div>