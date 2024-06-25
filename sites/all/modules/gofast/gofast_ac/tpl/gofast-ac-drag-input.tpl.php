<div class="gofast-ac-drag-input">
    <span class="tagify-ac-drag-span EditableInput__value editable d-block"><?= $templated_value ?: $span_placeholder ?></span>
    <div class="tagify-ac-drag-input d-none" id="gofast-ac-drag-input-<?= $input_id ?>">
        <input class="form-control" type="text" placeholder="<?= $input_placeholder ?>" value="<?= $value ?>" />
        <tags class="tagify tagify--focus">
            <?php foreach ($rulable_tags as $tag_name => $tag_value) : ?>
                <tag class="tagify__tag tagify__tag--model tagify__tag--primary text-white" draggable="true" data-drag="<?= $tag_value ?>" class="d-inline-block"><?= $tag_name ?></tag>
            <?php endforeach; ?>
        </tags>
        <span class="editableInputConfirmationButtons d-flex align-items-center justify-content-center" style="margin-left: auto; margin-block: auto;">
            <button data-toggle="tooltip" title="<?= $clear_tooltip ?>" class="btn btn-icon btn-sm clearButton"><i class="fa fa-trash text-secondary"></i></button>
            <button class="btn btn-icon btn-sm cancelButton"><i class="fas fa-times text-danger"></i></button>
            <button data-submit="<?= $submit_endpoint ?>" class="btn btn-icon btn-sm confirmButton"><i class="fas fa-check text-success"></i></button>
        </span>
    </div>
</div>