$view = new view();
$view->name = 'gofast_private_msg';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'pm_message';
$view->human_name = 'gofast_private_msg';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'subject' => 'subject',
  'recipient' => 'recipient',
  'timestamp' => 'timestamp',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'subject' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'recipient' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'timestamp' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Relationship: Privatemsg: Recipient */
$handler->display->display_options['relationships']['recipient']['id'] = 'recipient';
$handler->display->display_options['relationships']['recipient']['table'] = 'pm_index';
$handler->display->display_options['relationships']['recipient']['field'] = 'recipient';
/* Field: Privatemsg: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'pm_message';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
/* Field: Privatemsg: Recipient */
$handler->display->display_options['fields']['recipient']['id'] = 'recipient';
$handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
$handler->display->display_options['fields']['recipient']['field'] = 'recipient';
$handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
$handler->display->display_options['fields']['recipient']['separator'] = ' ';
/* Field: Broken/missing handler */
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['id'] = 'gofast_views_handler_field_recipients';
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['table'] = 'pm_message';
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['field'] = 'gofast_views_handler_field_recipients';
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['label'] = 'GoFAST pm recipient';
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['element_type'] = 'div';
$handler->display->display_options['fields']['gofast_views_handler_field_recipients']['element_class'] = 'gofast-pm-participants';
/* Field: Privatemsg: Send date */
$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
$handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
/* Field: Privatemsg: Message ID */
$handler->display->display_options['fields']['mid']['id'] = 'mid';
$handler->display->display_options['fields']['mid']['table'] = 'pm_message';
$handler->display->display_options['fields']['mid']['field'] = 'mid';
$handler->display->display_options['fields']['mid']['exclude'] = TRUE;
/* Field: Privatemsg: Author */
$handler->display->display_options['fields']['author']['id'] = 'author';
$handler->display->display_options['fields']['author']['table'] = 'pm_message';
$handler->display->display_options['fields']['author']['field'] = 'author';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Operations';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[mid]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn fa fa-lg fa-trash-o';
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare']['id'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['operator'] = '<>';
$handler->display->display_options['filters']['fields_compare']['right_field'] = 'author';
$handler->display->display_options['filters']['fields_compare']['left_field'] = 'recipient';
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'recipient';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: Privatemsg: Is deleted */
$handler->display->display_options['filters']['deleted']['id'] = 'deleted';
$handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
$handler->display->display_options['filters']['deleted']['field'] = 'deleted';
$handler->display->display_options['filters']['deleted']['value'] = '0';

