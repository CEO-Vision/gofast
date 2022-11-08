<?php
$form['group_ldap_sync']['#keen-accordion'] = TRUE;
$form['group_ldap_sync']['#collapsed'] = TRUE;
$form['group_gofast_sync']['#keen-accordion'] = TRUE;
$form['group_gofast_sync']['#collapsed'] = TRUE;
?>
<div class="card card-custom GofastForm__CardContainer">
  <div class="card-body">
    <div class="GofastForm__Field">
      <?php echo render($form['fieldset_userlist']); ?>
    </div>
    <div class="GofastForm__Field">
      <?php echo render($form['group_ldap_sync']); ?>
    </div>
    <div class="GofastForm__Field">
      <?php echo render($form['group_gofast_sync']); ?>
    </div>
  </div>
  <div class='card-footer pb-0 pt-3 d-flex w-100 GofastAddForms__buttons'>
    <?php echo render($form['actions']); ?>
  </div>
</div>

<div class="d-none">
    <?php echo drupal_render_children($form); ?>
</div>
