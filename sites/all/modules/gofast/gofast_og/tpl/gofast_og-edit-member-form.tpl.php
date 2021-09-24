<?php  /**
 * @file
 * Displays the form to add members in space 
 *
 * Available variables:
 *   - $form: The gofast_og_space_admin_add_members_form FORM
 *
 * @ingroup themeable
 */ 
?>
<div class="col-md-6">
  <strong><?php print t('Step 1', array(), array('context' => 'gofast')) ?> 
    : <?php print t('Select users', array(), array('context' => 'gofast'))?>
  </strong>
  <br /><br />
  <div style="overflow-y:auto; height:400px;">
    <?php print drupal_render($form['spaces']); ?>
  </div>
</div>
<div class="col-md-6">
  <strong><?php print t('Step 2', array(), array('context' => 'gofast')) ?> 
    : <?php print t('Action on user(s)', array(), array('context' => 'gofast'))?>
  </strong>
  <br/><br/>
  <span class=" fa fa-exclamation-circle"></span> <?php print t('Please note that those actions might take several minutes !', array(), array('context' => 'gofast')); ?>
  <br/><br/>
  <div class="panel panel-default">
    <div class="panel-heading">
      <?php print t('Change user(s)\' role', array(), array('context' => 'gofast')) ?>
    </div>
    <div class="panel-body">
      <?php print drupal_render($form['role']); ?>
      <?php print drupal_render($form['submit']); ?>
    </div>
  </div>
  <strong><?php print t('OR', array(), array('context' => 'gofast')); ?></strong>
  <br/>  <br />
  <div class="panel panel-default">
    <div class="panel-heading">
      <?php print t('Remove selected user from spaces', array(), array('context' => 'gofast:gofast_og')) ?>
    </div>
    <div class="panel-body">
      <?php print drupal_render_children($form); ?>
    </div>
  </div>
</div>
