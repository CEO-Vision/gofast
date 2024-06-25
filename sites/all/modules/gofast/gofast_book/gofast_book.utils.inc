<?php

function gofast_book_get_parent_nid($nid) {
    $parent_wiki_nid = FALSE;

    $article_ref = gofast_cmis_node_get_reference_by_nid_without_cmis($nid);
    $parent_path = gofast_cmis_webservice_get_node_parents($article_ref)[0];
    $parent_item = gofast_cmis_item_get_by_path($parent_path);
    if ($parent_item && !empty((array) $parent_item)) {
      if (substr($parent_path, -strlen("/Wikis")) == "/Wikis") {
        $group_path = substr($parent_path, 0, -strlen("/Wikis"));
        $group_item = gofast_cmis_item_get_by_path($group_path);
        if ($group_item && !empty((array) $group_item)) {
          $parent_wiki_nid = $group_item->properties["gofast:nid"];
        }
      } else {
        $parent_path = substr($parent_path, -1) == "/" ? substr($parent_path, 0, -1) : $parent_path;
        $parent_name = end(explode('/', $parent_path));
        $parent_wiki_path = $parent_path . "/" . $parent_name . ".html";
        $parent_wiki_item = gofast_cmis_item_get_by_path($parent_wiki_path);
        $parent_wiki_nid = $parent_wiki_item->properties["gofast:nid"];
      }
    }
    return $parent_wiki_nid;
}

function gofast_book_is_article_homepage($nid) {
    $table = "field_data_homepage";
    $field = "homepage_value";
    $query = db_select($table, "f");
    $query->condition("f.$field", $nid);
    $count = $query->countQuery()->execute()->fetchField();
    return $count > 0;
}

function gofast_book_is_node_wiki_article($nid) {
    if (gofast_get_node_type($nid, TRUE) != "article") {
        return FALSE;
    }
    $ref = gofast_cmis_node_get_reference_by_nid_without_cmis($nid);
    $path = gofast_cmis_webservice_get_node_parents($ref)[0];
    return strpos($path, "/Wikis") > 0;
}

function gofast_book_format_article_handle_subwikis($child, &$articles) {
    $key = urlencode($child->name);
    if ($child->isFolder) {
        foreach($child->children as $kc => $c){
            if(urlencode($c->name) == $key){
                $nid = $c->nid;
                $child->nid = $nid;
                $child->link_path = $c->link_path;
                $child->edit_link = $c->edit_link;
                unset($child->children[$kc]);
            }
        }
    }
    
    $articles[] = $child;
}

function gofast_book_format_article_from_alfresco_api_descendant($descendant, $parent) {
    $descendant->name = str_replace(".html", "", $descendant->name);
    if (isset($descendant->properties->{"gofast:nid"})) {
        $descendant->nid = $descendant->properties->{"gofast:nid"};
    }
    $descendant->id = random_int(0, 999999);
    $descendant->pid = $parent->id;
    if ($descendant->isFile) {
        $nid = $descendant->properties->{"gofast:nid"};
        if (!$nid) {
            return FALSE;
        }
        if (gofast_book_is_article_homepage($nid)) {
            return FALSE;
        }
        $descendant->link_path = "/node/" . $nid;
        $descendant->edit_link = "/modal/nojs/article/" . $nid . "/edit";
        $descendant->weight = gofast_book_get_articles_weights([$nid])[0]->body_summary;
    }
    if ($descendant->isFolder && empty($descendant->children)) {
        return FALSE;
    }
    if ($descendant->isFolder && !empty($descendant->children)) {
        $children = [];
        foreach($descendant->children as $descendant_child) {
            $descendant->nested = TRUE;
            $descendant_child = gofast_book_format_article_from_alfresco_api_descendant($descendant_child, $descendant);
            gofast_book_format_article_handle_subwikis($descendant_child, $children);
        }
        // sort by weights
        usort($children, function($a, $b) {
            return (int) $a->weight <=> $b->weight;
        });
        $descendant->children = $children;
    }
    if ($parent->nested) {
        $descendant->description =  t("This wiki article belongs to the sub-wiki @wiki", array("@wiki" => $parent->name), array("context" => "gofast:gofast:book"));
    } else {
        $descendant->description = t("This wiki article belongs to the space @space", array("@space" => $parent->name), array("context" => "gofast:gofast:book"));
    }
    return $descendant;
}

