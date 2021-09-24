<?php
/**
 * @file
 * Displays Dashboard Page
 *
 * Available variables:
 *
 * @see template_preprocess_gofast_cdel_dashboard_main()
 *
 * @ingroup themeable
 */
?>
<style>
  #gofast_over_content.col-sm-9{
    width: 100% !important;
  }
</style>
<div class="content well well-sm Dashboard">
  <div class="row dashboard">
    <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_private_space">
      <?php echo theme('gofast_dashboard_dashboard_private_space'); ?>
    </div>
    <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_main_orga">
      <?php echo theme('gofast_dashboard_dashboard_main_orga'); ?>
    </div>
    <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_private_space">
      <?php echo theme('gofast_dashboard_dashboard_memo'); ?>
    </div>
    <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_shortcut_group">
      <?php echo theme('gofast_dashboard_dashboard_shortcut_group'); ?>
    </div>
    <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_shortcut_group">
      <?php echo theme('gofast_dashboard_dashboard_favorites_folders'); ?>
    </div> 
      <div class="col-xs-12 col-sm-6 col-lg-4 dashboard_shortcut_group">
      <?php echo theme('gofast_dashboard_dashboard_favorites_contents'); ?>
    </div>
    <div class="col-md-12" style="display: none;">
      <div class="row">
        <div class="col-md-4 dashboard_private_space">
          <?php //echo theme('gofast_dashboard_dashboard_private_space'); ?>
        </div>
        <div class="col-md-4 dashboard_main_orga">
          <?php //echo theme('gofast_dashboard_dashboard_main_orga'); ?>
        </div>
        <div class="col-md-4 dashboard_private_space">
        <?php //echo theme('gofast_dashboard_dashboard_memo'); ?>
        </div>
      </div>
      <div class="row">
        <div class="col-md-4 dashboard_shortcut_group">
          <?php //echo theme('gofast_dashboard_dashboard_shortcut_group'); ?>
        </div>
        <div class="col-md-4 dashboard_shortcut_group">
          <?php //echo theme('gofast_dashboard_dashboard_favorites_folders'); ?>
        </div> 
         <div class="col-md-4 dashboard_shortcut_group">
          <?php //echo theme('gofast_dashboard_dashboard_favorites_contents'); ?>
        </div>
      </div>
    </div>   
  </div>
</div>

<script type='text/javascript'>
  jQuery(document).ready(function(){
    if (jQuery("#dashboard-block-last-commented").length > 0){
      jQuery.post(location.origin+"/dashboard/ajax/last_commented", function(data){
        jQuery("#dashboard-block-last-commented").replaceWith(data);
      });
    }

    if (jQuery("#dashboard-block-mail").length > 0){
      jQuery.post(location.origin+"/dashboard/ajax/mail", function(data){
        jQuery("#dashboard-block-mail").replaceWith(data);
      });
    }
  });
</script>