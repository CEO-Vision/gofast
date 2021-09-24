<?php

/**
 * @file
 *  Describes data tables (or the equivalent) to Views.
 */

/**
 * Implements hook_views_data().
 */
function gofast_views_views_data() {
  $data = array();

  // Download link.
  $data['node']['gofast_download_link'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Download link', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to download the document.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_download_link',
    )
  );

  $data['node']['delete_node_modal'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Delete link modal', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to delete the content with modal confirmation.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_link_delete_modal',
    )
  );

  $data['node']['gofast_edit_mode'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast:')),
    'field' => array(
      'title' => t('Edit mode link', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to go into edit mode.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_link_edit_mode',
    )
  );

  $data['node']['gofast_new_version_link'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to replace it with a new version', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to the document replaced by a new version.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_link_new_version',
    )
  );

  $data['node']['gofast_manage_keywords'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to manage keywords', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to manage keywords.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_link_manage_keywords',
    )
  );


  $data['node']['gofast_filter_group_title'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'title' => t('Group nid', array(), array('context' => 'gofast')),
    'help' => t('The group title.', array(), array('context' => 'gofast')),
    'filter' => array(
      'field' => 'nid',
      'handler' => 'gofast_views_handler_filter_group_title',
    )
  );

  $data['node']['gofast_block_file_management'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Block file management', array(), array('context' => 'gofast')),
      'help' => t('Provide a block of buttons to manage the files.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_block_file_management',
    )
  );

  $data['node']['gofast_edit'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Edit link', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to edit.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_link_edit',
    )
  );

  $data['node']['gofast_format'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Icon format', array(), array('context' => 'gofast')),
      'help' => t('Provide a content icon format.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_format',
    )
  );

  $data['node']['gofast_last_modifier'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Node last modifier', array(), array('context' => 'gofast')),
      'help' => t('Retrieve the node last modifier picture.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_last_modifier',
    )
  );

  $data['node']['gofast_last_event'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Node last event', array(), array('context' => 'gofast')),
      'help' => t('Retrieve the node last event.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_last_event',
    )
  );

    $data['node']['gofast_taxo_state'] = array(
    'group' => t('GoFAST Fields Taxonomy State', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Taxonomy State', array(), array('context' => 'gofast')),
      'help' => t('Retrieve the node taxonomy state.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_taxonomy_state',
    )
  );

  $data['users']['gofast_link_add_relationship'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to add friend', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to become a friend.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_relationships_link_add_relationship',
    )
  );

  $data['users']['gofast_user_mobilephone'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to call', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to call the user.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_mobilephone',
    )
  );

  $data['users']['gofast_views_handler_field_user_new_message'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to write new message', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to write a new message to the user.', array(), array('context' => 'gofast')),
    )
  );

  $data['users']['gofast_views_handler_field_subscribe_user'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Link to subscribe to the user', array(), array('context' => 'gofast')),
      'help' => t('Provide a simple link to subscribe to the user.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_subscribe_user',
    )
  );

  $data['users']['gofast_views_handler_field_user_quick_actions'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Quick action on the user', array(), array('context' => 'gofast')),
      'help' => t('Provide a block of buttons to quick actions on the user.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_quick_actions',
    )
  );

  $data['users']['gofast_user_relationships'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'title' => t('My relationships', array(), array('context' => 'gofast')),
    'help' => t('Filters the user\'s approved relationships', array(), array('context' => 'gofast')),
    'filter' => array(
      'field' => 'uid', // sur quel champs faire la jointure s'il y a (le filtre)
      'handler' => 'gofast_views_handler_filter_user_relationships',
    )
  );

  $data['users']['gofast_views_handler_field_user_picture'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('GoFAST user picture', array(), array('context' => 'gofast')),
      'help' => t('Provide themed user picture.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_picture',
    )
  );

  $data['users']['gofast_views_handler_field_user_roles'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('GoFAST user roles', array(), array('context' => 'gofast')),
      'help' => t('Display GoFAST (non-technical) user roles.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_roles',
    )
  );

  $data['users']['gofast_views_handler_field_user_og_roles'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('GoFAST user OG roles', array(), array('context' => 'gofast')),
      'help' => t('Display GoFAST (non-technical) user OG roles, given a space (OG group) context.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_og_roles',
    )
  );


  /**
   * Directories views
   */

  $data['users']['gofast_views_handler_field_user_directories_user_gofast_role'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Default GoFAST Role', array(), array('context' => 'gofast')),
      'help' => t('The default GoFAST Role', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_user_directories_user_gofast_role',
    ),
  );
  //// pm_message handlers

  $data['pm_message']['table']['group'] = t('Messages');

  $data['pm_message']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('Private messages', array(), array('context' => 'gofast')),
    'help' => t('Private messages sent between users.', array(), array('context' => 'gofast')),
    'defaults' => array(
      'field' => 'body',
    )
  );

  $data['pm_message']['table']['entity type'] = 'privatemsg_message';

  $data['pm_message']['table']['join'] = array(
    'pm_index' => array(
      'left_table' => 'pm_index',
      'left_field' => 'mid',
      'field' => 'mid',
    )
  );

  $data['pm_message']['mid'] = array(
    'title' => t('Message ID', array(), array('context' => 'gofast')),
    'help' => t('The private message ID.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'pm_index',
      'field' => 'mid',
      'handler' => 'views_handler_relationship',
      'label' => t('Message index', array(), array('context' => 'gofast')),
      'title' => t('Message index', array(), array('context' => 'gofast')),
      'help' => t('Relate the message to threading info.', array(), array('context' => 'gofast')),
    ),
  );

  $data['pm_message']['author'] = array(
    'title' => t('Author', array(), array('context' => 'gofast')),
    'help' => t('The private message author.', array(), array('context' => 'gofast')),
    'field' => array(
      'help' => t('The UID of the private message author.', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'title' => t('The pm author ID', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_filter_user_name',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'author',
      'handler' => 'views_handler_relationship',
      'label' => t('Author', array(), array('context' => 'gofast')),
      'help' => t('Relate to the user who sent the private message.', array(), array('context' => 'gofast')),
    )
  );

  $data['pm_message']['subject'] = array(
    'title' => t('Subject', array(), array('context' => 'gofast')),
    'help' => t('The subject of the private message.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'gofast_views_handler_field_pm_subject',
      'format' => array('field' => 'format'),
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );

  $data['pm_message']['body'] = array(
    'title' => t('Message', array(), array('context' => 'gofast')),
    'help' => t('The text of the private message.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'gofast_views_handler_field_pm_body',
      'format' => array('field' => 'format'),
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    )
  );

  $data['pm_message']['timestamp'] = array(
    'title' => t('Send date', array(), array('context' => 'gofast')),
    'help' => t('The date and time when the message was sent.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_date',
    )
  );

  $data['pm_index']['table']['group'] = t('Messages', array(), array('context' => 'gofast'));

  $data['pm_index']['table']['base'] = array(
    'field' => 'thread_id',
    'title' => t('Privatemsg threading index', array(), array('context' => 'gofast')),
    'defaults' => array(
      'field' => 'thread_id',
    )
  );

  $data['pm_index']['table']['join'] = array(
    'pm_message' => array(
      'left_table' => 'pm_message',
      'left_field' => 'mid',
      'field' => 'mid',
    )
  );

  $data['pm_index']['table']['entity type'] = 'privatemsg_message';

  $data['pm_index']['thread_id'] = array(
    'title' => t('Thread ID', array(), array('context' => 'gofast')),
    'help' => t('The ID of the private message thread.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'help' => t('Filter according to the thread privatemsgs belong to.', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_argument_many_to_one',
    )
  );

  $data['pm_index']['thread_link'] = array(
    'real field' => 'thread_id',
    'title' => t('Link to thread', array(), array('context' => 'gofast')),
    'help' => t('A link to the private message thread.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'gofast_views_handler_field_pm_thread_link',
    )
  );

  $data['pm_index']['recipient'] = array(
    'title' => t('Recipient', array(), array('context' => 'gofast')),
    'field' => array(
      'help' => t('The UID of the private message recipient.', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'help' => t("Filter according to the recipient's uid.", array(), array('context' => 'gofast')),
      'handler' => 'views_handler_argument_user_uid',
    ),
    'relationship' => array(
      'base' => 'users',
      'field' => 'recipient',
      'handler' => 'views_handler_relationship',
      'label' => t('Recipient', array(), array('context' => 'gofast')),
      'help' => t('Relate to the user receiving the private message.', array(), array('context' => 'gofast')),
    )
  );

  $data['pm_index']['is_new'] = array(
    'title' => t('Is new', array(), array('context' => 'gofast')),
    'help' => t('Whether the private message is unread.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'help' => t('Filter to private messages that have/have not been read.', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Show new', array(), array('context' => 'gofast')),
      'type' => 'yes-no',
    )
  );

  $data['pm_index']['deleted'] = array(
    'title' => t('Is deleted', array(), array('context' => 'gofast')),
    'help' => t('Whether the private message has been deleted.', array(), array('context' => 'gofast')),
    'field' => array(
      'handler' => 'views_handler_field_boolean',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'help' => t('Filter to private messages that have/have not been deleted.', array(), array('context' => 'gofast')),
      'handler' => 'views_handler_filter_boolean_operator',
      'label' => t('Show deleted', array(), array('context' => 'gofast')),
      'type' => 'yes-no',
    )
  );

  $data['pm_message']['gofast_recipients'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('GoFAST pm recipient', array(), array('context' => 'gofast')),
      'help' => t('Provide pm recicpient.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_recipients',
    )
  );

  $data['pm_message']['gofast_author'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('GoFAST pm author', array(), array('context' => 'gofast')),
      'help' => t('Provide pm author.', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_pm_author',
    )
  );

  $data['node']['gofast_mobile_activity_feed_view'] = array(
    'group' => t('GoFAST Fields', array(), array('context' => 'gofast')),
    'field' => array(
      'title' => t('Title', array(), array('context' => 'gofast')),
      'help' => t('The data is rendered into this field', array(), array('context' => 'gofast')),
      'handler' => 'gofast_views_handler_field_node_gofast_mobile_activity_feed',
    )
  );
  return $data;
}
