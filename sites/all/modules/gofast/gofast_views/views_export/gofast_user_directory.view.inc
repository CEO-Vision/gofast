$view = new view();
$view->name = 'gofast_user_directory';
$view->description = '';
$view->tag = 'default';
$view->base_table = 'users';
$view->human_name = 'gofast_user_directory';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'inactive_users';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'access user profiles';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['distinct'] = TRUE;
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '30';
$handler->display->display_options['style_plugin'] = 'grid';
$handler->display->display_options['style_options']['row_class'] = 'col-md-2';
$handler->display->display_options['style_options']['columns'] = '2';
$handler->display->display_options['row_plugin'] = 'fields';
/* Relationship: OG membership: OG membership from User */
$handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
$handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
$handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: User: Last login */
$handler->display->display_options['fields']['login']['id'] = 'login';
$handler->display->display_options['fields']['login']['table'] = 'users';
$handler->display->display_options['fields']['login']['field'] = 'login';
$handler->display->display_options['fields']['login']['label'] = '';
$handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['login']['date_format'] = 'privatemsg_years';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['text'] = '[ldap_user_givenname] [ldap_user_sn]';
$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'users/[name]';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User: Company */
$handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['label'] = '';
$handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
/* Field: User: Title */
$handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['label'] = '';
$handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
/* Field: User: Department */
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['id'] = 'ldap_user_departmentnumber_1';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['table'] = 'field_data_ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['field'] = 'ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['label'] = '';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
/* Field: User: Signature */
$handler->display->display_options['fields']['signature']['id'] = 'signature';
$handler->display->display_options['fields']['signature']['table'] = 'users';
$handler->display->display_options['fields']['signature']['field'] = 'signature';
$handler->display->display_options['fields']['signature']['label'] = '';
$handler->display->display_options['fields']['signature']['element_label_colon'] = FALSE;
/* Field: Privatemsg: Send Privatemsg link */
$handler->display->display_options['fields']['privatemsg_link']['id'] = 'privatemsg_link';
$handler->display->display_options['fields']['privatemsg_link']['table'] = 'users';
$handler->display->display_options['fields']['privatemsg_link']['field'] = 'privatemsg_link';
$handler->display->display_options['fields']['privatemsg_link']['label'] = '';
$handler->display->display_options['fields']['privatemsg_link']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['privatemsg_link']['return'] = 0;
/* Field: User: Mobile phone number */
$handler->display->display_options['fields']['ldap_user_mobile']['id'] = 'ldap_user_mobile';
$handler->display->display_options['fields']['ldap_user_mobile']['table'] = 'field_data_ldap_user_mobile';
$handler->display->display_options['fields']['ldap_user_mobile']['field'] = 'ldap_user_mobile';
$handler->display->display_options['fields']['ldap_user_mobile']['label'] = '';
$handler->display->display_options['fields']['ldap_user_mobile']['element_label_colon'] = FALSE;
/* Field: User: Active */
$handler->display->display_options['fields']['status']['id'] = 'status';
$handler->display->display_options['fields']['status']['table'] = 'users';
$handler->display->display_options['fields']['status']['field'] = 'status';
$handler->display->display_options['fields']['status']['label'] = '';
$handler->display->display_options['fields']['status']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['status']['not'] = 0;
/* Contextual filter: User: Uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'users';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
/* Filter criterion: User: Name */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'users';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['operator'] = 'not in';
$handler->display->display_options['filters']['uid']['value'] = array(
  0 => 0,
  1 => '68',
  2 => '1',
);
$handler->display->display_options['filters']['uid']['group'] = 1;
/* Filter criterion: User: Lastname (ldap_user_sn) */
$handler->display->display_options['filters']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['filters']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['operator'] = 'starts';
$handler->display->display_options['filters']['ldap_user_sn_value']['group'] = 1;
$handler->display->display_options['filters']['ldap_user_sn_value']['exposed'] = TRUE;
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator_id'] = 'ldap_user_sn_value_op';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['label'] = 'Nom';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator'] = 'ldap_user_sn_value_op';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['identifier'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

/* Display: user directory */
$handler = $view->new_display('page', 'user directory', 'page');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'User Directory';
$handler->display->display_options['defaults']['group_by'] = FALSE;
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: OG membership: OG membership from User */
$handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
$handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
$handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
/* Relationship: OG membership: Group Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Gofast Fields: Gofast user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
/* Field: User: Last login */
$handler->display->display_options['fields']['login']['id'] = 'login';
$handler->display->display_options['fields']['login']['table'] = 'users';
$handler->display->display_options['fields']['login']['field'] = 'login';
$handler->display->display_options['fields']['login']['label'] = '';
$handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['login']['date_format'] = 'privatemsg_years';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['text'] = '[ldap_user_givenname] [ldap_user_sn]';
$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'users/[name]';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User: Company */
$handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['label'] = '';
$handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
/* Field: User: Title */
$handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['label'] = '';
$handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
/* Field: User: Department */
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['id'] = 'ldap_user_departmentnumber_1';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['table'] = 'field_data_ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['field'] = 'ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['label'] = '';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
/* Field: Gofast Fields: Link to add friend */
$handler->display->display_options['fields']['gofast_link_add_relationship']['id'] = 'gofast_link_add_relationship';
$handler->display->display_options['fields']['gofast_link_add_relationship']['table'] = 'users';
$handler->display->display_options['fields']['gofast_link_add_relationship']['field'] = 'gofast_link_add_relationship';
/* Field: Gofast Fields: Quick action on the user */
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['id'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['field'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: User: Uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'users';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'OR',
);
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: User: Name */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'users';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['operator'] = 'not in';
$handler->display->display_options['filters']['uid']['value'] = array(
  0 => 0,
  1 => '68',
  2 => '1',
);
$handler->display->display_options['filters']['uid']['group'] = 1;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['value'] = '0';
$handler->display->display_options['filters']['uid_current']['group'] = 1;
$handler->display->display_options['filters']['uid_current']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['uid_current']['expose']['label'] = 'Is the logged in user';
$handler->display->display_options['filters']['uid_current']['expose']['operator'] = 'uid_current_op';
$handler->display->display_options['filters']['uid_current']['expose']['identifier'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['expose']['required'] = TRUE;
/* Filter criterion: Gofast Fields: Group nid */
$handler->display->display_options['filters']['gofast_filter_group_title']['id'] = 'gofast_filter_group_title';
$handler->display->display_options['filters']['gofast_filter_group_title']['table'] = 'node';
$handler->display->display_options['filters']['gofast_filter_group_title']['field'] = 'gofast_filter_group_title';
$handler->display->display_options['filters']['gofast_filter_group_title']['relationship'] = 'og_membership_related_node_group';
$handler->display->display_options['filters']['gofast_filter_group_title']['group'] = 1;
$handler->display->display_options['filters']['gofast_filter_group_title']['exposed'] = TRUE;
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['operator_id'] = 'gofast_filter_group_title_op';
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['label'] = 'Group nid';
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['operator'] = 'gofast_filter_group_title_op';
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['identifier'] = 'gofast_filter_group_title';
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['gofast_filter_group_title']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: User: Skills (field_skills) */
$handler->display->display_options['filters']['field_skills_tid']['id'] = 'field_skills_tid';
$handler->display->display_options['filters']['field_skills_tid']['table'] = 'field_data_field_skills';
$handler->display->display_options['filters']['field_skills_tid']['field'] = 'field_skills_tid';
$handler->display->display_options['filters']['field_skills_tid']['group'] = 1;
$handler->display->display_options['filters']['field_skills_tid']['exposed'] = TRUE;
$handler->display->display_options['filters']['field_skills_tid']['expose']['operator_id'] = 'field_skills_tid_op';
$handler->display->display_options['filters']['field_skills_tid']['expose']['label'] = 'Skills';
$handler->display->display_options['filters']['field_skills_tid']['expose']['operator'] = 'field_skills_tid_op';
$handler->display->display_options['filters']['field_skills_tid']['expose']['identifier'] = 'field_skills_tid';
$handler->display->display_options['filters']['field_skills_tid']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['field_skills_tid']['expose']['multiple'] = TRUE;
$handler->display->display_options['filters']['field_skills_tid']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['filters']['field_skills_tid']['type'] = 'select';
$handler->display->display_options['filters']['field_skills_tid']['vocabulary'] = 'skills';
$handler->display->display_options['filters']['field_skills_tid']['hierarchy'] = 1;
$handler->display->display_options['filters']['field_skills_tid']['error_message'] = FALSE;
/* Filter criterion: User: Lastname (ldap_user_sn) */
$handler->display->display_options['filters']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['filters']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['operator'] = 'starts';
$handler->display->display_options['filters']['ldap_user_sn_value']['group'] = 2;
$handler->display->display_options['filters']['ldap_user_sn_value']['exposed'] = TRUE;
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator_id'] = 'ldap_user_sn_value_op';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['label'] = 'Lastname';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator'] = 'ldap_user_sn_value_op';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['identifier'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: User: Lastname (ldap_user_sn) */
$handler->display->display_options['filters']['ldap_user_sn_value_1']['id'] = 'ldap_user_sn_value_1';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['field'] = 'ldap_user_sn_value';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['operator'] = 'starts';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['group'] = 2;
$handler->display->display_options['filters']['ldap_user_sn_value_1']['exposed'] = TRUE;
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['operator_id'] = 'ldap_user_sn_value_1_op';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['label'] = 'Lastname';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['operator'] = 'ldap_user_sn_value_1_op';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['identifier'] = 'ldap_user_sn_value_1';
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['ldap_user_sn_value_1']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
/* Filter criterion: Gofast Fields: My relationships */
$handler->display->display_options['filters']['gofast_user_relationships']['id'] = 'gofast_user_relationships';
$handler->display->display_options['filters']['gofast_user_relationships']['table'] = 'users';
$handler->display->display_options['filters']['gofast_user_relationships']['field'] = 'gofast_user_relationships';
$handler->display->display_options['filters']['gofast_user_relationships']['value'] = '0';
$handler->display->display_options['filters']['gofast_user_relationships']['exposed'] = TRUE;
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['operator_id'] = '';
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['label'] = 'Relationship with current user';
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['operator'] = 'gofast_user_relationships_op';
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['identifier'] = 'gofast_user_relationships';
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['required'] = TRUE;
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['remember'] = TRUE;
$handler->display->display_options['filters']['gofast_user_relationships']['expose']['remember_roles'] = array(
  2 => '2',
  1 => 0,
  3 => 0,
  6 => 0,
  4 => 0,
  5 => 0,
);
$handler->display->display_options['path'] = 'user_listing_grid';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Directory';
$handler->display->display_options['menu']['description'] = 'User\'s directory';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: inactive users */
$handler = $view->new_display('page', 'inactive users', 'page_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Inactives User Directory';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Gofast Fields: Gofast user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
/* Field: User: Last login */
$handler->display->display_options['fields']['login']['id'] = 'login';
$handler->display->display_options['fields']['login']['table'] = 'users';
$handler->display->display_options['fields']['login']['field'] = 'login';
$handler->display->display_options['fields']['login']['label'] = '';
$handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['login']['date_format'] = 'privatemsg_years';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['text'] = '[ldap_user_givenname] [ldap_user_sn]';
$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'users/[name]';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User: Company */
$handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['label'] = '';
$handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
/* Field: User: Title */
$handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['label'] = '';
$handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
/* Field: User: Department */
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['id'] = 'ldap_user_departmentnumber_1';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['table'] = 'field_data_ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['field'] = 'ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['label'] = '';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
/* Field: Gofast Fields: Link to add friend */
$handler->display->display_options['fields']['gofast_link_add_relationship']['id'] = 'gofast_link_add_relationship';
$handler->display->display_options['fields']['gofast_link_add_relationship']['table'] = 'users';
$handler->display->display_options['fields']['gofast_link_add_relationship']['field'] = 'gofast_link_add_relationship';
/* Field: Gofast Fields: Quick action on the user */
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['id'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['field'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Name */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'users';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['operator'] = 'not in';
$handler->display->display_options['filters']['uid']['value'] = array(
  0 => 0,
  1 => '68',
  2 => '1',
);
$handler->display->display_options['filters']['uid']['group'] = 1;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
/* Filter criterion: User: Last access */
$handler->display->display_options['filters']['access']['id'] = 'access';
$handler->display->display_options['filters']['access']['table'] = 'users';
$handler->display->display_options['filters']['access']['field'] = 'access';
$handler->display->display_options['filters']['access']['operator'] = '<=';
$handler->display->display_options['filters']['access']['value']['value'] = '-3 days';
$handler->display->display_options['filters']['access']['value']['type'] = 'offset';
$handler->display->display_options['path'] = 'inactive_users';

/* Display: user grid contrib */
$handler = $view->new_display('page', 'user grid contrib', 'page_2');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Actives Contributors';
$handler->display->display_options['defaults']['group_by'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Gofast Fields: Gofast user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['text'] = '[ldap_user_givenname] [ldap_user_sn]';
$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'users/[name]';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User: Company */
$handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['label'] = '';
$handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
/* Field: User: Title */
$handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['label'] = '';
$handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
/* Field: User: Department */
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['id'] = 'ldap_user_departmentnumber_1';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['table'] = 'field_data_ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['field'] = 'ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['label'] = '';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
/* Field: Userpoints total: Current total points */
$handler->display->display_options['fields']['points']['id'] = 'points';
$handler->display->display_options['fields']['points']['table'] = 'userpoints_total';
$handler->display->display_options['fields']['points']['field'] = 'points';
$handler->display->display_options['fields']['points']['label'] = '';
$handler->display->display_options['fields']['points']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['sorts'] = FALSE;
/* Sort criterion: Userpoints total: Current total points */
$handler->display->display_options['sorts']['points']['id'] = 'points';
$handler->display->display_options['sorts']['points']['table'] = 'userpoints_total';
$handler->display->display_options['sorts']['points']['field'] = 'points';
$handler->display->display_options['sorts']['points']['order'] = 'DESC';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: User: Name */
$handler->display->display_options['filters']['uid']['id'] = 'uid';
$handler->display->display_options['filters']['uid']['table'] = 'users';
$handler->display->display_options['filters']['uid']['field'] = 'uid';
$handler->display->display_options['filters']['uid']['operator'] = 'not in';
$handler->display->display_options['filters']['uid']['value'] = array(
  0 => 0,
  1 => '68',
  2 => '1',
);
$handler->display->display_options['filters']['uid']['group'] = 1;
/* Filter criterion: User: Active */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'users';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = '1';
$handler->display->display_options['filters']['status']['group'] = 1;
$handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
$handler->display->display_options['path'] = 'user_listing_grid_contrib';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Directory';
$handler->display->display_options['menu']['description'] = 'User\'s directory';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Single Profile */
$handler = $view->new_display('block', 'Single Profile', 'gofast_single_profile');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['defaults']['relationships'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: User: Last login */
$handler->display->display_options['fields']['login']['id'] = 'login';
$handler->display->display_options['fields']['login']['table'] = 'users';
$handler->display->display_options['fields']['login']['field'] = 'login';
$handler->display->display_options['fields']['login']['label'] = '';
$handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['login']['date_format'] = 'privatemsg_years';
/* Field: User: Firstname */
$handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
$handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
$handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
/* Field: User: Lastname */
$handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
$handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
$handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
$handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['text'] = '[ldap_user_givenname] [ldap_user_sn]';
$handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['name']['alter']['path'] = 'users/[name]';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: User: Company */
$handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
$handler->display->display_options['fields']['ldap_user_o']['label'] = '';
$handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
/* Field: User: Title */
$handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
$handler->display->display_options['fields']['ldap_user_title']['label'] = '';
$handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
/* Field: User: Department */
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['id'] = 'ldap_user_departmentnumber_1';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['table'] = 'field_data_ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['field'] = 'ldap_user_departmentnumber';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['label'] = '';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
$handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
/* Field: Gofast Fields: Link to add friend */
$handler->display->display_options['fields']['gofast_link_add_relationship_1']['id'] = 'gofast_link_add_relationship_1';
$handler->display->display_options['fields']['gofast_link_add_relationship_1']['table'] = 'users';
$handler->display->display_options['fields']['gofast_link_add_relationship_1']['field'] = 'gofast_link_add_relationship';
$handler->display->display_options['fields']['gofast_link_add_relationship_1']['label'] = '';
$handler->display->display_options['fields']['gofast_link_add_relationship_1']['element_label_colon'] = FALSE;
/* Field: Gofast Fields: Quick action on the user */
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['id'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['field'] = 'gofast_views_handler_field_node_user_quick_actions';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_node_user_quick_actions']['element_label_colon'] = FALSE;
/* Field: Gofast Fields: Gofast user picture */
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
$handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
/* Contextual filter: User: Uid */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'users';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
$handler->display->display_options['block_description'] = 'Single Profile';
$translatables['gofast_user_directory'] = array(
  t('Master'),
  t('inactive_users'),
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
  t('OG membership from user'),
  t('[ldap_user_givenname] [ldap_user_sn]'),
  t(' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>'),
  t('Send message'),
  t('All'),
  t('Nom'),
  t('user directory'),
  t('User Directory'),
  t('Group node from OG membership'),
  t('GoFAST user picture'),
  t('Link to add friend'),
  t('Is the logged in user'),
  t('Group nid'),
  t('Skills'),
  t('Lastname'),
  t('Relationship with current user'),
  t('inactive users'),
  t('Inactives User Directory'),
  t('Quick action on the user'),
  t('user grid contrib'),
  t('Actives Contributors'),
  t('.'),
  t(','),
  t('Single Profile'),
);
