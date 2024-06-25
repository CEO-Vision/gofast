<?php global $base_url; ?>
<?php if ($type == "site") : ?>
<div class="card card-custom card-stretch mt-4" style="height: calc(100%  - 2rem);">
    <div class="card-body p-5 d-flex flex-column" style="gap: .5rem;">
<?php endif; ?>
        <div id="gofastAuditTable" class="datatable datatable-bordered datatable-head-custom" data-type="<?php echo $type ?>" data-etid="<?php echo $etid ?>" data-columns='<?php echo $columns ?>'></div>
<?php if ($type == "site") : ?>
        <div class="d-flex flex-column">
            <span class="text-muted"><?= t("Export: This will export all the filtered results under a limit of 50 000 results", [], ["gofast:gofast_audit"]) ?></span>
            <span class="text-muted"><?= t("Click for export", [], ["gofast:gofast_audit"]) ?>&nbsp;
                <span id="audit_export_xls_button" style="display:none;">
                    <a href="/gofast_audit_xls" data-query=""></a>
                </span>
                <button onclick="Gofast.download_audit_export()" id="audit_export_btn_group_xlsx" type="button" class="btn btn-default p-0">
                    <span class="fa fa-file-excel-o"></span>
                </button>
            </span>
        </div>
    </div>
</div>
<?php endif; ?>

<script src="<?php echo $base_url . "/sites/all/modules/gofast/gofast_directory/js/gofastAuditDirectoryTable.js" ?>"></script>
<script>
    jQuery(document).ready(function() {
        Gofast.initAuditDirectory();
    });
</script>

<?php if ($type == "node" && user_access("access audit")) : ?>
    <a id="audit_node_button" class="d-block mt-2" href="/gofast_audit" ><button class="btn btn-default btn-sm"><?= t('Go to audit page' , array(), array('context' => 'gofast:gofast_audit')) ?></button></a>
<?php endif; ?>