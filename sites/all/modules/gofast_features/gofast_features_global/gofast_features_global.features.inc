<?php
/**
 * @file
 * gofast_features_global.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gofast_features_global_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr" && $api == "apachesolr_environments") {
    return array("version" => "1");
  }
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return array("version" => "3");
  }
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return array("version" => "1");
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "ldap_servers" && $api == "ldap_servers") {
    return array("version" => "1");
  }
  if ($module == "radioactivity" && $api == "radioactivity_decay_profile") {
    return array("version" => "1");
  }
  if ($module == "slick" && $api == "slick_default_preset") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gofast_features_global_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function gofast_features_global_flag_default_flags() {
  $flags = array();
  // Exported flag: "Bookmarks".
  $flags['bookmarks'] = array(
    'entity_type' => 'node',
    'title' => 'Bookmarks',
    'global' => 0,
    'types' => array(
      0 => 'alfresco_item',
      1 => 'extranet',
      2 => 'webform',
      3 => 'group',
      4 => 'organisation',
      5 => 'article',
      6 => 'page',
      7 => 'book',
      8 => 'public',
      9 => 'forum',
    ),
    'flag_short' => 'Bookmark this',
    'flag_long' => 'Add this post to your bookmarks',
    'flag_message' => 'This post has been added to your bookmarks',
    'unflag_short' => 'Unbookmark this',
    'unflag_long' => 'Remove this post from your bookmarks',
    'unflag_message' => 'This post has been removed from your bookmarks',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => -7,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'print' => 0,
      'ical' => 0,
      'token' => 0,
      'custom_gofast' => 0,
      'gofast_node_infos' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Cart".
  $flags['cart'] = array(
    'entity_type' => 'node',
    'title' => 'Cart',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Add to cart',
    'flag_long' => 'Add this content to your cart',
    'flag_message' => 'Added to your cart',
    'unflag_short' => 'Remove from cart',
    'unflag_long' => 'Remove from your cart',
    'unflag_message' => 'Removed from your cart',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'print' => 0,
      'ical' => 0,
      'token' => 0,
      'custom_gofast' => 0,
      'gofast_node_infos' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Public bookmark".
  $flags['flag_public'] = array(
    'entity_type' => 'node',
    'title' => 'Public bookmark',
    'global' => 1,
    'types' => array(
      0 => 'alfresco_item',
      1 => 'article',
      2 => 'page',
      3 => 'book',
      4 => 'forum',
    ),
    'flag_short' => 'Add public bookmark',
    'flag_long' => 'Add this content to Groups/Organisations \'s favorites',
    'flag_message' => 'This post has been added to the public bookmarks',
    'unflag_short' => 'Remove public bookmark',
    'unflag_long' => '',
    'unflag_message' => 'This post has been removed from the public bookmarks',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => -6,
    'show_in_links' => array(
      'full' => 0,
      'teaser' => 0,
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'print' => 0,
      'ical' => 0,
      'token' => 0,
      'custom_gofast' => 0,
      'gofast_node_infos' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Subscribe: Content".
  $flags['subscribe_node'] = array(
    'entity_type' => 'node',
    'title' => 'Subscribe: Content',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Subscribe',
    'flag_long' => 'Subscribe to this content',
    'flag_message' => 'You are now subscribed to this content.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => 'Unsubscribe from this content',
    'unflag_message' => 'You are no longer subscribed to this content.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 'teaser',
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'print' => 0,
      'ical' => 0,
      'token' => 0,
      'custom_gofast' => 0,
      'gofast_node_infos' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Subscribe: Group".
  $flags['subscribe_og'] = array(
    'entity_type' => 'node',
    'title' => 'Subscribe: Group',
    'global' => 0,
    'types' => array(
      0 => 'extranet',
      1 => 'group',
      2 => 'organisation',
      3 => 'public',
    ),
    'flag_short' => 'Subscribe',
    'flag_long' => 'Subscribe to this space',
    'flag_message' => 'You are now subscribed to this space.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => 'Unsubscribe from this space',
    'unflag_message' => 'You are no longer subscribed to this space.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 'teaser',
      'rss' => 0,
      'search_index' => 0,
      'search_result' => 0,
      'print' => 0,
      'ical' => 0,
      'token' => 0,
      'custom_gofast' => 0,
      'gofast_node_infos' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Subscribe: Term".
  $flags['subscribe_term'] = array(
    'entity_type' => 'taxonomy_term',
    'title' => 'Subscribe: Term',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Subscribe',
    'flag_long' => 'Subscribe to this term',
    'flag_message' => 'You are now subscribed to this term.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => 'Unsubscribe from this term',
    'unflag_message' => 'You are no longer subscribed to this term.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'ical' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  // Exported flag: "Subscribe: User".
  $flags['subscribe_user'] = array(
    'entity_type' => 'user',
    'title' => 'Subscribe: User',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Subscribe',
    'flag_long' => 'Subscribe to this user',
    'flag_message' => 'You are now subscribed to this user.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => 'Unsubscribe from this user',
    'unflag_message' => 'You are no longer subscribed to this user.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'search_index' => 0,
      'search_result' => 0,
      'ical' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => 0,
    'show_on_profile' => 1,
    'access_uid' => 'others',
    'module' => 'gofast_features_global',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function gofast_features_global_image_default_styles() {
  $styles = array();

  // Exported image style: gofast_thumbnail.
  $styles['gofast_thumbnail'] = array(
    'label' => 'Gofast Thumbnail (40 x 40)',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 40,
          'height' => 40,
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_default_message_type().
 */
