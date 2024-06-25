<?php

global $user;

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
<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap GofastNode__header--small">

  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup">
      <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_info_tab active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <?php foreach($extra_datas as $extra_data) : ?>
          <a class="dropdown-item" data-toggle="tab" href="#<?php print $extra_data['id']; ?>">
            <?php print $extra_data['title']; ?>
          </a>
        <?php endforeach; ?>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100 active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>

  <li class="nav-item dropdown">
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
    </a>
    <div class="dropdown-menu">
      <a class="dropdown-item" data-toggle="tab" href="#document__commentstab">
        <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
        <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__historytab">
        <span class="nav-text"><?php print t('Versions', [], ['context' => 'gofast']); ?></span>
      </a>
      <?php if (gofast_audit_access("node", $node->nid)) { ?>
        <a class="dropdown-item" data-toggle="tab" href="#document__audittab">
          <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
        </a>
      <?php } ?>
    </div>
  </li>
</ul>
<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap GofastNode__header--medium">

  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup">
      <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_info_tab active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <?php foreach($extra_datas as $extra_data) : ?>
          <a class="dropdown-item" data-toggle="tab" href="#<?php print $extra_data['id']; ?>">
            <?php print $extra_data['title']; ?>
          </a>
        <?php endforeach; ?>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100 active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>

 <li class="nav-item dropdown">
  <li class="nav-item dropdown">
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
      <span class="nav-text"><?php print t('More', [], ['context' => 'gofast']); ?>
      </span>
    </a>
    <div class="dropdown-menu">
      <a class="dropdown-item" data-toggle="tab" href="#document__commentstab">
        <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>      
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__historytab">
        <span class="nav-text"><?php print t('Versions', [], ['context' => 'gofast']); ?></span>
      </a>
      <?php if (gofast_audit_access("node", $node->nid)) { ?>
        <a class="dropdown-item" data-toggle="tab" href="#document__audittab">
          <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
        </a>
      <?php } ?>
    </div>
  </li>
