<?php if ($before) : ?>
<div class="gofast_metadata_field col-<?php echo isset($info['col_size']) ? $info['col_size'] : '12'; ?> d-flex justify-content-between align-items-center document__editable<?php echo isset($info['order']) ? ' order-' . $info['order'] : '' ?>"<?php echo isset($info['id']) ? ' id="gofast-extra-metadata-item-' . $info['id'] . '"' : '' ?>>
    <?php if (!empty($info["title"]) && !$info["no_title"]) : ?>
        <div class="font-weight-bolder flex-shrink-0 my-auto">
            <span><?php print $info["title"] ?> :</span>
        </div>
    <?php endif; ?>
    <div class="document__editable--field <?php if (!$info["no_flex"]) { ?> d-flex <?php } ?> w-100 <?php if (!empty($info["title"]) && !$info["no_title"]) { ?> justify-content-end pl-2 <?php } ?>  text-truncate">
        <div class="spinner document__editable--spinner d-none"></div>
<?php endif; ?>
<?php if ($after) : ?>
    </div>
</div>
<?php endif; ?>