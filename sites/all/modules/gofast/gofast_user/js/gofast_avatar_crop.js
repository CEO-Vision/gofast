(function($, Drupal, Gofast) {
  'use strict';

  // Refresh user thumbnail when updating profile avatar.
  $(document).on('avatarChange', function(e, data, uid) {
    var thumbnailUrl = data && data.thumbnailUrl;
    if (thumbnailUrl) {
      $('.user-picture[id|="' + uid + '"] img').attr('src', thumbnailUrl);
      $('.GofastUserProfile__picture img').attr('src', thumbnailUrl);
    }
    if (thumbnailUrl && Gofast.get("user").uid == uid) {
      $('.menu-profile.topbar-item img').attr('src', thumbnailUrl);
    }
  });


  Drupal.behaviors.avatar_crop = {
    attach: function(context, settings) {
      if ($('#gofast_crop_avatar').length) {
        $('#gofast_crop_avatar:not(.crop-processed)').addClass('crop-processed').each(function(e){
          $(document).trigger('crop');
        });
      } else {
        return;
      }

      var $image = document.getElementById('image');
      var saveHandler = function(el, cropper) {
        var src = $('#image').attr('src');
        var ext = "";

        if ((src.startsWith('blob:') || src.startsWith('data:'))  && window._inputImageExt) {
          ext = window._inputImageExt;
        }
        else {
          ext = src.split('.').pop();
        }
        // canvas.toDtaURL returns JPEG format if mimeType = image/jpeg, otherwise, it returns PNG format for the others mimeType.
        var result = cropper.getCroppedCanvas({maxWidth: 300,maxHeight:300}).toDataURL('image/' + ext, 1,0);
        var user_uid = $('#save').attr('uid');
        $.ajax({
          url: '/gofast/save/avatar',
          type: 'POST',
          dataType: 'json',
          data: {
            data: result.substring(result.indexOf(',') + 1),
            uid: user_uid,
            ext: ext
          },
          beforeSend: function(xhr) {
            $('#save').html('<span class="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span> ' + Drupal.t('Saving...', {}, {'context' : 'gofast'}));
            $('.crop-buttons.btn, .crop-buttons input').attr('disabled', 'disabled');

            //Commented because its not necessary ?
            //Gofast.xhrPool = Gofast.xhrPool || {};
            //Gofast.xhrPool.xhrSaveAvatar = xhr;
          },
          complete: function(xhr, status) {
             //delete Gofast.xhrPool.xhrSaveAvatar;
          },
          error: function(xhr, textStatus, err){
            var errorMsg = xhr.responseJSON && xhr.responseJSON.errorMsg || 'unknown';
            console.error(err, errorMsg);
            Gofast.toast(err + ': ' + errorMsg, 'error');
            $('#save > span').remove();
            $('#save').text(Drupal.t('Save', {}, {'context' : 'gofast'}))
            $('.crop-buttons.btn, .crop-buttons input').removeAttr('disabled');
            // Leave time for the user to see the error message before the cropper resets.
            setTimeout(function(){$('#modal-content button#reset').click()}, 1000);
          },
          async: true
        }).done(function(result) {
          if (result.status) {
            $(document).trigger('avatarChange', [result, user_uid]);
            Gofast.processAjax('/user/' + user_uid , false);
            Drupal.CTools.Modal.dismiss(); //auto close modal
          }
        });
      };

      // Class definition
      var GofastCropper = Gofast.getGofastCropper();
      if($('#img-cropper').length){
        GofastCropper.init($image, saveHandler);
      }
    }
  };
})(jQuery, Drupal, Gofast);
