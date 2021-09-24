<?php
/**
 * @file
 * Displays Main Orga block for dashboard
 *
 * Available variables:
 * - $og_nid : Main Organisation (OG node) ID
 * - $og_name : Main Organisation (OG node) name
 *
 * @see template_preprocess_gofast_cdel_dashboard_main_orga()
 *
 * @ingroup themeable
 */
?>
  <div class="panel panel-dashboard panel-default dashboard dashboard-top">
    <div class="panel-heading">
      <div class="row">
        <div class="col-sm-11" style="font-weight: bold">
          <?php
            if(!empty($og_nid)){
              print $og_name;
            }
            else{
              print t('Your main space', array(), array('context' => 'gofast'));
            }
          ?>
        </div>
        <div class="col-sm-1">
          <?php $node = node_load($og_nid); ?>
          <?php //echo gofast_cdel_get_node_actions($node); ?>
        </div>
      </div>
    </div>
    <div class="panel-body">
      <?php
        if(!empty($og_nid)){
      ?>
      <ul class="list-group dashboard cdel">
        <li class="list-group-item">
          <a class="btn" href="/node/<?php echo $og_nid ?>#ogdocuments">
            <span class="fa fa-sitemap"></span>
            <span class="dashboard-block-ellipses" style="width:300px;text-align: left; vertical-align: bottom;">
              <?php  print t('Go to documents of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>
            </span>
          </a>
        </li>
        <li class="list-group-item">
          <?php if(gofast_mobile_is_mobile_domain()): ?>
            <a class="btn" href="/calendar_simplified">
          <?php else: ?>
            <a class="btn" href="/node/<?php echo $og_nid ?>#ogcalendar">
          <?php endif; ?>
            <span class="fa fa-calendar"></span>
            <span class="dashboard-block-ellipses" style="width:300px;text-align: left; vertical-align: bottom;">
              <?php  print t('Show calendar of @main_orga', array('@main_orga' => $og_name), array('context' => 'gofast_cdel'))?>
            </span>
          </a>
        </li>
      </ul>
      <?php
        }
        else{
          print t("You have no main space yet.", array(), array('context' => 'gofast'));
        }
      ?>
    </div>
  </div>


