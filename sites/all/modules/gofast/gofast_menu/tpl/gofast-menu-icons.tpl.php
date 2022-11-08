<!-- START NAVBAR MAIN MENU -->
<div class="d-flex go-navbar-main-menu">
  <!-- gofast_view-view_name-display_id -->
  <!-- gofast_menu_magical_menu function -->
  <!-- gofast_block_delta-gofast_workflows-gofast_workflows_light_dashboard -->

  <!-- GOFAST PROSSES -->
  <div class="go-navbar-menu-item dropdown" id="gofast_block_delta-gofast_workflows_light_dashboard-gofast_workflows" data-pinned="false" data-unread="<?php print $unread_workflows_count ?>">
      <span class="go-pin"><i class="fa fa-thumb-tack"></i></span>
      <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-workflow-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="fas fa-cogs"></i>
      </a>
      <span class="updated-workflow unread_count badge badge-notify-menu badge-notify">0</span>
      <div class="dropdown-menu" aria-labelledby="go-navbar-menu-workflow-item" >
          <div class="pointeur"></div>
          <div class="gofast-block-inner">
              <!-- workflow_bloc view -->
              <div style="text-align: center;">
                <div class="loader-blog"></div>
              </div>
          </div>
      </div>
  </div>


  <!-- GOFAST MESSAGES -->
  <div class="go-navbar-menu-item dropdown" block_title="Internal Private Message" id="gofast_view-gofast_private_msg-gofast_inbox" data-pinned="false" data-unread="<?php print $unread_messages_count ?>">
      <span class="go-pin"><i class="fa fa-thumb-tack"></i></span>
      <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-message-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="far fa-envelope"></i>
      </a>
      <span id="unread_pm_count" class="unread_messages unread_count badge badge-notify badge-notify-menu">0</span>
      <div class="dropdown-menu " aria-labelledby="go-navbar-menu-message-item" >
          <div class="pointeur"></div>
          <div id="gofast_pm_block" class="gofast-block-inner">
              <!-- privatemsg-privatemsg_bloc view -->
              <div style="text-align: center;">
                <div class="loader-blog"></div>
              </div>
          </div>
      </div>
  </div>

  <!-- GOFAST TACHES -->
  <div class="go-navbar-menu-item dropdown" id="gofast_view-gofast_private_msg-gofast_notifications" data-pinned="false" data-unread="<?php print $unread_notifications_count ?>">
      <span class="go-pin"><i class="fa fa-thumb-tack"></i></span>
      <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-taches-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="fa fa-flag-o fa-2x" ></i>
      </a>
      <span class="unread_notifications unread_count badge badge-notify">0</span>
      <div class="dropdown-menu " aria-labelledby="go-navbar-menu-taches-item" >
          <div class="pointeur"></div>
          <div class="gofast-block-inner">
              <!-- privatemsg-privatemsg_bloc_notifications view -->
              <div style="text-align: center;">
                <div class="loader-blog"></div>
              </div>
          </div>
      </div>
  </div>

  <!-- GOFAST RSS -->
  <div class="go-navbar-menu-item dropdown" id="gofast_view-gofast_aggregator-gofast_aggregator" data-pinned="false">
      <span class="go-pin"><i class="fa fa-thumb-tack"></i></span>
      <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-rss-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="fas fa-rss"></i>
      </a>
      <div class="dropdown-menu " aria-labelledby="go-navbar-rss-taches-item">
          <div class="pointeur"></div>
          <div class="gofast-block-inner">
              <!-- aggregator module block view (category-1) -->
              <div style="text-align: center;">
                <div class="loader-blog"></div>
              </div>
          </div>
      </div>
  </div>

  <!-- GOFAST FAVORITE -->
  <div class="go-navbar-menu-item dropdown" id="gofast_view-gofast_flag_bookmarks-gofast_flag_bookmarks" data-pinned="false">
      <span class="go-pin"><i class="fa fa-thumb-tack"></i></span>
      <a class="dropdown-toggle" href="#" role="button" id="go-navbar-menu-favorites-item" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
        <i class="far fa-star"></i>
      </a>
      <div class="dropdown-menu " aria-labelledby="go-navbar-menu-favorites-item">
        <!-- tab headers -->
        <ul class="nav nav-tabs" >
          <li id="contentFavoritesTab" class="active" onclick="Gofast.Display_ContentFolders(event);">
            <a class="bookmarksTab">
              <tab-heading translate="" ><span onclick="Gofast.Display_ContentFolders(event);"> <?php t("Favorites content", array(), array("gofast")) ?></span></tab-heading>
            </a>
          </li>
          <li id="foldersFavoritesTab" class="" onclick="Gofast.Display_FavoritesFolders(event);">
            <a class="bookmarksTab">
              <tab-heading translate=""><span onclick="Gofast.Display_FavoritesFolders(event);"><?php t("Favorites folders", array(), array("gofast")) ?></span></tab-heading>
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
</div> 

<!-- END NAVBAR MAIN MENU -->