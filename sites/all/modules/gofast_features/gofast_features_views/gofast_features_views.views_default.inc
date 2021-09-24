<?php
/**
 * @file
 * gofast_features_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gofast_features_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'calendar';
  $view->description = '';
  $view->tag = 'Calendar';
  $view->base_table = 'node';
  $view->human_name = 'Calendar';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_date']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Sort criterion: Content: Deadline (field_date) */
  $handler->display->display_options['sorts']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['sorts']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['sorts']['field_date_value']['field'] = 'field_date_value';
  $handler->display->display_options['filter_groups']['operator'] = 'OR';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    3 => 'AND',
    2 => 'AND',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'task' => 'task',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  /* Filter criterion: Content: Members (field_members) */
  $handler->display->display_options['filters']['field_members_target_id']['id'] = 'field_members_target_id';
  $handler->display->display_options['filters']['field_members_target_id']['table'] = 'field_data_field_members';
  $handler->display->display_options['filters']['field_members_target_id']['field'] = 'field_members_target_id';
  $handler->display->display_options['filters']['field_members_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_members_target_id']['expose']['operator_id'] = 'field_members_target_id_op';
  $handler->display->display_options['filters']['field_members_target_id']['expose']['label'] = 'Members (field_members)';
  $handler->display->display_options['filters']['field_members_target_id']['expose']['operator'] = 'field_members_target_id_op';
  $handler->display->display_options['filters']['field_members_target_id']['expose']['identifier'] = 'field_members_target_id';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'conference' => 'conference',
    'alfresco_item' => 'alfresco_item',
    'webform' => 'webform',
    'article' => 'article',
    'page' => 'page',
    'book' => 'book',
    'forum' => 'forum',
  );
  $handler->display->display_options['filters']['type']['group'] = 2;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_1']['id'] = 'status_1';
  $handler->display->display_options['filters']['status_1']['table'] = 'node';
  $handler->display->display_options['filters']['status_1']['field'] = 'status';
  $handler->display->display_options['filters']['status_1']['value'] = '1';
  $handler->display->display_options['filters']['status_1']['group'] = 2;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status_2']['id'] = 'status_2';
  $handler->display->display_options['filters']['status_2']['table'] = 'node';
  $handler->display->display_options['filters']['status_2']['field'] = 'status';
  $handler->display->display_options['filters']['status_2']['value'] = '1';
  $handler->display->display_options['filters']['status_2']['group'] = 3;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_2']['id'] = 'type_2';
  $handler->display->display_options['filters']['type_2']['table'] = 'node';
  $handler->display->display_options['filters']['type_2']['field'] = 'type';
  $handler->display->display_options['filters']['type_2']['value'] = array(
    'task' => 'task',
  );
  $handler->display->display_options['filters']['type_2']['group'] = 3;
  /* Filter criterion: Content: Responsible (field_person_in_charge) */
  $handler->display->display_options['filters']['field_person_in_charge_target_id']['id'] = 'field_person_in_charge_target_id';
  $handler->display->display_options['filters']['field_person_in_charge_target_id']['table'] = 'field_data_field_person_in_charge';
  $handler->display->display_options['filters']['field_person_in_charge_target_id']['field'] = 'field_person_in_charge_target_id';
  $handler->display->display_options['filters']['field_person_in_charge_target_id']['group'] = 3;

  /* Display: Month */
  $handler = $view->new_display('page', 'Month', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<p title="[title]"> [title] </p>';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_date']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity_reset'] = 0;
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'calendar-node-field-date/month';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Week */
  $handler = $view->new_display('page', 'Week', 'page_2');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'week';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'week';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'week';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-date/week';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Week';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Day */
  $handler = $view->new_display('page', 'Day', 'page_3');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'day';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'day';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'day';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-date/day';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Day';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'year';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['calendar_type'] = 'year';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => '',
  );
  $handler->display->display_options['fields']['field_date']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_date']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['granularity'] = 'year';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  $handler->display->display_options['path'] = 'calendar-node-field-date/year';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'mini';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '1';
  $handler->display->display_options['style_options']['mini'] = '1';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );

  /* Display: Upcoming */
  $handler = $view->new_display('block', 'Upcoming', 'block_2');
  $handler->display->display_options['display_description'] = 'Upcoming events block';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['add_delta'] = 'yes';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );

  /* Display: Month Mobile */
  $handler = $view->new_display('page', 'Month Mobile', 'page_4');
  $handler->display->display_options['defaults']['use_ajax'] = FALSE;
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['date_id'] = 'month';
  $handler->display->display_options['pager']['options']['link_format'] = 'clean';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '0';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Date: Date (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'og_context';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'calendar-node-field-date/month-mobile';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Month';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Calendar';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['calendar'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Group node from OG membership'),
    t('Members (field_members)'),
    t('Month'),
    t('<p title="[title]"> [title] </p>'),
    t('Tout'),
    t('All'),
    t('Week'),
    t('Day'),
    t('Year'),
    t('Block'),
    t('Upcoming'),
    t('Upcoming events block'),
    t('Month Mobile'),
  );
  $export['calendar'] = $view;

  $view = new view();
  $view->name = 'contacts_listing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contacts listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Contacts listing';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_contact_name' => 'field_contact_name',
    'field_contact_firstname' => 'field_contact_firstname',
    'field_contact_entity' => 'field_contact_entity',
    'field_contact_email' => 'field_contact_email',
    'field_contact_address' => 'field_contact_address',
    'field_contact_phone' => 'field_contact_phone',
    'delete_node_modal' => 'delete_node_modal',
    'gofast_edit' => 'gofast_edit',
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
    'field_contact_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_firstname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_entity' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_email' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contact_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node_modal' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_edit' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    'contact' => 'contact',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: contact_name */
  $handler->display->display_options['fields']['field_contact_name']['id'] = 'field_contact_name';
  $handler->display->display_options['fields']['field_contact_name']['table'] = 'field_data_field_contact_name';
  $handler->display->display_options['fields']['field_contact_name']['field'] = 'field_contact_name';
  $handler->display->display_options['fields']['field_contact_name']['label'] = 'Last name';
  /* Field: Content: contact_firstname */
  $handler->display->display_options['fields']['field_contact_firstname']['id'] = 'field_contact_firstname';
  $handler->display->display_options['fields']['field_contact_firstname']['table'] = 'field_data_field_contact_firstname';
  $handler->display->display_options['fields']['field_contact_firstname']['field'] = 'field_contact_firstname';
  $handler->display->display_options['fields']['field_contact_firstname']['label'] = 'First name';
  /* Field: Content: contact_entity */
  $handler->display->display_options['fields']['field_contact_entity']['id'] = 'field_contact_entity';
  $handler->display->display_options['fields']['field_contact_entity']['table'] = 'field_data_field_contact_entity';
  $handler->display->display_options['fields']['field_contact_entity']['field'] = 'field_contact_entity';
  $handler->display->display_options['fields']['field_contact_entity']['label'] = 'Entity';
  /* Field: Content: contact_email */
  $handler->display->display_options['fields']['field_contact_email']['id'] = 'field_contact_email';
  $handler->display->display_options['fields']['field_contact_email']['table'] = 'field_data_field_contact_email';
  $handler->display->display_options['fields']['field_contact_email']['field'] = 'field_contact_email';
  $handler->display->display_options['fields']['field_contact_email']['label'] = 'Email';
  /* Field: Content: contact_address */
  $handler->display->display_options['fields']['field_contact_address']['id'] = 'field_contact_address';
  $handler->display->display_options['fields']['field_contact_address']['table'] = 'field_data_field_contact_address';
  $handler->display->display_options['fields']['field_contact_address']['field'] = 'field_contact_address';
  $handler->display->display_options['fields']['field_contact_address']['label'] = 'Address';
  $handler->display->display_options['fields']['field_contact_address']['exclude'] = TRUE;
  /* Field: Content: contact_phone */
  $handler->display->display_options['fields']['field_contact_phone']['id'] = 'field_contact_phone';
  $handler->display->display_options['fields']['field_contact_phone']['table'] = 'field_data_field_contact_phone';
  $handler->display->display_options['fields']['field_contact_phone']['field'] = 'field_contact_phone';
  $handler->display->display_options['fields']['field_contact_phone']['label'] = 'Mobile';
  /* Field: GoFAST Fields: Delete link modal */
  $handler->display->display_options['fields']['delete_node_modal']['id'] = 'delete_node_modal';
  $handler->display->display_options['fields']['delete_node_modal']['table'] = 'node';
  $handler->display->display_options['fields']['delete_node_modal']['field'] = 'delete_node_modal';
  $handler->display->display_options['fields']['delete_node_modal']['label'] = '';
  $handler->display->display_options['fields']['delete_node_modal']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Edit link */
  $handler->display->display_options['fields']['gofast_edit']['id'] = 'gofast_edit';
  $handler->display->display_options['fields']['gofast_edit']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_edit']['field'] = 'gofast_edit';
  $handler->display->display_options['fields']['gofast_edit']['label'] = '';
  $handler->display->display_options['fields']['gofast_edit']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'contacts-listing';
  $translatables['contacts_listing'] = array(
    t('Master'),
    t('Contacts listing'),
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
    t('<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>'),
    t('Title'),
    t('Page'),
    t('Last name'),
    t('First name'),
    t('Entity'),
    t('Email'),
    t('Address'),
    t('Mobile'),
  );
  $export['contacts_listing'] = $view;

  $view = new view();
  $view->name = 'gofast_activity_feed';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_activity_feed';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h1  class="text-center"><small><em>No Match Found</em></small></h1>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = 'Title';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['label'] = 'popularity';
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '0',
  );
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['label'] = 'state';
  $handler->display->display_options['fields']['field_state']['click_sort_column'] = 'target_id';
  $handler->display->display_options['fields']['field_state']['type'] = 'entityreference_label';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_state']['group_column'] = 'target_id';
  /* Field: Comment: Title */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['relationship'] = 'cid';
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
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

  /* Display: activity feed */
  $handler = $view->new_display('block', 'activity feed', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Activity feed';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'gofast_activity_feed_view';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '16';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['total_pages'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Autorefresh */
  $handler->display->display_options['header']['autorefresh']['id'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['table'] = 'views';
  $handler->display->display_options['header']['autorefresh']['field'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['interval'] = '20000';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: Node last modifier */
  $handler->display->display_options['fields']['gofast_last_modifier']['id'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_last_modifier']['field'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['label'] = '';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  /* Field: GoFAST Fields: Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: GoFAST Fields: Block file management */
  $handler->display->display_options['fields']['gofast_block_file_management']['id'] = 'gofast_block_file_management';
  $handler->display->display_options['fields']['gofast_block_file_management']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_block_file_management']['field'] = 'gofast_block_file_management';
  $handler->display->display_options['fields']['gofast_block_file_management']['exclude'] = TRUE;
  /* Field: Title (original) */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title (original)';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Title (trimmed link) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (trimmed link)';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alt'] = '[title_1]';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_activity_feed_title"> [title] </div>
<div class="gofast_activity_feed_handlers">
[gofast_format]
<span class="gofast_activity_feed_type">[type]</span>
[gofast_block_file_management]
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Node last event */
  $handler->display->display_options['fields']['gofast_last_event']['id'] = 'gofast_last_event';
  $handler->display->display_options['fields']['gofast_last_event']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_last_event']['field'] = 'gofast_last_event';
  $handler->display->display_options['fields']['gofast_last_event']['label'] = 'Last event';
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['label'] = 'Spaces';
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  $handler->display->display_options['fields']['og_group_content_ref']['multi_type'] = 'ul';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '100',
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Popularity';
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '1';
  $handler->display->display_options['fields']['expression']['decimal'] = ',';
  $handler->display->display_options['fields']['expression']['expression'] = '[field_popularity]';
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_link';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'token_display_selected' => '',
    'token_display_unselected' => '',
  );
  $handler->display->display_options['fields']['field_state']['field_api_classes'] = TRUE;
  /* Field: GoFAST Fields Taxonomy State: Taxonomy State */
  $handler->display->display_options['fields']['gofast_taxo_state']['id'] = 'gofast_taxo_state';
  $handler->display->display_options['fields']['gofast_taxo_state']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_taxo_state']['field'] = 'gofast_taxo_state';
  $handler->display->display_options['fields']['gofast_taxo_state']['label'] = 'State';
  $handler->display->display_options['fields']['gofast_taxo_state']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Updated/commented date */
  $handler->display->display_options['sorts']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'conference' => 'conference',
    'alfresco_item' => 'alfresco_item',
    'forum' => 'forum',
    'webform' => 'webform',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: GoFAST Fields: Group nid */
  $handler->display->display_options['filters']['gofast_filter_group_title']['id'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['table'] = 'node';
  $handler->display->display_options['filters']['gofast_filter_group_title']['field'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group'] = 1;
  $handler->display->display_options['filters']['gofast_filter_group_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['operator_id'] = 'gofast_filter_group_title_op';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['label'] = 'Group title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['operator'] = 'gofast_filter_group_title_op';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['identifier'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['label'] = 'Group nid';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['identifier'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: State (field_state) */
  $handler->display->display_options['filters']['field_state_tid']['id'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['table'] = 'field_data_field_state';
  $handler->display->display_options['filters']['field_state_tid']['field'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_state_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator_id'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['label'] = 'State (field_state)';
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['identifier'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_state_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_state_tid']['vocabulary'] = 'state';
  $handler->display->display_options['filters']['field_state_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Updated/commented date */
  $handler->display->display_options['filters']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['filters']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['operator'] = '>';
  $handler->display->display_options['filters']['last_updated']['value']['value'] = '-15 day';
  $handler->display->display_options['filters']['last_updated']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['last_updated']['group'] = 2;
  /* Filter criterion: Content: Sticky */
  $handler->display->display_options['filters']['sticky']['id'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['table'] = 'node';
  $handler->display->display_options['filters']['sticky']['field'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['value'] = '1';
  $handler->display->display_options['filters']['sticky']['group'] = 2;
  $handler->display->display_options['block_description'] = 'activity feed';

  /* Display: activity group feed */
  $handler = $view->new_display('block', 'activity group feed', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'activity group feed';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = 'Gofast user picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
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
  $handler->display->display_options['block_description'] = 'activity group feed';

  /* Display: unpublished activity */
  $handler = $view->new_display('block', 'unpublished activity', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'unpublished activity';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '16';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content revision: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Utilisateur';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['label'] = 'popularity';
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '0',
  );
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['label'] = 'state';
  $handler->display->display_options['fields']['field_state']['click_sort_column'] = 'target_id';
  $handler->display->display_options['fields']['field_state']['type'] = 'entityreference_label';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_state']['group_column'] = 'target_id';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['block_description'] = 'unpublished activity';

  /* Display: personal activity feed */
  $handler = $view->new_display('block', 'personal activity feed', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'personal activity feed';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content revision: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Utilisateur';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
  $handler->display->display_options['block_description'] = 'personal activity feed';

  /* Display: my forums activity feed */
  $handler = $view->new_display('block', 'my forums activity feed', 'block_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'my forums activity feed';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '6';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content revision: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Utilisateur';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = 'Name';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['text'] = 'Name';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '26';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
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
    'forum' => 'forum',
  );
  $handler->display->display_options['block_description'] = 'my forums activity feed';

  /* Display: clone activity feed */
  $handler = $view->new_display('block', 'clone activity feed', 'block_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Activity feed';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'gofast_activity_feed_view';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '16';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Autorefresh */
  $handler->display->display_options['header']['autorefresh']['id'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['table'] = 'views';
  $handler->display->display_options['header']['autorefresh']['field'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['interval'] = '20000';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: Node last modifier */
  $handler->display->display_options['fields']['gofast_last_modifier']['id'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_last_modifier']['field'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['label'] = '';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  /* Field: GoFAST Fields: Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: GoFAST Fields: Block file management */
  $handler->display->display_options['fields']['gofast_block_file_management']['id'] = 'gofast_block_file_management';
  $handler->display->display_options['fields']['gofast_block_file_management']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_block_file_management']['field'] = 'gofast_block_file_management';
  $handler->display->display_options['fields']['gofast_block_file_management']['exclude'] = TRUE;
  /* Field: Title (original) */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title (original)';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Title (trimmed link) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (trimmed link)';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alt'] = '[title_1]';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_activity_feed_title"> [gofast_format] [title] </div>
<div class="gofast_activity_feed_handlers">
<span class="gofast_activity_feed_type">[type]</span>
[gofast_block_file_management]
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Node last event */
  $handler->display->display_options['fields']['gofast_last_event']['id'] = 'gofast_last_event';
  $handler->display->display_options['fields']['gofast_last_event']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_last_event']['field'] = 'gofast_last_event';
  $handler->display->display_options['fields']['gofast_last_event']['label'] = 'Last event';
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['label'] = 'Spaces';
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  $handler->display->display_options['fields']['og_group_content_ref']['multi_type'] = 'ul';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '100',
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Popularity';
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '1';
  $handler->display->display_options['fields']['expression']['decimal'] = ',';
  $handler->display->display_options['fields']['expression']['expression'] = '[field_popularity]';
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_link';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'token_display_selected' => '',
    'token_display_unselected' => '',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Updated/commented date */
  $handler->display->display_options['sorts']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'conference' => 'conference',
    'alfresco_item' => 'alfresco_item',
    'forum' => 'forum',
    'webform' => 'webform',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: State (field_state) */
  $handler->display->display_options['filters']['field_state_tid']['id'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['table'] = 'field_data_field_state';
  $handler->display->display_options['filters']['field_state_tid']['field'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_state_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator_id'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['label'] = 'State (field_state)';
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['identifier'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_state_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_state_tid']['vocabulary'] = 'state';
  $handler->display->display_options['filters']['field_state_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Updated/commented date */
  $handler->display->display_options['filters']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['filters']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['operator'] = '>';
  $handler->display->display_options['filters']['last_updated']['value']['value'] = '-90 day';
  $handler->display->display_options['filters']['last_updated']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['last_updated']['group'] = 2;
  /* Filter criterion: Content: Sticky */
  $handler->display->display_options['filters']['sticky']['id'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['table'] = 'node';
  $handler->display->display_options['filters']['sticky']['field'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['value'] = '1';
  $handler->display->display_options['filters']['sticky']['group'] = 2;
  $handler->display->display_options['block_description'] = 'activity feed';
  $translatables['gofast_activity_feed'] = array(
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
    t('‹ ‹'),
    t('› ›'),
    t('last »'),
    t('<h1  class="text-center"><small><em>No Match Found</em></small></h1>'),
    t('OG membership from node'),
    t('Group node from OG membership'),
    t('Title'),
    t('Date'),
    t('Parent Groups'),
    t('popularity'),
    t('state'),
    t('activity feed'),
    t('Activity feed'),
    t('Type'),
    t('Icon format'),
    t('Block file management'),
    t('[title_1]'),
    t('<div class="gofast_activity_feed_title"> [title] </div>
<div class="gofast_activity_feed_handlers">
[gofast_format]
<span class="gofast_activity_feed_type">[type]</span>
[gofast_block_file_management]
</div>'),
    t('Last event'),
    t('Spaces'),
    t('Popularity'),
    t(','),
    t('State'),
    t('Group title'),
    t('Group nid'),
    t('State (field_state)'),
    t('activity group feed'),
    t('Gofast user picture'),
    t('unpublished activity'),
    t('Utilisateur'),
    t('personal activity feed'),
    t('my forums activity feed'),
    t('Name'),
    t('All'),
    t('clone activity feed'),
    t('<div class="gofast_activity_feed_title"> [gofast_format] [title] </div>
<div class="gofast_activity_feed_handlers">
<span class="gofast_activity_feed_type">[type]</span>
[gofast_block_file_management]
</div>'),
  );
  $export['gofast_activity_feed'] = $view;

  $view = new view();
  $view->name = 'gofast_aggregator';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'aggregator_item';
  $view->human_name = 'gofast_aggregator';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Headlines';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Aggregator: Item ID */
  $handler->display->display_options['fields']['iid']['id'] = 'iid';
  $handler->display->display_options['fields']['iid']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['iid']['field'] = 'iid';
  $handler->display->display_options['fields']['iid']['label'] = '';
  $handler->display->display_options['fields']['iid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['iid']['element_label_colon'] = FALSE;
  /* Field: Aggregator: Link */
  $handler->display->display_options['fields']['link']['id'] = 'link';
  $handler->display->display_options['fields']['link']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['link']['field'] = 'link';
  $handler->display->display_options['fields']['link']['label'] = '';
  $handler->display->display_options['fields']['link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['link']['display_as_link'] = FALSE;
  /* Field: Aggregator: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'aggregator_item';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<a href="[link]" target="_blank">[title]</a>';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['display_as_link'] = FALSE;
  /* Sort criterion: Aggregator: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'aggregator_item';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';

  /* Display: Gofast Aggregator */
  $handler = $view->new_display('page', 'Gofast Aggregator', 'gofast_aggregator');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '4';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'gofast_aggregator';
  $translatables['gofast_aggregator'] = array(
    t('Master'),
    t('Headlines'),
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
    t('.'),
    t(','),
    t('<a href="[link]" target="_blank">[title]</a>'),
    t('Gofast Aggregator'),
  );
  $export['gofast_aggregator'] = $view;

  $view = new view();
  $view->name = 'gofast_audit';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ceo_vision_audit';
  $view->human_name = 'gofast_audit';
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
  /* Field: User: Last name */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['relationship'] = 'uid';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  /* Field: User: First name */
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
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'gofast_audit';
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
  $translatables['gofast_audit'] = array(
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
    t('Date ( jj-mm-aaaa ), from'),
    t('Document title'),
    t('Display name'),
    t('Possède les termes de taxonomie'),
    t('Possède les termes de taxonomie (avec profondeur)'),
    t('Page'),
    t('more'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Feed'),
  );
  $export['gofast_audit'] = $view;

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

  $view = new view();
  $view->name = 'gofast_audit_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'ceo_vision_audit';
  $view->human_name = 'gofast_audit_node';
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
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '3';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'timestamp' => 'timestamp',
    'ldap_user_sn' => 'ldap_user_sn',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'details' => 'details',
    'event_type' => 'event_type',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_sn' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_givenname' => array(
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
  );
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
  /* Field: CEO-Vision Audit: Event type */
  $handler->display->display_options['fields']['event_type']['id'] = 'event_type';
  $handler->display->display_options['fields']['event_type']['table'] = 'ceo_vision_audit';
  $handler->display->display_options['fields']['event_type']['field'] = 'event_type';
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
  $handler->display->display_options['arguments']['nid']['exception']['title'] = 'Tout';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'gofast_audit_node');
  $handler->display->display_options['exposed_block'] = TRUE;
  $handler->display->display_options['path'] = 'gofast_audit_node/%';
  $handler->display->display_options['menu']['title'] = 'Audit';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'xls';
  $handler->display->display_options['path'] = 'gofast_audit_node_xls/%';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );

  /* Display: Bloc */
  $handler = $view->new_display('block', 'Bloc', 'block_audit');
  $translatables['gofast_audit_node'] = array(
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
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Node id in this table that references a node.'),
    t('User id in this table that references a node.'),
    t('Date'),
    t('Event type'),
    t('Tout'),
    t('Page'),
    t('more'),
    t('Feed'),
    t('Bloc'),
  );
  $export['gofast_audit_node'] = $view;

  $view = new view();
  $view->name = 'gofast_conference';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_conference';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Conference';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'body' => 'body',
    'field_date' => 'field_date',
    'field_existing_participants' => 'field_existing_participants',
    'delta' => 'delta',
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
    'body' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_existing_participants' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Existing participants */
  $handler->display->display_options['fields']['field_existing_participants']['id'] = 'field_existing_participants';
  $handler->display->display_options['fields']['field_existing_participants']['table'] = 'field_data_field_existing_participants';
  $handler->display->display_options['fields']['field_existing_participants']['field'] = 'field_existing_participants';
  $handler->display->display_options['fields']['field_existing_participants']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_existing_participants']['delta_offset'] = '0';
  /* Field: Content: Existing participants (field_existing_participants:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_existing_participants';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['delta']['alter']['text'] = '[title] [body] [field_date]';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    'conference' => 'conference',
  );
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_date.field_date_value' => 'field_data_field_date.field_date_value',
  );

  /* Display: ical_view */
  $handler = $view->new_display('page', 'ical_view', 'page');
  $handler->display->display_options['path'] = 'gofast-conference';

  /* Display: ical_feed */
  $handler = $view->new_display('feed', 'ical_feed', 'ical_feed');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'date_ical';
  $handler->display->display_options['style_options']['cal_name'] = 'Gofast\'s conference';
  $handler->display->display_options['style_options']['disable_webcal'] = TRUE;
  $handler->display->display_options['row_plugin'] = 'date_ical';
  $handler->display->display_options['row_options']['date_field'] = 'field_data_field_date.field_date_value';
  $handler->display->display_options['row_options']['summary_field'] = 'default_title';
  $handler->display->display_options['row_options']['location_field'] = 'none';
  $handler->display->display_options['path'] = 'calendar/%/export.ics';
  $handler->display->display_options['displays'] = array(
    'page' => 'page',
    'default' => 0,
  );
  $translatables['gofast_conference'] = array(
    t('Master'),
    t('Conference'),
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
    t('Body'),
    t('Deadline'),
    t('Existing participants'),
    t('Existing participants (field_existing_participants:delta)'),
    t('[title] [body] [field_date]'),
    t('.'),
    t(','),
    t('ical_view'),
    t('ical_feed'),
  );
  $export['gofast_conference'] = $view;

  $view = new view();
  $view->name = 'gofast_flag_bookmarks';
  $view->description = 'A page listing the current user\'s bookmarks at /bookmarks.';
  $view->tag = 'flag';
  $view->base_table = 'node';
  $view->human_name = 'gofast_flag_bookmarks';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'gofast_flag_bookmarks';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'flag bookmarks';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'gofast_format' => 'gofast_format',
    'title' => 'title',
    'nothing' => 'nothing',
    'field_emplacement' => 'field_emplacement',
    'ops_1' => 'ops_1',
    'nid' => 'nid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_views_handler_field_user_picture' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_format' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_emplacement' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'You have not yet bookmarked any content. Click the "Bookmark this" link when viewing a piece of content to add it to this list.';
  $handler->display->display_options['empty']['text']['format'] = 'plain_text';
  /* Relationship: Flags: bookmarks */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'bookmarks';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'bookmarks';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '24';
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = '';
  $handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'private_space' => 'private_space',
    'public' => 'public',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'gofast_flag_bookmarks');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '24';
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['label'] = 'Bookmark location';
  $handler->display->display_options['fields']['field_emplacement']['element_class'] = 'gofast-bookmarks-list';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_emplacement']['multi_type'] = 'ul';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops_1']['id'] = 'ops_1';
  $handler->display->display_options['fields']['ops_1']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops_1']['field'] = 'ops';
  $handler->display->display_options['fields']['ops_1']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops_1']['label'] = 'Action';
  $handler->display->display_options['fields']['ops_1']['alter']['text'] = '[ops_1]';
  $handler->display->display_options['fields']['ops_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ops_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'gofast_bookmarks';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Page_dashboard */
  $handler = $view->new_display('page', 'Page_dashboard', 'page_1');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'page_dashboard';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['label'] = 'Bookmark location';
  $handler->display->display_options['fields']['field_emplacement']['element_class'] = 'gofast-bookmarks-list';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_emplacement']['multi_type'] = 'ul';
  /* Field: CEO-Vision Dashboard: Node actions */
  $handler->display->display_options['fields']['node_actions']['id'] = 'node_actions';
  $handler->display->display_options['fields']['node_actions']['table'] = 'gofast_dashboard';
  $handler->display->display_options['fields']['node_actions']['field'] = 'node_actions';
  $handler->display->display_options['fields']['node_actions']['label'] = '';
  $handler->display->display_options['fields']['node_actions']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'private_space' => 'private_space',
    'public' => 'public',
  );
  $handler->display->display_options['path'] = 'gofast_bookmarks_dashboard';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Page_dashboard_spaces */
  $handler = $view->new_display('page', 'Page_dashboard_spaces', 'page_2');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'page_dashboard_spaces';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_format' => 'gofast_format',
    'title' => 'title',
    'nothing' => 'nothing',
    'field_emplacement' => 'field_emplacement',
    'ops_1' => 'ops_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_format' => array(
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
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_emplacement' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: CEO-Vision Dashboard: Node actions */
  $handler->display->display_options['fields']['node_actions']['id'] = 'node_actions';
  $handler->display->display_options['fields']['node_actions']['table'] = 'gofast_dashboard';
  $handler->display->display_options['fields']['node_actions']['field'] = 'node_actions';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'private_space' => 'private_space',
    'public' => 'public',
  );
  $handler->display->display_options['path'] = 'gofast_bookmarks_dashboard_spaces';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'gofast_bookmarks_folders');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '24';
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['label'] = 'Bookmark location';
  $handler->display->display_options['fields']['field_emplacement']['element_class'] = 'gofast-bookmarks-list';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_emplacement']['multi_type'] = 'ul';
  /* Field: Content: reference */
  $handler->display->display_options['fields']['field_reference']['id'] = 'field_reference';
  $handler->display->display_options['fields']['field_reference']['table'] = 'field_data_field_reference';
  $handler->display->display_options['fields']['field_reference']['field'] = 'field_reference';
  $handler->display->display_options['fields']['field_reference']['label'] = '';
  $handler->display->display_options['fields']['field_reference']['element_label_colon'] = FALSE;
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops_1']['id'] = 'ops_1';
  $handler->display->display_options['fields']['ops_1']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops_1']['field'] = 'ops';
  $handler->display->display_options['fields']['ops_1']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops_1']['label'] = 'Action';
  $handler->display->display_options['fields']['ops_1']['alter']['text'] = '[ops_1]';
  $handler->display->display_options['fields']['ops_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ops_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['path'] = 'gofast_bookmarks_folders';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';

  /* Display: Page_dashboard_spaces_3_elem */
  $handler = $view->new_display('page', 'Page_dashboard_spaces_3_elem', 'page_3');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'page_dashboard_spaces';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_format' => 'gofast_format',
    'title' => 'title',
    'nothing' => 'nothing',
    'field_emplacement' => 'field_emplacement',
    'ops_1' => 'ops_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_format' => array(
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
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_emplacement' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: CEO-Vision Dashboard: Node actions */
  $handler->display->display_options['fields']['node_actions']['id'] = 'node_actions';
  $handler->display->display_options['fields']['node_actions']['table'] = 'gofast_dashboard';
  $handler->display->display_options['fields']['node_actions']['field'] = 'node_actions';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'private_space' => 'private_space',
    'public' => 'public',
  );
  $handler->display->display_options['path'] = 'gofast_bookmarks_dashboard_spaces';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['gofast_flag_bookmarks'] = array(
    t('Defaults'),
    t('gofast_flag_bookmarks'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('You have not yet bookmarked any content. Click the "Bookmark this" link when viewing a piece of content to add it to this list.'),
    t('bookmarks'),
    t('author'),
    t('Title'),
    t('<div class="gofast_flag_title"> [gofast_format] [title] </div>'),
    t('Location'),
    t('Page'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Bookmark location'),
    t('Action'),
    t('[ops_1]'),
    t('Page_dashboard'),
    t('Page_dashboard_spaces'),
    t('Node actions'),
    t('Page_dashboard_spaces_3_elem'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
  );
  $export['gofast_flag_bookmarks'] = $view;

  $view = new view();
  $view->name = 'gofast_flag_cart';
  $view->description = 'A page listing the current user\'s bookmarks at /bookmarks.';
  $view->tag = 'flag';
  $view->base_table = 'node';
  $view->human_name = 'gofast_flag_cart';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'My Cart';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'flag cart';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'gofast_format' => 'gofast_format',
    'title' => 'title',
    'nothing' => 'nothing',
    'last_comment_timestamp' => 'last_comment_timestamp',
    'ops' => 'ops',
  );
  $handler->display->display_options['style_options']['default'] = 'last_comment_timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_views_handler_field_user_picture' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_format' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_comment_timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = TRUE;
  $handler->display->display_options['empty']['text']['content'] = 'You have no content into your cart';
  $handler->display->display_options['empty']['text']['format'] = 'plain_text';
  /* Relationship: Flags: cart */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'cart';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cart';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '24';
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = '';
  $handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Last comment time */
  $handler->display->display_options['sorts']['last_comment_timestamp']['id'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_comment_timestamp']['field'] = 'last_comment_timestamp';
  $handler->display->display_options['sorts']['last_comment_timestamp']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'gofast_flag_cart');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '5';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_label'] = 'Éléments par page';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all_label'] = '- Tout -';
  $handler->display->display_options['pager']['options']['expose']['offset_label'] = 'Décalage';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« premier';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ précédent';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'suivant ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'dernier »';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['label'] = '';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_format']['element_label_colon'] = FALSE;
  /* Field: hidden : title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'hidden : title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Icon and title */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Icon and title';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="gofast_flag_title"> [gofast_format] [title] </div>';
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_emplacement']['id'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['table'] = 'field_data_field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['field'] = 'field_emplacement';
  $handler->display->display_options['fields']['field_emplacement']['delta_offset'] = '0';
  /* Field: Flags: Flagged time */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'flagging';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['timestamp']['label'] = 'date d\'ajout au panier';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops_1']['id'] = 'ops_1';
  $handler->display->display_options['fields']['ops_1']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops_1']['field'] = 'ops';
  $handler->display->display_options['fields']['ops_1']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops_1']['label'] = 'Action';
  $handler->display->display_options['fields']['ops_1']['alter']['text'] = '      ';
  $handler->display->display_options['fields']['ops_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ops_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['path'] = 'gofast_cart';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My bookmarks';
  $handler->display->display_options['menu']['weight'] = '0';
  $translatables['gofast_flag_cart'] = array(
    t('Defaults'),
    t('My Cart'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('You have no content into your cart'),
    t('cart'),
    t('author'),
    t('Title'),
    t('<div class="gofast_flag_title"> [gofast_format] [title] </div>'),
    t('Location'),
    t('Page'),
    t('Éléments par page'),
    t('- Tout -'),
    t('Décalage'),
    t('« premier'),
    t('‹ précédent'),
    t('suivant ›'),
    t('dernier »'),
    t('date d\'ajout au panier'),
    t('Action'),
    t('      '),
  );
  $export['gofast_flag_cart'] = $view;

  $view = new view();
  $view->name = 'gofast_group_article';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_group_article';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '2';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h1  class="text-center"><small><em>No Match Found</em></small></h1>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: Content revision: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['label'] = 'Utilisateur';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Relationship: OG membership: Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node']['id'] = 'og_membership_related_node';
  $handler->display->display_options['relationships']['og_membership_related_node']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node']['field'] = 'og_membership_related_node';
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = 'Name';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '26';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '30';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Updated/commented date */
  $handler->display->display_options['sorts']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['order'] = 'DESC';
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
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '7';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $translatables['gofast_group_article'] = array(
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
    t('‹ ‹'),
    t('› ›'),
    t('last »'),
    t('<h1  class="text-center"><small><em>No Match Found</em></small></h1>'),
    t('Utilisateur'),
    t('Group node from OG membership'),
    t('node from OG membership'),
    t('Name'),
    t('Title'),
    t('Date'),
    t('All'),
    t('Block'),
  );
  $export['gofast_group_article'] = $view;

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
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹ ';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› › ';
  $handler->display->display_options['style_plugin'] = 'table';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h1  class="text-center"><small><em>No Match Found</em></small></h1>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
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
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '8';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹ ';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› › ';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Hidden : Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Hidden : Title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Hidden : Icon Format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'Hidden : Icon Format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[gofast_format] [title]';
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
  $handler->display->display_options['pager']['options']['id'] = '9';
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
  /* Relationship: Flags: flag_public */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'flag_public';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Hidden : Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['ui_name'] = 'Hidden : Icon format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: Hidden : Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Hidden : Title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[gofast_format] [title]';
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
    t('<h1  class="text-center"><small><em>No Match Found</em></small></h1>'),
    t('Group node from OG membership'),
    t('node from OG membership'),
    t('Type'),
    t('Title'),
    t('Status'),
    t('Date'),
    t('popular content'),
    t('popular_content'),
    t('Icon format'),
    t('[gofast_format] [title]'),
    t('popularity'),
    t('popularity (field_popularity:radioactivity_energy)'),
    t('All'),
    t('content with status'),
    t('‹ ‹'),
    t('› ›'),
    t('flag'),
    t('personal popular content'),
    t('personal_popular_content'),
    t('author'),
  );
  $export['gofast_group_content'] = $view;

  $view = new view();
  $view->name = 'gofast_mobile_activity_feed';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_mobile_activity_feed';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Autorefresh */
  $handler->display->display_options['header']['autorefresh']['id'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['table'] = 'views';
  $handler->display->display_options['header']['autorefresh']['field'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['interval'] = '20000';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h1  class="text-center"><small><em>No Match Found</em></small></h1>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = 'Title';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'raw time ago';
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['label'] = 'popularity';
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '0',
  );
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['label'] = 'state';
  $handler->display->display_options['fields']['field_state']['click_sort_column'] = 'target_id';
  $handler->display->display_options['fields']['field_state']['type'] = 'entityreference_label';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_state']['group_column'] = 'target_id';
  /* Field: Comment: Title */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'comment';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['relationship'] = 'cid';
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
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

  /* Display: mobile activity feed */
  $handler = $view->new_display('block', 'mobile activity feed', 'block_mobile_activity_feed');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'gofast_activity_feed_view';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '16';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: Node last modifier */
  $handler->display->display_options['fields']['gofast_last_modifier']['id'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_last_modifier']['field'] = 'gofast_last_modifier';
  $handler->display->display_options['fields']['gofast_last_modifier']['label'] = '';
  $handler->display->display_options['fields']['gofast_last_modifier']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gofast_last_modifier']['element_label_colon'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  /* Field: GoFAST Fields: Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: Title (original) */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title (original)';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Title (trimmed link) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (trimmed link)';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alt'] = '[title_1]';
  $handler->display->display_options['fields']['title']['alter']['max_length'] = '35';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['html'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Title';
  $handler->display->display_options['fields']['nothing']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="gofast_activity_feed_title"> [title] </span>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Date';
  $handler->display->display_options['fields']['last_updated']['exclude'] = TRUE;
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'today time ago';
  $handler->display->display_options['fields']['last_updated']['custom_date_format'] = 'm/d/y H:i';
  $handler->display->display_options['fields']['last_updated']['second_date_format_custom'] = 'm/d/y H:m';
  $handler->display->display_options['fields']['last_updated']['second_date_format'] = 'short';
  /* Field: Content: Parent Groups */
  $handler->display->display_options['fields']['og_group_content_ref']['id'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_content_ref']['field'] = 'og_group_content_ref';
  $handler->display->display_options['fields']['og_group_content_ref']['label'] = 'Spaces';
  $handler->display->display_options['fields']['og_group_content_ref']['exclude'] = TRUE;
  $handler->display->display_options['fields']['og_group_content_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['og_group_content_ref']['delta_offset'] = '0';
  /* Field: Content: Popularity */
  $handler->display->display_options['fields']['field_popularity']['id'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['table'] = 'field_data_field_popularity';
  $handler->display->display_options['fields']['field_popularity']['field'] = 'field_popularity';
  $handler->display->display_options['fields']['field_popularity']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_popularity']['click_sort_column'] = 'radioactivity_energy';
  $handler->display->display_options['fields']['field_popularity']['settings'] = array(
    'energy' => '0',
    'type' => 'energy',
    'accuracy' => '100',
  );
  /* Field: Global: Math expression */
  $handler->display->display_options['fields']['expression']['id'] = 'expression';
  $handler->display->display_options['fields']['expression']['table'] = 'views';
  $handler->display->display_options['fields']['expression']['field'] = 'expression';
  $handler->display->display_options['fields']['expression']['label'] = 'Popularity';
  $handler->display->display_options['fields']['expression']['exclude'] = TRUE;
  $handler->display->display_options['fields']['expression']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['expression']['precision'] = '1';
  $handler->display->display_options['fields']['expression']['decimal'] = ',';
  $handler->display->display_options['fields']['expression']['expression'] = '[field_popularity]';
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_state']['id'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['table'] = 'field_data_field_state';
  $handler->display->display_options['fields']['field_state']['field'] = 'field_state';
  $handler->display->display_options['fields']['field_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_state']['type'] = 'taxonomy_term_reference_link';
  $handler->display->display_options['fields']['field_state']['settings'] = array(
    'token_display_selected' => '',
    'token_display_unselected' => '',
  );
  $handler->display->display_options['fields']['field_state']['field_api_classes'] = TRUE;
  /* Field: GoFAST Fields: Title */
  $handler->display->display_options['fields']['gofast_mobile_activity_feed_view']['id'] = 'gofast_mobile_activity_feed_view';
  $handler->display->display_options['fields']['gofast_mobile_activity_feed_view']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_mobile_activity_feed_view']['field'] = 'gofast_mobile_activity_feed_view';
  $handler->display->display_options['fields']['gofast_mobile_activity_feed_view']['label'] = '';
  $handler->display->display_options['fields']['gofast_mobile_activity_feed_view']['alter']['text'] = '[gofast_last_modifier] [nothing] <br />
Document type : [gofast_format] [last_updated] [field_state]
<div> Spaces : [og_group_content_ref] </div>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Updated/commented date */
  $handler->display->display_options['sorts']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['sorts']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['sorts']['last_updated']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
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
    'conference' => 'conference',
    'alfresco_item' => 'alfresco_item',
    'forum' => 'forum',
    'webform' => 'webform',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: GoFAST Fields: Group nid */
  $handler->display->display_options['filters']['gofast_filter_group_title']['id'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['table'] = 'node';
  $handler->display->display_options['filters']['gofast_filter_group_title']['field'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group'] = 1;
  $handler->display->display_options['filters']['gofast_filter_group_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['operator_id'] = 'gofast_filter_group_title_op';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['label'] = 'Group title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['expose']['use_operator'] = TRUE;
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
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['label'] = 'Group nid';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['identifier'] = 'gofast_filter_group_title';
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['gofast_filter_group_title']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: State (field_state) */
  $handler->display->display_options['filters']['field_state_tid']['id'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['table'] = 'field_data_field_state';
  $handler->display->display_options['filters']['field_state_tid']['field'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_state_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator_id'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['label'] = 'State (field_state)';
  $handler->display->display_options['filters']['field_state_tid']['expose']['operator'] = 'field_state_tid_op';
  $handler->display->display_options['filters']['field_state_tid']['expose']['identifier'] = 'field_state_tid';
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_state_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_state_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_state_tid']['vocabulary'] = 'state';
  $handler->display->display_options['filters']['field_state_tid']['hierarchy'] = 1;
  /* Filter criterion: Content: Updated/commented date */
  $handler->display->display_options['filters']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['filters']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['filters']['last_updated']['operator'] = '>';
  $handler->display->display_options['filters']['last_updated']['value']['value'] = '-30 day';
  $handler->display->display_options['filters']['last_updated']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['last_updated']['group'] = 2;
  /* Filter criterion: Content: Sticky */
  $handler->display->display_options['filters']['sticky']['id'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['table'] = 'node';
  $handler->display->display_options['filters']['sticky']['field'] = 'sticky';
  $handler->display->display_options['filters']['sticky']['value'] = '1';
  $handler->display->display_options['filters']['sticky']['group'] = 2;
  $handler->display->display_options['block_description'] = 'mobile activity feed';
  $translatables['gofast_mobile_activity_feed'] = array(
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
    t('‹ ‹'),
    t('› ›'),
    t('last »'),
    t('<h1  class="text-center"><small><em>No Match Found</em></small></h1>'),
    t('OG membership from node'),
    t('Group node from OG membership'),
    t('Title'),
    t('Date'),
    t('Parent Groups'),
    t('popularity'),
    t('state'),
    t('mobile activity feed'),
    t('Type'),
    t('Icon format'),
    t('[title_1]'),
    t('<span class="gofast_activity_feed_title"> [title] </span>'),
    t('Spaces'),
    t('Popularity'),
    t(','),
    t('State'),
    t('[gofast_last_modifier] [nothing] <br />
Document type : [gofast_format] [last_updated] [field_state]
<div> Spaces : [og_group_content_ref] </div>'),
    t('Group title'),
    t('Group nid'),
    t('State (field_state)'),
  );
  $export['gofast_mobile_activity_feed'] = $view;

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
  $handler->display->display_options['css_class'] = 'gofast_og_full_list';
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
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'public' => 'public',
  );
  /* Filter criterion: Field: Parent Group (og_group_ref) */
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
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'gofast_og_list';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Relationship: OG membership: OG membership from Node group */
  $handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['relationship'] = 'og_membership_rel_group';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = 'Admin';
  $handler->display->display_options['fields']['picture']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'gofast_thumbnail';
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
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'public' => 'public',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'public' => 'public',
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
    4 => 0,
    7 => 0,
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
        'group_node' => 'group_node',
        'all' => 0,
        'article' => 0,
        'page' => 0,
        'book' => 0,
        'alfresco_item' => 0,
        'forum' => 0,
        'orga' => 0,
        'private_space' => 0,
        'webform' => 0,
      ),
    ),
    2 => array(
      'title' => 'Organisation',
      'operator' => 'in',
      'value' => array(
        'orga' => 'orga',
        'all' => 0,
        'article' => 0,
        'page' => 0,
        'book' => 0,
        'alfresco_item' => 0,
        'forum' => 0,
        'group_node' => 0,
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
  $handler->display->display_options['path'] = 'og/old_list_grid';

  /* Display: list grid backup */
  $handler = $view->new_display('page', 'list grid backup', 'page_2');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = 'Admin';
  $handler->display->display_options['fields']['picture']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'gofast_thumbnail';
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
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'public' => 'public',
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'extranet' => 'extranet',
    'group' => 'group',
    'organisation' => 'organisation',
    'public' => 'public',
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
    4 => 0,
    7 => 0,
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
        'group_node' => 'group_node',
        'all' => 0,
        'article' => 0,
        'page' => 0,
        'book' => 0,
        'alfresco_item' => 0,
        'forum' => 0,
        'orga' => 0,
        'private_space' => 0,
        'webform' => 0,
      ),
    ),
    2 => array(
      'title' => 'Organisation',
      'operator' => 'in',
      'value' => array(
        'orga' => 'orga',
        'all' => 0,
        'article' => 0,
        'page' => 0,
        'book' => 0,
        'alfresco_item' => 0,
        'forum' => 0,
        'group_node' => 0,
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
  $handler->display->display_options['path'] = 'og/list_grid_backup';
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
    t('list grid backup'),
  );
  $export['gofast_og_list'] = $view;

  $view = new view();
  $view->name = 'gofast_og_members';
  $view->description = 'Show user of a group';
  $view->tag = 'default';
  $view->base_table = 'users';
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
  $handler->display->display_options['row_options']['separator'] = ' ';
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_users_roles']['label'] = 'og_users_roles';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['picture_only'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: User: Roles */
  $handler->display->display_options['fields']['rid']['id'] = 'rid';
  $handler->display->display_options['fields']['rid']['table'] = 'users_roles';
  $handler->display->display_options['fields']['rid']['field'] = 'rid';
  $handler->display->display_options['fields']['rid']['label'] = '';
  $handler->display->display_options['fields']['rid']['element_label_colon'] = FALSE;
  /* Field: OG membership: OG user roles in group */
  $handler->display->display_options['fields']['og_roles']['id'] = 'og_roles';
  $handler->display->display_options['fields']['og_roles']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_roles']['field'] = 'og_roles';
  $handler->display->display_options['fields']['og_roles']['label'] = '';
  $handler->display->display_options['fields']['og_roles']['element_label_colon'] = FALSE;
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );

  /* Display: gofast_og_members_page */
  $handler = $view->new_display('page', 'gofast_og_members_page', 'gofast_og_members_page');
  $handler->display->display_options['display_description'] = 'This view list all the members of a group';
  $handler->display->display_options['path'] = 'gofast-og-members/%';

  /* Display: members role admin */
  $handler = $view->new_display('page', 'members role admin', 'gofast_og_members_role_admin_page');
  $handler->display->display_options['display_description'] = 'This view list all the members of a group filtered by role admin';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = '5';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['row_options']['separator'] = ' ';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: Excluded for filter : displayname */
  $handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['ui_name'] = 'Excluded for filter : displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_displayname']['type'] = 'text_plain';
  /* Field: Excluded for filter : firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['ui_name'] = 'Excluded for filter : firstname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['type'] = 'text_plain';
  /* Field: Excluded for filter : lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['ui_name'] = 'Excluded for filter : lastname';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['type'] = 'text_plain';
  /* Field: Excluded for filter : name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Excluded for filter : name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Field: Custom user displayname */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Custom user displayname';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Display name */
  $handler->display->display_options['fields']['ldap_user_displayname_1']['id'] = 'ldap_user_displayname_1';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['text'] = '[ldap_user_givenname] <br /> [ldap_user_sn]';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user OG roles */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['sorts']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
  /* Filter criterion: OG user/userlist roles: Role Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'og_role';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
  $handler->display->display_options['filters']['name']['value'] = array(
    'administrator member' => 'administrator member',
  );
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Role Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['name']['reduce_duplicates'] = TRUE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine_1']['id'] = 'combine_1';
  $handler->display->display_options['filters']['combine_1']['table'] = 'views';
  $handler->display->display_options['filters']['combine_1']['field'] = 'combine';
  $handler->display->display_options['filters']['combine_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine_1']['group'] = 1;
  $handler->display->display_options['filters']['combine_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine_1']['expose']['operator_id'] = 'combine_1_op';
  $handler->display->display_options['filters']['combine_1']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine_1']['expose']['operator'] = 'combine_1_op';
  $handler->display->display_options['filters']['combine_1']['expose']['identifier'] = 'administrators_filter_input';
  $handler->display->display_options['filters']['combine_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['combine_1']['fields'] = array(
    'ldap_user_displayname' => 'ldap_user_displayname',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_sn' => 'ldap_user_sn',
    'name' => 'name',
  );
  $handler->display->display_options['path'] = 'gofast-og-role-admin/%';

  /* Display: members role contributor */
  $handler = $view->new_display('page', 'members role contributor', 'gofast_og_members_role_contrib_page');
  $handler->display->display_options['display_description'] = 'This view list all the members of a group filtered by role';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = '5';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['row_options']['separator'] = ' ';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: Excluded for filter : displayname */
  $handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['ui_name'] = 'Excluded for filter : displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_displayname']['type'] = 'text_plain';
  /* Field: Excluded for filter : firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['ui_name'] = 'Excluded for filter : firstname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['type'] = 'text_plain';
  /* Field: Excluded for filter : lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['ui_name'] = 'Excluded for filter : lastname';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['type'] = 'text_plain';
  /* Field: Excluded for filter : name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Excluded for filter : name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Field: Custom user displayname */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Custom user displayname';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Display name */
  $handler->display->display_options['fields']['ldap_user_displayname_2']['id'] = 'ldap_user_displayname_2';
  $handler->display->display_options['fields']['ldap_user_displayname_2']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_2']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_2']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_2']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['ldap_user_displayname_2']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user OG roles */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['group contributor'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['sorts']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
  /* Filter criterion: OG user/userlist roles: Role Name */
  $handler->display->display_options['filters']['name']['id'] = 'name';
  $handler->display->display_options['filters']['name']['table'] = 'og_role';
  $handler->display->display_options['filters']['name']['field'] = 'name';
  $handler->display->display_options['filters']['name']['relationship'] = 'og_users_roles';
  $handler->display->display_options['filters']['name']['value'] = array(
    'group contributor' => 'group contributor',
  );
  $handler->display->display_options['filters']['name']['group'] = 1;
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Role Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['name']['reduce_duplicates'] = TRUE;
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
    7 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'ldap_user_displayname' => 'ldap_user_displayname',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_sn' => 'ldap_user_sn',
    'name' => 'name',
  );
  $handler->display->display_options['path'] = 'gofast-og-role-contributor/%';

  /* Display: members role member */
  $handler = $view->new_display('page', 'members role member', 'gofast_og_members_role_member_page');
  $handler->display->display_options['display_description'] = 'This view list all the members of a group filtered by role';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['empty'] = 'There are no members';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: Excluded for filter : displayname */
  $handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['ui_name'] = 'Excluded for filter : displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_displayname']['type'] = 'text_plain';
  /* Field: Excluded for filter : firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['ui_name'] = 'Excluded for filter : firstname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['type'] = 'text_plain';
  /* Field: Excluded for filter : lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['ui_name'] = 'Excluded for filter : lastname';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['type'] = 'text_plain';
  /* Field: Excluded for filter : name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Excluded for filter : name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Field: Custom user displayname */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Custom user displayname';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Display name */
  $handler->display->display_options['fields']['ldap_user_displayname_1']['id'] = 'ldap_user_displayname_1';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user OG roles */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['read only member'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['sorts']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
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
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Role Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['name']['reduce_duplicates'] = TRUE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'members_filter_input';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'ldap_user_displayname' => 'ldap_user_displayname',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_sn' => 'ldap_user_sn',
    'name' => 'name',
  );
  $handler->display->display_options['path'] = 'gofast-og-role-members/%';

  /* Display: members pending request */
  $handler = $view->new_display('page', 'members pending request', 'gofast_og_members_pending_request_page');
  $handler->display->display_options['display_description'] = 'This view list all the members of a group filtered by role';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['empty'] = 'There are no members';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: Excluded for filter : displayname */
  $handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['ui_name'] = 'Excluded for filter : displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_displayname']['type'] = 'text_plain';
  /* Field: Excluded for filter : firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['ui_name'] = 'Excluded for filter : firstname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['type'] = 'text_plain';
  /* Field: Excluded for filter : lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['ui_name'] = 'Excluded for filter : lastname';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['type'] = 'text_plain';
  /* Field: Excluded for filter : name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Excluded for filter : name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Field: Custom user displayname */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Custom user displayname';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Display name */
  $handler->display->display_options['fields']['ldap_user_displayname_1']['id'] = 'ldap_user_displayname_1';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user OG roles */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['sorts']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
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
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'requesters_filter_input';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'ldap_user_displayname' => 'ldap_user_displayname',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_sn' => 'ldap_user_sn',
    'name' => 'name',
  );
  $handler->display->display_options['path'] = 'gofast-og-pending-request/%';

  /* Display: members role banned */
  $handler = $view->new_display('page', 'members role banned', 'gofast_og_banned_members');
  $handler->display->display_options['display_description'] = 'This view list all the banned members of a group ';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'og_membership_rel';
  /* Relationship: OG membership: OG Roles from membership */
  $handler->display->display_options['relationships']['og_users_roles']['id'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_users_roles']['field'] = 'og_users_roles';
  $handler->display->display_options['relationships']['og_users_roles']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['empty'] = 'There are no members';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['popup'] = TRUE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: Excluded for filter : displayname */
  $handler->display->display_options['fields']['ldap_user_displayname']['id'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['ui_name'] = 'Excluded for filter : displayname';
  $handler->display->display_options['fields']['ldap_user_displayname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_displayname']['type'] = 'text_plain';
  /* Field: Excluded for filter : firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['ui_name'] = 'Excluded for filter : firstname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_givenname']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['type'] = 'text_plain';
  /* Field: Excluded for filter : lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['ui_name'] = 'Excluded for filter : lastname';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_sn']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['type'] = 'text_plain';
  /* Field: Excluded for filter : name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['ui_name'] = 'Excluded for filter : name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Field: Custom user displayname */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Custom user displayname';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: User: Display name */
  $handler->display->display_options['fields']['ldap_user_displayname_1']['id'] = 'ldap_user_displayname_1';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['table'] = 'field_data_ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['field'] = 'ldap_user_displayname';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['label'] = '';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_displayname_1']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['ldap_user_displayname_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user OG roles */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['id'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['field'] = 'gofast_views_handler_field_user_og_roles';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = '<br/>';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['read only member'] = TRUE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['sorts']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['sorts']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['state']['group'] = 1;
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
  $handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['label'] = 'Role Name';
  $handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
  $handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
  $handler->display->display_options['filters']['name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['name']['reduce_duplicates'] = TRUE;
  /* Filter criterion: Global: Combine fields filter */
  $handler->display->display_options['filters']['combine']['id'] = 'combine';
  $handler->display->display_options['filters']['combine']['table'] = 'views';
  $handler->display->display_options['filters']['combine']['field'] = 'combine';
  $handler->display->display_options['filters']['combine']['operator'] = 'contains';
  $handler->display->display_options['filters']['combine']['group'] = 1;
  $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
  $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
  $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'members_filter_input';
  $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['combine']['fields'] = array(
    'ldap_user_displayname' => 'ldap_user_displayname',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_sn' => 'ldap_user_sn',
    'name' => 'name',
  );
  $handler->display->display_options['path'] = 'gofast-og-banned-members/%';
  $translatables['gofast_og_members'] = array(
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
    t('og_membership_rel'),
    t('og_users_roles'),
    t('Uid'),
    t('All'),
    t('gofast_og_members_page'),
    t('This view list all the members of a group'),
    t('members role admin'),
    t('This view list all the members of a group filtered by role admin'),
    t('OG Roles from OG membership'),
    t('<a href="/user/[uid]">[ldap_user_givenname] [ldap_user_sn]</a>'),
    t('[ldap_user_givenname] <br /> [ldap_user_sn]'),
    t('Role Name'),
    t('Search'),
    t('members role contributor'),
    t('This view list all the members of a group filtered by role'),
    t('Combine fields filter'),
    t('members role member'),
    t('There are no members'),
    t('members pending request'),
    t('members role banned'),
    t('This view list all the banned members of a group '),
  );
  $export['gofast_og_members'] = $view;

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
    'action::og_user_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::og_membership_delete_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
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
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Filter by name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
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
    'edit_membership' => 'edit_membership',
    'delete_membership' => 'edit_membership',
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
    'edit_membership' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'delete_membership' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
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
  $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::og_set_state_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::og_user_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => '',
    ),
    'action::og_membership_delete_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = 'User';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['picture_only'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
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
  /* Field: OG membership: Edit link */
  $handler->display->display_options['fields']['edit_membership']['id'] = 'edit_membership';
  $handler->display->display_options['fields']['edit_membership']['table'] = 'og_membership';
  $handler->display->display_options['fields']['edit_membership']['field'] = 'edit_membership';
  $handler->display->display_options['fields']['edit_membership']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['edit_membership']['label'] = '';
  $handler->display->display_options['fields']['edit_membership']['element_label_colon'] = FALSE;
  /* Field: OG membership: Delete link */
  $handler->display->display_options['fields']['delete_membership']['id'] = 'delete_membership';
  $handler->display->display_options['fields']['delete_membership']['table'] = 'og_membership';
  $handler->display->display_options['fields']['delete_membership']['field'] = 'delete_membership';
  $handler->display->display_options['fields']['delete_membership']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['delete_membership']['label'] = '';
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
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Filter by name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
    2 => '2',
    3 => '3',
  );
  $handler->display->display_options['filters']['state']['exposed'] = TRUE;
  $handler->display->display_options['filters']['state']['expose']['operator_id'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['label'] = 'Filter by membership state';
  $handler->display->display_options['filters']['state']['expose']['operator'] = 'state_op';
  $handler->display->display_options['filters']['state']['expose']['identifier'] = 'state';
  $handler->display->display_options['filters']['state']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );

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
    'action::og_user_roles_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::og_membership_delete_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
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
    t('Filter by name'),
    t('Block'),
    t('User'),
    t('Filter by membership state'),
    t('Block simplified'),
    t('Show only members'),
  );
  $export['gofast_og_members_admin'] = $view;

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
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
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
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['separator'] = ' ,';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_og_roles']['administrator member'] = FALSE;
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
  $export['gofast_og_members_page'] = $view;

  $view = new view();
  $view->name = 'gofast_private_msg';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'pm_index';
  $view->human_name = 'gofast_private_msg';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Messages';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'thread_id' => 'thread_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'thread_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Relationship: Messages: Recipient */
  $handler->display->display_options['relationships']['recipient']['id'] = 'recipient';
  $handler->display->display_options['relationships']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['relationships']['recipient']['field'] = 'recipient';
  /* Field: Messages: Thread ID */
  $handler->display->display_options['fields']['thread_id']['id'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['table'] = 'pm_index';
  $handler->display->display_options['fields']['thread_id']['field'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['exclude'] = TRUE;
  /* Field: Messages: Is new */
  $handler->display->display_options['fields']['is_new']['id'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['table'] = 'pm_index';
  $handler->display->display_options['fields']['is_new']['field'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['label'] = '';
  $handler->display->display_options['fields']['is_new']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_new']['not'] = 0;
  /* Field: Messages: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'pm_message';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Messages: Recipient */
  $handler->display->display_options['fields']['recipient']['id'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['fields']['recipient']['field'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
  /* Field: GoFAST Fields: GoFAST pm recipient */
  $handler->display->display_options['fields']['gofast_recipients']['id'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['table'] = 'pm_message';
  $handler->display->display_options['fields']['gofast_recipients']['field'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['label'] = 'Participants';
  /* Field: Messages: Send date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[thread_id]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
  /* Sort criterion: MAX(Messages: Send date) */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['group_type'] = 'max';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: Messages: Is deleted */
  $handler->display->display_options['filters']['deleted']['id'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
  $handler->display->display_options['filters']['deleted']['field'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['value'] = '0';
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'recipient';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';

  /* Display: Messages */
  $handler = $view->new_display('page', 'Messages', 'gofast_inbox');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Messages: Thread ID */
  $handler->display->display_options['fields']['thread_id']['id'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['table'] = 'pm_index';
  $handler->display->display_options['fields']['thread_id']['field'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['thread_id']['separator'] = '';
  /* Field: Messages: Is new */
  $handler->display->display_options['fields']['is_new']['id'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['table'] = 'pm_index';
  $handler->display->display_options['fields']['is_new']['field'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['label'] = '';
  $handler->display->display_options['fields']['is_new']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_new']['not'] = 0;
  /* Field: Messages: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'pm_message';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Messages: Recipient */
  $handler->display->display_options['fields']['recipient']['id'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['fields']['recipient']['field'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
  /* Field: GoFAST Fields: GoFAST pm recipient */
  $handler->display->display_options['fields']['gofast_recipients']['id'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['table'] = 'pm_message';
  $handler->display->display_options['fields']['gofast_recipients']['field'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['label'] = 'Participants';
  /* Field: Messages: Send date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Actions';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[thread_id]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
  $handler->display->display_options['path'] = 'private-messages';
  $translatables['gofast_private_msg'] = array(
    t('Master'),
    t('Messages'),
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
    t('Thread ID'),
    t('.'),
    t(','),
    t('Subject'),
    t('Participants'),
    t('Send date'),
    t('Operations'),
    t('<a href="del_privatemsg" class="delete_message_ajax" id=\'[thread_id]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>'),
    t('Actions'),
  );
  $export['gofast_private_msg'] = $view;

  $view = new view();
  $view->name = 'gofast_privatemsg';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'pm_message';
  $view->human_name = 'gofast_privatemsg';
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
  $handler->display->display_options['pager']['options']['id'] = '2';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'mid' => 'mid',
    'thread_id' => 'thread_id',
    'is_new' => 'is_new',
    'gofast_author' => 'gofast_author',
    'subject' => 'subject',
    'recipient' => 'recipient',
    'gofast_recipients' => 'gofast_recipients',
    'timestamp' => 'timestamp',
    'author' => 'author',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'mid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'thread_id' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'is_new' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_author' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
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
    'gofast_recipients' => array(
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
    'author' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Relationship: Messages: Recipient */
  $handler->display->display_options['relationships']['recipient']['id'] = 'recipient';
  $handler->display->display_options['relationships']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['relationships']['recipient']['field'] = 'recipient';
  $handler->display->display_options['relationships']['recipient']['required'] = TRUE;
  /* Relationship: Messages: Message index */
  $handler->display->display_options['relationships']['mid']['id'] = 'mid';
  $handler->display->display_options['relationships']['mid']['table'] = 'pm_message';
  $handler->display->display_options['relationships']['mid']['field'] = 'mid';
  /* Field: Messages: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'pm_message';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Messages: Recipient */
  $handler->display->display_options['fields']['recipient']['id'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['fields']['recipient']['field'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
  $handler->display->display_options['fields']['recipient']['separator'] = ' ';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['id'] = 'gofast_views_handler_field_recipients';
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['table'] = 'pm_message';
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['field'] = 'gofast_views_handler_field_recipients';
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['label'] = 'Gofast pm recipient';
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['element_type'] = 'div';
  $handler->display->display_options['fields']['gofast_views_handler_field_recipients']['element_class'] = 'gofast-pm-participants';
  /* Field: Messages: Send date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
  /* Field: Messages: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'pm_message';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Messages: Author */
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
  /* Sort criterion: MAX(Messages: Send date) */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['group_type'] = 'max';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
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
  /* Filter criterion: Messages: Is deleted */
  $handler->display->display_options['filters']['deleted']['id'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
  $handler->display->display_options['filters']['deleted']['field'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['value'] = '0';

  /* Display: Messages */
  $handler = $view->new_display('page', 'Messages', 'gofast_inbox_old');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Messages';
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You haven\'t got any message.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Messages: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'pm_message';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Messages: Is new */
  $handler->display->display_options['fields']['is_new']['id'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['table'] = 'pm_index';
  $handler->display->display_options['fields']['is_new']['field'] = 'is_new';
  $handler->display->display_options['fields']['is_new']['label'] = '';
  $handler->display->display_options['fields']['is_new']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['is_new']['alter']['text'] = '<img id="msg-new-[thread_id]" class="msg-new" src="/sites/all/themes/bootstrap-gofast/img/newMessage.gif" width="16px" height="16px" alt="edit"/>';
  $handler->display->display_options['fields']['is_new']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['is_new']['type'] = 'custom';
  $handler->display->display_options['fields']['is_new']['type_custom_true'] = 'TRUE';
  $handler->display->display_options['fields']['is_new']['not'] = 0;
  /* Field: GoFAST Fields: GoFAST pm author */
  $handler->display->display_options['fields']['gofast_author']['id'] = 'gofast_author';
  $handler->display->display_options['fields']['gofast_author']['table'] = 'pm_message';
  $handler->display->display_options['fields']['gofast_author']['field'] = 'gofast_author';
  $handler->display->display_options['fields']['gofast_author']['label'] = '';
  $handler->display->display_options['fields']['gofast_author']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_author']['text'] = 'Author';
  /* Field: Messages: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'pm_message';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  $handler->display->display_options['fields']['subject']['alter']['text'] = '<a class="ctools-use-modal" href="gofast/nojs/messages/view/[thread_id]">[subject]</a>';
  /* Field: Messages: Recipient */
  $handler->display->display_options['fields']['recipient']['id'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['fields']['recipient']['field'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['relationship'] = 'mid';
  $handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
  $handler->display->display_options['fields']['recipient']['separator'] = ' ';
  /* Field: GoFAST Fields: GoFAST pm recipient */
  $handler->display->display_options['fields']['gofast_recipients']['id'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['table'] = 'pm_message';
  $handler->display->display_options['fields']['gofast_recipients']['field'] = 'gofast_recipients';
  $handler->display->display_options['fields']['gofast_recipients']['element_type'] = 'div';
  $handler->display->display_options['fields']['gofast_recipients']['element_class'] = 'gofast-pm-participants';
  /* Field: MIN(Messages: Send date) */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['group_type'] = 'min';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
  /* Field: Messages: Author */
  $handler->display->display_options['fields']['author']['id'] = 'author';
  $handler->display->display_options['fields']['author']['table'] = 'pm_message';
  $handler->display->display_options['fields']['author']['field'] = 'author';
  $handler->display->display_options['fields']['author']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="del_privatemsg" class="delete_message_ajax" id=\'[thread_id]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'btn fa fa-lg fa-trash-o';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Messages: Is deleted */
  $handler->display->display_options['filters']['deleted']['id'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
  $handler->display->display_options['filters']['deleted']['field'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['value'] = '0';
  $handler->display->display_options['filters']['deleted']['group'] = 1;
  /* Filter criterion: Messages: The pm author ID */
  $handler->display->display_options['filters']['author']['id'] = 'author';
  $handler->display->display_options['filters']['author']['table'] = 'pm_message';
  $handler->display->display_options['filters']['author']['field'] = 'author';
  $handler->display->display_options['filters']['author']['operator'] = 'not in';
  $handler->display->display_options['filters']['author']['value'] = array(
    0 => '1',
  );
  $handler->display->display_options['filters']['author']['group'] = 1;
  /* Filter criterion: Messages: Is new */
  $handler->display->display_options['filters']['is_new']['id'] = 'is_new';
  $handler->display->display_options['filters']['is_new']['table'] = 'pm_index';
  $handler->display->display_options['filters']['is_new']['field'] = 'is_new';
  $handler->display->display_options['filters']['is_new']['value'] = '0';
  $handler->display->display_options['filters']['is_new']['group'] = 1;
  $handler->display->display_options['filters']['is_new']['exposed'] = TRUE;
  $handler->display->display_options['filters']['is_new']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['is_new']['expose']['label'] = 'Show new';
  $handler->display->display_options['filters']['is_new']['expose']['operator'] = 'is_new_op';
  $handler->display->display_options['filters']['is_new']['expose']['identifier'] = 'is_new';
  $handler->display->display_options['filters']['is_new']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: Messages: The pm author ID */
  $handler->display->display_options['filters']['author_1']['id'] = 'author_1';
  $handler->display->display_options['filters']['author_1']['table'] = 'pm_message';
  $handler->display->display_options['filters']['author_1']['field'] = 'author';
  $handler->display->display_options['filters']['author_1']['value'] = '';
  $handler->display->display_options['filters']['author_1']['group'] = 1;
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
  /* Filter criterion: Messages: Subject */
  $handler->display->display_options['filters']['subject']['id'] = 'subject';
  $handler->display->display_options['filters']['subject']['table'] = 'pm_message';
  $handler->display->display_options['filters']['subject']['field'] = 'subject';
  $handler->display->display_options['filters']['subject']['operator'] = 'contains';
  $handler->display->display_options['filters']['subject']['group'] = 1;
  $handler->display->display_options['filters']['subject']['exposed'] = TRUE;
  $handler->display->display_options['filters']['subject']['expose']['operator_id'] = 'subject_op';
  $handler->display->display_options['filters']['subject']['expose']['label'] = 'Subject';
  $handler->display->display_options['filters']['subject']['expose']['operator'] = 'subject_op';
  $handler->display->display_options['filters']['subject']['expose']['identifier'] = 'subject';
  $handler->display->display_options['filters']['subject']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
  );
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'recipient';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  $handler->display->display_options['path'] = 'pm_test';

  /* Display: Notifications */
  $handler = $view->new_display('page', 'Notifications', 'gofast_notifications');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Notifications';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '3';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You haven\'t got any notification.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Messages: Subject */
  $handler->display->display_options['fields']['subject']['id'] = 'subject';
  $handler->display->display_options['fields']['subject']['table'] = 'pm_message';
  $handler->display->display_options['fields']['subject']['field'] = 'subject';
  /* Field: Messages: Recipient */
  $handler->display->display_options['fields']['recipient']['id'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['table'] = 'pm_index';
  $handler->display->display_options['fields']['recipient']['field'] = 'recipient';
  $handler->display->display_options['fields']['recipient']['exclude'] = TRUE;
  $handler->display->display_options['fields']['recipient']['separator'] = ' ';
  /* Field: Messages: Send date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'pm_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'custom';
  $handler->display->display_options['fields']['timestamp']['custom_date_format'] = 'd/m H:i';
  /* Field: Messages: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'pm_message';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Messages: Author */
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
  /* Filter criterion: Messages: The pm author ID */
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
  /* Filter criterion: Messages: Is deleted */
  $handler->display->display_options['filters']['deleted']['id'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['table'] = 'pm_index';
  $handler->display->display_options['filters']['deleted']['field'] = 'deleted';
  $handler->display->display_options['filters']['deleted']['value'] = '0';
  $handler->display->display_options['filters']['deleted']['group'] = 1;
  /* Filter criterion: Messages: Is new */
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
  /* Filter criterion: Messages: Subject */
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
  $translatables['gofast_privatemsg'] = array(
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
    t('Message index'),
    t('Subject'),
    t('.'),
    t(' '),
    t('Gofast pm recipient'),
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
    t('<img id="msg-new-[thread_id]" class="msg-new" src="/sites/all/themes/bootstrap-gofast/img/newMessage.gif" width="16px" height="16px" alt="edit"/>'),
    t('TRUE'),
    t('<a class="ctools-use-modal" href="gofast/nojs/messages/view/[thread_id]">[subject]</a>'),
    t('GoFAST pm recipient'),
    t('<a href="del_privatemsg" class="delete_message_ajax" id=\'[thread_id]\' >
  <i class="glyphicon glyphicon-trash"></i>
</a>
<span class="delete_message_ereur"></span>'),
    t('Show new'),
    t('Privatemsg: Author'),
    t('Notifications'),
    t('You haven\'t got any notification.'),
    t('Is new'),
  );
  $export['gofast_privatemsg'] = $view;

  $view = new view();
  $view->name = 'gofast_recently_read';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gofast Recently Read';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recently Read';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Recently Read: Recently Read */
  $handler->display->display_options['relationships']['node_rr_nid']['id'] = 'node_rr_nid';
  $handler->display->display_options['relationships']['node_rr_nid']['table'] = 'node';
  $handler->display->display_options['relationships']['node_rr_nid']['field'] = 'node_rr_nid';
  $handler->display->display_options['relationships']['node_rr_nid']['required'] = TRUE;
  /* Field: GoFAST Fields: Icon format */
  $handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
  $handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[gofast_format] [title]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Recently Read: Recently Read Date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'recently_read';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['relationship'] = 'node_rr_nid';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Recently Read: Current */
  $handler->display->display_options['filters']['current']['id'] = 'current';
  $handler->display->display_options['filters']['current']['table'] = 'recently_read';
  $handler->display->display_options['filters']['current']['field'] = 'current';
  $handler->display->display_options['filters']['current']['relationship'] = 'node_rr_nid';
  $handler->display->display_options['filters']['current']['value'] = '1';

  /* Display: Recently Read */
  $handler = $view->new_display('block', 'Recently Read', 'block');
  $translatables['gofast_recently_read'] = array(
    t('Master'),
    t('Recently Read'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Icon format'),
    t('[gofast_format] [title]'),
  );
  $export['gofast_recently_read'] = $view;

  $view = new view();
  $view->name = 'gofast_statistics_global';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_statistics_global';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'gofast_statistics_global';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
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
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'statistics/global';
  $translatables['gofast_statistics_global'] = array(
    t('Master'),
    t('gofast_statistics_global'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Group'),
    t('Type'),
    t('Page'),
  );
  $export['gofast_statistics_global'] = $view;

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
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Ascending';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Descending';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'ldap_user_sn' => 'ldap_user_sn',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_departmentnumber_1' => 'ldap_user_departmentnumber_1',
    'ldap_user_o' => 'ldap_user_o',
    'ldap_user_title' => 'ldap_user_title',
    'gofast_views_handler_field_user_directories_user_gofast_role' => 'gofast_views_handler_field_user_directories_user_gofast_role',
    'login' => 'login',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_views_handler_field_user_picture' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_sn' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_givenname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_departmentnumber_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_o' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_views_handler_field_user_directories_user_gofast_role' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'login' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
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
  $handler->display->display_options['fields']['ldap_user_departmentnumber_1']['exclude'] = TRUE;
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
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  /* Field: GoFAST Fields: Link to add friend */
  $handler->display->display_options['fields']['gofast_link_add_relationship']['id'] = 'gofast_link_add_relationship';
  $handler->display->display_options['fields']['gofast_link_add_relationship']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_link_add_relationship']['field'] = 'gofast_link_add_relationship';
  /* Field: GoFAST Fields: Quick action on the user */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['id'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['field'] = 'gofast_views_handler_field_user_quick_actions';
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

  /* Display: inactive users */
  $handler = $view->new_display('page', 'inactive users', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Inactives User Directory';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['empty'] = '-';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: User: Lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = 'Last name';
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_sn']['empty'] = '-';
  /* Field: User: Firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = 'First name';
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_givenname']['empty'] = '-';
  /* Field: User: Company */
  $handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['label'] = 'Entity';
  $handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_o']['empty'] = '-';
  /* Field: User: Title */
  $handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ldap_user_title']['empty'] = '-';
  /* Field: GoFAST Fields: Default GoFAST Role */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['id'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['field'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['label'] = 'Role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['empty'] = '-';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['login']['empty'] = '-';
  $handler->display->display_options['fields']['login']['date_format'] = 'short';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'privatemsg_current_day';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['empty'] = '-';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Champ: Champs GoFAST : Action rapide sur l'utilisateur */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['id'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['field'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
  $handler->display->display_options['filters']['access']['value']['value'] = '-3 months';
  $handler->display->display_options['filters']['access']['value']['type'] = 'offset';
  $handler->display->display_options['filters']['access']['group'] = 1;
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['operator'] = 'not in';
  $handler->display->display_options['filters']['uid']['value'] = array(
    0 => 0,
  );
  $handler->display->display_options['filters']['uid']['group'] = 1;
  /* Filter criterion: User: Company (ldap_user_o) */
  $handler->display->display_options['filters']['ldap_user_o_value']['id'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['filters']['ldap_user_o_value']['field'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator_id'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['label'] = 'Company';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['identifier'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Created date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'users';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Created date';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Firstname (ldap_user_givenname) */
  $handler->display->display_options['filters']['ldap_user_givenname_value']['id'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['field'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator_id'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['label'] = 'First name';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['identifier'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Last login */
  $handler->display->display_options['filters']['login']['id'] = 'login';
  $handler->display->display_options['filters']['login']['table'] = 'users';
  $handler->display->display_options['filters']['login']['field'] = 'login';
  $handler->display->display_options['filters']['login']['exposed'] = TRUE;
  $handler->display->display_options['filters']['login']['expose']['operator_id'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['label'] = 'Last login';
  $handler->display->display_options['filters']['login']['expose']['operator'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['identifier'] = 'login';
  $handler->display->display_options['filters']['login']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['filters']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['filters']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator_id'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['identifier'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['path'] = 'inactive_users';

  /* Display: user grid contrib */
  $handler = $view->new_display('page', 'user grid contrib', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Actives Contributors';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: User: Firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = 'First name';
  $handler->display->display_options['fields']['ldap_user_givenname']['element_label_colon'] = FALSE;
  /* Field: User: Lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = 'Last name';
  $handler->display->display_options['fields']['ldap_user_sn']['element_label_colon'] = FALSE;
  /* Field: User: Company */
  $handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['element_label_colon'] = FALSE;
  /* Field: User: Title */
  $handler->display->display_options['fields']['ldap_user_title']['id'] = 'ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['table'] = 'field_data_ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['field'] = 'ldap_user_title';
  $handler->display->display_options['fields']['ldap_user_title']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Default GoFAST Role */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['id'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['field'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['label'] = 'Role';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['date_format'] = 'short';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Userpoints total: Current total points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = 'Userpoints';
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
  /* Filter criterion: User: Company (ldap_user_o) */
  $handler->display->display_options['filters']['ldap_user_o_value']['id'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['filters']['ldap_user_o_value']['field'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator_id'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['label'] = 'Company';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['identifier'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Created date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'users';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Created date';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Firstname (ldap_user_givenname) */
  $handler->display->display_options['filters']['ldap_user_givenname_value']['id'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['field'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator_id'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['label'] = 'Firstname';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['identifier'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Last login */
  $handler->display->display_options['filters']['login']['id'] = 'login';
  $handler->display->display_options['filters']['login']['table'] = 'users';
  $handler->display->display_options['filters']['login']['field'] = 'login';
  $handler->display->display_options['filters']['login']['exposed'] = TRUE;
  $handler->display->display_options['filters']['login']['expose']['operator_id'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['label'] = 'Last login';
  $handler->display->display_options['filters']['login']['expose']['operator'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['identifier'] = 'login';
  $handler->display->display_options['filters']['login']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['filters']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['filters']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator_id'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['label'] = 'Lastname';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['identifier'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
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
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['label'] = '';
  $handler->display->display_options['fields']['login']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['login']['date_format'] = 'privatemsg_years';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'privatemsg_current_day';
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
  $handler->display->display_options['fields']['ldap_user_departmentnumber_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['ldap_user_departmentnumber_1']['alter']['text'] = ' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>';
  $handler->display->display_options['fields']['ldap_user_departmentnumber_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Quick action on the user */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['id'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['field'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: Link to add friend */
  $handler->display->display_options['fields']['gofast_link_add_relationship_1']['id'] = 'gofast_link_add_relationship_1';
  $handler->display->display_options['fields']['gofast_link_add_relationship_1']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_link_add_relationship_1']['field'] = 'gofast_link_add_relationship';
  $handler->display->display_options['fields']['gofast_link_add_relationship_1']['label'] = '';
  $handler->display->display_options['fields']['gofast_link_add_relationship_1']['element_label_colon'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['override_name'] = TRUE;
  /* Field: GoFAST Fields: Link to subscribe to the user */
  $handler->display->display_options['fields']['gofast_views_handler_field_subscribe_user']['id'] = 'gofast_views_handler_field_subscribe_user';
  $handler->display->display_options['fields']['gofast_views_handler_field_subscribe_user']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_subscribe_user']['field'] = 'gofast_views_handler_field_subscribe_user';
  /* Field: Userpoints total: Current total points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = '';
  $handler->display->display_options['fields']['points']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['points']['separator'] = '';
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
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['block_description'] = 'Single Profile';

  /* Display: User list */
  $handler = $view->new_display('page', 'User list', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'User Lists';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['relationship'] = 'og_membership_related_node_group';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['type']['value'] = array(
    'userlist' => 'userlist',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['path'] = 'userlists_directory';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Directory';
  $handler->display->display_options['menu']['description'] = 'User\'s directory';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: User Directory Table */
  $handler = $view->new_display('page', 'User Directory Table', 'user_directory');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'gofast_views_handler_field_user_picture' => 'gofast_views_handler_field_user_picture',
    'ldap_user_sn' => 'ldap_user_sn',
    'ldap_user_givenname' => 'ldap_user_givenname',
    'ldap_user_o' => 'ldap_user_o',
    'status' => 'status',
    'gofast_views_handler_field_user_directories_user_gofast_role' => 'gofast_views_handler_field_user_directories_user_gofast_role',
    'login' => 'login',
    'created' => 'created',
    'points' => 'points',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'gofast_views_handler_field_user_picture' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_sn' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_givenname' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ldap_user_o' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'gofast_views_handler_field_user_directories_user_gofast_role' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'login' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'points' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: GoFAST Fields: GoFAST user picture */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['id'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['field'] = 'gofast_views_handler_field_user_picture';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['gofast_views_handler_field_user_picture']['dimensions'] = '40';
  /* Field: User: Lastname */
  $handler->display->display_options['fields']['ldap_user_sn']['id'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['field'] = 'ldap_user_sn';
  $handler->display->display_options['fields']['ldap_user_sn']['label'] = 'Last name';
  $handler->display->display_options['fields']['ldap_user_sn']['empty'] = '-';
  /* Field: User: Firstname */
  $handler->display->display_options['fields']['ldap_user_givenname']['id'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['field'] = 'ldap_user_givenname';
  $handler->display->display_options['fields']['ldap_user_givenname']['label'] = 'First name';
  $handler->display->display_options['fields']['ldap_user_givenname']['empty'] = '-';
  /* Field: User: Company */
  $handler->display->display_options['fields']['ldap_user_o']['id'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['field'] = 'ldap_user_o';
  $handler->display->display_options['fields']['ldap_user_o']['label'] = 'Entity';
  /* Field: User: Active */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'users';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['label'] = 'Status';
  $handler->display->display_options['fields']['status']['type'] = 'active-blocked';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: GoFAST Fields: Default GoFAST Role */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['id'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['field'] = 'gofast_views_handler_field_user_directories_user_gofast_role';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_directories_user_gofast_role']['label'] = 'Role';
  /* Field: User: Last login */
  $handler->display->display_options['fields']['login']['id'] = 'login';
  $handler->display->display_options['fields']['login']['table'] = 'users';
  $handler->display->display_options['fields']['login']['field'] = 'login';
  $handler->display->display_options['fields']['login']['empty'] = '-';
  $handler->display->display_options['fields']['login']['date_format'] = 'short';
  $handler->display->display_options['fields']['login']['second_date_format'] = 'privatemsg_current_day';
  /* Field: User: Created date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'users';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['empty'] = '-';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'privatemsg_current_day';
  /* Field: Userpoints total: Current total points */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'userpoints_total';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['label'] = 'Points';
  /* Field: GoFAST Fields: Quick action on the user */
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['id'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['table'] = 'users';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['field'] = 'gofast_views_handler_field_user_quick_actions';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['label'] = '';
  $handler->display->display_options['fields']['gofast_views_handler_field_user_quick_actions']['element_label_colon'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
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
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Lastname (ldap_user_sn) */
  $handler->display->display_options['filters']['ldap_user_sn_value']['id'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['table'] = 'field_data_ldap_user_sn';
  $handler->display->display_options['filters']['ldap_user_sn_value']['field'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['ldap_user_sn_value']['group'] = 1;
  $handler->display->display_options['filters']['ldap_user_sn_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator_id'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['label'] = 'Lastname (ldap_user_sn)';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['operator'] = 'ldap_user_sn_value_op';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['identifier'] = 'ldap_user_sn_value';
  $handler->display->display_options['filters']['ldap_user_sn_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Firstname (ldap_user_givenname) */
  $handler->display->display_options['filters']['ldap_user_givenname_value']['id'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['table'] = 'field_data_ldap_user_givenname';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['field'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['group'] = 1;
  $handler->display->display_options['filters']['ldap_user_givenname_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator_id'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['label'] = 'Firstname (ldap_user_givenname)';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['operator'] = 'ldap_user_givenname_value_op';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['identifier'] = 'ldap_user_givenname_value';
  $handler->display->display_options['filters']['ldap_user_givenname_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Company (ldap_user_o) */
  $handler->display->display_options['filters']['ldap_user_o_value']['id'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['table'] = 'field_data_ldap_user_o';
  $handler->display->display_options['filters']['ldap_user_o_value']['field'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['group'] = 1;
  $handler->display->display_options['filters']['ldap_user_o_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator_id'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['label'] = 'Company (ldap_user_o)';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['operator'] = 'ldap_user_o_value_op';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['identifier'] = 'ldap_user_o_value';
  $handler->display->display_options['filters']['ldap_user_o_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Last login */
  $handler->display->display_options['filters']['login']['id'] = 'login';
  $handler->display->display_options['filters']['login']['table'] = 'users';
  $handler->display->display_options['filters']['login']['field'] = 'login';
  $handler->display->display_options['filters']['login']['operator'] = 'between';
  $handler->display->display_options['filters']['login']['group'] = 1;
  $handler->display->display_options['filters']['login']['exposed'] = TRUE;
  $handler->display->display_options['filters']['login']['expose']['operator_id'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['label'] = 'Last login';
  $handler->display->display_options['filters']['login']['expose']['operator'] = 'login_op';
  $handler->display->display_options['filters']['login']['expose']['identifier'] = 'login';
  $handler->display->display_options['filters']['login']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Created date */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'users';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = 'between';
  $handler->display->display_options['filters']['created']['group'] = 1;
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date de création';
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Active';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  $handler->display->display_options['path'] = 'user_listing_tab';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Directory';
  $handler->display->display_options['menu']['description'] = 'User\'s directory';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['gofast_user_directory'] = array(
    t('Master'),
    t('inactive_users'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Ascending'),
    t('Descending'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('No results'),
    t('<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>'),
    t('Group node from OG membership'),
    t('[ldap_user_givenname] [ldap_user_sn]'),
    t(' <tr><td id="orga" > [ldap_user_departmentnumber_1-value] </td></tr>
</table></td></tr><tr><td colspan="2">[signature]</td></tr>'),
    t('Send message'),
    t('GoFAST user picture'),
    t('Link to add friend'),
    t('Quick action on the user'),
    t('All'),
    t('Nom'),
    t('inactive users'),
    t('Inactives User Directory'),
    t('-'),
    t('Last name'),
    t('First name'),
    t('Entity'),
    t('Title'),
    t('Role'),
    t('Last login'),
    t('Created date'),
    t('Company'),
    t('user grid contrib'),
    t('Actives Contributors'),
    t('Uid'),
    t('Userpoints'),
    t('.'),
    t(','),
    t('Firstname'),
    t('Lastname'),
    t('Single Profile'),
    t('Link to subscribe to the user'),
    t('User list'),
    t('User Lists'),
    t('Description'),
    t('Name'),
    t('User Directory Table'),
    t('Status'),
    t('Points'),
    t('Lastname (ldap_user_sn)'),
    t('Firstname (ldap_user_givenname)'),
    t('Company (ldap_user_o)'),
    t('Date de création'),
    t('Active'),
  );
  $export['gofast_user_directory'] = $view;

  $view = new view();
  $view->name = 'gofast_userlist_creator_contributor';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_userlist_creator_contributor';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Userlists_administrators';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
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
  $handler->display->display_options['style_options']['row_class'] = 'col-md-5';
  $handler->display->display_options['style_options']['columns'] = '5';
  $handler->display->display_options['style_options']['fill_single_line'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  /* Relationship: OG membership: Group OG membership type from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['id'] = 'og_membership_related_og_membership_type_group';
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['field'] = 'og_membership_related_og_membership_type_group';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: OG membership from Node group */
  $handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
  /* Field: Content: Author uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'node';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'userlist' => 'userlist',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Userlists_creator */
  $handler = $view->new_display('page', 'Userlists_creator', 'gofast_userlist_creator');
  $handler->display->display_options['path'] = 'gofast-userlist-creator/%';
  $handler->display->display_options['menu']['title'] = 'Directory';
  $handler->display->display_options['menu']['description'] = 'User\'s directory';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Userlists_administrators */
  $handler = $view->new_display('page', 'Userlists_administrators', 'gofast_userlist_administrator');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  /* Relationship: OG membership: Group OG membership type from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['id'] = 'og_membership_related_og_membership_type_group';
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_og_membership_type_group']['field'] = 'og_membership_related_og_membership_type_group';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: OG membership: OG membership from Node group */
  $handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_members_target_id']['id'] = 'field_members_target_id';
  $handler->display->display_options['relationships']['field_members_target_id']['table'] = 'field_data_field_members';
  $handler->display->display_options['relationships']['field_members_target_id']['field'] = 'field_members_target_id';
  $handler->display->display_options['relationships']['field_members_target_id']['label'] = 'Entité Utilisateur réferencée par field_members';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: OG membership: Entity id */
  $handler->display->display_options['fields']['etid']['id'] = 'etid';
  $handler->display->display_options['fields']['etid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['etid']['field'] = 'etid';
  $handler->display->display_options['fields']['etid']['relationship'] = 'og_membership_rel_group';
  $handler->display->display_options['fields']['etid']['label'] = 'Id de l\'entité';
  $handler->display->display_options['path'] = 'gofast-userlist-administrators/%';
  $handler->display->display_options['menu']['title'] = 'Directory';
  $handler->display->display_options['menu']['description'] = 'User\'s directory';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['gofast_userlist_creator_contributor'] = array(
    t('Master'),
    t('Userlists_administrators'),
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
    t('user from OG membership'),
    t('Group og_membership_type from OG membership'),
    t('OG membership from node'),
    t('OG membership from node group'),
    t('Author uid'),
    t('All'),
    t('Userlists_creator'),
    t('Entité Utilisateur réferencée par field_members'),
    t('Id de l\'entité'),
    t('.'),
    t(','),
  );
  $export['gofast_userlist_creator_contributor'] = $view;

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
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_description' => 'field_description',
    'uid' => 'uid',
    'field_userlist_ulid' => 'field_userlist_ulid',
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
    'field_description' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'uid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_userlist_ulid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Nom';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Description */
  $handler->display->display_options['fields']['field_description']['id'] = 'field_description';
  $handler->display->display_options['fields']['field_description']['table'] = 'field_data_field_description';
  $handler->display->display_options['fields']['field_description']['field'] = 'field_description';
  /* Field: Userlist admins: Userlist admins */
  $handler->display->display_options['fields']['gofast_userlist_handler_field_userlist_directories_userlist_number_members']['id'] = 'gofast_userlist_handler_field_userlist_directories_userlist_number_members';
  $handler->display->display_options['fields']['gofast_userlist_handler_field_userlist_directories_userlist_number_members']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gofast_userlist_handler_field_userlist_directories_userlist_number_members']['field'] = 'gofast_userlist_handler_field_userlist_directories_userlist_number_members';
  $handler->display->display_options['fields']['gofast_userlist_handler_field_userlist_directories_userlist_number_members']['label'] = 'Admins';
  /* Field: Userlist members: Userlist members */
  $handler->display->display_options['fields']['gofast_userlist_number_members']['id'] = 'gofast_userlist_number_members';
  $handler->display->display_options['fields']['gofast_userlist_number_members']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gofast_userlist_number_members']['field'] = 'gofast_userlist_number_members';
  $handler->display->display_options['fields']['gofast_userlist_number_members']['label'] = 'Members';
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

  /* Display: Userlists */
  $handler = $view->new_display('page', 'Userlists', 'page_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    5 => '5',
  );
  $handler->display->display_options['path'] = 'userlists_tab';
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
    t('<h2><?php echo t("No results availables", array(), array("context" => "gofast:gofast_integrity")); ?></h2>'),
    t('Nom'),
    t('Description'),
    t('Admins'),
    t('Members'),
  );
  $export['gofast_userlist_directory'] = $view;

  $view = new view();
  $view->name = 'gofast_userlist_members';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'gofast_userlists';
  $view->human_name = 'gofast_userlist_members';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'gofast_userlist_members';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['style_options']['columns'] = '5';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User List: userlist_members */
  $handler->display->display_options['fields']['field_userlist_members']['id'] = 'field_userlist_members';
  $handler->display->display_options['fields']['field_userlist_members']['table'] = 'field_data_field_userlist_members';
  $handler->display->display_options['fields']['field_userlist_members']['field'] = 'field_userlist_members';
  /* Contextual filter: User List: User list ID */
  $handler->display->display_options['arguments']['ulid']['id'] = 'ulid';
  $handler->display->display_options['arguments']['ulid']['table'] = 'gofast_userlists';
  $handler->display->display_options['arguments']['ulid']['field'] = 'ulid';
  $handler->display->display_options['arguments']['ulid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['ulid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['ulid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['ulid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'gofast_userlist_members_displays');
  $handler->display->display_options['path'] = 'gofast-userlist-members/%';

  /* Display: Page 2 */
  $handler = $view->new_display('page', 'Page 2', 'page_1');
  $handler->display->display_options['path'] = 'gofast-userlist-members/%';
  $translatables['gofast_userlist_members'] = array(
    t('Master'),
    t('gofast_userlist_members'),
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
    t('userlist_members'),
    t('All'),
    t('Page'),
    t('Page 2'),
  );
  $export['gofast_userlist_members'] = $view;

  $view = new view();
  $view->name = 'gofast_views';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gofast_views';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'content_statut';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'table';
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
  /* Field: Content: reference */
  $handler->display->display_options['fields']['field_reference']['id'] = 'field_reference';
  $handler->display->display_options['fields']['field_reference']['table'] = 'field_data_field_reference';
  $handler->display->display_options['fields']['field_reference']['field'] = 'field_reference';
  $handler->display->display_options['fields']['field_reference']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_reference']['alter']['text'] = 'Telecharger';
  $handler->display->display_options['fields']['field_reference']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_reference']['alter']['path'] = 'cmis/browser?id=[field_reference]';
  /* Field: GoFAST Fields: Download link */
  $handler->display->display_options['fields']['gofast_download_link']['id'] = 'gofast_download_link';
  $handler->display->display_options['fields']['gofast_download_link']['table'] = 'node';
  $handler->display->display_options['fields']['gofast_download_link']['field'] = 'gofast_download_link';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::node_make_sticky_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete (fake unpublish)',
    ),
  );
  /* Sort criterion: Content: Comment status */
  $handler->display->display_options['sorts']['comment']['id'] = 'comment';
  $handler->display->display_options['sorts']['comment']['table'] = 'node';
  $handler->display->display_options['sorts']['comment']['field'] = 'comment';
  $handler->display->display_options['sorts']['comment']['expose']['label'] = 'Comment status';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Has taxonomy term';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'state';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Has taxonomy term */
  $handler->display->display_options['filters']['tid']['id'] = 'tid';
  $handler->display->display_options['filters']['tid']['table'] = 'taxonomy_index';
  $handler->display->display_options['filters']['tid']['field'] = 'tid';
  $handler->display->display_options['filters']['tid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['tid']['value'] = array(
    32 => '32',
    31 => '31',
    29 => '29',
    30 => '30',
  );
  $handler->display->display_options['filters']['tid']['expose']['operator_id'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['label'] = 'Has taxonomy term';
  $handler->display->display_options['filters']['tid']['expose']['operator'] = 'tid_op';
  $handler->display->display_options['filters']['tid']['expose']['identifier'] = 'tid';
  $handler->display->display_options['filters']['tid']['reduce_duplicates'] = TRUE;
  $handler->display->display_options['filters']['tid']['type'] = 'select';
  $handler->display->display_options['filters']['tid']['vocabulary'] = 'state';
  $translatables['gofast_views'] = array(
    t('Master'),
    t('content_statut'),
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
    t('Title'),
    t('Status'),
    t('Date'),
    t('reference'),
    t('Telecharger'),
    t('Download link'),
    t('Content'),
    t('- Choose an operation -'),
    t('Delete (fake unpublish)'),
    t('Comment status'),
    t('Has taxonomy term'),
    t('Block'),
    t('‹ ‹'),
    t('› ›'),
  );
  $export['gofast_views'] = $view;

  $view = new view();
  $view->name = 'upcoming';
  $view->description = 'Displays upcoming meetings, deadlines..';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Upcoming';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming meetings';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '7';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹';
  $handler->display->display_options['pager']['options']['tags']['next'] = '›';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'field_date' => 'field_date',
    'title' => 'title',
    'field_linked_folders' => 'field_linked_folders',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_date' => array(
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
    'field_linked_folders' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = FALSE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Deadline (field_date) */
  $handler->display->display_options['sorts']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['sorts']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['sorts']['field_date_value']['field'] = 'field_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Deadline (field_date) */
  $handler->display->display_options['filters']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['filters']['field_date_value']['field'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_date_value']['granularity'] = 'minute';
  $handler->display->display_options['filters']['field_date_value']['default_date'] = 'now -1 day';
  $handler->display->display_options['filters']['field_date_value']['year_range'] = '-0:+10';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'conference' => 'conference',
  );

  /* Display: Upcoming meetings */
  $handler = $view->new_display('page', 'Upcoming meetings', 'upcoming_meetings');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Linked folders */
  $handler->display->display_options['fields']['field_linked_folders']['id'] = 'field_linked_folders';
  $handler->display->display_options['fields']['field_linked_folders']['table'] = 'field_data_field_linked_folders';
  $handler->display->display_options['fields']['field_linked_folders']['field'] = 'field_linked_folders';
  $handler->display->display_options['fields']['field_linked_folders']['label'] = '';
  $handler->display->display_options['fields']['field_linked_folders']['element_class'] = 'gofast_display_none';
  $handler->display->display_options['fields']['field_linked_folders']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_linked_folders']['delta_offset'] = '0';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_class'] = 'gofast_display_none';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'upcoming-meetings';

  /* Display: Upcoming deadlines */
  $handler = $view->new_display('page', 'Upcoming deadlines', 'upcoming_deadlines');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming deadlines';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Deadline */
  $handler->display->display_options['fields']['field_date']['id'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['table'] = 'field_data_field_date';
  $handler->display->display_options['fields']['field_date']['field'] = 'field_date';
  $handler->display->display_options['fields']['field_date']['label'] = '';
  $handler->display->display_options['fields']['field_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_date']['type'] = 'date_plain';
  $handler->display->display_options['fields']['field_date']['settings'] = array(
    'format_type' => 'custom',
    'custom_date_format' => '',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_remaining_days' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_class'] = 'gofast_display_none';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Deadline (field_date) */
  $handler->display->display_options['filters']['field_date_value']['id'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['table'] = 'field_data_field_date';
  $handler->display->display_options['filters']['field_date_value']['field'] = 'field_date_value';
  $handler->display->display_options['filters']['field_date_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_date_value']['granularity'] = 'minute';
  $handler->display->display_options['filters']['field_date_value']['default_date'] = 'now -1 day';
  $handler->display->display_options['filters']['field_date_value']['year_range'] = '-0:+10';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'alfresco_item' => 'alfresco_item',
  );
  $handler->display->display_options['path'] = 'upcoming-meetings';
  $translatables['upcoming'] = array(
    t('Master'),
    t('Upcoming meetings'),
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
    t('‹'),
    t('›'),
    t('last »'),
    t('Group node from OG membership'),
    t('Title'),
    t('Upcoming deadlines'),
  );
  $export['upcoming'] = $view;

  return $export;
}
