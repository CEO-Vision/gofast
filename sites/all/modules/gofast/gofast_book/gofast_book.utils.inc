<?php

function gofast_book_is_article_homepage($nid) {
    $query = db_select("field_data_field_is_homepage", "f");
    $query->condition("f.entity_id", $nid);
    $count = $query->countQuery()->execute()->fetchField();
    return $count > 0;
}

// get all articles for given space book with minimal info
function gofast_book_get_book_by_gid($gid, $fromAjax = FALSE) {
    $books = db_query("SELECT * FROM book WHERE bid = :bid AND nid != :bid", array(':bid' => $gid))->fetchAll();
    foreach($books as $key => $book) {
        if(gofast_book_is_article_homepage($book->nid)) {
            unset($books[$key]);
            continue;
        }
        $books[$key]->title = gofast_get_node_title($book->nid);
        $book_weight = db_query("SELECT {weight}, {link_path} FROM {menu_links} WHERE mlid = :mlid", array(':mlid' => $book->mlid))->fetchAll();
        $books[$key]->link_path = $book_weight[0]->link_path;
        $books[$key]->weight = $book_weight[0]->weight;
    }
    // sort by weights
    usort($books, function($a, $b) {
        return (int) $a->weight <=> $b->weight;
    });
    if ($fromAjax) {
        drupal_json_output($books);
        drupal_exit();
    }
    return $books;
}

function gofast_book_get_articles_with_emplacements_query($filter = []) {
    $articles = db_select('node', 'n');
    $articles->leftJoin('field_data_field_emplacement', 'e', 'n.nid = e.entity_id');
    $articles = $articles->fields('n', array('nid'))->fields('e', array('field_emplacement_value'))->condition('n.type', 'article');

    if (!empty($filter)) {
        $articles = $articles->condition(...$filter);
    } 

    $articles = $articles->execute()->fetchAll();

    $structured_articles = [];
    foreach ($articles as $article) {
        $structured_articles[$article->nid]['emplacements'][] = $article->field_emplacement_value;
    }
    return $structured_articles;
}

// log multifiled articles
function gofast_book_log_multifiled_articles($label = "") {
    $articles = gofast_book_get_articles_with_emplacements_query();
    $fileName = "gofast_wikis.log";
    $logFile = fopen(DRUPAL_ROOT . "/sites/default/files/logs/$fileName", 'a');
    $stringLabel = "-----------------------------------------------------\n";
    $stringLabel .= $label . "\n";
    $stringLabel .= "-----------------------------------------------------\n";
    fwrite($logFile, $stringLabel);
    foreach($articles as $nid => $article) {
        if (count($article['emplacements']) > 1) {
            $currentDate = (new DateTime())->format("Y-m-d H:i:s");
            $stringData = $currentDate . " - Article node n°$nid has multiple emplacements including " . implode(" ; ", $article['emplacements']);
            fwrite($logFile, $stringData . "\n");
        }
    }
    fclose($logFile);
}

// make sure a non-multifiled article is in the space matching its book; if not move it back in the space matching its book
function gofast_book_sync_spaces_to_books() {
    $articles = db_select('node', 'n');
    $articles->leftJoin('field_data_field_main_emplacement', 'm', 'n.nid = m.entity_id');
    $articles->leftJoin('field_data_field_emplacement', 'e', 'n.nid = e.entity_id');
    $articles = $articles
        ->fields('n', array('nid'))
        ->fields('m', array('field_main_emplacement_value'))
        ->fields('e', array('field_emplacement_value'))
        ->condition('n.type', 'article')->execute()->fetchAll();

    $structured_articles = [];
    foreach ($articles as $article) {
        $structured_articles[$article->nid]['emplacements'][] = $article->field_emplacement_value;
    }

    foreach($structured_articles as $nid => $article) {
        // skip multifiled articles
        if (count($article['emplacements']) > 1) { continue; }
        $space_id = gofast_og_get_group_id_from_title_2($article['emplacements'][0], TRUE);
        if (!$space_id) { continue; }
        $book = gofast_cmis_get_book($nid, TRUE);
        if (empty($book)) { continue; }
        if ($space_id != $book[0]->bid) {
            gofast_book_move_article_to_space($nid, $book[0]->bid);
        }
    }
}

