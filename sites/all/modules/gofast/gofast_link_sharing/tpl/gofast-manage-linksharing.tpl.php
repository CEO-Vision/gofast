<?php $locations_a = array(); ?>

<div class="panel panel-default manage-linksharing-panel">
  <div class="panel-body">
    <?php if(is_numeric(($uid))){ ?>
        <span id="uid" style="display:none;"><?php echo $uid; ?></span>
        <?php echo t('Send to ', array(), array('context' => 'gofast:gofast_linksharing')); ?> <strong id="title"><?php print theme('user_picture', array('account' => user_load($uid))); echo gofast_user_display_name(user_load($uid)); ?></strong> : 
    <?php }else{ ?>
        <span id="uid" style="display:none;"><?php echo $uid; ?></span>
        <?php echo t('Send to ', array(), array('context' => 'gofast:gofast_linksharing')); ?> <strong id="title"><?php echo $uid; ?></strong> : 
    <?php } ?>
    <div class="manage-linksharing-info" style="position: absolute; right: 100px; margin-top: -5px;"><i class='fa fa-clock-o' style='color:orange' aria-hidden='true'></i> <?php echo t('Pending...', array(), array('context' => 'gofast:cmis')) ?></div>
    <span id="nids" style="display:none"><?php echo json_encode($nids); ?></span>
    <span id="subject" style="display:none"><?php echo $subject ?></span>
    <span id="message" style="display:none"><?php echo $message ?></span>
    <span id="folder_sharing_title" style="display:none"><?php echo $download_page_title ?></span> 
  </div>
</div>