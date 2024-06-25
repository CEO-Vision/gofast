<?php if (!$no_buttons) : ?>
<h3 class="h1"><?= t("The category %name has a naming rule", ["%name" => $term_name],  ["context" => "gofast:gofast_naming_rules"]) ?></h3>
<?php endif; ?>

<?php if ($add && !$invalid) : ?>
    <p class="font-size-lg m-0 mt-4"><?= t("This means that once applied to the document, the document name will change according to the following rule:", [], ["context" => "gofast:gofast_naming_rules"]) ?></p>
    <?= theme("gofast_naming_rules_rule_container", ["rule" => $ruled_theme]) ?>
    <p class="font-size-lg m-0 mt-4"><?= t("Therefore, the document will be renamed as follows:", [], ["context" => "gofast:gofast_naming_rules"]) ?></p>
    <?= theme("gofast_naming_rules_rule_container", ["rule" => $ruled_value]) ?>
<?php endif; ?>

<?php if ($add && $invalid) : ?>
    <?= theme("gofast_naming_rules_rule_container", ["rule" => $ruled_theme]) ?>
    <p class="font-size-lg m-0 mt-4"><?= t("But all the fields required by the naming rule are not filled. You have to fill all the required fields in order to apply the category.", [], ["context" => "gofast:gofast_naming_rules"]) ?></p>
<?php endif; ?>

<?php if ($remove) : ?>
    <p class="font-size-lg m-0 mt-4"><i class="text-warning mr-2 fas fa-exclamation-triangle"></i><?= t("Removing the category %name from this document will also remove its current naming rule", ["%name" => $term_name],  ["context" => "gofast:gofast_naming_rules"]) ?></p>
<?php endif; ?>

<?php if (!$no_buttons) : ?>
<?php if ($remove || !$invalid) : ?>
<btn id="apply_category_confirm" class="btn btn-success"><?= t("Apply") ?></btn>
<?php endif; ?>
<btn id="apply_category_cancel" class="btn btn-secondary"><?= t("Cancel") ?> </btn>
<?php endif; ?>