<?php


function gofast_create_menu_create()
{
$link = [
'icon' => 'fas fa-plus',
'label' => 'Create',
'id' => 'gofastMenuTopbarCreateMenuItem',
'class' => 'menu-item-rel',
'subclass' => 'menu-submenu-left',
'href' => '',
'menu' => []
];
$menu = array();

$conference = array(
'icon' => 'fas fa-video',
'label' => t('Conference'),
'href' => '/node/add/conference',
'class' => '',
'subclass' => 'menu-submenu-right',
);
$menu[] = $conference;

$content = array(
'icon' => 'fas fa-file-medical',
'label' => t('Content'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '',
'menu' => array(
'file' => array(
'icon' => 'far fa-file',
'class' => '',
'subclass' => 'menu-submenu-right',
'label' => t('File, Document'),
'href' => '/node/add/alfresco-item'
),
'article' => array(
'icon' => 'far fa-ballot',
'label' => t('Wiki article'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/article'
),
'external' => array(
'icon' => 'fas fa-globe n-color',
'label' => t('External page'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/alfresco-item?external=true'
),
'forum' => array(
'icon' => 'far fa-comments',
'label' => t('Forum'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/forum'
),
'webform' => array(
'icon' => 'far fa-list-alt',
'label' => t('Webform'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/webform'
),
)
);
$menu[] = $content;

$space = array(
'icon' => 'fas fa-folder-plus',
'label' => t('Space'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '',
'menu' => array(
'group' => array(
'icon' => 'fas fa-users n-color',
'label' => t('Group'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/group'
),
'organisation' => array(
'icon' => 'fas fa-sitemap n-color',
'label' => t('Organisation'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/organisation'
),
'public' => array(
'icon' => 'fas fa-share-alt n-color',
'label' => t('Public'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/public'
),
'extranet' => array(
'icon' => 'fas fa-globe-europe n-color',
'label' => t('Extranet'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/node/add/extranet'
),
)
);
$menu[] = $space;

  $user = array(
    'icon' => 'fas fa-address-book',
    'label' => t('Contact'),
    'class' => '',
    'subclass' => 'menu-submenu-right',
    'href' => '/modal/nojs/contact/add',
    'linkClass' => 'ctools-use-modal'
  );
  $menu[] = $user;

$user = array(
'icon' => 'fas fa-user-plus',
'label' => t('User'),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/admin/people/create'
);
$menu[] = $user;

$userlist = array(
'icon' => 'fas fa-user-friends',
'label' => t("Userlist", array(), array("context" => "gofast")),
'class' => '',
'subclass' => 'menu-submenu-right',
'href' => '/userlist/add'
);
$menu[] = $userlist;

foreach (module_implements('alter_topbar_create_menu') as $module){
  $menu = module_invoke($module, 'alter_topbar_create_menu', $menu);
}

$link['menu'] = $menu;
$link['title'] = t('New', array(), array("context" => "gofast"));
  
return $link;
}


function gofast_create_menu_workflow($isEssential = false){
  //$unread_workflows_count = json_decode(gofast_menu_get_unread_workflows())->count;
  $unread_workflows_count = 0;
  $menu = [
    'title' => t('Workflows & Tasks'),
    'id' => 'gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows',
    'id_toggle' => 'go-navbar-menu-workflow-item',
    'icon' => 'fas fa-cogs',
    'count' => $unread_workflows_count
  ];
  if(!$isEssential){
    $menu["href"] = '/workflow/dashboard';
  }
  return $menu;

}


function gofast_create_menu_nofification()
{

$unread_notifications_count = json_decode(gofast_menu_get_unread_notifications())->count;

$menu = [
'id' => 'gofast_view-gofast_private_msg-gofast_notifications',
'id_toggle' => 'go-navbar-menu-taches-item',
'icon' => 'fa fa-flag-o',
'count' => $unread_notifications_count
];

return $menu;
}

function gofast_create_menu_others_menus(){

$menus = [];

$unread_rss_count = '';
$unread_favorites_count = '';

$rss = [
'id' => 'gofast_aggregator',
'id_toggle' => 'go-navbar-menu-rss-item',
'title' => 'Flux RSS',
'icon' => 'fas fa-rss',
'count' => $unread_rss_count,
'desktop_only' => TRUE
];

$menus[] = $rss;

$favorites = [
'id' => 'gofast_topbar_flag_bookmarks',
'title' => t('My Favorites', array(), array("context" => "gofast")),
'id_toggle' => 'go-navbar-menu-favorites-item',
'icon' => 'far fa-star',
'count' => $unread_favorites_count
];
$menus[] = $favorites;

$last_recenlty_read = [
'id' => 'recenlty_read_block_menu',
'title' => t('My lasts recently read', array(), array("context" => "gofast")),
'icon' => "fas fa-history",
];
$menus[] = $last_recenlty_read;

return $menus;
}

function gofast_create_menu_about(){

  $link = [
    'icon' => 'fas fa-question',
    'label' => '',
    'id' => 'gofastAboutMenu',
    'class' => '',
    'subclass' => 'menu-submenu-right',
    'href' => '',
    'linkClass' => '',
    'target' => '',
    'onClick' => 'Gofast.tour.launchEssentialTour(event)',
    'menu' => []
  ];

  $menu = array();

  if (module_exists("gofast_community")) {
    $manifest = gofast_update_get_release_manifest();
    $hotfix_available = gofast_update_get_available_hotfix_version($manifest);
    $version_available = gofast_update_get_available_version($manifest);
    if (!empty($hotfix_available || !empty($version_available))) {
      $main_icon = 'fas fa-exclamation-circle ';
    } else {
      $link['icon'] = 'fas fa-question';
    }
  }


  $forum = array(
    'href' => 'https://community.ceo-vision.com',
    'label' => t('Forums', array(), array('context' => 'gofast:gofast_menu')),
    'icon' => 'fas fa-comments',
    'target' => "_blank"
  );
  $menu[] = $forum;

  if (variable_get("gofast_carousel_active", FALSE)) {
    $features = array(
      'href' => '/gofast/nojs/carousel',
      'linkClass' => 'ctools-use-modal',
      'label' => t('New features'),
      'icon' => 'fas fa-plus',
    );
    $menu[] = $features;
  }

  global $user;
  $gofast_url_doc = "https://gofast-docs.readthedocs.io/" . $user->language . "/4.0/";
  $documentation = array(
    'href' => $gofast_url_doc,
    'label' => 'Documentation',
    'icon' => 'fas fa-book',
    'target' => "_blank"
  );
  $menu[] = $documentation;

  if (gofast_essential_is_essential()) {
    $tour = array(
      'icon' => 'fas fa-question',
      'label' => t('Launch help tour', array(), array('context' => 'gofast:gofast_tour')),
      'onClick' => "Gofast.tour.tourButtonAction(event)",
    );
    $menu[] = $tour;
  }

  if (variable_get("gofast_has_custom_menu_link", FALSE)) {
    $custom_menu_link = array(
      'href' => variable_get("gofast_custom_menu_link_href", "https://community.ceo-vision.com"),
      "label" => variable_get("gofast_custom_menu_link_label", t("Custom Link", [], ["context" => "gofast:gofast_menu"])),
      "icon" => variable_get("gofast_custom_menu_link_icon", "fas fa-archway"),
      "target" => "_blank"
    );
    $menu[] = $custom_menu_link;
  }

  $about = array(
    'href' => '/gofast/nojs/versions',
    'linkClass' => 'ctools-use-modal',
    'label' => t('About'),
    'icon' => 'fas fa-question-circle'
  );
  $menu[] = $about;

  if (module_exists("gofast_community")) {
    $community = array(
      'href' => '/admin/config/gofast/update',
      'label' => 'Update',
      'icon' => 'fas fa-exclamation-circle'
    );

    if (!empty($hotfix_available || !empty($version_available))) {
      $community['icon'] = 'fas fa-exclamation-circle danger';
    }

    $menu[] = $community;

  }

  $link['menu'] = $menu;

  return $link;
}

function gofast_create_menu_profile()
{
  global $user;

  $link = [
    'icon' => 'fas fa-user',
    'label' => '',
    'id' => '',
    'class' => '',
    'href' => '',
    'menu' => []
  ];

  $profile_r['profil'] = array(
    'href' => '/user/' . $user->uid,
    'label' => t('My Profile', array(), array('context' => 'gofast:gofast_menu')),
  );
  $profile_r['subscriptions'] = array(
    'href' => '/modal/nojs/subscriptions',
    'label' => t('Subscriptions', array(), array('context' => 'gofast:gofast_menu')),
  );
  $profile_r['logout'] = array(
    'href' => '/user/logout',
    'label' => t('Logout', array(), array('context' => 'gofast:gofast_menu')),
  );

  $link['menu'] = $profile_r;


return $link;
}



/**
 *
 * Asynchronous function called by "Drupal.behaviors.async_last_recently_read_menu"
 *
 * @return recently read block
 */
function gofast_menu_get_last_recenlty_read($size = 10) {
    global $user;

    $query = db_select("recently_read", "rr")
              ->fields("rr", array("entity_id"));
    $query->condition("rr.sid", $user->uid, "=");
    $query->orderBy("rr.timestamp", "DESC");
    $nids = $query->execute()->fetchCol();

    $recently_read = array();
    foreach($nids as $nid) {
      if(count($recently_read) >= $size){
        break;
      }
      
      $node = node_load($nid);
      // Don't show node if user can't access it
      if(!node_access("view", $node)){
        continue;
      };

      $recently_read[] =  $node;
    }
    
    print theme('gofast_menu_topbar_recently_read', array('recently_read' => $recently_read));
}

/**
 *
 * Asynchronous function called by "Drupal.behaviors.async_last_recently_read_menu"
 *
 * @return recently read block
 */
function gofast_menu_get_favorites() {
  print theme('gofast_menu_topbar_favorites');
}

function gofast_menu_get_rssFeed() {
  drupal_add_http_header('Content-Type', 'application/json');
  // $rssFeed =  gofast_get_block_menu(0, 0, 'gofast_aggregator', 'gofast_aggregator', 'Feed');
  // print $rssFeed;

  // in the end, this should be optimized with some caching or memoizing :
  // example: if the timestamp written at the beginning of the file or the redis entry is less than one hour, we load directly the cached rss feed, otherwise we compute it and overwrite the file
  $urls = db_query("SELECT url FROM {aggregator_feed}")->fetchCol();
  $rssItems = [];
  foreach ($urls as $url) {
    $ch = curl_init($url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);

    // Identify the request User Agent (as Firefox on Linux but any value may work) to prevent RSS load being blocked due to missing User Agent
    curl_setopt($ch, CURLOPT_USERAGENT, 'Mozilla/5.0 (X11; Linux x86_64; rv:100.0) Gecko/20100101 Firefox/100.0');
    $feed = curl_exec($ch);
    if (!$feed) {
      continue;
    }
    $rss = new SimpleXMLElement($feed);
    foreach($rss->channel->item as $item) {
      $rssItems[] = ["link" => $item->link, "title" => $item->title, "date" => strtotime($item->pubDate)];
    }
  }
  usort($rssItems, function($a, $b) {
    return (int) $b['date'] <=> (int) $a['date'];
  });
  print json_encode(["output" => theme('gofast_menu_topbar_rss_feed', array('items' => $rssItems))]);
  exit();
}

function gofast_menu_get_privateMessages() {
  drupal_add_http_header('Content-Type', 'application/json');
  $pm =  gofast_get_block_menu(0, 0, 'gofast_private_msg', 'gofast_inbox', 'Internal Private Message');
  print $pm;
}

/**
 * This method fetch private messages for global (current) user
 * @return int
 */
function gofast_menu_get_unread_messages()
{
  global $user;
  $count = gofast_privatemsg_unread_count($user);
  return json_encode(array('count' => $count));
}

/**
 * This method fetch private messages for global (current) user
 * @return int
 */
function gofast_menu_get_unread_notifications()
{
  global $user;
  $count = 0;
  return json_encode(array('count' => $count));
}

/**
 * This method fetch private messages for global (current) user
 * @return int
 */
function gofast_menu_get_unread_workflows()
{
  if (module_exists("gofast_workflows")) {
    global $user;
    $count = gofast_workflows_get_number_pending_tasks();

    //Init workflow count context
    gofast_poll_set_context('workflows', 'count', $count);
  } else {
    $count = 0;
  }
  return json_encode(array('count' => $count));
}


// function gofast_menu_get_html_navigation()
// {

//   $unread_notifications_count = json_decode(gofast_menu_get_unread_notifications())->count;
//   $unread_messages_count = json_decode(gofast_menu_get_unread_messages())->count;
//   $unread_workflows_count = json_decode(gofast_menu_get_unread_workflows())->count;

//   $menu = array(
//     'notifications' => array(
//       'id' => 'gofast_view-gofast_private_msg-gofast_notifications',
//       'id_toggle' => 'go-navbar-menu-taches-item',
//       'icon' => 'fa fa-flag-o fa-2x',
//       'count' => $unread_notifications_count
//     ),
//     'workflow' => array(
//       'id' => 'gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows',
//       'id_toggle' => 'go-navbar-menu-workflow-item',
//       'icon' => 'fas fa-cogs',
//       'count' => $unread_workflows_count
//     ),
//     'messages' => array(
//       'id' => 'gofast_view-gofast_private_msg-gofast_inbox',
//       'id_toggle' => 'go-navbar-menu-message-item',
//       'block_title' => 'Internal Private Messages',
//       'icon' => 'far fa-envelope',
//       'count' => $unread_messages_count
//     ),
//     'rss' => array(
//       'id' => 'gofast_view-gofast_aggregator-gofast_aggregator',
//       'id_toggle' => 'go-navbar-menu-rss-item',
//       'block_title' => 'Flux RSS',
//       'icon' => 'fas fa-rss',
//       'count' => $unread_messages_count
//     ),
//     'favorites' => array(
//       'id' => 'gofast_view-gofast_flag_bookmarks-gofast_flag_bookmarks',
//       'block_title' => 'Bookmarks',
//       'id_toggle' => 'go-navbar-menu-favorites-item',
//       'icon' => 'far fa-star',
//       'count' => $unread_messages_count
//     )
//   );


//   $return = theme('gofast_menu_navigation', array('menu' => $menu));

//   return $return;
// }
// function gofast_menu_get_html_sidebar()
// {
//   global $user;
//   $menu = array(
//     'dashboard' => array(
//       'title' => t('Dashboard'),
//       'icon' => 'fas fa-tachometer-alt',
//       'href' => '/dashboard'
//     ),
//     'activity' => array(
//       'title' => t('Activity'),
//       'icon' => 'fas fa-list-alt',
//       'href' => '/activity'
//     ),
//     'espaces' => array(
//       'title' => t('Browser'),
//       'icon' => 'fas fa-folder-open',
//       'href' => '/gofast/browser'
//     )
//   );
//   $submenu = array(
//     'calendar' => array('title' => t('Calendar'), 'icon' => 'fas fa-calendar-alt', 'href' => '/node/' .  gofast_og_get_user_private_space($user->uid) . "#ogcalendar"),
//     'task' => array('title' => t('Tasks'), 'icon' => 'fas fa-cogs', 'href' => '#'),
//     'discussion' => array('title' => t('Discussion'), 'icon' => 'fas fa-comments', 'href' => '#'),
//     'directory' => array('title' => t('Directory'), 'icon' => 'fas fa-address-book', 'href' => '#')
//   );

//   $config = array('title' => t('Configuration'), 'icon' => 'fas fa-tools', 'href' => '#');

//   $return = theme('gofast_menu_sidebar', array('menu' => $menu, 'submenu' => $submenu, 'config' => $config));

//   return $return;
// }

function gofast_menu_get_html_icons_menu()
{
  $unread_notifications_count = json_decode(gofast_menu_get_unread_notifications())->count;
  $unread_messages_count = json_decode(gofast_menu_get_unread_messages())->count;
  $unread_workflows_count = json_decode(gofast_menu_get_unread_workflows())->count;

  $return = theme('gofast_menu_icons', array('unread_notifications_count' => $unread_notifications_count, 'unread_messages_count' => $unread_messages_count, 'unread_workflows_count' => $unread_workflows_count));

  return $return;
}

function gofast_menu_mobile_get_html_icons_menu()
{
  $unread_messages_count = json_decode(gofast_menu_get_unread_messages())->count;
  $unread_workflows_count = json_decode(gofast_menu_get_unread_workflows())->count;

  $return = '<div class="visible-lg gofast-blocks-wrapper">

    <!-- gofast_view-view_name-display_id -->
    <!-- gofast_menu_magical_menu function -->
    <!-- gofast_block_delta-gofast_workflows-gofast_workflows_light_dashboard -->
              <div class="gofast-block block-workflow" id="gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows" data-pinned="false" data-unread="' . $unread_workflows_count . '">
                  <span class="pinned"><i class="fa fa-thumb-tack"></i></span>
                  <i class="fa fa-cogs fa-2x"></i>
                  <span class="updated-workflow unread_count badge badge-notify-menu badge-notify">0</span>
                  <div class="gofast-block-outer" >
                      <div class="pointeur"></div>
                      <div class="gofast-block-inner">
                          <!-- workflow_bloc view -->
                          <div style="text-align: center;">
                            <div class="loader-blog"></div>
                          </div>
                      </div>
                  </div>
              </div>

              <div class="gofast-block block-privatemsg" block_title="Internal Private Message" id="gofast_view-gofast_private_msg-gofast_inbox" data-pinned="false" data-unread="' . $unread_messages_count . '">
                  <span class="pinned"><i class="fa fa-thumb-tack"></i></span>
                  <i class="fa fa-envelope-o fa-2x"></i>
                  <span id="unread_pm_count" class="unread_messages unread_count badge badge-notify badge-notify-menu">0</span>
                  <div class="gofast-block-outer" >
                      <div class="pointeur"></div>
                      <div id="gofast_pm_block" class="gofast-block-inner">
                          <!-- privatemsg-privatemsg_bloc view -->
                          <div style="text-align: center;">
                            <div class="loader-blog"></div>
                          </div>
                      </div>
                  </div>
              </div>

              <div class="gofast-block block-bookmarks" id="gofast_view-gofast_flag_bookmarks-gofast_flag_bookmarks" data-pinned="false">
                  <span class="pinned"><i class="fa fa-thumb-tack"></i></span>
                  <i class="fa fa-star-o fa-2x"></i>
                  <div class="gofast-block-outer">
                    <!-- tab headers -->
                    <ul class="nav nav-tabs" >
                      <li id="contentFavoritesTab" class="active" onclick="Gofast.Display_ContentFolders(event);">
                        <a class="bookmarksTab">
                          <tab-heading translate="" ><span onclick="Gofast.Display_ContentFolders(event);">'  . t("Favorites content", array(), array("gofast")) . '</span></tab-heading>
                        </a>
                      </li>
                      <li id="foldersFavoritesTab" class="" onclick="Gofast.Display_FavoritesFolders(event);">
                        <a class="bookmarksTab">
                          <tab-heading translate=""><span onclick="Gofast.Display_FavoritesFolders(event);">' .  t("Favorites folders", array(), array("gofast")) . '</span></tab-heading>
                        </a>
                      </li>
                    </ul>
                      <div class="pointeur"></div>
                      <div class="gofast-block-inner">
                          <!-- flag_bookmarks-block_1 view -->
                          <div style="text-align: center;">
                            <div class="loader-blog"></div>
                          </div>
                      </div>
                  </div>
              </div>

                <div class="gofast-block block-recently-read" id="block-views-gofast-recently-read-block" data-pinned="false">
                  <span class="pinned"><i class="fa fa-thumb-tack"></i></span>
                  <i class="fa fa-eye fa-2x"></i>
                  <div class="gofast-block-outer">
                    <h2 class="block-title block-recently-read-title">' . t("Recently Read") . '</h2>
                    <div style="text-align:center;">
                        <div id="recently-read-actions-loading" class="recenlty-read-actions-loading loader-actions not-processed" style="width:50px;height:50px;display:none;"></div>
                    </div>
                  </div>
                </div>';


  return $return;
}

// function gofast_menu_magical_menu()
// {
//   global $user;
//   $path_exist = 0;
//   $block = module_invoke_all('menu');
//   if (count($block['dashboard']) != NULL) {
//     $path_exist = 1;
//     $frontpage = variable_get('site_frontpage');
//   }

//   $block_recenlty_read = module_invoke('views', 'block_view', 'gofast_recently_read-block');
//   $block_recenlty_read_content = $block_recenlty_read['content'];


//   return theme('gofast_menu_magical_menu', array(
//     'is_admin' => $is_admin,
//     'path_exist' => $path_exist,
//     'block_recenlty_read' => $block_recenlty_read,
//     'block_recenlty_read_content' => $block_recenlty_read_content
//   ));
// }

// function gofast_menu_mobile_magical_menu()
// {
//   global $user;
//   $path_exist = 0;
//   $block = module_invoke_all('menu');
//   if (count($block['dashboard']) != NULL) {
//     $path_exist = 1;
//     $frontpage = variable_get('site_frontpage');
//   }

//   $block_recenlty_read = module_invoke('views', 'block_view', 'gofast_recently_read-block');
//   $block_recenlty_read_content = $block_recenlty_read['content'];

//   if (gofast_user_has_role('administrator', $user) == 1) {
//     $is_admin = true;
//   }
//   return theme('gofast_menu_mobile_magical_menu', array('is_admin' => $is_admin));
// }



function gofast_menu_get_html_menu_from_gid()
{
  $gid = $_GET["gid"];
  if (!isset($gid)) {
    return;
  }

  $submenus = gofast_create_menu_subspaces($gid);
  $output .= theme('gofast_menu_menu_content', ['links' => $submenus, 'class' => 'gf-megamenu-col']);

  print $output;
  exit;
}
