(Gofast, jQuery, Drupal, function () {
  Drupal.behaviors.gofastBluemind = {
    // when page is loaded
    attach: function (context, settings) {
      jQuery(document).ready(function () {
        // Add change event listener to the file input.
        jQuery('.form-file').on("change", function () {
          var fileInput = this;
          var filename = jQuery(fileInput).val().split('/').pop().split('\\').pop();
          jQuery(".uppy-status").html('<i class="fa fa-upload"></i> ' + filename);

          // Check the file size.
          var fileSize = fileInput.files[0].size; // Assuming only one file is selected.
          var maxFileSize = 9 * 1024 * 1024; // 9MB

          if (fileSize > maxFileSize) {
            // Display an alert or handle the error as needed.
            Gofast.toast(Drupal.t("File size exceeds the maximum allowed (9MB). Please choose a smaller file.", {}, { context: 'gofast:gofast_calendar' }), "error");

            // Optionally, you can clear the file input.
            jQuery(fileInput).val('');
            jQuery(".uppy-status").html('<i class="fa fa-upload"></i> '); // Clear the displayed filename.
          }
        });

        // Change the type attribute of color input field.
        jQuery('.form-type-color').attr('type', 'color');
      });
    }
  };
})(Gofast, jQuery, Drupal);
