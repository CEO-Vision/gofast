<?php

global $user;

if (gofast_user_is_business_admin($user)) {
  $is_admin = TRUE;
} else {
  $is_admin = FALSE;
}

if (count(module_implements("extra_metadata")) >= 1) {
  //Check if node have metadata
  $extra_data = '';
  foreach (module_implements("extra_metadata") as $module) {
    $metadata = call_user_func($module . "_extra_metadata", $node);
    $extra_data .= $metadata;
  }

  if(!empty($extra_data)){
    $extra_metadata = TRUE;
  } else {
    $extra_metadata = FALSE;
  }
}
?>
<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap">

  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup">
      <a class="nav-link px-2 d-flex justify-content-center dropdown-toggle active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <a class="dropdown-item" data-toggle="tab" href="#document__extra_metadata_tab">
          <?php print t('Specifics informations', [], ['context' => 'gofast']); ?>
        </a>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>


  <li class="nav-item ">
    <a class="nav-link px-2 d-flex justify-content-center" data-toggle="tab" href="#document__commentstab">
      <span class="nav-icon"><i class="fas fa-comments icon-nm"></i></span>
      <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
          <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
    </a>
  </li>
  <?php if ($is_admin) { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100" data-toggle="tab" href="#document__audittab">
        <span class="nav-icon"><i class="flaticon2-paperplane"></i></span>
        <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
    <?php } ?>
</ul>