</ul>
<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap GofastNode__header--large">

  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup">
      <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_info_tab active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Info.', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <?php foreach($extra_datas as $extra_data) : ?>
          <a class="dropdown-item" data-toggle="tab" href="#<?php print $extra_data['id']; ?>">
            <?php print $extra_data['title']; ?>
          </a>
        <?php endforeach; ?>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100 active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Info.', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>

 <li class="nav-item dropdown">
     <li class="nav-item ">
    <a class="nav-link px-2 d-flex justify-content-center h-100 <?php echo ($node_type == 'forum') ? 'disabled' : ''; ?>" data-toggle="tab" href="#document__commentstab">
      <span class="nav-icon"><i class="fas fa-comments icon-nm"></i></span>
      <span class="nav-text"><?php print t('Comment.', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
          <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
    </a>
  </li>
  <?php if (!gofast_audit_access("node", $node->nid)) : ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100" data-toggle="tab" href="#document__historytab">
        <span class="nav-icon"><i class="fas fa-history icon-nm"></i></span>
        <span class="nav-text"><?php print t('Vers.', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php else : ?>
  <li class="nav-item dropdown">
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
      <span class="nav-text"><?php print t('More', [], ['context' => 'gofast']); ?></span>
    </a>
    <div class="dropdown-menu">
      <a class="dropdown-item" data-toggle="tab" href="#document__historytab">
        <span class="nav-text"><?php print t('Versions', [], ['context' => 'gofast']); ?></span>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__audittab">
        <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
      </a>
    </div>
  </li>
  <?php endif;?>
</ul>
<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap GofastNode__header--xlarge">


  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup" style="margin-right:0;">
      <a class="nav-link px-2 d-flex  h-100 dropdown-toggle header_info_tab active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <?php foreach($extra_datas as $extra_data) : ?>
          <a class="dropdown-item" data-toggle="tab" href="#<?php print $extra_data['id']; ?>">
            <?php print $extra_data['title']; ?>
          </a>
        <?php endforeach; ?>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item" style="margin-right:0;">
      <a class="nav-link px-2 d-flex justify-content-center h-100 active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>

  <li class="nav-item ">
    <a class="nav-link px-2 d-flex justify-content-center h-100 <?php echo ($node_type == 'forum') ? 'disabled' : ''; ?>" data-toggle="tab" href="#document__commentstab">
      <span class="nav-icon"><i class="fas fa-comments icon-nm"></i></span>
      <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
          <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
    </a>
  </li>
  <?php if (!gofast_audit_access("node", $node->nid)) : ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100" data-toggle="tab" href="#document__historytab">
        <span class="nav-icon"><i class="fas fa-history icon-nm"></i></span>
        <span class="nav-text"><?php print t('Versions.', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php else : ?>
  <li class="nav-item dropdown">
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
      <span class="nav-text"><?php print t('More', [], ['context' => 'gofast']); ?></span>
    </a>
    <div class="dropdown-menu">
      <a class="dropdown-item" data-toggle="tab" href="#document__historytab">
        <span class="nav-text"><?php print t('Versions', [], ['context' => 'gofast']); ?></span>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__audittab">
        <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
      </a>
    </div>
  </li>
  <?php endif;?>
</ul>

<ul class="nav nav-tabs nav-fill gofastTab w-100 mb-0 justify-content-end flex-nowrap GofastNode__header--xxlarge">


  <?php if ($extra_metadata) { ?>
    <li class="nav-item dropdown dropup" style="margin-right:0;">
      <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_info_tab active" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
      <div class="dropdown-menu">
        <a class="dropdown-item" data-toggle="tab" href="#document__infotab">
          <?php print t('Informations', [], ['context' => 'gofast']); ?>
        </a>
        <?php foreach($extra_datas as $extra_data) : ?>
          <a class="dropdown-item" data-toggle="tab" href="#<?php print $extra_data['id']; ?>">
            <?php print $extra_data['title']; ?>
          </a>
        <?php endforeach; ?>
      </div>
    </li>
  <?php } else { ?>
    <li class="nav-item" style="margin-right:0;">
      <a class="nav-link px-2 d-flex justify-content-center h-100 active" data-toggle="tab" href="#document__infotab">
        <span class="nav-icon"><i class="fas fa-info-circle icon-nm"></i></span>
        <span class="nav-text"><?php print t('Informations', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>

  <li class="nav-item ">
    <a class="nav-link px-2 d-flex justify-content-center h-100 <?php echo ($node_type == 'forum') ? 'disabled' : ''; ?>" data-toggle="tab" href="#document__commentstab">
      <span class="nav-icon"><i class="fas fa-comments icon-nm"></i></span>
      <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
          <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
    </a>
  </li>
  <li class="nav-item ">
    <a class="nav-link px-2 d-flex justify-content-center h-100" data-toggle="tab" href="#document__historytab">
      <span class="nav-icon"><i class="fas fa-history icon-nm"></i></span>
      <span class="nav-text"><?php print t('Versions', [], ['context' => 'gofast']); ?></span>
    </a>
  </li>
  <?php if (gofast_audit_access("node", $node->nid)) { ?>
    <li class="nav-item ">
      <a class="nav-link px-2 d-flex justify-content-center h-100" data-toggle="tab" href="#document__audittab">
        <span class="nav-icon"><i class="flaticon2-paperplane"></i></span>
        <span class="nav-text"><?php print t('Audit', [], ['context' => 'gofast']); ?></span>
      </a>
    </li>
  <?php } ?>
</ul>
<script>
  jQuery(document).ready(function() {
    <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
      Gofast.removeCommentsBadge();
    <?php } ?>
    // ensure the hash is always updated
    jQuery("#node-tabsHeader .nav-link").on("click", ({target}) => {
      const targetHref = target.getAttribute("href");
      if (!targetHref || !targetHref.startsWith("#") || !targetHref.length > 1 || targetHref == "#") {
        return;
      }
      window.history.pushState({}, "", location.pathname + location.search + target.getAttribute("href"));
    });
    // if there already is a hash navigation, we don't want to override it but to enforce it
    if (window.location.hash.length && !Gofast._settings.isEssential) {
      jQuery("[href='" + window.location.hash + "']:not(.active):visible").click();
      return;
    }
  });
</script>
