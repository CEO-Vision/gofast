
<div class="w-100 px-2 <?php if($hidden_filebrowser){ print
  'd-none'; } ?>">
  <?php foreach ($menus as $name => $menu) : ?>
      <ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap <?= gofast_essential_is_essential() ? "essentialBrowserNavTabs " : ""?> <?php print $name ?>" id="gofastBrowserNavTabs" role="tablist">
        <?php foreach ($menu['links'] as $link) : ?>
          <?php if($link['dropdown']) : ?>
                <li class="nav-item dropdown">
                    <a id="<?php print $link['id'] ?>" class="nav-link px-2 d-flex justify-content-center dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
                            <span class="nav-icon">
                            <i class="<?php print $link['icon'] ?>"></i>
                            </span>
                        <span class="nav-text"><?php print $link['label']; ?></span>
                    </a>
                    <div class="dropdown-menu">
                      <?php foreach ($link['dropdown-menu'] as $dropdown_link) : ?>
                        <div <?php if($dropdown_link['hovertext']){ echo 'data-toggle="tooltip" data-theme="dark" data-trigger="hover" data-html="true" data-placement="top" data-original-title="' . $dropdown_link["hovertext"] . '"';} ?>>
                          <a class="dropdown-item<?php if($dropdown_link['hidden'] == true){ echo ' d-none'; } ?><?php if($dropdown_link['disabled'] == true){ echo ' disabled'; } ?>" data-toggle="tab" id="<?php print $dropdown_link['id']; ?>" aria-controls="<?php print $dropdown_link['href']; ?>" href="#<?php print $dropdown_link['href']; ?>">
                                    <span class="navi-icon pr-2">
                                        <i class="<?php print $dropdown_link['icon'] ?>"></i>
                                    </span>
                              <span class="navi-text"><?php print $dropdown_link['label']; ?></span>
                          </a>
                        </div>
                      <?php endforeach; ?>
                    </div>
                </li>
          <?php else : ?>
                <li class="nav-item <?php if($link['dropdown']){ echo 'dropdown'; } ?><?php if($link['disabled'] == true){ echo 'disabled'; } ?>" <?php if($link['hovertext']){ echo 'data-toggle="tooltip" data-theme="dark" data-trigger="hover" data-html="true" title="' . $link["hovertext"] . '"';} ?>>                    
                    <a class="nav-link px-2 d-flex justify-content-center <?= gofast_essential_is_essential() ? "essentialNavTab " : "" ?><?php if($link['disabled'] == true){ echo 'disabled'; } ?>" id="<?php print $link['id']; ?>" aria-controls="<?php print $link['href']; ?>" data-toggle="tab" href="#<?php print $link['href']; ?>">
                            <span class="nav-icon">
                            <i class="<?php print $link['icon'] ?>"></i>
                            </span>
                        <span class="nav-text"><?php print $link['label']; ?></span>
                    </a>
                </li>
          <?php endif; ?>
        <?php endforeach; ?>
      </ul>
  <?php endforeach; ?>
</div>
