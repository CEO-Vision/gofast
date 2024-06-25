<?php
$items_count = count($nodes_description);
?>

<?php
/** @var string[] Array of node types that need the file warning displayed */
$display_file_warning_types = [
    'alfresco_item',
    'article',
];

$check_item_needs_display_warning = function($description) use ($display_file_warning_types) {
    // isn't a node -> is a folder
    if(!isset($description->node_type)) {
        return true;
    }
    // when it is a node, check if its type is included in the list of types that need the file warning
    return in_array($description->node_type, $display_file_warning_types);
};

// check if ANY item description needs the warning displayed
$should_display_file_warning = false;
foreach($nodes_description as $description) {
    if($check_item_needs_display_warning($description)) {
        $should_display_file_warning = true;
        break;
    }
}

if($should_display_file_warning) {
?>
<div class='alert alert-custom alert-notice alert-light-warning fade show' role='alert'>
    <div class='alert-icon'><i class='flaticon-warning'></i></div>
    <div class='alert-text m-0'>
        <ul class="m-0">
            <li class="font-weight-bold"><?= t("Files will also be removed from all their locations", [], ["context" => 'gofast' ]) ?></li>
            <li><?= t("Files with ", [], ["context" => 'gofast']) ?> <i class="fa fa-question-circle"></i> <?= t(" have more than one emplacements", [], ["context" => 'gofast']) ?></li>
        </ul>
    </div>
</div>
<?php } ?>

<h3> <?= format_plural($items_count, "Are you sure you want to delete the following item?", "Are you sure you want to delete the following items?", [], ["context" => "gofast:ajax_file_browser"]) ?></h3>

<?php foreach ($nodes_description as $index => $node_description) :
    $locations_string = implode("", array_map(function($loc) {
        return "<ul class='list-group'>" . str_replace("/Sites", "", $loc) . "</ul>";
    }, $node_description->locations));
    $is_templates = $node_description->title == "TEMPLATES";
    ?>
    <div style="width: max-content;" class="my-2" <?php if (count($node_description->locations) > 1) : ?>data-toggle="tooltip" data-html="true" data-trigger="hover" data-placement="bottom" title="<li class='border-0 list-group-item'><?= $locations_string ?></li>" <?php endif; ?> <?php if (!empty($node_description->children)) : ?> type="button" data-toggle="collapse" data-target="#removableContent<?=$index?>" <?php endif; ?>>
        <div class="d-flex align-items-center">
            <i class="fa-2x <?= $node_description->icon ?>" <?= $is_templates ? "style=\"color: #F0685A !important;\"" : "" ?>></i>
            &nbsp;<span class="font-size-lg"><?= $node_description->title ?></span>
            <?php if (count($node_description->locations) > 1) : ?>&nbsp;<i class="fa fa-question-circle"></i><?php endif;?>
        </div>
        <?php if (!empty($node_description->children)) : ?>
        <div class="collapse" id="removableContent<?=$index?>">
            <div class="font-weight-bold">
                <?= t("The folder above has the following content:", [], ["context" => "gofast:ajax_file_browser"]) ?>
            </div>
            <?php foreach($node_description->children as $child) :
                $is_templates = $child->title == "TEMPLATES";
                ?>
                <div>
                    <i class="<?= $child->icon ?>" <?= $is_templates ? "style=\"color: #F0685A !important;\"" : "" ?>></i>
                    &nbsp;<span><?= $child->title ?></span>
                </div>
            <?php endforeach; ?>
        </div>
        <?php endif; ?>
        <?php if (!empty($node_description->linked_contents['target_links'])) : ?>
            <div class="collapse show ml-5" id="removableContent<?=$index?>">
                <div class="font-weight-bold">
                    <?= t("This document has links to the following contents:", [], ["context" => "gofast:ajax_file_browser"]) ?>
                </div>
                <?php foreach($node_description->linked_contents['target_links'] as $target_link) : ?>
                    <div>
                        <i class="<?= $target_link['icon'] ?>"></i>
                        &nbsp;<span><?= $target_link['title'] ?></span>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>
        <?php if (!empty($node_description->linked_contents['source_links'])) : ?>
            <div class="collapse show ml-5" id="removableContent<?=$index?>">
                <div class="font-weight-bold">
                    <?= t("This document is linked by the following contents:", [], ["context" => "gofast:ajax_file_browser"]) ?>
                </div>
                <?php foreach($node_description->linked_contents['source_links'] as $source_link) : ?>
                    <div>
                        <i class="<?= $source_link['icon'] ?>"></i>
                        &nbsp;<span><?= $source_link['title'] ?></span>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>
    </div>
    <div class="separator separator-solid my-1"></div>
<?php endforeach; ?>

<script>
    jQuery(document).ready(function() {
        setTimeout(function() {
            jQuery("body").tooltip({ selector: '[data-toggle=tooltip]' });
            jQuery(".dropdown-menu").removeClass("show");
        },  1000);    
    });
</script>
