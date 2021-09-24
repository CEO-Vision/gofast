<?php
/**
 * @file
 * gofast_features_global.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gofast_features_global_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'gofast_audit_nid';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ceo_vision_audit';
  $view->human_name = 'gofast_audit_nid';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'GoFAST Audit';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'plus';
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Appliquer';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Réinitialiser';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Trier par';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['total_pages'] = '2500';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'ldap_user_displayname' => 'ldap_user_displayname',
    'title' => 'title',
    'details' => 'details',
    'event_type' => 'event_type',
    'term_node_tid' => 'term_node_tid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_displayname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'details' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'event_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'term_node_tid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result_1']['id'] = 'result_1';
  $handler->display->display_options['footer']['result_1']['table'] = 'views';
  $handler->display->display_options['footer']['result_1']['field'] = 'result';
  $handler->display->display_options['footer']['result_1']['content'] = '<br />Export : The export is limited to a maximum 5 000 results';
  /* Relationship: CEO-Vision Audit: Node content */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: CEO-Vision Audit: User content */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: CEO-Vision Audit: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  /* Field: User: Lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'uid';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  /* Field: User: Firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'uid';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '50';
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  /* Field: CEO-Vision Audit: Details */
  $handler->display->display_options['fields']['details']['id'] = 'details';
  $handler->display->display_options['fields']['details']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['fields']['details']['field'] = 'details';
  $handler->display->display_options['fields']['details']['element_label_colon'] = FALSE;
  /* Field: CEO-Vision Audit: Event type */
  $handler->display->display_options['fields']['event_type']['id'] = 'event_type';
  $handler->display->display_options['fields']['event_type']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['fields']['event_type']['field'] = 'event_type';
  /* Field: Content: All taxonomy terms */
  $handler->display->display_options['fields']['term_node_tid']['id'] = 'term_node_tid';
  $handler->display->display_options['fields']['term_node_tid']['table'] = 'node';
  $handler->display->display_options['fields']['term_node_tid']['field'] = 'term_node_tid';
  $handler->display->display_options['fields']['term_node_tid']['relationship'] = 'nid';
  $handler->display->display_options['fields']['term_node_tid']['label'] = 'Vocabulary';
  $handler->display->display_options['fields']['term_node_tid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['term_node_tid']['limit'] = TRUE;
  $handler->display->display_options['fields']['term_node_tid']['vocabularies'] = array(
    'category' => 'category',
    'forums' => 0,
    'criticity' => 0,
    'format' => 0,
    'hobbies' => 0,
    'interests' => 0,
    'skills' => 0,
    'state' => 0,
    'tags' => 0,
    'userpoints' => 0,
  );
  /* Sort criterion: CEO-Vision Audit: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: CEO-Vision Audit: Timestamp */
  $handler->display->display_options['filters']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['filters']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['operator'] = 'between';
  $handler->display->display_options['filters']['timestamp']['group'] = 1;
  $handler->display->display_options['filters']['timestamp']['exposed'] = TRUE;
  $handler->display->display_options['filters']['timestamp']['expose']['operator_id'] = 'timestamp_op';
  $handler->display->display_options['filters']['timestamp']['expose']['label'] = 'Date ( jj-mm-aaaa ), from';
  $handler->display->display_options['filters']['timestamp']['expose']['operator'] = 'timestamp_op';
  $handler->display->display_options['filters']['timestamp']['expose']['identifier'] = 'timestamp';
  $handler->display->display_options['filters']['timestamp']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'nid';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Document title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Display name (ldap_user_displayname) */
  $handler->display->display_options['filters']['ldap_user_displayname_value']['id'] = 'ldap_user_displayname_value';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['field'] = 'ldap_user_displayname_value';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['relationship'] = 'uid';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['operator'] = 'word';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['group'] = 1;
  $handler->display->display_options['filters']['ldap_user_displayname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_displayname_value']['expose']['operator_id'] = 'ldap_user_displayname_value_op';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['expose']['label'] = 'Display name';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['expose']['operator'] = 'ldap_user_displayname_value_op';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['expose']['identifier'] = 'ldap_user_displayname_value';
  $handler->display->display_options['filters']['ldap_user_displayname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: CEO-Vision Audit: Event type */
  $handler->display->display_options['filters']['event_type']['id'] = 'event_type';
  $handler->display->display_options['filters']['event_type']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['filters']['event_type']['field'] = 'event_type';
  $handler->display->display_options['filters']['event_type']['group'] = 1;
  $handler->display->display_options['filters']['event_type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['event_type']['expose']['operator_id'] = 'event_type_op';
  $handler->display->display_options['filters']['event_type']['expose']['label'] = 'Event type';
  $handler->display->display_options['filters']['event_type']['expose']['operator'] = 'event_type_op';
  $handler->display->display_options['filters']['event_type']['expose']['identifier'] = 'event_type';
  $handler->display->display_options['filters']['event_type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Has taxonomy terms (with depth) */
  $handler->display->display_options['filters']['term_node_tid_depth']['id'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['table'] = 'node';
  $handler->display->display_options['filters']['term_node_tid_depth']['field'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['relationship'] = 'nid';
  $handler->display->display_options['filters']['term_node_tid_depth']['exposed'] = TRUE;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator_id'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['label'] = 'Possède les termes de taxonomie';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['operator'] = 'term_node_tid_depth_op';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['identifier'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['term_node_tid_depth']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['filters']['term_node_tid_depth']['group_info']['label'] = 'Possède les termes de taxonomie (avec profondeur)';
  $handler->display->display_options['filters']['term_node_tid_depth']['group_info']['identifier'] = 'term_node_tid_depth';
  $handler->display->display_options['filters']['term_node_tid_depth']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['term_node_tid_depth']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  $handler->display->display_options['filters']['term_node_tid_depth']['type'] = 'select';
  $handler->display->display_options['filters']['term_node_tid_depth']['vocabulary'] = 'category';
  $handler->display->display_options['filters']['term_node_tid_depth']['depth'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'gofast_audit/%';
  $handler->display->display_options['menu']['title'] = 'Audit';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5000';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'xls';
  $handler->display->display_options['path'] = 'gofast_audit_xls';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $translatables['gofast_audit_nid'] = array(
    t('Master'),
    t('GoFAST Audit'),
    t('plus'),
    t('Appliquer'),
    t('Réinitialiser'),
    t('Trier par'),
    t('Asc'),
    t('Desc'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
    t('Displaying @start - @end of @total'),
    t('<br />Export : The export is limited to a maximum 5 000 results'),
    t('Node id in this table that references a node.'),
    t('User id in this table that references a node.'),
    t('Date'),
    t('Title'),
    t('Details'),
    t('Event type'),
    t('Vocabulary'),
    t('All'),
    t('Date ( jj-mm-aaaa ), from'),
    t('Document title'),
    t('Display name'),
    t('Possède les termes de taxonomie'),
    t('Possède les termes de taxonomie (avec profondeur)'),
    t('Page'),
    t('more'),
    t('Feed'),
  );
  $export['gofast_audit_nid'] = $view;

  return $export;
}
