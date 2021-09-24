<?php
/**
 * @file
 * Displays Breadcrumb for dashboard page
 *
 * @see template_preprocess_gofast_block_user_mails()
 *
 * @ingroup themeable gofast_dashboard_breadcrumb() if defined
 */
?>
<?php if(gofast_mobile_is_mobile_domain() != TRUE){ ?>
  <?php if($activity){ ?>
  <div class="breadcrumb gofast breadcrumb-gofast">
    <a href="/dashboard">
      <span class="fa fa-th"></span><?php echo ' '.t('Dashboard', array(), array('context' => 'gofast_cdel')); ?>
    </a>
  </div>

  <div class="breadcrumb-alt">
      <span class="fa fa-bars"> </span><?php echo ' '.t('Activity Feed', array(), array('context' => 'gofast')); ?>
  </div>
  <?php }else{ ?>
  <div class="breadcrumb gofast breadcrumb-gofast">
      <span class="fa fa-th"></span><?php echo ' '.t('Dashboard', array(), array('context' => 'gofast_cdel')); ?>
  </div>

  <div class="breadcrumb-alt">
    <a href="/activity">
      <span class="fa fa-bars"> </span><?php echo ' '.t('Activity Feed', array(), array('context' => 'gofast')); ?>
    </a>
  </div>
  <?php } ?>
<?php } ?>
