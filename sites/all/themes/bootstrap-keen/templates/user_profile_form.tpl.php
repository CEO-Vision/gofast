<div class="GofastForm__Field">
  <?php echo render($form['group_account']); ?>
</div>
<div class="GofastForm__Field GofastForm__Field--Roles">
  <?php echo render($form['group_roles']); ?>
</div>
<div class="GofastForm__Field">
  <?php echo render($form['gofast_default_role']); ?>
</div>
<div class="GofastForm__Field">
  <?php echo render($form['group_profile_data']); ?>
</div>
<div class="GofastForm__Field">
  <?php echo render($form['wrapper_language_settings_info']['locale']); ?>
</div>
<div class="GofastForm__Field">
  <?php echo render($form['wrapper_timezone']["timezone"]); ?>
</div>
<?php if(variable_get('gofast_bluemind_is_active', 0)): ?>
  <div class="GofastForm__Field">
    <?php echo render($form['group_gofast_bluemind']); ?>
  </div>
<?php endif; ?>

<div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
  <?php echo render($form['actions']); ?>
  <div class="d-none"><?php echo drupal_render_children($form); ?></div>
</div>
