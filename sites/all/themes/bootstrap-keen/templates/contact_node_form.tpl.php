<div class="card card-custom GofastForm__CardContainer">
    <div class="card-body">
        <div class="GofastForm__Field GofastForm__Field--contact-name">
          <?php echo render($form['field_contact_name']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--contact-firstname">
          <?php echo render($form['field_contact_firstname']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--contact-email" >
          <?php echo render($form['field_contact_email']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--contact-phone" >
          <?php echo render($form['field_contact_phone']); ?>
        </div>
        <div class="GofastForm__Field GofastForm__Field--contact-entity" >
        <?php echo render($form['field_contact_entity']); ?>
        </div>
    </div>
    <div class='card-footer pb-0 pt-3 d-flex GofastAddForms__buttons'>
      <?php echo render($form['actions']); ?>
    </div>
</div>
<div class="d-none"><?php echo drupal_render_children($form); ?></div>
