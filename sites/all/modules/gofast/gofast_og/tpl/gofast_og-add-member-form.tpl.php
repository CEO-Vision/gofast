<?php  
/**
 * @file
 * Displays the form to edit members in space 
 *
 * Available variables:
 *   - $form: The gofast_og_space_admin_edit_members_form FORM
 *
 * @ingroup themeable
 */
?>
<div class="col-md-4">
  <strong><?php print t('Step 1', array(), array('context' => 'gofast')) ?> 
    : <?php print t('Select users', array(), array('context' => 'gofast'))?>
  </strong>
  <br /><br />
  <?php print drupal_render($form['users_filter']); ?>
  <div class="form-item">
    <label class="control-label" for="select_all">
      <input id="edit-users-all" name="users_all" value="all" class="form-checkbox" type="checkbox">
      <strong><?php print t('Select all', array(), array('context' => 'gofast'));?></strong>
    </label>
  </div>
  <div id="users_list" style="overflow-y:auto; height:400px; padding-top:5px;">
    <?php print drupal_render_children($form['users']); ?>
  </div>
</div>
<div class="col-md-4">
  <strong><?php print t('Step 2', array(), array('context' => 'gofast')) ?> 
    : <?php print t('Select spaces', array(), array('context' => 'gofast'))?>
  </strong>
  <br /><br />
  <div style="overflow-y:auto; height:400px;">
    <?php print drupal_render($form['spaces']); ?>
  </div>
</div>
<div class="col-md-4">
  <strong><?php print t('Step 3', array(), array('context' => 'gofast')) ?>
    : <?php print t('Select roles', array(), array('context' => 'gofast'))?>
  </strong>
  <?php print drupal_render_children($form); ?>
  <div>
    <span class=" fa fa-exclamation-circle"></span> <?php print t('Please note that this action might takes several minutes !', array(), array('context' => 'gofast')); ?>
  </div>
</div>

<script type="text/javascript" >
  jQuery(document).ready(function() {
    
    function filterUser(){
      var filter_value = jQuery('input.edit-users-filter').val();
      jQuery('#users_list> div').each(function(key, item){
          if( (jQuery(this).find('label').text().toLowerCase()).indexOf(filter_value.toLowerCase())  < 0 ){
            jQuery(this).hide();
          }else{
             jQuery(this).show();
          }  
      });
    }
    jQuery('input.edit-users-filter').on('change', function(){
      filterUser();
    });
    
    jQuery('input#edit-users-all').on('change', function(){
      var checked = jQuery(this).prop('checked');
      jQuery('#users_list > div > label > input').each(function(key){
         if(jQuery(this).is(':visible')){
            jQuery(this).prop('checked', checked);
        }
      });
    });
    
  });
</script>
          
