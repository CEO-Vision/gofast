<?php
/**
 * @file
 * Displays list of Group shortcut of a user
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_shortcut_group()
 *
 * @ingroup themeable
 */
?>
  <div class="panel panel-dashboard panel-dashboard-big panel-default">
    <div class="panel-heading">
      <div class="row">
        <div class="col-sm-11" style="font-weight: bold">
          <?php print t('My favorites spaces', array(), array('context' => 'gofast_dashboard'))?>
        </div>
        <div class="col-sm-1">
          <a href="/modal/nojs/dashboard_add_to_dashboard" class="ctools-use-modal"  data-toggle="tooltip" title="<?php echo t('Pin new Space', array(), array('context' => 'gofast_cdel')); ?>" >
            <span class="fa fa-plus"></span>
          </a>
        </div>
      </div>
    </div>
    <div id="dashboard-favorite-spaces" class="panel-body">
      <!--<div class="loader-dashboard-block"></div>-->
       <?php echo views_embed_view('gofast_flag_bookmarks', 'page_2'); ?>
    </div>
  </div>


<script>
    jQuery("document").ready(function(){
        //Load menu asyncly
        Gofast.processDashboardDropdowns();
    });
</script>
