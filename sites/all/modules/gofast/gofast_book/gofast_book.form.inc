<?php
function gofast_book_location_form($form, &$form_state) {
    if (!isset($form_state["build_info"]["args"][0]) || !is_object($form_state["build_info"]["args"][0])) {
        drupal_set_message(t("An error occurred while handling article informations", array(), array("context" => "gofast:gofast_book")), "error");
        $form_state['executed'] = TRUE;
        return;
    }

    $node = $form_state["build_info"]["args"][0];
    $parent_wiki_nid = gofast_book_get_parent_nid($node->nid);
    $parent_wiki_name = str_replace(".html", "", gofast_get_node_title($parent_wiki_nid));

    $form['target'] = [
        '#attributes' => [
            'id' => 'wiki_tree_location_input',
        ],
        "#type" => 'hidden',
        '#value' => $parent_wiki_nid,
    ];

    $form['page_selector'] = array(
        '#type' => 'select',
        '#title' => t('Number / Position in Wiki Book'),
        '#default_value' => 0,
        '#options' => array(
          0 => t('Please select a location'),
        ),
        '#validated' => TRUE,
    );

    gofast_book_render_page_selector($form);

    $form["page_selector"]["#title"] = "<h3>" . t("Change location of @title", array("@title" => $node->title, "@wiki" => $parent_wiki_name), array("context" => "gofast:gofast_book")) . "</h3>";

    $book_content = gofast_book_get_minimal_book_by_gid($parent_wiki_nid);
    $form['source_book_content'] = array(
        '#type' => 'hidden',
        '#value'=> json_encode($book_content)
    );
    $form['weights']["#value"] = json_encode($book_content);

    $form['template_markup'] = array(
        '#markup' => theme("gofast_book_tree_widget")
    );

    unset($form['page_selector']['#options'][0]);
    $form['page_selector']['#options']['start'] = "W000 - " . t("Insert at the start of the wiki", array(), array("context" => "gofast:gofast_book"));
    $book_page_counter = 0;
    foreach ($book_content as $book_article) {
        $book_page_counter++;
        $padded_page_counter = str_pad($book_page_counter, 3, "0", STR_PAD_LEFT);
        $form["page_selector"]['#options'][$book_article->nid] = "W" . $padded_page_counter . " - " . t("Insert after the page", array(), array("context" => "gofast:gofast_book")) . " " . $book_article->name;
    }
    $form['page_selector']['#default_value'] = $node->nid;

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#attributes' => array(
            'class' => array('btn', 'btn-success'),
        ),
    );
    $form['actions']['cancel'] = array(
        '#value' => t("Cancel"),
        "#type" => "button",
        '#attributes' => array(
            'class' => array('btn', 'btn-secondary'),
            'id' => 'edit-cancel',
        ),
        '#weight' => '20',
    );
    $form['#validate'] = ['gofast_book_location_form_validate'];
    $form['#submit'] = ['gofast_book_location_form_submit'];
    return $form;
}

function gofast_book_location_form_validate($form, $form_state) {
  $location_value = gofast_xss_clean($form_state['input']['target']);
  $node = $form_state["build_info"]["args"][0];

  if ($location_value == $node->nid) {
    form_set_error('book', t('A sub-wiki parent cannot be moved inside its own sub-wiki', array(), array("context" => "gofast:gofast_book")));
  }
}

function gofast_book_location_form_submit($form, &$form_state) {
    $node = node_load($form_state["build_info"]["args"][0]->nid);
    
    $parent_location_nid = gofast_xss_clean($form_state['input']['target']);
    $parent_node = node_load($parent_location_nid);
    
    gofast_book_subwiki_handle_move($node->nid, $parent_node->nid);

    // Update weights
    $target_location_nid = $form_state['values']['page_selector'];
    $source_book_content = json_decode($form_state['input']['source_book_content']);
    $target_book_content = json_decode($form_state['input']['weights']);
    // Remove now moved wiki article from source book data
    foreach ($source_book_content as $key => $content) {
      if ($node->nid == $content->nid) {
        unset($book_content[$key]);
        break;
      }
    }
    // set weights in target location
    $new_weight = gofast_book_reset_weights($target_book_content, $target_location_nid);
    // renormalize weights of source book as well
    gofast_book_reset_weights($source_book_content, FALSE);

    // update node to make sure the field change is persistent
    $node->body[LANGUAGE_NONE][0]['summary'] = $new_weight;
    $gid = $parent_node->nid;
    if ($parent_node->type == "article") {
        $gid = $parent_node->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}[LANGUAGE_NONE][0]['target_id'];
    }
    $node->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}[LANGUAGE_NONE][0]['target_id'] = $gid;
    node_save($node);

    drupal_set_message(t('The wiki article position has been updated successfully.', array(), array('context' => 'gofast')));
}
