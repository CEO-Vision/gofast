        <li class="menu-item menu-item-submenu menu-item-rel" id="gofast-flag-lang-switch" data-menu-toggle="hover" aria-haspopup="true">
          <a class="btn btn-icon btn-clean btn-dropdown btn-lg ">
            <span class="symbol symbol-light-info symbol-30">
              <div class="symbol-label font-size-h5">
                <?= strtoupper(is_array($selected_language) ? $selected_language['lcode'] : $selected_language) ?>
              </div>
            </span>
          </a>
          <div class="menu-submenu menu-submenu-classic menu-submenu-right max-w-200px" data-hor-direction="menu-submenu-right">
            <ul class="menu-subnav navi">
              <?php foreach ($languages as $language) : ?>
                <li class="navi-item">
                    <a href="<?php print gofast_xss_clean($language['href']); ?>" class="navi-link" onclick="Gofast.addLoading();">
                    <span class="symbol symbol-light-dark symbol-30 mr-3">
                      <div class="symbol-label font-size-h5">
                        <?= strtoupper($language['lcode']) ?>
                      </div>
                    </span>
                    <span class="navi-text"><?php print t($language['name']) ?></span>
                  </a>
                </li>
              <?php endforeach; ?>
            </ul>
          </div>
        </li>
