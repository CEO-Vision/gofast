<?php
// normal case: we're displaying a list item
if (strlen($item[1]) > 0) : ?>
    <span><?= $item[0] ?></span>
    <div class="d-flex align-items-center">
    <?php // data labels
    if (isset($item[2])) : ?>
            <span class="label label-inline label-light font-weight-bold"><?= $item[2] ?></span>
            <?php if($is_admin) : ?>
            <span class="label label-inline label-dark font-weight-bold"><?= $item[1] ?></span>
            <?php endif; ?>
    <?php else : ?>
        <?php if($is_admin || isset($item["subitem"])) : ?>
        <span class="label label-inline label-light font-weight-bold"><?= $item[1] ?></span>
        <?php endif; ?>
    <?php endif; ?>
    <?php // eventual subitem
    if (isset($item["subitem"]) && $is_admin) : ?>
        <ul class="list-group">
            <?php foreach ($item["subitem"] as $subitem) : ?>
                <li class="list-group-item ml-auto border-0">
                    <small><strong><?= $subitem[0] . ":" ?></strong>&nbsp;<?= $subitem[1] ?></small>
                </li>
            <?php endforeach; ?>
        </ul>
    <?php endif; ?>
    </div>
<?php // special case: we're displaying a subtitle
else : ?>
    <span class="mx-auto font-weight-bold font-size-h3"><?= t($item[0], ["@site_name" => variable_get("site_name", "GoFAST")], ["context" => "gofast"]) . ":" ?></span>
<?php endif; ?>