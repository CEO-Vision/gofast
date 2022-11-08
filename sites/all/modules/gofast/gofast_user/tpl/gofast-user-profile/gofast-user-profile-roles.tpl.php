<?php foreach ($roles as $role) : ?>
<span class="label label-inline label-rounded label-outline-primary mr-2 mb-2"><span class="gofastUserProfileRoleLabel" style="width: 10ch; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; text-align: center;"><?= t($role, array(), array("context" => "gofast")) ?></span></span>
<?php endforeach; ?>
<?php foreach ($permissions as $permission_technical_name => $permission) :
$is_internal = FALSE;
$permission_color = "warning";
if(!array_values($permission)[0] && $permission_technical_name != "extranet") {
    continue;
}
if(!array_values($permission)[0] && $permission_technical_name == "extranet") {
    $is_internal = TRUE;
    $permission_color = "success";
}
?>
<span class="label label-inline label-rounded label-outline-<?= $permission_color ?> mr-2 mb-2"><span class="gofastUserProfileRoleLabel" style="width: 10ch; overflow: hidden; text-overflow: ellipsis; white-space: nowrap; text-align: center;"><?= $is_internal ? t("Internal", array(), array("context" => "gofast:gofast_user")) : array_keys($permission)[0] ?></span></span>
<?php endforeach; ?>
<script>
    jQuery(document).ready(function() {
        $(".gofastUserProfileRoleLabel").each(function(i, e) {
            if (e.innerText.length < 10) {
                return;
            }
            e.title = e.innerText;
            $(e).tooltip();
        });
    });
</script>