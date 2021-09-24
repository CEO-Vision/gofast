(function($, Drupal, Gofast) {

  'use strict';
  
  Drupal.behaviors.crop = {
    attach: function(context, settings) {
      if ($('#gofast_crop_avatar').length > 0) {
        $(document).trigger('crop');
      }
    }
  };
  
  $(document).ready(function() {
    
    // Refresh user thumbnail when updating profile avatar.
    $(document).on('avatarChange', function(e, data, uid) {
      var thumbnailUrl = data && data.thumbnailUrl;
      if (thumbnailUrl) {
        $('.user-picture[id|="' + uid + '"] img').attr('src', thumbnailUrl);
      }      
    });
    
    $(document).on('crop', function() {
      if (!$("#current_image").attr("src") && $('#no_avatar_message').length < 1) {
        var message = Drupal.t("You don't have any avatar for now. ", {}, {'context' : 'gofast'})
                    + Drupal.t('Please click on ', {}, {'context' : 'gofast'})
                    +'<span class="fa fa-upload"></span>'
                    +Drupal.t(' to upload your avatar.', {}, {'context' : 'gofast'});
        $('.img-container-current').before('<div id="no_avatar_message">'+message+'</div>');
      }

      var console = window.console || { log: function () {} };
      var $image = $('#image');

      var result = '';
      var options = {
        aspectRatio: 1
      };

      var ext = null;
      var src = $image.attr('src');

      if (src.startsWith('blob:') && window._inputImageExt) {
        ext = window._inputImageExt;
      }
      else {
        ext = src.split('.').pop();
      }

      $('#reset').once(function() {
        $(this).click(function(e) {
          var currentSrc = $('#current_image').attr('src');
          ext = currentSrc.split('.').pop();
          $image.cropper('reset').cropper('replace', currentSrc);
        });
      });

      // Cropper
      $image.cropper(options);

      // Buttons
      if (typeof document.createElement('cropper').style.transition === 'undefined') {
        $('button[data-method="rotate"]').prop('disabled', true);
      }

      // Methods
      $(".docs-buttons").off('click', '**');
      $('.docs-buttons').on('click', '[data-method]', function () {
        var $this = $(this);
        var data = $this.data();
        var $target;

        if ($this.prop('disabled') || $this.hasClass('disabled')) {
          return;
        }

        if ($image.data('cropper') && data.method) {
          data = $.extend({}, data); // Clone a new one

          if (typeof data.target !== 'undefined') {
            $target = $(data.target);

            if (typeof data.option === 'undefined') {
              try {
                data.option = JSON.parse($target.val());
              } catch (e) {
                console.log(e.message);
              }
            }
          }

          result = $image.cropper(data.method, data.option, data.secondOption);

          if ($.isPlainObject(result) && $target) {
            try {
              $target.val(JSON.stringify(result));
            } catch (e) {
              console.log(e.message);
            }
          }
        }
      });

      $('#save').off('click', '**');
      $('#save').once(function(){
        $(this).on('click',function(e) {
          // canvas.toDtaURL returns JPEG format if mimeType = image/jpeg, otherwise, it returns PNG format for the others mimeType.
          result = $image.cropper('getCroppedCanvas',{maxWidth: 300,maxHeight:300}).toDataURL('image/' + ext,1.0); 
          var user_uid = $('#save').attr('uid');
          $.ajax({
            url: '/gofast/save/avatar',
            type: 'POST',
            dataType: 'json',
            data: {
              data: result.substring(result.indexOf(',') + 1),
              uid: user_uid ,
              ext: ext
            },
            beforeSend: function(xhr) {
              $('#save').html('<span class="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span> ' + Drupal.t('Saving...', {}, {'context' : 'gofast'}));
              $('.docs-buttons .btn, .docs-buttons input').attr('disabled', 'disabled');

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
              $('.docs-buttons .btn, .docs-buttons input').removeAttr('disabled');
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
        });
      });

      // Import image
      var $inputImage = $('#inputImage');
      var URL = window.URL || window.webkitURL;
      var blobURL;

      if (URL) {
        $inputImage.once(function(){
          $(this).change(function () {
            var files = this.files;
            var file;

            if (!$image.data('cropper')) {
              return;
            }

            if (files && files.length) {
              file = files[0];            
              $('#no_avatar_message').remove();

              if (/^image\/\w+$/.test(file.type)) {
                blobURL = URL.createObjectURL(file);
                $image.one('built.cropper', function () {
                  // Revoke when load complete
                  URL.revokeObjectURL(blobURL);
                  ext = file.name.split('.').pop();
                  window._inputImageExt = ext;
                }).cropper('reset').cropper('replace', blobURL);

                $inputImage.val('');
              } 
              else {
                window.alert(Drupal.t('Please choose an image file.', {}, {'context' : 'gofast'}));
              }
            }
          });
        });
      } 
      else {
        $inputImage.prop('disabled', true).parent().addClass('disabled');
      }
    });
  });
})(jQuery, Drupal, Gofast);