// move the $nid article into the $gid space, Alfresco-side as well as Drupal-side, making sure it's moved into the Wikis folder
function gofast_book_move_article_to_space($nid, $gid) {
    $space_wikis_folder = gofast_cmis_space_get_webdav_path($gid) . "/Wikis";
    if ($space_wikis_folder === "/Sites/Wikis") {
        return;
    }
    $article = node_load($nid);
    $space_wikis_folder_id = gofast_cmis_item_get_by_path($space_wikis_folder)->id;

    // delete and insert again in the right folder
    gofast_cmis_node_delete($article);
    $mimetype = "text/html";
    $article_content = isset($article->body[LANGUAGE_NONE][0]['value']) ? $article->body[LANGUAGE_NONE][0]['value'] : "";
    $article_title = $article->title;
    $inserted_article = gofast_cmis_item_content_insert($space_wikis_folder_id, $article_title, $article_content, $mimetype, array(), TRUE);
    $article_reference = $inserted_article->properties['alfcmis:nodeRef'];
    // update Drupal-side
    $article->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] = $article_reference;
    $article->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE][0]['value'] = $space_wikis_folder;
    $article->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['value'] = $space_wikis_folder;
    $article->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]['safe_value'] = $space_wikis_folder;
    $ruid = $article->revision_uid;
    $article = gofast_prepare_node_save_technically($article);
    node_save($article);
    db_update('node_revision')
    ->fields(array('uid' => $ruid))
    ->condition('nid', $article->nid)
    ->execute();

    // create space book if not exists, update book-related fields
    $space_book = gofast_cmis_get_book($gid);
    if (empty($space_book)) {
        gofast_cmis_create_space_book($gid);
        $space_book = gofast_cmis_get_book($gid);
    }
    $pages[] = ['nid' => $nid, 'bid' => $gid, 'plid' => $space_book[0]->mlid];
    gofast_book_add_pages($pages);
}

// get articles emplacements outside "/Wikis" subfolders
function gofast_book_get_orphan_articles() {
    return gofast_book_get_articles_with_emplacements_query(['e.field_emplacement_value', '%/Wikis', 'NOT LIKE']);

}

// move article into "/Wikis" subfolder, make book from space if not exists, add article to book
function gofast_bookify_article($nid) {
    $query_space = db_query("SELECT gid FROM og_membership LEFT JOIN node ON og_membership.entity_type = 'node' AND og_membership.etid = node.nid AND og_membership.field_name = 'og_group_content_ref' WHERE node.nid = :nid", array(":nid" => $nid));
    $gid = 0;
    $full_space = new stdClass();
    foreach($query_space as $space) {
        $gid = $space->gid;
        $full_space = node_load($gid);
        // we keep "/Wikis" in private spaces but not in root spaces
        if (gofast_og_is_root_space($full_space) || $gid == 1) {
            return;
        }
        break;
    }
    if ($gid == 0) {
        return;
    }
    gofast_book_move_article_to_space($nid, $gid);
}

// put orphan articles in the right place and in the right book; if article is multifiled, ignore it
function gofast_book_handle_orphans() {
    $orphan_articles = gofast_book_get_orphan_articles();
    foreach ($orphan_articles as $nid => $orphan) {
        // multifiled, we don't take the risk to handle it automatically
        if (count($orphan['emplacements']) > 1) {
            continue;
        }
        // not multifiled
        gofast_bookify_article($nid);
    }
}

// check if the "/Wikis" folder of a space already has some content inside
function gofast_book_get_wiki_content($gid, $fromAjax = FALSE) {
    $wikis_path = gofast_cmis_space_get_webdav_path($gid) . "/Wikis";
    $wikis_item = gofast_cmis_item_get_by_path($wikis_path);
    if (!isset($wikis_item->id)) {
        return [];
    }
    $wikis_descendants = (array) gofast_cmis_webservice_item_get_descendants($wikis_item->id, "documents", false, true);
    if ($fromAjax) {
        drupal_json_output($wikis_descendants);
        drupal_exit();
    }
    return $wikis_descendants;
}

// $targets is an array of ['nid' => 'nid_value', 'bid' => 'bid_value', 'mlid' => 'mlid_value']
function gofast_book_add_pages($targets) {
    // handle missing books pages
    foreach ($targets as $target) {
        $target_node = node_load($target['nid']);
        if (!$target_node) {
            continue;
        }
        $ruid = $target_node->revision_uid;
        $target_node->book = array();
        $target_node->book['bid'] = $target['bid'];
        $target_node->book['plid'] = $target['plid'];
        $target_node = gofast_prepare_node_save_technically($target_node);
        node_save($target_node);
        db_update('node_revision')
            ->fields(array('uid' => $ruid))
            ->condition('nid', $target['nid'])
            ->execute();
    }
}

function gofast_bookify_spaces($handle_articles = TRUE) {
    // get all spaces
    $spaces = db_select('node', 'n')
        ->fields('n', array('nid'))
        ->condition('n.type', ['private_space', 'group', 'organisation', 'extranet', 'public'], 'IN')
        ->execute()
        ->fetchCol();
    // init target list
    $must_update_articles = [];
    // handle missing spaces books and targets missing books pages
    foreach($spaces as $gid) {
        $space = node_load($gid);
        if (gofast_og_is_root_space($space) || $gid == 1) {
            continue;
        }
        // make sure all existing spaces have their homepages
        if (!gofast_og_get_article_homepage_from_og($gid)) {
            gofast_og_add_article_homepage($space);
        }
        $wiki_content = gofast_book_get_wiki_content($gid);
        // if the space has no book but already has some wiki content, we create the book
        $space_book = gofast_cmis_get_book($gid);
        if (count($wiki_content) > 0 && empty($space_book)) {
            gofast_cmis_create_space_book($gid);
            $space_book = gofast_cmis_get_book($gid);
        }
        if (count($wiki_content) > 0) {
            foreach($wiki_content as $content) {
                // we add the article in the target list only if it is not already in the space book
                empty(gofast_cmis_get_book($content->nid, TRUE)) && $must_update_articles[] = ['nid' => $content->nid, 'bid' => $gid, 'plid' => $space_book[0]->mlid];
            }
        }
    }
    // handle missing books pages
    if ($handle_articles) {
        gofast_book_add_pages($must_update_articles);
    }
}

