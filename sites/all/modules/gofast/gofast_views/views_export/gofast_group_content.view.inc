$view = new view();
$view->name = 'gofast_group_content';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'gofast_group_content';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'content_status';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'mini';
$handler->display->display_options['pager']['options']['items_per_page'] = '5';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹ ';
$handler->display->display_options['pager']['options']['tags']['next'] = '› › ';
$handler->display->display_options['style_plugin'] = 'table';
/* Relationship: OG membership: Group Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
/* Relationship: OG membership: Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node']['id'] = 'og_membership_related_node';
$handler->display->display_options['relationships']['og_membership_related_node']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node']['field'] = 'og_membership_related_node';
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: State */
$handler->display->display_options['fields']['field_state']['id'] = 'field_state';
$handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
$handler->display->display_options['fields']['field_state']['field'] = 'field_state';
$handler->display->display_options['fields']['field_state']['label'] = 'Status';
$handler->display->display_options['fields']['field_state']['alter']['path'] = 'search/apachesolr_search/*:*?filters=tid:[tid]';
$handler->display->display_options['fields']['field_state']['click_sort_column'] = 'target_id';
$handler->display->display_options['fields']['field_state']['type'] = 'entityreference_label';
$handler->display->display_options['fields']['field_state']['settings'] = array(
  'link' => 0,
);
$handler->display->display_options['fields']['field_state']['group_column'] = 'target_id';
/* Field: Content: Updated/commented date */
$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['label'] = 'Date';
$handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
/* Sort criterion: Content: Popularity (field_popularity:radioactivity_energy) */
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['id'] = 'field_popularity_radioactivity_energy';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['table'] = 'field_data_field_popularity';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['field'] = 'field_popularity_radioactivity_energy';
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: popular content */
$handler = $view->new_display('block', 'popular content', 'block_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'popular_content';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: OG membership: Group Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Popularity */
$handler->display->display_options['fields']['field_popularity_1']['id'] = 'field_popularity_1';
$handler->display->display_options['fields']['field_popularity_1']['table'] = 'field_data_field_popularity';
$handler->display->display_options['fields']['field_popularity_1']['field'] = 'field_popularity';
$handler->display->display_options['fields']['field_popularity_1']['label'] = 'popularity';
$handler->display->display_options['fields']['field_popularity_1']['click_sort_column'] = 'radioactivity_energy';
$handler->display->display_options['fields']['field_popularity_1']['settings'] = array(
  'energy' => '10',
  'type' => 'energy',
  'accuracy' => '100',
);
/* Field: Content: Updated/commented date */
$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['label'] = 'Date';
$handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Sort criterion: Content: Popularity (field_popularity:radioactivity_energy) */
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['id'] = 'field_popularity_radioactivity_energy';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['table'] = 'field_data_field_popularity';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['field'] = 'field_popularity_radioactivity_energy';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['order'] = 'DESC';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['expose']['label'] = 'popularity (field_popularity:radioactivity_energy)';
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: OG membership: Group ID */
$handler->display->display_options['arguments']['gid']['id'] = 'gid';
$handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
$handler->display->display_options['arguments']['gid']['field'] = 'gid';
$handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
$handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['block_description'] = 'popular content';

/* Display: content with status */
$handler = $view->new_display('block', 'content with status', 'block');
$handler->display->display_options['defaults']['pager'] = FALSE;
$handler->display->display_options['pager']['type'] = 'mini';
$handler->display->display_options['pager']['options']['items_per_page'] = '5';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
$handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: OG membership: Group Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
/* Relationship: OG membership: Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node']['id'] = 'og_membership_related_node';
$handler->display->display_options['relationships']['og_membership_related_node']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node']['field'] = 'og_membership_related_node';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: State */
$handler->display->display_options['fields']['field_state']['id'] = 'field_state';
$handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
$handler->display->display_options['fields']['field_state']['field'] = 'field_state';
$handler->display->display_options['fields']['field_state']['label'] = 'Status';
$handler->display->display_options['fields']['field_state']['alter']['path'] = 'search/apachesolr_search/*:*?filters=tid:[tid]';
$handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_plain';
$handler->display->display_options['fields']['field_state']['settings'] = array(
  'link' => 0,
);
$handler->display->display_options['fields']['field_state']['group_column'] = 'target_id';
/* Field: Content: Updated/commented date */
$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['label'] = 'Date';
$handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
$handler->display->display_options['defaults']['sorts'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: OG membership: Group ID */
$handler->display->display_options['arguments']['gid']['id'] = 'gid';
$handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
$handler->display->display_options['arguments']['gid']['field'] = 'gid';
$handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_related_node';
$handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
$handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
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
  'article' => 'article',
  'alfresco_item' => 'alfresco_item',
  'forum' => 'forum',
  'webform' => 'webform',
);
/* Filter criterion: Content: State (field_state) */
$handler->display->display_options['filters']['field_state_tid']['id'] = 'field_state_tid';
$handler->display->display_options['filters']['field_state_tid']['table'] = 'field_data_field_state';
$handler->display->display_options['filters']['field_state_tid']['field'] = 'field_state_tid';
$handler->display->display_options['filters']['field_state_tid']['operator'] = 'not empty';
$handler->display->display_options['filters']['field_state_tid']['value'] = '';
$handler->display->display_options['filters']['field_state_tid']['vocabulary'] = 'state';

/* Display: personal popular content */
$handler = $view->new_display('block', 'personal popular content', 'block_2');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'personal_popular_content';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Popularity */
$handler->display->display_options['fields']['field_popularity_1']['id'] = 'field_popularity_1';
$handler->display->display_options['fields']['field_popularity_1']['table'] = 'field_data_field_popularity';
$handler->display->display_options['fields']['field_popularity_1']['field'] = 'field_popularity';
$handler->display->display_options['fields']['field_popularity_1']['label'] = 'popularity';
$handler->display->display_options['fields']['field_popularity_1']['click_sort_column'] = 'radioactivity_energy';
$handler->display->display_options['fields']['field_popularity_1']['settings'] = array(
  'energy' => '10',
  'type' => 'energy',
  'accuracy' => '100',
);
/* Field: Content: Updated/commented date */
$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['label'] = 'Date';
$handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Sort criterion: Content: Popularity (field_popularity:radioactivity_energy) */
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['id'] = 'field_popularity_radioactivity_energy';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['table'] = 'field_data_field_popularity';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['field'] = 'field_popularity_radioactivity_energy';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['order'] = 'DESC';
$handler->display->display_options['sorts']['field_popularity_radioactivity_energy']['expose']['label'] = 'popularity (field_popularity:radioactivity_energy)';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Content: Published */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'node';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = 1;
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['block_description'] = 'personal popular content';
$translatables['gofast_group_content'] = array(
  t('Master'),
  t('content_status'),
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
  t('‹ ‹ '),
  t('› › '),
  t('last »'),
  t('Group node from OG membership'),
  t('node from OG membership'),
  t('Type'),
  t('Title'),
  t('Status'),
  t('Date'),
  t('popular content'),
  t('popular_content'),
  t('popularity'),
  t('popularity (field_popularity:radioactivity_energy)'),
  t('All'),
  t('content with status'),
  t('‹ ‹'),
  t('› ›'),
  t('personal popular content'),
  t('personal_popular_content'),
  t('author'),
);
