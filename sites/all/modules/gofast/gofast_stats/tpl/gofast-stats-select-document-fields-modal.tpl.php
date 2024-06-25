<div id="document-fields-space-export" class="mt-5">
  <div class="mb-10">
    <h2><?= t("Select all the fields you want to export :", array(), array("context" => "gofast:gofast_stats")); ?></h2>
  </div>
  <div class="d-flex col-lg-12 flex-column form-group">
    <div class="row mb-2">
      <div class="col-md-4">
        <label class="checkbox mr-3 mb-2 user-select-none">
          <input type="checkbox" name="fields-bulk-check" id="fields-bulk-check"/>
          <span class="mr-2"></span>
          <div class="checkbox-label"><?= t("Check all") ?></div>
        </label>
      </div>
    </div>
    <div class="separator separator-solid my-3"></div>
    <div class="row all-fields-row">
      <?php foreach($fields_options as $field_name => $field_translated_name): ?>
        <div class="col-md-4">
          <label class="checkbox mr-3 mb-2 user-select-none">
            <input type="checkbox" name="<?= $field_name ?>" value="<?= $field_name ?>"/>
            <span class="mr-2"></span>
            <?= $field_translated_name ?>
          </label>
        </div>
      <?php endforeach; ?>
    </div>
  </div>
  <div class="mb-10 mt-20">
    <h2 class="mb-5"><?= t("Date :")?></h2>
    <input id="gofastDocumentsStatsDatetimepicker" class="form-control gofastDatepicker" data-boundary="window" type="text">
    <div class="text-muted"><?= t("Documents created or modified after this date") ?></div>
  </div>
</div>
<div class="btn btn-primary btn-sm" value="Delete" onclick="Gofast.downloadSpaceState()"><?= t("Export") ?></div>
<div class="btn btn-secondary btn-sm" value="Cancel" onclick="Drupal.CTools.Modal.dismiss()"><?= t("Cancel") ?></div>
<script>
  $(".all-fields-row").on("change", () => {
    let allChecked = $(".all-fields-row input:checked").length === $(".all-fields-row input").length
    $("#fields-bulk-check").prop("checked", allChecked).trigger("change")
  })
  
  $("#fields-bulk-check").on("click", () => {
    let checked = $("#fields-bulk-check").prop("checked");
    $(".all-fields-row input[type=checkbox]").prop("checked", checked);
  })

  $("#fields-bulk-check").on("change", () => {
    let allChecked = $(".all-fields-row input:checked").length === $(".all-fields-row input").length
    $("#fields-bulk-check").siblings(".checkbox-label").text(allChecked ? Drupal.t('Uncheck all') : Drupal.t('Check all'));
  })
</script>