// set weight to $weight_value for menu link id $mlid
function gofast_book_set_weight($mlid, $weight_value) {
    db_query("UPDATE {menu_links} SET weight = :weight WHERE mlid = :mlid", array(':weight' => $weight_value, ':mlid' => $mlid));
  }
  
/**
 * reset book weights to give room to another wiki article insert, return available weight value for target
 * @param array $book_content minimal book content returned by gofast_book_get_book_by_gid
 * @param int $target_location_nid nid for the article after which to insert, "start" if we insert at the beginning
 * @return int in the -128 / 127 range
 */
function gofast_book_reset_weights($book_content, $target_location_nid) {
    // the counter is used to give a unique weight to each menu link
    // we really want to have some predictable weights, so we assume it will always start by the minimal value
    $counter = -128;
    $new_weight = -128;
    foreach ($book_content as $content) {
        if ($target_location_nid == "start") {
            $counter++;
            continue;
        }
        // if the weight of the current article is not predictable, set it to a predictable incremental value
        if($content->weight != $counter) {
            gofast_book_set_weight($content->mlid, $counter);
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

/**
 * Retreive and reset Alfresco reference for the given wiki
 * WARNING !! => Also republish node if it was unpublished
 * @param Node $node
 * @return boolean
 */
function gofast_book_wiki_repare_alf_reference($node){
  
  $fixed = FALSE;

  //retreive reference
  $alf_ref = gofast_cmis_node_get_reference_by_nid($node->nid);
  if ($alf_ref !== FALSE) {
    
      //fix wiki
      $_POST['technically_save'] = TRUE;
      $node->technically_save = TRUE;
      $node->technically_changed = $node->changed;
      $node->status = 1; //be sure to publish wiki, cause some might have been unpublished due to empty alfref)
      $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] = $alf_ref;
      field_attach_update('node', $node); // no hook_field_update()
      node_save($node);
      entity_get_controller('node')->resetCache([$node->nid]);
     
    $fixed = TRUE;
    watchdog('gofast_book', '%name() FIXED : Added missing link to Alfresco item(%alf_ref) to wiki(%nid)', array('%name' => __FUNCTION__, '%alf_ref' => $alf_ref, '%nid' => $node->nid));
  } else {
    $fixed = FALSE;
    watchdog('gofast_book', '%name() COULD NOT BE FIXED : No Alfresco item (or too much) found for wiki(%nid)', array('%name' => __FUNCTION__, '%nid' => $node->nid));
  }

  return $fixed;
}


/**
 * Retreive and reset field_emplacement / main_field_emplacment for the given wiki
 * @param type $node
 * @param type $parents
 */
function gofast_book_repare_emplacements($node, $parents) {

  watchdog('gofast_book', '%name() -- START RESETTING emplacements for wiki(%nid)', array('%name' => __FUNCTION__, '%nid' => $node->nid));

  $_POST['technically_save'] = TRUE;
  $node->technically_save = TRUE;
  $node->technically_changed = $node->changed;
  $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE] = $parents;
  field_attach_update('node', $node); // no hook_field_update()
  entity_get_controller('node')->resetCache([$node->nid]);
  watchdog('gofast_book', '%name() - field_emplacement : RESET for wiki(%nid)', array('%name' => __FUNCTION__, '%nid' => $node->nid));

  //check if main_emplacement is correct or not ( check if it exists into emplacements )
  $main_emplacement_exists = false;
  foreach ($node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE] as $emplacement) {
    if ($emplacement["value"] == $node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]["value"]) {
      $main_emplacement_exists = true;
      watchdog('gofast_book', '%name() - field_main_emplacement : OK (do nothing)  for wiki(%nid)', array('%name' => __FUNCTION__, '%nid' => $node->nid));
    }
  }

  if ($main_emplacement_exists == false) {
    $node->{GOFAST_CMIS_MAIN_LOCATION_FIELD}[LANGUAGE_NONE][0]["value"] = $node->{GOFAST_CMIS_LOCATIONS_FIELD}[LANGUAGE_NONE][0]["value"];
    field_attach_update('node', $node); // no hook_field_update()
    entity_get_controller('node')->resetCache([$node->nid]);

    watchdog('gofast_book', '%name() - field_main_emplacement : RESET (null or wrong value) for wiki(%nid)', array('%name' => __FUNCTION__, '%nid' => $node->nid));
  }
}
