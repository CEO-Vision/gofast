<?php

global $user;

if (gofast_user_is_business_admin($user)) {
  $is_admin = TRUE;
} else {
  $is_admin = FALSE;
}

if (count(module_implements("extra_metadata")) >= 1) {
  //Check if node have metadata
  $extra_datas = array();
  foreach (module_implements("extra_metadata") as $module) {
    $metadata = call_user_func($module . "_extra_metadata", $node);
    if(!empty($metadata)){
      $extra_datas[] = $metadata;
    }
  }

  if(!empty($extra_datas)){
    $extra_metadata = TRUE;
  } else {
    $extra_metadata = FALSE;
  }
}

 $context['workflows_document'] = null;
 gofast_set_context($context);
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
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle dropdown-toggle-more" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
      <span class="nav-text"><?php print t('More', [], ['context' => 'gofast']); ?>
          <?php
            if ( (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0)
               || (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0)
            ) {
            $count_total_notif = ($count_notif['count_comment_notif'] ?? 0) + ($count_notif['count_wf_my_notif'] ?? 0);
          ?>
            <span class="label label-light-danger mr-2"><?= $count_total_notif ?></span>
          <?php } ?>
      </span>
    </a>
    <div class="dropdown-menu">
    <a class="dropdown-item" data-toggle="tab" href="#document__commentstab">
        <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0) { ?>
        <span id="gofast-comment-notifiation" class="label label-danger ml-2"><?php echo $count_notif['count_comment_notif'] ?></span>
        <?php } ?>
    </a>
    <a class="dropdown-item" data-toggle="tab" href="#document__tasktab" id="lightDashboardDocumentMyParentTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab">
        <span class="nav-text"><?php print t('My tasks', [], ['context' => 'gofast:gofast_workflows']); ?></span>
        <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__tasktab" id="lightDashboardDocumentOtherParentTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab">
        <span class="nav-text"><?php print t('Other tasks', [], ['context' => 'gofast:gofast_workflows']); ?></span>
        <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__tasktab" id="lightDashboardDocumentHistoryParentTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab">
        <span class="nav-text"><?php print t('Processes history', [], ['context' => 'gofast:gofast_workflows']); ?></span>
        <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
      </a>
      <a class="dropdown-item" data-toggle="tab" href="#document__tasktab" id="lightDashboardDocumentNewParentTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab">
        <span class="nav-text"><?php print t('New process', [], ['context' => 'gofast:gofast_workflows']); ?></span>
        <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
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
     <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_tasks_tab" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon">
          <i class="fas fa-cogs"></i>
        </span>
        <span class="nav-text"><?php print t('Tasks', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0) : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation"><?= $count_notif['count_wf_my_notif'] ?></span>
        <?php else : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
        <?php endif; ?>>
     </a>
     <div class="dropdown-menu">
         <a class="dropdown-item" id="lightDashboardDocumentMyParentTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("My tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentOtherParentTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("Other tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentHistoryParentTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-history"></i>
             </span>
             <span class="nav-text"><?php echo t("History", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentNewParentTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-play"></i>
             </span>
             <span class="nav-text"><?php echo t("New", array(), array("context" => "gofast")) ?></span>
         </a>
     </div>
  <li class="nav-item dropdown">
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle dropdown-toggle-more" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
      <span class="nav-text"><?php print t('More', [], ['context' => 'gofast']); ?>
      <?php
        if ( (isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0)
            || (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0)
        ) {
        $count_total_notif = ($count_notif['count_comment_notif'] ?? 0) + ($count_notif['count_wf_my_notif'] ?? 0);
      ?>
        <span class="label label-light-danger mr-2"><?= $count_total_notif ?></span>
      <?php } ?>
      </span>
    </a>
    <div class="dropdown-menu">
      <a class="dropdown-item" data-toggle="tab" href="#document__commentstab">
        <span class="nav-text"><?php print t('Comments', [], ['context' => 'gofast']); ?></span>
        <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
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
     <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_tasks_tab" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon">
          <i class="fas fa-cogs"></i>
        </span>
        <span class="nav-text"><?php print t('Tasks', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0) : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation"><?= $count_notif['count_wf_my_notif'] ?></span>
        <?php else : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
        <?php endif; ?>
     </a>
     <div class="dropdown-menu">
         <a class="dropdown-item" id="lightDashboardDocumentMyParentTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("My tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentOtherParentTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("Other tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentHistoryParentTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-history"></i>
             </span>
             <span class="nav-text"><?php echo t("History", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentNewParentTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-play"></i>
             </span>
             <span class="nav-text"><?php echo t("New", array(), array("context" => "gofast")) ?></span>
         </a>
     </div>
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
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle dropdown-toggle-more" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
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

  <li class="nav-item dropdown">
     <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_tasks_tab" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon">
          <i class="fas fa-cogs"></i>
        </span>
        <span class="nav-text"><?php print t('Tasks', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0) : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation"><?= $count_notif['count_wf_my_notif'] ?></span>
        <?php else : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
        <?php endif; ?>
     </a>
     <div class="dropdown-menu">
         <a class="dropdown-item" id="lightDashboardDocumentMyParentTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("My tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentOtherParentTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("Other tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentHistoryParentTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-history"></i>
             </span>
             <span class="nav-text"><?php echo t("History", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentNewParentTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-play"></i>
             </span>
             <span class="nav-text"><?php echo t("New", array(), array("context" => "gofast")) ?></span>
         </a>
     </div>
 </li>
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
    <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle dropdown-toggle-more" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
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

  <li class="nav-item dropdown">
     <a class="nav-link px-2 d-flex justify-content-center h-100 dropdown-toggle header_tasks_tab" data-toggle="dropdown" href="#" role="button" aria-haspopup="true" aria-expanded="false">
        <span class="nav-icon">
          <i class="fas fa-cogs"></i>
        </span>
        <span class="nav-text"><?php print t('Tasks', [], ['context' => 'gofast']); ?></span>
        <?php if (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0) : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation"><?= $count_notif['count_wf_my_notif'] ?></span>
        <?php else : ?>
          <span id="gofast-task-notifiation" class="label label-danger ml-2 gofast-task-notifiation d-none"></span>
        <?php endif; ?>
     </a>
     <div class="dropdown-menu">
         <a class="dropdown-item" id="lightDashboardDocumentMyParentTab" aria-controls="lightDashboardDocumentMy" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("My tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentOtherParentTab" aria-controls="lightDashboardDocumentOther" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-flag"></i>
             </span>
             <span class="nav-text"><?php echo t("Other tasks", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentHistoryParentTab" aria-controls="lightDashboardDocumentHistory" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-history"></i>
             </span>
             <span class="nav-text"><?php echo t("History", array(), array("context" => "gofast:gofast_workflows")) ?></span>
         </a>
         <a class="dropdown-item" id="lightDashboardDocumentNewParentTab" aria-controls="lightDashboardDocumentNew" data-toggle="tab" href="#document__tasktab">
             <span class="nav-icon pr-2">
                 <i class="fas fa-play"></i>
             </span>
             <span class="nav-text"><?php echo t("New", array(), array("context" => "gofast")) ?></span>
         </a>
     </div>
 </li>
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
    <?php if ((isset($count_notif['count_comment_notif']) && $count_notif['count_comment_notif'] > 0)
      || (isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0)) { ?>
      Gofast.removeCommentsBadge();
    <?php } ?>
    <?php if ((isset($count_notif['count_wf_my_notif']) && $count_notif['count_wf_my_notif'] > 0)) : ?>
      setTimeout(function () {
        jQuery(".gofastTab:visible > li:nth-of-type(2) > a").click();
        jQuery(".gofastTab:visible > li:nth-of-type(2) .dropdown-item:first-of-type").click();
      }, 1000);
    <?php endif; ?>
    // ensure the hash is always updated
    jQuery("#node-tabsHeader .nav-link").on("click", ({target}) => {
      const targetHref = target.getAttribute("href");
      if (!targetHref || !targetHref.startsWith("#") || !targetHref.length > 1 || targetHref == "#") {
        return;
      }
      window.history.pushState({}, "", location.pathname + location.search + target.getAttribute("href"));
    });
    // if there already is a hash navigation, we don't want to override it but to enforce it
    if (window.location.hash.length) {
      jQuery("[href='" + window.location.hash + "']:not(.active):visible").click();
      return;
    }
  });
</script>
