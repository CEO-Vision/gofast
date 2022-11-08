<div class="card card-custom GofastForm__CardContainer">
  <div class="card-body">
    <div class="GofastForm__Field GofastForm__Field--title">
      <?php echo render($form['wrapper']['title']); ?>
    </div>
    <?php if(!empty($form['wrapper']['language'])): ?>
      <div class="GofastForm__Field GofastForm__Field--language">
        <?php echo render($form['wrapper']['language']); ?>
      </div>
    <?php endif; ?>
    <div class="GofastForm__Field  <?php if(!empty($form['og_group_content_ref'][LANGUAGE_NONE][0]['#entity'])): ?> GofastForm__Field--content <?php else: ?>  GofastForm__Field--edit--content <?php endif; ?>" >
      <?php echo render($form['body']); ?>
    </div>
    <?php if(!empty($form['og_group_content_ref'][LANGUAGE_NONE][0]['#entity'])): ?>
      <div class="GofastForm__Field GofastForm__Field--broadcast" >
        <?php echo render($form['og_group_content_ref']); ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="card-footer pb-0 pt-3 d-flex w-100 GofastAddForms__buttons">
    <?php echo render($form['actions']); ?>
    <?php drupal_process_attached($form); ?>
    <div class="d-none"><?php echo drupal_render_children($form); ?></div>
  </div>
</div>
