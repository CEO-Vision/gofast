<div id="dropdown-menu-page" class="gofast-magical-menu">
    <i class="fa fa-2x fa-bars dropbtn"></i>
    <ul class="dropdown-menu dropdown-content" style="margin:0px !important;">
        <li>
            <a class="dropdown-item" href="/home_page_navigation#navActivity"><?php print t('Home') ?></a>
        </li>
        <li role="separator" class="divider"></li>
        <li class="dropdown-submenu">
            <a class="dropdown-item" href="#"><?php print t('Create', array(), array('context' => 'gofast:gofast_retention')) ?><span class="fa fa-caret-right" aria-hidden="true" style="position:absolute; right:5px; margin-top:2px;"></span></a>
            <ul class="dropdown-menu">
                <li><a tabindex="-1" href="/node/add/conference"><?php print t('Conference'); ?></a></li>
                <li><a tabindex="-1" href="/node/add/alfresco-item"><?php print t('Content'); ?></a></li>
                <li class="dropdown-submenu">
                    <a href="#"><?php print t('Spaces'); ?><span class="fa fa-caret-right" aria-hidden="true" style="position:absolute; right:5px; margin-top:2px;"></span></a>
                    <ul class="dropdown-menu">
                        <li><a href="/node/add/group"><?php print t('Group'); ?></a></li>
                        <li><a href="/node/add/organisation"><?php print t('Organisation'); ?></a></li>
                        <li><a href="/node/add/public"><?php print t('Public'); ?></a></li>
                        <li><a href="/node/add/extranet"><?php print t('Extranet'); ?></a></li>
                    </ul>
                </li>
            </ul>
        </li>
        <li role="separator" class="divider"></li>
        <li>
            <a class="dropdown-item" href="/home_page_navigation?&path=/Sites/_<?php print $user->name ?>#navBrowser">
                <p><?php print t('Private Documents', array(), array('context' => 'gofast:gofast_mobile')) ?></p>
            </a>
        </li>
        <li>
            <a class="dropdown-item" href="/home_page_navigation?&path=/Sites#navBrowser">
                <p><?php print t('Spaces and documents', array(), array('context' => 'gofast:gofast_mobile')) ?></p>
            </a>
        </li>
        <li>
            <a class="dropdown-item" href="/conversation">
                <p><?php print t('Chat') ?></p>
            </a>
        </li>
        <li role="separator" class="divider"></li>
        <li class="dropdown-submenu">
            <a class="dropdown-item" href="#"><?php print t('Directories') ?><span class="fa fa-caret-right" aria-hidden="true" style="position:absolute; right:5px; margin-top:2px;"></span></a>
            <ul class="dropdown-menu">
                <li><a tabindex="-1" href="/og/list_grid"><?php print t('Spaces'); ?></a></li>
                <li><a tabindex="-1" href="/user_listing_tab"><?php print t('Users'); ?></a></li>
                <li><a tabindex="-1" href="/userlists"><?php print t('Userlists'); ?></a></li>

            </ul>
        </li>
        <li><a href="/tasks_page_navigation" class="dropdown-item">
                <p><?php print t('Workflows') ?></p>
            </a>
        </li>
        <li><a href="/calendar_simplified" class="dropdown-item">
                <p><?php print t('Calendar') ?></p>
            </a>
        </li>
    </ul>
</div>