// log multifiled articles
function gofast_book_log_multifiled_articles($label = "") {
    $fileName = "gofast_wikis.log";
    $logFile = fopen(DRUPAL_ROOT . "/sites/default/files/logs/$fileName", 'a');
    $stringLabel = "-----------------------------------------------------\n";
    $stringLabel .= $label . "\n";
    $stringLabel .= "-----------------------------------------------------\n";
    fwrite($logFile, $stringLabel);
    fclose($logFile);
}

function gofast_book_get_articles_weights($nids, $fromAjax = FALSE) {
    if (is_numeric($nids)) {
        $nids = [$nids];
    }
    $weights = db_select("field_data_body", "b")
        ->fields("b", array("body_summary", "entity_id"))
        ->condition("entity_id", array($nids))
        ->orderBy("body_summary", "ASC")
        ->execute()->fetchAll();
    if ($fromAjax) {
        drupal_json_output($weights);
        exit();
    }
    return $weights;
}

// set weight to $weight_value for menu link id $mlid
function gofast_book_set_weight($entity_id, $weight_value) {
    $item = db_select("field_data_body", "b")
        ->fields("b", array("body_summary"))
        ->condition("b.entity_id", $entity_id)
        ->execute()->fetchAll();
    if (!empty($item)) {
        db_query("UPDATE {field_data_body} SET body_summary = :weight WHERE entity_id = :entity_id", array(':weight' => $weight_value, ':entity_id' => $entity_id));
    } else {
        $node = node_load($entity_id);
        $node->body[LANGUAGE_NONE][0]['summary'] = $weight_value;
        field_attach_update("node", $node);
    }
}

  
/**
 * reset book weights to give room to another wiki article insert, return available weight value for target
 * @param array $book_content minimal book content returned by gofast_book_get_book_by_gid
 * @param int $target_location_nid nid for the article after which to insert, "start" if we insert at the beginning
 * @return int
 */
function gofast_book_reset_weights($book_content, $target_location_nid) {
    // the counter is used to give a unique weight to each menu link
    // we really want to have some predictable weights, so we assume it will always start by the minimal value
    $counter = 1;

    if ($target_location_nid == "start") {
        $new_weight = $counter;
        $counter++;
    }
    foreach ($book_content as $content) {
        // if the weight of the current article is not predictable, set it to a predictable incremental value
        if($content->weight != $counter) {
            gofast_book_set_weight($content->nid, $counter);
        }
        if ($content->nid == $target_location_nid) {
            // we increment twice the counter, so between the two increments we have a gap of one to leave room to new article weight
            $counter++;
            $new_weight = $counter;
        }
        $counter++;
    }
    return $new_weight;
}

function gofast_book_api_reset_weights($nid) {
    // only internal requests are authorized
    if($_SERVER['REMOTE_ADDR'] !== "127.0.0.1" && $_SERVER['REMOTE_ADDR'] !== "localhost" && $_SERVER['REMOTE_ADDR'] !== "::1"){
        drupal_access_denied();
        exit;
    }
    usurp(1);
    $source_path = FALSE;
    $target_path = FALSE;
    if (isset($_GET["source_path"]) && isset($_GET["target_path"])) {
        $source_path = gofast_xss_clean($_GET["source_path"]);
        $source_path = "/Sites" . explode("/Sites", $source_path)[1];
        $target_path = gofast_xss_clean($_GET["target_path"]);
        $target_path = "/Sites" . explode("/Sites", $target_path)[1];
    }
    if (!$source_path || !$target_path) {
        drupal_json_output("KO");
        usurp(FALSE);
        exit();
    }
    // remove from source wiki
    $source_book_content = gofast_book_get_minimal_book_by_gid(NULL, FALSE, $source_path, TRUE);
    $counter = 1;
    foreach ($source_book_content as $content) {
        // remove moved item from source path
        if ($content->nid == $nid) {
            continue;
        }
        // book is already ordered by weight so if the value is not predictable, something is wrong and the weight has to be renormalized again
        if($content->weight != $counter) {
            gofast_book_set_weight($content->nid, $counter);
        }
        $counter++;
    }
    $target_book_content = gofast_book_get_minimal_book_by_gid(NULL, FALSE, $target_path, TRUE);
    $counter = 1;
    foreach ($target_book_content as $content) {
        // book is already ordered by weight so if the value is not predictable, something is wrong and the weight has to be renormalized again
        if($content->weight != $counter) {
            gofast_book_set_weight($content->nid, $counter);
        }
        $counter++;
    }
    // add moved item at the end of target path
    gofast_book_set_weight($nid, $counter);
    usurp(FALSE);
    drupal_json_output("OK");
    exit();
}