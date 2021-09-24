
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


<script type="text/javascript" >
  (function ($, Gofast, Drupal) {
    'use strict';

    Gofast.userlist = Gofast.userlist || {};

    Gofast.userlist.showPopup = function (elt) {
      Gofast.userlist.overPopup = true;

      var ulid = $(elt).data('ulid');
      var url,
              ogContext = Drupal.settings.ogContext,
              popup = $(elt).parent().find('.userlist-location-popup'),
              throbber = '<i aria-hidden="true" class="icon glyphicon glyphicon-refresh glyphicon-spin"></i>';

      //before loading hide all popup already displayed
      $('#edit-userlists').find('.userlist-location-popup>.details').children().remove();

      url = '/userlist/location_popup/' + ulid;
      if (ogContext && ogContext.groupType === 'node' && ogContext.gid) {
        url += '/' + ogContext.gid;
      }

      $.ajax({
        url: url,
        dataType: 'html',
        beforeSend: function (xhr) {
          Gofast.xhrPool = Gofast.xhrPool || {};
          Gofast.xhrPool.xhrShowPopup = xhr;
        },
        'complete': function () {
          delete Gofast.xhrPool.xhrShowPopup;
        },
        success: function (response) {
          if (Gofast.userlist.overPopup === true) {
            popup.find('.details').html(response);
            Drupal.attachBehaviors();
          }
        }
      });
    };

    Gofast.userlist.hidePopup = function (elt) {
      Gofast.userlist.overPopup = false;
      $(elt).parent().find('.userlist-location-popup>.details').children().remove();
    };

    Drupal.behaviors.gofastUserListPopup = {
      attach: function (context, settings) {
        var config = {
          sensitivity: 7,
          interval: 100,
          over: Gofast.userlist.showPopup,
          timeout: 0,
          out: Gofast.userlist.hidePopup
        };
        $('.userlist-location-popup:not(.gofast-popup-processed)').addClass('gofast-popup-processed').each(function () {
          $(this).hoverIntent(config);
        });
      }
    };

  })(jQuery, Gofast, Drupal);
</script>



