<?php

/**
 * Implements hook_form_alter().
 */
function gofast_search_advanced_form_alter(&$form, &$form_state, $form_id) {
  if ($form['#form_id'] === 'user_profile_form') {
    $form["field_search_history"]["#access"] = 0;
  }
}


function gofast_search_form($form, &$form_state) {

  $form['space'] = array(
    '#type' => 'textfield',
    '#name' => 'ac-list-tags-list-spaces',
    '#title' => t('Space(s)'),
    '#attributes' => array(
      'placeholder' => t('Start entering a space name...'),
      'class' => [' form-control-tags js-tagify text-truncate'],
      'data-get-spaces' => '',
      'data-exclude-root-spaces' => '',
    ),
  );

  $form['content_type'] = array(
    '#type' => 'select',
    '#options' => gofast_search_advanced_get_categories(),
    '#title' => t('Select content category(ies)'),
    '#attributes' => array(
      'placeholder' => t('Start entering a category name...'),
      'multiple' => true,
    ),
  );

  $form['search_label'] = array(
    '#type' => 'textfield',
    '#title' => t('Search'),
    '#attributes' => array(
      'placeholder' => t('Enter search...'),
    ),
  );

  return $form;
}


function gofast_search_advanced_history_clear_confirm_form($form, &$form_state){
  $form['confirm_clear_label'] = array(
    '#type' => 'item',
    '#markup' => t("Are you sure you want to delete the advanced search history ?"),
  );

  $form['submit'] = array(
    '#type' => 'submit',
     '#value' => t('Delete history'),
     "#attributes" => array(
       'class' => array("btn btn-success")
     )
  );
  return $form;
}

function gofast_search_advanced_history_clear_confirm_form_submit($form, &$form_state){

  // Clear history
  gofast_search_advanced_history_clear();
}
