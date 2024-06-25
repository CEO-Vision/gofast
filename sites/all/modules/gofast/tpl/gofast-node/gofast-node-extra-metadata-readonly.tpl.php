<div id="gofast-node-info-basic">
    <div class="row font-size-sm gofast_metadata_infotab" id="document__infotab">
        <?php foreach ($extra_infos as $key => $info) { ?>
            <?php if ($info['type'] == 'separator') : ?>
    </div>
    <div class="separator separator-solid my-4"></div>
    <div class="row font-size-sm gofast_metadata_infotab" id="document__infotab">
    <?php else : ?>
        <div class="gofast_metadata_field col-<?php echo isset($info['col_size']) ? $info['col_size'] : '12'; ?> d-flex justify-content-between align-items-center order-<?php echo $info['order'] ?>">
            <?php if (!empty($info["title"]) && !$info["no_title"]) : ?>
                <div class="font-weight-bolder flex-shrink-0 my-auto">
                    <span><?php print $info["title"] ?> :</span>
                </div>
            <?php endif; ?>
            <?php if (!empty($info["value"])) : ?>
                <span class="p-2 text-wrap text-right"><?php echo $info['value']; ?></span>
            <?php endif; ?>
        </div>
    <?php endif; ?>
<?php } ?>
    </div>
</div>