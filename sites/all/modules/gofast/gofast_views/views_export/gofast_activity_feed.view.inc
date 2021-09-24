<?php
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
/* Relationship: Comment: Comments of the node */
$handler->display->display_options['relationships']['cid']['id'] = 'cid';
$handler->display->display_options['relationships']['cid']['table'] = 'node';
$handler->display->display_options['relationships']['cid']['field'] = 'cid';
/* Relationship: OG membership: Group Node from OG membership */
$handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
$handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
$handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
/* Relationship: Comment: Comments of the node */
$handler->display->display_options['relationships']['cid_1']['id'] = 'cid_1';
$handler->display->display_options['relationships']['cid_1']['table'] = 'node';
$handler->display->display_options['relationships']['cid_1']['field'] = 'cid';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'node';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
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
$handler->display->display_options['fields']['title']['label'] = 'Titre';
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
$handler->display->display_options['pager']['options']['quantity'] = '9';
$handler->display->display_options['pager']['options']['tags']['previous'] = '‹ ‹';
$handler->display->display_options['pager']['options']['tags']['next'] = '› ›';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Bulk operations: Content */
$handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
$handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
$handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
$handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
  'action::node_assign_owner_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
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
  'action::flag_node_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::node_make_sticky_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::node_make_unsticky_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::private_set_private_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::private_set_public_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_modify_action' => array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
    'settings' => array(
      'show_all_tokens' => 1,
      'display_values' => array(
        'article::field_tags' => 'article::field_tags',
        'alfresco_item::field_tags' => 'alfresco_item::field_tags',
        'forum::field_tags' => 'forum::field_tags',
      ),
    ),
  ),
  'action::views_bulk_operations_move_to_book_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
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
  'action::node_promote_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::node_publish_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::node_unpromote_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::views_bulk_operations_remove_from_book_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::node_save_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
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
  'action::node_unpublish_action' => array(
    'selected' => 1,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 1,
    'label' => 'Delete item',
  ),
  'action::node_unpublish_by_keyword_action' => array(
    'selected' => 0,
    'postpone_processing' => 0,
    'skip_confirmation' => 0,
    'override_label' => 0,
    'label' => '',
  ),
  'action::pathauto_node_update_action' => array(
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
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
/* Field: Gofast Fields: Icon format */
$handler->display->display_options['fields']['gofast_format']['id'] = 'gofast_format';
$handler->display->display_options['fields']['gofast_format']['table'] = 'node';
$handler->display->display_options['fields']['gofast_format']['field'] = 'gofast_format';
$handler->display->display_options['fields']['gofast_format']['exclude'] = TRUE;
/* Field: Gofast Fields: Block file management */
$handler->display->display_options['fields']['gofast_block_file_management']['id'] = 'gofast_block_file_management';
$handler->display->display_options['fields']['gofast_block_file_management']['table'] = 'node';
$handler->display->display_options['fields']['gofast_block_file_management']['field'] = 'gofast_block_file_management';
$handler->display->display_options['fields']['gofast_block_file_management']['exclude'] = TRUE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['exclude'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
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
/* Field: Content: Updated/commented date */
$handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
$handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
$handler->display->display_options['fields']['last_updated']['label'] = 'Date';
$handler->display->display_options['fields']['last_updated']['date_format'] = 'gofast_custom_date';
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
$handler->display->display_options['filter_groups']['operator'] = 'OR';
$handler->display->display_options['filter_groups']['groups'] = array(
  1 => 'AND',
  2 => 'AND',
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
  'alfresco_item' => 'alfresco_item',
  'forum' => 'forum',
  'webform' => 'webform',
);
$handler->display->display_options['filters']['type']['group'] = 1;
/* Filter criterion: Gofast Fields: Group nid */
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

/* Display: activity group feed */
$handler = $view->new_display('block', 'activity group feed', 'block_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'activity group feed';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = 'Nom';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = 'Titre';
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
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
$handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = 'Titre';
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
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = 'Nom';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = 'Titre';
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
$handler->display->display_options['pager']['options']['id'] = '0';
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
/* Field: User: Picture */
$handler->display->display_options['fields']['picture']['id'] = 'picture';
$handler->display->display_options['fields']['picture']['table'] = 'users';
$handler->display->display_options['fields']['picture']['field'] = 'picture';
$handler->display->display_options['fields']['picture']['relationship'] = 'uid';
$handler->display->display_options['fields']['picture']['label'] = '';
$handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['label'] = 'Titre';
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
/* Field: Content: Type */
$handler->display->display_options['fields']['type']['id'] = 'type';
$handler->display->display_options['fields']['type']['table'] = 'node';
$handler->display->display_options['fields']['type']['field'] = 'type';
$handler->display->display_options['fields']['type']['exclude'] = TRUE;
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
  'webform' => 'webform',
);
$handler->display->display_options['block_description'] = 'my forums activity feed';
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
  t('Comments'),
  t('Group node from OG membership'),
  t('author'),
  t('Title'),
  t('Titre'),
  t('Date'),
  t('Parent Groups'),
  t('popularity'),
  t('state'),
  t('activity feed'),
  t('Activity feed'),
  t('Content'),
  t('- Choose an operation -'),
  t('Delete item'),
  t('Type'),
  t('Icon format'),
  t('Block file management'),
  t('<div class="gofast_activity_feed_title"> [gofast_format] [title] </div>
<div class="gofast_activity_feed_handlers">
<span class="gofast_activity_feed_type">[type]</span>
[gofast_block_file_management]
</div>'),
  t('Spaces'),
  t('Popularity'),
  t(','),
  t('State'),
  t('Group title'),
  t('Group nid'),
  t('State (field_state)'),
  t('activity group feed'),
  t('Nom'),
  t('unpublished activity'),
  t('Utilisateur'),
  t('personal activity feed'),
  t('my forums activity feed'),
  t('All'),
);
