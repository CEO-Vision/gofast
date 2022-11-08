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

<div style="position: relative; z-index: 200; margin-top: 2px;">
  <div style="top: -5px; left:0; background-color: #F8F8F8; position: absolute; min-width: 500px;">
    <div class="panel panel-primary">
      <div class="panel-heading"> <?php echo t('Locations of which the userlist is a member', array(), array('context' => 'gofast_userlist')); ?></div>
      <div class="panel-body">
        <?php if(count($locations) == 0):?>
          <?php echo t('This userlist does not have any space membership', array(), array('context' => 'gofast_userlist')); ?>
        <?php else: ?>
          <?php foreach ($locations as $nid_ul => $path) : ?>
              <?php echo gofast_get_node_space_breadcrumb_async($nid_ul, NULL, TRUE, $ulid); //Get breadcrumbs for all groups ?>
          <?php endforeach; ?>
        <?php endif;?>
      </div>  
   </div>
  </div>
</div>
