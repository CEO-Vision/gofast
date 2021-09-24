<?php  
/**
 * @file
 * xxxxxxxxxxxxxxxxxx
 *
 * Available variables:
 *   - $form: The xxxxxxxxxxxxxxxxxxxxxxxxxxx FORM
 *
 * @ingroup themeable
 */
?>
<div class="col-md-12">
  <?php print drupal_render_children($form, array('recipients')); ?>
</div>
<div class="col-md-12">
  <?php print drupal_render_children($form, array('list_retention')); ?>
</div>
<div class="col-md-12 gf-retention-form gf-retention-form-hidden">
  <?php print drupal_render_children($form, array('add_edit_retention')); ?>
</div>
