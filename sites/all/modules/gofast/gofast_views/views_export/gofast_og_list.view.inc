$view = new view();
$view->name = 'gofast_og_list';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'gofast_og_list';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Spaces';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '90';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['row_class'] = 'col-md-2';
$handler->display->display_options['style_options']['columns'] = '2';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: OG membership: OG membership from Node group */
$handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
$handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
$handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
/* Relationship: OG membership: Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node']['id'] = 'og_membership_related_node';
$handler->display->display_options['relationships']['og_membership_related_node']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node']['field'] = 'og_membership_related_node';
$handler->display->display_options['relationships']['og_membership_related_node']['relationship'] = 'og_membership_rel_group';
/* Relationship: OG membership: User from OG membership */
$handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['relationship'] = 'og_membership_rel_group';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = 'Group';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
/* Field: Content: All taxonomy terms */
$handler->display->display_options['fields']['term_node_tid']['id'] = 'term_node_tid';
$handler->display->display_options['fields']['term_node_tid']['table'] = 'node';
$handler->display->display_options['fields']['term_node_tid']['field'] = 'term_node_tid';
$handler->display->display_options['fields']['term_node_tid']['label'] = 'Type';
$handler->display->display_options['fields']['term_node_tid']['vocabularies'] = array(
  'forums' => 0,
  'format' => 0,
  'hobbies' => 0,
  'interests' => 0,
  'skills' => 0,
  'state' => 0,
  'tags' => 0,
  'userpoints' => 0,
);
/* Field: Content: Description */
$handler->display->display_options['fields']['field_description']['id'] = 'field_description';
$handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
$handler->display->display_options['fields']['field_description']['field'] = 'field_description';
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = 'Manager';
/* Field: COUNT(Content: Title) */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node';
$handler->display->display_options['fields']['title_1']['group_type'] = 'count';
$handler->display->display_options['fields']['title_1']['label'] = 'contributions';
/* Field: Content: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'node';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
/* Field: COUNT(User: Uid) */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['group_type'] = 'count';
$handler->display->display_options['fields']['uid']['label'] = 'Members';
/* Sort criterion: Content: Type */
$handler->display->display_options['sorts']['type']['id'] = 'type';
$handler->display->display_options['sorts']['type']['table'] = 'node';
$handler->display->display_options['sorts']['type']['field'] = 'type';
$handler->display->display_options['sorts']['type']['order'] = 'DESC';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'group' => 'group',
  'organisation' => 'organisation',
);
/* Filter criterion: Content: Parent Group (og_group_ref) */
$handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
$handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
$handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
$handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';

