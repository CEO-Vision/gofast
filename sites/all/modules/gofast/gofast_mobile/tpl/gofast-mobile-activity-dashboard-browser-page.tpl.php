<?php include_once 'MobileDetect.php'; ?>

<div id="gofast-mobile-home" class="mainContent GofastMobileHome p-3 h-100 <?php print $classes; ?> " <?php print $attributes; ?>>
  <div class="card card-custom card-stretch GofastMobileHome__container" <?php print $content_attributes; ?>>
    <div class="card-body d-flex p-0 flex-column">
      <div class="w-100 px-2">
        <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap navigation_simplified align-items-center" id="gofastMobileHomeNavTabs" role="tablist">
          <?php foreach ($links as $key => $link) : ?>
            <?php if($link['dropdown']) : ?>
                <li class="nav-item dropdown">
                    <a class="nav-link px-2 d-flex justify-content-center dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
                        <span class="nav-icon">
                        <i class="<?php print $link['icon'] ?>"></i>
                        </span>
                        <span class="nav-text"><?php print $link['label']; ?></span>
                    </a>
                    <div class="dropdown-menu">
                        <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                            <a class="dropdown-item" data-toggle="tab" id="<?php print $dropdown_link['id']; ?>" aria-controls="<?php print $dropdown_link['href']; ?>" href="#<?php print $dropdown_link['href']; ?>">
                                <span class="navi-icon pr-2">
                                    <i class="<?php print $dropdown_link['icon'] ?>"></i>
                                </span>
                                <span class="navi-text"><?php print $dropdown_link['label']; ?></span>
                            </a>
                        <?php endforeach; ?>
                    </div>
                </li>
            <?php else : ?>
                <li class="nav-item <?php if($link['dropdown']){ echo 'dropdown'; } ?><?php if($link['disabled'] == true){ echo 'disabled'; } ?>">
                    <a class="nav-link px-2 d-flex justify-content-center <?php if($link['disabled'] == true){ echo 'disabled'; } ?>" id="<?php print $link['id']; ?>" aria-controls="<?php print $link['href']; ?>" data-toggle="tab" href="#<?php print $link['href']; ?>">
                        <span class="nav-icon">
                        <i class="<?php print $link['icon'] ?>"></i>
                        </span>
                        <span class="nav-text"><?php print $link['label']; ?></span>
                    </a>
                </li>
            <?php endif; ?>
          <?php endforeach; ?>
        </ul>
      </div>
      <div class="h-100 w-100 overflow-scroll" >
        <div class="tab-content h-100 w-100" id="gofastMobileHomeContentPanel">
          <?php foreach ($links as $key => $link) : ?>
            <?php if($link['dropdown']) : ?>
                <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                    <div class="tab-pane px-0 pt-0 fade h-100 w-100" id="<?php print $dropdown_link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $dropdown_link['id']; ?>">
                        <?php print $dropdown_link['content']; ?>
                    </div>
                <?php endforeach; ?>
            <?php else : ?>
                <div class="tab-pane px-0 pt-0 fade h-100 w-100" id="<?php print $link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $link['id']; ?>">
                    <?php print $link['content']; ?>
                </div>
            <?php endif; ?>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </div>
</div>
<script>
  // toggle nav based on hash to avoid having zero active tab after aside menu navigation
  jQuery(document).ready(function() {
    if (location.hash.length && $("[href='" + location.hash + "']").length) {
      $("[href='" + location.hash + "']").click();
    }
  });
</script>