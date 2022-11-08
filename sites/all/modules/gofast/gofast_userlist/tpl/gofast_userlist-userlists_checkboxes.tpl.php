
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

<?php //print_r(json_encode($checkboxes)); ?>
<div  class="container-fluid">

  <div id="edit-userlists" class="form-checkboxes">

    <?php foreach ($checkboxes['#options'] as $key => $checkbox): ?>
      <div class="row">
        <div class="form-item form-item-userlists-<?php echo $key ?> form-type-checkbox checkbox col-md-4">
          <label id ="userlists_ulid-<?php echo $key ?>"  class="control-label" for="edit-userlists-<?php echo $key ?>"  >
            <input type="checkbox" id="edit-userlists-<?php echo $key ?>" name="userlists[<?php echo $key ?>]" value="<?php echo $key ?>" class="form-checkbox"> 
            <i class="fa fa-users userlist"></i>&nbsp;<?php echo $checkbox ?> 

          </label>
          &nbsp;

        </div>
        <div class="col-md-4">
          <!--<div class="glyphicon glyphicon-search" data-ulid="<?php echo $key; ?>" onmouseover="Gofast.userlist.showPopup(this)" onmouseout="Gofast.userlist.hidePopup(this)"></div>-->
          <div class="userlist-location-popup" data-ulid="<?php echo $key; ?>"  onmouseout="Gofast.userlist.hidePopup(this)">
            <div class="glyphicon glyphicon-search" onmouseover="Gofast.userlist.showPopup($(this).parent())"></div>
            <div class="details" style="position: relative; z-index: 100; margin-top: 2px; /*display:none;*/" ></div>
          </div>
        </div>
      </div>
    <?php endforeach; ?>

  </div>
</div>

