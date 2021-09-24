<?php
/**
 * @file
 * Displays Private space block for dashboard
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_private_space()
 *
 * @ingroup themeable
 */
?>
  <div class="panel panel-dashboard panel-default dashboard-top">
    <div class="panel-heading" style="font-weight: bold"><?php print t('Private Space and Profile', array(), array('context' => 'gofast_cdel'))?></div>
    <div class="panel-body">
      <ul class="list-group dashboard cdel">
        <li class="list-group-item">
          <a class="btn gofast-non-ajax" href="/home"><span class="fa fa-home"></span><?php  print t('Go to my private space', array(), array('context' => 'gofast_cdel'))?></a>
        </li>
        <li class="list-group-item">
          <a class="btn gofast-non-ajax" href="/home?calendar=1"><span class="fa fa-calendar"></span><?php  print t('Show my calendar', array(), array('context' => 'gofast_cdel'))?></a>
        </li>
        <li class="list-group-item">
          <a class="btn" href="/user"><span class="fa fa-id-card-o"></span><?php  print t('Go to my user profile', array(), array('context' => 'gofast_cdel'))?></a>
        </li>
        <li class="list-group-item">
          <a class="btn ctools-use-modal" href="/modal/nojs/subscriptions"><span class="fa fa-flag"></span><?php  print t('Manage my subscriptions', array(), array('context' => 'gofast_cdel'))?></a>
        </li>
      </ul>
    </div>
  </div>


