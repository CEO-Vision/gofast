$view = new view();
$view->name = 'gofast_og_members_admin';
$view->description = '';
$view->tag = 'og';
$view->base_table = 'users';
$view->human_name = 'GoFast OG members admin';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'OG members admin';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'none';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'id' => 'id',
  'gid' => 'gid',
  'views_bulk_operations' => 'views_bulk_operations',
  'picture' => 'picture',
  'name' => 'name',
  'state' => 'state',
  'og_roles' => 'og_roles',
  'created' => 'created',
  'og_membership_request' => 'og_membership_request',
  'delete_membership' => 'delete_membership',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'gid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'views_bulk_operations' => array(
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
  'name' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'state' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'og_roles' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'created' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'og_membership_request' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
  'delete_membership' => array(
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
/* Header: OG membership: Group membership overview */
$handler->display->display_options['header']['og_membership_overview']['id'] = 'og_membership_overview';
$handler->display->display_options['header']['og_membership_overview']['table'] = 'og_membership';
$handler->display->display_options['header']['og_membership_overview']['field'] = 'og_membership_overview';
$handler->display->display_options['header']['og_membership_overview']['manager'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_members_1'] = 0;
$handler->display->display_options['header']['og_membership_overview']['total_members_2'] = 0;
$handler->display->display_options['header']['og_membership_overview']['total_members_3'] = 0;
$handler->display->display_options['header']['og_membership_overview']['total_members'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_content'] = 1;
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['content'] = 'No people found matching the search criteria.';
$handler->display->display_options['empty']['area']['format'] = 'filtered_html';
/* Relationship: OG membership: OG membership from User */
$handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
$handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
$handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: OG membership: Group ID */
$handler->display->display_options['fields']['gid']['id'] = 'gid';
$handler->display->display_options['fields']['gid']['table'] = 'og_membership';
$handler->display->display_options['fields']['gid']['field'] = 'gid';
$handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['gid']['label'] = '';
$handler->display->display_options['fields']['gid']['exclude'] = TRUE;
$handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gid']['separator'] = '';
/* Field: Bulk operations: OG membership */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'og_membership';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
  'action::views_bulk_operations_delete_item' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_delete_revision' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_script_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_modify_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        '_all_' => '_all_',
      ),
    ),
  ),
  'action::og_set_state_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::og_user_roles_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_argument_selector_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'url' => '',
    ),
  ),
  'action::og_membership_delete_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::system_send_email_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
);
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_class'] = 'small-picture';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
/* Field: OG membership: State */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'og_membership';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['relationship'] = 'og_membership_rel';
/* Field: OG membership: OG user roles in group */
$handler->display->display_options['fields']['og_roles']['id'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['table'] = 'og_membership';
$handler->display->display_options['fields']['og_roles']['field'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['og_roles']['label'] = 'Roles';
$handler->display->display_options['fields']['og_roles']['type'] = 'ul';
/* Field: OG membership: Created */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'og_membership';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['created']['label'] = 'Member since';
$handler->display->display_options['fields']['created']['date_format'] = 'time ago';
/* Field: OG membership: Request message */
$handler->display->display_options['fields']['og_membership_request']['id'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['table'] = 'field_data_og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['field'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['relationship'] = 'og_membership_rel';
/* Field: OG membership: Delete link */
$handler->display->display_options['fields']['delete_membership']['id'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['table'] = 'og_membership';
$handler->display->display_options['fields']['delete_membership']['field'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['delete_membership']['label'] = '';
$handler->display->display_options['fields']['delete_membership']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['delete_membership']['alter']['text'] = '<a href="/modal/nojs/og/[gid]/remove/member/[id]" class="ctools-use-modal">Delete</a>';
$handler->display->display_options['fields']['delete_membership']['alter']['path'] = 'modal/nojs/og/[gid]/remove/member/[id]';
$handler->display->display_options['fields']['delete_membership']['alter']['link_class'] = 'ctools-use-modal';
$handler->display->display_options['fields']['delete_membership']['element_label_colon'] = FALSE;
/* Sort criterion: User: Name */
$handler->display->display_options['sorts']['name']['id'] = 'name';
$handler->display->display_options['sorts']['name']['table'] = 'users';
$handler->display->display_options['sorts']['name']['field'] = 'name';
/* Contextual filter: OG membership: Group_type */
$handler->display->display_options['arguments']['group_type']['id'] = 'group_type';
$handler->display->display_options['arguments']['group_type']['table'] = 'og_membership';
$handler->display->display_options['arguments']['group_type']['field'] = 'group_type';
$handler->display->display_options['arguments']['group_type']['relationship'] = 'og_membership_rel';
$handler->display->display_options['arguments']['group_type']['default_action'] = 'not found';
$handler->display->display_options['arguments']['group_type']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['group_type']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['group_type']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['group_type']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['group_type']['limit'] = '0';
/* Contextual filter: OG membership: Group ID */
$handler->display->display_options['arguments']['gid']['id'] = 'gid';
$handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
$handler->display->display_options['arguments']['gid']['field'] = 'gid';
$handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
$handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 0;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: User: Name */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'users';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['value'] = '';
$handler->display->display_options['filters']['uid']['exposed'] = TRUE;
$handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
$handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
$handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';

/* Display: Block */
$handler = $view->new_display('block', 'Block', 'block_1');
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
/* Header: OG membership: Group membership overview */
$handler->display->display_options['header']['og_membership_overview']['id'] = 'og_membership_overview';
$handler->display->display_options['header']['og_membership_overview']['table'] = 'og_membership';
$handler->display->display_options['header']['og_membership_overview']['field'] = 'og_membership_overview';
$handler->display->display_options['header']['og_membership_overview']['manager'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_members_1'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_members_2'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_members_3'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_members'] = 1;
$handler->display->display_options['header']['og_membership_overview']['total_content'] = 1;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: OG membership: Group ID */
$handler->display->display_options['fields']['gid']['id'] = 'gid';
$handler->display->display_options['fields']['gid']['table'] = 'og_membership';
$handler->display->display_options['fields']['gid']['field'] = 'gid';
$handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['gid']['label'] = '';
$handler->display->display_options['fields']['gid']['exclude'] = TRUE;
$handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gid']['separator'] = '';
/* Field: Bulk operations: OG membership */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'og_membership';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
  'action::views_bulk_operations_delete_item' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_delete_revision' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_script_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_modify_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        '_all_' => '_all_',
      ),
    ),
  ),
  'action::og_set_state_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::og_user_roles_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_argument_selector_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'url' => '',
    ),
  ),
  'action::og_membership_delete_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::system_send_email_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
);
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_class'] = 'small-picture';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
/* Field: OG membership: State */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'og_membership';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['relationship'] = 'og_membership_rel';
/* Field: OG membership: OG user roles in group */
$handler->display->display_options['fields']['og_roles']['id'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['table'] = 'og_membership';
$handler->display->display_options['fields']['og_roles']['field'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['og_roles']['label'] = 'Roles';
$handler->display->display_options['fields']['og_roles']['type'] = 'ul';
/* Field: OG membership: Created */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'og_membership';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['created']['label'] = 'Member since';
$handler->display->display_options['fields']['created']['date_format'] = 'time ago';
/* Field: OG membership: Request message */
$handler->display->display_options['fields']['og_membership_request']['id'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['table'] = 'field_data_og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['field'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['relationship'] = 'og_membership_rel';
/* Field: OG membership: Delete link */
$handler->display->display_options['fields']['delete_membership']['id'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['table'] = 'og_membership';
$handler->display->display_options['fields']['delete_membership']['field'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['delete_membership']['label'] = '';
$handler->display->display_options['fields']['delete_membership']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['delete_membership']['alter']['text'] = '<a href="/modal/nojs/og/[gid]/remove/member/[id]" class="ctools-use-modal">Delete</a>';
$handler->display->display_options['fields']['delete_membership']['alter']['path'] = 'modal/nojs/og/[gid]/remove/member/[id]';
$handler->display->display_options['fields']['delete_membership']['alter']['link_class'] = 'ctools-use-modal';
$handler->display->display_options['fields']['delete_membership']['element_label_colon'] = FALSE;

/* Display: Block simplified */
$handler = $view->new_display('block', 'Block simplified', 'block_2');
$handler->display->display_options['display_description'] = 'Show only members';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['header'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['id']['separator'] = '';
/* Field: OG membership: Group ID */
$handler->display->display_options['fields']['gid']['id'] = 'gid';
$handler->display->display_options['fields']['gid']['table'] = 'og_membership';
$handler->display->display_options['fields']['gid']['field'] = 'gid';
$handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['gid']['label'] = '';
$handler->display->display_options['fields']['gid']['exclude'] = TRUE;
$handler->display->display_options['fields']['gid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gid']['separator'] = '';
/* Field: Bulk operations: OG membership */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'og_membership';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['views_bulk_operations']['exclude'] = TRUE;
$handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
  'action::views_bulk_operations_delete_item' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_delete_revision' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_script_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_modify_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        '_all_' => '_all_',
      ),
    ),
  ),
  'action::og_set_state_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::og_user_roles_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_argument_selector_action' => array(
    'selected' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'url' => '',
    ),
  ),
  'action::og_membership_delete_action' => array(
    'selected' => 1,
    'postpone_processing' => 1,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::system_send_email_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
);
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_class'] = 'small-picture';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
/* Field: OG membership: State */
$handler->display->display_options['fields']['state']['id'] = 'state';
$handler->display->display_options['fields']['state']['table'] = 'og_membership';
$handler->display->display_options['fields']['state']['field'] = 'state';
$handler->display->display_options['fields']['state']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['state']['exclude'] = TRUE;
/* Field: OG membership: OG user roles in group */
$handler->display->display_options['fields']['og_roles']['id'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['table'] = 'og_membership';
$handler->display->display_options['fields']['og_roles']['field'] = 'og_roles';
$handler->display->display_options['fields']['og_roles']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['og_roles']['label'] = 'Roles';
$handler->display->display_options['fields']['og_roles']['exclude'] = TRUE;
$handler->display->display_options['fields']['og_roles']['type'] = 'ul';
/* Field: OG membership: Created */
$handler->display->display_options['fields']['created']['id'] = 'created';
$handler->display->display_options['fields']['created']['table'] = 'og_membership';
$handler->display->display_options['fields']['created']['field'] = 'created';
$handler->display->display_options['fields']['created']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['created']['label'] = 'Member since';
$handler->display->display_options['fields']['created']['exclude'] = TRUE;
$handler->display->display_options['fields']['created']['date_format'] = 'time ago';
/* Field: OG membership: Request message */
$handler->display->display_options['fields']['og_membership_request']['id'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['table'] = 'field_data_og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['field'] = 'og_membership_request';
$handler->display->display_options['fields']['og_membership_request']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['og_membership_request']['exclude'] = TRUE;
/* Field: OG membership: Delete link */
$handler->display->display_options['fields']['delete_membership']['id'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['table'] = 'og_membership';
$handler->display->display_options['fields']['delete_membership']['field'] = 'delete_membership';
$handler->display->display_options['fields']['delete_membership']['relationship'] = 'og_membership_rel';
$handler->display->display_options['fields']['delete_membership']['label'] = '';
$handler->display->display_options['fields']['delete_membership']['exclude'] = TRUE;
$handler->display->display_options['fields']['delete_membership']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['delete_membership']['alter']['text'] = '<a href="/modal/nojs/og/[gid]/remove/member/[id]" class="ctools-use-modal">Delete</a>';
$handler->display->display_options['fields']['delete_membership']['alter']['path'] = 'modal/nojs/og/[gid]/remove/member/[id]';
$handler->display->display_options['fields']['delete_membership']['alter']['link_class'] = 'ctools-use-modal';
$handler->display->display_options['fields']['delete_membership']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
$translatables['gofast_og_members_admin'] = array(
  t('Master'),
  t('OG members admin'),
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
  t('No people found matching the search criteria.'),
  t('OG membership from user'),
  t('.'),
  t('OG membership'),
  t('- Choose an operation -'),
  t('Name'),
  t('State'),
  t('Roles'),
  t('Member since'),
  t('Request message'),
  t('<a href="/modal/nojs/og/[gid]/remove/member/[id]" class="ctools-use-modal">Delete</a>'),
  t('All'),
  t('Block'),
  t('Block simplified'),
  t('Show only members'),
);
