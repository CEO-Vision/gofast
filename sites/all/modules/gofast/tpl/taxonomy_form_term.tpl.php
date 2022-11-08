<div class="card card-custom GofastForm__CardContainer">
  <div class="card-body Conference__Form">
    <div class="Conference__Field GofastForm__Field GofastForm__Field--name">
      <?php echo render($form['name']); ?>
    </div>
  </div>
</div>

<div class="d-none"><?php echo drupal_render_children($form); ?></div>