function gofast_features_global_default_message_type() {
  $items = array();
  $items['message_log'] = entity_import('message_type', '{
    "name" : "message_log",
    "description" : "Message Log",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "en",
    "arguments" : null,
    "message_text" : { "en" : [
        {
          "value" : "\\u003Cp\\u003EMessage Log\\u003C\\/p\\u003E\\r\\n",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003EMessage Log\\u003C\\/p\\u003E\\n"
        }
      ]
    },
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_node_info().
 */
function gofast_features_global_node_info() {
  $items = array(
    'alfresco_item' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('A <em>document</em>.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'article' => array(
      'name' => t('Page Intranet'),
      'base' => 'node_content',
      'description' => t('Utilisez les <em>articles</em> pour des contenus possédant une temporalité tels que des actualités, des communiqués de presse ou des billets de blog.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'blog' => array(
      'name' => t('Blog'),
      'base' => 'node_content',
      'description' => t('A <em>status</em>.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'book' => array(
      'name' => t('Page de livre'),
      'base' => 'node_content',
      'description' => t('<em>Les livres</em> possèdent une navigation hiérarchique intégrée. Cela est utile pour des guides ou des tutoriels.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'conference' => array(
      'name' => t('Conference'),
      'base' => 'node_content',
      'description' => t('Jitsi-meet conference'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'contact' => array(
      'name' => t('Contact'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'extranet' => array(
      'name' => t('Extranet'),
      'base' => 'node_content',
      'description' => t('Partitioned space for external groups and projects managment.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Detailed description'),
    ),
    'group' => array(
      'name' => t('Groupe'),
      'base' => 'node_content',
      'description' => t('A group consists of members around a theme (project, product, team ...).'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Detailed description'),
    ),
    'kanban' => array(
      'name' => t('Kanban'),
      'base' => 'node_content',
      'description' => t('kanban board'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'organisation' => array(
      'name' => t('Organisation'),
      'base' => 'node_content',
      'description' => t('Une organisation est un espace collaboratif dédié à une division, un département, un service, etc. Il s\'agit d\'espaces hiérarchisés qui représentent votre organigramme.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Detailed description'),
    ),
    'page' => array(
      'name' => t('Page de base'),
      'base' => 'node_content',
      'description' => t('Utilisez les <em>pages de base</em> pour votre contenu statique, tel que la page \'Qui sommes-nous\'.'),
      'has_title' => '1',
      'title_label' => t('Titre'),
      'help' => '',
    ),
    'private_space' => array(
      'name' => t('Private Space'),
      'base' => 'node_content',
      'description' => t('A private space for a user'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
    'public' => array(
      'name' => t('Public'),
      'base' => 'node_content',
      'description' => t('Public space that consists of contents, groups, projects, etc., with unrestricted access.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Detailed description'),
    ),
    'task' => array(
      'name' => t('Task'),
      'base' => 'node_content',
      'description' => t('Kanban Task'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'userlist' => array(
      'name' => t('UserList'),
      'base' => 'node_content',
      'description' => t('Used to group users and facilitate permission definition.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => t('Detailed description'),
    ),
    'webform' => array(
      'name' => t('Formulaire'),
      'base' => 'node_content',
      'description' => t('Créer un nouveau formulaire ou questionnaire accessible aux utilisateurs. Les soumissions et leurs statistiques sont enregistrées et accessibles aux utilisateurs privilégiés.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
