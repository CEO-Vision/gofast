<div id="dropdown-menu-page" class="gofast-magical-menu">
    <i class="fa fa-2x fa-bars dropbtn"></i>
    <ul class="dropdown-menu dropdown-content" style="margin:0px !important;">
        <li>
            <a class="dropdown-item" href="/activity"><?php print t('Activity feed') ?></a>
        </li>
        <?php if ($path_exist) { ?>
            <li>
                <a class="dropdown-item" href="/dashboard"><?php print t('Dashboard') ?></a>
            </li>
        <?php } ?>
        <li>
            <a class="dropdown-item" href="/workflow/dashboard"><?php print t('Workflows dashboard', array(), array('gofast:gofast_workflows')) ?></a>
        </li>
        <li role="separator" class="divider"></li>
        <li class="dropdown-submenu" id="recenlty_read_dropdown">
            <a href="#" id="async_recently_read"><?php print t('Last recently read') ?><span class="fa fa-caret-right" aria-hidden="true" style="position:absolute; right:5px; margin-top:2px;"></span></a>
            <ul class="dropdown-menu">
                <div id="block-views-gofast-recently-read-block">
                    <h2>
                        <?php print t('Recently Read') ?>
                    </h2>
                    <div style="text-align:center;">
                        <div id="recently-read-actions-loading" class="recenlty-read-actions-loading loader-actions not-processed" style="width:50px;height:50px;display:none;"></div>
                    </div>
                </div>
            </ul>
        </li>
        <?php if ($is_admin) { ?>
            <li role="separator" class="divider"></li>
            <li class="dropdown-submenu" id="admin_options_dropdown">
                <a href="#" id="admin_options"><?php print('Administration') ?><span class="fa fa-caret-right" aria-hidden="true" style="position:absolute; right:5px; margin-top:2px;"></span></a>
                <ul class="dropdown-menu">
                    <li>
                        <a href="/admin/config/gofast/global" title=""><?php print t('GoFAST Configuration') ?> </a>
                    </li>
                    <li>
                        <a href="/admin/config/gofast/ldap/manage" title=""><?php print t('Import Users From LDAP') ?></a>
                    </li>
                    <li>
                        <a href="/gofast_audit" title=""><?php print t('Audit') ?></a>
                    </li>
                    <li>
                        <a href="/gofast_stats/dashboard" title=""><?php print t('Statistics') ?></a>
                    </li>
                </ul>
            </li>
        <?php } ?>
    </ul>
</div>
