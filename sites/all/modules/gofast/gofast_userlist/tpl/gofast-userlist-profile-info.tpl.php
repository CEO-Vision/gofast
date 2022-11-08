<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> " <?php print $attributes; ?>>
  <div class="card card-custom card-stretch GofastNodeOg__container p-3" <?php print $content_attributes; ?>>
    <div class="card-body pb-2 pt-0 px-1 d-flex flex-column">
      <div class="w-100 px-2">
        <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap" id="gofastBrowserNavTabs" role="tablist">
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
                    <a class="nav-link px-2 d-flex justify-content-center <?php if($link['disabled'] == true){ echo 'disabled'; } ?> <?php if($key == "locations"){ echo 'active show';} ?>" id="<?php print $link['id']; ?>" aria-controls="<?php print $link['href']; ?>" data-toggle="tab"  href="#<?php print $link['href']; ?>">
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
      <div class="h-100 w-100 overflow-hidden" >
        <div class="tab-content h-100 w-100" id="gofastBrowserContentPanel">
          <?php foreach ($links as $key => $link) : ?>
            <?php if($link['dropdown']) : ?>
                <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                    <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden" id="<?php print $dropdown_link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $dropdown_link['id']; ?>">
                        <?php print $dropdown_link['content']; ?>
                    </div>
                <?php endforeach; ?>
            <?php else : ?>
                <div class="tab-pane px-2 pt-4 fade h-100 w-100 overflow-hidden <?php if($key == "locations"){ echo 'active show';} ?>" id="<?php print $link['href']; ?>" role="tabpanel" aria-labelledby="<?php print $link['id']; ?>">
                    <?php print $link['content']; ?>
                </div>
            <?php endif; ?>
          <?php endforeach; ?>
        </div>
      </div>
    </div>
  </div>
</div>
