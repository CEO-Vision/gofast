<?php
  global $user;
  $private_space_nid = gofast_og_get_user_private_space($user)->nid;
  $browser_path = gofast_mobile_is_mobile_domain() ? '/home_page_navigation?&path=/Sites#navBrowser' : "/node/$private_space_nid#ogdocuments";
?>
<a href="/modal/nojs/dashboard_add_folder_to_dashboard" class="ctools-use-modal btn btn-icon btn-link-primary btn-xs ml-2" data-toggle="tooltip" data-html="true" title="<?php echo t('Pin new folder', array(), array('context' => 'gofast_cdel')); ?>">
  <span class="fas fa-plus"></span>
</a>
<a href="<?php echo $browser_path; ?>" class="btn btn-icon btn-link-primary btn-xs ml-2" data-toggle="tooltip" data-html="true" title="<?php echo t('Go to the file browser', array(), array('context' => 'gofast_cd74')); ?>">
  <span class="fas fa-folder-open"></span>
</a>