/* Display: Messages */
$handler = $view->new_display('page', 'Messages', 'gofast_inbox');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Messages';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'You haven\'t got any message.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Privatemsg: Thread ID */
$handler->display->display_options['fields']['thread_id']['id'] = 'thread_id';
$handler->display->display_options['fields']['thread_id']['table'] = 'pm_index';
$handler->display->display_options['fields']['thread_id']['field'] = 'thread_id';
$handler->display->display_options['fields']['thread_id']['exclude'] = TRUE;
/* Field: Privatemsg: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'pm_message';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
$handler->display->display_options['fields']['subject']['alter']['text'] = '<a class="ctools-use-modal" href="gofast/nojs/messages/view/[thread_id]">[subject]</a>';
/* Field: Privatemsg: Recipient */
$handler->display->display_options['fields']['recipient']['id'] = 'recipient';
$handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
$handler->display->display_options['fields']['recipient']['field'] = 'recipient';
$handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
$handler->display->display_options['fields']['recipient']['separator'] = ' ';
/* Field: Gofast Fields: GoFAST pm recipient */
$handler->display->display_options['fields']['gofast_recipients']['id'] = 'gofast_recipients';
$handler->display->display_options['fields']['gofast_recipients']['table'] = 'pm_message';
$handler->display->display_options['fields']['gofast_recipients']['field'] = 'gofast_recipients';
$handler->display->display_options['fields']['gofast_recipients']['element_type'] = 'div';
$handler->display->display_options['fields']['gofast_recipients']['element_class'] = 'gofast-pm-participants';
/* Field: Privatemsg: Send date */
$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
$handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
/* Field: Privatemsg: Message ID */
$handler->display->display_options['fields']['mid']['id'] = 'mid';
$handler->display->display_options['fields']['mid']['table'] = 'pm_message';
$handler->display->display_options['fields']['mid']['field'] = 'mid';
$handler->display->display_options['fields']['mid']['exclude'] = TRUE;
/* Field: Privatemsg: Author */
$handler->display->display_options['fields']['author']['id'] = 'author';
$handler->display->display_options['fields']['author']['table'] = 'pm_message';
$handler->display->display_options['fields']['author']['field'] = 'author';
$handler->display->display_options['fields']['author']['exclude'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Operations';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[mid]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn fa fa-lg fa-trash-o';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare']['id'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['operator'] = '<>';
$handler->display->display_options['filters']['fields_compare']['right_field'] = 'author';
$handler->display->display_options['filters']['fields_compare']['left_field'] = 'recipient';
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'recipient';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
/* Filter criterion: Privatemsg: Is deleted */
$handler->display->display_options['filters']['deleted']['id'] = 'deleted';
$handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
$handler->display->display_options['filters']['deleted']['field'] = 'deleted';
$handler->display->display_options['filters']['deleted']['value'] = '0';
/* Filter criterion: Privatemsg: The pm author ID */
$handler->display->display_options['filters']['author']['id'] = 'author';
$handler->display->display_options['filters']['author']['table'] = 'pm_message';
$handler->display->display_options['filters']['author']['field'] = 'author';
$handler->display->display_options['filters']['author']['operator'] = 'not in';
$handler->display->display_options['filters']['author']['value'] = array(
  0 => '1',
);
/* Filter criterion: Privatemsg: Is new */
$handler->display->display_options['filters']['is_new']['id'] = 'is_new';
$handler->display->display_options['filters']['is_new']['table'] = 'pm_index';
$handler->display->display_options['filters']['is_new']['field'] = 'is_new';
$handler->display->display_options['filters']['is_new']['value'] = 'All';
$handler->display->display_options['filters']['is_new']['exposed'] = TRUE;
$handler->display->display_options['filters']['is_new']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['is_new']['expose']['label'] = 'Show new';
$handler->display->display_options['filters']['is_new']['expose']['operator'] = 'is_new_op';
$handler->display->display_options['filters']['is_new']['expose']['identifier'] = 'is_new';
$handler->display->display_options['filters']['is_new']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Privatemsg: The pm author ID */
$handler->display->display_options['filters']['author_1']['id'] = 'author_1';
$handler->display->display_options['filters']['author_1']['table'] = 'pm_message';
$handler->display->display_options['filters']['author_1']['field'] = 'author';
$handler->display->display_options['filters']['author_1']['value'] = '';
$handler->display->display_options['filters']['author_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['author_1']['expose']['operator_id'] = 'author_1_op';
$handler->display->display_options['filters']['author_1']['expose']['label'] = 'Privatemsg: Author';
$handler->display->display_options['filters']['author_1']['expose']['operator'] = 'author_1_op';
$handler->display->display_options['filters']['author_1']['expose']['identifier'] = 'author_1';
$handler->display->display_options['filters']['author_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Privatemsg: Subject */
$handler->display->display_options['filters']['subject']['id'] = 'subject';
$handler->display->display_options['filters']['subject']['table'] = 'pm_message';
$handler->display->display_options['filters']['subject']['field'] = 'subject';
$handler->display->display_options['filters']['subject']['operator'] = 'contains';
$handler->display->display_options['filters']['subject']['exposed'] = TRUE;
$handler->display->display_options['filters']['subject']['expose']['operator_id'] = 'subject_op';
$handler->display->display_options['filters']['subject']['expose']['label'] = 'Subject';
$handler->display->display_options['filters']['subject']['expose']['operator'] = 'subject_op';
$handler->display->display_options['filters']['subject']['expose']['identifier'] = 'subject';
$handler->display->display_options['filters']['subject']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['path'] = 'pm_test';

/* Display: Notifications */
$handler = $view->new_display('page', 'Notifications', 'gofast_notifications');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Notifications';
$handler->display->display_options['defaults']['empty'] = FALSE;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['empty'] = TRUE;
$handler->display->display_options['empty']['area']['content'] = 'You haven\'t got any notification.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Privatemsg: Subject */
$handler->display->display_options['fields']['subject']['id'] = 'subject';
$handler->display->display_options['fields']['subject']['table'] = 'pm_message';
$handler->display->display_options['fields']['subject']['field'] = 'subject';
/* Field: Privatemsg: Recipient */
$handler->display->display_options['fields']['recipient']['id'] = 'recipient';
$handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
$handler->display->display_options['fields']['recipient']['field'] = 'recipient';
$handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
$handler->display->display_options['fields']['recipient']['separator'] = ' ';
/* Field: Privatemsg: Send date */
$handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
$handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
$handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
$handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
/* Field: Privatemsg: Message ID */
$handler->display->display_options['fields']['mid']['id'] = 'mid';
$handler->display->display_options['fields']['mid']['table'] = 'pm_message';
$handler->display->display_options['fields']['mid']['field'] = 'mid';
$handler->display->display_options['fields']['mid']['exclude'] = TRUE;
/* Field: Privatemsg: Author */
$handler->display->display_options['fields']['author']['id'] = 'author';
$handler->display->display_options['fields']['author']['table'] = 'pm_message';
$handler->display->display_options['fields']['author']['field'] = 'author';
$handler->display->display_options['fields']['author']['exclude'] = TRUE;
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Operations';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[mid]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
$handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn fa fa-lg fa-trash-o';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Global: Fields comparison */
$handler->display->display_options['filters']['fields_compare']['id'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['table'] = 'views';
$handler->display->display_options['filters']['fields_compare']['field'] = 'fields_compare';
$handler->display->display_options['filters']['fields_compare']['operator'] = '<>';
$handler->display->display_options['filters']['fields_compare']['group'] = 1;
$handler->display->display_options['filters']['fields_compare']['right_field'] = 'author';
$handler->display->display_options['filters']['fields_compare']['left_field'] = 'recipient';
/* Filter criterion: Privatemsg: The pm author ID */
$handler->display->display_options['filters']['author']['id'] = 'author';
$handler->display->display_options['filters']['author']['table'] = 'pm_message';
$handler->display->display_options['filters']['author']['field'] = 'author';
$handler->display->display_options['filters']['author']['value'] = array(
  0 => '1',
);
$handler->display->display_options['filters']['author']['group'] = 1;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'recipient';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['filters']['uid_current']['group'] = 1;
/* Filter criterion: Privatemsg: Is deleted */
$handler->display->display_options['filters']['deleted']['id'] = 'deleted';
$handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
$handler->display->display_options['filters']['deleted']['field'] = 'deleted';
$handler->display->display_options['filters']['deleted']['value'] = '0';
$handler->display->display_options['filters']['deleted']['group'] = 1;
/* Filter criterion: Privatemsg: Is new */
$handler->display->display_options['filters']['is_new']['id'] = 'is_new';
$handler->display->display_options['filters']['is_new']['table'] = 'pm_index';
$handler->display->display_options['filters']['is_new']['field'] = 'is_new';
$handler->display->display_options['filters']['is_new']['exposed'] = TRUE;
$handler->display->display_options['filters']['is_new']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['is_new']['expose']['label'] = 'Is new';
$handler->display->display_options['filters']['is_new']['expose']['operator'] = 'is_new_op';
$handler->display->display_options['filters']['is_new']['expose']['identifier'] = 'is_new';
$handler->display->display_options['filters']['is_new']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Privatemsg: Subject */
$handler->display->display_options['filters']['subject']['id'] = 'subject';
$handler->display->display_options['filters']['subject']['table'] = 'pm_message';
$handler->display->display_options['filters']['subject']['field'] = 'subject';
$handler->display->display_options['filters']['subject']['operator'] = 'contains';
$handler->display->display_options['filters']['subject']['exposed'] = TRUE;
$handler->display->display_options['filters']['subject']['expose']['operator_id'] = 'subject_op';
$handler->display->display_options['filters']['subject']['expose']['label'] = 'Subject';
$handler->display->display_options['filters']['subject']['expose']['operator'] = 'subject_op';
$handler->display->display_options['filters']['subject']['expose']['identifier'] = 'subject';
$handler->display->display_options['filters']['subject']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['path'] = 'pm_notifications';
$translatables['gofast_private_msg'] = array(
  t('Master'),
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
  t('Recipient'),
  t('Subject'),
  t('.'),
  t(' '),
  t('GoFAST pm recipient'),
  t('Send date'),
  t('Message ID'),
  t(','),
  t('Author'),
  t('Operations'),
  t('<a href="del_privatemsg" class="delete_message_ajax" id=\'[mid]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>'),
  t('Messages'),
  t('You haven\'t got any message.'),
  t('Thread ID'),
  t('<a class="ctools-use-modal" href="gofast/nojs/messages/view/[thread_id]">[subject]</a>'),
  t('Show new'),
  t('Privatemsg: Author'),
  t('Notifications'),
  t('You haven\'t got any notification.'),
  t('Is new'),
);
