$view = new view();
$view->name = 'gofast_userlist_directory';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'node';
$view->human_name = 'gofast_userlist_directory';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Userlists';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  5 => '5',
);
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['row_class'] = 'col-md-2';
$handler->display->display_options['style_options']['columns'] = '2';
$handler->display->display_options['row_plugin'] = 'fields';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = '';
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
/* Field: Content: Description */
$handler->display->display_options['fields']['field_description']['id'] = 'field_description';
$handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
$handler->display->display_options['fields']['field_description']['field'] = 'field_description';
/* Field: Content: Author uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'node';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
/* Field: Content: userlist_ulid */
$handler->display->display_options['fields']['field_userlist_ulid']['id'] = 'field_userlist_ulid';
$handler->display->display_options['fields']['field_userlist_ulid']['table'] = 'field_data_field_userlist_ulid';
$handler->display->display_options['fields']['field_userlist_ulid']['field'] = 'field_userlist_ulid';
$handler->display->display_options['fields']['field_userlist_ulid']['label'] = '';
$handler->display->display_options['fields']['field_userlist_ulid']['element_type'] = '0';
$handler->display->display_options['fields']['field_userlist_ulid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['field_userlist_ulid']['element_default_classes'] = FALSE;
$handler->display->display_options['fields']['field_userlist_ulid']['type'] = 'number_unformatted';
$handler->display->display_options['fields']['field_userlist_ulid']['settings'] = array(
  'thousand_separator' => '',
  'prefix_suffix' => 1,
);
/* Sort criterion: Content: Title */
$handler->display->display_options['sorts']['title']['id'] = 'title';
$handler->display->display_options['sorts']['title']['table'] = 'node';
$handler->display->display_options['sorts']['title']['field'] = 'title';
/* Filter criterion: Content: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'node';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['value'] = array(
  'userlist' => 'userlist',
);
$handler->display->display_options['filters']['type']['group'] = 1;

/* Display: Userlists */
$handler = $view->new_display('page', 'Userlists', 'userlist_page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'role';
$handler->display->display_options['access']['role'] = array(
  3 => '3',
  5 => '5',
);
$handler->display->display_options['path'] = 'userlists';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Directory';
$handler->display->display_options['menu']['description'] = 'User\'s directory';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
$translatables['gofast_userlist_directory'] = array(
  t('Master'),
  t('Userlists'),
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
  t('Description'),
  t('Author uid'),
);
