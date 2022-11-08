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
<a class="btn gf-retention-new" ><span class="fa fa-plus"></span>  <?php print t('Create', array(), array('context' => 'gofast:gofast_retention')) ?></a>     

<?php $list_period = variable_get(GOFAST_RETENTION_PERIOD_MATRICE_VAR); ?>
<table class="table table-striped">
  <?php foreach( $list_period as $key => $period ): ?>
    <tr class=" gf-retention-period">
      <?php $period_category_name = i18n_taxonomy_localize_terms(taxonomy_term_load($period['tid']))->name; ?>
      <td><?php print $period_category_name; ?></td>
      <td><?php print $period['period'] ?> <?php print t($period['period_unit'], array(), array('context' => 'gofast:retention')); ?></td>
      <td><?php print t($period['action'], array(), array('context' => 'gofast:gofast_retention')); ?></td>
      <td>
        <a class="fa fa-pencil gf-edit-period" 
              data-category-uuid="<?php print $period['uuid'];?>" 
              data-category-name="<?php print $period_category_name;  ?>" >
        </a>
      </td>
      <td>
        <a class="fa fa-play gf-apply-retroactive" 
              data-category-uuid="<?php print $period['uuid'];?>" 
              data-category-name="<?php print $period_category_name;  ?>" 
              title="<?php print t("Apply retention on all documents", array(), array("context" => 'gofast:gofast_retention')) ?>" >
        </a>
      </td>
    </tr>
  <?php endforeach; ?>
</table>

<script type="text/javascript" >
  
  Gofast.applyRetention = function(cat_name, uuid){
    var matrice = Drupal.settings.gofast_retention.retention_matrice;
    var retention_period_obj = matrice[uuid];
    
    Drupal.CTools.Modal.dismiss();
    Gofast.addLoading();
    
    jQuery.post(location.origin + "/retention/apply?", {retention_obj : retention_period_obj, category: cat_name}, function(response){
        Gofast.removeLoading();
        Gofast.toast("<?php echo t('Your retention is applying on all associated documents...', array(), array("context" => "gofast:gofast_retention")) ?>", "success");
    });
  };
  
  Gofast.prefillRetentionForm = function(uuid, cat_name){
    var matrice = Drupal.settings.gofast_retention.retention_matrice;
    var retention_period_obj = matrice[uuid];
    
    jQuery('#edit-add-edit-retention-new-retention-widget input:checked').prop('checked', false);
    jQuery('#edit-add-edit-retention-new-retention-widget input[value=1]').prop('checked', true);
    
    jQuery('#edit-add-edit-retention-new-retention').val('1');
    
    jQuery('#edit-add-edit-retention-category option:selected').prop('selected', false); 
    jQuery('#edit-add-edit-retention-category [value='+retention_period_obj.tid+ ']').prop('selected', true);
    jQuery('#edit-add-edit-retention-category').prop('disabled', true);
    
    jQuery('#edit-add-edit-retention-duration').val(retention_period_obj.period);
    
    jQuery('#edit-add-edit-retention-duration-unit option:selected').prop('selected', false);
    jQuery('#edit-add-edit-retention-duration-unit [value='+retention_period_obj.period_unit+ ']').prop('selected', true);
    
    jQuery('#edit-add-edit-retention-retention-action option:selected').prop('selected', false);
    jQuery('#edit-add-edit-retention-retention-action [value='+retention_period_obj.action+ ']').prop('selected', true);
    
    jQuery('#edit-add-edit-retention-tid').val(retention_period_obj.tid);
    jQuery('#edit-add-edit-retention-uuid').val(uuid);
    
  };
  
  jQuery(document).ready(function(){
      
    jQuery('#edit-add-edit-retention-new-retention-widget input[value=1]').prop('disabled', true);

    jQuery('a.gf-retention-new').bind('click', function(){
      jQuery('.gf-retention-form').removeClass('gf-retention-form-hidden');
      
      jQuery('#edit-add-edit-retention-new-retention-widget input:checked').prop('checked', false);
      jQuery('#edit-add-edit-retention-new-retention-widget input[value=0]').prop('checked', true);
    
      jQuery('#edit-add-edit-retention-new-retention').val('0');
      
    });

    jQuery('a.gf-edit-period').bind('click', function(){  
      
      //display form
      jQuery('.gf-retention-form').removeClass('gf-retention-form-hidden');
      
      var uuid = jQuery(this).data('category-uuid');
      var name = jQuery(this).data('category-name');
      Gofast.prefillRetentionForm(uuid,name );
    });
    
    jQuery('a.gf-apply-retroactive').bind('click', function(){        
      var uuid = jQuery(this).data('category-uuid');
      var name = jQuery(this).data('category-name');
      
      //Display a confirmation modal
      var modal_html = "<?php echo t("You are going to apply this retention to all documents with the associated category. These documents won't be editable anymore as long as they have this category. Are you sure ?", array(), array('context' => 'gofast:gofast_retention')) ?>";
      modal_html += "<br /><br />";
      modal_html += "<button class='btn btn-success btn-sm icon-before' type='submit' onclick='Gofast.applyRetention(\"" + name + "\", \"" + uuid + "\")'><i class='fa fa-play'></i> <?php echo t("Apply retention", array(), array('context' => 'gofast:gofast_retention')); ?></button>";
      
     Gofast.modal(modal_html, "<?php echo t("Apply retention", array(), array('context' => 'gofast:gofast_retention')) ?>");
    });
    
    jQuery('#edit-add-edit-retention-new-retention-widget').bind('change', function(){
      
      if( jQuery(this).val() == 0){
        jQuery('#edit-add-edit-retention-new-retention').val(0);
        
        jQuery('#edit-add-edit-retention-category option:selected').prop('selected', false);
        jQuery('#edit-add-edit-retention-category').prop('disabled', false);
        
        jQuery('#edit-add-edit-retention-duration').val('');

        jQuery('#edit-add-edit-retention-duration-unit option:selected').prop('selected', false);

        jQuery('#edit-add-edit-retention-retention-action option:selected').prop('selected', false);

        jQuery('#edit-add-edit-retention-tid').val('');
        jQuery('#edit-add-edit-retention-uuid').val('');
     }else{
       jQuery('#edit-add-edit-retention-new-retention').val(1);
     }   
   });
    
 });
</script>
  


