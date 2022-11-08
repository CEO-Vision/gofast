
(function ($, Drupal, Gofast) {
  'use trict';

  $(document).ready(function () {
    if ($("#dashboard-block-last-commented").length > 0) {
      $.post(
        location.origin + "/dashboard/ajax/last_commented",
        function (data) {
          $("#dashboard-block-last-commented").replaceWith(data);
        }
      );
    }

    if ($("#dashboard-block-mail").length > 0) {
      $.post(location.origin + "/dashboard/ajax/mail", function (data) {
        $("#dashboard-block-mail").replaceWith(data);
      });
    }
  });
})(jQuery, Drupal, Gofast);


