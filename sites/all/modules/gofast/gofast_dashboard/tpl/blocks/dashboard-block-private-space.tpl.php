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

<?php
global $user;

$detect = new Mobile_Detect();
$is_mobile = gofast_mobile_is_phone();
$private_space_nid = gofast_og_get_user_private_space($user)->nid;
?>


<div class="row m-0 h-auto">
    <div class="col-6 p-4 h-50">
        <a href="<?= $is_mobile ? '/home' : '/node/'.$private_space_nid.'#ogdocuments'; ?>" class="btn shadow-xs btn-hover-primary btn-block h-100 d-flex flex-column justify-content-center align-items-center m-auto">
            <i class="fas fa-home icon-xxl mb-2"></i>
            <div><?php  print t('My personal space', array(), array('context' => 'gofast_cdel'))?></div>
        </a>
    </div>
    <div class="col-6 p-4 h-50">
        <?php if($is_mobile): ?>
            <a href="/calendar_simplified" class="btn shadow-xs btn-hover-primary btn-block h-100 d-flex flex-column justify-content-center align-items-center m-auto">
        <?php else: ?>
            <a href="/node/<?php echo $private_space_nid; ?>#ogcalendar" class="btn shadow-xs btn-hover-primary btn-block h-100 d-flex flex-column justify-content-center align-items-center m-auto">
        <?php endif; ?>
            <i class="fas fa-calendar-alt icon-xxl mb-2 text-dark"></i>
            <div><?php  print t('My calendar', array(), array('context' => 'gofast_cdel'))?></div>
        </a>
    </div>
    <div class="col-6 p-4 h-50">
        <a href="/user" class="btn shadow-xs btn-hover-primary btn-block h-100 d-flex flex-column justify-content-center align-items-center m-auto">
            <i class="fas fa-address-card icon-xxl mb-2 text-dark"></i>
            <div><?php  print t('My user profile', array(), array('context' => 'gofast_cdel'))?></div>
        </a>
    </div>
    <div class="col-6 p-4 h-50">
        <a href="/modal/nojs/subscriptions" class="ctools-use-modal btn shadow-xs btn-hover-primary btn-block h-100 d-flex flex-column justify-content-center align-items-center m-auto">
            <i class="fas fa-rss icon-xxl mb-2 text-dark"></i>
            <div><?php  print t('My subscriptions', array(), array('context' => 'gofast_cdel'))?></div>
        </a>
    </div>
</div>



