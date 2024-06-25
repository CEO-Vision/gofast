<?php


function gofast_contextual_menu_get_all_items($node, $browser_path, $from_tree, $all = FALSE){
  global $base_url; 
  
  $detect = new Mobile_Detect;
  
  // Get path 
  $browser_path_link_folder = parse_url($browser_path);
  
  // Encode path
  $browser_path_link_folder = rawurlencode(rawurldecode($browser_path_link_folder['path']));
  
  // Raplce %2F by slash
  $browser_path_link_folder = str_replace("%2F", "/", $browser_path_link_folder);

  $parent_path = dirname($browser_path_link_folder);
  
  $parent_nid = false;

  $item_type = "folder";
  if($node != null){
    $item_type = $node->type;
  }

  $bookmark_folder_is_flagged = gofast_ajax_file_browser_folder_is_bookmark(gofast_ajax_file_browser_get_reference_from_href(str_replace('/alfresco/webdav', '', $browser_path)));
  $folder_reference = gofast_ajax_file_browser_get_reference_from_href(str_replace('/alfresco/webdav', '', $browser_path));

  $bookmark_flag = flag_get_flag("bookmarks");
  $bookmark_is_flagged = $bookmark_flag->is_flagged($node->nid);

  if($node == null || $node->type == "folder"){
    while($parent_nid == false){
      $parent_nid = gofast_ajax_file_browser_get_nid_from_href($parent_path);
      $parent_path = dirname($parent_path);
    }
    $nid = $parent_nid;
  } else {
    $nid = $node->nid;
  }

  $items = [];
  $items = [
    'open_new_tab' => [
      'text' => t('Open in a new tab', array(), array('context' => 'gofast')),
      'link_id' => "open_new_tab" ,
      'href' => '',
      'icon_class' => 'fa fa-arrow-right',
      'onClick' => 'window.open(\'/node/' . $node->nid . '\', \'_blank\')',
      'title' => t('Open in a new tab of your browser'),
      'page' => array('gofast_contextual_menu_is_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'group', 'organisation', 'extranet', 'public'),
      'access_function' => ''
    ],
    'open_current_tab' => [
      'text' => t('Open in the current tab', array(), array('context' => 'gofast')),
      'link_id' => "open_current_tab",
      'href' => '/node/' . $node->nid,
      'icon_class' => 'fa fa-arrow-right',
      'target' => '',
      'onClick' => '',
      'title' => t('Open in a new tab of your browser'),
      'page' => array('gofast_contextual_menu_is_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'group', 'organisation', 'extranet', 'public'),
      'access_function' => ''
    ],
    'open_file_location' => [
      'text' => $node->type == "article" ? t('Open wiki\'s location', array(), array('context' => 'gofast')) : t('Open file\'s location', array(), array('context' => 'gofast')),
      'link_id' => "browse",
      'link_class' => '',
      'href' => '/node/' . gofast_og_get_group_id_from_title_2(gofast_cmis_get_first_available_location($node), TRUE) . '?path=' . rawurlencode(gofast_cmis_get_first_available_location($node)),
      'icon_class' => "fa fa-external-link",
      'target' => '_blank',
      'onClick' => '',
      'title' => t('Open file\'s location'),
      'page' => array('gofast_contextual_menu_not_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => '',
      'hide_from_mobile' => TRUE
    ],
    'link_to_folder' => [
      'text' => t('Link to this folder', array(), array('context' => 'gofast')),
      'link_id' => 'link_to_folder',
      'href' => '',
      'icon_class' => 'fa fa-arrow-right',
      'target' => '',
      'onClick' => 'Gofast.ITHit.linkToFolder(\''.$browser_path.'\','.$nid.')',
      'title' => t('Copy the link from this location to the clipboard'),
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'type' => array('group', 'organisation', 'extranet', 'public', 'folder'),
      'access_function' => '',
    ],
    'compress' => [
      'link_class' => 'compress-files',
      'text' => t('Compress', array(), array('context' => 'gofast')),
      'link_id' => 'compress',
      'href' => '',
      'icon_class' => 'fa fa-file-archive-o n-color',
      'target' => '',
      'onClick' => 'Gofast.ITHit.bulkSelected(event, \'' . $browser_path .
        '\');$(\'.gofast-node-actions.open\').click();',
      'title' => t('Compress the selected file'),
      'type' => array('folder'),
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'access_function' => array('gofast_contextual_menu_node_is_not_delete'),
    ],
    'subscribe_space' => gofast_contextual_menu_create_flag('subscribe_og',  'fa fa-rss', array('group', 'organisation', 'public', 'extranet'), FALSE, $node->nid),
    'bookmark_space' => [
      'text' => $bookmark_is_flagged ? t('Remove this from bookmark', array(), array("context" => "gofast:gofast_contextual_menu")) : t('Bookmark this', array(), array("context" => "gofast:gofast_contextual_menu")),
      'link_id' => "bookmarks",
      'link_class' => 'bookmarks '.($bookmark_is_flagged ? "" : "ctools-use-modal"),
      'icon_class' => "fas fa-star",
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group', 'organisation', 'public', 'extranet'),
      'href' => $bookmark_is_flagged ? "" : "/modal/nojs/bookmark_collection/flag/{$node->nid}/bookmark_flag_tree",
      'access_function' => '',
      'divider' => FALSE,
      'hide_from_mobile' => TRUE,
      "hide_from_tablet" => TRUE,
      'hide_from_essential' => FALSE,
      'onClick' => $bookmark_is_flagged ? "Gofast.Bookmark_Collection.bookmarkItem(event, {$node->nid}, null, 'bookmark_content_tree', 'content');" : "",
    ],
    'join_space' => [
      'text' => t('Ask to join', array(), array('context' => 'gofast')),
      'link_id' => 'join-'.$node->nid,
      'link_class' => 'ctools-use-modal',
      'icon_class' => 'fa fa-user-plus',
      'href' => "/modal/nojs/ask/join/{$node->nid}/space",
      'target' => '',
      'onClick' => '',
      'title' => t('Ask to join this space', array(), array('context' => 'gofast')),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group','organisation', 'extranet'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_is_not_member'),
      'divider' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'restore' => [
      'text' =>  t('Restore', array(), array('context' => 'gofast')) ,
      'title' => t('Restore', array(), array('context' => 'gofast')),
      'link_id' => "restore",
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/node/' . $node->nid . '/manage',
      'icon_class' => "fa fa-undo",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_node_is_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'forum', 'conference'),
      'access_function' => array('gofast_contextual_menu_user_can_delete_node', 'gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_is_not_multifiled', 'gofast_contextual_menu_can_restore_node'),
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => FALSE
     ],
     'img_preview' => [
      'text' => t('Preview', array(), array('context' => 'gofast')),
      'link_id' => 'preview',
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/preview/show/' . $node->nid,
      'icon_class' => 'fa fa-eye',
      'onClick' => '',
      'title' => t('Show preview in modal'),
      'page' => array('gofast_contextual_menu_not_from_node', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => '',
      'divider' => TRUE
    ],
    'delete_folder' => [
      'text' => t('Delete', array(), array('context' => 'gofast')),
      'link_id' => 'delete',
      'href' => '',
      'icon_class' => 'fa fa-trash',
      'target' => '',
      'onClick' => 'Gofast.ITHit.deleteSelected(event, \'' . $browser_path . '\');$(\'.gofast-node-actions.open\').click();',
      'title' => t('Delete this folder'),
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_folder_is_not_template', 'gofast_contextual_menu_folder_is_not_wiki', 'gofast_contextual_menu_folder_is_not_mirroring','gofast_contextual_menu_node_is_not_template')
    ],
    'manage_folder_locations' => [
      'text' => t('Share/Edit locations', array(), array('context' => 'gofast:gofast_views')) . '&nbsp;<span class="label label-lg label-light-warning label-inline">BETA</span>',
      'link_id' => "manage-folder-locations",
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/folder/manage-locations?path=' . $browser_path,
      'onclick' => 'Gofast.ITHit.bulkSelected(event)',
      'icon_class' => "fa fa-share-alt n-color",
      'title' => t('Manage locations of this folder'),
      'page' => array('gofast_contextual_menu_all_pages'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_parent_is_not_mirroring'),
    ],
    'share_folder_email' => [
      'text' => t('Share Folder By Email', array(), array('context' => 'gofast')),
      'href' => '/modal/0/share_folder_by_email/' .
        str_replace('/alfresco/webdav/', '', $browser_path_link_folder),
      'icon_class' => "fa fa-envelope",
      'link_class' => 'ctools-use-modal',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_is_share_candidate_template'),
    ],
    'rename_folder' => [
      'text' => t('Rename', array(), array('context' => 'gofast')),
      'link_id' => 'rename',
      'href' => '',
      'icon_class' => 'fa fa-pencil',
      'target' => '',
      'onClick' => gofast_contextual_menu_rename_onclick_folder($browser_path, $from_tree, $item_type),
      'title' => t('Rename this folder'),
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_folder_is_not_wiki','gofast_contextual_menu_node_is_not_template')
    ],
    'sync_userlist' => [
      'text' => t("Synchronize this userlist" , array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/userlist/{$node->nid}/sync",
      'icon_class' => 'fas fa-refresh',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('userlist'),
      'access_function' =>  array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_userlist_can_be_sync'),
      'divider' => TRUE
    ],
    'edit-space-description' => [
      'text' => t("Edit space description" , array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => '',
      'href' => "",
      'onClick' => "Gofast.triggerEditableInput('.gofastArticleDescription.homeDescription > div', '#oghome')",
      'icon_class' => 'fas fa-pen',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_not_from_tree', 'gofast_contextual_menu_not_from_browser'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' =>  array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator'),
    ],
    'edit' => gofast_contextual_menu_edit_link($node),
    'delete_userlist' => [
      'text' => t("Delete" , array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/node/{$node->nid}/manage",
      'icon_class' => 'fa fa-trash',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('userlist'),
      'divider' => TRUE,
      'access_function' =>  array('gofast_contextual_menu_user_can_delete_node', 'gofast_contextual_menu_userlist_has_no_tasks'),
    ],
    'add_members' => [
      'text' => t('Add members/lists', array(), array('context' => 'gofast:gofast_userlist')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/og/{$node->nid}/add/members",
      'icon_class' => 'fa fa-user-plus',
      'target' => '',
      'onClick' => '',
      'title' => t("Add existing Users/Userslists to this space"),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator'),
    ],
    'create_user_into_group' => [
      'text' => t("Create user in this space", array(), array("context" => "gofast:gofast_og")),
      'link_id' => '',
      'href' => "/admin/people/create?gids[]=".$node->nid,
      'icon_class' => 'fa fa-user-plus',
      'target' => '',
      'onClick' => '',
      'title' => t("Create user in this group"),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_user_is_administrator')
    ],
    'add_subspace' => [
      'text' => t("Add Sub-space"),
      'link_id' => '',
      'href' => "/node/add/" . $node->type . '?parent=' . $node->nid,
      'icon_class' => 'fa fa-plus',
      'target' => '',
      'onClick' => '',
      'title' => t("Add " . gofast_og_node_types()[$node->type] . " Sub-space"),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'type' => array('group', 'organisation', 'extranet'),
      'access_function' => array('gofast_contextual_menu_user_can_create_subspace')
    ],
    'manage_chat_room' => [
      'text' => gofast_riot_can_add_room($node) ? t('Create Chat room', array(), array('context' => 'gofast:gofast_riot')) :  t('Delete Chat room', array(), array('context' => 'gofast:gofast_riot')) ,
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => gofast_riot_can_add_room($node) ?  "/modal/nojs/riot/{$node->nid}/add/room" : "/modal/nojs/riot/{$node->nid}/delete/room" ,
      'icon_class' => gofast_riot_can_add_room($node) ? 'fa fa-user-plus' : 'fa fa-trash',
      'target' => '',
      'onClick' => '',
      'title' => gofast_riot_can_add_room($node) ? t('Create Chat room linked to this space') :  t('Delete Chat room linked from this space'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator')
    ],
    'bookmark_folder' => [
      'text' => $bookmark_folder_is_flagged ? t('Remove this from bookmark', array(), array("context" => "gofast:gofast_contextual_menu")) : t('Bookmark this', array(), array("context" => "gofast:gofast_contextual_menu")),
      'link_id' => $bookmark_folder_is_flagged ?  "unbookmark_folder" : 'bookmark_folder',
      'link_class' => 'ctools-use-modal',
      'onClick' => $bookmark_folder_is_flagged ? "Gofast.Bookmark_Collection.bookmarkItem(event, '{$folder_reference}', null, 'bookmark_folder_tree', 'folder');" : "",
      'icon_class' => "fa fa-bookmark",
      'title' => $bookmark_folder_is_flagged ? t('Remove this folder from your bookmarks') : t('Add this folder to your bookmarks'),
      'page' => array('gofast_contextual_menu_is_from_browser'),
      'type' => array('folder'),
      'access_function' => '',
      'href' => $bookmark_folder_is_flagged ? "" : "/modal/nojs/bookmark_collection/flag/0/bookmark_folder_flag_tree?folder_reference={$folder_reference}",
    ],
    'co-edit_onlyoffice' => [
      'text' => t('Co-edit with onlyoffice', array(), array('context' => 'gofast')),
      'link_id' => 'contextual_btn_onlyoffice',
      'link_class' => 'gofast-non-ajax contextual_link_onlyoffice',
      'href' => $base_url . '/onlyoffice/editor/' . $node->nid,
      'icon_class' => 'fa fa-edit',
      'target' => '_blank',
      'onClick' => gofast_onlyoffice_get_onclick_contextual_action($node),
      'title' => t("Edit this document with OnlyOffice"),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_locked_onlyoffice', 'gofast_contextual_menu_is_onlyoffice_compatible', 'gofast_contextual_menu_node_onlyoffice_is_edition_enabled'),
      'hide_from_mobile' => $detect->isTablet() ?  FALSE : TRUE, 
    ],
    'ithit_edit' => [
      'text' => t('Edit from my PC', array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => "alfresco_download_edit_url nid-" . $node->nid,
      'href' => alfresco_url_download_modify($node),
      'alf_id'=> !empty($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']) ? $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] : FALSE,
      'icon_class' => 'fa fa-edit',
      'target' => '',
      'onClick' => '',
      'title' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_is_desktop_edition_enabled'),
      'divider' => TRUE,
      'hide_from_mobile' => TRUE,
      "hide_from_tablet" => TRUE,
    ],
    'reply' => [
      'text' => t('Reply', array(), array('context' => 'gofast')),
      'link_id' => '',
      'href' => "/node/add/alfresco-item?field_target_link=" . $node->nid,
      'icon_class' => 'fa fa-plus',
      'target' => '_blank',
      'onClick' => '',
      'title' => t('Reply to this message'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_mail_node_is_mail'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_node_not_archived'),
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'new_comment' => [
      'text' => t('New comment', array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => $base_url . "/gofast/nojs/comment/reply/" . $node->nid,
      'icon_class' => 'fa fa-comment',
      'target' => '',
      'onClick' => '',
      'title' =>'',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'forum', 'external_page'),
      'access_function' => '',
      'divider' => !gofast_contextual_menu_is_from_node(null, null, null, null) ? TRUE : FALSE,
    ],
    'annotate' => [
      'text' => t('Annotate', array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'context-menu-svg-img',
      'href' => '',
      'icon_class' => 'context-menu-svg-img',
      'svg' => '/sites/all/modules/gofast/gofast_contextual_menu/img/comment-pen-solid.svg',
      'target' => '',
      'onClick' => 'Drupal.gofast_cmis.reloadPreview(true)',
      'title' =>'',
      'page' => array('gofast_contextual_menu_is_from_node', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_is_annotable'),
      'divider' => TRUE
    ],
    'share_locations' => [
      'text' => $node->type == "article" ? t('Edit wiki article location', array(), array('context' => 'gofast:gofast_contextual_menu')) : t('Share/Edit locations', array(), array('context' => 'gofast:gofast_views')),
      'link_id' => "manage-locations",
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/node/' . $node->nid . '/manage-locations',
      'onclick' => 'Gofast.ITHit.bulkSelected(event)',
      'icon_class' => "fa fa-share-alt n-color",
      'title' => $node->type == "article" ? t('Manage location of this wiki article') : t('Manage locations of this document'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'external_page', 'forum'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_not_in_mirror_folder', 'gofaxt_contextual_menu_is_not_homepage', 'gofaxt_contextual_menu_wiki_is_subwiki_home'),
    ],
    'share_by_mail' => [
      'text' => t('Share by email', array(), array('context' => 'gofast')),
      'link_id' => "",
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/linksharing/' . $node->nid,
      'onclick' => '',
      'icon_class' => "fa fa-envelope",
      'title' => t('Share by mail this document'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'external_page'),
      'access_function' => array('gofast_contextual_menu_is_not_confidential_internal'),
    ],
    'download' => [
      'text' => t('Download', array(), array('context' => 'gofast')),
      'href' => '/cmis/browser?id=' . (!empty($node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value']) ? $node->{GOFAST_CMIS_REFERENCE_FIELD}[LANGUAGE_NONE][0]['value'] : ''),
      'icon_class' => "fa fa-cloud-download",
      'onClick' => 'Gofast.auditAction.download(\'' . $node->nid . '\')',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'external_page'),
      'access_function' => array('gofast_contextual_menu_is_not_confidential_internal'),
    ],
    
    'folder download' => [
      'text' => t('Download', array(), array('context' => 'gofast')),
      'link_class' => 'download-folder',
      'href' => '',
      'icon_class' => "fa fa-cloud-download", 
      'onClick' => $from_tree ? "event.preventDefault();Gofast.ITHit.downloadFiles([{nodeRef: '$folder_reference'}]);" : "Gofast.ITHit.bulkSelected(event, '$browser_path');$('.gofast-node-actions.open').click();",
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_is_not_confidential_internal', 'gofast_contextual_menu_folder_is_not_wiki','gofast_contextual_menu_node_is_not_template'),
    ],
    
    'permalink' => [
      'text' => t('Permalink', array(), array('context' => 'gofast')),
      'link_id' => "permalink",
      'link_class' => 'permalink',
      'href' => '/node/' . $node->nid,
      'icon_class' => "fas fa-link",
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'conference', 'forum', 'external_page', 'webform'),
      'access_function' => '',
      'divider' => TRUE,
      'hide_from_mobile' => TRUE,
      "hide_from_tablet" => TRUE,
      'hide_from_essential' => FALSE
    ],
    'rename_browser' => [
      'text' => t('Rename', array(), array('context' => 'gofast')),
      'link_id' => 'rename',
      'href' => '',
      'icon_class' => 'fa fa-pencil',
      'target' => '',
      'onClick' => gofast_contextual_menu_rename_onclick_folder($browser_path, $from_tree, $item_type),
      'title' => t('Rename this document'),
      'page' => array('gofast_contextual_menu_is_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_locked'),
      'divider' => TRUE
    ],
    'create_from_template' => [
      'text' => t('Create from template', array(), array('context' => 'gofast:gofast_views')),
      'link_id' => "",
      'link_class' => 'create from_template_open_span',
      'href' => '/node/add/alfresco-item?template=' . $node->nid.'#createFromTemplate',
      'onclick' => '',
      'icon_class' => "fa fa-file-o",
      'title' => t('Create from template'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_node_is_template','gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_not_archived'),
      'hide_from_mobile' => TRUE,
      "hide_from_tablet" => TRUE,
    ],
    'publication' => gofast_contextual_menu_get_publication_link($node),
    'preadd userlist members' => [
      'text' => t('Pre-Add members', array(), array('context' => 'gofast:gofast_userlist:preadd:contextual_menu:item_label')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/og/{$node->nid}/userlist/preadd/members",
      'icon_class' => 'fa fa-user-plus',
      'target' => '',
      'onClick' => '',
      'title' => t('Pre-Add members', array(), array('context' => 'gofast:gofast_userlist:preadd:contextual_menu:item_label')),
      'type' => array('userlist'),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_userlist_og_can_preadd_user_to_userlist'),
    ],
  ];

  $detect = new Mobile_Detect();
  if(!gofast_essential_is_essential() || gofast_essential_is_essential() && !$detect->isMobile()){
    // Signature options
    $items['signature'] = gofast_contextual_menu_get_signature_options($node, $browser_path, $from_tree);
  }
  
  // Specific actions 
  $items += gofast_contextual_menu_get_specific_menu($node, $browser_path, $from_tree);

  if (!$all && (!$detect->isMobile() || $detect->isTablet())){
    $items['more'] = gofast_contextual_menu_get_more_actions($node, $browser_path, $from_tree);
  } else {
    $items += gofast_contextual_menu_get_more_actions($node, $browser_path, $from_tree);
  }

  // Hook to alter already existing items in other modules
  drupal_alter("gofast_contextual_menu", $items);

  return $items;
}

function gofast_contextual_menu_get_more_actions($node, $browser_path, $fromTree){
  $items = array();
  $bookmark_flag = flag_get_flag("bookmarks");
  $bookmark_is_flagged = $bookmark_flag->is_flagged($node->nid);
  $items = [
    'rename' => [
      'text' => t('Rename', array(), array('context' => 'gofast')),
      'link_id' => 'rename',
      'href' => '',
      'icon_class' => 'fa fa-pencil',
      'target' => '',
      'onClick' => 'jQuery(\'#title-reference .breadcrumb-item .editable\').trigger(\'click\');jQuery(\'#title-reference .breadcrumb-item .EditableInput__input\').focus();',
      'title' => t('Rename this document'),
      'page' => array('gofast_contextual_menu_not_from_browser', 'gofast_contextual_menu_is_from_node', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_locked'),
      'hide_from_essential' => TRUE
    ],
    'edit-resume' => [
      'text' => t('Edit Summary', array(), array('context' => 'gofast')),
      'link_id' => "edit-resume",
      'link_class' => '',
      'href' => '',
      'icon_class' => "fa fa-edit",
      'onClick' => 'jQuery(\'#gofastSummaryContent\').collapse(\'show\');jQuery(\'#gofastSummaryAccordion > .card\').removeClass(\'\d-none\');jQuery(\'#gofastSummaryContent\').removeClass(\'\d-none\');jQuery(\'.gofastSummaryContent .editable\').trigger(\'click\');',
      'title' => t('Edit resume for this content'),
      'page' => array('gofast_contextual_menu_is_from_node', 'gofast_contextual_menu_not_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_not_locked'),
      'hide_from_mobile' => TRUE,
      'hide_from_tablet' => TRUE
    ],
    'delete_from_browser' => [
      // if other custom text values, create function to handle displayed text
      'text' =>  t('Delete', array(), array('context' => 'gofast')) ,
      'title' => gofast_contextual_menu_is_not_multifiled($node) ? t('Delete', array(), array('context' => 'gofast')) : t("This document is into at least one personal space so you can't delete it", array(), array("context" => "gofast")),
      'link_id' => "delete",
      'link_class' => '',
      'href' => '',
      'icon_class' => "fa fa-trash",
      'target' => '',
      'onClick' => 'Gofast.ITHit.deleteSelected(event, \'' . $browser_path . '\');$(\'.gofast-node-actions.open\').click();',
      'page' => array('gofast_contextual_menu_is_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'forum', 'conference'),
      'access_function' => array('gofast_contextual_menu_user_can_delete_node', 'gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_is_not_multifiled', 'gofast_contextual_menu_folder_is_not_wiki'),
      'divider' => TRUE
    ],
    'rename_space' => [
      // if other custom text values, create function to handle displayed text
      'text' => t('Rename this space', array(), array('context' => 'gofast')),
      'link_id' => '',
      'icon_class' => 'fa fa-pencil',
      'target' => '',
      'href' => '',
      'onClick' => "$('.breadcrumb-gofast-show-title .EditableInput__value.editable').trigger('click').trigger('focus');",
      'title' =>  t('Rename this space', array(), array('context' => 'gofast')),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_not_from_tree', 'gofast_contextual_menu_not_from_browser'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator', 'gofast_contextual_menu_space_not_archived'),
    ],
    'move_space' => [
      'text' => t('Move this space', array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/space/{$node->nid}/move",
      'icon_class' => 'fa fa-random',
      'target' => '',
      'onClick' => '',
      'title' => t("Move this space", array(), array('context' => 'gofast')),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator', 'gofast_contextual_menu_space_not_archived'),
      'hide_from_essential' => TRUE
    ],
    'manage_archive' => [
      'text' => !gofast_group_is_archive($node) ? t('Archive this space', array(), array('context' => 'gofast')) :  t('Unarchive this space', array(), array('context' => 'gofast')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => !gofast_group_is_archive($node) ? "/modal/nojs/og/{$node->nid}/archive" : "/modal/nojs/og/{$node->nid}/unarchive",
      'icon_class' => 'fa fa-archive',
      'target' => '',
      'onClick' => '',
      'title' => !gofast_group_is_archive($node) ? t('Archive this space', array(), array('context' => 'gofast')) :  t('Unarchive this space', array(), array('context' => 'gofast')),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group', 'extranet'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator')
    ],
    'delete_space' => [
      // if other custom text values, create function to handle displayed text
      'text' => gofast_contextual_menu_has_no_subspace($node) ? t('Delete', array(), array('context' => 'gofast')) : t("Remove subspaces to delete", array(), array("context" => "gofast")),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/gofast_og/delete_space/{$node->nid}",
      'icon_class' => 'fa fa-trash',
      'target' => '',
      'onClick' => '',
      'title' =>  gofast_contextual_menu_has_no_subspace($node) ? t('Delete', array(), array('context' => 'gofast')) : t("Remove subspaces to delete", array(), array("context" => "gofast")),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_user_is_administrator', 'gofast_contextual_menu_user_can_delete_space', 'gofast_contextual_menu_has_no_subspace', 'gofast_contextual_menu_space_not_archived'),
      'divider' => TRUE
    ],
    'preadd members' => [
      'text' => t('Pre-Add members/lists', array(), array('context' => 'gofast:gofast_userlist')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/og/{$node->nid}/preadd/members",
      'icon_class' => 'fa fa-user-plus',
      'target' => '',
      'onClick' => '',
      'title' => t('Pre-Add members/Userlists', array(), array('context' => 'gofast:gofast_userlist')),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete', 'gofast_contextual_menu_space_not_archived'),
      'type' => array('group','organisation', 'extranet'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space', 'gofast_contextual_menu_check_url_permission'),
    ],
    'contact administrators' => [
      'text' => t('Contact administrators of this space', array(), array('context' => 'gofast:gofast_og')),
      'link_id' => '',
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/og/{$node->nid}/contact/admins",
      'icon_class' => 'fa fa-user-plus',
      'target' => '',
      'onClick' => '',
      'title' => t("Contact administrators of this space"),
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('group', 'organisation', 'extranet', 'public'),
      'access_function' => array('gofast_contextual_menu_is_not_root_space'),
      'hide_from_essential' => TRUE,
    ],
    'delete_from_node' => [
      // if other custom text values, create function to handle displayed text
      'text' =>  t('Delete', array(), array('context' => 'gofast')) ,
      'title' => gofast_contextual_menu_is_not_multifiled($node) ? t('Delete', array(), array('context' => 'gofast')) : t("This document is into at least one personal space so you can't delete it", array(), array("context" => "gofast")),
      'link_id' => "delete",
      'link_class' => 'ctools-use-modal',
      'href' => '/modal/nojs/node/' . $node->nid . '/manage',
      'icon_class' => "fa fa-trash",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_is_from_node', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'forum', 'conference'),
      'access_function' => array('gofast_contextual_menu_user_can_delete_node', 'gofast_contextual_menu_node_not_locked', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_is_not_multifiled'),
      'divider' => TRUE,
      'hide_from_mobile' => TRUE
    ],
    'unzip' => [
      'text' => t('Extract', array(), array('context' => 'gofast')),
      'link_id' => 'unzip',
      'href' => '',
      'icon_class' => 'fa fa-file-archive n-color',
      'target' => '',
      'onClick' => 'Gofast.ITHit.unzipSelected(event, \'' . $browser_path . '\');$(\'.gofast-node-actions.open\').click();',
      'title' => t('Extracts the selected file'),
      'page' => array('gofast_contextual_menu_unzip_file'),
      'type' => array('alfresco_item'),
      'access_function' => '',
    ],
    'compress' => [
      'link_class' => 'compress-files',
      'text' => t('Compress', array(), array('context' => 'gofast')),
      'link_id' => 'compress',
      'href' => '',
      'icon_class' => 'fa fa-file-archive-o n-color',
      'target' => '',
      'onClick' => 'Gofast.ITHit.bulkSelected(event, \'' . $browser_path .
        '\');$(\'.gofast-node-actions.open\').click();',
      'title' => t('Compress the selected file'),
      'type' => array('folder'),
      'access_function' => array('gofast_contextual_menu_node_is_not_delete'),
    ],
    'duplicate' => [
      'text' => t('Duplicate this file', array(), array('context' => 'gofast')),
      'href' => '',
      'icon_class' => "fa fa-clone",
      'link_class' => 'gf-filebrowser-full-only',
      'onClick' => 'Gofast.ITHit.duplicate(\'' . $node->nid . '\')',
      'page' => array('gofast_contextual_menu_is_from_browser', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array("alfresco_item"),
      'access_function' => array('gofast_contextual_menu_user_can_update_node'),
      'divider' => TRUE
    ],
    'manage_translations' => [
      'text' => t('Manage translations', array(), array('context' => 'gofast')),
      'link_id' => "",
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/node/{$node->nid}/manage-translations",
      'icon_class' => "fa fa-flag",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_retention_date', 'gofast_contextual_menu_node_not_archived'),
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'upload_new_version' => [
      'text' => t('Upload new version', array(), array('context' => 'gofast')),
      'link_id' => "alfresco_item_upload_new_version",
      'link_class' => 'ctools-use-modal',
      'href' => "/modal/nojs/get/alfresco/file/form/{$node->nid}",
      'icon_class' => "fa fa-cloud-upload",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_not_locked'),
      'divider' => TRUE
    ],
    'tag_major_version' => [
      'text' => t('Tag this version as major'),
      'title' => t('Tag this version of content as major'),
      'link_id' => "major_version_open_span",
      'link_class' => 'ctools-use-modal major_version_contextual_button',
      'href' => "/modal/nojs/node/{$node->nid}/tag-major-version",
      'icon_class' => "fa fa-files-o",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_not_locked'),
      'hide_from_mobile' => TRUE,
      'hide_from_tablet' => TRUE
    ],
    'delete_minor_versions' => [
      'text' => t('Delete all minor versions'),
      'title' => t('Delete all minor versions'),
      'link_id' => "major_version_open_span",
      'link_class' => 'ctools-use-modal delete_minor_versions_contextual_button',
      'href' => "/modal/nojs/node/{$node->nid}/delete-minor-versions",
      'icon_class' => "fa fa-trash-o",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article'),
      'access_function' => array('gofast_contextual_menu_user_can_update_node', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_node_not_locked'),
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'compare_versions' => [
      'text' => t('Compare versions', array(), array('context' => "gofast:gofast_pdf_compare")),
      'title' => t('Compare versions', array(), array('context' => "gofast:gofast_pdf_compare")),
      'link_id' => "compare_versions_open_span",
      'link_class' => 'ctools-use-modal compare-versions',
      'href' => "/modal/nojs/node/{$node->nid}/compare_versions",
      'icon_class' => "fa fa-exchange",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item'),
      'access_function' => '',
      'divider' => TRUE,
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'bookmarks' => [
      'text' => $bookmark_is_flagged ? t('Remove this from bookmark', array(), array("context" => "gofast:gofast_contextual_menu")) : t('Bookmark this', array(), array("context" => "gofast:gofast_contextual_menu")),
      'link_id' => "bookmarks",
      'link_class' => 'bookmarks '.($bookmark_is_flagged ? "" : "ctools-use-modal"),
      'icon_class' => "fas fa-star",
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'webform', 'forum'),
      'href' => $bookmark_is_flagged ? "" : "/modal/nojs/bookmark_collection/flag/{$node->nid}/bookmark_flag_tree",
      'access_function' => '',
      'divider' => FALSE,
      'hide_from_mobile' => TRUE,
      "hide_from_tablet" => TRUE,
      'hide_from_essential' => FALSE,
      'onClick' => $bookmark_is_flagged ? "Gofast.Bookmark_Collection.bookmarkItem(event, {$node->nid}, null, 'bookmark_content_tree', 'content');" : "",
    ],
    'flag_public' => gofast_contextual_menu_create_flag('flag_public','fa fa-star', array('alfresco_item', 'article', 'webform', 'forum'),  TRUE,  $node->nid),
    'cart' => gofast_contextual_menu_create_flag('cart', 'fas fa-shopping-basket', array('alfresco_item', 'article'), TRUE,  $node->nid, array('hide_from_mobile' => TRUE, "hide_from_tablet" => TRUE)),
    'pin_content' => [
      'text' => $node->sticky ? t('Unpin this content') : t('Pin this content'),
      'title' => $node->sticky ? t('This content will be unpinned and won\'t appear anymore at the top of the activity feed') : t('This content will be pinned to the top of the activity feed'),
      'link_id' => $node->sticky ? 'unpin_content_open_span' : 'pin_content_open_span',
      'link_class' => 'ctools-use-modal pin-content',
      'href' => "/modal/nojs/node/{$node->nid}/pin-content",
      'icon_class' => "fa fa-thumb-tack",
      'target' => '',
      'onClick' => '',
      'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
      'type' => array('alfresco_item', 'article', 'conference', 'forum', 'webform', 'external_page'),
      'access_function' => array('gofast_contextual_menu_user_can_delete_node'),
      'divider' => in_array($node->type, array('article', 'conference')) ? TRUE : FALSE,
      'hide_from_mobile' => TRUE,
      'hide_from_essential' => TRUE
    ],
    'compress' => [
      'link_class' => 'compress-files',
      'text' => t('Compress', array(), array('context' => 'gofast')),
      'link_id' => 'compress',
      'href' => '',
      'icon_class' => 'fa fa-file-archive-o n-color',
      'target' => '',
      'onClick' => 'Gofast.ITHit.bulkSelected(event, \'' . $browser_path .
        '\');$(\'.gofast-node-actions.open\').click();',
      'title' => t('Compress the selected file'),
      'type' => array('alfresco_item'),
      'access_function' => array('gofast_contextual_menu_node_is_not_delete'),
    ],
    'subscribe' => gofast_contextual_menu_create_flag('subscribe_node',  'fa fa-rss', array('alfresco_item', 'article', 'conference', 'forum', 'webform'), FALSE, $node->nid),
  ];

  return $items;
}


function gofast_contextual_menu_unzip_file($node, $browser_path = NULL, $fromTree = NULL){

  if ($node->field_filename['und'][0]['value'] !== NULL){
    $title = explode('.', $node->field_filename['und'][0]['value'] );

    if(array_pop($title) === 'zip'){
      return TRUE;
    }
    return FALSE;
  }
  return FALSE;

}

function gofast_contextual_menu_get_signature_options($node, $browser_path, $from_tree){
  $items = array();
  
  foreach (module_implements("node_available_signature") as $module) {
    $items += call_user_func($module . "_node_available_signature", $node);
  }

  return $items;
}

function gofast_contextual_menu_get_specific_menu($node, $browser_path, $from_tree){
  $items = array();
  foreach (module_implements("node_available_actions") as $module) {
    $items += call_user_func($module . "_node_available_actions", $node);
  }
  return $items;
}

function gofast_contextual_menu_get_node_actions_dropdown($node, $browser_path = NULL, $fromTree = NULL){
  //Easily memorise last main entry and its index to put a divider before the "More ..." dropdown
  $last_action = array();
  $action_counter = 0;
  $is_in_store = gofast_contextual_menu_is_in_store($node);
  $is_from_browser = isset($_POST["fromBrowser"]) && gofast_contextual_menu_not_from_tree($node, $browser_path, $fromTree);
  $node_actions = array();
  foreach (gofast_contextual_menu_get_all_items($node, $browser_path, $fromTree) as $key => $action) {
    $action_types = (array) $action['type'];
    $unreplicated_document = ($node->nid == null && $node->type != "folder");
    if(in_array($node->type, $action_types) && !$unreplicated_document) {
      $condition = TRUE;
      $display = TRUE;
      $access_function = $action['access_function'];
      $page_display = $action['page'];
      if (!empty($page_display)) {
        $access_param = array($node, $browser_path, $fromTree, $action);
        foreach ($page_display as $function) {
          $result = call_user_func_array($function, $access_param);
          if ($result == FALSE) {
            $display = FALSE;
          }
        }
      }
      if (!empty($access_function)) {

        // Init list of tooltip to explain why the action is disabled
        $tooltips = '';

        $access_param = array($node, $browser_path, $fromTree, $action);
        foreach ($access_function as $function) {
          $result = call_user_func_array($function, $access_param);
          if ($result !== TRUE) {
            $tooltips = $result;
            $condition = FALSE;
          }
        }
      }

      if (!$is_in_store) {
        $tooltips = t("The content is temporarily unavailable. Please try again later.", array(), array("context" => "gofast:gofast_contextual_menu"));
      }

      if ($display == TRUE && $key !== 'more') {
        
        $detect = new Mobile_Detect;
        if ($detect->isTablet() && $action['hide_from_tablet'] == TRUE) { // Ability to hide some menu links on tablet.
          continue;
        } else if (gofast_mobile_is_phone() && $action["hide_from_mobile"] == TRUE){ // Ability to hide some menu links on mobile.
          continue;
        }else if(gofast_essential_is_essential() && $action['hide_from_essential'] == TRUE) {  // Ability to hide some menu links on Essential version.
          continue;
        }
        
        if ($condition == TRUE && $is_in_store) {
          $node_actions[]['themed'] = theme('gofast_link_generic', array(
            'text' => $action['text'],
            'link_id' => $action['link_id'],
            'link_class' => $action['link_class'],
            'href' => $action['href'],
            'icon_class' => $action['icon_class'],
            'target' => $action['target'],
            'onClick' => $action['onClick'],
            'title' => $action['title'],
            'flag' => $action['flag'],
            'divider' => $action['divider'],
            'svg' => $action['svg'],
          ));
            $last_action = $action;
            $action_counter++;
        } else {
          $node_actions[] = array(
            'themed' => theme('gofast_link_generic', array(
              'text' => $action['text'],
              'link_id' => $action['link_id'],
              'link_class' => 'disabled',
              'href' => '',
              'disabled' => 'disabled',
              'icon_class' => $action['icon_class'],
              'target' => $action['target'],
              'onClick' => '',
              'title' => $action['title'],
              'flag' => $action['flag'],
              'divider' => $action['divider'],
              'svg' => $action['svg'],
            )),
            'title' => $tooltips
          );
        }
      }
    }
    if (is_array($action) && $key === 'more' && !empty($action)) {
      $children = array();
      foreach ($action as $child) {
        
         
        $detect = new Mobile_Detect;
        if ($detect->isTablet() && $action['hide_from_tablet'] == TRUE) { // Ability to hide some menu links on tablet.
          continue;
        } else if (gofast_mobile_is_phone() && $action["hide_from_mobile"] == TRUE){ // Ability to hide some menu links on mobile.
          continue;
        }else if(gofast_essential_is_essential() && $action['hide_from_essential'] == TRUE) {  // Ability to hide some menu links on Essential version.
          continue;
        }

        $more_condition = TRUE;
        $more_display = TRUE;
        $more_access_function = $child['access_function'];
        $more_page_display = $child['page'];
        if (!empty($more_page_display)) {
          $access_param = array($node, $browser_path, $fromTree, $child);
          foreach ($more_page_display as $function) {
            $result = call_user_func_array($function, $access_param);
            if ($result == FALSE) {
              $more_display = FALSE;
            }
          }
        }
        if (!empty($more_access_function)) {
          $child_tooltips = '';
          $access_param = array($node, $browser_path, $fromTree, $child);
          foreach ($more_access_function as $function) {
            $result = call_user_func_array($function, $access_param);
            if ($result !== TRUE) {
              $child_tooltips =  $result;
              $more_condition = FALSE;
            }
          }
        }
        $child_types = $child['type'];
        if (!empty($node->type) && $child_types && in_array($node->type, $child_types) && $more_display == TRUE) {
          $has_access = true;

          if ($more_condition == TRUE && $has_access && $is_in_store) {
            $children[]['themed'] = theme('gofast_link_generic', array(
              'text' => $child['text'],
              'link_id' => $child['link_id'],
              'link_class' => $child['link_class'],
              'href' => $child['href'],
              'icon_class' => $child['icon_class'],
              'target' => $child['target'],
              'onClick' => $child['onClick'],
              'title' => $child['title'],
              'flag' => $child['flag'],
              'divider' => $child['divider']
            ));
          } else {
            $children[] = array(
              'themed' => theme('gofast_link_generic', array(
                'text' => $child['text'],
                'link_id' => $child['link_id'],
                'link_class' => 'disabled',
                'href' => '',
                'disabled' => 'disabled',
                'icon_class' => $child['icon_class'],
                'target' => $child['target'],
                'onClick' => '',
                'title' => $child['title'],
                'flag' => $child['flag'],
                'divider' => $child['divider']
              )),
              'title' => $child_tooltips
            );
          }
        }
      }

      if(!empty($children)){
          $dropleft = gofast_contextual_menu_dropleft($node, $is_from_browser, $fromTree);
          
          $node_actions[] = array(
          'themed' => theme('gofast_link_generic', array(
              'text' => t('More ...', array(), array('context' => 'gofast')),
              'link_class' => 'pl-14 d-flex navi-item' . ($dropleft ? '' : ' flex-row-reverse'),
              'title' => t('More'),
              'icon_class' => $dropleft ? 'fas fa-arrow-left' : 'fas fa-arrow-right',
              'dropleft' => $dropleft
          )),
          'children' => $children
        );
      }
    }
    
    if (is_array($action) && $key === 'signature' && !empty($action)) {
      $children = array();
      foreach ($action as $child) {
        
        $detect = new Mobile_Detect;
        if ($detect->isTablet() && $action['hide_from_tablet'] == TRUE) { // Ability to hide some menu links on tablet.
          continue;
        } else if (gofast_mobile_is_phone() && $action["hide_from_mobile"] == TRUE){ // Ability to hide some menu links on mobile.
          continue;
        }else if(gofast_essential_is_essential() && $action['hide_from_essential'] == TRUE) {  // Ability to hide some menu links on Essential version.
          continue;
        }

        $more_condition = TRUE;
        $more_display = TRUE;
        $more_access_function = $child['access_function'];
        $more_page_display = $child['page'];
        if (!empty($more_page_display)) {
          $access_param = array($node, $browser_path, $fromTree, $child);
          foreach ($more_page_display as $function) {
            $result = call_user_func_array($function, $access_param);
            if ($result == FALSE) {
              $more_display = FALSE;
            }
          }
        }
        if (!empty($more_access_function)) {
          $child_tooltips = '';
          $access_param = array($node, $browser_path, $fromTree, $child);
          foreach ($more_access_function as $function) {
            $result = call_user_func_array($function, $access_param);
            if ($result !== TRUE) {
              $child_tooltips =  $result;
              $more_condition = FALSE;
            }
          }
        }
        $child_types = $child['type'];
        if (!empty($node->type) && in_array($node->type, $child_types) && $more_display == TRUE) {
          $has_access = true;

          if ($more_condition == TRUE && $has_access && $is_in_store) {
            $signature[]['themed'] = theme('gofast_link_generic', array(
              'text' => $child['text'],
              'link_id' => $child['link_id'],
              'link_class' => $child['link_class'],
              'href' => $child['href'],
              'icon_class' => $child['icon_class'],
              'target' => $child['target'],
              'onClick' => $child['onClick'],
              'title' => $child['title'],
              'flag' => $child['flag'],
              'divider' => $child['divider']
            ));
          } else {
            $signature[] = array(
              'themed' => theme('gofast_link_generic', array(
                'text' => $child['text'],
                'link_id' => $child['link_id'],
                'link_class' => 'disabled',
                'href' => '',
                'disabled' => 'disabled',
                'icon_class' => $child['icon_class'],
                'target' => $child['target'],
                'onClick' => '',
                'title' => $child['title'],
                'flag' => $child['flag'],
                'divider' => $child['divider']
              )),
              'title' => $child_tooltips
            );
          }
        }
      }

      if(!empty($signature)){
          $dropleft = gofast_contextual_menu_dropleft($node, $is_from_browser);
          $node_actions[] = array('divider' => TRUE);
          $node_actions[] = array(
          'themed' => theme('gofast_link_generic', array(
              'text' => t('Signature options', array(), array('context' => 'gofast')),
              'link_class' => 'pl-14 d-flex navi-item' . ($dropleft ? '' : ' flex-row-reverse'),
              'title' => t('Signature options'),
              'icon_class' => $dropleft ? 'fas fa-arrow-left' : 'fas fa-arrow-right',
              'dropleft' => $dropleft,
          )),
          'children' => $signature
        );
        $node_actions[] = array('divider' => TRUE);

      }
    }
  }
  // print "<pre>"; print_r($node_actions); exit;
  return $node_actions;
}

function gofast_contextual_menu_get_action_access($action_name, $node, $browser_path = NULL, $from_tree = NULL) {
  $action = gofast_contextual_menu_get_all_items($node, $browser_path, $from_tree, TRUE)[$action_name];
  if (!$action) {
    $action = gofast_contextual_menu_get_all_items($node, $browser_path, $from_tree, TRUE)["more"][$action_name];
  }
  $access = TRUE;
  $access_function = $action['access_function'];
  $access_param = array($node, $browser_path, $from_tree, $action);
  foreach ($access_function as $function) {
    $result = call_user_func_array($function, $access_param);
    if ($result !== TRUE) {
      $access = $result;
      break;
    }
  }
  return $access;
}

function gofast_contextual_menu_dropleft($node, $is_from_browser = FALSE, $is_from_tree = FALSE){
  if(isset($_POST["isFromActivityFeed"]) && $_POST["isFromActivityFeed"] == TRUE){
    return FALSE;
  }
  $currentDropleftValue = FALSE;
  if($node->type == "forum" || $node->type == "article" || $node->type == 'webform' || (gofast_essential_is_essential() && !gofast_mobile_is_phone())){
    $currentDropleftValue = TRUE;
  }
  if ($is_from_tree) {
    // we don't want to dropleft if the contextual menu is called from the ztree in essential version
    $currentDropleftValue = FALSE;
  } else {
    // we want to dropleft the burger menu in the topbar of the filebrowser in Plus version
    $currentDropleftValue = $is_from_browser || $currentDropleftValue;
  }
  return $currentDropleftValue;
}

###### Page section ######

function gofast_contextual_menu_all_pages($node, $browser_path, $fromTree){
  if($node->status !== 0){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_is_from_browser($node, $browser_path, $fromTree, $menu_item = NULL){
  if(!empty($browser_path)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_not_from_browser($node, $browser_path, $fromTree, $menu_item = NULL){
  if(empty($browser_path)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_from_tree($node, $browser_path, $fromTree, $menu_item = NULL){
  if ($fromTree == "1"){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_not_from_tree($node, $browser_path, $fromTree, $menu_item = NULL){
  if ($fromTree != "1"){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_is_from_node($node, $browser_path, $fromTree, $menu_item)
{
  // if we're in the browser we're not viewing a specific node
  if (strpos(current_path(), 'filebrowser') !== false) {
    return FALSE;
  }  
  if(strpos(current_path(), '/poll')){
    return TRUE;
  }else{
    return strpos(current_path(), 'node/') !== FALSE || strpos(current_path(), 'node-actions/') !== FALSE;
  }
}

function gofast_contextual_menu_not_from_node($node, $browser_path, $fromTree, $menu_item)
{
  return strpos(current_path(), 'node/') === FALSE && strpos(current_path(), 'node-actions/') === FALSE;
}

function gofast_contextual_menu_node_is_not_delete($node, $browser_path, $fromTree, $menu_item){
  // if the node is empty, it means it's a folder
  if ($node->type == "folder") {
    return TRUE;
  }
  if($node->status == 0){
    return FALSE;
  }else{
    return TRUE;
  }
}

function gofast_contextual_menu_node_is_delete($node, $browser_path, $fromTree, $menu_item){
  if($node->status == 0){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_is_annotable($node, $browser_path, $fromTree, $menu_item){
  $extension = strtolower(gofast_cmis_node_get_extension($node));
  
  //Retrieve saved documents form configuration
  $default_documents_form_configuration = array(
    'ticket' => 1,
    'ticket_path_length' => 200,
    'gofast_onlyoffice_ro_preview' => FALSE,
  );
  $documents_form_defaults = variable_get("documents_form_defaults", $default_documents_form_configuration);
  
  if($documents_form_defaults['gofast_onlyoffice_ro_preview'] && in_array($extension, gofast_onlyoffice_viewable_document_extensions()) && !module_exists('gofast_community')){
    //CASE : View in read only mode with OnlyOffice
    return FALSE;
  }else if(in_array($extension, ['jpg', 'jpeg', 'png', 'gif', 'svg', 'bmp', 'mp3', 'mp4', 'webm'])){
    //CASE : No PDF generation
    return FALSE;
  }else{
    return TRUE;
  }
}

###### End Page section ######


function gofast_contextual_menu_is_node($node, $browser_path, $fromTree, $menu_item){
  if(!empty($node)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_user_can_update_node($node, $browser_path, $fromTree, $menu_item){
  if(node_access("update", $node)){
    return TRUE;
  }else{

    if($node->type == 'article' && $node->field_is_homepage[LANGUAGE_NONE][0]['value']){
      return t("This wiki article is the space's homepage, you should be the space's administrator to be able to edit it", array(), array('context' => 'gofast:gofast_contextual_menu'));
    }else{
      return t('You do not have the necessary rights', array(), array('context' => 'gofast:gofast_contextual_menu'));
    }
    
  }
}

function gofast_contextual_menu_node_not_archived($node, $browser_path, $fromTree, $menu_item){
  $archived_node = gofast_get_content_state_archived($node);

  if($archived_node){
    return FALSE;
  }else{
    return TRUE;
  }
}

function gofast_contextual_menu_node_not_locked($node, $browser_path, $fromTree, $menu_item){
  // use node id in static key to desambiguate the result in case of multiple calls on different nodes within same request
  $result = &drupal_static(__FUNCTION__ . "_" . $node->nid, "");
  if ($result != "") {
    return $result;
  }
  if (gofast_cmis_node_is_locked($node) == false) {
    $result = TRUE;
  } else {
    $result = t('This file is locked', array(), array('context' => 'gofast:gofast_contextual_menu'));
  }
  return $result;
}

function gofast_contextual_menu_node_onlyoffice_is_edition_enabled($node, $browser_path, $fromTree, $menu_item){
  $tags = taxonomy_get_term_by_name('NO-COEDITION', 'tags');
  $tid_template = array_keys($tags);


  $node_tags= array();
  foreach($node->field_tags[LANGUAGE_NONE] as $tag){
    $node_tags[] = $tag['tid'];
  }

  if(count(array_intersect($tid_template, $node_tags)) > 0){
      return FALSE;
  }else{
      return TRUE;
  }
}

function gofast_contextual_menu_node_is_desktop_edition_enabled($node, $browser_path, $fromTree, $menu_item){
  $tags = taxonomy_get_term_by_name('NO-EDITION', 'tags');
  $tid_template = array_keys($tags)[0];

  foreach($node->field_tags[LANGUAGE_NONE] as $tag){
    if ($tag['tid'] == $tid_template) {
      return FALSE;
    }
  }
  return TRUE;
}

function gofast_contextual_menu_node_locked_onlyoffice($node, $browser_path, $fromTree, $menu_item){
  if (gofast_cmis_node_is_locked($node) == FALSE || gofast_onlyoffice_document_get_soft_lock($node)) {
    return TRUE;
  }
  return t('This file is locked', array(), array('context' => 'gofast:gofast_contextual_menu'));
}

function gofast_contextual_menu_node_is_published($node, $browser_path, $fromTree, $menu_item){
  if($node->status === strval(NODE_PUBLISHED)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_node_not_retention_date($node, $browser_path, $fromTree, $menu_item){
  if (module_exists('gofast_retention')) {
    if (gofast_retention_get_retention_date($node) !== NULL) {
      return t('This file have a retention date', array(), array('context' => 'gofast:gofast_contextual_menu'));
    }
  }
  return TRUE;
}


function gofast_contextual_menu_node_is_template($node, $browser_path, $fromTree, $menu_item){
  $template_tag_name = variable_get("gofast_taxonomy_tags_forced_cases", 0) ? "TEMPLATE" : "Template";
  $tags = taxonomy_get_term_by_name($template_tag_name, 'tags');
  $tid_template = array_keys($tags);

  $node_tags = array();
  foreach ($node->field_tags[LANGUAGE_NONE] as $tag) {
    $node_tags[] = $tag['tid'];
  }

  if (count(array_intersect($tid_template, $node_tags)) > 0) {
    return TRUE;
  } else {
    return t('This file is not a template', array(), array('context' => 'gofast:gofast_contextual_menu'));
  }
}

function gofast_contextual_menu_folder_is_not_template($node, $browser_path, $fromTree, $menu_item){
  if(urldecode($browser_path) !== "/alfresco/webdav/Sites/FOLDERS TEMPLATES/" && urldecode($browser_path) !== "/alfresco/webdav/Sites/FOLDERS TEMPLATES"){
    return TRUE;
  }else{
    return t('This file is not a template', array(), array('context' => 'gofast:gofast_contextual_menu'));;
  }
}

function gofast_contextual_menu_folder_is_not_wiki($node, $browser_path, $fromTree, $menu_item){
  $is_wiki = substr($browser_path, -strlen("Wikis")) === "Wikis" || substr($browser_path, -strlen("Wikis/")) === "Wikis/";
  if ($is_wiki) {
    return t("Wikis folders can't be deleted", [], ["context" => "gofast"]);
  } else {
    return TRUE;
  }
}

function gofast_contextual_menu_node_is_not_template($node, $browser_path, $fromTree, $menu_item){
  $is_template = substr($browser_path, -strlen("TEMPLATES")) === "TEMPLATES" || substr($browser_path, -strlen("TEMPLATES/")) === "TEMPLATES/";
  if ($is_template) {
    return t("Template folders can't be renamed or deleted", [], ["context" => "gofast"]);
  } else {
    return TRUE;
  }
}
function gofast_contextual_menu_is_share_candidate_template($node, $browser_path, $fromTree, $menu_item){
  $is_template = gofast_contextual_menu_node_is_not_template($node, $browser_path, $fromTree, $menu_item);
  if ($is_template === TRUE) {
    return TRUE;
  } else {
    return t('TEMPLATE folders cannot be shared', array(), array('context' =>
      'gofast:gofast_contextual_menu'));;
  }
}
function gofast_contextual_menu_user_can_delete_node($node, $browser_path, $fromTree, $menu_item){
  if(node_access('delete', $node)){
    return TRUE;
  }else{
    return t('You can\'t delete this file', array(), array('context' => 'gofast:gofast_contextual_menu'));
  }
}
function gofast_contextual_menu_can_restore_node($node, $browser_path, $from_tree, $menu_item){
  
  $item = gofast_cmis_is_deleted_from_alfresco($node->field_reference[LANGUAGE_NONE][0]["value"]);
  $item_is_deleted = isset($item);
  
  if(!$item_is_deleted){
    return t("This file has been removed from the trash and cannot be restored.");
  } else {
    return TRUE;
  }
}

function gofast_contextual_menu_is_publication($node, $browser_path, $fromTree, $menu_item){
  return gofast_cmis_get_publication_source($node) != FALSE;
}

function gofast_contextual_menu_user_can_publish_node($node, $browser_path, $fromTree, $menu_item){
  if(gofast_cmis_user_can_publish($node)){
    return TRUE;
  }else{
    return t('You can\'t publish this file', array(), array('context' => 'gofast:gofast_contextual_menu'));
  }
}


function gofast_contextual_menu_rename_onclick_folder($browser_path, $from_tree, $item_type = "folder"){
  $browser_path = addslashes($browser_path);
  if ($from_tree) {
    return "Gofast.ITHit.renameTree('{$browser_path}', '{$item_type}')";
  } else {
    return "Gofast.ITHit.rename('{$browser_path}', '{$item_type}')";
  }
}

function gofast_contextual_menu_userlist_has_no_tasks($node){
  $ulid = gofast_userlist_get_ulid_by_nid($node->nid);
  $tasks_count = gofast_workflows_get_userlist_tasks($ulid, true);
  if($tasks_count > 0){
    return t("You can't delete a userlist with assigned tasks.", array(), array("context" => "gofast:gofast_contextual_menu"));
  } else {
    return true;
  }
}

function gofast_contextual_menu_get_publication_link($node){
  //CAS 1, le champs field_publication est vide et aucun champs CCK field_publication_doc d'autre noeud ne pointe vers notre noeud
  //on est donc dans le cas ou ce noeud n'a aucun rapport avec une publication (ni origine, ni destination)
  if (gofast_cmis_node_is_published($node) === FALSE && !gofast_cmis_get_publication_source($node)) {
    $href = "/modal/nojs/node/$node->nid/publication";
    $icon = 'fa fa-arrow-up';
    $title = t("Create publication", array(), array('context' => 'gofast'));
  }
  //CAS 2, le champs field_publication_doc n'est pas vide, ce noeud est donc le noeud d'origine d'une publication existante
  //on affiche le boutton qui permet de publier a nouveau ce document
  elseif (gofast_cmis_node_is_published($node) !== FALSE) {
    $href = "/modal/nojs/node/$node->nid/publication";
    $icon = 'fa fa-arrow-up';
    $title = t("Publish again this document", array(), array('context' => 'gofast'));
  }
  //CAS 3, un champs CCK field_publication_doc d'un autre noeud pointe vers notre noeud
  //on est donc dans le cas ou ce noeud est la publication d'un autre, donc on affiche un lien vers le noeud d'origine
  elseif (($nid = gofast_cmis_get_publication_source($node)) !== FALSE) {
    //si le user est l'auteur de la publication, j'affiche le bouton de suppression de la publication
    //if (gofast_user_is_adm() || $user->uid == $node->uid || $user->uid == 1) {
    if (node_access('delete', $node)) {
      $href = "/modal/nojs/node/$node->nid/publication/delete";
      $icon = 'fa fa-trash-o';
      $title = t("Delete this publication", array(), array('context' => 'gofast'));
    } else {
      $href = "/node/" . $nid;
      $title = t("This document is the publication of an other document", array(), array('context' => 'gofast'));
      $icon = 'fas fa-repeat';
      $remove_modal = true;
    }
  }

  return array(
    'href' => $href,
    'link_class' => !isset($remove_modal) ? 'ctools-use-modal ' : ' create_publication_contextual_button',
    'icon_class' => $icon,
    'text' => $title,
    'title' => $title,
    'type' => array('alfresco_item'),
    'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
    'access_function' => array(
      'gofast_contextual_menu_user_can_update_node',
      'gofast_contextual_menu_node_not_locked',
      'gofast_contextual_menu_node_not_archived',
      'gofast_contextual_menu_node_not_retention_date',
      'gofast_contextual_menu_user_can_publish_node'
    ),
    'hide_from_mobile' => TRUE,
    'hide_from_essential' => FALSE,
  );
}

function gofast_contextual_menu_edit_link($node){
    if (is_numeric($node)) {
        $node = node_load($node);
    }
  $nid = $node->nid;
  $onClick = FALSE;

  $text = t('Edit', array(), array('context' => 'gofast'));
  $access_functions = array('gofast_contextual_menu_node_is_published', 'gofast_contextual_menu_node_not_archived', 'gofast_contextual_menu_user_can_update_node');
  $page = array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete');

  if ($node->type == 'webform'){
      $href = "/node/{$nid}/edit"   ;
      $text = t('Edit this webform', array(), array('context' => 'gofast'));
  }else if($node->type == "conference"){
      $href = "/node/{$nid}/edit"   ;
      $text = t('Edit this conference', array(), array('context' => 'gofast'));
  }else if($node->type == "article"){
      $href = "";
      $onClick = "Gofast.triggerEditableInput('.gofastArticleContent > div')";
      $text = t('Edit this article', array(), array('context' => 'gofast'));
      $access_functions[] = 'gofast_contextual_menu_not_from_browser';
      $page[] = 'gofast_contextual_menu_not_from_browser';
  }else if($node->type == "contact"){
      $href = "/node/{$nid}/edit"   ;
      $text = t('Edit this contact', array(), array('context' => 'gofast'));
  }else if($node->type == "userlist"){
      $href = "/userlist/{$nid}/edit"   ;
      $text = t('Edit this userlist', array(), array('context' => 'gofast'));
  }else if($node->type == "forum"){
    $href = null;
    $text = null;
  }else if (gofast_og_is_space($node)) {
    $href = "";
    $onClick = "Gofast.triggerEditableInput('.gofastArticleContent.homeArticle > div', '#oghome')";
    $text = t('Edit the homepage', array(), array('context' => 'gofast'));
    $page = [...$page, ...["gofast_contextual_menu_is_not_root_space", "gofast_contextual_menu_not_from_tree", "gofast_contextual_menu_not_from_browser"]];
  }else{
      $href = "/node/{$nid}/edit";
      $text = t('Edit this content', array(), array('context' => 'gofast'));
  }

  return $text ? array(
      'text' => $text,
      'link_id' => '',
      'href' => $href,
      'icon_class' => 'fa fa-edit',
      'target' => '',
      'onClick' => $onClick ?: '',
      'title' => '',
      'page' => $page,
      'type' => array('webform', 'conference', 'article', 'contact', 'userlist', 'forum', 'private_space', 'group', 'organisation', 'extranet', 'public'),
      'access_function' => $access_functions,
      'divider' => $node->type == "private_space" ? FALSE : TRUE
  ) : null;
}

function gofast_contextual_menu_create_flag($flag_name, $flag_icon, $array_type = "alfresco_item", $divider = FALSE,  $entity_id, $variables = array()){
  $flag = flag_get_flag($flag_name);
  if (!$flag) {
    // Flag does not exist.
    return;
  }
  if (!$flag->access($entity_id) && (!$flag->is_flagged($entity_id) || !$flag->access($entity_id, 'flag'))) {
    // User has no permission to use this flag.
    return;
  }

  //if user doesn't member of space, return
  global $user;
  if(in_array($array_type, array('groups','organisation','extranet', 'public'))){
    $role_name = gofast_og_get_user_final_roles_for_space('node',$entity_id,$user->uid);
    if(empty($role_name)){
       return;
    }
  }

  $theme_suggestion = array();
  $theme_suggestion[] = 'flag__' . $flag->name . '__ctx';
  $theme_suggestion[] = 'flag__' . $flag->link_type . '__ctx';
  $theme_suggestion[] = 'flag';

  $action = $flag->is_flagged($entity_id) ? 'unflag' : 'flag';

  $link_type = $flag->get_link_type();
  $link = module_invoke($link_type['module'], 'flag_link', $flag, $action, $entity_id);

  $href = isset($link['href']) ? check_url(url($link['href'], $link)) : FALSE;
  $text = isset($link['title']) ? $link['title'] : $flag->get_label($action . '_short', $entity_id);
  $title = isset($link['attributes']['title']) ? check_plain($link['attributes']['title']) : check_plain(strip_tags($flag->get_label($action . '_long', $entity_id)));
  return [
    'href' => $href,
    'flag' => TRUE,
    'link_class' => 'flag flag-action flag-link-toggle',
    'icon_class' => $flag_icon,
    'text' => $text,
    'title' => $title,
    'page' => array('gofast_contextual_menu_all_pages', 'gofast_contextual_menu_node_is_not_delete'),
    'type' => $array_type,
    'access_function' => array(),
    'divider' => $divider,
    'hide_from_mobile' => isset($variables['hide_from_mobile']) ? $variables['hide_from_mobile'] : '',
    'hide_from_tablet' => isset($variables['hide_from_tablet']) ? $variables['hide_from_tablet'] : '',
    'hide_from_essential' => isset($variables['hide_from_essential']) ? $variables['hide_from_essential'] : ''
  ];
}

function gofast_contextual_menu_user_is_administrator($node, $browser_path, $fromTree, $menu_item){

  global $user;
  if(in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $node->nid, $user->uid), true)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_user_can_create_subspace($node, $browser_path, $fromTree, $menu_item){

  global $user;
  if(in_array('administrator member', gofast_og_get_user_final_roles_for_space('node', $node->nid, $user->uid), true)){
    return TRUE;
  }else{
    $spaces_defaults = gofast_admin_get_space_defaults();
    
    //Check special configuration
    if(!$spaces_defaults['create_sub_space']){
      return FALSE;
    }else{
      //If the previous configuration is enabled, all users are able to create 2nd level subspaces
      $first_level_spaces = array_merge(
        gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_GROUPS_GID, FALSE, FALSE, TRUE),
        gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_EXTRANET_GID, FALSE, FALSE, TRUE)
      );
      
      if(in_array($node->nid, $first_level_spaces)){
        return TRUE;
      }else{
        return FALSE;
      }
    }
  }
}

function gofast_contextual_menu_is_subspace($node, $browser_path, $fromTree, $menu_item){
  $spaces_defaults = gofast_admin_get_space_defaults();
  if ($spaces_defaults['create_sub_space']) {
    $first_level_spaces = array_merge(
      gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_GROUPS_GID, FALSE, FALSE, TRUE),
      gofast_og_get_children(GOFAST_CMIS_LOCATIONS_FIELD_EXTRANET_GID, FALSE, FALSE, TRUE)
    );
  }
  if($spaces_defaults['create_sub_space']){
    return TRUE;
  }else{
    return FALSE;
  }
}


function gofast_contextual_menu_space_in_first_level($node, $browser_path, $fromTree, $menu_item){
  $spaces_defaults = gofast_admin_get_space_defaults();
  if ($spaces_defaults['create_sub_space']) {
    $first_level_spaces = array_merge(
      gofast_og_get_children(4, FALSE, FALSE, TRUE),
      gofast_og_get_children(6, FALSE, FALSE, TRUE)
    );
  }
  if(in_array($node->nid, $first_level_spaces)){
    return TRUE;
  }else{
    return FALSE;
  }
}


function gofast_contextual_menu_is_not_root_space($node, $browser_path, $fromTree, $menu_item){
  if(!gofast_og_is_root_space($node)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_space_is_archived($node, $browser_path, $fromTree, $menu_item){
  if(gofast_group_is_archive($node)){
    return TRUE;
  }else{
    return FALSE;
  }
}

function gofast_contextual_menu_space_not_archived($node, $browser_path, $fromTree, $menu_item){
  if(gofast_group_is_archive($node)){
    return FALSE;
  }else{
    return TRUE;
  }
}

function gofast_contextual_menu_user_can_delete_space($node, $browser_path, $fromTree, $menu_item){
  global $user;
  if ($node == NULL) {
    return FALSE;
  }
  if(gofast_og_can_delete_space($user,$node)){
    return TRUE;
  }else{
    return FALSE;
  }
}

// function gofast_get_target_onlyoffice($node){
//   $onlyoffice_locked= gofast_onlyoffice_document_get_soft_lock($node);
//   $locked = gofast_cmis_node_get_lock($node);

//   if ($locked != "nolocked" && $onlyoffice_locked == "1") {
//     $target = "";
//   } elseif ($locked != false && $onlyoffice_locked == "0") {
//     $target = "";
//   }
//   return $target;
// }

function gofast_contextual_menu_is_not_confidential_internal($node, $browser_path, $fromTree, $menu_item){
  $is_not_confidential = !(isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Confidential Data");
  $is_not_internal = !(isset($node->field_criticity['und'][0]['tid']) && taxonomy_term_load($node->field_criticity['und'][0]['tid'])->name == "Internal Distribution");
  return $is_not_confidential && $is_not_internal;
}

function gofast_contextual_menu_is_not_member($node){
  global $user;

  if(og_is_member('node', $node->nid, 'user',$user->uid)){
    return FALSE;
  }else{
    return TRUE;
  }
}

function gofast_contextual_menu_check_url_permission($node, $browser_path, $fromTree, $menu_item){
     //check url permission
        $path = substr($menu_item['href'], 1);
        if ($router_item = menu_get_item($path)) {
            if (!$router_item['access']) {
             return false;
            }else{
             return true;
            }
        }else{
            return true;
        }
}

function gofast_contextual_menu_is_not_multifiled($node) {
  if(count((array) $node->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}[LANGUAGE_NONE]) == 1){
    return true;
    }else{
        //multiple og. check if at lease one private space
        foreach($node->{GOFAST_OG_CONTENT_MEMBERSHIP_FIELD}[LANGUAGE_NONE] as $og){
          $type = gofast_get_node_type($og["target_id"]);
          if($type == "Personal Space"){
                return false;
          }
        }
        return true;
    }
}

function gofast_contextual_menu_has_no_subspace($node) {
  $children = gofast_og_get_children($node->nid);
  return empty($children);
}

function gofast_contextual_menu_is_not_picture($node) {
  $node_mimetype = gofast_cmis_get_mimetype_extension_match_array()[gofast_cmis_node_get_extension($node)];
  return strpos($node_mimetype, "image") === FALSE;
}

function gofast_contextual_menu_is_onlyoffice_compatible($node) {
  //check if this file can be edited with OnlyOffice
  if (!in_array(strtolower(gofast_cmis_node_get_extension($node)), gofast_onlyoffice_editable_document_extensions())) {
    //Check if this document is an old MS format
    if(in_array(strtolower(gofast_cmis_node_get_extension($node)), gofast_onlyoffice_old_ms_extensions())){
      return t('This file format is obsolete and incompatible with Onlyoffice coedition. You can change it\'s format from the file browser : rename the title to change the .doc/.ppt/.xls to .docx/.pptx/.xlsx', array(), array('context' => 'gofast:gofast_contextual_menu'));
    }else{
      return t('This file cannot be edited with Onlyoffice, please click on Edit from my PC', array(), array('context' => 'gofast:gofast_contextual_menu'));
    }
  }
  
  return true;
}

function gofast_contextual_menu_is_in_store($node) {
  $cmis_object = gofast_cmis_item_get(gofast_cmis_node_get_item_id($node), TRUE);
  if (gofast_og_is_space($node)) {
    return $cmis_object->properties["cmis:path"] != null;
  }
  return TRUE;
}

function gofaxt_contextual_menu_is_wiki($node, $browser_path, $fromTree, $menu_item){
  return gofast_book_is_node_wiki_article($node->nid);
}

function gofaxt_contextual_menu_is_not_wiki($node, $browser_path, $fromTree, $menu_item){
  return !gofast_book_is_node_wiki_article($node->nid);
}

function gofaxt_contextual_menu_is_not_homepage($node, $browser_path, $fromTree, $menu_item){
  return !gofast_book_is_article_homepage($node->nid);
}

/**
 * Check if folder have not multiple parents
 *
 * @param  object $node
 * @return bool true if folder have not multiple parents
 */
function gofast_contextual_menu_folder_is_not_mirroring($node, $browser_path){
  $path = str_replace('/alfresco/webdav', "", $browser_path);

  $item = gofast_cmis_item_get_by_path(urldecode($path));
  $reference = $item->properties['alfcmis:nodeRef'];

  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);

  if ($folder_parents && count($folder_parents) > 1) {
    return t('The folder have multiple locations, then you can\'t delete it.');
    exit;
  }else{
    return true;
  }
}


/**
 * Check if folder parents have not multiple parents
 *
 * @param  object $node
 * @return bool true if folder have not multiple parents
 */
function gofast_contextual_menu_parent_is_not_mirroring($node, $browser_path){

  $path = str_replace('/alfresco/webdav', "", $browser_path);

  $item = gofast_cmis_item_get_by_path(urldecode($path));
  $reference = $item->properties['alfcmis:nodeRef'];

  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);

  foreach ($folder_parents as $parent) {
    $parent_reference = gofast_cmis_item_get_by_path($parent)->properties['alfcmis:nodeRef'];
    $parents_parents = gofast_cmis_webservice_get_node_parents($parent_reference);
    // If more than 1 parents, it's a mirroring
    if (count($parents_parents) > 1) {
      return t('The parents folder have multiple locations, then you can\'t share it.');
    }
  }
  
  return true;

}

function gofast_contextual_menu_node_not_in_mirror_folder($node, $browser_path){
  
  // Check if the node is in a mirror folder
  $reference = $node->reference;
  
  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);
  
  foreach ($folder_parents as $parent) {
    $parent_reference = gofast_cmis_item_get_by_path($parent)->properties['alfcmis:nodeRef'];
    $parents_parents = gofast_cmis_webservice_get_node_parents($parent_reference);
    // If more than 1 parents, it's a mirroring
    if (count((array) $parents_parents) > 1) {
      return t('The node is in a mirror folder, then you can\'t share it.');
    }
  }
  
  return true;
}

function gofast_contextual_menu_folder_nodes_are_not_multified($node, $browser_path){
  
  // Reach all documents into folder
  
  $path = str_replace('/alfresco/webdav', "", $browser_path);
  
  $item = gofast_cmis_item_get_by_path(urldecode($path));
  $reference = $item->properties['alfcmis:nodeRef'];
  
  $folder_parents = gofast_cmis_webservice_get_node_parents($reference);
  
  // If it's already a mirror folder, then can share it
  if(count($folder_parents) > 1){
    return true;
  }
  
  // Get descendants
  $descendants = gofast_cmis_webservice_item_get_descendants($reference, 'documents');
  foreach ($descendants as $key => $descendant) {
    
    // Get all locations of the document
    $locations = gofast_cmis_webservice_get_node_parents($descendant->id);
    
    // If more than 1 locations, it's a multified
    if (count($locations) > 1) {
      return t('Nodes inside have multiple locations, then the folder can be a mirror folder');
    }
  }
  
  return true;
  
}

function gofast_contextual_menu_folder_folders_are_not_mirror($node, $browser_path){
  $res = true;

  // Reach all folders into folder
  $path = str_replace('/alfresco/webdav', "", $browser_path);

  $item = gofast_cmis_item_get_by_path(urldecode($path));
  $reference = $item->properties['alfcmis:nodeRef'];

  // Get descendants
  $descendants = gofast_cmis_webservice_item_get_descendants($reference, 'folders');

  foreach ($descendants as $key => $descendant) {

    // Get reference with the path 
    $descendant_reference = gofast_cmis_item_get_by_path($descendant)->properties['alfcmis:nodeRef'];
    // Get all locations of the folder
    $descendants_parents = gofast_cmis_webservice_get_node_parents($descendant_reference);
    
    if (count($descendants_parents) > 1) {
      // Foreach $descendants_parents
      foreach ($descendants_parents as $key => $descendant_parent) {
        
        // Get item
        $descendant_parent_item = gofast_cmis_item_get_by_path($descendant_parent);
        
        // Get reference
        $descendant_parent_reference = $descendant_parent_item->properties['alfcmis:nodeRef'];
        
        // Get all parents of the descendant$descendant_parent
        $descendant_parent_parents = gofast_cmis_webservice_get_node_parents($descendant_parent_reference);
        
        // If more than 1 parents, it's a mirroring
        if (count($descendant_parent_parents) <= 1) {
          $res = false;
        }
      }
    }
  }

  if($res == false){
    return t('There are mirrors folders inside folder, then you can\'t share it.');
  }

  return $res;
}

function gofast_contextual_menu_node_is_pdf($node, $browser_path){
  $extension = gofast_cmis_node_get_extension($node);
  if ($extension == "pdf" || $extension == "PDF") {
      return TRUE;
  }else{
    return t('This file is not a PDF');
  }
}

function gofast_contextual_menu_userlist_can_be_sync($node, $browser_path){
  if($node->field_is_gofast_sync[LANGUAGE_NONE][0]["value"] == 0 && $node->field_is_ldap_sync[LANGUAGE_NONE][0]["value"] == 0){
    return t("Synchronisation is not configured on this userlist", array(), array('context' => 'gofast:gofast_userlist'));
  }else{
    return true;
  }
}

function gofaxt_contextual_menu_wiki_is_subwiki_home($node, $browser_path){
  if($node->type != "article"){
    return TRUE;
  }
  
  // Get target folder
  $ref = gofast_cmis_node_get_reference_by_nid_without_cmis($node->nid);
  $item = gofast_cmis_item_get($ref);
  $name = str_replace(".html", "", $item->properties["cmis:name"]);
  $path = gofast_cmis_webservice_get_node_parents($ref)[0];
  $folder = end(explode('/', $path));
  
  if($folder == $name){
    //This is the "main" wiki of subwikis
    return t("You can move this subwiki by moving it's folder");
  }
  
  return TRUE;
}