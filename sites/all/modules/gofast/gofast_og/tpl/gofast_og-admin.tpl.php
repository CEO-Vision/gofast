<?php
/**
 * @file
 * Display the page for managing members in spaces
 *
 * Available variables:
 * - $js : is form in ajax (TRUE or FALSE);
 * - $action : 'add' or 'edit'
 *
 * @ingroup themeable
 */
?>
<div id="fullscreen-node">
  <div id="gofast-og-admin" class="gofast-og-page <?php print $classes; ?> clearfix"<?php print $attributes; ?>>
    <div class="content">
      <div>
        <ul class="nav nav-tabs nav-justified" role="tablist">
          <li id="gofast_og_admin_add" role="presentation" class="active">
              <a href="#space-members-add" aria-controls="space-members-add" role="tab" data-toggle="tab">
                <?php print t("Add members", array(), array('context' => 'gofast')); ?></a></li>
          <li id="gofast_og_admin_edit" role="presentation" >
            <a href="#space-members-edit" aria-controls="space-members-edit" role="tab" data-toggle="tab">
              <?php print t("Update members", array(), array('context' => 'gofast'));  ?></a></li>
        </ul>

        <div class="tab-content content well well-sm">
          <div role="tabpanel" class="tab-pane active" id="space-members-add">
            <div class="container-fluid">
              <div class="row">
                <h5><?php print t('Description', array(), array('context' => 'gofast'))?></h5>
                <span>
                  <?php
                    print t('Add multiple users to spaces with a specific  role',
                      array(), array('context' => 'gofast:gofast_og'));
                  ?>
                </span>
              </div>
              <br />
              <div id="gofast-og-admin-add-member-form" class="row">
                <?php
                  $form_add = drupal_get_form('gofast_og_space_admin_add_members_form', $js );
                  print drupal_render($form_add);
                 ?>
              </div>
            </div>
          </div>
          
          <div role="tabpanel" class="tab-pane" id="space-members-edit">
            <div class="container-fluid">
              <div class="row">
                <h4><?php print t('Description', array(), array('context' => 'gofast'))?></h4>
                <?php
                print t('Add multiple users to spaces with a specific role',
                        array(), array('context' => 'gofast'));
                ?>
              </div>
              <br />
              <div id="gofast-og-admin-edit-member-form" class="row">
                <?php
                  $form_mod = drupal_get_form('gofast_og_space_admin_edit_members_form', $js);
                  print  drupal_render($form_mod);
                 ?>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
</div>
<script type="text/javascript">
  jQuery(document).ready(function() {
    var action = '<?php print $action; ?>';
    
  if( action === 'add'){
      jQuery('li#gofast_og_admin_add').find('a').click();
    }else{
      jQuery('li#gofast_og_admin_edit').find('a').click();
    }
  });
  
</script>