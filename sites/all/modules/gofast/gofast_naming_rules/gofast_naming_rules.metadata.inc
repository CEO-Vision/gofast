<?php

function gofast_naming_rules_metadata_get_metadata_types()
{
    $metadata_types = [
        t("Reference", [], ["context" => "gofast:gofast_naming_rules"]) => "field_document_reference",
        t("Creation date", [], ["context" => "gofast:gofast_naming_rules"]) => "created",
        t("Category", [], ["context" => "gofast:gofast_naming_rules"]) => "field_category",
        t("Author", [], ["context" => "gofast:gofast_naming_rules"]) => "field_document_author",
        t("Title", [], ["context" => "gofast:gofast_naming_rules"]) => "field_title",
        GOFAST_METADATA_CUSTOM_DATE_LABEL => "field_custom_date",
    ];
    return $metadata_types;
}


function gofast_naming_rules_metadata_get_metadata_value($node, $term, $field_name)
{
   if ($field_name == "field_category") {
    return i18n_taxonomy_localize_terms($term)->name;
   }
   if ($field_name == "created" || $field_name == "field_custom_date") {
    $value = $node->created;
    $datetime = DateTime::createFromFormat('U', $value)->setTime(0, 0)->format(DATE_ATOM);
    $date = explode("T", $datetime)[0];
    return $date;
   }
   if ($field_name == "field_document_author") {
    $infos = gofast_cmis_alfresco_get_infos($node);
    return $infos['document_author'];
   }
   return $node->$field_name[LANGUAGE_NONE][0]["value"];
}

/**
 * Intended to work with the contextual menu.
 * Returns true if the naming rule has _no_ naming rule, otherwise returns an explanatory message.
 */
function gofast_naming_rules_node_has_no_naming_rule($node)
{
    $node_category_tid = $node->field_category[LANGUAGE_NONE][0]["tid"];
    if(!$node_category_tid) {
        return TRUE;
    }
    $has_rule = (bool) db_select("field_data_field_naming_rules", "nr")
        ->fields("nr", array("entity_id"))
        ->condition("entity_id", $node_category_tid)
        ->countQuery()->execute()->fetchField();
    $has_ruled_value = TRUE;
    // we're not inserting so if the node doesn't hold a ruled value it means it doesn't have the naming rule applied
    if ($has_rule && !isset($node->original) && !isset($node->is_new)) {
        $term = taxonomy_term_load($node_category_tid);
        $ruled_value = gofast_naming_rule_get_node_ruled_value($node, $term, TRUE);
        $node_title = explode(".", $node->title);
        $node_title = implode(".", $node_title);
        // node is already named according to its naming rule
        $has_ruled_value = $ruled_value == $node_title;
    }
    if ($has_rule && $has_ruled_value) {
        return t("This document has a naming rule enforced by its category", [], ["context" => "gofast:gofast_naming_rules"]);
    } else {
        return TRUE;
    }
}

/**
 * A naming rule is stored in the database with technical field values but must be shown with human-readable values.
 * The purpose of this function is to make the conversion.
 */
function gofast_naming_rule_convert_naming_rule_value($naming_rule, $to_human_readable = TRUE) {
    $rule_string = preg_replace_callback('/{{(.*?)}}/', function ($matches) use ($to_human_readable) {
        if ($to_human_readable) {
            return "{{" . array_flip(gofast_naming_rules_metadata_get_metadata_types())[$matches[1]] . "}}";
        }
        return "{{" . gofast_naming_rules_metadata_get_metadata_types()[$matches[1]] . "}}";
    }, $naming_rule);
    return $rule_string;
}

/**
 * Given a node and a term with a naming rule naming rule, returns the node name with the naming rule applied.
 * $node is mandatory only if we're getting the metadata values
 */
function gofast_naming_rule_get_node_ruled_value($node, $term, $get_metadata_values = FALSE, $themed = FALSE)
{
    $naming_rule = $term->field_naming_rules[LANGUAGE_NONE][0]["value"];
    // human-readable value if we are to return the rule itself in a theme
    if ($themed && !$get_metadata_values) {
        $naming_rule = gofast_naming_rule_convert_naming_rule_value($naming_rule);
    }
    $invalid = FALSE;
    $ruled_value = preg_replace_callback('/{{(.*?)}}/', function ($matches) use ($node, $term, $get_metadata_values, $themed, &$invalid) {
        // $matches[1] contains the content between {{ and }}: replace it with custom template to fake tags
        $value = $matches[1];
        if ($get_metadata_values) {
            $value = gofast_naming_rules_metadata_get_metadata_value($node, $term, $value);
            if (!strlen($value)) {
                $invalid = TRUE;
            }
        }
        if ($themed) {
            $value = theme("gofast_ac_tag_placeholder", ["value" => $value, "added_classes" => ["text-dark"]]);
        }
        return $value;
    }, $naming_rule);
    if ($invalid) {
        return FALSE;
    }
    return $ruled_value;
}