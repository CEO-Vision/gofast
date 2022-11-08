$view = new view();
$view->name = 'gofast_og_members_page';
$view->description = 'Show members of a group';
$view->tag = 'default';
$view->base_table = 'og_membership';
$view->human_name = 'gofast_og_members';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'gofast_og_members';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '15';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['default_row_class'] = FALSE;
$handler->display->display_options['style_options']['row_class_special'] = FALSE;
$handler->display->display_options['style_options']['columns'] = '5';
$handler->display->display_options['row_plugin'] = 'fields';
$handler->display->display_options['row_options']['inline'] = array(
  'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
  'nothing' => 'nothing',
);
/* Relationship: OG membership: OG Roles from membership */
$handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
$handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
/* Relationship: OG membership: OG UserList Roles from membership */
$handler->display->display_options['relationships']['gofast_og_userlists_roles']['id'] = 'gofast_og_userlists_roles';
$handler->display->display_options['relationships']['gofast_og_userlists_roles']['table'] = 'og_membership';
$handler->display->display_options['relationships']['gofast_og_userlists_roles']['field'] = 'gofast_og_userlists_roles';
/* Relationship: OG membership: User from OG membership */
$handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
/* Relationship: OG membership: User List from OG membership */
$handler->display->display_options['relationships']['og_membership_related_userlist']['id'] = 'og_membership_related_userlist';
$handler->display->display_options['relationships']['og_membership_related_userlist']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_userlist']['field'] = 'og_membership_related_userlist';
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
/* Field: GoFAST Fields: GoFAST user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
/* Field: OG membership: Entity id */
$handler->display->display_options['fields']['etid']['id'] = 'etid';
$handler->display->display_options['fields']['etid']['table'] = 'og_membership';
$handler->display->display_options['fields']['etid']['field'] = 'etid';
$handler->display->display_options['fields']['etid']['label'] = '';
$handler->display->display_options['fields']['etid']['exclude'] = TRUE;
$handler->display->display_options['fields']['etid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['etid']['separator'] = '';
/* Field: OG membership: Entity_type */
$handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['label'] = '';
$handler->display->display_options['fields']['entity_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['entity_type']['element_label_colon'] = FALSE;
/* Field: User: Roles */
$handler->display->display_options['fields']['rid']['id'] = 'rid';
$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
$handler->display->display_options['fields']['rid']['field'] = 'rid';
$handler->display->display_options['fields']['rid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['rid']['label'] = '';
$handler->display->display_options['fields']['rid']['exclude'] = TRUE;
$handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
/* Field: User: Display name */
$handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ldap_user_displayname']['settings'] = array(
  'trim_length' => '600',
);
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
/* Field: User: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
/* Field: User : Custom display name */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'User : Custom display name';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['hide_empty'] = TRUE;
/* Field: Userlist : Custom name */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Userlist : Custom name';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<a href="/node/[nid]">[name]</a>';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['hide_empty'] = TRUE;
/* Field: GoFAST Fields: GoFAST user OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
/* Sort criterion: User: Display name (ldap_user_displayname) */
$handler->display->display_options['sorts']['ldap_user_displayname_value']['id'] = 'ldap_user_displayname_value';
$handler->display->display_options['sorts']['ldap_user_displayname_value']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['sorts']['ldap_user_displayname_value']['field'] = 'ldap_user_displayname_value';
$handler->display->display_options['sorts']['ldap_user_displayname_value']['relationship'] = 'og_membership_related_user';
/* Contextual filter: OG membership: Group ID */
$handler->display->display_options['arguments']['gid']['id'] = 'gid';
$handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
$handler->display->display_options['arguments']['gid']['field'] = 'gid';
$handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
$handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'AND',
);
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'og_role';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
$handler->display->display_options['filters']['name']['value'] = array(
  'administrator member' => 'administrator member',
  'group administrator' => 'group administrator',
  'group contributor' => 'group contributor',
  'member' => 'member',
  'read only member' => 'read only member',
);
$handler->display->display_options['filters']['name']['group'] = 1;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name_1']['id'] = 'name_1';
$handler->display->display_options['filters']['name_1']['table'] = 'og_role';
$handler->display->display_options['filters']['name_1']['field'] = 'name';
$handler->display->display_options['filters']['name_1']['relationship'] = 'gofast_og_userlists_roles';
$handler->display->display_options['filters']['name_1']['value'] = array(
  'administrator member' => 'administrator member',
  'group administrator' => 'group administrator',
  'group contributor' => 'group contributor',
  'member' => 'member',
  'read only member' => 'read only member',
);
$handler->display->display_options['filters']['name_1']['group'] = 2;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'og_membership';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  1 => '1',
);
$handler->display->display_options['filters']['state']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['value'] = 'user';
$handler->display->display_options['filters']['entity_type']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type_1']['id'] = 'entity_type_1';
$handler->display->display_options['filters']['entity_type_1']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type_1']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type_1']['value'] = 'userlist';
$handler->display->display_options['filters']['entity_type_1']['group'] = 2;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine_1']['id'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['table'] = 'views';
$handler->display->display_options['filters']['combine_1']['field'] = 'combine';
$handler->display->display_options['filters']['combine_1']['operator'] = 'contains';
$handler->display->display_options['filters']['combine_1']['group'] = 2;
$handler->display->display_options['filters']['combine_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine_1']['expose']['operator_id'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['expose']['operator'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['identifier'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine_1']['group_info']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['group_info']['identifier'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['group_info']['remember'] = FALSE;
$handler->display->display_options['filters']['combine_1']['group_info']['group_items'] = array(
  1 => array(),
  2 => array(),
  3 => array(),
);
$handler->display->display_options['filters']['combine_1']['fields'] = array(
  'name' => 'name',
);

/* Display: gofast_og_members_page */
$handler = $view->new_display('page', 'gofast_og_members_page', 'gofast_og_members_page');
$handler->display->display_options['path'] = 'gofast-og-members/%';

/* Display: members role admin */
$handler = $view->new_display('page', 'members role admin', 'gofast_og_members_role_admin_page');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
/* Field: GoFAST Fields: GoFAST user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['exclude'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['hide_empty'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
/* Field: GoFAST Fields: OG member picture */
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['id'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['table'] = 'og_membership';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['field'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['dimensions'] = '40';
/* Field: OG membership: Entity id */
$handler->display->display_options['fields']['etid']['id'] = 'etid';
$handler->display->display_options['fields']['etid']['table'] = 'og_membership';
$handler->display->display_options['fields']['etid']['field'] = 'etid';
$handler->display->display_options['fields']['etid']['label'] = '';
$handler->display->display_options['fields']['etid']['exclude'] = TRUE;
$handler->display->display_options['fields']['etid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['etid']['separator'] = '';
/* Field: OG membership: Entity_type */
$handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['label'] = '';
$handler->display->display_options['fields']['entity_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['entity_type']['element_label_colon'] = FALSE;
/* Field: User: Roles */
$handler->display->display_options['fields']['rid']['id'] = 'rid';
$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
$handler->display->display_options['fields']['rid']['field'] = 'rid';
$handler->display->display_options['fields']['rid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['rid']['label'] = '';
$handler->display->display_options['fields']['rid']['exclude'] = TRUE;
$handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
/* Field: User: Display name */
$handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ldap_user_displayname']['settings'] = array(
  'trim_length' => '600',
);
/* Field: User List: Label */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User List: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['separator'] = '';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
/* Field: User: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
/* Field: User : Custom display name */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'User : Custom display name';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['hide_empty'] = TRUE;
/* Field: Userlist : Custom name */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Userlist : Custom name';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<a href="/node/[nid]">[name]</a>';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['hide_empty'] = TRUE;
/* Field: GoFAST Fields: GoFAST user OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
/* Field: GoFAST Fields: GoFAST userlist OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['id'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['field'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['separator'] = '<br />';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'AND',
);
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'og_role';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
$handler->display->display_options['filters']['name']['value'] = array(
  'administrator member' => 'administrator member',
);
$handler->display->display_options['filters']['name']['group'] = 1;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name_1']['id'] = 'name_1';
$handler->display->display_options['filters']['name_1']['table'] = 'og_role';
$handler->display->display_options['filters']['name_1']['field'] = 'name';
$handler->display->display_options['filters']['name_1']['relationship'] = 'gofast_og_userlists_roles';
$handler->display->display_options['filters']['name_1']['value'] = array(
  'administrator member' => 'administrator member',
);
$handler->display->display_options['filters']['name_1']['group'] = 2;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'og_membership';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  1 => '1',
);
$handler->display->display_options['filters']['state']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['value'] = 'user';
$handler->display->display_options['filters']['entity_type']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type_1']['id'] = 'entity_type_1';
$handler->display->display_options['filters']['entity_type_1']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type_1']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type_1']['value'] = 'userlist';
$handler->display->display_options['filters']['entity_type_1']['group'] = 2;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'administrators_filter_input';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine_1']['id'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['table'] = 'views';
$handler->display->display_options['filters']['combine_1']['field'] = 'combine';
$handler->display->display_options['filters']['combine_1']['operator'] = 'contains';
$handler->display->display_options['filters']['combine_1']['group'] = 2;
$handler->display->display_options['filters']['combine_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine_1']['expose']['operator_id'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['expose']['operator'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['identifier'] = 'administrators_filter_input_userlist';
$handler->display->display_options['filters']['combine_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine_1']['fields'] = array(
  'name' => 'name',
);
$handler->display->display_options['path'] = 'gofast-og-role-admin/%';

/* Display: members role contributor */
$handler = $view->new_display('page', 'members role contributor', 'gofast_og_members_role_contrib_page');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
/* Field: GoFAST Fields: GoFAST user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['exclude'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
/* Field: GoFAST Fields: OG member picture */
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['id'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['table'] = 'og_membership';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['field'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['dimensions'] = '40';
/* Field: OG membership: Entity id */
$handler->display->display_options['fields']['etid']['id'] = 'etid';
$handler->display->display_options['fields']['etid']['table'] = 'og_membership';
$handler->display->display_options['fields']['etid']['field'] = 'etid';
$handler->display->display_options['fields']['etid']['label'] = '';
$handler->display->display_options['fields']['etid']['exclude'] = TRUE;
$handler->display->display_options['fields']['etid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['etid']['separator'] = '';
/* Field: OG membership: Entity_type */
$handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['label'] = '';
$handler->display->display_options['fields']['entity_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['entity_type']['element_label_colon'] = FALSE;
/* Field: User: Roles */
$handler->display->display_options['fields']['rid']['id'] = 'rid';
$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
$handler->display->display_options['fields']['rid']['field'] = 'rid';
$handler->display->display_options['fields']['rid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['rid']['label'] = '';
$handler->display->display_options['fields']['rid']['exclude'] = TRUE;
$handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
/* Field: User: Display name */
$handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ldap_user_displayname']['settings'] = array(
  'trim_length' => '600',
);
/* Field: User List: Label */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User List: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['separator'] = '';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
/* Field: User: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
/* Field: User : Custom display name */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'User : Custom display name';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['hide_empty'] = TRUE;
/* Field: Userlist : Custom name */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Userlist : Custom name';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<a href="/node/[nid]">[name]</a>';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['hide_empty'] = TRUE;
/* Field: GoFAST Fields: GoFAST user OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['hide_alter_empty'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['group contributor'] = TRUE;
/* Field: GoFAST Fields: GoFAST userlist OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['id'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['field'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['separator'] = '<br />';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['administrator member'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['group contributor'] = TRUE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'AND',
);
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'og_role';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
$handler->display->display_options['filters']['name']['value'] = array(
  'group contributor' => 'group contributor',
);
$handler->display->display_options['filters']['name']['group'] = 1;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name_1']['id'] = 'name_1';
$handler->display->display_options['filters']['name_1']['table'] = 'og_role';
$handler->display->display_options['filters']['name_1']['field'] = 'name';
$handler->display->display_options['filters']['name_1']['relationship'] = 'gofast_og_userlists_roles';
$handler->display->display_options['filters']['name_1']['value'] = array(
  'group contributor' => 'group contributor',
);
$handler->display->display_options['filters']['name_1']['group'] = 2;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'og_membership';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  1 => '1',
);
$handler->display->display_options['filters']['state']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['value'] = 'user';
$handler->display->display_options['filters']['entity_type']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type_1']['id'] = 'entity_type_1';
$handler->display->display_options['filters']['entity_type_1']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type_1']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type_1']['value'] = 'userlist';
$handler->display->display_options['filters']['entity_type_1']['group'] = 2;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'contributors_filter_input';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine_1']['id'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['table'] = 'views';
$handler->display->display_options['filters']['combine_1']['field'] = 'combine';
$handler->display->display_options['filters']['combine_1']['operator'] = 'contains';
$handler->display->display_options['filters']['combine_1']['group'] = 2;
$handler->display->display_options['filters']['combine_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine_1']['expose']['operator_id'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['expose']['operator'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['identifier'] = 'contributors_filter_input_userlist';
$handler->display->display_options['filters']['combine_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine_1']['group_info']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['group_info']['identifier'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['group_info']['remember'] = FALSE;
$handler->display->display_options['filters']['combine_1']['group_info']['group_items'] = array(
  1 => array(),
  2 => array(),
  3 => array(),
);
$handler->display->display_options['filters']['combine_1']['fields'] = array(
  'name' => 'name',
);
$handler->display->display_options['path'] = 'gofast-og-role-contributor/%';

/* Display: members role member */
$handler = $view->new_display('page', 'members role member', 'gofast_og_members_role_member_page');
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
/* Field: GoFAST Fields: GoFAST user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['exclude'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
/* Field: GoFAST Fields: OG member picture */
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['id'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['table'] = 'og_membership';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['field'] = 'gofast_userlist_og_handler_field_member_picture';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_userlist_og_handler_field_member_picture']['dimensions'] = '40';
/* Field: OG membership: Entity id */
$handler->display->display_options['fields']['etid']['id'] = 'etid';
$handler->display->display_options['fields']['etid']['table'] = 'og_membership';
$handler->display->display_options['fields']['etid']['field'] = 'etid';
$handler->display->display_options['fields']['etid']['label'] = '';
$handler->display->display_options['fields']['etid']['exclude'] = TRUE;
$handler->display->display_options['fields']['etid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['etid']['separator'] = '';
/* Field: OG membership: Entity_type */
$handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['label'] = '';
$handler->display->display_options['fields']['entity_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['entity_type']['element_label_colon'] = FALSE;
/* Field: User: Roles */
$handler->display->display_options['fields']['rid']['id'] = 'rid';
$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
$handler->display->display_options['fields']['rid']['field'] = 'rid';
$handler->display->display_options['fields']['rid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['rid']['label'] = '';
$handler->display->display_options['fields']['rid']['exclude'] = TRUE;
$handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
/* Field: User: Display name */
$handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ldap_user_displayname']['settings'] = array(
  'trim_length' => '600',
);
/* Field: User List: Label */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['exclude'] = TRUE;
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User List: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['nid']['label'] = '';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nid']['separator'] = '';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
/* Field: User: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
/* Field: User : Custom display name */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'User : Custom display name';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['hide_empty'] = TRUE;
/* Field: Userlist : Custom name */
$handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
$handler->display->display_options['fields']['nothing_1']['table'] = 'views';
$handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Userlist : Custom name';
$handler->display->display_options['fields']['nothing_1']['label'] = '';
$handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<a href="/node/[nid]">[name]</a>';
$handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing_1']['hide_empty'] = TRUE;
/* Field: GoFAST Fields: GoFAST user OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['read only member'] = TRUE;
/* Field: GoFAST Fields: GoFAST userlist OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['id'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['table'] = 'gofast_userlists';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['field'] = 'gofast_views_handler_field_userlist_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['relationship'] = 'og_membership_related_userlist';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['separator'] = '<br />';
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['administrator member'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_userlist_og_roles']['read only member'] = TRUE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'AND',
);
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'og_role';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
$handler->display->display_options['filters']['name']['operator'] = 'not';
$handler->display->display_options['filters']['name']['value'] = array(
  'administrator member' => 'administrator member',
  'group contributor' => 'group contributor',
);
$handler->display->display_options['filters']['name']['group'] = 1;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name_1']['id'] = 'name_1';
$handler->display->display_options['filters']['name_1']['table'] = 'og_role';
$handler->display->display_options['filters']['name_1']['field'] = 'name';
$handler->display->display_options['filters']['name_1']['relationship'] = 'gofast_og_userlists_roles';
$handler->display->display_options['filters']['name_1']['operator'] = 'not';
$handler->display->display_options['filters']['name_1']['value'] = array(
  'administrator member' => 'administrator member',
  'group administrator' => 'group administrator',
  'group contributor' => 'group contributor',
);
$handler->display->display_options['filters']['name_1']['group'] = 2;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'og_membership';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  1 => '1',
);
$handler->display->display_options['filters']['state']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['value'] = 'user';
$handler->display->display_options['filters']['entity_type']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type_1']['id'] = 'entity_type_1';
$handler->display->display_options['filters']['entity_type_1']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type_1']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type_1']['value'] = 'userlist';
$handler->display->display_options['filters']['entity_type_1']['group'] = 2;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'members_filter_input';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine_1']['id'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['table'] = 'views';
$handler->display->display_options['filters']['combine_1']['field'] = 'combine';
$handler->display->display_options['filters']['combine_1']['operator'] = 'contains';
$handler->display->display_options['filters']['combine_1']['group'] = 2;
$handler->display->display_options['filters']['combine_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine_1']['expose']['operator_id'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['expose']['operator'] = 'combine_1_op';
$handler->display->display_options['filters']['combine_1']['expose']['identifier'] = 'members_filter_input_userlist';
$handler->display->display_options['filters']['combine_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine_1']['group_info']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine_1']['group_info']['identifier'] = 'combine_1';
$handler->display->display_options['filters']['combine_1']['group_info']['remember'] = FALSE;
$handler->display->display_options['filters']['combine_1']['group_info']['group_items'] = array(
  1 => array(),
  2 => array(),
  3 => array(),
);
$handler->display->display_options['filters']['combine_1']['fields'] = array(
  'name' => 'name',
);
$handler->display->display_options['path'] = 'gofast-og-role-members/%';

/* Display: members pending request */
$handler = $view->new_display('page', 'members pending request', 'gofast_og_members_pending_request_page');
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: OG membership: User from OG membership */
$handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: State */
$handler->display->display_options['filters']['state']['id'] = 'state';
$handler->display->display_options['filters']['state']['table'] = 'og_membership';
$handler->display->display_options['filters']['state']['field'] = 'state';
$handler->display->display_options['filters']['state']['value'] = array(
  2 => '2',
);
$handler->display->display_options['filters']['state']['group'] = 1;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'requesters_filter_input';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
$handler->display->display_options['path'] = 'gofast-og-pending-request/%';

/* Display: members role banned */
$handler = $view->new_display('page', 'members role banned', 'gofast_og_banned_members');
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: OG membership: OG Roles from membership */
$handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
$handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
/* Relationship: OG membership: User from OG membership */
$handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
$handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: OG membership: Og membership ID */
$handler->display->display_options['fields']['id']['id'] = 'id';
$handler->display->display_options['fields']['id']['table'] = 'og_membership';
$handler->display->display_options['fields']['id']['field'] = 'id';
$handler->display->display_options['fields']['id']['label'] = '';
$handler->display->display_options['fields']['id']['exclude'] = TRUE;
$handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
/* Field: GoFAST Fields: GoFAST user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
/* Field: OG membership: Entity id */
$handler->display->display_options['fields']['etid']['id'] = 'etid';
$handler->display->display_options['fields']['etid']['table'] = 'og_membership';
$handler->display->display_options['fields']['etid']['field'] = 'etid';
$handler->display->display_options['fields']['etid']['label'] = '';
$handler->display->display_options['fields']['etid']['exclude'] = TRUE;
$handler->display->display_options['fields']['etid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['etid']['separator'] = '';
/* Field: OG membership: Entity_type */
$handler->display->display_options['fields']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['fields']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['fields']['entity_type']['label'] = '';
$handler->display->display_options['fields']['entity_type']['exclude'] = TRUE;
$handler->display->display_options['fields']['entity_type']['element_label_colon'] = FALSE;
/* Field: User: Roles */
$handler->display->display_options['fields']['rid']['id'] = 'rid';
$handler->display->display_options['fields']['rid']['table'] = 'users_roles';
$handler->display->display_options['fields']['rid']['field'] = 'rid';
$handler->display->display_options['fields']['rid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['rid']['label'] = '';
$handler->display->display_options['fields']['rid']['exclude'] = TRUE;
$handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
/* Field: User: Display name */
$handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
$handler->display->display_options['fields']['ldap_user_displayname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['ldap_user_displayname']['settings'] = array(
  'trim_length' => '600',
);
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'users';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
$handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['name_1']['link_to_user'] = FALSE;
/* Field: User: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'users';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
/* Field: User : Custom display name */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['ui_name'] = 'User : Custom display name';
$handler->display->display_options['fields']['nothing']['label'] = '';
$handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
$handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['nothing']['hide_empty'] = TRUE;
/* Field: GoFAST Fields: GoFAST user OG roles */
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: OG user/userlist roles: Role Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'og_role';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
$handler->display->display_options['filters']['name']['operator'] = 'not';
$handler->display->display_options['filters']['name']['value'] = array(
  'member' => 'member',
);
$handler->display->display_options['filters']['name']['group'] = 1;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_user';
$handler->display->display_options['filters']['status']['value'] = '0';
$handler->display->display_options['filters']['status']['group'] = 1;
/* Filter criterion: OG membership: Entity_type */
$handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['table'] = 'og_membership';
$handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
$handler->display->display_options['filters']['entity_type']['value'] = 'user';
$handler->display->display_options['filters']['entity_type']['group'] = 1;
/* Filter criterion: Global: Combine fields filter */
$handler->display->display_options['filters']['combine']['id'] = 'combine';
$handler->display->display_options['filters']['combine']['table'] = 'views';
$handler->display->display_options['filters']['combine']['field'] = 'combine';
$handler->display->display_options['filters']['combine']['operator'] = 'contains';
$handler->display->display_options['filters']['combine']['group'] = 1;
$handler->display->display_options['filters']['combine']['exposed'] = TRUE;
$handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['label'] = 'Combine fields filter';
$handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
$handler->display->display_options['filters']['combine']['expose']['identifier'] = 'members_filter_input';
$handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  4 => 0,
  5 => 0,
  6 => 0,
);
$handler->display->display_options['filters']['combine']['fields'] = array(
  'ldap_user_displayname' => 'ldap_user_displayname',
  'ldap_user_givenname' => 'ldap_user_givenname',
  'ldap_user_sn' => 'ldap_user_sn',
  'name_1' => 'name_1',
);
$handler->display->display_options['path'] = 'gofast-og-banned-members/%';
$translatables['gofast_og_members_page'] = array(
  t('Master'),
  t('gofast_og_members'),
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
  t('OG Roles from OG membership'),
  t('OG UserList Roles from OG membership'),
  t('user from OG membership'),
  t('userlist from OG membership'),
  t('.'),
  t(','),
  t('<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>'),
  t('<a href="/node/[nid]">[name]</a>'),
  t('All'),
  t('Combine fields filter'),
  t('gofast_og_members_page'),
  t('members role admin'),
  t('members role contributor'),
  t('members role member'),
  t('members pending request'),
  t('members role banned'),
);