/* Display: full list */
$handler = $view->new_display('page', 'full list', 'page');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'title' => 'title',
  'type' => 'type',
  'term_node_tid' => 'term_node_tid',
  'field_description' => 'field_description',
  'picture' => 'picture',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'title' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'type' => array(
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
  'field_description' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'picture' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['path'] = 'og/list';

/* Display: list grid */
$handler = $view->new_display('page', 'list grid', 'page_1');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['label'] = '';
$handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
/* Field: Content: Description */
$handler->display->display_options['fields']['field_description']['id'] = 'field_description';
$handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
$handler->display->display_options['fields']['field_description']['field'] = 'field_description';
$handler->display->display_options['fields']['field_description']['label'] = '';
$handler->display->display_options['fields']['field_description']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_description']['type'] = 'text_plain';
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = 'Admin';
$handler->display->display_options['fields']['picture']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
/* Field: COUNT(Content: Title) */
$handler->display->display_options['fields']['title_1']['id'] = 'title_1';
$handler->display->display_options['fields']['title_1']['table'] = 'node';
$handler->display->display_options['fields']['title_1']['field'] = 'title';
$handler->display->display_options['fields']['title_1']['relationship'] = 'og_membership_related_node';
$handler->display->display_options['fields']['title_1']['group_type'] = 'count';
$handler->display->display_options['fields']['title_1']['label'] = 'contributions';
/* Field: COUNT(User: Uid) */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['group_type'] = 'count';
$handler->display->display_options['fields']['uid']['label'] = 'Members';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Sort criterion: Content: Type */
$handler->display->display_options['sorts']['type']['id'] = 'type';
$handler->display->display_options['sorts']['type']['table'] = 'node';
$handler->display->display_options['sorts']['type']['field'] = 'type';
$handler->display->display_options['sorts']['type']['order'] = 'DESC';
/* Sort criterion: Content: Title */
$handler->display->display_options['sorts']['title']['id'] = 'title';
$handler->display->display_options['sorts']['title']['table'] = 'node';
$handler->display->display_options['sorts']['title']['field'] = 'title';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: Content: Type */
$handler->display->display_options['arguments']['type']['id'] = 'type';
$handler->display->display_options['arguments']['type']['table'] = 'node';
$handler->display->display_options['arguments']['type']['field'] = 'type';
$handler->display->display_options['arguments']['type']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['type']['title'] = '%1';
$handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['type']['limit'] = '0';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'group' => 'group',
  'organisation' => 'organisation',
);
/* Filter criterion: Content: Parent Group (og_group_ref) */
$handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
$handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
$handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
$handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type_1']['id'] = 'type_1';
$handler->display->display_options['filters']['type_1']['table'] = 'node';
$handler->display->display_options['filters']['type_1']['field'] = 'type';
$handler->display->display_options['filters']['type_1']['value'] = array(
  'group' => 'group',
  'organisation' => 'organisation',
);
$handler->display->display_options['filters']['type_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
$handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
$handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
$handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['filters']['type_1']['expose']['reduce'] = TRUE;
$handler->display->display_options['filters']['type_1']['group_info']['label'] = 'Type';
$handler->display->display_options['filters']['type_1']['group_info']['identifier'] = 'type_1';
$handler->display->display_options['filters']['type_1']['group_info']['widget'] = 'radios';
$handler->display->display_options['filters']['type_1']['group_info']['remember'] = 1;
$handler->display->display_options['filters']['type_1']['group_info']['group_items'] = array(
  1 => array(
    'title' => 'Group',
    'operator' => 'in',
    'value' => array(
      'group' => 'group',
      'all' => 0,
      'article' => 0,
      'page' => 0,
      'book' => 0,
      'alfresco_item' => 0,
      'forum' => 0,
      'organisation' => 0,
      'private_space' => 0,
      'webform' => 0,
    ),
  ),
  2 => array(
    'title' => 'Organisation',
    'operator' => 'in',
    'value' => array(
      'organisation' => 'organisation',
      'all' => 0,
      'article' => 0,
      'page' => 0,
      'book' => 0,
      'alfresco_item' => 0,
      'forum' => 0,
      'group' => 0,
      'private_space' => 0,
      'webform' => 0,
    ),
  ),
);
/* Filter criterion: Content: Title */
$handler->display->display_options['filters']['title']['id'] = 'title';
$handler->display->display_options['filters']['title']['table'] = 'node';
$handler->display->display_options['filters']['title']['field'] = 'title';
$handler->display->display_options['filters']['title']['operator'] = 'contains';
$handler->display->display_options['filters']['title']['exposed'] = TRUE;
$handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
$handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
$handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
$handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['path'] = 'og/list_grid';
$translatables['gofast_og_list'] = array(
  t('Master'),
  t('Spaces'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Items per page'),
  t('- All -'),
  t('Offset'),
  t('« first'),
  t('‹ previous'),
  t('next ›'),
  t('last »'),
  t('author'),
  t('OG membership from node group'),
  t('node from OG membership'),
  t('user from OG membership'),
  t('Group'),
  t('Type'),
  t('Description'),
  t('Manager'),
  t('contributions'),
  t('Nid'),
  t('Members'),
  t('full list'),
  t('list grid'),
  t('Admin'),
  t('All'),
  t('%1'),
  t('Title'),
);
