<?php

/**
 * Returns a modal confirm template before applying a category related to a naming rule.
 * Looks for the category term name in the "value" POST param.
 * If the category has no naming rule, will return FALSE.
 */
function gofast_naming_rules_apply_category_confirm() {
    $theme = "";
    $nid = gofast_xss_clean($_POST["nid"]);
    $node = node_load($nid);
    if (!$node) {
        return FALSE;
    }
    $value = gofast_xss_clean($_POST["value"], false, array("iframe"));
    $term = reset(taxonomy_get_term_by_name($value, "category"));
    $no_buttons = FALSE;
    if ($term && $term->field_naming_rules[LANGUAGE_NONE][0]["value"]) {
        $theme .= theme("gofast_naming_rules_apply_category_confirm_modal", ["node" => $node, "term" => $term, "add" => TRUE]);
        $no_buttons = TRUE;
    }
    $original_cat = $node->field_category[LANGUAGE_NONE][0]['tid'];
    $original_term = taxonomy_term_load($original_cat);
    if ($original_term && $original_term->field_naming_rules[LANGUAGE_NONE][0]["value"]) {
        $theme .=  theme("gofast_naming_rules_apply_category_confirm_modal", ["node" => $node, "term" => $original_term, "remove" => TRUE, "no_buttons" => $no_buttons]);
    }
    if (strlen($theme) > 0) {
        return json_encode(["message" => t("This category has a naming rule", [], ["context" => "gofast:gofast_naming_rules"]), "theme" => $theme]);
    }
    return FALSE;
}

function gofast_naming_rules_get_rule($term)
{
    $themed = isset($_GET["themed"]);
    $readable = isset($_GET["readable"]);
    if ($themed || $readable) {
        return gofast_naming_rule_get_node_ruled_value(NULL, $term, FALSE, TRUE);
    }
    return $term->field_naming_rules[LANGUAGE_NONE][0]["value"];
}

/**
 * Sets the naming rule for the category.
 * @param $term the full category taxonomy term entity
 * Looks for the naming rule string in the "value" POST param.
 * If the value is empty, will unset the naming rule.
 * @return a JSON-encoded array containing a message and a callback intended to be run client-side once the operation is done.
 */
function gofast_naming_rules_post_rule($term)
{
    $intended_rule = gofast_xss_clean($_POST["value"], false, array("iframe"));
    if (empty($intended_rule)) {
        $term->field_naming_rules[LANGUAGE_NONE] = [];
    } else {
        // Tagify formats tags as [[{value: "value"}]] masks: we simplify them into {{value}} masks
        $intended_rule = preg_replace('/\[\[{"value":"(.*?)"}]]/', '{{\1}}', $intended_rule);
        // Then we replace human-readable values by technical values
        $intended_rule = gofast_naming_rule_convert_naming_rule_value($intended_rule, FALSE);
        $term->field_naming_rules[LANGUAGE_NONE][0]["value"] = $intended_rule;
    }
    taxonomy_term_save($term);
    return json_encode([
        "message" => ["status" => "success",  "value" => t("The naming rule has been set successfully", [], ["context" => "gofast:gofast_naming_rules"])],
        "callback" => ["function" => "GofastKDataTableReload", "arguments" => ["gofastCategoriesTable"]]
    ]);
}
