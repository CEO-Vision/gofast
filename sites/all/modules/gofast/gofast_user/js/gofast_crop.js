(function($, Drupal, Gofast) {

  'use strict';

  Drupal.behaviors.crop = {
    attach: function(context, settings) {
      if ($('#gofast_crop_avatar').length > 0) {
        $('#gofast_crop_avatar:not(.crop-processed)').addClass('crop-processed').each(function(e){
          $(document).trigger('crop');
        });
      }
      var $image = document.getElementById('image');
      // Class definition
      var KTCropperDemo = function() {

        // Private functions
        var initCropperDemo = function() {
          // Cropper
          const cropper = new Cropper($image, {
            aspectRatio: 1,
            viewMode: 1,
            crop(event) {
              console.log(event.detail.x);
              console.log(event.detail.y);
              console.log(event.detail.width);
              console.log(event.detail.height);
              console.log(event.detail.rotate);
              console.log(event.detail.scaleX);
              console.log(event.detail.scaleY);

              var lg = document.getElementById('cropper-preview-lg');
              lg.innerHTML = '';
              lg.appendChild(cropper.getCroppedCanvas({width: 100, height: 100}));
            }
          });

          var buttons = document.getElementById('cropper-buttons');
          console.log(buttons);

          var methods = buttons.querySelectorAll('[data-method]');
          methods.forEach(function(button) {
            button.addEventListener('click', function(e) {
              var method = button.getAttribute('data-method');
              var option = button.getAttribute('data-option');
              var option2 = button.getAttribute('data-second-option');

              try {
                option = JSON.parse(option);
              }
              catch (e) {
              }

              var result;
              if (!option2) {
                result = cropper[method](option, option2);
              }
              else if (option) {
                result = cropper[method](option);
              }
              else {
                result = cropper[method]();
              }

              if (method === 'getCroppedCanvas') {
                var modal = document.getElementById('getCroppedCanvasModal');
                var modalBody = modal.querySelector('.modal-body');
                modalBody.innerHTML = '';
                modalBody.appendChild(result);
              }

              var input = document.querySelector('#putData');
              try {
                input.value = JSON.stringify(result);
              }
              catch (e) {
                if (!result) {
                  input.value = result;
                }
              }
            });
          });

          // Refresh user thumbnail when updating profile avatar.
          $(document).on('avatarChange', function(e, data, uid) {
            var thumbnailUrl = data && data.thumbnailUrl;
            if (thumbnailUrl) {
              $('.user-picture[id|="' + uid + '"] img').attr('src', thumbnailUrl);
            }
          });

          var $inputImage = $('#inputImage');
          var URL = window.URL || window.webkitURL;
          var blobURL;
          $inputImage.once(function(){
            $(this).change(function () {
              var files = this.files;
              var file;

              if (files && files.length) {
                file = files[0];
                var ext = files[0].name.split('.').pop();
                window._inputImageExt = ext;
                $('#no_avatar_message').remove();
                var reader = new FileReader();
                reader.readAsDataURL(file);
                reader.onload = function(e) {
                    // browser completed reading file - display it
                    cropper.replace(e.target.result,false);
                };
              }
            });
          })

          $('#save').once(function(){
            $(this).on('click',function(e) {

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
              console.log(result);
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
            });
          });
        };

        return {
          // public functions
          init: function() {
            initCropperDemo();
          },
        };
      }();
      if($('#img-cropper').length){
        KTCropperDemo.init();
      }
    }
  };

})(jQuery, Drupal, Gofast);
