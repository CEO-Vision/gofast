<?php
if ($warning == true) {
    $class = "onlyoffice_button";
    $onclick = "onClick=\"Gofast.gofast_onlyoffice_show_warning('" . $path . "', $node->nid, event);return false;\"";
} else {
    $class = "";
    $onclick = "onClick=\"window.open('" . $path . "', '_blank')\"";
    $title = t("Edit this document in ligne from OnlyOffice");
}

if(module_exists('gofast_onlyoffice')){
    if(gofast_onlyoffice_is_edition_disabled($node)){
        $disabled = true;
    }
}

?>
<?php if (!isset($disabled)) : ?>
    <a id="contextual_btn_onlyoffice" class="btn btn-sm center-block sidebar-items <?php echo $class; ?>" <?php echo $onclick; ?> title="<?php print $title; ?>">
        <div class="list-items-icons"><i class="fa fa-edit"></i></div>
        <p><?php print $text; ?></p>
    </a>
<?php else : ?>
    <a id="contextual_btn_onlyoffice" class="btn btn-sm center-block sidebar-items <?php echo $class; ?>" disabled>
        <div class="list-items-icons"><i class="fa fa-edit"></i></div>
        <p><?php print $text; ?></p>
    </a>
<?php endif; ?>
