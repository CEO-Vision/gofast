(function ($, Drupal, Gofast) {
  "use strict";

  // Refresh user thumbnail when updating profile avatar.
  $(document).on('ogLogoChange', function(e, src) {
    if (src) {
      $("#gofast-og-home-space-logo").css("backgroundImage", "url(" + src + "?id=" + Math.random() * 1000 + ")");
    }
  });

  Drupal.behaviors.avatar_crop = {
    attach: function (context, settings) {
      if (
        !$("#gofast_crop_og_logo").length ||
        $("#gofast_crop_og_logo.crop-processed").length
      ) {
        return;
      }
      $("#gofast_crop_og_logo").addClass("crop-processed");

      var $image = document.getElementById("image");
      var saveHandler = function (el, cropper) {
        var src = $("#image").attr("src");
        var ext = "";

        if (
          (src.startsWith("blob:") || src.startsWith("data:")) &&
          window._inputImageExt
        ) {
          ext = window._inputImageExt;
        } else {
          ext = src.split(".").pop();
        }
        // canvas.toDtaURL returns JPEG format if mimeType = image/jpeg, otherwise, it returns PNG format for the others mimeType.
        var result = cropper
          .getCroppedCanvas({ maxWidth: 300, maxHeight: 300 })
          .toDataURL("image/" + ext, 1, 0);
        var space_gid = $("#save").attr("gid");
        $.ajax({
          url: "/og/" + space_gid + "/space_logo",
          type: "POST",
          dataType: "json",
          data: {
            data: result.substring(result.indexOf(",") + 1),
            ext: ext,
          },
          beforeSend: function (xhr) {
            $("#save").html(
              '<span class="glyphicon glyphicon-refresh glyphicon-refresh-animate"></span> ' +
                Drupal.t("Saving...", {}, { context: "gofast" })
            );
            $(".crop-buttons.btn, .crop-buttons input").attr(
              "disabled",
              "disabled"
            );
          },
          error: function (xhr, textStatus, err) {
            var errorMsg =
              (xhr.responseJSON && xhr.responseJSON.errorMsg) || "unknown";
            console.error(err, errorMsg);
            Gofast.toast(err + ": " + errorMsg, "error");
            $("#save > span").remove();
            $("#save").text(Drupal.t("Save", {}, { context: "gofast" }));
            $(".crop-buttons.btn, .crop-buttons input").removeAttr("disabled");
            // Leave time for the user to see the error message before the cropper resets.
            setTimeout(function () {
              $("#modal-content button#reset").click();
            }, 1000);
          },
          async: true,
        }).done(function (result) {
          if (result.success) {
            Gofast.toast(Drupal.t('Image successfully changed!'), "success")
            $(document).trigger("ogLogoChange", [result.src]);
            Drupal.CTools.Modal.dismiss(); //auto close modal
          }
        });
      };
      // Class definition
      var GofastCropper = Gofast.getGofastCropper();
      if ($("#img-cropper").length) {
        GofastCropper.init($image, saveHandler);
      }
    },
  };
})(jQuery, Drupal, Gofast);
